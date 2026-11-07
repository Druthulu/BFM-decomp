---
ts: 2026-11-06T21:08:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YFriXOTMe78AWuxeKHUU
---
So the hard v0 becomes live at each `(set (reg:SI 2 v0) ...)` insn and conflicts with all allocnos live at that point. And r74 conflicts with v0 → there must be an insn setting hard v0 while r74 is live.

Look at the ranges of r74 in block 1: birth at 27 (load), death at 35 (ashift, hard v0 set at 35!). Order at insn 35: deaths processed first (r74 dies) → then v0 born. Hmm, but wait — REG_DEAD note at insn 35: yes. So r74 is not live when v0 is born.

BUT: at insn 33 (the store of r74 to memory), is v0 live? No.

Hmm, what about block 1's beginning: r74 born at 27. Before that, at insn 22 the branch with REG_DEAD v0. Not relevant.

Let me check block 3 (insns 47-55) and block 5 (67-76).

Block 3: 47 load r74; 50 addiu; 53 store; 55 ashift v0, REG_DEAD r74. Same pattern.

Block 5: 67 load; 70 addiu; 73 store; 81 sign_extend v0; 76 store 0x18 with REG_DEAD r74. Wait! Here the v0 set at insn 81 comes BEFORE r74's death at insn 76 in the *insn order* (81 is between 73 and 76 in the chain: insn 76's prev is 81). The insn chain: 73 -> 81 -> 76. So the v0 sign_extend at 81 happens while r74 is still live (it dies at 76, which comes after 81 in the chain). That's the conflict!

In the source, the comparison `if (*(s16 *)((u8 *)s1 + 0x1a) < 0)` reloads from memory and uses v0, while t is still live (t is used at the store to 0x18 after the comparison in the original order). So the reload's register (v0 after local-alloc) is set while t is live → conflict → t can't be v0.

In the target, the order is: `addiu v0; sh v0,26(s1); lh v1,26(s1); bgez v1; sh v0,24(s1)`. The reload went to v1 (because t occupies v0), which is exactly the target. So in the target, t got v0 because it was pinned; the reload then took v1.

So to get t into v0 lever-free, we must avoid the conflict: the reload pseudo (the s16 load in the comparison) must not be allocated to v0 before t is... hmm, but the conflict is computed by global.c based on hard regs after local-alloc. The reload is a *local* pseudo assigned v0 by local-alloc. If local-alloc assigned the reload to v1 instead, then no v0 conflict, and global-alloc would give r74 v0.

But local-alloc assigns v0 to the reload because... the block's pseudos: r85 (2 bytes, 6 insns), r86, r87, r89, r90, r91, r92, r94, r95, r96, r97. The reload is r85 probably (2 bytes, used 6 times across 6 insns). In block 5, which pseudo gets v0? The target's reload is v1.

Interesting: if we can make the reload die earlier or have lower priority... Hmm.

Alternatively, restructure the source so that the comparison is evaluated BEFORE the 0x18 store — i.e., compute the sign test into a variable earlier, so the reload is born and dies before... no wait, the conflict is about the hard reg being live while r74 is live. If the reload is born at an insn where r74 is live, it conflicts regardless of assignment — unless it's assigned v1.

Hmm, but the *assignment* is local-alloc's, which happens before global. Local-alloc doesn't know about r74 (global). So the reload gets v0 if v0 is free in that block. To make local-alloc pick v1 for the reload, something else must occupy v0.

Idea: make t's use extend past the reload? No, t is global and not yet allocated.

Idea: the reload's priority vs other local pseudos. If another local pseudo in block 5 has higher priority, it takes v0 and the reload takes v1. In the target, the reload is v1 because v0 is... hmm, in the target the reload is v1 and t is v0 — but t is a global allocno, allocated after local. So local-alloc assigned v0 to something else? No — in the target the reload got v1 because local-alloc saw... hold on. In the target (pinned), t is a HARD reg v0, so local-alloc sees v0 as live across the whole t range and assigns the reload v1. Right.

So lever-free, we need local-alloc to not choose v0 for the reload. What determines local-alloc's choice? In block 5, the highest-priority local pseudo gets v0. Candidates: the reload (r85: 2 bytes, 6 refs, 6 insns), the address computations, etc.

Wait, actually, why is the reload 2 bytes (HImode) with 6 refs? `sign_extend:SI (mem:HI ...)` — the mem load into a HImode pseudo then extended? Hmm.

Alternatively: avoid the reload entirely by reusing the value we already have: `if (t < 0)` using the s32 t? But the target explicitly reloads (`lh v1,26(s1)`) — because the source compares the *stored s16* value. Hmm, if we wrote `if ((s16)t < 0)`, the compiler might use t directly (no reload) → different code (no lh). The target has the lh, so we need the reload.

OK so we need to change local-alloc's assignment of the reload from v0 to v1. Levers: give another pseudo in block 5 higher priority, or extend the reload's live range (lowers priority), or change the birth order.

Hmm, what if the reload's value is also used later (more refs)? No.

Alternative: make v0 occupied at the reload by a *live* value: e.g., if t were used after the reload... but t is global, unallocated at local-alloc time. Hmm — but wait! local-alloc runs first; it doesn't know t. However, if we make the reload's own block contain a *local* pseudo live across it, that pseudo could take v0.

