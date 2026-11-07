---
ts: 2026-11-07T00:52:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B71e4k2HAeAvfV9VRHVN
---
All 6 — the same as before (the `move a0,s0` vs `addiu a0,s0,24`). So all spellings fold to the same.

I need something that prevents the constant folding of `mb + 0x18` across the call.

Key: the base is a *constant*. cse knows it. To keep the base in s0 and add at each site, the compiler must not know the sum... 

Wait, actually: in the target, s0 holds the BASE. The sum is computed per call. That happens naturally if the two call arguments are NOT the same expression... but they are.

Hmm, hold on. What if the target's `s0 = &D_800AF630` is not from the two calls but from something else, and the calls' `addiu a0,s0,24` are each computed from a *different* base expression? Both use s0.

Alternatively, maybe the target's compiler kept the base because `mb` was used elsewhere (e.g., `func_8004914C(mb + 0x18)` and later `mb` is reused for another purpose) — but in the target, s0 dies after the second call (c6d8 reuses s0 for sp+104).

Let me think about gcc 2.7.2's behavior: for `func_8004914C(mb + 0x18)` with mb a known constant, cse replaces `mb + 0x18` with the constant `(plus (symbol_ref) 24)`. Then the argument materialization is `lui/addiu` of that constant address. Two uses of the same constant → one materialization in s0 (callee-saved) and two moves.

For the target, the two addiu's are computed from s0 = base. That means the RTL had `(plus (reg) (const 24))` at each site with the reg holding the base — i.e., cse did NOT substitute the constant.

When would cse not substitute? If the constant is not in the table because... the expression `mb + 0x18` where mb's *value* is known as a constant: cse records the constant in the table. Hmm.

Unless mb's value is NOT known because the first call invalidated it: if `mb` is a *pseudo holding a constant*, cse's `qty_const` for that pseudo persists across calls (registers are not invalidated for pseudos). Hmm.

But if `mb` were *memory* (a stack slot), the call would invalidate it → reload → unknown → two adds.

So: make mb a *memory* variable! E.g., if `mb` is a local whose address escapes (e.g., `&mb` is taken), the compiler keeps it in memory. Then `mb + 0x18` at each site would load mb from the stack (extra insn) — no.

Hmm.

Alternatively: what if the base is passed through a call? no.

Let me look at the actual difference more carefully — maybe the target's `addiu a0,s0,24` comes from a different source: maybe the source is `func_8004914C(&D_800AF630[0x18]);` and the compiler materialized `D_800AF630` into s0 and then... no, it would fold.

Hmm, hold on. Let me reconsider: maybe in the target, the FIRST call's arg is `addiu a0,s0,24` where s0 was set up by the lui/addiu — and the second call's `addiu a0,s0,24` is a *separate* materialization because cse's equivalence was killed by the first call. What kills it? The call invalidates *registers* (a0) but the constant pseudo... 

Actually — maybe in the target, the compiler did NOT cse the two `mb+0x18` because the first call's argument was computed and the call clobbered... no.

Let me approach empirically: what if the first call's argument and the second's differ by being in different *basic blocks*? They're adjacent.

Hmm, let me look at what the *launder* does mechanically in the target: the asm's output constraint makes mb an unknown value, so the second `mb + 0x18` is a real add on an unknown value → addiu. And the base... wait, but the base (s0) is a constant.

So in the target (with the launder): mb is unknown after the asm, but the compiler still kept s0 = &D_800AF630 (the constant) — because before the asm, mb was the constant, and the asm's output constraint "=r"(mb) with "0"(mb) ties the output to the input register: mb stays in the same register (s0) but its VALUE becomes unknown. So the compiler knows the register s0 still holds... no, it thinks the value is unknown.

Then `mb + 0x18` = addiu on the unknown s0. So s0 = base (constant, from before the asm) and the sum is computed. That's exactly the target.

So the target is produced by the launder — the launder is what makes s0 = base and two addiu's. So the ORIGINAL C must have had something similar: a value that is unknown to the compiler but equal to the base.

In the original game's C, that would be... hmm, maybe the original code passed a *pointer variable* that came from elsewhere. E.g., the original source might have used a global pointer variable `D_800AF630_ptr` loaded from memory (unknown), or a parameter.

Since func_8018EDB0 has no caller (signature unconstrained), we could change... no, the brief says "no signature or decl change outside the body".

Hmm, but we can use an existing global that holds the address. Let me search for a pointer to D_800AF630 in src.

Alternatively — the trick used in many of these items: make the value come from a real computation the compiler can't fold, e.g., `mb = (u8 *)((u32)&D_800AF630 & ~0x1F)`? That's an identity launder (banned by the brief: "identity address spellings do NOT count as a crack").

Hmm. But what about a *genuine* computation: the base could be derived from something real. For example, `mb = (u8 *)&D_800AF630; ... func_8004914C(mb + 0x18);` and the second call could use a base obtained from a *previous* call's effect... no.

Let me look at the sibling banked function func_8018F060 (ov_SC06_018) mentioned in the comment — it's a banked MATCH of the same shape. How did it handle this? The comment says "The .s is byte-identical in structure to the banked sibling". So the sibling matched with the same launder? Or without?

Let me check the sibling's source in src/ov_SC06_018/.
