---
ts: 2026-10-22T21:11:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gVNOUb8QeJr0mJe1Ab5y
---
Many includers. Let me set up item 1. First copy the def to orig.c, and get the baseline score (with levers) to confirm it scores 0 currently.

Note "no signature or decl change outside the body" — for header items the body is what I write in win.c; tryinc.py uses --body mode? Actually tryinc.py calls delever_search --try with the header path... wait, it passes sys.argv[2:5] = header, fn, body. So the "TU" is the header path and the includer recipes get rotated. So --body mode applies the body in each includer context.

Let me set up and run baseline for item 1.

Item 1: func_80149374 — launder is `__asm__ __volatile__("" : "=r"(q))` on q = &sp18. Lever-free: need q not to be an asm-pinned pseudo. The comment says: "kills the (plus sp 0x18) CSE class reg; emits 0 bytes" — i.e., the launder makes q a hard-reg pseudo that breaks the cse equivalence so that the address &sp18 is rematerialized (or held in a reg).

Let me first score the orig to see baseline.
