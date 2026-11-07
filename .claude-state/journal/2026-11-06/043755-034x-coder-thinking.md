---
ts: 2026-11-06T11:37:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dvlOdyy0XOi2YzzKCxQ2
---
Only 5 minutes elapsed! Great, I have time. Let me be more thorough.

So item 1 is likely WALL but let me try more variants. Actually, wait: let me reconsider. Maybe the pins can be dropped if I make the group A values naturally take v0..a1 by making them live LONGER than group B. Global-alloc priority = refs/live_length. Group A (r2..r5, first group) currently has short live ranges. If they were live longer (e.g., used at the very end), they'd get lower priority.

Hmm, but the target allocation has group A in v0,v1,a0,a1 (best) and group B in a2,a3,t0,t1,t2. That means group A had HIGHER priority (shorter live), which is the natural outcome when group A dies early. So allocation would naturally match if the schedule matches.

The schedule is the issue. Let me try to find a source form where sched1 doesn't hoist Blk8#1.

What if the two Blk8 copies are written as a single 16-byte struct copy? Then target would show one BLKmode copy of 16 bytes: lwl/lwr ×4 for src, swl/swr ×4. But target has TWO separate copies with different registers, interleaved with the group A2 loads. So they're separate.

What if the Blk8 copies are written as explicit field copies of a struct with s32 members, e.g.:
```
typedef struct { s32 a, b; } Blk8;
```
Then `D_80126960 = *(Blk8*)&D_80120210;` is BLKmode because Blk8 is a struct (aggregate) even if it fits in a register? In gcc 2.7.2, an 8-byte struct assignment may use BLKmode. Yes.

If instead I write two s32 assignments:
```
*(s32*)&D_80126960 = *(s32*)&D_80120210;   // aligned → lw/sw
```
would give lw/sw not lwl/lwr. But D_80120210 is s16, so *(s32*)&D_80120210 is an unaligned access; gcc knows the pointer type s32 has alignment 4, so it assumes aligned → lw. Hmm, but the target uses lwl/lwr meaning the compiler knew the address was only 2-byte aligned. That happens if the type is a struct with alignment 1? Or if the source is `s16` array? 

Actually lwl/lwr for a 4-byte load from address with known alignment < 4. If we write `*(s32*)((char*)&D_80120210 + 0)`, gcc might still assume 4.

If the original wrote `D_80126960 = *(Blk8*)&D_80120210` where Blk8 is a struct of 2 s32, the alignment of Blk8 is 4 (from s32), so the pointer cast to Blk8* assumes 4-byte alignment... but the target uses lwl/lwr, meaning unaligned. So Blk8 must have alignment 1 (packed) or the compiler used BLKmode which copies byte-wise? BLKmode move of 8 bytes on MIPS generates lwl/lwr sequences regardless of alignment. Yes! BLKmode move is alignment-agnostic → lwl/lwr. Good, so struct assignment → BLKmode → lwl/lwr. Confirmed.

So the Blk8 copies are struct assignments.

OK so now: how did the original prevent hoisting? 

Let me reconsider: maybe in the original, group A temps were declared with `register`? Not allowed (and the constraint says no register vars). But `register` in the ORIGINAL would not affect codegen anyway in gcc 2.7.2 (it does sometimes, but rarely).

Hmm, what if the original had the loads in a different order: group B loads BEFORE group A loads? Then target's order (group A first) wouldn't match.

What if the Blk8 copy #1 source was read BEFORE the group A loads in source, but sched1 moved it after? No, sched1 wouldn't move a load later unless pressure.

Wait, actually maybe sched1 DOES balance register pressure: it computes `INSN_PRIORITY` and also uses `maybe_bb_...`. There's `sched.c`'s "large_insn_p" and the `sched_verbose`. 

