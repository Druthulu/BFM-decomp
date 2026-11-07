---
ts: 2026-11-06T15:11:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PbempLlBJ0yNHPwaR70H
---
In c_dw: vol's mult is first (mfhi t0 at 206) and pan's second (209-210) — the ORDER IS RIGHT (vol first, pan second)! But:
1. `t0` is used instead of `a2` (mfhi t0 vs mfhi a2) — the pan result register is t0 instead of a2.
2. Missing the `nop` hazard.
3. Score 16.

So c_dw has the right order but pan's result went to t0 instead of a2, and the mfhi for vol went to t0 as well... In target: vol's mfhi goes to t1, pan's to a2.

Hmm, c_dw: mfhi t0 for vol, then mult v0,a0, then mfhi t0 for pan? Both mfhi to t0. In target: mfhi t1 (vol), mfhi a2 (pan).

So the register assignment for the magic-mult results differs: mine uses t0 twice (reusing after death), target uses t1 and a2.

Hmm, t0 is $8 (a temp), a2 is $6.

Since sx/pan ends in a2 in the target, and the pan quotient's mfhi goes to a2... 

OK so c_dw is "close" in order but registers differ.

Combining: what if do-while(0) + the u16 cast? c_u16dw gave 236/18.

Hmm.

Let me step back and think about which of these is closest: c_u16 at score 2 (registers all correct, one delay slot off). That's really close.

The remaining difference: reorg stole the andi instead of the sll.

What if I make the sll *earlier in the fall-through block* so reorg prefers it? reorg scans forward and takes the first eligible. The andi is in the branch's own block (before the branch) — how did it get stolen?

Let me verify: maybe in c_u16 the andi at 4b84 is actually in the fall-through block because the branch got inverted: `bne a2,v0,4b8c` — taken = !=16 → 4b8c (sll). Fall-through = ==16 → li a2,15 at 4b88, sll at 4b8c.

So the delay slot at 4b84 executes on both. The andi must have been in the branch block (before 4b80) and stolen into the slot.

reorg.c: `fill_simple_delay_slots` — for a jump, it fills from the fall-through thread. But there's also the case where the delay slot insn comes from *before* the jump: in reorg.c, `fill_simple_delay_slots` has a loop over `next_trial` and there's a special case: "If this is a conditional jump, and the insn before it can be moved into the delay slot (because it's not needed on the taken path), do it" — this is the `maybe_never` / `fill_slots_from_thread` logic. Actually in reorg.c there IS code: `if (! INSN_ANNULLED_BRANCH_P (delay_insn) && eligible_for_delay (insn, 0, trial, flags))` scanning backward... 

The gcc 2.7.2 reorg.c has `fill_simple_delay_slots` which first tries `prev_nonnote_insn` (the insn before the jump) — yes! There's a block:
```
      /* See if we have a simple insn before the jump that can be moved into the delay slot. */
```
This is the "fill from before the jump" for the case where the jump is at the end of a block and the preceding insn is not needed on the branch path (it's a "eager" fill for unconditional; for conditional it requires the insn be dead on the taken path).

So: the andi (before the branch) is stolen. It's dead on the taken path? No — vol is used on both. But reorg checks whether the register is live at the branch target; if a1 (vol) is live at 4b8c, it can't steal. Hmm, unless it re-inserts the insn at the branch target ("steal and re-add"). reorg does that: it can move the insn into the delay slot and re-emit it on the other path if needed.

OK whatever. The practical question: how to make reorg not steal the andi?

If the andi's result (vol in a1) is live at the branch target, reorg would have to duplicate it — it does duplicate (that's why only one extra insn appears? no).

Hmm, actually in c_u16 there's exactly ONE andi before the branch, stolen into the delay slot. The taken path (4b8c) then uses a1 without the andi... that's wrong code! Unless the delay slot executes on both paths — YES, delay slots always execute. So the andi executes on both paths. Fine, no duplication needed.

So stealing is legal.

To prevent: make the stolen insn's register conflict with the branch's needs, or make it ineligible.

What if the andi were a *load*? On MIPS, a load in a delay slot is legal (no annul). reorg's eligible_for_delay in gcc 2.7.2 mips.h: `#define DELAY_SLOTS_FOR_EPILOGUE`, `eligible_for_epilogue_delay`. For ordinary delay slots, mips.h defines:
```
#define HAVE_cc0 0
#define DELAY_SLOTS_FOR_EPILOGUE 1
#define ELIGIBLE_FOR_EPILOGUE_DELAY(trial, slots_filled) ...
```
and generic `eligible_for_delay` checks: `if (GET_CODE (insn) == JUMP_INSN) return 0; if (asm_noperands(...) >= 0) return 0; if (GET_CODE(pat) == SEQUENCE) return 0; ... if (slots_filled == 0 && (get_attr_... ))`.

