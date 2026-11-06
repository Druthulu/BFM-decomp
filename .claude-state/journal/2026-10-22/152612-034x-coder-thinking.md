---
ts: 2026-10-22T21:26:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QAzzbRlPxdd1XE20g6yR
---
So v15 keeps arm1/arm3 separate (114 ins) — the merge is defeated by the statement-order change in arm1. The residual: in arm1, the `sh zero,46` and the `j` are swapped (mine has j then sh zero,46; target has sh zero,46 then j).

So arm1's source order is now: ..., unk30=-0x50, unk2E=0. The scheduler put `sh zero,46` in the delay slot of the j. Target has it before the j.

I need a source order where sched1 emits: sh0-36; sh0-46; j; sh v0,48.

Currently with source order unk24, unk30, unk2E: output ... let me look at the actual mine disassembly. mine[54] missing sh zero,46 → so mine has: sh0-36; j; sh zero,46 (delay); sh v0,48? Let's see: delete mine[55:57] = j then sh zero,46; insert target[54:56] = sh zero,46 then j.

So mine: [53] sh zero,36; [54] ?; [55] j; [56] sh zero,46. Hmm, target [53] sh0-36; [54] sh0-46; [55] j; [56] sh v0,48.

Wait the diff says insert at mine[54] the target's sh zero,46 and j; delete mine[55..56] j and sh zero,46. So mine: [53] sh0-36, [54] sh v0,48?, [55] j, [56] sh zero,46. Hmm confusing. Let me just dump v15 and look at arm1.

The goal: arm1 order must be sh0-36, sh0-46, j, sh v0,48. Currently something's in the delay slot wrongly.

Let me try other arm1 orders:
- unk24, unk2E, unk30 (original → merges).
- unk30, unk24, unk2E.
- unk24, unk30, unk2E (v15 → 4).
- unk20/unk22 swapped? would change sh 32/34 order.
- unk2E, unk24, unk30.

Since v15 is close (4), maybe another order gives 0. Note the delay-slot content: the j's delay slot in the target is `sh v0,48` (the k store). In v15 the scheduler put `sh zero,46` in the delay slot instead — because unk2E's store comes last in source, so reorg picked it as the delay filler? Actually reorg picks the insn before the jump (fall-through) as the delay slot candidate.

With source order unk24, unk30, unk2E: the last store before the jump is unk2E → reorg puts it in the delay slot, and moves... hmm, but the target has unk2E before the j and unk30 in the delay slot.

sched1 runs before reorg. In the target's arm1 (ROM): sh0-36; sh0-46; j; sh v0,48. So sched1 ordered: unk24 store, unk2E store, unk30 store (last) → then reorg filled the delay slot with the last insn (sh v0,48) since it's safe (executes in both paths? no — the delay slot executes on the taken jump; the store is needed anyway).

In v15 the order became: sh0-36; sh v0,48; ... hmm.

Let me try to make arm1's source order: unk24, unk2E, unk30 — that's the original, which merges. The merge happens because arm1 == arm3.

Hmm, but what if instead I change arm3's order and keep arm1 as the original? Then arm3's block differs (no merge) and arm3's own schedule might still be right. Try: arm3 order unk24, unk30, unk2E (v9 — compile error, fix), or arm3 unk30 first.

Let me first fix the compile errors: v9-v13 — the k decl is emitted first, but the store `unk30 = k` may come before... no. Let me check the error message.

Actually the error was truncated. Let me check v9 quickly.

Also I realize: for arm1 the delay-slot difference is about reorg. Let me try several arm1 orders:
 a) unk24, unk30, unk2E (v15: 4)
 b) unk2E, unk24, unk30
 c) unk30, unk24, unk2E
 d) unk24, unk2E, unk30 (= orig, merges)
 e) unk20, unk22, unk30, unk24, unk2E

And arm3 orders keeping arm1 original:
 f) arm3: unk24, unk30, unk2E
 g) arm3: unk30 first

Let me fix gen.py and produce these. First check the v9 error.
