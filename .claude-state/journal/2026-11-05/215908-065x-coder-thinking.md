---
ts: 2026-11-06T04:59:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mxzVA7k8RvO5ienbDdJx
---
In cse1 (a1), insn 64 already forwarded: `(set (reg:SI 4 a0) (reg/v:SI 76))`. And insn 57 is a real load. Why is insn 57 not forwarded but insn 64 is?

Because cse1 processes blocks: after jump_insn 53, it starts a new block (label 70? actually the fall-through). The load at 57 loads D_80127524; the table at that point has (mem D_80127524) -> 76 from insn 50? If it did, insn 57 would be forwarded. So it wasn't in the table — maybe the table was cleared at the jump/branch boundary. Then insn 57's load records (mem D_80127524) -> reg 84 in the table. Then insn 61 stores through reg 84+26: varying address, PLUS, HI → nonscalar only, so the scalar entry (mem D_80127524)->84 survives. Then insn 64 loads D_80127524 → forwarded to... reg 84? But the dump says reg 76. Hmm, reg 76 is the stored value, not 84.

Wait, maybe the address folding: insn 57's load address is `(symbol_ref D_80127524)` — cse folds reg 75 to the symbol. And the table entry from insn 50 (mem (reg/v 75)) may have been canonicalized to (mem (symbol_ref D_80127524)) -> 76, surviving the branch because cse follows... Actually cse1's cse_basic_block can follow the conditional jump's fall-through and target if `flag_cse_follow_jumps`? Or cse_skip_blocks. The table may persist across the jump into the fall-through block if the jump is a "simple" one? There's code in cse_basic_block that handles following jumps.

Anyway, the forwarding to 76 happens. The load at 57 was not forwarded, maybe because the table entry was invalidated at the jump for the *first* block, then re-established? Confusing. But the key: insn 57's load creates an entry -> 84, then insn 61's store doesn't kill scalar entries, then insn 64 loads and gets... 76? That means the table still had (mem D_80127524) -> 76 and lookup returned 76 (the canonical/first entry), not 84. Possibly because insn 57's load also has a REG_EQUAL note? Hmm, or cse chose 76 as the equivalent with lower cost.

Regardless: to make insn 64 a real load, we need the memory entry gone. Since insn 61's store is HI+PLUS (nonscalar only), it doesn't kill it.

What if we make the sh store QImode? Can't — target is sh (HI).

What if we add a real store of a *different* kind between insn 61 and the call that cse treats as all=1, but which doesn't emit an instruction in the target? We could add a store that flow/combine deletes. The only deletable stores are: (a) register stores to dead regs (no memory invalidation), (b) MEM stores to the same location as a later MEM store (last_mem_set).

Idea (b): add TWO stores to the same location, where the first has a varying QImode address... but then the second store to the same location would survive (emitting an instruction). Unless the second store is the existing `sh`? No, different location.

Wait, actually, maybe we can make the *dead* store be one that cse sees and flow deletes because a *later* store to the same location exists, and the later store is something already in the target! Is there a later store to the same address? The target's sh is `*(s16*)(D_80127524+0x1A) = 1`. If we add a first store to the same location that cse considers all=1... but a store to the same location is fixed (symbol+const) unless written via a varying pointer. If we write the same location through a varying pointer: `s16 *r = (s16 *)(D_80127524 + 0x1A); *r = 0; *(s16 *)(D_80127524 + 0x1A) = 1;` — the first store's address is (reg r), a bare register → all=1! And the second store is to the fixed location. flow's last_mem_set: rtx_equal_p of the two MEMs? The first is (mem:HI (reg r)), the second (mem:HI (plus (reg D_80127524value) 26)) — not equal, so not deleted. Hmm.

Alternatively, make the first store use the same address expression as the second but through a QImode cast? `*(u8 *)(D_80127524 + 0x1A) = 0;` — addr PLUS, mode QI → all=1! Then the second store `*(s16 *)(D_80127524 + 0x1A) = 1;` — different MEM (QI vs HI), so last_mem_set won't match (rtx_equal_p includes mode). So the QI store survives → extra instruction.

Unless the QI store is to a location that the HI store overwrites, and flow can prove dead? insn_dead_p only checks rtx_equal_p, not overlap. So no.

Hmm, but combine runs after flow. If the QI store and HI store are adjacent, combine might merge? Unlikely.

What if the dead store is to the *same* MEM but a different expression that cse sees as varying? We need rtx_equal_p with the later store's MEM. rtx_equal_p on MEMs compares the address rtx. If both use the same register expression, they'd be equal and the first deleted. But then both have the same address form: if the address is a bare register (varying, all=1), both stores are (mem:HI (reg r)) — the first is deleted by flow, the second survives. But the target's store address is plus reg 26, not bare reg. We could compute r = value+26 as a pointer and store through it: `s16 *r = (s16 *)(D_80127524 + 0x1A); *r = 0; *r = 1;` — combine/flow would delete the first store (*r=0), and the surviving store is `sh 1, 0(r)` — offset 0 from r, but r = value+26; the instruction would be `sh ...,26(reg)` only if the compiler folds the constant into the addressing mode (it does: r is a pseudo = reg+26, and the store uses (reg + 0); after allocation it's `sh ...,26(v1)`? The pseudo r would be computed by addiu then used with offset 0 → `addiu v1, value, 26; sh 1,0(v1)` — extra addiu, not matching target `sh 1,26(v1)`.

Hmm. Unless combine folds the addiu into the store's address. In target, the address is `plus(reg, 26)` directly. If we write `*(s16 *)(D_80127524 + 0x1A) = 1;` the RTL address is plus(reg, 26) — no addiu. Good.

So we want the dead store to have the exact same MEM rtx as the sh: (mem:HI (plus (reg X) 26)). rtx_equal_p requires the same register. Two stores to the same address, first dead → flow deletes the first. And for cse, the address is PLUS with HI → NOT all=1 (nonscalar only). So that doesn't invalidate scalars. Damn.

The exemption: `! ((MEM_IN_STRUCT_P (written) || GET_CODE (addr) == PLUS) && GET_MODE (written) != QImode)`. For HI+PLUS, exemption applies → not all. For QI+PLUS, all=1. For any mode with non-PLUS addr, all=1.

So to get all=1 with a store that flow deletes, we need either QI+PLUS (mode differs from the HI target store, so rtx_equal_p fails) or non-PLUS address (bare reg; if the target store also used a bare reg with the same register and HI mode, rtx_equal_p holds and the first is deleted).

Option: make BOTH the dead store and the target sh use a bare-register address that is `value+26` computed by addiu. Then target would have an extra addiu... unless the address is formed by a register that already holds value+26? No.

Hmm, wait: what if the dead store uses the SAME address register but QI mode, and the target sh is HI — different MEM, not deleted.

What about the "last_mem_set" mechanism: maybe it's more general — let me read propagate_block's dead-store handling. It may delete a store if a later store to an *overlapping* location exists? Let me read around line 1208-1350.
