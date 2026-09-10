/* func_80181E58 — shared body (overlay slot 0x80128158, h_exact beb530ef). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32  func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_8018276C(s32 a0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32  func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern s32  func_8012A828(void *a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u8 D_801C6410;
extern u8 D_8018DE14;
extern s32 D_801D42F8;
extern u8 D_8018DE20;
extern u8 D_8018DE70;
extern u8 D_8018DE50;
extern u8 D_8018DF4C;
void func_80181E58(void *a0)
{
    void *self;
    void *obj;
    s32 pad[8];
    void *a02;
    a02 = a0;
    self = a02;
    if ((*(s32 *)((s32)self + 0x20) = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(self);
        return;
    }
    *(u16 *)((s32)self + 0x72) |= 0x1000;
    if (*(s16 *)((s32)self + 0x70) == 0) {
        func_8001C214(*(s32 *)((s32)self + 0x20), (s32)&D_801C6410);
        *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12) = 0x400;
        obj = (void *)func_8012C194();
        *(s32 *)((s32)self + 0xCC) = (s32)obj;
        if (obj == 0) {
            func_8012CAE4(self);
            return;
        }
        func_8001CB6C((u8 *)obj, (s32)&D_8018DE14, 0x2F0, 0x138);
        func_8018276C((s32)self);
        {
            void *p1 = &D_801D42F8;
            void *p2 = &D_8018DE20;
            *(u16 *)((s32)obj + 0x18) = 0x2200;
            *(u16 *)((s32)obj + 0x1A) = 0x1600;
            *(u16 *)((s32)obj + 0x12) = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
            *(u32 *)((s32)obj + 4) |= 0x51000000;
            *(u8 *)((s32)obj + 0x27) = 0xED;
            func_80128EA8((s32)obj, (s32)p1, (s32)p2);
        }
        *(u8 *)((s32)self + 0xC0) = 1;
        *(s32 *)((s32)self + 0xBC) = (s32)&D_8018DE70;
        *(s32 *)((s32)self + 0x58) = (s32)&D_8018DE50 | 0x40000000;
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
    }
    func_8001CA1C(*(s32 *)((s32)self + 0x20), 0);
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)((s32)self + 0x20) + 4) |= 0x71000000;
    *(s32 *)((s32)self + 0x10) = 0xFFFD0000;
    *(s32 *)((s32)self + 0x14) = 0xFFFE0000;
    *(u16 *)((s32)self + 0xFC) = 0;
    func_8012A828(self, &D_8018DF4C);
    func_8012AD44((s32 *)self, 9);
}
