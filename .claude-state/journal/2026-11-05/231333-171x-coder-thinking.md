---
ts: 2026-11-06T06:13:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dgwga3p8kLXS4VVSenG1
---
s5 = score 1! Only ONE mismatch: `lh v0,256(a0)` vs target `lh v0,256(s0)`.

Hmm, but s5's `s16 v1` is now unused (I replaced the uses with v1w). Let me clean that up later.

The remaining issue: in the last block, the source `v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;` uses the parameter a0, and gcc emits `lh v0,256(a0)`. The target uses s0.

In the target, the source's last block uses `s0` (the variable) for the unk100 field, and pa0 (a0) for the other accesses.

Since I eliminated the s0 variable (replacing it with `(s32)a0`), all accesses use a0. gcc chose a0 for the unk100 load (since a0 == s0 at that point).

To make gcc use s0, I need the source to reference the s0 variable there.

Hmm — but reintroducing s0 caused the extra copy. 

Wait, maybe I can keep the `(s32)a0` replacement everywhere EXCEPT the last block, where I introduce a local `s32 s0 = (s32)a0;`? That would create a copy... hmm.

Alternatively: the target's last block has `move a0,s0` before the `lh a1,112(a0)` — that's the pa0 copy. So in the target, the last block uses BOTH s0 and pa0.

In my body, pa0 doesn't exist. The target's `lh a1,112(a0)` (pa0+0x70) and `sw v0,88(a0)` (pa0+0x58) — in my body these are `(s32)a0 + 0x70` and `(s32)a0 + 0x58` → gcc uses a0 (after move a0,s0). And `((Unkstruct_800B5CB8 *)(s32)a0)->unk100` → gcc used a0, but the target uses s0.

So the target's source distinguishes: the `unk100` access uses the s0 variable, the pointer arithmetic uses pa0.

Hmm! So in the target's source, the last block is:
```c
{
    s32 v0, v1;
    s32 pa0;
    pa0 = s0;                      // the launder (copy)
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;   // s0
    v0 |= 0x40000000;
    *(s32 *)(pa0 + 0x58) = v0;
    *(s32 *)(pa0 + 0x1C) = *(s16 *)(pa0 + 0x70);
    func_8012AD50((void *)pa0);
}
```
So `unk100` uses s0, and the others use pa0.

In my body, I replaced s0 with (s32)a0 everywhere. To match, I should keep s0 for the unk100 access and use a0/pa0 for the rest.

But if I keep the s0 variable, the extra copy appears (the s0 = a0 copy at the top).

Hmm. Unless... the extra copy came from the *whole-function* s0 variable being live across all the calls. If s0 is only used in the last block (after the last call), it wouldn't need a callee-saved reg!

Idea: don't declare s0 at the top; instead, in the last block, declare `s32 s0 = (s32)a0;` (a local copy just for that block). Since a0 already holds the pointer (after `move a0,s0`... hmm, but in my body there's no s0; the pointer lives in the parameter a0, which gcc copies to a callee-saved reg at the prologue).

Hmm, wait: in my body (q1/s5), the parameter a0 is used across calls. gcc copies it to s0 at the prologue (`move s0,a0`) and uses s0 for the calls (`move a0,s0`). So the pointer IS in s0.

So in the last block, a0 and s0 both hold the pointer. The `lh v0,256(a0)` uses a0; the target uses s0.

If I write the last block's unk100 access with a *separate local variable* assigned from a0 at the top of the block, gcc might use s0 (the callee-saved copy) or a0.

Hmm, what if I write the last block as:
```c
{
    s32 v0, v1;
    s32 pa0;
    pa0 = (s32)a0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)pa0)->unk100 << 4) + v1;
    ...
}
```
Hmm, then everything uses pa0.

The target uses s0 for unk100 and pa0 for the rest. So the source's unk100 line references the original variable (s0) and the rest reference pa0.

