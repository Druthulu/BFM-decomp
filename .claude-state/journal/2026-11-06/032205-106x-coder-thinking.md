---
ts: 2026-11-06T10:22:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WYLMhSQshnsuwgFRp2Xy
---
No. The in-place sign-extension is hard.

Let me reconsider. The temp v1 for the sll: `sll v1,s0,0x10; sra s0,v1,0x10`. This is 2 instructions, same as target's `sll s0,s0,16; sra s0,s0,16`. The only diff is the temp register (v1 vs s0). 

In the target, the sll is in-place. This is the classic "sign-extension of a hard register" pattern. Since div is a pseudo, gcc uses a temp. 

Hmm, can I make gcc use the same pseudo for the sll result? `div = (s16)div` → the result is assigned to div. gcc generates `(set (reg div) (sign_extend (subreg (reg div) 0)))`. The MIPS expander for extendhisi2 might generate `(set (reg temp) (ashift (reg div) 16))` then `(set (reg div) (ashiftrt (reg temp) 16))`. So the temp is an intermediate.

If combine sees `sll temp,div,16` and `sra div,temp,16`, it might merge into a single sign-extension pattern if one exists. But the MIPS machine has `sll`+`sra` as the sign-extension sequence.

Hmm, what if I write the sign-extension as `div = (s16)div;` where div is declared `s32` — same.

What if div is used in a way that combine folds the sign-extension into the division? The MIPS div instruction takes a register; the sign-extension is separate.

OK, the in-place sign-extension requires the temp to be the same reg as div. local-alloc assigns the temp v1. If the temp were allocated to s0... 

The temp is a 2-ref, 2-live pseudo → priority 10000. It's allocated in local-alloc. At its birth, which registers are free? v0 is busy (call result), v1 free → v1.

What if I make v0/v1 busy at the temp's birth so it picks s0? Hmm.

Alternatively, what if the sign-extension temp is tied to div via a copy preference? The temp's def is `sll temp,div` and its use is `sra div,temp`. In combine_regs, for `sll temp,div,16`: ureg=div, sreg=temp. may_save_copy? sll is not a copy. But `(set (reg temp) (ashift (reg div) ...))` — the source and dest are different. combine_regs might tie temp to div if div dies at this insn. div doesn't die (it's used in the sra). Hmm.

For `sra div,temp,16`: ureg=temp, sreg=div. temp dies here (REG_DEAD). combine_regs would tie div to temp's qty if div has no qty yet. But div already has a qty (global). So no tie.

Hmm.

Let me think about the pin's role here: with the pin, div is a hard reg s0, so the sll is `sll s0,s0,16`? Wait, the pin forces div into s0 as a hard register. Then `div = (s16)div` with div being a hard reg: gcc emits `sll s0,s0,16; sra s0,s0,16`? But then the temp would be needed... Actually, for a hard reg, gcc can do the sign-extension in-place using the hard reg as both.

Hmm.

OK, let me consider a different C spelling that might produce in-place: `div = (s16)div;` vs `*(s16*)&div`? No.

What about `div = (s16)(div & 0xFFFF);`? The `& 0xFFFF` would zero-extend, then (s16) sign-extends. That's `andi div,div,0xFFFF; sll; sra` — 3 insns. No.

Hmm. What if the divisor is kept as a `u16` and the division promotes it? Let me try `u16 div;` (f8 used s16).

Let me think about the target again: `sll s0,s0,0x10` then later `sra s0,s0,0x10`. If the source had `div = div << 16; ... div = div >> 16;` with a statement in between, gcc would emit `sll s0,s0,16` in-place (shift by constant, in-place allowed) and `sra s0,s0,16` in-place! Because the shift patterns allow src==dest.

f3 did exactly that (`div = div << 16; div = div >> 16;`) and scored 22. Hmm, but f3 was based on f2 (with keepalive). Let me check f3's diff — maybe the shifts produced in-place but something else broke.

Let me diff f3.
