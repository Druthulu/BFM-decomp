---
ts: 2026-11-06T22:56:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4dVyy8LsWPXlKj3VLBVi
---
None better than 33 (w7) except w19 (25, structurally different).

Hmm. Let me reconsider w7 = 33 (mask-in-place, no do-while). Wait, w19 = 25 (s16 d). And w7 = 33.

Let me re-examine: is w7 really lever-free and does it score 33? Yes.

Hmm, but actually, hold on. Let me reconsider the w6 approach: d=$s0, s1ang=$s1 correct, but u5/iVar4 wrong and no arg0 copy. What if I can fix the u5/iVar4 by making the u5 pseudo prefer $a0?

The target: u5 = $a0. In w6, u5 = $v1. If u5 had a preference for $a0, it would get it. Where could u5 get an $a0 preference? u5 = (call_result - 0x400) & 0xFFF. The call result is $v0. If we write u5 as a subtraction involving a hard reg $a0... e.g., `u5 = (ratan2(...) - 0x400) & 0xFFF;` — no hard reg.

What if the ratan2 call's first argument is arg0-derived and stays in $a0? The arg `*(s16*)(arg0+0xE) - D_80126CB8` is computed into $a0 before the call. After the call, $a0 is dead. If u5 were computed as `$a0 + something`... no.

Hmm.

What if u5 is a parameter? No.

OK. Let me now consider the WALL. I need ≥30 scored tries. Let me count my tries: prev_win baseline (1), w0-w30 excluding gaps... Let me count the sc.sh scores: w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10,w11,w12,w16,w17,w18,w19,w20,w21,w22,w23,w24,w25,w26,w27,w28,w29,w30 = 28. Plus prev_win (1) = 29. Plus the --explain runs (2). Hmm, ~30.

The brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I've done 28 scored candidate tries + baseline. Let me do 2-3 more to be safe, then write the WALL row.

Actually, wait. Before walling, let me make one more serious attempt: maybe I can fix the w6 arg0 copy by forcing the tie through the source. The tie is between arg0 (r72) and the pointer temp (r80). In w6, the pointer load is scheduled first. 

What if I write the source so that the pointer load's base is arg0 and arg0 is used AFTER the pointer load in a way that... no.

What if I make the pointer load use a separate variable and make arg0 die there explicitly? Hmm.

Alternatively, what if the arg0 copy is not needed if the pointer load uses $a0? The target has `move $2,$4` and `lw $2,32($2)`. If we can't get that, we can't match.

Let me try one thing: reorder the source so the u5 computation comes first and the s1ang load last, with the mask-in-place. That's w10 (45) — but w10's d/s1ang didn't swap because arg0 took $s0.

Hmm, in w10, arg0 took $s0 (crossed the call). What if I prevent that by making arg0 die before the call? The scheduler...

OK, let me try w31: w10 but with the pointer load's result assigned to a variable used immediately, forcing the schedule.

Actually, let me try a different structure: compute the pointer load LAST:
```
u5 = ratan2(*(s16*)(arg0+0xE) - D_80126CB8, D_80126CB4 - *(s16*)(arg0+6)) ...;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
```
This is w10. The scheduler hoisted the pointer load early anyway? Let me check w10's asm order. r72 crossed the call → the lw or an arg0 use is after the call.

Hmm.

Let me just accept the WALL. But let me make the WALL row accurate: best = 25 (w19, s16 d). Hmm, but w19 is structurally different (the div sign-extends each time). Is that a legitimate "lever-free body"? Yes, it's a real-C move (width change per C0505). The score is 25. So the best lever-free score is 25.

Hmm, wait. Actually, let me reconsider: the WALL result should be a body that's lever-free and scores the lowest. w19 qualifies. But the "wall" evidence should describe the mechanism: the pin reserves $s0; lever-free the block-local s1ang raw (2 refs/7, crosses the jal) takes $s0 in local-alloc, so d (global, conflicts $s0) can only take $s1. The mask-in-place (w6) makes the raw global and fixes d/s1ang but shifts u5→$v1 and iVar4→$a1 (an $a1 copy-preference on iVar4 from the d=arg1 copy chain) and loses the arg0 copy/schedule.

