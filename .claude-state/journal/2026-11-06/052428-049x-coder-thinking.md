---
ts: 2026-11-06T12:24:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qtrMuckUNvYscItlUpks
---
Mine: 141-142 build 0x64808080 (lui/ori), then 143 sh y. Target: 141 sh y, then 142-143 lui/ori.

So in mine the lui/ori pair (for the q-0x10 store constant) got hoisted above the y store; in target the y store comes first.

With the memory barrier, the lui/ori couldn't move above the barrier... wait, the barrier is BEFORE the 0x4000000 store, i.e. after the y store. So the barrier is between `sh y` and the rest. The lui/ori at 142-143 are pure register ops — a memory barrier shouldn't stop those... unless in gcc 2.7.2, an asm with a memory clobber is a scheduling barrier for everything (it has a "memory" clobber which makes it depend on all memory; the pure lui/ori could still move).

Hmm, but empirically removing it moved the lui/ori pair above the sh.

Real-C fix: reorder the C statements so the store of 0x64808080 comes later, or make the y store's value... The target order suggests the C order in target might be: y store, then 0x4000000, then 0x78, then 0x64808080, then 0x4056...

Actually with the barrier present, the emitted order 141 (sh y), 142-143 (lui/ori 0x64808080), 144-145 (sw 0x4000000), 146-147 (sb 0x78), 148-149 (li + sw 0x64808080)... 

Hmm interesting: the lui/ori at 142-143 compute v1 = 0x64808080 early but store it at 149. So the constant build was hoisted but the store stayed late. In mine, the lui/ori pair moved above the y store.

Fix: force the constant build to happen after the y store. Options:
- Reorder C: move `*((u32 *)(q - 0x10)) = 0x64808080;` before `*((u32 *)ot) = 0x4000000;`? That changes the store order (target has sw 0x4000000 at 145 before sw v1 at 149).
- Make the y store earlier in C: it already is right before.

What if I move the y store to be the LAST statement of the group? Then it'd be at the end. No.

Alternative: make the lui/ori build depend on something produced after the y store. E.g. express 0x64808080 via a variable computed later... that's contrived.

Better: reorder the C so that the statement order matches the target's insn order:
target insn order: sb q[-7] (136), lhu+addiu (137-140), sh y (141), lui/ori (142-143), sw 0x4000000 (144-145), sb q[-8] (146-147), li+sw 0x64808080 (148-149).

So the C statement order that yields this: 
```
*(s16 *)(q - 10) = y;
*((u32 *)ot) = 0x4000000;
q[-8] = 0x78;
*((u32 *)(q - 0x10)) = 0x64808080;
...
```
That's exactly the current C order! And mine (without the barrier) schedules the constant build 2 slots early.

So the question: what real-C change makes sched1 not hoist the lui/ori? The lui/ori feed the sw at 149. Sched1 hoists them because they're ready early and have high priority (chain to the end).

What if the constant 0x64808080 is stored via a variable computed just before, e.g. `u32 c64 = 0x64808080;` declared and assigned where? If assigned right at the store, sched1 could still hoist the move. Hmm, but if the value is a pseudo set immediately before the store, sched1 might keep it.

Let me try: replace `*((u32 *)(q - 0x10)) = 0x64808080;` with a temp:
```
u32 c64 = 0x64808080;
*((u32 *)(q - 0x10)) = c64;
```
placed at the same spot. gcc would fold the constant into the store (li/lui ori + sw) — same insns, but the pseudo's birth may be pinned near the store by sched1... it's the same insn sequence though: lui/ori/sw. Sched1 could still hoist.

Alternative: reorder the two sw's in C: put `*((u32 *)(q - 0x10)) = 0x64808080;` AFTER `*(s16 *)(q - 6) = 0x4056;`? Then the store order changes (target has sw v1 at 149 which is right after li 16470 at 148 and before sh 0x4056 at 150). Hmm! Target: 148 li v0,16470 (0x4056), 149 sw v1,-14(a1) (0x64808080), 150 sh v0,-4(a1) (0x4056 → q-6).

So in target, the 0x64808080 store lands between the 0x4056 li and its sh. That's just scheduling.

Let me try a few statement orders around these 4 stores and see if any gives 0:
- o1: current order (b0) = 2.
- o2: swap `*((u32 *)ot) = 0x4000000;` and `q[-8] = 0x78;`
- o3: move `*((u32 *)(q - 0x10)) = 0x64808080;` after `*(s16 *)(q - 6) = 0x4056;`
- o4: move the 0x64808080 store to just after the y store.
- o5: use a temp for the constant.

