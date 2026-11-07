---
ts: 2026-11-06T14:45:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4j7fxscvdEzkpSte6ZMm
---
Now I see both. Target:
```
$L67:
	sll	$2,$17,16
	sra	$16,$2,16
	bne	$16,$0,$L68
	li	$3,3            # v1 = 3
	la	$2,D_8018C4FC
	j	$L60
$L68:
	beq	$16,$3,$L70     # t==3 -> L70
	li	$2,5            # v0 = 5
	bne	$16,$2,$L71     # t!=5 -> L71
 #APP
 #NO_APP
	bne	$16,$3,$L73     # t!=3 -> L73
$L70:
	la	$2,D_8018C520
	j	$L60
$L73:
	...
$L71:
	...
```

Mine (c1):
```
$L67:
	sll	$2,$17,16
	sra	$16,$2,16
	bne	$16,$0,$L68
	li	$2,3            # v0 = 3
	la	$2,D_8018C4FC
	j	$L60
$L68:
	beq	$16,$2,$L70     # t==3 -> L70
	li	$2,5            # v0 = 5
	beq	$16,$2,$L73     # t==5 -> L73?? 
	j	$L71            # else -> L71
$L70:
	la	$2,D_8018C520
	j	$L60
$L73:
	...
$L71:
	...
```

Wait, mine: `beq $16,$2,$L73` means if t==5 goto L73 (sel_094). But the C says `if (t == 5) { if (t != 3) goto sel_094; sel_054: ... }`. So if t==5, we go into the block; then `if (t != 3) goto sel_094` — but t==5, so t != 3 is true, so goto sel_094 (L73). So `t==5 -> L73` is correct! And if t != 5, goto L71 (the code after the if). So mine's structure is:
```
beq t,3,L70
li v0,5
beq t,5,L73
j L71
```
This is CORRECT but differs from the target:
```
beq t,3,L70
li v0,5
bne t,5,L71
bne t,3,L73
```
The target doesn't fold the `t==5 && t!=3` into `t==5`. Why? Because the launder asm between them prevents the compiler from proving t is unchanged across the asm (the asm reads and writes t, so the compiler must assume t may change). So after the asm, `t != 3` is a separate check, and the branch `bne t,5,L71` then `bne t,3,L73`.

Without the launder, the compiler knows t is unchanged, so `t==5` implies `t!=3`, and it folds the inner check away: `beq t,5,L73` (skip the t!=3 check since t==5 means t!=3).

So the launder's effect: it makes the compiler treat `t` as potentially modified by the asm, so the `if (t != 3)` check after it can't be folded.

To reproduce this with real C, I need the compiler to NOT fold `t != 3` after the `t == 5` check. That requires t to be potentially modified between the two checks — impossible in pure C without an asm or a volatile.

Hmm. But maybe there's a real-C way to structure the code so the compiler emits the target's branches. For example, restructure the if:
```
if (t == 5) {
    if (t != 3) goto sel_094;
    sel_054: ...
}
```
The compiler folds t==5 -> t!=3. To prevent, I could write:
```
if (t == 5) {
    s32 u = t;
    if (u != 3) goto sel_094;
    ...
}
```
Hmm, u == t, the compiler still knows.

What if I use a real operation that changes t but not its value? Like `t = t & 0xFFFF`? If t is s16, `t & 0xFFFF` might change the type/value (t is s16, so t&0xFFFF could be different if t is negative, but t=5 here). Hmm, `t = t & 0xFFFF` would emit an `andi` — extra instruction.

What if `t = (s16)(t + 0)`? folds.

Hmm. The key: the target's branch structure `bne t,5,L71; bne t,3,L73` means the compiler did NOT fold t==5 => t!=3. That's only possible if t is opaque (asm) or if the two checks are on different values.

Wait — maybe the target's structure comes from a different C formulation, not from the launder's opacity. Let me think about what C would produce:
```
beq t,3,L70
li v0,5
bne t,5,L71
bne t,3,L73
```
This is: if (t==3) goto L70; if (t!=5) goto L71; if (t!=3) goto L73; L70: ...

