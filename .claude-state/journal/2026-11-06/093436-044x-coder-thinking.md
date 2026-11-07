---
ts: 2026-11-06T16:34:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L6PRYTzO0fu0pxVQANRn
---
Now I see c1 assembly:
```
move $5,$4        ; a1 = a0  (72 = 73? here 73→a0, 72→a1? The copy is move a1,a0 → so 73=a0 (source) and 72=a1 (dest)?? insn 4 was (set 72 (reg a0)) → move a1,a0. insn 11 (set 73 (reg 72)) → after global: 73=a0? no...
```
Hmm the assembly: `move $5,$4` = a1 = a0. That's insn 4: 72 = a0 → 72=a1. Then insn 11: 73 = 72 → 73=a0? That would be `move $4,$5` which is absent! So insn 11 was eliminated (copy propagation, 73 coalesced with 72?) But then uses of 73 would be a1. Indeed then-arm uses $5 (a1). Else uses $4 (a0) — from the source a0 directly.

So global-alloc assigned 73=a0 and then regmove/coalescing... whatever.

The bottom line: in c1, the else uses $4 (a0) because 73 (self) was assigned a0.

Now what we need: self in a1 everywhere. In the pinned version, self was 72 (a1) because the copy 73→72? Let's dump the pinned body to compare. Let me create orig body as a candidate in the same harness (splice orig.c) and inspect the greg dump: which regs and conflicts.

Do that now.
