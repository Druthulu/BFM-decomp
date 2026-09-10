s32 func_80162438(s32 _unused0) {
    extern void func_80024054(void *, void *);
    extern void func_8001CE28(void *, void *);
    extern void func_8001CE68(void *, void *);
    extern void func_800242D0(s32, void *, s32);
    extern s32 func_801626B8(void);
    extern void func_80162760(void);
    extern u8 D_80192F98[];
    extern s32 D_80192FB0;
    extern u8 D_801EDC14[];
    extern u8 D_801EDC3C[];
    extern u8 D_801EDC58[];
    extern int D_801EDC08[];
    extern u16 D_800B5BD8;
    extern u16 D_800B5C10;
    extern u16 D_800B5C48;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s16 D_800B5BE0;
    extern s16 D_800B5BE2;
    extern s16 D_800B5C04;
    extern u8 D_800B5BFF;
    extern s16 D_800B5C18;
    extern s16 D_800B5C1A;
    extern s16 D_800B5C3C;
    extern u8 D_800B5C37;
    extern s16 D_800B5C50;
    extern s16 D_800B5C52;
    extern s16 D_800B5C74;

    u32 uVar2;
    u8 *base;
    u8 *item;

    base = &(*(u8 *)&D_800AF630);
    uVar2 = func_800291DC(0x12);
    if ((uVar2 & 0x8000) != 0) {
        if (D_800B5BD8 == 0) {
            u8 *t = base + 0x65A8;
            item = t;
            D_801EDC08[0] = (s32)item;
            func_80024054(D_80192F98, D_801EDC14);
            func_8001CE28(item, D_801EDC14);
            D_800B5C04 = 1;
            D_800B5BFF = 1;
            D_800B5BE0 = -D_800AF7BC / 2 + 0xD0;
            D_800B5BE2 = -D_800AF7BE / 2 + 0x28;
        }
        if (D_800B5C10 == 0) {
            u8 *t = base + 0x65E0;
            item = t;
            D_801EDC08[1] = (s32)item;
            func_80024054(((u8 *)&D_80192FB0), D_801EDC3C);
            func_8001CE28(item, D_801EDC3C);
            D_800B5C3C = 1;
            D_800B5C37 = 1;
            D_800B5C18 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C1A = -D_800AF7BE / 2 + 0x30;
        }
        if (D_800B5C48 == 0) {
            u8 *t = base + 0x6618;
            item = t;
            D_801EDC08[2] = (s32)item;
            func_800242D0((s16)func_801626B8(), D_801EDC58, 0x84);
            func_8001CE68(item, D_801EDC58);
            D_800B5C74 = 1;
            D_800B5C50 = -D_800AF7BC / 2 + 0xD0;
            D_800B5C52 = -D_800AF7BE / 2 + 0x10;
        }
        func_800242D0((s16)func_801626B8(), D_801EDC58, 0x84);
        if ((uVar2 & 0x7FFF) == (s32)(*(s16 *)&D_80078EB0)) {
            func_80162760();
        }
    }
}
