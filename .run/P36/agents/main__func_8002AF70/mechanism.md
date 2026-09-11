# func_8002AF70 (src/800.c) — e29, P36 S104 — SCORE 0, zero levers

(a) Residual (lever-free text, 27 COUNT / sweep best 2 ORDER): the hand-written Blk16 loop gives `src` s0 and `dest` s1
(the target has dest = s0, src = s1, val = s2) and orders the prologue differently; the tree faked it with a `$16` pin on
`dest`, an asm `lui/addiu` and a launder on `src` after the loop.

(b) The bytes are not a C loop at all: they are gcc's own BLOCK MOVE for one struct assignment of 0x2DC bytes.
`expand_block_move` (tools/reference/gcc-2.7.2/config/mips/mips.c:2330ff) copies the DEST address into a register first
(`copy_addr_to_reg`, :2348) then the source; for a constant size > 2*MAX_MOVE_BYTES with word alignment it calls
`block_move_loop` (:2222) — `final_src = src + (bytes - leftover)` (the `addiu a2,s1,720`), a 16-byte
`movstrsi_internal` (4 lw + 4 sw, MAX_MOVE_REGS=4, :2216), `src += 16; dest += 16; bne src,final_src` (:2280-2287, the
exact `addiu s1 / bne s1,a2 / addiu s0` shape), then the 12-byte leftover `movstrsi_internal` (:2291). 0x2D0 + 12 = 0x2DC.
Proven on bytes (score 0).

(c) Move: replace the Blk16 loop + Blk12 tail with ONE struct assignment of a 0x2DC-byte struct (body-local typedef
`struct { u32 w[0x2DC/4]; }`, u32 for word alignment):
    func_80016714(D_80075CC0, 0x300);
    *(Blk2DC *)D_80075CC0 = *(Blk2DC *)a0;
    D_80076040 = a1;
Both the cast-at-use spelling (body.c) and a `Blk2DC *dest = …` local score 0.

(d) GENERATOR PROPOSAL: when a body copies Blk16 (or 4 words) in a do-while `src != src + N/16` loop followed by a
<16-byte tail copy (Blk12/Blk8/word), replace loop + tail with one struct assignment of size N + tail (word-aligned
struct), deleting the loop pointers — `block_move_loop` emits exactly that loop; the same TU's func_8002B00C (the reverse
copy, already matched as a loop) is the same idiom.

(e) Not tried further: register/order levers — unnecessary once the copy is a struct assignment (the regs follow from
expand_block_move's dest-first copy_addr_to_reg and the source's natural allocation).

(f) Method gap: nothing in the method names "a hand-written 16-byte-stride copy loop with a 12-byte tail = gcc's
block_move_loop"; the residual reads as a register permutation and every generator mutates the loop text.

(g) Structs: YES, a struct is exactly the answer here — D_80075CC0 is a 0x2DC-byte struct (likely a saved-state block,
func_8002B00C copies it back out) and a0 points to the same type; declaring `D_80075CC0` with that struct type at file
scope would make both functions plain `D_80075CC0 = *a0;` / `*dest = D_80075CC0;`. Tested with a body-local typedef: 0.
