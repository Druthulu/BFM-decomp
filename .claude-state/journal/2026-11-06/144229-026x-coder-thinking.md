---
ts: 2026-11-06T21:42:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wCh6CrtLcizdwqp9U8ss
---
Item 3: header func_80177EA4, kinds launder. Need to remove the launder `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c))` while keeping score 0 on all 141 includers.

The notes say: p1 = c1 + launder restored (non-volatile): score 2, only `sw v0,-4(t0)` placement (mine 41, target 39). q1 = p1 + do-while on the uVar1 store: 0. So the launder (anti-coalescing) is still needed: without it `iv2c = iVar2` folds into iVar2 (no `move v1,a0`), and sched puts the store late.

Now I need a real C way to keep `iv2c` from being coalesced with iVar2, producing the `move v1,a0`. Ideas from catalog: s16/u8 widths, temps, statement order, do-while.

The mechanism: `iv2c = iVar2` — a copy that cse merges (copy propagation) because they're equivalent. The launder blocks it by making iv2c a hard-reg asm output.

Real-C alternatives: make the copy a different mode (e.g., s16/u8 intermediate) so cse's copy equivalence doesn't apply — the "HImode copy escapes cse" trick used in several MATCHes (func_80182ED4: `tmp=(s16)t; u=tmp`). That's exactly the pin category, but here it's the launder category. The trick: a width-changing copy (HImode) is not a simple reg copy; it becomes a sign-extend. But target wants `move v1,a0` (a plain move), not a sll/sra pair. Hmm.

Wait, in func_80182ED4: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot". So the copy becomes `move v1,v0` (since s16 copy of a value in a register is a move; the sign extension may be a no-op because the value is known s16?). Hmm — in that case it survived as a plain move.

Let me look at the actual header body and the notes' q1 win (prev_win.c). Let me read the header and prev_win.
