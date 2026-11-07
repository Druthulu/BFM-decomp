---
ts: 2026-11-06T09:35:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ES4yijo4fJvj2kmYnXmv
---
This is the TU-level sched dump (all functions). Our function starts at 80472. The blocks with insns 37/40/42 (block 2) are early in the function. Hmm, insn numbers here are the RTL insn uids, not final indices. The block "2 from 37 to 42" has insns 37 (priority 1), 40 (priority 2), 42 (barrier). 

I need to map to our function. The function starts at line 80472. Blocks 0-4 are in our function (they're small). Block 2: insns 37,40,42. Hmm.

Rather than the sched trace, let me compare the .lreg dumps (after local-alloc) for the store and copy. The relevant difference might be in local-alloc (which reg the store's base uses) rather than sched1.

Actually the diff shows: orig: `sh zero,392(s0)` at 37 then `move a0,s0` at 38. win: `move a0,s0` at 37 then `sh zero,392(a0)` at 40.

In orig, the store uses s0; in win, the store uses a0. That's a register substitution: in win, the compiler propagated a0=s0 into the store (and hoisted the copy). This is the "copy propagation" in sched1/local-alloc: local-alloc may tie the store's base pseudo to the copy's source/dest.

Wait, actually the store's base is the *variable* s0 (a callee-saved pseudo). The copy a0=s0 is a separate move created for the call arg. In win, the store uses a0 — meaning the store's base pseudo was rewritten to the a0 pseudo. That's regmove/copy-propagation.

Hmm, in orig the store uses s0 and the copy comes after.

Since the asm use of s0 sits between, the store can't be rewritten to a0 (the copy would have to be before the asm; the asm use of s0 forces s0 to be live, and the copy is after).

Real C: we need a use of s0 between the store and the copy. Is there any genuine one? The RMW is after the asm and uses a0. Hmm, what if we write the RMW's *value load* using s0 explicitly in a way that stays s0... The compiler chooses to rewrite all post-copy uses to a0.

What if the RMW came *before* the 0x188 store in source? Then s0 is used (RMW) after... no: the order would be RMW, store, call. Target: store, copy, RMW, call. So no.

What if we split the RMW: `u32 v = *(u32*)(s0+0x44);` before the 0x188 store, and the store `*(u32*)(s0+0x44) = v & ~4;` after? That's semantically the same (no other writes to +0x44 in between? The inner if writes +0x44 in the true branch, but the RMW is after the if/else — reading before the store would read the value after the if/else, which is fine since the load is also after the if/else... wait, if I move the *load* before the 0x188 store but after the if/else, the value is the same (0x188 store doesn't touch +0x44). So:

```
u32 v = *(u32 *)(s0 + 0x44);
*(u16 *)(s0 + 0x188) = 0;
*(u32 *)(s0 + 0x44) = v & 0xFFFFFFFB;
func_801553C0(s0);
```
The load uses s0 (before the store), the store uses s0 (after). Hmm, but the target's `lw v0,68(a0)` uses a0, not s0! So target's RMW load is via a0. If we move the load before, it'd be `lw v0,68(s0)` — different.

Hmm. What if we keep the RMW as-is but make the 0x188 store's base depend on something that must be computed... no.

New idea: what if the call's argument is not s0 directly but a copy variable that is defined *after* the store in source, e.g.:
```
s32 arg = s0;
...
func_801553C0(arg);
```
Then `arg` is a separate variable; the copy a0=arg... The compiler might coalesce arg to s0. Hmm, try.

Or: `func_801553C0((s32)(s0));` tried (t6) = 2.

Another idea: reorder the source so that the 0x188 store comes *after* the RMW but the compiler moves it before? Unlikely.

Let me look at the .lreg dump to see how the store and copy are represented. Let me find the block in the lreg dump. Actually, let me compare the two .lreg dumps around the region with diff (they're huge; use a window). The function starts at line 80472 in sched; for lreg the line numbers differ. Let me grep for "func_8016432C" in each and then look at the first ~200 lines after.

Alternatively use alloc_table for both and compare rows. The alloc table shows pseudos/priorities. Let me look at the store base pseudo and the copy.

Hmm, time: 02:34. Item 3 started 02:32:49, so ~1.5 min. Plenty of budget (20-30 min).

Let me think about the actual real C. The keepalive is between the 0x188 store and the RMW. In the real game's C, what would create a use of s0 there? Maybe the real C had a *different statement* there: e.g., `*(u16 *)(s0 + 0x18A) = 0;` — wait, the 0x18A store is at the top (insn 15). Hmm.

Actually, maybe the real C had the 0x188 store *inside* a statement like `s0->unk188 = s0->unk18A = 0;`? Chained assignment! `*(u16*)(s0+0x188) = *(u16*)(s0+0x18A) = 0;` would produce: store 0 to 0x18A, then store to 0x188 (or vice versa). Target has 0x18A store at 15 and 0x188 at 37 — far apart, so no.

What about the real C using a *pointer* variable for the +0x44 RMW that is loaded from s0? 

Let me try a different tack: maybe the answer is to move the RMW statement *before* the 0x188 store in source, and the target's order (store at 37, RMW at 39) could still result if sched1 reorders? Let's test t3 was the reverse (store moved after RMW) = 2 (same diff?). Let me check t3's actual insn order — maybe t3 = 2 but with a different diff.

Actually t3 score 2 COUNT; let me see its diff.
