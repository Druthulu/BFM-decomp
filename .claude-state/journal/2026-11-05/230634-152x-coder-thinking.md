---
ts: 2026-11-06T06:06:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3nAMtMq4IQcOsuyh9TXO
---
The naive lever-free is quite different:
- Frame 56 vs 48 (extra s1/s2 saves).
- Target: `move a0,s0` (a0 = s0) everywhere; mine: `move a0,s1` / `move a0,s2` — meaning the launder created copies of s0 into s1 and s2 (two variables), which is wrong.
- Also `lh a0,0(at)` vs `lh v1,0(at)` etc. — the v1 pin.

So the launder (pa0 = s0) creates a *copy* of s0 that gcc allocates to a different register (s1/s2), causing extra saves. Without the launder, pa0 = s0 directly (same variable) — hmm, but mine has s1/s2 copies, meaning the launder removal made gcc create copies elsewhere? Let me look at the n1 source: I removed the launder line, so `pa0` is declared but never assigned! That's the bug: the launder line was `__asm__("" : "=r"(pa0) : "0"(s0));` — removing it leaves pa0 uninitialized. So the code uses pa0 (uninitialized) — UB. That's why gcc created weird copies.

Right! The launder IS the assignment `pa0 = s0`. Removing it breaks the code. So I need to replace the launder with `pa0 = s0;` (a plain copy) — the real C equivalent.

Let me fix: n2 = orig with the pins removed and the launder replaced by `pa0 = s0;`.

Let me redo.
