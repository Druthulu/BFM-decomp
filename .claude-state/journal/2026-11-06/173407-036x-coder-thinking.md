---
ts: 2026-11-07T00:34:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FhsFdd6rtDBxErbxSlSi
---
There's the spliced TU (365 KB). I can dump passes on it. But careful about disk and time. Let me dump only cse1 (.cse) for this candidate. The cc1_dumps_tu.sh runs many dumps (-dr -ds ... -dt -dJ -dd) — that produces a lot but on a 365KB TU it's manageable? It might be big (100s of MB?). Disk is capped with ~4 GB free. Hmm, the dumps for a 14k-line TU could be ~50-100 MB. Risky but let's cap: I can grep the .cse for the function.

Actually, a cheaper route: write my own minimal dump command? The rules say don't invent tools... but a scratch script is fine. Simpler: run cc1 with only -dc (cse1 dump) on the .i file. I'd have to reproduce the cpp line. cc1_dumps_tu.sh accepts a .c file and does cpp+cc1. It hardcodes the full dump flag set. DUMP_ROOT is configurable.

Let me set DUMP_ROOT to my item dir and run it, then immediately grep and rm -rf the dumps. It's ~1 command + cleanup.

Actually wait. Before burning time on dumps, let me reconsider the mechanism once more, because there's a subtlety I may have missed: cse's table entry for the symbol load — when is it inserted? In cse_insn, a load's src is inserted if `sets[i].src_elt == 0`... The load `(set (reg v0) (mem (symbol_ref)))`: src = the MEM, and cse inserts it into the table. But there's a check: cse only inserts an expression if it's "not too expensive" — no, that's for replacing (COST). Insertion happens for all sources... Actually there IS a condition: in cse_insn,

```
	  /* Don't enter a value into the table if it is a volatile mem... */
```
Let me grep for "volatile" and the insert conditions around line 7100-7230.

Rather than guess, let me look at the actual cse1 dump for the *orig* body (with the barrier) vs my w3, to see whether the two loads exist. But the target (orig) obviously has two loads.

Faster: let me try more candidates empirically. The empirical loop is cheap (~10 s per score). Let me generate a batch of ~12 candidates covering the move families, then score them all with sc.sh, and pick the best.

Candidate ideas (real C only):
1. w3 variants: dead byte store at different places (before the first use, after the call).
2. Dead byte store to a *global* byte symbol? That would emit a store that isn't dead → extra insn.
3. Use `volatile`? no.
4. Store via a bare pointer variable at offset 0 (REG address → all=1): e.g. `u16 *q = (u16 *)(obj + 0x14); *q = *q + (...);` — the store would be `sh v0,0(q)`; but if the target's store is `sh v0,20(a1)` this changes one insn (score 1?) but might fix the pointer reload (saving 2 insns and a nop). Net could be better or worse. Worth trying.
5. Byte store through a bare pointer: `*(u8 *)obj = 0;`? That's a real store to obj (not dead) → extra insn.
6. Make the first use's load not cse-cached: e.g., read the pointer through a *different* expression that's not cse-equal: `*(u16 *)((u8 *)D_80126B78 + 0x12)` vs `*(u16 *)((u8 *)D_80126B78 + 0x10 + 2)`. Constant folding happens in the front end, so identical.
   What about `((u16 *)((u8 *)D_80126B78))[9]` — identical RTL.
7. What if use1 reads via an s32 pointer cast at a byte offset: `*(u16 *)((u8 *)D_80126B78 + 0x12)` — same.
8. What if use2 reads `a0->unk2A = ...` where the pointer is loaded into a *different-typed* variable, e.g. `u8 *p = (u8 *)D_80126B78;` — same.

Hmm. What if the two uses genuinely differ in mode: use1 reads `(u16*)` (HI), use2 also HI. Same.

9. What if the second use is spelled with a struct member: `((Unkstruct_800B5CB8 *)D_80126B78)->unk12` — RTL identical (plus const 0x12), MEM_IN_STRUCT_P maybe 1 → in_struct=1. Then the *store* at obj+0x14 (nonscalar, PLUS, HI) sets nonscalar=1 but not all; invalidate_memory removes entries with `nonscalar && p->in_struct`. If use2's *pointer load* MEM has in_struct... no, the pointer load is a different MEM (the symbol). Hmm, unless cse caches the whole `(mem:HI (plus (mem:SI (sym)) 18))` expression — no, it caches the innermost loads.

