---
ts: 2026-11-06T14:41:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tiivFI1exCATtH7ui2uW
---
All still 4 or worse. q9 (reorder OR chain) gave 8 (ORDER) — the OR order matters. q15 gave 6.

So the best lever-free score is 4 (ORDER), with the la position being the only difference.

I've now done: c1, v1-v9 (9), nopin, p1-p4 (4), q1-q15 (15) = 30 scored tries. Plus the baseline. So I've reached ≥30 tries and ~35 minutes on this item.

Let me record a WALL with best=4. Wall tag: `sched1-birth-order`? The mechanism is the keepalive's empty asm pinning the a1 la early; without it, the la sinks to the call. Let me use a tag from walls.txt. The closest is `sched1-birth-order` (sched1 orders insn births opposite to source). But here it's more "asm barrier pins an la; without it sched sinks it". Let me check walls.txt for a better tag. The tags include `sched1-load-order`, `sched1-birth-order`, `sched1-load-delay-fill`. 

Hmm, the mechanism: the keepalive asm creates a data dependency (asm reads a1) that pins the la; the scheduler otherwise sinks the la to its consumer (the call). This is a "keepalive-order" or "sched1-load-order" wall. Let me use `sched1-load-order`? That tag's description: "sched1 orders an addiu/lw pair opposite to the target (G20)". Not quite.

The brief says the wall tag can be a new `<pass>-<what>`. Let me use `sched1-asm-barrier-order` or `sched1-la-sink`. Let me pick `sched1-la-sink` (new tag): "sched1 sinks an la to its only consumer; the keepalive's empty asm was the barrier that pinned it".

Actually, the difference appears after sched2 (both sched1 and sched2 place it early, but the final .s sinks it). Hmm, my analysis was inconclusive about which pass. The score category is ORDER. Let me use `sched2-la-sink`? Or just `sched1-la-sink` and note the uncertainty.

Actually, let me reconsider: the sched1/sched2 dumps both showed the la scheduled early, but the final .s has it late. That means REORG (delayed branch) moved it. But reorg doesn't move non-branch insns arbitrarily... unless the la is in a delay slot. Hmm.

Wait — maybe I misread the .s. Let me re-examine the c1.s very carefully around the la. Actually, let me use objdump on the --keep object to see the true final order. Let me get the --keep object for c1 and objdump it.

Actually, the delever_search diff already gives the true object order (it disassembles the object). The diff says mine[31:33] has the la and target[22:24] has it. So the object has it late in mine. Confirmed.

So the mechanism is real. Let me record the WALL.

But hold on — before recording, let me reconsider whether the keepalive is really "needed differs" for an ORDER that could be fixed by the do-while(0) trick at a different place. I tried v1/v8. Let me try one more: wrap the la AND everything up to the call in a do-while(0)? That might prevent the sink if the block boundary is after the la. But sched operates per basic block, and a do-while(0) is not a basic block.

Actually, C0535 says the do-while(0) splits cse1's EBB. The sink happens in sched (after cse). So a cse EBB split wouldn't help sched. But C0535's other examples show sched1 birth order being preserved by the split, so the split must affect sched's LUID ordering.

Let me try wrapping a LARGER region: `do { a1 = ...; v0 = ...; s0 = 4; ... } while (0);`? Hmm.

Actually, let me try the specific C0535 pattern: `do { a1 = (s32)&D_8019DC34; } while (0);` was v1 (4). 

Let me try `do { a0 = s0; a1 = ...; v0 = ...; } while (0);` (v16). And `do { a1 = ...; v0 = ...; } while (0);` (v8, 4).

Let me try v16 and maybe a nested one. Then record the WALL.

Actually, I've spent enough. Let me record the WALL with best=4, tries=31, tag `sched1-la-sink` (new).

Wait, but the task says "a WALL needs ≥ 20 min and ≥ 30 scored tries". I have ~31 scored tries (including COMPILE-ERROR q4? that's not a score). Let me count actual scored tries: c1, v1,v2,v3,v4,v5,v6,v7,v8,v9, nopin, p1,p2,p3,p4, q1,q2,q3,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14,q15 = 29 scored (q4 compile-error excluded). Plus the baseline orig (score 0, but that's not a lever-free try). Hmm, 29. Let me do a few more to be safe (30+).

Let me do 3 more quick variants (v16, v17, v18) and then record.

v16: do-while around a0,a1,v0.
v17: do-while around a1 and the store.
v18: `a1 = (s32)&D_8019DC34;` and use a1 in the `if` condition indirectly? no.

Let me do v16, v17, and one more (declare a1 as `s32 a1 = (s32)&D_8019DC34;` at the top but keep the assignment too? no).

Let me just do v16 and v17 and one reordering.

Actually, let me also try: `a1 = (s32)&D_8019DC34;` then `a2 = (s32)&D_8019DC3C;` then a `do{}while(0)` around them, then use both at the call. Hmm.

Let me do v16, v17, v18 quickly.