What if the 0x18 store value is a separate local copy: `s16 v = t; ... store v ...`? Then v is a local pseudo live across the reload; local-alloc would consider v (live longer, maybe higher priority) and give it v0, pushing the reload to v1. But then t (global) would conflict with v0 (v is in v0) → t goes to v1! Bad.

Hmm. We want: in block 5, the reload should be v1 and t should be v0. Since t is global and allocated later, v0 must be free from local-alloc's perspective (no local pseudo in v0 during t's live range). So the reload must take v1 because v0 is taken by *something else* that dies before... no, if anything takes v0, t conflicts.

Wait, no: local-alloc assigns a register to a pseudo only within its live range. If the reload takes v1 (for whatever reason), v0 is free during t's range → t gets v0. For the reload to take v1, either (a) v0 is occupied by another local pseudo whose live range overlaps the reload's, or (b) the reload has a lower priority than another pseudo that takes v0.

In block 5, what else is there? The address computations for the stores. Let's look at the local pseudos in block 5 from the .flow dump: r81, r82, r83, r84 (2-4 insns), r85 (6 insns), r86... Actually those are in block 5: r81 (2 bytes), r82 (2 bytes), r83, r84, r85 (2 bytes, 6 insns). Hmm.

Actually, maybe easier: rather than fight the conflict, remove the reload's hard-v0 status by making the comparison use a pseudo that local-alloc won't put in v0. 

Hmm, what if we reorder the source so the comparison happens BEFORE the store to 0x18 and the store to 0x1a? Then t's live range would end before the reload, removing the conflict! But the target's order is: sh t,26(s1); lh v1,26(s1); bgez; sh t,24(s1). The store to 0x18 is in the branch delay slot, using t. So t IS live across the reload in the target. Hmm.

But wait — in the target, t is a hard reg (pinned), so liveness doesn't matter for allocation. Lever-free, if we reorder the source to `if (*(s16*)(s1+0x1a) < 0)` computed before the 0x18 store... the generated code order would change (the branch would come before the 0x18 store), which differs from the target. Not good.

Alternative: compute the comparison into a variable that is *not* in v0. The reload pseudo gets v0 from local-alloc. What if we make the comparison's operand a pseudo with higher priority elsewhere... 

Let me look at local-alloc's choice: the reload is r85? Let's check block 5's local pseudos and priorities in the .lreg table. From the alloc_table earlier for w2? Let me just run alloc_table on w2 dumps.

Actually, a cleaner idea: make the *0x18 store* use a separate variable that is also s16, so t's live range ends at the 0x18 store... no.

Hmm, think differently. What if we avoid making `t` a single global allocno at all? If each block's t were a separate pseudo, local-alloc would handle them (like the load/sll in block 1), and the v0 choice would be local — the target's v0 comes from the load being in v0 and the sub tying. That might match! In fact, in the original pinned version, r74 is one global allocno because the C variable t is one variable. If we declare separate variables per block (t1, t2, t3), each is local → local-alloc assigns per block. Then block 1: load v0, sub... the sub is the same pseudo as t1: `t1 = load; t1 -= 0x100` — local-alloc sees one pseudo t1 born at the load, living to the sll. It gets v0 (highest priority in the block? r78 in the earlier dump got v0). Then the store and sll use v0 → matches the target!

Block 5: t3 local; the reload also local. Priorities decide. In the target, t3=v0, reload=v1.

Let me try separate variables: t1, t2, t3. But careful: variable declarations in the function vs block scope. The original has one `s32 t;` at function scope. Using three separate declarations is a real-C change (decl scope/order) allowed by the catalog.

Let's try:
```c
void func_800CC4E8(void *a0) {
    void *s1;
    s32 t;
    ...
}
```
with `s32 t1, t2, t3;`? Hmm, or declare inside blocks. Let me try function-scope t1,t2,t3.

Actually, wait. Even simpler: keep one variable but... no, one variable = one pseudo (GCC reuses the same pseudo for a variable across the function? Actually it did: r74 with 3 disjoint ranges). Hmm, does GCC reuse one pseudo per C variable? Normally GCC's expand creates a fresh pseudo for each assignment to a variable (it doesn't keep the variable in a register unless it's a "user variable"). Hmm, but the dump shows one pseudo r74 with 3 ranges. That's because... GCC's `expand_expr` for a variable: if the variable's rtl is a pseudo that's "stable"? Actually for a local variable assigned in different branches, GCC can reuse the same pseudo if the variable is not in SSA. Yes, GCC 2.7.2 reuses one pseudo per variable across the function (it's not SSA).

So separate variables → separate pseudos. Let's test.

But note: 3 separate s32 variables might increase frame/register pressure? They're local to blocks; local-alloc handles them. Since the live ranges don't overlap, fine.

Let me write w3.c with t1,t2,t3 as separate declarations, each doing load-then-subtract.

Actually, hmm: if t1 is one pseudo born at the load and dying at the sll, local-alloc gives it v0 (highest priority in block 1). The load is also v0? The load writes t1 directly now (`t1 = load`), so there's no separate load pseudo — one pseudo. Then `addiu v0,v0,-256`, `sh v0`, `sll v0`. That matches the target exactly!

Block 3: same → v0. Target: yes v0.
Block 5: t3 in v0; the reload competes. Priorities: t3 (refs 3: store26, store24, ashift? plus the addiu), live long; reload (2 refs). t3 should win v0, reload v1. 

Let's try.
