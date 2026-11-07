---
ts: 2026-11-06T10:14:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bBjvnClLS54lwpuwCBGa
---
Per-block keepalives: rv got a2 (not v0), and the blocks are no longer merged (each has its own j + nop), producing 34 ins. The `goto done` blocks aren't cross-jumped/merged, so the structure differs. Score 15.

Hmm. The keepalive use made rv block-local but assigned a2 (because $2/$3 taken). And the control flow differs: the target has a shared epilogue (j 93c). With per-block keepalives, the blocks can't be merged because each has an asm.

So this doesn't work.

Let me think differently. The target's structure:
- The early-exit blocks jump to a shared return block (L94) where `jr ra` and v0=rv.
- rv is in v0 across the shared block.

The shared block means rv is live across blocks (from each def to L94). That's global. Global-alloc gives $3. To get $2, we need a return.

I'm now very confident it's impossible lever-free.

But wait — maybe a different restructuring: what if the function has a single exit computed via `if/else` so that rv is defined only in the final block? E.g.:
```c
if (a0 >= x) rv = -1;
else if (x >= y) rv = -1;
else { d = x-a0; if (d<16) rv = d*2; else { d=y-x; if (d<16) rv=d*2; else rv=31; } }
keepalive(rv);
```
This still has multiple defs reaching one use → global. Same.

What if we compute a *single expression* that selects the value? E.g.:
```c
rv = (a0 >= x) ? -1 : (x >= y) ? -1 : ((d=x-a0) < 16) ? d*2 : ...;
```
Still multiple defs.

Hmm, what if the value is computed via a function call that returns it? No.

