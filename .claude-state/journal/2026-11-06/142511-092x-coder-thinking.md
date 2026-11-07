---
ts: 2026-11-06T21:25:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qKLvvBfoAtqxwPHwClhR
---
Target:
- s1 = a0 (arg)
- s0 = tp (D_801274F0), set at 4838: lui s0; addiu s0
- s2 = base (D_80185FF0)
- s3 = base + 0x10/0x20/... (computed)
- frame -48 (not -40; mine earlier said target 40? Let me recheck: target addiu sp,sp,-48. Hmm the diff said target `sw ra,40(sp)`, frame 48. Earlier I misread. mine had frame 44.)

So target frame is 48. Mine f1 has frame 44? Let me check. The extra 4 bytes and extra callee-saved s4 in mine.

So target uses s0,s1,s2,s3 (4 callee-saved) + ra. Mine uses s0,s1,s2,s3,s4 (5) → frame 44 (5 regs * 4 + ra... actually 48 vs 44).

The tp is in s0. The launder forces tp to be materialized and kept.

So the crack must:
1. base → s2 (pin)
2. tp → s0 (launder)
3. buf address rematerialized (ap launder)
4. s3 = base+offset computed
5. frame 48

Without levers, mine uses an extra s4. So one more callee-saved reg is used.

This is a hard 2-lever wall. Given the time (started 14:42, now ~15:00 = 18 min), let me put in a few more tries to reach 30, then record WALL.

Actually, let me reconsider: maybe there's a much simpler rewrite. The target's s2=base suggests base is live across all calls. The pin forced it. Without the pin, base goes to s0. If I could make base's allocation prefer s2 by declaration order or by adding a fake use...

Actually, the callee-saved order in global-alloc: allocnos get callee-saved regs in priority order. base has high priority (many refs, live across calls). The pin forced $18. Without, it gets $16 (s0). To get $18 (s2), another allocno must take $16 and $17 first. That's what the pin does indirectly.

Real C: add more high-priority callee-saved allocnos so base lands on s2. E.g., if tp also needs a callee-saved reg with higher priority than base, it takes s0, then base takes s1? No, s1 is a0.

This is exactly the "global-pri-bank-order" wall (line 274).

OK. Let me do ~15 more quick scored tries to meet the 30-try threshold, trying plausible real-C moves, then WALL.

Quick variants (batch):
- g1: ap as s16* (type change)
- g2: declare locals in different order (base first, tp last)
- g3: tp as u8* pointer, ap removed, base plain
- g4: use buf[0] instead of *(Blk8*)buf for the initial copy? changes code
- g5: tp = (s32)D_801274F0... then store, and use `tp` via a pointer `Blk8 *q = (Blk8*)tp;` no
- g6: base as `u8 *base` instead of s32, with base+0x10 etc.

Actually, g6 is interesting: the source uses `base + 0x10` as an integer. If base were a pointer `u8 *base = (u8*)&D_80185FF0;` then `base+0x10` is pointer arithmetic. The target uses `addiu s3,s2,16` etc. Same. But the type might affect allocation.

Let me test a few. Also g7: move `tp = (s32)D_801274F0` assignment earlier (right after LEND) — already there.

Let me also try: `tp` used as the destination of the initial Blk8 copy — what if we write `*(Blk8_8017CF48 *)(tp) = *(Blk8_8017CF48 *)(buf);` (explicit) — same.

Honestly, I think this is a WALL. Let me run ~12 more scored candidates quickly to meet the threshold, then record.

Let me generate a batch of variants programmatically.

Variants:
1. g1: base as u8*
2. g2: tp as u8*, use *(u32*)? no
3. g3: reorder decls: base first
4. g4: reorder decls: tp, ap, base, buf
5. g5: remove `u1`/`u2` temps? they're used
6. g6: `tp = (s32)D_801274F0_8017CF48;` moved before the L174 branch
7. g7: keep ap but assign `ap = &buf[0];`
8. g8: `buf` as `s16 buf[4]` → `s16 buf[4];` same

Let me just generate and score a batch. Actually, scoring many candidates via sc.sh is fine (one line each).

Let me create ~10 variants.
