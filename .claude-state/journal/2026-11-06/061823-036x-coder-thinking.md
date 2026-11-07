---
ts: 2026-11-06T13:18:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dBj2YmfEP11lbppLpqeF
---
Line 320: "n as s16 (outer cross-jump copy survives)" — interesting: making a variable s16 made a cross-jump copy survive. That's a width change: two copies that were identical at s32 become different? Or the outer cross-jump copy... Hmm, "n as s16" changed the code so that the two copies differ? Let me look at func_80187EA0 for context. It's a MATCH with barrier,pin kinds, and the move included "n as s16 (outer cross-jump copy survives)".

That suggests a width change can break cross-jump: two copies that both use `n` as s32 are identical; making `n` s16 introduces a sign-extension (sll/sra) in one place? But that changes code... unless the extension was already there.

Alternatively, the s16 change affects the *condition* insn: e.g., comparing an s16 variable uses `sll/sra` before slt, while the other copy compares an s32 → different RTL, but the final code... no.

Hmm, let me look at the actual item (ov_SC06_029 func_801857A4? no). func_80187EA0 is another shard's item.

Let me look at the source of that function and its notes? It's in src somewhere. But that's a detour.

Let me reconsider item1: maybe a much simpler real-C difference: the two copies could use different *memory addressing*: e.g., in case 3 use `p->unk1C` via a `u32` cast vs `s32`. If one copy stores with `sw` and the other... no.

Think about rtx_renumbered_equal_p more carefully. At post-reload, registers are hard. The function's purpose: allow matching when regs differ. It builds a mapping from reg in x to reg in y. If x uses reg R twice and y uses two different regs, that's inconsistent → unequal. But the final bytes would then differ... unless the two different regs are the same at assembly? No.

BUT: what about a *dead* register difference? E.g., an insn `sw v0, 28(s0)` in A vs `sw v0, 28(s0)` — same.

What about the *delay-slot nop*? Not present yet.

What about a REG_DEAD/REG_UNUSED note difference? Notes are in the insn's REG_NOTES, not the pattern; rtx_renumbered_equal_p compares PATTERN only. Not it.

What about a difference in the *order* of the two copies' instructions? Same bytes impossible.

OK here's another thought: maybe the original source's case 1 and case 3 differ in that one uses a *function call in between*? No, bytes same.

Let me look at the actual target's bytes again — are the two copies REALLY identical? Compare 0x940-0x960 and 0x9c0-0x9e0:
0x940: 8e02001c lw v0,28(s0)
0x944: 00000000 nop
0x948: 24420001 addiu v0,v0,1
0x94c: ae02001c sw v0,28(s0)
0x950: 28420010 slti v0,v0,16
0x954: 10400032 beqz v0,a20
0x958: 00000000 nop
0x95c: 0800029c j a70
0x960: 00000000 nop

0x9c0: 8e02001c
0x9c4: 00000000
0x9c8: 24420001
0x9cc: ae02001c
0x9d0: 28420010
0x9d4: 10400012 beqz v0,a20  ← same target a20
0x9d8: 00000000
0x9dc: 0800029c j a70
0x9e0: 00000000

Identical bytes except the beqz immediate (a20 both!). Wait: 0x954: 10400032 — immediate 0x32 → target = 0x954+4+0x32*4 = 0x958+0xC8 = 0xa20. 0x9d4: 10400012 → 0x9d8 + 0x48 = 0xa20. Same target. So both beqz target a20.

And both j target a70 (0800029c: target = (0x95c+4 & 0xf0000000) | 0x29c*4 = 0x80000000 + 0xa70 = 0x80000a70? For the object, the reloc R_MIPS_26 .text. The diff tool masks the reloc but the target address is within .text: a70). Both same.

So the two copies are truly identical instruction-for-instruction, including branch targets. Cross-jump MUST merge them... unless something structural prevented it in the original compilation.

Possibilities:
1. In the original, the two jumps to TAIL were not in the same jump_chain because one of them was a `j` created by jump optimization from a conditional and the chain wasn't updated? Unlikely.
2. The original had a CODE_LABEL between them.
3. The original had different insns that became identical AFTER the cross-jump pass: what runs after jump_optimize? dbr_schedule (delay slot filling) and assembly. Also `MACHINE_DEPENDENT_REORG`? Let me check what MIPS defines. If the MIPS port has MACHINE_DEPENDENT_REORG... In gcc 2.7.2 mips.h, there's no MACHINE_DEPENDENT_REORG I think. dbr_schedule fills delay slots. Could dbr_schedule transform a different instruction sequence into these bytes? For example, one copy could have `move v0,v0` (a no-op) which jump_optimize's noop_moves deletion removes... that's before cross-jump? The pass order within jump_optimize: let me check whether delete_noop_moves happens before the cross-jump loop. If it happens AFTER, then a no-op move in one copy would prevent the merge and then be deleted later in the same pass! Let me check jump_optimize's structure.

That's promising: "delete no-op move insns" is mentioned in the comment at line 3135-3138: "One more attempt to remove jumps to .+1 left by dead-store-elimination. Also do cross-jumping this time and delete no-op move insns." So the pass does both. If the no-op moves are deleted at the END (or in a separate phase), a `move r,r` could block cross-jump and then be deleted.

Let me check jump_optimize in jump.c: search for "noop_moves".
