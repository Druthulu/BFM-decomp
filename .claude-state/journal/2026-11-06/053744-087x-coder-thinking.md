---
ts: 2026-11-06T12:37:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hefppMWyC8ConxprN2bm
---
Target head:
```
0 move t2,a0
1 move t3,a1     ; arg1 -> t3
2 andi a1,a1,0x1 ; test the ORIGINAL a1
3 bnez a1,...
4 move t4,a2
```
So the target copies arg1 to t3 (line 1) AND tests a1 (line 2). So the test uses a1 after the copy — the launder's a1v is a1, and the test `a1v & 1` uses a1.

In mine (n1), the test uses t3 (`andi v0,t3,0x1`) — i.e. gcc used the copied value instead of a1. That's a local-alloc/cse choice.

With the pinned a1v: a1v = $5 = a1, and the asm forces the value into a1. So the test is on a1.

Real C equivalent: hmm, we need arg1 (after being copied to t3) to still be tested in a1. That's exactly a register steer.

Alternatively: could we make the copy to t3 NOT happen? t3 holds arg1 for the later uses (lines 64, 71). If instead arg1 were kept in a1... it can't (a1 is call-clobbered and there might be calls in between? The div!). Actually there IS a div — `(temp_a1 * b8[0]) / var_a3` compiles to `div`/`mflo` (no call). Hmm, but there might be a call to a helper.

Hmm. What if I make the two later uses use a local variable that I keep? That would change the code more.

I think the launder at 2 is a register steer without a C equivalent. 

Similarly the keepalive (3): target keeps var_v0_3 in v0 (a separate register from t4=pos), because pos is live longer (the keepalive).

And the barriers (12): a jump2 cross-jump that only the barrier prevents (the barrier adds insn slots that make the arms non-identical).

So item 4 is also a WALL... but wait, could I get a PARTIAL? PARTIAL = win.c scores 0 keeping only SOME kinds. That requires cracking at least one kind fully. The launder is at 2, keepalive at 3, barrier at 12 — none at 0.

Hmm, hold on. Let me try harder on the launder (2) since it's the closest. What if the C uses `a1v` in the test and the compiler keeps it in a1... 

Idea: declare a1v as a *parameter copy* with the same type and put the test FIRST:
```
register s32 a1v __asm__("$5");
a1v = arg1;
if (!(a1v & 1)) {
```
= l0 = 2 (mine tests t3?). Let me check l0's diff again: `andi v0,t3,0x1` — yes, still t3. So gcc ignores the pin for the test? No — it must have put a1v's value in t3? But a1v is pinned to $5 (a1)! Unless the pin variable was optimized away (a1v's uses folded into arg1's copy in t3).

Right: with `a1v = arg1;` (plain copy), gcc's copy propagation replaces a1v with arg1 everywhere (they're equal), then the pin is dead and the copy is deleted. So `a1v` disappears and we get n1's code.

To keep a1v alive, it must be used in a way that prevents copy propagation: the launder asm does that.

Hmm — so any plain assignment is copy-propagated away.

What if a1v is assigned from something else, e.g. `a1v = arg1 & 0xFFFF;`? That changes the value (for negative arg1). Actually the test is only `& 1`, and later uses of a1v... none. So a1v is only used in the test. So a1v's value is only used for bit 0. `a1v = arg1;` then `if (!(a1v & 1))` — the compiler folds to arg1.

To keep a1v separate: give it a different value, e.g. `a1v = arg1 | 0;`? folded.

Hmm, what if a1v is used in a comparison that requires the full value... no.

OK. Now, let me reconsider: maybe I should target the keepalive (3) — target: `addiu v0,t4,2` / `sh v0,2(v1)`; mine: `addiu t4,t4,2` / `sh t4,2(v1)`. So in mine, var_v0_3 coalesced with pos (t4). The keepalive extends pos's live range so it can't be overwritten.

Real C: make pos used AFTER the if/else, so var_v0_3 can't share its register. The only later statements are the three D_8012672x stores. Could `pos` be used there? Semantically no.

Alternatively: make `pos` and `var_v0_3` different types so they can't coalesce? They're both s16.

Or: don't use `pos` in the arms at all: `var_v0_3 = (arg1 & 1) ? ...` no.

Or: use arg2 directly instead of pos: `var_v0_3 = arg2 + 2;` — then pos (pinned $12 = t4) is only used at line 31 (`pos = arg2`), so the pin forces arg2 into t4 and... the arms would use arg2. But then the target's `addiu v0,t4,2` (using t4=pos) wouldn't match — target uses t4. Hmm, unless arg2 is in t4 (the pin `pos = arg2` forces a copy into t4; if pos is unused, the copy is dead).

So no.

Let me try a couple of cheap variants on the keepalive:
- `var_v0_3 = pos + 2;` → `b4b[1] = pos + 2;` directly (drop var_v0_3) in both arms. Then the store is per-arm. Target has one store at the join, but maybe jump2 re-merges.
- var_v0_3 declared u16.
- pos declared s16 instead of s32 (pos is `s32` pinned; the target's `addiu v0,t4,2` suggests pos is in t4 as s32...).

Hmm, actually: `register s32 pos __asm__("$12")` — $12 = t4. Yes.

Let me try: `var_v0_3 = pos + 2;` with var_v0_3 as s16 → the sh truncates. Mine reuses t4 because var_v0_3 dies immediately.

What if I add `(s16)` casts? n3 = 3 (same).

What if the two arms' addiu results are used in a way that forces v0? E.g. `b4b[1] = var_v0_3;` then later use var_v0_3 again? No.

OK. Let me try the barrier reorder variants (4 tries) since the barrier is 12 — the biggest. If the arms can be made non-mergeable, we might get to 2+3 = 5 total... but PARTIAL needs 0.

Realistically item 4 is a WALL too. But let me spend 10 more tries (I need ≥30 for a WALL; I have 4 + 4 = 8 so far... let me count: v0, l0, bb, k0 (4), n1-n4 (8). Need 22 more.

Hmm, 22 more tries on a 156-ins function is cheap (1 s each). Let me generate a batch of ~22 variants: statement reorders in the barrier arms, pos/var_v0_3 variants, a1v variants.

Let me write a generator with ~24 variants.

Barrier region variants (on bb.c = barriers removed):
- reorder the else arm: var_v0_3 before the store (3 permutations)
- reorder the if arm
- b4b[1] per arm
- combine
- move `b4b = D_8017E918;` before the if (1 try — changes code, but let's see)
- put `D_801152AA = 0xFFF;` after var_v0_3 in both arms

Launder variants (on orig):
- a1v = arg1 with the test using arg1 (n1) — done
- a1v = (s32)arg1
- test `if (!(a1v & 1))` where a1v is a u16
- declare a1v as s16
- use a1v in the later tests too (lines 64/71)

Keepalive variants (on k0 = keepalive removed):
- var_v0_3 s32 (n2 = 3), u16
- store per arm from pos directly
- `var_v0_3 = (s16)(pos + 2)` (n3 = 3)

Let me write them.
