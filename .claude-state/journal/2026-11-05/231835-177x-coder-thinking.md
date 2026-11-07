---
ts: 2026-11-06T06:18:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ORt3mAlRS4nmEL2CRgqa
---
That's the wrong function (the TU has many functions; the first D_80184CCC at 12491 might be a different function). Let me find the right one — the func_8017EF9C region.

Let me get the function's rtl start line and search within.

Actually, let me take a different approach. The remaining mismatch is one instruction: `lh v0,256(a0)` vs `lh v0,256(s0)`. This is a register-allocation/scheduling detail.

Given the time, let me try a few more spellings of the last block and if none work, decide whether to record a WALL at best 1 (very close) or keep trying.

Actually — a WALL with best 1 is a shame. Let me think harder.

The load: `v0 = (((Unkstruct_800B5CB8 *)s0)->unk100 << 4) + v1;` where s0 = the pointer.

In the target, the base is $16 (s0). In mine, a0.

What if I make the base a *fresh local variable* that gcc allocates to $16? Hmm.

What if I write the access as `((Unkstruct_800B5CB8 *)(s32)a0)->unk100` but with a *do-while* that changes the block, preventing regmove? u1 (do-while on the whole statement) gave 6 (66 ins).

What if the do-while is around the *call* instead? Hmm.

What if I move the `func_8012AD50` call's argument to a variable assigned at the top? Hmm.

Let me look at the exact instruction sequence in mine vs target:
```
target: 292c move a0,s0; 2930 lui v1; 2934 addiu v1; 2938 lh v0,256(s0); 293c lh a1,112(a0)
mine:   292c move a0,s0; 2930 lui v1; 2934 addiu v1; 2938 lh v0,256(a0); 293c lh a1,112(a0)
```
So only the base of the first lh differs.

Hmm! What if I reorder the source statements so the `*(s16 *)(pa0 + 0x70)` load comes before the unk100 load? Then the asm order would change.

Hmm.

What if the unk100 access is written via a *pointer variable* `p` assigned before the block? Hmm.

Let me try: use a local `s32 s0v` assigned from a0 at the top of the last block, and use s0v for the unk100 access, with pa0 for the rest. gcc might allocate s0v to $16 (since it's a copy of the parameter in $16) and regmove might not rewrite it.

Let me test that (v1).

Also try: `u16 u = ((Unkstruct_800B5CB8 *)(s32)a0)->unk100;` (a separate variable) then use u.

Let me run both.
