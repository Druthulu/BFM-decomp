---
ts: 2026-10-22T00:06:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_MTlcI5wotKgjmmyVnbCx
---
Oops, v2 is the same as v1 except the order of `s1 = 1;` and the store (I swapped them). Let me instead make v2 a real variant: introduce a temp for the index.

Let me write v2 as:
```
                off = ((Unkstruct_800B5CB8 *)a0)->unk100 * 8;
                {
                    s32 t = off;
                    D_801270C8 = *(s16 *)((u8 *)p + t + 4);
                }
```
Hmm, that introduces a copy (a move) — probably an extra insn. Hmm.

Hmm. Let me think about the swap more cleverly.

The RTL: mine `addu v0,v0,a1` (v0 = index, a1 = p) → the result = index + p.
Target: `addu v0,a1,v0` (a1 = p, v0 = index) → the result = p + index.

The tree order in the RTL: mine (plus reg_v0 reg_a1), target (plus reg_a1 reg_v0).

In gcc, `combine` canonicalizes commutative operands in some cases (e.g. by comparing costs or reg numbers). The "commutative swap" R-rules are about the ALLOCATOR's choice.

Hmm, the hint: "the caller-saved swap is decided in local-alloc's block_alloc/combine_regs by which dying pseudo the operand ties to — the temp inlined/introduced first".

So: the operand that "ties to" the dying pseudo. Hmm.

Practical approach: try spelling variants that change the tree:
(a) `*(s16 *)((u8 *)p + off + 4)` — current (index + p after combine).
(b) `*(s16 *)((u8 *)(p + (off / 8)) + 4)` — hmm, off/8 → a shift right; the target has a shift LEFT ✗.
(c) Introduce the pointer arithmetic on a `u8 *`: `u8 *pb = (u8 *)p; D_801270C8 = *(s16 *)(pb + off + 4);` — the pb copy might be coalesced; the tree is the same.
(d) Make `off` a pointer-typed thing: e.g. `D_80195AF6_t *pq = p + idx;` hmm, that's the element arithmetic (the target's sll*8 suggests byte arithmetic).

Hmm! (d): `D_801270C8 = *(s16 *)((u8 *)(p + idx) + 4);` — p is D_80195AF6_t* so p + idx is element arithmetic → the scale would be sizeof(D_80195AF6_t) — hmm, the target's scale is 8 (sll 0x3) so the element size is 8 ✓ if sizeof(D_80195AF6_t) == 8! Then `p + idx` → the address = p + idx*8 (the sll) ✓ and the tree = (plus p (mult idx 8))?? Hmm, and the +4 → the MEM's offset ✓.

So: `D_801270C8 = *(s16 *)((u8 *)(p + ((Unkstruct_800B5CB8 *)a0)->unk100) + 4);` — hmm, but the scale: p is D_80195AF6_t* → the element size = sizeof(D_80195AF6_t). If it's 8, we get the sll 0x3 ✓. But the C currently uses `off = unk100 * 8` (a manual *8) and `(u8*)p + off` → the sll 0x3 ✓ too.

The difference: with `p + idx` (pointer arithmetic on the typed pointer), the tree = (plus p (mult idx 8)) — hmm, the same as the target's order. And with `(u8*)p + off` where off = idx*8, the tree = (plus p (mult idx 8)) too. Hmm, the same.

Hmm, but the result differed. So combine swapped one of them. Hmm.

Let me check sizeof(D_80195AF6_t) — if it's not 8, then `p + idx` would give a different scale. Let me check the struct definition. Hmm.

Let me try a couple of variants quickly:
v2: `D_801270C8 = *(s16 *)((u8 *)(p + ((Unkstruct_800B5CB8 *)a0)->unk100) + 4);` (drop `off`)
v3: `D_801270C8 = *(s16 *)((u8 *)p + ((Unkstruct_800B5CB8 *)a0)->unk100 * 8 + 4);` (inline, no `off` variable)

Let me test v3 first (inline the index, keeping the byte arithmetic).

Hmm, but `off` is a declared variable used only there; removing it changes the local set (fine).

Let me write v3 with the inline index.
