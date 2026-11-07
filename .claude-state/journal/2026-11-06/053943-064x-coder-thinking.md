---
ts: 2026-11-06T12:39:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bRyh1B8u5qPEaJbLIdoG
---
Confirmed: sched1 runs BEFORE local_alloc/global_alloc. So the RTL order seen by global-alloc is sched1's output. In c2, sched1 put `li a0,7` before `sw v0,216(s1)`; in the target, sched1 put the store first and the li into the delay slot.

So the ordering difference is sched1's decision — and it depends on the registers/priorities in a chicken-and-egg way? No: sched1 runs before allocation, so the same source → same sched1 order regardless of the pin... unless the pin (register asm) changed the RTL before sched1 (it does: the pseudo has a hard reg, so sched1 sees `set (reg:SI 2) (const_int 7)` — no wait, the pin makes it a hard reg? With `register s32 ret __asm__("$2")`, the variable is a hard register (reg:SI 2) from the start, so `ret = 7` is `set (reg:SI 2) (const_int 7)` — a hard-reg set, and sched1 treats it differently, and the li lands in the delay slot.

Without the pin, sched1 sees `set (reg/v:SI 73) (const_int 7)` — and reordered.

So the question becomes: how to get sched1 to place the ret=7 def AFTER the v0 store. sched1's ordering depends on dependencies and priorities. The `li` (constant) has no deps; the store depends on v0 (call result). Sched1's list scheduling puts ready insns in priority order; the li is ready immediately, the store waits for the call's result. So the li gets scheduled before the store. In the target, the li is after the store because the store's v0 is the call result and... hmm, but the target also has the li ready earlier.

Wait, in the target the store `sw v0,216(s1)` is immediately after the jal (v0 = call result) — that's a fixed dependency (the jal writes v0). And `li v0,7` also writes v0 → it must come after the store reads v0 (anti-dependency). In the target, ret = v0 (hard reg), so the li has a WAR dependency on the store → sched1 must place the li after the store!

In mine, ret is a pseudo → no dependency → sched1 puts the li early.

So: if ret is a hard reg v0, the dependency exists. Without the pin, we can't. Chicken-and-egg: the allocator would need to know.

BUT: what if we create a real C dependency between the value and v0? Hmm.

Alternative: what if the store `unkD8 = call(...)` and `ret = 7` are ordered so that even with a pseudo, sched1 keeps the store first? Sched1 sorts by priority = length of the dependency chain... The store's insn priority is based on how much depends on it. Hmm.

Trick: make the ret value depend on the call result? No, ret = 7.

Alternative trick: use `(s16)` casts or something to change priorities? Hmm.

Another idea: since the conflict comes from this ordering, maybe a different arm structure could avoid the conflict: e.g., if the arm's `ret = 7` were placed after the store in the RTL by making it a *use* of something the store defines. 

Hmm! What if we write `ret = 7;` as `ret = (s32)7;`... no.

What if we reorder the C so that `ret = 7` comes after the store — it already does. The scheduler ignores source order when there are no deps.

Could we force a dependency? For instance:
```
s32 t = func_80143994(param_1, 0x3000);
unkD8 = t;
ret = 7;
```
That's the same.

What if the C were:
```
unkCC = (s32)&D_801EE880;
unkD8 = ...call...;
ret = 7;
```
same.

Hmm. What if the C assigns ret from an expression involving the call's result? No, ret = 7.

Alternative: maybe the target's arm order in the RTL is: store, li. And the reason is the anti-dependency (ret is v0). Since we can't pin...

New idea: maybe the allocator conflict is avoidable another way: ret conflicts with v0 because ret is live across that store. What if ret's live range were shorter: ret's def is the li; the use is at STORE. If the li comes before the store, ret is live across the store → conflict.

Unless... the STORE use is a `use` at the very end; the live range is def→STORE.

OK, radical: what if we change the STORE to use v0 differently? 