OK. Let me reconsider whether the *pin* is actually necessary, or whether the keepalive can be placed to make rv global but $2. The issue is global-alloc's choice. Let me look at what registers global-alloc considers: $2 is caller-saved and used by local-alloc'd comparisons. Global-alloc's conflict: rv live across blocks where $2 is live (local pseudos). Since local-alloc assigned $2 to comparison pseudos in blocks that rv is live across, rv can't use $2. In the target, rv is $2 (hard), and the comparisons also $2 — allowed because hard regs bypass conflicts (the local pseudos would be allocated around it, but they got $2 too because they don't overlap at insn level).

So the problem: local-alloc assigned $2 to comparisons; global-alloc can't reuse $2 for rv because of block-level conflicts. If we could make local-alloc assign the comparisons to a *different* reg (e.g., $3), then global-alloc could give rv $2. But the target's comparisons use $2. Wait — if local-alloc gives comparisons $3, the target would mismatch (comparisons in $3 not $2). Unless global-alloc then... no.

Hmm, in the target, the comparisons use $2 AND rv uses $2. The order: in the real game, rv is the return value (hard $2), and the comparisons are allocated $2 by local-alloc because they don't conflict with the hard reg at the same insns? Actually, local-alloc assigns $2 to comparisons regardless of rv (hard regs are pre-assigned). At the insn level, rv=$2 is defined in the return block; the comparisons are in earlier blocks. Since local-alloc is per-block, it sees $2 free in the comparison blocks (rv's hard reg isn't "live" there in the block-local sense? but it is across blocks...). Actually, the hard reg $2 is live from its def to the end; in the comparison blocks, is it live? The return block is after; the comparison blocks flow toward it. If rv=$2 is defined in an earlier block (e.g., li v0,-1 in the `a0>=x` block), then on that path it's live to the end, but the comparison blocks are on a different path (not reached after the def). So $2 is not live in the comparison blocks. Hence local-alloc can use $2 there. That's why the target works.

For global-alloc with a *pseudo* rv (not hard), it computes conflicts more conservatively (live range as a single interval from first def to last use), so it thinks rv conflicts with $2 in the comparison blocks → $3.

Could we make rv's live range not a single interval? Only by splitting the pseudo (e.g., separate variables per path), but then the keepalive/use merges them... Actually, if we use *separate* variables per branch and only combine at the end, the combine is a copy/phi, which adds instructions.

Hmm, what if each branch assigns to a *different* variable, and at the end we have a single `rv` assigned via if/else? That's the same.

What if the keepalive uses a *different* variable per block? Then no single rv.

I think it's a genuine wall.

Let me reconsider item 4: k1 scored 14 (keepalives only, pins dropped), all 119 ins present, only registers differ (v1→a1, tmp3→a2). Could per-block/placement changes fix the registers? The `cmp` keepalive is in the second branch; the `tmp3` keepalive too. The pins forced $2 (v0) and $3 (v1). Without them:
- `v1` variable got a1 instead of $3.
- `tmp3` got a2 instead of $3.

Why does v1 get a1? The `v1` variable is used in both branches. In the first branch, `v1 = 0x7F - v0; if (v1<0x1F) v1=0x1F; if (v1>=0x80) v1=0x7F; func(a0, v1|0x1000)`. It's block-local (all in one block) → local-alloc. It chose a1. The target has $3. In the target, v1 is $3 because the orig pin $3 on tmp3 in the second branch? No, the target's first-branch v1 is $3 naturally (real game).

Hmm, could a real-C move make local-alloc pick $3 for v1? Local-alloc picks the first free hard reg in a preference order. a1 ($5) vs v1 ($3). GCC's local-alloc preference: `reg_preferred_class`/`reg_alternate_class` and `qty_phys_copy_sugg`/`qty_phys_num_sugg`. It also uses `REG_ALLOC_ORDER` or the hard reg order. For MIPS, the order might be $2,$3,$4,...,$5? If $3 is free, why a1? Maybe $3 is live (used by another pseudo) in that block. In k1's first branch, `v0` (the var) is in $2; `t` in $2/$3; `v1`... Let me look at the full diff: mine[61] `sra a1,v0,0xc` — v0 holds t; a1 holds v1. So $3 is free? Maybe $3 is used for something else (the magic constants / mult). The `mult` uses hi/lo, `mfhi` to a2. Hmm.

The target uses v0 for t and v1 for v1. Mine uses v0 for t and a1 for v1. $3 might be used for the magic constant (lui v1,0x1948 in target). In target, the magic constant is in v1 ($3) and then v1 is reused for the result. In mine, the magic is in... `lui a1?` Let me look at the full k1 asm. Let me dump k1? I'd need the dump script again. The diff shows mine[61-64]: `sra a1,v0,0xc; li v0,127; subu a1,v0,a1; slti v0,a1,31`. So t→v0, v1→a1. The magic constant would be in a0 or a1 earlier. In the target, the magic is in v1 then v1 is reused. So the target's v1 (result) coalesces with the magic constant's register. Mine uses a1 for the result; the magic maybe in a1 too? `lui a1,0x1948`? Then a1 reused. The difference is $3 vs a1 for the constant+result.

Could a real-C move make the magic constant land in $3? The constant is generated by the division; its register is chosen by... It's a pseudo for the constant (0x1948B0FD). Local-alloc. In the target, it's $3. Mine, a1.

Hmm, this is the `lreg-qty-priority` / allocation-order wall. Real-C moves might shift it, but the pin was the lever.

Given the strong structural evidence, I'll keep the walls. But let me reconsider the task instruction "Go on with the task." Maybe the harness expects me to continue because my report was too terse or because I should double-check something. The user message is generic ("Go on with the task. End your turn only with your report"). It might be an automatic nudge. Since the task is complete (all rows, win.c, log, notes, moves), I should just re-report.

But to be safe, let me re-verify the deliverables are complete and maybe strengthen the walls with a couple more tries. Actually, the brief says walls need ≥30 tries; I have that. Let me not overdo.

Wait — maybe I should reconsider: the user's message might indicate the previous turn ended without a proper report (I did end with `done` + lines). Hmm, it says "End your turn only with your report: its first word is done, question or blocked." My previous message did start with `done` (no space: "donefunc_..." because I wrote `done` immediately followed by the next line? Let me check: my message was:
```
donefunc_80182420__ov_SC03_124_jr_80181B44  WALL  best 13  expand-void-return
...
```
Oops! The first line is "donefunc_80182420..." — the word `done` is glued to the next line because I wrote "done" then the item line without a newline? Looking at my message: "donefunc_80182420__ov_SC03_124_jr_80181B44..." — yes, it seems the newline was lost. The requirement: "your final message starts with the bare word done (or blocked) as its very first word". "donefunc_80182420" is not the bare word `done`. That's probably why the harness says "Go on with the task. End your turn only with your report".

So I need to re-send the report with `done` as the first word on its own line. Let me also consider whether to add anything. The report should be ≤10 lines: per item dir result best wall.

Let me re-send properly:
```
done
func_80182420__ov_SC03_124_jr_80181B44  WALL  best 13  expand-void-return
func_8018A168__ov_SC04_018_jr_80188E1C  WALL  best 13  expand-void-return
func_80189E68__ov_SC05_017_jr_80188B1C  WALL  best 13  expand-void-return
func_8017D730__ov_SC06_006_jr_8017BEBC  WALL  best 19  flow-unused-result
```

But before that, since the user said "Go on with the task", maybe I should do a bit more work to be safe. Let me quickly verify the artifacts once more and then report. Actually, let me reconsider whether the clones could be PARTIAL:keepalive with the per-block idea but fixing the control flow. The per-block keepalives prevented block merging. What if we place a single keepalive at `done:` but split rv's live range via... no.

Alternatively, place the keepalive at `done:` but make rv's *value* come from a0/a1 in a way that... no.

Let me try one more promising idea for the clones: instead of `rv`, use the *return register via a call*? No.

Actually, here's a thought: the target's rv is $2. What if we declare `rv` as `s32` and use it as the argument to a *sink function* at the end? That adds a call. No.

What if we use `rv` in a `switch` at the end? `switch (rv) {}` — gcc might emit `slt`/branches or nothing. Dead.

What if we use `rv` as the *condition of a loop that never executes*? Adds instructions.

No.

Let me also reconsider: could the function be made to *return* by using `return` in a void function with `-fno-...`? The compiler drops it. b1 confirmed.

OK. Walls final.

Let me verify the deliverables one last time and re-report. Let me check the log exists, results rows, notes, moves.

Actually, I already verified. Let me just re-report. But the instruction "Go on with the task" might want me to actually continue investigating. Given I'm confident, and the task's DONE WHEN is met, I'll report.

Hmm, but let me reconsider one more time the possibility that the clone wall is crackable via a *different signature-compatible* trick: the function's callers use it as a value. What if the function body ends with a *store to a global* that is the return value? The target has no store.

What if the function is `void` but we use the `asm` label alias trick (like the worked example's `aB9A02 __asm__("D_800B9A02")`)? That's a symbol-name alias, not a codegen lever, and it's for globals, not return values.

No.

Final. Let me also make sure the moves.md append didn't break (the tail showed 4 lines).

Let me re-send the report with the correct format. But the user said "Go on with the task. End your turn only with your report" — so they want me to continue and end with the report. I'll do a final quick verification command then report.

Actually, let me do one genuinely useful extra check: verify that the win.c bodies are bare definitions that the scorer accepts (they score as recorded). Already done.

Let me also clean up the `.run/P36/engine/score` scratch if any left (the tool removes it). Not my concern.

Let me check the shard size and that no stray files outside. Done (832K).

I'll report now.
