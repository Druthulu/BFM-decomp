---
ts: 2026-11-06T12:52:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tuQXeBMW7m5MCVlGMNst
---
Baseline scores 0 on includer 0 (141 includers). Note: list.tsv said 120 but there are 141 includers (the count column may be stale). MATCH requires 0 on all 141.

Now I need to remove the keepalive and launder asm while keeping the pins.

Levers to remove:
1. `__asm__ ("" : : "r"(c36), "r"(dcount));` — keepalive (line ~99)
2. `__asm__ ("" : "=r"(decoy) : "r"(ba));` — launder out-only
3. `__asm__ ("" : : "r"(decoy));` — keepalive

Pins stay: dp $4, ba $5, dst $4.

The tail block:
```
{
    u16 *src = base;
    s32 dcount;
    s32 df;
    s32 decoy;
    s32 c36;
    u16 tv;
    register s32 *dp __asm__("$4");  // pin
    register u16 *ba __asm__("$5");  // pin
    dp = D_80127548;
    dcount = *dp;
    c36 = 0x24;
    __asm__ ("" : : "r"(c36), "r"(dcount));  // keepalive
    df = c36 - dcount;
    tmp = (df << 1) + df;
    tmp = tmp << 4;
    dp = dp + 1;
    ba = (u16 *)(tmp + (u8 *)dp);
    __asm__ ("" : "=r"(decoy) : "r"(ba));  // launder out-only
    __asm__ ("" : : "r"(decoy));  // keepalive
    {
        register u16 *dst __asm__("$4");  // pin
        dst = ba;
        do {
            tv = *src; src++;
            *dst = tv; dst++;
            tv = *src; src += 0x35;
            *dst = tv; dst++;
            iVar2++;
        } while (iVar2 < 0xc);
    }
}
```

What do these asm do?
- keepalive on c36/dcount: +refs to influence allocation (c36, dcount in specific regs?).
- launder out-only on decoy with "r"(ba): makes ba opaque (so `ba`'s value is "used" by an unknown output) and decoy is an uninitialized output; then keepalive(decoy) uses decoy so it's live. This keeps ba in $5 across? and decoy allocated.

Removing them lever-free: need real C that produces the same code.

Let me first score the naive removal and see the residual.

Note the body is the header file content itself (the whole file: extern decls + function). The `--body` flag expects the function definition only... The item dir has `tu` = the header path. tryinc.py passes $(cat tu) as the file and --body. Hmm, but the header contains extern declarations too. It worked (score 0) so the tool accepts it as a "body"? Interesting — it took the header file as the body text. OK, so I edit a copy of the header as the candidate body.

Let me create orig.c = copy of the header, then c1 = orig without the three asm lines.

Wait: FRESH says copy the def to <dir>/orig.c. The header's def includes the extern decls at the top (they're part of the file). I'll use the whole file as the body (since that's what scored 0).

Let me do it.
