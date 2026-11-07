---
ts: 2026-11-06T14:48:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ypqZZoQiavMM9KFkQNs5
---
Identical diff. So v7/v8 didn't change anything (the assignments folded away). The fold persists.

So the C front-end/cse is folding `t != 3` given t == 5. The `t = (s16)a1` and the save/restore are optimized away (front-end knows they're redundant, or cse).

Let me check WHERE the fold happens: front-end or cse. If the front-end, then no C-level trick works (the front-end's `fold` doesn't track conditions). Actually, the front-end doesn't track conditions across statements, so it can't fold `t != 3` given `if (t == 5)`. So it must be cse or jump.

Let me look at the .rtl dump (before cse) for c1 to see if the `t != 3` branch is present. Then the .cse dump (after cse1) and .cse2.

Let me grep the .rtl dump for the case 5 branches. The function's case 5 is around insn... let me find the `(const_int 3)` branches.

Actually, let me look at the .cse dump (after cse1) vs .rtl. If cse1 folded it, the .cse dump has fewer branches.

Let me count the occurrences of `(if_then_else (ne:SI (reg:SI 16` or similar in .rtl vs .cse vs .cse2. Hmm, the reg numbers.

Let me just look at the .rtl dump for the case 5 block. Let me find `const_int 5` in the .rtl.

Actually, let me take a different approach: let me check if the fold is done by cse by looking at the .cse2 dump's branch structure in the case 5 region. The target (orig) has 3 branches; c1 might have 2. Let me count the `if_then_else` in the case 5 region.

Hmm, this is slow. Let me instead try to find a real-C formulation that naturally emits the target's 3-branch structure. 

Let me reconsider the C. The target's structure:
```
beq t,3,L70      # t==3 -> sel_054
bne t,5,L71      # t!=5 -> after
bne t,3,L73      # t!=3 -> sel_094
L70: sel_054
```
This is: `if (t == 3) goto sel_054; if (t != 5) goto after; if (t != 3) goto sel_094; sel_054: ...`

What if I write the C EXACTLY like this (with explicit gotos)?
```
if (t == 3) goto sel_054;
if (t != 5) goto after;
if (t != 3) goto sel_094;
sel_054:
    sel = &D_8018C520;
    goto set_sel;
sel_094:
    ...
after:
    ...
```
But the C would still fold `t != 3` given `t == 5` (fall-through of the `t != 5` branch). The compiler's cse/jump would fold.

Unless... the `if (t != 5) goto after;` doesn't record t==5 on the fall-through because it's a `!=`? cse's record_jump_equiv records the condition on both paths. For `bne t,5,after`, the fall-through is t==5, so cse records t==5. Then `t != 3` folds.

Hmm.

What if I invert: `if (t == 5) goto in5; goto after; in5: if (t != 3) ...`. The fall-through to after is t!=5, and in5 is reached from the t==5 branch. cse might record t==5 in the in5 block (from the branch). It does (record_jump_equiv adds the equivalence on the target too). So folds.

Hmm.

What if the in5 block has multiple predecessors? As I discussed, that prevents cse from recording t==5 (cse's record_jump_equiv only applies if the block has one predecessor? Let me check). In cse.c, `record_jump_equiv` is called with the branch and it records the equivalence for the target and fall-through, but only if... let me look.

Let me grep cse.c for record_jump_equiv.
