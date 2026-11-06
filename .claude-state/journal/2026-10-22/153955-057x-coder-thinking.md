---
ts: 2026-10-22T21:39:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EikpUXUlSxOyzAGhtBFk
---
Not enough info quickly. Let me take the practical path: try a handful more variants; if none, WALL.

Ideas that could create a memory dependence visible to sched2 without an asm:
1. Make the dead stores go through a pointer whose value is unknown (a local pointer set from a call? no).
2. Use `sp10` as an array indexed by a variable that's 0 — e.g. `sp10[arg0 & 0] = 0;` → folds to 0.
3. Introduce an aliasing store: e.g. store to `*(s16 *)&loc`... 
4. What about making `s0` (the arg variable) a pointer deref before the stores? no.

Alternatively: maybe the target's sw ra position can be reached by changing the ORDER of the two dead stores AND the load such that sched2's hazard rule picks differently. a1 (swap) still 2 but maybe a different insn is off now. Let me check a1's diff — it said score 2; maybe the residual is different.

Actually let me check a2's disassembly to see if the pointer changed anything.

Time: I'm at ~15:48. Let me be efficient: run 6 more variants, check diffs of the best, then WALL by ~15:55.

Actually — a cleverer idea: the `sw ra` is sunk because the block has many independent insns and sched2's potential_hazard makes MEM insns (the load) launch first. What if I make the *first* memory insn after the prologue depend on the stack pointer in a way that blocks... 

What about adding a *real* use of sp10 so the stores aren't dead? E.g. `sp10[1] = -0x40; sp10[0] = 0;` then `func_8002D4C8(sp10[0], sp10[1])`? changes insns.

Hmm, what about this: the two dead stores are `sh v0,18(sp)` and `sh zero,16(sp)`. If instead I write a single `s32` store... changes insns.

Let me try:
b1: `s16 sp10[2] = {0, -0x40};` init at decl.
b2: `sp10[0] = 0, sp10[1] = -0x40;` comma expr.
b3: pointer from a global? no.
b4: load first: `s32 v = D_801270C8[0];` before the stores (a4 was that but had a compile error because of the duplicated statement). Let me redo a4 properly.
b5: `if (D_801270C8[0] == 0xA)` with the stores moved AFTER the if? changes layout drastically.

Let me do b1, b2, b4, and a "store through a s16* variable read from a global"? no.

Actually here's a thought: `s16 sp10[2]` is dead. What if I make it `s16 sp10[2]; sp10[1] = -0x40; sp10[0] = 0;` where the writes are via `*(s16*)((u8*)&sp10 + ...)`. Already tried (a6).

OK, run b1, b2, b4 + 3 more random, then WALL.

Actually — one more idea that often works for sched2 walls: change the *number* of insns in the block (adding a real insn changes the schedule). E.g. `s32 v = D_801270C8[0]; if (v == 0xA)` adds a copy that combine may fold. a4 had a syntax error — let me fix and test.

Let me also test: `if (D_801270C8[0] == 0xA)` → `if (0xA == D_801270C8[0])` (canonical order swap) — probably identical.

Let me just run the batch.
