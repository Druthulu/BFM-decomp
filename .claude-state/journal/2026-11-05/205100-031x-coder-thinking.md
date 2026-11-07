---
ts: 2026-11-06T03:51:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kWV6rVmC2YzeG1bENimz
---
All worse (11). c1/c2 at 4 is best. So t-reuse for the C4 load matters. The zero store placement is the remaining 4.

Hmm. Let me look at what changes at score 11 — maybe the load hoisted. Anyway.

Focus: in c1, the diff is only the zero store position. Need to make `sh zero,EA` come right after the C4 load. 

Idea: make the EA zero store's address or value depend on t. What if the source uses `D_801269EA = 0;` where the compiler can share the address with E8? They're different symbols but adjacent addresses? D_801269EA and D_801269E8 — separate extern symbols.

Alternative: write the two halfwords as a single 32-bit store? Target has two sh, so no.

What if we use `D_801269EA = t, D_801269E8 = t;`? Then both stores use t; the first (EA) gets t instead of 0 — wrong value.

Wait, maybe the EA zero store in the target is actually generated from a *different* statement: e.g., `D_801269EA = 0;` might be `D_801269EA = (s16)0;` — same.

Let me think about sched1's behavior. The zero store got deferred because of the `at` WAW dependency: after the C4 load's `lw` (which uses at for address), the next insn using at is the E8 store's `lui at`. The zero store also needs at. Order between E8 store and zero store in the ready list: both depend on the C4 load? No. Actually why does E8 come first in mine? Because t's load just completed and E8 is its consumer (high priority, closer to critical path). The zero store is independent, lower priority, so scheduled later.

To make the zero store higher priority, give it a dependency on the load: e.g., compute zero from t: `D_801269EA = t ^ t;`? Combine might fold. But what about `D_801269EA = (s16)(t - t);`? Folds.

What about using an actual expression that GCC 2.7.2 won't fold: `D_801269EA = t & 0;`? combine folds and with 0 to 0, yes.

`D_801269EA = t * 0;` folds to 0.

Hmm.

Different approach: make the E8 store LATER by giving the zero store a separate address computation that must precede? 

Or: put the zero store and E8 store in a `do{}while(0)` block? C0535 says do-while splits cse1 EBB, affecting sched1. A do-while(0) around the zero store might make sched treat the block boundary and keep order. The brief says `do{}while(0)` only with `// !FAKE: do-while`. So allowed with annotation. Let's try wrapping the two stores:
```
do {
    D_801269EA = 0;
    D_801269E8 = t;
} while (0);  // !FAKE: do-while
```
Hmm, do-while(0) around a single statement? It creates a loop note that cse1 respects as EBB boundary. Could keep order. Let's test.

Also try wrapping just the zero store.

c6: do-while around both stores.
c7: do-while around zero store only.

Let me create.
