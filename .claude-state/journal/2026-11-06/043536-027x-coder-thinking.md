---
ts: 2026-11-06T11:35:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1meSGTAix0wEHWY1SDVX
---
Interesting: mine's Blk8 copy 20210→26960 moved to the top (sched1 moved the whole copy up), and the stores are interleaved.

The target has all loads first, then all stores. Mine interleaves.

Why? Because the original compiler (with no barrier) chose to hoist. Hmm, but target is the original. Unless the original source had a data dependency forcing the order: e.g., the stores use `at` (address temp) and the loads also use lui... no.

Key: in target, the second Blk8 copy (20218→26968) appears AFTER the second group loads. In mine, it's... let me see. Mine has t6,t5 pointers later.

Actually, the difference might be because the ORIGINAL had the assignments in a different source order, or the original used a single statement per line with different grouping.

Let me think about the target's register allocation more carefully as a signature:

Group A (first 4 s32 loads): v0,v1,a0,a1.
Group B (r6,r7 = u16; r8 = s32; r9,r10 = u16): a2,a3,t0,t1,t2.
Blk8#1: ptr a1 (src 20210), a0 (dst 26960), data v0,v1.
Group A2 (4 u16 loads from 220..226, but wait they're u16 → stored with sh): v0,v1,a0,a1.
Blk8#2: ptr t6 (src 20218), t5 (dst 26968), data t3,t4.
Stores: a2,a3,t0,t1,t2 then v0,v1,a0,a1.

So group B (r6..r10) is in a2,a3,t0,t1,t2 — the 5 registers right after a0,a1... Actually order v0,v1,a0,a1,a2,a3,t0,t1,t2,t3...

Hmm. The allocation order suggests that the variables were allocated in the order they're first used / declared, with group A taking v0..a1, group B taking a2,a3,t0,t1,t2.

Global-alloc assigns in order of priority. All have 2 refs. But group B values are live longer (from load to near end). Group A dies early. So group B has higher priority (longer life) and should get the BEST registers (v0,v1...). But they got a2,a3,t0,t1,t2, which are worse. So maybe global-alloc ordering isn't by that.

Actually in gcc 2.7.2, global-alloc: `allocno_compare` sorts by (floor of log2 of refs * live length)... Let me recall: 
```
/* Allocate the registers in order of decreasing priority. */
```
priority = floor_log2(refs) * 10000 / (live_length or 1)? Something like that.

Hmm, actually from moves.md: "greg-pri-refs — pb 4 refs/74 insns". So priority = refs / live_length roughly.

Group A: 2 refs, live length short (~2-3 insns each). Group B: 2 refs, live length long (~50 insns). So group A has HIGHER priority (shorter live) and gets the best registers v0..a1. Group B gets next. That matches!

But then why did mine assign t3..t6 to the first group and v0..a1 to the second group? Because sched1 reordered, changing live lengths.

So the crucial thing is the ORDER of instructions, which sched1 determines. Hmm, but sched1 runs after global-alloc? No: global-alloc runs after sched1? Actually order: ... cse1, ... sched1 (first scheduling), then local-alloc, global-alloc, sched2 (reorg). Wait, in gcc 2.7.2, `schedule_insns` runs twice? There's one sched pass after global-alloc? Let me recall the pass order in toplev.c:

```
rest_of_compilation:
  ...
  cse (cse1)
  ...
  if (optimize) scheduling? 
```
Actually gcc 2.7.2: `rest_of_compilation` does:
- jump_optimize
- cse
- ...
- `if (flag_schedule_insns) schedule_insns(insns)` — this is before local-alloc? Let me check tools/reference/gcc-2.7.2/.

Actually the pass order in 2.7.2 toplev.c:
```
  /* On some machines, the first scheduling pass... */
  if (flag_schedule_insns) schedule_insns (insns, ...);  /* sched1 */
  ...
  local_alloc
  global_alloc
  ...
  if (flag_schedule_insns_after_reload) schedule_insns(...); /* sched2 */
```
Yes: sched1 is BEFORE local/global alloc. So the instruction order after sched1 determines live ranges and hence allocation. So to control allocation, I need to control sched1's ordering.

sched1 reorders based on dependencies. In the target, sched1 left the loads at the top and stores at the bottom. In mine, it moved the Blk8 copy to the top.

Why would sched1 move the Blk8 copy up? Because it has no dependency on the loads (different memory locations). In the original target, it didn't. Hmm.

Wait — maybe the original had a *memory barrier* that is a real C construct? No, real C can't.

Unless... the original code order was different: maybe the Blk8 copy 20210→26960 was NOT written as a struct copy but as explicit loads/stores that created dependencies. Hmm.

Hold on. Maybe the original source is not this shape at all. Maybe it's:
```
D_80126950 = D_80120200;
...
```
i.e., direct assignments without temps, and the compiler generates the lw/sw. Then the "temps" are the compiler's own. Let's test that! Direct assignment `D_80126950 = D_80120200;` would produce lw/sw pairs and the register allocation would be by the compiler. That's a much more natural original C.

But then the order of operations: with direct assignments, each `D_80126950 = D_80120200;` becomes lw t; sw t. The compiler might still hoist all loads. Let's just try it.

Actually wait: the target has ALL 9 loads first then stores. With direct assignments, sched1 would interleave or hoist. Let me just test.

Also note the Blk8 copies: `D_80126960 = (*(Blk8 *)&D_80120210);` — a struct assignment.

Let me write w2: direct assignments, no temps.

Also consider: the original might be a memcpy-ish with `s32` vars because the values are used for both groups.

Let me try w2.
