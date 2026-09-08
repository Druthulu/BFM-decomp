/* func_8017EBC8 — shared body (overlay slot 0x80128158, h_exact d0406d9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80171928(void *a0);
void func_8017EBC8(u8 *a0) {
    if ((*(u16 *)(a0 + 0xB8) & 0x8000) == 0) {
        return;
    }
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(s32 *)(a0 + 0x198) = 0;
        func_80171928(a0);
    }
}
