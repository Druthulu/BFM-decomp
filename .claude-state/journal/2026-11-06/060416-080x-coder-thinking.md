---
ts: 2026-11-06T13:04:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hc7Bw54zdriH72UvkF0Z
---
Now clear: the target has a `nop` after `beq v1,v0,1394` (the `== 4` test) that mine lacks (mine filled the delay slot with `li v0,10`).

Target:
```
68 li v0,4
69 beq v1,v0,ret
70 nop              <- delay slot NOT filled
71 li v0,10
72 beq v1,v0,ret
73 nop
```
Mine:
```
68 li v0,4
69 beq v1,v0,ret
70 li v0,10          <- filled
71 beq v1,v0,ret
72 nop
```
So in the target, the first beq's delay slot is a nop; mine puts `li v0,10` there (dbr).

The barrier in source sits between `if (D_8011512C == 4) return;` and `if (D_8011512C == 0xA) return;`. Without it, dbr fills the first branch's delay slot with the second test's `li v0,10`.

Real-C fix: make the `li v0,10` not movable into the first branch's delay slot. Since it's a constant load for the second comparison, dbr threads it.

Ideas:
1. Reorder: put the `== 0xA` test first: `if (D_8011512C == 0xA) return; if (D_8011512C == 4) return;` → then the first branch (0xA, li 10) would get `li v0,4` in its slot. Target wants the first beq to be `== 4` with a nop. So no.

2. Use a switch? `switch (D_8011512C) { case 4: return; case 0xA: return; }` — codegen differs.

3. Make the second test's constant come from a variable/computation so it's not a `li` that dbr can hoist... but then it wouldn't be `li v0,10` in the target.

4. Change the first test's form so its delay slot can't be filled: e.g. `if (D_8011512C == 4) { return; }` — same.

5. Insert a real statement between them that can't be moved: e.g. `i = 0;`? That would be an insn.

6. Make the second condition read a *different* variable that happens to hold the same value? e.g. `if (D_8011512C - 6 == 4)`? changes codegen.

7. Use a nested if: `if (D_8011512C == 4) return; else if (D_8011512C == 0xA) return;` — same CFG probably.

8. What about making the first test `if (4 == D_8011512C)`? Same.

Hmm, dbr's fill_slots_from_thread fills a delay slot with an insn from the branch's *target* or *fall-through* thread. Here the `li v0,10` comes from the next block (fall-through). dbr fills the delay slot with an insn from the branch target when safe... 

In the target, the delay slot is a nop. Why? Because the barrier asm is at the head of the next block, so dbr's `stop_search_p` halts at the asm insn (as the header of func_80030F80 noted: "reorg.c stop_search_p halts fill_slots_from_thread at ANY asm insn").

So the asm barrier blocks the fill. Real-C: make the first insn of the next block non-movable. 

Idea: make the second test's `li v0,10` depend on a value... e.g. `if (D_8011512C == 0xA)` where the constant is written as an expression that's folded at RTL: `(0xA)` — same.

Idea: put the `== 0xA` test inside an `else` of the first: `if (D_8011512C == 4) { return; } else if (D_8011512C == 0xA) { return; }` — the CFG is the same (the else is the fall-through).

Idea: make the first test a `!=`: `if (D_8011512C != 4) { ... }` — restructuring.

Idea: use a `switch (D_8011512C)` with cases 4 and 0xA both returning — gcc would emit a compare tree.

Idea: make the second test's comparison use a variable: `s16 t = 0xA; if (D_8011512C == t) return;` — an extra move? Maybe folded.

Idea: swap the *order* of the tests so the target's layout arises naturally? Target: beq ==4 with nop, then li v0,10, beq ==0xA with nop. Both delay slots are nops in the target! Look: 
```
69 beq v1,v0,1394
70 nop
71 li v0,10
72 beq v1,v0,1394
73 nop
```
Hmm, the second beq at 72 has nop at 73, then `lui v1,0x0` at 74.

So the target has nops in both slots. Mine fills the first with `li v0,10`.

Interesting: in the target, both branches jump to the same target (1394) — the return. 

So the target is: load, li 4, beq (nop), li 10, beq (nop).

In mine: load, li 4, beq (li 10), beq (nop).

To stop the fill of the first slot: the next insn `li v0,10` must not be movable. 

What if the second test reads the global *again* (a second load)? Then the block starts with a load... dbr could still fill with the load? Actually filling a delay slot with a load is allowed (the load executes on the taken path too, harmless).

Hmm.

What if I restructure so that the `li v0,10` is not the first insn of the fall-through block? E.g.:

```
if (D_8011512C == 4) return;
i = 0;                       // something
if (D_8011512C == 0xA) return;
```
That adds an insn.

What about:
```
if (D_8011512C == 4) {
    return;
}
if (D_8011512C != 4 && D_8011512C == 0xA) {
    return;
}
```
Folds.

