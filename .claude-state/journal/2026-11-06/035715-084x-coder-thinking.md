---
ts: 2026-11-06T10:57:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qYrRFNgalrgUqF1vD3Er
---
With the barrier kept (no pins), the twin scores 10 with the same reg swap (t v1, a v0) — same as item 1's v_bar2. So the pin is what gives t v0.

Interesting: in this twin, v1 = 0x4000 gets the right register with the barrier. So the barrier fixes v1's allocation too.

So the twin's lever-free needs: barrier replacement (order) + pin replacement (t in v0) + v1's register.

Let me try the do-while variants and check whether v1's issue persists. Let me try w_dw with the v1 assignment moved into the do-while.

Variants:
1. do { v1 = 0x4000; t = unkC4; } while(0); then unk58, RMW.
2. do { t = unkC4; } while(0); and move `v1 = 0x4000;` to after the RMW? (source order changes)

Hmm. Actually, the target's li v1,16384 is at position 35, after the RMW. The source has `v1 = 0x4000;` before the load. sched1 moved it late (to just before its first use). In mine it went to a0 (register choice), not a scheduling issue.

The register: local-alloc picks a0 ($4) for v1's qty. In the target, v1 got $3. The target's orig has the barrier splitting the block before v1's birth; v1 is born in the block after the barrier. In that block, the qtys: v1, t(pinned $2), and the constant pseudo. local-alloc for v1: it needs a caller-saved reg. Why $3 not $4? find_free_reg scans... the MIPS register order in local-alloc is determined by `reg_alloc_order` in the machine description. For the MIPS, the alloc order might be $2,$3,$4,...? If $2 is taken (t pinned), the next free is $3 → v1 gets $3. In my lever-free base (no pin), $2 is free → v1 gets $2? But mine got a0 ($4), not v0. Hmm.

Wait, mine has `li a0,16384` — a0 is $4. Why not $2/$3? Because in the same block, other qtys (t's load, the address constant, the v0 result) took $2/$3.

OK. Let me try variants and score. Let me generate several:
- v1 in the do-while with the load
- v1 assigned later (after the RMW) in source
- v1 as a u16/s16 (HImode) — 0x4000 fits in u16? 0x4000 = 16384, yes. But the stores are `sh` (u16) and `sw`? The target stores `sh v1,24(v0)` (u16 fields) and `sh` for 0x1c. All three 0x4000 stores are u16 (`sh`). So v1 could be declared `u16`! HImode. That changes qty_size to 2 and could change allocation. But `li v1,16384` would still be the same. Let me check the target: `li v1,16384` then `sh v1,24(v0)`, `sh v1,26(v0)`, `sh v1,28(v0)`. All u16 stores. So declaring `u16 v1 = 0x4000;` is semantically fine.

Hmm, but would that change the code? `li v1,16384` (lui/ori? 16384 = 0x4000 → li = ori v1,zero,0x4000? The target shows `li v1,16384` which maspsx renders; the actual insn might be `addiu v1,zero,0x4000` or `ori`). With HImode, the constant might load differently. Risky.

Let me try the simple ones first.

Actually, let me reconsider: in w_dw the register pairs were a0->v1 x3 and v1->v0 x1. So v1 took a0 and the load took v1. The load's t got v1, the address v0 (the usual swap), and v1var got a0.

What if I make v1var's qty be born later (after the load) so it gets a different reg? The source has it before the load. Moving `v1 = 0x4000;` to after the RMW in source might make sched1 hoist it... or not.

Let me try moving `v1 = 0x4000;` to right before its first use (after the RMW), i.e., source order: t=load; unk58; unkC4=t|2; v1=0x4000; then the stores. The target's schedule has li v1,16384 after the RMW — so the source order might be exactly that in the target! Wait, the orig has `v1 = 0x4000;` BEFORE the load. But the emitted li is after the RMW. So sched1 moved it. If I move it in source to after the RMW, the schedule would be the same but the register allocation might differ (birth index later).

Let me test: w_v1late.c.

And w_v1dw.c: do { v1 = 0x4000; t = unkC4; } while(0).

Let me score both.
