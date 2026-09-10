void func_80145934(void) {
    /* §5a cross-jump alias (replaces the memory barrier that used to sit in the >=0x6A4 arm).
     * Both the >=0x6A4 and the >=0x384 arm take the address of D_80192964, so their blocks are the
     * identical pair `la a0,D_80192964 / j <call>` and jump2's cross-jumper merges them (jump.c:1969).
     * find_cross_jump compares the two SYMBOL_REFs with rtx_renumbered_equal_p, which tests the name
     * STRING POINTERS (jump.c:2440 `case SYMBOL_REF: return XSTR (x, 0) == XSTR (y, 0);`), so a second
     * declaration of the same symbol under its own asm label gives the first arm a distinct string and
     * the two blocks stay separate.  Same bytes, same R_MIPS_HI16/LO16 D_80192964 relocations. */
    extern u8 aD80192964 __asm__("D_80192964");
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &aD80192964;
    } else if (v >= 0x5DC) {
        p = &D_801928D4;
    } else if (v >= 0x578) {
        p = &D_801928B0;
    } else if (v >= 0x514) {
        p = &D_8019288C;
    } else if (v >= 0x384) {
        p = &D_80192964;
    } else if (v >= 0x258) {
        p = &D_80192940;
    } else if (v >= 0xC8) {
        p = &D_8019291C;
    } else if (v >= 0xA) {
        p = &D_801928F8;
    } else {
        p = &D_80192868;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
