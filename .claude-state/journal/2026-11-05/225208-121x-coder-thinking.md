---
ts: 2026-11-06T05:52:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ditx4jTKXl5Sqzde0T8T
---
The target has `s3` (a callee-saved register) used for `hold`, and `s2` for the constant 1 (`one`). Mine lacks s3 (frame 48 vs 56) — because the pin `one`=$18 reserves $18/s2 and forces `hold` into s3.

Wait: target uses s2 for `one` (the constant 1, pinned) and s3 for `hold`. Mine: `hold` in s2 (addiu s2,v0,256) and `one` in s1 (li s1,1).

Hmm interesting: mine uses s1 for one, s2 for hold; target uses s2 for one, s3 for hold. And mine has one FEWER callee-saved reg (frame 48 vs 56).

The pin forces `one` into s2 and `hold` into s3. Lever-free, `one` goes to s1 and `hold` to s2.

Hmm, and mine is missing instructions at 23-26: the target has
```
bne s1,s2, 1898
move a0,s0
li a1,192
jal func_8012D624
li a2,48
```
That's the call `func_8012D624(a0, 0xC0, 0x30)` — mine has it elsewhere (the diff says mine[20:23] vs target[21:29]). Actually mine has the call too but scheduled differently (mine at insns 24-... hmm, the diff shows "replace mine[20:23] target[21:29]" with mine having sra/li/beq and target having sra/li/bne/move/li/jal/li/beq).

So mine is 89 ins vs target 95: 6 insns missing. Hmm, mine must have eliminated something. Wait, the diff is confusing because of the shift.

Let me get the full target and mine asm to compare. Let me dump mine (n1) and the target.

Actually, the missing 6 instructions: maybe the launder removal caused cse to merge `cc` (the call result) with something, eliminating code? The launder was `__asm__ __volatile__("" : "=r"(cc) : "0"(cc));` after `cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);`.

Let me isolate: n2 = pin removed only (launder kept); n3 = launder removed only (pin kept).
