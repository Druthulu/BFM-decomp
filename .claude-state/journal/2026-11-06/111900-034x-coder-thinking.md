---
ts: 2026-11-06T18:19:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XMz6u7P8sZKgXyIhuf3q
---
So the preference "4" on allocno 76 comes from a SET whose SRC is a hard reg (a0 = pseudo 4? no, hard reg 4) and dest is pseudo 76: `(set (reg 76) (mem (plus (reg 4 a0) 204)))`? But set_preference takes SET_SRC (setter) = the mem, and `GET_RTX_FORMAT (GET_CODE (src))[0]` for MEM is 'e' (first element is the address expression) → src = XEXP(mem,0) = (plus ...), copy=0. Then GET_CODE(plus) is not REG/SUBREG → return. Hmm, that returns.

Wait, maybe the preference is recorded from another SET: `(set (reg 76) (reg 4 a0))`? That would be a copy. Hmm, the greg dump showed insns like `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` — after renumbering. Before renumbering it'd be `(set (reg/v:SI 76) (mem (plus (reg/v:SI 4 a0) 204)))`. set_preference(76, mem) → src = plus → not REG → return. So where's preference 4?

Hmm, `GET_RTX_FORMAT (MEM)[0]` is 'e'? For MEM, format is "ei" (address, alias set). So yes 'e', src = XEXP = address. If the address is a REG directly (not plus), e.g., `(mem:SI (reg 4))`? No, there's an offset.

Wait — maybe the preference comes from the store `(set (mem:SI (plus (reg 76) 176)) (reg 75))`: set_preference(dest=mem, src=reg 75). dest is MEM → not REG → return.

Hmm. Let me look for insns where a pseudo is set from a0 directly. Actually the three loads in the dump: insn 32, 40, 53 all `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` — this is after renumbering: both the dest and the base are $4. But the allocno table says 72 in 4 and 76 in 4; there are 3 loads. Let me see the pre-renumber RTL in the .lreg dump (local-alloc runs after global-alloc? no: global-alloc then local-alloc. .lreg is local-alloc's output; .greg is global's output with renumbering).

Hmm, actually the RTL printed in .greg is renumbered (as dispositions show). The three loads: two are in blocks with allocnos 72/76, the third is a block-local pseudo (78/79?) assigned locally later... The loads at insns 32 (block?), 40, 53. The renumbered dump shows all dest = $4, base = $4. And the store at insn 61: `(set (mem (plus (reg/v:SI 4 a0) 176)) (reg/v:SI 2 v0))` — store to $4+176.

So in the lever-free build all three loads land in a0, and the store uses a0. That matches score 3.

Now: how to get the *global* allocno (the one live into the join) to prefer $3 instead of $4? The preference is "4" (a0). If we remove the preference, the order 75 76 72 74 means: 75 → $2; 76 → next free $3? Wait, but $3 is free at that point and the target wants 76 in $3. Then 72 → would get $4 (preference) or next free $4. Hmm, but then which pseudo becomes the merged block's load? After jump2 merges, only 2 loads remain: one in the branch block and one in the merged else. Both need $3 in the target (target d24 and d30 both lw v1). Hmm, target has both loads in v1 ($3). But the pre-reload has 3 loads: 72 (fall-through branch), 76 (else), and a third (block-local 78/79).

Hold on, the target's two loads are in two different blocks, and both use $3. If 72 and 76 are two global allocnos (different blocks, no conflict), both could get $3! Since they don't conflict, the same hard reg is fine. So we need 72 and 76 both in $3, and the third (block-local) load also in $3.

In the current build: 72→$4, 76→$4, block-local 78→$5? (disposition 78 in 5, 79 in 2). Hmm, 78 in 5 = a1, 79 in 2 = v0. But wait, those are per-block local allocnos from the .lreg of... confusing.

Actually, let me look at the .lreg dump to see the final local allocation. The .lreg dump (local-alloc output) shows the RTL with all hard regs. Our build: loads all $4. Target: $3.

OK so the key: kill the a0 preference for allocno 76 (and 72). Where does the preference come from? Let me search the .greg RTL before renumbering... Actually the .greg dump shows after renumbering. Hmm, but preferences were computed from the pre-renumbered RTL.

Wait: set_preference is called from mark_reg_store with the SET_SRC. For `(set (reg 76) (mem (plus (reg 4) 204)))`: src = mem → GET_RTX_FORMAT(MEM)[0] = 'e' → src = XEXP = (plus (reg4) 204) → not REG → return. So no preference.

Unless the load is expressed as `(set (reg 76) (reg 4 a0))` — a copy! Maybe combine split the load? No...

Hmm, let me reconsider: maybe r76 is not the load result. Let me look at the full greg RTL pre-renumbering. Is there a dump before global? .rtl (the initial RTL dump) — let me look at the .rtl or .lreg? Actually .greg shows the function after global_alloc with pseudos renumbered. The pre-allocation RTL is in .rtl (dump at expand). Let me check the .rtl dump for the function to see the pseudo structure. Also .combine/.cse.

Let me grep the .rtl dump for func_80184B70 and view it.
