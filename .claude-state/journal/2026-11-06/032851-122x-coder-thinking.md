---
ts: 2026-11-06T10:28:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xvK4EX4V8h6H3GNgBqIQ
---
C0050 (§47) is the live-length slider via zero-byte asm. That's exactly the lever being used. A lever-free substitute would need real C to change live lengths.

Let me read C0050 to understand the mechanism and see if there's a real-C equivalent. But it's a "zero-byte asm" technique — inherently a lever. The question is whether real C can replicate the live-length change.

Actually, the task is to find a lever-free body. The barriers here do live-length arithmetic. Real C can change live lengths by moving statements or adding uses. But adding uses emits code.

Given the difficulty, let me try a batch of real-C variants and record WALL if no crack.

The key: 13 fences after `pkt = D_800A5E60;` extend some pseudo's live range. Which pseudo? Probably `pkt` itself, or `flags`, `tpage`, `otab`, `idx`. The comment says "0 -> 15, 8 -> 13, 10/11/12 -> 7, 13 -> MATCH" — the scores for 0,8,10,11,12,13,14,16 fences. So the fence count is a slider; 13,14,16 all match.

A real-C move to extend live lengths: hmm, the fences are between `pkt = D_800A5E60;` and the if. If I add real statements there that are later optimized... no, they'd emit code.

Alternatively, move `pkt = D_800A5E60;` earlier (before the tpage computation) to extend pkt's live range by the tpage block. That changes live length without extra code! Let me try:
```
tp = ...;
if (...) tpage = ...; else tpage = ...;
pkt = D_800A5E60;
```
→ move `pkt = D_800A5E60;` before the `tp = ...` lines. That extends pkt's live range by ~6 insns (the tp/tpage computation). The fences extended by 13 insns. Hmm, but moving the assignment earlier might change the load's position.

Actually, the fences are 13 zero-byte asm insns which count as insns in the block → they extend the live range of all live pseudos by 13. Moving `pkt = D_800A5E60;` earlier extends pkt's life by the number of insns between. The tpage block is about 6-7 insns. Not 13.

But the effect isn't exactly "13 insns"; it's the priority ratio. Let me just try moving pkt's assignment earlier and see the score.

Also, other real-C live-length moves:
- Move `b9 = D_800B9A02;` / `flags = ...` / `otab = ...` around.
- Compute tpage before otab.
- Move the `pkt = D_800A5E60;` to the very top of the function.

Let me generate variants for func_80023BF0:
l1: move `pkt = D_800A5E60;` before `tp = ...`.
l2: move `pkt = D_800A5E60;` to the top (after declarations).
l3: move `pkt = D_800A5E60;` before `mat = ...`.
l4: move `flags = ...` later.
l5: move `b9`/`otab` later.
l6: combine.

Let me look at the function's top part again:
```
    mat = D_800AF630;
    prims = *(u16 **)(arg0 + 0x20);
    b9 = D_800B9A02;
    flags = ((Unkstruct_80023BF0 *)arg0)->unk4;
    otab = (PTag_80023BF0 *)(b9 * 0x4000 + D_800A6610);
    if (flags & 0x4000000) {...}
    tp = (((Unkstruct_80023BF0 *)arg0)->unk27 + 0x100) << 6;
    if (...) tpage = ...; else tpage = ...;
    pkt = D_800A5E60;
    [13 fences]
    if (!(flags & 0x400000)) {...} else {...}
    ...
```
The fences extend the live ranges of everything live across them: pkt, tpage, x, y, idx, otab, flags, base. Their live lengths increase by 13, lowering their allocno priorities.

Real-C equivalent: insert real statements that are live... can't without code.

Alternative: move the `pkt = D_800A5E60;` earlier so pkt's life is longer. But the fences extend ALL live pseudos, not just pkt.

Hmm, what if I move the whole `tp/tpage` computation AFTER the fences? Then tpage's life shortens, not lengthens.

Let me just try the move of `pkt = D_800A5E60;` earlier and see how the score moves. If it goes down, continue.

Let me generate l1-l10.

Actually, let me first understand the residual direction. nopin = 102. The comment says with 13 fences it's 0. With 0 fences the score is 15 (per the comment "0 -> 15"). Wait, "0 -> 15" means 0 fences → score 15? But our nopin (0 fences, pin removed) = 102. Ah, the comment's numbers are with the pin present! "0 -> 15" = 0 fences but with the $3 pin → 15. And our pins_off_barriers_on = 76, barriers_off_pins_on = 52. Hmm, that doesn't match "0 fences with pin = 15".

Wait, the comment says the fences were re-measured on "THIS body" which includes the bitfield fix etc. Our barriers_off_pins_on = 52, not 15. Hmm, maybe the comment's body differs (the current src is the final body; the fences count 13). Let me recount: the src has 13 `__asm__ __volatile__("");` lines? Let me count. Earlier I saw 13 lines after `pkt = D_800A5E60;` plus 1 more in each loop branch (2 more). Total maybe 15. My barriers_off_pins_on removed all of them (grep -c asm = 1, which is the pin line). So I removed 15 barriers, not 13. The 2 in the loop branches are the §194-A fence (load can't pass). Removing those changes more.

Let me redo: remove only the 13 fences after `pkt = ...` (the live-length ones) and keep the 2 loop barriers. That might give a different score. Let me count the fences: the block after `pkt = D_800A5E60;` has 13 identical lines. The loop branches each have 1 `__asm__ __volatile__("");` before `c = *prims;`.

Let me create barriers_off_pins_on_13 (remove only the 13) and see.

Actually, the comment says "THIRTEEN zero-byte fences after `pkt = D_800A5E60;`". So 13 in that block. Plus 2 in the loops (the §194-A fence). My sed removed all 15. Let me remove only the 13.

Hmm, but the sed `/__asm__ __volatile__("");/d` removed lines matching exactly that (the loop ones also match, since they're `        __asm__ __volatile__("");  // !FAKE: barrier`). All 15 match.

Let me count and selectively remove. Let me count lines.
