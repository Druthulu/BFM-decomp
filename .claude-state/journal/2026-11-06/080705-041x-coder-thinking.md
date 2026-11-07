---
ts: 2026-11-06T15:07:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wm9QQerLDHX320BFjGop
---
d4 still has `move a0,zero` at 9 — so the fold still happened. The do-while didn't prevent it; it just reordered the prologue stores.

So cse's fold isn't blocked by the do-while label. Maybe the fold is in `flow`/`combine` via reg_n_sets? Let's check: s0's sets: `s0 = 0` and `s0 = s0 + 1` (loop). reg_n_sets = 2. combine's get_last_value uses LOG_LINKS — for `a0 = s0 << 10`, the LOG_LINK to `s0 = 0`? But the loop's back edge means s0 also has a set from the loop. Hmm, but in the pre-loop block, the reaching definition is only `s0 = 0`. combine's `get_last_value` uses LOG_LINKS, which are per-block reaching defs. So it finds `s0 = 0` and folds. The label condition `reg_last_set_label == label_tick` — if we insert a label between them, `reg_last_set_label[s0]` would be the label tick when s0 was set (before the label), and label_tick would have advanced → condition false → no fold. So a label between them SHOULD block combine. But cse also folds (qty_const).

d4's do-while: did it produce a label between? Maybe gcc's jump pass removed the label because the loop is trivially once. The `do { s0 = 0; } while (0)` body has no side effects (s0 is a local pseudo), so the front-end/jump optimization deletes the branch and the label. Then no boundary.

C0535's do-while wrapped *two copies* (also side-effect-free?) — but there it worked at the sched1 level, which is after... hmm.

OK let me think of a label that survives: a `goto` label that is the target of an actual jump that survives. E.g.:

```
s0 = 0;
if (s1 != 0) goto L;
L:
a0 = s0 << 10;
```
The jump to the immediately-following label is removed.

What about a loop that the optimizer can't remove, but whose net effect is zero? Hmm.

Alternatively: use the fact that `reg_n_sets[s0] == 1` disables the label condition. Since s0 has 2+ sets (loop), the label condition applies. So we need a label. 

What creates a surviving label? A conditional branch whose condition is opaque. E.g. `if (s1) { }` — empty, removed. `if (s1) s0 = s0;` — may be removed.

What about a real branch that is taken/not-taken based on a value: e.g.
```
if (s1 & 1) s0 = 0; else s0 = 0;
```
Then both paths set 0; combine sees each block's last value 0 and the merge... The shift is after the merge; the label at the merge (join) would reset label_tick. But cse might still propagate the constant across the join if both arms set the same constant! cse handles joins by intersecting equivalences; if both arms set s0=0, at the join s0 is still known 0. combine's get_last_value might also handle. Hmm.

What about:
```
s0 = 0;
if (s1 & 1) { s0 = s0 + 0; }   // folds
```

We need s0 = 0 on the fall-through but the compiler not to know. Use a branch where one arm sets 0 and the other sets something that's also 0 at runtime but unknown statically? E.g. `else s0 = s0;` no.

Hmm, how about exploiting `s2` (the symbol address)? `s0 = (s32)D_8019B538 - (s32)D_8019B538;` — gcc folds to 0? It might not fold symbol differences? Actually fold_rtx handles PLUS/MINUS of symbols maybe. But even if not folded, it would emit code (lui/addiu twice, subu) — changes instruction count.

We need zero-cost.

Think about it from a different angle: what if we make the *shift expression* not foldable by making s0's value a *copy of a register that's set to 0 through a type pun*? 

Alternative: maybe don't fight the fold — instead make gcc emit `sll a0,s0,0xa` for a different reason: if `a0` is a *pointer* offset? Hmm.

What about `a0 = (s32)((s0 + 0) << 10);` folds.

What about making s0 itself an `s32` but assigning with a shift: `s0 = 0 << 0;` folds.

Hmm, what about the "init at decl" move: `s32 s0 = 0;` at declaration. That's a different RTL placement (expand-time) but still a constant set.

What about declaring s0 as a *register* variable with a pin? No new pins.

What about using a `u8`/`s16` variable in a way that requires a conversion which blocks the fold? d2/d3 gave more instructions. But maybe a *different* variable type: e.g., `s0` stays s32 but the shift operand is `((u8)s0)`:
`a0 = ((u8)s0) << 10;` — (u8)0 folds.

What about `a0 = (s32)((u16)s0 << 10);`? folds.

Hmm.

Let me reconsider whether the fold is really cse/combine. Let me test by compiling with -fno-... Actually I can dump the cc1 passes for the candidate to see which pass turns sll into move. Use tools/cc1_dumps_tu.sh on the TU with a body spliced. But the body must be in the TU. Alternatively use the --try scratch copy with --keep? The scratch TU has the candidate spliced; I could run cc1_dumps_tu.sh on that scratch .c. But --try deletes it unless --keep.

Plan: run --try --keep, get the scratch src path, then run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir, and inspect .cse/.combine/.flow dumps to see where sll→move.

Actually the scratch dir is .run/P36/engine/score/.../p<pid>/. Let me get the path. From the earlier --keep output the object was .../p3/cand.o; the scratch src is .../p3/<basename>. Let me list.
