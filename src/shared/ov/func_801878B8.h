/* func_801878B8 — shared body (overlay slot 0x80128158, h_exact e765f85a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_801C700C[])(void);
extern void func_80049CAC(s32 a0, s32 a1);
void func_801878B8(void *a0) {
    D_801C700C[*(u16 *)(a0 + 2)]();
    if (*(u16 *)a0 != 0) {
        if ((*(s16 *)(a0 + 0x70)) == 0 || (*(s16 *)(a0 + 0x70)) == 7) {
            func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        }
        if ((*(s16 *)(a0 + 0x70)) == 0xF) {
            func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        }
        func_8012B260((u8 *)a0);
    }
}
