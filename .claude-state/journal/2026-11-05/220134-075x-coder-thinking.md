---
ts: 2026-11-06T05:01:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0L779CWbb6k9BL8pyW6S
---
OK. Key practical: we need an insn that invalidates memory in cse (all=1) but is removed later. What insns set all=1 in note_mem_written?
- written==0 (e.g., a CLOBBER without a MEM?) 
- MEM with BLKmode
- MEM (scratch)
- varying address not (struct or PLUS) with mode != QI
- QI mode with PLUS/varying

And invalidate_from_clobbers is called for CLOBBERs of MEM too.

What about a store to a *BLKmode* MEM? That happens for struct assignments or `__builtin_memcpy`? A struct assignment `s = t;` where the struct is small might be BLKmode and then expanded to loads/stores at the tree/RTL level. Hmm, a BLKmode store would emit a movstr pattern (a call to memcpy) — not free.

What about a store that is dead because it's a *store to a stack slot* that flow can delete via last_mem_set: two stores to the same stack MEM. The first store must have all=1... but a stack slot address is (plus fp const) — varying? cse_rtx_addr_varies_p for (mem (plus (reg) const)) with reg a pseudo without known constant → returns true (varies). Mode: if the store is QI → all=1! So:

```
u8 pad[1];  // or s8
*(u8 *)&pad[0] = 0;   // addr plus(reg, const), QI → all=1
*(u8 *)&pad[0] = 0;   // second identical store: flow deletes the FIRST (last_mem_set)
```
Both stores to the same MEM (mem:QI (plus (reg) const)). The first is dead (last_mem_set equals), flow deletes it. The second survives → emits a `sb` instruction. That's an extra instruction. Unless the second store is also dead... it's a store to a local never read; flow's last_mem_set only deletes the previous when a later equal store appears. The last store stays.

Hmm, can we make BOTH deleted? No, the last one always stays (unless... at the end of the block? no).

What if the second store's MEM equals an *existing* target store? The target has `sh 1,26(v1)` — HI mode, different from QI. Not equal.

What if the dead store is QI to the same address as a later QI store that is already needed? No QI store in target.

Alternative: use the fact that `last_mem_set` is cleared by a call. Hmm.

What about a store to a MEM that is later *overwritten by a call*? no.

OK, let me reconsider. Maybe there's a completely different real-C move for this function. The residual from a1 is 12. Maybe instead of fighting cse, restructure so the call arg is loaded from a different variable that cse can't forward, e.g., make the call arg a *function* of the loaded value that forces a load: `func_80138C30(*(s32 *)p)` — same.

What if we change the *store* to not be a plain `*p = v0` but write through a `s32 *` obtained differently, e.g., store to `D_80127524` symbol directly: `D_80127524 = v0;` (not via p). Then the store's dest is (mem (symbol)), and the load `*p` for the call arg would be folded to the symbol and forwarded to v0 — same. But the sh base load `*(s16*)(D_80127524 + 0x1A)` also loads the symbol. Hmm.

Wait, maybe I should check whether the forwarding is from the store or from the sh-base load. In cse1, the entry from insn 50 (store) was (mem symbol)->76. The load at 57 was NOT forwarded, meaning the entry was not visible at 57 (table reset at the jump). Then 57 creates (mem symbol)->84. Then at 64, lookup found 76?! That can't be unless the entry from 50 was still there and 57's load was not forwarded for a different reason.

Hmm, maybe insn 57's load *was* from a different address: `(mem:SI (symbol_ref D_80127524))` vs the store's `(mem:SI (reg/v 75))` folded... The dump shows insn 57's address already folded to the symbol. And the store insn 50's dest remains `(mem:SI (reg/v:SI 75))` — NOT folded! Because fold_rtx on a SET_DEST might not substitute reg 75 if... Actually the dump shows the store dest as (reg/v 75). So the store's dest hash is of (reg 75), and the load's address is the symbol. They differ → no forward at 57 (correct). Then insn 57 creates (mem symbol)->84. At insn 64, the load is (mem (reg/v 75))? Let me check insn 64 in cse1: it was `(set (reg:SI 4 a0) (reg/v:SI 76))` — already forwarded before cse1? That was in the .cse dump (after cse1). So at cse1, insn 64's source was originally `(mem:SI (reg/v:SI 75))` (via p). fold_rtx would fold reg 75 to the symbol → (mem symbol), then lookup finds the entry from insn 57 (->84) OR the store's (->76)? The dump says 76.

