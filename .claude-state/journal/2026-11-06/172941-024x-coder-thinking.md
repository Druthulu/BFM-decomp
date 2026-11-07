---
ts: 2026-11-07T00:29:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IWR0HQaAZAByGBV8vNvy
---
This is very informative! note_mem_written:

For the store `(set (mem:HI (plus (reg) (const 20))) ...)`: cse_rtx_addr_varies_p(written) — the address is `(plus (reg) (const))`; cse_rtx_addr_varies_p checks if the address contains a register... let me check. If it varies:
- `if (! ((MEM_IN_STRUCT_P(written) || GET_CODE(addr) == PLUS) && GET_MODE(written) != QImode)) writes_ptr->all = 1;`

Our store: addr is PLUS, mode HI ≠ QImode → the condition `((in_struct || PLUS) && mode != QI)` is TRUE → so `all` is NOT set; only nonscalar=1 and var=1.

Then invalidate_memory with nonscalar=1, all=0: removes entries with in_memory && (in_struct || addr varies). Our pointer load `(mem (symbol_ref))` has addr not varying and in_struct=0 → SURVIVES. Confirmed: cse keeps the symbol load.

So to make cse drop the cached symbol load, the store in between must set `all`:
- store with QImode (a byte store!): if mode == QImode, the condition fails → all=1! Because char can alias anything.
- store with BLKmode (struct assignment / memcpy-like)
- store with a non-PLUS varying address (e.g., `(mem (reg))` directly — a store through a plain pointer with no offset! GET_CODE(addr)==REG, not PLUS → all=1!)
- a non-scalar store whose MEM_IN_STRUCT_P is false and addr is not PLUS.

That's the key insight! In the target, the store that invalidates the pointer cache must be a store whose address is a bare REG (offset 0) or a byte store.

Wait — but the target's own store is `sh v0,20(a1)` = PLUS. So in the target's compile, cse still had the symbol load... but the target reloads. Hmm, that contradicts.

Unless in the target's compile, the store happened at a different point relative to the two loads, or the first load was never cached because the store came before it, and then the second load... 

