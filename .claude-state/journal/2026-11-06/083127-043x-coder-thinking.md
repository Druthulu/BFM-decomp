---
ts: 2026-11-06T15:31:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7nUQ1g6rbfU36UcJ64YE
---
b2: `andi s1,v0,0xe000` — combine folded the second andi into the copy, making it an andi into s1. So the value of flags is raw & 0xE000 and the masks folded. Not target.

We need `move s1,v0`.

Let me think again about what produces a real copy that cse won't delete.

What if flags is used in a context that forces a copy because of *register class* or because the copy is needed for a call? The target's copy exists because raw dies early and flags lives across calls. gcc's global allocator would normally handle this: if cse kept two pseudos, global-alloc would assign raw to v0 (dies before the calls) and flags to s1, and emit a copy. The problem is purely cse's copy elimination.

So the real question: how to make cse1 keep the copy without an asm.

cse deletes `(set flags raw)` when it rewrites it to `(set raw raw)`. What if the source is not a plain REG but something cse won't rewrite to the same reg? E.g. `flags = raw + 0` folds to raw in fold_rtx. `flags = (s32)raw` same.

What if the copy is a *different mode*: `(set (reg:SI flags) (subreg:SI raw))`? no.

What if raw is in a *different quantity* because it was written by the call: `(set raw (reg v0))` — the call's return copy. Then `(set flags raw)`: insert_regs(dest=flags, classp=raw's class) → joins. Hmm.

What if we insert an instruction between them that modifies raw? Like `raw = raw ^ 0` (folds). 

What about a *partial* modification of raw that gcc can't fold but is a no-op? E.g. `raw |= 0` folds.

OK, radical idea: use the `fire`-style dead-reset trick on the *source* variable but arrange the first test to use a copy that was made before the reset. Since cse merges everything into one qty at the first copy, the reset invalidates the qty but the other regs (flags, t) still share a qty. Let's test what happens concretely with b4-style but with the ret fix. Actually let me look at the cse dump for the orig (with asm) to see what the RTL looks like — maybe the target's raw pseudo is actually not a C variable at all.

Let me dump the orig TU's cse.
