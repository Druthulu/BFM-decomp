---
ts: 2026-11-06T18:30:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KbNGTXbWJpKbPCs6dsAZ
---
Score 4: the a1 lui/addiu pair is moved from position 22-23 to position 31-32 (later). So the keepalive forced the a1 load earlier. Without it, sched1/combine sinks it.

Target: a1 load at insns 22-23 (after the second move a0,s0, before lui v0,0xfff6 at 24). Mine: a1 load at 31-32, after the v0 chain and before a2/a3? Let me see the mine asm. Let me get the full diff/asm. Let me run dt with a bigger tail or dump the candidate.

The position in target: 
```
20: move a0,s0 (second)
22: lui a1
23: addiu a1
24: lui v0,0xfff6
25: li s0,4
26: sw v0,20(a0)
...
```
Mine: a1 load after the v0|v1 chain (insns 31-32), before a2/a3 loads.

So I need a real-C way to keep the a1 load early: the keepalive was `__asm__ __volatile__("" ::"r"(a1))` — a scheduling barrier + liveness. Real-C alternatives:
- Reorder statements so a1 is *used* earlier: e.g., use a1 before the v0 chain. There's no use.
- Make a1 a call argument earlier? It is used at the call (func_8012D5E4).
- Use do{}while(0) around the v0 chain (C0535: splits the EBB, changes sched1 order).
- Move the a1 assignment later in the source (so it's adjacent to the use) — that would make it even later.
- Make the v0 chain a separate block via do-while.

C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". Let me try do-while around the v0 chain / the stores.

Also, the sched1 dump would tell. But first, cheap tries:
w2: do { v0 = 0xFFF60000; s0 = 4; ... } while(0) — where to put the block boundaries?

Actually, why did the keepalive force the early load? The asm is a volatile insn — it acts as a scheduling barrier (sched1 doesn't move insns across asm volatile? Actually sched1 treats volatile asm as a barrier for movement). The a1 load was before the barrier, so it stayed early. Without it, sched1 moved the load later (to just before the use region) or combine hoisted/sank.

Target's a1 load is early (position 22-23). So I need sched1 to keep it there. What real-C construct creates a barrier? A function call is a barrier, but there is no call between. A `do{}while(0)` creates basic-block boundaries (EBB splits), which stops scheduling across.

The target: a1 load at 22-23, right after the second `move a0,s0` (which is the pin's doing). Then the v0 chain. If I put the a1 assignment in its own basic block (e.g., inside an `if` that's always taken?), sched1 wouldn't move it across blocks... but it would also not be scheduled with the rest.

Let me think about what sched1 does: it schedules each basic block. The whole body after the call func_8012B1B4 is one basic block up to the func_8012D5E4 call. The a1 load and the v0 chain are in the same block. sched1 orders them by dependency/priority. The a1 load is independent of the v0 chain; sched1 chose to put it later (mine at 31). Target has it early.

The keepalive asm (volatile) forced it: the asm is a barrier, so the a1 load (before the asm) couldn't move after it. The v0 chain after the asm couldn't move before it. So the asm fixed the order.

Real-C equivalents that create an ordering: a store! The stores to unk14/unk2/unk58 are memory operations; sched1 respects memory dependencies only if aliasing is uncertain. The a1 load is a constant address (lui/addiu) — no memory. Hmm.

What about making a1's value depend on something computed early? E.g., a1 = (s32)&D_801A15AC; the lui/addiu are independent.

Alternatively, make a1 used before the v0 chain by a real use that costs no insns... e.g., the second `move a0,s0`? No.

Hmm, what about the pin a0? The target has TWO moves a0,s0 (insns 20,21 in the asm). Our build (score 4) has the same 51 insns with only the a1 pair moved. So the double move is already there.

Let me look at what mine's insn order is. Let me dump the candidate asm. Use --keep and look at the object? Simpler: dt.sh prints the diff with context; let me run with a bigger tail to see all mismatches (only 2 groups). The diff says: insert a1 pair at 22, delete at 31-33. So mine's insn 22..30 are the target's 24..32 (shifted): i.e., mine has `lui v0,0xfff6; li s0,4; sw v0,20(a0); lui v0,0x0; addiu; lui v1,0x4000; or; lui v1,0x2000; or` then `lui a1; addiu a1` at 31-32.

So I need sched1 to place the a1 load before the v0 chain. sched1's ordering is by dependency; the a1 load has no deps. Its position in the source (after `a0 = s0;`) — sched1 reorders. The keepalive asm kept it.

Real-C ideas:
1. Make the a1 load depend on something available early (a chain that sched1 must schedule first). E.g., `a1 = (s32)&D_801A15AC + (v0 - v0)`? launder/identity — forbidden.
2. Make the v0 chain depend on a1? no.
3. Put the a1 assignment inside a do-while block before the v0 chain: the block boundary stops sched1 from moving the load later (it can't move across the block end? Actually sched1 schedules per basic block; a do-while(0) creates a new basic block, so the a1 load in its own block would be emitted before the next block — but the next block's insns can't move before it. That would put a1 early!). But do{}while(0) also creates a jump? No — an empty do-while(0) generates no code (the loop body executes once); GCC's `do { } while (0)` creates a NOTE_INSN_BLOCK_BEG/END but not a basic block... Actually C0535 says "do{}while(0) splits cse1 EBB" — it does create an EBB boundary (a basic block) because of the loop structure, even with a constant condition. In GCC 2.7.2, `do { A } while (0)` compiles to: A; then a conditional branch? Let me think: the loop has a test at the end; with the constant 0, expand may emit `if (0) goto top` → the branch is optimized away but the basic block boundary may remain in the CFG? The evidence from the cookbook says it splits cse1's EBB, so it does create a block.

If I wrap the v0 chain in do{}while(0), the a1 load (before the block) stays before it? Let's see: the a1 assignment is in the outer block; the v0 chain in the inner block. sched1 schedules the outer block: it contains the a1 load and the stores. The inner block contains the v0 chain. The outer block's insns can't be reordered with the inner block's. The a1 load is at the end of the outer block (in source order), then the inner block. That would put a1 AFTER the stores but before the v0 chain — hmm, target has a1 at 22 before the v0 chain, and the stores unk14 (26) and unk2/unk58 (36,38) after.

Wait, target order: a0=s0 (20), a0=s0 (21), a1=load (22-23), v0=0xfff60000 (24), s0=4 (25), unk14=v0 (26), v0=&D_801A1474 (27-28), v1=0x40000000 (29), or (30), v1=0x20000000 (31), or (32), a2=load (33-34), a3=0x20 (35), unk2=s0 (36), unk58=v0 (37), call (38)...

Hmm, in the target the a2 load is at 33-34 and a3 at 35, after the v0 chain. In mine, the a1 pair is at 31-32 (after the v0 chain, before a2/a3?). Let me get the exact mine order. Let me dump the candidate.

Let me use --keep and objdump the candidate object. Actually the .s dump via cc1_dumps_tu.sh on the scratch TU would give the asm (t3.s). But that's the whole TU. Simpler: dt.sh's diff is enough.

Let me just try candidates:
w2: do{}while(0) around the v0 chain (from `v0 = 0xFFF60000;` through the ors).
w3: do{}while(0) around just `a1 = ...;`? That would isolate a1 in a block.
w4: move the a1 assignment to just after `a0 = s0;` — already there.
w5: use a1 earlier: make the call's args computed in a different order, e.g., `a2 = ...; a3 = ...;` before the v0 chain? That changes their positions.
w6: assign a1 to a temp and use it at the call: `s32 a1t = (s32)&D_801A15AC;` (init at decl at the top) — the load would be at the top of the function (before the first if) — target has it inside the if.

Hmm, what about `a1 = (s32)&D_801A15AC;` moved to the TOP of the if body (before the func_8012B1B4 call)? Then the a1 load would be before the call — target has it after. No.

Let me look at the actual full asm of w1 to understand the order. Let me get a dump. I'll use the scratch TU from --keep.
