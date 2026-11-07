---
ts: 2026-11-06T09:35:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FYylB08JGDvBMFvUK4DW
---
Item 3: 36 tries, best 56 → WALL.

Now item 4: generate 30+ variants. Real-C moves: loop shape, e pointer forms, i width, decl order, e reuse, base type.

The lever-free best is 8 (56 vs 58). Variants:
- decl orders (6)
- loop forms: e inside loop (orig), e before loop (b2), e as primary (e += 0x18), i as s32/u16
Let me build 6*5 = 30.

Item 5: generate 30+ variants: decl order, t width, sp10 array vs pointer, p/q reuse, rv type/order.

Let me write both generators.

Item 4 loop forms:
L0: original (e = base+4 inside loop)
L1: e before loop, reassigned at loop end (b2)
L2: e as primary: e = base+4; loop: ...; e = (Sub*)((u8*)e+0x18); and base = (u8*)e - 4 used in the call? That changes the call. Hmm, keep base as a variable updated too.
L3: pointer arithmetic with base as u8* and e = (Sub*)(base+4) each iteration but i as u8.
L4: for-loop with i and base increment in the for clause.

Let me write:
L0: for (i=0;i<0x40;i++) { e=(Sub*)(base+4); ...; base += 0x18; }
L1: e before loop; for { ...; base+=0x18; e=(Sub*)(base+4); }
L2: for (i=0;i<0x40;i++) { e=(Sub*)(base+4); ...; e=(Sub*)((u8*)e+0x18); base=(u8*)e-4; } — hmm, base = e-4 then the call uses base; and e-> accesses. This changes base's meaning. Let me instead:
L2: for (i=0;i<0x40;i++) { ...; base += 0x18; } with e computed via `e = (Sub_80180A54 *)(base + 4);` at top — same as L0.

Simpler: vary the `e` declaration type and the access spelling:
L3: `u8 *e;` and access `((Sub_80180A54 *)(e))->flag`? no.

Let me do: L0, L1 (b2), L2 (e = (Sub*)(base + 1) with u32* arithmetic? no).

Alternative real-C moves: i as u8/s16; `base` as s32 and `(u8*)base`; the outer `for` vs `while`.

L2: while loop: `i = 0; while (i < 0x40) { e = ...; ...; base += 0x18; i++; }`
L3: `for (i = 0; i < 64; i++)` (decimal)
L4: e computed from base each use: `if (((Sub_80180A54 *)(base + 4))->flag == 0)` and `e = (Sub*)(base+4)` before the stores (b4 tested = 10).
L5: `base` declared `u8 *base = D_801DA130;` init at decl.

Let me build 6 decl orders × 5 loop forms = 30.

Item 5 forms:
L0: original
L1: t declared before p/q
L2: sp10 as s16[4] used via sp10[1], sp10[3], sp10[5]? Hmm, the source uses `*(s16*)((s32)sp10 + 0x2)` etc. A real-C move: `sp10[1]`, `sp10[3]`, `sp10[5]`? sp10 is s32[4] = 16 bytes; offsets 2,6,10 are halfwords. Rewriting as s16 array would change the call address (&sp10). Risky.
L3: rv declared s32 before/after; rv assigned from sp20 via a temp.
L4: `p`/`q` reuse: `p = (u16*)(q-3)` vs `p = (u16*)&D_80126CBA - 3`.
L5: if/else inverted.

Let me build 6 decl orders × 5 loop/body forms = 30.

Let me write both generators now.
