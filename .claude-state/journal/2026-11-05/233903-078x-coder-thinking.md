---
ts: 2026-11-06T06:39:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WGdljCkBR7IW3jULChFI
---
Best: v_s16t at 12 (42 insns = target count). Interesting: making t an s16 gives the right count.

Let me look at v_s16t's residual — if it's the same v0/v1 swap or something else.

The core issue remains: t must be $2 but conflicts with the load dest.

Hmm, wait. Let me reconsider: maybe the fix is to make the *table load dest* not $2 but still the call target... impossible.

Actually, wait! Let me re-examine. In the target:
```
lhu $2,2($5)     ; t
#APP #NO_APP
sll $2,$2,2
lw $2,D_801D0A3C($2)
jal $31,$2
```
The `lw $2,D_801D0A3C($2)` — the base and dest are both $2.

If t were a pseudo in $3 (v1), the code would be `lhu $3,2($5); sll $3,$3,2; lw $2,D_801D0A3C($3)` — hmm, that's what mine does? Let me check mine's tail from the earlier diff (lines 29-32). Let me print the tail of my current diff for v_s16t.

Actually from the very first diff:
```
29  lhu	v1,2(a1)    | lhu v0,2(a1)
replace mine[31:32] target[31:32]
```
So mine: `lhu v1,2(a1)` (t in v1), target `lhu v0,2(a1)`. And the rest presumably `sll v1; lw v0,D_801D0A3C(v1)`.

So it's just the register choice for t.

Given the conflict analysis: t conflicts with v0 because the load dest is v0 and t is the base. If t were $3, no conflict.

Hmm, so how could the target's compiler ever put t in $2 without the pin? It couldn't — that's why the pin exists.

BUT: the pin is `$2`. Is there a plain-C way to make t's priority so high that... no, a conflict is a conflict: t can't take $2 at all.

Unless the conflict doesn't exist in a different RTL shape. E.g., if the index were computed into a *different* pseudo at the load: `lw v0, D_801D0A3C(sll)` hmm.

What if the table load's destination is a separate pseudo that takes $2, and t's value is dead before? Then t (in $3) and the dest ($2). But the target has the base = $2 too.

The ONLY way: t in $2 with the load dest also $2 — the same register. Plain C's allocator forbids that (two live pseudos at the same insn need different regs).

Unless... the load is spelled so the base and dest are the same pseudo! E.g., `t = D_801D0A3C[t];` — i.e., assign the loaded function pointer back to t! Then the RTL is `(set (reg t) (mem (plus (reg t) ...)))` — one pseudo, base and dest the same → no conflict!

And then the call: `((void (*)(void *))t)(a0);` — the target's `jal $31,$2`.

Would that produce the same code? Target: `lw $2,D_801D0A3C($2)` — yes, exactly a single pseudo load into itself!

But wait, in the target the C source is `D_801D0A3C[t](a0)` where t is the index. The compiler loads into a new pseudo. But if I write `t = D_801D0A3C[t]; ((void(*)(void*))t)(a0);` the RTL is a self-load.

Hmm, but t is s32 and the table is `void (*[])(void*)`. A cast is needed: `t = (s32)D_801D0A3C[t];` then call via a cast.

Let me try that! It's a real C restructuring (no lever).

Actually careful: `D_801D0A3C[t]` is used as the call target directly. Writing `t = (s32)D_801D0A3C[t]; ((void (*)(void *))t)(a0);` — the function pointer through an s32 → cast back. This might produce an extra insn or not.

Let me test. Also, does gcc keep the self-load? `t = D_801D0A3C[t]` — t is both base and dest. In RTL: (set (reg t) (mem (plus (reg t) (symbol)))). gcc allows this (no conflict since it's the same reg). The register allocator would see one pseudo. 

Let me try it.

Also the earlier part: t = unkA etc. If t is now also the loaded pointer, its live range extends? t dies at the call.

Let me write v_self.c and test.

Also alternative: `((void (*)(void *))D_801D0A3C[t])(a0);` — the load dest is a temp.

Let me test the self-assign version.