Hmm, hold on. What if we simply *reorder the C statements* so that the call-result store happens in the previous statement group? The store `unkD8 = call(...)` is inherent.

What if we split:
```
s32 r = func_80143994(param_1, 0x3000);
unkD8 = r;
ret = 7;
```
`r` is a temp pseudo; the store uses r. Then ret's def is still independent of r... but sched1 might order differently: the store `sw r,216(s1)` where r = call result. Same.

What if the temp is assigned from the call and then `unkD8 = r; ret = 7;` — the scheduler still sees `li 73,7` independent.

Hmm. What determines sched1's order here? Let me look at the sched dump (-ds) for this region to see why. Maybe the priority of the li vs the store: sched1 picks the highest priority ready insn; the store isn't ready until v0 is available (the call insn is a barrier? calls are scheduling barriers in sched1? In 2.7.2 sched1 treats calls specially (can't schedule across)).

Actually wait — if sched1 can't move insns across calls, then the order after the call is preserved as emitted! The emitted order after the call: `sw v0,216(s1)` (the assignment of the call result) then `li a0,7`. So sched1 shouldn't swap them...

Unless the emit order is: call; li 73,7; sw v0,216. Which would mean the *expander* emitted the li before the store. Why? Because the call result store: gcc expands `unkD8 = call(...)` as: emit call → then `emit_move_insn(mem, v0)`. Then the next statement `ret = 7` → `set 73 = 7`. So order: call, store, li. Hmm.

But the lreg dump shows insn 127 (li) before insn 124 (store) in the stream. And the numbers: 124 < 127. So the store was emitted BEFORE the li (lower number) but appears AFTER in the stream. So something reordered them: sched1! (which runs before lreg). So sched1 DID reorder them, meaning calls are not complete barriers for this.

Hmm, so sched1 moved the li before the store (both after the call). Why? Probably because the store has a dependency on v0 (the call result) and the li is independent, so list scheduling emits the li first.

In the target, the li sets v0 (hard) so it must come after the store (WAR) → the store goes first, and the li goes into the j delay slot.

So to reproduce: make the C such that the value assigned to ret has a WAR dependency on the call result... i.e., ret's value must be produced in v0. Circular.

Alternatively, make the store come first by giving it higher priority: the store's priority depends on what depends on it. If the li depended on the store... 

Idea: `ret = 7;` where ret is assigned *from* a variable that was stored: e.g.
```
unkD8 = call(...);
ret = 7;
```
What if we write `ret = 7;` after a statement that *uses* unkD8? Like `((Unkstruct*)param_1)->unkD8 = ...; ...; ret = 7;` — the store and the li are independent.

What if the C were `ret = 7;` but placed inside a do-while(0) block with the store? Block boundaries (NOTE_INSN_BLOCK_BEG/END) don't stop sched1... Actually, do they? C0535 says a do-while(0) splits cse1's EBB and affects sched1's birth order. Sched1 works on basic blocks; a do-while(0) doesn't create a basic block boundary by itself, but the NOTE may split sched1's regions? In sched.c, the region boundaries are determined by basic blocks, and NOTE_INSN_BLOCK_BEG might not matter.

Hmm, but C0535 says it splits cse1's EBB, which changes *cse*, not sched.

Let me look at the sched dump to see the region and the priorities. Quick: grep the sched dump around the call.

Actually, maybe a much simpler C-level fix: put the `ret = 7` assignment BEFORE the unkD8 store in the source but make it depend... no, that makes it live across the call.

Wait, actually: what if `ret = 7` is moved before the call? Then ret is live across the call → needs saved reg (s0). No.

Hmm, what about making the two stores' order: target has `sw v0,204(s1)` (unkCC) in the jal's delay slot and `sw v0,216(s1)` after. In c2, same (1b0c delay slot store 204, then store 216).

Let me look at the sched dump for this block to see the priorities.
