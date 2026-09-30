# disc-dump-location

The legally-owned BFM USA BIN/CUE dump is at `/mnt/z/Storage/git/BFM-decomp/Brave Fencer Musashi (USA)/` (Windows `Z:\Storage\git\BFM-decomp\Brave Fencer Musashi (USA)`). Drew corrected me here on 2026-06-13 after I guessed a wrong `/mnt/z/Games/Emu/...` copy.

- **Track 1** `...(Track 1).bin` = 364,846,944 B — the MODE2/2352 data track holding the ISO9660 volume + every `.CD` file.
- Tracks 2–4 are CD-DA AUDIO (each `(Track N).bin` = 150-sector INDEX 00→01 pregap + audio). The 3 `.DA` ISO files (ST01_13A.DA=Track2, ST01_13B.DA=Track3, DUMMY_DA.DA=Track4) point into them.
- **Scope change 2026-06-13 (Drew):** stage ALL 4 tracks + the `.cue` to ext4 `disks/`, and extract the `.DA` files too. `extract.py` extracts them as raw 2352-byte/sector audio (sizes differ from the 2048-based ISO entry). Supersedes the earlier "Track 1 only / .DA out of scope" plan.
- Per H2 the dump is read once, **not built against** — copied to ext4 `disks/` (gitignored) for fast iteration instead of reading repeatedly over the slow 9P `/mnt` bridge.
- The raw dump is never committed (gitignore firewall, survives even the H1 relaxation in [[rom-content-git-policy]]).
