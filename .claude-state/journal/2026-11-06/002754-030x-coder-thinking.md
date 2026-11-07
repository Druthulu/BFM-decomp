---
ts: 2026-11-06T07:27:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2WSvAF0upkkhkX0ue8XV
---
Key: `used` includes `regs_live_at[ins]` for the qty's live range. So if a0 is live at those insns (from global-alloc-assigned pseudos), a0 is excluded. In target, a0 is live across the copy block. Since no instruction shows it, a pseudo live across but unused in that block could be `s1`... but s1 is in $17.

Wait — maybe in the target, `s0` (the struct pointer) is NOT in $16 but... no, move s0,a0 and s0 is $16.

Which global pseudo could be allocated a0? A caller-saved reg is never used for a value live across a call. All values live across the copies also cross the func_800CAF84 call later? Let's see: s0 and s1 are live across calls → callee-saved. The 4 temps are not live across calls.

Hmm, so a0 live in the copy block must be a pseudo that dies before the call. What pseudo is defined before the copies and dies before/at the call? None visible... unless the original C had a value like `v0 = *(s32*)(s1+0x20)` (the pointer) — v0 is $2, allocated. Wait the pointer v0 is used for all the loads; it's live in the block but in $2.

Could `arg0` itself be live? `move s0,a0` then arg0 could still be live if used later. If arg0 is used later (after the call), it would be callee-saved, and the compiler would keep arg0 in s0 (it does) OR keep arg0 in a0 and save/restore it around calls (a0 caller-saved would be clobbered by the calls). Since there are calls, a0 can't hold it. Unless the use of arg0 is BEFORE the call — e.g. in the copies: `*(Struct16*)(arg0+0x38) = ...` uses arg0 (a0) at the store. But the store uses s0 in target.

Hmm. What if the original C passed arg0 to something before the copies? No.

Let's approach empirically. The target excludes a0 from the copy block. What source change would reserve a0 there? Adding a quantity that is live across the copies and allocated to a0. For example, a local `s32 t = 0;` used after the copies? But that adds instructions.

Alternative: maybe local-alloc's `used` set includes regs live at the *block boundaries* due to a global pseudo that is live from the function start to some point past the block, allocated to a0. For example, `id` if global-alloc allocated it a0 and its live range starts at entry? No.

Let me reconsider: In the target, is a0 maybe reserved because the pseudo `arg0`'s value is still live in a0 due to the `REG_DEAD` note placement? `move s0,a0`: after this insn a0 is dead, so local-alloc knows a0 free. Unless the copy `move s0,a0` was actually scheduled differently: maybe the original has `s0 = arg0` but the compiler keeps arg0's pseudo in a0 until the end because `arg0` and `s0` are the same pseudo (the copy coalesced). Actually GCC might coalesce: `s0` variable = arg0 pseudo, and `move s0,a0` is the coalesced move emitted because arg0 (a0) must be moved to a callee-saved reg for its later uses. So arg0's pseudo becomes s0, dead in a0 after move. Yes.

Hmm, let me look at this from a different angle: maybe the target's a0 reservation is due to the `id` pseudo after all, via global-alloc: global-alloc assigns registers to pseudos live across basic blocks. `id` is set in the if-block and used there — local to one block, so local-alloc. But wait, the if-block contains a call; local-alloc allocates a0 to id there. That doesn't affect the earlier block.

Unless `id` is a pseudo whose live range starts at function entry because of how it's declared and set? No.

Let me try to just test variants and see what flips a0. Variants:
1. Move the two struct copies into a separate block (do-while) — changes local-alloc block? No, local-alloc per basic block; a do-while(0) is not a basic block boundary in RTL (no branch), so no.
2. Add a temporary to the copy region.
3. Use `u32`/`s32` widths for the struct copy values.
4. Change `s0 = arg0` into `s32 s0; s0 = arg0;` (separate) — changes birth order.
5. Reorder the two struct copies.
6. Split each struct copy into explicit field copies (already are).

Also the li order issue: `id = 0x4B;` — maybe move the assignment up before the copies? That would change scheduling. Actually target's `li a0,75` is at 32 (in the if-block, after the branch). Source has it inside the if. Fine.

The insert/delete li order: target births li a0,75 before li v0,0x8000. In target, a0 is allocated to id; in mine, a0 is allocated to a copy temp, so id got... wait, in mine, li a0,75 is also a0! Mine: `li v0,0x8000; li a0,75`. Both allocate id to a0. Order differs: target li a0,75 first. So it's a scheduling (sched1) birth-order issue, possibly affected by the a0 copy liveness: in target a0 was live in the copy block, so the `id` pseudo in a0... no.

Let me try to make the copies use a1-a3 by adding a real C statement that uses a0 across them. The only natural candidate: the function argument arg0. What if the original C did not use `s0` but used `arg0` for the two struct copies and then copied? Hmm, target stores to s0.

Wait, actually — maybe the original C is:
```
void func_800CB458(s32 arg0) {
    s32 s0;
    ...
    s0 = arg0;
```
and the keepalive/pin emulates something else entirely. Let me look at P36 pack for t8_tus2 to see what the original levers were for. Search .run/P36 for "800CB458".
