---
ts: 2026-11-06T14:55:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cCJvmT2xO2Q9ABRu7232
---
`thread_jumps`: "find a conditional branch, the label it may branch to, and the branch after that label. If the two branches test the same condition, walk back... If we make it back to the target of the first branch, then we know that the first branch will either always succeed or always fail."

So thread_jumps looks at a conditional branch b1, its target label, and the branch b2 after that label. It threads.

Our case: `bne t,5,L71` (b1), target L71. The branch after L71 (b2) is... the block at L71. But L71 is the "after" block, which starts with `lbu D_801802E4[t]` and then the func_800291B4 call. Hmm, not a branch on t.

Hmm, maybe not thread_jumps.

Let me look at the `delete_dead_code` / `delete_unreachable_code`. Or the `if_then_else` simplification.

Actually, let me look at line 829: `redirect_jump (p, target)` and the surrounding code. Let me read around 800-860.

Actually, let me search for where a conditional jump is turned into an unconditional one based on the comparison operands being known. There's `can_reverse_comparison_p` and `simplify_relational_operation` at line 1492 (cc0 only).

Hmm. Let me look at the `find_cross_jump` (line ~2363) — the cross_jump optimization. The jump2 pass is called with cross_jump=1. Let me read `find_cross_jump` and `cross_jump`.

Actually, the fold `bne t,3,L73` -> `j L73` might be `delete_dead_code` deleting the branch because... no.

Wait — maybe it's not a fold at all. Maybe the C `if (t != 3) goto sel_094;` where the compiler (at the C level) knows t==5 because of `if (t == 5)`? No, the front-end doesn't track.

Hmm, but maybe the front-end's `fold` DOES do some condition tracking for `if` statements? Actually, gcc's `fold` doesn't, but the `expand` might. No.

Let me look at the jump2 dump of the c1 more carefully: the `jump_insn 262` (j L276) has `(nil)` LOG_LINKS. It replaced the `bne t,3`. The `bne t,3` in orig has `(insn_list 260)`. So in c1, the comparison insn 260 was deleted, and the branch became unconditional.

Who deletes the comparison? `delete_dead_code`? Or the cross_jump? Hmm.

Actually, maybe the fold is done by `jump_optimize`'s `delete_dead_code` or the `if_then_else` simplification using `REG_DEAD`/`REG_EQUAL` notes. Let me look at jump.c around line 1800-1900 (the "if (x) ..." handling).

This is a deep rabbit hole. Let me just accept the WALL and do the batch of tries.

Actually, wait. Let me reconsider: the fold might be preventable by NOT having the `if (t == 5)` and `if (t != 3)` in the same basic block. But they are (no label between). The target has the asm between them (an insn, same block).

What if I put the `if (t != 3)` in a SEPARATE basic block (via a label), and jump2's optimization requires them in the same block? Let me test a structure with a label between:
```
if (t == 5) {
    goto chk;
}
goto after;   // wait, need to handle t==3 first
```
Hmm, the C flow. Let me write:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t != 5) {
            goto after;
        }
    chk:
        if (t != 3) {
            goto sel_094;
        }
    sel_054:
        sel = ...;
        goto set_sel;
    sel_094:
        ...
    after:
        ...
```
This has a `chk:` label before the `if (t != 3)`, creating a block boundary. The `goto after` skips to after. The label `chk` is the target of the fall-through of `if (t != 5)`. Hmm, actually the fall-through of `if (t != 5)` is the next statement (chk), so no explicit goto needed:
```
        if (t == 3) goto sel_054;
        if (t != 5) goto after;
        if (t != 3) goto sel_094;
    sel_054: ...
```
This is the target's structure exactly! But without a label, it's one block. With a label before the third if:
```
        if (t == 3) goto sel_054;
        if (t != 5) goto after;
    chk:
        if (t != 3) goto sel_094;
    sel_054: ...
```
The `chk` label is the fall-through target (unreferenced label). The compiler might remove it. If it survives, it creates a block boundary, and jump2 might not fold across it.

But a label emits no instruction, so the code could still match. Let me test this structure (v16).

Also, I need `after:` as a label for the `goto after`. The code after the if is `if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) { goto call_45F; } ...`. Let me restructure the case 5 block.

Actually, the original C:
```
        if (t == 3) {
            goto sel_054;
        }
        if (t == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054:
            sel = (u32)&D_8018C520;
            goto set_sel;
        sel_094:
            if ((func_800291B4(0x40) & 0xFF) == 0) {
                goto call_45F;
            }
            sel = (u32)&D_8018C560;
            goto set_sel;
        }
        if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) {
            goto call_45F;
        }
        ...
```
Let me rewrite the case 5 body with explicit gotos and a label:
```
        if (t == 3) goto sel_054;
        if (t != 5) goto c5_after;
    c5_chk:
        if (t != 3) goto sel_094;
    sel_054:
        sel = (u32)&D_8018C520;
        goto set_sel;
    sel_094:
        if ((func_800291B4(0x40) & 0xFF) == 0) goto call_45F;
        sel = (u32)&D_8018C560;
        goto set_sel;
    c5_after:
        if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) goto call_45F;
        ...
```
This is semantically identical to the original. Let me test it (v16).

The labels c5_chk and c5_after are real labels. The code layout should be the same as the target if the compiler doesn't reorder. Let me test.

Let me generate v16.
