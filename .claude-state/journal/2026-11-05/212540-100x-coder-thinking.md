---
ts: 2026-11-06T04:25:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rnalWSLsrdFLexitT8rM
---
`insn_cost(x, prev, insn)` — for a load, the cost might be 1 (default) unless the machine description says otherwise. The comment says with all latency 1, no scheduling. So if the p load and the sll both have cost 1, their priorities would be equal and no move. But mine moved the load above the sll — meaning the load's cost > 1 (load latency 2?) or the dependence differs.

Actually in the target, no move happened for the p load; in mine it did. Same compiler, same machine description. So the difference must be in the RTL *order*: sched1 only moves insns forward if the priority is higher. The priorities depend on the dependency chains, which are the same. Unless the birth order affects the tie-break: when priorities are equal, the scheduler picks... let me look at the ready-list ordering. If priorities are equal, it picks by `insn` order? The scheduler picks `ready` list sorted by priority and `birth`? Let me look at schedule_insn/schedule_block.

Actually, in mine, the p load was moved BEFORE the sll. If priorities are equal (1 each), sched wouldn't move anything (comment). So the p load must have priority > sll. The p load's dependent chain: lw p → addiu (depends on v, not p!) wait, addiu is v+0x600, doesn't depend on p. The store sh depends on both p and v. So the p load's chain: lw p → sh (via address) = priority 2 (cost of lw maybe 1, sh...). The sll's chain: sll → addu → sll → sh = 4. So the sll should have higher priority. Yet the p load was scheduled first.

Unless the p load is SCHED_GROUPed with the preceding store? Or the RTL order has the p load BEFORE the sll (i.e., the source/expand order is store, p load, multiply)? In x1 the source was multiply, add, p — but the emitted order has p before sll, which means sched moved it OR the compiler reordered earlier (e.g., cse/combine). Hmm, combine might reorder? No.

Wait, maybe I misread which load is which. In x1's disassembly: 4924 lw v1,32(s1) [the 0x1A store's model load]; 492c sh v0,26(v1); 4930 lw v1,28(s2) [obj->1C]; 4934 lw a0,32(s1) [p reload]; 4938 sll v0,v1,1; ... So the p reload is at 4934, after the obj->1C load (4930) but before the sll. If the RTL order were chain (sll...) then add then p, the sched output would start with the sll. It didn't. So sched moved the p load up, OR the RTL order is different.

Hmm, could it be that the p reload is *emitted* early because the C `p = ...` statement is hoisted by the compiler's expand? No, expand preserves order.

Actually wait — maybe cse/combine moved the p load earlier. Or the p load is the one at 4934 and the RTL order after cse is: obj->1C load, p load, chain... Because cse processes and might reorder? No, cse doesn't reorder.

Let me look at the pre-sched RTL (combine dump / sched1 dump) for the candidate. There are tools: tools/cc1_dumps_tu.sh and hdump.sh. Let me use the sched dump. Actually `tools/cc1_dumps_tu.sh` gives TU dumps. Let me check its usage.

Alternatively, maybe the answer is simpler: the target's `<0x11` arm's p load is at 4944 because in the ORIGINAL C, the multiply was computed BEFORE the store? No, target order shows store first.

Hmm, let me look at the target's *source-level* order implied by the RTL: store(0x1A raw), multiply, p load, add, store(0x18). Our source: store, multiply, p, add, store. Same. So the only difference is sched1's decision. Since the compiler is deterministic, the RTL must differ somewhere. The RTL differs in... the register allocation happens after sched1, so RTL before sched1 is the same. Unless the *pseudo numbering* differs (due to the rest of the function) and sched1's tie-break uses pseudo numbers/insn uids.

The rest of the function differs from the original: our C differs in other arms (the fences were replaced by do-while in w4). So the pseudo numbering/birth order could differ, affecting sched1.

Maybe the original C had NO do-while and a different structure. Our w4 added a do-while in the `==0` arm, which changed the schedule globally (improving 22→14). That suggests sched1 is sensitive to global pseudo numbering.

