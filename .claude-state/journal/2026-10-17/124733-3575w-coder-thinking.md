---
ts: 2026-10-17T18:47:33.612Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
That's worse too. I'm trying another approach, keeping the variable as a signed 16-bit value but testing whether writing the constant differently changes how the compiler emits it in that instruction form.

I realize the objdump shows 0xf900 loaded via ori for the HImode constant, while the SImode negative constant prints as decimal with addiu — so the negative lines really need an SImode subtraction to get the right encoding. I keep testing variable type combinations for the b7 case, trying different ways to express the subtraction that still preserve the needed copy instruction without changing the constant's representation.

Oddly b4's -0x120 line matched using s32 t paired with s16 a0, but b1 using s32 u everywhere failed badly, with a large diff suggesting an early mismatch cascading through the rest. I want to dig into the b7 diff directly to see exactly where the -0x700 line breaks down.
