/* func_80188670 — shared body (overlay slot 0x80128158, h_exact 9b98ab28). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int a0, int a1);
extern s32  func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80188F80(void *a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32  func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u8 D_801E450C;
extern u8 D_801918BC;
extern s32 D_801EAC88;   /* engine_core.h DEFINE_func_801892E4() block-declares this as s32 in this very TU (L3861) -- MUST agree */
extern u8 D_801918C8;
extern u8 D_80191918;
extern u8 D_801918F8;
extern u8 D_801919F4;
void func_80188670(void *a0)
{
    void *self = a0;
    void *obj;
    s32 h;
    s32 pad[8];
    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)self + 0x20) = h;
    if (h == 0) {
        goto L_fail;
    }
    if (*(s16 *)((s32)self + 0x70) != 0) {
        goto L_da8;
    }
    func_8001C214(h, (s32)&D_801E450C);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12) = 0;
    obj = (void *)func_8012C194();
    *(s32 *)((s32)self + 0xCC) = (s32)obj;
    if (obj != 0) {
        goto L_ce4;
    }
L_fail:
    func_8012CAE4(self);
    return;
L_ce4:
    func_8001CB6C((u8 *)obj, (s32)&D_801918BC, 0x2F0, 0x138);
    func_80188F80(self);
    *(u16 *)((s32)obj + 0x18) = 0x2400;
    *(u16 *)((s32)obj + 0x1A) = 0x1C00;
    *(u16 *)((s32)obj + 0x12) = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
    *(u32 *)((s32)obj + 4) |= 0x51000000;
    *(u8 *)((s32)obj + 0x27) = 0xED;
    func_80128EA8((s32)obj, (s32)&D_801EAC88, (s32)&D_801918C8);
    *(u8 *)((s32)self + 0xC0) = 1;
    *(s32 *)((s32)self + 0xBC) = (s32)&D_80191918;
    *(s32 *)((s32)self + 0x58) = (s32)&D_801918F8 | 0x40000000;
    *(u16 *)((s32)self + 0x5C) = 0x8000;
    *(s16 *)((s32)self + 0xAE) = -3;
    {
        s32 v0 = *(s32 *)((s32)self + 0xC4);
        u16 v1 = *(u16 *)((s32)self + 0xA);
        *(s32 *)((s32)self + 0xB4) = 0;
        *(u8 *)((s32)self + 0xC1) = 0;
        *(s32 *)((s32)self + 0xC4) = v0 | 2;
        *(u16 *)((s32)self + 0xFE) = v1;
    }
    func_8012AD50(self);
    return;
L_da8:
    func_8001CA1C(h, 0);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)((s32)self + 0x20) + 4) |= 0x71000000;
    *(s32 *)((s32)self + 0x14) = 0xFFFE0000;
    *(s32 *)((s32)self + 0x18) = 0xFFFD0000;
    *(u16 *)((s32)self + 0xFC) = 0;
    func_8012A828((s32)self, &D_801919F4);
    func_8012AD44((s32 *)self, 9);
}
