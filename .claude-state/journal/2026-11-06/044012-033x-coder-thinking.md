---
ts: 2026-11-06T11:40:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a3xBpuRQmtvj4cOzdEGw
---
All still 4 — none of these produced a label that survived to reorg at the head. The label-inducing constructs get optimized away before reorg (or the label isn't at the head).

Let me reconsider. Maybe the label needs to survive. In C, a label that is the target of a goto from a reachable path survives. But reorg's stop_search_p stops on CODE_LABEL only for the fall-through thread (labels_p=1). The label must be the FIRST insn after the branch.

What if I use a label that's genuinely the branch target but ALSO at the fall-through head? Impossible (branch target is the taken path).

Alternative: make the fall-through's first insn a JUMP_INSN. That means the if-body starts with a `goto`. A goto that survives: e.g., `goto body;` where body is NOT immediately after (there's a statement between). But then the jump is real and adds an insn. Unless the target has that jump too. The target doesn't.

Hmm, wait. Let me reconsider whether the delay-slot fill can be achieved differently: make reorg's fall-through scan find `addiu v0,s1,1` (the i++) as the best candidate BEFORE `move a0,s0`. But the i++ is after the call in the fall-through thread. fill_slots_from_thread scans forward and can skip the call. It considers insns in order: move a0,s0 (fe4), jal (CALL), move a1,s2, move s0,v0, addiu v0,s1,1 (ff4), then target label. It stops at the target label (ff8) — but for the fall-through scan, labels_p=1 so it stops at ff8. So it scans fe4..ff4. The first eligible candidate is move a0,s0 → stolen. If move a0,s0 were NOT eligible (e.g., it sets a resource needed later or can trap), it might skip to addiu v0,s1,1.

eligible_for_delay checks if the insn can go in the slot. `move a0,s0` sets a0. The call needs a0. If reorg can move it to the delay slot (before the branch), that's fine because the branch doesn't use a0. But it checks `insn_sets_resource_p(trial, &opposite_needed)` — resources needed at the opposite (target) thread. a0 is not needed at the target (ff8 uses v0, s1). So move a0,s0 is eligible → stolen.

To make move a0,s0 NOT the first thing, or not eligible: what if the call's first argument setup is something else? The call is func_801889B8(ot, w, i): a0=ot (s0), a1=w (s2), a2=i. The setup order: move a0,s0; move a1,s2; (a2 from i). If I reorder the call arguments? Can't (signature). 

What if the call is `func_801889B8(w, i, ot)`? No, wrong.

Hmm. What if I precompute the arguments into temps so the first fall-through insn is a load or something not eligible? E.g., the target's fall-through after the beqz is `move a0,s0`. To prevent stealing, the first insn must be ineligible. `may_trap_p` — a load can trap, so if the first insn were a load, it's not eligible (unless annul). A `move` is always eligible.

What if the first argument setup involves a load? E.g., if `w` were loaded from memory right there. But w is a pointer in a callee-saved reg.

Alternatively, make reorg's fall-through scan return 0 (nothing) so it then tries the target thread and copies addiu v0,s1,1. For the fall-through scan to find nothing, all insns fe4..ff4 must be ineligible. move a0,s0 is eligible. So impossible unless there's a stop.

So I DO need a stop (label/jump) at the head. Let me figure out how to keep a label there.

What if the label is the target of a goto that the compiler can't eliminate because it's from a different basic block that's reachable? E.g.:
```
if (h != 0) {
    if (D_80115158[i].h != 0) {
        goto body;
    }
body:
    ot = call(...);
}
```
The inner condition is the same as the outer, so gcc folds. Dead.

What about a label targeted by a computed goto? No.

What about using a `switch` where the case label is at the head and the switch value is opaque (from memory)? The switch would add a comparison/jump. But maybe the switch on the same `D_80115158[i].h` after the != 0 test gets folded to just the default path with a label? The v_lab_sw scored 4, so no label survived (or it was optimized).

