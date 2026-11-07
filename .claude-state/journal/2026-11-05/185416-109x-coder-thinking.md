---
ts: 2026-11-06T01:54:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9aOL1uArYGkBeSj05LNr
---
w15: store then sh inside a do-while → score 2 (ORDER), 138 ins. Same as v1.

So all shapes that emit the store before sh avoid the merge but have the wrong final order.

Hmm, w1/w2 (do-while) still merge.

Key insight: we need the store NOT last at jump2 but sh;sw order in the final. Since sched1/sched2 keep source order for these two stores, the source must be sh;sw. So the merge must be broken by something else.

Let me look at the *dec* block once more. What if dec's store is not the last insn before its jump at jump2 — e.g., if dec's `unk1C--` were written in a way that emits an extra insn after the store that gets removed before final? For instance, dec as:
```
t = unk1C;
unk1C = t - 1;
```
emits lw; addiu; sw; j. Same.

What if dec's block ends with a *call* after the store? No, target doesn't.

Hmm, what if the dec block's jump is not simplejump_p because it's a `return` that's conditional? Target: j.

Let me reconsider: maybe the merge in the target was prevented by the zero block's store being followed by a *jump* at jump2, and the jump WAS deleted at jump2 (not the first pass) because the zero block's trailing jump was NOT a jump-to-next at the first pass. When could that happen? If at the first pass, the return label was not immediately after the zero block's jump, but at jump2 it was. Is there anything that changes the return label's position between the first pass and jump2? The epilogue label is placed at the end during expansion. Hmm.

OR the zero block's trailing jump is a jump to a *different* label (not the return label) that gets threaded to the return label by jump2. For example, a `goto L;` where `L:` is a user label at the end, followed by the return label. At the first pass, the jump to L is a jump-to-next if L is the next insn → deleted. Hmm.

What if the user label L is at the end but the return label comes AFTER it (compiler-generated epilogue label is after user labels)? Then the jump to L is to the next insn (L) → jump-to-next deletion at the first pass. Deleted.

What if the label L is placed *before* the zero block's store? e.g.:
```
zero:
   ...
   goto done;
done:
   unk1C = 0x1D;   // ??? 
```
No, the store is last.

Hmm, what if the original C is:
```
zero:
    ...
    unk1C = 0x1D;
    goto done;
done:
    ;
}
```
The `done:` label right after the jump → the jump is to next → deleted at first pass. Same.

What if `done:` is followed by a statement that emits no code but is not a note, e.g., a nested block? Blocks emit notes.

OK, let me think about the *first jump pass's* jump-to-next deletion more carefully. I couldn't find it in jump.c, yet it happens. Maybe it's in `cse.c`'s `delete_dead_from_cse`? No, the jump is gone in the .jump dump (before cse).

Let me look at jump.c line 1000-1050 for the simplejump "reallabelprev == temp" case. Line 1039: `reallabelprev == temp`. Let me read that block.
