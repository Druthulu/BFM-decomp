---
ts: 2026-11-06T08:41:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9U3RZwVz689J4WQpBPib
---
Target around the branch:
```
6304: jal rand
630c: andi v0,v0,1
6310: bnez v0,631c        <- if (rand()&1) goto 631c (val=nudge path)
6314: move v1,s1          <- delay slot: val = nudge  (executed on BOTH paths!)
6318: negu v1,v1          <- else: val = -val
631c: sw v1,16(s0)
```
So the `move v1,s1` is in the branch delay slot — executed always. The asm made `val = nudge;` a real insn (move v1,s1), and then `val = -val` negates it. Without the asm, combine merges: `negu v1,s1` directly (one insn instead of two).

So we need real C that keeps the copy. The asm `"r"(val)` forces val into a register at that point.

Lever-free options: make the `val = nudge;` have a use that prevents the merge. In the target, `move v1,s1` is in the bnez delay slot — meaning the copy is emitted before the branch? Wait, the bnez at 6310 tests rand()&1: if true → val = nudge (631c). The move at 6314 is in the delay slot, so it executes regardless — that's exactly the copy `val = nudge` from the *else* branch being hoisted into the delay slot. And then negu in the else path.

Hmm: the source structure:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    asm(val);
    val = -val;
}
```
Target: the else's `val = nudge` is placed in the bnez delay slot (reorg moved it up from the else block, safe since it's the same value as the if's assignment). Then the else negates.

Without asm, combine sees `val = nudge; val = -val;` in the else → `val = -nudge`, so the else is just `negu v1,s1` and the if's `val=nudge` is `move v1,s1` in the delay slot? Let's check mine: diff only shows mine[51] = negu v1,s1 vs target negu v1,v1, and register pair s1->v1 x1. So mine still has the move v1,s1 at 6314 in the delay slot (from the if branch) but the else does negu v1,s1 directly.

So the crack: prevent combine from folding `val = nudge; val = -val;` into `val = -nudge`. Real C options:
- Insert a real use of val between: e.g. `val = nudge; if (val) ...` no.
- Make the negation an expression that uses val twice? `val = -val;` is the negation.
- Use a volatile? no.
- Use a different C spelling that combine can't merge: e.g. `val = 0 - val;` → combine may turn into neg. `val = ~val + 1;` → combine may simplify to neg. `val = (s32)(0u - (u32)val);` → could still become negu.
- `val = val * -1;` → combine strength-reduces to neg.

Hmm. combine-copy-merge wall is listed. But there may be a real-C route.

What about making the copy meaningful: the target's `move v1,s1` in the delay slot serves BOTH branches. In the source, the if-branch does `val = nudge;`. The else does `val = nudge; ...; val = -val;`. What if the else's copy is avoided in source, i.e., write the else as `val = -nudge;`? Then target would be: move v1,s1 (if), negu v1,s1 (else) — same as mine. Not the target.

So we need `val = nudge; val = -val;` to stay two insns. Combine merges copy+neg. To block: make `val` used between the two assignments in a way that forces materialization but adds no insn. The asm did exactly that.

What real C has an effect that costs nothing? Hmm, a `do {} while(0)` around `val = nudge;`? C0535: do-while splits cse1 EBB. Let's test: 

```c
} else {
    do { val = nudge; } while (0);
    val = -val;
}
```
Would combine still merge? The do-while creates a basic block boundary (label), which may prevent combine from merging across it (combine works within extended basic blocks). That's promising — and do-while is allowed with the `// !FAKE: do-while` comment per constraints (do{}while(0) only with `// !FAKE: do-while`).

Let me test that. Also test other variants:
- `val = nudge;` then `val = -val;` with a `goto` label between? similar.
- Swap: `if (rand() & 1) val = nudge; else { val = nudge; val = -val; }` is current.

Alternative: make the else's copy a *different expression*: `val = nudge; val = -(s32)val;` same.

Let me try the do-while first. Note the comment requirement: `do{}while(0)` only with `// !FAKE: do-while`.

Let me create candidates:
c2: do { val = nudge; } while (0); // !FAKE: do-while
c3: if/else restructure: 
```c
if (rand() & 1) { val = nudge; } else { val = nudge; { s32 t = val; val = -t; } }
```
that's a copy to a temp then negate — could produce move + negu? `t = val; val = -t;` combine merges again probably.
c4: `val = nudge; val = -val;` with a `(void)val;` between? dropped.
c5: write the else as `val = nudge; if (1) val = -val;`? adds a branch maybe folded.
c6: `val = nudge;` then `val = 0 - val;`.

Let me test c2 (do-while) first.
