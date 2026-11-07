---
ts: 2026-11-06T01:52:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TESOpqnaWEjFBMG6XASF
---
None of these obviously. Let me take the empirical shortcut: use gdb? Or use `-d` to see... Actually, maybe I can find the deletion by checking which pass: compile vA with -dj only? The .jump dump is after the first jump_optimize. We know the jump is gone after it.

Hmm, wait: maybe the jump wasn't deleted but *redirected into a RETURN and then the RETURN was deleted by the "delete insns following barriers" pass at the start of the NEXT jump_optimize*? But the dump is before the next pass.

OK let me just instrument: run cc1 under gdb with a breakpoint on delete_insn? That's heavy but decisive. Alternatively, use the gcc source knowledge: the function `jump_optimize` at the end has `#ifdef HAVE_return` block. Wait — is HAVE_return defined for this MIPS port? The mini test's asm shows `j $31` at the end (the epilogue is just `j $31` for a leaf). In our target function, the epilogue is `lw ra; lw s0; addiu sp; jr ra`. These come from final.c's function_epilogue. So HAVE_return might be undefined.

Hmm.

Let me try yet another approach: look at what the *first* jump pass does to a trailing `return;` in a non-leaf function with a frame. In the mini2 test (leaf), the trailing return was elided at .rtl or .jump? mini2: rtl had 4 jump_insns, jump had 2. So 2 jumps were deleted in the first pass. Which? The first return's jump (to $L1) and the final return's jump. Both deleted? But the asm shows `j $L1; sw` for the first return — that's a jump! Wait, the asm: 
```
beq $2,$0,$L2
li $2,2
j $L1
sw $2,4($4)
$L2: li $2,3
sw $2,8($4)
$L1: j $31
```
So the first branch's `return;` became `j $L1; sw`. That jump exists in the final asm. But the .jump dump had only 2 jump_insns: the beq and the j $L1. The final `return;` in the else was elided (fall-through). So .rtl had 4 jumps: beq, j $L1 (if-return), another? and the final return's j. So the first pass deleted the final return's jump (jump-to-next).

So jump-to-next deletion for a simplejump DOES happen. Where? Let me find it: maybe in `thread_jumps`? No. Hmm, in jump_optimize there's this code near the beginning (line ~176): "Delete insns following barriers, up to next label." Not it.

Let me look at line 430-440 and 455-465.
