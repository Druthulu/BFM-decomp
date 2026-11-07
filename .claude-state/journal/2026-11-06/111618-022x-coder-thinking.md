---
ts: 2026-11-06T18:16:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_b7vhG3GRJvfQT6xlWGAE
---
So for the load `lw v1, 204(a0)`: r0 = dest v1, r1 = operand 1 = the address `(plus a0 204)`? The operand constraint for mips load is "=r,m" — for operand 1 the constraint is 'm' or 'o'? In the code, if the operand is an address (constraint 'p' or address_operand), it walks PLUS to XEXP 0. Then combine_regs(r1=a0, r0=v1, may_save_copy=0...) — a0 is hard reg → record `qty_phys_sugg` (normal suggestion, not copy) for v1's qty. Wait but this happens only if `GET_CODE (r0) == REG`. And the loop breaks only if win.

Then in the first allocation phase, "Try to put each quantity in a suggested physical register, if it has one": qty_phys_num_sugg != 0 → find_free_reg with just_try_suggested=1, restricted to the suggested reg set (a0). So v1 gets a0 — the base register of the load becomes the suggestion for the destination. That's the mechanism: "copy preference" (actually address-base preference).

To avoid: make the load's address base not a dying hard reg... but the base IS a0 (the arg). If we first copy a0 to a local pointer p and use p as the base, then the suggestion is p's hard reg (not necessarily a0). Hmm, but p=a0 copy: global-alloc coalesces p with a0 (same hard reg $4). Then the load's base is $4 again → suggestion $4. Same.

Unless p is a *different* type that prevents coalescing? E.g., if p is a pointer and a0 is `void *`... same mode, coalesced.

What if we make the base an offset expression so the base reg is a different pseudo: e.g., `s32 base = (s32)a0;` then `v1 = *(s32*)(base + 0xCC);` — same.

Alternative: don't use a0 as the base at the load: e.g., compute the address earlier: `v1 = (s32)a0 + 0xCC;` then `v1 = *(s32*)v1;`? That's a load where the address is a pseudo (born earlier), the dest is the same pseudo → combine_regs: usedreg == setreg → "Don't tie something to itself" → no suggestion. But the extra `addiu` insn would appear (target has only lw). Unless combine folds addiu+lw into lw with offset (it does: `v1 = *(s32*)((char*)a0 + 0xCC)` → addiu folded into load offset). But if written as two statements with a temp `t = (s32)a0 + 0xCC; v1 = *(s32*)t;`, combine would fold the addiu into the load's address and then the base is a0 again.

Hmm.

What about the target's actual register: $3 = v1. Note $3 is `v1` in MIPS ABI. In the target, the load result is v1 ($3) and the compare result v0 ($2).

Since the suggestion mechanism prefers a0 (the base), we need the base to NOT be a hard register at that point, or the suggestion to be rejected because $4 is busy. If a0 is still live after the load (i.e., used later in the block), find_free_reg with just_try_suggested would fail for $4 and then fall to normal allocation which tries $0.. and gives $3.

Can a0 be live after the load with zero extra insns? The target's own code: after `lw v1,204(a0)` in block d30, `li v0,2`, then the store `sw v0,176(v1)`. If the store were `sw v0, 176(v1)`... a0 not used.

But what if the *source* uses a0 after the load in a way that combine/flow can eliminate? E.g., `if (a0 == 0) ...` no.

Alternative: make the two branch loads use different bases so no single suggestion... no.

Alternative: change the order so the load happens BEFORE the compare, i.e., hoist the load to the top: `v1 = ((...)a0)->unkCC;` at the very start, before v0 = D_80078EB1. Then a0 dies at the hoisted load, and v1 is live across the whole function (longer live range → lower qty priority, but still the suggestion $4 applies...). Hmm, but if v1 is live across the branch, the target's structure would differ (target loads in each branch).

Hmm wait. In target, the two loads are in two different blocks (d24 and d30). Both `lw v1,204(a0)`.

What if we keep a0 live by using it in the store as well? `*(s32*)(v1 + 0xB0) = v0` → could be `*(s32*)((s32)a0 ... )` no.

Idea: use `v1` for the load and also use a0 for something after, via a *dead* but not eliminated use? "dead" uses are eliminated by flow. A real use that costs no insn... e.g., a compare whose result is used? costs.

Alternative approach: make the load result not need a register at all? No.

What about `v0` and `v1` swap: the compare result goes to $2. If we instead name things so that the load result's qty suggestion... 

