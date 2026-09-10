/* func_80145934 — shared body (overlay slot 0x80128158, h_exact 1b5f376e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145934(void) {
    /* §5a cross-jump alias (replaces the memory barrier that used to sit in the >=0x6A4 arm).
     * Both the >=0x6A4 and the >=0x384 arm take the address of D_80180FFC, so their blocks are the
     * identical pair `la a0,D_80180FFC / j <call>` and jump2's cross-jumper merges them (jump.c:1969).
     * find_cross_jump compares the two SYMBOL_REFs with rtx_renumbered_equal_p, which tests the name
     * STRING POINTERS (jump.c:2440 `case SYMBOL_REF: return XSTR (x, 0) == XSTR (y, 0);`), so a second
     * declaration of the same symbol under its own asm label gives the first arm a distinct string and
     * the two blocks stay separate.  Same bytes, same R_MIPS_HI16/LO16 D_80180FFC relocations. */
    extern u8 aD80192964 __asm__("D_80180FFC");
    s32 v;
    void *p;

    v = func_80029504();
    if (v >= 0x6A4) {
        p = &aD80192964;
    } else if (v >= 0x5DC) {
        p = &D_80180F6C;
    } else if (v >= 0x578) {
        p = &D_80180F48;
    } else if (v >= 0x514) {
        p = &D_80180F24;
    } else if (v >= 0x384) {
        p = &D_80180FFC;
    } else if (v >= 0x258) {
        p = &D_80180FD8;
    } else if (v >= 0xC8) {
        p = &D_80180FB4;
    } else if (v >= 0xA) {
        p = &D_80180F90;
    } else {
        p = &D_80180F00;
    }
    ((void (*)(void *))func_800D185C)(p);
    func_80145B24();
}
