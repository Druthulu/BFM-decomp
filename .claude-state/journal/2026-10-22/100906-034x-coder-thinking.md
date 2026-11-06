---
ts: 2026-10-22T16:09:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hlyvKNWVhEYvtZ65290s
---
The residual: mine uses a0 for D_80120194 and v1 for D_801202A0; target uses v1 for D_80120194 and a0 for D_801202A0. Just swapped registers (a0<->v1). Also target computes `addiu a0,v1,25996` (p = it + 0x658C using v1 base) at index 3, while mine computes p at index 2? Let me see the full sequence.

Target:
0 lui v1,0x0
1 addiu v1,v1,0
2 lw? ... (the diff aligns mine[2] and target[2] as equal)
3 addiu a0,v1,25996
...
mine:
0 lui a0,0
1 addiu a0,a0,25996
2 lw a0,0(a0)? hmm

Wait, mine[0..1]: lui a0,0; addiu a0,a0,25996 → mine computes the address D_80120194 + 0x658C = D_801202A0... wait 0x658C = 25996. And D_80120194 + 0x658C = D_80120720. Hmm, so `p = it + 0x658C`.

Target: lui v1,0; addiu v1,v1,0 (that's D_80120194 with low 0? The diff shows addiu v1,v1,0 — the immediate is masked/normalized? Actually the score masks relocations: `addiu v1,v1,0` probably has a reloc to D_80120194). Then mine[2]=target[2] (lw v0,0(v1) probably — loading the pointer value). Then target[3] addiu a0,v1,25996 = p = it+0x658C using v1 directly; mine[3] nop, because mine computed the address into a0 at insn 0-1 (lui a0; addiu a0,a0,25996 = D_80120720) instead of using `it` in a0? Hmm.

Let me get the full instruction listing for both. Use dump.py? It needs a candidate object. Use `--try --keep`... but scratch is shared/stale. Better: write a tiny script using masked_diff to dump the target and a candidate object. Or use dump.py with the candidate object — I need a fresh candidate .o. The --keep object path was shared but if I run --keep now for this item and immediately copy the object into my item dir, then use dump.py on my copy. Let's do that.

Actually, the diff already tells me: the only differences are register choices (a0 vs v1) and the placement of the p computation. Specifically:
- mine: computes D_80120194 in a0, loads it (lw a0,0(a0)?), then... wait mine[2] == target[2]. Let me reconstruct:
  mine[0] lui a0,0
  mine[1] addiu a0,a0,25996
  mine[2] ? (same as target[2])
  mine[3] nop
  target[0] lui v1,0
  target[1] addiu v1,v1,0
  target[2] ?
  target[3] addiu a0,v1,25996

Hmm, target[1] addiu v1,v1,0 → the low 16 of D_80120194 is 0? D_80120194 low = 0x0194 ≠ 0. Unless the reloc is masked as 0. In these dumps, reloc immediates are often shown as 0 in the object. So target[0..1] = lui v1,%hi(D_80120194); addiu v1,v1,%lo(D_80120194) → address in v1.
target[2] = lw v1,0(v1)?? That would be `it = *(s32*)D_80120194` — wait, `it = (s32)D_80120194` where D_80120194 is declared as what? If D_80120194 is an extern s32, then `(s32)D_80120194` loads its value! Yes: `it = (s32)D_80120194;` — D_80120194 is an `extern s32`, so this loads the *value*. And `(s32)D_801202A0` loads the value of D_801202A0.

So the code:
- load D_80120194 → it (v1 in target, a0 in mine)
- p = it + 0x658C
- goto test
- test: load D_801202A0 → it; if (it == p) goto zero
- body: if (*(u16*)it == 0) goto copy; it += 0x10C; if (it != p) goto body
- copy: return it
- zero: return 0

Mine: lui a0,%hi(D_80120194); addiu a0,a0,%lo; lw a0,0(a0)? But then p = it + 0x658C computed as a *constant* address D_80120194+0x658C into a0? The diff mine[0..1] shows addiu a0,a0,25996 — that's %lo(0x658C) added to %hi(D_80120194) → a0 = D_80120194 + 0x658C = p as a *constant*, then mine[2] (same as target[2])... hmm that doesn't fit.

Wait, mine[0..1] = lui a0,%hi(D_80120194+0x658C); addiu a0,a0,%lo(...) → p = D_80120194+0x658C computed as a constant address! Because cse folded `it = D_80120194` (value) ... no wait, `it = (s32)D_80120194` is a *load*, not the address. Unless D_80120194 is a macro/array? Let me check the header preamble for the declarations.

Hmm, actually maybe `D_80120194` is an `extern s32` and `(s32)D_80120194` loads. Then p = it + 0x658C. Mine computing lui/addiu with 25996 suggests the compiler folded `it + 0x658C` where it = the *address* D_80120194... 

Wait, maybe D_80120194 is `extern u16 D_80120194[]` or a pointer? Let me look at the header preamble.

Let me read the full header.
