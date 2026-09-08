/* func_80144A98 — shared body (overlay slot 0x80128158, h_exact 6109627b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
void func_80144A98(u8 *a0) {
    s32 v0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, 0);
        *(s16 *)(a0 + 0x2) = 1;
    }
}
