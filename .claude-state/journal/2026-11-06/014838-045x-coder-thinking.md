---
ts: 2026-11-06T08:48:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V6Z1oNR5tyn8NYvctEpe
---
Excellent! The cse dump (after cse1) shows the *good* structure:
```
insn 132: (set reg78 (reg77))    ; else: val = nudge
insn 134: (set reg78 (neg reg78)) ; val = -val
```
Wait, this is the cse dump *after* the pass? The .cse dump is printed after cse1. And here the copy is separate and the neg uses reg78. Good — so cse keeps it.

The combine dump shows the *bad* result:
```
insn 124: (set reg78 (reg77))  ; if-branch copy
...
insn 265: (use reg78)          ; ??? this is interesting
...
insn 134: (set reg78 (neg reg77))  ; merged!
```
So combine merged insn 132+134 into `(neg reg77)`, deleting the copy. Note insn 265 `(use (reg/v:SI 78))` — that's a leftover from the asm! Wait no, this is c1 (asm removed)? Let me check: c1.c was created with sed deleting the `!FAKE: keepalive` line — yes, asm removed. But the RTL shows `(insn 265 128 130 (use (reg/v:SI 78)) -1 (nil))` at the start of the else block (label 128) — a USE of reg78 with no effect! That's... hmm, where does that come from? An `use` insn with no code. That could be from a `(void)val`? There's no such thing in c1.

Wait, maybe this dump is from the ORIGINAL TU (with asm)? I passed the p3 scratch TU which was created for c1 (asm removed). Hmm, but the scratch dir p3 might be from the last --keep call which was c1. Let me check the scratch .c for the asm.

Actually wait: the `(use (reg/v:SI 78))` insn 265 sits right after the label 128 (the else block start) and before the neg. This looks like the RTL of the *asm* — GCC models `__asm__("" : : "r"(val))` as `(insn (use (reg val)))`? Actually an asm with no output and a register input is an `asm_operands` insn, not a bare use. But combine might convert it? Hmm, a `(use ...)` insn is what GCC emits for a `USE` note... Actually, the `(use reg)` insn at 265 might be the asm's remains after combine simplified `asm("" : : "r"(val))` — no.

Let me check the scratch file content.
