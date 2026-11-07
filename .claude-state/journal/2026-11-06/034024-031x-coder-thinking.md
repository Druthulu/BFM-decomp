---
ts: 2026-11-06T10:40:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rc5W53QA5jpXwe9FRf4W
---
Excellent, much closer. Now the only diff: the load `lw v1,196(s0)` at mine[19] is scheduled EARLY (before the D_801907D4 address etc.), whereas the target has it at 28 (later, after `sh v0,92(s0)`). And the regs: mine loads t into v1 and address into v0; target loads t into v0 and address into v1.

Wait mine[19] `lw v1,196(s0)` is placed early — that's because without the barrier, the load got hoisted up. And mine[35-37] `ori v1,v1,2; sw v1,196; li v1,16384`. Target: load at 28, address v1, sw, ori v0, sw v0,196, li v1.

So the barrier removal let sched1 hoist the load earlier. We need to keep the load late (after the D_801907D4 store and the 0x8000 store), i.e., where it is in the C.

The C order: ... unk5C = 0x8000; [barrier]; t = unkC4; unk58 = &D_801907C4; unkC4 = t|2; ...

The barrier kept the load from being hoisted above unk5C=0x8000. Without it, sched1 hoists the load to mine[19] (before the li 1 / sh 2(s0) etc.? mine[19] is early — before `li v0,1; sh v0,2(s0)`).

How to keep the load late without a barrier? Real-C moves: make the load depend on something, or make a store before it that it can't cross. The load is from unkC4 (196). The stores before it are to unk2, unkC0, unkBC, unk5C — different offsets, but the compiler doesn't know they don't alias (it does know: same base pointer s0 with different constant offsets → they don't alias since offsets differ and types differ? Actually a store to 92(s0) and a load from 196(s0) can be proven non-aliasing).

In the target, the load is placed right after the unk5C store, before the unk58 store. The unk58 store is to 88(s0). The load from 196(s0) doesn't alias 88 either.

So in the target, sched1 chose to keep the load at its source position (after the 0x8000 store). In mine it hoisted the load above everything (to position 19). The barrier stopped that.

Real-C way to stop hoisting: create a dependence. E.g., make the load address depend on a previous store's value, or use a volatile read. Volatile is not a "lever"? Volatile is a C qualifier — the brief's levers are pin/launder/barrier/keepalive/asm. Volatile might count as a barrier-ish trick? The target itself is `volatile u16 *pbh` in func_8018B238, which the author used for the double read. Hmm, but for this item, adding volatile to force ordering is arguably a "launder/barrier" in spirit. The rules say lever-free = none of the row kinds remain, no new lever of any kind. A volatile read is a real C construct but functions as a scheduling barrier. The original author used it as a lever in other funcs (§37). I'd rather avoid volatile as it's the same class as a barrier.

Alternative: change the statement order so the load sits where the target has it — it already does in source. The scheduler hoists it because it's independent. To block, make it dependent on the preceding store's value: e.g.,

```
unk5C = 0x8000;
t = unkC4;
```
The target has the load after the unk5C store. If we reorder the C: put `t = unkC4;` after `unkBC = &D_801907D4;`? The target order is:
```
sh 1,2(s0)        unk2
sb 1,192(s0)      unkC0
lui/addiu v0,D_801907D4; sw v0,188(s0)   unkBC
li v0,0x8000; sh v0,92(s0)               unk5C
lw v0,196(s0)     t = unkC4
lui/addiu v1,D_801907C4; sw v1,88(s0)    unk58
ori v0,v0,2; sw v0,196(s0)               unkC4 = t|2
```
So in the target, the load is between the unk5C store and the unk58 store. That's the source order. Mine hoists it to 19 (before unk2 store).

Hmm, why does the target keep it? Because of the barrier. Without it, sched1 hoists. So we need another dependence.

Idea: make `t` load address depend on something computed before. E.g., write the unkC4 access through the same pointer variable used in the previous store? Already s0.

Idea: use `t = ((Unkstruct*)s0)->unkC4;` — same.

Idea: make the load use the result of the unk5C store? Like `unk5C = 0x8000; t = unkC4;` — no dependence.

What about reordering the C statements so that the load naturally lands where the target has it *after* scheduling? If sched1 hoists the load as early as possible, then to get it at position 28, we'd need a dependence chain. Hmm.

Wait, maybe sched1 hoisted the load because it was in the same basic block and had a long latency. In the target, the barrier created a block boundary at that point. Without the barrier, the whole tail is one block, and sched1 does a global schedule of the block. The target's schedule (with barrier) has the load at source position.

Options:
1. Split the block without asm: e.g., insert a conditional (`if`) that the compiler keeps but with no code? A `do{}while(0)` doesn't split. A real branch would add code.
2. Use a call? no.
3. Create a dependence: make the loaded value feed an earlier instruction? That changes the order.
4. Make the load volatile — the target has no volatile here, but the *emitted* code is the same (lw). Volatile is real C. But is it a lever? The brief's kinds are barrier,pin; "no new lever of any kind" — a volatile access used to pin scheduling order is the §37 lever used elsewhere in this project (they used `volatile u16 *pbh` for the double read). It's borderline: it's a C type qualifier, not an asm barrier. The constraint's definition of "lever" lists: "no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm". A volatile load is not in that list. Hmm, "no new lever of any kind" though.

