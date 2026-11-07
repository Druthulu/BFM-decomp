---
ts: 2026-11-07T00:31:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VfqgvanhjyuRv8YC6JBk
---
Worse (21, 69 ins). The do-while added an insn.

Hmm. Let me think again about what splits cse's EBB without adding insns.

Alternatively, maybe the right move is different: make the first use's pointer load *not* recorded in cse at all. Or make the store between them set all=1.

Idea: the store between them is `sh v0,20(a1)`. If in the original source that store were written so that its address is `(reg)` — e.g., using `obj` directly with offset 0 through a pointer variable at 0x14... we discussed the target shows `sh v0,20(a1)` — base+offset. Hmm, BUT: what if the source uses a *u16* pointer variable q = (u16*)obj + 0xA; then `q[0] = ...`? Still PLUS.

What about a store to a *byte*? Not in the target.

Hmm, what about a store where the address is a bare REG but that reg is allocated to the same as a1 with offset folded? Impossible.

Let me reconsider: is it possible that in the target's compile, the first use's load was NOT cse-cached because cse didn't have the symbol load in the table — because it was loaded into a *hard* register? No, it's a pseudo.

New idea: maybe cse's table entry for `(mem (symbol_ref D_80126B78))` IS removed by the store at obj+0x14 because of `p->in_struct`. What sets in_struct for the pointer load? `hash_arg_in_struct` is set in canon_hash when MEM_IN_STRUCT_P(x). The MEM `(mem:SI (symbol_ref))` for a global pointer variable declared as `extern s32 *D_80126B78;` — MEM_IN_STRUCT_P would be 0 (scalar). Unless the declaration makes it part of a struct... 

Hmm, wait. What if the original source accesses it as `((Unk**)&D_80126B78)[0]`? no.

Let me step back and consider a totally different explanation: maybe the target's second load is not a *repeat* load of the same value but the result of the first load's value being killed by the store at 2dd4 — because the store's base register a1 is... no, a1 = obj, distinct.

Alternatively, maybe cse DID forward and the target's code comes from *reload* re-materializing a spilled pseudo? No spills.

Hmm, hold on. Let me reconsider the whole shape: maybe the target's two loads are because the original source's two uses go through *different variables*, e.g.:
- use1: `*(u16 *)((u8 *)D_80126B78 + 0x12)` 
- use2: `*(u16 *)((u8 *)D_80126B78 + 0x12)` — same.

But what if the original source computes the second as `a0->unk2A = a0->unk2A - diff` style... no, the store value is the loaded u16.

Let me try a different empirical approach: maybe I can get cse to not merge by making use1's MEM in_struct=1 and the store nonscalar. Recall invalidate_memory removes entries with `nonscalar && in_struct`. If the first use's *pointer load* were in_struct... it's the symbol load; can't.

BUT: what if the load that cse caches isn't the pointer but the full `(mem:HI (plus (reg) 0x12))`? That one has a varying address, so it's invalidated by the store anyway (both uses reload it — indeed both uses do `lhu ...,18(...)`).

So the ONLY cached thing is the symbol pointer load.

What if the source reads the pointer value into a local variable ONCE (before use1), and the second use re-reads the symbol? Then:
```
s32 *gp = D_80126B78;   // load 1
...use (u16*)((u8*)gp+0x12)...
a0->unk2A = *(u16*)((u8*)D_80126B78 + 0x12);   // load 2
```
cse would still merge load 2 into gp's value (same expression).

