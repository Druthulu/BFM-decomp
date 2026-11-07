---
ts: 2026-11-06T05:33:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U6nC0C67tZ7bJCqsrnDn
---
Only 22:33. Item 2 started ~22:24, so ~9-10 minutes. Plenty of budget. But I've done ~25 tries. Let me continue exploring a bit more; the budget is 20-30 min per item, so I have time.

Let me think much more carefully about the priority problem, since that's the crux.

Actually — WAIT. Big realization: maybe I should make the *copy* survive in a way where iVar2 has FEWER refs. In a1, iVar2 had 8 refs. What if the copy is from a *different* pseudo — e.g., copy from the sign-extended temp chain? Like:

```c
s32 v = CAST_SIGN(s16, iVar1, 0x10);   // iVar2 = v
iVar2 = ...;
tmp = v;
```
Hmm.

Or: what if `tmp` is assigned from the *load expression* directly, and iVar2 is assigned from tmp?
```c
tmp = CAST_SIGN(s16, iVar1, 0x10);   // tmp gets the loaded s16
iVar2 = tmp;                          // iVar2 = tmp
if (iVar2 != 0) { ... }
```
Then iVar2 is a copy of tmp. The target's tests use iVar2 and the arms use tmp. Hmm! That could work: the load goes into tmp, iVar2 = tmp (a copy). The tests use iVar2; the arms use tmp. The copy would be `move`... and iVar2's live range is from the copy to the last test, tmp's from the load to the arms.

But the target's asm: `lh a0,16(v1)` (iVar2 = a0) then `move v0,a0` (tmp = iVar2) then `bgez a0`. In this reversed version, the load goes into tmp and the copy into iVar2: `lh v0` then `move a0,v0`? The move would be in the delay slot of the beqz testing iVar2. Hmm, the target's delay slot is `move v0,a0` (dest v0, src a0), so the load dest is a0 and the copy dest is v0. In the reversed version, the load dest would be the copy source (a0) and the copy dest (v0) is iVar2... but then the tests would use v0, not a0. Target tests use a0. So no.

Hmm.

Let me reconsider: maybe the priority issue can be solved by making iVar2's *live range longer* via the second block. What if iVar2 is used in the `skip2` block? Looking at the source:
```c
skip2:
    if (*(s32 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x10) == 0) {
```
What if this used `iVar1` (which was reloaded)? It does via unk20.

Hmm.

New idea: what if the second block's iVar2 assignment is *removed* and the same iVar2 is reused? No.

Let me look at the actual qty numbers in the *target* build (orig2 lreg): reg74 (iVar2) 8 refs/10 insns → 9.6. If the lever-free version could get iVar2 to 6 refs/10 insns → 4.8 < 5.33 ✓.

What contributes to the 8 refs? Let me examine the orig2 RTL around reg74 more carefully, counting occurrences.

From the cse2 dump:
- insn 26: (set (reg/v:SI 74) (ashiftrt ...)) — def
- jump 29: (eq (reg/v:SI 74) 0) — use
- insn 33: (set (reg/v:SI 75) (reg/v:SI 74)) — use
- jump 38: (ge (reg/v:SI 74) 0) — use

4 occurrences. The dump says 8 refs. Hmm, maybe n_refs counts differently (REG_N_REFS counts each mention in each insn; a jump_insn's condition may count 1). Or maybe the count includes both blocks (the second if's iVar2 too — but that's a different qty in a different block).

Hmm, "used 8 times across 10 insns". Maybe the sign-extend chain's reg74 is used in the second block too? Let me look at the full RTL for reg74 occurrences in the first block region.

Let me grep orig2.i.cse2 for "reg/v:SI 74".
