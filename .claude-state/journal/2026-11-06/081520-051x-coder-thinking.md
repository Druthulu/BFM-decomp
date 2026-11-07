---
ts: 2026-11-06T15:15:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J4kllhszmGeQn3sDgk4d
---
Still the same: li one slot later. The `id` variable didn't change the schedule (sched1 still puts the li after the ori).

Let me look at the actual instruction sequence around there to know exactly what mine does. Mine at 220,221,222: likely `or a1,a1,a2`? Let me get the disassembly. Use --keep once more (costly but informative).

Actually the diff format "insert mine[221:221] target[221:222]" means target has li at 221 and mine doesn't; "delete mine[222:223] target[223:223]" means mine has li at 222 and target doesn't. So mine's insn 221 = target's 221's other content... i.e. mine has an extra insn at 221 that target has at 222, and li shifted.

Hmm: it says at position 221 target has [li a0,2715] inserted relative to mine; at 222 mine has [li a0,2715] deleted. So mine: ... [220]=X, [221]=Y, [222]=li a0, target: [220]=X, [221]=li a0, [222]=Y. So mine has Y before li, target has li before Y.

Y is probably `ori a1,a1,0x3000`.

So mine = ori, li; target = li, ori.

To flip: lower the ori's priority or raise the li's. 

What if the li is needed by something earlier, e.g. if I write the call's first arg as `0xA9B` but the call is `func_8002D4C8(0xA9B, ...)` — the arg is loaded into a0.

Idea: make the ori part of a longer chain by moving the mask: `vol = (vol | 0x3000) & 0xFFFF;` → ori + andi as the 2nd set (2 insns), then the call arg `(vol | sx)`. Chain: ori→andi→or→jal = 3, li→jal=1. Still ori first.

Idea: make the li part of a longer chain: the first arg feeds only the jal. Unless... we compute the arg as a variable used twice? no.

Hmm, in the target, why is li first? Maybe because in target's RTL the `ori` is scheduled later due to a *dependence on a1 being ready*. a1 (vol) is ready at 4b68. Both are ready.

Maybe sched1 in the target ordered li first because the li was born earlier in the RTL insn stream and priorities were EQUAL. If priorities are equal, sched1 picks by insn order (the queue is a sorted list; ties broken by insn number). So if both have the same priority, the earlier-born wins.

What's the priority? In gcc 2.7.2 sched.c:
```
static int priority (insn)
{
  ...
  /* We use the following heuristics: ... */
  ...
  /* Compute the longest path to the end of the block */
  ...
  /* insns that set a register used by a later insn get +1 */
```
There's a specific rule: `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == SET && REG_P (SET_DEST(...)) && ...)` — the "birth" boost: insns that set a register which is used after the block get a boost of 1? In sched.c:

```
	  /* An insn that is a "birth" of a register used outside the block gets priority. */
```
Hmm.

Empirically: in target li before ori; in mine ori before li.

What if I give the ori a *longer* chain so it's even earlier? That's the wrong direction.

What if I make the ori come AFTER the `or`: `func_8002D4C8(0xA9B, ((vol | sx) | 0x3000) & 0xFFFF);` with `vol = vol | 0x3000` gone... but then vol has 1 set (plain drop, 30).