Let me just experiment empirically with a generator: vary statement order permutations and see if any gives score 0. But the target order is fixed; any source order that yields the target schedule wins. Since sched1 hoists Blk8#1 from any position, maybe placing Blk8#1 FIRST in source and relying on sched1 to... no, it'd stay first.

Let me test a hypothesis: what if the Blk8#1 copy comes before the group A loads in source? Then target requires it after — impossible unless sched1 moves it down. It won't.

What if the group A stores come AFTER the Blk8#1 in source? Then source: loads, Blk8#1, stores. sched1 hoists Blk8#1 → still first. No.

So no source order works; the only lever is a dependency. Real C dependency options:
- Use a variable as both a scalar value and the Blk8 pointer base.

E.g., what if the destination of Blk8#1 is written via a pointer variable that is initialized to &D_80126960 and used for the earlier stores too? E.g.:
```
s32 *p = &D_80126950;
p[0] = r2; p[1] = r3; p[2] = r4; p[3] = r5;
*(Blk8*)(p+4) = *(Blk8*)&D_80120210;   // hmm, D_80126960 = p+4
```
But then the stores use a base register, changing the code (target uses lui at for each). So no.

What if the Blk8 copy's data registers are forced to be the same as r2/r3 by making it a struct copy through a variable? Can't; BLKmode needs 2 regs.

Alternative: what if the copy is written as:
```
D_80126960 = *(Blk8*)&D_80120210;
```
but placed inside a scope with a `do{}while(0)` and the earlier stores inside a different scope? No effect.

Hmm, what about declaring the Blk8 temps? No, it's a struct copy.

Let me look at this from another angle: maybe the target's order can be achieved if the group A stores are moved up and the Blk8 copy's lwl is NOT hoisted because the `at` register used by the stores conflicts. In sched1, `at` is a fixed hard register! The stores use `lui at` + `sw ...0(at)`. In RTL, `at` is a hard reg. So the sequence `lui at; sw` and the next `lui at; sw` have WAR dependencies on at. And the Blk8 copy uses `lwl` which doesn't use at. Hmm.

But in sched1, the address computation for each store is `lui at, %hi(sym); sw r, %lo(sym)(at)`? Actually RTL: `(set (mem (plus (reg) (const))) ...)` — the address is computed with `high`/`lo_sum`. The `at` appears in the final assembly but in RTL it's a pseudo until reload. So sched1 sees pseudos. No at.

OK. Given the "global-hardreg-reserve" wall tag exists and describes exactly this, I'll mark WALL. But I still need ≥30 scored tries. Let me produce 30 variants mechanically (different orders/widths) and score them. Actually, "≥ 30 scored tries on that item (fewer is not an attempt)". So I need 30 scored candidate bodies. Let me generate them.

I'll write a generator in .run/P40/T11/G29/gen.py that emits variants, then score all with sc.sh.

Variants: permutations of the statement blocks. Let me define blocks:
A = load group A (4 s32)
S = store group A (4 sw)
B = load group B (5)
C1 = Blk8#1
A2 = load group A2 (4 u16)
C2 = Blk8#2
SB = store group B
S2 = store group A2

Target order: A B S C1 A2 C2 SB S2.

All permutations won't preserve semantics? Actually yes, all are independent (different globals), so any order is semantically valid. And we can permute. But sched1 reorders anyway. Still, let me try a bunch of source orders — the uid tie-breaks may matter.

Also variants in widths/decls.

Let me generate ~30 source-order permutations (keeping A before S etc. since S depends on A? Actually S uses A's values; if S before A it's wrong. Keep A before S, A2 before S2).

Blocks with deps: A→S, A2→S2, others free.
Target order: A, B, S, C1, A2, C2, SB, S2.

I'll generate permutations of the 8 blocks respecting deps, and take 30.

But sched1 hoists C1 regardless. Let me just test a handful first to see if any order changes the result, then decide.

Actually, a smarter experiment: does the score depend on source order at all? Let me test 5 orders quickly with sc.sh.

Let me write a generator producing 30 files.
