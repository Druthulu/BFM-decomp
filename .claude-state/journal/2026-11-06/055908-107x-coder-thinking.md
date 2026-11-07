---
ts: 2026-11-06T12:59:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XCH4NQEGTVCoy2WtLIsz
---
Target around 63c4:
```
63b8: andi v0,v0,0xf
63bc: addiu a0,v0,1
63c0: sll a1,a1,0x4
63c4: move v1,a0        ← iv2c = iVar2 (a0)
63c8: li v0,1
63cc: beq v1,v0,63d8
63d0: nop
63d4: move t3,zero
63d8: andi v0,a2,0xffff
...
```
And mine lacks `move v1,a0` — so mine does `li v0,1; beq a0,v0` directly (the copy coalesced).

The launder `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));` created `iv2c = iVar2` as a separate value (a copy into another register) — the asm prevented coalescing.

Lever-free: `iv2c` is `int iv2c = iVar2;` then `if (iv2c != one) uVar5 = 0;` where `one` is pinned $2.

Mine: `move a0,iVar2`? Let me look at mine's asm. In mine, iVar2 is in a0 (from `addiu a0,v0,1`), then `li v0,1; beq a0,v0`. So iv2c coalesced with iVar2.

To get `move v1,a0`, iv2c must be a distinct pseudo. The classic trick: make the copy a *different mode* (HImode) so cse can't merge, or a cast that blocks coalescing.

From moves.md line 217: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class".

So: `int iv2c = (short)iVar2;`? Hmm, iVar2 is `int`, and the compare `iv2c != one`. A (s16) cast would produce sll/sra insns (2 extra). Unless iVar2 is known small... 

Hmm. In the target, `move v1,a0` is a plain 32-bit copy. To keep it, we need the copy not coalesced.

Options:
- Make iv2c `volatile`? no (a lever).
- Make iv2c a `short` variable: `short iv2c = iVar2;` then `if (iv2c != 1)`. The copy to a short variable would be `move v1,a0`? A short variable in a register is stored as a 32-bit value (sign-extended). Since iVar2 is a value 0..? hmm, iv2c = iVar2 where iVar2 = t+1 (0..16), so no truncation needed — but gcc must sign-extend if it doesn't know the range: it might emit sll/sra. If it knows iVar2's range (from `t = param_2 >> 0x10 & 0xf; iVar2 = t + 1;` → 1..16), no extension needed → just a copy. That could give exactly `move v1,a0`!

Then the compare `iv2c != one` with one = 1 (pinned $2): `li v0,1; beq v1,v0`. 

Let me try `short iv2c = iVar2;` — but wait, the variable declaration is inside a block: `int iv2c; iv2c = iVar2;`.

Let me try several:
- n1: `s16 iv2c = iVar2;` and `if (iv2c != one)`.
- n2: `int iv2c = iVar2; if ((s16)iv2c != one)`.
- n3: `int iv2c = iVar2 + 0;` no.
- n4: `u16 iv2c = iVar2;`

Also the other diffs: `sw v0,-4(t0)` insert, `j 63f4` vs `j 63f0`, etc. Let me see the rest of the diff first. Score 7 with ~6 diffs, all likely cascading from the missing move and the branch offsets.

Let me try the width variants.
