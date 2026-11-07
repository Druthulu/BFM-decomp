---
ts: 2026-11-06T15:56:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vB8Z1WmXynRjaIdSFNis
---
vh1: the la IS first now (insn 2-4)! And the rest has order differences (score 12) because I moved the pointer setups after the call but sched2 placed them differently (the spills order changed).

Target prologue:
```
addiu sp
lui a0; addiu a0
sw s4,88
lui s4; addiu s4
sw s3,84
lui s3; ori s3
sw s7,100
lui s7
sw s2,80
addiu s2,s4,41
sw s5,92
addiu s5,s4,20
sw s6,96
addiu s6,s4,4
lui v0 D_800B9A02
lhu v0
lui v1 D_800A6610
addiu v1
sw ra,108
sw s8,104
sw s1,76
sw s0,72
sw zero,48
sll v0,v0,0xe
jal
addu s8,v0,v1
```

vh1:
```
addiu sp
lui a0; addiu a0
sw s4,88
lui s4; addiu s4
sw s3,84
lui s3; ori s3
sw s5,92
addiu s5,s4,20
lui v0 D_800B9A02
lhu v0
lui v1 D_800A6610
...
```
The difference: target has `sw s7,100; lui s7` and `sw s2,80; addiu s2` and `sw s6,96; addiu s6` interleaved, while vh1 has them later (after the lhu). So moving the setups after the call changed their scheduling order (the la was fixed but the spill order broke).

Hmm, score 12. But this shows the la position CAN be fixed by moving the call early. Now I need to get the setup order right too. The target's order corresponds to the source order: arg, r, mlo, mhi, c, va, vb, ot, call. If I move the call early, the setups' LUIDs change → different order.

Alternative: keep the source order as target but make the call's la low-LUID another way. Hmm.

Wait — what if I move the call early but ALSO keep the setups in their original source positions (before ot)? I moved the call before the setups. Instead, what if I move ONLY the `arg` assignment to the first statement (already) and the call stays last — that's the original c2, la late.

The la position in c2 was 15-16 (after the setups). The la's LUID = the copy at the call. The copy's LUID is high (call statement). So sched2 put it after the setups.

In vh1, the la's LUID is low (call statement 3) → first. But the setups' order broke.

So the trade-off: to get the la first, the call must be early, which reorders the setups.

Can I move the call early AND keep the setups' order? The setups' order in target is: r, mlo, mhi, c, va, vb — i.e., source order. If the call is early (statement 3), the setups come after the call in source. Their relative order stays r, mlo, mhi, c, va, vb. But sched2's placement of them changed (s7/s2/s6 moved later). Hmm, why? Because the spills are placed based on LUID; the setup insns' LUIDs are now after the call.

Hmm. The target has the setups before the call. So the source order must have them before the call. But then the call's la is late.

Unless... the la comes from a *separate early statement* that survives (the launder's role).

OK so we're back to needing the early set to survive. The launder does it.

Is there ANY plain-C way to make a single-use constant set survive combine? Let me think about combine's behavior: it deletes the first set because the copy uses the REG_EQUAL constant. If the copy's source reg has a REG_EQUAL but combine can't prove... 

What if the variable is assigned *twice* with the second set being a *real different value used elsewhere*, e.g.:
```
arg = &D_800AF648;
...
func_80052E38(arg);
arg = 0;
if (arg) {}  // real use? adds branch
```
No.

What if we use arg as a *loop-carried* variable? no.

What if the first set is a *store to memory* (address taken)? adds.

I think the arg launder is genuinely needed. So item 4 is a WALL.

But wait — maybe there's a trick: the C0414 dead-reset applied to the *call's arg copy* — i.e., name the argument:
```
arg = &D_800AF648;
a = arg;           /* copy */
func_80052E38(a);
a = 0;             /* dead reset of the copy */
```
Hmm, combine would fold a = const and then the call uses a; the dead reset a=0 invalidates the hash entry for the constant... Let me think: cse sees a = arg (arg's value = const) → a = const; the call copies a; then a = 0. The dead reset invalidates a's equivalence at the second set, but the call's use is before. Combine folds the call copy to const and deletes a's set? a's set is dead after the call (a=0 overwrites). Hmm.

Actually, the C0414 pattern is for *memory addresses* passed to two calls. Here it's one call.

Let me try anyway: `arg = &D_800AF648; a = arg; func_80052E38(a); a = 0;` and variants. Cheap.

Also: `func_80052E38(arg);` then a dead reset of arg *immediately*: `arg = 0;` — tested (va1) → 4.

Let me try the copy+reset.
