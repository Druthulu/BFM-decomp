---
ts: 2026-11-06T21:30:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AcdAhTo06CjPkRV25Tz8
---
So the priority of 55 and 63 is 0x7f000001. That's the INSN_PRIORITY. Hmm, that's huge — meaning priority() gave them a big value? The priority function returns max_priority = 1 + ... but maybe with the "dead" flag.

Hmm, 0x7f000001 = 2130706433. In sched.c, there's a macro:
```
#define INSN_PRIORITY(INSN) (XINT (INSN, 4))
```
and priority() sets `INSN_PRIORITY (insn) = max_priority;` where max_priority = 1 + ...

Hmm, but there's also `INSN_PRIORITY_STATUS` etc. 0x7f000001 might be the priority with a bit set: 0x7f000000 | 1. Hmm, 0x7f000000 = 2130706432.

Wait — maybe the priority values 55 and 63 are the ones with "0x7f" = a flag for insns that were originally... Hmm.

Actually, let me look at the .sched log again:
```
;; insn[  55]: priority =    1, ref_count =    2
...
;; ready list at T-3: 60 (1) 55 (7f000001) 63 (7f000001), now 63 55 60
```
So at the time of the dump, INSN_PRIORITY(55) = 0x7f000001 but the earlier log said "insn[55]: priority = 1". So the priority changed to 0x7f000001 during scheduling. Maybe the high bits are a "scheduled" marker: 0x7f000001 = SCHEDULED flag | 1? Hmm.

Hmm, whatever. The point: 55 and 63 have the same value, 60 has 1. So the ready list is sorted: [60(1), 55(7f000001), 63(7f000001)]? That's ascending, not descending. But schedule_select groups by priority starting from ready[0]...

I'm going too deep. Let me take the empirical route: I've spent enough; let me try a batch of C variants for item 3 and see if any gives 0. If not, WALL with best 2.

Time budget for item 3: started ~14:20, so until ~14:40-14:50.

Let me generate a set of variants:
- w1: pin kept, keepalive dropped (score 2) [current best]
- Variants around the move:
  - `a = arg0;` placed at various points
  - `a` used for the store/call vs arg0
  - different declarations
  - the `if` condition variations
  - `q` reused for p (the first load) — the `p`/`q` reuse is a real lever: `p = *(s32*)((u8*)arg0+0x20)` and `q = *(s32*)((u8*)arg0+0x20)` — two identical loads. Could we use one variable? The target has two loads (lw a0,32(s0) at 6884 and lw v1,32(s0) at 68a8) — so two loads from the same address, meaning the source used two variables or cse didn't merge (volatile? no). Interesting: the target has both loads, so the source likely had `p` and `q` as separate variables and cse didn't merge them because... the store to `*(u16*)(p+0x10)` intervenes, so the second load can't be CSE'd (memory clobber). Right.
  
Let me focus on the move scheduling. Ideas:
1. Change the order of the two stores (tried, worse).
2. Use `a` in the first store's address: no.
3. Make `a = arg0` conditional: `a = arg0;` inside `if (1)`? deleted.
4. Declare `a` as `s32 *a` and cast: `a = (s32 *)arg0;` — the move is the same.
5. Use `a` for the q load: `q = *(s32 *)((u8 *)a + 0x20);` — changes the load base to a0 (target uses s0). But wait — if `a` is pinned to a0, the load would be `lw v1,32(a0)`. Target: `lw v1,32(s0)`. Mismatch.

Hmm, but what if `a` is NOT pinned and `q = *(s32*)((u8*)a+0x20)` — then a coalesces with s0, the load uses s0, and a's use at the q load makes the copy... no copy needed (coalesced).

6. What if we introduce a *second* use of a0 after the move that keeps reg 72 alive? E.g., the store `*(u16 *)((u8 *)arg0 + 0xb8) = 1;` uses arg0 (s0) while `a` is used for the call. Then `a = arg0` doesn't kill reg 72. Hmm, and the store uses s0 — target uses a0. Mismatch.

7. What about the delay-slot choice: maybe a different `if` form changes which insn reorg picks. E.g., `if (0xc00 > *(s16 *)((u8 *)q + 0x10))` — the same slti.

8. What if we change the *call* to use `a` but the store to use `a` — that's w1.

Let me try a couple of things and check. Actually, let me first look at the .sched2 dump: maybe sched2 (post-reload) reorders. The final asm comes from sched2 + reorg. Let me check the .sched2 order for w1.

Actually, the .s (final asm) shows the move at 25, so sched2 didn't fix it.

Hmm, one more idea: since the move is a *copy to a fixed register* (a0), maybe I can make it not a copy: e.g., `a = arg0 + 0` — folds. `a = (void *)((s32)arg0 | 0)` — folds. `a = (void *)((s32)arg0 ^ 0)` — folds. These are identity statements anyway (not allowed as cracks).