Let me look for a real-C move. The moves catalog: "statement order", "init at decl", "temps", "loop shape", "&&/|| folds", "pointer reuse", "decl order/scope", "s16/u8 widths".

What about "statement order": move the `t = unkC4` statement earlier/later in the C so that after scheduling it lands at the right place? The scheduler hoists independent loads to the top. If we put the load at the very top of the else block, it'd be scheduled... also at the top. Hmm, sched1 might not hoist a load above a store it might alias. The load is from 196(s0); the stores to 2, 192, 188, 92(s0). Since all use the same base s0 with different offsets, gcc knows no alias.

What if we make the load's address depend on a variable computed from a previous store, e.g., use a different pointer variable for the load? E.g., `Unkstruct_800B5CB8 *p = s0; t = p->unkC4;` — same.

What if the load is from a *different* alias class: `*(volatile s32 *)&s0->unkC4`? that's volatile again.

What about making the preceding stores use a *different* pointer expression that the alias analysis can't resolve, so the load can't move above them? E.g., store via `((Unkstruct_800B5CB8 *)a0)` and load via a local pointer? Both known equal.

Hmm, what about: the load can't be hoisted above a store that *may* alias it. If one of the stores is to a pointer of unknown provenance, the load stays after it. The store to unkBC = &D_801907D4 is a constant store to 188(s0). If instead we wrote the unkBC store via a `s32 *q = (s32*)s0; q[47] = (s32)&D_801907D4;` — still known.

The target's schedule has the load after the unk5C store specifically. What creates the dependency in the target is the barrier.

Alternative: exploit a real dependence: make the loaded value be used by the 0x8000 store? No, semantics.

Alternatively, reorder the C so the load is naturally late: put `t = unkC4` *after* the unk58 store? Target has it before. But the emitted order might still be right if the scheduler moves it. Hmm.

Wait, actually look at the target more carefully: the load is at 28, before the unk58 store (88) which is at 31. And mine after removing the barrier has the load at 19, way early. What if we place the load in the C after the unk58 store? Then sched1 might hoist it to just before... it hoists independent loads as early as possible (upward). The earliest it can go is limited by aliasing with preceding stores. It hoisted to position 19, which is before `li v0,1; sh v0,2(s0)` (the unk2 store). Why is 19 the earliest? Let's see mine's full listing around 19.

Mine positions: 19 lw v1,196(s0). What's before at 18? Probably the call `jal func_8012A828` + delay. So the load was hoisted to right after the second call (the start of the else block's data instructions).

So sched1 hoists the load to the top of the basic block (after the calls). The target (with barrier) has it later.

Hmm — is the block split by the calls? Calls end blocks? No, calls don't split basic blocks in gcc (they do in some). Actually, calls are not basic-block boundaries in gcc's CFG.

So we need a block split or a dependence.

Real-C block split: an `if` with a condition that's always true? The compiler would fold it. A `switch`? folded. 

Dependence: what if we compute the address of unkC4 using a value stored earlier? E.g., the unkBC store stores &D_801907D4; then `t = unkC4` — no.

What about using `s0->unkC4` via a *union* or a different type that might alias? Aliasing analysis in gcc 2.7.2 is primitive: it uses `alias_sets_conflict_p` based on types. A load of s32 from a pointer cast to a different struct type vs stores of s16/u8 through the struct pointer — they might be considered potentially aliasing! In the target's code, the store to unk5C is `sh` (u16) and the load is `lw` (s32) — different modes. gcc 2.7.2's true_dependence: if the types differ, they may be considered conflicting unless one is char. Since both are through the same struct type, gcc knows the offsets differ (constant offsets 92 vs 196) → no dependence.

If we spell the load through a different type, e.g. `*(s32 *)((s32)s0 + 0xC4)` (a raw cast), gcc might not prove non-aliasing with the struct stores, keeping the order! That's the "de-cast / field-direct" move in reverse. The original C already uses `*(s32 *)((s32)s0 + 0x20)` for the unk20 loads. Let me try spelling the t load as `*(s32 *)((char *)s0 + 0xC4)` — hmm, char pointer alias might make it conflict with everything (char aliases all). But gcc 2.7.2's alias sets: char pointers alias everything? In old gcc, `-fstrict-aliasing` was off by default in 2.7.2! Actually gcc 2.7.2 doesn't have strict aliasing; type-based aliasing wasn't strict. The dependence analysis uses `alias_sets_conflict_p` with MEM alias sets, where a char/void cast often gives alias set 0 (conflicts with all). So `*(s32*)((s32)s0 + 0xC4)` would be alias set 0 (conflicts with all) → the load couldn't move above any store! That would keep it late. But maybe too late? It needs to be after the unk5C store and before the unk58 store. If it can't move above ANY store, it stays at its source position (after unk5C, before unk58) — exactly the target!

But the target's C likely had the plain struct field. Whatever; the emitted code is what matters.

Let me test: replace `t = ((Unkstruct_800B5CB8 *)a0)->unkC4;` with `t = *(s32 *)((s32)a0 + 0xC4);` and the store `((Unkstruct*)a0)->unkC4 = t | 0x2;` with `*(s32 *)((s32)a0 + 0xC4) = t | 0x2;`.

Also the v0/v1 swap: target has t in v0 and the address constant in v1. In mine, t in v1 and the address in v0. That's because t's pseudo gets a lower priority than the address? Hmm. With the load moved later, the allocation might change.

Let me try the cast variant.
