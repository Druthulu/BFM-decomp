---
ts: 2026-11-06T05:46:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fLWnAHexBi4V87rdOv9e
---
So the launders only matter for the `andi` source register: target `andi v0,a1,1` — c is in a1, and the call result (v0) is elsewhere.

So `c` must be a separate register from the call result. With the launder, c is forced into a1. Without, cse folds c into the call result (v0).

To keep c separate in plain C: make c a different *mode* (QI) so the copy escapes cse, or make c live across something.

Let me look at the target asm around insn 60 to see the context.

Actually, the pattern `c = func() & 0xFF; if ((c & 1) != 0)` — the target has `andi v0,a1,1`, so the `c & 1` operand is a1 (c) while the call result was in v0.

If c is `u8`: the RTL would be c(QI) = subreg(call result); then `c & 1` = zero_extend(c) & 1. gcc might emit `andi v0,a1,0xFF` then `andi v0,v0,1`? Or fold. Hmm, risky.

Alternatively, the classic moves.md trick: route the copy through an s16 temp:
```c
s16 t = (s16)(func(...) & 0xFF);
c = t;
```
Hmm, that's 2 variables.

Wait, but here the issue is the *mask* (c = call & 0xFF) followed by another mask (c & 1). cse folds the two masks. The launder breaks it.

The comment says: "without it cse folds `(raw & 0xFF) & 1` back onto the raw call result and emits `andi $v0,$v0,1`; the target reads the masked copy, `andi $v0,$a1,1`".

So in the target, the call result goes to v0, then `c = result & 0xFF` copies to a1 (andi a1,v0,0xFF), and `c & 1` reads a1.

Hmm, let me look at the actual asm around insn 58-66 to understand.

Let me disassemble the target.