In my body, the "original variable" is the parameter a0 (gcc's s0 copy). If I keep a named variable `s0` for the whole function, gcc makes the extra copy (the s0 = a0 issue).

Hmm, why does gcc make the extra copy? Let me investigate: maybe it's because the source's s0 is `s32` and the parameter is `void *`. gcc might keep the parameter in one reg and s0 in another.

What if I declare the parameter as `s32 a0` — no, signature change.

What if the body does `s32 s0 = (s32)a0;` but I use a *union* or something to make them the same mode? They're both SImode.

Hmm, let me look at why global_alloc doesn't coalesce. In p1's RTL: insn 4 (reg72 = a0), insn 11 (reg73 = reg72). Two allocnos, both crossing calls? reg72's conflict list includes 2,3,4,29 — so reg72 IS considered live across calls. Why? It's live from insn 4 to 11; the first call is at insn 14. So it shouldn't.

Unless... the RTL's insn ordering differs: maybe the call at insn 14 comes before the copy in some pass. Hmm.

Wait, maybe global.c's conflicts include the hard regs that the allocno's *conflicting* insns set. Hmm.

Actually, let me look at the p1 greg dump again:
```
;; 72 conflicts: 72 73 74 76 2 3 4 29
```
Conflicts with hard regs 2,3,4,29 (v0,v1,a0,ra). These are the call-clobbered regs + ra. So reg72 is live across a call. Hmm.

Unless global.c marks all allocnos that *cross* a basic block as conflicting with call-clobbered regs (conservatively). reg72 crosses from the entry block to... it's used in the same block. Hmm.

Whatever. Let me try a different approach for the last block: use a *different expression* for unk100 that gcc evaluates with s0.

Actually — what if I keep `s0` as a variable but only assign it where needed? Hmm.

Let me try: in the last block, write `v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;` — currently uses a0. What if I write it as `v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;` where s0 is... I don't have s0.

Hmm, what if I reintroduce a local `s32 s0 = (s32)a0;` INSIDE the last block? Then gcc would have a copy from a0 to s0 in that block; since a0 == the pointer (in the callee-saved reg), gcc might coalesce them and use s0... but it would emit a `move` (1 instruction). We're at 65 = target, so an extra move would make 66.

Hmm, but maybe the move coalesces away.

Let me try it:
```c
{
    s32 v0, v1;
    s32 pa0;
    s32 s0 = (s32)a0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;
    ...
    *(s32 *)(pa0 + 0x58) = v0;
```
Hmm, but pa0 is undefined (I removed it). Let me construct carefully from s5.

Actually, let me look at s5's last block source:
```c
    {
        s32 v0, v1;
        v1 = (s32)&D_80184CCC[0];
        v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;
        v0 |= 0x40000000;
        *(s32 *)((s32)a0 + 0x58) = v0;
        *(s32 *)((s32)a0 + 0x1C) = *(s16 *)((s32)a0 + 0x70);
        func_8012AD50((void *)(s32)a0);
    }
```
Target's last block:
```c
{
    s32 v0, v1;
    s32 pa0;
    pa0 = s0;                     // launder
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;
    v0 |= 0x40000000;
    *(s32 *)(pa0 + 0x58) = v0;
    *(s32 *)(pa0 + 0x1C) = *(s16 *)(pa0 + 0x70);
    func_8012AD50((void *)pa0);
}
```
So the target has pa0 = s0 (a copy). In the asm: `move a0,s0` at 292c (the copy), then `lh v0,256(s0)` (the unk100 access), `lh a1,112(a0)`, `sw v0,88(a0)`.

In my s5, there's no pa0; gcc uses a0 for everything after `move a0,s0` (at 292c — wait, does s5 have that move?).

Let me check s5's asm around 292c: from the earlier s1 dump, `292c: move a0,s0` exists (the call arg setup for func_8012AD50). Then `2938: lh v0,256(a0)` — uses a0. The target uses s0.

So in my body, the unk100 access compiles to `lh v0,256(a0)` because gcc sees the parameter a0 and picks it (a0 == s0 at that point).

To force s0, I could write the unk100 access using a variable that's NOT a0 — but I don't have one.

Idea: introduce a local `s32 s0v = (s32)a0;` at the top of the last block and use it for the unk100 access. gcc would allocate s0v... to the callee-saved reg holding a0? Hmm.

Alternatively, maybe I can restructure so the unk100 access happens BEFORE `move a0,s0` (i.e., earlier in the block), when a0 still holds... hmm, a0 holds the pointer at the block start? Let me check: at 2928 (after the func_8012B14C call), `move a0,s0` at 292c. Before that, a0 was clobbered by the call.

In the target, the order is: `move a0,s0` (292c), then `lh v0,256(s0)`, `lh a1,112(a0)`, ... So s0 is used for unk100.

Hmm.

What if I reorder the source statements so the unk100 access comes first (before the pointer arithmetic)? The target's order: `lh v0,256(s0)` (2938) then `lh a1,112(a0)` (293c). In the source, `v0 = (unk100 << 4) + v1;` comes before `*(s32 *)(pa0 + 0x58) = v0;` and `*(s32 *)(pa0+0x1C) = *(s16*)(pa0+0x70);`.

In my body, the unk100 access is via `(s32)a0`; gcc chose a0.

Hmm. What if I make the unk100 access go through a *different* expression that gcc evaluates with the callee-saved copy? E.g., `((Unkstruct_800B5CB8 *)(s32)a0)->unk100` — same.

OK, let me try introducing a local pointer variable in the last block:
```c
{
    s32 v0, v1;
    s32 s0v = (s32)a0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)s0v)->unk100 << 4) + v1;
    ...
```
Hmm, s0v is a copy of a0; gcc may coalesce.

Alternatively, use the `pa0` structure like the target:
```c
{
    s32 v0, v1;
    s32 pa0 = (s32)a0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;
    v0 |= 0x40000000;
    *(s32 *)(pa0 + 0x58) = v0;
    *(s32 *)(pa0 + 0x1C) = *(s16 *)(pa0 + 0x70);
    func_8012AD50((void *)pa0);
}
```
Here the unk100 uses `(s32)a0` and the rest use pa0. If gcc allocates pa0 to a0 (coalescing the copy), then the unk100 access would use... a0 (same as now) or s0?

Hmm.

Let me just try it empirically. Let me construct s6 from s5 with pa0.

Also, maybe the register choice depends on the *order*: if pa0's copy forces a0 to be the pointer, then `(s32)a0` uses a0. In the target, the unk100 access used s0 because the source referenced the s0 variable directly.

So I need a variable that gcc maps to s0 (the callee-saved copy). Hmm — the parameter a0 is in s0 (copied at the prologue). The `(s32)a0` expression uses the *parameter pseudo*, which is in s0! But gcc emitted `lh v0,256(a0)` — meaning it re-materialized a0? No: at 292c `move a0,s0` sets a0 = s0 for the call; then `lh v0,256(a0)` reads a0 (which holds the same value). So gcc used the call-arg copy in a0.

Interesting: the `move a0,s0` at 292c is for the *func_8012B14C* call? No wait: 2924 jal func_8012B14C, then 2928 sw v0,24(sp), 292c move a0,s0 — that's the arg setup for the func_8012AD50 call at 2954. So a0 = s0 is set early (at 292c) and stays until 2954.

So at 2938, a0 == s0 == the pointer. gcc picked a0 for the unk100 load.

In the target, the source referenced `s0` (the variable), so gcc used s0.

Hmm, so I need the source's unk100 access to reference a variable that gcc keeps in s0, not the parameter a0.

But in my body, the parameter a0 IS the pointer (gcc's s0 copy). The `(s32)a0` expression refers to the parameter pseudo → which is in s0 → so it should emit `lh v0,256(s0)`! But it emitted a0.

Hmm, maybe gcc's copy propagation replaced the parameter pseudo with the a0 hard reg at that point (since a0 holds the same value after the move). cse/combine could do that.

Hmm. In the target, s0 is a hard reg ($16), and pa0 is a different value; the source's s0 reference can't be replaced by a0 (different hard regs).

OK. So to match, I need a source variable that maps to a *different* register than the a0 used for the call args.

Idea: introduce a copy `pa0 = (s32)a0;` in the last block. Then pa0 is a distinct pseudo. gcc allocates pa0 to a0 (the call arg) via the copy. And the unk100 access via `(s32)a0`... hmm, that's still the parameter.

Hmm, what if the unk100 access uses a *different* variable that maps to s0?

Let me think about the target's RTL: s0 is the hard reg $16 (pinned), pa0 is a local pseudo in $4. The source's `((Unkstruct_800B5CB8 *)s0)->unk100` uses the hard reg $16; the `pa0 + 0x58` uses $4.

In my lever-free body, the "s0" equivalent is the parameter a0 (gcc's callee-saved copy in s0). And pa0 would be a local copy.

So the source:
```c
{
    s32 v0, v1;
    s32 pa0;
    pa0 = (s32)a0;
    v1 = (s32)&D_80184CCC[0];
    v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;
    v0 |= 0x40000000;
    *(s32 *)(pa0 + 0x58) = v0;
    *(s32 *)(pa0 + 0x1C) = *(s16 *)(pa0 + 0x70);
    func_8012AD50((void *)pa0);
}
```
Here the unk100 uses the parameter a0 (in s0), and pa0 is a copy allocated to a0. Then gcc would emit `lh v0,256(s0)` for unk100 (since a0-the-parameter is in s0) and `move a0,s0` for the copy, then the rest via a0. That's exactly the target!

Wait — but in s5 (without pa0), gcc emitted `move a0,s0` at 292c for the call arg and then used a0 for unk100. Hmm, why would a0 be used for unk100 if the parameter is in s0?

Because gcc's register allocator: the parameter pseudo is in s0 (callee-saved). But at the point of the unk100 load, gcc might have used the a0 copy (the call arg setup) because a0 was already set to s0 and the load could use either.

Hmm, but that's combine/cse substituting. Hmm.

Let me just try it empirically. Let me create s6 with pa0.

Also, let me clean up the unused `s16 v1` in s5 (it's unused now). Actually, keeping it might affect allocation... let me test both.

Let me create s6 = s5 + pa0 structure.
