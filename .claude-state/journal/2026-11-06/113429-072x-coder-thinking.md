---
ts: 2026-11-06T18:34:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PoGXH3k8Cm9lXBBLo6KJ
---
In the orig (with keepalive):
- block 3 has insns 45,47,49,52,55,57,60,63,66,69,72,74,77,79,88,91,96,98,100,102,106,107.
- insn 55 (the a1 symbol_ref) has priority 1 but in the ready list at T-18: "52 (1) 55 (7f000001)" — 55 has a special marker 7f000001! That's the "insn is in the ready list with priority 0x7f000001" — this is the `SCHED_GROUP` or the "asm" flag? Actually 7f000001 suggests priority 0x7f000001 = 2130706433 — a special "barrier" priority? Hmm, in the trace, some insns show (7f000001) and others (1). The call insns show 7fffffa5. The 7f000001 ones are probably "asm" insns (volatile) — no wait, 55 is the a1 symbol_ref, not the asm.

Hmm, the value 7f000001 = 0x7f000001. In sched.c, `INSN_PRIORITY` is capped at 0x7f000000? Let me check: sched.c has `#define INSN_PRIORITY(INSN) (INSN_UID... )`. There's `priority` set to `0x7fffffff` for the last insn. 0x7f000001 might be "the insn has a REG_DEP_ANTI to a call" or something.

Actually 55 in the orig is insn 55 = `(set 77 (symbol_ref D_801A15AC))`. In the scheduled RTL of the w1 build, the symbol_ref got folded into the call arg insn 94. In the orig, insn 55 has a use by the asm (insn 57, ref_count 11 — the asm uses all memory). So 55's ref_count is 1 but its priority in the ready list is 7f000001. Hmm.

Interesting: in the trace at T-18, "52 (1) 55 (7f000001), now 55 52" — so 55 was chosen before 52. So 55 is scheduled at T-18 → near the beginning of the final order. The final order (reverse of T): T-22=45, T-21=47, T-20=49, T-19=52, T-18=55, T-17=57, ... so 55 comes at position 5 (after 45,47,49,52) — matching the target's a1 at 22-23 (after the two moves).

So in the orig, insn 55 is scheduled early because it's in the ready list with a special priority 0x7f000001. What is that? Looking at sched.c: `INSN_PRIORITY` for insns with `REG_DEP_ANTI`? Hmm. Let me grep sched.c for "7f000000" or 0x7f.

In sched.c, the priority of an insn is `max(0, ...)`; the ready list dump prints `INSN_PRIORITY (insn)`. There's a special: `if (GET_CODE (insn) == JUMP_INSN) priority = 0x7fffffff`? Hmm. Or maybe insns with a `REG_DEAD` note?

Let me grep for 0x7f in sched.c.
