---
ts: 2026-11-06T21:40:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KaQVhmrJj5gkDJFKsOph
---
w1 scores 0 and is lever-free (no pin, no barrier asm). Wait — w1 still has `__asm__` for the symbol aliases, which are names, allowed. Check: no `register`, no `__asm__ __volatile__`. Yes.

But careful: the constraint says "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had may stay, never added". The struct alias is a new move — is a "1-field struct alias of D_801151D0 (MEM_IN_STRUCT)" a lever of some kind? It's not register-asm/launder/barrier. It's a real C type alias. It cracked in G31y and is a legit move. Good.

However — is `do { } while (0);` an "identity-statement launder"? The brief says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". An empty do-while is a different thing (C0535 EBB split) and is explicitly allowed with the !FAKE comment. Fine.

Hmm but wait: does the empty do-while count as a "barrier" kind? In the moves it's used as the barrier replacement (C0535). The kinds file lists `barrier` — presumably meaning asm barriers. The recipe from G31y was accepted as MATCH. Fine.

Let me double check w1 truly has no levers: grep for asm/register.

Also need to verify score detail: "score 0 (OTHER; mine 175 ins, target 175)". Good.

Let me pick w1 as win.c (simplest, no do-while keepalive needed since s16 casts handle pricing). Actually w1 has the empty do-while in the arm (needed for reorg). Good.

Write win.c = w1. Then results row.

But first verify w1's levers: grep.
