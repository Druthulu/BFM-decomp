---
ts: 2026-11-06T09:26:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3kEuBuouIVclsyCI2sGl
---
So K2+K3 removed, K1 kept → only the fc/limit reg swap remains (v1->a1 x4, a1->v1 x3). That's the K3 effect: fc=v1, limit=a1 vs target fc=a1, limit=v1.

Interesting: with K2 present but K3 removed (w3), the swap was v1->a1 x4, a1->a0 x3, a0->v1 x3. With both K2,K3 removed, the swap is simpler: fc v1 vs a1; limit a1 vs v1 (just a swap!).

So we need to swap fc and limit's registers. That's a local-alloc priority question. fc has uses: move (iVar7=fc), slt1, slt2 = 3 uses. limit: load at 75, reload at 83, slt1, slt2... The pseudo for the first limit load is used at slt1; the reload at 83 used at slt2 and the clamp comparison.

Target: fc=a1, limit(a0)=a0 (first load), reload v1.
Mine: fc=v1, limit(a1)=a1, reload a0.

A pure swap. Local-alloc assigns regs in pseudo order/priority. How to make fc get a1? Increase fc's priority or decrease the limit pseudo's.

The limit load's pseudo (call it L1) is used in `if (fc < *(s16*)(param_1+0xe))` — one use. fc used 3 times. Yet L1 gets a1 and fc gets v1.

Hmm, why? Local-alloc's qty_compare uses refs/live_length. fc: 3 refs over a long live range (from load to the second comparison, across the whole block). L1: 1 ref, short range. Priority = refs * 10000 / live_length roughly. So fc's long live range lowers its priority! L1's short range gives high priority → allocated first → gets a1 (or the reg it prefers).

Target: fc=a1. Maybe the real C's fc has a *shorter* live range or higher refs. The keepalive extended fc's live range (which would lower priority...) hmm, but it also added a ref.

Alternatively: the real C might load fc *later* (just before the comparison), shortening its live range → higher priority → a1. Currently `fc = *(s16*)(param_1 + 0xc);` is right after the &0x10 test. Target insn 74 `lh a1,12(a2)` — after the &0x10 store (73). So the load is where it is.

What if fc's live range is shortened by moving the iVar7 move later? `iVar7 = fc + zr;` is right after the load. Target has `move v1,a1` at 79 (after the slt at 77). So iVar7 = fc happens after the first comparison in the target! Our source has iVar7 = fc + zr before the if. But the compiler schedules the move later (into the branch's delay slot at 79). Fine.

Idea: restructure the fc block so fc is used differently: e.g., 
```
if (fc < lim) { t = fc + 0x400; ... } else if (lim < fc) { t = fc - 0x400; ... }
```
The current source computes iVar7 = fc + zr *before* the if, then t = iVar7 ± 0x400. If instead we write t = fc ± 0x400 directly (dropping iVar7/zr), the target's `move v1,a1` would disappear → different. The zr pin is needed for the copy.

What if iVar7 is assigned *inside* each branch? e.g.:
```
if (fc < lim) { iVar7 = fc + zr; int t = iVar7 + 0x400; ... }
else if (lim < fc) { iVar7 = fc + zr; int t = iVar7 - 0x400; ... }
```
Then iVar7's live range is short, fc's... fc still used in both conditions. Might change allocation. Worth a try.

Another: compute `iVar7 = fc + zr;` *after* the first comparison but before the second? Can't.

Another idea: declare fc as `s16` (x4 gave 14 — worse with all removed; but try with K1 kept).

Let me try a batch of ~8 more:
y1: K1 kept, iVar7 assigned inside each branch.
y2: K1 kept, fc plain s16.
y3: K1 kept, limit load into a variable `s16 lim`? (would change insns — skip)
y4: K1 kept, `if (fc < *(s16*)(param_1+0xe))` written as `if (*(s16*)(param_1+0xe) > fc)`.
y5: K1 kept, fc load moved to just before the if (already).
y6: all removed, iVar7 inside branches.
y7: K1 kept, iVar7 = fc + zr moved after the load but fc declared before? 
y8: K1 kept, `int t` hoisted to block top (decl order).

Let me generate and score.
