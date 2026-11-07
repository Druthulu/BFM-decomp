---
ts: 2026-11-06T15:19:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0DvYkuvBb2HEuSN2MaOL
---
Still 4. Let me check whether it folded (probably the switch compiled to compares and folded).

Time: ~08:22, item 2 ~14 min. I need 20. Let me try a few more ideas.

Idea: put the t != 3 test in a function-like block that the compiler treats as a separate basic block via a *label that is actually used*: e.g., the existing `set_sel` label is used by many gotos. What if we route the test through a goto to a shared label?

For example, change the flow so that the `t != 3` test is at the `sel_094` label or at `set_sel`:
```
if (t == 5) {
    goto sel_094;   // no test
}
```
No.

What if we make the test a *branch to a shared label* that has multiple predecessors with different t values, so flow can't propagate? The `call_45F` label has multiple predecessors (from several cases). If the test were `if (t != 3) goto call_45F`... no, the target's branch goes to sel_094.

Hmm, but the *target's* sel_094 has only one predecessor (the test's taken path)? Actually sel_094 could also be reached from... let me check the target's CFG: 71c (sel_094) is reached only from 704's bne. So one predecessor.

OK. Another thought: maybe the register mismatch in g1 is fixable by making a1's *live range* end at the compare so gcc can put it in s0? The target has a1 in s1 throughout (callee-saved). The compare in the target uses s0 (t). In g1, the compare uses s1 (a1). If we could make the compiler copy a1 to a caller-saved/temp register... 

What if we write `if ((s32)(s16)a1 != 3)`? That's (s16)a1 — folds.

What if `if (a1 != 3 && 1)`? same.

What if `if ((a1 | 0) != 3)`? folds to a1.

Hmm.

Let me try: `if (a1 != (s32)(s16)3)` — same as a1 != 3.

OK, I'll accept the wall. But I need ~6 more minutes. Let me use them to try a couple of genuinely different ideas:

m1: Move the t!=3 test to the *top* of the case-5 block (before t==0/t==3/t==5 tests) with a guard. E.g.:
```
t = (s16)a1;
if (t == 0) {...}
if (t != 3) {
    if (t == 5) { goto sel_094; }   // wait, semantics
}
```
Hmm: the original: if t==3 → sel_054; if t==5 → sel_094 (since t!=3 always true). So actually the original reduces to: if t==3 → sel_054; else if t==5 → sel_094. The launder's test is redundant! The target has it because the asm blocks the optimization. 

Wait — actually, since t==5 implies t!=3, the original's `if (t != 3) goto sel_094;` inside `if (t==5)` is always taken. So the whole thing is equivalent to: if t==3 goto sel_054; if t==5 goto sel_094. The launder preserves the redundant test. So the target's code has a redundant test — a "flow-known-value" wall indeed.

m2: What if we make the t==5 test *not* imply t==5 to the compiler by testing `(s16)(t & 0xFF) == 5`? h1/h4 added an andi (30). But maybe a different mask that's free: `(t & 0xF) == 5`? For t=5 → 5. But t=0x15 would also match → semantics differ, and gcc emits andi.

m3: Use a `char`/`u8` cast: `if ((u8)t == 5)` — gcc might emit andi (needs zero-extend). 

m4: What about `if ((s16)t == (s16)5)` — same.

I think the wall is real. Let me spend the remaining time on a couple of "comparison operand" ideas, then finalize.

n1: `if (a1 != 3)` but with `t` declared before and used... g1 already.
n2: `if (a1 != 3)` and also make the t==5 test use a1: `if (a1 == 5)` — would compare a1, wrong register for that branch.
n3: `if ((s16)a1 != 3)` folded.

Let me instead try to see if g1's register difference can be resolved by making a1's value be copied into s0 via a temp that also serves t... 

Actually! Here's an idea: `if (t != 3)` where the *t* used is reassigned from a1 with a full-width store into a new s32 variable that aliases... no.

What about: declare `t` as s32 and write:
```
t = a1;                  // s32 t = full a1
if (t == 3) goto sel_054;  // hmm, target compares (s16)a1
```
No.

Alternatively, compare `t != 3` where t is redefined as `t = (s16)(a1 | 0x10000);`? That changes the value (0x10005 → as s16 = 5? (s16)0x10005 = 5! and a1=5 → 0x10005 → 5). So `t = (s16)(a1 | 0x10000)` is value-preserving for the low 16 bits! And the compiler can't know the low bits of a1... but it knows t == 5 from the branch! So it folds. Ugh — the knowledge is from the branch, not the computation.

Right: ANY expression that sets t will be evaluated by the compiler using its knowledge t==5, and folded. Unless the expression is not const-foldable with t==5. E.g., `t = (s16)(a1 | 0x10000);` — the compiler would need a1's value (unknown) → can't fold → emits code! Let me test this: it would emit `ori` + `sll` + `sra` — extra instructions. Hmm, 3 extra.

But maybe a cheaper opaque: `t = (s16)(a1 | 0x10000)` → gcc knows the result's low 16 bits = a1's low bits = 5... wait, does it? It knows t==5, and t is a *variable* holding the value. After `t = (s16)(a1|0x10000)`, the new t is a different expression. The compiler knows a1's low 16 bits? It knows t_old = (s16)a1 = 5. So a1's low 16 bits are 5. Does gcc's cse track that? Probably via the equivalence t_old ↔ sign_extend(subreg a1), and t_old == 5. To fold `(s16)(a1|0x10000)`, it would need to reason: (a1|0x10000) low16 = a1 low16 = 5. That's plausible via fold_rtx but maybe not. Worth a test.

If it folds, no gain. If it doesn't, we get extra instructions.

I'll test one: m5 = `t = (s16)(a1 | 0x10000);` before the test. And m6 = `if ((s16)(a1 | 0x10000) != 3)`.

Actually, these change t's value? (s16)(a1 | 0x10000) = (s16)a1 (since bit16 doesn't affect the low 16) → yes value-preserving.

Let me test.
