---
ts: 2026-11-06T22:31:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sFPYCIjy0b4NDcdjX8wR
---
The target (pinned) asm:

```
subu $sp,$sp,32
move $2,$4        # arg0 -> $v0
sw $16,16($sp)
move $16,$5       # d = arg1 -> $s0
sw $31,24($sp)
sw $17,20($sp)
lh $3,14($2)
lh $4,D_80126CB8
lh $5,6($2)
lw $2,32($2)
subu $4,$3,$4
lh $3,D_80126CB4
lh $17,18($2)     # s1ang raw -> $s1
jal ratan2
subu $5,$3,$5
addu $2,$2,-1024
andi $4,$2,0x0fff   # u5 -> $a0
sll $16,$16,16      # d cast
andi $17,$17,0x0fff # u6 = s1ang & 0xFFF -> $s1
bne $17,$4,$L72
sra $16,$16,16
...
```

So target: d=$s0 (hard pin), s1ang raw=$s1, u5=$a0, u6=$s1, iVar4=$v1, q/t temps $v0/$v1.

Now lever-free w0:
- d=$s1, s1ang raw=$s0, u5=$v1, u6=$s0, iVar4=$a1.

Hmm, interesting: u5 in w0 is $v1 and iVar4 is $a1, vs target u5=$a0, iVar4=$v1. That's a consequence of d occupying $s1 and the different priority. Actually in w0's alloc table: r78 (10 refs/10 ins, conflicts v0,sp, prefers a1) = iVar4? r80 (4/4, prefers v0) = u5? Let's map from greg order 78 80 79 74 77 76:
- r78: 10 refs, 10 ins, dies in 2, conflicts v0,sp, prefers a1 → probably iVar4 (u5-u6 then modified in both arms) — in target iVar4=$v1. Hmm but r78 gets... .greg order first = r78. It conflicts v0 and sp; available regs include a1 (preference). In w0 asm iVar4 = $a1 indeed.
- r80: 4 refs, 4 ins, prefers v0, conflicts sp → u5? In w0 u5 = $v1. Hmm r80 got? Actually u5 = $v1 in w0 asm. r80 pri 20000 (4 refs, 4 live → 4*5000=20000). It prefers v0 but conflicts v0 → takes v1? Yes u5=$v1.
- r79: 7 refs/8, conflicts v0,sp, prefers a1 → this is `u6`? no u6 is r77. Hmm. r79 maybe the divisor-related? Let's see: u6 = s1ang & 0xFFF = r77 (5 refs/10). r79 (7 refs/8) could be... `q`? q = iVar4/d then possibly 1/-1. Hmm.

Anyway, the key structural difference: d gets $s1 instead of $s0, and then everything else shifts.

Goal: get d into $s0. The blocker: r75 = s1ang raw is block-local, crosses the call, local-alloc gives it $s0.

Idea: make the s1ang raw value a global pseudo instead of block-local. If we make it live across a basic block boundary, local-alloc won't allocate it; global-alloc will. Then global-alloc would allocate r75 alongside d. d has 9 refs/27 ins (pri 10000 at the 10000 cap? Actually pri caps at 10000? The table shows 10000 for several. Hmm, pri formula: floor(1e6? )). r75 with 2 refs/7 → pri 2857. So d (pri 10000) would be allocated before r75 → d gets $s0, r75 gets $s1 (or $s0 if d's live range ends... no).

How to make s1ang raw global without changing the code's semantics/instruction stream? Move the `u6 = s1ang & 0xFFF;` into a different basic block than the load. The load is in block 0; the & is currently also block 0 (insn 69). If we place u6 computation inside an if-branch... but it's used in `if (u6 == u5) return 0;`. 

Hmm, what if we restructure: `if ((s1ang & 0xFFF) == u5) return 0; u6 = s1ang & 0xFFF;` — that duplicates the & expression. The first use would be computed at insn 69 (block 0), and the second... but the second is in the else block. However, the value s1ang would still be used in block 0 only? No: the second use of s1ang is in the block after the return, which is block 2 (the fallthrough). That makes s1ang live into block 2 → global.

