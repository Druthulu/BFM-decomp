---
ts: 2026-11-06T16:52:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_G67pkPZ4tmqMHf2H94Gb
---
Now mine: `addiu s1,a1,48; move a2,s1` — it keeps the +0x30 result in a callee-saved register (s1) for reuse? Wait: mine[140:141] `addiu s1,a1,48; move a2,s1` vs target `addiu a2,a1,48`. So mine computes the m+0x30 into s1 (a register) then moves to a2 — because s1 is used later (in group B's same symbol? no).

Hmm, mine still holds some values in s-registers: s2 holds a symbol (a1,s2,-48; move a2,s2). The dead reset didn't fully work because the reset kills m but the *constant* m+0x30 might be reused.

Actually mine[158:160]: `addiu a1,s2,-48; move a2,s2` — so s2 = some address, a1 = s2-0x30, a2 = s2. That means s2 holds m+0x30 for a symbol, computed once and reused at a later site.

Hmm, so the reset isn't enough for the +0x30 value.

Let me think: the dead reset `m = 0;` invalidates m. But `(void *)(m + 0x30)` produces a separate pseudo whose constant is `(const (plus (symbol_ref) 48))`; cse can merge that separately across sites. Need a dead reset for that too.

Add: after the call, reset both m and the +0x30 value. But the +0x30 is an expression, not a variable. We could name it: `s32 m2 = m + 0x30;` and reset both.

Let me restructure each site:
```
{ s32 m = (s32)D_8018E2DC; s32 n = m + 0x30; func_8017D8A4(A, (void *)m, (void *)n, 0, 1); m = 0; n = 0; }
```
Then cse can't carry either.

But wait, the target's RTL for each site is: `(set reg m (symbol))` and `(set reg n (const (plus (symbol) 48)))` and uses them. With the resets, each site's pseudos die. Let's try.

Actually, hmm, adding `n = m + 0x30` might change the RTL vs target (target has `addiu a2,a1,48` computed from a1 — the same). And the reset of n adds a dead set deleted by flow. Should be zero-cost.

Let me test.
