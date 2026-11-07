---
ts: 2026-11-06T08:33:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6psATBUNk0KCtR7DymJQ
---
There's asm-differ and `tools/cc1_dumps_tu.sh`. For target disassembly, maybe `tools/asm-differ` or a `dump` tool. Let me ask the retriever? Actually, cheaper: `--keep` on delever_search --try prints the candidate object path. The target object is in build/. Let me find the build object for the TU and objdump it. But is objdump allowed? Yes via a script.

Actually, maybe I don't need the full listing — the diff already tells me exactly what to fix: get `addiu a0,sp,24` emitted before the bnez (in the beqz delay slot).

Real-C approaches:
(a) Use `sp18` as an argument expression that must be evaluated before the inner branch. What if the inner if is inverted: `if (D_801270CC != 0) return-ish else {...}`? No, the outer is `if (D_801270C8 != 0)`.

(b) Make a0pin initialized and *used* by a store before the branch that the target also has. The target's first instruction after addiu a0 is bnez; so no store before.

(c) The call `func_8012C51C(a0pin, param_1)`: argument setup order — gcc emits a0 first? If args are computed left-to-right, a0 = sp18's address computed before a1 = param_1 (which is already in a0? no, param_1 is the incoming arg in a0!). Interesting: param_1 comes in $a0. So the call needs a0 = &sp18, a1 = param_1. param_1 is in a0 originally, so it must be moved to a1 first, or saved. Let me see the code around the call in the target. Let me dump the target asm.

Let me look at how delever_search gets the target: maybe there's a function to dump. Simplest: compile the TU, find the object, objdump. `--keep` prints the candidate object path. Let's run --keep with orig_body and then inspect its dir; the target object path might be nearby.

Actually the tool likely has the target .o path derivable: build/src/ov_SC01_084/ov_SC01_084_jr_80182A00.o? Let me check build tree.
