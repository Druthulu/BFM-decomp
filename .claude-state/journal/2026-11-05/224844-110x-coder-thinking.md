---
ts: 2026-11-06T05:48:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kZeElZ2FCuJOpNujgjzU
---
The remaining diff (9): 
- Target: v1 = 0xA2 constant, v0 = pointer (lui v0/addiu v0), a0 = lhu load.
- Mine: v0 = 0xA2, a0 = pointer, v1 = lhu.
- Plus two `move v0,a0` in the delay slots (mine) vs nop (target).

The comment explains: "the two-def return pseudo of the early-out below falls to global_alloc and lands in $a0 (costing a `move $v0,$a0` in each of the two delay slots the target leaves as `nop`). The pin restores the target's $v0 = pointer / $v1 = 0xA2 / $a0 = halfword assignment at zero byte cost."

So the `v` variable (the return value) is the issue: `v = (s32)&D_801922A0; if (unk0 == 0xA2) v = (s32)&D_80192278; return v;`

With the pin ($2), v is in v0. Without, global_alloc puts v in a0 (because v has 2 defs → global allocno? and it's the return value...). Then the return copies a0→v0 (`move v0,a0`) in the two delay slots.

So we need v in v0 naturally. v is the return value: `return v;`. The function returns s32. The RESULT_DECL prefers v0.

Hmm, the comment says the "two-def return pseudo of the early-out falls to global_alloc and lands in $a0". So v is a global allocno (live across blocks? it's defined in two blocks and returned). global_alloc assigns $16+ for cross-block... but here it lands in a0 ($4).

Hmm. The pin forced $2.

Lever-free: can we make v stay in v0? The return value normally goes to v0 via a copy at the return. The target has `move v0,a0`? No — target has nop in the delay slots and returns v in v0 directly.

Hmm, wait: if v is in v0 in the target, then `return v` is free. Without the pin, v is in a0 and the return needs `move v0,a0`.

Why does v land in a0? Maybe because the RESULT_DECL is not the variable v; the function returns `v` (a variable) → the return statement copies v to the result. Hmm.

The comment says "the two-def return pseudo of the early-out falls to global_alloc and lands in $a0". So there's a "return pseudo" with two defs. Since the function has an early return and a final return, the return value pseudo has multiple defs.

How to make it v0 naturally? Options:
1. Make v's qty local (not global) — e.g., restructure so the early return is a single variable.
2. Make v a *different* variable per path? 

Let me look at the structure:
```c
if (!cond) {
    v = (s32)&D_801922A0;
    if (unk0 == 0xA2) v = (s32)&D_80192278;
    return v;
}
result = (s32)&D_80191F00;
switch (...) { ... }
return result;
```
The function has two returns: `return v;` and `return result;`.

The "return pseudo" — in gcc, the function's return value is a single pseudo (the DECL_RESULT). Each return assigns to it. So there are 2 defs: one from v, one from result.

The target: the early return's value in v0. Hmm.

Wait, the target's early-out:
```
26 li v1,162         (0xA2)
27 lui v0,0x0        (D_801922A0)
28 addiu v0,v0,0
29 lhu a0,0(s0)      (unk0)
31 bne a0,v1, ...
32 nop
33 lui v0,0x0        (D_80192278)
34 addiu v0,v0,0
36 nop
```
So the pointer goes into v0 and the comparison `bne a0,v1` (a0 = unk0, v1 = 0xA2). Then the return: the function's return value is in v0.

Hmm, so in the target, the value `&D_801922A0` is loaded into v0 directly and the second store into v0. So v IS in v0.

Mine: v0 = 0xA2, a0 = pointer, v1 = unk0. So the allocation is rotated: v (pointer) → a0, 0xA2 → v0, unk0 → v1.

So without the pin, the pointer v goes to a0. Why? Because the return pseudo prefers v0 but the 0xA2 constant and the load take v0/v1 first?

Hmm. Let me look at the RTL/alloc. The comment says it "falls to global_alloc" — meaning v is a global allocno (live across basic blocks) and global_alloc assigns it $4 (a0) because $2/$3 are taken or because of priority.

Hmm, actually global_alloc assigns callee-saved regs to allocnos that cross calls. v doesn't cross calls. Let me think: in gcc 2.7.2, global_alloc assigns ALL allocnos that are live across basic block boundaries; local-alloc handles those within a block. v is defined in the early-out block and used at the return — across blocks → global allocno.

global_alloc assigns from the register classes with priorities; it can assign caller-saved regs too ($2-$15) if the allocno doesn't cross calls. The RESULT_DECL... hmm.

So v gets $4 (a0) in global_alloc. To make it $2, we could:
- Make v not a global allocno (restructure so it's local to a block).
- Raise its priority above the other global allocnos.
- Use a different structure that avoids the variable.

Idea: instead of `v = ptr; if (...) v = ptr2; return v;` — maybe write the two returns directly:
```c
if (!cond) {
    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2) {
        return (s32)&D_80192278;
    }
    return (s32)&D_801922A0;
}
```
That changes the branch structure (the target has one branch and a select).

Hmm, the target's shape: load ptr1 into v0, compare unk0 to 0xA2, if equal load ptr2 into v0, then return. So it's a select (v = cond ? ptr2 : ptr1).

What if we write it as `return cond ? (s32)&D_80192278 : (s32)&D_801922A0;`? The comment warns about `?:` canonicalisation (the target's cross-jumped shape needs [zero][load]). Hmm, but that's about a different if/else (the cond computation).

Let me think about what makes v a global allocno. If we could make the early-out a *local* computation (all within one basic block), local-alloc would handle it. The early-out has a branch inside it (`if (unk0 == 0xA2)`), so v spans blocks.

Alternative: make the return value pseudo local by having the return in each branch:
```c
if (!cond) {
    v = (s32)&D_801922A0;
    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2) {
        v = (s32)&D_80192278;
    }
    return v;
}
```
Same as now.

Hmm, what if the *function's* return is structured so that the DECL_RESULT is assigned in each block and the register allocator keeps it in v0? The RESULT_DECL is special: `current_function_return_rtx` is a pseudo that global-alloc gives... hmm.

Actually, in gcc 2.7.2, the return value pseudo (function_value) is a hard reg ($2) usually. Hmm, but the comment says a "return pseudo" falls to global_alloc.

Let me look at the RTL to understand. Let me dump e1.

Actually, let me look at the diff more carefully: mine has `move v0,a0` at 32 and 36 — the delay slots. So the return path copies a0→v0. That means the function's return value is in v0 (hard) and v is in a0.

Let me try to make v get v0 by:
1. Declaring v as `register s32 v;`? The `register` keyword is banned ("no register vars").
2. Restructuring.

Hmm, what about making v a *pointer-typed* variable? `void *v; v = &D_801922A0; ... return (s32)v;` — pointer allocnos might have different priorities.

Or the reverse: what if `result` is the issue? The final `return result;` — result is also a return pseudo. In the target, result is in s1 (`move v0,s1` at 81ec? hmm).

Let me look at the RTL. Let me dump e1's TU and look at the .lreg/.greg for the return.

Actually, let me first try the obvious: make the early-out return value *not* a variable. E.g.:

```c
if (!cond) {
    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2) {
        return (s32)&D_80192278;
    }
    return (s32)&D_801922A0;
}
```
This changes the code shape: two returns instead of a select. The asm would be:
```
lhu a0,0(s0)
li v1,0xA2
bne a0,v1,L1
lui v0,D_80192278...
jr ra
L1: lui v0,D_801922A0...
jr ra
```
The target has a single return path with a conditional load. Hmm, not matching.

Let me look at the target's early-out asm fully to understand.

From the diff: target insns 26-36:
```
26 li v1,162
27 lui v0,0x0
28 addiu v0,v0,0
29 lhu a0,0(s0)
30 ? (nop?)
31 bne a0,v1, 8324
32 nop
33 lui v0,0x0
34 addiu v0,v0,0
35 ? 
36 nop
```
Hmm, insn 31 is `bne a0,v1, 8324` — jumping to 0x8324 which is... the case 3 arm? Hmm, weird. Let me dump the target's early part.

Let me get the target asm insns 20-40.
