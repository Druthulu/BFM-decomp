/* func_80183604 — shared body (overlay slot 0x80128158, h_exact 79e7b5c8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);
s32 func_80183604(s32 param_1) {
    s32 obj = param_1;
    s32 ptr;
    s32 ptr2;
    s32 result;
    do { ptr = *(s32 *)((char *)obj + 0x64); } while (0);
    if (*(u16 *)((char *)ptr + 0x2) != 6) {
        return 0;
    }
    result = func_8012BD14(ptr);
    if (result >= 0x2401) {
        return 0;
    }
    ptr2 = *(s32 *)((char *)obj + 0x64);
    *(u16 *)((char *)ptr2 + 0x2) = 0xB;
    func_80178BF8();
    return (s32)func_80172710;
}
