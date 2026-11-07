---
ts: 2026-11-06T10:54:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nxiBX761ml3aj3RGjc5q
---
v_ref4: order correct (lw, lui, addiu, sw88, ori, sw) but regs still swapped (t v1, a v0). Hmm, so the 4 refs didn't flip it. Because with `t = t|2; store t`, maybe combine merged it back to 2 refs.

Let me check the .lreg for v_ref4? That requires a spliced TU. Hmm.

Time: ~03:58 now, started 03:35 → 23 min. I should wrap up item 1 soon. But I'm close: multiple score-2 candidates.

Let me try one more idea for the reg flip: make `a` an HImode or a different size? qty_size affects priority: size 4 for SImode. If a were HImode (2 bytes), its priority halves: 1*2*2 = 4 vs t's 8. But the address must be SImode.

What if `a` is not a variable at all but the store uses a *u16*? no.

What if I make the address pseudo share with something? 

Alternative: give t an even higher priority by making it a pointer? No, size is 4 either way.

What if t is used 8 times? floor_log2(8)=3.

Hmm, what about the opposite: make `a` have refs=1 (a single use)? a has a set and a use = 2 refs. A constant address `(s32)&D_801907C4` used once is one pseudo. If the store used the symbol directly (`unk58 = (s32)&D_801907C4`), then the constant is loaded into a pseudo — refs=1? A constant pseudo (reg_equiv_constant) isn't a qty; it's a constant that reload materializes. Hmm! In the ORIGINAL C, the store is `unk58 = (s32)&D_801907C4;` and the address is a *constant* pseudo (reg_equiv_constant), not a qty. Then local-alloc doesn't allocate it; reload materializes it into a register later (after local-alloc). Reload picks v1 because v0 is taken by t.

That's why v_addr (with the `a` variable) behaves differently: making `a` a variable creates a real qty competing with t.

So: DON'T introduce `a`. Use the constant directly. Then the address is a constant pseudo → reload assigns it a register. The original v_addr3/v_addr introduced `a`; but the target's address is materialized by reload.

But earlier, with the constant directly and the do-while (d_S2S3S4), we got score 2 with the store sinking and t v0 (correct regs!). The issue there was only the store's position.

So back to d_S2S3S4 (score 2): the store sinks. The address is a constant pseudo → v1 by reload. The regs are right.

So I need to fix the store sinking without introducing a qty. What if I introduce a variable for the address ONLY to... no.

Idea: make the store's *value* a variable that is already in a register and used elsewhere? Hmm.

What if the store is written to a different location expression that the scheduler treats as higher priority? E.g., `*(s32 *)((s32)a0 + 0x58) = (s32)&D_801907C4;` (cast spelling). The RTL is the same.

Hmm. What if I move the store *earlier in the source*, before the load? Then the RTL order is store, load, ori. sched1 with the load present: it might issue the load first (hoisting) then the store... Let's think: if the source is:
```
do { unk58 = &D_801907C4; } while(0);   // block1
t = unkC4;                               // block2
unkC4 = t | 2;
```
Then the schedule: block1: lui, addiu, sw. block2: lw, ori, sw. Order wrong (store before load).

If instead no do-while and the source is store-then-load:
```
unk58 = &D_801907C4;
t = unkC4;
unkC4 = t|2;
```
sched1 may hoist the load above the store (independent) → lw, lui, addiu, sw, ori, sw = the TARGET! Let me test that: p_S3S2S4 (from my permutation set) scored 11 — the load was hoisted to 19 (above the earlier stores), not just above the unk58 store.

Hmm, but if I put a do-while around the load in that order? `unk58 = ...; do { t = unkC4; } while(0); unkC4 = t|2;` — then the load can't hoist above the store (block boundary after it). Order: store, load, ori. Wrong.

What if the do-while wraps the *preceding* statement so the load's block starts after it? That was v_dw5 (do-while around unk5C) → nop + store sunk.

OK here's another thought: what if I make the load *depend* on the unk5C store via a memory dependence by making them the same "varying" address? Earlier analysis: memrefs_conflict_p with both addresses base+const (same base) → no conflict. But if the load's address is `(reg)` alone (varying) and the store is base+const, memrefs_conflict_p may return 1 → dependence → the load can't hoist above the store. That's the p_ptr experiment (v_ptr) — but cse folded p.

What if p is a *global* variable? No.

What if the load's base is a *different* pseudo that cse can't merge: e.g., a pointer passed through a function? No.

