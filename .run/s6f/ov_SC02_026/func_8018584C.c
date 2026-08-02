struct B16_8018584C { s32 w[4]; };

extern struct B16_8018584C D_800A5E88;
extern struct B16_8018584C D_801CCC80;
extern s32 D_800A5E90;
extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_8018584C(void *a0) {
    s32 t;

    D_800A5E88 = D_801CCC80;
    t = func_8004787C(*(s16 *)((s32)a0 + 0xFE));
    if (t < 0) t += 0x1FF;
    D_800A5E90 = (t >> 9) + 8;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, &D_800A5E88);
}
