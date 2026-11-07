---
ts: 2026-11-06T21:32:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_99yVHZ47fjZXIQMENWXo
---
v25 (v03 without the pin) = 3, so the pin is load-bearing. v03 keeps the pin (allowed, non-row kind) and drops the keepalive → MATCH.

Now, wait. Let me reconsider whether this is really acceptable as MATCH. The brief says:

"CHANGE: For each item ... write a lever-free body of `func` ... that scores 0.
- Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm, this says lever-free = none of the row kinds remain, then gives a parenthetical list including "no pin". For this item, the row kinds = {keepalive}. The parenthetical enumerates what a lever can be. The CONSTRAINTS section clarifies: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So the pin may stay. MATCH.

But hmm, "pins under other causes" — the pin here is `$4` for `a`. Is it "under another cause"? The kinds row says only "keepalive", so the pin was classified under another cause (headers1 pin). Fine.

Now, the MATCH row requires score 0 on every includer. The background job is checking v03 on all 141.

Meanwhile, let me prepare the notes.md for item 3 and the final win.c (= v03.c). Let me also record the mechanism: hoisting `a = arg0` above the inner if changes the sched1 order so the move lands in the beqz delay slot.

Hmm, wait: v03 hoists the assignment above the inner `if`, so the C order is: ... q load; a = arg0; if (cond) { stores; call }. The target's asm has the move in the delay slot of the inner-if branch. The hoist means the move is generated before the branch, and sched1/reorg places it in the delay slot. Good.

Let me check the background job.
