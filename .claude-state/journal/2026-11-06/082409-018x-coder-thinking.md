---
ts: 2026-11-06T15:24:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wIaqdR32QTO7bIcRCAHV
---
No effect. The do-while around the copy didn't change codegen (maybe cse still propagates or the block doesn't split because a do-while with a single stmt is merged).

Let me think more carefully about the first difference:
mine: `andi v1,s1,0x6000` / `li v0,8192` / `beq v1,v0` — target: `andi v0,v0,0x6000` / `li v1,8192` / `beq v0,v1`.

So the target's first test reads $v0 (the call's return value directly, "RAW return register"), and the constant goes to $v1. Mine has the saved copy in $s1 and the andi on it, constant in $v0.

So indeed the launder's job: keep raw in $v0 (local, dies) and flags in $s1.

Second: the `fire` copies.

Both launders are "re-tie" tricks. A real second set: for flags, the trick from the moves list is "real 2nd set". What if I do `flags = raw;` then later `flags = flags;`? identity, no.

Hmm — what about assigning `flags` in a way that is a genuine second definition that cse cannot merge: the pattern "real 2nd set `pv &= mask`" is a second set that kills the equivalence because the variable is redefined. For `flags`, I could restructure so that `flags` is set twice with the same value in a way that isn't a copy: e.g.

```
raw = call();
flags = raw;
...
```
then before the second if, reassign `flags = raw` again? cse merges both.

What about: `flags = raw;` and then use a *different expression* to compute flags' uses, e.g. keep flags only for the $s1 survival and compute `m` from `flags` — no.

Alternative approach: avoid needing two pseudos by restructuring to make the value naturally live in $v0 for the first test and in $s1 later. E.g., the first test could use the call's return directly as an expression:

```
if ((func_8012CBA4(a0) & 0x6000) != 0x2000) ...
flags = <call result>
```
requires storing the call result. Hmm.

Wait — what if I keep the call result in a variable and use it directly (one variable), and then the *global* one is created by an actual recomputation? Like:

```
raw = call();
if ((raw & 0x6000) != 0x2000) { ... }
m = raw & 0x8000;
if (m != 0 || (raw & 0x6000) != 0x2000) ...
```
That's one pseudo living across the calls → $s1 everywhere, first andi on $s1. Not target.

The target has the first test on $v0 (the return reg) and later uses on $s1. So there must be two pseudos: one that is the call result (dies at the andi), one that survives the calls. The natural C way: `raw = call(); flags = raw;` — and then the first test uses raw, later uses flags. Without the asm, gcc merges them. But wait, does it? The two pseudos have different live ranges: raw dies at the andi; flags is live from the copy across the calls. If they were merged into one pseudo, the merged live range would be from call to last use, crossing the calls → global. That's what happens (mine: andi on s1).

Actually no: mine has `andi v1,s1,0x6000` meaning the merged pseudo is in $s1 from the start (the call result copied to s1). Hmm.

How to prevent the merge? In gcc, copy propagation (flow? or cse's canon_reg) rewrites uses of the copy destination to the source. cse's canon_reg uses the reg_eqv table: `flags ≡ raw` after the copy; then when compiling the uses of flags later (in the same EBB), it substitutes raw. But the first if block has calls; does the EBB continue across the if? An EBB ends at a label/jump target. The `if` creates a branch; the join point is a new block. cse1 works on extended basic blocks: it continues across jumps only into blocks with a single predecessor and no label... The join after the if has two predecessors → new EBB. So cse shouldn't propagate raw into the uses after the join!

Unless the merge happens in global-alloc via copy coalescing: `flags = raw` is a copy; local-alloc/global-alloc coalesce copies when possible. Since raw dies at the copy... no wait, raw is used in the first if after the copy, so they're not coalescible directly (interference).

Hmm, let me actually look at the RTL. Let me dump cc1 output for a1 vs the target. Use tools/cc1_dumps_tu.sh. Actually let's check the diff more: mine 251 ins vs target 253. And register pairs v1->v0 x2, v0->v1 x2, s1->v0 x1.

Let me look at the whole assembly diff to understand. Maybe use dt.sh's diff and compare with a full listing. Let me generate the mine listing: delever_search might have a mode to dump. Let me check --help.
