---
ts: 2026-11-06T09:43:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PSkhBKMR41jGkkPCt1jY
---
The includer TUs just include the header. No other copy.

Let me check the disassembly of the target function from the binary to be sure about insn 37/38. The diff already shows it.

OK, decision: item 3 is a WALL with best 2 (a single instruction-position diff). Wall tag: `sched1-argcopy-hoist` (existing).

But before finalizing, let me try a couple more real-C ideas during the remaining minutes:

Idea A: change the RMW to a *different type width*: the target's lw/and/sw are 32-bit. What if the source wrote `*(u32*)(s0+0x44) &= ~4;` (compound) — t1 = 2.

Idea B: what if the original C had the call *before* the RMW? w6 = 10.

Idea C: what if the 0x188 store were `*(u16 *)(s0 + 0x188) = 0;` but the *RMW* used `s0` via a variable `s32 t = s0;` defined *before* the if (so the copy is early)? no.

Idea D: maybe the real C used a struct pointer type, e.g. `typedef struct { u8 pad[0x44]; u32 unk44; ... }` — the store/RMW via struct members. The address computation is the same; but the RMW `p->unk44 &= ~4` might generate different RTL (same). Let me try a struct-based body? That's a big rewrite and could change many insns.

Idea E: the RMW might have been written with the load into v44 (reuse): `v44 = *(u32*)(s0+0x44); *(u32*)(s0+0x44) = v44 & 0xFFFFFFFB;` — but v44 was set before the inner if; reusing it here is semantically the same only if the inner if didn't change +0x44. If the inner if's true branch ran, +0x44 = v44|0x10, so reusing v44 would be wrong. Unless the load is fresh. u5 did a fresh load = 2.

Let me try the struct approach quickly? It's a big change and unlikely to fix the scheduling.

Alternative: maybe the real C had the 0x188 store *after* the RMW but the compiler's sched1 moved the store *up* because of the potential-hazard rule? In t3 the store stayed after the copy. Hmm.

Let me test one more thing: the store moved *before the inner if* (right after the 0x18A store):
```
*(u16 *)(s0 + 0x18A) = 0;
*(u16 *)(s0 + 0x188) = 0;   // moved up
if (...)
...
RMW
call
```
The target has the 0x188 store after the join (37), but maybe with this source the scheduler would place it... it would be in the first block, definitely different. Skip.

Let me instead try making the store the *last* statement before the call in a different block via an if:
```
if (*(s32*)(s0+0x184) != 0 && ...) {...} else {...}
*(u16*)(s0+0x188) = 0;
```
Already.

OK, let me also try: `*(u16 *)(s0 + 0x188) = 0;` written with the *same* base variable as the RMW via a cast to a struct pointer... no.

I'll accept the wall. Now, I need to fill time to 20 min (02:53). It's 02:44. Let me do a few more batches (each ~30s) with systematic variations, which is honest effort.

Batch z1-z8: permutations of statement order and spellings:
z1: RMW before store with compound assignment.
z2: store between the call's arg setup? no.
z3: store twice (0x188 and 0x18A) at the join? no.
z4: store via `*(u16 *)((u8 *)s0 + 0x188) = 0;`
z5: store via `*(u16 *)((s32)s0 + 0x188) = 0;`
z6: store via `*(u16 *)(s0 + 0x188) = 0, 0;`? no.
z7: RMW with the mask as a variable: `u32 m = 0xFFFFFFFB; *(u32*)(s0+0x44) &= m;`
z8: store with a `short` variable zero: `s16 z = 0; *(s16*)(s0+0x188) = z;`

Let me run them.
