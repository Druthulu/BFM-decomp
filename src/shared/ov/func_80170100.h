/* func_80170100 — shared body (overlay slot 0x80128158, h_exact 9ff852f7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80171928(void *a0);
void func_80170100(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(s32 *)(a0 + 0x198) = 0;
        func_80171928(a0);
    }
}