Hmm, in gcc 2.7.2's reorg.c:
```
static int
eligible_for_delay (insn, slot, trial, flags)
{
  if (num_delay_slots (trial) > slot) ...
  if (GET_CODE (insn) == JUMP_INSN) return 0;
  if (asm_noperands (PATTERN (insn)) >= 0) return 0;   /* asm can't go in a delay slot */
  if (GET_CODE (PATTERN (insn)) == SEQUENCE) return 0;
#ifdef HAVE_cc0 ...
```
So asm is ineligible — that's the launder's other role maybe.

Also `fill_simple_delay_slots` has the "insn before the jump" fill only if `! JUMP_P (prev)` and the insn is not a `USE` and `eligible_for_delay`, and importantly:
```
	      /* Don't use an insn that sets a register that is used in the jump. */
```
Hmm.

I can't easily control this. Let me consider a totally different body shape that avoids the reorg issue: what if the vol 2nd set is placed so that it's AFTER the branch (in the fall-through block), then reorg would put it first in the fall-through... same.

What if the extra insn is a `nop`-like insn that isn't stolen? no.

New idea: make the branch's delay slot content irrelevant by removing the if! `sx = (sx + 0xA0) / 0x14; if (sx == 0x10) sx = 0xF;` — the if is required.

Hmm, alternatively: what if the extra insn is a `move` (from a copy through a temp) that cse would merge... but if it's not merged, it's a `move` which reorg could steal too.

Let me try a different tack entirely: **the 2nd set on vol placed inside the if-block's true path is wrong; instead use the `do{}while(0)` + u16 cast in a smarter place**.

Or: accept 2 and try to fix by adding ONE more plain-C move that makes reorg prefer the sll. For instance, if the andi's operand a1 were also used by the branch target path... 

What if vol is used in the `sx == 0x10` comparison? e.g. `if ((sx & 0xFFFF) == 0x10)` — no.

What about making the final `& 0xFFFF` apply to vol only, earlier:
`func_8002D4C8(0xA9B, ((vol & 0xFFFF) | (0x3000 | sx)) & 0xFFFF);` — that's two andis.

Hmm, what about this: make the andi *needed* before the branch by using vol in the branch condition in a value-preserving way... 

Actually here's a clean one: swap the order so the cast's andi is needed for the branch! No.

Alternative: since reorg steals from before the jump when the insn is not needed at the target — if vol (a1) IS needed at the target, reorg might still steal (delay executes both ways). It always executes.

OK, radical idea: what if I make the pan division the one with a 2nd set and vol single-set, but ALSO get the order right via a dead-store trick? Meh.

Let me look at the problem from the "what does the target's C look like" angle: the original author wrote the launder because they needed the sched1 order. The lever-free crack in other shards for this exact situation (two magic multiplies, sched1 swaps them) was moves.md line 199: "func_8017FE9C | MATCH — dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL) give vol 2 defs, so the /160 chain schedules before the /20 chain". 

That's the recipe! A dead copy `vol2 = vol;` plus a 2nd def. Let me look at that more: "dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL) give vol 2 defs, so the /160 chain schedules before the /20 chain".

And line 212: "MATCH — the re-tie gives vol a 2nd SET ... plain C: `vol = vol | 0x3000;` right before the call — value preserved because the arg ORs 0x3000 and masks 0xFFFF".

So here: `vol = vol | 0x3000;` right before the call, value-preserving because the arg ORs 0x3000 and masks 0xFFFF! That's EXACTLY this shape: our call is `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);`.

If we do `vol = vol | 0x3000;` before the call and change the arg to `(vol | sx) & 0xFFFF`, the value is preserved: (vol|0x3000|sx) & 0xFFFF = ((vol|0x3000)|sx)&0xFFFF. Yes!

And it's a real 2nd SET of vol, placed late (right before the call). The ori a1,a1,0x3000 already exists in the target at 4b94! So this could merge perfectly: the target has `ori a1,a1,0x3000` then `or a1,a1,a2`.

In the target, `ori a1,a1,0x3000` is a separate insn: the arg `vol | (0x3000 | sx)` where 0x3000|sx is computed... wait, target: `ori a1,a1,0x3000` (a1 = vol|0x3000) then `or a1,a1,a2` (a2 = sx<<8). So the compiler already turned `vol | (0x3000 | sx)` into `ori vol,0x3000` + `or sx`. 

So writing `vol = vol | 0x3000;` before the call + arg `(vol | sx) & 0xFFFF` should produce the SAME instructions, with vol having 2 sets. 

But careful: fold's associate rewrite was mentioned as a lever: "the OR must be spelled `vol | (0x3000 | sx)`. fold's `associate:` rewrites (VAR|CON)|ARG1 to (CON|ARG1)|VAR, which is what puts `ori ...,0x3000` on VOL". With my change, `vol | sx` — fold may reassociate differently. But since vol already has |0x3000 applied in a previous statement, it's `or a1,a1,a2` directly. 

Let's try it! Place `vol = vol | 0x3000;` right before the call (after the shift) and change the arg.

Also the "dead copy vol2=vol" trick as a fallback.

Let me write the candidate.
