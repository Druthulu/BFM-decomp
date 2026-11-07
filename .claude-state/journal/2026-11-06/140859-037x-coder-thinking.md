---
ts: 2026-11-06T21:08:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ev512mkU34U1tMGbGcEV
---
Excellent! Score 9, 63 insns both, only the last block's x/y register swap remains. t is now fully matched (v0). Now the last block: target x=v0, y=v1; mine x=v1, y=v0.

The last block: `x = (lhu 0x10 + 0x2d) & 0xfff; y = (lhu 0x12 + 0x16) & 0xfff; store x; store y; call`.

Target: x=v0, y=v1. Mine: x=v1, y=v0. Priority: in block 7, x and y are both 2 refs; y lives longer (its store is in the delay slot after the call). So y wins v0. In the target, x is pinned to v0.

How to make x win v0 lever-free? Options: 
- Give x more refs (e.g., use it twice).
- Make y die earlier (store y before the call? the store order is fixed: x then y).
- The target order: `sh v0,16` ... `sh v1,18` (in the delay slot). Both stores are at the end.

Hmm. Actually in the target, the stores: `sh v0,16(s1)` at 1738 and `sh v1,18(s1)` at 1740 (delay slot). Mine: `sh v1,16` at 54 and `sh v0,18` at 56.

Wait, in mine, x=v1, y=v0; x's store is at 54 and y's at 56. So the *order* of the stores is the same (x then y), only the registers swap.

To make x take v0: give x higher priority. x: `(lhu + 0x2d) & 0xfff`. y: `(lhu + 0x16) & 0xfff`. Same shape. The difference: y's store is later (after the call), so y's live range is longer → lower priority? Priority = refs*size/live_length. Longer live → LOWER priority. Wait: pri = floor_log2(refs)*refs*size/live. So y (longer live) has LOWER priority. Then x should win v0. But mine gives y v0!

Hmm, but this is local-alloc, where qty_birth/death are computed within the block. Maybe x's live range is longer because x is born first? Both born at their loads. Let's compute: x born at insn 46 (lhu 16), dies at 54 (sh). y born at 47, dies at 56. Both refs 2, size 4? Hmm, x and y are u16 → size 2? In the earlier table: r88 (2 bytes), r89 (2 bytes), r90, r93 (2 bytes), r94 (2 bytes), r95. 

Hmm wait, actually x and y are u16 variables, but the computation `(lhu + 0x2d) & 0xfff` is done in SImode then truncated to u16 for the store? The target shows `lhu v0,16; addiu v0; andi v0; sh v0,16` — the same register v0 through the whole chain, so the pseudo is SImode (4 bytes) and stored via subreg. Hmm, but the .flow dump said "2 bytes" for some.

Let me check the local priorities in w3's block 7 via alloc_table. Let me dump w3 and look.

Actually, maybe simpler experiments:
1. Reorder: compute y before x? No, the target order has x's load first.
2. Make x and y one variable? No.
3. Give x an extra ref via a fold, e.g. `x = x & 0xfff` after? That's identity → not allowed as a launder.
4. Change the store order: store y first then x? Target stores x then y — no.

Hmm, what if x is declared as s32 instead of u16? Then x's size is 4 (higher priority) vs y's 2 → x wins v0! But the store would be `sh` of a subreg — the same. Would it change codegen? The value is masked with 0xfff so no difference in code. Let's try: `s32 x = ...; u16 y = ...;` Hmm, but the target's target.s has x in v0 and y in v1. Sizes affect priority: pri = floor_log2(refs)*refs*size/live. With refs 2: floor_log2(2)=1, so pri = 2*size/live. x s32: size 4; y u16: size 2 → x wins.

But careful: `u16 y` vs `s32 x` — the store `*(u16*)(s1+0x10) = x` with x s32 → subreg HImode store, same instruction.

Let's try w4: x as s32, y as u16.

Actually also consider: declare both as s32? Then equal size, and live lengths decide: y longer → lower pri → x wins v0. That might work too and is more natural. Let me try both.

Let me also think: the target's x/y both come from the pinned source where x was `register u16 x __asm__("$2")`. The natural C would be u16 x, u16 y. But whatever produces the match is fine as long as it's real C.

Try w4a: both s32. w4b: x s32, y u16.

Wait, but if x is s32, `(*(u16*)(s1+0x10) + 0x2d) & 0xfff` — the lhu zero-extends, add, andi; store via subreg. The instruction `sh` needs the value in a reg; no difference.

Let's test both in one sc.sh run.
