---
ts: 2026-11-06T06:16:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5pTXqBPZ1LMAbYfz9nMe
---
Order: ... cse2, jump, ... flow_analysis (2983), combine_instructions (3004), local_alloc, global_alloc.

So flow counts refs BEFORE combine. And dead code deletion: cse2 runs before flow; dead insns deleted by cse2/jump.

So a *dead* extra use would be deleted before flow → no ref. But an extra use that survives cse2 but is folded by combine would count.

For the otz problem, we want an insn between the call-result set and the a0 copy that survives cse2 (and flow) but is removed by combine. Hmm, but if combine removes it, fine.

What kind of insn does combine remove? E.g. `(set t (plus x 0))`, or a redundant copy.

Alternatively — what if the extra use makes otz have 2 uses so combine can't fold, and the extra use costs an insn? Then we'd be at 162+? No: we need exactly the target's 162.

Hmm wait. Let's reconsider. Maybe there's a cleaner path: instead of trying to block combine, make the *front end* not produce a direct `a0 = v0` copy in the first place. What does the tree look like: `otz = RotTransPers4(...); otz = func_801823D4(otz, -0x1A);` — expand emits (set otz (call)) then (set a0 otz) etc.

Combine: `(set otz (reg v0))` followed by `(set a0 otz)`. try_combine does a 2->1 combination: it sees otz is dead after (REG_DEAD on the copy) and substitutes v0 into the a0 set. That's the standard "set of a register that is dead can be folded into the user".

To prevent: otz must not be dead after the a0 copy, i.e. otz must have another use *before it is overwritten*. In the source, otz's first value is used only once. If we add a second use of the first value... but that's an insn.

Unless the second use is in the same insn! For example, if `func_801823D4` took otz twice: `func_801823D4(otz, -0x1A)` — no.

Hmm, what if the call is `func_801823D4(otz, -0x1A)` and we write `func_801823D4(otz, otz - 0x1A - otz)`? folds.

What about `AddPrim(..., q)` — the second arg is q.

Hmm, what if otz's value is used in the same statement in a foldable way: e.g.
```
otz = func_801823D4(otz + 0, -0x1A);
```
`otz + 0` folds at tree level.

`otz * 1` folds.

Hmm, what about the *loop increment*: `i++`? no.

Different approach: give otz a second *set* before the use, so combine's fold sees otz's value defined twice? no.

OK, let me think about the target more: target has `move s1,v0` then `move a0,s1`. That's exactly the RTL (set otz v0), (set a0 otz) with otz in s1. So the target's RTL is the *unfolded* version. The asm prevented the fold.

Could we instead prevent the fold by making otz **live across a call**? If otz's first value were live across the func_801823D4 call... no.

Alternatively: prevent combine's fold by having otz's set be in a different basic block from the a0 copy. The do-while(0) put the call in a loop block, but jump optimization merged... Actually the dump shows LOOP_CONT/LOOP_END notes and then insn 164 (a0=v0) right after the LOOP_END — so the copy is in the same block (the loop block ends right there). Combine's try_combine works on LOG_LINKs within a block; here the set is in the loop block and the copy after LOOP_END... but they're adjacent insns and combine does combine across block boundaries? try_combine uses insn links within a block. Hmm, apparently it still merged (the result shows a0=v0 with REG_DEAD v0, and otz's set gone).

Hmm wait — maybe the fold happened in *cse2/jump*, not combine. The dump I looked at is `.combine` (after combine). Let me check the `.cse2` or `.jump2` dump to see where otz's set vanished. Actually the .cse2 dump would show it before combine.

Let me grep w2.i.cse2 (that's after cse2) for the same region. If otz's set is already gone there, the fold happened in cse/jump.

Actually more efficient: grep the .rtl dump (before cse) — but let me just check cse2.
