---
ts: 2026-11-06T15:07:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E4g0YXH2q2QTVDm9mnLl
---
Now vol went to a3 (was a1 in target). Because the u16 cast moved vol's register (a3). Interesting.

Back up. In the target: vol in a1, pan in a2. In c_u16: vol in a1 (correct), pan in a2 (correct) — only the delay-slot issue. c_u16 had score 2 and 237? It said 237 ins. But my objdump showed 2 andis and 238 total... maybe the tool's count differs from mine (maybe it counts 237 for both and my manual count of the target was off by one).

Hmm, target disasm: let me count from 4b1c to 4ba0... whatever.

c_u16 = 237 ins, one slot wrong (andi in bne delay slot instead of sll). In target the bne delay slot has sll and jal delay slot has andi. In c_u16: bne delay has andi (the cast's) and jal delay has andi (the final mask). So c_u16 has one MORE andi than target but the tool says both 237. So target must have one insn c_u16 lacks. Looking at the target's 4b54-4b58: `addiu v0,a2,160; nop; mult v0,a0` — the nop is a hazard nop. c_u16 at 4b54: from the dump: `4b54: ?` we saw 4b5c mult v0,a0 and -B14 didn't show 4b54/4b58. Let me assume c_u16 lacks that nop (hazard) and has an extra andi → 237 both.

So to be exact: I need to remove the cast's andi (losing 1) and gain the hazard nop (gaining 1). The hazard nop appears when the pan mult immediately follows the vol mult's mfhi.

So really: c_u16's schedule has the pan mult right after mfhi (no hazard nop) while target has `addiu v0,a2,160; nop; mult v0,a0`.

Hmm. So the schedules differ beyond the delay slot: mine lacks the nop.

Let me get c_u16's full tail to compare precisely. Use the cand.o from --keep (p3). But I've since overwritten? The path .run/P36/engine/score/.../p3/cand.o is from c_u16 (the last --keep I ran was c_u16). Yes.

Let me dump c_u16's 4b20-4ba4.
