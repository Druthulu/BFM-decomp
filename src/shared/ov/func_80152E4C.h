/* func_80152E4C — shared body (overlay slot 0x80128158, h_exact 01abd849). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80153B58(s32 *a0);
extern void func_80147A84(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern s32 func_801472C8(struct S *a0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80146CA0(void *a0);
void func_80152E4C(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    func_80149020((s32 *)s0);
    func_80153B58((s32 *)s0);
    func_80147A84(s0);
    func_801473EC((s32 *)s0);
    v0 = *(u8 *)(s0 + 0xDF);
    if (v0 == 0) {
        func_80148038(s0, 0x18000);
    } else {
        *(u8 *)(s0 + 0xDF) = v0 - 1;
    }
    func_80147460(s0);
    {
        u8 dv = *(u8 *)(s0 + 0xDE);
        *(u8 *)(s0 + 0xDE) = dv + 0xFF;
        if (dv != 0) return;
    }
    {
        *(u8 *)(s0 + 0xDE) = 0x10;
        func_801472C8(s0);
        func_801470B4(s0);
        func_8015369C(s0);
        func_80146CA0((void *)s0);
    }
}
