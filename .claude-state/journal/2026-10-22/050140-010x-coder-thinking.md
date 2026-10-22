---
ts: 2026-10-22T11:01:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_J6SiFGSWwECfQxKX0w44
---
orig.c matches the src def. Good (item 1 fresh).

Now, the task. All 5 items are "launder" kind — meaning the lever is a `__asm__("" : "=r"(x) : "0"(x));` re-tie that launders a value. I need to find a plain-C body that scores 0.

The previous attempt found walls. I need to try NEW moves.

Key insight from moves.md successful launder cracks:
- "launder->pv=*p; pv &= mask split (real 2nd set)" — the pattern: the launder's re-tie keeps a copy from being merged; replacing it with a real 2nd SET (e.g., `pv = *p; pv &= 0xFF000000; *p = pv | ...`) gives the copy a real second definition so cse doesn't merge.
- "pointer reuse" — reuse the same variable for a new pointer kills cse sym class.

Let me now think about each item:

**Item 1: func_8017DE84 (ov_SC02_039)** — launder kind, best 13.

Two re-ties:
1. `v1 = mode; __asm__("" : "=r"(v1) : "0"(v1));` — the copy `v1 = mode`.
2. `e = ...unk20; __asm__("" : "=r"(e) : "0"(e));` in case1 arm.

Notes say: removing both → 13 (88 ins); target has `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)`. The re-tie MATERIALISES a real move v1=mode. Plain C merges the copy (cse make_regs_eqv) so the move disappears.

Ideas:
- The move `v1 = mode` needs to survive. cse merges the copy because v1 has only one use chain. But: if we use v1 in a way that requires a distinct register — e.g. if v1 is later used in a comparison chain that becomes a case table, that breaks.

Actually: notes say removing only the v1 re-tie → 3108 ins because the equality chain becomes a CASE TABLE. So the v1 re-tie prevents a case table. Interesting: the target has both the move AND no case table.

Hmm, so what if we restructure the chain to avoid the case table? E.g., use `switch` with explicit cases? Actually cse's case-table conversion is triggered by the pattern of comparisons v1==1, v1>=2, v1==0, v1>=4.

Alternative: make v1 genuinely a distinct variable with more than one set so cse can't merge, while still producing the same code. E.g.:

```c
s32 v1 = mode;
s32 v1b = v1;   // real 2nd set
```
Hmm that adds an instruction.

What about the `mode` computation itself: `s32 mode = CAST_SIGN(u16, (u8*)s0, 0x70) & 3;` then `unkFE = mode; v1 = mode;`. Target: `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)`. So the target keeps `move v1,v0` — a distinct register copy of the same value.

In GCC, a copy `v1 = mode` where mode is in v0 → `move v1,v0` normally survives if v1 is a pseudo used later... Actually cse make_regs_eqv merges copies of the same value: it makes v1 equivalent to mode (same reg). So v1 becomes v0. Then later the comparison chain uses v0 which also holds mode. And the target has v1 as a separate register.

Hmm — so the question is: how to make GCC keep the copy without an asm?

Idea: What if v1 is used AFTER something that modifies mode? mode is never modified. But we could make it so the copy is "used" in a context requiring the original to remain: e.g., store `unkFE = mode` AFTER `v1 = mode`? No, still same value.

Actually — GCC's copy coalescing: `v1 = mode` where mode has multiple uses (unkFE = mode uses it too). If mode has 2 uses, cse may not merge. Currently order is: unkFE = mode (use 1), v1 = mode (use 2). Hmm, but the store uses mode first, so mode dies at the store? Actually mode's live range ends after the store if the store is before v1=mode... no wait, the store `unkFE = mode` comes first, then `v1 = mode`. So at the store, mode is live (needed later for v1=mode). Then mode dies at `v1 = mode`.

The notes say the target has: `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)`. So order: andi → move v1,v0 → sh v0,254(s0). So the MOVE comes BEFORE the store in the target! In the source the store comes first (`unkFE = mode; v1 = mode;`). Hmm, but sched1 could reorder... no, the move v1,v0 must come after the andi (data dep), and the store sh v0,254(s0) must also come after the andi. sched1 put the move first.

If we write `v1 = mode; unkFE = mode;` then the order is naturally move then sh. But cse would still merge v1 and mode into one reg.

Hmm, the real problem: to have both a move AND a sh with v0, the compiler must keep two registers for the same value.

