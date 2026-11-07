---
ts: 2026-11-06T21:37:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9esPlIv39bAQJcwFc3Z5
---
win.c has 1 `__asm__` — the pin `register void *a __asm__("$4")`. The keepalive asm is gone. Good (pin is a non-row lever that may stay).

Wait, the constraint "Lever-free = ... no pin (register-asm/`__asm__` reg steer)". Hmm, this makes me nervous again. Let me re-read the whole constraint block:

"CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added"

That's explicit: MATCH = the kinds gone; pins under other causes may stay. The item's kinds = keepalive. The pin is "under another cause". So MATCH.

But the CHANGE line says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm". Reading it as: "lever-free = none of the row kinds remain, where a lever can be a pin, launder, barrier, keepalive". The row kinds for this item = keepalive. So the keepalive must go; the pin may stay per CONSTRAINTS.

Hmm, but there's ambiguity: the CHANGE says "no pin". If the expert diffs orig→win, they'll see the pin retained. Would they count it as a lever of the row? The kinds file says keepalive only. I'll report MATCH and note explicitly that the `$4` pin (not a row kind) is retained and is load-bearing (dropping it scores 3). If the expert disagrees, they can reclassify.

Hmm, wait. Let me reconsider: could I get a fully pin-free body scoring 0? v25 (no pin, hoisted) = 3. What about v18 without the pin? v18 keeps the pin too. Let me try a few no-pin variants with the hoist to see if any scores 0. If one does, that's a cleaner MATCH (no levers at all).

Ideas for a no-pin body that produces `move a0,s0`:
- Without the pin, `a` coalesces with s0. To force a copy, `a` must be in a different register. The only forced register is a0 (call arg). Without the pin, the call argument setup `func_80146CA0(a)` still requires a0 = the value, and since a == arg0 (s0), a move a0,s0 is needed at the call. In w2 (no `a`, call arg0), the move was at 27 (just before the jal), not in the delay slot. The target has it in the beqz delay slot.

So without the pin, we need the scheduler to place the call-arg move earlier. Hoisting the assignment doesn't help because there's no separate assignment (a coalesces).

What if we force a copy without the pin by making the value "used twice in different registers"? E.g., `a = arg0` and then use `a` in a context requiring a different register — no.

Hmm, what if we use the *return value* of a call? no.

I think the pin is genuinely load-bearing. Let me try 2-3 no-pin hoist variants quickly to confirm:
- v26: `void *a; a = arg0;` before the if (w5-like but with the hoist) = 3 (tested as w5).
- v27: no `a` at all, call arg0, store arg0, but hoist something?

Let me test v18-without-pin (do-while wrapper, no a) quickly. Actually v18 = BASE + do-while, and BASE has the pin. Let me make a no-pin do-while variant.

Actually, the do-while(0) requires the `// !FAKE: do-while` annotation per the constraints. v18 lacks it. So v03 is the better result anyway.

Let me do a couple of quick no-pin attempts for completeness, then finalize.

Time check: 14:35ish. Item 3 started ~14:20 → 20+ min by 14:40. Let me finalize at ~14:40.

Let me test 3 no-pin variants:
n1: hoisted a (void *a) — 3 (done, v25).
n2: no a, do-while wrapper around the then-block.
n3: no a, call arg0, store arg0, but with the two stores swapped.

Let me just test n2 quickly.
