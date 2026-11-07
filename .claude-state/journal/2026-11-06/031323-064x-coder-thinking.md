---
ts: 2026-11-06T10:13:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xvHb885pXzCMFubCeSGD
---
All good:
- 4 rows, one per item.
- win.c files have no asm/register levers.
- src mtimes are old (not modified by me; 01:19, 11:46, 23:48 are prior dates).

Wait, the mtimes show 01:19, 11:46, 11:46, 23:48 — could be from earlier batches. My run is today; I didn't write src. Fine.

Now, let me reconsider the results: all 4 are WALL. The task expects "write a lever-free body ... that scores 0" — but walls are acceptable per the process. However, the brief says DONE WHEN: "every item of G27/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." So WALL rows satisfy done. ✓

One more consideration: the brief says "Per item append exactly one row to G27/results.tsv (format under INTERFACES)." ✓

"after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (G27)`." ✓ (4 lines)

"Notes in <dir>/notes.md; do not stop between items." ✓

"LOG: phase-ends/current/logs/T11.cG27.md (timeline per item, moves that cracked, walls with evidence)." ✓

"RETURN: your final message starts with the bare word done (or blocked)... + ≤ 10 lines: per item dir result best wall; nothing else."

So my final message must start with `done`, then ≤10 lines: per item dir result best wall.

Let me produce:
```
done
func_8017D730__ov_SC06_006_jr_8017BEBC  WALL  best 19  wall flow-unused-result
func_80182420__ov_SC03_124_jr_80181B44  WALL  best 13  wall expand-void-return
func_80189E68__ov_SC05_017_jr_80188B1C  WALL  best 13  wall expand-void-return
func_8018A168__ov_SC04_018_jr_80188E1C  WALL  best 13  wall expand-void-return
```

Wait — the brief says "nothing else" after the per-item lines. Also, since "no commit", I don't mention a commit.

Before finalizing, let me reconsider whether I should try harder on item 4 to get a MATCH. The wall there is a dead computation. Could there be a real-C move that makes the target's dead computation *not* dead while adding zero instructions? Hmm.

Actually, let me reconsider the target's second branch once more. What if the original C's second branch is NOT a dead computation but something like:

```
if (rem == D_80185D04) {
    t = ...;
    v0 = ...;
    v1 = 0x7F - v0;
    if (v1 < 0x1F) v1 = 0x1F;
    func_8002D4C8(0x407, v1 & 0);  // ??? 
}
```
No, the target's delay slot is `move a1,zero`, so the second arg is 0.

Or maybe:
```
func_8002D4C8(0x407, 0);
```
and the v1 computation is a leftover from a macro that expands to both branches. But the target keeps it, meaning the source kept it live somehow.

Wait — maybe the target's second branch computes v1 and then the call's second arg is `v1` but the *first* branch's clamp is different, and the call is `func_8002D4C8(0x407, 0)` because... no.

Hold on, let me re-read the target's second branch delay slot: `1a3c: 00002821 move a1,zero`. Yes, a1=0.

But what if the original source is:
```
if (v1 < 0x1F) {
    v1 = 0x1F;
}
func_8002D4C8(0x407, 0);
```
and gcc's flow *doesn't* delete the `if` because v1 is a `register` variable? No, v1 isn't register in the target.

Hmm, actually maybe gcc 2.7.2 does NOT delete dead stores to pseudos in all cases. In b1, the whole block was deleted. Why would the target keep it? Maybe because the target's `v1` is also used *after* the call? Let me look at the epilogue again: 1a40 lw ra; 1a44 addiu sp; 1a48 jr ra; 1a4c nop. No use. So dead.

Unless... the target's v1 in the second branch is the *same pseudo* as the first branch's v1, and its live range extends across the second branch's call, making the computation "live" (the first branch's v1 value is live at the call?). No, the call clobbers caller-saved regs; v1 would be dead.

Actually, here's a thought: in the target, the second branch's `v1 = 0x7F - v0` and `if (v1 < 0x1F) v1 = 0x1F;` might be kept because the value is used by the *first* branch's clamp? No.

Alternatively, the target's second branch might be the result of *jump2 cross-jumping* or a shared epilogue where v1 is used for the return of the void function? No.

Wait — maybe the target's second branch is:
```
func_8002D4C8(0x407, 0);
```
and the v1 computation belongs to the *first* branch, but the block ordering puts it in the second branch due to code motion? No, the first branch already has its own computation.

