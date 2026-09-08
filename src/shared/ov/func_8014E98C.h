/* func_8014E98C — shared body (overlay slot 0x80128158, h_exact 3abe6ffe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3);
s32 func_8014E98C(void *a0) {
    s16 buf1[3];
    s16 buf2[4];
    s32 acc;
    s32 i;
    acc = 0;
    i = 2;
    if ((*(s32 *)((u8 *)a0 + 0x44) & 0x80000) == 0) {
        if ((*(s32 *)((u8 *)a0 + 0x1F8) & 0x4000000) == 0) {
            do {
                buf1[0] = *(u16 *)((u8 *)a0 + 0x88);
                i -= 1;
                buf1[1] = *(u16 *)((u8 *)a0 + 0x8A) - 0x10;
                buf1[2] = *(u16 *)((u8 *)a0 + 0x8C);
                buf2[0] = *(u16 *)((u8 *)a0 + 0x6);
                buf2[1] = *(u16 *)((u8 *)a0 + 0xA) - 0x10;
                buf2[2] = *(u16 *)((u8 *)a0 + 0xE);
                acc = acc | func_8014EA4C(a0, buf1, buf2, i);
            } while (i != 0);
        }
    }
    return acc;
}
