---
ts: 2026-11-06T16:46:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iB4IQM65xexMJGqeqiYQ
---
m02's first block:
- v1 = unk70 (lh v1,112)
- v1 *= 2
- at = D_8019C7D4 + v1
- v1 = lhu 0(at)      ; v1 = the loaded value
- v0 = lhu 48(a1)     ; v0 = the field
- v0 = v0 + v1
- sll v1,v1,0x10      ; test
- bgez v1
- sh v0,48(a1)

Target:
- v0 = unk70
- v0 *= 2
- at = D_8019C7D4 + v0
- v0 = lhu 0(at)
- v1 = lhu 48(a1)
- v1 = v1 + v0
- sll v0,v0,0x10
- bgez v0
- sh v1,48(a1)

So mine swaps the roles: the *loaded* value goes to v1 (source v0!) and the field goes to v0 (source v1). Wait: in m02, `v0` (the source local) ended up in $v1 and `v1` (source) in $v0. That's the rotation. The source code is unchanged in structure; only the register assignment differs.

So the allocation: source v0 → $v1, source v1 → $v0. Why? Because local-alloc's priority: v1 has more refs? In the source, v0 is assigned many times (reused as a temp) and v1 is also reused. Let me count:

v0 sets: ~7; v1 sets: ~5. a0r: 2. a1: 1 (set at top). at: ~6.

Hmm, in the target v0→$2 and v1→$3. local-alloc's `allocno_compare`: priority = (refs*... )/live_length? Actually `floor_log2(refs) * ...`. The exact rule (local-alloc.c:1486-1507 per C0505): "A block with exactly THREE quantities is allocated in BIRTH order". Hmm.

Let me look at local-alloc.c allocno_compare and the block allocation. Maybe I can use tools/localalloc_sim.py to model the candidate? It's designed for the original TU.

Alternative pragmatic approach: try source-level changes that alter the ref counts/order and see if the assignment flips:
- Split v0's uses: e.g., use a different local for the second branch's temp.
- Merge v1 into v0? 
- Reorder statements so the birth order changes.

The target's first-block order is: v0(unk70), a1(unk20), then v1(field)... In mine the sched order is different but the allocation is the issue.

Let me try: make `v1` an `s16`? No, v1 holds u16 sums and comparisons; target uses sra 16 on v1, so v1 is s32.

What about the `pad[4]` local — it's declared but unused (it was for the frame). Removing it? It's dead. The frame is 40 bytes: 16 args + 8 ra/s0 + ... The pad might be needed. Let me check: frame 40 = 0x28. `sw ra,36(sp); sw s0,32(sp)` → 8 bytes saved regs; args at 16..? The stack args region is 16 bytes (0x10-0x1f)? Actually O32: 16 bytes of outgoing args. So 16+8+? = 40 → 16 bytes for locals? pad[4] = 16 bytes. So pad is the outgoing-arg area? Removing pad may change the frame. Keep it.

Let me try a big batch of source-level regalloc dials:
- n01: move `s32 v0;` to be the first declaration.
- n02: `s32 v0;` after `s32 at;`.
- n03: declare v0 inside the first block `{ s32 v0; ... }` — scope change (C0087: allocno class).
- n04: rename v1→w, v0→t (no effect, skip).
- n05: make `a1` a typed pointer.
- n06: `s32 a1;` → `Unkstruct_800B5CB8 *a1;` and cast at uses.
- n07: use `s0` as the pointer (drop a1) — but a1 is s0+0x20 (the struct). Hmm, a1 = CAST_SIGN(u32,s0,0x20) = s0 + 0x20? Actually `CAST_SIGN(u32, s0, 0x20)` extracts bits 0x20..? That's the `lw a1,32(s0)` — so a1 = *(s32*)(s0+0x20). It's a loaded pointer.
- n08: merge the `v0 = v0 * 2` into the index expression: `at = (s32)D_8019C7D4 + v0 * 2;` — C0505 "a load split from its update".
- n09: `at = (s32)D_8019C7D4 + ((Unk*)s0)->unk70 * 2; v0 = *(u16*)at;` — uses v0 fewer times (v0 gets fewer refs).
- n10: `v1 = CAST_WIDTH(u16,a1,0x30) + v0;` single statement instead of two.
- n11: `CAST_WIDTH(u16,a1,0x30) += v0;` compound.

Let me test n08-n11 and the decl-order ones. These change ref counts of v0/v1, which steers local-alloc.

Actually, a promising one: `v1 = CAST_WIDTH(u16, a1, 0x30); v1 = v1 + v0;` → `v1 = CAST_WIDTH(u16,a1,0x30) + v0;` reduces v1's sets from 2 to 1. That changes priority.

Let me run a batch.
