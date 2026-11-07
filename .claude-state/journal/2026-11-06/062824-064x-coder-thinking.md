---
ts: 2026-11-06T13:28:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qIqe71QcHOVonwOpRG05
---
Now I see the scheduled order (this is block 17's scheduled listing):
...
insn 302: s0 = s0 + t
insn 310: a1 = $fp + 16        ← the addiu a1,sp,16 (fp here = 30, but final uses sp? The frame is fixed; $fp maybe the frame pointer = sp in this function since no alloca)
insn 305: d[2] = s0 (store)
insn 312: call func_80015978
insn 315: ...

So insn 310 was scheduled between 302 and 305 — i.e., late (just before the call). And note insn 310 depends on 281 (insn_list:REG_DEP_ANTI 281).

In the target, the addiu is much earlier. The priority of insn 310 is 1.

Now the key: what if the call's argument setup had a *longer dependency chain*? Or what if we make the s0 chain's insns depend on the a1 setup? 

Alternatively — what if we make the store `d[2] = s0` come BEFORE the a1 setup in source? Currently source order: d[2] = s0; func_80015978(...). The scheduler placed 310 after 302 and before 305.

Target order: 310 (addiu a1) early, then the s0 chain, then 305 (store) in the jal delay slot.

Hmm. In the target, the store 305 is in the delay slot of the jal. In mine, the store is at 305 and the addiu at 310, then jal at 312 — so the delay slot is empty? The final code showed `jal; sh s0,28(sp)` — wait, in mine the store is after the jal too (0x3808 sh). Hmm, the RTL listing order (305 then 312) is the pre-dbr order; dbr moves 305 into the delay slot.

So in mine, RTL order: ..., 302 (addu s0), 310 (addiu a1), 305 (store), 312 (call). Final: addu; addiu a1; jal; sh (delay). 
Target RTL order: 310 much earlier, ..., 302, 305, 312.

So we need insn 310 to be scheduled earlier. Its priority is 1 (lowest). What determines it? It has no successors except the call (which is high priority). Actually all the chain insns also have priority 1-4. Hmm, the priority numbers: 310 has priority 1; 305 (the store) priority 1; 302 priority 2? Looking at the ready lists: insn 310: priority 1, ref_count 1; 302: priority 1? The initial list shows insn 310: priority 1 ref 1, 305: priority 1 ref 1, 302: priority 2? I see "insn[ 302]: priority = 2"? Let me look: the list shows insn 305: priority 1; 302: priority 2? From the listing: "insn[ 305]: priority = 1, ref_count = 1", "insn[ 302]: priority = 2, ref_count = 2"? I don't have it exactly. Anyway.

In the target, the barrier forced 310 before the barrier. Without a barrier, sched1 puts it late.

So we need a real-C ordering constraint. Options:
(a) A dependence from 310 to an insn that is scheduled early (before the s0 chain). For example, if a1's value were used by an early insn. 

What if we write the call as `func_80015978(aa, (s32 *)nn);` — already uses nn at the call only.

What if we pass `(s32 *)buf` in the call and keep nn for something else? Hmm.

(b) A dependence from an early insn to 310: e.g., make the a1 address depend on a value computed early. The address is `$fp+16` — no.

(c) Change what's in the chain: if `d[2] = s0` used nn? No.

(d) Increase ref_count of the a1 pseudo: ref_count 1. sched1's priority might incorporate ref_count? The ready list shows "(1)" for priority. Hmm.

(e) Make the a1 setup a *copy* from another register that is born early: e.g., `s32 np = (s32)buf; nn = np;` — tested, extra insn (not coalesced). But maybe if np is used MORE than once, local-alloc ties? Hmm.

Wait — actually maybe we can make the *frame address* be materialized earlier by making `buf` be referenced earlier in the source. E.g., if `buf` were initialized at declaration: `u16 buf[4] = {...}` or `u16 buf[4];` and then `buf[0] = ...` earlier? The address computation could be hoisted/CSE'd to the earliest use. Hmm, the target has the addiu right after the rand calls, which is its first use.

Hmm, what if we reference `buf` in the code BEFORE the rand calls? E.g., move `d[0]`, `d[1]` stores... no, those are d[].

Wait — maybe the answer is much simpler: reorder the source so the `aa`/`nn` assignments come BEFORE the `s0 = rand(); t = rand();` lines. Then in sched1, the addiu would be born before the rand calls... but the target has it after the second rand's move. Hmm, no: the target has addiu a0, addiu a1 at 37e8/37ec, AFTER `move s0,v0` (the rand result). But the *source* order of aa/nn is already after the rand calls. So source order matches target. The scheduler moved it.

Unless... the target's order comes from a different source order: maybe in the original, `nn` was assigned after `d[2] = s0;`? No, then it'd be later.

Hmm hold on. Let me reconsider: maybe the barrier's role here isn't scheduling at all; maybe it's *cse*: the barrier prevents cse from replacing the `(s32)buf` address computation... no, the addiu is the address.

Let me look at the barrier's effect in the RTL: with the asm, sched1 sees the asm as a barrier with dependencies on all regs; the addiu (set $5) is before it, and the s0 chain after. So the order is forced.

Real-C equivalent: a *call* also clobbers all caller-saved registers and memory! A function call is a scheduling barrier too (sched1 doesn't move insns across calls? It does move some). But a call emits code.

What about a memory store? A store to memory creates a dependence with other memory ops. The addiu is not a memory op.

What about a `(use ...)`? Not from C.

OK here's an idea: what if we make the addiu a1's *result* used earlier, before the s0 chain, in a way that produces no code. E.g., `nn` is used as an argument to a function that is *not* called... no.

What about making the s0 chain depend on `nn` through the memory alias: `d[2] = s0;` where d and buf alias? No.

Alternatively: what if we make the *store* `d[2] = s0` happen before the addiu in the RTL (source order), so the scheduler keeps the addiu after the store? That's what happens (310 before 305). Not helpful.

Hmm, let me look at the target's sched: in the target, what forced the addiu early? The barrier. The original source had the barrier. So the ONLY way the original achieved this is the barrier. But our task is to find a lever-free body with score 0 — which means we need a different mechanism. This may be a WALL (sched1-birth-order or similar) unless a clever C construct exists.

Wait, maybe not: the pins aa/nn could be replaced by real C that changes the allocation/scheduling. Since the item kind is "barrier" only, the pins may stay, but we're free to remove them if it helps. v21 (nn unpinned) gave 27 — worse. But maybe unpinning nn AND using a different source shape could work.

Hmm, what if the whole tail group (the pinned aa/nn) is restructured: since aa is pinned $4 and nn $5, the target's `addiu a0,s3,4` / `addiu a1,sp,16` are just the initializations. What if we assign them earlier via declaration init? `s32 nn = (s32)buf;` at declaration? That would place the addiu at the top of the function (before the rand calls) — not the target position.

Alternatively, the addiu could be scheduled early if the *first* rand call's result is used... no.

Let me look at the target's sched dump to see what the barrier does and confirm. I'd need a dump of the orig (with asm). Let me do that — it will show the block structure with the asm. Then I can see whether the asm splits the block (creating two blocks: before and after the asm). If the asm splits the basic block, then the addiu is at the end of the first block — and a real-C construct that splits the block would work.

Let me dump the orig (with barrier) and compare block structure.
