---
ts: 2026-11-06T10:55:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rwWxfQVrFmrUDuXBGFkV
---
Interesting! Now the unk58 store is in the right place, but the `sb zero,193(s0)` (unkC1 = 0) moved to position 37 instead of 34. So a different store sinks now.

The diff: mine has sb at 37, target at 34. So `unkC1 = 0` got delayed. That's the next store after the RMW.

Hmm. Because the RMW is in its own block, and the following stores are in the next block; sched1 sank the sb.

Ugh. Let me see the full listing. Actually, the pattern: within a block, sched1 sinks a zero-store. The block after the RMW contains: unkC1=0, unkB4=0, then the unk20 loads/stores...

The target order: ori, sw196, lw v0,32, li v1, sb zero,193, sw zero,180, sh v1,24(v0)...

Mine: ori, sw196, lw v0,32, ?, ..., sb at 37.

Let me dump to see.

Actually, maybe wrap unkC1=0 and unkB4=0 too... this is whack-a-mole.

Let me step back and think about the *actual* target block structure with the barrier: the barrier is BEFORE the load. So the block after the barrier contains: load, store88, RMW, unkC1=0, unkB4=0, the unk20 loads/stores, etc. — all in one block. And sched1 produced the source order almost exactly.

So the ONLY block split needed is right before the load. And within that block, sched1 keeps the source order (mostly).

My v_dw6 splits into 3 blocks and disturbs the later scheduling.

So the ideal is a single split before the load. v_dw5 (do-while around unk5C) did that but the schedule was off (lw, nop, ori, sw, lw32, lui, addiu, sw88) — the constant materialization was late.

Hmm, but why? With the barrier (v_bar2), the block is the same and the schedule is right. So the barrier does something else besides splitting: it affects reload's placement of the constant? Or sched2?

Difference between v_dw5 and v_bar2: in v_bar2 the asm insn is present in the RTL during reload; reload must place the constant materialization... The asm forces all memory ops to depend on it; the constant materialization (lui/addiu) has no memory dependence.

Hmm, wait: v_bar2's registers were swapped (t v1, a v0) — because the pin is gone. And its order was right. So the barrier gives the right order; the do-while gives a different order.

