---
ts: 2026-11-06T05:53:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6R9OKTTr3BZA5IGuVxg8
---
Now the target's structure:
```
1870 sll v0,v0,0x10
1874 sra s1,v0,0x10      ← cc = (s16)call
1878 li s2,1             ← one = 1
187c bne s1,s2, 1898     ← if (cc != one) goto second
1880 move a0,s0          (delay slot)
1884 li a1,192
1888 jal func_8012D624
188c li a2,48            (delay slot)
1890 beq s1,s2, 18c8     ← if (cc == one) goto rejoin
1894 move a0,s0          (delay slot — but dead, it's the second block's a0 setup)
1898 second: ...
```
So the target has BOTH tests. In the target, after the call, `beq s1,s2` — cc is still in s1 and equals one (since it was tested equal before the call and the call doesn't modify s1). So gcc COULD have folded it, but it didn't (because the launder made cc opaque).

So we need to prevent the fold. In plain C, the compiler knows cc == 1 on that path (the bne jumps away otherwise). So it will fold.

Unless... the second test is on a value that gcc can't prove. Hmm.

Idea: make cc a *memory* variable (local) that could be modified by the call:
```c
s16 cc;
cc = (s16)func_8012BD3C(...);
one = 1;
if (cc != one) goto second;
func_8012D624(...);
if (cc == one) goto rejoin;
```
If cc is a stack variable whose address is not taken, gcc keeps it in a register and still knows. Hmm, but if the call could modify it... gcc knows the address isn't taken → no.

Unless we take the address: `s16 cc; ... func_8012D624(a0, 0xC0, 0x30);` — the call takes (void*)a0, which could alias &cc if a0 pointed to it. But cc's address is never taken, so gcc knows.

Hmm, what if we pass &cc to the call? That would change the call args.

What if cc is a global? Then the call could modify it. But then the code would load/store cc from memory (extra instructions). The target has cc in a register.

Hmm.

Wait — maybe there's a different structure that produces the same instructions. What does the target's source look like? Let's think:

```c
cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);
one = 1;
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
second:
...
```
Semantically the second test is always true. So the original source might have been something else that gcc compiled this way — e.g., the original code might call a function that returns something, or cc might be recomputed.

Hmm, what if the source's second test is on a *fresh call*? Like:
```c
if (func_8012BD3C(a0, 0x100, 0x9000) == one) { ... }
```
No, that would be another jal.

Hmm. So the original source likely had the launder-equivalent asm (this is decomp code; the launder was added to force it). The task says: produce a lever-free body scoring 0. If the second test can't survive in plain C, it's a WALL.

But wait — maybe there's a plain-C trick: make the call *appear* to modify cc. If cc is a local variable whose address is passed to a function... 

What if we declare `cc` as a local `s16` and pass its address to the call? No.

Hmm, what about making `cc` volatile? Forbidden (barrier).

What about a *pointer* to cc that escapes? E.g., `s16 cc; s16 *pc = &cc;` and use `*pc` — if gcc can't prove pc doesn't escape... it can.

Hmm. What if we take the address and store it somewhere gcc can't track? Extra instructions.

OK, but hold on: maybe the *pin* part is the real lever and the launder can be replaced by a real 2nd set that also makes cc opaque. What real C operation makes a value opaque without instructions? 

Actually — a **memory round-trip that gcc keeps in a register**: no.

Hmm, what about the fact that `cc` is (s16) of the call result. If we declare `cc` as `u8` or another width, gcc still knows.

What about `cc = (s16)func(...); ... if ((s16)cc == one)`? Still known.

Hmm. What if the second test compares against a *different* variable that aliases one? Like `if (cc == one2)` where one2 = 1 (another variable)? gcc's cse would know one2 == 1 and cc == 1 → fold.

Hmm.

What if the *call* is between: `func_8012D624((void *)a0, 0xC0, 0x30);` — the call's arguments include `(void*)a0`. If gcc thinks the call could modify `one` (the variable 1)? one is a constant stored in a variable, pinned to s2 in the target. Without the pin, `one` might be a constant (li). Hmm.

Wait — in the target, `one` is a variable (pinned $18) holding 1, used in 3 comparisons (`cc != one`, `cc == one`, and `func_8012BD3C(...) == one`). In n1, `one` became... let me check: the naive n1 diff showed `li s1,1` and comparisons with s1. So `one` is a variable in s1.

If `one` were a plain constant (no variable), gcc would emit `li v0,1` and compare. The pin made it a variable.

Hmm.

Let me think about the second test differently. What if the source uses `cc` in a way that gcc can't propagate because the call might modify `cc` — e.g., if `cc` is a *global* variable? Then the code would be `sw cc, ...` before and `lw` after — extra instructions.

Unless the global is... hmm.

Actually, WAIT. Let me reconsider: maybe the second test isn't `if (cc == one)` in the original source. Maybe it's something else that compiles to `beq s1,s2`. E.g., a `while` or a duplicate condition.

Hmm, but the target literally has `beq s1,s2` where s1=cc and s2=1.

What if the source's second condition is `if (cc == 1)` written with a *different* variable that also holds 1? gcc would still fold.

Hmm, what if it's `if (func_8012D624's effect...)`? No.

OK, maybe I should consider that the launder here can be replaced by a *different* anti-fold: make `cc`'s value not provably 1 by changing the FIRST test's structure. For example:

```c
cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);
one = 1;
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
```
If the first test were `if (cc != one) goto second;` — gcc knows cc==one on the fall-through.

What if the first test is written as a switch or a comparison on a *copy*? Same.

What if the call `func_8012D624` is called with an argument that could modify cc? No.

Hmm, what if we make the second test depend on a value that gcc thinks might have changed: e.g., `if (cc == one)` where `cc` is re-read from a variable that the call could modify via a pointer passed to it. The call is `func_8012D624((void *)a0, 0xC0, 0x30)` — a0 is the function argument (an unknown pointer). If `cc` were stored in memory reachable from a0... gcc can't know. But cc is a local; its address isn't taken.

What if we make cc an element of a local array and take the array's address... extra.

Hmm.

OK, let me look at the OTHER 6 instructions more carefully: mine lost `move a0,s0; li a1,192; jal; li a2,48` and `beq`... Actually mine lost 6 insns total. Let me get mine's asm to see what it did.

Let me dump n3's asm (or n1's). From the diff, mine's flow:
```
20 sra v0,v0,0x10
21 li s1,1 (one)
22 beq v0,s2, 18a4     ← hmm, s2?
```
Wait, in n3 the pin is kept, so one is $18/s2. And cc is in v0. `beq v0,s2, 18a4` — if cc == one goto 18a4. Hmm, that's inverted from the target's `bne s1,s2, 1898`.

Mine's structure: since the second test always holds, gcc turned:
```
if (cc != one) goto second;
call;
if (cc == one) goto rejoin;
second:
...
```
into:
```
if (cc == one) { call; goto rejoin; }
second: ...
```
That's a different (shorter) structure: `beq v0,s2, Lcall; ... second ...; Lcall: call; goto rejoin`. Hmm, mine has 89 ins.

So without the launder, gcc simplifies the CFG: it moves the call into a conditional block.

To keep the target's shape, we need the second test to be opaque.

Options in plain C: make cc's value come from something gcc can't track. 

IDEA: what if cc is computed from the call result via a *second* call? No.

IDEA: use a **local variable whose address is taken** and pass it to a function that could modify it. The call `func_8012D624(a0, 0xC0, 0x30)` — if we pass `&cc`? No, args are fixed.

Hmm, but what if `cc` is a *field* of the struct pointed to by a0? E.g., `((Unkstruct_800B5CB8 *)a0)->unkXX`? The call takes a0, so gcc must reload the field after the call! That would add lw/sh instructions though.

Hmm, unless the field load is already there... no.

IDEA: Use the fact that `func_8012D624` is declared `void func_8012D624(void*, s32, s32)`. If cc were a global, gcc would reload. Extra.

Hmm, let me think about whether the target's second test could come from a *different source structure* that doesn't require opacity. For example:

```c
if (cc != one) goto second;
func_8012D624(a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
second:
```
What if instead the source is:
```c
if (cc == one) {
    func_8012D624(a0, 0xC0, 0x30);
    goto rejoin;    // no test
}
second:
```
That gives mine's shape (shorter). The target has an explicit second test.

So the original code really had a second comparison that the compiler couldn't fold, meaning cc was opaque (asm or volatile or a memory read).

Since we can't use asm/volatile, maybe a **memory read** is the only way — but that adds instructions.

Hmm, unless... the second test reads a *different* value that happens to be in the same register. E.g., what if `cc` is a `s16` variable and the test is `if ((s16)cc == one)`? Still known.

Wait, maybe the trick is the opposite: make the *first* test opaque so gcc can't prove cc == one on the fall-through. If the first test is on a *copy* of cc that gcc can't relate... e.g.:

```c
s32 c1 = cc;  // ?
if (c1 != one) goto second;
```
gcc knows c1 == cc.

What if the first test is `if (cc != 1)` and the second is `if (cc == one)` where one is a variable? gcc knows one == 1 (it's assigned 1)... unless one is assigned from something unknown! `one = 1;` is a constant.

Hmm, what if `one` is a variable assigned from a function call? No, extra.

Hmm, what if the comparisons are `cc != one` and `cc == one` where one is *volatile*? Forbidden.

OK, let me look at the possibility that the target's shape can be reached by a different control structure that yields the same instructions. The target:
```
187c bne s1,s2, second
1880 move a0,s0     (delay)
1884 li a1,192
1888 jal func_8012D624
188c li a2,48       (delay)
1890 beq s1,s2, rejoin
1894 move a0,s0     (delay — second block's a0 setup stolen)
1898 second:
```
Note 1894 `move a0,s0` is the *second block's* a0 setup, stolen into the beq's delay slot.

So the target has two branches. Mine has one branch + a jump.

Is there a C structure that yields two branches? E.g.:
```c
if (cc == one) {
    func_8012D624(a0, 0xC0, 0x30);
    if (cc == one) goto rejoin;
}
```
Here the inner test is inside the if — gcc knows cc == one → folds → goto rejoin. Mine's shape.

What if the inner test is `if (cc != 0)`? No, target compares to s2.

Hmm.

OK, so this looks like a genuine "fold-condret-merge"-style WALL: flow knows cc == one and deletes the second test. The launder (asm) prevented it. The wall tag could be "flow-known-nonzero" or "fold-condret-merge" (both in walls.txt? "flow-known-nonzero" is in moves.md line 186; walls.txt doesn't list it. walls.txt has "flow-unused-result". Hmm.)

Before declaring a WALL, let me check the pin part separately: n2 (pin removed, launder kept) = 15, 94 ins (1 missing). So the pin removal costs 1 instruction. Let me see n2's diff — maybe it's easier to fix.

Actually, the task requires BOTH levers gone. If the launder can't be replaced, it's a WALL. But let me try a few things:

1. Make cc `s16` (it's already s32 = (s16)cast). Hmm.
2. Try `cc = (s16)func(...); if (cc != one) goto second; func_8012D624(...); if ((s16)cc == one) goto rejoin;`
3. Try making the second test `if (cc == one)` with one recomputed: `one = 1;` after the call? That's a real assignment (li) — extra instruction. Hmm, but maybe the target has `li s2,1` only once. So no.

4. What if the call is declared with a *non-void* return that we use? No.

5. What if `cc` is passed to the call? No.

6. What if we make cc a `u8`? Then `(s16)cc == one`... gcc knows.

Hmm, what about making the second comparison use a *different* expression that gcc can't fold, like `if ((cc & 0xFFFF) == one)`? For s16 cc in [-32768,32767], cc & 0xFFFF differs from cc for negatives... but cc == 1 here. gcc knows cc == 1 → (1 & 0xFFFF) == 1 → folds.

What about `if (cc == (one & 0xFFFF))`? folds.

Hmm.

Let me look at the target's *pin* role: `one` = $18/s2. In n2 (pin removed, launder kept), score 15 with 94 ins. Let me see that diff to understand the pin's contribution.

Actually — hold on. Maybe there's an entirely different approach: keep the launder's *effect* (opaque cc) by using a **function call that returns the value**? No.

What about the fact that the launder is `__volatile__`? The volatile asm can't be removed. Hmm.

Let me look at what other shards did for "flow-known" walls. moves.md line 186: "WALL flow-known-nonzero — flow: n is provably 16/20, so the 2nd/3rd 'if (n != 0)' tests fold away; the asm keeps n opaque, all 3 tests stay". And line 188: "MATCH: the launder on the trip count n -> n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20})". 

Interesting: `n = (s16)n` was a real 2nd set that kept the tests. But in our case, `cc = (s16)cc` doesn't change the *knowledge* — gcc still knows the value. In that case (func_8017D73C), the value n was provably 16/20, and `n = (s16)n` made it... hmm, how did that help? Maybe because the 2nd set changes the RTL so flow's "known nonzero" doesn't apply (the value becomes a different pseudo with no known range? No, (s16)n preserves the value).

Hmm, the note says "the launder on the trip count n -> n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20}); the 2nd/3rd 'if (n != 0)' tests survive". So `n = (s16)n;` DID keep the tests! Why? Because after the 2nd set, gcc's flow analysis... hmm, maybe the sign-extend makes the value's range unknown to the specific optimization (the "known nonzero" is a REG_NOTE from a previous insn; a re-set creates a new value and the note doesn't carry).

Let me try `cc = (s16)cc;` after the call in our case! It's a real 2nd set. If it makes gcc forget cc == 1... Actually gcc's flow analysis recomputes known values per insn. A `cc = (s16)cc` set where cc is known 1 → the new cc is still known 1. Hmm, but maybe the REG_EQUAL/known-value propagation doesn't cross the second set.

Let me just TRY it. Also try `cc = cc + 0;` (folds), `cc = (s32)(s16)cc;`.

Let me generate variants of n3 (pin kept, launder removed) with a real 2nd set at the launder site:
g1: `cc = (s16)cc;`
g2: `cc = (u16)cc;`
g3: `cc = cc & 0xFFFF;`
g4: `cc = (s16)(cc + 0);`
g5: `cc = cc;` (deleted)

Let me test.
