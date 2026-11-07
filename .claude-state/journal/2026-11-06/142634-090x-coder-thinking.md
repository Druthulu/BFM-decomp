---
ts: 2026-11-06T21:26:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Lf4Qnk8wg2BEsJ5tZAPl
---
14:26. 2 more min. Let me do 2 more batches or a final verification. Let me do one batch (8) then a final verification + record at ~14:28.

Batch 13: try making the move be a *register-asm-free* user variable via a struct copy:
n1: `struct { s32 v; } sv; sv.v = (s32)a0;` dead.
n2: `rv = sp20; *a0 = rv; rv = (s32)((struct {s32 v;} *)a0)->v;` no.

Hmm. Let me instead try the *opposite*: maybe the target's move can be produced by a *call* whose return is discarded but the call is in the delay slot? No.

Let me try 8 more variants quickly and then record.

Actually, let me just do a final comprehensive verification and write the results row now (append at 14:28). Let me do one more batch to reach 14:27-14:28.

Batch 13: statement order variations around the call and store:
q1: `rv = sp20;` moved before the call? `rv = sp20;` before `func_8012B77C` → rv would read sp20 before the call (uninitialized). Wrong.
q2: store the call result: `rv = func_8012B77C(...); *a0 = rv;` — different.
q3: `*a0 = sp20; rv = (s32)a0;` (no temp) — r4-like.
q4: `rv = sp20; *a0 = rv; rv = (s32)a0;` with `rv` used in the call's out pointer: `func_8012B77C((s32)&rv, ...)` then `*a0 = rv; rv = (s32)a0;` — this changes the out slot to rv (a register, so &rv forces memory). Interesting! Let me try:
```
func_8012B77C((s32)&rv, a1 + 4, (s32)sp10);
*a0 = rv;
rv = (s32)a0;
```
Here `&rv` forces rv to memory (stack slot). The load `*a0 = rv` would load from rv's slot. The final `rv = a0` would store to rv's slot (since rv is address-taken, it's in memory!) → an extra store. Not a move. So no.

q5: declare `sp20` as `s32 sp20[1]` and `rv = sp20[0]`.
q6: use `sp10[3]` as the out slot.
q7: `rv = *(s32*)((char*)sp10 + 0x10);`
q8: `rv = sp10[4];` (sp10 is [4], out of bounds but adjacent to sp20).

Let me try q5-q8 and a couple. Then record.

Actually, I'll just run these 8 and then record. Let me write batch 13.