Hmm, what about giving v1 a copy suggestion that outranks the address suggestion? qty_sugg_compare: copy suggestions (may_save_copy) get priority over normal ones: `sugg = qty_phys_num_copy_sugg ? copy_sugg : sugg*FIRST_PSEUDO`. In the first phase, if a qty has copy suggestions, find_free_reg restricted to those. So if v1 also participates in a *copy* (set dest=src reg), it would get a copy suggestion to that register. But adding `v1 = x` adds an insn... unless combine folds it away (then no copy insn).

Wait — what if we write `v1 = ((Unkstruct*)a0)->unkCC;` where unkCC is a pointer and v1 is a pointer of a different mode? Modes tieable...

Different idea: what if the load's base reg is not a0 but $3? I.e., get a0's value into $3 first via a copy that survives (move $3,$4)? That's the target of other functions, not here.

OK let me step back. This is item 3 and I have 3 items; time budget 20-30 min each. Maybe try a batch of cheap variants and see scores:

1. plain (score 3) — done.
2. `void *p = a0;` and use p.
3. hoist load: v1 = ((...)a0)->unkCC at top; then v0=...; if...; store.
4. reorder: compute v1 after v0=2? No.
5. Split blocks differently: maybe swap the if arms (source order) so blocks differ.
6. Use `s32 v1 = ((...)a0)->unkCC;`? same.
7. Make the final store use `((Unkstruct*)v1)->unkB0 = v0` — different type spelling, same insns.
8. Use a struct-typed pointer variable for the load: `Unkstruct_80184B70 *p = a0;` then `v1 = p->unkCC;` — coalesced.

Hmm, actually think about the *suggestion* mechanism more: combine_regs(usedreg=$4, setreg=v1). It records qty_phys_sugg. The suggestion only wins if $4 is free over v1's live range. v1's range: born at the load, dies at the store. $4's life: ends at the load (REG_DEAD). The `used` set includes regs_live_at[born_index .. dead_index-1]. born_index = 2*n-1. If $4 is marked live at 2*n-1 (which is between insn n-1 and n), then $4 is used → suggestion fails. But empirically it succeeded, so $4 must be cleared at 2n-1... Hmm, maybe not; maybe the suggestion phase ran and failed, then normal allocation tried $0.. and picked... $4? No, if $4 is in `used` it can't.

Hmm wait: maybe the allocation order is $2 first? reg_alloc_order default is i (0..31). $0,$1 fixed; $2? Is $2 fixed? No. But $2 is used by v0 which is live... In block d30, at the load: v0 is dead? Let's see block d30: `lw v1,204(a0); li v0,2`. v0 is set after. Before the load, in block d30's entry, v0 from the previous block (slt result) — actually block d30 is entered from two places: fall-through from d1c? Let's trace: d10 slt a1,v0,a1; d14 bnez a1,d30; delay slt v0,v0,a2; d1c beqz v0,d30; delay li v0,1; d24 lw v1; j d38. So block starting d1c is one block? In RTL, basic blocks: block A: d10-d14 (bnez to d30, falls to block B d18). Block B: d18 (slt v0), d1c beqz v0,d30; d20 li v0,1; d24 lw v1; d28 j d38. Block C: d30 lw v1; d34 li v0,2; d38 store.

In block C, v0 is live-in (from the slt? no). Block C entered from d14 (bnez a1) with v0 = the first slt? No: at d10, v0 = lbu D_80078EB1 (loaded at d08). slt a1,v0,a1 → a1. Then delay slot slt v0,v0,a2 → v0. So entering d30 from d14, v0 = (v0<a2). Entering from d1c (beqz v0), v0 = same. In block C, v0 is redefined at d34 (li v0,2). Is v0 live-in and used? No use in block C. So v0 not live in C.

So in block C, live: a0 (until load). $3 free, $2 free, $4 free after load... find_free_reg tries $0 (fixed), $1 (fixed), $2 (free!) → would pick $2, not $3 or $4. But the target/our compile gives a0 ($4) via the suggestion. Right: suggestion mechanism overrides the normal order.

So to break the suggestion: prevent combine_regs from recording a suggestion for v1 from the load's base. Options:
- Make the base a pseudo whose hard reg is NOT free over v1's range: e.g., the base pseudo is live beyond the store. If a0 is used after the store... the function ends. But what if the base is a global-alloc'd pointer that stays live? Hmm.

- Make the load's base not a REG but something else: e.g., `lw` from `(plus reg const)` — always a reg.

