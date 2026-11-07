---
ts: 2026-11-06T05:32:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8N7T8wtK3ypvY0ku1pMg
---
Target: vars=24, regs=3 (s0,s1,ra), args=16. Frame 56 = 24 vars + 16 args + 12 regs + 4 align = 56. 
Nobar: vars=40, regs=3, args=16 → 40+16+12 = 68 → 72.

So both have args=16 (outgoing args for the two calls: 3 args × 4 = 12 → 16 rounded). The difference is vars: 24 vs 40. The nobar has 16 more bytes of vars.

The arrays a[8], b[8], out[8] = 24 bytes. Target vars=24 = exactly the three arrays. Nobar vars=40 = 24 + 16 (a 16-byte spill/temp).

So the nobar version has a 16-byte extra temp (probably a spill slot from reload, or a temp allocated during expansion). The clobber removes it. Interesting.

What creates the extra 16 bytes in nobar? Probably a reload spill slot (a pseudo that doesn't get a register). The clobber changes register allocation such that the pseudo gets a register in the target.

This is a `global-alloc`/`lreg` effect. Hmm.

Could pure C avoid the 16-byte spill? Maybe by reducing register pressure (e.g., fewer live temps). The nobar body has `move a1,v0`/`move a0,v1` and 89 ins; the target has 95. The spill might be for a value kept live across the calls.

Let me look at the nobar .s / asm to find the stack access at the extra 16 bytes. The nobar frame is 72 with arrays at 16,24,32 (up to 40); the extra 16 bytes are at 40-55 (since saved regs are at 56,60,64). Let me check if there are accesses to 40-55(sp). In the nobar asm I saw earlier, no. So the extra 16 bytes are *unused* vars — a reload spill slot allocated but unused (pseudo dead after reload).

So both versions have an *unused* 16-byte vars block or not. It's a reload artifact: in nobar, one pseudo (16 bytes?) is not allocated a register, so `alter_reg` allocates a stack slot, but the pseudo ends up dead. The clobber makes that pseudo get a register.

Wait, the nobar asm had `lw s1,60(sp)`, `lw s0,56(sp)` — 2 callee-saved regs. Both use s0,s1. So the same regs.

Hmm, 16 bytes = maybe a DImode/BLKmode pseudo. What pseudo could be 16 bytes? The `__builtin_memcpy` of 8 bytes! `__builtin_memcpy((void*)(e+0x80), out, 8)` — GCC expands it inline (lwl/lwr). Maybe a BLKmode pseudo from the memcpy expansion. Hmm.

Actually, `__builtin_memcpy` in the source is used for the 8-byte copy. The target .s uses lwl/lwr/swl/swr. The nobar also. So same.

Let me find the spill slot in the nobar RTL. Let me look at the nobar .lreg dump for a stack slot (virtual-stack-vars). Let me grep the nobar RTL around the function.

Actually, I already know the target (orig) has vars=24 and nobar vars=40. Let me grep the nobar .rtl for the function's virtual stack refs.
