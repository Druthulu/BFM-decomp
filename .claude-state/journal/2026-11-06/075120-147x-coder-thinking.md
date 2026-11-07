---
ts: 2026-11-06T14:51:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hAWCkozCgNv6Xnjce8z6
---
The jump_insn counts are the same between c1 and orig at every stage (72, 62, 62, 58). So cse1 already folded 10 jumps in BOTH? Wait, c1 has the fold (2 branches) and orig has the launder (3 branches). But the counts are the same at each stage. That means the fold difference is NOT in the jump_insn count — maybe the extra branch is represented differently, or the fold happens at expand.

Hmm. Let me look at the .rtl dump (72 jump_insns) for both — the counts are the same. So the front-end/expand produced the same RTL? But orig has the launder asm (1 extra insn). Let me count total insns.

Wait, the target has 279 instructions and c1 has 279. Same count. So the fold doesn't change the instruction count (a `beq` vs `bne`+`j` are both 1 insn; the fold merges 2 branches into 1 branch + 1 j, same count? Let me see: target has `bne t,5,L71; bne t,3,L73` (2 branches). Mine has `beq t,5,L73; j L71` (1 branch + 1 j = 2). Same count! So the instruction count is the same, just the branch types.

OK so the difference is beq vs bne and the jump structure. Let me look at the RTL .rtl dump for the case 5 region in c1 vs orig. The fold (if any) would show as a different comparison.

Let me grep the .rtl dumps for the case 5 comparisons. The t register is a pseudo. Let me find the `(const_int 3)` comparisons.

Actually, let me compare the .rtl dumps directly around the case 5 region. The case 5 is the 6th case (idx 5). In the RTL, the switch dispatch is a table jump. Let me find the block for case 5.

Hmm, this is getting long. Let me step back and think about the actual difference in the final asm:
- mine: `beq s0,v0,L70; ...; beq s0,v0,L73; j L71`
- target: `beq s0,v1,L70; ...; bne s0,v0,L71; bne s0,v1,L73`

Mine: if (t==3) L70; if (t==5) L73; else L71.
Target: if (t==3) L70; if (t!=5) L71; if (t!=3) L73.

These are logically the same. The difference: mine merged `t==5` and `t!=3` into `t==5 -> L73`, target kept them separate.

The merge is a jump.c optimization: after `if (t!=5) goto L71`, the fall-through has t==5. The next `if (t!=3) goto L73` is always true (t==5 => t!=3), so it becomes `goto L73` (unconditional). Then the `if (t!=5) goto L71; goto L73` becomes `if (t==5) goto L73; goto L71` — that's mine! 

So jump.c did this. With the launder (asm) between the two branches, jump.c can't assume t==5 at the second branch (the asm might change t), so it keeps `bne t,3`.

So the pass is jump.c (jump_optimize), and the mechanism is the same: opacity.

Now, the jump_insn counts are the same because the merge replaces 2 branches with 1 branch + 1 j (same count).

So how to prevent jump.c's merge with real C? jump.c's optimization: it sees `bne t,5,L71` then `bne t,3,L73` in sequence, and knows t==5 on the fall-through. This is jump.c's `thread_jumps` or the "second branch" optimization.

Wait, actually, the optimization `if (t!=5) goto L71; if (t!=3) goto L73` -> `if (t==5) goto L73; goto L71` requires knowing t==5 on the fall-through and that 5!=3. This is a conditional-branch simplification in jump.c.

To prevent it, I need jump.c to not know t==5. Again opacity.

Hmm, but maybe jump.c's optimization can be prevented by a different CFG structure. For example, if the two branches are in different basic blocks with a label between them, jump.c might not merge. But a label would create a block boundary and possibly extra code.

Let me think: what if I put a `goto` or a label between the `t!=5` branch and the `t!=3` branch? The C:
```
if (t == 5) goto in5;
goto after;
in5:
    if (t != 3) goto sel_094;
sel_054: ...
```
The `in5` label starts a new block. jump.c's merge works across the fall-through within a block. With a block boundary, maybe it won't merge. But the target has no label between them (the asm is there instead). Hmm.

Actually, the launder asm IS in the target between the two branches. It's an insn, not a label. So jump.c sees the asm between the branches and can't merge.

Real C: can I put a harmless insn between the branches that jump.c won't remove? A `do{}while(0)` produces no RTL. A label creates a block boundary but might be optimized away.

What if I add a real but dead computation between the branches? jump.c might delete it (dead code) before the merge optimization. Or it might keep it.

Hmm. What if I add a `nop`-like statement that survives? There's no such thing in C.

OK, let me look at the exact jump.c optimization. Let me find it in jump.c. Search for the conditional-branch merge. Actually, the merge might be in `jump_optimize`'s "delete unreachable code" or `thread_jumps`.

Let me look at the .jump dump (after jump_optimize) for c1 vs orig to see the branch structure. The .jump dump is after jump_optimize (line ~2920). If the merge happened by then, jump.c is the culprit.

Actually, the jump_insn counts at .rtl and .cse are the same (72 -> 62). So jump_optimize reduced 10 jumps. Both c1 and orig. So the merge difference isn't visible in the count.

