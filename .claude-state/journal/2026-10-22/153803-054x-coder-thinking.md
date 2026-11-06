---
ts: 2026-10-22T21:38:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MewTgprZ4ja95Yv8NJZ6
---
Only the sw ra position differs: mine has it at 2928 (after the sh -64), target at 2914 (right after move s0,a0).

sched2 sinks the prologue sw ra. The barrier prevented it.

Plain C ideas: make sched2 not sink it. Per the comment, the mechanism is sched2's potential_hazard. Let me check sched2 dump for the block and see why.

Quick experiments (cheap):
1. Swap the two dead stores: `sp10[0] = 0; sp10[1] = -0x40;`
2. Use a variable index for one store: `s16 *p = sp10; p[0] = 0;` — the address becomes non-constant.
3. Store to a global first: no.
4. Make `s0` not needed... no.
5. Move the load into a temp: `s32 t = D_801270C8[0]; if (t == 0xA)`.
6. Load into `iVar2` style.

Actually the key: in the target, sw ra is right after move s0,a0 — i.e. it stays in the prologue where expand put it (prologue insns are usually kept). In mine sched2 moved it after the load.

What does sched2 use to move it? The `sw ra` has no dependence on the load. sched2 reorders within a basic block using priorities; the load `lw v1,0(v1)` and `sw ra` are both MEMs — potential_hazard gives memory insns priority. Since the addresses are different (constant vs a global), sched2 thinks no dependence and can move the sw later.

To prevent: give sched2 a reason to keep sw ra early. Plain C options: make the *first* insn after the prologue a memory op with an address that could alias the stack, e.g. a store through a pointer variable whose address is unknown:

```
s16 *p = sp10;
p[1] = -0x40;
p[0] = 0;
```
Then the address is `(reg p)` — not constant. sched2's potential_hazard: an insn with a MEM whose address is a register is a potential hazard; ordering between sw ra and it becomes... hmm, potential_hazard affects the priority of the *other* insns (it lowers the priority of ALU insns, or raises MEM insns).

Let me just try a batch:
a1: swap the two stores.
a2: pointer p = sp10, p[1] = -0x40; p[0] = 0.
a3: load into a temp first.
a4: `sp10[1] = -0x40; sp10[0] = 0;` with sp10 declared as `s16 sp10[2] = {-0x40, 0};`? init at decl — changes prologue.
a5: assign both via a struct copy? no.
a6: `*(s16 *)(sp10 + 1) = -0x40;`
a7: make the load `if (*(volatile s32*)D_801270C8 == 0xA)`? volatile is a lever.
a8: reorder: `if (D_801270C8[0] == 0xA)` first then the stores? changes order.

Let me try a1-a4, a6 plus a variant where sp10 is written through a s16* local.

Also idea: `sp10[1] = -0x40;` where the value comes from a variable `s16 m = -0x40;` → li born earlier.

Let me generate.