So the C would be:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t != 3) goto sel_094;
    sel_054: ...
}
```
Compiled without folding: `beq t,3,L70; bne t,5,L71; bne t,3,L73; L70: ...`. The `bne t,5,L71` is the negation of `if (t==5)`, branching to the else (L71). Then inside, `bne t,3,L73`. Then fall into L70 (sel_054).

The compiler without the launder folds `t==5` to skip the `t!=3` check (since t==5 implies t!=3). With the launder, it can't.

So to get the target, I need t to be opaque at the second check. Real C can't make a variable opaque without volatile/asm.

BUT — maybe I can restructure the C so that the two checks are on DIFFERENT variables that happen to be equal, and the compiler can't prove it. For example:
```
t = (s16)a1;
...
if (t == 5) {
    s32 u = t;   // u == t
    if (u != 3) goto sel_094;
    ...
}
```
The compiler would still know u == t (copy propagation). Unless the copy is across a control-flow join.

Hmm. What if `t` is reloaded from a global or recomputed? E.g., after the `t==5` check, recompute `t = (s16)a1;`? Then the second check is on a fresh value, and the compiler can't prove it's 5? Actually, it can (a1 is unchanged, t = (s16)a1). It would fold.

What if a1 is a global or could change? a1 is a parameter, unchanged.

Hmm. What if I use a function call between the checks that the compiler thinks might modify something? There's no call.

So the launder's opacity is essential. This is a WALL of class "launder-cse-fold" / "combine-copy-merge"? The launder prevents the compiler from folding t==5 => t!=3. Real C can't prevent that without an opaque operation.

Wait — maybe I can achieve the same BRANCH structure by a different C formulation that doesn't rely on opacity. The target's branches:
```
beq t,3,L70       # if (t==3) goto sel_054
li v0,5
bne t,5,L71       # if (t!=5) goto L71
bne t,3,L73       # if (t!=3) goto sel_094
L70: sel_054...
```
This is logically equivalent to: if (t==3) goto sel_054; if (t==5) { if (t!=3) goto sel_094; } sel_054...
But since t==5 implies t!=3, the second check is dead. The target keeps it.

Could I write C that naturally emits both checks? For example, if the two checks are in different basic blocks with a join, the compiler might not fold. E.g.:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t == 3) goto sel_054;   // redundant but if the compiler doesn't fold...
    goto sel_094;
}
```
The compiler would fold t==5 && t==3 -> false. Hmm.

What if the second check is `if (t != 3)` written via a different expression, like `if ((s16)a1 != 3)`? The compiler knows (s16)a1 == t. Folds.

What if the second check uses a different variable that's assigned t before the branch but could be different? Like `u = t + 0`? folds.

Hmm. Let me look at how other launder items were cracked. Let me grep moves.md for launder MATCH entries. I saw many. Let me look at the techniques:
- "launder->real 2nd set pv &= mask"
- "pointer reuse"
- "per-segment q reassignment kills cse"
- "dead-reset cse-breaker"
- "do-while ref weight"

These are mostly about cse equivalence classes. For our case, the launder prevents a conditional fold (t==5 => t!=3). This is a "known value" fold in jump.c/fold.

Let me check: which pass folds `t==5 => t!=3`? The C front-end (fold) or jump.c (jump_optimize)? The fold of `t==5` then `t!=3` across a branch is done in jump.c's `thread_jumps` or the `if` simplification. Actually, the C front-end might fold `if (t==5) { if (t!=3) ... }` by noticing the inner condition is true given the outer. That's "conditional constant propagation" — done by fold? Or by jump.c's `mark_jump_label`/`thread_jumps`.

