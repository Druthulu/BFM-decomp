---
ts: 2026-11-06T21:16:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mJTgMHkZtohVTSW5oXh8
---
So lines 2-1006 are func_8017E590. Line 12/18/42 are its regs. Good: e=79: 2 refs, 4 insns. off=95: 3 refs, 8 insns.

But hold on: "used 2 times across 4 insns" — is 4 the live length or the number of insns where referenced? The dump says "used %d times across %d insns". reg_n_refs=2, reg_live_length=4. So live_length=4.

So e pri = 1*2/4 = 0.5; off pri = 1*3/8 = 0.375. e higher. Yet order shows e last.

Unless allocno for e has a different live_length because of multiple pseudos. Let me check if e is tied/copied to another pseudo. In global-alloc, pseudos connected by copies form one allocno. e = symbol_ref (not a copy). Hmm.

OR: allocno_size for e might be 0→1, same.

Let me just print the allocno order's priorities... can't.

Wait — maybe I misread which pseudo is which in the allocno list. Let me look at the conflict lines: "73 conflicts: 73 74 150 2 4 29". Note "73 conflicts: 73" — a pseudo conflicting with itself? That suggests allocno numbering vs reg numbering confusion. Actually the dump prints `allocno_reg[i]` for conflicts. The self-conflict (73 in 73's list) is odd but maybe means allocno 73 includes reg 73 and conflicts with another allocno that also has reg 73? No.

Hmm, actually the conflict lists are indexed by ALLOCNO number (i), and print `allocno_reg[j]`. So "73 conflicts: 73 74 ..." means allocno whose reg is 73 conflicts with allocnos whose regs are 73,74,... Self-conflict impossible unless two allocnos share reg 73 (tied copies are in the SAME allocno though).

I think I'm overanalyzing. Let me take the empirical result: e is allocated last, so off wins a0. To flip, raise e's refs. The launder does +2 refs.

Let me try to add exactly ONE real use of e that survives to RTL and generates no extra instruction. Is there such a thing? 

What about `if (e) {}`? That generates a compare and branch (extra). No.

What about using e in a `return` expression? The function returns `result`. If we do `return (void*)((u32)result + ((u32)e & 0));` — identity, folded, and changes return.

Hmm. What about assigning e to another variable that's used? `s16 *e2 = e;` then use e2 for the condition instead of e. Then e has 1 use (the copy), e2 has 1 use. combine would propagate e2=e and then use e → back to 1 use. Unless combine doesn't (e is used elsewhere?). 

Let me try:
```
s16 *e2;
e = (s16 *)D_801E8F78;
e2 = e;                       // e use #2 (def + this)
...
*(s16*)((u8*)e2 + off + 2)    // e2 use
```
combine will likely merge e2 into e → 1 use. But if e2 is used in a different block... same block.

What if e2 is used in the condition and e is used for something else that's needed? 

Honestly, this might genuinely be a WALL. The launder is load-bearing for global-alloc priority. Let me check the budget: 14:28, 30 min. I should record a wall for item 1 and move on. But let me try 2-3 more quick ideas first since I'm at ~20 tries.

Quick ideas:
1. `s16 *e2 = e;` copy (test).
2. Make e's type `unsigned long` vs pointer — same.
3. Add a `volatile` qualifier to a temp read of e — generates a load.
4. Change `pad[2]` to `pad[4]`? frame would change (wrong).
5. Use `e` in the `if (idx >= 0)` block: `p = D_801E8F98[idx];` → could we make p's computation use e? no.
6. Restructure the whole case-5 then-branch to use `e` as the row pointer AND keep target code. 

Let me test the copy idea and one more: use `off` to index e and e to index... 

Actually, let me reconsider the target once more. Target's `e` (a0) is the symbol. What if in the target RTL, e is used TWICE: once for the condition address and once for the lim address, but the lim address was folded to sym+off? No, if folded, e's use is replaced.

Let me try: `lim = *(s16 *)((u8 *)D_801E8F78 + off);` (explicit symbol+off) and `e = (s16*)D_801E8F78;` and condition uses e. Then lim uses off (not e). Same as current.

OK let me just try the copy and then wrap with a wall. Actually, let me reconsider the possibility that a do-while around the *lim* load splits the block and changes allocation. We tried do-while around e and off. Let me try do-while around the lim load (splitting the block between off and e) — that could change live ranges.

Let me test: u.c = do-while around lim, v.c = copy e2.
