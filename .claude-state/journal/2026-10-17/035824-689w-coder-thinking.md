---
ts: 2026-10-17T09:58:24.957Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6749d345bbfe00cf
model: claude-opus-5-5[1m]
effort: medium
turnId: c3f78c69-d425-4e5c-8c54-1a89f13910d6
---
I'm noticing a type conflict: D_801A6B40 is declared as a scalar extern elsewhere but the draft treats it as an array, and even a block-scope extern redeclaration would clash with the file-scope type, so I need another way to reconcile this.

I'm also considering using a cast macro that reinterprets the symbol as a struct array pointer, checking whether that indexing produces the same memory expression and MEM_IN_STRUCT flag as a true array access — likely identical, but worth verifying by testing a modified draft before integrating.

Separately, D_800B9A02 has conflicting short vs unsigned short declarations across files, so I'm resolving the load instruction mismatch (lh vs lhu) with an explicit cast, and confirming func_8017E26C's existing definition should keep the `(void)` parameter to match the draft.

Now I'm settling on using a local `#define` macro to alias the symbol as a typed struct pointer for the repeated indexed accesses, undefining it after the function, and checking that the translation unit already includes the headers needed for MATRIX/SVECTOR types.

Found conflicting declarations in ov_SC04_016: D_801A6B40 is a scalar `s32` accessed via a locally scoped cast-pointer macro to preserve indexed struct-field access, while D_800B9A02 is `short` and uses `*(u16 *)&` to match the draft's lhu instruction.
