/* func_8017E698 — shared body (overlay slot 0x80128158, h_exact 6cd03b3b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D1E28(void);
s32 func_8017E698(void *a0) {
    s32 *p = (s32 *)((u8 *)a0 + 0x28);
    *p = *p - 1;
    if (*p == -1) {
        func_800D1E28();
        (*(u8 *)((u8 *)a0 + 0x15))++;
    }
    return 0;
}