- Make the destination not a REG at that point: e.g., the load result is used directly? `v0 = ((...)a0)->unkCC` then store `*(s32*)(v0+0xB0) = ...`. In block C the dest is v0? No, target uses v1 for the pointer.

- Make the base's hard reg suggestion be rejected by class: no.

- Give v1 a copy suggestion that wins: `v1 = v1`? no.

Alternative: use TWO temps so the load dest has a different qty: e.g., `t = ((...)a0)->unkCC; v1 = t;` — combine would fold the copy (t and v1 coalesce). Hmm.

Wait, what about making the load happen where a0 is still live later in the same block? In block C, if the store used a0... no.

Alternatively, restructure so that block C's load base is not a0: e.g., make the source not have duplicate identical else blocks. What if the source uses a single else block (removing the duplicate) so jump2 doesn't merge, changing blocks? The target has both d24 (with j) and d30. If the C had only one else, we'd get different block structure — target requires the merged arms (the same `lw v1;li v0,2` in both blocks).

What if we hoist `v1 = ((...)a0)->unkCC` before the if (once), so only one load? Target has two loads in two blocks; score would differ.

OK, what about a totally different angle: make a0 not a hard register at the load — i.e., copy the arg to a pseudo early: `void *p = a0;` — global-alloc coalesces p with a0 normally (copy coalescing when p's only def is from a0 and no conflicts). Actually global-alloc tries to coalesce, and p would get $4. But maybe if p conflicts (e.g., p is live across a call? no calls), it still coalesces.

Alternatively make the base an offset from a different value: `s32 b = (s32)a0;` and load `*(s32*)(b + 0xCC)`: the addiu folds → base a0.

Hmm what about making the load 16-bit twice? No, target is lw.

Let me consider: maybe local-alloc suggestion is only recorded when `may_save_copy` or when the address operand is walked. Yes it is recorded for the address reg (r1). But wait: the operand constraint check: `if (insn_operand_constraint[...][i][0] == 'p')` — only walks PLUS if constraint starts with 'p' (address_operand). For mips `lw`, the memory operand constraint is 'm'? Let me check mips.md: `(define_insn "lw" ... (set (match_operand:SI 0 "general_operand" "=r,r") (match_operand:SI 1 "memory_operand" "m,o"))`. 'm' and 'o' are not 'p', so r1 stays the full `(plus a0 204)` mem? Then GET_CODE(r1) == MEM, not REG → no combine_regs. Hmm! Then no suggestion from the address.

So why a0? Maybe from `combine_regs` in another way, or from local-alloc's "if a register dies in this insn and another is born, give the new one the dying one's reg" via `qty_birth`... Actually there's the `reg_is_born` + `wipe_dead_reg` interaction: when a0 dies at the load and v1 is born at the load, the death happens first (wipe_dead_reg before note_stores), so regs_live_at has a0 cleared from 2n-1? Then find_free_reg's normal scan picks the lowest free: $2 is free... unless v0 is live. Hmm.

Wait, maybe v0 IS live in block C: block C is d30-d38: `lw v1,204(a0); li v0,2; sw v0,176(v1)`. v0 set then used. v1 live to store. So in block C, the free regs at the load: $2 (v0 born after), $3, $5,$6...

The qty order: v1 (born at load, dies at store: range ~4 half-insns, 1 ref... wait refs: v1 used once (store) → qty pri low). v0: born at li, dies at store: also short, 1 ref. $2 vs $3: v0 and v1 both short. qty order by pri; if equal pri, lower qty number first (qty numbers assigned in order of birth scanning). v0's qty: born at li v0,2 which is after the load. v1's qty born at load → lower qty number. So v1 allocated first: tries $0,$1 fixed, $2 free → should give $2! But the result shows v1=$3 and v0=$2. So something made $2 unavailable for v1 at that point — probably v0 is live-in to the block? Wait, if v0 were live-in, the target's `li v0,2` would still work but v0's old value dead. Hmm, but in block C entered from two paths, v0's value at entry is the slt result, but not used → dead. Unless flow didn't remove it.

Alternatively the target/our build's block C isn't a separate block: maybe reorg/flow merged. Hmm, but our compiled mine has exactly the same insns as target except the reg, so the block structure is identical! Only the register differs: mine uses a0, target v1. So in *our* build v1 got a0 (not $2!). So $2 was used at that point in both builds. Meaning v0 IS live at the load in block C? But then target's v1 got $3 because... if v0 occupies $2 at the load, then free: $3 first → target v1=$3. But our build gave v1=$4 (a0), meaning the suggestion mechanism did record a0 and $4 was free.

So both: $2 is taken (by v0, live across? or by something), $3 is free. Our build prefers the suggestion $4 over $3. Target presumably had the pin $3, which forced v1=$3.

So: to get $3, we must kill the $4 suggestion. If $4 were not free over v1's range (i.e., a0 live after the load), the suggestion fails and normal allocation tries $3 → match!

So: make a0 live past the load with zero extra instructions. In block C: after `lw v1,204(a0)`, `li v0,2`, then store. If the store were `sw v0, 176(v1)` — what if instead we make the store's address depend on a0 too? E.g., `*(s32*)(v1 + 0xB0) = v0` where v1 = a0->unkCC. Hmm.

What if we store via a pointer that is a0-derived in a way that uses a0 again after the load? e.g., make v1 = a0->unkCC and then the store uses `((Unkstruct*)a0)` — no, the store is to v1+0xB0.

Alternatively, reorder so a0's death is after another use: In block C, if we swap the two statements: `v0 = 2; v1 = a0->unkCC;`? Then the load is last, a0 dies at it. Same.

Hmm, but what about the *other* block (B, d24): `li v0,1; lw v1,204(a0); j`. Same pattern.

What if a0 is used in BOTH blocks and the value... no, blocks are exclusive.

OK so a0's last use in each block is the load. Its liveness ends there in both.

Alternative: prevent the suggestion by making the load's destination a SUBREG or a different-sized object? E.g., declare v1 as `unsigned short`? No, the pointer is 4 bytes.

What if the loaded value's pseudo also has a *copy* suggestion that outranks the normal suggestion? The suggestion phase: `if (qty_phys_num_sugg != 0 || qty_phys_num_copy_sugg != 0) find_free_reg(..., just_try_suggested=1...)`. In find_free_reg with just_try_suggested: if copy_sugg non-empty, restrict to copy suggs. So if v1 has a copy suggestion (from a `set reg reg` where v1 is dest or source with may_save_copy), that register wins. We need that register to be $3. A copy `v1 = $3something`... but adding an insn.

Hmm, unless a copy insn is later removed by combine (as redundant) but its local-alloc suggestion... no, local-alloc runs after combine; if the insn is removed, no suggestion.

What if the copy is `v1 = a0->unkCC` in one block and `v1 = v0` somewhere? no.

Different approach: make a0 NOT a hard reg at the load by splitting the function's argument usage: the param a0 is a hard reg ($4) by definition. If we copy it into a local `p` and use p... global-alloc gives p $4 (coalesced). But if p cannot coalesce (e.g., p is live across a point where $4 is clobbered — a call! there are no calls). Or p is used in a way that requires a different class. Hmm.

What if we make TWO copies, p and q, of a0, so they can't both be $4; e.g., `void *p = a0; void *q = a0;` then use p in one branch and q in another? Each is a copy from a0; global-alloc coalesces p and q both with a0 → both $4? If they don't conflict (different blocks), both can be $4. Then the load's base is $4 again.

Hmm.

What if the load is expressed with the *pointer* variable that's global (not the param)? E.g., `Unkstruct *p = a0; ... v1 = p->unkCC;` still $4.

Let me look at how the target's source likely looked. Maybe the original source had a different structure: e.g., 

```
s32 v0;
s32 v1;
...
v0 = D_80078EB1;
if (v0 < a1) { v1 = ((...)a0)->unkCC; v0 = 2; }
else if (v0 < a2) { v0 = 1; v1 = ((...)a0)->unkCC; }
else { v1 = ...; v0 = 2; }
```
Target's block layout: bnez a1 → d30 (the common else); then slt v0; beqz v0 → d30; li v0,1; lw v1; j; then d30: lw v1; li v0,2. So indeed two sources: `if (v0 < a1) {v1=..;v0=2;} else if (v0<a2) {v0=1;v1=..;} else {v1=..;v0=2;}`.

The register choice is the pin's job in the current src, so the "real" source may not have any special spelling. The task is to find a real-C move that flips it.

Let me look at how similar pins were cracked. From moves: "func_8017E1D4 MATCH — $0 zr pin: s16 flag copies (sign-extend escapes cse...)"; not this.

Let me search moves.md for "lw" / "load" + "suggestion" / "base". Also grep for functions in this overlay (ov_SC04_018) maybe siblings cracked.

Alternatively, maybe the answer is easier: change `v1` to be loaded via a *different* expression: `v1 = *(s32 *)((char *)a0 + 0xCC);` — same.

What about making the load result go through a `u16`/`s16` temp? no.

What about making v1's live range longer by using v1 earlier in the block? e.g., set `v1 = v1;`? no.

Hmm, what if the store uses v1 and ALSO a0? e.g., `*(s32 *)(v1 + 0xB0) = v0;` where v1 came from a0... What if we write `((Unkstruct*)v1)->unkB0 = v0;` — same.

Think about the suggestion source again. Actually maybe the suggestion comes not from the address but from a copy insn that combine left: In block B: `li v0,1` then `lw v1,204(a0)` — no copy. Hmm, but in block B there's a `j d38` with delay `nop`; target has `j` then `nop` (d28: j; d2c: nop). In our build same.

Let me actually look at the dumps to see. Use cc1 dumps of the current build? The tools: tools/cc1_dumps_tu.sh and alloc_table.py. The brief says use dumps when unsure. Let me get a dump for this TU and look at the .lreg/.greg or local-alloc output.

Actually simpler: let me just try a batch of candidates empirically. Candidates:
- w2: `void *p = a0;` use p for loads and stores.
- w3: hoist load before if (single load) — will change structure, likely bad.
- w4: use `((Unkstruct_80184B70 *)a0)->unkCC` assigned to `u32 v1`.
- w5: split v1 per branch (v1a, v1b, v1c) — three different temps! Then each has its own qty; the store uses... need one v1 at the end. Hmm, could do: in each branch set `v1` from a local temp? e.g., `s32 t; t = a0->unkCC; v1 = t;` — combine merges.
- w6: make the else arm compute `v1 = a0->unkCC` then `v0 = 2` (already).
- w7: store `*(s32 *)(v1 + 0xB0) = v0` → `*(s32 *)((char*)v1 + 0xB0)` same.

Another idea: give v1 a REG_UNUSED/extra use in the *other* blocks so its live range spans blocks? If v1 were live across blocks, local-alloc wouldn't handle it (it'd be global), and then global-alloc gives registers differently! That's promising: if v1 is assigned in one block and used in another, it's not block-local → global-alloc. In the target, v1 is block-local (each branch loads and the store is in a merged block? wait, the store block d38 is shared: both paths jump/fall to d38). v1 is live from d24 (block B) into d38 (block C?) Hmm! The store at d38 is in a separate block reached by the jump from d24 and by fall-through from d34. So v1 IS live across blocks (B → store block). So v1 is global? But global-alloc then local-alloc... The current pin forces $3 globally.

