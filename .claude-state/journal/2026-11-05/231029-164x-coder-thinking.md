---
ts: 2026-11-06T06:10:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IZO4wvlZ5v4HJPA2JxHQ
---
q1 is close! 64 ins vs 65. Differences:
1. The v1 pin: mine uses a0 for the loaded value (D_80184CA8 load), target uses v1 ($3). This is the `register s32 v1 __asm__("$3")` pin.
2. mine `lh v0,256(a0)` vs target `lh v0,256(s0)` at insn 50 — a register choice for the last block's pointer (a0 vs s0). In the target, the last block uses `move a0,s0` (a0=pa0) and `lh a1,112(a0)`, `sw v0,88(a0)`. In mine (q1), the last block uses a0 directly (the parameter is in a0... hmm).

Let me look at q1's full asm to understand.

Actually, the main remaining lever is the v1 pin. Let me first remove the v1 pin from q1 and see the score, then think.

q1 currently has the v1 pin (I only removed the s0 pin and the launder). Let me check: q1 derives from p1 which derives from n2 which had both pins removed. Wait, n2 removed both pins ($16 s0 and $3 v1). Then p1 removed pa0. Then q1 removed s0.

So q1 has NO pins and no launder. And it scores 11 with 64 ins.

The remaining diffs are the v1 register (a0 vs v1) and the last block's pointer.

Hmm, the v1 pin: target `lh v1,0(at)` — the loaded D_80184CA8 value in $3. Mine: `lh a0,0(at)` — in $4.

Interesting: in the target, v1 is $3 because of the pin. Lever-free, gcc picks a0 ($4) because $3 (v1) is... hmm, why? Let me look at the target's usage: v1 is used for the masks and the store. And the target's `lw v0,32(s0)` is scheduled after.

In mine: `lh a0,0(at); lw v1,32(s0); andi v0,a0,0xf000...`. So mine uses a0 for the loaded value and v1 for the unk20 pointer. Target: v1 for the loaded value, v0 for the unk20 pointer.

So the target's allocation: the D_80184CA8 load → $3 (v1), the unk20 load → $2 (v0), the masks → v0.

Mine: the D_80184CA8 load → $4 (a0), the unk20 load → $3 (v1), the masks → v0.

Hmm. The `v0` variable is a local (the masks). The pin forced the D_80184CA8 value into $3.

Without the pin, local-alloc assigns: v0 (the mask results) gets $2, then the loads compete for $3/$4.

To get the D_80184CA8 value into $3, we need it to have higher priority than the unk20 value. Hmm.

Wait — but note the target's `lw v0,32(s0)` is at insn 25 (after the masks), i.e., the unk20 load is *scheduled* later but its register is v0. Hmm.

Let me think about the source:
```c
v1 = D_80184CA8[((Unkstruct_800B5CB8 *)s0)->unk70];
((Unkstruct_800B5CB8 *)s0)->unkFE = (v1 & 0xF000) >> 12;
((Unkstruct_800B5CB8 *)s0)->unk100 = v1 & 0xF;
v0 = ((Unkstruct_800B5CB8 *)s0)->unk20;
((Unkstruct_800B5CB8 *)v0)->unk12 = v1 & 0xFF0;
v1 = ((Unkstruct_800B5CB8 *)s0)->unk100;
if (v1 == 2) { ... }
```
In the target, the loads: `lh v1,0(at)` (v1), `lw v0,32(s0)` (v0). The store `sh v1,18(v0)` uses v1 (the mask) and v0 (the pointer).

Without the pin, mine: `lh a0,0(at)` (a0), `lw v1,32(s0)` (v1), `andi v0,a0,0xff0; sh v0,18(v1)`.

Hmm, mine's mask result is in v0 and the store base is v1. Target's mask result is in v1 and the base is v0.

So it's a two-register swap (v0/v1) plus a0.

Since q1 is only 1 insn short and 11 score, maybe I can fix it.

