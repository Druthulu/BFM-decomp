---
ts: 2026-11-06T20:26:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hnn9e1FRac0yeYl6PsqW
---
In orig, the block's schedule: T-7 picked 100 (const a1), then 97 (move a0); forward order: 97, 100, 102(asm), 105(li), 107(sh), 114(call), 117, 120. So: move a0, const, asm, li, sh, call → reorg fills with sh. 

In nolau, the order: 95, 101, 103, 108, 110. So the const went last.

Why? In orig, the asm (102) is a scheduling barrier: it "uses and clobbers all registers", so 100 (const) must come before 102, and 105 (li) after 102. The ready list at T-6 picked 102, then at T-7 the only candidates were 97 and 100. So the const was forced before the asm.

In nolau, at T-4 the ready list was `103 (1) 95 (1) 108 (1)` and it picked 108. rank_for_schedule: priority equal (1); then it compares `INSN_LUID`? Let me check rank_for_schedule: it prefers insns with greater priority; ties broken by... `INSN_LUID` (the later insn first when scheduling backwards?), then `ref_count`? Actually the dump shows "103 (1) 95 (1) 108 (1)" — the list order. The scheduler picked 108 (the last in the list). Let me look at rank_for_schedule.

Actually, since all have priority 1, the tie-break is `INSN_LUID`: scheduling backwards, it prefers the insn with the *later* LUID (closer to the end)? The const 108 has the latest LUID among {95,103,108}? In the source order: 95 (move a0), 101 (li), 103 (sh), 108 (const)? Hmm, in nolau's RTL, what's the original order? From .dbr: insn 101 (li), 103 (sh), then call seq [110, 108 const]. So before reorg, the RTL order was 95, 101, 103, 108, 110. The const (108) was already after the store in the RTL — from where? That's the *output* of sched2? No wait, .dbr is after sched2. Hmm, the .sched2 dump shows the schedule; the order after scheduling is 95,101,103,108,110.

But what was the input order to sched2? Let me check the .lreg or .greg dump (pre-sched2). The C source order: q decl (move a0), r decl (const), store (li,sh), call. So RTL: 95 (move a0), 100 (const), 101 (li), 103 (sh), call. sched2 moved the const from position 2 to position 4.

Why did sched2 pick the const last? All priorities are 1. The tie-break is likely `INSN_LUID`: for backward scheduling, pick the insn with the highest LUID (latest) first. The const 108 has LUID after 103? Yes (source order: const insn was created... hmm, the const was at source position 2, so its LUID is between 95 and 101). But the scheduler renumbers? INSN_LUID is assigned by the scheduler at the start (`schedule_insns` assigns LUIDs in the current insn order). If the const's LUID is less than 103's, then at T-4 the scheduler should pick 103 (later LUID) first, not 108.

Hmm, the "ready list at T-4: 103 (1) 95 (1) 108 (1), now 108 103 95" — the "now" is the ready list after the pick, sorted; the picked one is not shown in "now". So it picked the *last* in the sorted list? Or the first? The list before the pick was presumably "108 103 95" and the pick was 108 (the head). Hmm, the dump prints the ready list at T-4 (before the pick?) then "now" after adding newly-ready insns.

Actually the format: "ready list at T-N: <list before pick>, now <list after pick+additions>". So at T-4 the list was `103 95 108` and after picking 108 (removed) and adding nothing, it's `103 95`. So it picked 108 from the tail? No — it picked 108, which was third in the list. Hmm, maybe the list is printed sorted after adding, and the head is the pick. The "now 108 103 95" is the *new* list including 108? That doesn't make sense either.

Let me read sched.c's dump code to interpret. Actually, not worth it. The practical question: how to make the const stay early in real C.

Since the asm barrier is the mechanism and plain C has no barrier, maybe we can find a *dependency* that pins the const before the li. The const (a1) is used by the call. The li v0,7 is used by the sh store. Both feed the call block end.

Idea: make the store's *value* come from r in a value-preserving way. We need `((Unk*)s0)->unk2 = 7` and r = 0xFFF80000, with a real dependency store←r.

What if we write `((Unk*)s0)->unk2 = (s16)(7 + (r >> 16 & 0x0));` — identity.

Alternatively, change the constant's position by making it feed the store's *address*: no.

Hmm, what about making the const depend on the store? i.e., the const's value computed from a load of unk2 after storing 7: `((Unk*)s0)->unk2 = 7; r = 0xFFF80000 + ((Unk*)s0)->unk2 * 0;` identity and adds a load.

OK, maybe a different route entirely: can we get the target's order by using a *different but equivalent* C that sched2 orders correctly? What if we define r before the `q` pin declaration (so the const is first in the block)? The block order would be: const, move a0, li, sh, call. sched2 might then leave the const first? Since the const is already at the top, the scheduler... it can still move it down.

What if we place the const's definition in the *previous* block (before the bnez)? E.g., define r before the if/else (outside both arms)? Then the const would be hoisted out of the arms into the common block before the bnez — the target has the const inside each arm. Hmm, but if r were defined once before the if, the code would have one lui before the bnez and both arms would use it — target has the lui inside each arm. Not matching.

Let me try the simple reorder variants and see:
vD: q and r decls swapped:
```
s32 r = 0xFFF80000;
register s32 q __asm__("$4") = s0;
```
vE: store first then r:
```
register s32 q __asm__("$4") = s0;
((Unkstruct_800B5CB8 *)s0)->unk2 = 7;
s32 r = 0xFFF80000;
func_8012B178(q, r);
```
(C89 allows decls only at block start, but gcc 2.7.2 might accept mixed; risky. Use a nested block.)

Let me first test vD, and also vD with the barrier fix (do-while) to see the barrier part separately.

Barrier variant: wrap `v ^= 1;` in `do { v ^= 1; } while (0);  // !FAKE: do-while`.

Let me create:
vD = nolau + swap q/r decls.
vE = nolau + do-while around v ^= 1.
vF = nolau + both.

Score them.
