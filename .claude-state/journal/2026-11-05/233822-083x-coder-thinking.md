---
ts: 2026-11-06T06:38:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V73djgWEHc9AkyRHFiAg
---
- Pins removed only: 135 (bad)
- Launders removed only: 43, 710 ins (right count)

So the launders are the bigger issue. Both need work.

Let me look at what the launders do. `mp = D_801CC7CC; __asm__("=r"(mp):"0"(mp));` then `func(..., mp, sp10)`.

The launder forces mp into a register and prevents cse from substituting the constant address D_801CC7CC into the call's argument (which would emit `lui/addiu` at the call site instead of a register).

Classic crack from moves.md: "cse-const-addr" walls; and MATCH examples where the address is rematerialized.

Actually, here's the thing: without the launder, what happens? The address D_801CC7CC gets... let me look at the diff of B.

Let me get the diff for B (43).