I think the wall is real. Prior shard entries confirm flow-unused-result walls.

But hold on — maybe the trick is that the second branch is actually a *duplicate of the first branch* that the target's source wrote out (copy-paste), and the call is `func_8002D4C8(0x407, 0)` where the second arg is 0 but the v1 clamp is present because the source had `if (v1 < 0x1F) v1 = 0x1F;` and gcc kept it due to... the `v1` being the return value of the function? The function is void.

Hmm, one more: what if the second branch's `v1` computation feeds the *first branch's* clamp through a shared variable that gcc keeps live? The source has two separate blocks; if the second branch's v1 assignment is to the same variable and the first branch's `func_8002D4C8(a0, ...)` call is after, no.

OK, I'll accept the wall.

Actually, let me do one more experiment for item 4: what if the second branch's call passes `v1` as the first argument in the source but the compiler proves v1... no, target has a0=0x407.

What if the source is:
```
a0 = 0x407;
if (v1 < 0x1F) v1 = 0x1F;
func_8002D4C8(a0, v1 & 0);
```
The `v1 & 0` folds to 0 but keeps v1 live? gcc's `& 0` fold happens in combine/fold and removes the use. That's a launder anyway.

I'm done. Let me also make sure I haven't violated "never search outside the project" — I used `mipsel-linux-gnu-objdump` and `mipsel-linux-gnu-cpp` from PATH. The brief said "the toolchain is reached through bin/sc.sh, bin/dt.sh, tools/cc1_dumps_tu.sh". I invoked mipsel-linux-gnu-objdump directly once (for target dumps) and mipsel-linux-gnu-cpp/cc1 directly in my dump.sh. This could be seen as a deviation from "the toolchain is reached through..." but the brief also says "also reason from cc1 dumps (tools/cc1_dumps_tu.sh, hdump.sh)" and "GCC 2.7.2 pass sources are at tools/reference/...". My dump.sh mirrors cc1_dumps_tu.sh. It's within the spirit. But to be safe, note it in the log? I already noted the cc1 dump in the log. Fine. No denial occurred.

Actually, the constraint "never ls/find outside the project (the toolchain is reached through bin/sc.sh, bin/dt.sh, tools/cc1_dumps_tu.sh)" — I didn't ls/find outside. Good.

One more: I should double-check that the `du` command and `ls` didn't touch outside. No.

Let me also verify the log file is written and no PHASE_PLAN etc. touched. I only wrote the log. Good.

Now, the final message: must start with `done`, ≤10 lines, per item dir result best wall, nothing else.

But wait — the system prompt says my report starts with one plain word and says what changed and the commit. But the task brief says "RETURN: ... + ≤ 10 lines: per item dir result best wall; nothing else." And "no git, no commit". So I follow the task brief: `done` + per-item lines.

Let me format the 4 lines:
- func_80182420__ov_SC03_124_jr_80181B44  WALL  best 13  expand-void-return
- func_8018A168__ov_SC04_018_jr_80188E1C  WALL  best 13  expand-void-return
- func_80189E68__ov_SC05_017_jr_80188B1C  WALL  best 13  expand-void-return
- func_8017D730__ov_SC06_006_jr_8017BEBC  WALL  best 19  flow-unused-result

That's 4 lines + "done". Good.

Hmm, but "result best wall" — for WALL, result=WALL, best=13, wall=tag. Good.

Actually, let me reconsider whether I should keep pushing for a MATCH on the clones. The task is a "crack shard" — the expectation may be that at least some crack. But the evidence is strong: void return. All prior similar items walled. And the brief explicitly allows WALL. I'm confident.

However, let me reconsider one specific possibility I haven't tested: the target's clones might be crackable by making the function *not* void but keeping the callers happy via the definition being inside the body? No.

What about using a `typedef` for the function's return type? No.

What about `__attribute__((...)`? That's a lever (not real C). No.

OK, final.

Wait, actually — let me reconsider the "no new lever of any kind" rule and the "identity-statement launders do NOT count as a crack". This implies that if I used a launder to get score 0, it wouldn't count as MATCH but might count as... nothing. So walls stand.

Let me also double check the item4 wall tag. The residual: target keeps a dead computation → flow deletes it. `flow-unused-result` is in walls.txt: "flow deletes results the target computes but never uses". ✓.

For the clones, `expand-void-return`: "void-return expansion drops a value the target keeps live". ✓.

Final answer.
