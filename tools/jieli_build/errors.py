"""Errors shared by the Jieli build helpers."""


class BuildError(RuntimeError):
    """Raised when a required Jieli build input is unavailable."""