What about making the copy from a *different* value that happens to equal arg0? no.

OK, let me try the remaining plausible variants and then declare the wall (sched1-ready-order). Note the wall needs ≥20 min and ≥30 tries for item 3 too. I started item 3 at ~14:20 (after item 2's finalization at 14:28? no — I started item 3 at ~14:20 while item 2's clock was running). Let me be careful: item 3's work started at ~14:20 (when I read its files). So 20 min → ~14:40.

I have ~15 min. Let me do a proper sweep of ~30 variants.

Let me write a generator for item 3 with many real-C variants:
v1: pin kept, keepalive dropped (score 2) — base
v2: no pin, no a (score 3)
v3: a=arg0 hoisted before the inner if (w5, score 3)
v4: stores swapped (w6, 6)
v5: a=arg0 after the q-store, before the a-store
v6: a used only for the call; store uses arg0
v7: a used only for the store; call uses arg0
v8: a = arg0; call(a); store after the call? (order: store q; a=arg0; call; store a) — hmm.
v9: declare a as `void *a;` (no pin), use a for the store and call (same as w2? w2 has no a).
v10: q = *(s32*)((u8*)a+0x20) with a pinned
v11: p = *(s32*)((u8*)a+0x20) with a pinned
v12: use `a` in the `if` condition via a comparison
v13: `if (*(s16 *)((u8 *)q + 0x10) < 0xc00)` → `if ((*(s16 *)((u8 *)q + 0x10) & 0xffff) < 0xc00)` — changes the sign extend to andi? no, `lh` + andi... changes code.
v14: `t` variable reuse (the header's sibling had a `t`) — add a temp for the s16 comparison: `s16 t = *(s16*)((u8*)q+0x10); if (t < 0xc00)`. Might change the code (the lh goes to a named temp) — the target has `lh v0,16(v1)` then `slti v0`. Same.
v15: different declaration order of p/q/a.
v16: `a = arg0;` twice? no.
v17: use `*(u16 *)((u8 *)a + 0xb8) = 1;` before the q-store with a=arg0 before both (w3+w6 combined).
v18: `func_80146CA0(a);` then the a-store (store in the delay slot automatically).
v19: `((Unkstruct...)...)` hmm.
v20: split the then-block with a `do { ... } while (0)`.

Let me just write ~25 and score. Also test removing the pin only (keepalive kept) — done: score 5.

Actually, wait. Let me reconsider the target order once more: move; li 3072; sh 16; li 1; jal; sh 184.

Hmm, notice: `sh v0,184(a0)` is in the jal delay slot and uses a0. For reorg to put that store in the delay slot, it must be the last insn before the call in the scheduled order.

In mine (w1): li 3072; sh 16; move; li 1; sh 184; jal → wait, the final asm showed the move at 25 and presumably `sh 184(a0)` at 29 (after jal?). The diff said mine[29] = sh v0,184(s0) vs target sh v0,184(a0) — hmm, in w1 the store uses a0? The diff earlier for w1: "insert move at 24, delete mine[25]=move". So mine = [24 li][25 move][26 sh 16][27 li 1][28 jal][29 sh 184]? Hmm, that gives sh 184 in the jal delay slot — same as target.

So mine's only difference: the delay slot of the beqz has `li v0,3072` instead of `move a0,s0`, and the move comes right after. So the *rest* is identical.

So reorg picked the li for the beqz delay slot (mine) vs the move (target). Reorg's fill picks the first insn after the branch that is safe. So the stream after the beqz must start with the move in the target.

Since sched1 output mine = li, move, sh, ... and target = move, li, sh, ...

So I need sched1 to emit the move first. All priorities are 1; the ready-list order decides.

Hmm, here's a thought: the ready list order is influenced by the insn UIDs (tie-break 5: lowest UID). The move has UID 55, the li has 58. In the reverse scheduler, the final order is the reverse of the pick order. To get the move first in the final order, it must be picked LAST. Among {55, 58, 60}, the pick order was 60, 55, 58 (reverse of the final 58,60,55). Hmm.

The tie-break "lowest UID" would pick 55 first (as the first in the final order?)... I'm going in circles.

Empirical: let me try changing the UID order by moving statements in C, and see if the final order changes. E.g., if `a = arg0` is the LAST statement before the call, its UID is largest; the final order might then put it first? Hmm.

Let me just try variants. I'll write ~20 and score them.

Actually, let me reconsider: is this item even worth a long fight? The kinds = keepalive only. The best lever-free body scores 2. It's a 1-insn scheduling difference. The wall tag sched1-ready-order exists. Let me do a solid 30-try sweep (20 min) and then wall it.

Let me write the generator.
