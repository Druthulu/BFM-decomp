---
ts: 2026-11-06T10:53:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oPGU9p7wR5tS5P1o7WSq
---
v_bar2 = 10: the ORDER is now right (lw, lui, addiu, sw, ori, sw) but the registers are swapped (t v1, a v0). So the barrier fixes the ordering, and the pin fixes the register. So we need a real-C replacement for BOTH.

So: the barrier → do-while (which splits the EBB and gives the order in v_addr3/v_addr4). The pin → need t to get v0.

From v_addr4: t global (block1) got v0. And the order was wrong (store sank). With a barrier... no, barrier not allowed.

Hmm, what if I use BOTH a do-while for the load (to fix the ordering, v_addr4-like) AND something to fix the store sink? In v_addr4 the store sinks; in v_addr5 the regs swap.

Let me try: v_addr4 but with the do-while wrapping the load, and the address+store in a do-while too, but the RMW... hmm.

Wait — actually v_bar2 shows that with the barrier, the *whole* schedule is right and only the regs are wrong. What if I keep the do-while structure of v_addr4 (t global → v0 ✓) and fix the store order by adding... the store sank in v_addr4. What made the store sink there? The scheduler had the ori ready.

In v_bar2, the barrier is before the load, so the load, store, ori are in one block (same as v_addr4's block2 minus the load). Hmm.

Let me look at v_addr4's actual structure: block1 = [lw t] (do-while), block2 = [a=addr, sw88, ori, sw196, ...]. In block2 the scheduler chose ori/sw before sw88.

In v_bar2: block = [lw, a=addr, sw88, ori, sw196, ...] — one block. The scheduler chose sw88 before ori.

So the presence of the load in the block changes the order! Because the load's result t is needed by the ori; the scheduler issues the load first, then... the ori depends on the load. With the load in the same block, sched1 knows the ori must wait for the load; it fills the gap with the address and the store. Without the load in the block (v_addr4), the ori is ready immediately and goes first.

So: I need the load AND the address AND the store AND the ori in the SAME block, with the load first. That's v_addr3 (all in one do-while): but there the regs were right (t v0!) and the order was lui, addiu, lw, sw... because sched1 kept the source order (address first).

Wait, v_addr3's source was `do { a = ...; t = ...; } while(0)` — a first. The scheduler kept that order. What if the source is `do { t = ...; a = ...; } while(0)` (v_addr) — order lw, lui, addiu ✓ but regs swapped.

Hmm! v_addr3 = regs right, order wrong; v_addr = order right, regs wrong. The difference is purely the source order of the two statements inside the do-while, which affects BOTH the schedule and the qty birth order.

In v_addr3 (a first, t second): local-alloc births: a first, t second → t (later birth, shorter range) wins v0. ✓
Schedule: sched1 keeps a-then-t (lui, addiu, lw). ✗ (target: lw first)

So I need t to be born after a but scheduled before a. sched1 uses source order for equal priorities. Can I give the load a higher priority than the address computation? The load's priority = 1 + max over dependents. The load's dependent is the ori → sw. The address's dependent is the store. Both similar.

Hmm, what if the address computation is made to depend on something (so it's not ready at the start)? For instance, compute the address using a value that's available only after... no.

What if I make the load "more urgent" by making its result feed something with a longer chain? Not without changing semantics.

Alternatively, make the address's birth index later but its *source position* later too (v_addr) and fix the qty priority by another means: make a's range longer. a's range: birth at the address, death at the store. t's: birth at the load, death at the ori. In the target order, the store comes before the ori, so a's range is shorter. local-alloc uses the RTL order (source), not the scheduled order! So if the source is t-then-a-then-store-then-ori, then a's birth is after t's, and a's death (store) is before t's death (ori). a's range = store_pos - addr_pos; t's = ori_pos - load_pos. a's is shorter → a wins v0.

To flip, we need t's range shorter in RTL terms. E.g., if the RTL order were: a=addr; t=load; store; ori — then t's birth is after a's, and t's death (ori) after the store. t's range = ori - load; a's = store - addr. If the load is right after the address and the store right after, both ranges are ~2. Tie → sorted by qty number → lower qty number wins (allocated first gets the better reg?). qty_compare_1 tie-break returns *q1 - *q2 (ascending), so the lower qty number comes first → allocated first → gets v0. The lower qty number = earlier birth? qty numbers are assigned at birth. So t born after a has a higher qty number → sorted later → gets v1. Hmm, but v_addr3 gave t v0.

Wait, in v_addr3 the source is a then t: a born first (lower qty), t born second (higher qty). qty_compare ties → sorted ascending → a first → a should get v0. But t got v0! So the tie-break isn't reached; the priorities differ: t's range is shorter.

In v_addr3: a born at lui/addiu, dies at sw88; t born at lw, dies at ori. RTL order: a, t, sw88, ori. a's range = 3 (birth 0 → death 2); t's range = 3 (birth 1 → death 3). Equal length! Hmm, then tie → a (lower qty) → v0. But observed t v0.

Unless death is computed as the index of the last insn +1 etc. Let me not over-model.

Empirically: a-then-t source → t gets v0 (good) but the schedule is a-then-t (bad). t-then-a source → order good, t v1.

What if the source is: `t = load;` then `a = addr;` but with the *store* between them in source? No.

What if I split the do-while: `do { a = addr; } while(0); t = load; ...`? Then a is in block1 (local), t in block2. Regs: t global → v0 (v_addr4-like). Schedule: lui, addiu (block1), lw (block2) — wrong order (address first).

The target order is lw first. So the load must be first in the block. Then a's birth is after the load → a has the shorter range → a wins v0. UNLESS t is global and a is local (different blocks): v_addr4 gives t v0 but then the store sinks because the load is in a previous block.

So the fundamental conflict: to get the load first AND t v0, t must be in the same block as a but have priority. The only way: t's range shorter or more refs.

More refs: refs=4 → floor_log2(4)=2 → doubles priority. How to get t 4 refs legitimately? In RTL, `t = load` (1 set), `t | 2` (1 use). To get 4, we'd need t used 3 times. Hmm.

What about making the ori write back to t (`t = t | 2`) and then store t: that's `t = t|2; unkC4 = t;` → refs: load set (1), ori use (1), ori set (1), store use (1) = 4 refs! I tested v_ref3 with that but in the v_addr4 structure (t global). Let me test it in the v_addr structure (both in one do-while, load first):

```
do { t = unkC4; a = (s32)&D_801907C4; } while(0);
unk58 = a;
t = t | 0x2;
unkC4 = t;
```
If t has 4 refs and a 2, t's priority = floor_log2(4)*4 = 2*4 = 8 vs a 2*4 = 8... wait floor_log2(2)=1 → 1*2=2; times size 4 → 8 for a. t: floor_log2(4)=2 → 2*4=8, times size 4 = 32. So t's priority is 4x a's → t wins v0!

Let me test this.
