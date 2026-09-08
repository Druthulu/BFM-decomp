/* func_8016FBB8 — shared body (overlay slot 0x80128158, h_exact 714e5f8a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801719A4(int a0, int a1);
extern void func_80171B44(s32 *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016FC24();
void func_8016FBB8(s32 a0) {
    u8 *p;
    *(s16 *)(a0 + 0x136) = 2;
    p = *(u8 **)(a0 + 0x20);
    *(s16 *)(a0 + 0x132) = *(u16 *)(p + 0x12);
    p = *(u8 **)(a0 + 0x20);
    *(s16 *)(p + 0x12) = (*(u16 *)(p + 0x12) + 0x800) & 0xFFF;
    func_801719A4(a0, 1);
    func_80171B44((s32 *)a0);
    func_80171990((u8 *)a0);
    func_8016FC24(a0);
}
