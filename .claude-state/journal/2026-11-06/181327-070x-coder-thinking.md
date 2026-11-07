---
ts: 2026-11-07T01:13:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hiU2VoyolKNIWwSw05KY
---
Time 18:13:14 — item 2 started at 18:09. Only 4 minutes in. Good, I have time (need 20 min → until ~18:29).

Results: w13 (do-while around the stores) scores 4 (ORDER) — the store block boundary changed the schedule but worse. w04 (store order swapped) 5, w06 (separate temps) 7, w12 (14 ins) 2, w14 (do-while around the call) 4.

Everything else 1.

Note w12: I removed the call entirely?! Let me check: w12 replaced the block ending with the call by the block without the call — so the function lost the func_80171990 call → 14 ins, score 2. That's not semantically equivalent! I must not use it. It was a mistake in the generator (I meant to move the call before the stores). Not a valid try (it changes behavior). I'll disregard it and note it.

w03/w11 compile errors: w03 uses `u8 *p` declared mid-block (C89: declarations must be at block start) → error. w11 declares s32 v0 mid-block → error.

So valid tries so far for item 2: w00-w02, w04-w10, w13-w15 = 13 scored (excluding w0 = the copied prior a1.c; count it too as a try? It's the same as w00. I'll count distinct bodies: w00, w01, w02, w04..w10, w13..w15 = 3+7+3 = 13).

I need 30+. Let me fix the compile errors and add more variants:

More ideas:
- Move the call before the stores correctly (with the call present).
- `u8 *p = (u8 *)s0;` declared at the top, used as the call arg.
- `void *p = s0;` as the call arg.
- Store 1 base via new_var too.
- Two different new_vars.
- Cast the call arg differently: `(u8 *)(void *)s0`.
- Call with `(u8 *) s0` vs `(u8 *) (char *) s0`.
- Reorder: new_var assignment after store 1 (w05 = 1).
- Use `*(s32 *)((char *)s0 + 0x200) = 8;` (constant inline) — the target uses li $2,8 then sw; constant inline would be the same.
- `*((s32 *) (((char *) s0) + 0x200)) = 8;` and `... = 0x100000;` (no v0 at all) — then the target's `li $2,8` would still be needed; but the store value would come from a fresh temp. Try it.
- Declare v0 as `int`.
- Make the second store's value `v0 = 0x100000;` placed before store 1 (order).
- Use a `char *new_var = (char *) s0;` init at decl.
- Put `s0 = a0;` after the call? Wrong (call uses a0).
- Move `s0 = a0` into the call's argument: `s0 = a0;` is needed.
- Use `((void (*)(void *))func_8017EE68)(s0);` — the call arg is s0 instead of a0! Then the arg copy is `a0 = s0` (r72) and the store base r72... the same copy exists. But the first call's arg being s0 means the copy `a0 = r72` happens BEFORE call 1 (where r72 = s0's pseudo is born at insn 4). Then the equivalence r72==a0 is created early, and a0 is clobbered by call 1 → the equivalence dies. Then after call 1, the second store's base r72 is not equivalent to a0 (a0 was clobbered). The second call's arg copy `a0 = r72` would again create an equivalence — but if the store comes before that copy, fine. Interesting! Try `func_8017EE68(s0)` instead of `(a0)`.

Hmm, but the source's first call is `func_8017EE68(a0)` — semantically a0 == s0 at that point (s0 = a0). So passing s0 is equivalent! And it changes the RTL: the arg setup becomes `a0 = r72` before call 1. Then call 1 clobbers a0. After the call, the second store's base is r72; the second call's arg copy `a0 = r72` is hoisted above the store by sched1 → equivalence again. Hmm, same as before? Not exactly: the equivalence from the first copy is killed by call 1; the second copy is the same situation.

But maybe the scheduler orders things differently. Worth trying.

Another: pass the call arg as `(u8 *)s0` but make the copy `a0 = r72` *not* the last thing: e.g., `func_80171990((u8 *) s0);` after an extra statement. Hmm.

What about making the call arg a *constant-offset address*: `func_80171990((u8 *)((char *)s0 + 0x200 - 0x200))` — identity, disallowed.

What about `func_80171990((u8 *)&s0[0])`? no.

Let me also try: `s0` declared as `char *` from the start, and the call arg `(u8 *)s0`.

And: the store base using `new_var` for BOTH stores (store 1 through new_var).

And: the call arg via a second variable `p` assigned *after* the stores (so at cse the copy is after; sched1 may still hoist).

Let me write batch 2 with ~18 variants.

Also note: w13 (do-while around the stores) scored 4 — worse but shows the block split changes the schedule. Maybe a do-while around ONLY the second store? Let me try variants of block splitting:
- do-while around store 2 only.
- do-while around store 1 only.
- do-while around new_var assignment.
- do-while around the call (w14 = 4).

Let me generate ~20 more.
