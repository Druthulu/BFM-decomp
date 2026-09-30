### WSL2 memory reclaim (2026-09-02)

`C:\Users\user\.wslconfig` sets `memory=32GB` / `swap=16GB` (lowered from 48GB on 2026-09-02 at Drew's request, leaving 32GB to Windows). **`autoMemoryReclaim=gradual` was
added 2026-09-02** and takes effect only after `wsl --shutdown` from Windows.

Without it WSL2 grows `vmmemWSL` to cover Linux's page cache and never returns it to the host:
Windows Task Manager showed **30 GB held while Linux itself was using 4 GB** and ~22 GB was
reclaimable cache (a gate wave reads the 450 MB `asm/` tree plus every build object, so the cache
fills fast). Nothing is leaking — but the host does not get the memory back on its own.

* **Reclaim now, no restart:** `sync; sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'` (measured
  2026-09-02: 20 GB free -> 43.6 GB free). Costs a re-read on the next build, never correctness.
* **Automatic, until the config applies:** `.run/memkeeper.sh` (nohup'd) drops the cache whenever it
  exceeds 12 GB, every 5 minutes, logging to `.run/memkeeper.log`.
* `autoMemoryReclaim=dropcache` is the aggressive variant if `gradual` proves too slow.


