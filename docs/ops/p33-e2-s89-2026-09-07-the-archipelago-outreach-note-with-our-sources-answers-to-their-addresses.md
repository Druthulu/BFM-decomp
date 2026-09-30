### P33 E2 (S89, 2026-09-07) — the Archipelago outreach note, with our source's answers to their addresses
- `docs/outreach/archipelago.md` (NEW; in `doc_links`' default set until P34 task 6 untracked the folder — sent, local only). Read from `AegeusEvander/Brave-Fencer-Musashi-AP-World`
  (v0.8.1, last push 2026-09-07; `client.py` 5,522 lines / 342 addresses; runtime code injection `patch/en/*c.bin` + `*Hooks.bin`;
  no license). **Derived for them and banked in `docs/memory-map.md` (G5/code-derived):** their day-of-week read `0x078eba` is
  CORRECT — `func_8014B084` (shared) does `day = day+1` (u16 0x80078EAC, wraps to 1 at 0x16E) and `dow = (dow+1) % 7` (u8
  0x80078EBA) → our `dayCounter` row corrected u8 → u16 and the "dow not yet separable" note resolved; their patch sites resolved
  to functions by a scan of every `.run/sig.ov_*.jsonl` (site ∈ [addr, addr+nbytes)): `0x8013F430` → `func_8013F350` (490 ins),
  `0x8014BCF8` → `func_8014BCEC` (14 ins: `bp_max (0x80078EB6) += a1`, clamp 0x662), `0x8015A7E4` → `func_8015A3C8` (493 ins;
  the patch is GONE from v0.8.1, so the memory map's "+0x2A8 vs +0x33C" inconsistency is marked HISTORIC), Time-Sanity hook
  `0x80146280` → `func_80146128` (142 ins) — each 141/141 location-overlay images, i.e. shared engine bodies; `0x8018E096` is
  per-map (7 overlays, 7 functions). **Open question #13 ANSWERED:** the client matches ASCII `SLUS-00726MUSASHI` at kernel-area
  0x8000BA94 with a fallback cascade; the game's own copy is `BASLUS-00726MUSASHI` at **0x80072DFC** in EXE `.data` (fileoff
  0x635FC, disc sector 222), so their `0x072e02` fallback is offset by 4 and inert on US. The note (GitHub issue text + Discord
  short form, plain style) asks for their unpublished US RAM notes and attribution consent; **Drew sends it after the flip.**
- **SENT 2026-09-08 (P34 task 3, Drew, in his words):** the GitHub issue
  **<https://github.com/AegeusEvander/Brave-Fencer-Musashi-AP-World/issues/1>** ("Decomp of BFM (US) is public, might be useful for
  the AP world", opened 2026-09-08T18:10:19Z, state open, 0 comments at the time of writing; their repo: issues on, no license, last
  push 2026-09-07). **Pending by name (P9):** their reply — handled per `docs/outreach/archipelago.md` §5 (every address they share →
  a memory-map row with `Source/Provenance` = "AP-world (AegeusEvander), <date>, <where>" and `Confidence` = `reported`, promoted only
  by Ghidra or a live datapoint; coined names via `config/symbols.us.txt` + `tools/ghidra_apply_symbols.sh`; if no reply within a
  month, note it and move on — the deliverable is the offer).

