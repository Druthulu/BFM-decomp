---
ts: 2026-11-07T00:47:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6HwCL6w3MXCap1RK2j4e
---
Best is 7 (w31, w32). Still not 0. The register issue (val v1 vs v0) remains.

Tries so far on item 2: w1,w2,w3, w10..w20 (11), w30..w39 (9) = 23. Plus orig (baseline, not a try). Need 30 for a wall.

Time: item 2 started 17:36; now ~17:53 → 17 min. I have time for more.

Let me think harder about the register issue.

The problem: local-alloc gives v0 to the const-1 pseudo (short life) and v1 to val. Target: val→v0, const→v1.

Real-C moves to change this:
1. Make val's life shorter: impossible (its use is at the end).
2. Make the const's life longer: possible if the li is born earlier in the RTL. E.g., if the source computes the constant 1 into a variable *before* the stores: `s32 one = 1;` at the top of the block, then `D_801B7988 = one;` later. The `one` pseudo would be born at the assignment (top) and die at the store (late) → long life → low priority → val gets v0!

But `one = 1` emits a `li` at the top → an extra insn (the target has exactly one li). Unless the compiler rematerializes: `one = 1` is a constant, and cse/combine may propagate the constant to the store and delete the li if `one` has only one use (REG_EQUIV). That's what typically happens: a constant-assigned local used once gets its value propagated. Then the li is born at the store again → same priority.

Hmm. But what if `one` is used twice? Then the li stays. That's an extra insn... but maybe the second use is free?

3. Change the *order* of the RTL so the const's pseudo has a longer life: e.g., `D_801B7988 = 1;` placed *before* the three stores in the source. Then the li is born at that point and the sw right after (short life still).

4. Make val's qty bigger: qty_size? If val were a bigger mode... no.

5. **Copy preference**: local-alloc's find_free_reg considers copy preferences. If val's load is a copy from memory into a reg, no preference.

6. **Make the const 1 not need a register**: if the store were `sw` of a register that's already live... e.g., if the constant 1 could reuse v1 from an earlier computation. In the target, v1 holds 1 and is used once.

Hmm, what if the constant 1 is produced by a *comparison* result? no.

7. What if `val` is *also* used in the block before the stores, so its life starts earlier and... no, longer life = lower priority.

8. What if we make the const's qty *die* at the same insn it's born (life 1)? Then its priority is even higher.

Hmm.

9. What about **global-alloc**? If the switch block's values are allocated globally (across blocks), the const 1 pseudo might be local. Hmm.

10. What if val is allocated by *global-alloc* instead of local-alloc? Global-alloc's priority is different: it uses refs/live-length across blocks. If val were live across blocks (e.g., used after the switch), global-alloc would handle it. In the target, val is used only in case 0.

Hmm, what if the *declaration* of `val` is moved to the function scope (outside the case block)? Then the pseudo is still local to the block, but maybe the allocator treats it differently (scope affects where the variable lives?).

Actually — decl scope affects *which* pseudo (the variable's live range is still the block). Not the priority.

11. What if the load's destination gets a *preferred* hard reg via a copy? E.g., `s32 t2; ... t2 = val; ... use t2` — extra insn.

Hmm.

Let me reconsider the problem: maybe I'm attacking the wrong lever. What if the ORDER can be fixed differently such that the register allocation follows?

In the target: load val → v0; li 1 → v1. In mine (w16/w31): load val → v1; li 1 → v0.

Since local-alloc assigns in qty priority order and the first free reg is v0... Actually find_free_reg prefers the *lowest-numbered* free register in the class. v0 = reg 2, v1 = reg 3.

If the const gets v0 and val v1 — that's what happens.

To flip: give val a higher priority. Priority = floor_log2(refs)*refs*size/(death-birth).

val: refs = 2 (one def, one use) → floor_log2(2)=1 → 1*2*4 = 8. Life = death - birth.
const: refs = 2 → 8. Life = 2 (li at index n, sw at n+1... actually the li and sw are 2 apart in the RTL).

So val's life must be < 4 for it to win (8/life > 8/2 → life < 2; equal life → tie → lower qty number wins → val's qty is lower (born earlier) → val wins!).

Wait: if val's life == the const's life (2), the tie-break `*q1 - *q2` (lower qty number first) favors val (born earlier). So if val's life were also 2, val would win v0!

val's life: from the load (insn 53) to the addiu (insn 73) = 20 in the RTL order. Can't shrink without moving the addiu.

Hmm, unless the *addiu* is scheduled before the stores in the RTL (source order). In the source, `D_801B7A84 = val + 1;` is last.

What if the source computed the increment early: 
```
val = D_801B7A84;
val = val + 1;      /* now val's use is adjacent */
... stores ...
D_801B7A84 = val;
```
Then val's life = 2 (load, addiu adjacent) → priority 8/2 = 4 = the const's 4 → tie → val's qty number is lower → val gets v0! And the code: load val; addiu val+1; then the stores; then sw val. But the target has the addiu near the end (8438), not right after the load (8410). Hmm, that would change the instruction order: mine would be load, addiu, stores, sw.

But wait — sched1 might sink the addiu... The addiu depends on the load; the final store depends on the addiu. sched1 could move the addiu later (it's free to). Since the target has the addiu at the end, maybe sched1 would produce that.

That's worth trying! And it's real C: `val = D_801B7A84; val = val + 1;` then `D_801B7A84 = val;`.

Hmm, but that changes `val + 1` into a two-step. Let me also try `val = D_801B7A84 + 1;` — the addiu's source would be the memory; cse would fold `val = D_801B7A84 + 1` into load+addiu with the load adjacent to the addiu. Then `D_801B7A84 = val;` at the end. That's a natural C spelling and gives val a short life!

Let me try:
```
s32 val;
...
val = D_801B7A84 + 1;
do { three stores } while(0);
*p = 0;
D_801B7988 = 1;
D_801B7A84 = val;
```
This is semantically identical to `D_801B7A84 = val + 1` — actually yes: val = *(D_801B7A84) + 1; then store.

Wait, careful: `D_801B7A84 = val + 1;` where val = D_801B7A84 (read earlier). Semantically the same as `val = D_801B7A84 + 1; ... D_801B7A84 = val;` provided nothing modifies D_801B7A84 in between. Correct.

Let me also consider that the target's RTL order (from the .sched dump): the load 53, then the asm 55, then the stores 58..67, then 70,72,75,77. In the target's pre-sched order (with barrier), what is it? Let me check the .rtl/.cse2 dump for the target: is the addiu adjacent to the load or at the end?

In the target's .sched dump, insn 75 and 77 are the addiu and the final store, both near the end. In the target's .rtl (initial RTL), let me check the order of 53, 73/75/77.

Let me look at the target's .rtl dump for the block.
