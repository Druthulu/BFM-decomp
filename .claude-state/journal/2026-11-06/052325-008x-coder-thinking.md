---
ts: 2026-11-06T12:23:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7Vx9iAMboIRLxTdZd0Ny
---
Now the levers in func_8017DEF0: barrier (empty asm), keepalive (asm with operands), pin (`register s32 zr __asm__("$0")`). We must remove all three and get score 0 with pure C moves.

Note the code body already has some notes: [3] uses zr for opaque copies, [4] empty asm barrier, [5] keepalive asm and memory barrier.

Prior shard walls say: for keepalive,pin types, "expand-void-return" was a common wall. But here it's void already... The function is `void func_8017DEF0(void)`.

Key challenge: pin zr ($0) → need an alternative to `n + zr` which is a `(plus rA (reg 0))` opaque copy. Alternative pure C: use `(s16)` sign-extend trick per func_8017E1AC note: `flag2 = (s16)flag;` gives addu. That's a launder though? No — launder is a specific kind (identity statements like `w = (w>>16<<16)|x`). Hmm, "launder" in the kinds means identity-op to obscure value. A cast `(s16)` narrows — in the movetable, "s16/u8 widths" are allowed real C moves. So `cnt = (s16)n;`? Hmm but n is s32 and values 1..3; (s16)n would produce sll/sra pair unless gcc knows range. Actually for a copy the extend gets optimized to addu if value range known... In func_8017E1AC they used `flag2 = (s16)flag;` where flag was u8 → sign extend then combine to addu. That's the RC-12 replacement discovered in P40 T10 lever-free. Great, that's exactly the technique.

Let me first get a baseline: copy the current def into orig.c and run dt.sh on it to see it scores 0 (current def). Actually the current def presumably scores 0 (it's banked?). Let me check: the def has pins etc. dt.sh with the full body would score 0. Let's verify baseline.

Also need orig.c per FRESH requirement. Let me extract the def. How do I extract the body? delever_search.py --try --body takes a file with the body (bare definition). Let me look at worked example .run/P40/T10/func_80181F4C/win.c to see the expected format.
