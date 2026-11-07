---
ts: 2026-11-06T12:16:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JNlVKoAUWCSf22eOxRGp
---
My candidate is byte-identical to target except the top 6 insns (and the branch offsets at d6c/d64). Wait, the diff showed mismatches only at top and the bnez target offsets (d64 vs d6c) — the offset difference is because target has 2 more insns (156 vs 154) — no wait, target is 156 insns, mine 154. Hmm, where are the 2 extra? The diff showed at insn 118-125 region a difference in the branch structure. Let me compare that region.

Target around cdc-cfc:
```
cdc: beqz v0,cfc
ce0: li v0,4095
ce4: lui v1 (D_801909C4)
ce8: lw v1
cec: lui at (D_801152AA)
cf0: sh v0
cf4: j d14
cf8: addiu v0,t4,2
cfc: lui v1 (D_801909C4)
d00: lw v1
d04: li v0,-4095
d08: lui at
d0c: sh v0
d10: addiu v0,t4,-2
d14: sh v0,2(v1)
```
Mine:
```
118 beqz v0,cf4
119 addiu a0,t3,2
...
122 j d04
123 li v0,4095
124 addiu a0,t3,-2
...
130 sh a0,2(v1)
```
So mine computes the address earlier (addiu a0) and the store uses a0, target computes into v0 later. That's a scheduling/copy difference.

The key difference: target's b4b (D_801909C4 load) is done inside each branch after the D_801152AA store, and var_v0_3 computed as v0 = t4±2 in the delay slot of the jump. Mine does it differently.

OK. So the real gap is only the top: register assignment of the arg copies and the a1v shape, plus the tail scheduling.

Total score 21 (COUNT-based, counting mismatched insns after alignment). The tail mismatches (83,88,94,99,101,103,113) are just branch target offsets caused by the 2-insn difference? Wait no, score counts register/insn mismatches; branch targets differ due to code layout shift of 8 bytes (2 insns). The 2 extra insns in target are... target 156 vs mine 154. Where? In the tail branch, target has `addiu v0,t4,2` in delay slot at cf8 (mine has `j d04; li v0,4095; addiu a0,t3,-2`). Hmm, both have similar counts.

Let me diff structurally. Let me extract the two function listings and diff them. I'll use a small python script under the item dir to strip addresses and compare. Actually the diff tool already did that. The main fixable difference is the top 6 insns. If I fix those, the rest may follow.

Goal: get `move t3,a1` and `andi a1,a1,0x1`, `move t4,a2`.

So I need arg1's copy to be allocated t3 and arg2's copy t4, plus a1v computed into a1.

Idea: introduce `s32 a1v = arg1;` but with a real second set to prevent coalescing: e.g.
```
s32 a1v = arg1;
if (!(a1v & 1)) ...
```
coalesces. 

What about using a1v = arg1 & 1 exactly:
```
s32 a1v = arg1 & 1;
...
if (!a1v)
```
Then the code has a value `a1v` that must be in a register; gcc will compute andi into some reg. If arg1 must stay live (used later), gcc keeps arg1 in a1 and computes a1v into another temp (v0). Target instead has the copy of arg1 to t3 FIRST, then andi a1. That means gcc chose to free a1 by copying arg1 to t3, then compute a1v into a1. That's plausible if the copy of arg1 has higher allocation priority than a1v... Actually local-alloc: arg1 is a parameter pseudo with many refs; it might prefer a1. Hmm.

Wait, actually: maybe in target the source was `a1v = arg1` (the launder) and gcc's behavior: a1v in $5. The asm has an output operand "=r" tied to arg1, so after the asm, arg1's pseudo (a0? no, $5) — the asm says a1v is in the same register as arg1's *input*. Since arg1's value is in a1, the asm output a1v is also in a1. This is a hard-reg asm, so gcc must materialize arg1 in a1 at the asm. Then a1v in a1. Later uses of arg1 need arg1 in some register but a1 is now "occupied" by a1v until... a1v dies at the first test. Hmm, but arg1 is used later, so gcc must copy arg1 out before a1 is overwritten by a1v? Actually a1v and arg1 both in a1 — same value. The asm says: a1v gets whatever is in arg1's register. The compiler knows a1v's value equals arg1's? No! With "=r" output and "0" input, gcc knows a1v is the output, and it may or may not know the value. The asm is opaque: gcc assumes a1v is a NEW value, not equal to arg1. So arg1's later uses need a separate copy: `move t3,a1` before the asm. That's the move at insn 2!

So the mechanism: the launder creates a fake new value, forcing arg1 to be copied for later use. To replicate lever-free with real C: we need a genuine computation producing a new value used for the first test, while arg1's original value is used later.

If we write `s32 a1v = arg1 & 1;` then arg1's later uses need arg1 live; gcc would keep arg1 in a1 and compute a1v in v0 — that's what I guessed. But maybe gcc's local-alloc prefers to give a1v the a1 register (since the andi's input is a1, it's natural to write in place `andi a1,a1,1` — a destructive op!). And then arg1 needs a copy. gcc's local-alloc does exactly this kind of "combine into the same register" if the pseudo dies. Does arg1 die? No, used later.

Hmm, but gcc's allocation might still pick a1 for a1v because a1 is the "preferred" reg (from the andi's input). It then copies arg1 to t3. This is exactly target! Let's try `s32 a1v = arg1 & 1;` and `if (!a1v)`.

But careful: is it legal? `!(a1v)` where a1v = arg1 & 1: `if (!(arg1 & 1))` same semantics. Good.

Also `s32 pos = arg2;` — target move t4,a2. In mine, pos got t3. If arg1's copy takes t3, pos should get t4. 

Let me try a2.c:
```
s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    ... decls
    s32 a1v;
    s32 pos;
    a1v = arg1 & 1;
    pos = arg2;
    if (!a1v) { ... }
```
But careful about the order of the moves: target has move t2,a0 (arg0 copy — from uses of arg0 later), move t3,a1, andi a1,a1,1, bnez, move t4,a2 (delay slot). So pos=arg2 is assigned in the branch delay slot after the bnez! That means gcc scheduled pos=arg2 into the delay slot, i.e., pos is set after the bnez. In my source pos is assigned before the if. gcc's reorg put it in the delay slot. Fine.

Also, in the source the a1v assignment is before the if; the andi is at insn 3.

Let me write a2.c accordingly: declare `s32 a1v = arg1 & 1;`? Init at decl might place it. Use `s32 a1v = arg1 & 1; s32 pos = arg2;` — the declaration init order. But the target order: move t3,a1 (arg1 copy) happens before andi. Where does the arg1 copy come from? gcc inserts it when arg1 is needed later — the copy would be emitted at the point where a1v takes over a1... likely right before the andi. Then move t4,a2 for pos. But target order is: move t3,a1; andi; bnez; move t4,a2 (delay). So pos's move is after the bnez. That's scheduler/reorg.

Let me just try it.

Also need to check the tail region mismatch after fixing the top. Let's go.
