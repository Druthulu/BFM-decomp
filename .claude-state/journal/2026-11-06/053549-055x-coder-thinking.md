---
ts: 2026-11-06T12:35:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hgiUhYiel0anhzlQOyrQ
---
This is intricate. Empirically it's easier to search C variants. But my budget for this item is 20-30 min. I've spent ~20 min on item 2 already (started 05:30, now maybe 05:50). Let me check the time.

Actually — an important thought: maybe the target's `ret` in v0 comes from the `register` pin in the *original* src, and this item might be a WALL. But the shard's purpose is to find lever-free cracks. Let me try a handful of quick variants (each ~10 s):

v1: early returns `return ret;` + ret declared with `s32 ret;` and the *last* statement before the first early return sets ret? no.

v2: make the arms assign via the struct field: `((...)->unk2 = ret = 7;`? changes insns.

v3: use a union/s16 for ret.

v4: change `return ret;` at the end to `return (s32)ret;` — same.

v5: put the `ret = <const>` assignment as the FIRST statement of each arm? no.

v6: declare ret as `s32 ret;` but make the early returns `return ret;` while adding `ret = param_1; ret = 0;`? no.

Let me think about local-alloc: `qty` allocation happens before global. ret is used in the arms (set) and at STORE. In local-alloc, each basic block's qty gets a hard reg if possible; the arms are separate blocks. Local-alloc might assign v0 to the arm qty (since v0 is free at the end of the block). Then global-alloc merges.

Hmm, in c2 ret got a0. So local-alloc's choice for the arm qty was a0? At the end of an arm block: `li a0,7; j` — hmm.

Actually, the ret pseudo's live range: defined in the arm, used at STORE (a different block) → it's live across blocks, so it's global.

What if the C made the STORE happen in the same block? e.g. each arm stores and returns (duplicating STORE)? Then the target's shared `sh v0,2(s1)` wouldn't happen.

Alternatively, make `ret` NOT live across blocks: if the C were `return` directly with the store inlined... no.

New idea: what if the arms' assignment target is a variable that's *also* stored to unk2 in the same block? Like:

```
if (unk70 == 0x28) {
    ...
    unk2 = 7;
    ret = 7;
    goto STORE;
}
```
No.

Let me look at the problem from the "what does the target C look like" angle differently: maybe the target's C doesn't have a `ret` variable at all but rather `return` inside a helper... The `j 1e3c` at the early exits and `j 1e38` at the arms are different labels, consistent with `return ret` (→ return label 1e3c) and `goto STORE` (→ 1e38). OK.

So the C is as given. The only lever-free hope: make global-alloc give ret v0 by changing ret's refs/live ranges.

Let me try: make the STORE label's use `unk2 = ret;` come BEFORE... it does.

What about adding `ret = ret;`? no.

Hmm, what about the possibility that `return ret;` at the end plus `unk2 = ret` gives ret a *copy preference* to v0, and the competing allocno that prefers v0 is... `ptr` (func_8012C1B8's result → a0). In the target ptr is a0 too. Hmm.

Let me just look at a cc1 -dl dump of c2 to see ret's allocno priority and which allocnos prefer v0. That's the systematic route. But time.

Cheaper experiment: what if I change the early returns to `return ret;` AND make ret's first def at entry be a *constant 0* but place it so that gcc folds it into v0 without an insn... no.

Let me try a different cheap experiment: make the last arm (line 166) `ret = ... + 1;` → `return ... + 1;`? no, STORE needs it.

Honest reassessment of budget: I've used ~25 min on item 2. Let me spend 10 more minutes on 3-4 quick variants, then record a WALL with best score if none crack.

Quick variants to try (each 1 compile):
A. c2 + `s32 ret;` → `s32 ret = 0;`? No (adds li).
B. c2 but the early returns are `return ret;` and ret is declared *after* a dummy? no.
C. Make the arms' constant assignments `ret = (s16)7;`? Might change nothing.
D. What about making the return at STORE `return ret;` into `return (ret = ret);`? no.

Hmm, what about the trick from moves.md line 217: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class". Not our issue.

Alternatively: maybe accept a *slightly different* C where the early returns return `ret` but ret is defined at entry to the value it would have... 

Wait, actually! Here's a thought: the first early return is `return ret;` where ret is uninitialized. gcc's flow analysis: an uninitialized pseudo use makes it live-in at entry. But what if we instead write the early return as `return ret;` AFTER assigning `ret = param_1;`?? That would be `move` — no.

Hmm, what if the early return is `return ptr;`? For the first: `func_8012CAE4(param_1); return ptr;` — ptr isn't defined yet at that point (it's defined after). Actually in the C, the first early return is before `ptr = func_8012C1B8();`. So no.

What if the C declares `ret` inside the first if? no, shared.

Let me try the direct approach: force ret into v0 via a *copy to a v0-typed expression*. In gcc 2.7.2, no way to name $2 without asm/register.

Therefore the only lever-free route is allocator priority/order. Let me check the cc1 dump: `-dl` prints allocno priorities and conflicts. But I need to see WHY v0 isn't chosen. Let's dump c2's TU with cc1 and look at the .greg (global) dump for the ret allocno. That's the systematic route and I have the tooling. But the TU is 152KB and dumps go under my item dir; must delete after.

Actually, cheaper: let me first check if the *pinned* original differs only in ret's allocation. We know it does.

Given time, let me try one quick idea first: `return ret;` in the early returns BUT with ret initialized at its declaration to a value that's already in v0 at entry? No such thing.

Second quick idea: change the arms to `ret = 7;` → the target's li v0,7 in the j delay slot. What if instead we write the arms as `ret = 7; goto STORE;` (as now) and add `return ret;` at STORE... same.

OK let me do the dump. Use cc1_dumps_tu.sh with the --keep TU (the spliced TU for c2). Hmm, --keep produces the TU with c2 spliced. Then dump with DUMP_ROOT under my item dir.

Actually, tools/cc1_dumps_tu.sh takes the .c file. The --keep TU is at .run/P36/engine/score/ov_SC01_009__func_8017FFD0/pNN/ov_SC01_009_jr_8017E590.c. Let me get it for c2 and dump. DUMP_ROOT must be absolute under my shard.

Let me do it.
