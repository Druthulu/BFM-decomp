---
ts: 2026-11-06T09:56:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7JbejbkPd1dwkFlMfWX0
---
All four orig bodies match (with levers). Now I need lever-free bodies that also score 0.

Let me start with the three clones. Their body is:
```c
void func_80182420(a0, a1)
s32 a0;
s32 a1;
{
    extern s32 D_801E1BCC[];
    register s32 rv __asm__("$2");  // pin
    s32 x = D_801E1BCC[0];
    s32 y = a1;
    s32 d;

    if (y < a0) {
        if (x < y) {
            x = x + 0x5A0;
        }
        y = y + 0x5A0;
    }
    if (a0 >= x) {
        rv = -1;
        goto done;
    }
    if (x >= y) {
        rv = -1;
        goto done;
    }
    d = x - a0;
    if (d < 16) {
        rv = d * 2;
        goto done;
    }
    d = y - x;
    if (d < 16) {
        rv = d * 2;
        goto done;
    }
    rv = 31;
done:
    __asm__("" :: "r"(rv));  // keepalive
}
```

Lever-free: `s32 rv;` and no asm. Let me try that first — nopin.c.

Note: the function returns void (implicit? K&R definition with no return type → int? `void func_80182420(a0,a1)` — yes void). So rv is just a local assigned and never used → flow will delete all `rv = ...` stores! That's the problem: with the keepalive removed, `rv` is dead. The target keeps the value in v0 (because in the real game the function probably returned it? But signature is void and callers cast to s32(*)(s32,s32) and use return value!). So the real function returns s32, but the TU declares void. Hmm.

Wait the target: 26 instructions. Let me dump target func_80182420 to see.
