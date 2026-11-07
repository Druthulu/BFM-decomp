---
ts: 2026-11-06T10:04:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pAWzNL4gAfDIVNY64q2b
---
Line 300 is exactly our situation: `keepalive,pin | func_80183E68 | WALL lreg-copy-pref-dying-base — local-alloc ties rv=(s32)a0 to the dying a0, so the target's move v0,s0 disappears; void def makes the value dead; lever-free 42/43, 30 tries (G26)`.

That's a WALL tag for a void-def missing move v0,s0! That's item 1's exact wall: "lreg-copy-pref-dying-base". So item 1 = WALL with that tag, or a new tag. Good, that confirms item 1 is a known wall class.

Now for item 2, line 178: "pin | func_801415C0 | WALL lreg-qty-order — locals c,d take $s0/$s1 before globals a,b,e; the target has a=$s0,b=$s1 and no plain-C spelling flips the order (G07)". Hmm.

Line 165: "WALL global-alloc-nrefs-prio".

But maybe item 2 can be cracked by making s1ang's local-alloc choose s1. Let me think about local-alloc's qty ordering. Let me read local-alloc.c to see how it picks the reg and the order.

Actually, key realization: r75 (s1ang) is local with refs 2, live 7, and crosses 1 call. Local-alloc assigns it a callee-saved reg. Which one? The `reg_alloc_order` for GR_REGS: let me check. In gcc 2.7.2 mips.h, `REG_ALLOC_ORDER` might put s0..s7 after t regs. The first callee-saved = 16 (s0). So s1ang gets s0.

For s1ang to get s1, s0 must be taken by another qty in local-alloc whose live range overlaps s1ang's. Are there other local qtys crossing the call? Let me check the lreg table: only r75 "crosses 1 call" and is local. So no.

UNLESS we introduce one via C. E.g., a second variable live across the call in the same block. But any such variable would also need to be used after the call, adding code... unless it's dead? Dead values are eliminated before allocation (flow does DCE before local-alloc? flow is run before local-alloc — yes, in the pass order: flow, combine, sched, local-alloc... Actually `-O2` pass order in gcc 2.7.2: ... flow, combine, sched, local-alloc, global-alloc ... Let me check toplev.c).

Hmm, a dead value would be removed by flow's DCE (dead code elimination) before local-alloc. So we can't add a dead local.

What if we add a variable that's live across the call and *used* after, but the use is optimized away later? It must survive to local-alloc.

Alternatively: make s1ang's live range NOT overlap s0's availability... 

Hmm, what if we make `d` local by putting all its uses in block 0? Can't.

Wait, actually — let me reconsider. Maybe we can make d's live range *shorter* so that in global-alloc it gets... no, global-alloc happens after local-alloc; s0 is already taken by s1ang.

So the ONLY way is to change local-alloc's assignment of s1ang to s0. Since s1ang is the only local qty needing a callee-saved reg, it gets s0 (the first in reg_alloc_order). Unless we can make local-alloc prefer s1 for it via a *copy preference*! 

Local-alloc has copy preferences: if a qty is copied to/from a hard reg, it prefers that hard reg. E.g., if `s1ang` is initialized from a value in s1, it prefers s1. Hmm.

Alternatively, if s1ang is *copied* to a variable that... 

Hmm, what about `qty_phys_copy_sugg`? Local-alloc prefers a hard reg that the qty is copied from/to. If we write the load as `s1ang = ...` the source is memory. No preference.

What if s1ang is loaded into a temp first and then copied? That adds a move.

Hmm, what if s1ang's *use* is `u6 = s1ang & 0xFFF` — no copy.

What if we write `u6 = s1ang; u6 &= 0xFFF;`? Still no hard reg preference.

Hmm.

Alternatively, make local-alloc assign s1ang to a *caller-saved* reg by not crossing the call. But it must cross.

Hold on — let me reconsider the target. What if in the target, s1ang is NOT live across the call because the load is *after* the call and the target's `lh s1,18(v0)` before the jal is actually a DIFFERENT load that happens to be s1ang? No, there's only one such load.

Hmm wait, actually, let me reconsider the target's instruction order. What if `lh s1,18(v0)` is in the *delay slot* region... no, jal's delay slot is 38f8.

OK, let me reconsider from the "original source" angle: the ORIGINAL source (from Square) presumably had a shape that gcc compiled to this. Our reconstruction is a guess. Maybe the original had:

```
s32 d;      // divisor
s32 s1ang;  // 
...
```

Alternatively the original might have had `d` as a *function parameter* used directly, e.g., the divisor was `arg1` used as `(s16)arg1` in the divisions. Then the pseudo for arg1 is live from entry to the divs. It's global. s1ang local gets s0. Still d gets s1.

Hmm, so how did the original get d in s0?! Unless in the original, s1ang was assigned s1 by local-alloc because of a copy preference or because another qty took s0.

Let me look for the possibility that in the original, there was a second local variable crossing the call. Look at the target's registers: only s0 and s1 are callee-saved used. If another local qty crossed the call, it would need a third callee-saved reg (s2) unless it shares.

Wait — unless the "other" local qty crossing the call is assigned s0 and s1ang s1, and that "other" is... the `u5` value? u5 is defined by the call (in v0) and used after (andi a0,v0). It's local, but v0 is caller-saved and free (the call result is in v0). Local-alloc gives it v0/a0, not callee-saved.

What about `iVar4`, `q`? They're in later blocks.

Hmm.

What if the original's s1ang was defined BEFORE the call in a way that it also gets a copy preference for s1? Like `s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);` — no.

Let me look at local-alloc.c's reg choice: maybe it prefers a reg that's already dead at the qty's birth (to avoid saving). Let me read the relevant part.
