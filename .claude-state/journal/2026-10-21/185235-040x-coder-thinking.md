---
ts: 2026-10-22T00:52:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_T4vFbjusGmvYbrBe52D2
---
This dumps gcc-2.7.2 RTL for a TU. The final `.s` output (the -o $tag.s) IS the assembly! So `cc1_dumps_tu.sh <file.c> <tag>` produces $d/$tag.s = the compiled assembly of the TU. That gives me the target's asm (for the src def, which matches).

But wait — the .s from cc1 is the pre-assembler output of the TU, in the same form as the target's object? The target object was built with the same compiler, so the function's instruction sequence in the .s should match the target.

This is a great tool: I can compile ANY candidate TU (a spliced copy) and see its .s. But my candidates are bodies spliced into the TU... The tool takes a .c file (the spliced TU). I can create a spliced TU copy? The src file is huge (179KB); copying it into my shard dir requires a file write of the whole file (I'd need to read it — 179KB, over the guard).

Alternative: use --keep with delever_search to get the candidate object, then... objdump denied. Hmm.

Hmm, but wait: is `mipsel-linux-gnu-cpp` / `cc1` runnable from bash? The tool is in tools/ so maybe allowed. Let me test running cc1_dumps_tu.sh on the src file for the TU. That's a big compile but fine.

Actually, the key question: do I need it? For item 2, the residual is a 2-instruction swap. Maybe I can find the fix by trying a couple of variants (each ~30 s). Let me first try the "constant earlier" variant and the "arg into a temp" variant.

Let me think about which is most likely. Actually, let me reconsider the structure of the target's tail:

```
79 bne a2,v0,98c      (branch)
80 sll a2,a2,0x8
81 sll a2,a2,0x8   ??
82 li a2,15
83 sll a2,a2,0x8
84 ori a1,a1,0x3000
85 or a1,a1,a2
```
Hmm, that doesn't work: sll a2,a2,0x8 twice in a row?

Let me reconsider: maybe target[80] = sll a2,a2,0x8 is the `x = x << 8` and target[81],[82],[83] = mine[81],[82],[83] which I believe are [li a2,15 / sll a2,a2,0x8 / or a1,a1,a2]? Hmm, but then where's the ori?

Let me carefully re-derive from cand02's diff (which had a bigger region) plus cand03's.

cand03 diff:
```
insert  mine[83:83] target[83:84]
   83  --      | li a0,2366
delete  mine[84:85] target[85:85]
   84  li a0,2366 | --
```
So mine[84] = li a0,2366 and target[83] = li a0,2366. All other positions equal. So mine[83] = target[84], mine[85] = target[85].

From cand02's diff (a different candidate but same structure region):
```
replace mine[79:81] target[79:81]
   79  bne a2,v0,988 | bne a2,v0,98c
   80  ori a1,a1,0x3000 | sll a2,a2,0x8
insert mine[84:84] target[84:85]
   84  -- | ori a1,a1,0x3000
replace mine[84:85] target[85:86]
   84  or a1,a1,a3 | or a1,a1,a2
```
Hmm, cand02's diff had "insert mine[84:84] target[84:85]" with target[84] = ori a1,a1,0x3000, and "replace mine[84:85] target[85:86]" — mine[84] = or a1,a1,a3 ↔ target[85] = or a1,a1,a2.

Wait, in cand02: mine[80] = ori, mine[84] = or a1,a1,a3. In cand03: mine[83] = ?, mine[84] = li a0,2366, mine[85] = or.

cand03 vs cand02 differ in the tail: cand02 had ori at 80 and or at 84; cand03 has (something) at 83, li at 84, or at 85.

Hmm, so in cand03, mine[83] = target[84] = ori a1,a1,0x3000 (since cand03's target[84] = mine[83] and in the target the ori is at 84). ✓. And mine[85] = target[85] = or a1,a1,a2.

So cand03's tail:
79 bne a2,v0,988
80 = target[80] = sll a2,a2,0x8
81 = target[81]
82 = target[82]
83 ori a1,a1,0x3000
84 li a0,2366
85 or a1,a1,a2

target:
79 bne a2,v0,98c
80 sll a2,a2,0x8
81 = mine[81]
82 = mine[82]
83 li a0,2366
84 ori a1,a1,0x3000
85 or a1,a1,a2

And mine[81],[82] = target[81],[82] = probably li a2,15 and sll a2,a2,0x8? Hmm, but that leaves: sll(80), ?(81), ?(82), ori(83). If 81 = li a2,15 and 82 = sll a2,a2,8, then the sequence is sll, li, sll — the x<<8 with the 0xF override.

Hmm, but where's the `or a1,a1,a2` (x) — at 85. And the ori at 83. So the a1 chain: ori a1,a1,0x3000 (83/84) then or a1,a1,a2 (85). But wait, the ori depends on vol (a1 = vol?), so a1 is set by the ori. Hmm, but the ori is at 83 and the x-chain at 80-82. OK.

So the target's tail order: [x-chain: sll, li, sll] then [li a0,2366] then [ori a1,a1,0x3000] then [or a1,a1,a2].

Hmm, interesting: the ori comes AFTER the li a0 and after the x chain.

In the original source with the launder:
```
{
    s32 flg = 0x3000;
    func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
}
```
The expression `((vol|flg)|x)&0xFFFF` is the 2nd arg. Its evaluation: vol|flg → ori, then |x → or, then &0xFFFF (folded away). So the ori and or are the arg's insns.

And `li a0,2366` for the 1st arg (constant).

For the li to be BEFORE the ori in the final schedule, the constant's LUID must be earlier. Hmm, unless... gcc's expand creates the constant's set (li) BEFORE expanding the second arg? The args are expanded in the order given in the RTL call (a0, a1, a2) but gcc's front end builds the arg list right-to-left (the last arg is expanded first). Hmm, for a call `f(c, expr)`, the front end (c-typeck / gimplify) evaluates the args in reverse order, so `expr` is evaluated first, then `c`.

BUT: for a CONSTANT arg, gimplification creates a gimple assign of the constant to a temp, and the temp is then used as the arg. The assign might be created at the point of the call. The RTL for the constant temp: `li a0, 2366` — created by expand at the temp's definition point.

And the second arg's expression: its gimple assigns are created when the expression is evaluated (before the call). So the expression's RTL has earlier LUIDs.

So mine's order (expr first, then li) is the natural one. The TARGET has the li first — meaning in the target, the expression's ori got a LUID AFTER the li.

How? If the expression's computation was DEFERRED: e.g. if the `vol|flg` expression's evaluation was placed in a later block or after the constant's temp assignment. Hmm — gimplification order: gimplify_call_expr evaluates args in order 0..n-1? Let me think: `gimplify_call_expr` iterates over the arguments in REVERSE (from last to first) so that the evaluation order is right-to-left. For each arg it calls gimplify_expr. A constant arg → gimplify_expr creates a temp with the constant value (a gimple assign `D.x = 2366`).

Hmm, if it iterates in reverse, the LAST arg (the complex expr) is gimplified first → its assigns come first → earlier LUIDs → the expr's ori before the li. That's mine.

For the target to have the li first, the args must be gimplified in FORWARD order, OR the constant's temp must be created earlier for another reason.

Hmm! Unless the expression's ori is NOT part of the arg expression but a separate statement that comes after the call's constant materialization. E.g., if the source were:

```
s32 c = 0x93E;         /* gimple assign D.c = 2366 — created BEFORE the call's args */
... 
func_8002D4C8(c, ((vol|flg)|x)&0xFFFF);
```
Then D.c = 2366's assign is created earlier (at the statement), so the li has an earlier LUID than the arg expression's ori. But gcc would then fold the constant into the call (gimplify folds constants into the call arg) → back to the natural order.

Unless the constant temp is NOT folded: e.g. if `c` is used more than once. But that's +1 insn.

Hmm, hold on. Maybe the answer is different: maybe in the target, the `li a0,2366` is NOT the call's arg setup but something else! 0x93E = 2366. Hmm, what else could 2366 be? It's the first argument of func_8002D4C8. So it is the arg.

OK, radical idea: maybe the launder's presence changed the *order of gimplification*! The launder is a statement between the vol computation and the x computation:
```
vol = ...;
__asm__("" : "=r"(vol) : "0"(vol));
x = ...;
```
The asm creates a new SSA-ish temp. Hmm, the asm statement's gimple assign is created at its position. The call comes later. That doesn't change the arg order.

Hmm, but here's a thought: with the asm, `vol` becomes a NEW temp V (the asm output). The expression `((vol|flg)|x)` uses V. The gimple for the call's 2nd arg is an expression tree; gimplification creates temps for subexpressions. The order of temp creation within the arg expression: `vol|flg` first, then `|x`.

I'm stuck on theory. Let me try the empirical route with a few variants and see. Since each try is ~20-40 s, and I have 30 min budget per item, let me try 4-6 variants:

cand05: constant in a variable assigned early (before the if block):
```
s32 c93e = 0x93E;   /* at the top of the function body */
...
func_8002D4C8(c93e, (vol|x)&0xFFFF);
```
Hmm, but then the constant's assign is at the top → early LUID.

Wait, but that would ALSO change the whole function's structure (the constant's temp exists across the whole function → maybe allocated to a callee-saved reg → +insns). Risky but let's see.

cand06: keep the arg expression but split it:
```
{
    s32 flg = 0x3000;
    s32 arg;
    arg = (vol | flg) | x;
    func_8002D4C8(0x93E, arg & 0xFFFF);
}
```
Hmm.

cand07: reorder so the ori statement comes after the constant's use... impossible.

cand08: use `& 0xFFFF` differently: `((vol | flg) | (x & 0xFFFF))`? Hmm.

Hmm, hold on! Let me reconsider the target's ori: `ori a1,a1,0x3000`. In the ORIGINAL source, `vol | flg` where flg = 0x3000 → `ori a1,a1,0x3000`. And `a1` at that point = vol. But hmm, wait: in the target, is `a1` = vol? The call is `func_8002D4C8(0x93E, arg)` → a0 = 0x93E, a1 = arg. So a1 = the 2nd arg = ((vol|flg)|x)&0xFFFF. So `ori a1,a1,0x3000` computes a1 = vol|0x3000 — so at that point a1 holds vol. Then `or a1,a1,a2` → a1 |= x (a2 = x). ✓.

And the `& 0xFFFF`: mine and target both lack an andi (folded away). OK.

Now: in the target, the ori is at 84 and the li a0 at 83. Both are arg setups. In mine, the ori is at 83 and the li at 84.

What if in the target, the ori is NOT the `vol|flg` from the expression, but comes from a DIFFERENT source: e.g. in the target, the launder's asm output V is the input to the ori, and the ori was created as part of the arg expression, so its LUID is at the arg expression's expansion — which happens BEFORE the constant's temp...

Argh, the ordering keeps pointing the wrong way.

Hmm hold on, maybe I have the direction of LUID vs. scheduling backwards. In sched1, insns are scheduled by priority; among equal priority, earlier LUID first. The `ori` (part of the arg expression) has an earlier LUID than the `li a0` (created at the call). If both have the same priority, the ori goes first → mine. For the target, the li must have HIGHER priority than the ori (or the ori lower).

The birth boost! sched1 boosts insns that are "born" (single-set) — the li a0,2366 is a single-set pseudo (a0 is set once) → boosted. The ori is also single-set (a1 set once here? no — a1 is set by the ori AND by the or → 2 sets) → NOT boosted.

Hmm, so both mine and target have the same set structure... unless in mine the ori has 1 set and in the target 2 sets (or vice versa).

In mine (cand03): `vol = vol | flg;` then `func_8002D4C8(0x93E, (vol | x) & 0xFFFF)`. Here the ori sets a1 (1 set: a1 = vol|flg) and then `or a1,a1,a2` sets a1 again (2 sets). Same in the target.

But the *priority* of the ori might depend on the chain: in mine, the ori is a separate statement whose LUID is before the call; in the target, the ori is part of the arg expression.

OK, ENOUGH. Let me try the empirical route: try variants and see which one flips the order. Cheap enough.

Variant A (cand05): make the a1 arg a temp assigned before the call AND the constant a temp assigned before that:
```
{
    s32 flg = 0x3000;
    s32 c;
    s32 arg;
    c = 0x93E;
    arg = (vol | flg) | x;
    func_8002D4C8(c, arg);
}
```
Hmm, that would likely produce `li a0,2366` and `or a1,a1,a2` in some order, maybe with extra moves.

Variant B (cand06): swap: compute the arg into a temp, then call with the constant first:
```
{
    s32 flg = 0x3000;
    s32 arg = (vol | flg) | x;
    func_8002D4C8(0x93E, arg);
}
```

Variant C (cand07): keep everything as cand03 but hoist the `vol = vol | flg;` statement to just after the x-chain? It already is.

Variant D (cand08): make the ori not the first arg op: write the expression as `((vol | x) | flg)`? That changes which op is first: `or a1,a1,a2` (x) then `ori a1,a1,0x3000`. Then the order would be [or, ori] hmm, that swaps the last two. But the target has ori then or. Hmm, but maybe the schedule would then place the li between them? Unlikely.

Hmm! Wait. Actually, let me reconsider Variant D more carefully: in the target the order is ori(84) then or(85) — consistent with the expression `((vol|flg)|x)`. In mine cand03 the same order. Fine.

Let me think about what else could delay the ori by one slot in the target... In the target, the ori is at 84, right before the or at 85 and the jal at 86. In mine, the ori is at 83, then li at 84, then or at 85. So in mine the li got scheduled BETWEEN the ori and the or. That's odd — the or depends on the ori (a1). The li (a0) is independent. So the scheduler put the li in the slot between them.

In the target, the li is BEFORE the ori. Both are valid orders for the scheduler; the difference is priority.

The priority of the ori in the target might be LOWER (because in the target, the ori is part of a longer chain? no...).

Hmm, here's a thought: in the target (with the launder), the ori consumes the ASM's output pseudo V. The asm has priority 1 (per §373). The chain: asm (pri 1) → ori → or. Since the asm is pri 1, the ori inherits a low priority?? Hmm, but the asm isn't in the final asm (0 bytes) — but its effect on priority remains in the RTL (the asm insn is still in the RTL until... hmm, actually the asm IS in the RTL, just emits no bytes).

So in the target, the ori is downstream of a pri-1 asm → its priority is lower → scheduled later. In mine, the ori is a plain statement.

So the lever is: make the ori (or the value feeding it) come from a low-priority insn. Hmm, in plain C, what has low priority? Nothing like an asm.

Alternatively: make the li a0 have HIGHER priority. The li is a constant → single-set → birth-boosted. Hmm.

What if I make the constant's set have 2 sets (so no birth boost) — no, that lowers it.

What if the constant is used TWICE (so it's not single-set)? Then it'd have a register and 2 sets → lower priority → worse.

Hmm, what if the constant's li is scheduled early because it's in the "call group"? In sched1, the call and its arg setups form a group; the group is scheduled together in LUID order. If the li's LUID is before the ori's LUID, the li goes first.

In the target, the li's LUID < the ori's LUID. The li is created at the call (expand creates the constant pseudo at the call's expansion). The ori is created when the arg expression is expanded. If the front end gimplifies args in FORWARD order (a0 first), the li's LUID would be earlier!

When does gcc gimplify args forward vs reverse? In gimplify_call_expr:
```c
  /* Process the arguments.  */
  ...
  for (i = nargs - 1; i >= 0; i--)
```
Hmm, gimplify_call_expr in gcc 2.7:
```c
  /* The args are processed in reverse order... */
  for (i = nargs - 1; i >= 0; i--)
    {
      ...
    }
```
Hmm, I recall the comment: "We reverse the order of the arguments because we want to evaluate them in reverse order (right to left)". But that's for the general case; for a simple constant arg, gimplify_expr creates a temp.

Hmm, but there's a subtlety: gimplify_expr for a CONSTANT doesn't create a new temp — it returns the constant itself! Then the arg is a constant, and expand creates the li at the call site... but the ORDER of expansion of the call's args in RTL: `call f (a0, a1)` — expand processes the args in order (a0 first)? The RTL insn's args are all "created" at the same time in expand (the call insn), and the li for a0 is created by expand when it processes the call's arg list — which it does in order (arg 0 first? or via `init_cumulative_args`).

In expand's `expand_call`, the args are processed in order 0..n-1, and each arg's RTL is generated there (via `expand_expr` for non-constant args). The constant args are converted to registers in `init_cumulative_args`/`convert_arg_registers` — the li for a constant arg is created in `convert_arg_to_registers` for each arg in order. So a0's li gets an earlier LUID than a1's expression expansion? NO — the expression for a1 was already expanded at gimple time into separate gimple statements (temporaries), so their RTL exists before the call insn.

So: the constant's li is created during expand_call (at the call), while the expression's ops were expanded earlier (when their gimple statements were expanded, in statement order). So the expression's ori has an earlier LUID.

BUT: `convert_arg_to_registers` for a constant creates `li a0, 2366` — hmm, but actually in gcc 2.7's `convert_arg_registers`, for a constant arg it emits the constant into the arg register at that point (during expand_call). So the li's LUID is at the call.

OK so the target's order (li before ori) implies the ori's LUID is LATER than the call's li. That means the ori was expanded AFTER the call insn was created?! Impossible in normal flow...

UNLESS the ori is not part of the call's arg expression but a separate statement AFTER the call's constant materialization. But statements come before the call...

Hmm, unless the ori is in a LATER BLOCK (a branch arm)! sched1 schedules per-block; the block containing the call might be scheduled after another block. But the ori and the call are in the same block.

I'm clearly missing something. Let me just look at the target's actual asm. Let me use the cc1 dump approach on the CURRENT src file (which equals the target) — that gives the final .s. The dump dir must be under my shard dir (DUMP_ROOT env var). But running `bash tools/cc1_dumps_tu.sh` — is that allowed? It's in tools/. The command has env var + args. Let me try.

Actually the script does `cd /home/musashi/bfm-decomp` itself and uses DUMP_ROOT. Let me run:
DUMP_ROOT=.run/P40/T11/G15/dumps bash tools/cc1_dumps_tu.sh src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c g15_030

The output .s is $d/$tag.s. Then I can read the function's part with grep/sed. The .s for the whole TU is big; I'll grep for the function label and print a range.

Note: this compiles the CURRENT src (with the launder) = the target.

Let me try it.
