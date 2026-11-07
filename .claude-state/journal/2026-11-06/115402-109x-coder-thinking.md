---
ts: 2026-11-06T18:54:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uAFn53cw0eACw1j8dam0
---
g007's loop tail:
```
addu $3,$3,104   (v1 += 0x68)
addu $7,$7,104   (a7 += 0x68)
addu $6,$6,1
slt $2,$6,20
bne ...
addu $5,$5,104   (delay slot)
```
Target:
```
f08: addiu a3,a3,104   (a7 first!)
f0c: addiu v1,v1,104
f10: addiu a2,a2,1
f14: slti v0,a2,20
f18: bnez v0,e84
f1c: addiu a1,a1,104
```
So the target has a7's increment first, then v1's. g007 has v1 first (its source order). The score 2 = the a3 increment is one slot late (mine 39 vs target 38).

So: I need the source order a7-increment THEN v1-increment, but with the *allocation* flipped (a7=$7). The allocation flip came from the source statement order: g007's increments are (v1, a7, a6, a5).

Hmm, why did the increment order flip the allocation? Because the RTL pseudo numbering/order changed → the allocno numbering and the priorities/conflicts changed. Actually more likely: the *initial* RTL order determines the pseudo numbers (v1 vs a7), and cse/combine's canonicalization differs, changing which pseudo is "first" and gets $3.

Wait — in g007, a7=$7 and v1=$3 (target). The source order of the increments is v1 first. In g001 (a7 first), a7=$3 and v1=$7.

So the increment order determines the allocation. What if I use a source order that has a7's increment first but still flips the allocation? Maybe the *init* order matters too: g007 has the init a7 = symbol; v1 = a7 (same as w1). Hmm.

What determines the flip? Let me think: the initial RTL's statement order determines the pseudo creation order. In w1 (increments a7, v1, a6, a5), the RTL creates a7's pseudo (74) before v1's (76)? In g007 (increments v1, a7...), the RTL creates v1's pseudo first? Hmm, the pseudos are created by expand in statement order: `a7 = &D_8011FD10` creates a7's pseudo first, then `v1 = a7`. So a7's pseudo is always first (74). Then the loop statements: the increments don't create new pseudos.

But cse/combine later can swap the assignments (as we saw: the .lreg had insn 14 → 76 and 17 → 74, swapped). The swap depends on the RTL/cse behavior, which the statement order influences.

OK, empirical: let me generate variants with the increments in a7-first order BUT with other statements varied (init order, load, stores, return) to see if any flips the allocation while keeping the increment order. The space: init order (2) × increments order (24) × others. Let me sweep:
- increments order: all 24
- init order: (a7 = symbol; v1 = a7) vs (v1 = symbol; a7 = v1)
- return: a7 vs v1
- load: `v0 = v1; if (*v0 != 0)` vs `if (*v1 != 0)`

That's 24*2*2*2 = 192. Each ~1.5s → ~5 min. Let me instead target: I want the increments a7-first (to match the target's order). Let me sweep the other dimensions with the increments fixed to (a7, v1, a6, a5) and also (a7, v1, a5, a6)? The target's order is a3, v1, a2 (a6), a1 (a5). So the increments order is (a7, v1, a6, a5) = g001 (score 3, wrong allocation).

Hmm, so with the target's increment order, the allocation is wrong. With v1-first, the allocation is right but the order is wrong.

Maybe sched1 can be made to swap the two increments: the target's a7-first vs mine's v1-first. Since the increments are independent, sched1's order depends on the ready list. With the source v1-first, sched1 kept v1 first.

What if the increments are (v1, a7, ...) but I add a dependency making a7's increment come first? E.g., the a7 increment could be expressed as `a7 = v1 + 0x68`? Then it depends on v1 (old value) — but that changes semantics? a7 and v1 are equal, so `a7 = (unsigned short *)((char *)v1 + 0x68)` is equivalent. And it creates a dependency: a7's increment reads v1 (the old value) → it must be scheduled BEFORE v1's increment (which overwrites v1). That would force a7's increment first in the asm! 

But careful: `v1 = v1 + 0x68; a7 = v1 + 0x68;` — if the order is v1 first, a7 would use the NEW v1 (+0x68 again) → wrong. So the source order must be a7 = v1 + 0x68; v1 = v1 + 0x68; — that's the a7-first order with a dependency. But that's the g001 order (a7 first) which has the wrong allocation.

Hmm. Let me try: the increments in the source as (v1 = ...; a7 = v1_old + 0x68) — impossible.

What about: `a7 = (unsigned short *)((char *)v1 + 0x68); v1 = a7;`? Then a7's increment first, then v1 = a7 (a copy instead of v1 += 0x68). The target's v1 increment is `addiu v1,v1,104` — with the copy it'd be `move v1,a7` (a different insn!). Hmm, but after coalescing, a7 and v1 are the same register... no, they're different registers ($7 and $3).

Wait, if a7 and v1 are in different registers, `v1 = a7` is a `move v1,a7` — the target has `addiu v1,v1,104`. Different.

OK, what about the target's actual source order? The target's asm has a7's increment first. The source (from the orig.c) has a7 first then v1. So the target's source order is (a7, v1, a6, a5). And the target's allocation is a7=$7.

So the original compiler (with the pin) produced the target from the a7-first source. Lever-free, the a7-first source gives the wrong allocation (g001 = 3).

Hmm, but g007 (v1-first source) gives the right allocation and the wrong order.

Is there another statement-order variant that gives both? Let me sweep all 24 increment orders × the other dims and look for score 0. The score 2 cases are close: only the a3 increment's position. Maybe some other variant (e.g., init swapped, load changed) with a2-first increments yields 0.

Let me run a bigger sweep: 24 increment orders × 2 init orders × 2 return × 2 load forms = 192 candidates. ~5 min. Let me run it through tools/run.sh (it will produce 192 lines; fine).

Actually, let me think about the sched1 order: the increments are independent; sched1's backward pass schedules them in some order. The RTL order determines the ready-list insertion. To get a7's increment first in the asm with v1's source first... maybe sched1 reorders based on register pressure? The a3 increment is in the target's delay... no.

Let me just run the sweep.
