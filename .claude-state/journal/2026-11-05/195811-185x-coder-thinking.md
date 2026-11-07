---
ts: 2026-11-06T02:58:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hrzD0JP3JvtiCTvD2rMi
---
Very close: mine has `sw zero,24(sp)` at 96 where the target has a nop. So the `flag = 0;` store was NOT fully deleted — it became `sw zero,24(sp)` (flag is a stack slot at 24(sp)). Flow didn't delete it because flag's address is taken (gte_stflg(&flag)), so it's a memory store.

So the dead-reset broke cse (great!) but left one store. We need the dead reset to be to a location whose store is deleted. If the reset is to a *register* variable (not address-taken), flow deletes the dead store entirely. `flag` has its address taken. `sp10` also has its address taken (gte_ldv0(sp10)). What about a new local that is NOT address-taken and used only here? E.g., declare `s32 z;` and do `z = 0;` — the store to z (a stack slot, memory) would still be emitted as `sw zero,K(sp)` because locals live in memory (not registers) in gcc 2.7.2 at -O2? Locals that are not address-taken can be kept in registers (they're pseudos). The front end assigns a pseudo to a scalar local; the store `z = 0` is a SET of a pseudo; flow's dead-store elimination deletes it. Then no instruction.

But wait: does a dead store to a pseudo get deleted before sched? flow.c's dead store elimination removes stores to pseudos not used later. Yes.

So use a local variable not address-taken, e.g. add `s32 z;` to the locals and insert `z = 0;`. But careful: adding a local changes the frame size! The frame is 0x38? The function has sp10[2] and flag. Adding z might increase the frame. However, if z is deleted (never materialized), no frame change. Let me test.

Alternatively use `t`? There's no t. The function has s0, sp10[2], flag. We could reuse `s0`? s0 is the table pointer (used). `s0 = 0;` would break the code.

Let me add a new local `s32 z;` and `z = 0;` between the statements. Also try `z = 1;` (any constant).

Actually, better: use a *register* variable that's already dead: `s0` is used later (func_801820E4(arg0) doesn't use s0). After the loop, s0 is dead! `s0 = 0;` after the store would be a dead store to a pseudo → deleted. But s0 is `u8 *s0`; `s0 = 0;` is valid. Hmm, but would cse see it as invalidating the memory? The dead-reset trick works because the SET of the pointer `p` invalidates cse's equivalence for expressions involving p. But our equivalence is a MEMORY equivalence (unk1C), not a register. Why did `flag = 0` break the cse memory forwarding? Because flag is a memory location (stack) and the store to flag invalidated the memory table entry for unk1C (cse's memory table: a store to an unknown-ish address invalidates other memory entries if they may alias). `flag` is at 24(sp), unk1C at 28(s1): cse's alias check (`true_dependence`) between a stack slot and a struct member may say "may alias" → invalidate → reload. 

So we need a store that (a) cse treats as possibly aliasing unk1C, and (b) is deleted before codegen. A store to a *pseudo* (register) is not a memory store → doesn't invalidate the memory table. Hmm. So we need a MEMORY store that gets deleted. A store to a local whose address is not taken is still a MEMORY store at RTL (locals are memory in gcc 2.7.2? or pseudos?).

In gcc 2.7.2, a scalar local that is not address-taken gets a pseudo (DECL_RTL = reg). So `z = 0` is a SET of a pseudo → not a memory store → doesn't invalidate the memory table. But maybe cse's `cse_insn` for a SET of a pseudo also invalidates memory? No.

Hmm. So we need a memory store to a stack slot that flow deletes. Flow deletes dead stores to pseudos only; a stack slot store is a memory store and is not deleted (no memory DSE). So any memory store that breaks cse will survive as an instruction. That's why i2 leaves `sw zero,24(sp)`.

Unless the memory store is to an address that is *aliased by the store we keep* — e.g., a store to the SAME unk1C address with a dead value would be overwritten by the next store... but it would still be emitted unless cse/flow removes it. Hmm, cse might remove a store that is immediately overwritten? No.

