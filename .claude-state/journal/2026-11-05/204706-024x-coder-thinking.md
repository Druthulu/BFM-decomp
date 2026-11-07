---
ts: 2026-11-06T03:47:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hzokbr74AcQjOXFi5uGO
---
Target order:
- AC load v0 → store D_8012697C
- B8 load v0 → sh D_80126980
- C4 load v0 → sh D_801269EA=0, sh D_801269E8=v0
- D0 load v0 → sw D_801A1274
- call func_8017D8C4
- sw s1 D_801151D4

So all four loads happen in strict source order, each into v0, each consumed before the next. In mine, the scheduler hoisted some loads.

The single-temp-reuse hypothesis fits: with `t` reused across all four, each load writes t after the previous store reads it (WAR), serializing them, and each can use v0.

Note also: `D_801269EA = 0;` is a sh zero between the C4 load and the E8 store. In target: lw C4; sh zero,EA; sh v0,E8. Good.

Let me write candidate:
```
idx = func_800291B4(0xE0) & 0xFF;
... stores ...
func_8012A018((s32)func_8017D8C4, 0);
func_8012A094((s32)D_80126948);
t = D_801864AC[idx];
D_8012697C = t;
t = D_801864B8[idx];
(D_80126980[0]) = t;
t = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = t;
t = D_801864D0[idx];
D_801A1274 = t;
func_8017D8C4(D_80126948);
D_801151D4 = (s32)D_80126948;
```
Wait `t` is s32; D_80126980 is u16 array; assignment truncates — target does `sh v0`, so the loaded value stored as half. Fine.

D_801269E8 is s16; `D_801269E8 = t;` truncates to half — target sh v0. Fine.

D_8012697C is s32; sw. D_801A1274 s32 sw. Good.

But hold on: does reusing t create the WAR dependency in RTL? At expand, each statement generates its own RTL. `t` is a single pseudo; the store of t then `t = load` — GCC may rename? In 2.7.2 no SSA; t is one pseudo with multiple defs. The scheduler works on insns with dependencies via regs. The store `sw t` reads t; next load writes t: WAR dep, sched1 must respect? sched1 computes dependencies via sched_analyze, including anti-deps (true? GCC's sched_analyze_1 adds anti-deps via add_dependee... I believe yes, it handles output/anti deps). Likely.

But also: the value `t` after the AC load is stored; then reassigned. Good.

Let me create this candidate as c1.c and score.

Also, there's a subtlety: `(D_80126980[0]) = t;` where t is s32 and array u16. Target sh v0 — yes.

Let me write c1.c based on nopin.c, replacing the four statements. Let me view nopin.c to edit precisely.
