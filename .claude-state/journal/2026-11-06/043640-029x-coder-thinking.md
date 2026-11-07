---
ts: 2026-11-06T11:36:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oZnn47c8ZOPhepkBLrem
---
Worse. Direct assignments produce 86 insns.

Let me reconsider. The original likely used the temp variables (since 78 insns). The pins forced the allocation.

Key question: how to get sched1 to keep loads at top. In target the order after sched1:
1. load group A (4 lw)
2. load group B (5 loads)
3. store group A (4 sw)
4. Blk8 copy #1
5. load group A2 (4 lhu)
6. Blk8 copy #2
7. store group B (5 stores)
8. store group A2 (4 sh)

Note: group A loads and group B loads are hoisted to the very top, before the stores. That's a big hoist: group B is loaded from 228,22A,294,298,29A which are far from group A's 200..0C.

In mine (w1), sched1 moved things differently.

Hmm, what if the original source order was: load ALL temps first, then do the stores in the order shown? That's exactly what the orig.c body does (all loads in one line, then stores). And mine (w1) is exactly that. Yet sched1 reordered.

Wait, w1 IS the same source order as orig. The only difference is the pins and barrier. So sched1 in the original ordering... hmm, the target was produced by the ORIGINAL source which is unknown. The current orig.c (with pins) reproduces target because the pins force registers and the barrier prevents motion.

Without the barrier, sched1 hoists the Blk8 copy to the top because it's independent. Why did the original compiler not do that? Because in the original, maybe the Blk8 copies are not independent — e.g., if the original didn't use struct assignment but individual word copies that depend on the loaded temps? No.

Alternatively, maybe the original source had the Blk8 copies written as explicit `s32` copies using the same temp variables, creating dependencies that prevent hoisting.

Let's look: Blk8#1 uses a1(src ptr),a0(dst ptr),v0,v1(data). Blk8#2 uses t6,t5(ptr),t3,t4(data).

If the original wrote:
```
r2 = *(s32*)&D_80120210; r3 = *(s32*)&D_80120214;   // data
D_80126960 = ... 
```
Hmm, but the target uses lwl/lwr (unaligned 8-byte copy) which is what a struct assignment generates, or what `*(s32*)` on a misaligned address... Actually lwl/lwr is generated for a 4-byte load of an unaligned pointer, but here it's used for 8-byte copy: lwl v0,3(a1); lwr v0,0(a1); lwl v1,7(a1); lwr v1,4(a1). That's two 4-byte unaligned loads, then two unaligned stores. This is exactly a struct/array copy of 8 bytes (BLKmode). So it's `D_80126960 = *(Blk8*)&D_80120210;`.

OK. So the question remains: how to prevent sched1 from hoisting Blk8#1 above the group A loads.

In the target, the group A loads are at the very top, above Blk8#1. In w1, Blk8#1 is at the very top, above group A loads. So it's a scheduling order issue.

sched1 works on the dependency graph. Both orders are valid. The choice depends on priorities: sched1 schedules by "priority" = length of longest path to the end. Loads from memory have a dependency on... hmm.

Actually maybe the difference is that in the target, the Blk8 copy is at a position where its data registers v0,v1 conflict with group A's v0,v1 — meaning the scheduler had to place group A first because... no, before allocation there are no register conflicts.

Wait, maybe the original had the group A stores before the Blk8 copy in source, and sched1 keeps the store's dependency. But sched1 wouldn't move the load of group A up if the stores are in between.

Hmm, let me reconsider: maybe the original source order is:
```
D_80126950 = D_80120200; ... (direct assignments)
```
which w2 tried (86 insns). Not it.

Let me try: temps loaded, but group A loaded and stored immediately, then Blk8, then group B. i.e., source order = target's order:
```
r2=D_80120200; r3=...04; r4=...08; r5=...0C;
r6=*(u16*)&...28; r7=...2A; r8=D_80120294; r9=...98; r10=...9A;
D_80126950=r2; ...
D_80126960 = *(Blk8*)&D_80120210;
r2=*(u16*)&...20; r3=...22; r4=...24; r5=...26;
D_80126968 = *(Blk8*)&D_80120218;
D_80126978=r6; ...
D_80126970=r2; ...
```
That's exactly w1 (same as orig minus barrier/pins). So no.

