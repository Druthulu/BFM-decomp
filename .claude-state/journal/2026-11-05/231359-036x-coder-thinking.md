---
ts: 2026-11-06T06:13:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KHylPuhH2lX68cLJv9RX
---
Excellent! The register allocation is now right (pp=s7, zpush=fp) thanks to the do-while(0) loop depth boost on pp's ref. Score 3 = only the missing move pair.

Now the otz copy. Need combine not to fold `move s1,v0` + `move a0,s1`.

In w2 the call is inside do-while(0) — the set is inside the loop block, the use (arg) after... wait no, the use is the very next statement after the do-while. If do-while created a block boundary, combine couldn't fold. But it still folded (mine has move a0,v0).

Hmm, mine[54] move a0,v0 — so combine folded. Wait, but where's otz's set? If combine folded the copy into a0=v0, then otz's set for the later AddPrim use... Let me look: mine has `move a0,v0` and no `move s1,v0`. So otz's value is used later (sll a0,s1,2 in target uses s1). In mine, maybe otz goes elsewhere.

Hmm, actually if combine folded, then otz's set is gone entirely and the AddPrim use reads... v0? That can't be (v0 clobbered). Let me look at the actual mine asm. I need the candidate object. Use --keep? Let's use the diff more: only lines 54-55 differ, so the rest matches, including `move a0,s1`? No—line 54/55 is the only replace pair. mine[54]=move a0,v0; target[54]=move s1,v0, [55]=move a0,s1. After that, mine[55] aligns with target[56] — meaning mine lacks one insn. Then everything else matches, including the later `move a0,s1`? The later `sll a0,s1,0x2` in target uses s1. In mine, after the fold, what register holds otz?

Wait — if mine has `move a0,v0` then jal func_801823D4, then `move s1,v0`, that's the second assignment (otz = func_801823D4(...)). So mine: otz = call1 → v0 directly passed as a0; then otz = call2 result → s1. Then AddPrim uses s1. That works and is 1 insn shorter. Right.

So we need otz's first set to be materialized in s1: `move s1,v0`. The asm re-tie did it. Why does the asm help? Because the asm has "=r"(otz) : "0"(otz) — an output tied to input, which forces a real set of otz at the asm. Then combine can't merge the call result directly into the arg copy... but the target has the asm removed and the move pair remains.

Hmm, wait. In the target, after the asm removal (lever-free), the target still has the move pair because... the target IS the current src? No! The target is the baseline object from build/, which was built from the *original* src (with levers). So the target has the asm's effect. We need to reproduce it in plain C.

Plain C: make otz's assignment not directly copyable into the arg. Options:
1. Assign otz in a way that produces a real set: e.g. `otz = (s32)RotTransPers4(...)`. no.
2. Split the call: `{ s32 t = RotTransPers4(...); otz = t; }` — a copy, probably coalesced.
3. Use do-while around the *use*: e.g. put `otz = func_801823D4(otz, -0x1A);` inside a do-while(0) — then the arg copy is in a different block from the set. But combine still sees the copy as `(set a0 otz)` with otz's set in another block... combine can't fold across blocks. So this might work! The arg copy would be `move a0,s1` and the set `move s1,v0`.

But wait — in w2, the call was wrapped, and the use after; the fold still happened. So either the do-while doesn't create a block boundary, or combine folds anyway.

Hmm. Actually maybe the fold isn't from combine but from the *front end / expand*? No.

4. Make otz's value pass through an arithmetic identity that survives to combine: `otz = RotTransPers4(...) | 0`? folds at tree level.

5. C0414 dead-reset: `otz = 0;` after the call? That's a real 2nd set — the dead reset would be deleted by delete_dead_from_cse (before flow), so no.

6. Use a different variable for the call result then assign: `s32 t = RotTransPers4(...); otz = t;` — cse coalesces the copy, same thing.

7. Store otz to a stack var and reload? adds insns.

8. Use `otz` in the do-while condition? e.g. `do { otz = RotTransPers4(...); } while (0);` — tried (w2) but the fold persisted.

Hmm wait, in w2 the *use* (func_801823D4 arg) is outside the loop. Maybe the fold happens in the *combine* pass which sees otz's set in the loop block and the use in the following block... combine doesn't cross blocks. Unless the loop body and the following block were merged (the do-while(0) loop gets its block merged into the predecessor by jump optimization!). Then no boundary.

What if we put the *use* inside a do-while(0) instead? Then the copy `a0 = otz` is in a new block, and otz's set is in the previous block. Still maybe merged.

Alternatively use a control-flow structure that survives: an if that's not folded? e.g.
```
if (1) otz = ...; 
```
folded.

What about a `for (;;) { otz = ...; break; }`? Hmm.

Alternatively: make otz a **volatile**? no, that adds loads/stores.

