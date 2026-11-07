---
ts: 2026-11-06T10:39:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DmMlBND0ZFvqbEU5P7T6
---
Line 137: "pin | func_8017E5C4 | MATCH: drop the `obj` copy and use the parameter directly — it is live across the call, so gcc parks it in $16/s0 and copies it in the prologue (G05)".

That's exactly our situation! Use the parameter directly (no local copy) — the parameter is live across the call, so gcc parks it in $16/s0 and copies it in the prologue. Let's try: replace all uses of `s0` with `a0`.

But careful: `(s32)s0` → `(s32)a0`, `((Unkstruct*)s0)` → `((Unkstruct*)a0)`. And remove `void *s0;` and `s0 = a0;`.

That should give: parameter a0 live across the call → parked in s0 with a copy in the prologue. 

Let me generate this variant.
