# md_MAIN_007:func_800CF408 (178 ins) — T4b HAND PASS, S84 (2026-09-06) — **BANKED byte-identical** (`8fa12bc22`)

## What closed it (one probe of the right kind after 135 of the wrong kind)
The residual (3 rows, idx 10–12: `ori $s5,0x96` two slots below its `lui`) was correctly attributed by the T4b Fable agent to
sched1's T-139 memory-unit bubble (the unboosted tag load lingering behind the store stream, its blocked cycle handed to the
highest-LUID floater) coupled to the `$t2/$t3` `qty_compare` contest (§501-L). Every cure inside the draft's own spelling
oscillated between 3 / 13 / 18 — the draft was the wrong SHAPE, not the wrong dial.

**The banked sibling `md_MAIN_009:func_800CD92C` (same four-prim SPRT+tpage family, §501-H) matched with a simpler shape:**
`v = (OT[idx * 0x1000] & m24) & m24; t = *(u32 *)p; t &= 0xFF000000; t |= v; *(u32 *)p = t;` and
`OT[oi] = (OT[oi] & 0xFF000000) | ((u32)p & m24);` on a TRUE `u32` ARRAY_REF of the OT symbol — no `ob` pointer variable, no
named `mhi`, no `arg1 = 0` kill, no `y1/y2` temps, the colour stores chained. Porting that spelling to this function's constants
(`0xE1000086/87/96/97`, `0x7980`, `0x80`, u=`0x20/0x40`, w/h `0xA0/0x100`, `x`/`x + 0xA0`, `y`/`y + 0x100`) = **MATCH 178/178 in the
real TU (`rtu_match --split md_MAIN_007 --source md_MAIN_007`)**, first try (`b0d_sibport_alias.c`).

**The one obstacle was the TU's declaration:** `src/md_MAIN_007/md_MAIN_007.c:317` declares `extern u8 D_800AA60C[];`, so the
sibling's `u32` array form CC1-FAILs (`b0_sibport.c`: conflicting types) and every `u8`-based respelling (`*(u32 *)&D_800AA60C[oi]`,
a one-member struct view, the P_TAG bitfield on `&D_800AA60C[oi]` — `b0b`/`b0c`) keeps ALL eight OT accesses in the raw
`lui $at/addu $at/lw %lo()($at)` macro form: cse binds the base into `$t2` only for the `u32` ARRAY_REF (element size 4, the
`(plus (mult idx 4) sym)` address goes through `memory_address → force_reg (sym)`; the `u8` form's `(plus sym idx)` never does).
The fleet's standard spelling for a second typed view of one symbol is the asm-label alias (1,438 banked files:
`extern u16 hD_80076240 __asm__("D_80076240"); extern s16 sD_80076240 __asm__("D_80076240");`):
`extern u32 wD_800AA60C[] __asm__("D_800AA60C");` — a declaration, not an asm body (R62 untouched).

## Measured this session (all in `.run/P32/t4c/func_800CF408/`)
| variant | change | result |
|---|---|---|
| b0_sibport | sibling port, `extern u32 D_800AA60C[]` | CC1 FAIL (TU declares `u8 D_800AA60C[]`) |
| b0b_sibport_otw | port on the `u8` array, one-member struct view for the OT word | far (raw `$at` form ×8) |
| b0c_sibport_ptag | port on the `u8` array, P_TAG bitfield write | far (same) |
| b1_pm1asm | draft + named prim-1 masked temp, 2-set via trailing `__asm__ volatile("" : "=r"(pm1))` (func_800CD674's lever 7) | worse: the volatile asm makes hard regs live → m24/colour swap `$t1↔$t0` |
| b2 | b1 + cure A + ob-after-index | same swap |
| b3_draft_alias | the Fable draft with only the OT accesses respelled to the alias array | 16 (frame 0x28: an extra slot — the named temps) |
| **b0d_sibport_alias** | **the sibling port with `wD_800AA60C[]` alias** | **MATCH 178/178** |

## Two facts worth keeping
* The draft's `vars= 8` frame (the target's too) is a combine-minted GHOST (`tools/ghost_census.py`: pseudo 92, refs 2,
  `ST_REGS or none; pointer` → SLOT) — the same producer proved for row (a); the sibling port reproduces it for free.
* The prologue-weave residual class (§501-H/L) is a SHAPE symptom: when a same-family sibling is banked, port its spelling
  before dialing the draft (135-variant sweep + 3 agents + a hand pass measured nothing the port did not give at once).
