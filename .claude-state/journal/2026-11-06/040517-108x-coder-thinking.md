---
ts: 2026-11-06T11:05:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oTrJhpWoYQHwFeNJmsh4
---
Mine: `beqz v0,ff0; move a0,s0` — the delay slot is filled with the fall-through's `move a0,s0` (the call setup). The target: `beqz v0,ff8; addiu v0,s1,1` — the slot is the target's addiu.

So the difference is exactly what the comment says: with the asm fence, reorg stops the forward scan and fills from the target.

Real-C replacement for that... The fence is `__asm__("")` at the head of the if-body. A `do{}while(0)` won't emit an insn.

Hmm, what about a construct that emits a real insn but is C-legal and not a lever? Like a call to a no-op function? That changes the code.

What if the loop is restructured so the `i++` computation comes before the branch? E.g., compute `i++` at the end of the body but as a separate statement... it already is.

What if we swap the order: `w++; i++;`? Then the delay slot might be filled with w++ (addiu s2,s2,32). The target's slot is addiu v0,s1,1 (i++). So the target fills from the i++ computation.

What if `i++` is written as `i = i + 1;`? Same.

Hmm, what if we make the if-body's first insn be something reorg won't move, like a call? The call IS the first insn of the body. reorg's fill from the fall-through takes `move a0,s0` (the call arg setup). The target takes the addiu.

What if the call's argument setup is not movable? E.g., pass the args differently.

Honestly, this looks like a genuine dbr-delay-fill wall.

Let me record item 3's wall: best 4, tag dbr-delay-fill, evidence: "the if-body asm fence stops reorg's forward scan so beqz fills from the target (addiu v0,s1,1); without it reorg fills from the fall-through (move a0,s0); n=s16 fixed the outer cross-jump copy".

Wait, but the wall needs ≥30 tries on this item. Let me count: orig(1), base, v_sa, 10 x_*, 5 y_* = 17. Need 30. Let me score more variants: generate permutations of the loop body order (i++/w++/call) and a few n variants. Let me do a batch of ~15 more.

Also for item 4 (func_8018B238), I'll need 30 tries too. Time is a concern; I've been going ~1h50m. Let me be efficient.

Let me generate a batch of loop-order variants for item 3.
