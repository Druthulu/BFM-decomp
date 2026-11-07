---
ts: 2026-11-06T08:52:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OO7T6iUbeHP4mv8kOUpZ
---
Both still score 1 — the label/goto was removed before combine.

Let me check the dumps for c9 to see whether the label survived. Actually, both score 1 means the merge still happened.

What else creates a block boundary at RTL before combine? The RTL passes order: expand → jump(1) → cse → ... Actually GCC 2.7.2's pass order: ... jump, jump_optimize (jump.c), cse, ... combine. jump.c runs before combine and deletes redundant jumps/labels. So goto/label gets removed by jump.c before combine.

What RTL constructs survive to combine as a boundary?
- A real branch (if/loop) — but the target has no extra branch.
- A call — adds a call insn.
- A label that is a *jump target from elsewhere* (so jump.c keeps it) — e.g., a label targeted by a jump from another block. Could we create a label in the else block that is also a target of a jump that jump.c keeps but that generates no insns in the final code? Any real branch would add insns unless it's optimized later (after combine). Interesting: jump2 (after reload) could remove a branch that combine saw. So we can create a *real* conditional branch that survives to combine but is eliminated by jump2/reorg? That seems hard to control and risky.

Alternative: make the else block's neg a separate block via a *loop*: `while (0)` removed early. A loop with a condition that's not a compile-time constant but folds later? e.g. `while (rand())`? adds a call.

Hmm. What about making the neg expression itself not mergeable: the merge is `(set A B)` + `(set A (neg A))` → `(set A (neg B))`. Combine requires the copy to be a simple set with a register source. If the copy's source is something combine can't substitute... e.g., a *memory load*: `val = *(s32*)&nudge;` — that adds a load (target has no load). But wait — would it? If `nudge` is a local, `*(s32*)&nudge` is a stack load. Adds lw.

What if the copy is a *sign extension*: `val = (s32)(s16)nudge;` — adds sll/sra. No.

Hmm, what if the negation is a different operation that combine won't merge into the copy: e.g. `val = val * -1;`? combine's simplify might turn `(mult A -1)` into `(neg A)`, and then the merge happens. c6 (~val+1) gave score 13 (extra insns), so combine didn't fold that to neg — but it produced 111 insns.

What about `val = -1 * val` where -1 is a *variable*: `s32 m1 = -1;` adds li.

What about `val = val ^ 0xFFFFFFFF; val = val + 1;`? That's two insns instead of negu. No.

What about making the negation `val = ~val; val = ~val;`? two insns.

Hmm, the target needs exactly `move v1,s1; negu v1,v1`.

Alternative: maybe we can produce `negu v1,v1` differently: make val's register v1 and the neg's source v1 without the copy being merged. If the neg is `val = -val;` and val's live range... 

What if the copy is not `val = nudge` but `nudge = nudge;`? no.

What if the *then* branch does the copy and the else does `val = -nudge` — no (mine).

What if the else's copy is needed by the *stores*? The stores use the negated value.

What if we change the order of the stores so the first store uses the *pre-negation* value? Not the target.

Hmm, let me look at the target's register allocation: move v1,s1 — why v1? val is in v1 because... local-alloc gives val v1 (caller-saved, since val's live range crosses calls? val is stored after the call at 6320 which is after another call at 6320? Actually after the if, there's `CAST_WIDTH... = val; unkE0 = val;` then `val = 0xFFE70000 - (rand()<<4)` — a call at 6320 comes after the stores. val's live range ends at the stores before the call. So val could be a caller-saved reg. It got v1.

OK here's another thought: maybe use `?:` to write the else:
```c
val = nudge;
val = (rand() & 1) ? val : -val;
```
No, rand called again.

Let me think about combine's merge condition more precisely. In try_combine, i2 = (set A B), i3 = (set A (neg A)). It merges if i2's destination is used only in i3... but A (val) is also used in the *successor* insns (the stores). Combine's merge is still valid because after the merge A = neg(B). But wait: if A is used after i3, then the intermediate value of A (B) is dead — merge valid. If A were used *between* i2 and i3, no merge.

So to block: an insn between i2 and i3 using A. In real C: a statement between `val = nudge;` and `val = -val;` that uses val. What statement uses val but compiles to nothing? A `(void)val` doesn't survive. A `if (val)` adds a branch.

Hmm, what about `val = val;` between? GCC removes self-assignments early? Maybe not! Let me check: `val = nudge; val = val; val = -val;` — gcc's tree-level might keep the self-assignment or remove it. If kept, RTL: (set A B); (set A A); (set A (neg A)). The middle set might be removed by cse/flow as a no-op... but if it survives to combine, it blocks. Let me test.

Also `val = nudge + 0;` — combine folds.

Test:
- c11: `val = nudge; val = val; val = -val;`
- c12: `val = nudge; if (0) val = 0; val = -val;` (if(0) removed early)
- c13: `val = nudge; (void)(val); val = -val;` (removed)
- c14: `val = nudge; val = -(-val);`? no.

Let me test c11 and a couple more. Also another idea: use a *compound* statement that gcc lowers to a use: e.g. `val = nudge; val = -val;` where the neg is `val = -(val);` same.

What about `val = nudge; val = -val, val;`? no.

Hmm, what about making `val` and `nudge` the same variable in a different scope... no.

Let me test c11.
