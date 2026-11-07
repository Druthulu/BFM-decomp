---
ts: 2026-11-06T03:46:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZH3tzoBPiTUp2VUqPlOF
---
Mine: B8 load (v0), then AC load (a1), then store B8 (sh v0), then C4 load, then... The AC store D_8012697C is where? Let me see further. Mine has reordered so AC load into a1 and its store later.

Target: AC load v0, store AC; B8 load v0, store B8.

The issue: sched1 hoists B8 load above AC load/store. To keep order, need dependency.

Idea: compute the AC load first into a temp and store it, and make the B8 index depend... no.

Alternative real-C approach: use a single temp variable reused:
```
t = D_801864AC[idx];
D_8012697C = t;
(D_80126980[0]) = D_801864B8[idx];
```
Doesn't add dependency.

Hmm, what about using the same index variable but re-derived: `idx` is s0. The loads are independent.

Could the target's order actually be reproducible by changing statement order in C to match? No—mine already has AC store before B8 store in source; scheduler moved it.

What about the barrier being "memory" clobber: it prevents reordering of memory operations across it. Equivalent real C: a store to a global then a load from a different global with aliasing concerns... The compiler can't prove non-aliasing? All these are extern symbols with known addresses; cse/sched can reorder.

Hmm, what about making the second statement's index a function of the first store's value in a way that is real, not identity? E.g., the AC value is stored and then B8 load uses idx; if idx were derived from D_8012697C? That changes semantics unless... Actually we could load into `idx2` and use it.

Wait — maybe the real fix: the value `D_801864AC[idx]` loaded into a temp `t` and then stored. If we write:
```
t = D_801864AC[idx];
D_8012697C = t;
```
then `t` is dead after store. B8 load independent.

Alternatively maybe the barrier's real purpose is to keep the store order because of "volatile"-like semantics. Is there a real C way? We could declare the globals `volatile`. But that changes codegen massively (volatile forces order). But the target's instruction stream is not volatile codegen. Hmm, but a volatile store of D_8012697C then a volatile load of B8... volatile loads/stores are not reordered relative to each other. That could produce exactly target order! But volatile would also prevent other optimizations in those statements only. Let me think: declaring `extern volatile s32 D_8012697C;` locally in the function (block-scope extern with volatile) — the type must match declaration? `extern volatile s32 D_8012697C;` conflicts with the TU-level declaration if it's non-volatile. If no TU-level declaration, block-scope extern is fine. Are these declared at TU scope? Probably not (they're in-function externs). Adding volatile to block-scope extern changes the lvalue type. This is a real C semantic (not a lever). But does it reproduce? Volatile store and volatile load: sched can't move loads across volatile stores? Actually volatile ops are treated as having side effects; CSE doesn't cross them. sched1 won't reorder volatile memory ops relative to each other? They're `volatile` MEMs, unspec_volatile. Let me consider — this might produce exactly the target order and is arguably real C.

But is "volatile" a lever? The kinds list is barrier/launder/pin. Volatile isn't in that list, but "no new lever of any kind" — hmm, that's concerning. Declaring a global volatile to force ordering is essentially a compiler-directive trick, similar to a barrier. It could be considered a lever of a new kind. Risky.

Let me think about what real C would give target order. Maybe the function originally was:
```
D_8012697C = D_801864AC[idx];
(D_80126980[0]) = D_801864B8[idx];
t = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = t;
```
Scheduler hoists loads. In the target (compiled from the original source), sched1 did NOT hoist. Why? Possibly because in the original source, the values were used via a different structure, e.g. a single variable reused, or the index was a `s32` local with a store.

Hmm. What if we assign to `idx` itself? Like `idx = D_801864AC[idx];` then `D_8012697C = idx;`? Then idx is reused... then B8 uses idx which is now the loaded value, not original index. No.

What if we make the loads use distinct index temps computed with dependencies? E.g.:
```
t = D_801864AC[idx];
D_8012697C = t;
idx2 = idx;   // copy
(D_80126980[0]) = D_801864B8[idx2];
```
No dependency.

Consider that the scheduler (sched1) is a list scheduler with dependencies. Loads from different globals have no dependency. So hoisting is natural. In target, the order suggests the barrier or something created a dependency. So the original source must have had a real dependency. What real dependency could exist? The D_8012697C store is a store to global; B8 load from another global. If both are `extern` arrays, alias analysis: all are `s32` globals, so they can alias? In GCC 2.7.2, memory alias analysis is basic (alias.c); a store to D_8012697C could alias a load from D_801864B8? If they can't be proven distinct, the scheduler would keep the order! But in the target they DID keep order while lever-free mine didn't... Hmm wait, mine has the SAME declarations. Both are `extern s32 D_8012697C;` and `extern s32 D_801864AC[];`. So alias behavior identical. Yet mine reordered. So why did target not reorder? Because of the barrier in target's build! Wait no — the target in build/ is built from the CURRENT tree (which includes the barriers!). Hold on.

