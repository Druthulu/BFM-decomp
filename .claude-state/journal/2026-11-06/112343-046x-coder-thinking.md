---
ts: 2026-11-06T18:23:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QrY1EJFCF4Sibt2BAIgl
---
No direct match. Let me try a few empirical candidates quickly. Given the analysis, the most promising is to change the branch structure so that 72 dies at a *different* place or 76's birth doesn't coincide with 72's death.

Idea A: move the store's pointer into a local: no.

Idea B: split the load into two statements with a temp so that the birth of 76 is a copy from a local temp:
```
s32 t;
...
t = ((Unkstruct*)a0)->unkCC;
v1 = t;
```
Then at the load: 72 dies, t is born (local, block-local). expand_preferences at the load: dest = t (allocno? t is block-local → reg_allocno[t] < 0 → no merge). Then `v1 = t` is a copy in the same block: set_preference(76, t) — t is a pseudo not yet allocated... no pref. And expand_preferences at the copy: 76 dest, REG_DEAD t → t has no allocno → no merge. So 76 gets NO pref! Then 76 → $3.

But the extra copy `v1 = t` would be coalesced by local/global alloc or by combine/cse: combine might propagate the copy (the load into t, then move t to 76 — cse's copy propagation could rewrite the load's dest to 76 directly, eliminating t). If cse eliminates it, we're back to square one. Let me test empirically — it's cheap.

Also the target's asm has no extra move, so if the copy survives we'd get an extra `move` (score 1-2). Let's see.

Idea C: `v1 = *(s32 *)((char *)a0 + 0xCC)` — same.

Idea D: Make the base pointer a variable that's used in all arms AND in the store block — impossible.

Idea E: Reverse the arms so the load is in the else... same.

Idea F: use `v1 = ((Unkstruct_80184B70 *)a0)->unkCC;` but declare `s32 v1` before v0? Decl order doesn't matter.

Idea G: **Make 76 a *different* pseudo per arm and copy at the join**: 
```
s32 v1, v1b, v1c;
if (...) { v0=1; v1 = load; }
else { v1 = load; v0=2; }
```
same variable.

What about:
```
if (...) { v0=1; v1 = load; }
else { v0=2; v1 = load; }
```
same.

Idea H: Make the load result's allocno conflict with 72 by making the load *not* the last use of a0 in the block. E.g., in the first arm, do the load and then use a0 again for the store... no.

Let me just test Idea B (temp) and a few more:
w3: temp split (t = load; v1 = t) in each arm.
w4: `v1 = (s32)((Unkstruct_80184B70 *)a0)->unkCC;` same.
w5: hoist the whole load out (single load before the if) — check the score (may be 1-2 off but could reveal).
w6: reverse if arms (`if (v0<a1) {...} else if ...`).
w7: declare `Unkstruct_80184B70 *p;` and use p->unkCC with p = a0 (same as 72, but tests).
w8: use `u32` for v1/v0.
w9: duplicate the store into the arms.
w10: swap `v0 = 1;` and the load.

Let me write a batch and score with sc.sh.

Actually, another important idea: **make 72 NOT a global allocno** by making it block-local. 72 is the param copy, live in all blocks. Hmm.

Wait, actually — what about making the load base a *new* pseudo per arm? E.g., in each arm use `(Unkstruct_80184B70 *)a0` — same 72.

Let me try a batch.
