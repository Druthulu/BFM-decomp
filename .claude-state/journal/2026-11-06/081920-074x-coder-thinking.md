---
ts: 2026-11-06T15:19:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UvJO51mklun21SS37CNl
---
All fold (front-end folding). k4 (`t = 0; t = (s16)a1;`) also 4 — the front end probably folded t=(s16)a1 to the known value... or cse folded. Either way, no.

40 tries now, ~13 min on item 2. I need ≥20 min. Let me use a few more minutes productively: try the "compare against a non-constant 3" idea to see if the branch can be produced without folding, and try comparing t with `(s16)(a1 - 2)`? no.

Hmm, actually — let me reconsider the target's instruction sequence once more:
```
704: bne s0,v1,71c
```
s0 = t. What if the source is `if (t != 3)` where t is compared, and the compiler folds... 

WAIT. Maybe the launder's effect isn't just opacity — maybe it forces `t` to be re-loaded into a NEW pseudo, and the compare uses the NEW pseudo. Hmm, the asm ties output to input, so t is redefined. In the RTL, the asm is `(set (reg t') (unspec [(reg t)]))`. Then t' is a new value. The compare uses t'. So the compare register is the same (s0) after allocation.

For plain C, we need a *new value* for t that the compiler doesn't know. The only cheap way: a copy from a register whose value is unknown. In g1, `a1` (full) is unknown — and comparing a1 worked. But the compare register differs.

What if we make the unknown value be in s0? We could do `t = a1;` — but t is s16 (truncates). What if we declare a *new* variable `w` (s32) = a1 and compare `w != 3`, hoping gcc puts w in s0? The target's compare register s0 holds t. If w = a1 and gcc keeps a1 in s1... no.

Alternatively, make `t` s32 instead of s16 and assign `t = a1;`? Then `t != 3` compares a1's value in t's register. But then t's later uses (indexing D_80183478[t], comparisons t==0xC etc.) would use the full a1 — semantics change. Unless we re-narrow t after the test: `t = (s16)t;`. Hmm, that could work!

Structure:
```
t = a1;                 // t (s32) = full a1
if (t == 3) goto sel_054;   // target compares t(s16) vs 3... hmm
```
Wait, the target's first test `if (t == 3)` compares the s16 t. If t = a1 (full), then a1 == 3 vs (s16)a1 == 3 differ for a1 = 0x10003. The target's semantics: idx = a0-1... a1 is the parameter. Hmm, but for the bytes to match, the comparisons must be the same.

Hmm, but the function is `func_8017F2D4(s32 a0, s32 a1)` — a1 is compared as s16 in all the cases (`(s16)a1`). So a1's high bits are ignored. If we changed t to s32=a1 and compared `t==3`, we'd get a different compare (32-bit vs the s16 value). Actually gcc's compare `t == 3` with t = a1 (s32) would emit a 32-bit compare of a1 vs 3 — different from `sra s0,v0,0x10` then compare.

No good.

OK — what if the compare uses a *re-narrowed* copy: `s16 u = (s16)a1; if (u != 3)` where u is a fresh pseudo that gcc allocates to s0? But t is already s0 and u would be a copy of t → cse equates and folds.

Hmm.

I think this is a genuine wall. But let me try ONE more structural idea that could work: put the `t != 3` test at a *join* block where t's value is the intersection of two paths (t==3 from one, t==5 from another), so flow can't know it. 

Concretely, restructure case 5 as:

```
if (t == 5) {
    if (t == 3) goto sel_054;   // never true
    goto sel_094;
}
```
No.

What about:
```
if (t == 3) goto sel_054;
if (t == 5) {
    goto sel_094;
sel_054:
    ...
```
The join at sel_054 has t==3 from both paths (the goto and the fall-through when t==3). Known 3.

Hmm what if we make the t!=3 test be the *first* thing at sel_054:
```
if (t == 3) goto sel_054;
if (t == 5) {
    goto sel_094;
sel_054:
    if (t == 3) { sel = &D_801C3C94; goto set_sel; }
    goto sel_094;
}
```
At sel_054, t==3 from both paths → `t==3` folds true → emits just the body. The target has a `bne t,3,sel_094` before sel_054. Not matching.

