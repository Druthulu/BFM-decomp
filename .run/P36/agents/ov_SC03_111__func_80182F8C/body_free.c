void func_80182F8C(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 0x11) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) < 0) {
        { s32 *q; q = *(s32 **)(a0 + 0x20);  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus8)
          q[1] = q[1] | 0x80000000; }
    } else {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) =
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) & 0x7FFFFFFF;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x14);

    {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 3;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_80047948(ang2) >> 3;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        gte_SetRotMatrix((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        gte_SetTransMatrix((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
    { s32 pad[2]; }   /* LEVER 1: frame pad -- matches func_80186B78's byte-verified 8-byte
                         trailing dead local (docs/matching-cookbook.md §136 L6). */
}