Hmm wait, w1 is exactly the source order of target. And sched1 changed it. So the original must have had something to constrain sched1.

Unless the original had a barrier-like effect from... a function call? Or the original code was compiled with -O2 vs -O1? No, same flags.

Could the original have used `volatile`? If the variables were volatile, loads/stores couldn't be reordered. But volatile would generate different code? Actually volatile on the globals would force each access to be exactly in order. Hmm, but then the loads would still be at the top in source order... and no reordering. Let's check: with volatile pointers, each load/store must happen in program order. The target order (all loads then stores) — but source order has loads r2..r5, loads r6..r10, stores... yes that matches source order! So volatile would produce exactly the target order.

But are the globals volatile in the original? They're defined elsewhere. Hmm. Adding `volatile` to the extern declarations would be a source change outside the body (the extern decls are inside the body though! they're local extern declarations). The body has `extern s16 D_80120218;` etc. inside the function. I could add `volatile` there. But is that a "lever"? The kinds are barrier,pin. Adding volatile is arguably a new lever of a different kind (a barrier-like). The brief says "no new lever of any kind". Volatile is definitely a lever. So no.

Hmm.

Let me reconsider whether the original really has all loads before stores. Let me recount target lines: lines 1-18 = 9 loads (4 lw + 2 lhu + 1 lw + 2 lhu) = group A + group B. Then lines 19-26 = 4 stores. Then Blk8#1. Then group A2 loads. Then Blk8#2. Then stores.

So yes, group A and group B loads both at top. That's a sched1 hoist (from source order they're already adjacent at top). Fine.

The only reorder in target vs source: Blk8#1 in source is before group A2 loads; in target it's also before group A2 loads. And in source, Blk8#2 is after group A2 loads; target same. So actually target = source order! No reordering at all.

So the target has NO scheduling reorder, while mine (w1) has sched1 moving Blk8#1 to the top and interleaving.

Why would sched1 not reorder in the original? sched1 reorders only within extended basic blocks, and it uses dependencies. Moving Blk8#1 (which is a memory copy) above the stores D_80126950.. is allowed only if no aliasing. The compiler knows D_80126960 and D_80126950 are distinct symbols, so no dependency. So sched1 can move it. In target it didn't; in mine it did.

The difference: sched1's decisions depend on the RTL and the "priority" values. With pins, the RTL is different (hard regs), changing priorities. Without pins, it reorders.

Hmm. Maybe the original had MORE than 78 instructions? No, target is 78.

Alternatively, maybe the original source had the Blk8 copies written as member-by-member copies that create dependencies, e.g.:
```
((s32*)&D_80126960)[0] = ((s32*)&D_80120210)[0];
```
That would produce lw/sw (aligned) not lwl/lwr. Hmm, unless the pointer is cast to an unaligned type. Actually `*(Blk8*)&x` where Blk8 is a struct of 8 bytes gives BLKmode move → lwl/lwr. If written as two s32 loads from unaligned addresses, gcc uses lwl/lwr for each. E.g., `((s32*)(&D_80126960))[0] = ((s32*)(&D_80120210))[0];` — D_80120210 is s16 so &D_80120210 is 2-byte aligned, gcc assumes alignment 2 for the pointer? Casting s16* to s32* — gcc uses the type's alignment, so it'd assume 4-byte aligned and emit lw. Actually with -mno-unaligned? Hmm, the lwl/lwr appears for unaligned loads.

Let me try a different tack: maybe the original used a loop? No, no branches.

Let me look at the actual instruction count difference. w1 had 78 insns but score 81 (COUNT) — wait "score 81 (COUNT; mine 78 ins, target 78)" — score 81 but same insn count? The diff showed extra/missing instructions but same count. Hmm, actually the diff showed mine had lines like "lui t3; lw t3" instead of "lui at; sw v0" — same count.

So w1 is 78 insns but different schedule. Score 81 = number of differing positions.

To get score 0, I need the exact schedule. Let me try source order variants that might make sched1 keep the order.

Idea: make the Blk8 copies depend on the loaded temps. E.g., do the copy through the same variables:
```
D_80126960 = (*(Blk8 *)&D_80120210);
```
independent.

