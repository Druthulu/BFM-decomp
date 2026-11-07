---
ts: 2026-11-06T05:52:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pub2LOWLWwTa1dMLwDXg
---
With the launder gone, mine merges the first call:
```
mine:
20 sra v0,v0,0x10        ← cc = (s16)call
21 li s1,1? (hmm, mine has one in s2 per the pairs)
22 beq v0,s2, ...
```
Target:
```
21 sra s1,v0,0x10        ← cc in s1
23 bne s1,s2, 1898
24 move a0,s0
25 li a1,192
26 jal func_8012D624
27 li a2,48
28 beq s1,s2, ...
```
Hmm wait, the target has:
```
20/21 sra s1,v0,0x10
22 ? 
23 bne s1,s2,1898   (if cc != one goto second)
24-26 call func_8012D624 (in the delay... no)
27 beq s1,s2,18c8   (if cc == one goto rejoin)
```
Hmm, that's odd: bne then the call then beq? The target's structure: 
```
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
```
The target compiled: `bne s1,s2, second` — but the call is in the delay slot region? Let me look at the actual target asm.

Let me dump the target function fully.

But first: why does mine lose the call? Mine's diff at [22:23] shows mine `beq v0,s2, 18a4` and target `bne s1,s2, 1898; move a0,s0; li a1,192; jal; li a2,48; beq s1,s2,18c8`. So mine's call `func_8012D624` is... where? Maybe mine has it but the diff alignment is off (mine 89 vs target 95 = 6 fewer). Mine lost 6 insns: the `move a0,s0; li a1,192; jal; li a2,48` (4 insns) plus 2 more.

Hmm! Maybe the launder removal made the second `if (cc == one)` fold: with the launder, `cc` is a fresh value after the asm, so `if (cc == one)` is a real test. Without, cse knows cc == (s16)call_result and the first `if (cc != one)` already tested it — so the second test is redundant and folds! That removes the call and the branch.

Look: the source:
```c
cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);
one = 1;
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
<launder>
if (cc == one) goto rejoin;
second:
...
```
Semantically: cc == 1 → call → then cc == 1 (unchanged) → goto rejoin. So the second test is always true! gcc can prove it without the launder (cc is unchanged). The launder made cc opaque so gcc couldn't.

So the launder is essential for keeping the second test and the call's position. This is a "fold-condret-merge"-like wall? Or can a real 2nd set of cc do the job?

The launder re-sets cc to an opaque value. A real 2nd set like `cc = (s16)cc;` — value-preserving and a real set. gcc might still know cc == 1. Hmm, but the launder's purpose is to make cc "unknown".

Wait, actually the launder is `__asm__ __volatile__("" : "=r"(cc) : "0"(cc))` — an asm with an output. gcc doesn't know the value after it. A real C 2nd set `cc = (s16)cc;` — gcc knows the value is unchanged (sign-extend of an s16-range value). So the second test would still fold.

Hmm. So we need cc to become unknown. In plain C, what makes a value unknown? A memory load (store/reload), a function call, volatile.

A function call: could we restructure so cc is read after a call? E.g., store cc to a local and read it back? Adds instructions.

Hmm, but wait — the target has the call `func_8012D624(a0, 0xC0, 0x30)` between the two tests. cc is a *caller-saved* register (s1 in the target), and the call clobbers caller-saved regs. So after the call, cc (in s1) must be... s1 is $17, callee-saved! The target keeps cc in s1 ($17). Hmm, so the call doesn't clobber it.

Hmm, in the target cc is in s1 ($17). So after the call, cc is still in s1. And the second test `beq s1,s2`.

OK. So how do we keep the second test in plain C? The compiler must not know cc == 1. 

What if cc is declared `volatile`? That's a barrier lever — not allowed.

What if cc is read from memory after the call? e.g.:
```c
s16 cc16;
cc16 = (s16)func_8012BD3C(...);
one = 1;
if (cc16 != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc16 == one) goto rejoin;
```
Same.

Hmm. But actually, maybe we don't need the second test to be "unknown" — maybe we can restructure the control flow to keep the same instructions. Let's look at the target asm to see the actual flow.

Let me dump the target.