What if I combine: do-while for the block split AND make the schedule right by adding the constant as a variable (so reload isn't involved)? v_addr had the right order but swapped regs; v_addr3 had the right regs but wrong order.

Let me try: do-while around unk5C (split before the load) + `a` variable defined before the load? No...

Hmm, hold on: what if I put the do-while around unk5C AND define `a = (s32)&D_801907C4;` INSIDE the same do-while (after unk5C)? Then the address is computed in block A (before the split), and the load+store+RMW in block B. The schedule would be: ..., sh unk5C, lui, addiu (block A), then lw, sw, ori, sw (block B). The target has lw FIRST, then lui/addiu. Wrong.

What if the do-while wraps [unk5C] and the address is a variable assigned in block B after the load? That's v_addr (order right, regs swapped).

Argh.

Let me try yet another angle on the reg swap in v_addr: the issue is that a (born later) wins v0. What if I make the load's pseudo born EARLIER than the address in the qty sense but keep the source order load-first? They ARE in source order load-first in v_addr: t born at the load (earlier), a born at the address (later). And a wins v0 because its live range is shorter.

Priority = refs*size/(death-birth). t: birth=load, death=ori (in block2, but for local-alloc in block1, death = block end if live out). Both live out of block1? t is used in block2 (ori), a is used in block2 (store). Both live at the end of block1 → death = block end. So both have the same death! Then priority differs only by birth: a born later → smaller (death-birth) → higher priority → v0. Yes.

So to make t win, t must be born later than a — but then the source order is a first, and sched1 keeps that order (v_addr3).

Unless sched1 reorders the load before the address. Why would it? sched1's ready list: at the block start, both the lui and the lw are ready. Priorities: the lw = 1 + priority(ori); the lui = 1 + priority(addiu) = 1 + (1 + priority(sw)) = 1+1+1 = 3? The lw = 1 + priority(ori) = 1 + (1 + priority(sw196)) = 3. Tie. Then sched1 picks by list order (the first in the ready list). The ready list is built in source order, so the lui first.

Hmm, unless the load's priority is higher. What if the ori is in the same block and depends on the load? priority(lw) = 1 + max(dependents) = 1 + priority(ori) = 1 + (1 + priority(sw196)) = 3. The lui: 1 + priority(addiu) = 1 + (1 + priority(sw88)) = 3. Tie.

To break the tie, make the address chain shorter: if `a` is computed with a single insn (lui) instead of two? The address D_801907C4 needs lui+addiu.

Or make the load's chain longer: the ori → sw196 → ... hmm.

What if the store sw88 is NOT in the same block (e.g., after the split)? Then the lui's priority = 1 + priority(addiu) = 2, and the lw's = 3 → the load wins! And a's qty: if the store is in a later block, a is global.

Hmm, this is the v_addr5 structure (a+store in block2, RMW in block3) which gave regs swapped (t global got v1).

OK. Time's up for item 1 (28 min). Let me record a WALL with best=2, tag sched-store-sink (or the closest), and move on. But wait — before I do, let me reconsider whether the second item (func_80189F7C) is identical. If so, its wall is the same; but I should still try briefly.

Actually, hold on. Let me reconsider the problem completely differently. What if the natural C body doesn't use a `t` temp at all but uses `|=` with the barrier's role taken by the *volatile*... no.

Or what if the original function's target could be matched by a *different statement order*: what if the target's `lw v0,196` at position 28 is actually `unkC4 |= 0x2` written directly, and the sw88 before it is naturally ordered because... 

Let me test: `unkC4 |= 0x2;` placed BEFORE `unk58 = ...` in source:
```
unk5C = 0x8000;
unkC4 |= 0x2;
unk58 = &D_801907C4;
```
Then RTL: lw, ori, sw196, lui, addiu, sw88. sched1 might reorder the sw88 before the ori/sw196? Probably not.

What about:
```
unk5C = 0x8000;
unk58 = &D_801907C4;
unkC4 |= 0x2;
```
RTL: lui, addiu, sw88, lw, ori, sw196. sched1 might hoist the load above the store (independent) → lw, lui, addiu, sw88, ori, sw196 = TARGET! And the registers: with `|=` there's no t variable; the load's result is an implicit pseudo used by the ori. Hmm, and the constant is a constant pseudo.

p_S3S4... wait, in my permutation set, "p_S3S4S2" and "p_S3_S4_S2" scored 14. Those had `t = unkC4` (a temp) not `|=`. Let me test the `|=` version with the store before it.

Actually p_or = S1, S3, |= → score 11. Hmm, p_or is: unk5C; unk58; unkC4 |= 2. That's exactly what I described, and it scored 11. Let me see its diff — maybe the load hoisted too far (to 19).

Right, the load hoists to the top of the EBB (position 19), above the unk2/unkC0/unkBC stores. That's the problem: the load can move above ALL the stores.

So we need the load to stop after the unk5C store (or after the unkBC store). The EBB starts at the else block start (after the calls). The load hoists to the top.

To stop it, the load must have a dependence on the unk5C store. Both are base+const with the same base → independent.

Unless the load's address is NOT base+const. What if we compute the unkC4 address via the *pointer stored at unk20*? No.

What if we use a pointer variable p = a0 + 0xC4 but prevent cse from folding it: p is used for both the load and the store (the RMW), and... cse would still equate.

Hmm, what if p is assigned from `(s32)a0 + 0xC4` where a0 is cast to `s32` — that's what `*(s32*)((s32)a0+0xC4)` does (folded).

What if p is a `u8 *` computed as `(u8 *)a0 + 0xC4`? Same fold.

What if the load is from a *different* object: e.g., declare `extern s32 D_800B5CB8_C4;` aliasing the field? No.

OK, I'm confident this is a wall for now. Let me record item 1 as WALL with best 2 and tag sched-store-sink. Evidence: sched1 sinks/hoists the unkC4 load or the unk58 store across the block; the barrier's split + pin's hard-reg reserve both needed.

Hmm, but actually, wait. Let me reconsider the wall tag: the diff in the best candidate (d_S2S3S4 / v_dw6) is a store moving. The tag `sched-store-sink` exists: "sched scheduler sinks a store past the target slot (G28)". That fits.

But hold on — before declaring a wall, let me check the time budget: a WALL needs ≥20 min and ≥30 scored tries. I have both.

Actually, let me do one final experiment that might crack it: the `|=` version with the load hoisted — what if I add a *second* statement before it that makes the load's hoisting stop: e.g., the unk5C store through a `volatile u16 *`? Volatile is a barrier-class lever — not allowed.

OK, record the wall.

Actually hold on, one more: what if the C declares the unkC4 access via a *struct pointer field* with a non-constant index? Like `((s32 *)a0)[49]` — the index 49 is constant. `((s32 *)((s32)a0 + 0x20))[...]` no.

Let me try `t = ((Unkstruct*)a0)->unkC4;` but with the struct accessed through a *different type* whose field is at 0xC4 — e.g., a local struct type with a member at 0xC4 and a different alias set? Different struct types have different alias sets in gcc? In 2.7.2, alias sets are per-type, but MEM_IN_STRUCT and rtx_addr_varies matter. The address is still base+const → no dependence.

Fine. WALL. Let me record and move on. Actually, since items 1 and 2 are twins, let me quickly check if item 2's orig is byte-identical to item 1's orig (modulo symbol names). If so, the same wall applies, but I should still run the same best candidate on it to confirm the same score.

Let me first write the results row for item 1 and the moves.md line, then handle item 2.

Wait — the results.tsv row format: `dir file func kinds result best tries wall evidence`. dir = the item dir name (e.g., func_8018966C__ov_SC03_028_jr_801887A8). result = WALL, best = 2, tries = number of scored tries, wall = sched-store-sink, evidence = gcc pass + mechanism ≤140 chars.

Let me count tries: I'll estimate 60+ (the 36 generated + ~20 manual). Let me count precisely-ish: manual candidates: orig, nopin, nobar, win0, v_param, v_cast, v_dw, v_dw2, v_dw4, v_or, v_ptr, v_ref3, v_ref4, v_bar, v_bar2, v_addr, v_addr3, v_addr4, v_addr5, v_dw5, v_dw6 = 21. Generated: p_all, p_or, 6 p_, 12 d_, 12 e_ = 32. Total ~53. Plus sc.sh scored all of them. So tries=53.

Hmm, but wait. Before I settle for a wall on BOTH small items and possibly both big items (4 walls), let me reconsider. The task is a "singleton crack shard" — presumably many items are crackable. Maybe I'm missing something obvious.

Let me re-read the target's prologue and compare with my best candidate to make sure the prologue matches. In v_dw6 the only diff was the sb position. So we're close.

Hmm, what if I just try wrapping more statements in do-whiles to control the block structure progressively? The v_dw6 diff was the sb (unkC1=0) moving from 34 to 37. Let me look at the full v_dw6 listing to see where things are.

Actually, let me try v_dw6 with the sb/sw zero pair wrapped too. Whack-a-mole but cheap. Let me see the diff first.
