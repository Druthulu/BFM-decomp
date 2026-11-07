---
ts: 2026-11-07T00:20:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8gjL27ObzCuUZAAOwqkG
---
No improvement; best stays 22. Item 4 is a WALL.

Tries: 1 (baseline) + 2 (nopin, nolau) + 13 (g*, incl. g06 error) + 2 (h01, h02) + 20 (perms) = 38. Good, ≥30.

best = 22 (lever-free).
wall = cse-const-addr.

Let me record item 4 and then write the log.

Row: `func_80188790__func_80188790  src/shared/ov/func_80188790.h  func_80188790  launder,pin  WALL  22  38  cse-const-addr  ...`

evidence: "cse folds tp=&D_80126B58 into each load (mine lui+lhu vs target lhu 14(s3)); 13 tp spellings all 82 ins; pin-free tp also takes $s1 not $s3 (3-cycle)"

≤140: let me trim: "cse folds tp=&D_80126B58 into each load (mine lui+lhu vs target lhu 14(s3)); 13 tp spellings all 82 ins; pin-free tp takes $s1 not $s3 (3-cycle)"

That's ~150. Trim: "cse folds tp into each load (mine lui+lhu, target lhu 14(s3)); 13 tp spellings all 82 ins; pin-free tp takes $s1 not $s3 (3-cycle)"

~135. Good.

Moves line: `launder,pin | func_80188790 | WALL cse-const-addr — cse folds tp=&D_80126B58 into every load (3 extra lui); 13 tp spellings + 20 stmt orders all keep 82 ins; pin-free tp takes $s1 not $s3 (3-cycle) (G23x)`

Let me record both, then write the log file.

Also I need to verify each MATCH/PARTIAL has a win.c scoring 0 — but I have no MATCH/PARTIAL, all WALLs. So win.c files are the best lever-free bodies (fine).

Wait — DONE WHEN: "every item of G23x/list.tsv has exactly one results.tsv row; each MATCH/PARTIAL has its win.c scoring 0." I have 4 rows, no MATCH/PARTIAL. Good.

Hmm, but this is a "crack shard" and I cracked nothing. That's disappointing but the evidence is solid.

Hold on. Let me reconsider item 1 once more. Actually, wait — I should double check my item-1 conclusion. Let me reconsider: the reg order wall there. Hmm.

Actually, let me reconsider whether I've been too quick. The task says "Budget 20-30 min wall per item". I've spent: item 1 ~17 min, item 2 ~9 min, item 3 ~5 min, item 4 ~15 min. Total ~46 min. I have time to revisit item 1 or others.

Given that all four are WALLs, maybe I should revisit the most promising one: item 1 (best 14, only the reg swap) or item 4 (nopin 15, 3-cycle).

Hmm, let me reconsider item 1's reg order once more. The priorities: base r72 1518 > mode r73 1204. I showed dropping a base ref flips it but changes code.

BUT: what if I add a *mode* reference that doesn't change the emitted code? Earlier I reasoned that any extra ref produces an extra insn. But what about a reference that's *combined* into an existing insn? E.g., mode is compared `mode >= 0` (slt). If I wrote `mode >= 0 && mode != 0x1234`, combine might fold.

Hmm.

What if mode's live length could be shortened? Let me reconsider: mode live 83, from the set at ~insn 34 to the last use at ~insn 133. If I move the `mode = -1;` statement... it's fixed.

Hmm, what about the LAST use? `if (mode == 0 && (res & 1))`. What if I restructure to use mode earlier? 

Actually — here's an idea: what if `mode` is used in the `res` computation? No.

Hmm, what if I declare `mode` and assign it at the declaration point (which is where it already is)? The declaration is at the top (line 956) but the assignment `mode = -1` is at line 970. In C, the declaration doesn't create a reference. So the first ref is at line 970.

What if I initialize at declaration: `s32 mode = -1;` at the top → the set moves earlier → live longer → worse.

What if I move the `mode = -1;` statement LATER — but it must precede the if at line 971.

Hmm.

OK, item 1 is a wall.

Let me reconsider item 4's nopin (15): the 3-cycle. If tp weren't an allocno... 

Hmm, actually, wait! For item 4, what if I make tp a LOCAL by assigning it inside the if — I tried h01/h02, but h02 failed to generate. Let me retry h02 properly (nopin with tp inside the if, keeping the launder). That could make tp block-local and fix the 3-cycle.

Let me try that — it's a promising PARTIAL:launder candidate.

Actually, with the launder kept (nopin), tp is assigned at the top and laundered. If I move tp's assignment into the if (after the launder), the launder would be in a weird place. Hmm, the launder must be right after the assignment.

Let me restructure: move both the tp assignment and the launder into the if-block:
```
r0 = rand();
s4 = ...;
kind = ...;
v1 = func_8012913C(kind);
if (v1 != 0) {
    tp = (u16 *)&D_80126B58;
    __asm__("" : "=r"(tp) : "0"(tp));
    ...
}
```
Hmm, but that keeps the launder (PARTIAL:launder). tp would be block-local.

But wait — the target materializes tp BEFORE the first rand call (lui s3 at insn 9). If tp is assigned inside the if, sched1 would need to hoist it above the call... unlikely.

Hmm, but the emitted code must match. Let me test.

Let me try it.

Actually, hold on. For PARTIAL:launder, the pin is removed and the launder kept. nopin currently has tp assigned at the top + launder. If I move both inside the if, the allocation changes. Let me test.

Let me create the variant properly.
