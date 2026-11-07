---
ts: 2026-11-06T21:35:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F5DlaRn68GBRmUr0frr8
---
All 12 or worse. Now I've done ~30 tries (15 + 15 + earlier ~15 = well over 30). Time ~15:38, started item 4 ~15:15 = 23 min. WALL threshold met.

Best = 12 (win.c). Wall tag: `lreg-qty-priority` or `global-pri-bank-order` or `greg-ref-count`. The mechanism: n is a global allocno crossing the bgez branch but not a call; without the $16 pin it takes caller-saved v1 instead of callee-saved s0; no real-C lever (target's n also does not cross a call). 

The closest wall tag: `global-pri-bank-order` (global-alloc assigns hard regs in a different order) or `lreg-qty-priority`. Since n crosses blocks → global-alloc. `global-pri-bank-order` fits ("global-alloc priority order assigns the hard regs in a different order than the target"). Actually `greg-ref-count` is "global-alloc ref-count priority gives a hot pseudo a different hard reg". Hmm.

Actually the real mechanism: caller-saved vs callee-saved choice. The pin forced callee-saved. Without, caller-saved. This is `global-hardreg-reserve`? No. Let me use `global-pri-bank-order`.

Hmm, walls.txt has `global-pri-bank-order`: "global-alloc priority order assigns the hard regs in a different order than the target (G22x)". That fits.

Let me record: result WALL, best 12, tries ~30, wall global-pri-bank-order, evidence: "n crosses bgez branch, no call; without $16 pin global-alloc gives caller-saved v1, target keeps s0; every real-C form = v1, count 117".

Let me set win.c (already the lever-free plain n body, score 12). Good.

Let me record results row, notes, moves, clean up.

Tries count: win, win2, win3, b, c, d, e, f, g, h, n16, nu16, j, k, l, m1-m15 = 15+15 = 30. Plus win/win2/win3 counted: win(1), win2(2), win3(3), b(4), c(5), d(6), e(7), f(8), g(9), h(10), n16(11), nu16(12), j(13), k(14), l(15), m1-15 (30). So 30 exactly. Good.

Let me record.
