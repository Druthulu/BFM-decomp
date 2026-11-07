---
ts: 2026-11-06T15:56:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KjysrHELidEzSG8Y8iRq
---
Score 40 (344 ins) — the do-while didn't prevent the merge; it just added 1 diff. Hmm.

Wait, 344 ins still. The do-while didn't split.

Let me try a different approach for the 2-output: the launders re-tie n and otz in place (same registers). What if we use a *different variable* in one tail? E.g. in the LINE tail, copy n to a new variable `n2 = n;` and test `n2 < 4` — but the target's code uses the same register s0. Hmm.

Actually, let's re-examine what the launders do to the register allocation: they force n and otz to be *re-set* (unknown) so their live ranges are split, and the two tails' tests can't share.

What if we use the `do{}while(0)` around the *OT store + tail* differently... 

Let me look at the actual target vs c3 in the tail region more carefully. Target insns around 280-302:
```
slti v0,s0,4
beqz v0,182c
...
[tail code]
...
slti v0,s0,4     <- second test
beqz v0,18c0
nop
```
Mine (c3):
```
slti a2,s4,4
beqz a2,182c
...
[tail code]
...
beqz a2,18b8     <- jumps to the SAME tail (shared)
```
So mine shares the tail. Target duplicates.

For jump.c cross-jump to merge, the two blocks must be identical. In the target they're not merged. Why? Because the asm insns (before each tail) have outputs n/otz tied to different registers? Hmm, in the target, n is s0 and otz is s3? The diff showed target uses s0 for n and s3 for mlo... 

I think this is the `jump2-crossjump-arms` wall: "cross-jump merges byte-identical switch/if arms; renaming the regs gives no plain-C split". That's exactly our situation (renaming gives no split; the asm was the split).

So item 4 is a WALL: two load-bearing launders, no plain-C crack found; best lever-free 43 (c1). Actually wait, c1 (all 3 removed) = 43; c2 (arg removed) = 4 — that's the LOWEST score of a lever-free body! c2 is lever-free? c2 has the 2-output launders still (kinds: launder). So c2 is NOT lever-free. The best *lever-free* body is c1 (all launders gone) = 43.

Hmm, "WALL (best = lowest score of a lever-free body)". So best = 43.

But hold on — PARTIAL:launder is allowed if win.c scores 0 keeping only that lever. Neither c2 (4) nor c3 (39) scores 0. So WALL with best 43.

Wait, maybe I can combine: c2 (arg launder removed, score 4) + a do-while or something for the la position. The score 4 is just the la position. Could a plain-C trick fix that? If yes, then c2 would score 0 with the 2-output launders kept → PARTIAL:launder. Let me think again about the la position.

The la position: target first, mine 15-16. What if we add a second use of arg that's *real*: the function calls func_80052E38(arg) once. What if the original called it with `&D_800AF648` and also had `arg` used in the loop? No.

Hmm, what if we move the `arg = &D_800AF648;` statement to AFTER the pointer setup but before ot, and see if the la lands in the same relative position? The target's la is first; we need it first.

What if the call's argument copy is given a lower LUID by writing the call as the first statement and moving the pointer setup after? The target's call is after the setups, but sched2 might move the setups before the call if independent! Let me test: reorder the C so the call is early:
```
arg = &D_800AF648;
ot = ...;          /* needed before call? no */
func_80052E38(arg);
r = ...; mlo...; ...
```
But the target has ot computed before the call (`sll v0,v0,0xe` before jal). If ot is computed after the call in C, the target wouldn't match. Unless sched2 moves the ot computation before the call (it's independent of the call except memory). sched2 can move insns across calls? Calls are barriers for sched2? Actually sched2 can schedule across calls if there are no dependencies, but the call clobbers memory; the ot computation loads D_800B9A02 and D_800A6610 (memory) — the call has a memory clobber, so the loads can't move across it. So ot would stay after the call. Wrong.

What if we keep ot before the call but move the *pointer setups* (r, mlo, mhi, c, va, vb) after the call? The target has them before the call (lui s4, etc. before jal). If moved after, the call would be earlier — but sched2 could move them before the call if independent (they don't touch memory except... r = &D_8019B7B8 is a constant; mlo/mhi constants; c/va/vb adds). These could be scheduled before the call by sched2! The target has them before the call. So moving them after in C might still produce the same code IF sched2 reorders them before the call. Risky but worth a test.

Actually, the la position: if the call (and its arg copy) is the first statement, the la's LUID is low → sched2 puts it first. Then the pointer setups (independent) can be scheduled after the la but before the call. The ot loads (memory) must stay before the call if they're before it in C. Hmm.

Let me test: reorder to:
```
arg = &D_800AF648;
ot = (u32)&D_800A6610[...];
func_80052E38(arg);
r = ...; mlo; mhi; c; va; vb;
for ...
```
Wait, but `ot` needs `*(u16*)&D_800B9A02` — fine.

But `r` etc. are used in the loop after the call; moving their setup after the call is semantically fine.

The target order: la a0; spills; lui s4 (r); lui s3 (mlo); lui s7 (mhi); addiu s2/s5/s6 (c/va/vb); lhu D_800B9A02; lui/addiu D_800A6610; sw ra...; sll v0,0xe; jal. So the pointer setups ARE before the ot computation and the call. If I move them after the call in C, sched2 would need to move them before the call. They're independent of the call (no memory), so sched2 could. But the call is a barrier for sched2? Let me just test.

Let me construct variant h1: reorder the prologue so the call is right after ot, and the pointer setup statements move after the call.

Actually, simpler: move just the `arg` assignment and the call to the front (after ot). Hmm, the arg assignment is already first.

Let me write h1: 
```
arg = &D_800AF648;
ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
func_80052E38(arg);
r  = (u8 *)&D_8019B7B8;
mlo = 0xFFFFFF;
mhi = 0xFF000000;
c  = r + 0x29;
va = r + 0x14;
vb = r + 4;
for (...)
```
Test on c2 (arg launder removed, score 4).