Hmm, what about making the load's base the value stored at unk20 (the s32 field)? `t = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + ...)` — no, wrong semantics.

Let me look at the time: 24 min. I'll give this ~5 more minutes, then record WALL best 2 and move to the next item. Actually, the brief says: "Budget 20-30 min wall per item; past 30 min stop and record a wall". So I have until ~04:05.

One more idea: the sched1 store sinking. What if the store to 88 uses a *different mode* (e.g., store a u32 vs s32)? Same.

What if the store is `*(u32 *)&s0->unk58 = (u32)&D_801907C4;`? Same.

What if I add a *second* use of the address constant so it gets a register earlier? E.g., store the same address to another field too? That changes the code.

Hmm, what about the order of the two stores: target sw88 then ori/sw196. In d_S2S3S4 the RTL order is already store then ori. sched1 swapped them. sched1's priority: ori = 1 + priority(sw196). sw88 = 1. So ori wins. To make sw88 win, its priority must be higher: if sw88 had a successor... a store has none.

Unless sw88 is not a store but part of a chain: e.g., if the stored value were used later. `a = (s32)&D_801907C4; unk58 = a;` — a's def is the lui/addiu; a store doesn't produce a value.

What if the store's address depends on the ori? No.

What if we write the store as a *read-modify-write* (e.g., `unk58 = ...` is a plain store). Hmm.

What if the store is scheduled as part of the memory-dependence chain with the load? In sched1, memory insns get dependences in order: the load, the store, the store. They're ordered by source. The ori isn't memory. So the ori can move freely. The scheduler picks the highest priority ready insn.

Priority of the ori = 1 + priority(sw196). Priority of sw88 = 1. So the ori always wins... unless the ori isn't ready yet (depends on the load). If the load is issued at cycle 0 and has a 2-cycle latency, the ori is ready at cycle 2. The store is ready at cycle 1 (after addiu). So the scheduler at cycle 1 picks sw88! That's exactly what happens in the target (with the load in the same block).

In v_addr4, the load is in the PREVIOUS block, so the ori is ready at cycle 0 and beats the store. Hence the sinking.

So: the load MUST be in the same block as the store and the ori. And then t's qty competes with the address constant pseudo (which is NOT a qty — it's a constant!). Wait, in d_S2S3S4 (the load wrapped in a do-while, store+ori in the next block), t is global. Hmm.

But what if the do-while wraps the statement BEFORE the load (unk5C) so the load, store, ori are all in the SAME block (the block after the do-while)? That was v_dw5 — the schedule was lw, nop, ori, sw, ... — the store sank! Because in v_dw5, the block starts at the load; the load is issued first (priority high), then the ori (ready at cycle 2), and the store... hmm, the store should be ready at cycle 1.

But v_dw5 gave: lw, nop, ori, sw196, lw32, lui, addiu, sw88. So the store was delayed even beyond the next load. That means the address computation (lui/addiu) was itself delayed — the constant pseudo's materialization was placed late by reload, not sched1! Because the constant is materialized at reload time, and reload places the lui/addiu near its use. So the store can't be scheduled until after the constant is loaded.

So with the constant pseudo, the address materialization is a reload artifact placed just before the store. The scheduler can't help.

In the target, the address (lui/addiu v1) is placed at 29-30, right after the load. That's because with the barrier, reload placed the constant materialization there (the reload insns are placed in the block and then scheduled? reload happens after sched1; sched2 might reorder). Hmm, the target's final schedule includes the reload insns, so sched2 (post-reload) did the ordering.

This is getting really deep. The register v1 for the constant is chosen by reload.

OK, given the complexity, let me consider that this item might be a WALL. But wait — the wall needs ≥30 scored tries (I have ~20). Let me count: orig(1), nopin, nobar, win0, v_param, v_cast, v_dw, v_dw2, v_dw4, v_or, p_all, p_or, 12 p_*, 12 d_*, 12 e_*, v_dw5, v_addr, v_addr3, v_addr4, v_addr5, v_ptr, v_ref3, v_ref4, v_bar, v_bar2. That's way over 30 scored tries. Good.

But before giving up, let me try the one shape I haven't: the do-while around unk5C *plus* the address as a variable (so reload isn't the issue). Hmm.

Actually, let me try a cleaner idea: the load + store + ori in one block, with the address as a *variable* so sched1 can schedule it. That's v_addr3 (a first) or v_addr (t first).

