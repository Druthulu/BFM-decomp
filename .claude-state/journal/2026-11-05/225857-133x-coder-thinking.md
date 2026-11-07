---
ts: 2026-11-06T05:58:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_irXU7G9ob7SKBgn0sYRX
---
Time 22:58:43. Item 4 started ~22:52 → 6.7 min. Still need ~13 more minutes.

Hmm, this is a lot of wall time. Let me consider: maybe the "20 min" is about effort, and my tool-call time is compressed. But to be safe, I should keep working on item 4 until ~23:12.

Let me continue trying to crack it. Let me think about the *pin* side more, since maybe I can at least improve the best score below 10, or find a crack.

Actually, let me reconsider the problem from scratch. Maybe there's a cleverer restructure that produces the target asm without needing opacity.

The target's flow:
```
cc = (s16)func_8012BD3C(...);
one = 1;
if (cc != one) goto second;
call func_8012D624;
if (cc == one) goto rejoin;
second: ...
rejoin: ...
```

What if the source were:
```c
if (cc == one) {
    func_8012D624(...);
}
if (cc == one) goto rejoin;
second: ...
```
gcc would fold the second test (cc == one is known in the first block? no — after the if, cc == one only on the path where the if was taken; but the if's body doesn't change cc, so on the fall-through cc != one; the second test `cc == one` → false → falls to second. Hmm, gcc would simplify.

Hmm.

What if the structure is a loop:
```c
do {
    if (cc != one) break;
    func_8012D624(...);
} while (cc == one);
goto rejoin;
```
A do-while with the condition `cc == one` — the loop condition is evaluated after the body, and gcc can't fold it across the loop backedge? Hmm, it could.

Actually, the target's `beq s1,s2, rejoin` after the call, then `second:` — a do-while(cc == one) would produce `bne s1,s2, exit; j loop_start` — different.

Hmm.

What about a `while` loop? `while (cc == one) { call; break; }`? Weird.

OK, let me try a different tactic: search moves.md/cookbook for this exact wall (flow-known / fold of a redundant test). Maybe there's a known lever.

moves.md line 186: "WALL flow-known-nonzero — flow: n is provably 16/20, so the 2nd/3rd 'if (n != 0)' tests fold away; the asm keeps n opaque, all 3 tests stay (G14)". And line 188: "MATCH: the launder on the trip count n -> n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20})".

So in func_8017D73C, `n = (s16)n` at both sites worked. Why didn't g1 (`cc = (s16)cc`) work here? Because there, the knowledge "n is 16 or 20" came from the *value flow* (a comparison earlier), whereas here the knowledge "cc == 1" comes from the *branch we're on*. A real 2nd set after the branch re-establishes cc's value from the current cc (known 1) → still known 1.

In func_8017D73C, the 2nd set was probably placed *before* the tests, breaking the value-flow chain.

Hmm, so what if we place a 2nd set of cc BEFORE the first test? E.g.:
```c
cc = (s16)func(...);
cc = (s16)cc;      // real 2nd set before the test
one = 1;
if (cc != one) goto second;
...
```
That doesn't change the branch knowledge.

Hmm.

OK, what if the first test uses a *different* variable that we can't relate to cc? For example:
```c
s16 cc;
s32 t;
cc = (s16)func(...);
t = cc;               // t is a copy
one = 1;
if (t != one) goto second;
func_8012D624(...);
if (cc == one) goto rejoin;
```
gcc knows t == cc.

What if t is a *different width* so the knowledge is lossy? E.g., `t = (s16)cc` — same. `t = cc & 0xFFFF` — the k10 trick.

Hmm, what if `t` is `u8`? `t = (u8)cc;` then `if (t != one)` — the branch gives (u8)cc == 1, which does NOT imply cc == 1! So the second test survives! And the cost is an `andi` for the (u8) conversion... unless the value is already used as a byte somewhere.

Hmm, the target's first test is `bne s1,s2` where s1 = cc (s16 value). If we compare (u8)cc, we'd need `andi` → extra.

Unless the conversion is free: if cc were already a u8 variable... but then `cc = (s16)func(...)` with cc u8 would truncate (andi). Hmm.

Wait — what if we keep cc as s32 and write the first test as `if ((u8)cc != one)`? gcc emits `andi` then compare. Extra instruction.

Hmm, but maybe gcc can use `andi` and fold the compare? No.

OK, what if we use a *signed* trick that needs no instruction: the first test `if (cc != one)` where cc is s16... no.

Alright. Let me consider the possibility that this item is genuinely uncrackable and spend the remaining time efficiently. I'll do a few more experiments to satisfy the budget, then write up.

Let me try a couple of "structural" variants that might change the CFG knowledge:
s1: the first test as `if (cc - one != 0)`.
s2: the first test as `if (cc != one) goto second;` with a label-based structure.
s3: use `switch (cc)` for the first test? `switch (cc) { case 1: call; ...; break; default: goto second; }` — gcc's switch might not propagate cc == 1! And the asm could be beq/bne. Let me try:

```c
switch (cc) {
case 1:
    func_8012D624((void *)a0, 0xC0, 0x30);
    if (cc == one) goto rejoin;
    break;
default:
    goto second;
}
```
Hmm, a switch with 2 cases might compile to beq + b. The target's first test is `bne s1,s2, second` — with the switch, gcc would emit `beq s1,s2, case1; j second`? Hmm, maybe. And inside case 1, `if (cc == one)` — gcc knows cc == 1 from the switch? It might.

Risky but worth a try.

s4: the first test as `if (cc == one) { call; } else goto second;` then the second test — same.

Let me try s3 and a couple more.

Actually, let me try a much simpler idea: what if the second test is on `one` compared to `cc` but with cc *reloaded from the function's argument*? no.

Let me try s3 (switch).

Also, let me reconsider: maybe the target's second test isn't redundant in the original because the call `func_8012D624` might modify `cc`'s *source*: `func_8012BD3C` returns a value stored in cc. Hmm no.

Let me just try the switch.
