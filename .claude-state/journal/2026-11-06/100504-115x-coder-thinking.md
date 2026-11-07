---
ts: 2026-11-06T17:05:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mrFpYnVg3RCeM3WqV7g1
---
z8 = 10, same as z6. Still `bgez s0` vs `bgez v0`. So even with if/else, the compiler compares n (s0) instead of q. That's cse/scheduling: after `move s0,v0` in the delay slot, the comparison uses s0.

The target's bgez tests v0. The difference: in the target, the comparison insn `bgez v0` is followed by `move s0,v0`. That's exactly the delay-slot fill: the branch tests v0, and the copy n=q fills the delay slot. In mine, the copy is before the branch and the branch tests s0.

This is a scheduling/ordering difference: mine's RTL order might be [n=q; if(q<0)...] with the copy first; the target's RTL has the branch first with the copy in the delay slot. Since sched1/dbr fill the delay slot, the RTL order matters.

Actually, mine's `move s0,v0; bgez s0; nop; addiu s0,s0,3` — the branch tests n. So cse propagated q→n. In the target, the branch tests v0 (q). So in the target's RTL, the branch condition used q, not n.

Since the pinned version has n as a hard reg, cse can't propagate it into the branch (a hard-reg copy is not a value propagation candidate? Actually cse does track hard regs but a set to a hard reg invalidates...). So the pinned RTL keeps q in the branch.

To reproduce, we need the copy `n = q` to not be a copy-propagatable temp. Hmm. What if n is not a copy of q but computed, e.g. `n = q + 0;`? That's an identity launder.

Alternatively, make the branch test a value that cse can't equate: e.g. test `q` after q has been modified? no.

Hmm, what if we make n's copy happen AFTER the branch in source order:
```
if (q < 0) n = q + 3;
else n = q;
```
We tried; the compiler moved the copy before.

What about writing the branch on a different variable that cse can't tie to n: e.g.
```
if (q & 0x80000000) n = q + 3; else n = q;
```
That changes the comparison instruction (andi vs bgez) — not target.

OK, let me think about the target's RTL once more. The target's `%4` expansion came from `q % 4` in the original source (not the manual expansion). The expansion is:
```
temp = q;
if (q < 0) temp = q + 3;
temp = temp >> 2;
temp = temp << 2;
result = q - temp;
```
The branch tests q (v0), and temp (s0) is the copy. So the temp is s0, and the branch uses q — exactly the `%` expansion. And the temp is s0, not v1. Why? Because in the original, the temp was live across a call OR the allocator chose s0.

Let's test: what does the target's `%4` temp's liveness look like in the RTL? If the temp is a compiler temp, its live range is from the copy to the subu. The subu is at 8ea4, before the sign jal. So no crossing.

Hmm, but maybe in the RTL the sign rand is evaluated BEFORE the subu: `if ((rand() & 1) == 0) m = -m;` — the sign rand is a separate statement after `m = ...`. So the subu is before.

I'm now fairly convinced the pin is load-bearing for the register choice and no plain-C move reproduces it... but the task says to try. Let me consider the wall list: "global-hardreg-reserve" is a wall tag: "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". Our case is the opposite: the pin GIVES the temp s0. Hmm.

