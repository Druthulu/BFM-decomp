/* func_8017CAB4 — shared body (overlay slot 0x80128158, h_exact efc4ec9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
void func_8017CAB4(s32 a0) {
    s32 v0;
    s32 *s0_ptr;
    u16 sp[8];
    s0_ptr = *(s32 **)(a0 + 0xDC);
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        return;
    }
    func_8001C214(v0, s0_ptr[1]);
    func_8012A828(a0, (void *)s0_ptr[2]);
    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0x58) = 0;
    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 0);
    func_800D23D0(&sp[4]);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = sp[5] + 0x800;
    *(u16 *)(a0 + 0x2) += 1;
}
