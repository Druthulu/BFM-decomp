---
ts: 2026-11-06T20:06:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PBoB7TGD9uCcxvwro0kJ
---
qty priority = floor_log2(refs) * refs * size / live_length. Higher first. And refs includes loop depth weighting? reg_n_refs counts uses weighted by loop depth. The loop body: both are in the loop.

result pseudo: refs: 1 def? refs counted as uses: sw (1), sh base (2 uses), so reg_n_refs maybe 3. size = 4 bytes (s32). live length ~ from jal to second sh.
table pseudo: refs 2, size 2 (u16)? qty_size for u16 is 2 bytes... Actually reg_n_refs counts number of references (sets+uses)? In combine/flow, REG_N_REFS counts total references.

floor_log2(3)=1 → 1*3*4 = 12. table: floor_log2(2)=1 → 1*2*2=4. So result has higher priority → allocated first → gets its preferred v0. But mine shows result in v1! So maybe the copy preference isn't v0, or something else.

Hold on: mine's diff at 44-46: mine `move v1,v0` / `sw v1,0(s1)`. That's the call result copy. Maybe the result pseudo was allocated v1, but then the copy `move v1,v0` — wait if allocated v1, the copy from $2 is needed. Why would local-alloc not pick v0?

Unless... the result pseudo is NOT the call result directly: `v0 = func_8012C588(...)`, then `*p = v0`. The pseudo for the call result: gcc assigns the call's return value to a pseudo; since the C var v0 is assigned, the pseudo may be allocated separately. But maybe because `v0` variable is reused later (`v0 = *(u16*)`), and cse/copy-prop... no.

Hmm, maybe the issue is the *table* pseudo is actually allocated v0 first because it has a *higher* qty in the target? No, mine has table in v0.

Let me just get the dumps and see. tools/cc1_dumps_tu.sh — let me check usage.