Wait, the store insn 50's dest is (mem (reg/v 75)); when the dest is inserted, cse uses `sets[i].dest_hash = HASH(dest, mode)` computed BEFORE folding? Line 6994-6998: "Compute the hash code of the destination now, before the effects of this instruction are recorded, since the register values used in the address computation are those before this instruction." And at line 6983-6985: `if (GET_CODE (dest) == MEM) { dest = fold_rtx (dest, insn); ... }`. So dest IS folded to the symbol. But the dump shows (mem (reg/v 75)) — the dump is after cse1, and maybe the store's dest was NOT folded because fold_rtx can't substitute reg 75 (REG_EQUAL exists on insn 35). Hmm, the dump shows it unfoled, but that's the final RTL; maybe fold_rtx folded it for hashing but then the printed RTL shows the original.

Anyway, at insn 64 the lookup found 76, the store's source. So the store's dest entry (hashed as the symbol) matched.

The load at 57 didn't find it. Why? Perhaps because between insn 50 and 57 there's a jump (block boundary), and cse's `cse_basic_block` at a jump to a label calls... it processes the fall-through but with a fresh table? Then how did 64 find 76? Both 57 and 64 are after the jump in the same block. Unless the entry 76 was re-added... 

OH WAIT. Maybe the order is: cse1 processes the block containing 57,61,64 with a table that still has the store entry (mem symbol)->76 from the previous block because cse *follows* the fall-through of the conditional jump (flag_cse_follow_jumps). At insn 57, the load's address is (mem (reg 75)) originally; fold_rtx folds it to the symbol; lookup finds (mem symbol)->76 → it SHOULD forward. But the dump shows a real load at 57. Unless insn 57's load was NOT (mem (reg 75)) but something else: the C is `*(s16 *)(D_80127524 + 0x1A) = 1;` where D_80127524 is a *symbol* (global s32). So the address is `(mem (plus (symbol D_80127524's value) 26))`? No! `D_80127524` in the C is the global variable; `D_80127524 + 0x1A` means the VALUE of the global plus 26. The RTL: load (mem symbol D_80127524) into reg 84, then store to (mem (plus reg84 26)). So insn 57 is a load from the symbol — same as *p (p=&D_80127524). So it should be forwarded from the store if the entry is visible.

The fact that 57 wasn't forwarded but 64 was suggests the store entry was invalidated between 50 and 57 and re-created by 57... and 64's forward to 76 means the entry (mem symbol)->76 was present at 64 but not at 57. Something re-added 76 between 57 and 64? The sh store at 61 is a store to (mem HI (plus reg84 26)) — its *source* is reg 85 (const 1), dest folded... no.

Hmm, unless cse's `cse_basic_block` handles the jump specially: at a jump, it invalidates but keeps "constant" entries? reg 76 might have a REG_EQUAL? No.

I'm spending a lot of time. Let me take the empirical route: try adding an intermediate store that cse treats as all=1 and that combine/flow can delete. 

Idea: a *store to the same location as the existing sh* but via a bare register, with the same HI mode and same address register — so rtx_equal_p holds. To have the same address register, we'd need a pointer r = value+26. If we write:

```
s16 *r = (s16 *)(D_80127524 + 0x1A);
*r = 1;
```
That's the sh but with an extra addiu (address in a register). Not target.

But what if we write BOTH stores through r and the compiler folds the +26 into the addressing mode of the store (so r is just `value`)? If we write:
```
s16 *r = (s16 *)D_80127524;
r[0xD] = 1;   // r + 26
```
The address is plus(reg, 26) — target form. Good. Then a dead store before it through the same expression:
```
r[0xD] = 0;   // QI? no, s16 → HI+PLUS → nonscalar only
```
No good.

To get all=1 with the same MEM as the target sh... impossible: the target sh is HI+PLUS which never sets all=1.

So we cannot invalidate via a store that shares the target sh's MEM. We need a *different* store (QI+PLUS or non-PLUS) that gets deleted. 

What about a store that combine will merge/delete? Combine can delete a store if it's overwritten by an adjacent store to the same location (combine's `try_combine` can combine two sets to the same memory? It usually doesn't).

What about a store whose value is a *dead register* and which flow deletes because the destination is a MEM equal to a previous... no.

Hmm, what if the extra store is to the *stack* through a QI pointer that flow deletes as dead because the stack slot is dead and insn_dead_p handles stack slots specially? Let me look at insn_dead_p more: for MEM dest, the only check is last_mem_set equality. So no.

What about `delete_dead_from_cse` (runs right after cse1 and cse2)? It deletes insns whose REG_EQUAL... Let me look at what it does. It deletes dead stores recorded from cse? Hmm, "delete_dead_from_cse" removes insns that compute values not used (per REG_DEAD?). Let me check.