Let me re-derive the target's instruction order: 
- 2db8 lui v0; 2dbc lw v0  (pointer load #1)
- 2dc0 lhu v1,42(s0)  (a0->unk2A)
- 2dc4 lhu a0,18(v0)  (load [ptr+0x12])
- 2dc8 lhu v0,20(a1)  (obj->unk14)
- 2dcc subu v1,v1,a0
- 2dd0 addu v0,v0,v1
- 2dd4 sh v0,20(a1)   (store)
- 2dd8 lui v0; 2ddc lw v0 (pointer load #2)
- 2de0 lw v1,44(s0)
- 2de4 lhu v0,18(v0)
- 2de8 bnez v1
- 2dec sh v0,42(s0)   (store a0->unk2A in delay slot)

So the target's compile had no `all` invalidation between. So how did cse not forward load #2 to the v0 of load #1? Because v0 gets overwritten at 2dc8 (`lhu v0,20(a1)`) — but cse's substitution happens at RTL level before allocation; cse would have replaced load #2 with a copy of the pseudo holding load #1's value, so the value would live in a pseudo and regalloc would keep it. So the target's RTL had TWO loads.

Therefore in the target's RTL, cse did not merge them. Something in the original source prevents it. What?

Possibility: the original source computes the second use from a *different expression* — e.g., the first uses `D_80126B78` and the second uses a local variable that was loaded BEFORE the store, e.g.:

```
s32 *base = D_80126B78;
... use (u16*)((u8*)base+0x12) ...
a0->unk2A = ...;
```
No, still cse-equal.

Possibility: the original source's first use reads `*(u16*)((u8*)D_80126B78 + 0x12)` and the second reads the same, but the FIRST read is not a MEM expression of the same form: maybe the first is `((Unk*)D_80126B78)->unk12` where the struct member is at 0x12 but the MEM has MEM_IN_STRUCT_P=1 and mode HI — the RTL MEM would still hash the same? canon_hash includes MEM_IN_STRUCT_P? Let's check: hash_arg_in_struct is set when MEM_IN_STRUCT_P, and it's used for `in_struct` field only, not in the hash value? Let me check canon_hash: line 1951 `if (MEM_IN_STRUCT_P (x)) hash_arg_in_struct = 1;` — and the hash value itself is computed from code, mode, and operands. MEM_IN_STRUCT_P isn't hashed. So they'd still match.

Hmm, but wait: `exp_equiv_p` compares rtx_equal_p-ish including MEM_IN_STRUCT_P? Let's check. If two MEMs differ in in_struct flag, they might not be equivalent! In gcc 2.7.2, `exp_equiv_p` for MEM compares XEXP and mode; but there's a special case: "If we have a MEM with in_struct differences..." Let me look at exp_equiv_p.

Actually, gcc's exp_equiv_p in 2.7.2:
```
    case 'e':
      ...
      /* If this is a MEM, ... */
```
Let me grep.

Alternatively — a cleaner idea, and a real-C move from the catalog: "struct-member u16 load ... in_struct: the nonscalar ptr[2] store invalidates it, cse re-loads *q after the store". That's the opposite direction: making the LOAD in_struct so the nonscalar store invalidates it. Our pointer load `(mem (symbol_ref D_80126B78))` — can we make it in_struct? If the source reads it as a struct member of a struct placed at D_80126B78... no, D_80126B78 is a pointer variable; we need its VALUE.

But wait — what if the source reads the value through a *different* route: e.g. `((s32 **)&D_80126B78)[0]`? The MEM would be `(mem (symbol_ref))` still.

Hmm, what about the offset: `*(u16 *)((u8 *)D_80126B78 + 0x12)` — the pointer load is `(mem:SI (symbol_ref))` in both uses.

What if the second use goes through the `obj` variable? No.

New angle: maybe the original source has the two uses in a different *order* or with the second use's pointer loaded through a function... no.

Another angle: maybe the original source reads `D_80126B78` into a local variable at the top of the function (before the call), and the call invalidates all memory, so after the call the load is fresh; then the first use... no, both loads are after the call.

Hmm, let me reconsider: maybe cse1 vs cse2. cse1 runs before the second cse. If cse1 merges them (my case), cse2 wouldn't split them. The target has them split, so the RTL going into cse1 must have had something.

What if the first use's pointer load is *not* cse'd because it's inside a different basic block? The store to obj+0x14 and the uses — if the original source had a control-flow structure between (e.g., an if), the blocks would differ and cse's table is per-block... but the target code has no branch there.

Hmm, what about the asm... no asm allowed.

Wait. Maybe I should reconsider what the target is: maybe the baseline object was built from a DIFFERENT source than the current src (the original game's decompiled... no).

Hold on. Let me re-read the diff. Maybe my candidate's *second* load is not the issue; maybe my candidate has 67 ins vs 68, and the target's second pointer load is an *extra* instruction set because the original source genuinely loads it twice, and the reason is: the first load is not from D_80126B78 the symbol but from... 

Let me check the relocations in the target: 2db8/2dbc relocs are D_80126B78 HI16/LO16. 2dd8/2ddc also D_80126B78. Same symbol. Yes.

OK, so the question: what C makes cse not forward a symbol load across a PLUS-addressed HI store?

Insight from the code above: the store's mode! `if (! ((MEM_IN_STRUCT_P (written) || GET_CODE (XEXP (written, 0)) == PLUS) && GET_MODE (written) != QImode)) writes_ptr->all = 1;`

So a QImode (byte) store with a PLUS address sets all=1 → invalidates the symbol load! Our function has no byte stores in the target though... 

But wait: writes_ptr->all=1 happens for a QImode store; the target has no such store. But what about the C source: a byte store that's later eliminated? cse runs after flow/combine... The order in gcc 2.7.2 toplev: cse1 (after jump_optimize), then flow... Actually the pass order: after expand, jump_optimize, cse (cse1), then loop, then cse2, then flow, combine, sched...

Hmm, if a byte store existed in the C source but was deleted by flow/combine before cse, it wouldn't help.

What if the C source has a store to a variable at address `(reg)` with no offset — GET_CODE(addr)==REG → all=1. E.g. `*p = x;` where p is a plain pointer and the offset is 0. In our body, the store `*(u32 *)(a0->unk20 + 4) ^= ...` is at offset 4 (PLUS). Hmm.

But here's a thought: what if the *original source* spells the store to obj+0x14 differently such that the address RTL is a bare REG? E.g.:
```
u16 *q = (u16 *)(obj + 0x14);  // q computed
... 
*q = *q + (...);   // store at (mem (reg q)) — bare REG address!
```
The MEM address would be `(reg q)` → GET_CODE(addr) == REG, not PLUS → `all = 1` → invalidates ALL memory entries including the symbol load! And that happens between load #1 and load #2 if the store is sequenced after load #1... 

But careful about the order: in the target, load #1 (2db8) comes before the store (2dd4), and load #2 (2dd8) after. So if the source is:

```
obj = a0->unk20;
q = (u16 *)(obj + 0x14);       // address into a reg
*q = *q + (a0->unk2A - *(u16*)((u8*)D_80126B78 + 0x12));
a0->unk2A = *(u16*)((u8*)D_80126B78 + 0x12);
```
Then cse: load ptr (use1), load [ptr+0x12], ..., store (mem (reg q)) → all=1 → invalidate everything → load ptr again for use2. 

But would that change the emitted code? The store becomes `sh v0,0(q)` instead of `sh v0,20(a1)`. Since q = obj+0x14 and the target shows `sh v0,20(a1)` with a1 = obj, the target's store uses the base+offset form. So the address was NOT in a separate reg in the target. Unless... the store instruction is `sh v0,20(a1)` — that's base a1 with offset 20, so the address was `(plus a1 20)` at the RTL level. So the target's store is a PLUS address. Contradiction with my theory.

Hmm. Unless cse saw the address as `(reg q)` where q was *coalesced/rematerialized* into a1+20 by the address optimizer later? No — gcc 2.7.2 does have address optimization in... Hmm, actually there IS: the `*q` form where q is a pseudo assigned `obj+0x14` — the RTL for the store would be `(mem:HI (reg q))`. The final instruction `sh v0,20(a1)` would require q to be allocated to a1 and the offset folded — not possible; a reg holding obj+0x14 is a separate value.

So the store's address at RTL must have been (plus reg const) → nonscalar only. So the invalidation theory fails for the target's own code... unless the invalidation comes from a *different* store that got deleted later, or from something else in the RTL stream at cse1 time.

Wait! What about the stack stores? `sh v0,16(sp)` etc. — the svec_in stores. Those are at (plus sp const) → PLUS → nonscalar only, not all.

Hmm, what about `(mem (symbol_ref))` entries and the `sp` writes? No.

OK, alternative theory: the loads are not merged because cse didn't *insert* the symbol load into the table. Why? Look at cse_insn: for a load `(set (reg) (mem ...))`, cse inserts the MEM expression if `dest` is a reg... There's a condition: "Don't insert a memory reference if it is volatile or if the address is a SYMBOL_REF and the value is not ... " Hmm. There's the concept of "the value of a load is recorded only if it's not a 'cheap' expression". Let me look at the insert path and any condition about `REG_P (dest)` and "SET_DEST is a SUBREG" etc.

Actually! Important: in gcc 2.7.2 cse, there's a rule that a MEM load is NOT recorded in the table if the destination is a hard register... no.

Let me think about another possibility: maybe the target's second load is a *reload* of a value that cse forwarded but the pseudo was spilled... no spills here.

Alternatively the second use's pointer might have been loaded into a pseudo that died and regalloc reused; but the instruction count says two lw's.

Hmm, what if the first "load" pair at 2db8 is not from the same statement? Let me look: 2db8 lui v0; 2dbc lw v0; 2dc0 lhu v1,42(s0); 2dc4 lhu a0,18(v0). Then 2dd8 lui v0; lw v0; 2de0 lw v1,44(s0); 2de4 lhu v0,18(v0); 2de8 bnez v1; 2dec sh v0,42(s0).

Wait: could the second load pair actually be from the *if* test? No, the if tests a0->unk2C (lw v1,44(s0)).

OK so let me try the empirical route: write candidate variants and score them. Time budget: ~25 min for this item, started 17:24; it's maybe 17:35 now. I have ~15 min more. Let me be efficient: try a batch of candidates with sc.sh.

Candidate ideas:
A) store via a `u16 *q = (u16*)(obj+0x14)` pointer (bare REG address → all invalidation). Even if it changes the store form, let's see the score — it might surprise us (address may still fold? no).
B) Dead-reset the pointer between uses: `s32 *gp = D_80126B78; ... use gp ...; gp = 0; a0->unk2A = *(u16*)((u8*)D_80126B78+0x12);` — hmm, the dead `gp = 0` doesn't invalidate the MEM entry.
C) Byte store: `*(u8*)&something = ...`? The target has no byte store.
D) Struct-member read for use1 so it's in_struct... no, the invalidation needs the *stored* expr to set all.

Hmm wait, actually re-read: `invalidate_memory` removes entries where `p->in_memory && (all || (nonscalar && p->in_struct) || cse_rtx_addr_varies_p(p->exp))`.

`p->exp` for our pointer load is `(mem (symbol_ref))`; cse_rtx_addr_varies_p(exp)? Let me check that function — it may be true for symbol refs?! If the function says "the address varies" for a symbol_ref (since a symbol's address... no, it's constant).

Hmm, but hold on: is our pointer load really recorded as `(mem (symbol_ref))`? D_80126B78 is `extern s32 *`. In the TU, `D_80126B78` is declared as a pointer. The load is `(mem:SI (symbol_ref "D_80126B78"))`. OK.

Let me check cse_rtx_addr_varies_p.