But that duplicates the andi. The target has one andi. Unless cse merges them... cse would merge into one value in the same block, but the second use is in a different block; cse can still merge if the first computation dominates. It does dominate (block 0 → block 2). So cse would compute u6 once in block 0 and reuse it — making it block-0 again? Hmm, but cse keeps the value in a register across blocks, making it global! Actually cse1 (local cse) operates within extended basic blocks; the value would be a pseudo live across the block boundary → global alloc.

Wait, but the current code already has u6 computed once and used in block 0 (compare) and in block 2 (iVar4 = u5 - u6). So r77 is already global (it's in the .greg order). The problem is r75 (s1ang raw) is block-local because its only use is the andi in block 0. If we make s1ang raw used in a later block directly (without the andi), then r75 becomes global.

Alternative: change `u6 = s1ang & 0xFFF;` to use s1ang later. E.g., compute `iVar4 = u5 - (s1ang & 0xFFF)` and also `u6 = s1ang & 0xFFF`... duplicates but cse merges.

Hmm, but the fundamental issue: we need s1ang raw to be live across the call and assigned a callee-saved register, while d gets $s0. If s1ang raw becomes global with pri 2857 and d pri 10000, d is allocated first → $s0, then s1ang raw → conflicts $s0 → $s1. That's exactly the target! And u6 (r77) would then prefer s0? r77 conflicts: 74 76 77 78 80 2 29 — no s0, and prefers 16. If d takes s0, r77 conflicts d? r77 conflicts 74 (=d) yes! So r77 can't take s0. Then it gets s1? But s1ang raw (r75) would have s1... r77 conflicts r75? r75 is not in r77's conflict list currently because r75 is local-alloc'd after? Hmm, if r75 becomes global, conflict lists change. Let me just try.

Wait, actually in the pinned target, u6=$s1 and s1ang raw=$s1 — same register! Because r75 (raw) dies at the andi (insn 69), and r77 (u6) is born there. So they share $s1. In the pinned table: r75 s1 (local-alloc), r77 `-` ... hmm but target has u6 in $s1. Actually the alloc table for pin shows r77 conflicts v0,s0,s1,sp. It conflicts s1 (because r75 occupies it) but... target u6 is in s1. Wait: `andi $17,$17,0x0fff` — $17=$s1 is both input (raw) and output (u6). So the andi is in-place: s1ang raw and u6 are the same hard reg, with the raw dying. So r77's live range starts after r75's ends, no conflict... but the table says r77 conflicts s1. Hmm, maybe because it's the same pseudo chain? Whatever.

Key: in the pin case, local-alloc gave r75 $s1 (since $s0 reserved). Then global-alloc gave r77... it conflicts s1 per the table, yet ends in s1. Actually the table's "conflicts" might include the register the pseudo was later coalesced into.

OK. Let me just experiment. Candidate ideas:

Idea A: make s1ang raw global by using it after the return block. E.g.:
```
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
u5 = ...;
do { d = (s16)d; } while (0);
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - (s1ang & 0xFFF);   // second use of s1ang in another block
...
```
But `iVar4 = u5 - u6` vs `u5 - (s1ang & 0xFFF)` — cse should keep u6 in a reg. This changes nothing semantically. But does it make r75 global? s1ang raw is used in block 0 (andi for u6) and in block 2 (andi for iVar4). cse1 is per-extended-basic-block and doesn't propagate the andi result; the second `s1ang & 0xFFF` would need s1ang in block 2 → s1ang raw global. Then cse2 (global cse) might merge the andi and eliminate the second one... cse2 runs before global-alloc? Pass order: cse, jump, cse2, loop, ... Actually the dump list: combine, cse, cse2, dbr, flow, greg, jump, jump2, loop, lreg, rtl, sched, sched2. Hmm order is alphabetical in ls. Real pass order in gcc 2.7.2: ... cse (cse1), jump_opt, cse (cse2), loop, ... then local_alloc, global_alloc...

If cse2 merges the two andi computations, the second use disappears and s1ang raw becomes block-local again. Hmm.

Let me check: does cse2 do cross-block value numbering? Yes, cse2 (cse after jump) does global cse. It would replace the second `s1ang & 0xFFF` with u6. So s1ang raw dies at block 0 again.

Alternative: use s1ang in a way cse can't merge: e.g., `u6 = s1ang & 0xFFF;` and later `if (s1ang == something)`. But that adds instructions.

Hmm, wait. Actually maybe there's another approach: prevent r75 from crossing the call. If s1ang raw does NOT cross the call, local-alloc can give it a caller-saved reg (e.g., $v1/$a0), and d gets $s0. But the target has the s1ang load before the call and its value used after the call. So it must cross the call. Unless... we reorder the source so the load happens after the call, but then the instruction stream differs from the target (the target has `lh $17,18($2)` before jal). So no.

Hmm. Wait, actually is it the load that crosses the call or the value? In target: `lh $17,18($2)` before the call, `andi $17,$17,0x0fff` after. Yes crosses.

Alternative approach: make d NOT conflict with $s0 by making d's live range not overlap r75. Impossible (d is live from entry).

Alternative: raise d's priority so it's allocated before... but r75 is LOCAL-alloc, which runs before global-alloc. Local-alloc doesn't consider priorities of globals; it just allocates block-local pseudos. So d can never beat r75 for $s0 as long as r75 is block-local and prefers $s0.

Unless r75's allocation preference is different. Local-alloc assigns the first free hard reg? It uses qty ordering and preferences. r75 = s1ang raw, 2 refs. It's a block-local that crosses a call → restricted to callee-saved regs ($16-$23) or maybe $s0-$s7. It takes $s0 because it's first.

Could we make r75 not cross a call? What if the `ratan2` call is evaluated before the s1ang load? That changes order vs target.

Hmm, what about making s1ang raw NOT block-local by having its use in block 0 but with a copy... Actually another way: make s1ang raw global by taking its address? No.

What about using s1ang in the return-value path in a way cse2 can't eliminate and that produces the same instructions? E.g., `iVar4 = u5 - u6;` — that's already using u6.

Alternatively: compute u6 in a different block. E.g.:
```
if (s1ang & 0xFFF) ... 
```
Hmm.

Let me think about what makes a pseudo global in gcc: it's global if it's live across basic block boundaries (referenced in more than one block). r75's single use is the andi. If we move the andi into block 2 (after the compare), we'd need the compare to use something else.

Actually, what if we restructure the code so that `u6 = s1ang & 0xFFF` happens in block 2, and the compare in block 0 uses `(s1ang & 0xFFF)` computed there? That's the duplication idea, and cse2 might merge.

Hmm, but wait: does cse2 merge the andi across blocks here? The second andi is in block 2, reached from block 0 fallthrough. The first andi in block 0 dominates block 2? Block 0 ends with `bne $17,$4,$L72` (branch taken to block 2 when not equal). The fallthrough (equal) returns. So block 2 is reached only via the branch from block 0. cse2 does global value numbering and can forward the value across the edge if the expression is available at block entry and not killed. It should merge. So the second andi would become a copy of u6... which is what we have.

But here's the thing: if cse2 merges, s1ang raw becomes block-local again. Unless cse2 is not run or the merge is blocked. Hmm.

Alternative idea: force s1ang raw to be global by making it cross a block boundary in a way that doesn't add instructions: what if the andi is moved after the branch? E.g.:

```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
```
becomes
```
if ((s1ang & 0xFFF) == u5) return 0;
u6 = s1ang & 0xFFF;
```
The first andi in block 0, second in block 2. Same as above.

Hmm. Is there a way to make the register allocator treat the raw s1ang differently? What if we split s1ang into two variables at source? E.g.:
```
s32 s1ang = *(s16 *)(...);
...
u6 = s1ang & 0xFFF;
```
The raw value is one pseudo. What if we write `u6 = (*(s16 *)(*(s32 *)(arg0+0x20)+0x12)) & 0xFFF;` directly, and separately keep s1ang for a later use? That would reload.

Wait — maybe there's a completely different angle. The target has `d` in $s0 from the start, via `move $16,$5`. What if we make d's value be the result of a call or an argument-copy that naturally prefers $s0? No.

What if we swap which variable is d? No, signature fixed.

What if we make `d` block-local? It's used in blocks 2-9. No.

Alternative: reduce r75's need for a callee-saved reg by making s1ang raw die before the call, but the target's `lh $17,18($2)` before the call means the LOAD is before the call. Could the value be loaded before but re-materialized after? No, the target uses $17 across the call (it's saved to the stack: `sw $17,20($sp)`).

Hmm OK so the target genuinely has a callee-saved pseudo live across the call, and the pin reserves $s0 for d. Without the pin, local-alloc gives the first callee-saved to that pseudo.

Can we make local-alloc give it $s1 instead of $s0? Local-alloc allocates block-local pseudos in qty order (priority = refs/live length?). If another block-local pseudo with higher qty wants $s0 and doesn't cross the call... then it takes $s0, and r75 gets $s1. But that other pseudo would then occupy $s0 in some other block, and d could still conflict if live ranges overlap? d is global and live across the whole function, so any local pseudo in $s0 anywhere in d's live range conflicts with d. So d would then get $s1... no good, unless the other pseudo's live range doesn't overlap d? d is live from entry to end (it's the divisor used in the last blocks). Actually d's live range: defined at entry (insn 6), used at insn 57 (cast, block 0), and in the divs (blocks ~5-11). So d is live across everything.

Hmm, but wait: in the pinned target, r75 got $s1 and d $s0. So $s1 must also be blocked for d... no, d is $s0 by pin.

What if we make r75's value also live across the call but assigned $s1 because $s0 is used by another LOCAL pseudo whose live range is entirely before d's... no, d is live everywhere.

Unless d's live range could start later! What if d is not live from entry? The target has `move $16,$5` at entry (d = arg1), and `sll $16,$16,16` at the cast. So d is live from entry. Hmm.

OK, different approach: make d global-alloc allocate it $s0 by removing the conflict. r74 conflicts 16 because r75 (local, $s0). If r75 is not a local-alloc pseudo but a global one with lower priority, d wins. To make r75 global: use s1ang raw in a second block in a way that survives cse2.

What real-C constructs produce a cross-block use that cse can't merge? E.g., a use under a condition where the value might be redefined... no. Or use s1ang in a comparison after the loop in a way that's a different expression.

But any use of s1ang after the call in another block adds an instruction unless it replaces an existing use. Currently `u6 = s1ang & 0xFFF` (one andi). If instead we do `iVar4 = u5 - s1ang;` — no, that's wrong semantics (needs & 0xFFF).

Hmm, what about changing the ORDER: compute iVar4 first, then u6?
```
iVar4 = u5 - (s1ang & 0xFFF);  // block 0? 
if (iVar4 == 0) return 0;
u6 = s1ang & 0xFFF;
```
That's not the target's structure (target compares u6==u5).

Let me reconsider. Maybe the goal doesn't require d=$s0 via s1ang being global. What if we make the *cast* of d produce $s0 differently?

Alternative: make d's copy from arg1 be a "preferred $s0" copy. Hmm, arg1 is in $a1; the move to $s0 happens because d is assigned $s0.

Another thought: what if we increase d's ref count so that local-alloc... no, local-alloc ignores globals.

Hmm wait. Actually, is r75 really allocated by local-alloc? The table says r75 has blk 0 and "crosses 1 call". In the lreg dump: "Register 75 used 2 times across 7 insns in block 0". Local-alloc only allocates pseudos with all references in one basic block. r75 qualifies. So yes.

Could we make r75's references span two blocks WITHOUT changing the instruction stream? The load `lh $17,18($2)` in block 0, and the andi `andi $17,$17,0x0fff` in block 0. If the andi were in block 1 or 2... In the target asm, the andi is right after the call, before the `bne`. Block structure: block 0 = insns 4..72 (first insn 4, last 72) per the lreg dump. Insn 69 is the andi, insn 72 is the bne. So andi is in block 0.

Hmm.

Wait, maybe the real target's r75 was also block-local and local-alloc gave it $s0, but the PIN made $s0 unavailable... yes exactly. The pin is the lever.

So to remove the pin, we need a real-C way to reserve $s0 or to make r75 not take it.

Idea: introduce a block-local variable in block 0 that local-alloc assigns $s0 BEFORE r75 (higher qty) and whose live range does not overlap d... but d is live everywhere, so any $s0 local conflicts d. Unless local-alloc gives it $s0 and d conflicts it → d gets $s1. Bad.

Hmm, but wait: does d conflict with a local pseudo if that pseudo's live range is within d's? Yes, conflict = overlapping live ranges.

So any local $s0 usage kills d. The only way d gets $s0 is if no local uses $s0 during d's range, i.e., r75 must go elsewhere ($s1), which means something else must take $s1 or $s0... Actually local-alloc assigns free callee-saved regs in some order. If $s0 is free, r75 gets it. We need r75 to get $s1. Local-alloc's qty order and preferences determine which reg.

What if r75 has a *preference* for $s1? Preferences come from copies: `x = y` where y is in a hard reg. r75 = load result. If we write `s1ang = some_var;` where some_var is in $s1... circular.

Alternatively, what if local-alloc's qty ordering gives $s1 first? In local-alloc, hard regs are ordered by qty (register allocation order). The allocno's qty preference... The order of hard regs in local-alloc is by REG_ALLOC_ORDER. For MIPS, $16 ($s0) comes before $17 ($s1). So first free = $s0.

Hmm, but what if r75 doesn't cross the call? Then it's not restricted to callee-saved, and local-alloc could give it a caller-saved reg like $v1 or $a0. Can we make r75 not cross the call while keeping the target instruction order? 

Wait — actually, what if s1ang raw is loaded before the call but its *use* is a copy to a different pseudo before the call? No, the target's `lh $17,18($2)` then after call `andi $17,$17,0x0fff` — same reg $s1.

Hmm, hold on. Let me reconsider: does r75 cross the call? The call is insn 47. r75 def at insn 20, use at insn 69. Yes, crosses.

What if we split s1ang into a load before the call and use the value after, but through a "sink" that makes the pseudo not cross? E.g., store s1ang to a stack slot before the call and reload after? That adds instructions.

OK, let me look at this from a different angle: what did other similar items do? func_8012BB3C (line 316) "C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0)". That's a different function but similar: they cracked the pin by adding a do-while on the div block, increasing refs so the divisor's priority rises. But here, the pin removal fails because of local-alloc, not global priority. Wait — in 8012BB3C the divisor is a global and the pin was $16; the do-while raised refs. In our function the problem is r75 (local). Hmm, but wait, maybe not: the W50x notes said "div do-while (w5) lifts d's global-alloc pri 5185->12222 and puts r74 ahead of r77 in the .greg order, but r74 conflicts with hard reg $16, so d still lands $s1". So they diagnosed the same: r74 conflicts $16 (due to r75 local). The conflict is the wall.

So we need to get r75 off $s0.

Hmm, what if we make s1ang raw's load happen before the call but make the raw pseudo *die* before the call by copying it to another pseudo? Like:
```
s32 raw = *(s16 *)(...);
s32 s1ang = raw;   // copy
```
The copy would be coalesced. No.

What if we make s1ang a `s16` variable? Then `u6 = s1ang & 0xFFF` — s1ang would be HImode. The load would be `lh` and the value used as HI. In the target, `lh $17,18($2)` then `andi $17,$17,0x0fff`. If s1ang is declared s16, the sign extension is implicit in lh; the andi operates on the SI value. GCC might do `lh` into a HI pseudo then use. Hmm, that could change things. Let's try: `s16 s1ang;` and `u6 = s1ang & 0xFFF;`. The extension from HI to SI happens at the andi. The pseudo might be HImode with a different register class or qty.

Actually the target's `lh $17,18($2)` writes a full register $17. If s1ang is s16, gcc generates `lh` into a HImode pseudo, then `andi` on the sign-extended value — extendhisi2. Might match.

But the key question is whether r75 still takes $s0. Its qty might change (2 refs, HI mode). Probably still local & callee-saved.

Alternative: make s1ang raw NOT cross the call by moving the load AFTER the ratan2 call in the source, but keep the target order? The target order is fixed: load before call. So no.

Hmm, wait. Let me reconsider whether the target really needs s1ang raw in a callee-saved reg. The target: `lh $17,18($2)` before `jal ratan2`, and $17 is saved with `sw $17,20($sp)` at entry. Yes.

Let me look at the sibling func_8012BA10's notes (line 315): "block-local s1ang (2refs/7ins) takes $s0 in local-alloc before the global divisor d (7/27); globalising s1ang lifts its pri 6363 past d 5185 (G27x)". Wait — that says "globalising s1ang lifts its pri 6363 past d 5185" — meaning they made s1ang global! And then? It says WALL, best... Let me read the full moves line 315: "keepalive,pin | func_8012BA10 | WALL lreg-qty-priority — block-local s1ang (2refs/7ins) takes $s0 in local-alloc before the global divisor d (7/27); globalising s1ang lifts its pri 6363 past d 5185 (G27x)".

Hmm, so for 8012BA10, globalising s1ang made its priority higher than d, so s1ang took $s0 and d took... that's the wrong direction. In our case we want d to win. So we want s1ang global with LOWER priority than d. In our function d has pri 10000 (capped?) and s1ang raw would be 2857. d wins. 

So the plan: make s1ang global with lower priority → d gets $s0, s1ang gets $s1. Let me test the duplication idea and see if cse2 merges it. Let me just try it.

Candidate w1: duplicate the andi in the iVar4 computation:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - (s1ang & 0xFFF);
```
Let me test score and dump.

Actually wait, there might be a cleaner trick: use `s1ang` in the compare directly and later:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
```
The current form. The second use is u6.

What if we reorder: `if ((s1ang & 0xFFF) == u5) return 0; u6 = s1ang & 0xFFF; iVar4 = u5 - u6;` — s1ang used in block 0 and block 2.

Let me test several candidates. Let me write w1 (dup andi) and w2 (reordered).

Actually, an even simpler idea: what if we reference s1ang in the `iVar4 = u5 - u6;` as `u5 - (s1ang & 0xFFF)` while keeping u6 for the compare? cse2 will likely merge. Let me check the cse2 dump to see.

Let me create candidates and score them. I'll write a few.

Candidate w1:
```
s32 func_8012B8E4(s32 arg0, s32 arg1) {
    s32 d;
    s32 s1ang;
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(...) - 0x400) & 0xFFF;
    do { d = (s16)d; } while (0);
    u6 = s1ang & 0xFFF;
    if (u6 == u5) return 0;
    iVar4 = u5 - (s1ang & 0xFFF);
    ...
```
Let me test.

Also candidate w2: use s1ang in the branch arms? No.

Let me also think: maybe making u5's computation use s1ang... no.

Another idea: declare s1ang before d? Decl order affects nothing much after RTL.

Another idea: make `s1ang` volatile? That adds loads — no.

Let me try w1.

Also, I should check the pass dumps to see if r75 becomes global. Let me write w1 and w2.