v_addr3 (a first, t second): order lui, addiu, lw — the address was scheduled first because it's first in source and ready. But if the load is first in source (v_addr), the order is lw, lui, addiu, sw, ori, sw ✓ with regs swapped.

So v_addr has the perfect order. Only the regs are swapped: t v1, a v0. In v_addr, both t and a are in the same do-while block; a is born later → shorter range → v0.

What if `a` is born EARLIER but still scheduled after the load? sched1 uses source order for equal priority. If a is first in source, it's scheduled first.

Unless the load has a HIGHER sched priority than the address computation. The load's priority = 1 + priority(ori). The address's = 1 + priority(sw88). Both 2? Hmm, if the load's dependent chain is longer (ori→sw196), and the address's (sw88), they're both depth 2.

What if the load feeds a longer chain? Not semantic.

OK: alternative — make `a` a *constant expression* at its use but give t more refs so t wins v0. In v_addr, t has 2 refs, a has 2. If t has 4 refs (t = t|2; store t) and a has 2, t should win. That's v_ref4 — but it scored 8 with regs swapped. Hmm, so combine probably merged `t = t|2` back.

Let me check whether v_ref4's RTL has t with 4 refs — hard without a dump.

Alternatively make `a` have fewer refs: a = (s32)&D_801907C4; unk58 = a; → 2 refs. Could we make a have 1 ref? If `a` is initialized at its declaration and used once: `s32 a = (s32)&D_801907C4;` — still a set + a use = 2.

Hmm, what if `a` is a `register`? Not allowed.

What if `a` is declared with an initializer that is a constant expression evaluated at compile time... no, the address isn't a constant.

OK, one more: use the constant directly (no a variable) AND put the load in the same block via a do-while around the preceding statement, but ALSO ensure the constant materialization is scheduled early by giving the store a higher priority... 

Actually! What if I put the *store* in the same do-while as the load, and the RMW outside? e_S2S3S4 = 7 (regs swapped). Hmm.

I'll stop the exploration here and record a WALL for item 1 with best 2. Wait — but the two small items are twins; if I can't crack one, the other is also a wall. And the two big ones are also twins.

Hmm, that would be 4 WALLs. Not great but the task allows walls.

Actually, let me try ONE more thing that's cheap: in v_addr (order perfect, regs swapped), make the address `a` a *u8 pointer* or use a different size to change qty_size. qty_size for a pointer is 4 (same). If `a` were declared `s16`, its size is 2 → priority halves → t wins v0! But the address is 32-bit; truncating to s16 would break the value. Unless we cast back: `s16 a = (s16)(s32)&D_801907C4;` — wrong value.

What about declaring `a` as `u32`? size 4.

Hmm, qty_size is based on the mode (SImode → 4). A pointer is SImode too.

What if `a` is a HImode variable holding part... no.

OK, what about making `t` a *pointer* (Pmode = SImode, size 4)? same.

Alright, let me try the HImode trick on the *store*: no.

Decision: record WALL for item 1 with best 2, then move to item 2 (same family). But wait — before that, let me reconsider one thing: maybe the target doesn't need the store before the ori in a way I think. The diff in d_S2S3S4 was exactly 2 (one instruction moved). It's a "sched1 store sink" wall. There's a wall tag: `sched-store-sink sched scheduler sinks a store past the target slot (G28)`. That's the tag!

So this is a known wall: sched-store-sink. Best 2. I'll record it as WALL with that tag.

Hmm, but wait. Let me try one last thing: the cookbook C0414 "dead-reset cse-breaker" and C0535. C0535's second use replaced a scheduling barrier. We used do-while. 

What about wrapping the *store* in a do-while with the RMW: 
```
do { t = unkC4; } while(0);
unk58 = &D_801907C4;
do { unkC4 = t | 2; } while(0);
```
Then the store is in its own block between two blocks. The store block: [store] alone (the constant materialization there too). Order: load block, store block, RMW block. That gives: lw; lui, addiu, sw; ori, sw. Target: lw, lui, addiu, sw, ori, sw — the same order! Regs: t is global (block1→block3) → v0? The address constant in block2 is materialized by reload into v1. This could work!

Wait, I think I tried something like this (v_addr5 without the a variable?). v_addr5 used an `a` variable. Let me try with the constant directly and three do-whiles. Actually just two: the load wrapped, and the RMW wrapped. The store unwrapped between.

Let me test: v_dw6.
