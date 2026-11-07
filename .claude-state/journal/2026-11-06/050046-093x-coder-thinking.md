---
ts: 2026-11-06T12:00:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RB1WCEdrlDW8dV9CSLng
---
v2 = 61, 97 insns. Better than 75 but not great. The struct copy is closer (97 vs 94). Interesting: the second copy uses the pinned $7 register s5 (mine) vs s3 (target).

Hmm, mine has s5 for the second block's pointer (the $7 pin). Wait, v2 removed the pin declarations! I removed `register Blk20 *s __asm__("$7")` etc. So where does s5 come from? Mine allocated blk's address to s5 — the stack address of blk. Target uses s3 (arg0) for the stores... no, target stores to sp.

Let me look at the target second block: `lui a3; addiu a3` (D_800AE620), loads, stores to sp+44.. So the target's second copy also reads D_800AE620 into a3.

In mine, the second copy reads from s3? `lw v0,0(s3)` — that's arg0, not D_800AE620! Wait: mine[58] `lw v0,0(s3)` — hmm, s3 might be the D_800AE620 pointer in mine.

OK this is getting long. v2 (61) is better than v0 (75) but worse than p2 (8).

Time check: item 3 ~30 min. Let me decide: this is a WALL. Best lever-free = 61 (v2). But I need ≥30 tries.

Let me do a final batch on v2 (struct copy) with variations to push the lever-free score down, and count tries. v2-based variants:
- struct copy + pins kept on the copies? (pins not needed)
- blk = D_800AE620 with s32/u16 vec
- copy order (second copy before ang2, etc.)
- `Blk20 blk = D_800AE620;` init at decl (first copy at decl time — changes birth order!)

Init at decl is a listed real-C move. `Blk20 blk = D_800AE620;` at the top would move the first copy earlier (before obj/ent).

Let me generate ~16 v2 variants and score; then record WALL (best 61 or lower).

Also, let me reconsider PARTIAL:launder with p2=8 — maybe worth 3-4 more attempts. But a PARTIAL requires 0; unlikely.

Actually, wait. Let me reconsider the whole thing: maybe there's a real C move that keeps s in a register without an asm: use `s` in a pointer-arithmetic way that prevents folding, e.g.:

```
Blk20 *s = &D_800AE620;
Blk20 *e = s + 1;   /* end */
```
Then a loop? No.

Or: pass s to something opaque? No.

What about making the struct copy explicit via a temp struct: `Blk20 tmp; tmp = D_800AE620; blk = tmp;` — extra copy.

OK let me just run the v2 sweep and finalize as WALL.

Actually — hmm, one more important idea: the target's copy is exactly `blk = D_800AE620;` with 3 registers. v2 got 97 vs 94 and score 61. The differences are register assignments (s5/s3) and copy order. Let me try:
- `Blk20 blk = D_800AE620;` init at decl.
- with `s32 t0,t1,t2` temps? no.

Let me generate variants.
