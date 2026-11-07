---
ts: 2026-11-06T09:12:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XpEdCnw4lMAEu2QLp4zF
---
Item 5: pin $2 rv + keepalive. The target returns `(s32)a0` in v0 at end (rv = (s32)a0). That's a void fn returning a value in v0 again — expand-void-return wall? Hmm, rv is used for `*a0 = rv` (from sp20) then rv = (s32)a0 and keepalive. Target: move v0,a0 at end presumably.

So item 5 also needs a value in v0 at end from a void function.

Items 1,2,4,5 all look like "value in v0" walls. Item 3 (pin $10 + mlo keepalive) is different.

Wait — but maybe there's a general real-C crack for the "value in v0 at end of void function": GCC 2.7.2 `expand_value_return` — if the function has a `return;` statement with no value, nothing. But what if the value is *the result of a function call* at the end? Hmm.

Let's actually test whether a void function that ends with `return found;` produces v0 in this GCC. Our c3 test showed it didn't (49 ins, found dead). But maybe with `-w`? It compiled (warning suppressed?) and dropped.

Hmm, what about `return (s32)found;`? Same.

What about the function returning void but ending with a call to a void function: no.

OK so how do these items crack? Maybe they don't — the shard may be mostly walls. But the task says "write a lever-free body of func that scores 0" as the goal, with PARTIAL/WALL allowed. Fine.

Let me check what a "PARTIAL" would be: win.c scores 0 keeping only those levers. For item 1, keeping the pin alone → 19 (because keepalive also needed); keeping keepalive alone → 1 (not 0). So no PARTIAL. WALL best 1.

Hmm wait, for item 1: pin alone = 19? That's because without keepalive, flow deletes the dead rv set even though rv is a hard reg? The comment says "flow.c insn_dead_p deletes a dead hard-reg set". Yes. So pin alone doesn't survive flow. So both needed.

For item 2: res = 0; ...; keepalive. Let me test pin-only vs keepalive-only there.

Actually, hold on. Let me reconsider the "value in v0" problem. There's a well-known GCC 2.7.2 behavior: `expand_value_return` in stmt.c handles returning a value from a void function? The comment in item 4 says "the function RETURNS the slot (`void *` signature, expand_value_return stmt.c:2505; the TU's extern is `void`)". Hmm, that reads like: the function is declared void in the TU extern but the original function returned void*; they pin because expand... Let me read stmt.c:2505 in the reference tree.
