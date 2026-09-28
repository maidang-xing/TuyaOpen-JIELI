import hashlib
import os
import tempfile
import unittest
from pathlib import Path
from unittest import mock

from jieli_build import (
    BuildError,
    WINDOWS_TOOLCHAIN_INSTALLER_NAME,
    WINDOWS_TOOLCHAIN_INSTALLER_SHA256,
    _sha256_of,
    _verify_installer,
    download_windows_toolchain_installer,
)


class _FakeResponse:
    """Minimal stand-in for the urlopen() context manager."""

    def __init__(self, payload):
        self._payload = payload
        self.headers = {"Content-Length": str(len(payload))}

    def __enter__(self):
        return self

    def __exit__(self, *exc_info):
        return False

    def read(self, size=-1):
        if size is None or size < 0:
            chunk, self._payload = self._payload, b""
            return chunk
        chunk, self._payload = self._payload[:size], self._payload[size:]
        return chunk


def _write(path, payload):
    path.write_bytes(payload)
    return hashlib.sha256(payload).hexdigest()


class InstallerChecksumTest(unittest.TestCase):
    def test_pinned_digest_is_well_formed(self):
        self.assertEqual(len(WINDOWS_TOOLCHAIN_INSTALLER_SHA256), 64)
        self.assertEqual(WINDOWS_TOOLCHAIN_INSTALLER_SHA256, WINDOWS_TOOLCHAIN_INSTALLER_SHA256.lower())
        int(WINDOWS_TOOLCHAIN_INSTALLER_SHA256, 16)

    def test_sha256_streams_the_whole_file(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            payload = bytes(range(256)) * 8192  # spans several read chunks
            target = Path(temp_dir) / "blob.bin"
            digest = _write(target, payload)

            self.assertEqual(_sha256_of(target), digest)

    def test_verify_installer_accepts_the_pinned_digest(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            target = Path(temp_dir) / "installer.exe"
            digest = _write(target, b"MZ" + b"payload")

            with mock.patch("jieli_build.WINDOWS_TOOLCHAIN_INSTALLER_SHA256", digest):
                _verify_installer(target)

    def test_verify_installer_rejects_a_mismatched_digest(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            target = Path(temp_dir) / "installer.exe"
            _write(target, b"MZ" + b"payload")

            with self.assertRaises(BuildError) as caught:
                _verify_installer(target)

            self.assertIn("checksum mismatch", str(caught.exception))

    def test_verify_installer_reports_an_unreadable_file(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            missing = Path(temp_dir) / "absent.exe"

            with self.assertRaises(BuildError) as caught:
                _verify_installer(missing)

            self.assertIn("cannot read", str(caught.exception))


@unittest.skipUnless(os.name == "nt", "the installer download is Windows-only")
class InstallerDownloadTest(unittest.TestCase):
    def test_discards_a_cached_installer_that_fails_verification(self):
        payload = b"MZ" + b"good payload" * 256  # above the minimum-size guard
        digest = hashlib.sha256(payload).hexdigest()

        with tempfile.TemporaryDirectory() as temp_dir:
            root = Path(temp_dir)
            cached = root / ".tools" / WINDOWS_TOOLCHAIN_INSTALLER_NAME
            cached.parent.mkdir(parents=True)
            cached.write_bytes(b"MZ" + b"stale payload" * 256)

            with mock.patch("jieli_build.WINDOWS_TOOLCHAIN_INSTALLER_SHA256", digest), \
                    mock.patch("urllib.request.urlopen", return_value=_FakeResponse(payload)):
                result = download_windows_toolchain_installer(root)

            self.assertEqual(result, cached)
            self.assertEqual(cached.read_bytes(), payload)

    def test_rejects_a_download_that_fails_verification(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            root = Path(temp_dir)

            with mock.patch("urllib.request.urlopen",
                            return_value=_FakeResponse(b"MZ" + b"tampered" * 256)):
                with self.assertRaises(BuildError) as caught:
                    download_windows_toolchain_installer(root)

            self.assertIn("checksum mismatch", str(caught.exception))
            self.assertEqual(list((root / ".tools").glob("*")), [])

    def test_keeps_a_cached_installer_that_matches(self):
        payload = b"MZ" + b"cached payload" * 256
        digest = hashlib.sha256(payload).hexdigest()

        with tempfile.TemporaryDirectory() as temp_dir:
            root = Path(temp_dir)
            cached = root / ".tools" / WINDOWS_TOOLCHAIN_INSTALLER_NAME
            cached.parent.mkdir(parents=True)
            cached.write_bytes(payload)

            with mock.patch("jieli_build.WINDOWS_TOOLCHAIN_INSTALLER_SHA256", digest), \
                    mock.patch("urllib.request.urlopen", side_effect=AssertionError("must not download")):
                result = download_windows_toolchain_installer(root)

            self.assertEqual(result, cached)


if __name__ == "__main__":
    unittest.main()
