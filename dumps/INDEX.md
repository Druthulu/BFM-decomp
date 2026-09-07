# RAM-dump corpus — Phase 3 live PCSX-Redux captures (2026-06-14)

Full 2 MB PS1 RAM images pulled from the Windows-native PCSX-Redux web API
(`GET http://172.17.208.1:8081/api/v1/cpu/ram/raw`) while Drew played a fresh SLUS-00726 run.
Each is a labeled game-state snapshot — a reusable corpus for offline RE in later phases
(overlay map, player-state, save-format) **without re-playing the game**.

- **Status (P33 B6, 2026-09-06): LOCAL-ONLY.** The 28 `.bin` images are ROM-derived game memory (2 MB each, 57 MB;
  the retail EXE's code sits in every one) and leave git at the public flip; `dumps/INDEX.md` + `dumps/CHECKSUMS.sha1`
  (one SHA1 per image, `cd dumps && sha1sum --check CHECKSUMS.sha1` → 28/28) stay tracked and describe them. The
  private archive repo (`Druthulu/BFM-decomp-archive`, the pre-rewrite history) holds the one committed copy.
- **Not regenerable byte-for-byte.** Each image is one moment of one play-through; a re-capture with
  `tools/ram_probe.py snapshot <name>` (PCSX-Redux web API → `.run/ram/<name>.bin`) is a NEW state snapshot of a
  different run — the same addresses hold the same kinds of facts, the bytes differ. Treat the SHA1s as the identity of
  THIS corpus, not as a target to reproduce. Back `dumps/` up off-machine like `disks/`.
- Resident blob always @0x800CEDF8 (`MAIN.CD/FILE_010/1.1`); location overlay slot @0x80128158.
- Verified addresses derived from these live in `docs/memory-map.md` (§3.4, §4.3, Q#1/#3-#6/#9/#12).

| File | State / location | Overlay @0x80128158 | Key facts | Used for |
|---|---|---|---|---|
| `ram_t6b.bin` | **tut_forest** (tutorial forest, game start, daytime) | `SC01/077` | the MILESTONE dump | T6b/T7 milestone byte-proof |
| `ram_spiral.bin` | Spiral Tower exterior, pre-erection | `SC01/080` | gold 1450, HP 146/150, BP 137/150, +Gunshot | overlay map; HP/BP/gold |
| `ram_spiral2.bin` | Spiral Tower exterior, tower erected | `SC01/080` | gold 1450, HP 136/150, BP 91/150, Day1 Mon | HP/BP change-detect (Q#12) |
| `ram_inside.bin` | Spiral Tower interior | `SC01/084` | gold 1550 | gold triangulation |
| `ram_inside2.bin` | Spiral Tower interior | `SC01/084` | gold 1650 | gold pin (0x80078E8C ÷10) |
| `ram_event.bin` | Spiral Tower interior, bell→fire→teleporter event | `SC01/084` | event-flag cluster lead | event flags (unisolated) |
| `ram_toptower.bin` | Spiral Tower top | `SC02/000≡003` | gold 1760 (dup overlay) | overlay map (SC02; dup pair) |
| `ram_lumina.bin` | Spiral Tower upper, head-chase (got Lumina) | `SC02/000≡003` | — | overlay map |
| `ram_castle.bin` | Allucaneet Castle Ch1 interior (Rootrick/princess) | `SC02/005` | — | overlay map |
| `ram_steamknight.bin` | Steam Knight fight, stage 1 (castle) | `SC02/005` | bossHP 27 | bossHp_SteamKnight 0x801E4398 |
| `ram_courtyard.bin` | Steam Knight stage 2 (courtyard) | `SC02/005` | bossHP 0 (defeated) | bossHP verify (27→0) |
| `ram_dummytown.bin` | Steam Knight stage 3 (dummy town) | `SC02/005` | bossHP 144 (refilled) | bossHP verify (per-stage) |
| `ram_savescreen.bin` | Save screen (location overlay FLUSHED) | (none — menu) | saveHeaderTemplate visible | Q#5 save-format header |
| `ram_ch2castle.bin` | Ch2 Allucaneet Castle bedroom (king/butler) | `SC01/005≡006` | — | overlay map (location×chapter) |
| `ram_library.bin` | Library (read-books menu, frozen/blue) | `SC01/008` | menu sub-state | overlay map |
| `ram_library2.bin` | Library (post-quit, speech menu, animated) | `SC01/008` | same overlay | overlay-model correction |
| `ram_castlehub.bin` | Allucaneet Castle hub (nav menu) | `SC01/004` | Visit/Library/Room/SubMenu/Village | overlay map |
| `ram_room.bin` | Room (Sleep/Toys/Leave) | `SC01/005≡006` | re-entry determinism | overlay map |
| `ram_visit.bin` | Visit / main hall (Geezer) | `SC01/009` | — | overlay map |
| `ram_submenu.bin` | SubMenu (main game menu) | `SC01/004` | gold 1650, HP 150/150, BP 100/150 | player-state cross-check |
| `ram_itemmenu.bin` | Item/inventory menu (empty) | `SC01/004` | — | menu-overlay model |
| `ram_gondola.bin` | Gondola / outside village | `SC03/002` | — | overlay map (SC03) |
| `ram_village1.bin` | Village (central hub) entry | `SC03/001` | hour 15 | overlay map; clock |
| `ram_village2.bin` | Village far corner | `SC03/001` | 18:15 | one-overlay proof; clock |
| `ram_inn.bin` | Inn (before pay-to-sleep) | `SC03/001` | pre-sleep state | tiredness "before" |
| `ram_time1.bin` | Village, clock snapshot 1 (paused) | `SC03/001` | Day1 Mon 13:30, tired 11% | clock/tiredness triangulation |
| `ram_time2.bin` | Village, clock snapshot 2 (paused) | `SC03/001` | 14:30, tired 14% | clock/tiredness triangulation |
| `ram_sleep.bin` | After Inn pay-to-sleep (paid 390) | `SC03/001` | HP/BP max, tired 0, Day2 Tue 3:00, gold 1260 | day/hour/tiredness/gold confirms |
