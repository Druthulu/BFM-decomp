---
ts: 2026-11-06T12:22:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Wi8JB4jKXrTtfBUVkveR
---
Worse (202 ins). Let me look at the diff.

Actually, the target has TWO loads of `*pb` (lhu a0,0(a2) at 59 and lhu v1,0(a2) at 73) — so pb's address load is done twice. With one variable, the register pressure differs.

Alternative: keep pb2 but give pb more real refs. The asm has 5 refs of pb. Hmm.

Wait: which variable is which? In target, `lhu a0,0(a2)` at 59 and `lhu v1,0(a2)` at 73 use the SAME register a2. So in the target, both pb and pb2 are in a2 (coalesced? they hold the same value!). Actually two different pseudos can share a register only if their live ranges don't overlap. Here pb is live throughout (used at 59, 73, 86, 89); pb2 at 86, 89. If pb2 == a2 too, they'd conflict... unless pb2 is coalesced into pb (same value via copy propagation: `pb2 = (u16 *)&D_800B9A02;` is a copy of the same address constant → gcc may use the same pseudo!).

Indeed: `pb2 = (u16 *)&D_800B9A02` and `pb = (u16 *)&D_800B9A02` — both are the address of the same symbol; cse would fold them into one pseudo! So in the target, pb and pb2 are probably the SAME pseudo already. Then why did the keepalive exist? Because 5 asm refs of pb boost that pseudo's priority to win a2 over something else.

In my v0 (levers removed), the pseudo got t0 instead of a2 — a register-priority difference vs another pseudo.

So the fix: boost the priority of that address pseudo with real refs, or reduce the competing pseudo's priority.

What is the competing pseudo? In the diff, `t0->a2 x11` and `a2->a3 x4`, `a3->t0 x6`. So mine: pb→t0, and something else (target a3) → mine a2. Let's see: target a3 at 110 `sll v0,a3,0x10` vs mine `sll v0,a3,0x10`... hmm mine 110 sll v0,a3,0x10 and target sll v0,t0,0x10. So there's a 3-way rotation: t0→a2, a2→a3, a3→t0.

So three pseudos rotate. One is the address (a2 in target), one is `k` (the index, m = D_8011511A), one is... Let's identify: target 102 `move t0,zero` (j=0), 103 `move a3,v1` (k = m), 105 `move t2,a2` — hmm.

In the C: j=0, k=m, eight=8, then in the loop `D_80115140[k]`, `k2 = k*2`, etc. So k is a hot pseudo (index into arrays, computed at 110 `sll v0,a3,0x10`? no).

Hmm: `sll v0,t0,0x10` then presumably `sra v0,v0,0x10` for (s16)idx2. Actually `(s16)idx2` where idx2 = idx + 0. And `m == (s16)idx2`.

Anyway, a 3-cycle rotation. The keepalive's 5 refs on the address pseudo pushed it from t0 to a2, and the others followed.

Real-C: give the address pseudo real refs. It's `*pb` — used 3 times (lines 36, 37, 38) plus 86, 89 = 5 uses already! Hmm, in the target it's `D_800AE7BC[*pb].ot[2]` (line 36), `D_800AE7BC[*pb].ot[2]` (37, 38) — that's 3 uses, then 86, 89 with *pb2 → 2 more = 5 uses total. The asm adds 5 more → 10.

To give real refs without adding instructions: express `*pb` more times in C? Each extra use would be a load unless cse folds it. E.g. write `D_800AE7BC[*pb].ot[2]` twice in the same expression → cse folds, but flow counts refs BEFORE cse? Order: cse1 runs before flow. Hmm, cse1 would remove the redundant load, so no extra refs at flow time.

Alternative: use a local temp for the address pseudo: `u16 *ap = pb;` — a copy. That adds a pseudo, not refs.

Hmm. Alternatively reduce the competing pseudos' priority. Which pseudo took a2 in mine? Let me look at the whole region to identify. Let me dump target 95-120 and mine's.

Actually, a cheaper experiment: vary the number of keepalive-like real uses by restructuring the address expression. E.g. instead of `D_800AE7BC[*pb].ot[2]` use `(*(Env_8017EFA8 *)((u8*)D_800AE7BC + *pb*0x14)).ot[2]`? No, changes code.

Think differently: maybe I can give the address pseudo a real second use by reusing it as a base: e.g. `p = (u16 *)&D_800B9A02` — no.

Hmm, what about declaring pb EARLIER or initializing it at the declaration (`u16 *pb = (u16 *)&D_800B9A02;`)? That's "init at decl" — a real-C move (C0505 catalog). Moving `pb = ...` from line 34 to the declaration could change the pseudo's birth order/priority. Let me try that.

Also `pb2 = ...` at line 58 — move it earlier too? Or initialize pb2 at its decl.

Let me try a few:
- t1: pb initialized at declaration (moved to top).
- t2: pb2 initialized at declaration.
- t3: both.
- t4: pb declared before p (order).

Also, what about the barrier? Let me handle both separately: first fix the barrier alone (keep the keepalive) → then combine.

Barrier alone: keep line 57's keepalive, remove line 78's memory barrier. Score?

Let me run: barrier-only removal (b0) and keepalive-only removal (k0) to measure each cost.
