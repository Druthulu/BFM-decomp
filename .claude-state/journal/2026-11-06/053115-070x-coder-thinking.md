---
ts: 2026-11-06T12:31:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1DnbMumAZud3lpeMYYkV
---
The keepalive at 291 (`"r"(fade)`) is in the second region: fade is computed, then cc is built from fade, then the asm uses fade, then rgbc is stored. The asm extends fade's live range so that... probably to keep cc/fade allocation.

For a real-C crack at 15 (each of 223/291), maybe reordering `cc = fade << 8; cc = fade | cc; cc = cc | (fade << 16);` vs the asm.

Honestly, the most promising small win here is the barrier at 6 (s5/s6 swap). But as analyzed, the two address pseudos' order is a tie decided by an insn slot.

Wait — actually, maybe I can flip s5/s6 with a real-C move: the two addresses are `&gsz0` and `&gsz1`, both created at `gte_stsz3(&gsz0, &gsz1, &gsz2)` (line 168). In global-alloc, ties break by allocno number = the order the pseudos are created = the order of the arguments in the expansion. If I could swap which one is created first... 

Idea: declare a separate `long *pz0 = &gsz0;`? adds insns.

Idea: change the ORDER of the gsz0/gsz1 declarations (line 17) — this changes the stack slots (292/296) but ALSO their pseudo creation order. If I swap gsz0 and gsz1 in the declaration, the stack offsets swap: gsz0 at 296, gsz1 at 292. Then target's `addiu s5,sp,292` would be gsz1... and the code's references to gsz0/gsz1 swap accordingly — the emitted code would be identical EXCEPT the register allocation order might flip, and the offsets stay the same (since the declaration order determines offsets but the names swap along with them, the generated code is byte-identical in offsets but the s5/s6 assignment could flip). 

Wait: swapping the declarations of gsz0 and gsz1 (both `long`) swaps their stack slots: gsz0 now at 296, gsz1 at 292. All code using gsz0/gsz1 refers to the variables, so the code is the same except the addresses' register allocation. And the pseudo creation order changes (gsz0 first still? The order of creation is by first reference in the body, not declaration). Hmm, but for stack slots, the address pseudo is created at first use.

Actually the offsets appear in gte_stsz3(&gsz0,&gsz1,&gsz2) — the arguments are &gsz0 then &gsz1, so gsz0's address pseudo is created first regardless of declaration order. So swapping declarations won't change the allocno order but WILL change the offsets... no wait, the offset for gsz0 would be 296 and for gsz1 292, and the code would emit `addiu sX,sp,296` for gsz0 first. The target has the first addiu (66) = sp,292 into s5. If gsz0 gets 296... that changes which address is 292.

Hmm, confusing. But the DECLARATION ORDER also determines the *variable* order in the frame. Currently: gotz, gflag, gopz, gsz0, gsz1, gsz2, gsz3 → offsets ascending? gsz0 at 292, gsz1 at 296 — yes ascending.

If I swap gsz0/gsz1 in the declaration: gsz1 at 292, gsz0 at 296. Then the code `gte_stsz3(&gsz0, &gsz1, ...)` emits addiu for gsz0 (296) first. The target's first addiu is 292. So the frame layout would change → many diffs.

Not good.

OK — item 3 is a WALL. Let me now do the 25 remaining tries quickly with a generator producing statement-order variants. I'll do it in one batch, then record.

Let me write gen8.py with ~25 variants:
- v: swaps in the box fill (lines 67-74): 4 variants
- my/mny compute order (64-65, 180-184): 4
- cc chain order (the fade/cc block at 217-222 and 285-289): 4
- rgbc/uvc0 store order: 3
- za/zb order in the 2nd region: 3
- combos with d202 (barrier dropped): 4 (to see if best < 71)

Let me look at lines 215-235 to get the exact text for the cc block.

Actually simpler: use generic string replacements I already know exist. Let me write them.
