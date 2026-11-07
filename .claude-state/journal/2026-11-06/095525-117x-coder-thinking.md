---
ts: 2026-11-06T16:55:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3lNWe3QU7R5eeTuYM6l5
---
Good tags. For item 2 the wall looks like:
- fp removal → global-alloc priority order/extra pointer (loop-extra-iv? or global-pri-bank-order).
- ot removal → lreg-qty-priority (block-local ot takes t0 before the global cnt) — or global-hardreg-reserve.
- t0c → combine-copy-merge ("combine merges a reg copy the target keeps, so the pin stays").

The dominant wall: the fp pin removal causes an extra callee-saved register and a full bank shift: `global-pri-bank-order` or `loop-extra-iv`. The extra pointer (fp-8) is created by combine folding the loop's address bases — a "loop-extra-iv"-like effect? Actually the extra s0 pointer is not a loop IV; it's an address base. Tag `cse-const-addr`? Hmm.

Let me pick `global-pri-bank-order` for the overall (callee-saved bank shifts + frame +8) and note the sub-walls in evidence.

Now I need 30 scored tries. Currently 19. Let me run 11 more quick variants to reach 30. I'll make them meaningful:

1. no_ot+no_t0c (fp pinned) — combination
2. no_ot+no_fp
3. nopin with `i` as u8
4. nopin with `i` as u16
5. nopin with fp declared at block scope (f4 was with fp pin... f4 kept ot/t0c pins? f4 removed only the fp pin. Yes.)
6. nopin with prim as s8*
7. nopin with tpage declared s32 vs u16
8. nopin with the two gte calls on separate statements? same.
9. nopin with `m` as u32
10. nopin with the loop `for (i = 0; i < 0x10; i += 4)` → `for (i = 0; i != 0x10; i += 4)`
11. nopin with `prim += 0x24; fp += 0x24;` order swapped (fp first)

Let me generate these and score.
