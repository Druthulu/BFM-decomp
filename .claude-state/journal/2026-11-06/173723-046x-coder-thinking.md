---
ts: 2026-11-07T00:37:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NBrFUeZCf9ArzFqsiCTF
---
The target: `val` is in v0 (loaded at 8408-840c: lui v0; lw v0), then `li v1,1` at 8410, stores via `at` (lui at; sw zero), then addiu v0,v0,1 and store to D_801B7A84.

So the pin `$2` (v0) makes `val` live in v0 — and the compiler uses `at` for the constant-address stores because v0/v1 are taken.

Lever-free: `s32 val;` without pin. The prior attempt found best 2 with sched1-birth-boost. The problem: without the pin, local-alloc gives v0 to something else, and the stores use v0 instead of at.

Let me test the lever-free version first: remove the pin and the barrier.

Candidate w1: 
```
    s32 *p;
    s32 val;
    func_8013C0F8((s32)&D_801A64C8);
    p = &D_801B7930;
    func_8017F53C((s32)p);
    val = D_801B7A84;
    D_801B7948 = 0;
    ...
```

Let me write it and score.

Note: `val` needs to be declared in the block. Let me write the full body.

Also I should check: does the *barrier* matter alone? Try removing only the barrier (keep the pin) and only the pin (keep the barrier) to see which lever each diff needs. That's cheap and informative.

w1: no pin, no barrier.
w2: no barrier (pin kept).
w3: no pin (barrier kept).

Let me write w1 and generate w2/w3 with sed.

Since the levers are inline, I'll write the three files via a small python script or Write. Let me just use Write for w1 and sed for w2/w3.
