---
ts: 2026-11-06T06:14:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gb325BDpZfpHAKCh0xUH
---
Interesting: after combine, `insn 164: (set a0 (reg v0))` — otz's pseudo is gone. That means the front end or cse already turned `otz = RotTransPers4(...)` into a0 directly, or combine merged.

Note "(note 151 ... NOTE_INSN_DELETED)" and LOOP_CONT/LOOP_END — the do-while(0) DID create loop notes! That's why pp's ref got boosted.

So where did otz's set go? Look at the call insn: `(set (reg v0) (call ...))`. Then insn 164 sets a0 = v0. So combine merged `(set otz v0)` + `(set a0 otz)` into `(set a0 v0)`.

In the target (with asm), the asm insn sits between. To block this, we need an insn between the call result set and the arg copy that uses otz.

Idea: `otz` used in a dead-but-surviving computation that combine can then fold into the next use... 

What if we write the arg as an expression involving otz that folds into a0? Like `func_801823D4(otz, -0x1A)` — already.

Hmm what if the call result is assigned and *then* the same value used to index something cheap... 

Alternative: use `otz` in a `do { } while (0)` condition? `do { } while (0)` with an empty body: `do { } while (otz, 0);`? The comma operator — `(otz, 0)` would fold to 0 at tree level, but does the front end emit a use of otz? Probably folded by fold().

What about `if (0) { otz++; }`? deleted.

Hmm — what about making otz's *first* set be a real computation: `otz = RotTransPers4(...); ` then later `otz = func_801823D4(otz, -0x1A);`. What if we add a real use of the first otz value that costs nothing: e.g. `q->unk = otz`? That's a store — extra insn.

What about the *second* call's arg: it's `otz`; what if we pass `otz` twice: `func_801823D4(otz, -0x1A)` — only one.

Hmm. Consider the C0414 dead-reset move: "dead-reset cse-breaker; cracked 3 launders in G16x". A dead reset is `x = 0;` which is deleted by cse's dead-store elimination (delete_dead_from_cse) — but that happens in cse, which is *before* flow. Hmm, but the note says it works as a cse-breaker for equivalence classes, not refs.

What about a dead reset that survives to combine: `otz = otz + 1;` dead? It'd be a real insn and then deleted? Dead code deletion happens where? `delete_dead_insns` in toplev is called after jump, before flow? Let me check: In gcc 2.7.2 toplev.c pass order around flow. Let me grep.
