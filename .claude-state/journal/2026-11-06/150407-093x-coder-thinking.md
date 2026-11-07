---
ts: 2026-11-06T22:04:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HE5WJHmDvoIqTrBAHg3u
---
Twin identical results: best 24 (u06/u13), same as item 2. Confirms the twins.

Now record items 2 and 4 as WALL best 24, tries ~56 each.

Wait — before walling both, let me reconsider one more possible crack for the tmp/dst: the `dst` s16 trick fixes the dst bank but breaks the load width. What if the *load* is written to force `lw` while dst is s16? E.g.:

```
dst = *(s32 *)(arg0 + 0xD0);
```
compiler narrows to lh. What if we make the *use* require the full 32 bits: e.g., compute `*(u16 *)(dst + 0xFC)` — the address dst+0xFC with s16 dst is computed as sign-extended 16-bit; the compiler knows the range. To force full width, use `((s32)dst)` in the address: `*(u16 *)((s32)dst + 0xFC)` — s32 cast of s16 → sign-extend (no extra insn since lh already sign-extends) — same as now.

What if we load a *u16* and then use it as an unsigned pointer? `u16 dst` + `(u32)dst + N` → lhu then zero-extend... lhu already zero-extends. The target uses lw. Still lhu.

What if dst is s16 but we write `dst = *(s32*)(arg0+0xD0) >> 16;`? No, wrong value.

To get `lw` with a 16-bit variable, the compiler would have to keep the full 32-bit value somewhere. Only if the high bits are used. We could add a *dead* use of the high bits that flow deletes... but flow runs before local-alloc, so a dead use would be removed before allocation. Hmm — flow runs before combine/sched1, and local-alloc after sched1. So dead code is gone before allocation. Unless the dead use survives flow (e.g., a store to a global that's never read — flow doesn't delete stores). A dead store `D_xxx = dst;` would survive and add an instruction. No.

What about a use of the full value in a *comparison* that's provably true? jump/flow would fold it.

So no.

One more idea: keep dst s32 and change the *number of temporaries* in the dst block so the allocation shifts. E.g., replace `*(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10)` with an explicit temp for the first load:
```
u16 a = *(u16 *)(dst + 0xFC);
*(u16 *)(*(s32 *)(dst + 0x20) + 0x10) = a + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);
```
This changes the RTL slightly (a temp) — might shift priorities. But the target's instructions show `lhu v0,252(a2); lhu v1,16(v1); addu v0,v0,v1` — so the two loads then add; an explicit temp for the first load wouldn't change the insns (same pseudos). Could change qty numbers/birth order → allocation. Worth a try!

Similarly, hoisting `*(s32 *)(dst + 0x20)` into a temp: target does `lw a0,32(a2)` then `sh v0,16(a0)` — the address temp. An explicit `s32 d20 = *(s32*)(dst+0x20);` used for both stores would keep it in one reg (target loads it twice: 152 `lw a0,32(a2)` and 158 `lw a0,32(a2)` — twice). So no.

The explicit u16 temp for the 0xFC load: target loads it once. Let me test a variant that adds `s32 v = *(u16 *)(dst + 0xFC);` — actually the sum is `*(u16*)(dst+0xFC) + *(u16*)(...src...)`; both loads feed one add. An explicit temp would be the same two loads.

Changing the *order* of the two loads: `*(u16*)(*(s32*)(src+0x20)+0x10) + *(u16*)(dst+0xFC)` — commutative add; operand order might swap which gets v0/v1. Could shift allocation. Let me test this on the s32 dst body: swap the add operands in both sums (4 sites).

Also: make `*(s32 *)(src + 0x20)` hoisted into a temp? Target reloads it per use (lw v1,32(s0) twice per block). So no.

Let me test the add-operand swap (q1) and an explicit temp (q2) on the s32 dst body. Quick.
