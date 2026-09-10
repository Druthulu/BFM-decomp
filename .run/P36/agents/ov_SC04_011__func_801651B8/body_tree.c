void func_801651B8(void * param_1)
{
    register s32 *puVar1 __asm__("$16"); /* $s0 */  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 iVar2;   /* $s1 */
    s32 p;        /* $s2 */

    p = param_1;
    ((s32 (*)(s32, s32, s32))func_80165240)(p, p + 0x2c, p + 0x50);
    iVar2 = 0;
    puVar1 = &D_801EDCA8;
    do {
        if (puVar1[3] != 0) {
            s32 a0v = p;
            __asm__ __volatile__("" : "=r"(a0v) : "0"(a0v));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            ((s32 (*)(s32, s32, s32))func_80165240)(a0v, (s32)puVar1, (s32)(puVar1 + 2));
            puVar1[3] = puVar1[3] + -1;
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 4;
    } while (iVar2 < 8);
}
