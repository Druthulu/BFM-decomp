---
ts: 2026-11-06T18:13:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0TH50aloXoFzbpTNBvXa
---
Score 3, same instruction count; just the register: a0 vs v1 ($3). The unkCC load lands in a0 (the argument register) because it's the dying a0 base — local-alloc copy preference ties to a0 (lreg-copy-pref-dying-base!). That's the WALL tag in moves: "func_80183E68 WALL lreg-copy-pref-dying-base — local-alloc ties `rv=(s32)a0` to the dying a0, so the target's `move v0,s0` disappears".

Here `v1 = a0->unkCC` — a0 dies after this load (in each branch), so local-alloc gives the load result a0. Target uses $3 (v1).

How to move it? If a0 is used after the load, it can't be reused. Options: make a0 live past the load by a real use... but no extra insns allowed. Hmm.

Wait, the three loads: in the merged else block, `lw v1,204(a0)` then `li v0,2`. a0 dead after. So local-alloc reuses a0.

What real-C moves can make the load land in $3? 
- Use a temp that's live longer / has more refs (qty priority). 
- Declare v1 as a different type? No.
- Make the pointer expression use a separate base temp that's live... adds insns.
- Split: compute `v1` earlier in a way that extends its live range: e.g., set v1 = 0 before the branch? That'd add an insn (li v1,0 might be optimized away as dead? no, it's overwritten in all paths; dead store deleted).

Hmm, what determines register choice here: local-alloc gives registers to pseudos in order of qty (refs/live length). v0 (the compare result) and v1 (the loaded pointer). The load result v1 is born at the load; a0's hard reg is free after. local-alloc's copy preference: when a pseudo is the destination of a copy from a dying hard reg? No — here it's a load, not a copy. Hmm, but the load `lw a0,204(a0)` uses a0 as base and dest. Local-alloc has "REG_LIVE_LENGTH" and prefers... Actually it's not a copy preference; it's that a0 is not live after, so qty: local-alloc assigns regs and can use a0 since it's dead (local-alloc knows hard regs' live ranges; a0 is a fixed hard reg with liveness from the function entry/use).

Wait — a0 is a function argument, live from entry. Its last use is the load. local-alloc: for each pseudo, `local_alloc` finds `reg_alloc_order`... In local-alloc, it allocates registers to pseudos in qty order, and a pseudo can be allocated a hard reg that's not live during its range. Since a0 dies at the load (the load's dest is born at same insn), a0 is free for the result.

To prevent: make a0 live after the load with a real use that costs no insn. Hmm: the final store `*(s32*)(v1+0xB0) = v0` uses v1, not a0.

Alternative: use the loaded pointer via a different variable/expression so that the load dest is not the same value... no.

What if we keep the two branch loads but reference a0 after? Actually a0's value is the struct pointer; target doesn't keep it.

Idea from the moves: func_800CD57C MATCH — "store subtract direct to unkA (no v0 var hop): fld load wins v0 in local-alloc". Not quite.

func_8017E594 WALL lreg-qty-priority. func_8017E6EC WALL lreg-v0-local-first: "split reused `t` per value (t1..t5) + load/add split".

Hmm, what about making v1 live from earlier (longer live range → different priority)? local-alloc gives hard regs based on qty = refs*... Actually in local-alloc, for each block it considers pseudos that die within the block, in order of `qty` (refs / live_length). If v1 has a longer live range (born earlier), its qty might drop (qty = floor(10000*refs/live_length)). But a0 being dead is the key: the result gets a0 because it's free. Longer life doesn't stop a0 from being free... local-alloc tries to allocate; it has `reg_alloc_order` and prefers... hmm.

Actually local-alloc's behavior: it computes for each pseudo the set of hard regs that are not live over its range (`qty` order), and allocates. a0 is a hard reg that is live from entry until the last use (the load). The load's result is born at the load insn. In local-alloc, live ranges are per-block with insn numbers: a0 live from block start to the load insn; v1 pseudo live from the load insn to the store. They overlap at the load insn? The load both uses a0 and defines v1 at the same insn. Local-alloc treats "live at insn i" as including the insn. So a0 and v1 would conflict at the load insn... but GCC still allocated a0 to v1! That's the known "copy preference" / REG_DEAD: when the load has a REG_DEAD note for a0, local-alloc's `reg_is_born`... Hmm, in local-alloc, `update_equiv_regs` or the `qty` computation with deaths: "if a pseudo is born at an insn where a hard reg dies, prefer that hard reg". That's `local-alloc.c` "birth" logic? Actually it's `global.c`? No, local-alloc has code in `block_alloc`:

