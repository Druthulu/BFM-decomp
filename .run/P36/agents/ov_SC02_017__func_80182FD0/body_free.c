void func_80182FD0(int param)
{
    u32 buf[3];
    u8 *s0;
    int v0;
    int x;
    int lim;

    s0 = ((u8 **)D_8018E8DC)[*(s16 *)(param + 0xFC)];

    /* gte_SetRotMatrix(&D_800AF648); gte_SetTransMatrix(&D_800AF648); */
    __asm__ volatile(
        "lui $2,%%hi(D_800AF648);addiu $2,$2,%%lo(D_800AF648);"
        "lw $12,0($2);lw $13,4($2);ctc2 $12,$0;ctc2 $13,$1;"
        "lw $12,8($2);lw $13,12($2);lw $14,16($2);"
        "ctc2 $12,$2;ctc2 $13,$3;ctc2 $14,$4;"
        "lw $12,20($2);lw $13,24($2);ctc2 $12,$5;"
        "lw $14,28($2);ctc2 $13,$6;ctc2 $14,$7"
        : : : "$12", "$13", "$14", "$2", "memory");

    func_80015978(param + 4, (s32 *)buf);

    /* gte_ldv0(buf); gte_rtps(); gte_stsxy(buf); */
    __asm__ volatile("lwc2 $0,0(%0);lwc2 $1,4(%0);nop;nop;rtps;swc2 $14,0(%0)"
                     : : "r"(buf) : "memory");
    /* gte_stflg(&buf[2]); */
    gte_stflg(buf + 2);

    lim = (D_800AF7BC >> 1) + 0x20;
    x = (int)(s16)buf[0];
    if (x <= -lim) goto done;
    if (x >= lim) goto done;

    lim = (D_800AF7BE >> 1) + 0x20;
    x = (int)(s16)((s16 *)buf)[1];
    if (x <= -lim) goto done;
    if (x >= lim) goto done;

    if ((int)buf[2] < 0) goto done;

    v0 = *(s32 *)(param + 0x1C);
    if (v0 != 0) { v0--; goto store; }

    if (*(s16 *)(s0 + 6) != 0xFF) {
        do {
            func_80183168((u8 *)param, s0);
            s0 += 8;
        } while (*(s16 *)(s0 + 6) != 0xFF);
    }
    v0 = *(s32 *)(param + 0xDC);
    *(s32 *)(param + 0x1C) = v0;
    v0 = *(volatile s32 *)(param + 0x1C);
    v0--;
store:
    *(s32 *)(param + 0x1C) = v0;
done:
    func_801831FC(param);
}
