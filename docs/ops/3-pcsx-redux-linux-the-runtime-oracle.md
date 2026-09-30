## §3 PCSX-Redux (Linux) — the runtime oracle

**Role:** Ghidra is the static oracle; PCSX-Redux is the **runtime oracle**. It proves overlay load addresses by live RAM comparison, validates decompressed blobs byte-for-byte against what the game actually loads, and drives the debug-menu/loader RE.

- **Install:** Linux AppImage from `https://distrib.app/pub/org/pcsx-redux/project/dev-linux-x64` (no stable pin — record the build date). **As-built (2026-06-13):** `tools/pcsx-redux/PCSX-Redux-HEAD-x86_64.AppImage` (87.5 MB, ELF static-pie, BuildID `db3b55ac…`). **distrib.app is a JS SPA — not curl-able headlessly** (the `dev-linux-x64` URL returns only an HTML shell; the real file is numeric-ID-gated); download via a browser. Runs directly under WSLg (FUSE 3.14.0 present; no `--appimage-extract` needed). Docs: `https://pcsx-redux.consoledev.net`. Ships OpenBIOS (boots without a retail BIOS dump). Launch with disc + auto-run: `./tools/pcsx-redux/PCSX-Redux-HEAD-x86_64.AppImage -iso "<cue>" -run`.
- **RAM dumps (primary use):** enable the built-in web server, then
  **`GET http://127.0.0.1:8081/api/v1/cpu/ram/raw`** returns the full 2 MB RAM image — diff slices of it against our extractor's output to prove byte-identity. (Port **8081**, resolved at Phase 3 install — ledger #4 — moved off 8080 to avoid the GhidrAssistMCP collision. **Verified 2026-06-13:** returns exactly 2,097,152 B; RAM[0x10000:] == extracted `SLUS_007.26`[0x800:] byte-for-byte.)
  > ✅ **Port collision (RESOLVED 2026-06-13):** PCSX-Redux's web server defaults to `localhost:8080` — same as GhidrAssistMCP. GhidrAssistMCP stays on 8080 (`.mcp.json`); the Redux web server moves to **8081** via `~/.config/pcsx-redux/pcsx.json` → `emulator.Debug.WebServer=true` + `emulator.Debug.WebServerPort=8081` (GUI: Configuration → Emulation → Web Server). Edit `pcsx.json` only while Redux is **stopped** (it rewrites the file on exit).
- **Lua scripting:** LuaJIT 2.1.0-beta3 (Lua 5.2 compat), FFI direct memory access; console + editor under the Debug menu. Gotcha: the editor autosaves to `pcsx.lua` and reloads it at startup — a crashing script wedges the emulator across restarts (delete `pcsx.lua` to recover); long-running scripts must yield via coroutines (~15 ms/frame budget).
- **Debugger:** fully featured MIPS debugger, VRAM/SPU viewers. GDB server on port 3333 (Configuration → Emulation → Enable GDB server); for Ghidra-attached debugging launch Redux with `-interpreter -debugger -gdb` (dynarec breaks debugging) and connect `gdb-multiarch -i mi2` → `target remote localhost:3333`.
- PSX RAM at 0x80000000 mirrors physical 0x0 (0x800425D0 ≡ 0x000425D0) — relevant when reading dump offsets.

---