Let me look at the actual .rtl dump for the case 5 region in c1 and orig. Let me find the comparison `(const_int 5)` in the .rtl.

Hmm. Let me grep for "const_int 5" in the .rtl dumps and look at the context.

Actually, let me try a more direct approach: I'll try to find a C formulation that produces the target's `bne t,5; bne t,3` structure. The key is to make jump.c NOT know t==5 on the fall-through of the first branch.

What if the first branch is on a DIFFERENT variable that's equal to t but jump.c can't relate? E.g., `if (u != 5) goto after;` where u == t. Then jump.c records u==5, not t==5. Then `if (t != 3)` can't fold (it doesn't know t==5)! 

But the emitted code must be `bne t,5,after` (the target uses t in the comparison). If I use u, the comparison would be on u's register. If u and t are the same register (copy-propagated), then jump.c sees `bne t,5` anyway and records t==5. Hmm.

Unless u is a separate pseudo that local-alloc later coalesces to the same register as t. Then the RTL comparison is on u, jump.c records u==5, and the t!=3 check can't fold. Then local-alloc assigns u and t the same register (since they're equal/copies), producing `bne s0,5` and `bne s0,3`. That could match!

So: introduce a copy `u = t;` and use u in the `t == 5` check. The compiler might copy-propagate u=t (cse), making u the same pseudo. Hmm. To prevent copy propagation, use the do-while(0) split or a real computation.

Actually, if cse copy-propagates u=t, then u and t are the same pseudo, and the check becomes `t != 5`. jump.c records t==5. Fold.

To prevent cse from propagating u=t, I can put the copy in a do-while(0) block (C0535 EBB split). Then cse doesn't propagate. jump.c sees `bne u,5` and records u==5. Then `bne t,3` can't fold (t is a different pseudo). local-alloc/global-alloc might coalesce u and t to the same register (since u=t is a copy). Then the code is `bne s0,5; ...; bne s0,3`. 

But wait — the target's code has `li $2,5` in the delay slot and the comparison `bne $16,$2,$L71` uses t ($16) and 5. If u is a separate pseudo coalesced to $16, the comparison would be `bne $16,5` (u in $16). Same. And the t!=3 check uses t ($16). Same register. So the code could match!

But there's a risk: the copy `u = t` emits a `move` instruction (extra). Unless the copy is coalesced away by local-alloc/global-alloc (copy propagation). If u and t are assigned the same register, the move becomes a self-move and is deleted. 

This is a promising idea! Let me test:
```
if (t == 5) {
    s32 u;
    do { u = t; } while (0);  // !FAKE: do-while
    if (u != 3) goto sel_094;
    ...
}
```
Hmm, but the `if (t == 5)` uses t, and inside I copy u=t. The copy might still be propagated by cse if the do-while(0) doesn't split. Let me test with and without the do-while(0).

Actually, simpler: change the `if (t == 5)` to use a copy `u` that's computed earlier:
```
s32 u;
...
u = t;   // before the checks
if (u == 5) {
    if (t != 3) goto sel_094;   // t != 3, and jump.c knows u==5 but not t==5
}
```
Hmm, jump.c knows u==5 on the fall-through. It doesn't know t==5 (t and u are different pseudos). So `t != 3` can't fold! And if u and t are coalesced to the same register, the code matches.

But wait — the target's check is `if (t == 5)`, and the comparison is on t. If I use u, the comparison is on u. If u and t are the same register, fine. But the copy `u = t` must be free (coalesced). Let me test.

Actually, the target's `bne $16,$2,$L71` compares $16 (t) with 5. If u is a copy of t and coalesced to $16, then `bne u,5` = `bne $16,5`. Same.

But the target also has `beq $16,$3,$L70` (t==3). If I keep that on t, and the u==5 check on u, then jump.c records u==5 (not t==5), and the `t != 3` can't fold. 

Let me try this. The C:
```
        if (t == 3) {
            goto sel_054;
        }
        u = t;   // copy
        if (u == 5) {
            if (t != 3) {
                goto sel_094;
            }
        sel_054: ...
```
Hmm, but `u = t` then `u == 5` — cse might propagate u=t and make it `t == 5`. To prevent, use a do-while(0) or a real computation.

Let me test both:
- v14: `s32 u = t; if (u == 5) { if (t != 3) ... }`
- v15: `do { u = t; } while (0); if (u == 5) { if (t != 3) ... }`

Wait, but if cse propagates u=t, then u and t are the same and the fold returns. Let me test.

Also, there's a subtlety: the target's `if (t == 5)` check is on t. If I use u, and u is coalesced to the same register, the code matches. But if not coalesced, there's an extra move.

Let me test v14/v15.

Actually, hold on. Let me reconsider: jump.c's record of u==5 on the fall-through of `if (u != 5)`. Then `if (t != 3)` — t is a different pseudo. Can jump.c know t==5? It would need to know t == u. If cse recorded u == t (from the copy), then yes. But if the copy is split by do-while(0), cse doesn't know. So jump.c can't fold.

But local-alloc later coalesces u and t (same register), and the move is deleted. 

Let me test v14 and v15. This is a real-C move (temp/copy). Let me generate.

I need to declare `u` (s32) at the function top or in the block. Let me add `s32 u;` to the declarations.

Let me write v14 and v15.
