#include "common.h"

void func_800CAE0C(void) {
    extern void func_800183E0(s32 a0);
    extern s32 D_800CC22C;
    extern s32 D_800CC1EC;
    ((void (*)(void *))func_800183E0)(&D_800CC22C);
    ((void (*)(s32))func_800183E0)((s32)&D_800CC1EC);
}




void func_800CAE44(void *a0) {

    extern void (*D_800CC134[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CC134[*(u8 *)((s32)a0 + 0x197)]();
}


extern void func_800CAEC0();
void func_800CAE88(void *a0) {
    func_800CAEC0(a0);
    *(u8 *)((s32)a0 + 0x197) += 1;
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CAEC0);

void func_800CAF18(void) {
}

void func_800CAF20(void) {
}

extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAFEC();
void func_800CAF28(s32 *a0) {
    func_80147078(a0, 32);
    ((void (*)(void *))func_800CAFEC)(a0);
}


extern void func_80147078(s32 *a0, s16 a1);
extern void func_800CAF90(void *a0);
void func_800CAF5C(s32 *a0) {
    func_80147078(a0, 32);
    func_800CAF90(a0);
}




void func_800CAF90(void *a0) {

    extern void (*D_800CC140[])(void);
    D_800CC140[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_800CAFEC();
void func_800CAFCC(void) {
    func_800CAFEC();
}


void func_800CAFEC(s32 *a0) {
    s32 *v1;
    extern s32 func_80161208();
    extern s32 func_80165A20(s32);
    extern void func_801553A8(s32 *a0);
    extern void func_80155440(s32 *a0);
    extern void func_80154150(s32 a0, s32 a1);
    extern void func_80154A74(s32 a0, s32 a1);
    extern void func_80146CA0(void *a0);

    if (func_80161208(a0) != 0) {
        ((void (*)(s32))func_80165A20)((s32)a0);
        return;
    }
    func_801553A8(a0);
    func_80155440(a0);
    func_80154150((s32)a0, 0x26);
    func_80154A74((s32)a0, 0x1E);
    v1 = (s32 *)a0[0x20 / 4];
    *(s16 *)((u8 *)v1 + 0x10) = 0xFE9;
    a0[0x238 / 4] = 0;
    func_80146CA0(a0);
}


extern s32 func_80161208();
extern s32 func_80165A20(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB06C(void *arg0) {
    s32 p;
    s32 q;
    register void *a __asm__("$4");
    if (func_80161208(arg0) != 0) {
        func_80165A20(arg0);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
    p = *(s32 *)((u8 *)arg0 + 0x20);
    *(u16 *)((u8 *)p + 0x10) =
        (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
    q = *(s32 *)((u8 *)arg0 + 0x20);
    if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
        a = arg0;
        __asm__ __volatile__("" : : "r"(a));
        *(u16 *)((u8 *)q + 0x10) = 0xc00;
        *(u16 *)((u8 *)a + 0xb8) = 1;
        func_80146CA0(a);
    }
}


extern s32 func_80161208();
extern s32 func_80165A20(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);

void func_800CB108(s32 a0) {
    if (func_80161208()) {
        func_80165A20(a0);
    } else if (*(u16 *)((s32)a0 + 0xB8) == 0x8000) {
        func_80154150(a0, 0x27);
        func_80154A74(a0, 0x1F);
        func_801466F0(0xD, a0, 0, -0x40, 0, 0, 0, 0);
        func_80147324(0x6E2);
        func_80146CA0((void *)a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB1A0);

extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

void func_800CB234(void *a0) {
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
    func_801553C0((s32)a0);
    func_80154A74((s32)a0, 0x11);
}


extern u8 D_80078EC1;
extern void (*D_800CC180[])();
extern void func_800CB7FC();

void func_800CB270(int param_1)
{
    if (D_80078EC1 != 24) {
        func_800CB7FC();
    } else {
        D_800CC180[*(u16 *)(param_1 + 2)]();
    }
}


extern s32 func_8014659C(void);
extern void func_8001C2C4(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80146CA0(void *a0);
extern void func_800CB7FC();

extern u8 D_800CC150[];
extern u8 D_800CC298[];

void func_800CB2CC(s32 arg0) {
    s32 s2;
    s32 s0;
    s32 v;
    u16 h;

    s2 = *(s32 *)(arg0 + 0x4C);
    s0 = func_8014659C();
    *(s32 *)(arg0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C2C4(s0);
        v = *(s32 *)(s2 + 0x20);
        h = *(u16 *)(v + 0x12);
        *(u16 *)(s0 + 0x1A) = 0;
        *(u16 *)(s0 + 0x18) = 0;
        *(u16 *)(s0 + 0x1C) = 0x1000;
        *(u16 *)(s0 + 0x12) = h;
        func_80146E90((s32 *)arg0, 0x20);
        func_80149374(s2, arg0 + 4);
        *(u32 *)(arg0 + 0x58) = (u32)&D_800CC150[0];
        *(u16 *)(arg0 + 0x60) = 0;
        *(u16 *)(arg0 + 0x62) = 0;
        *(u16 *)(arg0 + 0x64) = 0;
        func_801466B4(0x28, arg0, 0, 0, 1);
        func_801466B4(0x28, arg0, 1, 0, 1);
        memcpy(&D_800CC298[0], (void *)(s2 + 0x154), 8);
        func_80146CA0((void *)arg0);
    } else {
        func_800CB7FC(arg0);
    }
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB3E0);

INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB4A4);

extern void func_801662F4(void);
extern void func_80162CCC(void);
void func_800CB7FC(s32 a0) {
    func_801662F4();
    ((void (*)(s32))func_80162CCC)(a0);
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CB82C);

void func_800CBA44()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lhu    $2, 0($5)\n"
        "lhu    $3, 16($6)\n"
        "addu   $8, $4, $0\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 0($8)\n"
        "lhu    $2, 2($5)\n"
        "lhu    $3, 18($6)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 2($8)\n"
        "lhu    $2, 4($5)\n"
        "lhu    $3, 16($6)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 8($8)\n"
        "lhu    $2, 6($5)\n"
        "lhu    $3, 18($6)\n"
        "addiu  $29, $29, -8\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 10($8)\n"
        "lhu    $3, 8($5)\n"
        "lhu    $4, 16($6)\n"
        "lhu    $2, 0($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 16($8)\n"
        "lhu    $3, 10($5)\n"
        "lhu    $4, 18($6)\n"
        "lhu    $2, 2($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 18($8)\n"
        "lhu    $3, 12($5)\n"
        "lhu    $4, 16($6)\n"
        "lhu    $2, 0($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "sh     $2, 24($8)\n"
        "lhu    $3, 14($5)\n"
        "lhu    $4, 18($6)\n"
        "lhu    $2, 2($7)\n"
        "addu   $3, $3, $4\n"
        "addu   $2, $2, $3\n"
        "addiu  $3, $8, 8\n"
        "sh     $2, 26($8)\n"
        "addiu  $2, $8, 16\n"
        "lw     $5, 24($29)\n"
        "lw     $4, 28($29)\n"
        "lwc2   $0, 0($8)\n"
        "lwc2   $1, 4($8)\n"
        "lwc2   $2, 0($3)\n"
        "lwc2   $3, 4($3)\n"
        "lwc2   $4, 0($2)\n"
        "lwc2   $5, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "addiu  $2, $5, 16\n"
        "addiu  $3, $5, 8\n"
        "swc2   $12, 0($5)\n"
        "swc2   $13, 0($3)\n"
        "swc2   $14, 0($2)\n"
        "cfc2   $12, $31\n"
        "nop\n"
        "sw     $12, 0($29)\n"
        "lw     $2, 0($29)\n"
        "addiu  $3, $0, -4097\n"
        "and    $2, $2, $3\n"
        "bnez   $2, 99f\n"
        " addiu $2, $0, 1\n"
        "addiu  $2, $8, 24\n"
        "lwc2   $0, 0($2)\n"
        "lwc2   $1, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtps\n"
        "addiu  $2, $5, 24\n"
        "swc2   $14, 0($2)\n"
        "cfc2   $12, $31\n"
        "nop\n"
        "sw     $12, 0($29)\n"
        "lw     $2, 0($29)\n"
        "nop\n"
        "and    $2, $2, $3\n"
        "bnez   $2, 99f\n"
        " addiu $2, $0, 1\n"
        "lw     $2, 0($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 32($5)\n"
        "lw     $2, 4($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 36($5)\n"
        "lw     $2, 8($6)\n"
        "lw     $3, 0($4)\n"
        "nop\n"
        "addu   $2, $2, $3\n"
        "sw     $2, 40($5)\n"
        "lw     $3, 12($6)\n"
        "lw     $4, 0($4)\n"
        "addu   $2, $0, $0\n"
        "addu   $3, $3, $4\n"
        "sw     $3, 44($5)\n"
        "99:\n"
        "addiu  $29, $29, 8\n"
        ".set\treorder\n"
    );
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBBF8);

extern s16 currentLocationId;

void func_800CBCB4(void *a0) {
    s16 sp[4];

    func_80015978((s32)a0 + 4, sp);
    switch (currentLocationId) {
    case 0x3035:
        if (sp[0] < -0x93E) {
            sp[0] = -0x93E;
        }
        if (sp[0] >= -0x3C1) {
            sp[0] = -0x3C2;
        }
        if (sp[2] < 0x3C2) {
            sp[2] = 0x3C2;
        }
        if (sp[2] >= 0xCBF) {
            sp[2] = 0xCBE;
            goto after;
        }
        break;
    case 0x3037:
        if (sp[0] < 0x4C2) {
            sp[0] = 0x4C2;
        }
        if (sp[0] >= 0xA3F) {
            sp[0] = 0xA3E;
        }
        if (sp[2] < 0xAC2) {
            sp[2] = 0xAC2;
        }
        if (sp[2] >= 0x13BF) {
            sp[2] = 0x13BE;
            goto after;
        }
        break;
    case 0x3038:
        if (sp[0] < -0xF3E) {
            sp[0] = -0xF3E;
        }
        if (sp[0] >= -0x9C1) {
            sp[0] = -0x9C2;
        }
        if (sp[1] < -0xA00) {
            sp[1] = -0xA00;
        }
        if (sp[1] >= -0x201) {
            sp[1] = -0x202;
            goto after;
        }
        break;
    case 0x3039:
        if (sp[0] < -0x153E) {
            sp[0] = -0x153E;
        }
        if (sp[0] >= -0xFC1) {
            sp[0] = -0xFC2;
        }
        if (sp[2] < 0x3C2) {
            sp[2] = 0x3C2;
        }
        if (sp[2] >= 0xFBF) {
            sp[2] = 0xFBE;
        }
        break;
    }
after:
    func_80015954(sp, (s32)a0 + 4);
}


extern u8 D_80078EC1;
extern void (*D_800CC1C4[])();
extern void func_800CC004();

void func_800CBECC(int param_1)
{
    if (D_80078EC1 != 24) {
        func_800CC004();
    } else {
        D_800CC1C4[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CBF28);

extern void func_800CC024(void);
void func_800CBFE4(void) {
    func_800CC024();
}


extern void func_80162CCC(void);
void func_800CC004(void) {
    func_80162CCC();
}


INCLUDE_ASM("asm/md_MAIN_027/nonmatchings/md_MAIN_027", func_800CC024);
