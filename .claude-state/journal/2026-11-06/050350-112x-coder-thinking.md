---
ts: 2026-11-06T12:03:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_imhuXXrBpLjxYNnrVQjd
---
w2's diff: a 4-insn block (the `D_8018DB2C[idx]` load) is scheduled differently: mine has it at 134-137, target at 136-143. A sched1 ordering issue: the index computation `sll v0,v1,0x2; lui at; addu; lw` moved.

The barrier (memory clobber) forces the load of D_8018DB2C[idx] to stay after the `D_8011F83A = idx` store (the memory clobber prevents cse/sched from moving the load across). Without the barrier, the compiler hoists the array load earlier.

The code:
```
idx = D_8011F83A & 0x7F;
D_8011F83A = idx;
<barrier>
((void (*)(s32, u8 *))func_80024054)(((s32 *)D_8018DB2C)[idx], local);
```
Without the barrier, the load `D_8018DB2C[idx]` moves before the store `D_8011F83A = idx`? The diff shows the load block moved by 2 insns (from 134 to 136). Hmm, target has it at 136-143; mine at 134-137. So mine is EARLIER.

The barrier is a memory clobber → the load can't move before the store. Without it, sched1/cse hoists the load above the store.

Real C: make the load not hoistable. Since D_8011F83A is a global and D_8018DB2C is a global array, a real store to D_8011F83A... cse/sched treat globals as memory; the load `((s32*)D_8018DB2C)[idx]` reads memory that may alias the store to D_8011F83A. Sched1 (sched.c) is conservative about memory? sched_analyze_2 for a MEM: it uses `true_dependence`/`anti_dependence`. It should respect the store.

Hmm, but the store is to `D_8011F83A` (a specific global, address known) and the load is through `D_8018DB2C[idx]` (varying) — a real dependence check should say the load depends on the store (may alias). But maybe the load is `D_8018DB2C` (the array base, a fixed global) and the index. The load address = D_8018DB2C + idx*4. The store address = &D_8011F83A. Different known globals → `true_dependence` might prove no alias? But they're both globals; gcc 2.7.2's alias analysis for two SYMBOL_REF-based addresses can prove they don't overlap if the symbols differ... Actually the store address is a SYMBOL_REF (D_8011F83A) and the load address is `(plus (symbol_ref D_8018DB2C) (reg))` — a varying address → may alias. So sched should keep the order.

Hmm, but the diff shows only the load moved 2 insns earlier — maybe it's the *index computation* (sll/lui/addu/lw) moving, not the load itself.

Let me look at the actual code around 130-145 in both.

Let me dump mine (w2) and the target.