Hmm! But wait: what if the two uses' *pointer loads* differ in in_struct? `(mem:SI (symbol_ref D_80126B78))` — the MEM_IN_STRUCT_P flag on this load comes from the front end: if the source writes `((struct S*)D_80126B78)->unk12`, then the load of D_80126B78 itself is just a scalar variable load (in_struct=0).

10. Make the *first* use read the pointer as a scalar and the second use... 

OK here's another thought: what if the target's two loads come from cse NOT merging because the *first* load's value is stored into a pseudo that is then clobbered... no.

Let me look at the cse1 dump of the ORIGINAL (with barrier) to see the exact RTL — that tells me what the barrier did and what the RTL looks like. Then compare with w1's dump. Actually the more valuable dump is of a *successful* structure... there is none.

Time is ticking (24 min). Decision: I'll do a quick batch of ~10 candidates now, score them all, and if none hits 0, continue to 30 tries then wall it.

Batch plan (all derived from w1):
- a1: dead byte store to svec_in at 16(sp) placed *after* the first use but the store placed before the statement? (already w3)
- a2: `*(u8 *)&svec_out = 0;` after the call but before the unk2A store (svec_out IS read after — would break semantics/emit sb; skip).
- a3: bare-reg store q: `{ u16 *q = (u16 *)(obj + 0x14); *q = *q + (a0->unk2A - ...); }`
- a4: read use1 via `((u16 *)((u8 *)D_80126B78))[9]`
- a5: dead byte store placed before the big statement (after obj=...)
- a6: dead byte store to a local `u8 z;` — frame risk.
- a7: two-step: pointer var `s32 *gp = D_80126B78;` used in both, plus dead reset `gp = 0;` between.
- a8: `svec_in.vx = 0;` after the call (HImode store, not QI) — probably no effect but cheap.
- a9: use `*(u8 *)((u8 *)&svec_in + 6) = 0;` (same as w3 but explicit offset)
- a10: dead byte store to a global? e.g. `D_80126B5C = D_80126B5C;` — a store to a global byte; not dead → extra insn.

Hmm, let me reconsider (a7): the "2nd set" mechanism. Actually, maybe the target's reload is NOT from a cse invalidation but from a *second set* of the pseudo holding the pointer: if the source re-loads D_80126B78 into a variable that already holds it... cse replaces it with a copy from the existing value (no reload). So no.

Honestly, the most promising is the QImode store — but my test shows it didn't invalidate. Let me verify with the dump why. That's the key learning, and it may unlock the crack.

Actually WAIT. I bet I know why: **flow.c runs BEFORE cse?** Let me check toplev order in 2.7.2. If flow (dead code elimination) runs before cse1... no.

Hmm, alternatively the sb might have been moved by *jump_optimize* (before cse1)? It doesn't reorder.

OR the store might not be QImode: `*(u8 *)&svec_in = 0;` — could gcc promote it? No, it's an explicit char store; it emitted `sb`.

So why no invalidation? Let me check `note_mem_written` again:

```
else if (cse_rtx_addr_varies_p (written))
  {
    if (! ((MEM_IN_STRUCT_P (written)
	    || GET_CODE (XEXP (written, 0)) == PLUS)
	   && GET_MODE (written) != QImode))
      writes_ptr->all = 1;
    writes_ptr->nonscalar = 1;
  }
writes_ptr->var = 1;
```

For QImode + PLUS: `(MEM_IN_STRUCT_P || PLUS) && mode != QImode` = `(1||1) && 0` = 0; `!0` = 1 → all=1. So all=1. Then `invalidate_from_clobbers` → `if (w->var) invalidate_memory(w)` → removes all in_memory entries.

