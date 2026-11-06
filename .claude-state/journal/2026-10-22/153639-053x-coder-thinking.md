---
ts: 2026-10-22T21:36:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BTnnuQEIyMFfyqEnTzMe
---
The `sw ra,28(sp)` is sunk to position 8 in mine; the target has it at position 3 (prologue). Exactly what the barrier was for.

Per the comment: sched2's potential_hazard promotes the prologue sw $ra over ALU candidates and sinks it just above the branch. The clobber makes sw ra have a successor so it's ready only after the load.

Plain C moves: I need the sw ra to stay in the prologue. The scheduling hazard: sched2's potential_hazard rule — memory insns get priority when there's a potential hazard (a load-store alias unknown). In the target, the two dead stack stores and the D_801270C8 load are constant-address MEMs → sched2 finds no dependence → promotes the sw ra over the ALU candidates.

Wait, re-read: "the two dead s16 stack stores and the D_801270C8 load are all constant-address MEMs, so sched2 finds no memory dependence and its potential_hazard rule promotes the prologue sw $ra over the ALU candidates, sinking it to just above the branch."

Hmm, so the clobber creates a memory dependence making sw $ra blocked.

Plain C lever ideas:
- Make one of the stack stores have a *variable* address so sched2 sees a potential alias with sw ra? e.g. `sp10[i] = ...` with a variable index.
- Reorder: put the D_801270C8 load first? That's what happens.
- Make `sp10` accessed through a pointer variable (address not constant) → sched2 sees a potential hazard.

Alternatively, maybe the real issue is different: the dead stores `sp10[1] = -0x40; sp10[0] = 0;` are dead (sp10 unused). If they're dead, flow/DSE would remove them... they survive (35 ins).

Since sched2's potential_hazard rule: in gcc, `potential_hazard` in sched.c:
```
static int potential_hazard (insn) { ... if it's a memory reference, return 1 ... }
```
Actually sched2's `rank_for_schedule` gives priority to insns that may trap / have hazards.

Practical: try variants:
1. `sp10[0] = 0; sp10[1] = -0x40;` (swap order) — sched2 order of the two stores.
2. Make sp10 volatile? no (lever).
3. Use a pointer: `s16 *p = sp10; p[0] = 0; p[1] = -0x40;` — the address becomes a pseudo (not a constant MEM) → potential hazard with sw ra? Actually sw ra is a MEM too; sched2's potential hazard is about a MEM whose address isn't known.
4. Add a store to a global (variable address).
5. Move the load `D_801270C8[0]` earlier into a variable: `s32 t = D_801270C8[0]; if (t == 0xA)` — then the load is born earlier; the sw ra scheduling may change.

Let me think about the target order. Let me get the target disassembly to see the first 10 insns.
