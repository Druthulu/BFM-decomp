---
ts: 2026-11-06T09:14:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fyPze5JlC2sertabaPrg
---
Keepalive-only: mine has flg in v0 and res in v1; target has flg in v1 and res in v0. Also one instruction count differs (78 vs 79) — the tail: mine `lui v0; lw v0; nop; beqz v0,624; move v1,zero; lui v1; addiu v1; 624: ...`. Target: `lui v1; lw v1; nop; beqz v1,628; move v0,zero; lui v0; addiu v0; 628:`. The extra insn in target: at [44] target has `li a0,11` in a delay slot vs mine... hmm, the insn count difference is elsewhere (the diff at 44: mine has beqz at 44 then something at 45 = li a0,11? Actually mine[45] must be li a0,11; target[46] is li a0,11 — offset shift).

The real issue: register assignment of flg vs res. Target: flg in v1, res in v0. Mine: flg in v0, res in v1. Both are caller-saved block-local-ish. Why the swap? Because the keepalive asm reads res, making res live to the end; local-alloc allocates in some order.

If I swap declaration order of `res` and `flg`, or change the order of the two statements (flg = D_801F84AC before res = 0), the qty order changes and maybe res gets v0. Real-C moves! Let me try:

```
flg = D_801F84AC;
res = 0;
if (flg != 0) { res = ...; }
```
or declare res after flg. Local-alloc priority: qty order by... refs/live length. Both die at end (res used by asm). Hmm.

Also, the `li a0,11` delay slot difference: mine[45] vs target[46] — an extra insn in target at [44:46] means target has `beqz v0, 5f4` + `li a0,11` in delay, while mine has `beqz v0,5ec` and then... mine lacks the li in the slot? Actually the diff says target has 1 extra line at 45. So target has one more insn there — maybe `li a0,11` appears twice or a move.

Let me dump both tails fully to see.
