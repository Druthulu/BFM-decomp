/* func_80188828 — shared body (overlay slot 0x80128158, h_exact 6519c024). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013CABC(void);
extern void func_801890F8(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80188A80(s32 a0);
extern void func_801889B4(s32 a0);
extern s32 func_801846E4(void);
extern int func_80178970(void);
extern s32 D_801EAC90;
void func_80188828(s32 a0) {
    s32 self;
    self = a0;
    if (*(s32 *)(self + 0x1C) == 0x30) {
        func_8013CABC();
    } else if (*(s32 *)(self + 0x1C) == 0x10) {
        func_801890F8((void *)*(s32 *)(self + 0xD0));
    }
    if (*(u16 *)(self + 0x84) & 1) {
        *(u16 *)(*(s32 *)(self + 0x64) + 6) = *(u16 *)(*(s32 *)(self + 0x64) + 6) - 3;
        *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) =
            *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) - 3;
        *(u16 *)(self + 6) = *(u16 *)(self + 6) - 3;
    } else {
        *(u16 *)(*(s32 *)(self + 0x64) + 6) = *(u16 *)(*(s32 *)(self + 0x64) + 6) + 3;
        *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) =
            *(u16 *)(*(s32 *)(*(s32 *)(self + 0x64) + 0x20) + 8) + 3;
        *(u16 *)(self + 6) = *(u16 *)(self + 6) + 3;
    }
    {
        s32 t;
        t = D_801EAC90;
        *(u16 *)(self + 0x84) = *(u16 *)(self + 0x84) + 1;
        if (t == 0) {
            D_801EAC90 = func_801846E4();
        }
    }
    if (func_8012BEE8(self) && D_801EAC90) {
        func_80188A80(self);
    } else {
        if (*(s32 *)(self + 0x1C) < 0x48) {
            if ((*(u16 *)(self + 0x84) & 3) == 0) {
                func_801889B4(self);
            }
        }
    }
    ((void (*)(s32))func_80178970)(self);
}
