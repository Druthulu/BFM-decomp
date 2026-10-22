---
ts: 2026-10-22T12:41:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7SnnoF0cUkWBQR2olUOW
---
Fast (1s per score).

Score 4. The difference: target has `lui v1,0x0; addiu v1,v1,0` (materializing D_80120194 in v1 — wait, lui 0x0 + addiu v1,v1,0 = the address 0x00000000? Hmm, that's the relocation-masked form. Actually D_80120194 → lui v1, 0x8012; addiu v1,v1,0x194 would be 2 ins. Here "lui v1,0x0" and "addiu v1,v1,0" — the reloc operand masked shows 0. So these are lui + addiu forming the address of D_80120194, masked.

So target: v1 = &D_80120194 (materialized in v1, a callee-saved reg!), then addiu a0, v1, 25996 (0x658C).

Mine: a0 = &D_80120194 (lui a0/addiu a0) then addiu a0, a0, 25996 — GCC folded the address into a0 and used a0 for the pointer; then at the compare, beq a0,v1 swapped order (a0 vs v1).

So the launder forces `it` into a pseudo that gets v1 (callee-saved) — the launder's copy pseudo has a different class than the direct symbol, so GCC keeps the symbol address in a reg and copies.

Without launder: `it = (s32)D_80120194;` — gcc does `lui a0; addiu a0` and the "it" pseudo = a0, then p = a0+0x658C folded.

We need the target's shape: v1 = address (kept), a0 = v1 + 0x658C. So the target keeps D_80120194's address in a callee-saved register v1.

The launder's effect: creates a copy of `it` so cse cannot merge `it` with the symbol's address pseudo, forcing the address into a distinct reg which is global-alloc'd to v1 ($23) since it's live across the whole function.

Without asm, how to force that? Real C moves: maybe declare `it` as a volatile? No — that's a lever class (byte-needed volatile cast is class C/D, "STAYS"). Hmm, volatile is arguably a "keepalive" or barrier lever. The row kind is launder; adding volatile would be adding a lever of another kind → not allowed ("no new lever of any kind").

Options within real C:
1. Make the address come from a place GCC can't fold: e.g. `it = (s32)D_80120194;` → since D_80120194 is `extern u8[]`, the address is a link-time constant. GCC materializes it into a reg.

2. The key difference: the target's `it` value lives in v1 across the function and is incremented in the loop (`it += 0x10C`). Wait — actually in the target, at the `copy:` label it returns `it`... hmm.

Let's look at the target's full instruction list. Let me dump the target vs mine fully. Let me get more of the diff output (tail with larger n).

Let me run with tail 60 to see the full diff.