Wait, maybe I'm wrong that the target's `%4` temp is s0 because of the pin. Let me check: does the pin affect the `%4` temp at all? The pinned variable n IS the temp (the source's n is used in the manual expansion). So the pin directly pins the temp. Yes.

The real question: can real C make the compiler allocate this variable to s0? The answer might be: make the variable live across a call. In z5/z6, n was in s0 (the %4 part) because n was also used for the first modulo (crossing a call). That worked! The remaining issue is just the bgez operand.

So: combine the z3 idea (n used for the first modulo, making it cross a call) with the manual expansion, and fix the bgez.

z6 already has n crossing a call? Let me check z6: it did NOT use n for the first modulo (the source still has `func_8012B0B4(&sp10, rand() % 0x1000, ...)`). Yet z6's n was in s0! Why? Because z6 reuses n for the result and the shift, and n is live across the sign call? Let me see z6's first comp: `move s0,v0; bgez s0; ...; subu s0,v0,s0; jal; sll s0,s0,0x10` — n holds the result across the sign call → n crosses a call → s0. Yes!

So z6's n is in s0 because the result (n) is live across the sign call. The remaining diff is the bgez testing s0.

Now, in z6, the bgez tests s0 because cse replaced q with n. In the target, the bgez tests v0. 

Can we prevent cse from replacing q with n in the comparison? The copy is `n = q`. If the comparison is `q < 0` and q is later used (`n = q - n`), cse might prefer q... it chose n.

Idea: make the copy `n = q` happen in a way that cse treats as a real definition: e.g. `n = q + 0;` — identity. Not allowed.

Idea: use the value differently: `if (q < 0) n = q + 3; else n = q;` — tried (z8).

Idea: compute the sign test from n after assigning: `n = q; if (n < 0) n = n + 3;` — that's what we have (the test on n is what mine does; the target tests q). Hmm, mine matches the source `if (q<0)` by testing n because cse equated them.

What if we keep q and n as *different values* by making n = q + something that folds to 0? identity launder.

What if we test `q` in a way that's not equivalent to n: e.g. the source `if (q < 0)` — the compiler's cse sees n=q and rewrites. In the target (pinned), cse didn't rewrite because n is a hard reg.

Hmm, so maybe the fix is to prevent the copy propagation by making the copy a *use* in a different mode or with a barrier... 

What if the variable n is assigned from q in a different basic block? E.g.:
```
q = rand();
if (q < 0) {
    n = q + 3;
} else {
    n = q;
}
```
z8 tried; cse still tied them.

What if we declare n as a different type (e.g. u32)? Then `n = q` is a copy; the comparison `q < 0` stays on q? Let's try `u32 n;` — but then `n = n >> 2` is a logical shift (different insns: srl vs sra). No.

What about making the comparison use a separate variable:
```
q = rand();
s32 qq = q;
n = qq; ...
```
Hmm.

Let me look at what cse does: it replaces uses of q with n (the copy destination). To block this, the copy's destination must be "not cheaper". 

What if n is assigned AFTER the comparison in the source but before its uses? That's what the if/else does.

Alternatively: test q via a *different expression* that cse can't rewrite, e.g. `if (q < 0)` vs `if (q & 0x80000000)`. Different insn.

Hmm, let me look at the actual RTL of z6 vs target for the branch. Maybe the difference is in *scheduling* (the copy placed before the branch by sched1), not cse. In z6's final code: `move s0,v0; bgez s0; nop; addiu s0,s0,3`. The branch tests s0. If the RTL had the branch on q (v0) and the copy after, sched1 wouldn't reorder the branch to test s0. So it's cse.

Let me check the z6 RTL dump to confirm cse rewrote the branch. Actually, let me try a different formulation that keeps q's value in the branch: make n's copy from a *computation* that cse won't fold, e.g.:

```
q = rand();
n = q;
if (q < 0) n = q + 3;
```
→ cse ties n=q. 

What if we swap: `if (q < 0) { n = q + 3; } else { n = q; }` and then use `q` in the subtraction — cse ties them anyway.

I think we may need a different lever-free move entirely. Let me look at the wall candidates: maybe this is a WALL. But before that, let me try one more: what if the variable n is used in BOTH computations AND for the first modulo (one pseudo crossing calls), with the `%4` expansion as the natural `q % 4` (so the branch is on q and the temp is the compiler's)? Then the temp is a separate pseudo (v1), not n. Hmm.

Wait — what if the `%4` temp is the SAME pseudo as the first modulo's temp because both are `rand() % K` compiler temps that cse/global-alloc merged? No, they're different values.

Let me try: `n = rand() % 0x1000;` for the first (n crosses a call, s0), and for the %4 use the *manual expansion on n* — but the bgez... 

You know what? Let me just test the "n reused for the first modulo + manual %4" combo (z3 + z6):
```
n = rand() % 0x1000;
func(&sp10, n, rand() % X);
...
q = rand();
n = q;
if (q < 0) n = q + 3;
n >>= 2; n <<= 2;
n = q - n;
n <<= 16;
if ((rand()&1)==0) n = -n;
store n;
```
The first modulo's n crossing the call might change the expansion's shape (z3 showed v1 intermediates, worse).

Hmm. Time: ~10:10, 16 min. Let me try a couple more and then decide.

Actually — an important thought: in the target, the bgez tests v0 (q) and the copy `move s0,v0` is in the delay slot. That's the *natural* delay-slot fill of `bgez v0, L` + `n = q`. The RTL order: branch first, then the copy? No — the copy must execute before... the delay slot executes before the branch, so `move s0,v0` in the delay slot means the copy happens unconditionally before the branch. In RTL: [set n=q] [branch if q<0]. So the copy is BEFORE the branch in RTL. The dbr pass moved it into the delay slot. And the branch tests q (v0).

In mine (z6): `move s0,v0; bgez s0; nop; addiu s0,s0,3` — the branch tests s0, and the delay slot is nop (the addiu is after). So cse replaced q with n in the branch condition.

Why would cse do that? `n = q` then `if (q < 0)`: cse sees q's value is in n (a copy). It may substitute the *register with more uses* or the one that's "cheaper". In the target, n is a hard reg — cse doesn't substitute hard regs into comparisons? Hmm.

To stop cse: make the copy not a pure `n = q` but e.g. `n = q;` inside a block after a label? cse works per EBB; a label might split the EBB. If we put the copy in a separate EBB (e.g., after a conditional), cse can't propagate across. But the branch is conditional...

Hmm, what if the order is: branch first, copy in the taken/fall path? 

Let me try: `if (q >= 0) n = q; else n = q + 3;` — same as z8 with inverted condition. The branch tests q (v0) with bgez? `if (q >= 0)` → bltz v0 to else. Target has bgez v0 to the addiu path. Hmm.

Let me just try a few permutations quickly with sc.sh and see if any lands on 0. I'll generate a batch:
- z9: `if (q >= 0) { n = q; } else { n = q + 3; }`
- z10: `n = q + 3; if (q >= 0) n = q;`
- z11: `n = q; if (q < 0) n = q + 3;` with n declared `s32 n;` but used with a cast at the store? no.

Actually z10: `n = q + 3; if (q >= 0) n = q;` — the copy is in the taken path. Hmm.

Let me think about which C produces `bgez v0, L; move s0,v0; addiu s0,v0,3`:
- bgez v0, L → if q >= 0 goto L
- delay: move s0,v0 (n = q)
- addiu s0,v0,3 (n = q+3) — fall-through for q<0
- L: ...
So the code is: n = q; if (q < 0) n = q + 3; — the copy unconditional, then the branch. The delay slot holds the unconditional copy. RTL: [n=q][branch q<0 -> fallthrough addiu][addiu]. Sched1/dbr put the copy in the delay slot.

In mine, cse replaced q with n in the branch. To prevent, maybe make n's type `s32` but the assignment `n = q` not recognized as a copy because of a mode/type difference? E.g. `q` is `s32` and n is `s32` — same.

What if n is declared as `unsigned int`? Then `n = q` is a copy with a mode conversion (SI to SI, no-op) — cse may still equate.

Hmm, what about making the comparison use q AFTER n is modified? No.

Let me try adding a `// !FAKE`-free real statement between the copy and the branch, e.g. nothing.

OK, alternative: prevent cse from propagating by making n's copy happen in a different EBB: 
```
q = rand();
n = q;
if (q < 0) n = q + 3;
```
If we insert a label/branch between `n = q` and the if... e.g.:
```
n = q;
if (0) { }
if (q < 0) n = q + 3;
```
The empty if is folded away.

Hmm.

Let me look at the actual cse dump for z6 to see if it's cse or combine. Maybe it's the *scheduler* that reordered the branch to use n. Let me dump z6's jump/lreg. Actually, the branch instruction in the final code tests s0 — that's determined by the RTL before scheduling. Let me check the z6 .rtl dump.

I'll dump z6 and look at the branch insn.

Actually, time check: 16 min. Let me do this one diagnostic then decide.
