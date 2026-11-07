---
ts: 2026-11-06T10:19:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xjQf7RZhbJYU6VEvARrK
---
Line 514: "`conflicting types` on YOUR OWN function's definition, where the fleet canon is `(void)`" → §73 (the PARAMS axis) + §42 — keep the `(void)` signature and read the incoming arg via `register s32 a0v __asm__("$4")`.

And line 545: "`void` vs `s32` return — is promoting it byte-neutral? → NO, not always: §41d (byte-proven; a `void` body with no `return` gains an instruction). P30 adds a second mechanism: an `s32` return keeps `$v0` live-out and blocks dbr from filling a loop-back delay slot".

So promoting void→s32 is a known technique but it's a signature change. And here it would conflict with the callers' `extern void` decls (compile error).

Hmm — wait! What if the *definition* is K&R-style: `func_8017F1F0(a0, a1) s32 a0; s32 a1; { ... }`? That still conflicts with the later `extern void func_8017F1F0(s32, s32)`.

Hmm, what if the definition is K&R with NO return type (implicit int)? Still conflicts with void.

So no.

Let me read §73 and §42? That's about reading args, not return values.

OK. Now let me look at §41d quickly — maybe it reveals a trick: "a void body with no return gains an instruction" — the target HAS v0 set. So the source must have an s32 return. Since we can't change the signature, it's a wall.

Let me now write the deliverables. But first, let me reconsider the item 4 result once more: the shard is G26x and the wall tag `greg-ref-count` is "G26". So the shard likely was created *because* of the greg-ref-count class. The expert may expect WALL for item 4 with the mechanism documented.

Let me check the moves.md for the G26 entries to see what the shard's parent did.
