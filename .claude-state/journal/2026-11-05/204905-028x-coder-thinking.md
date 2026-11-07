---
ts: 2026-11-06T03:49:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Vu6lL1xx7nQsf6uBKNzu
---
Mine order: C4 lw, E8 sh, D0 lw, EA sh zero, A1274 sw. Target: C4 lw, EA sh zero, E8 sh v0, D0 lw, A1274 sw.

So the zero store got sunk after the D0 load. Need to keep the EA=0 store adjacent to the C4 load, before E8.

Idea: make the E8 store's value depend on the EA store. Since EA is a global store of 0 and E8 = t, what if the original wrote the zero through the same temp chain? E.g.:
```
t = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = t;
```
The scheduler sinks the zero store. To prevent sinking, maybe give the zero store a dependency on the load: `D_801269EA = D_801864C4[idx] - t;`? That reuses the loaded value (t) minus itself = 0, but compiler folds x-x? GCC 2.7.2 combine might not fold a load minus itself since load is a memory read (may be volatile? no, but it can't fold because the load could change? Actually a load minus itself: if the load is not volatile, the two reads are same value only if no intervening store; combine may not fold). But that adds an extra load (target has only one lw C4). Unless we use t: `D_801269EA = t - t;` → constant 0 after combine, and the dependency disappears. So no.

What about `D_801269EA = t & 0;`? folds to 0.

Hmm.

Alternatively reorder the C statements to help: put `D_801269EA = 0;` BEFORE `t = D_801864C4[idx];`. Then RTL order: sh zero, lw C4, sh E8. Target wants lw C4 first. Scheduler might sink the sh zero after the load? That's what happens anyway. Hmm, if source order is sh zero first, sched1 might keep it (it's a store, can't move across loads? Actually stores vs loads: sched respects alias; a store to EA and load from C4 — may alias? it didn't keep). Actually if source order has store before load, sched1 might move the load up before the store if it thinks no alias. Then target order! Let's test: source: `D_801269EA = 0; t = D_801864C4[idx]; D_801269E8 = t;`. Target: lw C4, sh zero, sh E8. Scheduler would need to sink the zero store below the load and keep it before E8. Plausible: it hoists the load above the store (no alias) and the zero store then sits after the load, before E8 store. Let's try.

Actually wait: does sched1 hoist loads above stores when it can't prove no alias? In GCC 2.7.2, sched_analyze handles memory: for a store, it adds deps to all prior loads of possibly-aliasing memory. If alias analysis says the globals don't alias, no dep. They're distinct symbols, so no alias. So yes, a load can move above a store.

Let me test variant c2: EA zero before the C4 load.

Actually there might be another subtlety: in target, `sh zero,EA` occurs between `lw v0,C4` and `sh v0,E8`. If C source is `EA=0; t=C4[idx]; E8=t;`, the scheduler would likely produce lw; sh zero; sh E8? The load is hoisted; the zero store stays after the load but before E8? The zero store has no dependency on the load, so its position depends on priority. Hmm.

Let me just try several variants quickly with sc.sh. Variants:
- c2: `D_801269EA = 0;` before `t = D_801864C4[idx];`
- c3: `D_801269EA = 0;` then `t = ...; D_801269E8 = t;` but maybe use `(s16)0`.
- c4: write zero via `D_801269EA = t, t = D_801864C4[idx];`? no.

Let me create c2 and c3.

Actually another idea: the store to EA=0 might have been originally `D_801269EA = 0;` before the *previous* statement? Let me consider target ordering globally: target has each load immediately followed by its stores. The zero store is between. Perhaps original source:
```
D_8012697C = D_801864AC[idx];
D_80126980[0] = D_801864B8[idx];
D_801269EA = 0;
t = D_801864C4[idx];
D_801269E8 = t;
D_801A1274 = D_801864D0[idx];
```
With a single temp t reused only for the E8 one? But then the AC/B8 loads hoist (baseline problem). Our c1 fixed that with t reuse. Keep t reuse for all, and move the zero store before the C4 load:
```
t = D_801864AC[idx]; D_8012697C = t;
t = D_801864B8[idx]; D_80126980[0] = t;
D_801269EA = 0;
t = D_801864C4[idx]; D_801269E8 = t;
t = D_801864D0[idx]; D_801A1274 = t;
```
Let's try.

Hmm, but wait: `D_801269EA = 0;` before `t = ...` — then t's previous def (from B8) is still live? t was stored; now zero store; then t reassigned. Fine.

Let me create c2.
