---
ts: 2026-11-06T11:54:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l84BHKUHN4aM5HVatq3f
---
Now I see the target's sched order:
99 (lw wx from mem 80), 109 (load -4 = wz), 102, 114 (load -8 = wy), 106 (lshiftrt 92 = wx>>16), 123 (wy+dy), 111 (wz>>16 = wv), 125 (launder wz), 127 (wy>>16)...

So in the target, the load -4 (wz, insn 109) comes BEFORE load -8 (wy, insn 114). And the launder (125) is after 111.

In v2 (mine), the order was: 99, 102, 114, 106, 123, 125, 109, 133, 136... i.e., 114 (-8) before 109 (-4).

The difference: in the target, insn 109 (wz load) is right after 99; in mine, 109 comes after 125.

So sched1 moved the wz load earlier in the target. Why? Because of the launder (125) — the launder is a use of reg 94 (wz) that must come after 109. In the target, the launder at 125 is after 111. Hmm.

Let me look at the .rtl dump (before scheduling) to see the original order. Actually, the key insight: sched1's `rank_for_schedule` uses INSN_LUID (original order). So the order after sched1 largely reflects the original order unless priorities differ.

Let me look at the .lreg or .rtl dump for the original order of these insns.

Hmm, this is deep. Let me think about what the launder does in sched1: the asm insn 125 has operands. In sched_analyze, an asm with a register operand creates dependencies. Also, `sched_analyze_insn` treats asm insns specially: it may flush pending dependencies.

Actually, more importantly: gcc 2.7.2's sched1 with `-O2` — the asm volatile barrier (the `__asm__ volatile ("")`) definitely splits scheduling regions. And the launder asm... `sched_analyze_1`/`sched_analyze_2` for ASM_OPERANDS: in sched.c, `sched_analyze_insn` has:
```
  /* We must not schedule across a volatile asm... */
  if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS)
```
Hmm.

Actually, in gcc 2.7.2 sched.c, `sched_analyze_insn`:
```
  if (GET_CODE (PATTERN (insn)) == ASM_OPERANDS)
    {
      /* We have to flush the queue because the asm may reference memory */
      ...
    }
```
Let me check.

This is very deep. Given time constraints, let me consider the practical question: can any real-C change make the wz load come before the wy load in the *original RTL order*? Since rank ties by LUID, if the RTL order is wz-then-wy, sched1 would keep it. In the target, the RTL order was... let me check the .rtl dump (pre-sched).

Actually, the .sched dump shows the order AFTER sched1. Let me look at .rtl (after reload? no, .rtl is after expand/first jump). Let me find the same insns in orig.i.rtl.

Hmm, but insn numbers are stable across dumps (the numbers 99, 109, 114 are the same). In the .sched dump, the chain order is 99 → 109 → 102 → 114. In the .rtl dump, the chain order would be the original.

Let me grep the .rtl dump for insn 109 and 114.

Actually, insn numbers are assigned at expansion: lower number = earlier. 99 (wx), 102, 106, 109 (wz), 111, 114 (wy), 123, 125, 127.

Wait, in the .sched dump for the target: chain 99 → 109 → 102 → 114 → 106 → 123 → 111 → 125 → 127. So the order is by the chain, and the insn *numbers* show the original order: 99, 102, 106, 109, 111, 114, 123, 125, 127. Hmm, 106 (wx>>16) < 109 (wz load) < 111 (wz>>16) < 114 (wy load) < 123 (wy+dy).

So the ORIGINAL RTL order (by insn number) is: wx load (99), wx>>16 (106), wz load (109), wz>>16 (111), wy load (114), wy+dy (123), launder (125), wy>>16 (127).

Hmm wait, that contradicts the source: source order is wx, mn, mx=wx>>16, wz, wv=wz>>16, wy, mny=wy+dy, launder, my=wy>>16. Yes! That matches the numbers exactly.

In the sched (target) order: 99, 109, 102, 114, 106, 123, 111, 125, 127. So sched1 moved 109 (wz load) right after 99, and 114 (wy load) before 106.

In v2's sched order: 99, 102, 114, 106, 123, 125, 109, 133, 136 — the wz load (109) moved LATER, after 125.

So sched1 in the target moved the wz load up; in v2 it moved it down. The launder (125) is present in the target and absent in v2.

Hmm, in v2, insn 109 comes after 125 (which is the wy>>16? let me recheck v2's dump: insn 125 = lshiftrt reg 131 = wy>>16; insn 109 = load -4).

So in v2: 99, 102, 114, 106, 123, 125(wy>>16), 109(wz load), 133, 136(wz store).

Interesting: in v2, the wz load is sunk to just before its use (the stores at 136). In the target, the launder forces the wz load earlier (because the launder uses wz and sched1... hmm, the launder is at 125, after 111).

Wait, in the target the order is 99, 109(wz load), 102, 114(wy load), 106, 123, 111(wz>>16), 125(launder), 127. So the wz load is at position 2.

Hmm, why? sched1's ready-list: at the start of the block, the ready insns are those with no deps: 99 (wx load), 109 (wz load), 114 (wy load)... all independent. Equal priority (1). Tie → LUID order: 99, 109, 114. So the target's order follows LUID! (99, 109, 114).

In v2: 99, 102, 114, ... — that's NOT LUID order (102 has LUID between 99 and 109). Hmm.

Hmm, maybe in v2 the priorities differ because of the missing launder. The launder is an asm that "flushes" the scheduler? Let me look at how sched.c handles ASM_OPERANDS: maybe it forces a "sched barrier" and creates different regions.

Actually, in gcc 2.7.2 sched.c `sched_analyze_insn`:
```
  if (GET_CODE (insn) == CALL_INSN) ...
  else if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS) ...
```

Hmm. Actually I recall gcc 2.7.2's sched1 treats all asm as scheduling barriers only if volatile. The launder isn't volatile.

Let me look at sched_analyze for ASM_OPERANDS.

Honestly, I've spent too long. Let me decide the outcome for item 2.

Given the wall rule (≥20 min, ≥30 scored tries), I have ~16 scored tries so far. I need 30 for a WALL. Hmm, that's a lot of extra tries.

Let me reconsider: maybe I'm missing a simpler crack. Let me look at the launder's purpose in the header comment: "zero-byte re-tie #2 — see (2) in the header". There might be a header comment in the TU explaining the levers! Let me look at the top of the function or a comment block. The TU may have a header explaining (1) and (2). Let me search for "re-tie" or "(2)" in the file.
