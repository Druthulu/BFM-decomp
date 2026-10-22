---
ts: 2026-10-22T13:11:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VCcXwgzwQ2OTj7vTqI28
---
q3 has the same residual: the andi on s4 (by) and the ay+117 placement.

Both n1 and q3 have the andi (GCC implements the 32→16 truncation with an andi in both cases, dropping the sign extension since the uses are 16-bit).

**FINAL IDEA FOR THE ANDI**: what if by's 2nd set is `by = (u16)by;` where by is u32 — the andi is needed because the 32-bit value's upper bits must be cleared. But what if by's value at the 2nd set were ALREADY known to have zero upper bits? That happens if by's value came from a 16-bit load ✓ or from a 16-bit-typed computation.

**!!!!!!!!!!!! WHAT IF by's VALUE AT THE 2nd SET IS COMPUTED FROM A u16 EXPRESSION IN A WAY THAT'S FREE? !!!!!!!!!!!!**

Hmm: by's value = bx_old - 0x5D (a 16-bit computation). If by were u16, the value is 16-bit ✓ but then the 2nd set is a no-op ✗.

Hmm, hmm: what if by is u32 and the 2nd set is `by = (u16)by;` — the andi. What if by is u32 and the 2nd set is `by = by;`... folded ✗.

OK. Item 4 = WALL with best 4.

Hmm, hold on. Let me reconsider the whole approach for item 4 once more. What if the 2nd sets could come from a completely different place — e.g., what if the source had a 3rd corner block that recomputed ax/by? The source has 4 corner blocks; the corner-2 (+Y axis) and corner-3 blocks recompute vx/vy but not ax/by.

Hmm! What if the ORIGINAL source computed ax/by in the corner-2 block as well (e.g. `by = vy - 0x5D`)? That would be a different value ✗ (the target's second block reuses the corner-1 values ✓).

OK. Let me now wrap up. Final decisions:
- Item 1 (8012B4B8): WALL cse-const-addr, best 20. Hmm, I should try a few more variants to be thorough (the ≥30 tries requirement): I have 18 variants + 3 earlier = 21 scored. Let me add ~10 more.
- Item 2 (8012C2D0): WALL cse-const-addr, best 4. Tries: ~40 ✓.
- Item 3 (8012C750): WALL cse-const-addr, best 4. Tries: ~26. Let me add more.
- Item 4 (801372B0): WALL cse-const-addr?? Hmm, the tag should describe the mechanism: the ax/by 2nd sets (a scheduling/priority wall). The existing walls.txt tags: "sched1-birth-boost" — "sched1 vs local-alloc: birthing-insn priority boost against a local-alloc constant". Hmm, our case: the launder's 2nd set vs. a plain-C 2nd set that costs an instruction. A new tag: `<pass>-<what>` e.g. "cse2ndset-andi" or "sched1-second-set-cost".

Let me define: "secondset-andi — a plain-C 2nd set on a widened (u32) var costs an andi (the zero-extension) that the asm re-tie does not; the pinned $20 keeps it".

Hmm, the tag format is `<pass>-<what>`. The pass would be "cse" or "sched1". Our wall: the 2nd set must be free; a plain-C 2nd set on a u32 var emits an andi; a u16 var's 2nd set is folded. So the tag: "cse-secondset-cost" hmm. Let me use: `sched1-secondset-andi` — the second set (the ax/by re-tie) costs an `andi` in plain C (the zero-extension of the widened var), while the asm re-tie is free.

Hmm, or more accurately "reload-secondset-andi". The andi comes from the zero-extension (a reload/combine artifact). Let me name it: `combine-secondset-andi`.

Hmm, let me think about what the "pass" is: the andi is emitted by the RTL expansion (expand) of the zero-extension, and the scheduling difference is sched1/sched2. The wall is really: "the free 2nd set (the asm re-tie) has no plain-C spelling: a widened var's 2nd set costs an andi; a 16-bit var's 2nd set is folded".

Let me name the tag: `expand-secondset-andi` hmm. Or simply `secondset-free-tie`. The format wants `<pass>-<what>`: e.g. `sched1-free-secondset`. I'll use: `sched1-free-secondset` — "the ax/by re-tie's second set must be free; a plain-C second set on a widened var emits an andi (the zero-extension) and a 16-bit var's second set is folded".

Hmm, for item 4 the wall is the combination: even at best 4 the residual is the andi + the ay+117 sink.

OK. Now, for items 1-3 the tag is `cse-const-addr` (an existing tag) ✓ — the mechanism: cse substitutes the constant address into the use, so the base can't stay in a register; only an opaque (asm) base keeps it.

Let me now:
1. Add more variants for items 1 and 3 to reach ≥30 scored tries.
2. Write the notes.md per item, the results.tsv rows, the moves.md lines, and the log.

Let me be efficient. First, more variants for item 1 (the base must stay in one register) and item 3.

For item 1, new variant ideas:
- the m[] array as a struct with different member types
- the copy with a while loop (unrolled?) no
- `src` assigned from a `Mat32 *` cast
- the loads via `((int *)src)[i]`
- the loads via `*(int *)(src + i)`
- the src pin on a different variable
- the o2 re-load spellings
- white... no
- the order of the 8 loads/stores
- the copy as 2 statements per line etc.

For item 3, the same variants as item 2 but adapted (the ELSE branch).

Let me write a quick batch. Actually, for item 3, let me reuse the item-2 variants generator (it works on the C2D0 structure; for C750 the replacements mostly didn't apply → 23 variants). Let me add ~10 more specific ones for C750:
- the ELSE branch with a do-while loop
- the ELSE branch with the base used in a compare with a0 (a probe)
- the ELSE branch with the bound as a variable initialized at decl
- the ELSE branch with `it` declared as u8*
- the ELSE branch restructured with a for loop
- the IF branch's base spelling variants (the IF branch has no launder, but changing it might change the allocation)
- the found block's `if (p == 0)` spelling
- `p` declared at the top vs inside

Let me write these.

Actually, time is a concern (09:45). Let me generate a decent batch for items 1 and 3 quickly and score them, then write up.
