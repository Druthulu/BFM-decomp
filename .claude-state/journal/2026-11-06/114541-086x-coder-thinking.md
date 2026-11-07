---
ts: 2026-11-06T18:45:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WAVNeZHkf0fBUOw6i0wq
---
Item 1 done. Now item 2: the header item (func_80146750, pin $7, src/shared/ov/func_80146750.h). Header item: MATCH only if score 0 on every includer (tryinc.py k=0..n-1).

Let me look at tryinc.py usage and find the includers.

The function:
```
unsigned short *func_80146750(unsigned short *a0)
{
    int a6;
    register unsigned short *a7 __asm__("7");  // pin
    int a5;
    unsigned short *v1;
    unsigned short *v0;
    a6 = 0x8;
    a7 = &D_8011FD10;
    v1 = a7;
    a5 = 0x340;
    do {
        v0 = v1;
        if (*v0 != 0) {
            a7 = (unsigned short *)((char *)a7 + 0x68);
            v1 = (unsigned short *)((char *)v1 + 0x68);
            a6 = a6 + 1;
            a5 = a5 + 0x68;
        } else {
            ... stores ...
            return a7;
        }
    } while (a6 < 0x14);
    return (unsigned short *)0;
}
```

Target: a3 = &D_8011FD10; v1 = a3; loop: v0 = v1 (lhu v0,0(v1)); if nonzero: a3 += 0x68; v1 += 0x68; a2++; a1 += 0x68; loop. Else: stores; return v0 = a3.

The pin is a7 = $7. Lever-free: `unsigned short *a7;` — then a7 and v1 are equal pointers kept in two registers. cse will merge them (cse-copy-merge/cse-copy-canonical). Let me test the direct removal first.

First, check the FRESH: orig.c vs src header lines 10-40 — identical (read earlier).

Then tryinc.py: `.run/P40/T10/tryinc.py <k> <header> <fn> <body>`. Let me look at its usage.