Hmm, let me think: in q1, the D_80184CA8 load got a0 ($4). That's odd — a0 is the parameter register. In q1 I replaced `s0` with `(s32)a0`, so a0 is the parameter and also the pointer used across calls. But a0 is caller-saved; gcc must copy it to a callee-saved reg for the calls. In q1's asm, the pointer is in s0 ($16) (from the pairs: a0->s0 x1). So the parameter a0 is copied to s0.

But the D_80184CA8 load into a0 — a0 is dead after the prologue copy? So a0 is free for a local. OK.

So mine: D_80184CA8 value in a0, unk20 in v1, masks in v0.
Target: D_80184CA8 value in v1, unk20 in v0, masks in v1/v0.

Hmm, target: `lh v1,0(at)` (the D_80184CA8 value in v1), `andi v0,v1,0xf000` (mask in v0), `andi v1,v1,0xff0` (mask in v1!), `lw v0,32(s0)` (unk20 in v0), `sh v1,18(v0)`.

So the target uses v1 for the loaded value and one mask, v0 for the other masks and the pointer.

Mine: a0 for the loaded value, v0 for the masks, v1 for the pointer.

To match, the loaded value should be in v1. Hmm.

Local-alloc densities: the D_80184CA8 value (v1 in source) is used 5 times; the unk20 value (v0) 2 times. So v1's density is higher → should get $2! But the target has it in $3.

Hmm, that suggests the masks (which are separate pseudos) take $2.

Let me not over-analyze. Let me try a few variants:
- Restructure the first block so the register assignment matches.

Actually, let me first check: what does q1 look like in the last block? The diff showed `lh v0,256(a0)` vs target `lh v0,256(s0)`. In the target, the last block uses pa0 (= a0 in the target's allocation) — hmm, the target has `move a0,s0` at 292c then `lh v0,256(s0)` at 2938 — wait, the target's 2938 is `lh v0,256(s0)`, not a0. And 293c is `lh a1,112(a0)`.

So the target's last block: `lh v0,256(s0)` (the unk100 field, via s0) and `lh a1,112(a0)` (via pa0=a0). Interesting.

In q1, both use a0? `lh v0,256(a0)` — because I replaced s0 with (s32)a0, so the code uses a0 directly (the parameter), which gcc copied to s0. Hmm, the use `((Unkstruct_800B5CB8 *)(s32)a0)->unk100` should use the s0 register... but mine shows `lh v0,256(a0)`. So gcc kept the parameter in a0 for that use (a0 still holds it if not clobbered? but there are calls...). Hmm, at insn 50 (near the end), a0 might hold s0 again via a `move a0,s0`.

OK. This is getting complicated. q1 = 11. Let me try a few variants to fix the v1 allocation.

Idea: make the D_80184CA8 value a *separate variable* with a name, and the unk20 value another. They already are (v1 and v0).

Idea: reorder the statements so the unk20 load comes before the masks? The target has it after.

Idea: declare v0 as `s32 v0` and v1 as `s32 v1` — already.

Hmm, what if the v1 variable is declared as a *pointer*? No.

Let me look at the target's RTL for the first block to understand the pseudo structure. Let me dump the orig's cse2 for the block.

Actually, let me try some quick variants:
r1: reorder: `v0 = unk20;` before the masks.
r2: use a temp for the unk20 pointer.
r3: split the `v1 & 0xF000) >> 12` into a temp.

Hmm.

Actually, let me reconsider: maybe the cleanest is to keep a *named* variable for the pointer and use it (not `(s32)a0` everywhere), but fix the extra copy. The extra copy came from `s32 s0; s0 = (s32)a0;`. What if we write `s32 s0 = (s32)a0;` (init at decl)? That might coalesce better! Init at decl is a C0505 move. Let me test.

Let me try:
- q3: `s32 s0 = (s32)a0;` (init at decl) with the rest of p1.
- q4: `void *s0 = a0;` (init at decl, pointer).

Let me test q3.