Hmm, but what if the target's `bne s0,v1,71c` is actually a *different* source construct — like `if (t >= 4) goto sel_094;`? Both fold.

I'm now fairly confident it's a wall. Let me also quickly consider whether the register mismatch in g1 could be a *known* pattern: "REG-callee" means a callee-saved register difference. The tag could be `global-copy-pref` or `global-pri-bank-order`? But the real cause is the compare operand.

Given the ≥20 min requirement: item 2 started around 08:08 (first candidate nolaunder at ~08:08). Now 08:20 → 12 min. I need ~8 more minutes. Let me try a handful more candidates to be thorough (each batch ~1 min).

Let me try:
- Comparing `t` to 3 with the t==5 test written as `if (t == 5)` but with an extra *use* of t in between that cse can't fold... no.

New idea: use a `switch (t)` for the t==5 test:
```
switch (t) {
case 3: goto sel_054;
case 5:
    if (t != 3) goto sel_094;
    ...
}
```
A switch with cases 3 and 5 (plus default) — gcc might emit a jump table (bad) or compares. And crucially, does cse record a jump equivalence from a switch? The switch becomes comparisons/branches; if it's a compare against 5, the equivalence is recorded. Hmm. But maybe the switch structure keeps the case label such that the test is in a separate block! A switch case body is a label — so `case 5:` starts a new block, and the t==5 knowledge... the jump to case 5 comes from the switch dispatch; the comparison is a subtract/compare chain, and cse may not record a simple reg==const equivalence across the switch's indirect jump. Worth testing!

l1: switch-based restructure.

Also:
l2: `if (t == 5) { if (t < 4) goto sel_094; }`? folds.
l3: use `!=` with a cast to s32: `if ((s32)t != 3)` folds.

Let me test the switch idea. I'll restructure case 5's t==3/t==5 part into a switch:

```
switch (t) {
case 3:
    goto sel_054;
case 5:
    if (t != 3) goto sel_094;
sel_054:
    sel = (u32)&D_801C3C94;
    goto set_sel;
sel_094:
    if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
    sel = (u32)&D_801C3CD4;
    goto set_sel;
}
```
But a switch needs a default: if t is neither 3 nor 5, it falls through to the code after the switch (the `if ((func_800291B4(D_80183478[t])...`). Let me construct carefully from the base.

The base (nolaunder.c) case 5:
```
    case 5:
        t = (s16)a1;
        if (t == 0) {
            sel = (u32)&D_801C3C70;
            goto set_sel;
        }
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_801C3C94;
            goto set_sel;
        sel_094:
            if ((func_800291B4(0x40) & 0xFF) == 0) {
                goto call_45F;
            }
            sel = (u32)&D_801C3CD4;
            goto set_sel;
        }
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) {
```
Let me look at the exact text from orig.c (nolaunder is the same minus the asm line). I have it above.

For a switch version:
```
    case 5:
        t = (s16)a1;
        if (t == 0) { sel = &D_801C3C70; goto set_sel; }
        switch (t) {
        case 3:
            goto sel_054;
        case 5:
            if (t != 3) goto sel_094;
        sel_054:
            sel = &D_801C3C94;
            goto set_sel;
        sel_094:
            if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
            sel = &D_801C3CD4;
            goto set_sel;
        }
        if ((func_800291B4(D_80183478[t]) & 0xFF) == 0) {
```
Hmm, the switch's default falls through to the code after, which matches the original (t neither 3 nor 5). Good.

But gcc will likely compile `switch (t)` with 2 cases into compares: `beq t,3,case3; bne t,5,after; ...`. The case labels are targets of branches — cse records jump equivalences at those branches too (`beq t,3` → on the fall-through t != 3; the bne t,5 → on the fall-through t == 5). So the equivalence would still be recorded. Hmm.

Unless gcc uses a jump table. With case values 3 and 5 (a range of 3), gcc might use a jump table: `sltiu; sll; lw; jr` — that's a big change.

Let me just test it. Cheap.

Also, an idea: what if the t==5 test is done on `a1` (full) and the code inside uses t? The target's branch compares t vs 5... no.

Let me test the switch and a couple more, then finalize.
