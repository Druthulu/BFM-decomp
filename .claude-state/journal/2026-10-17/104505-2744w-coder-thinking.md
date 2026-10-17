---
ts: 2026-10-17T16:45:05.757Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
It's 10:44, so I have about 13 minutes left on this item. All three cases share the same mechanism: a call argument constant address gets reused after the call from a callee-saved copy, which points to CSE. I'm wondering if there's a lever-free fix—maybe making the first use's pseudo die before CSE can propagate it, since the target recomputes the symbol after the call, and in gcc 2.x CSE does keep equivalences across CALL_INSN for pseudos.

I'm also considering how the original code without asm would have produced the recomputation—perhaps the first call's argument was a different expression type, like an array element or a struct member that folds to the same symbol. Looking at the disassembly, the second use computes the address as symbol plus an offset, while the target recomputes the symbol into a register after the call and stores a byte there; this suggests CSE replaced the post-call symbol reference with the cheaper equivalent pseudo copy based on gcc 2.x's cost model where a register copy is cheaper than re-materializing a symbol_ref.

I'm also wondering whether m's pseudo would have been invalidated in CSE's table by a reassignment between the call and the later store—like if m gets reused for a different purpose in the source code before being read again, though that reuse would need to come after the point where the symbol is actually needed for the store.

Actually, maybe the discrepancy isn't about reassignment at all, but about how the address literal is written in the source—if the symbol address is spelled as a raw integer constant like `0x80075FC0` instead of referencing the `D_80075FC0` symbol directly, that could affect how CSE treats the expression, since the relocation still needs a symbol reference for the linker.

I'll accept the partial result for this item since I've cracked both barriers, keeping track of which "launders" survive, and compute the best lever-free baseline by subtracting the three laundering transformations from the original score.
