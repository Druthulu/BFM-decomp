---
ts: 2026-11-06T16:29:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6rYxR6qWCKPQQaQja2xB
---
Interesting:
- Removing keepalive alone: score 1 (missing li v0,1). So keepalive only adds that one insn.
- Removing barrier alone: score 19! So the barrier is load-bearing for much more (block layout). Wait, removing barrier causes 19 score and 10 fewer insns. Hmm, the barrier is `__asm__ __volatile__("")` which is a scheduling/flow barrier. Removing it changes control flow? An empty asm shouldn't change basic blocks... but it can prevent cross-jumping/merge (jump2). Wait, 10 fewer instructions means jump2 merged two identical blocks! The 4-call block appears twice: in the `func_800D2454 != 0` branch and in `func_800D2704 != 0` branch. Both are identical: func_800D2D44(0); func_800468FC(); func_8002D8D4(); func_800D2AA0(0); goto ret. The barrier in the first arm prevented jump2 from merging them. In target both are duplicated (not merged). Hmm, actually target has both copies at 0x158-0x178 and 0x198-0x1b8. So target doesn't merge them.

Why doesn't target merge? Because cross-jumping merges when blocks are identical. Target keeps them separate — the original source probably had different register assignments or something. The barrier prevented the merge. Without the barrier, jump2 merges → 10 fewer insns.

- Removing pin alone: score 1 REG-caller (318 ins, 1 register differs). So the pin is needed for a register choice.

So all three levers are load-bearing in distinct ways. This item is likely a WALL, but let's think about real C moves:

1. Keepalive (li v0,1 at end): as discussed, likely expand-void-return — but wait, the `li v0,1` at the end comes from `v0r = 1`. Without keepalive, flow deletes it. Could a real-C construct keep it? What if `v0r` is used as the argument of a function that... no.

Hmm! Wait. Look at the target: at 0x90 `li v0,1` before the D_800EC9F0 store. That's the *same* v0 value used for the store. And at 0x55c `li v0,1`. What if the source was:

```
D_800EC9F0 = 1;
...
return 1;  // void function? no
```

Actually maybe the real source is `s32` return and the decomp's void decl is a decomp artifact. C0505 says park it. But moves.md line 28 shows a MATCH by making the return real: "keepalive replaced by return v0; (s32 fn returned nothing...)". That means for that function the decl was already s32.

For us the extern decl is `void` and callers call it as void. Changing to s32 def → conflict. Let me verify by trying it: maybe gcc 2.7.2 only warns? Let's test a quick candidate with `s32 func_800D1E9C(void *arg0)` and `return 1;`. If it compiles (old gcc may allow conflicting types with a warning), we could score. But constraint forbids signature change anyway. Still, worth knowing. Actually the constraint explicitly says "no signature or decl change outside the body". So no.

2. Barrier: target has duplicated 4-call blocks, not merged. Real C move to prevent cross-jump: make the blocks differ in some way that costs 0 bytes. C0505 mentions cross-jump merges byte-identical arms; renaming regs gives no plain-C split. Options: the first arm ends with `goto ret` (to the ret label) while the second arm also `goto ret`. Target: both jump to 0x554 (ret). Hmm both identical.

But wait, target at 0x158-0x178: `jal func_800D2D44; move a0,zero; jal func_800468FC; nop; jal func_8002D8D4; nop; jal func_800D2AA0; move a0,zero; j 554; nop`. And 0x198-0x1b8 identical. So the target does NOT merge them. If the source had them identical, gcc would merge (cross-jump runs after sched). So the original source must have made them non-identical in a way that survives to cross-jump but compiles to identical bytes... e.g., different *order*? No, then bytes differ.

Hmm, cross-jump compares insns including register usage; identical sequences with same regs merge. To prevent merging without changing bytes, one could add a label between? C0505: "a label between a store and its tail blocks jump1's if-conversion" — labels block optimization. In C, labels are source-level. Can we use a `goto` to a label placed in the middle to split? A label alone doesn't emit code, but it can block cross-jumping if the label is a jump target. E.g.:

```
if (A) { calls...; goto ret; }
if (B) { calls...; goto ret; }
```
vs. target. Cross-jump merges the two tails because they're identical. If we place a label `L:` at the start of the second block and `goto L` somewhere? No goto exists.

Alternatively use a `do { } while(0)` block split (C0535) — that splits cse1 EBB. Would it stop jump2 cross-jump? C0535 says it splits cse1's extended basic block. Cross-jump (jump2) works on the CFG, not EBB; do-while(0) adds no CFG nodes (it's optimized to nothing). So probably not.

