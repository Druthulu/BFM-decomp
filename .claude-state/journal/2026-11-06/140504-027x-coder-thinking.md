---
ts: 2026-11-06T21:05:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y3bGxE1gRrv9x0JZ4lmm
---
Now I see. r74 (t) conflicts: 72 73 74 2 29 → conflicts with v0 ($2) and sp ($29). Why v0? Because t is live across... Let's see: the global allocno r74 has multiple live ranges (dies in 3 places). Its conflict with v0 arises because in some live range, v0 is live or set. Look at block 1: `lhu v0,88(s0)` sets v0 (a hard reg) and t (r74) is live at that point (t's live range starts at insn 29 and dies at 34-ish; but v0 is set at 27, before t is born). Hmm, in global.c, a hard register conflict for an allocno is recorded if the hard reg is live *within* the allocno's live range at any point. t is born at insn 29 (the plus), v0 dies at 29 (REG_DEAD at 29). Hmm, but v0's death at insn 29 is exactly at t's birth... In global.c's `find_reg`, a hard register conflicts if it's live at any insn in the allocno's live range (inclusive?), i.e., `regs_live_at` at birth includes v0 (still live at the start of insn 29, dying in it). That may count.

Similarly, in the *next* blocks, t is born in an insn where v0 is the source (load), so v0 conflicts at birth.

Wait, but the target had t in v0 with the pin — that's fine because the pin forced it; the pin's asm makes it a fixed hard reg.

