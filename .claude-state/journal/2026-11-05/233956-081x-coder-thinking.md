---
ts: 2026-11-06T06:39:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VFn5u7DHHGzmZspP9WJv
---
v_self still has the whole v0/v1 swap: t (the middle value) is in v1 in mine. So the self-load didn't change the middle block's allocation.

The middle block: t = unkA; t -= 0x30; compare; t = ptr; t |= ...; store.

In mine, t is v1 and the compare temp is v0.

Why is t v1? Because t (r73) conflicts with v0. In v_self, t is still the same pseudo (it's used for the load too), so still conflicts with v0.

To remove the conflict, t must not be live where $2 is live. The conflict comes from the tail self-load (t = D_801D0A3C[t]) where the dest is... in v_self, the dest IS t, so the conflict should be gone for that insn. But the pseudo t is still the same one; the conflict may come from the earlier part.

Hmm, let me check whether the conflict remains in v_self. Hmm.

Time check: I'm at ~23:50. Item 3 started ~23:35. That's 15 min. I need 30 tries for a WALL; I have ~4+21+1 = 26 scored tries (including compile errors? no, those don't count). Let me count actual scored: base 17, s16t 12, u32t, u16t, split, split2, direct, direct2, or1, or2, arm1, ord1, ord2, ord3(?), dw, dw2, fc1, fc2, st1, st2, x2, self = ~21 + the first lever-free = 22. Need ~8 more.

Let me try a few more targeted ideas and then finish:
1. Make t NOT conflict by shortening its live range: use a separate variable for the tail (split) — tried (16).
2. Try `s32 t` + tail direct call (direct, 16).
3. Combine split + direct.
4. Try the middle with a second variable.

Actually — an important observation: maybe the conflict isn't from the tail at all. Let me check the conflicts of r73 in the base candidate: "conflicts v0,sp". In the .lreg, t is live at the start of block 4 and the call is in block 4.

Hmm, what if the conflict comes from the *first* block (unkFC)? No, t isn't used there.

Let me look at block 4's RTL precisely. The function section starts at 20545; let me print the RTL for insns in block 4 (63-98).

Let me get the exact section and look at the tail insns.