Unless gp gets a second set between: `gp = <something>` — a real 2nd set of gp kills the equivalence? No: the table entry is keyed by the *expression* `(mem (symbol_ref))` → reg gp. If gp is re-set, cse's reg_tick mechanism invalidates entries that *mention* gp... but the entry's value is gp itself; when gp changes, cse removes the entry via `reg_tick`. Hmm, but the entry is for the MEM expression whose value is gp; if gp changes, the entry becomes stale and cse removes it (that's `delete_reg_equiv` / tick). But then a re-load of the symbol would... re-insert. Still a load. Not helpful.

OK, radically different approach: what if the target's source uses `D_80126B78` in a form that is NOT cse-equal at the two sites because of a cast of different modes? E.g., use1 reads the pointer via a `u16 *` variable and use2 via an `s32 *`? The load of the symbol is `(mem:SI (symbol_ref))` in both cases since the pointer type is s32* either way.

Hmm, what if use1 uses `D_80126B78` directly and use2 uses a *copy* through a pointer-to-pointer with an offset that folds to 0: `*(&D_80126B78 + 0)`? RTL: `(mem (plus (symbol_ref) (0)))` — the front end folds +0 away probably.

What about `((s32 **)D_80126B78)`? no.

Time check: I'm spending too long. Let me reconsider the wall: notes say T10 S11 found best 11 in 6 tries, tagged cse-const-addr. The brief requires ≥30 scored tries and ≥20 min for a WALL. I've done 2 tries so far. I need to grind through ~30 candidates in the remaining time, exploring the catalog moves.

Let me be systematic and generate a batch of candidates quickly, scoring each with sc.sh (one line per candidate). I'll make ~10 at a time.

Candidate families:
1. Store-form variants for the obj+0x14 store:
   a. `obj[0x14/4]`? no, it's u16.
   b. pointer var q: `u16 *q = (u16 *)(obj + 0x14); *q = *q + (...);` — bare reg address → all=1 invalidation. Even though the emitted store would be `sh v0,0(a?)`, maybe the address ends up folded? Let's test; it's cheap.
   c. `((u16 *)obj)[0xA]`.
2. Read the second use through a struct member: `((Unkstruct*)D_80126B78)->unk12` where unk12 is at 0x12 in that struct... but Unkstruct_800B5CB8's unk12 is a field of the a0 object. D_80126B78 is an s32*; I can define a local struct type? I can't add decls outside the body but I can add locals... I could cast to a struct type defined in the TU. Hmm, if the struct member read makes MEM_IN_STRUCT_P=1 on the *pointer load*? No.
3. Make use2 read via a different pointer type/mode: e.g., read as `s16`/`u32` and mask? That changes instructions.
4. Force a real 2nd set of a variable holding the pointer, plus dead-reset.

Hmm, hold on. Let me reconsider the problem from the *other* side: maybe the reload comes from making the first use NOT keep the pointer: i.e., in the target, the pointer load at 2db8 feeds `lhu a0,18(v0)` immediately. In my w1, the pointer is in a2 and reused. What if cse merged them but regalloc *chose* to reload? No.

Actually, let me look at the possibility that in the target's compile, the two uses were in different basic blocks at cse1 because of the *if* structure... no, the if comes after.

Wait wait. Let me re-read the source. The statement:
```
CAST_WIDTH(u16, obj, 0x14) = CAST_WIDTH(u16, obj, 0x14) + (((Unkstruct_800B5CB8 *)a0)->unk2A - *(u16 *)((u8 *)D_80126B78 + 0x12));
```
The barrier, then:
```
((Unkstruct_800B5CB8 *)a0)->unk2A = *(u16 *)((u8 *)D_80126B78 + 0x12);
```

The target shows the pointer load for use2 AFTER the store, i.e., the load is not hoisted. And the load for use1 before. If cse merged, the value would be in a pseudo live across the store → a2 in mine. The target has a fresh load. So the original source truly has two loads at RTL after cse.

So the original source must prevent cse. What C constructs prevent cse from caching a global pointer load across a store, in gcc 2.7.2?

→ If the store is a QImode store with a PLUS address, all=1.

Is there a QImode store in the source that gets deleted before codegen but after cse? cse runs after flow/combine? No: order is jump, cse1, loop, cse2, flow, combine, sched. So a byte store present in the source would survive to cse1 unless jump_optimize/expand removed it.

Hmm! What about the *svec_in/svec_out* stack stores — `sh v0,16(sp)` are HImode.

What about a store through a `char *`? Not in the target.

Alternatively, an `all` invalidation comes from a call — and note the target's call to func_8012F14C is BEFORE both uses.

Hmm, so how?? Unless... cse1 processed the function in one EBB, and the pointer load at use1 was inserted into the table, and then at use2 cse *did* substitute — but then combine/flow/sched... no.

Hold on, maybe I should check: does the target actually come from the current src? Let me verify by compiling the current src (orig.c with barrier) — it scores 0, yes. So target = compile of orig.c. The barrier's memory clobber (an asm with `"memory"` clobber) sets... how does cse treat an asm with a memory clobber? The insn has `(clobber (mem:BLK (scratch)))` → note_mem_written/GET_CODE(addr)==SCRATCH → everything → all=1. Yes! That's the barrier's effect: it invalidates ALL cse memory entries, so use2 reloads the pointer.

So the question stands: what real C gives `all` invalidation between the uses?

Options for `all`:
(a) BLKmode store — a struct assignment! `struct_assign` of a whole struct emits BLKmode stores (or a call to memcpy for large ones). A small struct assignment emits several word stores, not BLKmode. Hmm, but if the assignment is to a *different* struct and then optimized... For BLKmode, the front end emits `(set (mem:BLK ...) ...)` only for large/unknown-size copies → memcpy call.
(b) QImode store with a PLUS address: a byte store!
(c) store with a bare-REG address (varying, not PLUS, not in_struct): `*p = v` where p is a pointer variable and the offset is 0!
(d) a call.

(c) is interesting: `*q = ...` where q is a pointer. The store instruction would be `sh v0,0(aX)`. The target shows `sh v0,20(a1)`. So the target's own store is PLUS-based. Unless the source has ANOTHER store through a bare pointer that we're missing... 

Hmm, is there one? Look at the target: stores are sh v0,6(s0), sh v0,10(s0), sh v0,14(s0) (svec_out fields), sh v0,20(a1) (obj+0x14), sh v0,42(s0) (a0->unk2A), sw v0,28(s0) (unk1C), sw v1,28(s0), sw v0,44(s0) (unk2C), sw v0,4(a0) (obj+4). All PLUS.

So no bare-REG or QImode store in the target's output. But a store could have been *deleted* by flow/combine before codegen — but cse runs before flow/combine. So a dead byte store in the source would be in the RTL at cse1 time and set all=1! And later passes (flow, combine, sched) delete it.

Ooh, that's a real possibility: a dead byte store that survives cse but is deleted by flow/combine/dead-store elimination later. But cse1 itself runs `delete_dead_from_cse`. Hmm, cse deletes a store if it's dead in the cse table? No, cse deletes loads whose values are unused, and it does "delete_dead_from_cse" for dead loads. A store to memory is never deleted by cse.

But: would the store appear in the final output? flow.c deletes dead stores (`insn_dead_p`). If the store is to a global, it's not dead. If to a local variable (stack), flow can delete it.

Hmm, but the target's stack frame is 40 bytes with no local beyond svec_in/svec_out... A dead byte store to a local would be deleted by flow (after cse1, before codegen). 

But would that be "real C"? A dead store like `*(u8*)&pad = 0;` where pad is a local — that's a dead-store lever, kind of like the dead-reset (C0414) which IS in the catalog. C0414 is "dead-reset cse-breaker" — a dead store used to break cse. So this is a legitimate catalog move!

The catalog: C0414 dead-reset cse-breaker. The move: assign a dead value to a variable between two uses; cse's store invalidation breaks the cache. For a *stack scalar* store: the store `(set (mem:HI (plus (fp) (const))) ...)` — address is PLUS → not all, nonscalar=1; the entry for the symbol load has in_struct=0 → survives. Hmm, so a dead store to a local doesn't set all unless it's QImode.

Wait, but C0414 worked in practice for "3 launders in G16x". The mechanism there was breaking a *register* equivalence (2nd set), not a memory entry.

For our case we need `all`. So: a dead **byte** store (QImode) with a PLUS address, or a store through a bare pointer register.

Let me check the QImode condition precisely:
```
else if (cse_rtx_addr_varies_p (written))
  {
    if (! ((MEM_IN_STRUCT_P (written) || GET_CODE (XEXP (written, 0)) == PLUS) && GET_MODE (written) != QImode))
      writes_ptr->all = 1;
    writes_ptr->nonscalar = 1;
  }
```
So QImode + varying address → all=1. Yes.

So: `*(u8 *)somewhere = 0;` — a dead byte store — would set all=1 and force the reload, then be deleted later if dead.

What byte store can I write that is legal and dead? E.g. a local `u8 pad; pad = 0;` → store to (plus fp const) QImode → all=1! And flow deletes it as dead (local, never read). 

Would it survive cse? Yes, flow runs after cse2.

Hmm, but does a dead store to a local get eliminated earlier by the front end (e.g., expand doesn't emit dead stores; the store is emitted). Yes, expand emits it.

But wait — does the dead store affect anything else? cse1 deletes dead *loads*, and the store remains; flow deletes it. If it's deleted, the emitted code is unchanged. Let's test!

Candidate w3: add a local `u8 pad;` (unused otherwise, but storing to it) — careful: an unused local adds stack frame! The frame is 40 bytes: svec_in (8 bytes at 16..23), svec_out (8 at 24..31), ra at 36, s0 at 32, sp+40. A local `u8 pad` would be allocated somewhere, but since the store is dead and deleted, the frame might still grow because the variable's stack slot is allocated at expand... Actually gcc 2.7.2 assigns stack slots in expand (the frame size is fixed at that point) — a dead store to a local would still reserve the slot? The slot allocation happens during expand (assign_stack_local) — so the frame would grow by 4-8 bytes, changing `addiu sp,sp,-40`. Hmm, that would break the match.

Unless the dead store is to an *existing* local (e.g., svec_in's padding). svec_in is SVECTOR {short vx,vy,vz,pad} — 8 bytes, at sp+16. A dead byte store to `svec_in.pad`? But svec_in is passed to the call, so its contents matter — but the pad field is not set by the source. If I write `((u8*)&svec_in)[6] = 0;` before the call, that changes the call's argument (the pad byte) — semantically fine? It changes the value in memory, not the code. And it would emit a `sb` before the call — which would then be part of the call's arg setup and NOT dead (memory passed to a call). That adds an insn.

Hmm. Alternatively, dead byte store to an existing local that is dead at that point: e.g., `svec_in` is dead after the call! A byte store into `(u8*)&svec_in` AFTER the call would be dead (the local is never read again) → flow deletes it. And the frame doesn't grow (svec_in already exists). And it would emit `sb` after the call → sets all=1 at cse1 → forces reload of the pointer for use2! Then flow deletes the dead store (stack slot never read).

But careful: would it be placed correctly? The store must be between use1 and use2. Let's place it right after the barrier spot (i.e., between the statement and the unk2A store).

Also: does the dead store change cse of the *first* use? It's after, so no.

But there's a risk: flow's dead-store elimination might not delete a store to a stack slot if the address escapes (it doesn't here).

Also cse1 itself: `delete_dead_from_cse` deletes dead *loads* only. Fine.

Another risk: sched1 might move the sb; but it's deleted by flow before sched.

Wait, actually the pass order: cse1, loop, cse2, flow, combine, sched... flow deletes dead stores? flow.c's `delete_dead_jumptables`... In 2.7.2, dead store elimination is in flow.c? Hmm, `flow_analysis` does `insn_dead_p` and deletes dead insns — yes, flow.c has dead code elimination in the `flow_analysis` pass, but dead *stores* to memory are handled by... combine? Actually gcc 2.7.2's dead store elimination is in flow.c (`delete_dead_insns`? no). Let me recall: `dse.c` doesn't exist in 2.7.2. Dead store elimination in 2.7.2 is done by `flow.c`'s `insn_dead_p` (which handles MEM destinations when `rtx_addr_varies_p` is false and the memory is a local...) and by `combine`'s `try_combine`? Hmm.

Actually in gcc 2.7.2, `flow.c` has `insn_dead_p` handling: "Don't delete stores to memory unless the memory is dead" — it uses `last_mem_set`/`rsp`? I recall the wall tag "flow-dead-store — flow.c insn_dead_p (last_mem_set + rtx_equal_p) deletes the repeated b[0]/b[2] stores". So flow DOES delete dead stores to stack slots. Good.

Let me just try it. Candidate w3: add after the increment statement:
```
    ((u8 *)&svec_in)[6] = 0;
```
Hmm, but wait: svec_in is dead after the call, so this is dead. But is it obviously dead to the compiler? Yes.

Actually, simpler: use svec_out — no, svec_out is read after the call. svec_in is dead after the call. 

But hmm, `svec_in` is passed by address to func_8012F14C; after the call the compiler doesn't know it's dead... it does: the local's address escaped (passed to a function), but after the call, a store to it is still dead if nothing reads it later (the compiler tracks only the local's uses). flow's dead-store analysis: `insn_dead_p` for a MEM store checks if the memory is "dead" — for a stack slot it uses `last_mem_set` logic... Let me just test empirically.

Alternatively use a different dead local that doesn't affect the frame... hmm.

Actually, even better: is there a *byte store in the target's frame* already? No.

Let me try w3 and score. If the store survives, the insn count changes; if deleted, we may get 0.

Let me also prepare a batch of variants to be efficient. But each candidate is a file. Let me write w3 with the dead byte store and score.
