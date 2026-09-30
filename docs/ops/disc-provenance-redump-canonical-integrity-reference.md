## Disc provenance (redump — canonical integrity reference)

The `SLUS_007.26` executable's own hash is not published anywhere (redump hashes disc *tracks*, not inner files), so dump authenticity is proven at the track level. `tools/bfm_extract/extract_exe.py --verify-disc` checks the Track-1 BIN against these:

| Track 1 (data) | Value |
|---|---|
| SHA1 | `b44f0f0a19936f23b26188b658e13201a6a9c211` |
| CRC32 | `c238191b` |
| MD5 | `838e9ecf8b4e4810f3f82228b40e77d8` |
| EXE build date | 1998-08-25 |

A Track-1 match proves the dump is the canonical redump dump, which transitively validates the extracted EXE (our own SHA1 `143dbb89f34491258bbc27810d0a12ec8b43a8dd`, 413,696 bytes — stable, independently reproduced from raw sectors). Audio tracks 2–4 SHA1s are in the research archive if ever needed.

---

