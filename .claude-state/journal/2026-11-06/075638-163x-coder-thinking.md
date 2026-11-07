---
ts: 2026-11-06T14:56:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZXtVxakiYeoUjsiAxun5
---
All 4 or worse. w8 (wrong semantics) 34, w10 32.

I've now done: c1, v2, v3, v4, v6, v7, v8, v9, v13, v14, v15, v16, w1-w15 = 27 scored tries. Plus the baseline. Close to 30.

Let me do 3-4 more meaningful tries, then record the WALL.

Actually, let me reconsider whether the fold is preventable at all. The key: jump2 folds `bne t,3` given t==5 on the fall-through. The launder asm is between them. Real C can't insert an insn.

BUT — what if the second check is in a block that's NOT the direct fall-through? E.g., if there's an unconditional jump between the `bne t,5` and the `bne t,3`. Like:
```
if (t == 5) goto in5;
goto after;
in5:
if (t != 3) goto sel_094;
```
Here, `bne t,5,after` (t!=5 -> after), then `j in5` (unconditional), then `in5: bne t,3,sel_094`. The `bne t,3` is in a block reached by the unconditional `j in5`, not the fall-through of `bne t,5`. jump2's value tracking on the fall-through of `bne t,5` records t==5, but the `bne t,3` is reached via the `j in5` — does jump2 propagate t==5 through the unconditional jump? If the `j in5` is on the fall-through path (t==5), then yes, it might. Hmm.

But the target has NO unconditional jump between them. So even if this prevents the fold, the emitted code would have an extra `j`. Unless the compiler removes the `j in5` (jump to the next insn). If `in5` is the next block, the `j` is redundant and removed, restoring the fall-through. Then jump2 folds again.

Hmm.

What if the `in5` block is placed elsewhere (not the next block)? Then there'd be a `j`, differing from the target.

OK, I'm confident it's a WALL.

Let me do 3 more tries (e.g., the switch restructure) and then record.

Actually, let me try the switch restructure (v17) since it might naturally produce the branches.

```
        switch (t) {
        case 3:
            goto sel_054;
        case 5:
            if (t != 3) goto sel_094;
            goto sel_054;
        }
        if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) { goto call_45F; }
        ...
    sel_054:
        ...
```
Hmm, the switch would compile to comparisons `beq t,3; beq t,5`. The inner `if (t != 3)` — the compiler might fold (t==5 from the case). Let me test.

Let me also test a version where the inner check is `if (t != 3)` but the outer is a switch.

Let me do v17 (switch) and v18 (switch with fallthrough) and v19 (the `sel` variable used).

Let me generate and score.