Interesting: v1 is live from block B into the join block. That means v1 is a global pseudo; global-alloc assigns it. Then why does our lever-free version give a0? Global-alloc's priority/coalescing. Hmm, but the observed a0 could be global-alloc's choice (not local-alloc). Global-alloc has copy preferences and prefers call-clobbered regs for short-lived values; the alloc order in global-alloc for non-call-crossing pseudos is $2,$3,$4...

Hmm wait, but the score diff shows 3 register mismatches: two loads (a0 vs v1) and the store. That's v1 = $4 in both blocks and the join. If global-alloc chose $4, it's because $4 (a0) is free after the load, and global-alloc prefers... global-alloc allocates in order of priority; `reg_alloc_order` for local? In global-alloc.c, `allocno_order` sorts by `floor_log2(n_refs)*n_refs*size/live_length`, and for each it calls `find_reg` which tries `reg_alloc_order` starting from... For call-clobbered pseudos it starts at $2? And it also has copy preferences: `allocno_copy_cost`/`register_preference`. The key: a0 dies at the load, so $4 is free over v1's range; $3 is also free. Why $4 over $3? Because $2, $3 might be taken by v0 (which is live in the join block too, used at the store!). Indeed v0 is live from each branch into the store block → global pseudo too. So both v0 and v1 are global; global-alloc assigns them; v0 gets $2, v1 gets... $3 or $4. Our build gives $4. The priority order might give v1 first (higher priority) and it takes $4? Why would it prefer $4? Hmm.

Let me look at global-alloc.c's find_reg/order. Actually maybe easier: use the dump tools to see which pass changed it. But the difference is only register choice; a dump comparison (mine vs target) would show the .lreg/.greg.

Let me check alloc_table.py and cc1_dumps_tu.sh usage. Actually, the brief gives: tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps). Let me see their help.
