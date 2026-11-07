---
ts: 2026-11-06T13:01:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FDQwtspiSfddInQdsbqQ
---
Item 4: mine 189 vs target 196 (7 short). The real delta at mine[107:108] vs target[107:115]:

mine:
```
107 j 210
```
target:
```
107 lw v0,28(s0)
108 nop
109 addiu v0,v0,1
110 sw v0,28(s0)
111 slti v0,v0,16
112 beqz v0,28c
113 nop
114 j 2dc
```

So the target has the case-3 body duplicated (7 insns) that mine jumps to a shared copy of (cross-jumped with case 0's identical body). Yes — exactly the documented wall.

So items 3 and 4 are the same class: jump2 cross-jump merges a byte-identical arm; the empty asm blocks it.

Item 5 is the twin of item 2.

Hmm, this shard is essentially all walls. But the brief wants me to try real-C moves. Let me think harder about cross-jump cracking, because items 3 and 4 (and item 2/5) would all fall if I find the trick.

For cross-jump: `find_cross_jump(e1, e2, minimum=2, ...)`. The scan goes backward from e1 (the conditional jump) and from e2 (the block before the jump target). It stops at a CODE_LABEL (decrementing minimum) or a mismatch.

Key insight: a CODE_LABEL between the matching insns stops the merge IF fewer than `minimum` insns matched. Each match decrements minimum by 1. So with minimum=2, we need 2 matching insns to merge. A label appearing after 1 match leaves minimum=1 → no merge. A label appearing after 2 matches leaves minimum=0 → merge happens.

In item 4's case, the duplicated block is 7 insns (lw, nop, addiu, sw, slti, beqz, nop? plus j). Actually the target's duplicated block: lw v0,28(s0); nop; addiu v0,v0,1; sw v0,28(s0); slti v0,v0,16; beqz v0,28c; nop; j 2dc. Hmm, the merged region is several insns.

To stop the merge we'd need a CODE_LABEL early in that sequence. A label in C = a goto target. Could I add a label in the middle of the duplicated block? The block is:
```
unk1C += 1;
if (unk1C >= 0x10) goto C78;
goto TAIL;
```
A label between `unk1C += 1` and the if? E.g.:
```
L: unk1C += 1;
```
That label would be at the start of the block, not in the middle.

Hmm, but what about a label *inside* the RTL sequence: `unk1C += 1` expands to lw, addiu, sw. A label can only be at a statement boundary.

So: `L_case3: ...` before the increment. The label would be at the block start, i.e. before the first of the 7 insns. That wouldn't stop the scan (it stops when it *hits* the label going backward, after matching all 7 → minimum would be 2-7 = negative → merge).

So a label at the start doesn't help.

What about a label between the `if` and the `goto TAIL`? That's where the barrier is. The RTL there: after the `if (>= 0x10) goto C78` block ends (a branch), then a label, then `goto TAIL`. Hmm — actually the merge region in target is [lw, nop, addiu, sw, slti, beqz, nop, j]. Hmm.

Honestly: `if (x) goto C78;` + `goto TAIL;` — in RTL this is a conditional jump to C78 and an unconditional jump to TAIL. Cross-jump compares the block *before* the unconditional jump `goto TAIL` (i.e., the insns before it, which include the conditional branch? no...).

Let me look at what mine merged: mine[107] `j 210` vs target's 7 insns. So mine has `j 210` where the target has the whole body then `j 2dc`. So the cross-jump merged case 3's tail with case 0's tail (at 210?), replacing case 3's copy with a jump to the shared copy at 210.

Hmm, wait: mine jumps to 210 and the target's case-3 copy is at 1ac..? and jumps to 2dc.

Anyway, the barrier prevented the merge.

Now: is there a real-C way to make case 3's tail differ from case 0's? Looking at the source: case 0's tail is identical C. What if I write case 3's increment differently, e.g. `((Unk*)param_1)->unk1C += 1;` → same.

What if I use a different field access type (u16 vs s32)? unk1C is s32.

What if I reorder case 3's statements? e.g. put the increment after the if? No.

Hmm, what if I change the switch's case order (case 3 before case 0)? That changes the whole layout.

Let me check what case 0 looks like exactly. Lines 60-66 in item 4's orig (I saw them). Let me look at the fuller context around case 0 and case 3.

Actually, from the earlier read:
```
        if ((((Unkstruct_800B5CB8 *)param_1)->unk1C & 3) == 0) {
            func_80143B6C(param_1, 1);
        }
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C >= 0x10) {
            goto C78;
        }
        goto TAIL;
```
and case 3:
```
        ((Unkstruct_800B5CB8 *)param_1)->unk1C += 1;
        if (((Unkstruct_800B5CB8 *)param_1)->unk1C >= 0x10) {
            goto C78;
        }
        <BARRIER>
        goto TAIL;
```

So the two tails are identical C. The compiler merges them.

Real-C route: make case 3's tail use a *different* spelling that yields the same target instructions but a different RTL for cross-jump... but cross-jump compares RTL after renumbering, so identical RTL → merged. The target's instructions for case 3's tail are identical to case 0's tail (that's why they'd merge). The only difference is the barrier.

So it's a WALL by construction: the target has duplicate identical code, which only an asm (or a label) can prevent the compiler from merging. And a label can't be placed mid-sequence.

Wait — but could a label be placed such that it lands mid-sequence? What if I add `if (0) { L: ; }`? Hmm.

Actually! What about a *loop*? `do { ... } while (0)` creates a CODE_LABEL at the loop end (for the backward branch). If a label landed between the slti and beqz... no.

What if the tail is wrapped in a do-while(0) so a label is placed *before* the goto TAIL? Let's see:
```
do {
    unk1C += 1;
    if (unk1C >= 0x10) goto C78;
} while (0);
goto TAIL;
```
The do-while(0) adds a label at the end of the loop body (the branch target). jump_optimize would delete the useless branch and the label (LABEL_NUSES=0). Hmm, but C0535 says it survives cse1.

Actually, maybe worth trying: for item 4 the merge region includes the whole tail, so even if a label appears at the end of the loop body (right before `goto TAIL`), the backward scan from `goto TAIL` would hit the label immediately (0 matches) → minimum 2→1, break → no merge! That would be exactly what we want!

Let me try:
```
case 3:
    do {
        unk1C += 1;
        if (unk1C >= 0x10) goto C78;
    } while (0);
    goto TAIL;
```
Hmm, but jump_optimize runs AFTER cse1 and before... wait, jump2 is the second jump_optimize pass (after regscan/reload?). Let me check: line 3142 `jump_optimize (insns, 1, 1, 0)` is after reload (cross_jump=1). And line 2827/2929 are earlier passes. The cross-jump that merges arms happens at jump2 (after reload). Labels are removed by then if unused.

But C0535's do-while EBB split works at cse1 (which is before jump2). So a do-while label wouldn't survive to jump2.

Hmm, unless the do-while leaves a real branch that survives to jump2.

Let me just try it empirically — cheap.

Another idea: make the two tails differ by ONE instruction in a way that the target also has. Not possible.

Another: make case 3's tail a *loop* that jump2 can't merge: e.g.
```
while (1) { unk1C += 1; if (unk1C >= 0x10) goto C78; break; }
```
Hmm, adds insns.

Let me try several for item 4:
d1: do-while(0) around the increment+if.
d2: do { unk1C += 1; } while (0); then if...
d3: wrap with `if (1) { ... }`.
d4: reorder: `if (unk1C + 1 >= 0x10)`.
d5: use a temp: `s32 v = unk1C + 1; unk1C = v; if (v >= 0x10) goto C78;`
d6: `goto TAIL;` → `if (1) goto TAIL;`? folded.

Let me try these quickly.

Actually, first let me reconsider: is the merge in item 4 between case 0 and case 3, or between case 3 and something else? mine[107] j 210 — target 1ac? The target's case-3 copy is at 1ac (from `bnez v0,1ac`). Hmm.

Whatever. Let me test d1-d5.
