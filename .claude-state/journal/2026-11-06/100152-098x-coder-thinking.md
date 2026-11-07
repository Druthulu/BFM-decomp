---
ts: 2026-11-06T17:01:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_d3gkEmQOMqr84WN5DI81
---
ae01/ae02 compile errors (q0 declared mid-block in C89? The function has declarations at the top; `Blk20 *q0 = &m;` mid-body is a C89 violation — the compiler is gcc 2.7.2 which allows declarations after statements? No, it's C89; but earlier I used `Blk20 *s = &D_800AE620;` inside a block at the top — that's fine. The error is probably a redeclaration or the declaration after a statement.

Let me put the declaration at the top. Actually, let me not spend more on this; time is short.

Current best for item 4: score 3 (z01 and many variants), with all row kinds (keepalive, launder) gone and only the a0 pin remaining. Score 3 is very close.

But wait — maybe I should reconsider: z01's residual is ONE instruction (addiu s1,sp,32) plus 2 moves. Could the a0 pin be causing it? The pin is `register void *a0 __asm__("$16") = arg0;` — $16 = s0. It's an other-kind lever, allowed to stay. But maybe removing it changes things? The pins were "NEEDED DIFFERS" though.

Let me check: if I remove the a0 pin from z01, what happens? That's an other-kind lever; removing is allowed. Let me test quickly. Also the `s1` cache: maybe the a0 pin forces s0 and leaves s1 for &m. Without the pin, the allocation might differ.

Let me test z01 without the a0 pin (replace with plain `void *a0 = arg0;`). And a couple more.

Time: ~10:07. Let me run this.
