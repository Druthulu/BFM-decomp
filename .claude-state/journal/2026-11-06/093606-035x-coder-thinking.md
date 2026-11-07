---
ts: 2026-11-06T16:36:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rfHDXHyQ7FWHdZm3sCOB
---
Still merges (307). So gcc collapsed the labels (adjacent labels merged, or the jump retargeted). Let me check the assembly: maybe the two labels are at the same address and cross-jump still merges because do_cross_jump just redirects one jump to the other label. Let me inspect: does the RTL still have two jumps? Cross-jump's second path: `for (target = jump_chain[UID(JUMP_LABEL(insn))])` — with ret and ret2 different, no. But the first path find_cross_jump(insn, JUMP_LABEL(insn), 1): for jumpB (goto ret2), it compares before jumpB with before ret2. Before ret2 = ... the insns before ret2 in the stream. What's before ret2? `func_80059658(1);` from `after:`. Not matching block B. So no.

But the merge still happened → maybe gcc merged the labels earlier: in jump1, `if (LABEL_NUSES == 0) delete`. Both used. Hmm, but there's an optimization in jump1: `jump_optimize` may redirect a jump whose target label is immediately followed by another label — I recall `if (GET_CODE (insn) == CODE_LABEL && ...)` handling. Let me check: jump.c line ~262 "&& ((GET_CODE (insn) == CODE_LABEL && n_labels-- > 0)". There's `delete_insn` for labels.

Actually, maybe the merge is not of the two if-blocks at all! Let me re-examine: without the barrier, 307 ins. What if the merge is of block A with the `done:` block's prefix? done: func_800D2D44(0); func_800468FC(); func_8002D8D4(); func_80043830(...). Block A shares the first 3. Cross-jump merges suffixes of jumps to the same label — no.

Let me actually look at the 307-ins assembly to see what merged. Use --keep to get the object and objdump? dt.sh doesn't. Let me use sc/keep: `delever_search.py --try ... --keep` prints the object path. Then objdump. Hmm, objdump location: tools/... Let me just use --keep and read the .s? Actually compile_obj produces an object. I can objdump it with the mips binutils from the recipe. Simpler: use `--explain`? No.

Alternative: generate the candidate .s via cc1 dumps? tools/cc1_dumps_tu.sh. But easier: use `--keep` and then find the objdump binary. Let me check the recipe pipeline to find the objdump used by md.insns_from_object. Let me grep tools for objdump path.