Unless cse_rtx_addr_varies_p(written) returned FALSE for the store! If the address is `(plus (reg) (const))` where the reg is a *constant-quantity* (e.g., the stack pointer is a known constant in cse's terms?) — for virtual-stack-vars regs, cse's qty_const could be valid (the frame pointer is a constant offset from the stack pointer). In the first branch: `GET_CODE(x)==MEM && GET_CODE(addr)==REG && qty valid && qty_const != 0 → return 0`. For PLUS with CONST_INT offset: second branch → `qty_const[...]` nonzero → return 0 (does NOT vary)!

So for a store to a stack slot with a constant offset from a known-constant base (virtual-stack-vars / frame pointer / arg pointer, which cse treats as a constant quantity), `cse_rtx_addr_varies_p` returns 0 → the `else if` branch is NOT taken → all stays 0, var=1 → invalidate_memory with all=0,nonscalar=0 → removes only entries with addr varies. So the sb does NOT invalidate! That explains w3.

So the dead byte store must be at a *varying* address: through a pointer register that isn't a known constant. E.g., a byte store through `obj` (a real pointer): `*(u8 *)obj = 0;` — address `(plus (reg obj) (const 0))`? Actually `*(u8*)obj` with offset 0 → `(mem:QI (reg obj))` → GET_CODE(addr)==REG and obj's qty_const is not valid (it's a loaded value) → varies → all=1! 

But such a store is a real store to a0->unk20's memory — would it be deleted? It's a store to memory pointed to by a pointer, not deletable. It would emit an extra `sb` → score +1, but might fix 3-4 insns.

Hmm. But is there a dead store through a varying address that gets deleted later? flow.c's insn_dead_p can delete a store to memory if the memory is "dead" — for a pointer-based store, flow can't prove it's dead (aliasing). So it stays.

Unless the store is to a stack slot *through a pointer* that flow can trace... e.g., `p = &svec_in; *p = 0;` — cse's address is `(reg p)`; is p's qty_const valid? If cse knows p = &svec_in (a constant address), then... cse_rtx_addr_varies_p checks qty_const[reg_qty[p]] != 0 → p's value is a constant address → returns 0 (doesn't vary). Hmm! So that fails too.

Hmm, so we need a store whose address is genuinely varying (unknown base) AND dead. A store through an unknown pointer is never dead.

BUT: what about the *QImode* condition applying to a store to a global symbol? `(mem:QI (symbol_ref))` — addr doesn't vary → not all. Hmm.

What about a store to a *stack slot at a variable offset*: `*((u8*)&svec_in + i)` where i is a variable that's 0 — the address `(plus (reg fp) (reg i))` → varies → QI → all=1! And flow may still delete it if it's a dead store to a local array... with a variable index, flow can't prove deadness. Hmm.

Wait, but actually, do we need the store to be deleted? Let me reconsider: maybe we can *keep* an extra insn if it fixes more. Currently score 11 (w1) with 67 ins vs 68. w3 is 68 with sb, score 10. The target has 68 ins including 2 pointer load pairs. If I add a byte store at a varying address, I get +1 insn (69) but the pointer reload adds 2 insns... hmm, the target's shape needs exactly the two loads and no extra store. Since a dead store can't be at a varying address without being non-dead... 

UNLESS the store is a byte store to a stack slot via a variable-offset address that flow deletes because it's a *dead local array element* with a constant... no.

Alternative: the store could be to memory that flow deletes: flow's insn_dead_p handles stores to `(mem (plus (reg) (const)))` where the reg is the frame pointer and the slot isn't used. That's the w3 case, but that address doesn't vary.

So: is there another route to `all=1`? A call — no. BLKmode — a struct copy! `svec_in = svec_out;` after the call: svec_out is read (well, after the call it IS read for the stores at 6/10/14(sp)). Hmm, if I do a struct assignment *after* those reads, it's dead but emits word stores (8 bytes = 2 sw) — extra insns, and BLKmode? For an 8-byte struct, gcc 2.7.2 uses two SImode stores (not BLKmode). Only big structs get BLKmode.

What about `memcpy`? no.

Hmm, what about the `obj+0x14` store being *spelled* so that its address varies: it already does (reg a1 + const) — varies (a1 unknown) → nonscalar=1, all=0 (because PLUS && HI != QI). What if the store were QImode? It's HI in the target.

What if I add a *byte* store at obj+0x14's neighbor... extra insn.

Hmm hold on, let me revisit: maybe the pointer reload in the target comes from a different mechanism entirely — perhaps the *first* pointer load is not cached because cse's `insert` for the load is skipped due to `sets[i].src_elt` conditions: e.g., if the load's SET has a REG_EQUAL note or the load is in a different "class"...

I should just look at the cse1 dump of the target build. The baseline object came from the src with the barrier; a cse1 dump of orig.c would show the RTL. But the RTL with the barrier tells me the barrier's effect, not the original C.

Better idea: dump cse1 for w1 and see if the two loads merged there (they did per the object). Then I know cse1 merges without an invalidation. The question remains how to invalidate.

Wait — maybe the answer: `invalidate_memory` is also called from `invalidate_skipped_block`/`skipped_writes_memory` (line 7827): 
```
  note_mem_written (dest, &skipped_writes_memory);
  if (skipped_writes_memory.nonscalar)
    skipped_writes_memory.all = 1;
```
That's for skipped blocks (jump-following). Interesting: for *skipped* blocks (code between the end of a block and the start of the next, i.e., code jumped over), a nonscalar write sets all=1.

Hmm, that's about CSE following jumps.

OK — new idea, and I think this is the real one: **cse's basic-block boundary**. cse does NOT carry memory entries across basic blocks. The target's two uses are in one basic block. But what if the original source had a *branch* that was later removed? E.g., `if (1)`? Constant-folded early.

Hmm, but here's a thought: what if the original source order is different: maybe the second use (`a0->unk2A = ...`) comes *before* the big statement in the source, and the target's code order... no, the target's order is fixed.

Let me try yet another approach: accept the constraint and try to make the FIRST pointer load not cached, e.g., by making use1's pointer expression cse-unequal to use2's. cse compares RTL with `exp_equiv_p`, which for MEM checks `MEM_VOLATILE_P` and mode and address. Two loads from `(mem:SI (symbol_ref))` are equal.

BUT: what if use1 loads the pointer via a *different symbol* that aliases the same address? No.

What if use1 reads `D_80126B78` as an `s32 *` and use2 as a `u8 *`? The load mode would still be SI (pointer). Equal.

Hmm, what if use2 reads the pointer through `*(s32 **)0x...`? no.

What if use1's expression is `(s32)D_80126B78` (the value) and use2 uses a variable assigned from it earlier? Same.

OK, what about the address computation: use2 could use `((u16 *)((u8 *)D_80126B78 + 0x12))` vs use1 `(*(u16 *)((u8 *)D_80126B78 + 0x10 + 2))`. Front-end folding makes them equal.

What if use2 adds the offset at runtime: `u8 *p = (u8 *)D_80126B78; ... *(u16 *)(p + 0x12)` — same RTL.

What if use2 uses a *different* variable holding the same pointer, assigned BEFORE the store: `s32 *g = D_80126B78;` then use1 uses `((u8*)g + 0x12)` and use2 uses `D_80126B78` — cse replaces the second load with g's value (copy). Same.

Hmm.

Let me reconsider: maybe the target's two loads arise because the original C reads the pointer TWICE and the store in between is a *nonscalar store with in_struct on the symbol load*... 

Ugh. Let me test the in_struct theory quickly: make use1 read via a struct member so its MEM is in_struct=1: `((Unkstruct_800B5CB8 *)D_80126B78)->unk12`? Wait — no! D_80126B78 is an `s32 *` to a camera struct; unk12 at 0x12? The struct Unkstruct_800B5CB8 has unk12, unk1A, etc. for the a0 object. The camera object is a different type, but I can use a cast to a struct with a u16 at 0x12 — e.g. reuse Unkstruct_800B5CB8 if it has unk12 as u16! Let me check the struct definition: `((Unkstruct_800B5CB8 *)a0)->unk12` is u16 (assigned to svec_in.vx). Yes.

So: `((Unkstruct_800B5CB8 *)D_80126B78)->unk12` — that's a member access on a cast pointer; MEM_IN_STRUCT_P would be... In gcc 2.7.2, the front end marks MEM_IN_STRUCT_P for aggregate member accesses (`COMPONENT_REF`), so YES, in_struct=1 for the HI load. But that's the *load of the u16*, not the pointer load. cse caches both loads separately:
- `(mem:SI (symbol_ref))` → the pointer (in_struct=0)
- `(mem:HI (plus (reg ptr) (18)))` → in_struct=1

The store at obj+0x14 (nonscalar) invalidates entries with in_struct → the HI load is invalidated either way (its addr varies anyway).

The pointer load survives (in_struct=0). So no.

Hmm, unless the *pointer load* can be made in_struct=1: if the source reads the pointer as a member of a struct: e.g. `((s32 **)&D_80126B78)`... no. But what about `D_80126B78` being declared as a struct member? No.

OK. Radically different: maybe the reload is forced by **local-alloc/global-alloc** rather than cse: i.e., cse merged them, but the merged pseudo was allocated to a *caller-saved* register... it's still one load.

Let me now check the actual cse1 dump for w1 to see whether cse1 merged or whether the merge happened in cse2, and whether the store invalidation appears. Actually, better: dump for orig (with barrier) — I know it produces the target. The interesting question is what the RTL looks like *without* the barrier at each pass.

Time: 17:50 (26 min). I must decide: wall or crack. The brief requires ≥30 tries for a WALL. I have 4. Let me spend ~10 more minutes on ~20 quick candidates via a generator, then wall if nothing.

Actually — hold on. One more idea, and it's cheap and plausible: **a store through a pointer variable at a nonzero offset where the base is unknown, with QImode, that IS dead**. Dead in what sense? flow.c deletes a store if the memory is never read afterwards and the address doesn't escape... For `(mem:QI (plus (reg p) (const)))` where p is a pointer to a local, flow's insn_dead_p: it checks `if (GET_CODE (x) == MEM) ... rtx_addr_varies_p(x)` → for a varying address, `insn_dead_p` returns 0 (can't prove dead). So no deletion.

