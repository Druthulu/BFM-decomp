/* func_80160FE0 — shared body (overlay slot 0x80128158, h_exact c953e0b9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80146CA0(void *a0);
void func_80160FE0(s32 *a0) {
    s32 *s0 = a0;
    func_80149020(a0);
    if (func_801399F0(*(s32 *)((u8 *)s0 + 0x198)) != 0) {
        func_80139914(*(s32 *)((u8 *)s0 + 0x198));
        *(s32 *)((u8 *)s0 + 0x198) = 0;
        func_80146CA0(s0);
    }
}
