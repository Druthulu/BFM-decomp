---
ts: 2026-11-07T00:09:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KfhRllcSwhWHSUsGbvMH
---
No improvement. Item 2 is a WALL. 45 tries total.

Let me record item 2 now and move to item 3.

best = 31 (perm_1432).
tries = 29 + 12 + 4 = 45.
wall = cse-copy-merge.

Wait, actually let me reconsider: perm_1432 changed the copy order and scored 31, but it's a lever-free body. Good.

Hmm, but is `perm_1432` really the best lever-free? The t variants were all 39; ty_s16 39. So 31 is the best.

Let me record.

Row: `func_8012DBD0__func_8012DBD0\tsrc/shared/ov/func_8012DBD0.h\tfunc_8012DBD0\tlaunder,pin\tWALL\t31\t45\tcse-copy-merge\t...`

evidence: "cse merges iVar5=t/iVar4=t: mine lh s1, target lh v0+move s1,v0; 12 t spellings all 39; param allocno order also inverted (best perm 31)"

Let me count chars: roughly 135. OK.

Moves line: `launder,pin | func_8012DBD0 | WALL cse-copy-merge — cse folds `iVar5 = t`/`iVar4 = t` so the load lands in $s1; target keeps t=$v0 + move; 12 t spellings all 39; param allocno order inverted (best perm 31, 45 tries) (G23x)`

Let me write both.
