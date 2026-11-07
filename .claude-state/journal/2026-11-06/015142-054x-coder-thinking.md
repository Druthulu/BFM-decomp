---
ts: 2026-11-06T08:51:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YdoKGnKwBNspIr4NkBl9
---
Now I see the orig RTL: the asm_operands insn 134 between the copy and the neg. Combine can't merge across the asm.

So we need a real-C construct that produces an RTL insn between the copy and the neg. Options in real C:
- A `(use)` insn: combine creates those only for death notes.
- A `clobber`/`use` from a `__attribute__`? banned-ish.
- A memory access (load/store) — adds instructions.
- A call — adds.

Hmm, what about **`(void)val;`**? GCC's tree-level optimizer removes it (no RTL).

What about a *statement expression* or a label? A label between the two statements would split the block, blocking combine. E.g.:

```c
} else {
    val = nudge;
    goto skip;
skip:
    val = -val;
}
```
A label creates a code_label between the two sets, making them different basic blocks → combine can't merge. But would the label survive to RTL? A user label that's unused might be deleted by... In GCC, unused labels are removed early? `goto skip; skip:` — the jump is a no-op and gcc may delete both. Let me test: the code would be identical if both are removed; but if the label survives, it splits blocks and the code might still be the same instructions (labels don't emit code). The target has no extra insns, so a surviving CODE_LABEL is fine! It could produce exactly the target (label between move and negu).

Wait, but a basic block boundary at a label: the move is at the end of the previous block and the negu starts a new block. Scheduling may differ, but let's test.

Similarly, a `do { } while (0)` with a body... we tested and it didn't work (gcc removed the loop before combine? or combine crossed).

Hmm, `do { val = nudge; } while (0); val = -val;` — the loop removal happens at tree level (statement expressions), so no label.

A `goto`/label pair: gcc's jump optimizer removes a jump to the immediately following label (`jump` pass runs after combine though; the label might survive until then). At combine time, the label exists → blocks split. Then jump.c deletes the label if unreferenced? If the label is referenced by the goto, and the goto is a no-op jump to the next insn, jump.c removes the jump and the label. The result: the two insns in one block but combine already ran. 

That could work! Let me test:
```c
} else {
    val = nudge;
    goto L;
L:
    val = -val;
}
```
But wait: `goto L; L: ...` — gcc's tree/expand might eliminate the goto early (jump threading at RTL). The RTL for a goto+label: expand emits a jump insn and a code_label. Actually GCC's expand might optimize `goto next; label: stmt` — I think it keeps the jump RTL; the jump optimizer later removes it.

But careful: the target has NO jump insn in the else block. If jump.c removes the redundant jump, fine. Let's test.

Another construct: an empty `if (0) { }`? folded early.

Another: `while (0) { }` between? removed early.

Another: `switch (0) { }`? maybe kept as RTL.

Another: a *nested block with a declaration*? No RTL.

Another idea: a `case` label? no switch.

Let me test the goto/label and a couple of variants. Also consider: instead of a label, make the neg a separate *statement expression* with a local variable:
```c
} else {
    val = nudge;
    { s32 t = val; val = -t; }
}
```
No block boundary.

Let me also consider the `(use)` route: is there any C construct that emits a USE insn? `__builtin_...`? Not in this compiler. `asm` banned.

What about a `volatile` *read* of a variable? That's a load.

The goto/label route is the most promising. Let me test:

c9:
```c
} else {
    val = nudge;
    goto l1;
l1:
    val = -val;
}
```
Hmm, but a label at the end of the else block, followed by the join label — the store follows. The label l1 would be right before the neg. Let me test.

Also test c10: 
```c
} else {
    val = nudge;
    do {
        val = -val;
        break;
    } while (1);
}
```
No.

Let me also test c11: `if (val) {}` no.

Test c9 now.
