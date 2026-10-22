---
ts: 2026-10-22T06:03:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Z2kUXlBCJukha4X7O084
---
Wait, the src file line 3117 is the function; the sed output showed the function but with some differences? Let me check: the src shows `sx = sx << 8;` etc. Actually the sed output showed a function starting at 3117 with `void func_80191020(s32 a0) {` and then the body — the output started at 3110 showing externs. The body matches orig.c closely. But wait, in the src, line for `sx = sx << 8` and `func_8002D4C8`. Yes matches.

Hmm, but the src body has `RotTransPers` etc. orig.c seems identical to src. Let me verify with a diff to be sure (FRESH check).

Actually, the constraint says "no signature or decl change outside the body (callers stay as they are)" and "no `register` vars, no `__asm__`". But the row kind is only `launder`. The `register s32 av __asm__("$5")` is a pin — but the brief says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

Hmm, that reads as: lever-free means none of the row kinds (here: launder) remain, AND no new lever of any kind added. But "no pin (register-asm/__asm__ reg steer)" is listed as one of the row kinds generically. The kinds file says "launder" only. So the pin on av ($5) is a different kind, not a row kind → it may stay. Indeed for func_8018CDEC: "the $2/$4/$6 pins stay, they are not the row kind".

But constraint also says "no `register` vars, no `__asm__`" — hmm, that's in CONSTRAINTS. That's ambiguous. Actually, comparing with the G14 work already done: for func_801813B0 the pin was...? Let me check what win.c files exist in other dirs. Actually func_8018CDEC's win.c kept the pins. Let me check one of the completed dirs to see conventions.

Actually for our item, the av pin `register s32 av __asm__("$5")` is in the body. The row kind is launder only. The levers "of other kinds the def already had (pins under other causes) may stay, never added".

Hmm, but "no register vars, no __asm__" in CONSTRAINTS might refer to the overall lever-free body. This is contradictory with "pins of other kinds may stay". Given the RESULT/PARTIAL distinction: PARTIAL:<kinds still kept> = win.c scores 0 keeping only those levers. So for a row of kind launder, PARTIAL:pin would mean win.c keeps the pin. But here the def already has a pin, so the pin is not a row kind. So a MATCH should be possible with the pin kept? Hmm but then CONSTRAINTS "no register vars, no __asm__" would be violated.

Let me look at how the other G14 items were handled — e.g. func_8018CDEC which had pins. Let's look at its win.c.
