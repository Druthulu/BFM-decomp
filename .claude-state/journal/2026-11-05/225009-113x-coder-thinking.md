---
ts: 2026-11-06T05:50:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NVYTkpf1E8CuoNkcVx1B
---
Now I see:
- insn 92: reg76 = D_801922A0 (v)
- insn 103: reg76 = D_80192278 (v)
- insn 108: (set (reg/i:SI 2 v0) (reg/v:SI 76)) — the return copy! v(76) → v0.

So the return statement creates `(set (reg/i:SI 2 v0) (reg/v:SI 76))` — a hard-reg set, not a pseudo. The comment said "the two-def return pseudo" — hmm, but here it's the hard reg v0.

So v (76) is copied to v0 at insn 108. If v were allocated $2, the copy would be `move v0,v0` → deleted.

Global alloc put v (76) in $4 (a0) because it conflicts with hard regs $2/$3 (call-clobbered). Why would v conflict with $2/$3? Because v is live across... hmm, no calls. Let me look at the conflicts: "76 conflicts: 72 76 2 3 29". Hard regs 2, 3, 29 (ra). Why?

Maybe because of the `(reg/i:SI 2 v0)` at insn 108 — no.

Hmm, in global.c, an allocno conflicts with a hard reg if some instruction in its live range *sets* that hard reg (for caller-saved, if there's a call). Hard reg 2 is set by call_insn (call result). v is live from insn 92 to 108. Is there a call in that range? insn 92-108: no calls (the calls are at insns 327+ in the other branch, and the cond computation before).

Hmm, but global.c computes conflicts per allocno; maybe the conflict comes from the `(set (reg/i:SI 2 v0) (reg/v:SI 76))` at insn 108 — that SETS v0 while v is live → conflict! Yes! The instruction that copies v to v0 is in v's live range (v is an input). Since the instruction sets hard reg 2, v conflicts with hard reg 2 → can't be allocated to $2. 

That's the classic "return copy prevents coalescing" issue. Hmm, but in the pinned version, v IS $2 — because the pin overrides the conflict (a hard-reg variable can't be assigned elsewhere).

So how do we avoid this in plain C? The return copy `(set (reg 2) (reg 76))` always conflicts.

Hmm, but normally gcc handles `return x;` by making x the return value directly if possible. In 2.7.2, `(set (reg/i:SI 2 v0) (reg/v:SI 76))` is a hard-reg set — so v must conflict with v0. Unless global_alloc's "copy" handling coalesces: global.c has `qty_phys_copy_sugg` for copies. Hmm.

Wait, but the target (pinned) has v in $2 and the copy `move v0,v0` deleted. The pin makes v a hard reg $2, so `(set (reg 2) (reg 2))` → deleted.

Without the pin, we need v to be allocated $2 despite the conflict. Hmm.

Alternatively: avoid the copy entirely by making the return expression directly a constant/pointer expression so gcc assigns the value to v0 directly:
```c
if (!cond) {
    if (unk0 == 0xA2) return (s32)&D_80192278;
    return (s32)&D_801922A0;
}
```
Then each return is `(set (reg/i:SI 2 v0) (symbol_ref))` — no intermediate variable, no copy! The asm would be:
```
lhu a0,0(s0)
li v1,0xA2
bne a0,v1, L
lui v0,D_80192278...
j epilogue
L: lui v0,D_801922A0...
```
Hmm, but the target's structure is: load A0 into v0 first, then compare, then conditionally load A1 into v0. With two returns, the branch would be inverted: the target does `bne a0,v1, epilogue` (jumping to the shared epilogue with v0=A0). Two returns would give a different layout: the second return's block after the first.

Let me think about the target's actual source semantics: 
```
v0 = A0
if (unk0 != 0xA2) goto epilogue    ; v0 = A0
v0 = A1
goto epilogue
```
This is a select. Two returns:
```
if (unk0 == 0xA2) { v0 = A1; goto epi; }
v0 = A0; goto epi;
```
would compile as: bne (inverted) to the A0 block; A1 block; j epi; A0 block: ...; epi.

Hmm, the target's `bne a0,v1, 8324` jumps to the *epilogue* (8324), meaning the A0 value is already in v0 before the branch. So the source is the select form with the A0 value loaded first.

With two returns, the compiler would likely put the A0 return *after* the branch (not before). So the asm would differ.

Hmm. But maybe gcc's if-conversion/optimization produces the same? Let me just try it — cheap.

Also try:
f1: two returns.
f2: ternary `return cond ? A1 : A0;` — hmm, the comment warns about ?: canonicalisation for the *cond* computation, not this.

Wait, actually the target's `v` select: `v = A0; if (unk0 == 0xA2) v = A1; return v;`. The asm loads A0 into v0 BEFORE the compare. That's the "select" shape. A ternary `v = (unk0 == 0xA2) ? A1 : A0;` would probably compile the same way.

Let me try f1 (two returns) and f2 (ternary).

Actually, hold on: with two returns, there's no v variable at all, so no copy issue. But the layout might differ. Let me just test.

Also f3: keep v but return the expression directly:
```c
if (!cond) {
    v = (s32)&D_801922A0;
    if (((Unkstruct_800B5CB8 *)a0)->unk0 == 0xA2) {
        return (s32)&D_80192278;
    }
    return v;
}
```
Hmm, mixed.

Let me test f1 and f2.
