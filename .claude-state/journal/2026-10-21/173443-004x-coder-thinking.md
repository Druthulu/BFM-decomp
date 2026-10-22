---
ts: 2026-10-21T23:34:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_IA8zw0rZOalEned8xZV6
---
The for-loop was denied. Let me use individual commands.

Interesting: there's an existing worked example where a `do { r = p + i; } while (0);` adds a loop-weighted ref. Note constraint says `do{}while(0)` only with `// !FAKE: do-while`. Hmm, but the worked example used it. Wait — the lever-free definition: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm. A do-while(0) that adds a REG_N_REFS ref is... a "keepalive"? Actually it's a lever — a new lever of any kind is disallowed. Hmm, but the T10 example did it to remove a pin. Wait "lever-free = none of the row kinds in <dir>/kinds remain: no pin ... no new lever of any kind." Hmm, the do-while loop trick is a codegen lever (loop-weighted ref). But it was used in the T10 example which is a worked example. Careful.

Actually re-read: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." So for a pin item, I must remove the pin mechanism and not add new levers of any kind. A do-while(0) fake loop would be adding a lever (loop). Hmm, but T10's example used exactly that to remove the pin. The T10 constraint presumably allowed it as "real C moves"? The brief lists C0505 catalog of real C moves: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse. "loop shape" is a real C move! So a do-while(0) with a comment `// !FAKE: do-while` is loop shape manipulation — permitted with the marker. OK so `do { r = p + i; } while (0);` with the marker comment is allowed as a "real C move" (loop shape), and it's not a pin/launder/barrier/keepalive.

Let me get the full picture. First read the tools: bin/dt.sh, bin/sc.sh, delever_search.py. And the item's src header and the kinds.

Let me be careful with tool approvals: avoid for loops in bash. Use separate commands.

Let me look at the item dirs.
