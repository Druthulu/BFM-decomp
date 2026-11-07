---
ts: 2026-11-06T09:41:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6IF3Th4mCggGScL5rlQS
---
Volatile store doesn't help either (score 2). So the store's scheduling isn't anchored by volatility.

Hmm. So what anchors it in the target? Let me reconsider: maybe the target's copy is NOT the call arg copy but a *different* move. Target insn 38 `move a0,s0` — then 39 `lw v0,68(a0)`, ..., 42 `jal func_801553C0` with a0 as the arg. So a0=s0 serves both.

In our build, the copy at 37 also serves both.

What if the original C had the RMW through a *separate* variable that forced a copy *after* the store, and the call arg reuses it? E.g.:

```
*(u16 *)(s0 + 0x188) = 0;
{
    s32 *p = (s32 *)s0;      // copy here (after the store)
    p[0x11] = p[0x11] & 0xFFFFFFFB;
    func_801553C0((s32)p);
}
```
Then the copy `p = s0` is a real statement after the store. sched1 could still hoist it (no dependence on the store). But if the copy is a *real* C copy, maybe the compiler keeps it (it's an insn with a birth). We tried u1/u2/v3/v5 variants — score 2.

Hmm, wait: in u1/v3 the pointer p was assigned after the store but the compiler coalesced p with s0 (no copy insn) or hoisted.

What if we make p *volatile*? no.

Let me look at the target's copy: is it possible that in the original C, s0 was loaded into a0 *by the RMW itself* because the RMW was written as a call-like expression? Hmm.

New idea: what if the original C's store was *after* the call in source but the call is `func_801553C0(s0)` and the RMW before the call, with the store *between*? No.

Let me reconsider the problem completely: maybe the real C used a *different variable* for the tail: e.g., the original might have been:

```
s32 s0 = *(s32 *)(s1 + 0x4C);
...
*(u16 *)(s0 + 0x188) = 0;
s0 = s0;                       // no
*(u32 *)(s0 + 0x44) &= ~4;
func_801553C0(s0);
```

Hmm.

What if the RMW is written via the *same* expression as the call: `func_801553C0((*(u32 *)(s0+0x44) &= ~4, s0));`? Ugly.

Let me look at this from the "which insn order does sched1 produce for different source orders" angle. The scheduler delays stores. In the target, the store came first. Maybe in the target's build, the store was *not* in the same basic block as the copy? The store is at 37 after the join label (83). The copy at 38 is in the same block. Hmm.

Unless the target's store was in the *previous* block (before the join)! Let me check the target's control flow: insn 36 `sw zero,388(s0)` is the else branch's store, then 37 `sh zero,392(s0)`. Is insn 37 in the join block or in the else block? If the 0x188 store were at the *end of the else branch* (inside the else), and also needed after the if-branch... no, the source has it once after the join.

But wait — maybe the original C had the 0x188 store *inside both branches* (duplicated)? The target would then show two sh instructions (one per branch). Target has one at 37. Hmm, but if it were in the else branch only, the if-branch path would skip it. The target's if-branch path (insns 30-35) jumps to 0x94 (insn 37?) — insn 34 `j 9ff8` = func+0x94 = insn 37. So the if-branch jumps to insn 37 (the store). And the else branch falls through 36 → 37. So the store at 37 is after the join. Yes, join block.

Hmm, so the join block starts at insn 37 (label 83) and contains the store, copy, RMW, call. sched1 scheduled the store first there. In our build, the same block starts at the store but sched1 moved the copy above it.

Wait — actually in our build, is the copy in the same block? The lreg dump's "Basic block 7 from 83 to 118" contains 86, 88, 91, ... and the copy 99. Yes.

The difference is purely sched1's hazard tie-break. In orig, the asm's presence changed the ready list. Without it, the scheduler chose the copy first.

What real C raises the store's priority above the copy's? INSN_PRIORITY of the store: it's computed in `priority()`: an insn with no dependents gets priority 1. The copy: 1. Tie-break: `rank()` compares priority, then... let me look at rank() in sched.c.

Actually the trace says "insn 86 has a greater potential hazard, now 86 97" — so rank() preferred 97 (the copy) because 86 has a hazard (it's a store). rank():

```
static int rank(s1, s2) { ... if (s1->priority != s2->priority) return ...; if (s1->cost != s2->cost) ...; if (s1->ref_count != s2->ref_count) ...; ... }
```
Let me look at the actual rank function to see the store penalty.