Actually, let me double check the u5/iVar4 shift cause. Hmm, I claimed the a1 preference. Let me verify: in w6, iVar4 prefers a1 and gets it. In the target, iVar4 has no preference and gets $v1. So the a1 preference is the cause. And the preference chain... I couldn't pin it down, but empirically it's there in all lever-free bodies and absent in the pinned one.

Hmm, actually, let me reconsider: maybe the a1 preference comes from `d = arg1` and expand_preferences through a copy I haven't found. In w0, the merge at insn 100 (iVar4 = u5 - u6) with REG_DEAD r77 (u6). u6's prefs: s0 (from the tie with s1ang). Hmm, so iVar4 should get s0. But it gets a1.

Let me actually look at the s0 preference on u6: "77 preferences: 16" (u6). Where from? u6 = (and s1ang 4095) with REG_DEAD s1ang (local). Hmm, set_preference(u6, and) → no. So how does u6 get s0?

OH. Maybe the preference is set by `combine_regs` in local-alloc? No, that's local-alloc, and the greg dump is after local-alloc. The preferences in global.c are computed in global_conflicts by scanning the RTL. The RTL at that point has local pseudos renumbered to hard regs (local-alloc ran). So the `and` insn is `(set r77 (and $s0 4095))` with REG_DEAD $s0? Then set_preference(r77, and) → src is an and, not a reg. Hmm.

But wait — if local-alloc assigned s1ang to $s0, the and becomes `(set u6 (and $s0 4095))`. The set_preference sees SET_SRC = and → returns. Hmm.

Unless the and is `(set u6 (and s1ang 4095))` where s1ang is still a pseudo? No, local-alloc renumbers.

Hmm, wait: the greg dump's "77 preferences: 16" — 16 = $s0. Where from? Maybe from `hard_reg_full_preferences` via expand_preferences: u6 merges with a dying src... the and's REG_DEAD is s1ang (now $s0, a hard reg, not an allocno) → skip.

I'm clearly misunderstanding the pipeline. Whatever.

Let me now write the WALL. But wait — the brief says "Budget 20-30 min wall per item; past 30 min stop and record a wall". I'm at ~50 min. I should wrap up.

Actually, let me reconsider whether w6 could be made to match by fixing the arg0 copy with a *different* move: what if I explicitly write `s32 v0 = arg0;` and use it, forcing the copy? The copy would be coalesced if possible. To prevent coalescing, the variable must be live across a call or conflict. Hmm.

Actually, here's a thought: the target's arg0 copy exists because the arg0 pseudo is tied with the pointer load (an in-place load `lw $2,32($2)`). What if I write the source so the pointer load is in-place by construction:
```
s32 p = *(s32 *)(arg0 + 0x20);
```
The pointer temp p and arg0... the lw is `lw p, 32(arg0)`. In-place requires p and arg0 in the same reg, which needs arg0 to die. The scheduler determines arg0's death point.

Hmm, what if I use a *cast* of arg0 to force... no.

OK, let me also try: w31 = w6 but with the s1ang load statement's pointer split into a separate statement placed last. And w32 = w6 with the u5 statement before the s1ang load but the pointer load kept first via a separate statement.

Let me just do 3 more tries and then wall.

w31: 
```
d = arg1;
p = *(s32 *)(arg0 + 0x20);
u5 = ...;
s1ang = *(s16 *)(p + 0x12);
do { d=(s16)d; s1ang &= 0xFFF; } while(0);
```
w32: same but with the cast do-while separate and the mask outside.

Let me write and score. Then write the WALL.

Actually, let me also reconsider: maybe I should try the "u5/iVar4" fix by declaring iVar4 as a different type or by changing the div structure. E.g., `if (iVar4 >= 0)` → the div. Hmm.

Let me do w31/w32 and one more (w33: w6 with `t` declared inside the arms).
