---
ts: 2026-10-17T16:13:59.671Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm wondering why cse doesn't treat the store through a varying address as conflicting with the fixed scalar access, since memrefs_conflict_p should flag a symbol-vs-reg+const comparison as unresolvable and thus a conflict—unless gcc's logic here works differently than I'd expect.

Actually, I think I found it: cse's note_mem_written treats a store whose address is a PLUS (reg+const) as an array-element access, which doesn't invalidate scalar variables unless the mode is QImode. So the aliasing escape only applies if the store's address is a plain register rather than reg+offset — meaning something like `u16 *p = &work->unkE;` with a bare pointer dereference would behave differently than reg+const addressing.

But that raises a question: wouldn't cse canonicalize p's address back into a PLUS form once it knows p equals work+14, folding it before note_mem_written records the write? That would still count as PLUS. So maybe the target's store used an address cse genuinely couldn't express as PLUS — perhaps offset-zero access to work itself, or the relevant loads of D_801BFCDC weren't from a fixed address at all.

I'm also reconsidering whether the load happened in a separate extended basic block, or whether something invalidated cse's cached value between the rand call and the load — though no calls intervene there. Maybe the real difference is in how D_801BFCDC's field access was structured in source, something I can't change since the type is fixed.

I'm wondering if a held pointer across calls could explain things, but the target's offset-based addressing rules that out, and struct field stores stay in-mode (sh for HImode, not sb). So I'm considering whether cse fails to match the second load because it's accessed through a differently-shaped MEM rtx or a different pointer cast, even though the underlying mode is still the same SImode.

Through a pointer, the memory address isn't fixed, and cse hashes by the original rtx anyway, so this case feels borderline rather than clear-cut. I'll just try it and see what happens with a real pointer variable.