```
/* ... if a register is born where another dies, try to use the dying register ... */
```
There's `reg_deaths` and the "birth_death" handling. Let me check local-alloc.c in the reference.

Practical: how did other functions crack lreg-copy-pref-dying-base? From moves: "func_800CD57C MATCH — store subtract direct to unkA (no v0 var hop): fld load wins v0 in local-alloc (W03)". Hmm.

Let me look at the reference local-alloc.c for the mechanism: "copy preference" — a pseudo that is the dest of a `set (reg) (reg)` gets preference for the source reg if the source dies. Here it's a load, not a copy. But the mechanism might be `reg_preferred_class`? No.

Actually, this could be `local-alloc.c: find_free_reg` with `qty` and "insn is a load from memory based on a dying reg" — I recall `local-alloc.c` has:

```
/* If we have a pseudo that is used only in one place, and it is
   set from a hard register that dies, we can... */
```

Let me just read the relevant part of local-alloc.c. But first, maybe easier experiments:

Experiment: give v1 more refs (qty). E.g., make the load `v1 = ((...)a0)->unkCC;` in each branch and additionally... can't add refs without changing insns.

Experiment: change the type of v1 to `void *` vs `s32`? The load is `lw` of a 4-byte field either way. The store `*(s32*)(v1+0xB0)`. Could declare v1 as `Unkstruct*` and store via `->unkB0`? Then the load is from `a0->unkCC` where unkCC type matters. Hmm, but the register allocation likely unchanged.

Experiment: use `u32 v1` — same.

Experiment: split the load: `v1 = (s32)((Unkstruct*)a0)->unkCC;`? same.

What about making v0 not die? In target, v0 is the compare value; at the load point (d24/d30), v0 is... At d30 block: lw v1,204(a0); li v0,2. v0 is dead before (it was the slt result? no: in block d1c-... v0 = slt result used at d1c beqz; then li v0,1 at d20 in the taken path). So v0 gets re-set.

Alternatively, make a0 a local copy: `void *p = a0;` then use p. That adds a move ($4 to another reg) — target has no such move... unless combine coalesces it. Since a0 is used 3 times (the compare? no—a0 only used in the loads and stores). Hmm, a0 is used in: two loads (in two blocks) and the store. Wait target: `lw v1,204(a0)` twice (in two separate blocks d24 and d30), then `sw v0,176(v1)`. So a0 is used in 3 places.

If I introduce `void *p = a0;` at the top and use p, gcc would coalesce p with a0 (no move) and then... p is a pseudo that dies at its last use (same as a0) — local-alloc might allocate p to a0 and then the load result to $3? Not necessarily; the same birth-death at the load applies: p dies at the load, result born there → reuses p's reg, whatever it is. If p got a different hard reg than a0... but global-alloc would give p a0 (arg copy coalescing, since p=a0 copy is coalesced by global-alloc's copy preference). Hmm.

Another idea: make the load's base die EARLIER than the load? Impossible.

What about preventing the reuse by having the load result conflict: the target's `lw v1,204(a0)` — after it, a0 is dead. If we add a real use of a0 after the load in the same block... but the only insn after is `li v0,2` and the store. In the fall-through block d24: lw v1,204(a0); j; nop. Hmm.

Wait, maybe the answer is different: the target's registers are v1=$3 for the pointer, v0=$2 for the result. If the load result goes to a0, then the store is `sw v0,176(a0)`. Score 3, only register naming. Could I influence by making the result used in a way that requires $3? No.

Look at the exact mechanism in local-alloc.c 2.7.2. Let me grep the source for "birth" or "dying".

Let me do that: grep local-alloc.c for "dies" / "birth".
