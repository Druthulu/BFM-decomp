---
ts: 2026-11-06T15:35:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WNJ08Gcb62nck1KWjzce
---
The launder is on `s0`, which is assigned `call(...) & 0x8000` at line 180, tested at 181, then at 188 the asm re-defines s0, and then line 191 `if (s0 != 0)` re-tests.

Purpose: "launder the VALUE so cse cannot fold the surviving dead re-test that thread_jumps leaves behind."

So the target has a dead re-test: after the if block, `if (s0 != 0)` is tested again even though s0 is known nonzero. The asm's opaque set prevents cse/thread_jumps from folding the second test.

A real 2nd set of s0 that is value-preserving: s0 is `call(...) & 0x8000` → 0 or 0x8000. So `s0 = s0 & 0x8000;`? That's value-preserving. But it costs an andi... unless it folds into the existing one. Hmm, but the point is to be a real 2nd set.

Alternatively `s0 = (s16)s0;`? s0 is 0 or 0x8000; as s16, 0x8000 = -32768, sign-extends back to 0xFFFF8000. Not value-preserving (0x8000 vs 0xFFFF8000), but `if (s0 != 0)` and `if (s0 != 0)` tests are the same for both. But it would emit sll/sra.

What about `s0 = (u16)s0;`? value-preserving for 0/0x8000.

Let me first test plain removal to see the score.
