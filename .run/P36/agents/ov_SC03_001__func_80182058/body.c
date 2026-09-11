s32 func_80182058(void *a0)
{

    extern s16 D_801EEAF0;
    extern s16 D_801EEAF2;
    void *p;
    u16 st;

    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        return 0;
    }

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) == 1) {
            goto hit;
        }
        goto fail;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            goto fail;
        }
    hit:
        D_801EEAF0 = st;
        D_801EEAF2 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
    fail:   /* the case-2/case-4 failures share this one `return 0`: a return
             * falling out of a conditional (as the first one does) is what
             * jump2's cross-jump would merge the early return into */
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}
