---
ts: 2026-11-06T12:26:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oImPYsYMcCb6FNtdq9G0
---
c1x (real assignment `a1v = arg1;` + barriers + keepalive + pins) = 2, same diff: andi v0,t3,1 vs andi a1,a1,1.

So with `a1v = arg1`, gcc puts a1v in t3 (the same as arg1's copy?) and the andi reads t3. Let me look at the top of c1x.

The diff says mine[2:4]: andi v0,t3,0x1 vs target andi a1,a1,0x1; bnez v0 vs bnez a1. So mine has andi v0,t3,1. Only 2 mismatches (v0→a1 x2, t3→a1 x1). Interesting: mine's andi input is t3.

What's at mine insn 1? Probably `move t3,a1` and then andi v0,t3,1. So a1v = arg1 compiled to move t3,a1 (the pin $5 not honored?) and andi v0,t3,1.

Hmm: a1v is pinned $5, so a1v should be a1. `a1v = arg1` → move a1,a1? gcc eliminated the self-move and gave a1v... Actually the pin forces a1v to $5. Then andi v0,a1,1 would be expected. But we see t3.

Maybe the pin was ignored because a1v and arg1 are copy-propagated (a1v = arg1 → a1v is arg1, pin lost). Then arg1's pseudo got t3 (because a1v's pin made a1 unavailable?) and the andi is v0,t3.

Hmm.

To get `andi a1,a1,1`, we need the andi's input in a1. Since a1v is pinned to a1, if a1v is a REAL value (not merged with arg1), gcc would compute `move a1, <arg1>` then andi a1,a1,1? But the target has NO move a1,x before the andi — it reads a1 directly. That's only possible if arg1 is already in a1, i.e., arg1's home is a1 (incoming) and a1v is a separate pseudo also in a1 (tied by the pin), so no move is needed and the andi reads a1.

So the requirement: arg1's home = a1, a1v (pinned a1) is a distinct value, and gcc must copy arg1 out (t3) for the later uses.

With `a1v = arg1` (real), gcc merges → a1v is arg1 → the pin applies to arg1's pseudo → arg1 gets a1! Then the later uses read a1 too, and the andi would be `andi a1,a1,1`... but we got t3.

Wait, maybe arg1 got t3 because the pin a1v→a1 forces arg1 (=a1v) to a1 only if the pin is honored for the merged pseudo. The output shows andi v0,t3,1, so arg1's home is t3.

Hmm, and where's `move t3,a1`? Probably at insn 1.

So gcc: arg1 pseudo → t3 (move at entry), a1v merged with arg1 → t3; andi v0,t3,1. The pin was dropped entirely (the pinned pseudo merged away).

To prevent the merge, the assignment must not be a plain copy... we're back to the launder problem.

BUT: what if we keep the launder's *effect* with a real second set that's semantically a copy? The only way gcc keeps two distinct values from the same source is a real computation.

IDEA: use `a1v = arg1 & 1;` (real) and keep the pin $5 on a1v! Then a1v is pinned to a1 and is a distinct value (andi). gcc must put the andi's result in a1: `andi a1, <src>, 1`. The src is arg1 (in a1 if arg1's home is a1). But arg1 must be copied out for the later uses (t3). Would gcc emit move t3,a1 then andi a1,a1,1? 

Let's test: a1v pinned $5, `a1v = arg1 & 1;`, first test `if (!a1v)`. Plus barriers/keepalive/pins. This is a real 2nd set with the pin (pin allowed to stay).

Let me build it from orig: replace the launder line with `a1v = arg1 & 1;` and the test `if (!(a1v & 1))` with `if (!a1v)`.

Also without the pins (fully lever-free) for comparison.

Let me test.
