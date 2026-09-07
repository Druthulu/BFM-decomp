# Outreach: the Brave Fencer Musashi Archipelago world (P33 E2)

> **What this is (2026-09-07).** The note Drew sends to the author of the BFM Archipelago world after the public flip, the
> facts behind every sentence in it, and what we do with the reply. Everything numeric below was read from the world's
> repository on 2026-09-07 (as data, X2) or derived from our own source and disc.

## 1. What Archipelago is, and what the BFM world is

**Archipelago** (archipelago.gg, `ArchipelagoMW/Archipelago`) is a multi-game *multiworld randomizer*: several players play
several different games at once; each game's items are shuffled into the item locations of all the games in the session,
so finding a chest in one game may send an item to another player's game. Each supported game is a **world** (an
`.apworld` plugin): the randomization logic (items, locations, regions, rules) plus a **client** that reads and writes the
running game's memory to detect checks and grant items. Console games are driven through an emulator connector; for
PlayStation that is BizHawk's Lua bridge, which exposes `MAIN_RAM` (the 2 MB of PS1 RAM, offset 0 = `0x80000000`).

**The BFM world** — `github.com/AegeusEvander/Brave-Fencer-Musashi-AP-World`, author AegeusEvander, world version **0.8.1**,
`minimum_ap_version 0.6.7`, BizHawk 2.7+ only, **US and JP discs** (a `jp_version` flag applies per-block deltas), no license
file, actively developed (commits 2026-05-20 → **2026-09-07**), 2 stars. Randomization: *which Bincho holds which NPC* is
shuffled; the goal is rescuing every NPC; castle NPCs can sit in other players' worlds; options include Time Sanity and a
BP Sanity mode. Technically it is a RAM-driven world: `client.py` (5,522 lines) polls **342 distinct addresses**, and since
v0.3.0 it needs no disc patch — it **injects code at runtime**: compiled MIPS blobs (`patch/en/*c.bin`, e.g. `setTimec.bin`,
`fixBinchoIDc.bin`, `writeBinchoc.bin`) written into RAM plus one-word `*Hooks.bin` jumps patched into the game's own
functions. That is exactly the surface a matching decompilation serves: every hook site and every polled address now has a
named function or variable behind it, in C.

**Why they matter to us:** `client.py` was our richest US RAM source in Phase 3 (memory-map §3.4–§3.6 and §4.2 cite it in
14 rows, region-tagged per G5); the README's Special-thanks section credits the world. `PROJECT_CONTEXT.md`'s parking lot
asked for this contact at Gen2 ("their BFM world has unpublished US RAM research").

## 2. What we can hand them (derived today, each with its evidence)

| Their datum (`client.py` v0.8.1, MAIN_RAM offsets) | What our source says | Evidence |
|---|---|---|
| `0x078eba` "#32 day of the week" | **Correct.** The shared rollover function `func_8014B084` does `day = day + 1` (u16 at `0x078eac`, wraps to 1 at 0x16E = 366) and `dow = (dow + 1) % 7` (u8 at `0x078eba`). Our memory map had listed the day counter as a u8 and "dow not yet separable" — corrected by this reading. | `src/shared/engine_core.h` `DEFINE_func_8014B084` (line ≈114752); memory-map §3.4 rows 0x80078EAC / 0x80078EBA |
| max-BP patch: nop the `addu $v0,$a1` at `0x14bcf8` | Inside `func_8014BCEC(a0, a1)`, 14 instructions: `bp_max (u16 at 0x078eb6) += a1`, clamped to `0x662`. The nop removes the increase. | `engine_core.h` line ≈115082; sig registry: the site falls in `func_8014bcec` in all 141 location-overlay images scanned |
| scroll-cursor patch site `0x13f430` | Inside `func_8013F350` (490 ins) | same scan, 141/141 |
| town-ID check `andi $v0,$s0,0x4000` at `0x15a7e4` | Inside `func_8015A3C8` (493 ins). **No longer in client.py v0.8.1** (town/portal handling now writes portal-table entries via `fix_town_id`), which also retires our memory map's "JP delta +0x2A8 vs +0x33C" inconsistency as historic. | same scan; `grep 15a7e4 client.py` = 0 hits |
| Time-Sanity hook: `0x146280` (`time_hook`, JP +0x2D0) | Inside `func_80146128` (142 ins): a jump rewritten to the injected `setTimec.bin` routine | sig scan |
| entrance byte `0x18e096` (1 → 0 "to prevent softlock") | Per-map code: seven location overlays carry code there, seven different functions — a byte inside an instruction immediate, not a shared body | sig scan (7 hits, 7 names) |
| version check: `SLUS-00726MUSASHI` at `0x00ba94`, fallbacks `0x009f9a`, `0x072e02`, then `SLUS_007.26;1` at eight addresses, then JP `SLPS_014.90;1` | The game's own copy is the product-code string **`BASLUS-00726MUSASHI` at `0x072dfc`** (EXE `.data`; disc Track 1 sector 222). So the `0x072e02` fallback reads from the string's 5th character and can never match on the US disc — harmless, the kernel-area check (a BIOS/emulator-dependent copy of the disc ID) hits first. This closes our memory-map open question #13. | `extracted/retail/SLUS_007.26` fileoff 0x635FC; the disc scan |

