"""Reusable ISO9660 reader for the Brave Fencer Musashi MODE2/2352 data track.

This is the FOUNDATION layer for the Phase 2 asset pipeline (.CD / PAC / LZSS),
so it is deliberately general: nothing here knows about SLUS_007.26 or any other
specific file. It only understands the on-disc geometry and the ISO9660 file
system on top of it.

Disc geometry (verified against the BFM USA dump)
-------------------------------------------------
The data track is stored as raw MODE2/2352 sectors. Each 2352-byte sector is::

    [ 12 sync ][ 4 header ][ 8 subheader ][ 2048 user data ][ 280 EDC/ECC ]
      0          12          16             24                 2072

So the 2048 bytes of user data for logical sector (LBA) N live at byte offset
``N * 2352 + 24`` in the BIN file. All ISO9660 structures are addressed in
logical sectors and read through that 2048-byte user-data window.

ISO9660 essentials
------------------
* The Primary Volume Descriptor (PVD) sits at LBA 16. Its user data starts with
  ``0x01`` (descriptor type "primary") followed by the ASCII magic ``CD001``.
* The PVD embeds the root directory record at offset 156 within its user data.
* A directory is a run of directory records packed into one or more sectors. A
  record whose length byte is 0 means "no more records in this sector" -> skip
  to the start of the next sector. Records never straddle a sector boundary.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass
from pathlib import Path
from typing import BinaryIO, Iterator

# --- Geometry constants -----------------------------------------------------

RAW_SECTOR_SIZE = 2352   # bytes per raw MODE2/2352 sector
USER_DATA_SIZE = 2048    # bytes of ISO9660 user data per sector
USER_DATA_OFFSET = 24    # 12 sync + 4 header + 8 subheader

# --- ISO9660 constants ------------------------------------------------------

PVD_LBA = 16                 # Primary Volume Descriptor is always at LBA 16
ISO_MAGIC = b"CD001"         # standard identifier, follows the descriptor type
VD_TYPE_PRIMARY = 0x01       # volume-descriptor type byte for the PVD
ROOT_RECORD_OFFSET = 156     # offset of the root dir record inside the PVD
VOLUME_ID_OFFSET = 40        # offset of the 32-byte volume identifier in the PVD
VOLUME_ID_LEN = 32

# Directory-record field offsets (relative to the start of a record).
DR_LENGTH = 0        # u8  : length of this record (0 => pad to next sector)
DR_EXTENT_LE = 2     # u32 : extent (data) LBA, little-endian
DR_DATA_LEN_LE = 10  # u32 : data length in bytes, little-endian
DR_FLAGS = 25        # u8  : file flags (bit 1 set => directory)
DR_NAME_LEN = 32     # u8  : length of the name field
DR_NAME = 33         # name bytes begin here

DIR_FLAG_DIRECTORY = 0x02  # file-flags bit 1


class Iso9660Error(Exception):
    """Raised when the BIN is missing, mis-shaped, or not a valid ISO9660."""


@dataclass(frozen=True)
class FileRecord:
    """One entry parsed from an ISO9660 directory.

    Attributes
    ----------
    name:
        File name with the ISO version suffix stripped (e.g. ``SLUS_007.26``).
    raw_name:
        File name exactly as stored on disc, version suffix included
        (e.g. ``SLUS_007.26;1``).
    lba:
        Logical sector of the file's data extent.
    size:
        Data length in bytes.
    is_dir:
        True if the record is a directory.
    """

    name: str
    raw_name: str
    lba: int
    size: int
    is_dir: bool


def _strip_version(raw_name: str) -> str:
    """Drop the trailing ``;N`` ISO version suffix if present."""
    semi = raw_name.find(";")
    return raw_name[:semi] if semi != -1 else raw_name


class Iso9660Image:
    """Read-only view of an ISO9660 file system on a MODE2/2352 data track.

    The image is opened lazily and read one logical sector at a time (a seek
    per sector), so the multi-hundred-megabyte track is never loaded whole.

    Typical use::

        with Iso9660Image(bin_path) as img:
            for rec in img.list_files():
                print(rec.name, rec.lba, rec.size)
            data = img.extract_file("SLUS_007.26")
    """

    def __init__(self, bin_path: str | Path):
        self.bin_path = Path(bin_path)
        if not self.bin_path.is_file():
            raise Iso9660Error(f"BIN data track not found: {self.bin_path}")

        size = self.bin_path.stat().st_size
        if size == 0 or size % RAW_SECTOR_SIZE != 0:
            raise Iso9660Error(
                f"{self.bin_path} is {size} bytes, which is not a whole number "
                f"of {RAW_SECTOR_SIZE}-byte MODE2/2352 sectors. This reader "
                f"expects a raw MODE2/2352 data track."
            )
        self.sector_count = size // RAW_SECTOR_SIZE

        self._fh: BinaryIO | None = open(self.bin_path, "rb")
        try:
            self._validate_pvd()
        except Exception:
            self.close()
            raise

    # -- context-manager plumbing -------------------------------------------

    def __enter__(self) -> "Iso9660Image":
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    def close(self) -> None:
        if self._fh is not None:
            self._fh.close()
            self._fh = None

    # -- low-level sector access --------------------------------------------

    def read_sector(self, lba: int) -> bytes:
        """Return the 2048 user-data bytes of logical sector ``lba``."""
        if self._fh is None:
            raise Iso9660Error("image is closed")
        if lba < 0 or lba >= self.sector_count:
            raise Iso9660Error(
                f"LBA {lba} out of range (0..{self.sector_count - 1})"
            )
        self._fh.seek(lba * RAW_SECTOR_SIZE + USER_DATA_OFFSET)
        data = self._fh.read(USER_DATA_SIZE)
        if len(data) != USER_DATA_SIZE:
            raise Iso9660Error(
                f"short read at LBA {lba}: got {len(data)} of "
                f"{USER_DATA_SIZE} bytes"
            )
        return data

    def read_extent(self, lba: int, size: int) -> bytes:
        """Return ``size`` bytes starting at logical sector ``lba``.

        Reads whole sectors and trims to ``size``; the file system stores files
        as runs of full sectors with the real length given separately.
        """
        if size < 0:
            raise Iso9660Error(f"negative extent size: {size}")
        out = bytearray()
        sectors_needed = (size + USER_DATA_SIZE - 1) // USER_DATA_SIZE
        for i in range(sectors_needed):
            out.extend(self.read_sector(lba + i))
        return bytes(out[:size])

    # -- ISO9660 parsing -----------------------------------------------------

    def _validate_pvd(self) -> None:
        """Read the PVD and stash the root record + volume id."""
        pvd = self.read_sector(PVD_LBA)
        if pvd[0] != VD_TYPE_PRIMARY or pvd[1:6] != ISO_MAGIC:
            raise Iso9660Error(
                "no ISO9660 Primary Volume Descriptor at LBA 16 "
                "(expected 0x01 'CD001'); is this a MODE2/2352 data track?"
            )
        self.volume_id = (
            pvd[VOLUME_ID_OFFSET : VOLUME_ID_OFFSET + VOLUME_ID_LEN]
            .rstrip(b" \x00")
            .decode("ascii", "replace")
        )
        # The root directory record is embedded directly in the PVD.
        root = self._parse_record(pvd, ROOT_RECORD_OFFSET)
        if root is None or not root.is_dir:
            raise Iso9660Error("PVD does not contain a valid root directory record")
        self.root = root

    # Smallest directory record that still has a (1-byte) name field: the 33
    # fixed header bytes plus at least one name byte.
    _MIN_RECORD_LEN = DR_NAME + 1

    @staticmethod
    def _parse_record(buf: bytes, offset: int) -> FileRecord | None:
        """Parse a single directory record at ``buf[offset:]``.

        Returns ``None`` when the length byte is 0 (sector padding) so callers
        can advance to the next sector.

        Validates that the record fits inside ``buf`` before touching any field,
        and converts any low-level ``struct``/index error into ``Iso9660Error``
        so malformed input never escapes the module's error contract.
        """
        try:
            if offset < 0 or offset >= len(buf):
                raise Iso9660Error(
                    f"directory record offset {offset} outside buffer "
                    f"(len {len(buf)})"
                )
            rec_len = buf[offset]
            if rec_len == 0:
                return None
            if rec_len < Iso9660Image._MIN_RECORD_LEN:
                raise Iso9660Error(
                    f"directory record at offset {offset} has length "
                    f"{rec_len}, below the {Iso9660Image._MIN_RECORD_LEN}-byte "
                    f"minimum"
                )
            if offset + rec_len > len(buf):
                raise Iso9660Error(
                    f"directory record at offset {offset} (length {rec_len}) "
                    f"runs past the end of the {len(buf)}-byte buffer"
                )
            rec = buf[offset : offset + rec_len]

            extent_lba = struct.unpack_from("<I", rec, DR_EXTENT_LE)[0]
            data_len = struct.unpack_from("<I", rec, DR_DATA_LEN_LE)[0]
            flags = rec[DR_FLAGS]
            name_len = rec[DR_NAME_LEN]
            if DR_NAME + name_len > rec_len:
                raise Iso9660Error(
                    f"directory record at offset {offset} declares a "
                    f"{name_len}-byte name that overflows its {rec_len}-byte "
                    f"length"
                )
            name_bytes = rec[DR_NAME : DR_NAME + name_len]
        except (struct.error, IndexError) as exc:
            raise Iso9660Error(
                f"malformed directory record at offset {offset}: {exc}"
            ) from exc

        # Entries 0x00 ("." / self) and 0x01 (".." / parent) use single-byte
        # names; decode everything else as plain ASCII.
        if name_bytes == b"\x00":
            raw_name = "."
        elif name_bytes == b"\x01":
            raw_name = ".."
        else:
            raw_name = name_bytes.decode("ascii", "replace")

        return FileRecord(
            name=_strip_version(raw_name),
            raw_name=raw_name,
            lba=extent_lba,
            size=data_len,
            is_dir=bool(flags & DIR_FLAG_DIRECTORY),
        )

    def iter_directory(self, dir_record: FileRecord) -> Iterator[FileRecord]:
        """Yield every child record of ``dir_record``, skipping '.' and '..'.

        Handles directories that span multiple sectors generally: the directory
        data length tells us how many sectors to walk, and a zero length byte
        within a sector means "advance to the next sector".
        """
        if not dir_record.is_dir:
            raise Iso9660Error(f"{dir_record.name!r} is not a directory")

        sectors = (dir_record.size + USER_DATA_SIZE - 1) // USER_DATA_SIZE
        for s in range(sectors):
            sector = self.read_sector(dir_record.lba + s)
            offset = 0
            while offset < USER_DATA_SIZE:
                rec_len = sector[offset]
                if rec_len == 0:
                    # Padding to the end of this sector; jump to the next one.
                    break
                # Records never straddle a sector boundary; a length that would
                # run past the end of this sector means the directory data is
                # corrupt, not that another sector continues the record.
                if offset + rec_len > USER_DATA_SIZE:
                    raise Iso9660Error(
                        f"directory record at sector offset {offset} (length "
                        f"{rec_len}) straddles the {USER_DATA_SIZE}-byte sector "
                        f"boundary in {dir_record.name!r}"
                    )
                record = self._parse_record(sector, offset)
                if record is not None and record.raw_name not in (".", ".."):
                    yield record
                offset += rec_len

    # -- public convenience API ---------------------------------------------

    def list_files(self, directory: FileRecord | None = None) -> list[FileRecord]:
        """Return a directory's entries (excluding '.' and '..').

        ``directory`` defaults to the volume root. Pass a directory
        ``FileRecord`` (e.g. one returned by :meth:`find`) to list a
        subdirectory instead. This does not recurse into subdirectories.
        """
        return list(self.iter_directory(directory or self.root))

    def find(self, name: str, directory: FileRecord | None = None) -> FileRecord | None:
        """Look up an entry by name within a single directory.

        Searches ``directory`` (default: the volume root); it does not recurse
        into subdirectories. Matches against both the version-stripped name and
        the raw on-disc name, so ``"SLUS_007.26"`` and ``"SLUS_007.26;1"`` both
        resolve.
        """
        for rec in self.iter_directory(directory or self.root):
            if name in (rec.name, rec.raw_name):
                return rec
        return None

    def extract_file(self, name: str, directory: FileRecord | None = None) -> bytes:
        """Return the raw bytes of a file looked up by name in one directory.

        Searches ``directory`` (default: the volume root); it does not recurse
        into subdirectories.
        """
        rec = self.find(name, directory)
        if rec is None:
            where = "root directory" if directory is None else f"{directory.name!r}"
            raise Iso9660Error(f"file not found in {where}: {name!r}")
        if rec.is_dir:
            raise Iso9660Error(f"{name!r} is a directory, not a file")
        return self.read_extent(rec.lba, rec.size)