BUT: flow has a special case — stores to the stack frame (frame pointer based) are handled. So only constant-offset stack stores get deleted. And those don't vary in cse.

Hmm, unless the *stack slot address* is through a pseudo pointer... 

What about the *argument* area? no.

New thought: what if we don't need the store to be deleted because we can *replace* an existing insn? E.g., make the store at obj+0x14 a byte store? It's HI in the target.

Alternatively: what if the invalidation comes from a store to the *same* stack slot region with a PLUS address whose base is the stack pointer... same.

Let me try: `*(u8 *)((u8 *)&svec_in + 0) = 0;` — same as w3.

OK, alternative route to the same *effect* without cse invalidation: make the second use's pointer come from a *different* pseudo by introducing a copy that cse can't collapse... e.g., `s32 *g = D_80126B78; g = (s32 *)((u8 *)g);` — a cast is a no-op.

What about reading the pointer as `(s32 *)((s32)D_80126B78)`? no-op.

Hmm, what about `u32 v = (u32)D_80126B78; ... (s32 *)v`? Same reg.

What if use2 uses the pointer through a *union* member? no.

Let me try the "different mode load" idea: use2 loads the pointer as `s32` into a variable of type `s32` and then casts: `s32 g = (s32)D_80126B78; a0->unk2A = *(u16 *)((u8 *)g + 0x12);` — the load is `(mem:SI (symbol_ref))` → same.

What if use2 loads the *low 16 bits* differently... no.

I think the mechanism might genuinely be the cse block boundary. Let me test the do-while idea again but in the right place: w2 (do-while around the second use) gave 69 ins / score 21 — worse. Maybe the do-while needs to be around the *first* use, or around both, or the C0535 "do{}while(0)" splits cse1's EBB only when there's a jump... Actually a do-while(0) creates a loop note; the EBB split happens at NOTE_INSN_LOOP_BEG? Let me check the C0535 cookbook entry for the exact mechanism and how it's applied.

Let me read cookbook C0535 and C0414 quickly (grep the index first). That's what the brief suggests (MOVES+).

Time cost: ~2 min. Worth it.
