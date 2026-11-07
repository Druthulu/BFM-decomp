---
ts: 2026-11-06T22:38:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8GzzrPdjoCCagNBVPSpn
---
g1 "mask in place": `s1ang = s1ang & 0xFFF;` — reassign s1ang to its own mask, eliminating the u6 variable. This makes s1ang a *global* pseudo (because it's reassigned and used across blocks) with 4 refs.

For our function, if we do `s1ang = s1ang & 0xFFF;` then s1ang is used in the compare and arms. Its priority would rise. But d's priority is 10000 (vs s1ang's ~?). Let me compute: s1ang with 4 refs (def load, def mask, uses...) and live ~13 → floor_log2(4)*4/13*10000 = 2*4/13*10000 = 6153. d = 10000. So d should win $s0! Then s1ang takes $s1 (if no conflict). 

Let me test g1-style for our function. But note the sibling's win.c is a PARTIAL? Their result was WALL (best 21). Their g1 gave s1ang $s0 (pri 6363 > d 5185). For us, d=10000 > s1ang~6153, so d wins.

But there's the register numbering: with `s1ang = s1ang & 0xFFF`, there's no separate u6. The target has u6 as a separate pseudo? In the target, `andi $17,$17,0x0fff` writes $17 in place (same reg as s1ang). So the masked value is in s1ang's reg. If s1ang is reassigned, that's in-place.

Hmm, but in our function the pinned target: r77 (u6) is a separate global pseudo, and r75 (s1ang raw) is local, and they share $s1 via the preference. If we reassign s1ang (mask in place), we'd have one pseudo. The register assignment might differ.

Let me just test it. Candidate w6 = g1 style for our function:
```
s32 func_8012B8E4(s32 arg0, s32 arg1) {
    s32 d;
    s32 s1ang;
    s32 u5; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(...) - 0x400) & 0xFFF;
    do { d = (s16)d; } while (0);
    s1ang = s1ang & 0xFFF;
    if (s1ang == u5) return 0;
    iVar4 = u5 - s1ang;
    if (iVar4 > 0x800) { t = s1ang + 0x1000; iVar4 = u5 - t; }
    if (iVar4 < -0x800) { t = s1ang - 0x1000; iVar4 = u5 - t; }
    if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
    else { q = iVar4 / d; if (q == 0) q = -1; }
    return q;
}
```
Wait, but the original keeps the u6 variable for the arms. Using s1ang after reassignment is semantically the same. Let me test.

Note: the do-while on the cast (keepalive replacement) is needed for the sll scheduling. Keep it.

Let me write w6 and score + dump.
