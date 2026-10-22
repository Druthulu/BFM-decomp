---
ts: 2026-10-22T06:34:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_uUJVQcsnkoJs9tDLFqu5
---
Now, cand01: remove the launder asm line. Let me use Edit on orig.c? No, orig.c should stay as the src def (the reference). Create cand01.c from orig.c with the asm line removed.

The line is:
```
    __asm__("" : "=r"(rgb) : "0"(rgb));   /* zero-byte 2nd SET: kills the sched1 birthing boost */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_mac1)
```

Let me write cand01.c via a python script or just sed deletion. I'll use grep -v on the specific pattern.

Note: the `!FAKE:` comments might be checked. Let me just remove the whole line.

Then score with dt.sh.

Actually wait — the "lever-free" body must also keep the pins? The pins `register s32 rgb __asm__("$16")` — are they "class A/B sites" (levers) that get stripped by lever_free_body? The scoring compares our body to the built target in build/. The delever --try scores the body as-is (compiles the TU with our body and compares the object to the target). Pins are a lever of kind "pin" — row kind is launder, so pins may stay per the constraint "levers of other kinds the def already had (pins under other causes) may stay".

Hmm, "pins under other causes" — meaning pins that exist for a reason other than the row's cause. Here rgb's pin $16 exists because the launder was on rgb? Hmm. The comment says pin $16 — NEEDED DIFFERS (P36 rung B t8_mac1). These pins are marked "!FAKE: pin $16 — NEEDED DIFFERS", meaning the pin is needed to match. Actually the census marked them as class A/B levers (pin kind).

Risk: the checker (expert) may consider pins under the row's cause as also needing removal. But the brief explicitly says: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." — hmm, this says "no pin ... no launder"?? That phrasing lists all kinds. But then "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added" — this clarifies: row kinds must go; other kinds the def already had may stay.

So for kind=launder, the launder must go; pins may stay. Good, that matches the G15 items 1-2 which had launder rows and presumably kept pins.

Let me check item 1's win.c to confirm pins werekept.
