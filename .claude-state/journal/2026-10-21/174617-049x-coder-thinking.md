---
ts: 2026-10-21T23:46:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_F1YVpRiI0fWuWmu8Xc36
---
Identical shape at the top (insns 0-15). Same move should work. Let me write the candidate: remove the launders, keep p0/p1 (or drop p0), and add the dead-reset.

For 801815D4, the order is: p0 = sp10; p1 = sp10+4; then the three zero stores; then launders; then calls.

Candidate:
```
    p0 = sp10;
    p1 = sp10 + 4;
    sp10[2] = 0;
    sp10[1] = 0;
    sp10[0] = 0;
    func_800D20C0(p0, p1, 1);
    p1 = 0;
    func_800D23D0(sp10 + 4);
```

Hmm, but p0 = sp10: is p0 used once? Yes, in call1. So gcc computes a0 = sp+16 directly. But wait: p0's value (symbol_ref sp10) and p1's value (plus (symbol_ref sp10)(const 8)) — cse might unify p0 and... no, different expressions. But find_best_addr might turn the MEM accesses (sp10[2], etc.) into (mem (reg)) with a register holding sp+16! Hmm — in the target, the stores are `sh zero,20(sp)` — direct sp-relative, so no register. OK.

Hmm, but note in the target: `addiu a0,sp,16` — the first call's a0. If p0 is a variable used once, gcc computes it directly → `addiu a0,sp,16` ✓.

Let me write it and score. Let me also keep p0 to minimize changes... Actually, in item 80180D54, I dropped p0 entirely (used `sp10` directly) and it worked. Let me do the same here for consistency: use `sp10` for a0.

Hmm, but for 80180D54 the u1 kept `p1` only. Let me mirror: keep p1 only.

For 801815D4:
```
    u16 sp10[6];
    u16 *p1;
    s16 mask;
    s16 i;
    u8 *p;

    sp10[2] = 0;
    sp10[1] = 0;
    sp10[0] = 0;
    p1 = sp10 + 4;
    func_800D20C0(sp10, p1, 1);
    p1 = 0;
    func_800D23D0(sp10 + 4);
    D_801C7540 = sp10[5] - 0x400;
    ...
```
Note: in the orig, p0/p1 are assigned BEFORE the three stores. The statement order might matter for scheduling. Let me keep the original order (p0 = sp10; p1 = sp10 + 4; then stores) to be safe, but with p0 dropped:

```
    p1 = sp10 + 4;
    sp10[2] = 0;
    sp10[1] = 0;
    sp10[0] = 0;
    func_800D20C0(sp10, p1, 1);
    p1 = 0;
    func_800D23D0(sp10 + 4);
```
Let me write that.
