/* func_80161124 — shared body (overlay slot 0x80128158, h_exact cca105be). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801483E8();
extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80149184(s32 a0);
extern void func_801553A8(s32 *a0);
extern s32 func_801725A4(u8 *a0);
extern s32 func_80161A60(s32 a0);
extern void func_80147324(s32 a0);
extern s16 D_801152A0;
void func_80161124(void *a0)
{
    u8 *self = (u8 *)a0;
    *(s16 *)(self + 0x24A) = 0;
    func_801483E8();
    func_8014CBF8(a0);
    func_801474EC((s32 *)a0);
    if (*(s32 *)(self + 0x2C) < (s32)0xFFF46000) {
        *(s32 *)(self + 0x2C) = 0xFFF46000;
    }
    if ((*(s32 *)(self + 0x24) | *(s32 *)(self + 0x2C)) != 0) {
        func_80154150((s32)self, 0xF);
    } else {
        func_80154150((s32)self, 0xD);
    }
    func_80154A74((s32)self, 0x22);
    *(s32 *)(self + 0x5C) = 0;
    *(s32 *)(self + 0x240) = 0;
    func_80146E90((s32 *)self, 4);
    D_801152A0 = func_80149184((s32)self);
    func_801553A8((s32 *)self);
    func_801725A4((u8 *)self);
    if (func_80161A60((s32)self) != 0) {
        func_80147324(0x8E1);
    }
}
