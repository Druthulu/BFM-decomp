---
ts: 2026-11-06T05:49:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kaixSLxcyRTQKbYQBfOf
---
Target early-out:
```
8178 li v1,162
817c lui v0,0x0     D_801922A0
8180 addiu v0,v0,0
8184 lhu a0,0(s0)
8188 nop
818c bne a0,v1, 8324   ← if (unk0 != 0xA2) goto return-path-2 (8324 is the epilogue?)
8190 nop
8194 lui v0,0x0     D_80192278
8198 addiu v0,v0,0
819c j 8324
81a0 nop
```
Interesting: `bne a0,v1, 8324` — if unk0 != 0xA2, jump to 8324 (the function epilogue, returning v0 = D_801922A0). Otherwise fall through, load D_80192278 into v0, then j 8324.

So the target has v0 = the selected pointer, and the epilogue at 8324 returns.

And mine (without the pin) has the pointer in a0 and the constant 0xA2 in v0, with `move v0,a0` in the delay slots — meaning the epilogue at 8324 does `move v0,a0; ... jr ra`? Hmm.

Wait, the diff said mine has `move v0,a0` at insn 32 and 36 (in the delay slots of bne and j). So mine's return copies a0→v0.

So the fix: make v land in v0.

Why does v land in a0? Let me look at the RTL. Let me dump e1's TU.

The variable v is a global allocno (crosses blocks). global_alloc assigns it. In the target (with the pin), v is $2. Without, v gets $4 (a0).

Hmm, but wait: the target's v is in v0 AND the return is free. In mine, v is in a0 and the return copies to v0 (the hard return register).

Hmm, that's odd: normally the return value pseudo IS v0 (the DECL_RESULT is assigned to the hard reg at the return). Let me look at the RTL.

Let me dump e1 and look at the greg (global alloc) dump for the v pseudo.

Actually, maybe a simpler approach: the pin is `register s32 v __asm__("$2")`. The comment says it restores the target's allocation. Without it, v → a0.

To make v → v0 naturally, maybe restructure the source so that v is *local* to a basic block, or make the return value directly the expression.

Idea: eliminate the v variable:
```c
if (!cond) {
    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2) {
        return (s32)&D_80192278;
    }
    return (s32)&D_801922A0;
}
```
Two returns. The asm would be:
```
li v1,162
lui v0,D_801922A0
addiu v0,v0,0
lhu a0,0(s0)
bne a0,v1, L2
lui v0,D_80192278
addiu v0,v0,0
L2: jr ra (epilogue)
```
Hmm, that's actually very close to the target! The target has:
```
lui v0,A0; addiu v0,v0,0
lhu a0,0(s0)
bne a0,v1, 8324   (epilogue)
lui v0,A1; addiu v0,v0,0
j 8324
nop
```
Wait, the target's bne jumps to the epilogue (8324), and the fall-through loads the second pointer and jumps to the epilogue. So both paths end at the same epilogue, with v0 holding the result. That's exactly what two returns would produce! The second return (`return &D_801922A0`) would be at the epilogue... hmm.

Actually, the target's shape suggests the source is:
```c
if (!cond) {
    v = &D_801922A0;
    if (unk0 == 0xA2) v = &D_80192278;
    return v;
}
```
which compiles to: load A0 into v0; bne; load A1 into v0; j epilogue.

The two-return version would compile to: load A0 into v0; bne → L; (fall) load A1 into v0; j epilogue; L: jr ra... Similar but the bne's target differs (L vs epilogue).

The target's bne targets 8324 which is the shared epilogue (`lw ra; ...; jr ra`). And the fall-through does `j 8324`. So both paths share the epilogue. That's the select shape (one return).

OK so keep the select. The question is making v → v0.

Let me look at the RTL. Let me dump e1 and examine the .greg dump for the return.

Actually, let me first try some quick structural variants:
f1: `return (s32)(((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2 ? &D_80192278 : &D_801922A0);` — a ternary.
f2: two returns.
f3: `v = (s32)&D_801922A0; if (...) { return (s32)&D_80192278; } return v;` — mixed.
f4: declare v as `s32 *v;` (pointer) and `return (s32)v;`.
f5: use `result` for the early return too? no.

Let me test f2 and f4 quickly. Also f6: make v `u32`.

Actually, let me think about global_alloc's priority. The comment says the "two-def return pseudo" falls to global_alloc. Hmm, "two-def return pseudo" — maybe it's not v but the function's return pseudo. Let me look at the RTL to be sure.

Let me dump e1.
