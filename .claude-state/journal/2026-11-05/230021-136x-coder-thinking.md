---
ts: 2026-11-06T06:00:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_n5zT9CB4JOlhLuXlyt16
---
Still 10. Time 23:00.

Let me try the q/u swap fix via a different route: maybe the swap comes from the *order of the two tests* in the block. Hmm.

Let me look at the k10 asm to see the full first block, and compare to the target.

Actually, let me consider: in the target, the first block is:
```
1850 lw v0,32(s0)       q
1854 li a1,256
1858 lhu v1,18(v0)      u
185c li a2,0x9000
1860 addiu s3,v1,256    hold
1864 addiu v1,v1,-896   u
1868 jal func_8012BD3C
186c sh v1,18(v0)       q->unk12 = u
1870 sll v0,v0,0x10
1874 sra s1,v0,0x10     cc
1878 li s2,1            one
187c bne s1,s2, second
```
Note: q=v0 and it's used AFTER the call at 186c (`sh v1,18(v0)`). So q lives across the call in v0 — but v0 is call-clobbered! Hmm, the call `func_8012BD3C(a0, 0x100, 0x9000)` clobbers v0. So how is q still in v0 at 186c? Because the `sh` uses the value... wait, the store is in the delay slot of the jal (1868 jal, 186c sh)! Yes, 186c is the jal's delay slot. So q=v0 is used in the delay slot before the call clobbers v0. Clever.

And in mine (k10): `lw v1,32(s0)` q=v1, `lhu v0,18(v1)` u=v0, then `sh v0,18(v1)` — also in the delay slot.

So the swap is q=v0 vs q=v1. Both work.

Hmm. This is a local-alloc density decision. To flip it, I'd need to change the densities of q and u.

q's refs: def + lhu base + sh base = 3.
u's refs: def + hold + sub + sh value = 4.

Density: u has more refs but similar live length → u wins $2. That's mine.

Target: q wins $2. Why? Maybe because with the launder, the qty numbering/death indices differ.

Hmm, actually — maybe the difference is the *order of the instructions*: in the target, `lw v0,32(s0)` comes first (q born), then `lhu v1,18(v0)`. Local-alloc assigns $2 to the qty with the highest density; if q and u have equal density, the tie-break is the qty number (lower first). q is born first → lower qty number → wins.

In mine, u wins → u's density is higher.

Hmm.

What if I add a use of q? E.g., in the first block, `q` is used 3 times. If I make the store `((Unkstruct_800B5CB8 *)q)->unk12 = u;` (already). What if the load is `u = ((Unkstruct_800B5CB8 *)q)->unk12;` (already).

To raise q's density, add a reference. Any real extra reference costs an instruction.

Hmm, what about making `u`'s live range longer or refs fewer? E.g., `hold = u + 0x100;` and `u -= 0x380;` — if we combine: `hold = u + 0x100; u = hold - 0x480;`? That changes the asm (hold - 0x480 instead of u - 0x380) — the target has `addiu v1,v1,-896` reading u. If we wrote `u = hold - 0x480`, gcc would use s3 (hold) → `addiu v1,s3,-1152`. Different.

Hmm.

OK. Let me stop trying to fix the swap.

Let me now think about whether to keep going. It's 23:00; I need until ~23:12. Let me do a few more experiments with different *structural* ideas, then write up.

Actually, let me try the "opacity via memory" once more but in a clever way: what if `cc` is read from the *stack* through a pointer that gcc can't resolve because it's passed through a function that doesn't exist... no.

What about making `cc` a `static` local (function-scope static)? Then it's a global with internal linkage; gcc would keep it in memory (static locals aren't register-allocated... actually gcc can keep them in registers if not address-taken). A call to an external function can't modify a static → no reload.

Hmm.

What about `register` keyword? Banned.

OK. Let me try one thing: maybe the wall can be avoided by making the second test *not* redundant — e.g., by calling func_8012BD3C again? That'd add a jal (extra insn).

Hmm, but wait: the target's second block calls func_8012BD3C again and tests it. What if the first block's second test is actually testing a *different* value that happens to be in s1? Like... no.

Let me look at the target's `beq s1,s2` once more: s1 = cc (from sra), s2 = 1. Yes.

OK, WALL. Let me do a few more (to fill time) then write.

Let me try 4 more variants that change the block structure:
v1: move the `one = 1;` assignment into a do-while.
v2: declare cc inside the if block.
v3: make the first test `if (cc != one) goto second;` with a label before it.
v4: add an `else` to the second test.

Then write up.

Actually, let me use the time differently: let me check the item-5 (func_8017EF9C) quickly? No — the brief says don't stop between items, but I should finish item 4 first.

Let me do a few more.