Hmm. What about a label targeted by a `goto` from AFTER the call (a backward goto that's part of a loop)? That's the for(;;)/while(1) which got optimized.

Let me check: does gcc 2.7.2 actually remove for(;;){body;break;}? Maybe it keeps the loop but the label is at the loop top which IS the head. But score stayed 4 — maybe the loop was kept but the delay slot still stolen? Let me disassemble v_lab_for to see if there's a label/jump.

Actually, let me step back and consider: the header explicitly says these six levers were each byte-verified load-bearing. The probability that real C can replace the barrier is low. But moves.md line 260 shows a WALL for exactly this (dbr-delay-fill). And line 247 shows a MATCH using `do { t = ...; sp10[4] = t; } while (0)` for a different delay-slot issue (keeping adds OUT of a load delay slot). And line 130: `init at decl s16 *s1 = 0;` → reorg puts it in the bnez slot.

Let me look for a MATCH where a barrier was replaced by a real-C construct that stops the scan. grep moves.md for "label" or "goto" + delay.

Let me grep moves.md for "stop_search" and "goto loop".

From earlier: 
- line 240: barrier | func_8017D508 | WALL jump2-crossjump-arms
- line 247: MATCH do-while

Let me grep for "delay slot" MATCH lines and "goto".

Actually, the brief mentions MOVES+: C0535 (do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item) and C0414 (dead-reset cse-breaker). These are for different mechanisms.

Let me look at the broader moves.md for any "barrier" MATCH that involved a delay slot filled from target. Let me grep "MATCH" with "delay".

Let me also reconsider: maybe the answer is a `goto`-based loop where the label IS at the if-body head and survives because the loop is real. The outer loop is a do-while. What if I restructure the OUTER loop to use a goto label at the top of the body, and put the if-body such that... no, the label is at the loop body top (fc0), not inside the if.

Hmm wait — what if I restructure so the `if (h != 0)` check's fall-through is preceded by the loop's label? I.e., merge the if into the loop condition? No.

Let me look at the exact target: the barrier was at the head of the if-body. What real C emits a CODE_LABEL at the head of a block? A `goto` target, or a `switch` case, or a `case` label. Let me try a switch where the case is reachable and the switch is NOT optimized away. E.g.:

```
if (h != 0) {
    switch (1) {
    case 1:
        ot = call(...);
        break;
    }
}
```
switch(1) with case 1 — gcc folds to just the case body (no label). 

```
switch (h) {
case 1: ... 
default: ot = call(...);
}
```
adds comparisons.

What about a `case` in an enclosing switch? The function has no switch.

Alternative: use `&&` short-circuit to create a label? No.

What about a `for` loop whose increment/latch is the call and the head label is the call? 

Hmm, let me try a different tactic: put the barrier-equivalent as a `volatile` access? No, that's a lever-ish (volatile is real C but changes codegen). Actually volatile is real C and not a "lever" per the kinds (barrier,pin). But the brief says lever-free = none of the row kinds remain. A volatile access is not a barrier/pin. But would it stop the scan? A volatile load/store is an INSN, not ASM_INPUT, so stop_search_p returns 0 (not a stop). But a volatile access might not be eligible for the delay slot (may_trap or volatile). Hmm. But adding a volatile access would add instructions (a load/store), which the target doesn't have. Bad.

Let me reconsider the whole thing. Maybe there's a simpler structural change: what if the i++ is moved so that the delay slot naturally gets it? 

Target: 
```
do {
    if (h != 0) {
        barrier;
        ot = call(ot, w, i);
    }
    i++;
    w++;
} while (i < cnt);
```
The delay slot of the beqz gets `addiu v0,s1,1` (i+1). This is the i++ computation. What if I write:
```
do {
    s16 next = i + 1;   // compute i+1 before the branch
    if (h != 0) { ot = call(...); }
    i = next;
    w++;
} while (i < cnt);
```
Then `next = i+1` is computed before the if → before the beqz. sched2/reorg might put it in the delay slot? But it would be BEFORE the branch naturally (not in the slot). Hmm.

Actually the target's delay slot insn is a COPY of i+1 that reorg placed. If I compute i+1 before the branch, the compiler would emit `addiu v0,s1,1` before the beqz, then the beqz delay slot would be filled with something else. Different.

What if I compute i+1 AFTER the if but use it in the loop condition, and the compiler schedules it into the delay slot naturally? That's what the target has (i++ after the call, and a copy in the slot). The copy in the slot is reorg's doing.

OK here's another idea: what if the if-body's call argument setup is NOT `move a0,s0` as the first insn? If I pass a computed value as a0, e.g. `ot = call((s32*)((u8*)ot), ...)` — no, ot is already a pointer.

What if I reorder so the first fall-through insn is `move a1,s2` (also a move, still eligible) — no.

The issue is any move is eligible. Need a non-move first, or a stop.

Let me check: is a `sw` (store) eligible? Stores have side effects; may_trap_p false but insn_sets_resource? A store references memory (sets MEM). The opposite thread (target ff8) doesn't use memory. Hmm, but stores can't be speculated? eligible_for_delay checks may_trap_p; a store doesn't trap but is it eligible? Actually reorg won't move a store into a delay slot across a branch unless... it might. Risky.

Let me look at how other shards cracked this exact "beqz slot filled from target" with real C. Let me grep the cookbook and moves for "filled from" / "target thread" / "stop_search".

Let me grep moves.md more broadly for "delay" MATCHes.