What if instead the original did:
```
r2 = ...; r3 = ...; r4 = ...; r5 = ...;
r6..r10 loads
stores r2..r5
// blk8 copy written as:
D_80126960 = *(Blk8*)&D_80120210;
```
Same.

Hmm, what about the order of declarations? Sched1 shouldn't care.

Let me look at this from the "what did the original source look like" angle. This is func_8012A1BC — a "save state" function copying globals to a buffer. The original probably had a struct assignment:
```
D_80126950 = ...
```
Hmm.

Actually, maybe the original used an array/struct:
```
*(struct S *)&D_80126950 = *(struct S *)&D_80120200;
```
where struct S is 0x14 bytes? That would be a BLKmode copy of 20 bytes → lwl/lwr sequences, not individual lw. No.

Let me try instead: what if the temps are declared as `s32` and the loads are done via a pointer chain that creates dependencies? 

Alternative: maybe the barrier and pins are genuinely necessary, making this a WALL. The task expects WALLs sometimes. But let me try a few more shapes (aim ~30 tries across items; 20 min).

Let me try: use `u16` temps for the u16 loads but stored as u16 (target stores sh). And separate variable for each. Actually w1 already uses u16 for r6,r7,r9,r10 and s32 r8. Good.

What if I reorder the source so that the Blk8#1 copy comes FIRST, then group A loads/stores? Then sched1 might leave it, but target has it after. Hmm.

What if the source has the stores immediately after each load group, forcing... no.

Let me examine sched1's behavior: it schedules the whole block. Priority is based on the longest path. Loads have high priority (they're at the head of dependency chains). The Blk8 copy's loads (lwl) are also high priority. So sched1 would tend to schedule all loads first — which is what target does (group A loads, group B loads, then... but Blk8#1's lwl comes AFTER the 4 stores in target). That contradicts "loads first".

Hmm, target: lwl v0,3(a1) comes at line 27, after 4 sw at lines 19-26. So sched1 did NOT hoist Blk8#1's loads. Interesting.

Unless the lui/addiu for a1,a0 (the Blk8 pointers) are at lines 23-26, right after the 4 sw. So the address computation is after the stores. So the whole Blk8 copy is after. That's source order.

So sched1 in the original kept source order almost exactly. In mine, it moved Blk8#1 up. Why?

One possibility: register pressure / the `at` register. In the target, the 4 stores each need a `lui at` for the address. In mine... also.

Hmm, maybe the difference is that in the original, the first group of loads was NOT hoisted above the Blk8 address computation because of the `at` register usage? No, at isn't in sched1 (it's allocated later).

Let me think about sched1's DFA/priority. Actually, maybe the difference is due to the *number of registers live*. sched1 tries to minimize register pressure; it moves instructions to reduce live ranges. In target, group A values are live from line 1 to line 19 (18 insns). Hmm.

Wait — in target, group A loads (lines 1-8) are far from their stores (lines 19-26), so live ranges are long. That's the OPPOSITE of minimizing pressure. So sched1 didn't move them down either. So sched1 did nothing.

In mine, sched1 moved Blk8#1 up (from position ~30 to position 1). That's a big move. Why would it? Because sched1 schedules blocks in order and for each block builds a dependency graph; it emits in "ready list" order by priority. The ready list initially contains all instructions with no predecessors. Both the group A loads and the Blk8 lwl are ready. Priority decides.

Hmm, unless in the original the Blk8 copy had a dependency on the stores (e.g., through `at`? no).

OK, I'm spending too long theorizing. Let me try empirical variants. The most promising: make the Blk8#1 copy depend on the earlier stores by using the same destination pointer variable? No, addresses are symbols.

Another idea: maybe the original used a **union/struct** so that the Blk8 copies are 8-byte moves of *the same object* being written piecewise, creating aliasing that sched1 must respect. E.g., if D_80126950 and D_80126960 are fields of one struct, then writes to one field don't alias another field... still no.

Alternatively, maybe the original's variables were `volatile`-ish because they're `register`? No.

Let me look at the actual target bytes and check whether the 4 stores use `at` or the lui folded. They use `lui at; sw v0,0(at)` — because the symbol is a 16-bit address? No, it's lui at,0x0 + sw v0,0(at) meaning the address is lui + offset 0. All the D_801269xx are in the same page 0x8012xxxx? No: D_80126950 is 0x80126950, D_80120200 is 0x80120200. Different pages? 0x80126950 vs 0x80120200 — both 0x8012xxxx! Same 64KB page? 0x80126950 >> 16 = 0x8012. Yes same page. So all could share one lui. But the compiler emits separate lui for each store (at). Hmm, that's because `at` is a scratch and each store gets its own address computation; cse might have merged but didn't.

