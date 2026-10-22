---
ts: 2026-10-22T00:04:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HD09daTFYw8G8rZji9Ms
---
Item: func_80184828, kind = launder. The launder:
```
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[...].f0;
            if (newval >= ...) {
                __asm__("" : "=r"(p) : "0"(p));  // launder
                s1 = 1;
                ...
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
So p = D_80195AF6 (a global array pointer) and the launder forces p into a register.

The target's corresponding code is in the else branch (the `D_801E4BBC != 1` path). Let me find the target's insns for that path. The target listing showed insns 49-... hmm, the listing I got was cut at 68. The `D_80195AF6` path would be further down. Let me get the rest of the target.

Let me look at the full target for this function.