So the fundamental issue: the pseudo `t` is a single global allocno spanning multiple blocks (because the C variable t is assigned in three places and the compiler created ONE pseudo for it? Hmm, normally each assignment creates a new pseudo. But here, apparently `t` is one pseudo reused across the blocks — no! Actually GCC's RTL: `t = a; ... t = b; ...` — each assignment creates a new pseudo (each SSA-ish). But here r74 is one pseudo with 9 refs and dies in 3 places, meaning one pseudo with disjoint live ranges. That's typical when the C variable is used as a "variable" across the function and the compiler doesn't create new pseudos for each assignment — GCC does create a new pseudo for each assignment, but for a simple variable, `t = X` and later `t = Y` in a different block: expand may reuse the same pseudo (reg) for the variable if... Actually expand_assign creates a new pseudo for each assignment when the variable is in a register? Hmm, it depends: with `-O2` and no SSA, GCC often reuses the same pseudo for a variable across assignments (it does "reg = reg" copies). Hmm.

Anyway, the observed fact: t is ONE pseudo r74 with disjoint live ranges in blocks 1,3,5 (dies in 3 places). Global-alloc must give it one hard reg across all live ranges. It conflicts with v0 because at each birth v0 is live (the load uses v0).

To make t go to v0, we could:
(a) Make t's live range not start at an insn where v0 is live — e.g., load into a separate variable first (u16 u = load; t = u - 0x100), so t is born at the addiu whose source is u (in another reg), and v0 dies at the load's use. But then t's birth insn is `addiu r74, u_reg, -256`, and v0 isn't live there. However, in the *next* blocks, same pattern. Hmm, but the conflict might come from elsewhere.

Wait, why does r74 conflict with v0 exactly? Let's find where v0 is live inside r74's live range. The .greg dump gives per-allocno conflicts but not the reason. Let me look at the .flow or .lreg to see the live ranges. r74: 9 refs, 10 insns, dies in 3 places. Live ranges: insn 29-34 (block 1), 44-49 (block 3), 63-... (block 5).

In block 1: insn 29 sets r74; insn 32 uses it (store); insn 34 uses it (sll). v0 is set at 27 and dies at 29. So at insn 29, v0 is live (dies at 29) — the allocno is born at 29. Does global.c consider a hard reg live at the birth insn as a conflict? In global.c `find_reg`, for each insn in the live range: `for (i = 0; i < HARD_REG_SET...; i++) if (TEST_HARD_REG_BIT (regs_live_at[...], i))` — it checks the live set at the birth insn and at each insn where the allocno is live. Since v0 is live at insn 29 (dying), conflict is recorded. Hmm, that's plausible: `regs_live_at` includes regs live at the *start* of the insn, and v0 dies in insn 29, so at the start of 29 v0 is live → conflict.

So: if t is born at an insn where v0 is NOT live at the start, no conflict. Options:
- Make the load go into a different pseudo, then t = load - 256. Then t is born at the addiu where v0 (the load's reg) is dying at that same insn... still live at start of the addiu. Damn, same.

Unless the load is assigned a register other than v0! Then v0 wouldn't be live at t's birth. The load pseudo (r78) is local-alloc'd to v0 because it's the highest priority in the block? Let's check block 1: r78 (load) used 2 times across 2 insns, r79 (sll) 2 times across 2 insns. Priorities: both refs 2, size... r78 is SImode 4, r79 SImode 4? live 2 both → equal priority 10000. Tie: lower allocno wins? The table said "TIE (lower allocno wins, global.c:607)". r78 < r79, so r78 gets v0.

Hmm, if we make the load's pseudo die into a different register... The load's reg is chosen by local-alloc: first free = v0.

Alternatively, make v0 NOT free at t's birth: i.e., have v0 occupied by another live value at that point, forcing the load into v1 and... no wait, then t still conflicts with whatever reg.

Hmm. The real goal: t gets v0. Global-alloc's order: the allocnos are sorted by priority; r74 (27000) is allocated first. The first free reg in GENERAL_REGS order for r74: it must avoid conflicts {v0, sp} and conflicts with r72,r73 (which are allocated later, so not yet assigned — global-alloc uses the conflict graph: r74 conflicts with r72, r73 too). Since r72/r73 get s0/s1 (callee-saved), r74 could get any of v0..t7/a0-a3. It got $3 (v1), meaning $2 (v0) was excluded by the conflict. So if we remove the v0 conflict, r74 would get $2.

So: we need t's live range to not include an insn where v0 is live.

Where does v0 stay live within r74's ranges? Each t range starts right after a `lhu v0`. If the load result were in v1 instead, t's birth insn wouldn't have v0 live. Can we make the load result go to v1? If v0 is occupied at that point (e.g., by a live value), local-alloc would put the load in v1. But then t's birth at the addiu would have v1 live → conflict with v1, and t would get v0! That's exactly what we want: t born while v0 is free.

How to occupy v0 at the load? Have some value live in v0 across the load. E.g., hoist the comparison result? Hmm.

Alternative approach: restructure so t is born in an insn that doesn't involve a v0-live value. E.g., use `t` computed as `(u16)load - 0x100` — no.

Wait, maybe simpler: the conflict is only at the birth insn. What if the load is directly into t? i.e., `t = load; t -= 0x100;`? Then the load insn sets r74 = mem, and the addiu is r74 = r74 - 256. t's birth is at the load insn (27), where v0 is NOT live (v0 dies at 21/branch). Then the live range covers insns 27..34; v0 is not live anywhere in that range (v0 not used). So no conflict → t gets v0!

But careful: `t = load; t = t - 0x100;` — with t s32 and load u16. That would be `lhu v0,88(s0); addiu v0,v0,-256` — exactly the target! And the store and sll follow. 

So the C fix: make the load result assigned to t directly, then subtract in place:
```c
t = CAST_WIDTH(u16, (u8 *)a0, 0x58);
t -= 0x100;
CAST_WIDTH(s16, (u8 *)a0, 0x58) = t;
```
This should produce `lhu t; addiu t,t,-256` with t one pseudo = v0. That's real C (statement split), no lever.

But wait: the third block's `if (*(s16*)(s1+0x1a) < 0)` reloads after the store — target has `lh v1,26(s1)` in v1 while t (v0) is stored. In target: `addiu v0; sh v0,26(s1); lh v1,26(s1); bgez v1; sh v0,24(s1)`. So the reload goes to v1 because t (v0) is live. Good, that falls out.

Let me try this variant. Also the last block: x pinned to v0, y to v1. Lever-free, x and y: target x=v0, y=v1. In my candidate x got... the assembly showed `lhu v1,16(s1)` hmm, that was from the earlier dt diff, but the .lreg for block 7 shows r88 in 3, r89 in 3, r90 in 3, r93 in 2, r94 in 3, r95 in 2. Hmm, r95 (v0) etc. Let me first fix t and see how the last block falls out.

Let me apply the change: split load and subtract for all three blocks.

Block 1: t = load; t -= 0x100; store; test.
Block 2: same with 0x5a.
Block 3: t = load 0x1a; t -= 0x100; store 0x1a; store 0x18; test reload.

But careful: t is one pseudo across blocks; making the first assignment `t = load` in each block means each block's load writes r74. Then r74's live range starts at the load insn where v0 is not live. 

Let's write variant w2.c and score.