Critical: "That target is the tree's own bytes — proven by the SHA1 check, carrying the candidates' ..." Hmm. Let me re-read: "the function's instructions are read out of that scratch object... run's baseline object under build/. That target is the tree's own bytes". So the target is from build/ which was built from the current src. If current src has barriers, then build's object = barrier version = byte-exact ROM. But the target should be the ROM ground truth, which equals the barrier version (score 0). So the target instruction stream includes whatever the barrier did. So indeed target has the barrier's effect, and the ROM is identical to the barrier build. So the ROM itself (the original game code) has that order, and we need plain C to reproduce it.

OK so in the real ROM, the original compiler (same gcc 2.7.2) produced this order without any barrier. So the original C had something creating the dependency/order. So there IS a plain-C formulation.

Since both loads are from arrays and store to a global: hmm, alias: D_801864AC and D_801864B8 are arrays; load from AC, store to D_8012697C, load from B8. If the compiler thinks D_8012697C may alias B8, it would keep the load after the store. But it doesn't, as mine shows.

What if the original wrote the value through a pointer? E.g., `*(s32*)&D_8012697C = ...`. Same.

What if the source computed `D_8012697C = D_801864AC[idx];` and then used `D_8012697C` in the next expression's index? Not semantically.

Wait. Maybe the target order arises from the loads being the same expression? `D_801864AC[idx]` and `D_801864B8[idx]` differ.

Alternatively: the difference is sched1's birth/sink heuristics. In target, the B8 load is NOT hoisted above the AC load. In mine it is. The reason could be register pressure: in target, `s0` (idx*4) is used; the AC load goes to v0; store; then B8 load to v0. In mine, B8 load goes to v0, AC load to a1 (because v0 is occupied by B8's value across the AC store). That's the difference: in mine, AC load can't use v0 because v0 holds B8's value... Actually the scheduler hoisted B8 load because its value is needed later. If we make AC's store happen before B8's load is even born, sched1 would keep it.

How does sched1 decide? It schedules basic blocks; the order in the RTL is source order. It hoists insns based on dependencies/priority. Both loads are independent, so it may pick either. The target picks AC first, mine picks B8 first. This is a priority tie-break. To flip, change the priority: e.g., make the B8 load have a longer dependency chain, or make its result used later, or introduce a temp.

Actually, note in target, the AC value is loaded into v0 and stored; then B8 value into v0 and stored. In mine, B8 into v0, AC into a1. The reason B8 went first may be that sched1 sees B8's store (sh) earlier? No, source order: AC store then B8 store.

Maybe simply reordering the C statements: put `(D_80126980[0]) = D_801864B8[idx];` BEFORE `D_8012697C = D_801864AC[idx];` in source? Then sched1 would... produce B8 first, then AC — but target has AC first. Hmm, that's the opposite.

Wait maybe in mine the RTL order is already swapped? Let me check without scheduling (-fno-schedule-insns?). The pre-sched order is source order. Mine's source: AC store first. So sched1 swapped. To keep source order, need dependency.

Idea: introduce a real dependency through a temp: 
```
t = D_801864AC[idx];
D_8012697C = t;
(D_80126980[0]) = D_801864B8[idx];
```
Still independent.

Idea: use the stored value as part of B8's index? No.

Hmm, maybe the real original source was different in a way that the AC value and B8 value share a register/chain. E.g.:
```
t = D_801864AC[idx];
D_8012697C = t;
t = D_801864B8[idx];
(D_80126980[0]) = t;
```
With a single temp `t` reused! Then t's live range: after the first store, t is reassigned. Scheduler: the second load writes t, which is the same pseudo? No, after cse/regalloc each load has its own pseudo; t is SSA-ish. But at RTL level, t is a single pseudo register; the second load writes the same pseudo, which is an anti-dependency with the first store reading t. That would force the first store before the second load! And the second load's output would be the same register (v0 maybe), giving target's v0 reuse. Yes! That's likely the original: a single temp reused.

But careful: writing `t = D_801864B8[idx];` after the store of t means the second load writes t after t is read by the store — a WAR dependency. sched1 respects anti-dependencies. That should keep the store before the load.

Currently source has `t = D_801864C4[idx];` later and `D_801269E8 = t;`. The B8 store is direct `(D_80126980[0]) = D_801864B8[idx];`. So maybe restructure:
```
t = D_801864AC[idx];
D_8012697C = t;
t = D_801864B8[idx];
(D_80126980[0]) = t;
t = D_801864C4[idx];
D_801269EA = 0;
D_801269E8 = t;
```
That's a plausible original. Then the second barrier (after D_801269E8 = t) exists to keep D_801A1274 load after. Hmm, actually the second barrier is after `D_801269E8 = t;` and before `D_801A1274 = D_801864D0[idx];`. Target shows... let me look at the rest of target. Let me see target lines after 2a40.

Let me get the full target disassembly.
