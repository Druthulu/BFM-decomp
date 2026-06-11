# bfm_extract — disc extraction tooling

Phase 1 tooling for the Brave Fencer Musashi (PS1, SLUS-00726 USA)
decompilation. It reads the game's MODE2/2352 data track, walks the ISO9660
file system, and extracts + validates the main executable `SLUS_007.26`.

## What's here

- **`iso9660.py`** — the reusable core. `Iso9660Image` opens a raw MODE2/2352
  BIN data track, reads logical sectors (the 2048 user-data bytes at +24 inside
  each 2352-byte sector), parses the Primary Volume Descriptor and root
  directory (multi-sector directories handled generally), and exposes
  `list_files()`, `find(name)`, `extract_file(name)`, and lower-level
  `read_sector` / `read_extent`. It knows nothing about any specific file — it
  is the foundation Phase 2 will extend with the .CD / PAC / LZSS pipeline.
- **`extract_exe.py`** — Phase 1 CLI. Locates `SLUS_007.26` via the ISO walk
  (not a hardcoded offset), writes it verbatim (PS-EXE header included, because
  `ghidra_psx_ldr` reads that header), validates the magic + five header fields
  + the exact `0x65000` size, and prints a PASS/FAIL report with the SHA1. Also
  offers `--verify-disc`, which hashes the entire Track-1 BIN and compares it to
  redump's published values to confirm the dump is canonical.

## Usage

The project is **all-in-WSL** (Linux-first): everything runs inside WSL2 Ubuntu
on a single ext4 clone. The tool is stdlib-only and OS-portable — invoke it with
`python3` on Linux/WSL (and with `python` on a Windows host; the two behave
identically). Run from the repo root:

```sh
# Extract + validate using the default dump path and gitignored output path
python3 tools/bfm_extract/extract_exe.py

# List the 27 root-directory entries (LBA / size / name) and exit
python3 tools/bfm_extract/extract_exe.py --list

# Verify the dump is the canonical redump dump (streams the whole ~348 MB BIN;
# checks Track-1 SHA1 + CRC32) and exit
python3 tools/bfm_extract/extract_exe.py --verify-disc

# Override the input track and/or output path
python3 tools/bfm_extract/extract_exe.py \
    --bin "Brave Fencer Musashi (USA)/Brave Fencer Musashi (USA) (Track 1).bin" \
    --out extracted/SLUS_007.26
```

The CLI exits nonzero on any validation failure, on a missing BIN, or on a BIN
that is not shaped like a MODE2/2352 track.

### `--verify-disc` — proving the dump is canonical

`--verify-disc` computes the SHA1 and CRC32 of the **entire** Track-1 BIN
(streamed in 1 MiB chunks, never loaded whole) and compares them against the
redump-published values for SLUS-00726 (USA):

- SHA1 `b44f0f0a19936f23b26188b658e13201a6a9c211`
- CRC32 `c238191b`
- reference build date `1998-08-25`

A PASS means the local dump is byte-for-byte the canonical redump image, which
transitively validates the extracted `SLUS_007.26` (whose own hash is not
publicly documented). The extracted EXE's expected SHA1 is
`143dbb89f34491258bbc27810d0a12ec8b43a8dd`.

## Output is ROM-derived and gitignored

The default output goes to `extracted/SLUS_007.26`. The `extracted/` directory
is gitignored on purpose: it is derived from the game disc and must **never** be
committed (see the ROM-content firewall in `PROJECT_CONTEXT.md`). Bring your own
disc dump.
