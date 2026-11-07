---
ts: 2026-11-06T06:31:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WND4WufWGZh372KyNuZu
---
No luck. So item 1 = PARTIAL:launder with best 0 (p1.c as win.c).

Hmm, wait. Before settling, let me reconsider one thing: maybe the launder can be replaced by a **real 2nd set that is free** if the value's mode allows. What if `otz` were declared `s16` and used as `(s32)otz`? No.

Hmm, hold on! What about this: what if the *second* call's argument is `otz` but we assign the raw result to a `s16` variable `otzs` and pass `(s32)otzs`? The extension costs 2 insns... 

BUT WAIT: what if we pass the s16 value to the function and the *sign extension* folds into the arg setup? `move a0,s1` + `sll/sra`? No.

OK. What about the target having 162 insns and mine 161 — maybe there's another *free* insn I could add elsewhere that the target has... no, the diff shows only the missing pair.

FINE. PARTIAL:launder, best 0, win.c = p1.c.

Hmm, hold on. Actually, let me reconsider the *whole* approach for this item. What if the pp/pf/zpush allocation could be fixed WITHOUT the do-while — because then the structure would be plain and maybe the copy behaves differently? No, w0 showed 8 with the same missing move.

OK, record item 1.

Wait, one more consideration: p1 keeps the asm. The brief says "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had may stay". Here the kind is `launder` and we keep it → PARTIAL:launder. Good.

But hmm — the do-while I added is a new lever? Is `do{}while(0)` a lever of a kind? The kinds list is launder,pin. The do-while is marked `// !FAKE: do-while`, which the constraints explicitly allow ("`do{}while(0)` only with `// !FAKE: do-while`"). So it's an accepted move.

Now let me write win.c = p1.c, notes.md, and the results row.

Actually hold on. Let me reconsider one final idea for MATCH, because it's so close: what if we make the first call's result *live across a call* by restructuring loop 1 to move `func_8012E28C` ... no.

Hmm, what about making `func_801823D4` take the raw value AND the sorted value being used... 

Actually! Here's a thought: what if the argument to func_801823D4 is `otz` and the result is assigned to `otz`, but we ALSO pass `otz` as... no.

Let me try one last creative thing: **make the raw value used by the loop's `i++`**? no.

OK, finalize item 1 as PARTIAL:launder.

Actually hmm, wait. Let me reconsider: maybe a WALL with best 3 is "more honest" than PARTIAL with score 0 keeping the launder? The brief defines PARTIAL as "win.c scores 0 keeping only those levers" — p1 scores 0 keeping launder. That's exactly it. So PARTIAL:launder is correct and better.

Let me write win.c and notes.md, and the results row.

Row format: `dir file func kinds result best tries wall evidence`
- dir: func_80181E08__ov_SC06_025_jr_8017EEC4
- file: src/ov_SC06_025/ov_SC06_025_jr_8017EEC4.c
- func: func_80181E08
- kinds: launder,pin
- result: PARTIAL:launder
- best: 0
- tries: (count) — let me count: w0,w1,w2,w4,w6,b1,b2,b3,b4,b5,b6,s0-s13,p1,p2,p3,p4 = 4+1+6+14+4 = let me count exactly: w0,w1,w2,w4,w6 (5), b1,b2,b3,b4,b5,b6 (6), s0..s13 (14), p1..p4 (4) = 29. Plus w3 compile error. Say 29 scored tries.
- wall: for PARTIAL, a tag: "combine-copy-merge" (the residual mechanism). The brief says: "wall (WALL/PARTIAL) = a tag from walls.txt or a new `<pass>-<what>`". So `combine-copy-merge` (new, lowercase, pass-what). Good.
- evidence: gcc pass + mechanism ≤ 140 chars.

Evidence: "combine: (set otz v0)+(set a0 otz) adjacent, otz dead -> fold to move a0,v0; target's 2nd insn came from the asm use; pins cracked by do-while ref weight (pp pri 483->1290 > zpush 793)".

Let me keep ≤140 chars: "combine folds (set otz v0)+(set a0 otz) (otz dead, adjacent); plain C 2nd set folds at tree; pins cracked: do-while(0) loop depth gives pp pri 1290 > zpush 793" — that's ~165. Trim.

"combine: adjacent (set otz v0)+(set a0 otz) with otz dead folds to move a0,v0; no plain-C 2nd set (tree folds); pins cracked via do-while pp ref boost" — count: roughly 150. Trim more: "combine folds adjacent (set otz v0)+(set a0 otz), otz dead; plain-C 2nd set folds at tree; pins cracked by do-while(0) pp ref boost" ~137. Good.

Wait, but the evidence should be "gcc pass + mechanism". OK.

Now: should I keep trying for MATCH? Let me weigh: I have 4 more items. Two are 90/96 ins (small), two are 307/308 (large). Given the time, let me move on.

Actually, hold on. Let me reconsider one thing quickly — what if we DON'T need the raw value at all: what if `otz` is used as the arg to func_801823D4 *through the second call's return*? no.

Moving on. Let me write the files.

Actually, wait. One more idea just came to me: **what if the first call's result is passed to func_801823D4 as `otz` but the assignment `otz = RotTransPers4(...)` is followed by `otz = otz + (i & 0)`?** folds.

Or what about making the depth-sort call take a value computed from otz that combine can't simplify: e.g. `func_801823D4(otz, -0x1A)` → what if we pass `(s32)(u16)(otz & 0xFFFF)`? That's an andi — 1 insn extra, but the target... no.

DONE. Record.

Hmm, actually, hold on! Wait. Let me reconsider the possibility of putting the raw value in a *callee-saved register* by making it live across the call — what if we simply pass `otz` to func_801823D4 TWICE by changing the *second* argument to a value derived from otz that is folded... no, we established tree folding kills it.

What about `func_801823D4(otz, -0x1A)` where the second arg is `(s32)(-0x1A)` — no-op.

OK, finalize.

Let me now write win.c (= p1.c), notes.md, and append the results row.

Also, the brief says: "Per item append exactly one row to G23/results.tsv" and "after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (G23)`" to moves.md.

Let me do that now. One action per command: a results.tsv fix is its own step.

First copy p1.c to win.c.
