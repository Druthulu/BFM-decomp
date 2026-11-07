---
ts: 2026-11-06T12:06:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_co7fOx1ZHvna2dZxeDOp
---
MATCH! k14 = score 0, 158 insns, lever-free (no barriers, no launders, no pins). 

Wait — k14 derives from k3 which removed va/vb entirely (inlined `(u8*)&f.cx`). So the lever-free body: no barriers, no launders, no pins. Let me verify no asm remains and no pins.

Let me check k14 content for "asm" and "register".

Then: MATCH, win.c = k14. Verify score 0 again with dt.sh, and verify the kinds are gone.

Let me also double-check the body is valid C and semantically identical (inlining &f.cx in both call args is identical since va and vb were both &f.cx).

Actually careful: originally `va = (u8*)&f.cx; ... vb = va;` and the call passes (va, vb) — both equal &f.cx. And later `func_800D20C0(&f.cx, ...)`. Fine.

Also the k11 change moved `p = D_800CB820; i = 0;` after the call — semantically fine (p and i used only in the do-loop after).

Let me verify and then bank.

Check for asm/register in k14.
