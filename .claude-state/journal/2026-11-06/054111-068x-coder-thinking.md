---
ts: 2026-11-06T12:41:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gdD392FHB9w9VvbKfxhz
---
Hmm, the printed "ready list at T-2: 124 (1) 127 (1), now 127 124" — the ", now" part prints the ready list. Confusing. Let me look at where "ready list at T-%d" is printed and the queue order semantics: maybe ready[] is a stack where the LAST element is scheduled first (i.e., ready[n_ready-1] is the head). In that case "124 127" with 127 last = 127 is scheduled first... and after moving 124 to the front (index 0), the list is "124 127" meaning 127 still scheduled first? That matches the output: 127 first, then 124.

Wait: if the head is the last element, then "now 127 124" (after moving 124 to front) means the last is 124 → 124 scheduled first. Ugh.

Let me settle it with the actual result: 127 (li) came first in the stream, then 124. Hmm, but hold on: is that the *stream* order or just the prev/next links which sched rewrites? The links say 127 then 124. So 127 was scheduled before 124.

Given "ready list at T-2: 124 (1) 127 (1), now 127 124" and "insn 124 has a greater potential hazard" — and the final order 127 then 124 — I conclude the ready list's HEAD is the LAST printed element... no wait: if 124 was moved to the front (index 0) and the head is index 0, then 124 would be first. Since 127 is first, the head must be the last element, and moving 124 to index 0 = the back. Then "now 127 124" has 127 at... ugh.

Whatever. Key insight: the potential_hazard of the insn decides. 124 (the sw of v0) has a greater potential hazard than 127 (li pseudo) → 124 is "preferred" for scheduling (front = earliest?).

Since 127 ended up first in the stream, maybe the hazard selection picks the *last* to schedule first...

Let me instead test empirically: what changes the order? The insn's potential_hazard depends on its operands (memory refs, registers). For the store, the hazard is computed from its memory access; for the li (constant into a pseudo) hazard is low.

Honestly, a more productive approach: since the pin gives v0 and the dependency (WAR) then forces the correct order, maybe I can create an equivalent dependency without a pin by making `ret`'s value flow through a value that the call also writes... 

IDEA: what if we write the arm as:
```
unkD8 = func_80143994(param_1, 0x3000);
ret = unkD8 ? 7 : 7;   // no, fake
```
No.

IDEA: what if `ret = 7;` were `ret = (s32)(0x3000 + 7) - 0x3000;`? no.

Let me look at this from a totally different angle: maybe the function's arms should not use a shared `ret` at all. What if the C were:

```
if (unk70 == 0x28) {
    ...
    unkD8 = call(...);
    return 7;      /* directly */
}
```
Then `return 7` → `v0 = 7` (a hard-reg set!) → the WAR dependency exists → correct order! But then the shared STORE (`sh v0,2(s1)`) would be duplicated per arm — the target has a single store. Unless cross-jumping merges the arms' tails: each arm would be `...; li v0,7; sh v0,2(s1); j epilogue` — 6 arms with identical tails (store + return). jump2's cross-jump could merge `sh v0,2(s1); j epilogue` into one block! But the constants differ, so only the store+return tail would merge. That's exactly what the target has: `j 1e38` (store) then the return.

Hmm! But in the target each arm does `j 1e38` where 1e38 = `sh v0,2(s1)` and the return epilogue at 1e3c. And the early returns `j 1e3c` (skipping the store). That's consistent with `return N` per arm + cross-jump merging the identical tails!

But wait: the early returns in the source are `return ret;` (uninitialized) — with the "return N per arm" theory, the early returns would be `return <something>` too, and their tails (j epilogue) merged with... the arms' tails are store+return, the early returns are return only.

Hmm, but the early returns in the target have `j 1e3c` = the return label directly, no store.

So if the C were:
```
if (cond) { call; return ???; }
```
What would return nothing? Hmm.

Let's test the "direct return per arm" theory: rewrite the arms to `unk2 = N; return N;`? No — that would store the constant directly (sh with a constant, no register), and the target's store uses v0.

Alternative: `return ret` where ret is assigned in the arm — that's what we have.

OK here's a cleaner idea based on the cross-jump theory: what if the C is:

```
if (unk70 == 0x28) {
    ...
    ret = 7;
    goto STORE;
}
```
and STORE:
```
STORE:
    unk2 = ret;
    return ret;
```
The target's arms do `j 1e38` = jump to the store. So `goto STORE` remains.

So the C is as we have it. The only difference is the pin.

Hmm, let me revisit: is it possible that the target's ret-in-v0 comes not from a pin but from `ret` being *returned* at multiple points so that gcc gives it v0 by copy preference? The copy preferences: `hard_reg_copy_preferences[ret]` gets v0 from `set (reg:SI 2) (reg:SI 73)` (the return copy). But `regs_someone_prefers` and pass-0 logic...

The conflict `73 conflicts: ... 2 3 ...` is fatal regardless of preferences: ret conflicts with v0 because of the sched order. If the order were store-then-li, ret wouldn't conflict with v0 and would take v0 (given a copy preference to v0).

So the ONLY problem is sched1's order in the arms. If I can flip that order in a lever-free way, everything falls into place.

How to flip? The hazard selection compares potential_hazard(124) vs potential_hazard(127). potential_hazard is about function units / memory refs. Let me read potential_hazard.
