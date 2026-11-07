---
ts: 2026-11-06T21:06:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eC3ZRzzxbAZLEZsiu1XX
---
I see the calls in block 5: `call_insn 63 61 65` — wait, insn 63 is a call at the START of block 5 (first insn 61). Hmm, that's the func_80146CA0 call? And the third if's t block is insns 67..80 (after the call!). Interesting: so the func_80146CA0 call (insn 63) happens BEFORE the t computation in block 5? That's the source order: `if (*(s16*)(s1+0x1a) < 0) { ...; func_80146CA0(a0); }` — no wait.

Hold on, let me map: in the source, the third block is:
```
t = *(u16*)(s1+0x1a);
t -= 0x100;
*(s16*)(s1+0x1a) = t;
*(s16*)(s1+0x18) = t;
if (*(s16*)(s1+0x1a) < 0) {
    unk60 = 0;
    *(s16*)(s1+0x1a) = 0;
    *(s16*)(s1+0x18) = 0;
    func_80146CA0(a0);
}
```
So t is used before the inner if; the call is after. In the RTL, block 5 = the third block (insns 61..80), and the call is insn 63? That doesn't fit. Unless block 5 is the block containing the call and the t computation, and the call at insn 63 is *before* insn 67 (t's load). Hmm — the call at 63 could be the `jal func_80146E98`? No, that's block 0.

Wait — actually, block 5's first insn is 61. The call_insn 63 61 65: the previous insn is 61, next 65. Then t's load at 67. So a call occurs at insn 63, before t's computation in the same block. Which call? Let me look at it. Maybe it's the func_80146CA0 call from a *previous* structure? Hmm, but the source has the call inside the inner if, after the stores.

Wait, maybe block 5 is the *inner if body* and the t computation is in block 5 too? Let me just print insns 55-100 of the .greg.
