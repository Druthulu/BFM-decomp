---
ts: 2026-11-06T05:54:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3FFXi144NC2bvQi5tB1c
---
All still 24/89 — the 2nd sets fold and the second test is deleted.

So a value-preserving 2nd set doesn't work here. The only way is opacity.

Hmm, what about a *different value* that gcc can't prove? E.g., after the call, set cc to a value that gcc can't know but which is guaranteed 1 at runtime... impossible in plain C without opaque ops.

Hmm, unless... we can restructure so the second test is on a *reloaded* value. What if `cc` is stored in a local array that the call could modify via a0? The call takes a0; if cc were part of the struct at a0 (a field), gcc would reload after the call. But that adds lw/sh.

Actually wait — let's look at the target's second block:
```
1898 second:
189c li a1,256
18a0 lhu v0,18(v1)
18a8 addiu v0,v0,2048
18ac jal func_8012BD3C
18b0 sh v0,18(v1)
18b4 bne v0,s2, 18c8
```
So the second block recomputes func_8012BD3C and tests it against one (s2). Note: `bne v0,s2` — v0 is the raw call result, compared to 1. So in the second block, the test `func_8012BD3C(...) == one` uses the raw result (no (s16) cast!). The source is `if (func_8012BD3C(a0, 0x100, 0x9000) == one)` — comparing the raw s32 result to 1. OK.

And the first block's `cc` is the (s16) cast.

Hmm. So the second test in the first block (`beq s1,s2`) compares cc (s1) to one (s2).

Idea: what if we could make the second test compare something gcc can't fold, like a *fresh* variable that we know is 1 but gcc doesn't:
```c
cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);
one = 1;
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
```
What if `one` is reassigned between? `one = 1;` again after the call → a `li s2,1` (extra instruction, and the target has only one li s2,1). No.

Hmm.

What if `cc` is a `s16` variable and we use `if ((u16)cc == (u16)one)`? gcc folds.

OK. Let me consider: is the target's second test maybe not from a C `if` but from something else? The `beq s1,s2, rejoin` followed by `move a0,s0` (the second block's first insn stolen into the delay slot). Hmm.

Let me consider the possibility that the launder's effect can be achieved by making `cc` live across the call in a *callee-saved* register AND reloaded... no.

Hmm, what if we make the call `func_8012D624` be a call through a *pointer* that could alias? No.

What if we make `cc` a `s16` local whose address is passed to `func_8012D624`? The call signature is (void*, s32, s32). We can't pass &cc without changing the call.

BUT: what if the first argument `(void *)a0` could be a pointer to cc? gcc's alias analysis: cc's address is never taken → no alias. Unless we take cc's address somewhere, e.g., `s16 *pcc = &cc;` and use `*pcc`? gcc would optimize it away (known local).

What if we make the address escape in a way gcc can't track: e.g., `s16 cc; ... ; func_8012D624((void *)((a0 == (s32)&cc) ? a0 : a0), ...)`? That takes the address but folds to a0.

Hmm.

What if we pass `(void*)&cc` as the first argument? Then the call gets the wrong argument → different asm (move a0,sp instead of a0,s0). No.

OK — what if cc is a *static* (file-scope) variable? Then a call could modify it (the callee might reference it? no, it's static to this TU... but gcc knows the callee can't see it if it's static and not address-taken). If it's non-static (global), gcc must reload after calls. But then the code would have sw/lw.

Hmm, but wait: how many extra instructions? A global cc would be: `sw cc, 0x...` after the call result, then `lw` for each use. That's several extra instructions. Target has 95; mine (with launder) is 95. So no room.

Therefore: the launder is load-bearing and can't be replaced in plain C. This item is a WALL (tag: flow-known-value / "flow-known-nonzero" or "fold-condret-merge").

But wait — I should also check the pin part; maybe the pin can be cracked, giving a PARTIAL? No — PARTIAL means win.c scores 0 keeping only those levers. Since the launder can't go, we can't get PARTIAL either (PARTIAL requires score 0).

Hmm, actually PARTIAL:<kinds still kept> means the win.c scores 0 while keeping some of the row's levers. If we can't remove the launder, we can't score 0 at all → WALL.

Let me try a few more things before declaring WALL:
1. Maybe the second test can be preserved by restructuring the code so the value is genuinely unknown — e.g., swap the order: test, call, test where the second test is on a *different* call's result? No.

2. What if we use `goto` to make the second test a loop condition? Hmm.

3. What if the first test is on a *different* value so gcc can't infer cc == one? E.g.:
```c
cc = (s16)func_8012BD3C(...);
one = 1;
if ((cc & 0xFFFF) != one) goto second;   // gcc knows cc & 0xFFFF == cc? for s16 cc, yes (known range)
```
Hmm, if cc is s16 and the comparison is `(cc & 0xFFFF) != one`, gcc knows (s16)cc & 0xFFFF == (s16)cc for the range... hmm, for negative cc it's not equal, but gcc's range analysis: cc ∈ [-32768,32767]; cc & 0xFFFF = cc only if cc >= 0. gcc might not know. Then the test would be `andi` + compare (extra instruction) and the implication cc == one wouldn't be established (since the masked value could be one while cc is -65535... no, cc is s16). Hmm, gcc's value-range might still derive it.

Let me try: first test `if ((cc & 0xFFFF) != one)` — this changes the asm (adds andi). No.

4. What if the second test is `if (cc == one)` but the call is placed between the tests in a way that gcc's flow can't track because cc is in a register that the call clobbers? cc is in s1 (callee-saved). If cc were in a *caller-saved* register, the call would clobber it and gcc would need to reload... but there's no reload in the target (s1).

Hmm.

OK, let me look at n2 (pin removed, launder kept) = 15, 94 ins. Let me see the diff — maybe the pin is crackable, which would be a useful finding even if the item is a WALL (best would improve? no, WALL best = lowest lever-free score; n2 keeps the launder so it's not lever-free).

Hmm. For the WALL, the best lever-free score is what matters: n1 = 25 (89 ins), g1-g4 = 24 (89 ins). So best = 24.

Let me do a few more tries to see if any lever-free body gets closer:
- Try `cc` declared s16.
- Try `one` declared differently (the pin removal).
- Try the second test written differently.

Actually, let me try removing the pin only in the g-variants and see the combined score. The pin removal in n2 cost 1 instruction (94 vs 95). Let me check n2's diff — maybe it's just the s2/s1 swap.

Let me look at n2's diff.
