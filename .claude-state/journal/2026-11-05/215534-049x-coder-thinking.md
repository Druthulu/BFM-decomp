---
ts: 2026-11-06T04:55:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Jv1M2ZIekZTXmZWcEGdn
---
Interesting! In the candidate, the load of D_80078EA6 (`lui v1; lh v1`) is hoisted BEFORE the store `sw v0` (sched1 reordering), whereas the target has the store first, then the load. The barrier (memory clobber) prevents sched1 from moving the load above the store.

So the barrier here is a *memory ordering* barrier (the `::: "memory"` clobber), preventing the load of D_80078EA6 from moving above the store to D_80078EA4.

Wait, but the target's ordering: `lw v0,EA4; addu; sw v0,EA4; lh v0,EA6; slti; bnez`. Candidate: `lw v0,EA4; lh v1,EA6; addu; slti; sw; bnez`. So the candidate's sched1 moved the independent load (EA6) up. The target keeps it after the store.

Is this sched1 or cse? The register difference (v1 vs v0) also matters. Hmm.

Actually, this is `sched1-load-order` or `sched1` reordering: the load of EA6 is independent of the store to EA4 (different symbols) so sched1 hoists it. The memory clobber in the asm prevents that.

A real-C way to prevent the hoist: make the load dependent on the store. E.g., store to EA4 then read EA6... they're different variables, so no dependency. Unless the C code creates a dependency: e.g., compute the new EA4 value, store it, and then use a value that depends on the store? Not in C.

BUT: the target's order is: load EA4, addu, store EA4, load EA6, slti, branch. In C: `D_80078EA4 += a1; if ((s16)D_80078EA6 >= 0xA1) ...`. sched1 moved the EA6 load before the store. To stop it, we can make the comparison expression depend on the stored value. Hmm, e.g.:

```
D_80078EA4 += a1;
if ((s16)D_80078EA6 >= 0xA1) { ... }
```
The load EA6 is independent. sched1 (the old one) uses REG_DEP_ANTI/OUTPUT and memory aliasing. It knows the store to EA4 and load of EA6 are different symbols → independent. The asm memory clobber marks everything.

Real-C move: introduce a *potential alias* — e.g., access the globals through pointers so the compiler can't prove they don't alias. `*(s32*)&D_80078EA4 += a1; if (*(s16*)&D_80078EA6 >= 0xA1)` — still distinct addresses, no alias.

Hmm, what if we access EA4 and EA6 through the *same* pointer base? E.g.:

```
u8 *p = (u8 *)&D_80078EA4;
*(s32 *)p += a1;
if (*(s16 *)(p + 2) >= 0xA1) ...
```
D_80078EA4 at 0x80078EA4 and D_80078EA6 at 0x80078EA6 = p+2! Yes! EA6 is exactly EA4+2. So accessing both through one base pointer `p` makes them potential aliases? No — p+0 and p+2 are distinct addresses; the compiler knows a 4-byte store at p+0 doesn't overlap a 2-byte load at p+2. Unless the compiler can't prove the offsets... it can.

What about making the load go through a `char *`? Still distinct.

Hmm. But note: sched1's dependency analysis on memory uses alias sets: it checks `true_dependence`/`anti_dependence`. For distinct symbols, no dependence.

What if the store were to a pointer that might alias the load address? E.g., store through a `void *q` parameter... but the address must be D_80078EA4.

Hmm, what about using the same *base symbol array*: `D_80078E78[]` is the base for the second half (`base + 0x60`). The first half uses the absolute D_80078EA4. If we access EA4 via `*(s32 *)(D_80078E78 + 0x2C)`? 0x80078EA4 - 0x80078E78 = 0x2C. And EA6 = 0x80078EA6 = base + 0x2E. Then the store at base+0x2C and load at base+0x2E — still distinct, no dependence.

Unless we use variable offsets the compiler can't disambiguate. But then the generated code would use computed addresses (different insns).

Alternative: sched1's ordering — maybe the issue is the *register allocation* (v1 vs v0), which changes the insn sequence anyway.

Hold on. Let me reconsider: maybe the difference is not sched1 but cse. In the target, the same block is duplicated 2x (first half) and 2x (second half) with the load in the *middle* position. In the candidate, the load is hoisted. Both have the block duplicated? The candidate's block at 608c-60b8 looks like the target's block but with the load hoisted.

Wait, but the score is 55 with 107 vs 114 insns — 7 insns difference. Where do the extra 7 come from? Let me count the blocks. The target has 6 blocks; the candidate maybe has 4 (cse merged some)?

Let me count target blocks: 
- first half: (1) a2!=0 arm, (2) call!=0 arm, (3) else arm.
- second half: (4), (5), (6) similarly.
Each block ~10 insns.

The candidate at 608c-60b8 has the a2!=0 arm; at 60d0-... the call!=0 arm. So still duplicated.

The 7-insn difference could be from the hoisted loads changing insn counts elsewhere (e.g., the third block's dead store being eliminated).

OK, let me look at the whole candidate vs target side by side in a compact way. Let me produce a normalized listing of both (just the instructions) and diff them.

Let me use objdump and cut the addresses, then diff. I'll write to .run under my shard.
