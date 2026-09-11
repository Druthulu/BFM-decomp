s32 func_801836D4(void *a0, void *a1) {
    s16 buf[16];                        /* dead-store scratch: forces frame 0x28 */
    register u16 b __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 a;
    s16 diff;
    s16 v1;
    register s32 tw __asm__("$2");      /* SImode -> lh */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s16 t16;     /* HImode copy of tw -> addu $a1,$v0,$0 */
    s16 xr;      /* xor result back in $v0 */

    if (*(s16 *)((s32)a0 + 0xEA) != 0) {
        *(s16 *)((s32)a0 + 0xEA) = *(s16 *)((s32)a0 + 0xEA) - 1;
    }

    v1 = *(s16 *)((s32)a0 + 0xE2);
    switch (v1) {
    case 0:
        a = *(u16 *)((s32)a0 + 0xE4);
        b = *(u16 *)((s32)a1 + 0x6);
        diff = a - b;
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        break;
    case 1:
        a = *(u16 *)((s32)a0 + 0xE6);
        b = *(u16 *)((s32)a1 + 0xA);
        diff = a - b;
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
        break;
    case 2:
        a = *(u16 *)((s32)a0 + 0xE8);
        b = *(u16 *)((s32)a1 + 0xE);
        diff = a - b;
        buf[2] = diff;
        tw = *(s16 *)((s32)a0 + 0xF0);
        break;
    default:
        goto default_case;
    }

    if (tw == 0) goto ret1;
    t16 = tw;
    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;

default_case:
    return *(s16 *)((s32)a0 + 0xEA) == 0;
}
