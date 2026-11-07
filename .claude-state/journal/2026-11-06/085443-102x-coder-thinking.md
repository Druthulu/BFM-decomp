---
ts: 2026-11-06T15:54:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w9OI4BjNOfnBFDdYe7Iv
---
Adding real statements adds instructions (350-352). Not the crack. ve3 (otz = otzr) adds 1 insn and score 44 (worse than 39).

Hmm. The launders are zero-byte. Real C re-derivations cost bytes.

Time check: item 4 has taken a while. Let me check the time.

Actually, maybe I should reconsider: the 2-output launder's role might be replicated by a `do{}while(0)` EBB split (C0535) around the tail? The EBB split would prevent cse unification without adding instructions. Let me test: wrap the `if (n<4) { ... }` block in `do { ... } while(0); // !FAKE: do-while`. Hmm, but the tail is inside the `if (otz < 0x1000)` block. Wrapping the second if in do-while splits the EBB.

Wait, what exactly needs preventing? Without the launders, jump.c cross-jumps the two `if (n<4)` blocks (POLY tail and LINE tail), saving 2 insns. To prevent that, make the two blocks non-identical. The launders (with #line) make them non-identical? Hmm.

Actually, let me reconsider: the two tails are in different branches (POLY vs LINE) but identical code `if (n < 4) { q = func_80010A08(8); ... }`. jump.c cross-jump merges identical blocks. The launders sit right before each block and set n/otz to unknown values; the *asm insns* are in the tails, and cross_jump's rtx_equal_p on ASM_OPERANDS compares file+line (identical → equal) — so the asm insns ARE equal and cross-jump is possible. But the target doesn't merge. Hmm, so why not?

Unless the asm's outputs (n, otz) are *used* differently in each tail due to the different register allocation, making the blocks non-identical? Or the asm prevents jump2's... 

The comment says: "The zero-byte `__asm__("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz))` launder retires cse1's cross-call unification of the OT index / n<4 test; its two copies carry identical `#line 900 "p.c"` so jump.c can cross-jump the POLY/LINE tails (ASM_OPERANDS rtx_equal_p compares file+line) — LOAD-BEARING."

So the launders *enable* cross-jump by making the asm operands identical? But the target has two copies of the test... Let me look at the target's tails. The diff at insn 280+ showed target has `slti v0,s0,4; beqz v0,182c` (one) and later `slti v0,s0,4; beqz v0,18c0; nop` (another) — two copies. So no cross-jump of the test. But maybe cross-jump merged something else (the q block?). Hmm.

Actually, the diff shows mine (c3) has 344 insns vs target 346: mine has 2 fewer. The diff at 280-302 shows mine has one `slti a2,s4,4; beqz a2,18b8` and target has `slti v0,s0,4; beqz v0,18c0; nop` twice. So mine merged the two tails into one (cross-jump), target kept two.

So the launders PREVENT cross-jump. And the comment says they *enable* it — contradictory. Maybe the comment is about a different pair of tails (the two `if (n<4)` blocks vs the tpage chains). Whatever.

The practical question: how to prevent the cross-jump with plain C, at zero cost? The `#line` directives are still there in c3 (I kept them). The launders are gone. What if I remove the `#line` directives too? That would change the line numbers of the tail insns, possibly preventing cross-jump (different lines → not equal). Let me test removing the #line lines from c3!

Actually, the #line 900 makes the following code's line number 900 for both tails (identical). If instead the two tails have different line numbers (their natural source lines differ), cross-jump's rtx_equal_p would compare the insn line numbers? jump.c cross_jump compares rtx_equal_p of the patterns; the insns' line numbers are in the NOTE_INSN or the insn's line field. For normal insns, line numbers don't matter for equality (only for ASM_OPERANDS). So removing #line might not matter. But let me test.

Also, the asm operands' file+line: without the asm, the tails have no ASM_OPERANDS. So the #line only mattered for the asm.

Test f1: c3 with the #line directives removed.

Let me also reconsider the whole item. Time: let me check.
