# Actor / Player struct — recovered layout + the byte-neutral finding (Phase 17 / T4-T5)

> **Base: `0x80078E00`** (the player instance). ~154 fields over **0x24C bytes**. This is the engine's
> central entity record — `arg0` to 550/941 of the struct-heavy residual functions. Recovered by (a) static
> inference from the union of m2c `M2C_FIELD(arg0, T, off)` accesses across all drafts, (b) a live PCSX-Redux
> RAM pass (R10/R11), anchored to the Phase-3 player-state fields.

## ⚠ Key finding (the matching verdict)
**Feeding this struct to m2c as `--context` is BYTE-NEUTRAL for the structural-miss bucket.** Measured: on a
12-function structural-miss sample, m2c-with-struct vs m2c-alone → **0 better / 10 same / 2 worse** (even with
the full code-inferred + RAM pointer set, 32 pointers). `arg0->f_X` and `M2C_FIELD(arg0, T*, X)` emit identical
bytes; the structural misses (50–98% instruction mismatch) are m2c *decompiler* limits, not missing types — so
the struct does not crack them, and neither will the permuter at that mismatch magnitude. This confirms the
Phase-17 deep-research caveat: type recovery is **comprehension**, not a blanket match-% lever. The struct is
kept as a Gen2 quality artifact + decomp.me enabler, **not** a build input.

## Confirmed fields (live-verified, R10)
| offset | type | meaning | evidence |
|---|---|---|---|
| +0x08C | s32 | gold | =126 (Phase-3 anchor) |
| +0x0AC | u8  | day | =2 |
| +0x0B1 | u8  | hour | =22 |
| +0x0B2 | u16 | hp_max | =150 |
| +0x0B4 | u16 | **hp_cur** | =150 (the plan's "+0xB4"; Phase-3 0x80078EB4) |
| +0x0B6 | u16 | bp_max | =150 |
| +0x0B8 | u16 | bp_cur (stamina) | 74→50 as the player walked (BP-drain) |
| +0x108 | s16 | position X | +6 on a walk north |
| +0x10C | s16 | position Z | +10 on a walk north |
| +0xF0  | s16 | step/heading counter | +1 per walk tick |

## Pointer fields (the m2c-can't-infer set; idle RAM scan + code-inferred)
RAM-observed: `+0x54 → 0x8017E75C`, `+0x58 → 0x8017E720`, `+0x68 → 0x8017E91C` (overlay code — likely
behavior/handler function pointers), `+0x6C/+0x70 → 0x800D1E20` (resident), `+0x5C → 0x8010F5C8`. Plus ~26 more
offsets m2c dereferences as pointers in code (e.g. `+0x08`, `+0x4C`, `+0x50`). Full set in `.run/actor_fields.json`.

## Reproduce
- Static layout: aggregate `M2C_FIELD(arg0, T*, off)` over `.run/wt_drafts/*.c` (regen via the harvest).
- Live typing: `tools/ram_probe.py` against PCSX-Redux (host in `.run/ram/HOST.txt`); snapshot/diff across
  controlled actions (walk/jump/swing/charge/damage) to type + name fields (R10 multi-datapoint).
- The validation (struct byte-neutral): m2c-with-`.run/actor_ctx2.c` → `match_one` vs m2c-alone.

## Deferred (comprehension, not the matching critical path)
Full field-naming via the emulator scenario list (jump=air-state/y-vel; swing=action-state+weapon-id;
charge=charge-level; damage=hp/hurt-state; the +0x14/+0x15 dispatch-state per memory-map; the flashing-HUD
"interactable nearby" Bincho flag). Resume when comprehension/decomp.me work is prioritized — it does **not**
move the byte-match needle (proven above).