What if the dead store is to a location that is later *read* by a load that we then... no.

Alternative: make the dead reset a store to `unk1C` itself with a value that gets overwritten: 
```
unk1C = unkDC;
unk1C = 0;      // dead store, but memory stores aren't DSE'd
unk1C -= 1;
```
The target would then have an extra store. ✗

Hmm. So i2's score 1 is tantalizing but the dead store survives.

Wait — what if the dead reset store is to a *global* that is a constant and the store is optimized away by cse because it's redundant? E.g., `D_800AF7BE = D_800AF7BE;` — a store of the same value (a load then store); cse might remove the store as redundant (storing the same value it loaded). That's a real memory store that cse could eliminate as a no-op! If cse sees `t = D_800AF7BE; D_800AF7BE = t;` it may delete it (store of a value just loaded). Actually gcc's cse has an optimization for redundant stores (store followed by a store of the same value). Hmm, risky.

Better: a store of a constant to a global where the global's value is known? No.

What about a store to a *volatile-free* global that is dead because the global is never read? Compilers don't do global DSE.

Hmm.

What about breaking cse's memory entry with a *load* instead of a store? cse's memory table is invalidated only by stores. A load doesn't invalidate.

What about a `(clobber (mem))` insn from a call? A call clobbers memory (the call's CLOBBER includes memory?) — in gcc 2.7.2, a call insn's pattern includes a clobber of the return register and `(clobber (mem:BLK (scratch)))`? Actually calls clobber memory conservatively. If we insert a call between the two statements, cse would not forward, and the call emits instructions. ✗ (target has no call).

Hmm. What if the call is a `const` function that gets optimized away? no.

OK, what about making the *load* not be forwarded by giving it a different REG_EQUIV? no.

Let me think about i2 more: the extra `sw zero,24(sp)` is at instruction 96, where the target has a nop. Interesting — the target's nop at that position is the *load delay* nop for the reload? Let me look at the target: 20a0 lw v0,28(s1); 20a4 nop; 20a8 addiu. The nop is the load-delay slot. In mine (i2), at position 96 mine has `sw zero,24(sp)` and target has `nop`; the rest matches (108 ins). So mine's sequence is: lw v0,28(s1); sw zero,24(sp); addiu... and the target has lw; nop; addiu. The dead store landed in the load-delay slot!

If the dead store were eliminated, we'd match. So we need the dead-reset to be a store that is deleted by a later pass. The store to flag (stack, address-taken) survived.

What if the dead reset is to a *pseudo* that is also used in memory? Hmm.

What if the dead reset is to a local that is NOT address-taken: the store is a SET of a pseudo; flow deletes it. But does it break cse? cse's memory table isn't affected by a pseudo set. However — maybe cse's forwarding here is not via the memory table but via REG_EQUAL notes? The load insn 181 gets a REG_EQUAL note from the store? Hmm.

Let me test a non-address-taken local reset and see: add `s32 z;` and `z = 0;`. If it breaks cse AND gets deleted → score 0. Let me test. Also try `z = flag;` etc.

Also, maybe a store to a *pseudo* that cse treats as aliasing? No.

Let me test:
j1: add `s32 z;` and `z = 0;` between.
j2: use `s0 = 0;` (s0 dead after the loop? it's used in the loop only; after the loop, s0 is not used). `s0 = 0;` — s0 is a pointer pseudo; dead store → deleted by flow. Does it break cse? s0 is the base of the loop's loads; setting it might invalidate expressions involving s0 but not the unk1C memory entry. Hmm.
j3: `z = flag;` (load flag, store z).
j4: `z = unkDC;`?
j5: `flag = flag;`? no-op.
j6: `sp10[0] = sp10[0];`? store of the same value — cse might remove it as redundant! And it's a memory store that breaks the unk1C entry. If cse removes it as a redundant store (value unchanged), it emits nothing. Let me test.

Let me test j1, j2, j6.
