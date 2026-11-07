---
ts: 2026-11-06T08:28:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vpx6ov2bpSZyn6UZ9nT1
---
vX3 emits exactly the target bytes: `li v0,1` and `move v0,zero`. The `for (; rv; rv = 0) {}` loop was compiled to... let me see: the code after the calls is `li v0,1` then epilogue. Where's the loop test? It seems the loop was optimized: the compiler kept the rv materialization (because rv is used in the loop test) but then eliminated the loop's branch entirely? That's odd but possible: the loop `for(;rv;rv=0){}` — GCC might transform it and realize the only effect is setting rv=0 if nonzero, which is dead, so it removes the loop but the rv *definitions* (li v0,1 / move v0,zero) remain because they're the rv values that feed the (removed) test? Hmm.

Actually, the emitted code shows no loop branch. So the loop body/test vanished, but the rv=1 and rv=0 assignments remained (they're the source-level rv definitions). So the loop's presence prevented flow from deleting rv (the use in the loop test existed at flow time), and later passes removed the loop itself. That's a lever-like trick: a dead loop used to keep rv live.

Is this a legitimate "real C" close? It's a use of rv in a loop condition, which is real C syntax, but semantically it's a no-op invented solely to steer codegen. The brief forbids "a new lever of any kind" and the catalog refuses "an invented always-false condition, a dead store kept only to steer a pass". A dead loop is analogous.

Hmm. But the C0535 do-while is accepted as a codegen steer. The difference: do-while(0) is a standard idiom for a block, explicitly allowed with `// !FAKE: do-while`. Our for-loop is not an allowed idiom.

I think the expert would likely reject `for (; rv; rv = 0) {}` as a new keepalive-style lever. But it's a judgment call. Let me consider alternatives that are more clearly "real C":

What if instead of a dead loop, we use rv in a REAL branch that has an observable effect? E.g., the original might be:
```
if (cond == 0) { calls; rv = 1; } else rv = 0;
if (rv) { ... something the function does ... }
```
But the target has no extra code after.

Given the target's last instructions, the ONLY real use of rv would be as a return value (signature change). Any in-body use is a no-op. So the "close" requires a no-op use — which is a keepalive in disguise.

The task's grading: "MATCH = the kinds in <dir>/kinds gone". The kind is "keepalive". Is a dead for-loop a keepalive? It's not an asm/macro. The brief's lever-free definition: "no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." A dead loop is arguably a new lever.

I should be honest. Let me consider: the C0505 catalog explicitly says a "dead store kept only to steer a pass" is refused. A dead loop is the same category. I should NOT report vX3 as a MATCH; it's a lever (a codegen steer), not a real C close.

But wait — the brief's MOVES+ says "C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item)". The do-while is a dead loop too (runs once, empty body) used to steer cse1/sched1! And it's accepted. So a dead loop IS an accepted steer in this project, with the `// !FAKE: do-while` marker. The difference is the marker/idiom.

Hmm, so is `for (; rv; rv = 0) {}` acceptable if marked `// !FAKE: ...`? The brief only specifies the marker for do-while. Our for-loop isn't a do-while.

Let me think about what the do-while does: it splits a basic block in cse1 (a structural steer), not a data-flow use. Our for-loop uses rv in a condition (a data-flow use) to keep it live — that's a keepalive by another name. The catalog's "dead store kept only to steer a pass" refusal applies.

I'm inclined to treat vX3 as NOT a legitimate MATCH and report WALL (best 3). But the score is 0 and the kinds (keepalive) are gone... The expert's rule: "MATCH = the kinds in <dir>/kinds gone" and "no new lever of any kind". If the expert considers the for-loop a new lever, it's not a MATCH.

Hmm, but the results.tsv `result` is my judgment. The brief says the expert routes questions. I could report it as MATCH with a note, or WALL with the 0 noted. Given the uncertainty, let me look for a more clearly-legitimate close first: a real use of rv that has an observable effect but no extra bytes. 

Idea: use rv as the loop condition of the EXISTING code? No.

Idea: what if rv is used in the `if` condition of the *first* if (v0 & 0x90)? No.

Idea: make rv the argument to `func_80147324(0x8E4)` in the first if? The first if already calls func_80147324(0x8E4). If the original's rv were passed... no, the target's call has a constant.

Idea: maybe the original code's rv is used in a `while` loop that the target doesn't have because it's optimized to nothing — but that's the same dead-loop issue.

Given the brief's explicit "no new lever of any kind" and the catalog's refusal of dead stores, I'll classify the dead for-loop as a lever and report WALL, BUT I'll record the score-0 dead-loop variant in notes and moves.md evidence so the expert can judge. Actually, the results row must have one result. Hmm.

Wait — let me reconsider. The do-while (C0535) is accepted and is a dead loop. Why is it not a "lever"? Because it's a *structural* steer (block split), a documented real-C technique. Our for-loop is a *data* use of rv. The catalog's accepted moves include "loop shape" — maybe a for-loop that uses the variable IS the loop-shape move! "loop shape" in the catalog means restructuring a loop (goto vs for), not inventing a dead loop.

Let me test whether a do-while with rv in the condition works and is more idiomatic:
```
do { ... } while (rv);  // uses rv, runs once if rv nonzero
```
That would add a branch (unless optimized). Let me test `do { } while (rv);` — it uses rv in the condition. If it scores 0 (the loop optimized away but rv kept), it's a do-while with a data use. Hmm.

Actually, the cleanest test of legitimacy: does the emitted code match the target with NO extra instructions AND the source use of rv is a real control-flow use? vX3 does. The question is whether the expert accepts it.

Let me look at the brief once more: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." — "keepalive macro or asm" specifically. A dead for-loop is not a macro or asm. But "no new lever of any kind" is broad.

The definition of "lever" in this project (from the AB_KINDS): pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. A dead loop isn't in that list. The catalog's "refused as closes" includes "an invented always-false condition, a dead store kept only to steer a pass, a pointer alias invented only to dodge cse". A dead loop is closest to "an invented always-false condition" — but our condition is `rv`, not always-false.

Hmm, `for (; rv; rv = 0) {}` — the condition is rv, which is 0 or 1. It's not invented always-false; it's a real test of rv. The loop body is empty and the increment zeroes rv. Semantically it's a no-op, but it genuinely reads rv.

I think the honest thing is to report this as a MATCH candidate but flag it clearly in notes and the log as a borderline "dead-loop use of rv", letting the expert judge. But the results row format has no room for "borderline". 

Alternatively, I can look for a use of rv that is clearly a real computation with an observable effect but 0 bytes. For example, the target's last store `*(u16 *)(s1 + 0x12) = v0;` — if rv were used in a comparison that sets a condition the code already computes... no.

Let me look at the target's `move v0,zero` in the delay slot: it's the else rv=0. The `li v0,1` is the if rv=1. If rv were used by a *later* conditional branch, the code would have an extra branch. The target doesn't. So the only 0-byte use is one that's optimized away after flow — a dead use. Any dead use is a lever-ish trick.

Given the task's purpose (find real-C closes), and the catalog explicitly allowing some steers (do-while), I'll make a judgment call: a dead `for (; rv; rv = 0) {}` is a *keepalive replacement* in real C, but it is semantically a no-op invented to keep a dead value — the catalog's refused category. I'll report WALL (best 3) and record the score-0 dead-loop variant in notes/evidence as a rejected close. Hmm, but the results row's `best` would then be 3, while a scored lever-free body reaches 0. That's contradictory.

Let me re-read the catalog refusal: "Refused as closes: an invented always-false condition, a dead store kept only to steer a pass, a pointer alias invented only to dodge cse." Our loop is an invented dead loop. I'll refuse it.

Actually, wait. Let me reconsider the whole thing: maybe the *intended* answer for item4 is indeed a dead-loop/keepalive-like construct, and the task expects it (since the signature can't change). The brief's MOVES+ explicitly cites C0414 (dead-reset cse-breaker — a DEAD STORE kept only to steer cse!) as a move that cracked 3 launders in G16x. So "dead store kept only to steer a pass" is cited as an ACCEPTED move in MOVES+ (C0414 is the dead-reset cse-breaker)! The catalog's refusal list says "a dead store kept only to steer a pass" is refused, but MOVES+ says C0414 (dead-reset, which IS a dead store) cracked items. Contradiction? C0414's dead-reset is a store that flow deletes before sched1 — it's a cse-breaker, accepted. So dead stores CAN be accepted when they're the documented C0414 technique.

Given that, a dead loop that keeps a value live could similarly be a documented technique (like the do-while). But it's not in the cookbook. The brief says "no new lever of any kind" — a dead loop would be a NEW lever (not in the catalog/MOVES+).

Hmm. This is a genuine judgment call. Let me look at whether the project has a precedent: search the cookbook/moves for "for (;" or dead loop patterns. Let me grep moves.md/cookbook for "dead loop" or "for (;".
