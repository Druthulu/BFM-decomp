---
ts: 2026-11-06T03:12:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NBPDa4NX5NnYcFR9fLbt
---
All 6 (merged). The cross-jump is robust. n2 (two separate ifs) broke the merge but changed the structure/regs.

Let me think about n2 more: it has 113 ins and the correct tail separation, but:
- mine: bgez v1,4c08 vs target j 4c08 (structure differs: the second if's test is re-evaluated as a conditional).
- register allocation differs.

What if we write the two ifs but with the second one's condition such that the compiler emits `j`? Hmm.

Alternative: use the if-else but make the *else* arm's block not fall through to REST by making the else's body end with a `goto REST` (explicit)? That emits a jump — but maybe the compiler merges it into the fall-through? An explicit `goto REST;` at the end of the else body: the jump targets REST which is the next insn → jump-to-next → deleted early. So it wouldn't block the cross-jump at jump2 (the jump is deleted before cse/jump2). Hmm, but the label REST... 

What if the else body ends with a `goto REST` where REST is NOT next because something is between? In the target, REST is right after the else.

Hmm, what about the structure where the else arm ends with a *store* that the target also has? No.

Let me reconsider n2's score 8 (MIXED). The register allocation difference: target uses v0 for d, mine uses v1. This might be fixable with a C move (declaration order, temp forms). But n2 also has the structural `bgez` vs `j` difference (1 insn). Actually the diff showed:
- mine[29] bgez v1,4c08 vs target j 4c08 (1 insn differs)
- plus register pairs.

If we could fix the registers and the bgez→j, we'd match. The bgez comes from the two-if structure (the second `if (d < 0)` is tested after the first if). The target's `j 4c08` is from the if-else. So n2's structure is inherently different.

What if we write:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
} else {
    d = buf1 - unkA;
    if (d > 0x200) goto TAIL;
}
```
(current, merges) vs:
```
if (d >= 0) {
    if (d > 0x200) goto TAIL;
    goto REST;
} else {
    d = buf1 - unkA;
    if (d > 0x200) goto TAIL;
}
```
The explicit `goto REST` at the end of the if-body — the compiler would emit the same `j REST` (it's already there). No change.

What if the else arm's body is moved into a separate function? no.

Hmm, what about making the *else* arm's block end with a real insn that the target has: the target's else block is subu; slti; beqz; nop. The nop is the delay slot (filled by reorg after jump2). At jump2, the else block ends with the beqz. 

What if the else arm's `if (d > 0x200) goto TAIL;` is written as `if (d > 0x200) goto TAIL; else goto REST;`? The else goto REST is a jump to the next insn → deleted early.

What if the else arm's test is written with a `switch`? no.

What if the else arm's d computation and test are wrapped in a do-while with a break to TAIL? e.g.:
```
} else {
    d = ...;
    do {
        if (d > 0x200) break;
    } while (0);
    goto TAIL;   // ???
}
```
Hmm, no.

Let me look at the target's else block once more: 4bf8 subu v0,v1,a0; 4bfc slti v0,v0,513; 4c00 beqz v0,4d04; 4c04 nop; 4c08 (REST). The else block's test branches to TAIL (4d04). The fall-through is REST.

What if the original C's else arm had the test as `if (d > 0x200) goto TAIL;` and the compiler's cross-jump *did* merge in the original too, but the target we compare against is the *build/* object which was built from the current src WITH the barrier. Wait! The target is build/ = the tree's own bytes, which were built from the current src including the barrier! So the target IS the barrier build. Our job is to find a lever-free body that matches the barrier build's bytes. Right — the build/ object was compiled from the src with the barrier.

So the target's separate tails are exactly what the barrier produces. The question is whether a lever-free C can produce the same bytes. The barrier's effect: it's an ASM_INPUT insn between the else's test and REST, blocking the cross-jump.

So we need a lever-free insn that emits zero bytes between the else's beqz and REST. That's hard: any real insn emits bytes. Unless... the else's beqz block ends with a NOTE? Notes are skipped.

Hmm, but maybe we can prevent the cross-jump by making the if-body's `j REST` not cross-jumpable: e.g., if the label REST has multiple predecessors or is not immediately after the else. 

What if REST's label is preceded by a *different* insn due to the C structure: e.g., add an empty statement that generates a label? no.

What if the else arm's test is moved so that REST is preceded by the else's *subu* instead of the beqz? E.g., reorder the else body:
```
} else {
    if ((d = buf1 - unkA) > 0x200) goto TAIL;
}
```
Same order (subu then slti then beqz).

What if we write the else as:
```
} else {
    d = buf1 - unkA;
    if (d > 0x200) goto TAIL;
    /* fall through */
}
```
same.

Hmm, what about making the if-body's `j REST` target a different label that is NOT REST: e.g., a user label placed just before REST with some code? In the target, the if-body jumps to 4c08 (REST). If we add a user label at REST and jump to it, same.

What if the if-body's end jumps to a label that is followed by an insn that's already there... 

Let me try a different structural approach: make the first arm's inner test a `goto TAIL` and the else's inner test a `goto TAIL`, but put a *real* statement between the else's test and the merge point that emits an insn the target also has. Looking at the target after the else: REST starts with `lw v0,224(s1)` (timer). The else's beqz's delay slot is nop. So nothing.

OK, maybe the trick is to prevent the cross-jump by making the if-body's jump target not REST but a label whose predecessor is different. What if the if-body ends with `goto AFTER` where AFTER is a label placed at REST but with the else body *after* REST? That would reorder the else body after the rest — changing layout.

What if we swap the if and else bodies (write the d<0 arm first)? n1 gave 6 (merged).

Hmm.

Let me look at the cross-jump more carefully: it merged the if-body's `j REST` with the else's fall-through by matching the beqz (and maybe the slti). The minimum=1. If we make the if-body's block end with a *different* jump target whose predecessor is not the else's beqz... e.g., if the if-body jumps to a label that is placed at the *start* of REST but with a `nop`? no.

What if we make the else's test branch to a *different* label than the if's? Both go to TAIL in the target (4d04). If the else's goto TAIL were a different label that later falls into TAIL... e.g., a user label `TAIL2:` right before TAIL. Then the else's beqz targets TAIL2, and the if's targets TAIL. The beqz insns would differ (different label refs) → cross-jump fails! And codegen: both labels at the same address → both branches encode the same target (4d04)! The label TAIL2 would be at the same address as TAIL; the assembler emits the same branch. And the extra label costs nothing.

That's a promising trick: give the else arm's `goto TAIL` a distinct user label that resolves to the same address.

In C:
```
    if (d >= 0) {
        if (d > 0x200) goto TAIL;
    } else {
        d = ...;
        if (d > 0x200) goto TAIL2;
    }
    ...
TAIL:
    timer = ...;
    ...
TAIL2:
    ??? 
```
Hmm, TAIL2 must be at the same address as TAIL. If I write `TAIL: TAIL2:` consecutive labels, both at the same address. The else's goto TAIL2 and the if's goto TAIL → different LABEL_REFs → at jump2 the beqz insns differ (label_ref to different labels) → no cross-jump! And after the labels are combined by the assembler/final, both branches target the same address.

But careful: jump.c's "combine consecutive labels" merges LABEL_NUSES; the labels are consecutive, so the assembler emits one label at the address. The branch encoding uses the same address. 

Also, the *first* jump pass may combine the labels and redirect the branches to one label (mark_jump_label + "combine consecutive labels"?). Hmm, jump.c does combine consecutive labels (`if (LABEL_NUSES... )`). Let me check: jump_optimize's "Mark the label each jump jumps to. Combine consecutive labels, and count uses of labels." If it combines TAIL and TAIL2 into one label, both branches would target the same label → identical beqz → merge again. Hmm.

But the combine happens only if one label is unreferenced? Let me look at jump.c's label combining. Search "Combine consecutive labels".
