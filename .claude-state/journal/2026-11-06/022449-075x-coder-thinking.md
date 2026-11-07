---
ts: 2026-11-06T09:24:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JZRQbdUiImbbiCbwpry0
---
Target: s0 = a0 (move s0,a0 in delay slot), `sw v0,0(s0)`, `move v0,s0` at end. So rv's first value (sp20) is used for *a0=rv, and then rv=(s32)a0 → move v0,s0.

With keepalive-only: rv is a plain local; `rv = sp20; *a0 = rv; rv = (s32)a0; asm(rv)`. The compiler may coalesce the second rv with a0's pseudo (s0) → no move. But maybe rv stays separate and gets a caller-saved v0? Let's test.

Actually, note: target uses `s0` for a0 (callee-saved) because a0 is used after a call. In the lever-free version the same should happen. The `move v0,s0` is the copy rv = a0. If rv is a distinct pseudo whose live range starts at `rv = (s32)a0` and ends at the asm, local-alloc gives it v0 (caller-saved, no call in between) → `move v0,s0`. And it can't coalesce with a0 because a0 is a parameter pseudo that's live across calls... actually coalescing could still happen if their live ranges don't conflict; but a0's pseudo (s0) is live from entry to the last use; rv is live from the copy to the asm — same end. If coalesced, rv = a0 → no move and the asm uses s0. The allocator's copy preference might coalesce. Let's just test.

Item 5 lines: 7514-7539 (def through closing brace at 7539?). From the earlier read: 7514 starts, and the closing `}` is after the asm. Let me get exact line numbers.
