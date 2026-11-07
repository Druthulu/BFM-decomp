---
ts: 2026-11-06T21:23:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yvt0TokSO0HNfY0lsjtz
---
w6: score 6, mine has the move at 24 (matching!) but the li/jal order differs: mine does `li; sh v0,184; jal; sh v0,16`? Let me parse: insert target[25:27] = li v0,3072; sh v0,16(v1) at mine 25; insert target[28:29] = jal at mine 26; delete mine[27:30] = li v0,3072, jal, sh v0,16(v1). So mine's order: [24 move a0,s0][25 li v0,1?][26 sh v0,184(a0)?][27 li v0,3072][28 jal][29 sh v0,16(v1)]. Hmm.

So swapping the C stores changed the schedule order of the stores: the a-store came before the q-store. Target has the q-store (li v0,3072; sh v0,16) first, then li v0,1; jal; sh v0,184(a0).

So I need the q-store scheduled first AND the move in the delay slot. w1 had the q-store first but the move later. w6 has the move first but the a-store first.

Hmm! So there's a trade-off. What if I keep the C order (q store first) and add something to make the move early?

In w1 (pin, no keepalive): mine order after beqz: li v0,3072; move a0,s0; sh v0,16(v1); li v0,1; jal; sh v0,184(a0)? The diff said insert move at 24 and delete mine[25] = move. So mine[24] = li v0,3072, mine[25] = move, mine[26] = sh v0,16... 

Wait, that means mine's stream is: li v0,3072; move a0,s0; sh v0,16(v1); li v0,1; jal; sh v0,184(a0). Target: move; li; sh; li; jal; sh. So only the first two are swapped! Just one position.

Reorg takes the first insn after the branch for the delay slot: mine takes li, target takes move.

So I need sched1 to emit the move before the li. In w1, sched1 emitted li then move. 

What determines this? Both are independent. sched1's priority: the li (set of v0 to 3072) and the move (a0=s0). Hmm.

What if we make the move's destination a0 needed by an earlier-scheduled insn... The `sh v0,16(v1)` uses v1 (q) and v0 (the li result). The move's a0 is used by the last store and the call.

What if the call's argument setup is done earlier by making `a` used at the *first* store? That's w6 (a-store first) — wrong order.

What if we make `a` used in the q-store's address? e.g., `*(u16 *)((u8 *)a + 0x10) = 0xc00;` — but that's q, not a. q = *(arg0+0x20) ≠ arg0.

Hmm, what if we compute q from a: `q = *(s32 *)((u8 *)a + 0x20);` with a = arg0 pinned? Then the q load uses a0. Target uses s0 for the load at 68a8. Hmm, but wait — the load at 68a8 is `lw v1,32(s0)`. If a is a0, it'd be `lw v1,32(a0)`. Mismatch (1 insn).

Unless... the target's `move a0,s0` at 68c0 is the ONLY use of a0 before the call. So a is only used in the then-block.

OK, what about the ordering trick: put `a = arg0` at the very top of the inner-if block, but the C order of the stores unchanged. That's w1 (a=arg0 first). sched1 still puts li first.

What makes sched1 order two independent insns? Let me look at sched.c's priority: `priority = ...` based on dependents count and depth. The move a0=s0: its dependents are the store (sh 184(a0)) and the jal (a0 use). The li v0,3072: its dependent is the sh. Similar.

Hmm, but there's also the branch: after the beqz, sched1 might treat the delay slot specially.

Let me look at what actually happens: maybe sched1 isn't the culprit; maybe it's reorg's `fill_slots_from_thread` choosing among insns. Reorg picks the first insn that's "eligible" (not a jump, no conflict). In mine the stream order after the branch is li, move, sh... Reorg takes the li. In target, move, li, sh... takes the move.

So the stream order differs. Which pass orders them? sched1 (before reorg) or sched2? The dump `.sched` is sched1 output, `.sched2` after the second scheduler.

Let me dump w1 (pin only) and look at the .sched/.sched2 order around the branch. But dumping a header item needs the includer TU. I can dump the includer with the header shadow... complex. 

Alternative: since the difference is one instruction position, maybe a C-level tweak changes sched1's priority. Ideas:
- Add a use of `a` in the *condition* of the inner if (so the move is needed before the branch): e.g., `if (*(s16 *)((u8 *)q + 0x10) < 0xc00 && a == arg0)`. That adds a comparison (extra insn). No.
- Make the move depend on something: `a = (void *)((u8 *)arg0 + 0);` → folds.
- `a = arg0; ...` and use `a` in the store `*(u16 *)((u8 *)q + 0x10) = 0xc00;`? q vs a — different.

Hmm. What about using `a` for the *0xb8 store* and *also* making that store's base computation fold? It's `sh v0,184(a0)` in the target (a0 + 184). With a pinned, the store's address is a0+184 — the store is scheduled last (delay slot of jal). 

The problem is purely the order of the first two insns after the branch: li v0,3072 vs move a0,s0.

What if we change the constant `0xc00` to an expression that makes the li later? The li is a separate insn; the store uses it.

What if the C store were `*(u16 *)((u8 *)q + 0x10) = 0xc00;` — the li. Could we express 0xc00 as a computed value that doesn't need an li? E.g., `0xc00` is a constant; any form still needs materialization.

What if we swap the *declaration* order or the statement order such that the move is generated before the li in the RTL? In w1, the C order is `a = arg0; *(u16*)q = 0xc00;` — so the move comes first in the RTL. Yet sched1 reorders. Hmm.

So sched1 actively moves the li before the move. Why? Maybe because the li is "cheaper" (no register pressure) or has higher priority. 

In the target (with the keepalive asm), the asm was a barrier, so sched1 couldn't reorder across it.

Is there a *real C* barrier? A function call is a barrier! If the then-block started with a call... no.

What about a `volatile` access? That's a barrier but adds an instruction.

Hmm, what about making `a`'s value depend on a computation that must happen after the branch? E.g., `a = (void *)((u8 *)arg0 + 0x0);` folds.

What about `a = arg0;` where arg0 is used... 

Wait, actually: maybe the move is scheduled first if it's the *first* insn in the block AND sched1 doesn't move the li up. Why does sched1 move the li up? Perhaps because of the "speculative" scheduling of the li into the delay slot region... 

Let me look at the .sched dump to understand. To dump a header item, I need the includer TU with the modified header. delever_search's header mode creates a shadow include dir. Let me replicate: I can create a scratch dir under my shard with a copy of the includer TU and a shadow `inc/` dir containing the modified header, then compile with cpp -Iinc first. The cc1_dumps_tu.sh script takes a .c file and runs cpp with -Iinclude -I(dirname) -Isrc/shared -Isrc. If I put my modified header in a dir and pass -I before -Iinclude... the script's cpp line is fixed. Hmm.

Alternative: copy the includer TU into a scratch dir *mirroring src layout*: e.g., .run/P40/T11/W49x/item3/dump/ov_MAIN_012/ov_MAIN_012_jr_8015A3C8.c and also create .run/P40/T11/W49x/item3/dump/shared/ov/func_80160C28.h? The include is `#include "shared/ov/func_80160C28.h"`? Let me check how the includer includes the header.

Let me grep the includer's include line.
