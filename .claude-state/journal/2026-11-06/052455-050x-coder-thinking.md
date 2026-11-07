---
ts: 2026-11-06T12:24:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CoaO4grySm6c8JG1U7NB
---
No good. The keepalive is hard here: 19.

Think again. The keepalive asm is `__asm__ volatile("" :: "r"(pb), "r"(pb), "r"(pb), "r"(pb), "r"(pb));` — 5 uses of pb. Note it's `volatile` with 5 identical operands. This gives pb 5 extra refs.

Real-C equivalents that give refs without extra instructions... The only "refs" that don't cost instructions are uses that get folded: e.g. using pb in an expression where the load is CSE'd, or where the address is used directly in an addressing mode.

Idea: `D_800AE7BC[*pb].ot[2]` — if I write the expression with pb used as a base pointer instead of `*pb` as an index... e.g. `*(Env_8017EFA8 *)((u8 *)D_800AE7BC + *pb * 0x14)`. Same.

Idea: use pb in the `q` computation or the `p` computation as a real (folded) use: e.g. `p = (u16 *)(t * 2 + (s32)a1p);` — could add `+ (*pb - *pb)`? That's a launder/identity — forbidden.

Hmm. What about restructuring so the competing pseudo (k) has fewer refs / shorter life?

k = m; used as D_80115140[k] (twice: line 64 and 71 via `((s8 *)D_80115140)[k]`), and `k * 2`.

What if `k` is not a variable but `m` used directly? Then the `move a3,v1` disappears (an insn less) → count mismatch.

What about making k's uses cheaper: `s32 k2 = k * 2;` inside the else (line 70).

Hmm. Since target has `move a3,v1` (k=m), the copy is required.

Alternatively: make the address pseudo get a3 and k get a2 (mine's assignment) — no, target has address=a2.

What if the competing pseudo isn't k but j? j=0, moved to t0 in target, a3 in mine. j is used as the loop counter and `if (j == 0)`.

Let me look at what else uses a2/a3/t0 across the function. Maybe I can raise the address pseudo's priority by making it live across a call? No calls here.

OK, alternative approach: accept the register rotation as the wall but fix the barrier (score 2) → PARTIAL:keepalive with the barrier cracked. That's the same outcome as item 1: PARTIAL:keepalive.

But wait — can I fix the barrier's ORDER(2) at all? Let me try the o-variants. If the barrier is cracked and the keepalive remains, that's PARTIAL:keepalive.

Let me try to crack the barrier (2 points) first: reorder statements.

o1: swap `q[-8] = 0x78;` and `*((u32 *)ot) = 0x4000000;`
o2: move `*((u32 *)(q - 0x10)) = 0x64808080;` after `*(s16 *)(q - 6) = 0x4056;`
o3: move the y store to just before `q[-8] = 0x78;` (i.e. after `*((u32*)ot) = 0x4000000;`)
o4: move `*((u32*)ot) = 0x4000000;` before the y store.
o5: temp for 0x64808080.

Let me generate on b0.c (barrier removed, keepalive kept).
