---
ts: 2026-11-06T14:53:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DoYMQCPjv7kvA3WUdD3d
---
Now I see it! In the jump2 dump (post-reload), the difference is:
- Mine (c1): at line 576, a `jump_insn` with `(label_ref N)` — an unconditional jump. So the `bne t,3` was folded into an unconditional jump.
- Orig: has the asm insn (line 575-581) and then the `jump_insn` with `(if_then_else (ne (reg s0) (reg v1)) ...)` — the conditional branch `bne t,3`.

So the fold happens BETWEEN jump_optimize and jump2 (post-reload). The passes: jump, cse, loop, cse2, flow, combine, sched1, local-alloc, global-alloc, reload, sched2, jump2 (reorg's jump pass).

The `jump2` pass (post-reload jump optimization) does the fold! It's `jump_optimize` called after reload (toplev.c: the `jump2` dump). Let me check: reorg.c or jump.c runs again after reload. The `jump2` dump is from the second jump pass.

So the fold is done by the SECOND jump pass (post-reload), which uses the register allocation. With the asm (launder), the second jump pass sees the asm as a barrier and can't fold.

Hmm, so it's a jump2 fold. The launder prevents it.

Real C: I need something that survives to post-reload and prevents the fold. The asm survives; real C statements are gone by then.

Hmm. Unless the C produces a real insn between the two branches that survives to jump2 and prevents the fold. But the target has no such insn (the asm is empty).

Wait — actually, the fold in jump2 might be preventable by the CONTROL FLOW structure. Let me look at the exact jump2 fold. The jump2 pass (jump_optimize after reload) does `thread_jumps` and `delete_unreachable_code`. It sees:
```
bne s0,5,L71
bne s0,3,L73
```
and knows s0==5 on the fall-through? How? After reload, the register is a hard reg (s0). The jump2 pass's `thread_jumps` might use the condition from the previous branch.

Hmm, but with the asm between, it can't.

So this is the same opacity wall, but at jump2.

Let me reconsider: maybe I can prevent the jump2 fold by making the second branch's target or structure different such that thread_jumps doesn't apply. For example, if there's a label/block boundary between the two branches. The asm creates an insn, not a label.

What if I insert a real insn between the branches that survives to jump2 and is a no-op? There's no C construct that emits a no-op insn... except maybe a `do{}while(0)` (no RTL), a label (block boundary), or an empty statement.

Hmm, what about a label? A `goto` target label between the branches:
```
if (t != 5) goto after;
label:
if (t != 3) goto sel_094;
```
A label creates a basic block boundary. jump2's thread_jumps might not merge across it. But a label with no branch to it might be optimized away. If I make it a real target (e.g., `goto label` from somewhere), it survives.

But the target has no label there. A label doesn't emit an instruction, so the code could still match if the layout is the same! Let me think: a label between the two branches creates a basic block. The jump2 pass wouldn't fold across the block boundary. The emitted code: the label doesn't emit anything, so the instructions are `bne s0,5,L71; bne s0,3,L73` — same as target!

But wait, the target's `bne s0,5,L71` is followed by `bne s0,3,L73`. If I insert a label between them, the assembler emits no instruction for the label. So the code matches! And the block boundary prevents jump2's fold.

But how do I create a label in C between the two branches? The two branches come from `if (t == 5) { if (t != 3) ... }`. I can insert a label at the start of the t==5 block:
```
if (t == 5) {
    chk:
    if (t != 3) goto sel_094;
    ...
}
```
But the label `chk` must be referenced (else it's optimized away). Hmm. If I add `if (t == 3) goto chk;` (as in v13), the label is referenced. But v13 scored 4 (same). So the label didn't prevent the fold. Maybe because the label is in the middle and the fold still applies, or the label was removed.

Hmm, v13's structure was:
```
if (t == 3) goto chk;
if (t == 5) {
chk:
    if (t != 3) goto sel_094;
```
The `chk` label has two predecessors (t==3 and t==5). Yet the output was identical to c1. So the compiler still folded (maybe it recognized the t==3 path makes the check false and the t==5 path makes it true, and merged).

Hmm. So a label alone doesn't prevent it.

Let me think about the jump2 fold more precisely. Let me look at what jump2 does. The fold `bne s0,5,L71; bne s0,3,L73` -> `beq s0,5,L73; j L71` is a "conditional branch simplification" using the known value from the first branch. This is `jump_optimize`'s `thread_jumps` or the `if_then_else` simplification in `jump.c`.

Wait, but the fold happened between .jump (after jump_optimize #1) and .jump2 (after jump_optimize #2). Let me check: the .jump dump (first jump pass) had the 3-branch structure in BOTH. The .jump2 (second jump pass) has the fold in c1 but not orig. So the second jump pass folded it.

The second jump pass runs after reload. It might have MORE information (the register values). Let me look at what it does.

Hmm, actually, maybe the fold is done by `reorg.c` or the `jump2` pass. Let me check toplev.c for the jump2 dump.

Actually, let me look at the jump2 dump's block structure for the case 5 region. The fold is a "jump to jump" threading. Let me look at the c1 jump2 dump around line 560-600 (the region with the unconditional jump).

Let me read the c1 jump2 dump around the case 5 region.

Actually, let me reconsider. The target's `bne s0,5,L71; bne s0,3,L73` — the second branch is redundant. The first jump pass (pre-reload) did NOT fold it (both .jump dumps have 3 branches). The second jump pass (post-reload) folded it in c1 (no asm) but not orig (asm). 

Why didn't the first jump pass fold it? Because pre-reload, the value of t is a pseudo and jump.c's threading might not know t==5. Post-reload, t is a hard register, and... hmm.

Actually, maybe the fold in c1 is not a "known value" fold but a branch-target optimization: the `bne s0,3,L73` where L73 is the target, and after reload, the layout puts L73 elsewhere. Hmm.

Let me look at the c1 jump2 dump around the case 5 region. Let me find the labels. Actually, the diff showed at line 576: mine has `(jump_insn (label_ref N))` (unconditional) where orig has the asm + conditional branch. So mine's second branch became unconditional.

Let me read the c1 jump2 dump around lines 560-590.
