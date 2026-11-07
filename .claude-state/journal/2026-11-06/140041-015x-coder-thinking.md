---
ts: 2026-11-06T21:00:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TTGbnWDlajFhRVCThdtU
---
So 5 instruction differences: the index temp (idx*4 = sll) uses a0 vs a1, and the `e` pointer lui/addiu uses a1 vs a0. So target: sll a1 (off), lui a0 (e); mine: sll a0 (off), lui a1 (e).

This is a global-alloc priority tie: off (s32) vs e (s16*). Both are call-crossing? They live across the func_80029178 call? Actually off and e are used inside `if (t<lim)` block and in the call argument.

Hmm. Target has off in a1 and e in a0. Mine has off in a0 and e in a1. Wait, a0/a1 here are temporaries used across... let me think about the target instructions:

```
32  sll a1,s0,0x2       # off = idx*4
34  addu at,at,a1       # at = &D_801E8F78 + off
36  lui a0,0x0          # e = D_801E8F78
37  addiu a0,a0,0
```

So target: off in a1, e in a0.

Mine: off in a0, e in a1.

Both are pseudo-regs with hard-reg preferences. This is a global-alloc priority ordering issue. Priorities: refs * length (or something). off is used: defined once, used in addu and in the load `*(s16*)((u8*)e+off+2)` twice? Let's see: off used at `(u8 *)e + off + 2` twice (two reads of the same expression). e used there too.

Since both pseudos need a0/a1. The one with higher priority gets a0. Target: e gets a0 (higher priority). Mine: off gets a0.

Wait actually in the target e gets a0 — e is loaded by lui/addiu and used as base. off in a1.

Hmm, how do we shift priority? e has more uses? In the source, `e` appears in the if condition twice: `*(s16 *)((u8 *)e + off + 2)`. And off appears twice too. But e is set once (e = D_801E8F78), off set once.

global-alloc priority = floor_log2(refs) * floor_log2(live_length) roughly (from global.c: `priority = floor_log2 (qty->n_refs) * floor_log2 (qty->live_length)`? Actually it's `(qty->n_refs * qty->live_length) / ...`? Let me recall GCC 2.7 global.c compute_reg_usage: 
```
qty->n_refs = ...;
...
/* Increase the priority of the qty if it is used in a loop */
...
floor_log2 (qty->n_refs) * floor_log2 (qty->live_length)
```
Hmm. In the moves log, greg-pri-refs: "pb 4 refs/live 72 pri 1111". So pri = something like n_refs^2 * live? Let me not compute; just experiment with refs.

The lever-free move: give e more refs, e.g. reuse it or split. But adding a use of e (like reading through it) could change code. Or reduce off's refs.

Alternative: reorder declarations? Global-alloc priority depends on live_length which depends on order of definitions/uses.

Actually, this is item 1 with barrier,launder. Score 4 is close. Let me try a few moves.

Option A: make `off` and `e` both ints? Widths: off is s32, e is s16*. Changing e's type would change codegen.

Option B: change statement order: compute e before off? The source computes off then lim then barrier then e. The target order in asm: sll a1 (off), addu (D_801E8F78 + off for lim load?), lui a0 (e). Hmm wait the lim load is `lim = D_801E8F78[idx][0]` which is load from D_801E8F78 + idx*4 (idx*4 = off). So:
- sll a1,s0,2 -> off
- addu at,at,a1 -> D_801E8F78 + off (for lim load) -- note at,at means lui at loaded earlier with D_801E8F78
- lw a1? no.

Hmm, actually line 34 addu at,at,a0 then 36-37 lui a0/addiu a0 = e. So target: at = D_801E8F78+off for lim; e = D_801E8F78.

So off lives in a1 and e in a0. Since e's lui/addiu comes after the addu, e is born later. Both are live through the block.

To swap: increase e's priority. e has n_refs: 2 uses in the condition. off has 2 uses (lim address and condition twice?). Let me count actual refs in the RTL. `off` used in: `D_801E8F78[idx][0]`? No that's idx. off used in the two `((u8 *)e + off + 2)` expressions — cse may share. Hmm.

Actually let me just try moves:
1. Reassign: instead of separate off, compute e as D_801E8F78 + off? i.e. `e = (s16 *)((u8*)D_801E8F78 + off)` and use `*(s16*)((u8*)e+2)`. That changes e to be derived, killing the lui/addiu separate... would change code.

2. Add a use of e earlier: e.g. set e before off: `e = (s16 *)D_801E8F78; off = idx*4;` — reorder statements. This changes live ranges: e born earlier, longer live_length → higher priority? Let's try.

Actually the natural approach: since target has e in a0 (born later) and off in a1, and global-alloc assigns a0 first to higher priority. In mine off wins a0. If I reorder so e is defined first, its live_length increases, possibly raising priority. Let me try.

Let me set up a small experiment script to try variants. But first, note that the barrier and launder were needed. The launder `e = (s16*)D_801E8F78` via asm with "=r"/"0" pins e to the same reg as the input. Removing it changes e's allocation. The barrier was a memory barrier.

Let me try variants systematically. I'll create candidate files and use sc.sh.

Let me write candidates:
- w1.c: e defined before off (reorder).
- w2.c: combine: `e = (s16 *)D_801E8F78;` then `off = idx * 4;` then `lim = ...`.
- w3.c: use `e[0]` for lim: `lim = D_801E8F78[idx][0]` stays.
- w4.c: change off to be part of pointer: no.

Also consider `idx` is s16; `off = idx*4` produces sll. The `D_801E8F78[idx][0]` — D_801E8F78 is s16[][2], so [idx][0] is at byte offset idx*4. cse may reuse off for the address.

Let me try reorder first. Write w1.c.

Actually, a cleaner idea: make `lim` load use `e`: `lim = e[idx][0];` since e = (s16*)D_801E8F78. Then e is used earlier (in the lim load), giving it more refs/longer live → priority. And it might make cse use e for the lim address. Let's test.

Let me create several variants at once.
