"""bfm_extract - Brave Fencer Musashi disc extraction tooling (Phase 1+).

The reusable core is :class:`Iso9660Image` in :mod:`iso9660`, which reads the
MODE2/2352 data track and walks the ISO9660 file system. Phase 2 will build the
.CD / PAC / LZSS pipeline on top of it.
"""

from .iso9660 import FileRecord, Iso9660Error, Iso9660Image

__all__ = ["Iso9660Image", "Iso9660Error", "FileRecord"]
