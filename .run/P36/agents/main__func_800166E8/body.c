void func_800166E8(void *a0, int a1) {
    u8 *p = a0;

    /* `int`, not the `s32` typedef: `a1-- != 0` is folded to `--a1 != -1` (fold-const.c:4399) only when the
     * decrement is not wrapped in a type conversion, and the s32 typedef variant gets one against the literal. */
    while (a1-- != 0) {
        *p++ = 0;
    }
}