Actually, the structure `if (t == 5) { if (t != 3) goto X; ... }` — the inner `t != 3` is known true when t==5. The front-end (fold) does NOT do this (it doesn't track conditions across statements). It's jump.c's `thread_jumps`/`simplify_if_then_else`? Or cse's constant propagation? Hmm.

Actually, gcc's jump.c has `jump_optimize` which does "conditional jump threading" and "delete unreachable code". The fold `t==5 => t!=3` might be done by jump.c's `thread_jumps` (finding that a jump to a target where the condition is known). 

The launder asm between them: after the asm, t is considered modified (the asm has an output constraint "=r"(t)), so the compiler can't assume t==5 anymore. Hence the check remains.

To reproduce without asm, I need the compiler to lose track of t. Real C: assign t a value that the compiler can't prove is 5. For example, reload t from memory: `t = D_801802E4[t]`? No, that changes t.

Hmm, what if I write `t = (s16)a1;` AGAIN inside the t==5 block? The compiler knows (s16)a1 == t, so it folds.

What if a1 is modified? No.

What if I use a volatile global? Not allowed (adds code).

Hmm. Let me look at the exact target structure again. The `bne $16,$3,$L73` after the asm checks t != 3. Since the asm's output is t (same register), the compiler must treat t as unknown after the asm. So the check is real.

Could I achieve the same by having the second check use a DIFFERENT variable that's the result of a function call? There's no call.

What if I restructure so that the `if (t != 3)` is on a value loaded from a global that I set to t earlier? E.g., `D_80190110 = t; ... if (D_80190110 != 3)`. That would emit stores/loads. Bad.

Hmm.

Let me look at the target's branch structure more carefully. The target:
```
	beq	$16,$3,$L70      # if (t == 3) goto L70
	li	$2,5
	bne	$16,$2,$L71      # if (t != 5) goto L71
 #APP
 #NO_APP
	bne	$16,$3,$L73      # if (t != 3) goto L73
$L70:
```
The `bne $16,$3,$L73` uses the constant 3 ($3 = v1) loaded earlier (`li $3,3` in the delay slot of the first bne). So $3 = 3 is set early.

Mine:
```
	bne	$16,$0,$L68
	li	$2,3             # v0 = 3
	...
$L68:
	beq	$16,$2,$L70      # if (t == 3) goto L70
	li	$2,5             # v0 = 5
	beq	$16,$2,$L73      # if (t == 5) goto L73
	j	$L71
```
Mine uses v0 for both 3 and 5 (reusing the register), and folds the t!=3 check.

So two differences:
1. The constant 3 is in v0 (mine) vs v1 (target).
2. The branch structure: mine folds t==5 => t!=3 into `beq t,5,L73`.

The launder causes both: the asm output forces t into a register and the constant 3 to be in v1 (since v0 is used for 5 and the asm clobbers...). Hmm.

Actually, the constant register difference might be a consequence of the branch structure. In the target, the `li $3,3` is placed early (delay slot of `bne t,0`) and kept in v1 across the asm. In mine, `li $2,3` is in the delay slot but then v0 is reused for 5.

The core issue is the fold of the second check. If I can prevent that fold, the branch structure would match, and maybe the constants follow.

How to prevent the fold in real C? The fold is `if (t==5) { if (t!=3) }` -> the inner is always true. This is done by jump.c or fold.

Wait — actually, maybe the fold is done by the C front-end's `fold` on the condition? No, fold doesn't know t==5 from the enclosing if.

Let me check: does gcc 2.7.2's jump.c do "condition known from dominating branch"? There's `thread_jumps` which threads jumps through blocks where a condition is known. The `bne t,5,L71` (t!=5 -> L71) and then `bne t,3,L73` — jump.c might notice that at the second branch, t==5 (from the fall-through of the first bne), so t!=3 is always true, and it could redirect the branch to always taken (goto L73) and remove the check. That's what mine does: `beq t,5,L73; j L71` — it folded the two branches into `beq t,5,L73`.

Hmm, mine's `beq t,5,L73; j L71` is the result of folding: the compiler determined that if t==5 then (t!=3) is true so goto L73, else goto L71. So it merged the two branches.

The launder's opacity prevents jump.c from knowing t==5 at the second check.

So this is a jump.c/cse "known value" wall. Real C can't make t opaque.

BUT — maybe I can restructure the C to produce the target's branches without opacity. The target's branches are logically:
- if t==3 goto L70
- if t!=5 goto L71
- if t!=3 goto L73
- L70: sel_054...

This is: if (t==3) goto L70; else if (t!=5) goto L71; else if (t!=3) goto L73; else L70.

Since t==5 => t!=3, the third check is redundant. To make the compiler emit it, I could write the C such that the compiler doesn't see the relationship. For example, use a variable that's set in a way the compiler can't track:

```
if (t == 5) {
    s32 u;
    u = t;         // copy
    if (u != 3) goto sel_094;
    ...
}
```
The compiler copy-propagates u=t and still folds.

What if `u` is computed as `u = (s16)(t | 0)`? folds.

What if `u` is `t` after a function call? No call.

Hmm, what if I restructure the control flow so the second check is in a separate block with a join, and the compiler's jump.c doesn't thread it? E.g.:
```
if (t == 5) goto in5;
goto after;
in5:
if (t != 3) goto sel_094;
sel_054: ...
after: ...
```
With explicit gotos, the compiler might still fold.

What about using a `switch (t)`? `switch (t) { case 3: goto sel_054; case 5: if (t != 3) goto sel_094; ... }`. The switch would compile to a jump table or comparisons. Hmm.

Actually, let me reconsider: the target's code is exactly what you get WITHOUT folding. Maybe the original source was:
```
if (t == 3) goto sel_054;
if (t == 5) {
    if (t != 3) goto sel_094;
    sel_054: ...
}
```
and the launder was needed because jump.c folds. So the launder is the "lever". The task is to find a real-C crack.

Given the launder's opacity requirement, maybe there IS a real-C trick: use a `volatile` local? `volatile s32 t;` would force loads/stores (extra code). Bad.

What about using a pointer to t and reading through it? `s32 *pt = &t; ... if (*pt != 3)`. The compiler might not track *pt (it's a local address, but gcc might still track it). And taking the address of t might force it to memory (extra code). Hmm.

Let me think about the moves.md launder cracks. Many are about cse equivalence. This one is about jump threading. Let me look for a "flow-known-value" or "jump-known-value" crack. The walls.txt has `flow-known-value`: "flow/jump: a redundant test on a known value is folded away; target keeps it (G22)". That's EXACTLY this wall! So this is a known wall class: a redundant test on a known value is folded away; the target keeps it.

Let me grep moves.md for "flow-known-value" to see if it was ever cracked.
