---
ts: 2026-11-06T21:30:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0TxRqRPsTkSCWkuzEmnX
---
Item 2 done. Now item 3: header item, func_8012B8E4, kinds keepalive,pin. Header: src/shared/ov/func_8012B8E4.h. MATCH only if score 0 on every includer (tryinc.py k = 0..n-1).

I need to find the number of includers and use tryinc.py. Let me read .run/P40/T10/tryinc.py usage and the header orig.

The header body (orig.c) is the same as the current header (verified earlier — the header is the src). Let me check FRESH: diff orig.c against the current header. Earlier I read the header and it matched orig.c exactly? Let me diff.

Item 3 orig.c:
```
s32 func_8012B8E4(s32 arg0, s32 arg1) {
    register s32 d __asm__("$16");  // pin $16
    s32 s1ang;
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(*(s16 *)(arg0 + 0xE) - D_80126CB8, D_80126CB4 - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF;
    __asm__ __volatile__("" : : "r"(u5));  // keepalive
    d = (s16)d;
    u6 = s1ang & 0xFFF;
    if (u6 == u5) return 0;
    iVar4 = u5 - u6;
    if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
    if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
    if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
    else { q = iVar4 / d; if (q == 0) q = -1; }
    return q;
}
```

Target: let me read target.s.

First, let me check tryinc.py and the number of includers. The header is included by 141 includers (from the moves.md pattern "0 on 141/141 includers"). The grep earlier found many. Let me count: `grep -rl 'func_8012B8E4.h' src/ | wc -l`.

Note: this function is the sibling of func_8012BB3C mentioned in moves.md line 316: "keepalive,pin | func_8012BB3C | WALL lreg-qty-priority — C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor; residual extendhisi2 temp $v1 vs in-place $s0 (G27x)". That's a very similar function! func_8012BB3C is likely the same family. The crack there used do-while(0) on the div block to crack the $16 pin and a 2nd do-while to replace the keepalive. Residual remained (WALL). Our function func_8012B8E4 is similar (d pin $16, u5 keepalive, div q).

Let me look at the target and try similar moves: do-while(0) on the div block, do-while on the cast block.

Let me read target.s and count includers, and check tryinc.py usage.
