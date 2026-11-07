---
ts: 2026-11-06T16:34:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b1ZiH6EKb4J1ws5kTz4W
---
Now it's clear! In cse1, the source has TWO pseudos: 73 = the pointer-typed `self` (created by the cast, used in address computations) and 72 = ... wait, insn 4 sets 73 from a0, and insn 11 sets 72 from 73. So the C `self = (Unkstruct*)arg0;` created pseudo 73 (pointer), then using `self` in the condition/stores created 72? Hmm, actually insn 11 is a copy from 73 to 72 — probably from the `flag = self->unkAA`? no.

Hmm, likely: 73 is the pointer pseudo (self, Pmode) and 72 is a copy created when... the cast? Let me look at the .rtl (before cse) to see.

Actually, the key: block 2 (else) uses 73 (the pointer pseudo) as base, block 1 uses 72. And 73 got a0 in global-alloc.

Let's look at the rtl dump (initial expand).
