---
ts: 2026-10-22T00:35:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_s0TXKdOWo5vhrjEYSmKM
---
Without the asms, GCC hoists the comparison constants (li t7,-150 etc.) into registers before the loop and uses a chain of bne. The target (with the asms) has fewer instructions (50 vs 52) and a different structure.

The target's ins 1-2: `li t3,-150`, `li t2,4` — so the target *does* hoist two constants (t3=-150, t2=4) but not the others. Interesting: the target has 50 ins.

Let me see the target's asm fully to understand the shape. Let me dump it.

Also, this is a case where the *lever* (12 asms) acts as a "keepalive/ref-boost" for v, which changes the register allocation: the target keeps the constants in t3/t2 and v elsewhere.

Let me look at the target asm.
