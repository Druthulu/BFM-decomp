/* func_80168EC4 — shared body (overlay slot 0x80128158, h_exact b7b15fe1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80168F40();
extern void func_800D22E4(s32 a0);
extern void func_80146C3C();
void func_80168EC4(s32 a0) {
    if (*(s32 *)(a0 + 0x1C) < 5) {
        func_80168F40();
        *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x6);
        *(u16 *)(a0 + 0x14) = *(u16 *)(a0 + 0xA);
        *(u16 *)(a0 + 0x18) = *(u16 *)(a0 + 0xE);
        func_800D22E4(a0);
        *(s32 *)(a0 + 0x1C) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}
