---
ts: 2026-10-17T16:10:39.477Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm puzzling over why the target reloads D_801BFCDC after each store while mine doesn't—since stores write u16 but the variable is s32, I wonder if the compiler's lack of strict aliasing in this gcc version means CSE could still consider the s32 load valid even after a HImode store overlapping that memory.

The key difference might be struct-flag aliasing: gcc 2.x treats accesses through a known struct pointer (MEM_IN_STRUCT_P) as unable to conflict with a scalar fixed-address memory reference, so if the original C code stores via a raw pointer cast like `*(u16*)(work + 0xE) = ...` rather than through the struct field, that non-struct access would correctly trigger a reload. This points me toward checking the actual field offsets and types in Unkstruct (fields at 0xE, 0xA, 0x6) to see whether the real source used direct pointer arithmetic instead of struct member access.
