---
ts: 2026-11-07T01:09:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_j3yusUlR2phqKSsGtamo
---
hdump.sh inlines the body in place of the header include in an includer TU. It uses python3 -c (inline) — that's their tool, fine.

For item 2, the includers are src/ov_SC03_126/ov_SC03_126_jr_8017D5C0.c (3 includers).

But hdump.sh's python -c writes into the TU dir? It writes $o/$5.c where o = outdir (absolute under my shard). Then cc1_dumps_tu.sh compiles it. The `#include "common.h"` in the copied TU resolves via -Iinclude. The `../shared/engine_prelude.h` resolves relative to $o → $o/../shared. Hmm, same problem. Unless the outdir is placed such that ../shared exists.

Wait, but hdump.sh was used in T10 for header dumps. Maybe those TUs didn't have the ../shared include, or the outdir was placed under a dir with a shared sibling.

Let me test hdump.sh on item 2 and see.

Actually, for the analysis I mainly need the target's 16 instructions. Let me get them from the build object directly. The oracle's baseline_path: let me check what build object holds func_8017E98C.

Actually, simpler: `delever_search.py --explain` prints "mine" and "target" mnemonics only for differing blocks. Since only 1 differs, I know: target has `sw v0,516(s0)`. To understand the whole function, I can dump MY candidate (16 ins) and infer the target differs only at insn 10.

My candidate's 16 instructions: let me dump it with cc1_dumps_tu on a scratch TU (body only, with externs). The function references func_8017EE68 and func_80171990 — externs needed.

Let me write dump2/body.c:
```c
#include "common.h"
extern void func_8017EE68();
extern void func_80171990();
void func_8017E98C(void *a0) { ... }
```
Then dump and read the .s or the RTL.

Actually, I mainly need to understand *why* mine uses a0 for the second store. Let me think about the source:

```
  s0 = a0;          // copy 1
  call1(a0);        // a0 clobbered
  new_var = (char*)s0;
  v0 = 8;
  *(s32*)((char*)s0 + 0x200) = v0;   // store 1, base s0
  v0 = 0x100000;
  *(s32*)(new_var + 0x204) = v0;     // store 2, base new_var(=s0)
  call2((u8*)s0);
```

In the target (pinned s0=$16), the pseudo s0 is hard $16, so both stores use $16 and call2 gets $16.

Lever-free: the pseudo s0 (the copy of param a0) is live across call1 → must be callee-saved. Both stores should use it. But mine uses a0 for store 2. How?

Possibility: the compiler re-materialized the copy after the call: since s0's value = a0's value, and a0 is dead after call1, the compiler could set... no, a0 is clobbered by call1.

Unless the call to func_8017EE68 is not recognized as clobbering a0? It's an indirect-ish call through a cast of a function pointer constant. It's a normal call → clobbers caller-saved.

Hmm, wait: maybe the copy `s0 = a0` was moved by sched1 to AFTER call1? The note says "sched1 hoists the arg copy a0 = P(param) above both stores". Hmm, "a0 = P(param)" suggests the param pseudo is copied into a0 after the call (a reload of the param?). 

Actually, in gcc 2.7.2, function parameters are copied from their hard regs into pseudos in the prologue ONLY if needed; otherwise the pseudo IS the hard reg. With `-O2`, the param a0 may stay in a0 (the pseudo is allocated to a0) if it doesn't conflict. The source's `s0 = a0` copy creates a new pseudo for s0.

The register allocator: the copy `s0 = a0` may be coalesced (reg_may_share) if the live ranges don't conflict. a0 (the param) dies after the copy... but the call clobbers a0, so they conflict? Actually the param pseudo a0's live range is just the copy, so it can share with s0? Then both are the same allocno; if that allocno is callee-saved ($s0 in the target), both uses are s0. In mine, maybe the allocno got $a0 (caller-saved) — then the value must be saved across call1... 

Wait, the call1 argument is a0 (the param). If the copy's allocno is a0, then after call1 the value is dead. But the stores use it after call1! So the allocno must be callee-saved or the value re-loaded.

Unless the copy is moved after call1: `call1(a0); s0 = a0;`? That would be wrong semantically if call1 modifies memory that... no wait, a0 is a register; call1 clobbers it. Moving `s0 = a0` after the call would use a clobbered value — but the compiler only does that if it can prove... it can't.

Hmm, let me look at the actual generated code. Let me dump my candidate.

Let me create a scratch TU and dump. Use cc1_dumps_tu.sh directly (it accepts a .c file). The body needs externs for the two called functions and common.h.

Then read the .s (or .rtl) to see the 16 insns.

Let me do it.
