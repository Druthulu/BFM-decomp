/* func_8018C1E0 — shared body (overlay slot 0x80128158, h_exact 5fb4815c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 aF801848DC(void *) __asm__("func_801848DC");
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */
s32 func_8018C1E0(void *a0) {
    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 3) {
        return 0;
    }
    if (aF801848DC(a0) == 0) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 4;
    func_80178BF8();
    return (s32)func_80172710;
}
