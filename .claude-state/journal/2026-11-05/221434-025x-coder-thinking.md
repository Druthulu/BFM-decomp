---
ts: 2026-11-06T05:14:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g8pC9UbvzpyHaxCzAu4O
---
So the target (with barrier) has an extra sp adjustment pair in the middle of the function — clearly the barrier asm is being expanded into a stack adjustment! The empty asm with memory clobber in GCC 2.7.2 apparently makes the function think it needs a frame (16 bytes), and the frame adjustment is emitted around the asm position due to scheduling.

Wait, that doesn't make sense as an "empty" asm. Unless the barrier is not empty in the target — but the current source has `__asm__("" ::: "memory")` and it scores 0. So yes, the empty asm produces these sp adjustments.

Hmm, why? In GCC 2.7.2, `expand_asm_insn` for an asm with `volatile`... Actually, I recall: an `asm` with clobbers makes the function `current_function_has_nonlocal_label`? No.

Ohh — I bet the empty asm is treated as a call for the purpose of `current_function_outgoing_args_size` or the stack pointer adjustment. Hmm. But 16 bytes = one outgoing arg slot. Interesting: `-16` = 4 words = outgoing args for a call? And there's no call... but the asm acts as a call site.

Hmm, actually maybe the mechanism: GCC 2.7.2 expands asm statements and, if they're `volatile`, inserts a `NOTE_INSN_BLOCK`? no.

Regardless of the mechanism, the crucial insight is: **the target contains stack-pointer adjustments that are a direct artifact of the barrier asm**. A lever-free body CANNOT produce those, because no C construct emits a mid-function sp adjustment without a call... unless we add a real function call! A call would emit `addiu sp,sp,-16` (outgoing args) — but a call also emits `jal` and needs ra saved. Not the same.

Hmm wait, but actually maybe the sp adjustment comes from the *frame* being 16 bytes and the prologue/epilogue being scheduled to the asm location because the asm clobbers memory and sched1 moved them? No, prologue instructions are emitted at the start by final, not sched.

Hold on. Let me reconsider: maybe the `addiu sp,sp,-16`/`addiu sp,sp,16` pair is not a frame at all but the *asm statement's own expansion*. In GCC 2.7.2, an asm statement that clobbers memory might be preceded by a stack adjustment because the compiler thinks the asm could call something? 

Actually! I remember: GCC 2.7.2 models `asm` as `ASM_OPERANDS` and in `sched.c`/`reorg.c`, `asm` insns are "schedulable"? The sp adjustment... 

Let me look at the RTL dump to see what the asm expands to. Use tools/cc1_dumps_tu.sh. But actually, more productive: if the target requires these sp adjustments and they're asm artifacts, then a lever-free body can never match → these items are WALLs. But the task says find lever-free bodies scoring 0. Maybe the intended answer is that these ARE walls? The task allows WALL if ≥20 min and ≥30 tries. But that seems like a lot of work for 5 items.

Wait — maybe I'm wrong. Maybe the sp adjustments are NOT from the barrier. Let me test: strip the barrier and see. We did — the candidate has no sp adjustments. So yes, the barrier causes them.

Hmm, but hold on: could the sp adjustment be from `__asm__("" ::: "memory")` acting as an "asm with memory clobber" that GCC thinks needs a frame because the function's stack frame is non-empty due to the *asm's clobbered registers needing spill*? There are no clobbered regs.

Let me actually look at the RTL/asm dump to understand. Use tools/cc1_dumps_tu.sh on the header includer. Let me first find an includer TU for func_80175820. Let me check how delever_search finds includers: it uses `recs_for`. Let me look at that.

Actually — WAIT. Maybe the target's sp adjustment pair is from the *barrier* being placed at that point and GCC's `expand_asm_insn` emitting a `cli`? No, MIPS.

Let me look at the actual RTL. hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>. I need an includer TU. Let me find one: grep for the include in src. But "never grep widely"? A targeted grep is fine.

Let me check how delever_search determines includers.
