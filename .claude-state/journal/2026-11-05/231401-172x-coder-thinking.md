---
ts: 2026-11-06T06:14:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EpBdqiA49gwv2DSpkDIL
---
s6 = 1, same as s5. The pa0 copy didn't change the `lh v0,256(a0)`.

Hmm. s7 compile error (the unused v1 removal broke something? probably the `s32 v0;\n s32 v1;` line got mangled — I removed `        s16 v1;` but the inner block has `s32 v0, v1;`... wait, s5's inner block is `s32 v0, v1;` and I added `s16 v1;` at the outer block. Hmm, let me check s5's structure.

Actually, in s5 I replaced "        s32 v1;" with "        s16 v1;\n        s32 v1w;" — but the outer block's declaration is `register s32 v1 __asm__("$3");` → after pin removal it's `        s32 v1;`. So s5 has `s16 v1; s32 v1w;` in the outer block. And the inner block has `s32 v0, v1;` (a different v1).

s7 removed `        s16 v1;` leaving `s32 v1w;`. Then... compile error. Maybe the inner block uses v1 (declared there). Hmm.

Whatever. s5/s6 = 1.

The remaining mismatch: `lh v0,256(a0)` vs `lh v0,256(s0)`.

Let me look at s6's asm to see the context. Maybe the issue is the *order*: in the target, `lh v0,256(s0)` comes before `lh a1,112(a0)`. In mine, `lh v0,256(a0)`.

Hmm, what if I write the unk100 access with a *different* expression that gcc can't substitute, e.g., using a local variable `s0v` that's assigned from a0 earlier (before the call)?

Idea: hoist `s32 s0v = (s32)a0;` to the top of the function? That's the s0 variable again → extra copy.

Hmm. But wait — what if the copy is placed such that it coalesces? The earlier issue was the copy `s0 = (s32)a0` creating two cross-call allocnos. But what if we assign s0 from a0 *after* the first call (when a0 is dead)? Hmm, the pointer is needed from the start.

Hmm, let me look at why the parameter and s0 aren't coalesced. In p1's RTL: reg72 = a0 (insn 4), reg73 = reg72 (insn 11). reg72 is used only at insn 11 → it should be a simple copy that local-alloc coalesces. But it's a global allocno (crossing blocks? the copy is in the entry block).

Hmm, insn 4 and 11 are both in the entry block. Why is reg73 global? Because it's used across blocks (the pointer is used in all blocks). And reg72? It's used only at insn 11 (same block). So reg72 should be a local qty...

But the greg dump lists both 72 and 73 as global allocnos ("4 regs to allocate: 74 72 76 73"). Hmm.

Hmm, maybe reg72 is the incoming parameter which is considered live across the whole function? No...

Let me look at the .lreg dump for p1 to see if reg72 is a local qty.

Actually, let me try a completely different spelling: make the parameter the only pointer (no s0 variable) but reference it in a way that gcc keeps in s0 for the unk100 access. 

Hmm, in s5 the unk100 access uses a0. What if I add a `do { } while (0)` around the last block's statements to change the scheduling? Or reorder the statements?

Let me try reordering the last block:
```c
v1 = (s32)&D_80184CCC[0];
v0 = (((Unkstruct_800B5CB8 *)(s32)a0)->unk100 << 4) + v1;
```
vs
```c
v1 = (s32)&D_80184CCC[0];
s32 u = ((Unkstruct_800B5CB8 *)(s32)a0)->unk100;
v0 = (u << 4) + v1;
```
Hmm.

What if the unk100 load is written as a separate statement before the pa0 copy? In the target, the order is: pa0 = s0 (launder), v1 = &D_80184CCC, v0 = (unk100 << 4) + v1. So the copy comes first.

In s6, pa0 = (s32)a0 is first. Same order.

Hmm, but the asm still uses a0.

Let me look at s6's asm around there.

Actually — maybe the difference is which register the *parameter* is in. In the target, s0 = $16 (pinned). In mine, the parameter is copied to s0 ($16) at the prologue (`move s0,a0`). So both are in s0.

Then why does mine use a0 for the unk100 load? Because at that point a0 holds the pointer (set by `move a0,s0` for the func_8012AD50 call at 2954 — wait, that move is at 292c, before the unk100 load at 2938).

Hmm, in the target, the same `move a0,s0` exists at 292c. So a0 also holds the pointer at 2938 in the target. But the target uses s0.

So it's a *scheduling/register-choice* difference: gcc could use either; the target used s0.

Hmm, maybe the difference is that in the target, s0 is a hard reg (the source variable), so the unk100 access MUST use $16. In mine, the source uses the parameter, which gcc can access via a0 or s0.

To force s0, I need a source variable that maps to s0 and is distinct from the call-arg copy.

Hmm, what if I use a local variable for the pointer in the last block, assigned from a0 *before* the move:
```c
{
    s32 v0, v1;
    s32 s0v;
    s0v = (s32)a0;      // copy from the parameter (in s0)
    ...
    v0 = (((Unkstruct_800B5CB8 *)s0v)->unk100 << 4) + v1;
```
Then s0v would be a copy of the parameter. gcc might allocate s0v to a0 (copy preference) or to s0. Hmm.

Actually, in the target the launder `pa0 = s0` created the copy to a0. And the source's s0 reference uses the hard reg.

For a lever-free body, maybe the cleanest is to keep a `s0` variable but avoid the extra prologue copy. Hmm.

Let me look at WHY the s0 variable causes two allocnos. Let me check p1's lreg for reg72/73.

Actually, let me try yet another spelling: declare the pointer variable as `s32 s0 = (s32)a0;` but make the parameter unused elsewhere. It's already.

Hmm, let me look at the .greg for q3 (init at decl) — same result (67 ins).

Let me look at the p1 .lreg to see if reg72 is local or global.
