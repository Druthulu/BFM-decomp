# wsl-disk-capped-75gb

The WSL2 disk (`/dev/sdd`, `ext4.vhdx`) was resized from WSL's 1 TB default down to
**75 GB (73 GiB usable)** on 2026-08-29. As of then: 38 GB live, ~32 GB free.
This is a HARD ceiling — ext4 cannot grow past it.

**Why it was done:** the vhdx had bloated to 111.6 GiB while holding only 38 GB of
live data, leaving C: with 11 GB free. Root cause: WSL creates a 1 TB ext4 filesystem
inside a dynamically-growing vhdx, and ext4's Orlov allocator deliberately places each
new *directory* in a block group with above-average free space. The `.run/wave_*`
pattern (hundreds of new top-level dirs) scattered data across 8192 block groups —
live data was smeared over 820 GiB of address space in 1363 groups. A dynamic vhdx
can only release whole 32 MB blocks, and nearly every touched block still held some
live data, so `compact vdisk` reclaimed ~7 GB of a possible 66. Zero-fill and sparse
VHD both fail or are unsafe here. `wsl --manage <distro> --resize` was the fix:
resize2fs relocated 33 GB down from above the boundary and packed data into 553 groups.
Result: vhdx 111.6 -> 53.3 GiB, C: 11.2 -> 69.9 GB free.

**Why it matters:** `.run/` is ~20 GB and grows every wave. With only ~32 GB of
headroom, a big fleet run can now fail with ENOSPC instead of the disk silently
growing. That failure will look like a mysterious mid-wave build error.

**How to apply:**
- Watch `df -h /` before launching large waves; prune old `.run/wave_*` when tight.
- The vhdx will still drift 53 -> 75 GiB over time (spreading is confined, not fixed).
  That is expected, not a new problem.
- Reclaim recipe (works now that data is packed): `sudo fstrim -av` -> `wsl --shutdown`
  -> diskpart `compact vdisk`. Do NOT bother with zero-fill.
- Need more room? GROWING is the supported direction and is safe:
  `wsl --shutdown` then `wsl --manage Ubuntu-24.04 --resize 150GB`.
- Sparse VHD (`--set-sparse`) is gated behind `--allow-unsafe` by Microsoft for
  data-corruption risk — do not use it.

Related: [[no-tmp-project-local-data]] (.run/ is the gitignored runtime scratch dir).
