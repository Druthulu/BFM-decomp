---
ts: 2026-11-06T06:36:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yhqQmJ9VJVRMgmcZmUnZ
---
The output is messy (it's mixing sections from other functions because my awk regex matched across the file after line 20545 — and the function section might be short).

Let me take a targeted approach: print the actual function body RTL from line 20545 to the next ";; Function".

Actually, the key facts I need: why does r73 conflict with v0? And what gives the middle value v1 in mine.

Rather than deep analysis, let me try quick variants:
1. Split `t` into two variables (t for the middle, t2 for the tail index).
2. Make the tail `t = unk2` use a separate variable.
3. Reorder the tail: `D_801D0A3C[((Unkstruct*)a0)->unk2](a0);` (no temp).

Since the target has ONE t (pinned $2) used in both places, splitting changes the codegen but might match.

Actually — think about what the pin does here: `register s32 t __asm__("$2")` forces t into $2 for the whole function. Lever-free, t is a global allocno conflicting with v0 (due to the call at the end), so it takes $3.

Hmm, "conflicts v0" — if t conflicts with v0, then giving t $2 in the target was only possible because it's a hard reg (pinned).

So a MATCH requires making t not conflict with v0, or making another allocno take v0 first...

Wait, actually: if t conflicts with v0, then t CAN'T be in v0 in plain C. But the target has t in v0! Contradiction? No: the pin forces it, and the register allocator allows a conflict for a hard-reg variable (the variable is *defined* to be there; the conflict is real in the RTL because the pseudo is live across a point where v0 is live — but if the pseudo IS v0, the "conflict" is vacuous... no, it would be a real conflict if v0 is live at the same time).

Hmm, so in the target, t is live across a call where v0 is also live? Let me check the target asm: the tail is
```
lhu v0,2(a1)     ; t = unk2
sll ...
lw v0,0(at)      ; table load
jalr v0?
```
Hmm, the target uses v0 for the table address computation and the call. Let me look at the target asm for this function. Let me dump the target .s (the src TU). Since orig scores 0, the src .s is the target.

Let me do that — it's the fastest way to understand.