The three shared sites (`func_8013F350`, `func_8014BCEC`, `func_8015A3C8`) and the hook function `func_80146128` are engine
bodies that are byte-identical in every location overlay — one C definition in `src/shared/engine_core.h` covers every map.
The scan behind the "141/141" rows: for each `.run/sig.ov_*.jsonl`, the function whose `[addr, addr+nbytes)` contains the
site (`tools/…` one-off in the S89 log; re-run from the registries, never from memory).

## 3. What we ask them

1. **US RAM research beyond `client.py`** — notes, spreadsheets, refuted addresses. We record each datum as a memory-map row
   with provenance (G5: source, region, confidence `reported` until verified in Ghidra or live) and name our symbols after
   their findings where they are the discoverer.
2. **Attribution consent** — their repository has no license file. We already cite `client.py` addresses as facts with
   attribution; the note asks whether that is fine and offers a link back (already in the README).
3. Nothing else. No request to change their code; the version-check offset is offered as information.

## 4. The message (Drew sends; GitHub issue on their repo, which has issues enabled)

> **Authorship rule (Drew, S89, 2026-09-07):** written the way a developer writes an issue, short and plain, no code spans, no bullet
> walls, no "evidence" scaffolding. Rewritten from the §2 facts, not a model draft with the tells taken out (the permuter maintainer
> spotted the de-telled version at once; the dense backtick formatting was the likely giveaway). No AI acknowledgement. Edit freely.

**Title:** Decomp of BFM (US) is public, might be useful for the AP world

**Body:**

```
Hey, I've been working on a matching decompilation of Brave Fencer Musashi (USA) and it's public
now: https://github.com/Druthulu/BFM-decomp. The whole exe and all the streamed modules rebuild
byte for byte from C, so basically every address your client pokes at has a function or a
variable behind it now.

Your client.py was a big help early on for US RAM addresses (you're in the README credits), so a
few things I found going back through it against the source:

- day of week at 0x078eba is correct. The rollover function bumps the day counter (u16 at
  0x078eac, wraps back to 1 at 366) and does dow = (dow + 1) % 7.
- the max BP patch at 0x14bcf8 is in a tiny 14 instruction function that does
  bp_max (u16 at 0x078eb6) += arg and clamps at 0x662. Nopping the addu just kills the increase,
  so that all checks out.
- the scroll cursor site (0x13f430), the old town id check (0x15a7e4) and your time sanity hook
  (0x146280) are all in shared engine code that's identical in every location overlay, so one C
  file covers all of them. The entrance byte at 0x18e096 is different per map though.
- minor: the exe's copy of the id string is actually "BASLUS-00726MUSASHI" starting at 0x072dfc,
  so the fallback read at 0x072e02 starts 4 bytes into it and won't ever match on US. Doesn't
  matter since the 0xba94 check hits first, just thought you'd want to know.

If you've got US RAM notes beyond what's in client.py I'd be glad to fold them in with credit, and
if you want any address resolved to its function just ask. Also wanted to check you're ok with us
citing client.py addresses in our memory map (the repo has no license so figured I'd ask).

Function names are still func_XXXXXXXX style for now, naming is the next big job.
```

**Short form** (Archipelago Discord, the game's channel, if preferred): "BFM (USA) has a full matching decomp now:
https://github.com/Druthulu/BFM-decomp. Went through client.py against the source, your day of week address checks out, the
max BP patch is in a 14 instruction function, every hook site has a named function now. Happy to look up any address."

**Send only after the flip** (the message links the public repository).

## 5. After the reply

- Every address or note they share → a memory-map row with `Source/Provenance` = "AP-world (AegeusEvander), <date>,
  <where>" and `Confidence` = `reported`, promoted to `verified` only by Ghidra or a live datapoint (R10/G5). Names they
  coined go into `config/symbols.us.txt` (R15) and Ghidra via `tools/ghidra_apply_symbols.sh`.
- If they decline attribution, the AP-sourced rows keep their facts (addresses are facts) but drop the citation text; the
  README thanks line stays unless they ask otherwise.
- Record the issue URL and the outcome in the phase log and in `docs/SETUP.md`'s P33 E2 section; if no reply within a month,
  note that and move on — the deliverable is the offer, not the answer (P9).

## 6. Related

`docs/memory-map.md` §3.4 (player state block), §4.2 (overlay-resident addresses, the patch sites), "Region deltas" and
"Address-base conversion" (their MAIN_RAM convention), open question #13 · `README.md` Special thanks · `PROJECT_CONTEXT.md`
parking lot ("Randomizer / Archipelago collaboration") · `docs/decompme-preset.md` (the other post-flip outreach, E1).
