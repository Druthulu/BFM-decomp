/* func_8014462C — shared body (overlay slot 0x80128158, h_exact c5084991). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AD80(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
void func_8014462C(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0xCC);
    func_8012AD80((s32)a0);
    *(u16 *)(s1 + 8) = *(u16 *)(a0 + 6);
    *(u16 *)(s1 + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE);
    if (func_80128ED8(s1, a0 + 0xD0)) {
        func_80016714(s1, 0x38);
        func_8012C218(a0);
    }
}
