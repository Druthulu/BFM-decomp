void func_80145934(void) {

    extern u8 D_8018C944;
    extern u8 D_8018C8B4;
    extern u8 D_8018C890;
    extern u8 D_8018C86C;
    extern u8 D_8018C920;
    extern u8 D_8018C8FC;
    extern u8 D_8018C8D8;
    extern u8 D_8018C848;
    /* §5a cross-jump alias (replaces the memory barrier that used to sit in the >=0x6A4 arm).
     * Both the >=0x6A4 and the >=0x384 arm take the address of D_8018C944, so their blocks are the
     * identical pair `la a0,D_8018C944 / j <call>` and jump2's cross-jumper merges them (jump.c:1969).
     * find_cross_jump compares the two SYMBOL_REFs with rtx_renumbered_equal_p, which tests the name
     * STRING POINTERS (jump.c:2440 `case SYMBOL_REF: return XSTR (x, 0) == XSTR (y, 0);`), so a second
     * declaration of the same symbol under its own asm label gives the first arm a distinct string and
     * the two blocks stay separate.  Same bytes, same R_MIPS_HI16/LO16 D_8018C944 relocations. */
    extern u8 aD8018C944 __asm__("D_8018C944");
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &aD8018C944;
    } else if (v >= 0x5DC) {
        p = &D_8018C8B4;
    } else if (v >= 0x578) {
        p = &D_8018C890;
    } else if (v >= 0x514) {
        p = &D_8018C86C;
    } else if (v >= 0x384) {
        p = &D_8018C944;
    } else if (v >= 0x258) {
        p = &D_8018C920;
    } else if (v >= 0xC8) {
        p = &D_8018C8FC;
    } else if (v >= 0xA) {
        p = &D_8018C8D8;
    } else {
        p = &D_8018C848;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
