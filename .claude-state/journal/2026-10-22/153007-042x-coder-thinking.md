---
ts: 2026-10-22T21:30:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZIs8jbXzibw1oeq8IcLI
---
Item 3 (func_801495C4): orig.c is lines 6-26 of the header (21 lines), asm on lines 13 and 14 of that excerpt.

The body:
```
void func_801495C4(s32 a0, s32 a1) {
    s16 in[4];
    s16 result[4];
    s16 buf[4];
    s16 *pin;
    s16 *m1;
    s16 *m2;
    s32 mtx;
    in[0] = *(u16 *)(a1 + 0x2);
    in[1] = *(u16 *)(a1 + 0x6);
    in[2] = *(u16 *)(a1 + 0xA);
    pin = in;                  
    mtx = *(s32 *)(a0 + 0x20); __asm__(...);
    m1 = buf;                  __asm__(...);
    call(mtx + 0x34, pin, m1);
    m2 = buf;                  
    call2(m2, result);
    *(s16 *)(a1 + 0x2) = result[0];
    ...
}
```
Same structure as item 2! So the same fix: drop both launders + dead-reset `m1 = 0;` after the first call.

Wait, but in this one, `pin = in` has no launder, and the target already matched with it. Also there's a trailing-space line for pin/m2 (the "pin" name suggests these were pins originally).

Let me apply: remove the two asm, add `m1 = 0;` after the call. Test.