Let me also handle the keepalive (19) — the register rotation. Ideas: the pb address pseudo needs priority. Options:
- initialize pb at declaration (move `pb = (u16 *)&D_800B9A02;` to the decl).
- declare pb earlier (before p).
- use `extern u16 D_800B9A02;` differently.

Actually! Look: the address pseudo is `(u16 *)&D_800B9A02` = a constant address (lui/addiu pair). Two variables pb and pb2 both assigned it. In the target, the SAME register a2 is used at 59 and 73 for `lhu a0,0(a2)`. Since it's a constant address, gcc probably keeps the value in a register (not rematerialized) because it's a "constant" pseudo... 

Hmm, actually gcc rematerializes constant addresses (lui/addiu) from the constant pool. The `lui a2,0x0; addiu a2,a2,0` at 50-51 in target — that's the address built once and kept in a2.

For the pseudo to win a2 over the competitors, it needs priority. With the 5 asm refs it wins.

Real-C: give the address pseudo more real refs. How? `D_800AE7BC[*pb]` — each `*pb` is a load (lhu). If I write `pb[0]` more times, each is a load. cse might merge within a block.

Alternatively reduce the OTHER pseudos' priority. The rotation was t0→a2, a2→a3, a3→t0. Which are these? Let me look at the full function's target assembly start to identify the 3 pseudos: j (0), k (=m), and the address.

Hmm — `move t0,zero` (j=0) at 102, `move a3,v1` (k=m) at 103, `move t2,a2` at 105 — that's saving a2 into t2? Then `lui a2,0xff; ori a2,a2,0xffff` (m24 = 0xFFFFFF) at 106-107. So a2 is REUSED for m24 after being copied to t2! So the address pseudo is in a2, copied to t2 (for later use at 86/89), and then a2 holds m24.

In mine: `move a3,zero` (j), `move a2,v1` (k), `move t2,t0` (address saved), `lui t0,0xff; ori t0` (m24 in t0).

So mine: address in t0 (saved to t2), m24 in t0 after; k in a2; j in a3.
Target: address in a2 (saved to t2), m24 in a2 after; k in a3; j in t0.

So the difference: which register k gets (a3 vs a2) and which the address gets (a2 vs t0).

k = m = D_8011511A (a loaded value), used a lot in the loop (D_80115140[k], k*2). The address pseudo (const) is used 5 times.

So in mine, k wins a2 and the address gets t0; target gives a2 to the address and k to a3.

To fix: raise the address pseudo's priority or lower k's. k's refs: `k = m;` then in the loop `D_80115140[k]`, `k*2` (k2), and `D_80115140[k]` again in the else branch — few refs but it lives across the whole loop (long live range) → high priority.

The address pseudo's live range also spans the loop.

With 5 extra asm refs, the address wins.

Real-C: can I add real uses of the address pseudo that don't add instructions? Hmm: `D_800AE7BC[*pb].ot[2]` appears at 36, 37, 38 (three times) — the compiler loads *pb each time? In target, `lhu a0,0(a2)` at 59 then `lhu v1,0(a2)` at 73 — two loads (the first region and the loop region).

What about making `pb` an argument-driven... no.

Alternative: reduce k's live range: k = m is set before the loop and used inside. If instead I use `m` directly in the loop (drop k), then k disappears! But target has `move a3,v1` (k = m) — a copy exists in the target. So k must remain a separate pseudo.

Hmm, but maybe I can make k die earlier: `s32 k2 = k * 2;` inside the else.

What about the `eight` variable (s32 eight = 8) — irrelevant.

Another idea: give the address pseudo a real second def/use: e.g. `pb = (u16 *)&D_800B9A02;` appears once. If I write `pb2 = pb;` (a copy) instead of re-taking the address... that's what the source has (pb2 = (u16*)&D_800B9A02). A copy `pb2 = pb;` might coalesce with pb and add refs? Coalescing merges them, reducing refs.

OK, let me try the simplest experiments:
- p1: initialize pb at its declaration (`u16 *pb = (u16 *)&D_800B9A02;` and remove the assignment line) — moves the birth earlier.
- p2: same for pb2.
- p3: both.
- p4: declare pb before `u16 *p;`.
- p5: declare pb2 next to pb at the top.

Let me batch these.

Note: for the ORDER (barrier) fix, I'll separately test o-variants on b0.

Let me do the keepalive ones first since they're bigger.