Hmm, what about the actual structure: `if (D_8011512C == 4) return;` then `if (D_8011512C == 0xA) return;`. What if I write:

```
if (D_8011512C == 4) {
    return;
} else if (D_8011512C == 0xA) {
    return;
}
```
Probably identical.

What about combining with a `goto`:
```
if (D_8011512C == 4) goto out;
if (D_8011512C == 0xA) goto out;
...
out: return;
```
That changes the CFG (one return block) — target has both jumping to 1394 (the same return). Hmm! Both beqs jump to the same address 1394 — that IS a shared return. With `return;` twice, gcc merges them into one epilogue block anyway.

Let me think about the target's exact shape: 
```
66 lui v1; 67 lh v1 ; 68 li v0,4 ; 69 beq v1,v0,ret ; 70 nop ; 71 li v0,10 ; 72 beq v1,v0,ret ; 73 nop ; 74 lui v1 ; 75 lbu ...
```
So both branches go to the shared return block.

In mine, the only difference is 70: `li v0,10` instead of nop.

So: the `li v0,10` was moved into the first branch's delay slot. This is dbr's fill_slots_from_thread. It fills the delay slot of the first beq with the *next* insn because the branch is "likely not taken" and the next insn would be executed anyway... Actually filling with the next insn is a no-op optimization (the insn executes either way) — that's "fill from the fall-through thread", valid when the branch is not taken in the common case? It's valid always if the insn is safe (executes on both paths).

To prevent it: the insn must not be safe to execute on the taken path. `li v0,10` is always safe. So dbr does it. The asm barrier prevents it because stop_search_p halts.

Real-C to make `li v0,10` unsafe on the taken path: impossible (it's a constant load).

Hmm — but what if the second test is not `== 0xA` but uses a value that requires the load to have happened? E.g.:

```
if (D_8011512C == 4) return;
{
    s16 v = D_8011512C;      // second load -> fills? 
    if (v == 0xA) return;
}
```
The second load would be `lh` at the block head; dbr could fill the delay slot with the load — which IS safe (loading is safe). So still filled. And it would add a load insn (target has one load).

What if the first test uses the loaded value and the second test's `li v0,10` is replaced by a comparison against a value that depends on... 

Alternative: make the second test `if (D_8011512C == 10)` where 10 comes from a global? Adds a load.

Alternative: use `else if` chain with a different shape so the branch target isn't the shared return.

Hmm, what about writing the two tests as a single `if` with `||`:
```
if (D_8011512C == 4 || D_8011512C == 0xA) return;
```
a4 = 9 (same). The codegen would be: li 4, beq; li 10, beq — same issue.

What about `if (D_8011512C == 4) return; if (D_8011512C == 0xA) return;` but with the second written as `if (D_8011512C - 0xA == 0) return;`? adds subu.

What about `switch (D_8011512C) { case 4: case 0xA: return; }`? gcc's switch would emit a compare tree, maybe with different delay slots. Worth a try.

What about `if (D_8011512C == 4) { return; } if (D_8011512C == 0xA) { return; }` — same.

Another idea: make the *first* test's branch target not the shared return but the following code... no.

Hmm, what if I move the `== 4` test to be the second one and the `== 0xA` first? Then the first branch is `li 10; beq` and the fall-through is `li 4; beq`. dbr would fill the first slot with `li v0,4`. Target's first branch is `li 4`. So no.

Let me look at this from dbr's perspective: it fills the delay slot with the following insn if that insn is "safe". To make it unsafe, the insn must be a branch/jump/load-with-trap... 

What if the second comparison's constant load is replaced by an `addiu` that depends on a value? e.g. `if (D_8011512C == (0x5 << 1))` → folded to 10.

What if the second test is `if (D_8011512C == 0xA && ret == 0)`? `ret` is 0 — folds.

What if the second test is `if (D_8011512C == 0xA) { D_801F2488 = D_801F2488; return; }` — adds a store.

Hmm.

OK here's another thought: the target's nop at 70 is because dbr couldn't fill. What if instead the *source* has something between the two tests that becomes the delay-slot content in the target... no, the target has a nop.

Let me try a batch:
- t1: `switch (D_8011512C) { case 4: return; case 0xA: return; }`
- t2: `if (D_8011512C == 4) { return; } else if (D_8011512C == 0xA) { return; }`
- t3: goto out form
- t4: `if (D_8011512C == 4) return; i = 0; if (D_8011512C == 0xA) return;` (i=0 might be dead... i is used later; setting i=0 before the for loop which sets i=0 anyway → dead, folded)
- t5: reorder to `== 0xA` first
- t6: use a helper variable: `{ s16 v = D_8011512C; if (v == 4) return; if (v == 0xA) return; }`

Let me try these.

Also, note a2 (volatile) was 15 — no.

Let me run t1-t6.
