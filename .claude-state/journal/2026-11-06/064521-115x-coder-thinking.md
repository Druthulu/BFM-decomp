---
ts: 2026-11-06T13:45:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T0IH6U4noJYJwCAh4Pva
---
Barrier C removal: score 8. Differences:
1. register pairs t3→t2 and t2→t3 swapped (2 places) — the prologue moves.
2. `andi a1,t2,0xffff` placement vs `andi v0,t3,0xffff`.

This is about `su`/`sv` (u16 su = x; u16 sv = y;) and the vv computation:
```
        uu = (su - ((tpage & 0xF) << 6)) << (2 - tpp);
        [barrier C]
        vv = sv;
        pkt->tpage = tpage;
        pkt->u0 = uu;
        if (tpage & 0x10) {
            vv -= 0x100;
        }
        pkt->v0 = vv;
```
Hmm.

Let me look at the target around index 89-105 and mine.

Actually, the register swap t2/t3 is in the prologue (`move t2,t1` vs `move t3,t1`) — the su/sv copies. In the target: `move t2,t1` (su = x?) and `move t3,a2` (sv = y). In mine: `move t3,t1` and `move t2,a2` — swapped. So the roles of t2/t3 are swapped. That's an allocation difference driven by the later code.

The `andi a1,t2,0xffff` (mine) vs `andi v1,t2,0xffff` (target at 90) and `andi v0,t3,0xffff` (target at 97).

This is the `su`/`sv` truncation: `andi ... ,0xffff`.

Hmm, this is a register allocation difference: mine uses a1 and v1; target uses v1 and v0.

This might be fixable via the order of `uu` and `vv` or the barrier.

Given the complexity and time, let me try the do-while C0535 trick around the `uu` assignment (where the barrier was).

Source around C:
```
        uu = (su - ((tpage & 0xF) << 6)) << (2 - tpp);
        __asm__ __volatile__("");
        vv = sv;
        pkt->tpage = tpage;
        pkt->u0 = uu;
```
Try: `do { uu = ...; } while (0);` and `do { vv = sv; } while (0);`.

Let me test a batch for C: do-while around uu, around vv, around both, around the pkt->tpage store.

Similarly for B: the source:
```
        tpage = ((tpp & 3) << 7) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6) | ((y & 0x200) << 2);
        __asm__ __volatile__("");
        cl = cyy << 6;
        ct = (cx >> 4) & 0x3F;
        cl |= ct;
        pkt->clut = cl;
```
Try do-while around the tpage assignment.

Let me generate a batch that fixes C only (with A and B still present) and B only.

Actually, better: fix all three with do-whiles in one body and see. But if one fix interacts, hard to tell. Let me do B alone first (score 30) with a few placements, then C alone.

Batch for B (keep A and C barriers):
- b1: do { tpage = ...; } while (0)
- b2: do { cl = cyy << 6; ct = ...; cl |= ct; } while (0)
- b3: do { pkt->clut = cl; } while (0)
- b4: do { tpage=...; cl=...; ct=...; cl|=ct; pkt->clut=cl; } while (0)

Batch for C:
- c1: do { uu = ...; } while (0)
- c2: do { vv = sv; } while (0)
- c3: do { uu=...; vv=sv; } while (0)
- c4: do { pkt->tpage = tpage; pkt->u0 = uu; } while (0)

Let me write one generator producing both batches, using string replacement on orig.c.
