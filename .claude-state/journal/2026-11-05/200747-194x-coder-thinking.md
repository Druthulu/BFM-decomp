---
ts: 2026-11-06T03:07:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9EvjB1gNAdf7neVLFI8x
---
Target arms:
- if (d >= 0): 4bd0 lh a0,10(s1); 4bd4 lh v1,26(sp); 4bdc subu v0,a0,v1; 4be0 bltz v0,4bf8 (else arm); 4be4 slti v0,v0,513; 4be8 beqz v0,4d04 (TAIL); 4bf0 j 4c08; nop.
- else: 4bf8 subu v0,v1,a0; 4bfc slti v0,v0,513; 4c00 beqz v0,4d04; 4c04 nop; then 4c08 (fall-through).

So the target has:
- First arm: bltz → else; slti/beqz → TAIL; j 4c08 (fallthrough to the rest).
- Else arm: subu; slti; beqz → TAIL; fall-through to 4c08.

Note the else arm's `d = buf1 - unkA` is computed as `subu v0,v1,a0` (v1 = buf1, a0 = unkA). The first arm's `d = unkA - buf1` is `subu v0,a0,v1`.

The tails: both arms end with `slti v0,v0,513; beqz v0,TAIL; nop`. In the target they are SEPARATE (4be4/4be8 and 4bfc/4c00). The cross-jump would merge them.

Mine (without barrier): merged, 109 ins. Let me see mine's asm. The diff said mine has `bgez v0,4bf0` vs target `bltz v0,4bf8`, and target has extra `beqz; nop; j; nop` at 27-30.

So in mine, the first arm's test `if (d >= 0)` became `bgez` (inverted), and the tails merged. Let me get mine's asm around there.

Real-C approaches:
1. Polarity: write the two `if (d > 0x200) goto TAIL;` differently. The target's both are `slti v0,v0,513; beqz v0,TAIL` — same polarity. Hmm, so the target itself has identical tails, and the compiler did NOT merge them in the original! How?

Wait — the original build has separate tails despite identical insns. The cross-jump should merge them... unless the CFG prevented it (minimum=2 and only 2 insns match? Let me count: the matching suffix is `slti; beqz; nop`? The delay slot nop counts? find_cross_jump compares insns: slti (match), beqz (match), then nop (match?) — that's 2-3 insns. With both sides reached by `j`... The first arm's tail is followed by `j 4c08`; the else arm falls through to 4c08. So one side falls through → minimum=1 → merge. Hmm.

But the target has them separate. So the original C must have shaped the CFG so cross-jump didn't apply. The barrier note says "keeps this arm's slti/beqz test a separate RTL block from the sibling arm's identical-looking test below, so gcc's cross-jump pass does not re-merge the two tails into one (which drops 2 instructions and swaps which arm is the branch target vs. the fallthrough)".

So the original C had the same issue; the reconstruction added the barrier. Our job: find real C.

Given the target's shape: first arm `bltz v0, else; slti; beqz TAIL; j 4c08; nop`. The else arm `subu; slti; beqz TAIL; nop` then falls to 4c08.

If cross-jump merged, dec... hmm.

Ideas from the cookbook (ov_SC03_099 §5a): use different polarity in the two sites. Here both sites are `if (d > 0x200) goto TAIL`. The target shows both as slti/beqz (same). So polarity isn't it.

Maybe the key is the *goto TAIL* vs a different structure. What if the else arm's tail is not `goto TAIL` but the code falls into the rest, i.e., the else arm's `if (d > 0x200) goto TAIL;` is written as `if (d <= 0x200) { rest }`? That would restructure.

Hmm, what if the two arms use different comparison expressions that still compile to slti 513: e.g., first `d > 0x200`, second `0x200 < d`? The front end canonicalizes. What about `d >= 0x201`? Same slti 513? `d >= 0x201` → slti 513; beqz (if d < 513 → skip). Yes, same instruction. But the RTL for `d > 0x200` vs `d >= 0x201`: both become (lt d 513) or (le 513 d)? They may be represented differently in RTL: `d > 0x200` = (gt d 512); `d >= 0x201` = (ge d 513). These are different RTL expressions that compile to the same insn! cse/jump compare the *insns* after expansion; the insns would be identical (slti 513; beqz). Hmm, but at jump2 the insns are the same.

Unless the difference in the RTL comparison causes a different expansion (e.g., slti 513 vs slti 513 + ...). Both produce `slti v0,v0,513` then `beqz`. Same insns.

Hmm.

What if one arm's test is `if (d > 0x200) goto TAIL;` and the other is `if (d < 0x201) { } else goto TAIL;`? The else form: `if (d < 0x201) ... else goto TAIL` — the compiler might invert to `slti; bnez` (branch if d < 513 → skip the goto). That would differ: `slti v0,v0,513; bnez v0,<fallthrough>; j TAIL`. Target shows `beqz v0,TAIL`. ✗

What if we restructure the else arm to avoid the goto: 
```
} else {
    d = buf1 - unkA;
    if (d <= 0x200) {
        /* fall through to the rest */
    } else {
        goto TAIL;
    }
}
```
This emits: slti; bnez (if <=, skip); j TAIL. Different polarity. ✗ (target is beqz TAIL).

Hmm, what about the two arms being in a different order or using `d` vs a temp?

Let me look at mine's asm to see exactly what the merge produced, and then think about which C shapes would produce the target.
