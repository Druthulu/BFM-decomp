s32 func_80182058(void *a0)
{

    extern s16 D_801EEAF0;
    extern s16 D_801EEAF2;
    void *p;
    u16 st;

    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        /* LOAD-BEARING zero-byte cross-jump barrier (cookbook §5a).
         * Without it gcc's find_cross_jump merges this `move v0,0; j epi`
         * tail with the identical case-2 failure tail -> 58 ins instead of
         * 60, and the case-2 `beq` then loses its delay-slot fill. */
        return 0;
    }

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801EEAF0 = st;
        D_801EEAF2 = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}
