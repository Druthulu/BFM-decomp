---
ts: 2026-11-06T05:25:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RJqQzmXZv9jMGOGYw1q1
---
Interesting! a1 (`tmp = (s16)iVar2`) DID keep a copy (`move v0,v1` at insn 14 and 37) but in the wrong place and with the registers swapped: iVar1 (the pointer) ended up in a0 instead of v1, and iVar2 in v1.

So the copy survives now. The problem is register allocation: iVar1 should be v1 and iVar2 a0.

In a1, mine: `lw a0,32(s0)` (iVar1 in a0), `lh v1,16(a0)` (iVar2 in v1), then `bgez v1`, `move v0,v1` (tmp = iVar2). Target: iVar1 v1, iVar2 a0.

So with the copy surviving, iVar1 needs v1. The pin did that. Lever-free, iVar1 is a long-lived pointer across the branches; local-alloc should give it a register... but it gave a0.

Hmm. In n1 (merged), iVar1 got v1 correctly. With a1, the copy changes the qty priorities and iVar1 gets a0.

Interesting: local-alloc assigns registers within a basic block. iVar1 is live across the whole function (it's a global-ish value used in both blocks). It's a "global" pseudo allocated by global-alloc? Actually in gcc 2.7.2, pseudos live across basic blocks are allocated by global-alloc (which assigns $16-$23, callee-saved). But iVar1 lives across blocks within the same... hmm, the function has branches. Let me think: global-alloc assigns hard regs to pseudos live across basic block boundaries. iVar1 is used across many blocks → should be in a callee-saved reg ($16+). But the target has it in v1 ($3), a caller-saved reg!

Hmm, that means iVar1's live ranges are per-block (local-alloc). The pin forces $3.

In the target: v1 holds iVar1 across the branches (2a44 lw v1,32(s0); used at 2a68, 2a84; reloaded at 2aa0). Between 2a68 and 2aa0 there are no calls, so v1 is fine.

So the target's iVar1 is in v1 across a couple of branches — a local-alloc decision. Without the pin, in n1 it also got v1. In a1 it got a0.

So the register order depends on qty priority: v0 and v1 and a0 are assigned to the local pseudos. Target: tmp=v0, iVar2=a0, iVar1=v1.

Hmm, that's odd ordering. Let me think about how local-alloc assigns: it processes qtys by priority (ref count, live length). The first gets $2 (v0), then $3 (v1), then $4 (a0)...

Target: tmp=v0, iVar2=a0, iVar1=v1. But wait — iVar2 and tmp are in the same basic block, iVar1 too. Hmm.

Actually, iVar1 is live across the block boundary (the beqz branch to 2aa4 and the bgez branches). Hmm.

Let me look at the RTL for n1 to see the pseudo structure and which are global.

Alternatively, empirically: the pin forces iVar1 v1. Without it, we need a natural reason for iVar1 to get v1 rather than a0.

Since the pin is a row kind and must go, maybe the crack is to make iVar1 naturally take v1 via qty priority. In n1, it does take v1! The diff for n1 only showed v0->a0 (iVar2/tmp). So n1 already has iVar1 in v1. So the only issue in n1 is that iVar2/tmp merged into v0 instead of (iVar2 a0, tmp v0).

So: keep the copy (a1 did) but keep iVar1 in v1 (a1 broke it). 

In a1, the copy survived and the priority order changed: iVar2 got v1 and iVar1 got a0. Why? Because with the extra pseudo, the qty priorities changed.

Hmm, what if we keep the copy using a *dead* copy that doesn't affect priorities? Like a do-while that didn't work...

Let me look at n1's RTL: how many local qtys and their refs. Let me dump n1 and a1 and compare the .lreg.

Actually, let me think differently. Maybe there's a different real-C structure: instead of `tmp = iVar2` (a copy), maybe the target's `move v0,a0` is something else, e.g., the `tmp` variable being assigned from a *function-like* expression that gcc materializes.

Actually, look: `if (0 < tmp * 0x10000)` and `if (tmp * 0x10000 < 0)`. tmp*0x10000 is `sll v0,v0,0x10` (in place). Fine.

What if the source uses `tmp` differently: e.g., `iVar2 = ...; if (iVar2 != 0) { if (iVar2 < 0) { iVar2 += 0x80; ...} else { iVar2 -= 0x80; ...}}` — i.e., no tmp at all, using iVar2 directly. Then there'd be no copy at all. Score would be? That's like n1 but without the tmp variable. Probably the same 8 or worse.

Hmm, the copy `move v0,a0` must come from somewhere.

Let me reconsider: maybe the copy is a *sign extension* of a HImode variable. In the target: `lh a0,16(v1)` loads into a0, and `move v0,a0` is a copy. What if iVar2 is `s16` and tmp is `s32`? Then `tmp = iVar2` is a sign-extend, which on MIPS is sll/sra unless gcc knows. Hmm.

But note the target has `bgez a0` — testing iVar2 (a0) as loaded. If iVar2 were s16, the comparison would need the sign-extended value.

Let's try: declare `s16 iVar2;` and keep `tmp = iVar2;`. Then `lh a0,16(v1)` loads into an HImode pseudo, `tmp = iVar2` sign-extends into v0 → could be `move v0,a0` if gcc knows the value is sign-extended (it does: lh sign-extends). And `if (iVar2 != 0)` tests the HImode... would need sll/sra? Hmm, but if gcc keeps it sign-extended in a0, the test is `beqz a0`.

Hmm, this is worth a try. Also `u16 iVar2`.

Also try: keep iVar2 s32 but make `tmp` s16? Then tmp += 0x80 in HImode → extra.

Let me try:
b1: `s16 iVar2;` (decl) with `tmp = iVar2;` and the CAST_SIGN assignments still work? `iVar2 = CAST_SIGN(s16, iVar1, 0x10);` assigns s16 to s16 — fine.
b2: `u16 iVar2;`
b3: iVar2 s32, tmp s32, but `tmp = iVar2;` replaced with `tmp = (s16)iVar2;` — that was a1 (18).

Let me test b1, b2.

Also, what about the second `iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;` reload at the end of the first if — that's in the source.

Let me try b1/b2.
