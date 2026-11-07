---
ts: 2026-11-06T07:28:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Fu1XDGsxkujWTSgDwdDI
---
Not present in the partial reference. In GCC 2.7.2, MIPS REG_ALLOC_ORDER is defined in mips.h (from the real toolchain, not in our reference dir). Typically for mips:
```
#define REG_ALLOC_ORDER { 4, 5, 6, 7, 8, 9, ... }
```
Hmm. Actually for the target, the allocator picks v1 before a0 for the first load, meaning reg_alloc_order starts with... v1? Or v1 was copy-suggested (tied to the store? no).

Let's look: first group load `lw v1,52(v0)` — 52(v0) is the source struct's first field. Why v1? In mine, first load also v1. So same. Second load: target a1, mine a0. So after v1, the next free reg in target is a1, mine a0. So a0 is used in target but not mine. Confirmed.

So a0 is genuinely reserved in target during the block. Let me find which value. In the if-block, `li a0,75` sets id. Suppose global-alloc assigned `id` to a0 and the live range of id spans... Let's check: if `id` were live across the copy block, it'd need a def before. It has no def before. So no.

Another candidate: the function's incoming arg0 pseudo might still be live because the `move s0,a0` doesn't kill it if there's a later use of arg0 in the if-block (e.g., `func_80146A6C(id, s1, ...)` uses s1 not arg0). Hmm.

WAIT. Maybe the original source's if-block uses `s0` but the *declaration* is `s32 s0 = arg0;` and the compiler's `move s0,a0` is placed at insn 2, but arg0 pseudo remains live until... the copy is a coalesced move where arg0's pseudo IS s0. Let me instead consider that the target has an extra live pseudo in a0: `v0`? No, $2.

Let me get more evidence: compile a variant where I add a dummy real use of a0 and see if the copies shift. E.g., pass arg0 to func_800CAF84? Can't change signature.

Alternative: maybe the original C had `s32 s0 = arg0;` plus `s32 id;` and the if was written as:
```
if (--((Unkstruct*)s0)->unk1C == -1) {
```
The pre-decrement. Target: `lw v0,28(s0); li v1,-1; addiu v0,v0,-1; bne v0,v1; sw v0,28(s0)`. Yes.

Hmm, what about the two struct copies: maybe the original used a `Struct16` local:
```
Struct16 tmp = *(Struct16*)(v0+0x34);
*(Struct16*)(s0+0x38) = tmp;
Struct16 tmp2 = *(Struct16*)(v0+0x44);
*(Struct16*)(s0+0x48) = tmp2;
```
That would put the 4 loads and 4 stores differently: 16-byte struct copy loads into 4 regs, stores. Same.

Let me test: the a0 reservation could come from `s1` if s1 were allocated to a0 in the first block... but s1 is used in the if-block across the call, so callee-saved. Unless the original recomputed s1 after the call: `s1 = ((Unkstruct*)s0)->unk34;` both before and after? No.

Let me try the "use arg0 in the if-block" variant. If arg0 is live across the call, global-alloc gives it a callee-saved reg. It might give arg0 $16 and s0... hmm, they're the same value.

Let me look at the P36 pack mechanism.md if exists. Search for the pack dir.
