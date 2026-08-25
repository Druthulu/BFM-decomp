#include "common.h"



void func_801E4C64(void *a0) {

    extern void (*D_801E663C[])(void);
    D_801E663C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4CA0);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4D14);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4D7C);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4DF0);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4E58);

void func_801E4EC0(void *a0) {
    extern void func_801E53E0(void *a0);
    extern s32 D_801270C8;
    u16 *p = (u16 *)*(s32 *)((s32)a0 + 0x20);

    func_801E53E0(a0);
    if (D_801270C8 != 7) {
        return;
    }
    if (--*(s32 *)((s32)a0 + 0x1C) != -1) {
        u16 t = p[0xE] - 0x200;
        p[0xE] = t;
        p[0xC] = t;
        p[0xD] += 0x200;
        p[0x16] |= 0x10;
    } else {
        u16 c = *(u16 *)((s32)a0 + 0x2) + 1;
        *(s32 *)((s32)a0 + 0x1C) = 8;
        *(u16 *)((s32)a0 + 0xE) += 0x100;
        *(u16 *)((s32)a0 + 0x2) = c;
    }
}


INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4F6C);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E4FC8);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E5030);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E5094);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E50F0);

void func_801E514C(s32 a0) {
    extern void func_801E53E0(s32);
    extern void func_8017E424(void);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8013767C(s32);
    extern s32 D_801270C8;
    extern u8 D_80197480[];
    extern u8 D_801E60D4[];

    func_801E53E0(a0);
    if (D_801270C8 == 16) {
        func_8017E424();
        func_8012A828(a0, D_801E60D4);
        *(s32 *)(a0 + 0xB0) = func_8013767C((s32)D_80197480);
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_801E51C0(s32 a0) {
    extern void func_801E53E0(s32);
    extern s32 func_801399F0(s32);
    extern void func_80139914(s32);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8017E454(void);
    extern s32 func_8013767C(s32);
    extern u8 D_801E5FFC[];
    extern u8 D_801974DC[];

    func_801E53E0(a0);
    if (func_801399F0(*(s32 *)(a0 + 0xB0)) != 0) {
        func_80139914(*(s32 *)(a0 + 0xB0));
        func_8012A828(a0, D_801E5FFC);
        func_8017E454();
        *(s32 *)(a0 + 0xB0) = func_8013767C((s32)D_801974DC);
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E5240);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E52BC);

INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E5338);

void func_801E53A8(void *a0) {

    extern void func_801439C0(u8 *a0);
    extern void func_8012C218(void *a0);
    func_801439C0(*(u8 **)((s32)a0 + 0xCC));
    func_8012C218(a0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void D_801E5DB4;
extern void D_801E5E0C;
extern void D_801E5F04;
extern void D_801E6314;

void func_801E53E0(s32 arg0)
{
    if ((*(u16 *)((s32)arg0 + 0x72) & 0x4000) && (*(void **)((s32)arg0 + 0x90) != &D_801E5DB4)) {
        void *a1 = &D_801E5DB4;
        void *ptr = *(void **)((s32)arg0 + 0x90);

        if ((ptr == &D_801E5E0C) || (ptr == &D_801E5F04)) {
            a1 = &D_801E6314;
        }
        func_8012A828(arg0, a1);
    }
}




void func_801E5450(void *a0) {

    extern void (*D_801E6680[])(void);
    D_801E6680[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E548C(s32 a0) {

    extern s32 D_801E63C4;
    extern s32 D_80196BBC;
    extern s32 D_801F3D3C;
    extern s32 func_8012C354(s32 arg0, s32 arg1);
    extern void func_8001C1E4(void *arg0, s32 arg1);
    extern void func_8012A828(s32 arg0, void *arg1);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    s32 v0;
    s32 p;

    p = (s32)&D_80196BBC;
    *(s32 *)p = (s32)&D_801F3D3C;
    if (func_8012C354(a0, p - 4) != 0) {
        v0 = *(s32 *)(a0 + 0x64);
        func_8001C1E4((void *)*(s32 *)(a0 + 0x20), *(s32 *)(v0 + 0x20));
        func_8012A828(a0, (void *)&D_801E63C4);
        *(s32 *)(a0 + 0xCC) = func_8012C658(0x3D4, 0x4000, a0);
        *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}


INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E5518);

void func_801E5580(s32 *a0) {
    s32 *s0 = a0;
    extern void func_801E590C();
    extern s32 func_801399F0(s32 a0);
    extern void func_80139914(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_801270C8;
    extern s32 D_801E63C4;

    func_801E590C(s0);
    if (func_801399F0(*(s32 *)((u8 *)s0 + 0xB0)) != 0) {
        func_80139914(*(s32 *)((u8 *)s0 + 0xB0));
        D_801270C8 = 5;
        func_8012A828((s32)s0, &D_801E63C4);
        (*(u16 *)((u8 *)s0 + 2))++;
    }
}


void func_801E55F4(s32 a0) {
    extern void func_801E590C();
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8013767C(s32);
    extern s32 D_801270C8;
    extern u8 D_8019729C[];
    extern u8 D_801E644C[];

    func_801E590C(a0);
    if (D_801270C8 == 11) {
        *(s32 *)((s32)a0 + 0xB0) = func_8013767C((s32)D_8019729C);
        func_8012A828(a0, D_801E644C);
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_801E5664(s32 *a0) {
    s32 *s0 = a0;
    extern void func_801E590C();
    extern s32 func_801399F0(s32 a0);
    extern void func_80139914(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_801270C8;
    extern s32 D_801E63C4;

    func_801E590C(s0);
    if (func_801399F0(*(s32 *)((u8 *)s0 + 0xB0)) != 0) {
        func_80139914(*(s32 *)((u8 *)s0 + 0xB0));
        D_801270C8 = 12;
        func_8012A828((s32)s0, &D_801E63C4);
        (*(u16 *)((u8 *)s0 + 2))++;
    }
}


void func_801E56D8(s32 a0) {
    extern void func_801E590C();
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8013767C(s32);
    extern s32 D_801270C8;
    extern u8 D_80197418[];
    extern u8 D_801E644C[];

    func_801E590C(a0);
    if (D_801270C8 == 14) {
        *(s32 *)((s32)a0 + 0xB0) = func_8013767C((s32)D_80197418);
        func_8012A828(a0, D_801E644C);
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_801E5748(s32 *a0) {
    s32 *s0 = a0;
    extern void func_801E590C();
    extern s32 func_801399F0(s32 a0);
    extern void func_80139914(s32 a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 D_801270C8;
    extern s32 D_801E63C4;

    func_801E590C(s0);
    if (func_801399F0(*(s32 *)((u8 *)s0 + 0xB0)) != 0) {
        func_80139914(*(s32 *)((u8 *)s0 + 0xB0));
        D_801270C8 = 15;
        *(s32 *)((u8 *)s0 + 0x1C) = 18;
        func_8012A828((s32)s0, &D_801E63C4);
        (*(u16 *)((u8 *)s0 + 2))++;
    }
}


extern s32 MoveImage(void *a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E65E4[];

void func_801E57C4(s32 a0) {
    s16 rect[4];
    s32 s0;
    s32 v0;

    s0 = a0;
    v0 = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v0;
    if (v0 == -1) {
        rect[0] = 0x328;
        rect[1] = 0x140;
        rect[2] = 8;
        rect[3] = 0x20;
        MoveImage(rect, 0x32C, 0x1C8);
        func_8012A828(s0, D_801E65E4);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
    }
}


void func_801E584C(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
}


void func_801E5874(void *a0) {

    extern s32 D_801270C8;
    D_801270C8 = 0x10;
    *(u16 *)((s32)a0 + 0x2) += 1;
}


void func_801E5894(void *a0) {

    extern s32 D_801270C8;
    if (D_801270C8 == 17) {
        ((struct { u8 pad[2]; u16 f; } *)a0)->f += 1;
        *(s32 *)((s32)a0 + 0x1C) = 8;
    }
}


INCLUDE_ASM("asm/md_SC02_009/nonmatchings/md_SC02_009", func_801E58C0);

void func_801E590C(void *a0) {

    extern s32 D_801E63C4;
    if (*(s32 **)((s32)a0 + 0x90) != &D_801E63C4) {
        if (*(s16 *)((s32)a0 + 0xE) >= -30) {
            *(s16 *)((s32)a0 + 0xE) -= 4;
        }
    } else {
        if (*(s16 *)((s32)a0 + 0xE) < -1) {
            *(s16 *)((s32)a0 + 0xE) += 8;
        }
    }
}




void func_801E5968(void *a0) {

    extern void (*D_801E66B0[])(void);
    D_801E66B0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801E59A4(void *a0)
{
    extern s32 D_80196BBC;
    extern u8 D_801D8B8C[];
    extern s32 D_80190C0C;
    extern s32 D_801E66C4;
    s32 s1 = (s32)a0;
    s32 *ptr;
    u16 tmp;

    ptr = &D_80196BBC;
    *ptr = (s32)&D_801D8B8C;

    if (func_8012C354(s1, (s32)ptr - 4) != 0) {
        func_8012A828(s1, &D_80190C0C);
        func_80136BC4(&D_801E66C4);

        *(s32 *)(s1 + 0x58) = (s32)&D_801E66C4 & 0x7FFFFFFF;
        *(u16 *)(s1 + 0x5C) = 0x800;
        *(u8 *)(s1 + 0x75) = 1;
        *(s32 *)(s1 + 0xCC) = func_80143994(s1, 0x3000);

        tmp = *(u16 *)(s1 + 0x2);
        *(u16 *)(s1 + 0x16) = 4;
        *(u16 *)(s1 + 0x2) = tmp + 1;
    }
}


void func_801E5A58(void *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    func_8012AD80((s32)a0);
    if (*(s16 *)((s32)a0 + 0xA) >= -0x802) {
        *(s16 *)((s32)a0 + 0xA) = -0x802;
        if (func_8012C588(0x56, (s32)a0) != 0) {
            *(s32 *)((s32)s1 + 0x4) = 0x80000000;
            func_801439C0(*(s32 *)((s32)a0 + 0xCC));
            func_8002D4C8(0x4FF, 0);
            func_8002D4C8(0x510, 0x105F);
            *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
        }
    } else {
        *(s32 *)((s32)a0 + 0x14) += 0x1C000;
    }
}



extern void func_8012C218(void);

void func_801E5B0C(void) {

    extern s32 D_801270C8;
    if (D_801270C8 == 13) {
        func_8012C218();
    }
}


extern void func_801439C0(void *a0);
extern s32 func_80134510(s32 arg);
extern s32 ratan2(s32 a0, s32 a1);
extern s16 D_801152AC;
extern s16 D_801152AA;
extern u8 D_801152A8[];

void func_801E5B3C(s32 a0) {
    s32 s1 = *(s32 *)(a0 + 0x64);
    s32 s0 = *(s32 *)(a0 + 0xCC);
    s16 sp[3];
    if (*(s16 *)(s1 + 0x36) != *(s16 *)(a0 + 0xFC)) {
        func_801439C0((void *)a0);
        return;
    }
    sp[0] = *(u32 *)(*(s32 *)(s1 + 0x20) + 0x68);
    sp[1] = *(u32 *)(*(s32 *)(s1 + 0x20) + 0x6C) - 0x10;
    sp[2] = *(u32 *)(*(s32 *)(s1 + 0x20) + 0x70);
    if (func_80134510((s32)&sp[0]) == 0) {
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x80000000;
        return;
    }
    *(s16 *)(s0 + 8) = sp[0];
    *(s16 *)(s0 + 0xA) = sp[1];
    *(s16 *)(s0 + 0xC) = sp[2];
    *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & 0x7FFFFFFF;
    *(s16 *)(s0 + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400;
    *(s16 *)(s0 + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA);
    *(s16 *)(s0 + 0x14) = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + 0x200;
}




void func_801E5C6C(void *a0) {

    extern void (*D_801E66BC[])(void);
    D_801E66BC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801921F8;

void func_801E5CA8(int param_1) {
    int iVar3;
    u16 uVar2;
    s16 sVar1;

    iVar3 = ((s32 (*)(void))func_8012C194)();
    if (iVar3 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        uVar2 = *(u16 *)(*(int *)(param_1 + 0x64) + 0x36);
        *(int *)(param_1 + 0xCC) = iVar3;
        *(u16 *)(param_1 + 0xFC) = uVar2;
        func_8001CB6C((u8 *)iVar3, (s32)&D_801921F8, 0x250, 0x1A0);
        *(int *)(iVar3 + 4) = 0x60000000;
        *(u8 *)(iVar3 + 0x27) = 0x14;
        *(u16 *)(iVar3 + 0x10) = 0x400;
        *(u16 *)(iVar3 + 8) = *(u32 *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x68);
        *(u16 *)(iVar3 + 0xA) = *(u32 *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x6C);
        *(u16 *)(iVar3 + 0xC) = *(u32 *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x70);
        sVar1 = *(s16 *)(param_1 + 0x70);
        if (sVar1 != 0) {
            *(s16 *)(iVar3 + 0x1A) = sVar1;
            *(s16 *)(iVar3 + 0x18) = sVar1;
        } else {
            *(u16 *)(iVar3 + 0x1A) = 0x2000;
            *(u16 *)(iVar3 + 0x18) = 0x2000;
        }
        *(u16 *)(param_1 + 2) = 1;
    }
}


INCLUDE_RODATA("asm/md_SC02_009/nonmatchings/md_SC02_009", D_801E4C60);
