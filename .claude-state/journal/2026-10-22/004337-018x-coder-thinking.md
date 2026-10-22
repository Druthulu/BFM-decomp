---
ts: 2026-10-22T06:43:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Jrx8xC0hi33AKWeoLaDp
---
So: `birthing_insn_p` boost for an insn that BIRTHS a pseudo with reg_n_sets == 1. So the birth of rgb's pseudo gets a LAUNCH_PRIORITY boost in mine (1 set) — and the boost makes `move s0,a2` launched EARLIER. But observed: in mine, move s0,a2 is LATER (position 7) vs target 6?!

Hmm wait, let me re-read the diff: "delete mine[5:6] target[5:5] / 5 li a0,16 | --" and "insert mine[8:8] target[7:8] / 8 -- | li a0,16".

The diff format is confusing. Let me get the target and mine instruction lists with indices to compare properly.

Target (from objdump):
0 addiu sp,sp,-48
1 sw s2,32(sp)
2 move s2,a0
3 sw s4,40(sp)
4 move s4,a1
5 sw s0,24(sp)
6 move s0,a2
7 li a0,16
8 sw ra,44(sp)
...

Mine:
0 addiu sp,sp,-48
1 sw s2,32(sp)
2 move s2,a0
3 sw s4,40(sp)
4 move s4,a1
5 li a0,16
6 sw s0,24(sp)
7 move s0,a2
8 sw ra,44(sp)

Hmm, but wait — maybe the diff indices are 1-based and the "delete mine[5:6]" means my instruction at 1-based index 5 = li a0,16 ✓ (0-based 4?). Eh.

Actually mine's li a0,16 is at 0-based 5, target's at 0-based 7. So mine's li is EARLIER by 2.

The C0458 entry "COPY THEN ACCUMULATE ON THE COPY: resolving the birthing-boost vs register-allocation dilemma" is likely relevant. And C0453. Let me read C0458 and also check for a cookbook entry about "how to get a second set in plain C" — the key question: how do I give rgb's pseudo a second set without asm?

The G14 result: "v = (s16)v; real 2nd sets" — a mode-changing cast.

For rgb (s32), what mode-changing cast preserves the value? None.

BUT: what if the pseudo in question isn't rgb but something else? Let's identify which pseudo is "birthing" in mine and boosted: the boost applies to the insn that BIRTHS a pseudo with reg_n_sets == 1. In mine, `move s0,a2` births rgb's pseudo ($16). Boosted → launched earlier. But observed: mine has move s0,a2 LATER (7) than target (6). Contradiction again!

Unless... the boost is on `li a0,16`? li a0,16 births the const pseudo 16 (a pseudo, since it's a constant loaded into a hard reg — actually `li a0,16` defines a0 hard reg; the const 16 is an immediate). Hmm, for MIPS, `li a0,16` = `addiu a0,zero,16`? That's a hard reg def, no pseudo.

Hmm, but wait: in the tree's version, is `li a0,16` even an instruction? Yes: d2e8: li a0,16.

So which pseudo is birthed by an insn that got boosted? Let's check with a -dS trace! We can compile the TU with -dS (sched1 dump) and look at the priorities. The project has tools/cc1_dumps_tu.sh. But we need gcc's internal dump: -dS prints sched1 details to stderr. Let me check what compiler the project uses (config/cc or tools). Let me look for the compile command in the project (e.g. config/*.mk, or the cc1 invocation used by delever_search).

Let me check how delever_search compiles the candidate, so I can replicate with -dS.

Actually simpler: use `tools/cc1_dumps_tu.sh` which is designed for this. Let me read it (--help).
