---
ts: 2026-11-06T12:47:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1OHCCmFJK4In7AW9jN32
---
w4 is at 9. Remaining:
1. The two early `return 0` → `move v0,zero` vs target `nop` (2 diffs + branch inversion).
2. A region around 135-148: mine uses a0 where target uses v0, and mine has `sll v1,v0,0x3` vs target `lh v0,112(s1); lh v1,266(s1); sll v1,v1,0x3`.

The register pair a0->v0 x1 is that region. Let me look at the code around there: that's `((Unkstruct *)param_1)->unk10A = idx;` then `tmp1 = D_801ED5F0[idx*2]; tmp2 = D_801ED5EC[unk10A*2];`.

In the target: `lh v0,112(s1)` (reload unk70), ... `lh v1,266(s1)` (unk10A) `sll v1,v1,0x3`.

So idx's reload path uses v0 for unk10A. Mine uses a0.

Hmm, this is the §137 allocno priority thing from the original comment: idx must take $v0 (pri 16000 vs 6666). The keepalive asm gave idx +1 ref. Now with the do-while(0) block splits, the priorities changed.

So I need idx (or the reload) to get v0 rather than a0.

The original note says: "the six pseudos here form a CONFLICT PATH ... All of {162,165,169,77,78} tied at pri 6666 (refs 2/len 3), so the tie fell to qty number and the reload won -> whole path inverted ($v0<->$v1, 11 insns off). idx (reg 156) sat at 6000 (refs 3/len 5). Folding an "r"(idx) input into the existing memory barrier adds one ref for ZERO emitted bytes -> pri 16000, so idx is allocated first, takes $v0".

So lever-free I need idx to have priority > 6666, i.e. refs 4+ (floor_log2(4)=2 → 2*4*10000/len). With len 5: 16000. So idx needs 4 refs (currently 3).

How to add a ref to idx lever-free? A real use that costs 0 bytes: e.g., using idx in an expression that folds. Ideas:
- `((Unkstruct *)param_1)->unk10A = idx;` is one use.
- `tmp1 = D_801ED5F0[idx * 2];` another.
- `D_801ED4B4[i70a]` def.

What if we write `tmp1 = D_801ED5F0[idx * 2]` and `tmp2 = D_801ED5EC[((...)->unk10A) * 2]` — the reload uses the field.

Add a use of idx: e.g. make the `unk10A` store use `idx` twice: `unk10A = idx & 0xffff;`? That could fold to nothing? For a u16 field store from a u16 value, `& 0xffff` folds.

Or declare idx as `u16 idx` and use `(s32)idx` in the index: `D_801ED5F0[(s32)idx * 2]` — a cast doesn't add a ref (same reg).

Refs count reg uses in RTL. A cast doesn't add uses.

Alternative: use idx in the `i70a`-based load too: e.g. `u16 idx = D_801ED4B4[i70a];` and then `((Unkstruct *)param_1)->unk10A = idx;` then `tmp1 = D_801ED5F0[idx * 2];` — 3 refs.

What about writing `D_801ED4B4[i70a]` as `D_801ED4B4[idx - idx + i70a]`? Fake.

Real C move: `((Unkstruct *)param_1)->unk10A = idx;` then `tmp2 = D_801ED5EC[idx * 2];`?? That would REMOVE the reload (the target reloads unk10A). But maybe the reload still happens because cse... no, cse would fold it.

Hmm, what about making tmp1's index use a separate statement:
```
u16 *tp = D_801ED5F0;
tmp1 = tp[idx * 2];
```
The pointer temp is a separate pseudo.

Alternatively: use idx in a comparison that folds? e.g. `if (idx != 0) ...` adds a branch.

What about `D_801F32D0 = 0;` — unrelated.

Hmm, the C0535-style trick: a do-while(0) around statements can add a ref? No.

Let's think: what gives a pseudo an extra "use" in RTL for free? A copy: `x = idx;` where x is then used — that's a real move (extra insn) unless coalesced. `((Unkstruct*)param_1)->unk10A = idx;` is the copy (a store).

What if the store is `unk10A = idx;` and then tmp1 uses `idx` and tmp2 uses `unk10A`... that's the current shape.

Maybe instead: make the *reload* path use a local `u16 rl = ((Unkstruct*)param_1)->unk10A;` — that adds a copy (extra insn).

Alternatively, maybe the priority issue can be fixed by *shortening idx's live length* or by giving the competing pseudos fewer refs.

Actually — hold on. Let me reconsider: in w4, the diff at 135-148 shows the whole path inverted: mine `lh a0,266(s1); sll v1,a0,0x3`? Let me look at the actual asm region in both. Let me dump w4's asm and compare with the target region.

Actually, maybe the do-while around the ret assignments (all arms) already changed priorities. Let me look at the exact residual: 9 points. Let me see the full diff (only 9 → few insns).

Diff:
- mine[21] move v0,zero vs nop (early return)
- mine[25] bnez a0 vs beqz a0 (early return #2, branch inversion)
- mine[27:29] j + move v0,zero vs nothing
- mine[135] insert lh v0,112(s1) (target has an extra lh!)
- mine[139] addu at,at,a0 vs addu at,at,v0
- mine[142] sll v1,v0,0x3 (mine) vs nothing
- mine[145] insert lh v1,266(s1)
- mine[148] insert sll v1,v1,0x3

So in the target, the reload of unk70 (`lh v0,112(s1)`) and unk10A (`lh v1,266(s1)`) both happen; mine reuses a0 (from an earlier load) and v0.

Let me look at the actual asm region to understand. Let me dump w4.
