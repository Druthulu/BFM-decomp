---
ts: 2026-11-06T15:13:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rL42gRZhHdXQC4UCvtQM
---
Same as i1: the li is one slot later in mine. Everything else matches.

So I need `li a0,2715` before the ori. The ori and li are both before `or`.

What if the first argument is materialised earlier because of a dependency? The li a0 is a constant. In target it comes first.

Hmm, what if I write the call's first arg as a variable declared earlier, e.g. `s32 id = 0xA9B;` at the top and `func_8002D4C8(id, ...)`. Then the li is born at the declaration (early) — but it would then be scheduled... the li might be hoisted way up (sched1 birth boost) — could change a lot. But worth a try? It adds a variable (decl) but no insn.

Actually careful: adding `s32 id = 0xA9B;` at the top gives a new pseudo; local-alloc might put it in a0 early. The li would then be born early. Risky but cheap.

Alternatively, in target the li a0,2715 at 4b90 is right after the branch target (4b90). Mine has ori there and li at 4b92.

What if I reorder so that the ori comes from the arg expression (target spelling) and the 2nd set is a *different* vol def placed after the branch... 

New idea: `vol = vol | 0x3000;` placed AFTER the call? No.

What if the 2nd set is `vol = vol | 0x3000;` and the call uses `(vol | sx) & 0xFFFF` — the ori is before `or`. In target the ori is also before `or` (4b94 ori, 4b98 or). Only the li position differs.

So I need to move the li one slot earlier, i.e. before the ori. sched1 picks by priority; the li has lower priority than the ori. To raise the li's priority: make it part of a longer chain. E.g. if the li fed something else...

What if the first arg is `(0xA9B & 0xFFFF)`? Same.

What if I swap the call's arg order? No, changes semantics.

What if the first arg is spelled `0xA9B + 0`? folded.

Hmm, what about making the ori LOWER priority by making its chain shorter... The ori feeds `or` which feeds `andi` which feeds the jal. If the andi weren't there (mask dropped), the ori's chain is ori→or→jal = 2, li→jal = 1. Still higher.

In the target, why is the li first? Maybe because in target the ori is not in the same scheduling region... or because sched1's priority for the li is boosted by the birth rule.

Alternatively maybe in target the ori is scheduled late because vol (a1) has a long path from the mfhi. Hmm, but sched1 doesn't care about operand readiness beyond deps.

Let me try: make the call's first argument a variable (`s32 id = 0xA9B;` declared at top of function). If the li is born at the top, it'd be hoisted near the top of the function (bad). 

Better: put the li's birth right before the branch? Hmm.

Alternative: use `func_8002D4C8(0xA9B, ...)` but make the second arg's ori dependent on something later, e.g.:
```
sx = sx << 8;
func_8002D4C8(0xA9B, ((vol | sx) | 0x3000) & 0xFFFF);
```
with `vol = vol | 0x3000;`? no.

Hmm, what if the ori is placed AFTER the `or`? i.e. `(vol | sx) | 0x3000` — then ori comes after or. Target has ori before or. No.

Let me think about the actual scheduling: sched1 is a list scheduler; it picks the highest-priority ready insn. Priorities are computed by `priority()` = the length of the longest path to the end of the block, with weights. The jal is at the end. li a0 → jal: 1 link. ori → or → andi → jal: 3 links. So ori first. But target has li first!

Unless in target the ori is NOT in the same basic block as the jal... it is.

Unless target's `li a0,2715` is not the call arg but something else. 0xA9B = 2715. Yes it's the arg.

Hmm, maybe sched1's priority has a "birth" boost for insns that are the first of a chain... In sched.c, `priority()`:
```
  /* We use the following heuristics: ... */
  for each insn: priority = 0; ... insn_dep ...
```
There's also `SCHED_S_TASK`... Actually gcc 2.7.2 sched.c priority():
```
      /* Add the length of the longest path to the end of the block */
      ...
      /* Adjust for insns that are "born" here (birth boost) */
```
Hmm, the "birth boost" mentioned in moves.md ("sched1 birth boost") suggests sched.c has a rule boosting the priority of the insn that births a value used far away.

Whatever. Let me try a few empirical flips:
- k1: first arg as a temp variable assigned just before the call: `s32 id = 0xA9B;`? adds a decl but the assignment is a set. Place `s32 id = 0xA9B;` at the top (init at decl) and call `func_8002D4C8(id, ...)`.
- k2: `vol = vol | 0x3000;` and call with `(vol | sx) & 0xFFFF` but move the mask to vol: `vol = (vol | 0x3000) & 0xFFFF;` (ori+andi as 2nd set... then the call `(vol | sx)` without mask → 2 extra insns but maybe folded).

Let me try k1.

Actually, wait. Another thought: what if the `li a0,2715` in target is scheduled before the ori because in target the ori is a *zero-width-ish* ... no, ori is real.

Let me try k1 and also k3: put `vol = vol | 0x3000;` BEFORE the `sx = sx << 8;` and ALSO move the mask... 

Let me just try k1.