Let me try a different way to fix the `==0` arm (which the do-while fixed): the `==0` arm needed the p load after the sh. What did w4's do-while do? It kept the p load after the sh. Maybe a dead-reset or a different structure could do it without do-while, and the pseudo numbering would differ, possibly fixing the `<0x11` arm too.

The `==0` arm: `store via raw; p = model; v = 0x1200;`. Target: lw model; li 1536; sh; lw model; j; li 4608. The p load after the sh. Without the do-while (nopin), mine had the p load... let me check nopin's `==0` arm: 48e8 lw v1,32(s1); li v0,1536; sh v0,26(v1); 48f4 lw a1,32(s1); j 4944; li a0,4608. That looks CORRECT (p load after sh). So why did the do-while improve the score from 22 to 14? Because it changed the register allocation (p from a1 to a0?) and the jump offsets. Hmm, actually the improvement 22→14 was mostly the `<0x11` arm's p reload position? Let me compare nopin vs w4 diffs. nopin had mine[87:88] lw a1,32(s1) vs target nop, and mine[90:93] sll a0...; the p reload hoisted. w4 had the same hoist but p=a0. The score difference 22→14 likely from the `n<8` arm registers (a0/a1→v0/v1?).

This is getting long. Let me take a step back and consider the budget: item 4 started at 21:22, now likely ~22:10 (48 min). That's past the 30-min budget. The rule: "Budget 20-30 min wall per item; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I've spent ~48 min and maybe ~20 scored tries. To record a WALL I need ≥30 scored tries. I could either continue to 30 tries (batch cheap variants) or... The instruction says past 30 min stop and record a wall, but a WALL needs ≥30 tries. So I should push to 30 tries quickly with a batch of cheap variants, then record WALL with best 14 (or keep trying a few).

But wait — maybe I can still crack it. Let me think about the p reload once more.

The p reload's position depends on sched1. Let me try making the p load a **2nd SET of the same pseudo as the first model load** but with the store in between (pointer reuse u1 did that and got 32). Hmm.

Alternative: use a **different variable for p per arm** (block scope) so the pseudos are separate and the schedule differs. Let me try declaring `s32 p;` inside each arm (block-scope p). Actually p is used in the shared tail, so it must be function-scope for the shared store. Unless the shared store uses a different mechanism.

What if the shared store `((Unk*)p)->unk18 = v;` is at the end, and each arm sets p. The p pseudo is one. The `<0x11` arm's p load is the one hoisted.

What if we make the shared store load p itself: `((Unk*)((Unk*)a0)->unk20)->unk18 = v;` — then no p variable for the shared store; each arm's p is only for its own 0x1A store. Then the `<0x11` arm's shared store reloads model at the store, which is after the addiu (since the store's value v is ready). Let me try: replace the merge block line 71 `((Unkstruct_800B5CB8 *)p)->unk18 = v;` with a raw expression. Then p is only used for the 0x1A stores in the `n<8`, `n<0x16`, `==0`, `<0x11` arms. The merge block would load model again.

Target's merge block: 494c sh v0,24(v1) where v1 was loaded at 4944 (in the `<0x11` arm) or earlier in other arms. For the `n<8` arm, the merge is `sh v0,26(v1)` at 48bc (its own store) then jumps to 494c with v1 = p. So the merge block's `sh v0,24(v1)` uses the p loaded in each arm. So the merge block doesn't reload; each arm sets p. So the raw-expression idea would add a load in the merge block for the n<8/n<0x16 arms (they'd need their own store + the merge). Actually the merge block's store is `((Unk*)p)->unk18 = v` where p is set by each arm. If I make it raw, the merge block would load model → an extra load in those arms (target has one load per arm, used for both stores? No: in the n<8 arm, target has lw v1,32(s1) once, used for the 0x1A store and the 0x18 store at the merge. So the merge uses the same p). So raw would break it.

OK, let me try the reverse: in the `<0x11` arm, DON'T reload p explicitly; instead let the merge block's p be the same p from the 0x1A store? But cse kills it because of the sh. The target reloads. So the reload is needed.

Time to consider: maybe the original C for the `<0x11` arm had the multiply using `n` (reusing the n variable) and p loaded... Let me look at the target's register: obj->1C in v1, p in v1 (disjoint). n is v1 in the n<8 arm. So v1 is a hot register for these values. In mine, p is a0 because the p reload overlaps v1's use. If I could make the p reload NOT overlap, it'd get v1 and everything might match.