Let's think about what the asm does at RTL: `__asm__("" : "=r"(otz) : "0"(otz))` produces a parallel insn with an output operand that is the *same* register. In RTL, this is an asm insn that sets otz from otz. Since it's a hard-reg... no, "r" allows any reg. It creates a genuine set of otz after the call, and a use of otz. So combine sees:
(set otz v0) ... (set otz (asm)) ... (set a0 otz).
The asm insn between prevents merging (combine won't fold across an asm insn).

A plain-C equivalent producing an insn between: any real computation that survives cse but is removed by combine, OR an insn that stays.

What about a *real 2nd set* that's value-preserving and cheap: `otz = (s16)otz;` would emit sll/sra (2 insns) — target has none. But wait: the target has 162 insns and mine 161. If I add 2 insns I'd get 163. Not good.

What about a use of otz that folds: e.g. `otz = otz * 1`? folds.

Hmm — what about `do { } while (0)` placed BETWEEN the set and the use, which is what w1 did — and w1 stayed at score 8, so no block split (or it didn't help). Hmm, w1 also didn't fix the register issue.

What about an empty `if (otz) { }`? That creates a test on otz — adds insns.

Alternative: change the loop structure so that the RotTransPers4 call is in one block and the func_801823D4 call in another *for real*: e.g. use `continue`:

```
for (; i < 12; ) {
    ...
    otz = RotTransPers4(...);
    if (i >= 0) { ... }
}
```
no.

What about reordering: `otz = func_801823D4(RotTransPers4(...), -0x1A);` — then combine folds to direct. Worse.

Hmm, what about making the argument an expression: `otz = func_801823D4(otz & -1, -0x1A)`? folds.

What about `func_801823D4((s32)(u16)otz, ...)`? adds andi.

What about assigning otz to a **u16/s16 temp** and back? `otz = (s16)otz` adds sign extension.

Hmm. Let's reconsider: maybe the fold is happening in *local-alloc/global-alloc* copy coalescing rather than combine? If otz is a global pseudo in s1 and the arg copy a0=otz... target keeps both moves. Mine folds. The difference must be an RTL insn.

Wait — actually maybe the asm's real effect is on the **global allocno**: the asm "=r" makes otz a hard-reg-ish? no.

Hmm, let me reconsider the target: `move s1,v0` at 301c, `move a0,s1` at 3020, jal, `move s1,v0` at 302c. So there are two assignments to otz: call1 result → otz(s1); call2 result → otz(s1). And the arg copy a0=s1.

In mine: call1 result → a0 directly; call2 result → s1.

So the difference is only the first assignment's materialization. In target, otz's first set is materialized. Why? Because of the asm re-tie forcing a set.

Plain C options that force a set without extra insns... 

Idea: **use otz between the two calls in a way that costs nothing**: e.g. `AddPrim(... otz ...)` before func_801823D4? no, changes order.

Idea: make the first assignment's value used *twice* before the second call: e.g. `otz = RotTransPers4(...); if (otz < 0) ...` no.

Idea: **combine's fold requires the pseudo to have a single use**. If otz's first value had 2 uses, combine wouldn't fold it into one. Can we add a second use that's free? E.g., the func_801823D4 call takes otz; what if we also pass otz to something that folds? Hmm.

Actually, maybe simpler: what if the RotTransPers4 result is used for the *stack arg* as well? no.

Alternative: change otz's declaration to `s16 otz`? Then the set would be `move s1,v0` + sign-extend (sll/sra) = extra insns.

Hmm, what about declaring otz `volatile s32 otz`? That forces a store/load to stack — extra insns.

Let me look at what actually happens: maybe the fold is done by combine's `try_combine` merging `(set otz (reg v0))` into `(set a0 otz)` because otz dies there. If otz had another use before dying, no fold.

What free second use could otz have? The AddPrim index is the *second* otz value. 

Hmm — what about restructuring: `otz = RotTransPers4(...); AddPrim(..., otz); ...` no, order.

What about the *else* branch: `v3p = arg0 + 0x8C;` no.

Let me look at this from the C0535 direction: do-while(0) splits cse1 EBB. But cse runs before flow, and combine runs after. If cse1 splits the EBB, does combine see separate blocks? cse's EBB split is internal bookkeeping; the actual CFG blocks are from jump optimization. Hmm, but cse's `delete_dead_from_cse`... 

Actually! Maybe the relevant pass is **local-alloc/global-alloc coalescing**: the copy `a0 = otz` and `otz = v0` form a copy chain. In the target the copy chain is broken by the asm.

Let me look for the RTL in a dump. I have the dumps for w0 (without do-while). Let me instead dump w2 and look at the .combine output to see what happened to the move. That's precise. Let me splice w2 and dump.

Actually cheaper: dump w0 already exists; let me check its .rtl/.combine for otz to understand. But w2 differs (do-while). Let me just dump w2 (fast, ~seconds).

Let me do it and grep the combine dump around RotTransPers4.
