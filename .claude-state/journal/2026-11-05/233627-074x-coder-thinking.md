---
ts: 2026-11-06T06:36:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6vRPbKAuEfWhw2JA4o2k
---
r73: 13 refs across 14 insns, live at the start of block 4 — that's `t`! Block 4 is the tail (after the if/else), and t is live at the start of block 4. Yes: t = unk2 at the end.

Wait, t is assigned in block 2 (t = unkA...) and used in block 4? Hmm. t's live ranges: 
- block 2: t = unkA; t -= 0x30; compare; t = D_801D094C or D_801D093C; t |= ...; unk58 = t. Then t = unk2 in block 4.

So t is one pseudo (r73) with 13 refs across 14 insns, live at the start of block 4 (the assignment t = unk2 happens in block 4). Hmm, "Registers live at start: 29 30 72 73" for block 4 — t is live into block 4 because the assignment `t = unk2` is in block 4 and... whatever.

So r73 = t, pri 27857, and it's FIRST in the alloc order — so it should get $2! But the final assignment put the middle value in v1 ($3).

Hmm, wait: order is 73 76 72 74. r73 first → the lowest free reg. But r73's conflicts: "conflicts v0,sp" — it conflicts with $2! So it can't take $2.

Why does t conflict with $2 (v0)? Because of a call: t is live across... hmm, v0 is call-clobbered. Does t cross a call? Yes! The final `D_801D0A3C[t](a0)` — t is used as an index at the call. But being used AT a call doesn't make it conflict with v0... Actually it does: at a CALL_INSN, all call-clobbered hard regs are marked live, so any pseudo live across the call conflicts with v0/v1/a0-a3.

t is live at the call (as the index), so it conflicts with v0 (and v1). Hmm, but the target has t in $2 at that point.

Wait, the target: `t = unk2; D_801D0A3C[t](a0)` — the index is loaded then used immediately; it's live across the jal? No: the sequence is `lhu v0,2(a1)` then the table load `sll/lui/addu/lw` then `jal`. The t value is consumed before the jal (the call target is computed from it). But the *argument* a0 is live across the call. Hmm, and the call `D_801D0A3C[t](a0)` — t is dead after computing the call address.

But flow says t is live at the start of block 4 and conflicts with v0. Hmm, the "conflicts v0" comes from the call: at the CALL insn, v0 is live (call-clobbered) and t is live (it's used to compute the call target just before? if t is still live at the call insn, it conflicts).

Let me look at the RTL around the call: t (r73) is used in `(set (reg 73) (mem (plus (reg 73) ...)))` then the call. If t dies before the call insn, no conflict. But the dump says t conflicts with v0.

Hmm, in MY body, `t = ((Unkstruct*)a0)->unk2; D_801D0A3C[t](a0);` — t is loaded, used to index, then dead.

But flow's live analysis: t is live at the start of block 4 and dies... at the call? The call insn's uses include t (indirect call target via memory). If t's REG_DEAD is after the call insn, t is live AT the call → conflicts with v0.

Hmm, but in the target t IS v0 ($2 pinned) — a hard reg can be used at a call (it's the target computation).

So in the target, the pin forces $2 despite the conflict. Lever-free, t can't get $2 because it conflicts with v0.

Hmm, wait. That doesn't sound right either: t would then conflict with v0 only if t is live *across* the call. Let me look at the RTL of block 4.

Actually the conflicts line says r73 conflicts with v0 and sp only (not v1, a0). If t were live across the call, it'd conflict with v1, a0-a3 too. So t conflicts with v0 only — meaning t is live at a point where v0 is live (e.g., a call result or...). Hmm.

Let me look at block 4's RTL.