The overlap: mine's p reload at 4934 (before the sll at 4938 that uses v1). If I move the p reload after the sll, no overlap.

What if I make the multiply chain NOT use v1? E.g., load obj->1C into a different variable/register. The obj->1C load is `*(s32*)(obj + 0x1C)` used in the multiply. If I load it into `n` (or a temp), the register could be v0/a0. Target has it in v1.

Hmm, target: 4930 lw v1,28(s2); 4938 sll v0,v1,1; 493c addu v0,v0,v1; 4940 sll v0,v0,5; 4944 lw v1,32(s1). So v1 = obj->1C, then reused for p after obj->1C dies. This is a *register reuse* pattern: the same register v1 is used for two non-overlapping values. Mine: v1 = obj->1C; a0 = p (overlapping). To get the reuse, p's load must be after obj->1C's last use. sched1 decides.

The scheduler's "birth" of the p load: if the p load is born AFTER the multiply insns in the RTL, and sched1 doesn't move it up, we get the reuse. Mine's p load is born after (source), but sched moves it up.

Why would sched move it up? To hide load latency. The target doesn't. Maybe in the target, the p load's cost is lower or the scheduler's priority for it is 1 (equal), so no move. The difference could be that in the target's RTL, the p load's use (the store) is in the NEXT basic block (after the label 494c), so the load's dependence chain within the block is just the load itself (priority 1) → no move! Whereas in mine, the store is in the same block (no label?) — wait, the shared tail is a label in both.

Hmm, in the target, the merge block at 494c is a branch target (from 48b8, 48d0, 48f8, 491c). So the store at 494c is in a different basic block. The p load at 4944 is in the arm's block. sched1 schedules each block separately; the p load's only dependent within its block is... none (the store is in the next block). So its priority is 1 → no move → it stays at birth (after the chain). That's why the target keeps it there!

In mine, why did sched move it? If the p load's only dependent is in the next block, its priority is 1 and it shouldn't move. Unless in mine, the p load is NOT before the label but the compiler merged blocks differently? The label 494c is a branch target in mine too (jumps from 48b8 etc.). Hmm.

Wait, maybe in mine the p load is moved not by sched1 but by **combine** or **cse**? Or by `reorg`? No, the order 4934 is before the sll; that's within the block.

Hmm, maybe the difference: in mine, the p load and the sll are in the same block, and the p load's priority is 1 (no dependent in-block), while the sll's priority is 1 too (its chain's final consumer, the addiu, is in-block; the sh is in the next block). If all priorities are 1, "no scheduling is done" → the order stays as RTL (chain then p). But mine has p before the chain, so the RTL order must have p before the chain!

That means in mine's RTL (pre-sched), the p load comes BEFORE the sll. How? The source order is multiply (sll/addu/sll), then add, then p (x1). Unless combine reordered the multiply after the p load. Hmm.

OR: the p load in the disassembly is actually the *first* model load (for the 0x1A store) and the second is elsewhere? Let me carefully re-examine mine's `<0x11` arm in x1:
```
4924 lw v1,32(s1)   # ? 
4928 nop
492c sh v0,26(v1)   # 0x1A store (v0=3072 from branch delay li v0,3072)
4930 lw v1,28(s2)   # obj->1C
4934 lw a0,32(s1)   # p reload
4938 sll v0,v1,1
493c addu v0,v0,v1
4940 sll v0,v0,5
4944 addiu v0,v0,1536
4948 sh v0,24(a0)   # merge store
```
So the p reload is at 4934, after obj->1C (4930). If the RTL order is: lw model (4924), sh (492c), lw obj->1C (4930), sll, addu, sll, lw p, addiu, sh — then sched moved the lw p from position 7 to position 4 (right after lw obj->1C). 

So sched did move it. Its priority must be > the sll's. Hmm.

Unless combine merged the addiu into the sh? No.

Let me get the sched1 dump to see the pre-sched order and priorities. tools/cc1_dumps_tu.sh may provide dumps. Let me check its usage.
