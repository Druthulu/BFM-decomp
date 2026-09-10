s32 func_801852E4(s32 p) {

    extern s32 D_80126B9C;
    extern u8 D_801BD0BC[];
    s32 buf10[2];
    register s32 r __asm__("$2");   /* $v0 — see note 2 above */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    if ((*(u32 *)(p + 0xE0) & 1) == 0) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 1) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 0xD) {
        return 0;
    }
    if ((D_80126B9C & 2) == 0) {
        return 0;
    }
    if (0x10000 < func_8012BCCC(p)) {
        return 0;
    }
    r = func_80187460(p, 0x380);
    if (r == 0) {
        return r;
    }
    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801BD0BC, buf10);
    if (func_80187318(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0) {
        goto store;
    }
ret0:
    return 0;
store:
    *(u16 *)(p + 2) = 0xC;
    return 1;
}