Hmm, but C0505 says: "a goto chain → structured C ... a label between a store and its tail blocks jump1's if-conversion". 

Wait, maybe the real source is structured differently: maybe the two blocks aren't identical in source because one is `func_800D2AA0(0);` with different argument spelling, or the two ifs are combined with `||`. Let's think: The first if: `if (func_800D2454(...) != 0) { A }`; second: `if (func_800D2704(...) != 0) { A }`. If source were `if (f1() != 0 || f2() != 0) { A }`? No — f2 is called after f1's else path... Actually structure: first if calls f1; if nonzero, run block and goto ret. Then second if calls f2 (only if f1==0); if nonzero run block and goto ret. Not foldable into ||.

What if the block is a macro or a `goto` shared? If source used `goto cleanup;` for both, then there'd be one copy. Target has two copies → source had two copies.

So why didn't the original gcc merge? Because the barrier? No — the barrier is our fake. Hmm, maybe because in the original, the two blocks differ: one ends `goto ret` where ret is `func_80010A98(); return 1;` and the other... both go to 0x554. Identical.

Unless the second block's `func_800D2AA0(0)` argument differs in spelling but same value 0. Same bytes.

Wait, maybe cross-jump merging was prevented by the preceding call setup: cross-jump only merges blocks whose entire contents match AND the fall-through/jump structure. Actually let me look at gcc 2.7.2 jump.c cross-jump conditions. It merges when two blocks have identical insn sequences (modulo registers). But there's a limit: it doesn't merge if the blocks are "too large"? There's `cross_jump` with a threshold: it only compares up to some number of insns? Let me check jump.c:2371 area.

Actually gcc 2.7.2 cross-jumping has `MAX_CROSS_JUMP_INSNS`? Let me grep.

Hmm, this is a rabbit hole. Let me be pragmatic: try the standard lever-free moves, score them, and if none work, record a WALL with evidence. The brief demands 30 tries per item for WALL. With 4 items that's 120 compiles. Each compile ~2-4 s. That's fine.

But the time budget is 20-30 min per item. Let's be efficient: batch candidates with sc.sh (one line per candidate).

Let me think about what real C could achieve:

(A) The missing `li v0,1`: 
- Maybe `func_80010A98()` returns s32 and we do `v0r = func_80010A98();`? Then v0 = return of func_80010A98, not 1.
- What if the last two statements are `func_80010A98(); D_800EC9F0 = 1;`? No, that stores.
- Use `v0r = 1;` then a use that generates no code: e.g. `v0r = 1; if (v0r) {}` → generates a test? `if (v0r)` with empty body gets folded away, and v0r becomes used at tree level → not dead! Then expand might still emit li v0,1 and the test gets folded by jump1? Let's think: `if (v0r) ;` — the condition is a local; fold knows v0r = 1? Only if cse/const propagation sees it. Since v0r is a pseudo assigned a constant, `if (v0r)` becomes `if (1)` → folded, and then v0r dead again. Hmm.
- What about `v0r = 1;` followed by a `switch (v0r)`? folded.
- What about passing v0r to a varargs function? That changes code.
- What about `v0r = 1;` where v0r is a *parameter-like*? no.
- What about using the value in a comparison whose result is stored to a variable that's used... chain grows.

Actually the cleanest: the function returns int in the real source. C0505 flags this as "park it". But maybe a MATCH is possible via `func_80010A98()` being K&R-declared and taking args? no.

(B) The pin: w4 score 1 REG-caller. Which register differs? Let me see the diff for w4. Maybe real-C (decl order/scope) can fix it.

(C) The barrier: 19 score. This is the hard one.

Given the item is likely a WALL, but let's actually try. Also note the item may have a PARTIAL outcome: e.g. keep the barrier but drop pin+keepalive? No — PARTIAL means win.c scores 0 keeping only some row kinds. So if we can get score 0 with only the barrier remaining, that's PARTIAL:barrier. Interesting! That's a valid outcome and much more achievable: keep barrier, crack pin and keepalive.

But keepalive removal alone gives score 1 (missing li v0,1). So keeping keepalive is necessary unless we crack it. Pin removal gives score 1 (register). So to get PARTIAL:barrier we need to crack pin and keepalive.

Hmm, can we keep only keepalive (drop pin+barrier)? No: barrier removal gives 19.

Let's check what w4 (pin removed, keepalive+barrier kept) diff is.
