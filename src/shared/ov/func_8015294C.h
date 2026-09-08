/* func_8015294C — shared body (overlay slot 0x80128158, h_exact cf34981a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800B99DA;
extern void func_80149020(s32 *a0);
extern void func_801470B4(s32 a0);
extern void func_801470AC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern s32 func_801472C8(struct S *a0);
extern void func_8015369C(s32 a0);
extern void func_80146CA0(void *a0);
void func_8015294C(s32 a0) {
    s32 s0 = a0;
    func_80149020((s32 *)s0);
    if (D_800B99DA & 1) {
        func_801470B4(s0);
    } else {
        func_801470AC((s32 *)s0);
    }
    func_80147A84(s0);
    func_801473EC((s32 *)s0);
    func_80148038(s0, 0x18000);
    func_80147460(s0);
    {
        u8 v = *(u8 *)(s0 + 0xDE);
        *(u8 *)(s0 + 0xDE) = v + 0xFF;
        if (v == 0) {
            *(u8 *)(s0 + 0xDE) = 0x10;
            func_801472C8((s32 *)s0);
            func_801470B4(s0);
            func_8015369C(s0);
            func_80146CA0((void *)s0);
        }
    }
}