Whatever.

Let me try a few concrete variants quickly:

w3: put the two Blk8 copies adjacent (both before group A2 loads)? No, target order.

w4: interleave differently.

Actually, maybe the key is that in the original, the variables were declared with `register` keyword? No, that's not allowed and doesn't affect.

Hmm, let me look at whether there's a known technique: "sched1-birth-boost", "sched1-order". The moves.md has many sched1 entries. The mechanism for controlling sched1 order: instruction birth order (uid), which comes from source order. sched1's ready-list tie-break uses uid (earlier uid first). So source order matters!

In mine, Blk8#1 is at source position after the group A stores. Its lwl uid > group A loads' uid. So it should NOT be scheduled first... unless sched1 moved it because of higher priority (longer path).

Priority in sched1 = length of longest path from insn to end (or to the end of the block). The Blk8 copy's lwl → lwr → swl → swr chain length 4, and its results feed stores. Group A's lw → sw chain length 2. So Blk8 has higher priority → scheduled first. That explains mine.

In target, the group A loads are first. So maybe in the original, the group A loads had a longer path? If the group A values were used in more than one place... Hmm.

OR: in the original, the Blk8 copy's chain was shorter/lower priority because it was scheduled as part of a different block? No branches.

Wait — maybe the original code had the group A stores depend on something that made their path longer. Hmm.

Alternatively: maybe sched1 in gcc 2.7.2 only schedules within "extended basic blocks" and stops at... no.

Let me just check: does the score improve if I reorder source so Blk8#1 is at the top? If I put Blk8#1 first in source, sched1 might keep it first, but target wants it after the 4 stores. So no.

Let me try: what if the group A loads are declared/used such that they feed the Blk8 copy? E.g.:
```
r2 = D_80120200; ...
D_80126950 = r2; ...
```
No.

New idea: maybe the original wrote the stores as `D_80126950 = r2` where r2 etc. are ALSO used later. E.g., the original might reuse the same variables for both groups (r2..r5), which is what orig does. The first group's values die at the stores. 

Hmm, what if in the original the first group values were used AGAIN later (not reloaded)? But target reloads them (lhu v0...). So no.

I think this might be a genuine WALL, but let me try a couple more quick ideas before moving on. Time check: started 04:32, now maybe 04:45.

Let me try w3: same as w1 but with the Blk8 copies written as two 4-byte copies via s32 temps that are part of the same temp set — creating dependencies that might change scheduling.

Actually, here's a thought: what if the original used ONE big set of temps for everything, i.e., the Blk8 copy data goes through r2/r3? In target, Blk8#1 data is v0,v1 — which are also the first group's registers but dead by then. So maybe the original wrote:
```
r2 = *(s32*)&D_80120210; r3 = *(s32*)&D_80120214;
*(s32*)&D_80126960 = r2; ...
```
but that would be lw/sw, not lwl/lwr. Unless the pointers are unaligned.

Hmm, actually if the original used `*(Blk8*)&D_80120210` it's a struct copy.

Let me try yet another approach: maybe the original code is:
```
D_80126960 = *(Blk8*)&D_80120210;
D_80126968 = *(Blk8*)&D_80120218;
```
placed BEFORE all the scalar copies, with the scalar temps loaded first. But target shows Blk8#1 after the 4 sw.

OK let me test a variant where the first group stores are moved up in source to just after the group A loads (before group B loads). Then sched1 might hoist group B loads up anyway... Let's see: source:
```
r2..r5 loads
stores r2..r5
r6..r10 loads
Blk8#1
r2..r5 loads
Blk8#2
stores r6..r10
stores r2..r5
```
sched1 might hoist r6..r10 loads to top (they're independent). Then we'd get: group A loads, group B loads, group A stores, Blk8#1... which matches target! Let me try that.

Actually that's promising: in the target, group B loads ARE hoisted above group A stores. So source had stores right after loads, and sched1 hoisted the group B loads. Let me try w3.