Trick used in other shards: "a real 2nd set" — make the variable have two distinct definitions so it isn't a copy. E.g.:

```c
s32 mode = ... & 3;
s32 v1;
v1 = mode;
v1 = v1 & 3;   // no, adds insn
```

Alternative trick: make the value stored come from a different expression with the same result, so it's not a "copy" of a pseudo but two separate computations:

```c
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
v1 = mode;
```
vs
```c
v1 = mode;
((Unkstruct_800B5CB8 *)s0)->unkFE = v1;
```
Hmm the latter: store uses v1, so v1 must be materialized... but then it's still one reg and v1 = mode merged.

Hmm. Actually! The trick: cse merges copies when it can prove equivalence and the register allocator picks one. But GCC keeps `move v1,v0` if v1 is a pseudo that's live across a point where mode's register is needed... but here both die at the same time.

Key: the register allocator won't allocate the same reg to two pseudos that overlap in live range. v1's live range is from `v1 = mode` until the comparison chain. mode's live range ends at the store (if store before) — but then v1 = mode reads mode AFTER mode died? No, mode is live to the copy point.

So actually: if the store comes first (as now), mode is live from andi to the copy. Then v1 is live from copy to the chain. There's a point where only v1 is live. So the register allocator could allocate mode and v1 to the SAME register only if their live ranges don't conflict — they do overlap at the copy point. Actually at the copy point both are live (mode being read, v1 being defined). So they must be in different registers... unless cse merges them first.

cse make_regs_eqv: for a copy `v1 = mode`, cse may substitute mode's reg into v1 (making them the same reg), because the value is the same and it's cheaper (one move eliminated). That's the "copy merge". cse does this when the copy is "redundant" i.e. v1 not yet used.

To defeat: make v1's definition NOT a simple copy of a live pseudo, but a copy of an expression. E.g.

```c
s32 v1 = ((Unkstruct_800B5CB8 *)s0)->unkFE;  // no
```

Hmm. What if we introduce a second definition of the same value from a different source expression, so that cse cannot canonicalize? E.g.

```c
s32 mode = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;
...
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
v1 = mode & 3;   // mode is already &3, so &3 is a no-op semantically but produces a new set
```
That would produce an extra `andi` — changes instruction count. Unless the compiler is smart: `mode & 3` where mode = X & 3 → GCC's simplify might fold (X&3)&3 = X&3, and then merge. Likely folds.

What about `v1 = mode; v1 += 0;`? GCC folds that.

What about making v1's set a phi/merge? Hmm.

Let's think differently. The lever-free body just needs to compile to the SAME instructions. Target: `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)`. That means in the target, mode is in v0 and v1 is a distinct copy in v1.

Alternative C that forces two registers: use a value twice in a way that requires distinct registers, e.g. pass mode to a function by value while also comparing it.

Hmm — what if we restructure: instead of `v1 = mode` then comparing v1, we do the comparison on mode but with a helper that consumes v1?

Hmm, but the target's comparison chain is on v1 presumably (the `andi v0,v0,0x3; move v1,v0` then compares v1).

What about making v1 a parameter-like copy: e.g., `v1 = mode;` where mode is `const`? No.

Alternative: what if `mode` is not a variable but the store writes a DIFFERENT expression? Like:

```c
s32 v1 = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;
((Unkstruct_800B5CB8 *)s0)->unkFE = v1;
```
Then v1 has 2 uses, no copy at all — GCC would compute andi into one reg and use it for both. Target wants a move.

Hmm, what if there are TWO separate computations:
```c
s32 mode = CAST_SIGN(u16, (u8*)s0, 0x70) & 3;
s32 v1 = CAST_SIGN(u16, (u8*)s0, 0x70) & 3;
```
That would recompute → 2 andi. No.

OK here's another classic: `v1 = mode;` where mode is a *volatile* or where mode is set in a way that...

Let me look at what the target actually does more concretely. I should look at the target assembly. Let me check the build dir. The scorer compares against build/ object. Let me get the target disassembly of func_8017DE84.

Let me find the object file.

Actually, `tools/delever_search.py --try` gives score + diff tail. Let me first run dt.sh on orig.c to see baseline score 0 and understand the output format.

Let me run that.

Also I should check the "R3.40-013 helpers" — tryinc.py, hdump.sh. And tools/cc1_dumps_tu.sh + tools/alloc_table.py.

Let me get going: run dt.sh for item1 orig.c.
