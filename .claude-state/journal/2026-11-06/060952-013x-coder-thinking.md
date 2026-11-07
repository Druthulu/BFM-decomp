---
ts: 2026-11-06T13:09:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ce41kSSttQddhVS1aL6Y
---
These are large functions with pins. Wait — the kinds row says "barrier" only, but these functions have pins too! The constraint says: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". So pins that exist in orig may stay (they're levers of other kinds — but wait, the row kind is only "barrier", meaning the pin is not the reason this function is in the residue; the pin was needed but... hmm). Actually the constraint: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer)...". Hmm that contradicts. Let me re-read carefully.

CHANGE bullet 2: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

CONSTRAINTS: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added"

Hmm. So the kinds column for these items is "barrier" — meaning only the barrier must go. But the CHANGE bullet enumerates what "lever-free" means generally (for any kinds). The operative rule is: none of the row kinds remain. Pins are a different kind, so pins may stay since they're pre-existing (the def already had them).

Wait, but the kinds file says "barrier" for all five. Yet item2's def has `register __asm__("$2")` pins. So the row says only barrier kind is being removed? Hmm, but the item was placed in the residue under "barrier". The brief's MATCH definition: "MATCH = the kinds in <dir>/kinds gone". So for these, barrier gone. Pins may stay (they're levers of another kind the def already had).

Hmm, but then "no pin (register-asm...)" in bullet 2 — that's the generic definition of lever-free. I think bullet 2 is a generic description and CONSTRAINTS clarifies. Given the row kind is barrier only, I'll target barrier removal, keeping existing pins. Actually wait — careful: "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c (the expert diffs orig.c -> win.c lever lines); a win.c that keeps all row kinds is a WALL, whatever it scores." So for kinds=barrier, win.c keeping the barrier = WALL. So removing the barrier is the crack; pins can stay.

Hmm, but actually maybe the intent is that these functions were assigned kinds=barrier because that's the only lever class the census attributes as "needed". The pins are also levers but maybe they're not needed? Whatever — the rule is explicit.

Now let me check the barrier in item2, item3, item4, item5. Let me grep for `__asm__` in each of the 5 src files near their functions, and read the remaining functions.

Let me read item2 rest and item3 rest, plus item4/item5.
