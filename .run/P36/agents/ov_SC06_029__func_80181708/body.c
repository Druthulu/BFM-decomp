void func_80181708(int param_1) {
    typedef struct { s16 vx, vy, vz, pad; } SV;
    typedef struct { u8 pad[0x3C]; s32 x3C; s32 x40; s32 x44; s32 x48; s32 x4C; s32 x50; } OB;
    extern s16 D_801904C6_a[] __asm__("D_801904C6");
    extern s16 D_801904CE_a[] __asm__("D_801904CE");
    SV *p1 = (SV *)D_801DFD8C;
    SV *p2 = (SV *)D_801DFD90;

    ((OB *)param_1)->x48 = p1->vx;
    ((OB *)param_1)->x50 = p1->vz;
    ((OB *)param_1)->x3C = p2->vx;
    ((OB *)param_1)->x44 = p2->vz;
    ((OB *)param_1)->x4C += (s16)func_80012CB8(D_801904C6_a[0], p1->vy, 0xC0);
    ((OB *)param_1)->x40 += (s16)func_80012CB8(D_801904CE_a[0], ((SV *)D_801DFD90)->vy, 0xC0);
    if (((OB *)param_1)->x4C < ((SV *)D_801DFD8C)->vy)
        ((OB *)param_1)->x4C = ((SV *)D_801DFD8C)->vy;
    if (((OB *)param_1)->x40 < ((SV *)D_801DFD90)->vy)
        ((OB *)param_1)->x40 = ((SV *)D_801DFD90)->vy;
}
