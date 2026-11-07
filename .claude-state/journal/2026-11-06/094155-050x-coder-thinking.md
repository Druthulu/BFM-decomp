---
ts: 2026-11-06T16:41:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ldJrBjtdidSwXtawSksH
---
w1 scored 0! The `if (d < 0x51) { } else { goto skip; }` spelling produces the normal EQ form branch and prevents the merge.

Wait, w2 includes `d = d;` which is an identity launder, and it also scored 0 — but that's a launder, not allowed. w1 is clean: `if (d < 0x51) { } else { goto skip; }` — hmm, is this an "identity statement"? It's an empty then block; arguably it's a real C control-flow spelling (no value launder). But it does look like a workaround. Let me check whether w1's win.c has no levers and whether the empty block is acceptable. The constraint: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". An empty then-branch with an else goto isn't an identity value statement; it's a real C control-flow form. Hmm, but is it a "new lever"? No lever kind (pin/launder/barrier/keepalive/asm).

Actually, can we do better with a natural spelling? `if (d < 0x51) { } else goto skip;` is ugly. Maybe `if (!(d < 0x51)) goto skip;` also works and is more natural. Let me test that plus maybe `if (d >= 0x51) goto skip;` inverted vs normal.

Wait — the reason w1 works is the branch form: `if (d < 0x51) { } else goto skip;` gives a branch to the (empty) then block... but the then block is empty so GCC might branch to skip. Let's verify the emitted code matches target exactly (score 0 says yes).

Let me test `if (!(d < 0x51)) goto skip;` (w3) and also check w1's disassembly for sanity. Actually score 0 = byte-identical per the tool. Good.

But I want the cleanest real-C spelling. Let me test a few:
- w3: `if (!(d < 0x51)) { goto skip; }`
- w4: `if (0x51 <= d) goto skip;`

Hmm w4 is the same as `d >= 0x51`. GCC canonicalizes.

Let me test w3.
