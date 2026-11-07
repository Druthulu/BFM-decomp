---
ts: 2026-11-06T16:58:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q90nLPC2YHpi7NRaqp9P
---
Still 3. The &m cache persists.

Let me reconsider: maybe the struct assignment isn't the issue; maybe the q dead-reset works only with the hand-expanded copy because of how cse numbers things. Let me try the hand-expanded copy (without the s-launder) + the q dead-reset + something to fix the D_800AE620 remat.

The D_800AE620 remat (x1, 19) is the bigger issue. The s-launder fixes it by making `s` a register. What real C keeps `s` in a register?

The struct assignment `m = D_800AE620;` does exactly that (it produces the target's copy block). So the struct assignment is the right replacement for the s-launder + hand-expanded copy! And it only leaves the &m cache issue (score 3).

So: struct assignment + fix the &m cache. The target rematerializes &m at the func_800484EC call. Mine caches it in s1.

Why does mine cache &m? Because the struct assignment `m = D_800AE620;` takes the address of m once (for the stores), and cse records `&m` as an equivalent register. Then RotMatrixY(ang, &m) uses it, and func_800484EC(&m) reuses the cached register.

The q dead-reset should break it. Unless the cached register is established at the struct copy and used at RotMatrixY *before* any reset.

Hmm: `m = D_800AE620;` stores to sp+32 (address materialized). Then `q = &m;` — cse sees &m already in a register (from the struct copy) and uses it for q. Then `q = 0` kills q's equivalence. Then `func_800484EC((s32)&m,...)` — cse re-materializes &m (should be addiu a0,sp,32). But mine caches it in s1 across the RotMatrixY call.

Wait, mine's diff: `addiu s1,sp,32` at index 48, then `move a1,s1; move a0,s1`. So s1 holds &m and is used for both RotMatrixY's a1 and func_800484EC's a0. The `addiu s1,sp,32` is placed before RotMatrixY (index 48). So cse decided to keep &m in s1 across the call. The q dead-reset should prevent q from being that register... unless the register is not q but the struct copy's base.

The struct assignment's store base is &m = sp+32; after the copy, that register (s1) still holds &m. cse may treat the *value* sp+32 as available in s1 and reuse it.

To kill it: after the struct assignment, invalidate s1. A dead-reset of a pointer used as the struct base? We can't name the internal base.

Alternative: do the struct copy through a pointer variable so we control it:
```
Blk20 *mp = &m;
*mp = D_800AE620;   // struct assignment through a pointer
mp = 0;             // dead reset (C0414)
```
Hmm, `*mp = D_800AE620;` might not emit the block move (it's a struct copy through a pointer, which gcc does with move_by_pieces too).

Or:
```
q = &m;
*q = D_800AE620;
q = 0;
```
Then q's reset kills the equivalence. Let me try.

Also, maybe simpler: the target's `addiu a0,sp,32` at e7c is the func_800484EC arg computed early. Mine has `addiu s1,sp,32; move a1,s1; move a0,s1`. If I pass &m through a *fresh* expression for each call, cse might still CSE them.

Let me try:
- ab01: `q = &m; *q = D_800AE620; q = 0;` then the RotMatrixY block.
- ab02: struct assignment + `q = &m; q = 0;` where q is used... tried aa01.
- ab03: `m = D_800AE620;` then `func_800484EC((s32)&m, ...)` — replace &m with a volatile-ish read? no.

Let me test ab01.

Also, another thought: maybe the target's behavior comes from the q-launder being an *asm* that blocks cse across it. The dead-reset works in y01 but not z01 due to the struct copy. Let me test ab01.
