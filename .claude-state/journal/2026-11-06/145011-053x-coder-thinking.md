---
ts: 2026-11-06T21:50:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jxrkFWvtrh8IddKJouGv
---
Not directly relevant. Let me instead check whether the copy survives cse in w2 by examining the .cse dump for two adjacent insns: one setting a reg from another reg (reg:SI X = reg:SI Y) near the compare of 1.

Let me grep the cse dump for "beq" isn't there (RTL). Let me print the RTL of the block around the `one = 1` (const_int 1) insn.

Simpler: grep -n "const_int 1" in w2.i.cse and look near.

Actually, let me do a decisive experiment instead: put a block boundary that jump1 can't merge between the copy and the compare, using a construct with no runtime cost... Is there any? An `if` with an empty body gets deleted. A label + goto: 
```
iv2c = iVar2;
goto L;
L:
one = 1;
if (iv2c != one) ...
```
jump1 will delete the goto and merge. 

A `switch(0)`? deleted.

Hmm. What about a *loop*: `do { ... } while (0)` merged as discussed.

What about `while (cond) { ... }` where cond is a variable that's... no.

OK, different approach entirely: change the source of the copy so that the value in iv2c isn't iVar2 but something *provably equal at runtime yet different in RTL*, and the copy is the only way to compute it. E.g., iv2c = iVar2 computed via a different expression that yields the same value but needs a move: like `iv2c = t + 1` where t is another variable holding t... cse CSEs `t+1`. But what if we use a *different but equal* expression, e.g., `iv2c = (param_2 >> 16 & 0xf) + 1;` — cse CSEs it with the same expression computed in the else arm (same EBB? the else arm is a different block; the join is a new block). Hmm! cse works per EBB; the else-arm computation and the join computation are in different blocks... but the join block is reachable from the else arm by fall-through, so cse may treat it as the same extended basic block (cse's EBB = a block plus its fall-through successors until a label that's a jump target). The join block IS a jump target (from the then arm), so it starts a new EBB. 

So if I write in the join:
```
iv2c = (param_2 >> 16 & 0xf) + 1;   // recompute
```
cse in the join EBB can't CSE it with the else arm's computation (different EBB). Then we'd get `sra v0,a1,0x10; andi v0,v0,0xf; addiu v1,v0,1` — 3 extra insns, not a move. No.

Hmm, but what about computing it as `iv2c = iVar2` where iVar2's register is... no.

What if we *reverse*: assign iVar2 from iv2c, and use iv2c in the compare... same copy.

OK here's another thought — maybe we can exploit the pinned `one` variable: `one` is `register int one __asm__("$2")` and assigned `one = 1`. The launder forced iv2c into a register because asm output. Could a *real* C construct force a copy because of a hard-reg conflict? Yes! If iv2c's live range overlaps with a hard register's live range, local-alloc can't put iv2c in that register. But we need the copy to *exist*, i.e., cse/combine must not eliminate it.

So the real question remains: which pass removes the copy, and how to stop it with real C.

Let me test whether it's cse or combine by making the copy's use not immediately foldable. E.g.:

w4:
```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
```
That's the current. What if we add a use of iVar2 in between that would make combine's substitution... no.

Decisive test: put a do-while around the copy AND check the cse dump to see if the copy survived cse. If it survived cse but died in combine, then the trick is to block combine.

Let me look at w2's .cse dump around the compare. Find the `li v0,1` equivalent: in RTL, `(set (reg:SI X) (const_int 1))`. grep const_int 1 in cse dump.
