---
ts: 2026-11-06T12:51:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uKeDuNJR2KerqQEDnek1
---
v1 and v2 stay at 2 — same residual. So do-while doesn't split sched regions here (or it does but sched still reorders).

Let me check v1's diff — maybe the do-while changed nothing at all (identical to w0). Let me think about the actual scheduler reason.

The instruction in question: `sh v0,-8(a1)` (y store) vs `lui v1,0x6480; ori v1,v1,0x8080` (constant build for the 0x4 store).

Backward scheduling: sched processes insns from last to first, choosing the highest-priority ready insn. Priority is computed as the max over successors' priorities + 1 (i.e., critical path length to the end). The lui/ori feed the sw at -14(a1) which is fairly late, so they have a long path? Hmm, they'd have a certain priority. The sh's priority: it's a store, no successors, priority 1.

In target, the sh is placed BEFORE the lui/ori. In mine, after. Since sched is backward and picks highest priority first, the lui/ori (priority higher because they feed the sw which is scheduled later... hmm.

Let me look at sched.c's priority computation: insn priority = 1 + max over dependent insns of their priority, with a bias for REG_DEP_ANTI etc. Also "birth" priority boost for insns that set registers.

Honestly, an empirical approach with real-C moves is better. Options to change the priority/scheduling of the sh:

1. Make y's computation later: y = D_801C11CE + 1 — the lhu. If the lhu were born later, the sh would be later. But target has the lhu at 138, nop 139, addiu 140, sh 141.

2. Give the sh more priority: e.g. make the store feed something. Not possible (store has no value).

3. Make the lui/ori later in source? They're already after.

4. Change the *order* of the two constant builds: the 0x400 and 0x64808080. Target order at 142-146: lui v1,0x6480; ori; lui v0,0x400; sw v0,0(s0). Hmm, that's the 0x64808080 pair BEFORE the 0x400 build, even though the 0x400 store (0(s0)) is earlier in the program than the 0x4 store.

Mine: lui v1,0x6480; ori; sh; lui v0,0x400; sw. So both have the same relative order of the constants; only the sh moves.

So the question is purely: can the sh be kept above the lui/ori pair?

Idea: make the 0x64808080 store's *address* depend on y? No.

Idea: use a single statement that stores both: no.

Idea: change the type of the store so it's a block move: `*(u32*)((u8*)out+0x4) = 0x64808080` → a 4-byte struct copy from a static? That would be lw from memory — different target.

Idea: put the sh INSIDE the if/else arms (i.e., merge the y assignment and store into the arms)? That changes the CFG (two stores, one per arm) — jump2 might merge them back... Actually that's a known move: "barrier -> store per if-arm" (moves.md has several: "barrier: y store per if-arm"). For func_80189214, func_8017E804 etc., the barrier was cracked by writing the y store in each if-arm. But here the y store is AFTER the if/else (common to both arms). If I move the store into each arm, the CFG changes: two stores. That might give the target schedule because the store is then in a different basic block (the if-arm ends with a branch to the join).

But the target has ONE sh at 141 (after the join). If I put a store in each arm, jump2 might cross-jump them (merge). Risky but let me check the moves: "barrier,keepalive | func_8017E804 | PARTIAL:keepalive greg-pri-refs — barrier: y store per branch" — that's a crack for a barrier. And "func_8017E7DC", "func_8017E93C" — "barrier: y store written per if-arm (no y temp)".

In our function, the y value differs per arm: arm0 y = D_801C11BA - 2; arm1 y = D_801C11CE + 1. So writing the store per arm means:
arm0: { out[0xD]=0x30; y = D_801C11BA-2; store sh y; }
arm1: { ...; y = D_801C11CE+1; store sh y; }
Then the join has the rest.

But the target has the sh AFTER the branch join? Let me check: the branch at 133 `bnez v0,6e4` (jump to the else arm), and 610 addiu v0,t0,1 is the delay slot. Then 614-... is the arm0 path. Where does arm0 jump to the join? Let me dump more of the target to see the structure.

Actually, the code is a loop with `continue` statements. The two arms both `continue` if the condition fails. The structure:

```
for (j=0;j<2;j++) {
  if (j==0) { if (cond) continue; out[0xD]=0x30; y = A-2; }
  else { if (cond) continue; out[0xD]=0x38; y = B+1; }
  sh 0xA = y;
  ...
}
```

So there's a join point after the if/else where the sh is. With a per-arm store, we'd have two sh's, each in its own BB. The target has one sh at 141 in the join block. Hmm, but wait — jump2's cross-jump could merge the two arms' tails... but the rest of the block is common anyway.

Actually, if I put the store in each arm, the compiler would emit sh in each arm and the join block would start after. The target's sh at 141: which block is it in? Let me check the target's control flow around 600-6e4.

Let me dump the target region 100-175 to see branches.

Alternatively, think about a completely different real-C lever: make the sh store *volatile*? No.

What about making the lui/ori pair be shared/hoisted differently? The constant 0x64808080 is a literal. What if I write it as a variable `u32 c = 0x64808080;`? Then it becomes a pseudo with a copy — local-alloc might assign it a register and sched might treat it differently. The target builds it into v1 with lui/ori (immediate build). A variable initialized to the constant would still be built with lui/ori (or li). Let me try: `u32 k64 = 0x64808080;` declared in the block, then `*(u32*)((u8*)out+0x4) = k64;`. If k64 gets a register whose live range starts at its birth (after the sh), then sched can't move the build above the sh? No — sched can move the build up freely as long as no dependence; birth position in source doesn't constrain sched (sched may move insns anywhere in the block as long as deps allow).

Hmm, but wait: in target, why is the lui/ori below the sh? Because the barrier forces it. In mine, sched chose to place the lui/ori above the sh. That's a *scheduling priority* decision. To flip it, change the priorities.

What determines priority in sched.c (2.7.2)? Let me read the priority function.
