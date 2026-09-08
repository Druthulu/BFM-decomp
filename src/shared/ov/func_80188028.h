/* func_80188028 — shared body (overlay slot 0x80128158, h_exact 87fb1964). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 func_80143970(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_80192D94;
extern u16 D_80194294;
extern u8 D_801A7164;
extern u16 D_800B99DC;
void func_80188028(s32 a0) {
    s32 v0;
    s32 v1;
    volatile u16 *p;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    v1 = v0;
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    if (*(s16 *)(a0 + 0x70) == 0) {
        func_8001C214(v0, (s32)&D_80192D94);
    } else {
        func_8001C214(v1, (s32)&D_80194294);
        *(s16 *)(a0 + 0xFC) = 1;
    }
    func_8012A828(a0, (void *)&D_801A7164);
    p = &D_800B99DC;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = -0x800;
    *(s32 *)(a0 + 0xDC) = 0x30;
    *(s32 *)(a0 + 0xE0) = (*p & 0xF) + 0x20;
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) + 0xC0;
    *(s32 *)(a0 + 0xE8) = (*p & 0x1F) + 0xE0;
    *(s32 *)(a0 + 0xE4) = 0;
    func_8002D4C8(0x6A9, 0);
    *(u16 *)(a0 + 2) += 1;
    func_80143970(a0);
    func_8012B23C(a0);
}
