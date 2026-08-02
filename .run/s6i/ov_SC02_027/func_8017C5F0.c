extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);

extern u8 D_801D9F00;
extern u8 D_801D9F01;
extern u8 D_801D9F02;
extern u8 D_801D9F04;
extern u8 D_801D9F05;
extern u8 D_801D9F06;
/* 0x801DA0F0 has no symbol (it is interior to D_801DA084); the real relocs
 * in the .s are D_801DA104/108/10C, with $s0 = D_801DA104 - 0x14. */
extern s32 D_801DA104[];

void func_8017C5F0(s32 a0) {
    s32 v0;
    u8 *p;
    s16 sp[8];

    v0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    if (v0 == 0) {
        return;
    }

    p = &D_801D9F00;
    *(s32 *)(a0 + 0xD0) = v0;
    func_8001CD50(v0, (s32)p);

    D_801D9F01 = 0xFF;
    D_801D9F02 = 0xFF;
    *p = 0xFF;
    D_801D9F06 = 8;
    D_801D9F04 = 8;
    D_801D9F05 = 0x18;
    func_800233CC(p, 0x100);

    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA) - 0x38;
    sp[2] = *(u16 *)(a0 + 0xE);
    func_800D20C0(&sp[0], &sp[4], 5);

    D_801DA104[0] = sp[0];
    D_801DA104[1] = sp[1];
    D_801DA104[2] = sp[2];
    func_800D23D0(&sp[4]);
    RotMatrixYXZ(&sp[4], &D_801DA104[-5]);

    *(s32 *)(v0 + 0x34) = (s32)&D_801DA104[-5];
    *(s16 *)(v0 + 0x1A) = 0;
    *(s16 *)(v0 + 0x18) = 0;
    *(s32 *)(v0 + 0x4) |= 0x50000000;
    *(u16 *)(a0 + 0x2) += 1;
}