Hmm, but wait: what if the 2nd set is the `& 0xFFFF` on vol:
```
sx = sx << 8;
vol = vol & 0xFFFF;      /* 2nd set, value-preserving */
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
Then the andi is the 2nd set. But the andi would be stolen into the delay slot (like c_u16) → score 2 with the delay issue.

What if the 2nd set is `vol = vol | 0x3000;` placed AFTER the `sx = sx << 8;` (i1) — that's what we have.

New idea: what if we make the ori's operand (vol, a1) *needed* by the li? no.

What if we make the li's chain longer by making the first arg a computed value: `func_8002D4C8(0xA9B | 0, ...)` folded.

Hmm, what about `func_8002D4C8(0xA9B, ...)` where 0xA9B is passed as `(s32)0xA9B`? folded.

Idea: what if the ori is born after the li in the RTL because the arg expansion order? In gcc, for a call with args (a0=0xA9B, a1=expr), expand_call evaluates args in reverse order (last first) if PUSH_ARGS_REVERSED. MIPS defines PUSH_ARGS_REVERSED? For MIPS with the O32 ABI, args are passed in registers; gcc expands them in order... 

Given target has li first, the li is born first → args expanded in source order (first arg first).

In mine, the ori is a separate statement born before the call → before the li.

So: put the ori in the arg expression (so it's born after the li) — but then it's the target spelling with 1 set of vol (score 30). UNLESS the ori in the arg still constitutes a "2nd set" — it doesn't.

Wait... unless the ori in the arg CAN be a 2nd set if vol is otherwise set... no, the arg's ori is a use, not a set.

Hmm, so we need vol's 2nd set to be born AFTER the li (the first arg). The only way: put the 2nd set inside the second argument's expression — j1 did that: `((vol = vol | 0x3000) | sx) & 0xFFFF` → still score 2 with li after ori. Hmm, because the assignment is evaluated during the second arg's expansion, which happens... the second arg is expanded after the first? Then the ori is born after the li — but sched1 still ordered ori first (priority).

So the birth order doesn't matter; priority does. The ori has a longer chain (ori→or→andi→jal).

In the target, the ori is at 4b94 and the li at 4b90: target's ori chain: ori→or→andi→jal (3), li→jal (1). Same as mine. Yet target ordered li first!

Unless in the target the ori is NOT before the `or` in the chain... it is (or a1,a1,a2 uses a1).

Hmm, so why? Maybe because in the target, the ori's source a1 (vol) is produced by `subu a1,a0,v1` at 4b68, and sched1 had to wait... no, it's ready.

Could the difference be that in the target the ori is born in a *different* basic block? If the ori were born before the branch (in the branch block), it couldn't be scheduled after the branch.

Wait — actually! In the target, maybe `ori a1,a1,0x3000` is scheduled BEFORE the branch? No, it's at 4b94, after the branch at 4b80.

OK, empirical: let me try making the ori's chain shorter by dropping the andi (mask) and instead making vol's mask... 

Alternatively, accept the ori's position and instead flip by giving the li an extra use: e.g. `func_8002D4C8(0xA9B, ...)` → make the first arg used twice? no.

Hmm, what about making the ori's result need a `move` (register copy) that lengthens the chain? no, lengthens the wrong one.

What if the ori's input is vol (a1) and the `or` uses a1 — so the ori is in the chain. If instead the 2nd set were `vol = vol | 0x3000` but the call arg used a DIFFERENT variable for the vol part... e.g.:
```
vol = vol | 0x3000;
func_8002D4C8(0xA9B, (vol | sx) & 0xFFFF);
```
Here ori→or→andi→jal.

If the mask weren't there: ori→or→jal (2) vs li→jal (1). Still ori first.

Unless the li has priority 2: what if the first arg's li is followed by... 

Hold on, maybe sched1's priority counts the number of insns in the path, and both paths end at the jal. Actually priority() in sched.c computes for each insn the length of the longest path *from the beginning of the block* (depth), not to the end? No — sched1 schedules backward (from the end), so it uses "priority" = longest path to the end.

Let me look at the actual sched.c source at tools/reference/gcc-2.7.2/sched.c to understand priority and the tie-break. That could tell me how to flip it. But is it worth it? I'm at ~08:20, 20 min in.

Actually — simpler empirical approach: try moving the `sx = sx << 8;` and ori around, and try `vol |= 0x3000;` (compound assign) which might be treated differently. Also try making the ori's target a different variable:
```
s32 v2 = vol | 0x3000;
```
No.

Let me try `vol |= 0x3000;` (compound) — in gcc, compound assignment may generate slightly different RTL (the same, but the assignment node is MODIFY_EXPR with the same target). Try.

And try `vol = (vol | 0x3000) & 0xFFFF;` with arg `(vol | sx)`.

And try putting the ori before the shift with the arg mask dropped.

Let me also try: `func_8002D4C8(0xA9B, (vol | sx | 0x3000) & 0xFFFF);` + `vol = vol | 0x3000;`? redundant.

Let me run a batch of 3.
