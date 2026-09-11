#include "common.h"
#include "../shared/engine_prelude.h"
#include "ov_SC02_011_shared.h"

/* P31 S74 — split out of src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c at a jtbl-span TU boundary
 * (vram 0x80183178-0x80188E3C, file 0x5B020-0x60CE4). This TU owns .rodata span B
 * (0x801E9DB0-0x801E9E30, tables of func_80183178 / func_80183630 / func_8018418C); the parent
 * TU already owns span A (0x801E9D60-0x801E9DA0) and one object contributes exactly ONE
 * contiguous .rodata run, so span B needed its own object. See config/splat.ov_SC02_011.yaml
 * and cookbook §426/§431. Declarations shared with the sibling TUs live in
 * src/ov_SC02_011/ov_SC02_011_shared.h. */

extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_8012B200(u8 *a0);
extern void func_8012AD80(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80184964(s32 a0);
extern s32 func_80184A28(s32 *a0);
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern void func_80184918(s32 arg0, s32 arg1);


typedef struct Sub83178 {
    char pad0[0x10];
    s16 unk10;
} Sub83178;

typedef struct Ent83178 {
    char pad0[0x20];
    Sub83178 *unk20;
} Ent83178;

void func_80183178(s32 a0) {

    extern u8 D_80195184[];
    extern u8 D_80195114[];
    extern u8 D_801F404C[];
    extern void *D_80195144;
    extern s32 D_801950D8;
    extern u8 D_801F3EFC[];
    extern short D_801F3EA4;
    extern s16 D_801EBA7C;
    s32 s0 = a0;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) -= 0x20;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = -0x400;
        }
        if (func_8012CBCC(s0) & 0x2000) {
            *(u16 *)(s0 + 0x34) = 0xA;
            func_8013C9C4((void *)D_80195184);
            func_80184964(s0);
            func_8002D4C8(0x5CA, 0);
            D_801EBA7C = 3;
        }
        break;
    case 1:
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 2:
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) += 0x80;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) >= 0) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
            func_8012B23C(s0);
            func_8012B14C(s0, (s32)D_80195114);
            func_8012A828(s0, (void *)D_801F404C);
            *(s32 *)(s0 + 0x1C) = 0xA;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 3:
        if (func_8012BEE8(s0) != 0) {
            if (((s32 (*)(s32, s32))func_8012CC40)(s0, (s32)&D_80195144) & 0x8000) {
                *(u16 *)(s0 + 0x98) = 0;
                func_8012B200((u8 *)s0);
                func_8012B14C(s0, (s32)&D_801950D8);
                func_8012A828(s0, (void *)D_801F3EFC);
                D_801EBA7C = 3;
                *(s32 *)(s0 + 0x1C) = 0x1E;
                *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            }
        }
        break;
    case 4:
        if (func_8012BEE8(s0) == 0) {
            func_8012AD80(s0);
        }
        break;
    case 5:
        func_8012B23C(s0);
        *(u16 *)(s0 + 0x98) = 0;
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 6:
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) -= 0x20;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = -0x400;
        }
        if (func_8012CBCC(s0) & 0x2000) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = -0x400;
            *(s32 *)(s0 + 0x1C) = 0x2D;
            func_8013C9C4((void *)D_80195184);
            func_80184964(s0);
            func_8002D4C8(0x5CA, 0);
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 7:
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 8:
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) += 0x80;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) >= 0) {
            D_801EBA7C = 3;
            ((Ent83178 *)s0)->unk20->unk10 = 0;
            func_8012A828(s0, (void *)&D_801F3EA4);
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 9:
        break;
    case 10:
        if (func_80184A28((s32 *)s0) == 1) {
            D_801EBA7C = 3;
            ((Ent83178 *)s0)->unk20->unk10 = -0x400;
            *(s32 *)(s0 + 0x1C) = 0x2D;
            *(u16 *)(s0 + 0x34) = 1;
        }
        break;
    }

    if (func_801789AC(s0) == 1) {
        ((void (*)(s32))func_80178D18)(s0);
        *(u16 *)(s0 + 2) = 8;
        func_80184918(s0, 0x1C);
    }
}


extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182380(void);
extern u8 D_80195114[];
extern u8 D_801F404C[];

void func_801834EC(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 9;
    func_8012B23C(s0);
    func_8012B14C(s0, (s32)D_80195114);
    func_8012A828(s0, (void *)D_801F404C);
    *(s32 *)(s0 + 0x1C) = 0xA;
    *(s32 *)(s0 + 0xDC) &= ~1;
    func_80182380();
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_8012A828(s32 a0, void *a1);

extern void *D_80195144;
extern short D_801F40A4;

void func_80183558(s32 a0) {
    s32 v1;

    if (func_8012BEE8(a0) != 0) {
        v1 = ((s32 (*)(s32, s32))func_8012CC40)((int)a0, (int)&D_80195144);
        if (v1 & 0x8000) {
            *(s16 *)(a0 + 0x98) = 0;
            *(s16 *)(a0 + 0x2) = 0xA;
        } else if (v1 & 0x6000) {
            *(s16 *)(a0 + 0x2) = 8;
        } else if ((*(u32 *)(a0 + 0xDC) & 1) == 0 && *(s32 *)(a0 + 0x14) >= 0) {
            ((void (*)(s32, s32))func_8012A828)((int)a0, (int)&D_801F40A4);
            *(u32 *)(a0 + 0xDC) |= 1;
        }
    }
}


extern void func_8018452C();
    void func_8018360C(short *param) {
        param[1] = 0xB;
        func_8018452C();
    }


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BEE8(s32 a0);
extern void *D_80195144;

void func_80183630(s32 a0) {
    extern s32 func_801845F4();
    extern void func_8018487C(s32 a0);
    extern s32 func_80183954(s32 a0);
    extern s32 func_80183B30(s32 a0, s32 a1);
    extern s32 func_80183994(s32 a0, s32 a1);
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_8012B2CC(s32 a0);
    extern s32 func_8012CBCC(s32 a0);
    extern void func_8012CC1C(s32 arg0, s32 arg1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8013C9C4(void *a0);
    extern void func_8012B200(u8 *a0);
    extern void func_8012AD80(s32 a0);
    extern void func_8012B260(u8 *a0);
    extern void func_8018452C();
    extern s32 D_801955F0;
    extern u8 D_801F3EFC[];
    extern u8 D_801F3FA4[];
    extern u8 D_801F41DC[];
    extern u8 D_801F3EA4[];
    extern u8 D_80195120[];
    extern u8 D_80195184[];

    if (func_801845F4() == 1) {
        return;
    }
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        func_8018487C(a0);
        D_801955F0 = func_80183954(a0);
        if (func_80183B30(a0, D_801955F0) == 1) {
            *(s16 *)(a0 + 0x34) = 8;
            return;
        }
        if (func_80183994(a0, D_801955F0) != 1) {
            return;
        }
        *(s16 *)(a0 + 0x34) = 3;
        return;
    case 1:
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x34) = 2;
    case 2:
        if (func_80183994(a0, D_801955F0) == 1) {
            *(s16 *)(a0 + 0x34) = 3;
            return;
        }
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 0x34) = 0;
            func_8012A828(a0, D_801F3EFC);
            *(s32 *)(a0 + 0x1C) = 0x2D;
        }
        return;
    case 3:
        func_8012B23C(a0);
        func_8012B178(a0, 0xA0000);
        *(s16 *)(a0 + 0x34) = 4;
        return;
    case 4:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x20;
        if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = -0x400;
        }
        if (func_8012CBCC(a0) & 0x2000) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = -0x400;
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(a0 + 0x34) = 5;
            func_8002D4C8(0xB09, 0);
            func_8013C9C4(D_80195184);
        }
        return;
    case 5:
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 0x34) = 6;
        }
        return;
    case 6:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += 0x80;
        if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) >= 0) {
            func_8012B2CC(a0);
            func_8012B23C(a0);
            func_8012B178(a0, 0xFFFC8000);
            func_8012A828(a0, D_801F3FA4);
            *(s16 *)(a0 + 0x34) = 7;
        }
        return;
    case 7:
        if (((s32 (*)(s32, s32))func_8012CC1C)(a0, (s32)&D_80195144) & 0x8000) {
            *(s16 *)(a0 + 0x34) = 0;
            func_8018452C(a0);
            *(s32 *)(a0 + 0xDC) &= ~0x10;
        }
        return;
    case 8:
        func_8012A828(a0, D_801F41DC);
        *(s32 *)(a0 + 0x1C) = 0x14;
        *(s16 *)(a0 + 0x34) = 9;
        return;
    case 9:
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 0x34) = 0xA;
            *(s16 *)(a0 + 0x98) = 0;
        }
        return;
    case 10:
        func_8012A828(a0, D_801F3EA4);
        func_8012B200((u8 *)a0);
        func_8012B14C(a0, (s32)D_80195120);
        func_8012AD80(a0);
        func_8012B23C(a0);
        func_8012B260((u8 *)a0);
        *(s16 *)(a0 + 0x34) = 0xB;
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s32 *)(a0 + 0xDC) = (*(s32 *)(a0 + 0xDC) & ~0x20) | 0x48;
        return;
    }
}


extern void func_8012AD80(s32 a0);

s32 func_80183954(s32 a0) {
    u8 *s0;
    s16 val;

    func_8012AD80(a0);
    s0 = (u8 *)a0;
    val = *(s16 *)(s0 + 0xA);
    return ((val - 0xB0) < -0xA01) ? 0 : 2;
}


extern s32 rand(void);
extern u8 D_801202A0[];
extern u8 D_801955F4[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012ADE4(u8 *a0);
extern void func_8012B260(u8 *a0);
extern void func_8017C294(s32 a0, s16 *a1, s16 a2);
extern s32 func_80183C2C();

s32 func_80183994(s32 a0, s32 a1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801F3EFC[];
    s32 hit;
    u8 *p;
    s32 i;
    s32 t;

    hit = 0;
    p = D_801202A0;
    i = 0;
    do {
        if (*(u16 *)p == 0xB0) {
            if (hit == 0) {
                func_8012B260((u8 *)a0);
                hit = 1;
            }
            if (func_80183C2C(a0, p, a1) != 0) {
                func_8012ADE4((u8 *)a0);
                func_8012B260((u8 *)a0);
                *(s16 *)(a0 + 0x98) = 0;
                t = 0;
                if (func_80183C2C(a0, p, 4) != 1) {
                    return t;
                }
                *(s32 *)(a0 + 0xDC) |= 0x10;
                return 1;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);

    if (*(s16 *)(a0 + 0x98) == 0) {
        func_8012A828(a0, D_801F3EFC);
    }
    t = *(s32 *)(a0 + 0xE8) - 1;
    *(s32 *)(a0 + 0xE8) = t;
    if (t <= 0) {
        *(s32 *)(a0 + 0xE8) = 0x2D;
        if (rand() % 3 != 0) {
            goto ret0;
        }
        func_8017C294(a0, (s16 *)((rand() & 1) * 8 + (s32)D_801955F4), 1);
        func_8017C294(a0, (s16 *)((rand() & 1) * 8 + ((s32)D_801955F4 + 0x10)), 1);
    }
ret0:
    return 0;
}


extern void func_8012B14C(s32 a0, s32 a1);
extern s32 D_801950E4;

s32 func_80183B30(s32 param_1, s32 param_2)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801950D8;
    unsigned short uVar2;

    switch (param_2) {
    case 0:
        *(unsigned int *)(param_1 + 0xdc) |= 0x20;
        return 1;
    case 1:
        if ((*(unsigned int *)(param_1 + 0xdc) & 4) != 0) {
            return 0;
        }
        uVar2 = *(unsigned short *)(param_1 + 0xfc) ^ 1;
        *(unsigned short *)(param_1 + 0xfc) = uVar2;
        func_8012B14C(param_1, (s32)&D_801950E4 + (s16)uVar2 * 12);
        *(unsigned int *)(param_1 + 0xdc) |= 4;
        break;
    case 2:
        if ((*(unsigned int *)(param_1 + 0xdc) & 4) == 0) {
            return 0;
        }
        func_8012B14C(param_1, (s32)&D_801950D8);
        *(unsigned int *)(param_1 + 0xdc) &= 0xfffffffb;
        break;
    }
    return 0;
}


extern s32 func_801840C0();

s32 func_80183C2C(s32 param_1, s32 param_2, u32 param_3)
{
    unsigned short sp10[3];
    unsigned short sp18[3];
    unsigned int addr;
    s32 ret;

    addr = (*(unsigned int *)(param_1 + 0x58) & 0xFFFFFFF) | 0x80000000;
    if (param_3 & 1) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    if (param_3 & 2) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xC);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xE);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    if (param_3 & 4) {
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 4);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 4);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 8);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 8);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
        sp10[0] = *(unsigned short *)(addr + 6);
        sp10[1] = *(unsigned short *)(addr + 0xA);
        sp10[2] = *(unsigned short *)(addr + 0xC);
        sp18[0] = *(unsigned short *)(addr + 6);
        sp18[1] = *(unsigned short *)(addr + 0xA);
        sp18[2] = *(unsigned short *)(addr + 0xE);
        ret = func_801840C0(param_1, param_2, sp10, sp18);
        if (ret == 1) {
            return 1;
        }
    }
    return 0;
}


extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_801840C0(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 sp10[2];
    s32 sp18[2];

    func_8012F214(a0, a2, (s32)sp10);
    func_8012F214(a0, a3, (s32)sp18);
    return func_80135888(*(s32 *)(a1 + 0x20), *(s32 *)(a1 + 0x58),
                         (s32)sp10, (s32)sp18) != 0;
}


extern void func_80184738(s32 a0);
extern void func_80188228(void);

void func_80184134(s32 param_1) {
    func_801823B8();
    *(s16 *)(param_1 + 2) = 0xD;
    *(s16 *)(param_1 + 0x34) = 0;
    func_80184738(1);
    func_80178BF8();
    func_80178CBC(param_1, *(s32 *)(param_1 + 0xCC));
    func_80188228();
}


/* Declarations: the five names already at file scope above (func_8012B23C L15,
 * func_8012B14C L16, func_8012A828 L17, func_8012BEE8 L36, func_80184738 L335)
 * are NOT redeclared.  Every new name is spelled exactly as this TU already
 * spells it further down (func_8012CBCC L813/L862, func_8013C9C4 L2566,
 * func_801439C0 L1885, func_80178D18 L2586, func_8001AAD0 L818/L865,
 * func_80172658 L369/L443, D_80126B58 L371/L1271/L3304) so the duplicate
 * declarations are identical; the rest follow the fleet canon.  The
 * engine_core.h hits for these symbols are all inside DEFINE_ macros
 * (block scope), so they cannot conflict at file scope.
 *
 * CODEGEN NOTE — the one non-obvious lever (REGALLOC-PERM/$v0>$v1>$v0, 3 ins).
 * Case 1, case 5 and the case-2 clamp-hit arm all reach the SAME
 * `(*(u16 *)(s0+0x34))++` tail at 0x80184304.  Writing case 2's arm as a
 * `goto` into that shared tail compiles to the right instruction sequence but
 * allocates the post-call block's constant/pointer pair as $v1/$v0 instead of
 * the target's $v0/$v1.  Writing the increment out LONGHAND in case 2 instead
 * matches: gcc-2.7.2 runs the cross-jumping `jump_optimize` pass AFTER
 * register allocation, so the duplicated tail is allocated in its own block
 * (giving the target's registers) and only then merged back into the shared
 * `j 0x80184304`.  Both forms emit 162 instructions; only the duplicated form
 * is byte-identical.  (Cookbook §176-B's law — "1-4 off is usually NOT
 * register allocation" — with a new lever: a shared tail reached by `goto`
 * vs. duplicated in the source is a REGALLOC dial, not just a jump dial.) */

extern s32 func_8012CBCC(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_8012E8C4(u8 *a0);
extern void func_8013C9C4(void *a0);
extern s32 func_80172658(s32 *a0);
extern s32 func_801439C0(s32 a0);
extern s32 func_801789AC(s32 a0);
extern void func_80178D18(void);
extern void func_8001AAD0(s32 a0, s32 a1);
extern void func_8001931C(void);

extern s32 D_80126B58;
extern s32 D_80195138;
extern u8 D_8019514C[];
extern u8 D_80195184[];
extern s16 D_801EBA7C;
extern u8 D_801F4654[];

void func_8018418C(s32 a0) {
    s32 s0 = a0;

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        break;
    case 1:
        func_8012B23C(s0);
        goto incr;
    case 2:
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) - 0x20;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = -0x400;
        }
        if (func_8012CBCC(s0) & 0x2000) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = -0x400;
            *(s32 *)(s0 + 0x1C) = 0x3C;
            func_8013C9C4(D_80195184);
            /* longhand on purpose — see CODEGEN NOTE; cross-jumped into 0x80184304 */
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 3:
        func_8012E8C4((u8 *)s0);
        if (func_8012BEE8(s0) != 0) {
            D_801EBA7C = 3;
            *(s16 *)(s0 + 0x34) = 0;
            func_8001931C();
            if (*(s32 *)(s0 + 0xD0) != 0) {
                func_801439C0(*(s32 *)(s0 + 0xD0));
            }
        }
        break;
    case 4:
        if (func_80172658(&D_80126B58) != 0) {
            D_801EBA7C = 3;
            *(s16 *)(s0 + 0x34) = 0;
            func_8001931C();
        }
        break;
    case 5:
        if ((*(u16 *)(s0 + 0x5C) & 1) == 0) {
            break;
        }
        *(u16 *)(s0 + 0x5C) = *(u16 *)(s0 + 0x5C) & 0xFFFE;
        *(s16 *)(s0 + 0x98) = 0;
        func_8012B23C(s0);
        func_8012B14C(s0, (s32)&D_80195138);
        func_8001AAD0(1, 0x4331);
    incr:
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        break;
    case 6:
        if ((((s32 (*)(s32, s32))func_8012CC1C)(s0, (s32)D_8019514C) & 0x2000) == 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8012B23C(s0);
            func_8012A828(s0, D_801F4654);
        }
        break;
    case 7:
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) + 0x20;
        if (*(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) > 0x400) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0x400;
        }
        if (func_8012CBCC(s0) & 0x2000) {
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0x400;
            *(s32 *)(s0 + 0x1C) = 0x3C;
            *(s16 *)(s0 + 0x34) = 3;
            func_8013C9C4(D_80195184);
        }
        break;
    }

    if (func_801789AC(s0) == 1) {
        ((void (*)(s32))func_80178D18)(s0);
        *(s16 *)(s0 + 2) = 0xE;
        func_80184738(0);
    }
}


#include "common.h"

extern void func_8018823C(void);
extern s32 func_800D0CE0(void);
extern void func_8012C218(void *a0);
extern u8 D_801952D8[];

void func_80184414(void *arg0) {
    if (*(void **)((char *)arg0 + 0xCC) != (void *)D_801952D8 || func_800D0CE0() != 0) {
        func_8018823C();
        func_8012C218(arg0);
    }
}


void func_8018446C(s32 param_1) {
    extern s32 func_8012BEE8(s32 a0);
    extern s32 func_80172670(s32 *a0);
    extern s32 func_80172658(s32 *a0);
    extern void func_801472DC(void);
    extern s32 D_80126B58;
    extern u16 D_80126B62;
    extern u8 D_801954B8[];
    extern u8 D_801952D8[];

    s32 *s0 = (s32 *)param_1;

    if (func_8012BEE8((s32)s0) == 0) {
        return;
    }

    {
        s32 *s1 = &D_80126B58;

        if (func_80172670(s1) != 0) {
            *(s16 *)((s32)s0 + 2) = 0xC;
        } else if (func_80172658(s1) != 0) {
            *(s16 *)((s32)s0 + 2) = 0xC;
        } else {
            return;
        }

        if (func_80172658(s1) != 0 && (s16)D_80126B62 < -0xA01) {
            func_8018490C(s0, (s32)D_801954B8, 3);
        } else {
            func_8018490C(s0, (s32)D_801952D8, 1);
            func_801472DC();
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern s32 D_801950D8;
extern u8 D_801F3EFC[];

void func_8018452C(s32 a0)
{
    s32 s0;

    func_8012B200((u8 *)a0);
    s0 = a0;
    func_8012B14C(s0, (s32)&D_801950D8);
    func_8012A828(s0, (void *)D_801F3EFC);
    *(u16 *)(s0 + 0xFC) = rand() & 1;
    *(s32 *)(s0 + 0x1C) = 0x2D;
    *(u16 *)(s0 + 0x34) = 0;
}


void func_80184590(s32 param_1) {
    extern u8 D_80126B5C;
    extern s32 func_8012C588(s32 a0, s32 a1);

    *(s32 *)(param_1 + 4) = *(s32 *)&D_80126B5C;
    func_8012C588(0xBA, param_1);
}


void func_801845C0(s32 param_1) {
    extern u8 D_80126B5C;
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

    *(s32 *)&D_80126B5C = *(s32 *)(param_1 + 4);
    func_8012C658(0xBA, 1, param_1);
}


s32 func_801845F4(s32 param_1) {
    extern s32 func_80172670(s32 *a0);
    extern s32 func_80172658(s32 *a0);
    extern void func_801746DC(void);
    extern void func_8018490C(s32 *a0, s32 a1, s16 a2);
    extern s32 D_80126B58;
    extern u8 D_801954B8[];
    extern u8 D_801953D8[];

    s32 *s0 = (s32 *)param_1;
    s32 *s1 = &D_80126B58;
    s32 var;

    if (func_80172670(s1) == 0 && func_80172658(s1) == 0) {
        return 0;
    }
    if (func_80172658(s1) != 0 && *(s16 *)((s32)s1 + 0xA) < -0xA01) {
        if ((*(u32 *)((s32)s0 + 0xDC) & 0x80) == 0) {
            func_801746DC();
            *(u32 *)((s32)s0 + 0xDC) |= 0x80;
        }
        var = *(u32 *)((s32)s0 + 0xDC);
        if ((var & 0x30) != 0) {
            return 0;
        }
        *(u32 *)((s32)s0 + 0xDC) = var & ~0x80;
        *(s16 *)((s32)s0 + 2) = 0xC;
        if ((*(u32 *)((s32)s0 + 0xDC) & 8) != 0) {
            func_8018490C(s0, (s32)D_801954B8, 3);
        } else {
            func_8018490C(s0, (s32)D_801953D8, 2);
            *(s16 *)((s32)s0 + 0x98) = 0;
        }
        return 1;
    } else {
        if ((*(u32 *)((s32)s0 + 0xDC) & 8) != 0) {
            func_801746DC();
            *(s32 *)((s32)s0 + 0x1C) = 0x10;
            *(s16 *)((s32)s0 + 2) = 0xF;
            return 1;
        }
        return 0;
    }
}


void func_80184738(s32 a0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p == 0xB0) {
            if ((*(u16 *)(p + 0x70) & 0xF) == 0) {
                *(s16 *)(p + 0xFC) = a0;
                *(u16 *)(p + 0x70) |= 0x800;
            }
        }
    }
}


void func_8018479C(void) {
    extern u16 D_80126B66;
    extern u16 D_80126B5E;
    extern s32 D_80195414;

    D_80195414 = ((u32)D_80126B5E | (((s32)(s16)D_80126B66 - 0x180) << 16));
}


extern void func_8012A568(void (*a0)(void));
    extern s32 func_8018263C();
    void func_801847C8(void) {
        ((void (*)(void *))func_8012A568)((void *)func_8018263C);
    }


extern void func_8012A568(void (*a0)(void));
    extern s32 func_801823EC(s32 a0);
    void func_801847F0(void) {
        ((void (*)(void *))func_8012A568)((void *)func_801823EC);
    }


extern void func_80184918(s32 arg0, s32 arg1);
    void func_80184818(s32 arg0) {
        func_80184918(arg0, 0x1D);
    }


extern void func_80184918(s32 arg0, s32 arg1);
    void func_80184838(s32 arg0) {
        func_80184918(arg0, 0x1E);
    }


extern void func_80029124(s32 arg0, s32 arg1);
    void func_80184858(void) {
        func_80029124(0x9E, 1);
    }


#include "common.h"

extern s32 D_80126B60;
extern s32 D_80195640;
extern void func_8012B14C(s32 a0, s32 a1);

void func_8018487C(s32 param_1)
{
    s32 tmp;
    s32 iVar1;
    s32 quot;
    s32 scaled;
    s32 *p;

    tmp = *(s32 *)(param_1 + 8) + -0x900000;
    iVar1 = D_80126B60 - tmp;
    if (iVar1 < 0) {
        iVar1 = iVar1 + 0xfffff;
    }
    quot = iVar1 >> 0x14;
    scaled = quot << 0xf;
    if (scaled > 0) {
        scaled = 0;
    } else {
        if (scaled < -0x40000) {
            scaled = -0x40000;
        }
    }
    p = &D_80195640;
    *p = scaled + -0x20000;
    func_8012B14C(param_1, (s32)p - 4);
}


void func_8018490C(s32 *a0, s32 a1, s16 a2) {
        *(s32 *)((s32)a0 + 0xCC) = a1;
        *(s16 *)((s32)a0 + 0x102) = a2;
    }


extern void func_800D0C48(s32 a0);

void func_80184918(s32 arg0, s32 arg1) {
    func_800D0C48(1);
    *(s16 *)((s32)arg0 + 0x104) = 1;
    *(s32 *)((s32)arg0 + 0xE4) = 0x1E;
    *(s32 *)((s32)arg0 + 0xE0) = arg1;
}


extern s32 func_80143BDC(u16 *a0);

void func_80184964(s32 a0) {
    u16 pos[3];
    s32 hit;
    u32 ptr;

    pos[0] = *(u16 *)(a0 + 0x6);
    pos[1] = *(u16 *)(a0 + 0xA);
    pos[2] = *(u16 *)(a0 + 0xE);
    pos[1] += 0x28;
    pos[2] += 0x52;
    func_80143BDC(pos);
    hit = func_80143BDC(pos);
    if (hit != 0) {
        ptr = *(u32 *)(hit + 0xCC);
        *(u16 *)(ptr + 0x1A) = 0x6000;
        *(u16 *)(ptr + 0x18) = 0x6000;
    }
}


extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801F45D4;

void func_801849D4(s32 param_1) {
    if ((func_80029178(0x125) & 0xFF) != 0) {
        func_8012A828(param_1, &D_801F45D4);
        func_80029124(0x125, 0);
    }
}


s32 func_80184A28(s32 *a0) {
    return *(s16 *)((char *)a0 + 0xFE) == 0;
}


extern s32 func_800D0CE0(void);
    s32 func_80184A34(void) {
        return func_800D0CE0() != 0;
    }


extern u8 D_801202A0[];
extern void func_8012C098(void *param_1);

void func_80184A54(void)
{
    int i;
    u8 *p;
    int s2;

    i = 0;
    p = D_801202A0;
    s2 = 0x6C;
    do {
        u16 v = *(u16 *)p;
        if ((u32)(v - 0x123) < 2 || v == s2) {
            ((void (*)(u8 *))func_8012C098)(p);
        }
        i = i + 1;
        p = p + 0x10C;
    } while (i < 0x60);
    return;
}



extern void (*D_801957F8[])(void);

void func_80184ACC(void *a0) {
    D_801957F8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);

void func_80184B08(s32 param_1) {
    extern u8 D_801CA540;
    extern u8 D_80195648;
    extern u8 D_80195734;
    extern s32 D_8019105C;
    extern u8 D_80126B5C;
    extern s32 D_80126B60;
    extern s32 D_80126B64;
    s32 v0;

    *(s16 *)(param_1 + 0x76) = 10;
    *(u16 *)(param_1 + 0x5C) = 0x8C00;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(v0, (s32)&D_801CA540);
        *(u32 *)(param_1 + 0x58) =
            (((*(u16 *)(param_1 + 0x70) & 1) << 4) + (s32)&D_80195648) | 0x60000000;
        if ((*(u16 *)(param_1 + 0x70) & 1) != 0) {
            *(s16 *)(param_1 + 2) = 2;
            *(u16 *)(param_1 + 0x5C) |= 0x200;
            func_8012A828(param_1, (void *)&D_8019105C);
            *(s32 *)(param_1 + 4) = *(s32 *)&D_80126B5C;
            *(s32 *)(param_1 + 8) = D_80126B60;
            *(s32 *)(param_1 + 0xC) = D_80126B64;
        } else {
            *(s16 *)(param_1 + 2) = 1;
            func_8012A828(param_1, (void *)&D_80195734);
        }
        func_8012B2CC(param_1);
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801F432C;
extern s32 D_80195744;

void func_80184C0C(s32 param_1) {
    *(u16 *)(param_1 + 6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
    *(u16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
    if (*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x90) == (s32)&D_801F432C) {
        *(s16 *)(param_1 + 2) = 3;
        func_8012A828(param_1, &D_80195744);
        *(s32 *)(param_1 + 0x1c) = 0xe;
    }
}


typedef struct { s16 a, b, c; } SV3_80184C98;
extern void func_8012B23C(s32 a0);
extern void func_80185098(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern u8 D_801957EC[];

void func_80184C98(s32 param_1) {
    SV3_80184C98 pt;
    u16 v1;
    s32 v0;

    v1 = *(u16 *)(param_1 + 0x5C);
    if (v1 & 1) {
        *(u16 *)(param_1 + 0x5C) = v1 & 0xFFFE;
        if (*(u16 *)(param_1 + 0x5E) == 9) {
            func_8012B23C(param_1);
            pt.a = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
            pt.b = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA);
            pt.c = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
            if (((s32 (*)(s32, s32))func_80185098)(param_1, (s32)&pt) == 1) {
                func_8012B14C(param_1, (s32)D_801957EC);
            }
            *(u16 *)(param_1 + 2) = 5;
        }
    }
}


typedef struct { s16 a, b, c; } SV3_80184D50;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801957EC[];
extern void func_8012B23C(s32 a0);
extern void func_80185098(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);

void func_80184D50(s32 param_1) {
    SV3_80184D50 pt;
    s32 t;
    u16 h;

    t = *(s32 *)(param_1 + 0x1C) - 1;
    *(s32 *)(param_1 + 0x1C) = t;
    if (t == 0) {
        h = *(u16 *)(param_1 + 0xE);
        *(u16 *)(param_1 + 2) = 4;
        *(u16 *)(param_1 + 0x98) = 0;
        *(u16 *)(param_1 + 0xE) = h + 0x68;
        func_8012B23C(param_1);

        pt.a = D_80126B5E;
        pt.b = D_80126B62;
        pt.c = D_80126B66;
        if (((s32 (*)(s32, s32))func_80185098)(param_1, (s32)&pt) == 1) {
            func_8012B14C(param_1, (s32)D_801957EC);
        }
        func_8012AD80(param_1);
        *(s32 *)(param_1 + 0x1C) = 0x1E;
    }
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h, where the
 * real TU's SV3 {short a,b,c} lives (via ../shared/engine_core.h). Function-scoped local
 * name so it collides with nothing; integrator may drop this and reuse the TU's own SV3. */
typedef struct { s16 a, b, c; } SV3_80184E00;

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801957CC;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8 D_801152A8[];

extern void func_80185098(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8014C978(void);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8001AAD0(s32 a0, s32 a1);

void func_80184E00(s32 param_1)
{
    SV3_80184E00 pt;
    SV3_80184E00 sv1;
    SV3_80184E00 sv2;

    pt.a = D_80126B5E;
    pt.b = D_80126B62;
    pt.c = D_80126B66;
    func_80185098(param_1, (s32)&pt);

    if (func_8012CBCC(param_1) & 0x6000) {
        *(s16 *)(param_1 + 2) = 6;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        return;
    }

    if (*(s16 *)(param_1 + 0xFC) != 0) {
        return;
    }

    func_8012F214(param_1, (s32)&D_801957CC, (s32)&sv1);
    func_8012F214(param_1, (s32)&D_801957CC + 8, (s32)&sv2);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&sv1, (s32)&sv2) == 0) {
        return;
    }

    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, (s32)&sv2, (s32)D_801152A8);

    *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x34) = 4;
    *(s16 *)(param_1 + 0xFC) = 1;
    func_8001AAD0(1, 0x4292);

    D_80126B66 = D_80126B66 + 0x20;
}


typedef struct { s16 a, b, c; } SV3_80184F48;
extern u8 D_801957DC;
extern void func_80185098(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8001AAD0(s32 a0, s32 a1);

void func_80184F48(s32 param_1)
{
    SV3_80184F48 sv1;
    SV3_80184F48 sv2;
    SV3_80184F48 pt;

    pt.a = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6);
    pt.b = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA);
    pt.c = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE);
    func_80185098(param_1, (s32)&pt);

    if (func_8012CBCC(param_1) & 0x6000) {
        *(s16 *)(param_1 + 2) = 6;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        return;
    }

    if (*(s16 *)(param_1 + 0xFC) != 0) {
        return;
    }

    func_8012F214(param_1, (s32)&D_801957DC, (s32)&sv1);
    func_8012F214(param_1, (s32)&D_801957DC + 8, (s32)&sv2);

    if (func_80135888(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20), *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x58), (s32)&sv1, (s32)&sv2) == 0) {
        return;
    }

    *(s16 *)(param_1 + 0xFC) = 1;
    *(s16 *)(*(s32 *)(param_1 + 0x64) + 0x34) = 1;
    func_8001AAD0(1, 0x4331);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80185048(s32 param_1)
{
    s32 *temp_v0;

    temp_v0 = *(s32 **)(param_1 + 0x20);
    temp_v0[1] ^= 0x80000000;
    if (func_8012BEE8(param_1) != 0) {
        func_8012C218(param_1);
    }
}


/* The TU (src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c) forward-declares this function FOUR
 * times, all `extern void func_80185098(s32 a0, s32 a1);` -- and two of those call sites
 * (func_80184C98, func_80184D50) already work around the wrong return type themselves, by
 * calling through `((s32 (*)(s32, s32))func_80185098)(...)`. So the TU's own authors already
 * knew the real function returns a value; `void` is simply what's on file, and we must not
 * touch it (TU is authoritative). Defining under the C name `func_80185098` with a non-void
 * return conflicts with those declarations (verified: real cc1 raises the exact
 * "conflicting types for `func_80185098'" error the blocker names). Declaring the DEFINITION
 * itself `void` is not an option either (verified): with a void return type, cc1 elides the
 * `return 0;` / `return 1;` computation entirely as dead code, so $v0 never gets set -- the
 * two callers that DO read the return value via the function-pointer cast would get garbage,
 * and the compiled bytes for the body's tail no longer match the .s target at all.
 *
 * Fix: give the definition a DIFFERENT C-level name and use GNU C's function-scope
 * `asm("label")` to pin its assembler symbol to the real one. The C front end's
 * conflicting-types check is per-C-identifier, so `func_80185098_impl` never collides with
 * the TU's `func_80185098` declarations; the linker resolves every existing call site (both
 * the direct calls and the pointer-cast ones) to this object's `func_80185098:` label exactly
 * as before. Byte-verified against a hand probe against the pinned cc1 before use here. */

extern u8 D_801957EC[];

s32 func_80185098_impl(s32 a0, s32 a1) asm("func_80185098");
s32 func_80185098_impl(s32 a0, s32 a1) {
    s16 val;

    val = *(s16 *)(a1 + 2);
    if (val < *(s16 *)(a0 + 0xA) || *(s16 *)(a0 + 0xFC) != 0) {
        return 0;
    }
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = -ratan2(*(s16 *)(a1 + 4) - *(s16 *)(a0 + 0xE),
                                                   val - *(s16 *)(a0 + 0xA));
    func_8012B2CC(a0);
    func_8012B14C(a0, (s32)D_801957EC);
    return 1;
}



extern void (*D_801958B8[])(void);

void func_80185120(void *a0) {
    D_801958B8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018515C(void *param_1)
{
    extern u8 D_80195834[];
    extern u16 D_801958A8[];
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8012CAE4(void *a0);
    extern void func_8012C1B8(void);
    extern void func_8001C810(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);

    u16 f;
    u8 *s1;
    s32 v0;

    f = *(u16 *)((s32)param_1 + 0x70);
    s1 = &D_80195834[(f & 1) * 0x34];

    if ((f & 0x80) != 0) {
        *(s32 *)((s32)param_1 + 0x78) = (s32)s1;
        *(u16 *)((s32)param_1 + 0x5C) = *(u16 *)(s1 + 2);
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)((s32)param_1 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(param_1);
            return;
        }
        func_8001C810(v0, *(s32 *)(s1 + 4));
        *(s32 *)((s32)param_1 + 0x58) = *(s32 *)(s1 + 8) | 0x60000000;
        *(s32 *)(*(s32 *)((s32)param_1 + 0x20) + 4) |= 0x8000;
    } else {
        if (func_8012C354((s32)param_1, (s32)s1) == 0) {
            return;
        }
    }

    *(s32 *)((s32)param_1 + 0xDC) = 1;
    func_8012A828((s32)param_1, D_801958A8);
    *(u8 *)((s32)param_1 + 0x75) = 0;

    if ((*(s16 *)((s32)param_1 + 0x70) & 0x8000) != 0) {
        *(s16 *)((s32)param_1 + 2) = 1;
    } else {
        *(s16 *)((s32)param_1 + 2) = 3;
    }
}


void func_80185268(short *a0)
{
    *(u16 *)((char *)a0 + 0x2) = 2;

    if ((*(u16 *)((char *)a0 + 0x70) & 0x800) != 0) {
        if (*(s32 *)((char *)a0 + 0xDC) != 0) {
            *(s32 *)((char *)a0 + 0x1C) = 0x96;
        } else {
            *(s32 *)((char *)a0 + 0x1C) = 0x4B;
        }
    } else {
        if (*(s32 *)((char *)a0 + 0xDC) != 0) {
            *(s32 *)((char *)a0 + 0x1C) = 0x4B;
        } else {
            *(s32 *)((char *)a0 + 0x1C) = 0xB4;
        }
    }
}


#include "common.h"

/* Decl environment: func_8012BEE8 (9342), func_8012B178 (2605) and func_8012B200
 * (8844) are already at file scope in this TU with these exact spellings; repeated
 * identical decls are byte-neutral and match the TU's house style.
 * func_8018567C is NOT in scope at this point and is DEFINED `s32 ...` further down
 * (line 9635), so it is declared at BLOCK scope exactly as the neighbours
 * func_80185480 / func_801854DC (lines 9519 / 9534) already do. */
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801852B0(s32 a0)
{
    extern void func_8018567C(s32 a0, s32 a1);

    s32 s0 = a0;
    s32 v;
    u8 *p;

    if (func_8012BEE8(a0) == 0 && *(s16 *)(s0 + 0xFC) == 0) {
        return;
    }

    /* `p` must be a SEPARATE local live across the if/else: global.c's copy
     * preference from the func_8012B200 arg load gives it $a0, so the copy
     * `addu $a0,$s0,$zero` is emitted at p's definition and sched2 slides it
     * behind the `lh` to fill the guard's load-delay -- reorg then parks it in
     * the `beqz` delay slot (target idx 14). Spelled inline at the call it is
     * copy-propagated away and the copy lands next to the `jal` instead (+1 ins). */
    p = (u8 *)s0;

    if (*(s16 *)(s0 + 0xFC) != 0) {
        v = *(s32 *)(s0 + 0xDC);
        if (v == 0) {
            *(s16 *)(s0 + 2) = 5;
            return;
        }
    } else {
        v = *(s32 *)(s0 + 0xDC);
    }

    /* cookbook-index L22 / §5a + the §34 zero-byte fence toolkit: reorg's eager
     * filler otherwise COPIES this `xori` out of the join thread into the
     * `bnez` delay slot above and redirects the branch one insn further on.
     * `stop_search_p` halts that search on an asm insn, so the target's
     * unfilled `nop` (idx 18) survives. Emits nothing. */
    __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    v ^= 1;
    *(s32 *)(s0 + 0xDC) = v;
    func_8012B200(p);
    *(u16 *)(s0 + 0x5C) |= 0x400;

    /* Both arms: the target sets up $a0/$a1 BEFORE the `= 7` / `= 6` store, so
     * the store (not the `li $a1`) is what reorg pulls into the jal's delay slot.
     * Plain source order cannot reach that -- sched2 ranks `li $v0,K` (priority 2,
     * it feeds the `sh`) ahead of the priority-1 arg copies. The $a0/$a1 register
     * pins place the copies, and the zero-byte re-tie on the $a1 pin (ADD-8 ->
     * §245 addendum, "the re-tie barrier pins call-arg setup to source order")
     * stops the constant from being rematerialised down at the call. */
    if (*(s32 *)(s0 + 0xDC) == 0) {
        register s32 q __asm__("$4") = s0;  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        s32 r = 0xFFF80000;
        __asm__ __volatile__("" : "=r"(r) : "0"(r));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        *(s16 *)(s0 + 2) = 7;
        func_8012B178(q, r);
        v = 0x20;
    } else {
        register s32 q2 __asm__("$4") = s0;  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
        s32 r2 = 0x100000;
        __asm__ __volatile__("" : "=r"(r2) : "0"(r2));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        *(s16 *)(s0 + 2) = 6;
        func_8012B178(q2, r2);
        v = 0x10;
    }

    *(s32 *)(s0 + 0x1C) = v;
    func_8018567C(s0, 0x61A);
}


extern s32 func_80029178(s32 arg);

void func_80185388(void *a0) {
    *(s16 *)((char *)a0 + 2) = 4;
    if ((func_80029178(0x9E) & 0xFF) != 0) {
        *(s16 *)((char *)a0 + 0xFC) = 1;
    }
}


extern s32 func_80185548(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801853CC(s32 a0) {
    u16 v1 = *(u16 *)(a0 + 0x34);

    switch (v1) {
    case 0:
        if (*(s16 *)(a0 + 0xFC) != 0) {
            *(u16 *)(a0 + 0x34) = v1 + 1;
            func_8012B178(a0, 0xFFF80000);
            *(s32 *)(a0 + 0x1C) = 0x20;
        }
        break;
    case 1:
        if (func_80185548(a0) == v1) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 2:
        break;
    }
}


void func_80185464(void *a0) {
        s16 v0;
        v0 = *(s16 *)((char *)a0 + 0xfc);
        if (!v0) {
            *(s16 *)((char *)a0 + 0x2) = 2;
        }
    }


extern void func_80185480_dummy(void);
void func_80185480(void *a0) {
    extern s32 func_80185548(s32);
    extern void func_8018567C(s32, s32);

    if (func_80185548((s32)a0) == 1) {
        if ((*(s16 *)((s32)a0 + 0x70) & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 2) = 1;
        } else {
            *(s16 *)((s32)a0 + 2) = 3;
        }
        func_8018567C((s32)a0, 0x61B);
    }
}


void func_801854DC(void *a0) {
    extern s32 func_80185548(s32);
    extern void func_8018567C(s32, s32);

    if (func_80185548((s32)a0) == 1) {
        if ((*(s16 *)((s32)a0 + 0x70) & 0x8000) != 0) {
            *(s16 *)((s32)a0 + 2) = 1;
        } else {
            *(s16 *)((s32)a0 + 2) = 3;
        }
        func_8018567C((s32)a0, 0x61B);
        *(u16 *)((s32)a0 + 0x5C) &= ~0x400;
    }
}


#include "common.h"

/* func_80185548 -- ov_SC02_011 / ov_SC02_011_jr_8017AE2C   [target: 77 ins]
 *
 * The engine "save camera vector, run the collision probe, restore on hit" body.
 * Structure lifted from src/shared/engine_core.h's DEFINE_func_8012E014 (the byte-proven
 * idiom for this exact func_8012F0BC / func_8012B2CC / func_8012F1A4 triad over the
 * D_80126B5C/60/64 vector).
 *
 * KEY FINDING (this is what closed the last 2 instructions):
 *   D_80126B5E / D_80126B62 / D_80126B66 are NOT independent globals -- they are the HIGH
 *   HALFWORDS of the 16.16 fixed-point words D_80126B5C / D_80126B60 / D_80126B64 (little
 *   endian: sym+2 is the integer part). Writing them as three separate `extern u16` symbols
 *   is byte-wrong in two ways at once:
 *     (a) gcc's memory disambiguator sees three distinct SYMBOL_REFs, finds NO dependency
 *         between `sw D_80126B64` and `lhu D_80126B66`, and sched1 hoists the free load to
 *         the top of the region -> 21 mismatches; and
 *     (b) papering over (a) by reusing ONE local for both the out[2] readback and the
 *         halfword refill merges them into a SINGLE pseudo whose live range now runs past
 *         the `addiu $a2, $sp, 0x40` argument setup, so it conflicts with $a2 and first-fit
 *         hands it $a3 -- the REGALLOC-PERM/$a3>$a2 residual (2 mismatches).
 *   Expressing the halfword as `*((u16 *)&gVecZ + 1)` fixes BOTH at once: the shared base
 *   gives sched1 the true memory dependency that keeps `sw` before `lhu`, AND the two values
 *   stay separate pseudos, so out[2] dies at the `sw` (free to take $a2) while the halfword
 *   lives into the jal delay slot (conflicts with $a2, takes $a3). Exactly the target.
 *   The %hi/%lo relocations come out against D_80126B5C/60/64 with in-place addend 2, which
 *   the HI16/LO16 pair resolves to D_80126B5E/62/66 -- identical linked bytes (same form the
 *   TU's constant-index global array accesses already emit).
 *
 * `base` (the unconditional `&D_80126B58` pointer local, computed before the `if`) is
 * load-bearing: it is what forces the 4-callee-saved-register frame (sw s1/ra/s2/s0) and
 * keeps the buffer base live in $s2 across the three intervening calls. Without it only 3
 * regs are saved and every later stack offset drifts by a word.
 */

s32 func_80185548(s32 param_1) {
    /* asm-label alias per engine_core.h DEFINE_func_8012E014: the TU already carries
     * `extern u8 D_80126B5C;`, so a plain `extern s32 D_80126B5C;` is a conflicting-types
     * hard error, and the cast-at-use `*(s32 *)&D_80126B5C` form makes gcc force_reg the
     * constant address (+ CSE'd `la` pseudos). The alias gives a real s32 object at the same
     * assembler symbol, so every access stays a direct lw/sw. */
    extern s32 gVecX __asm__("D_80126B5C");
    extern s32 gVecY __asm__("D_80126B60");
    extern s32 gVecZ __asm__("D_80126B64");
    extern s32 D_80126B58;
    extern void func_8012AD80(s32 a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
    extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern s32 func_8012BEE8(s32 a0);
    s32 in[4];
    s32 out[4];
    s32 tmp[4];
    u8 buf[8];
    u8 *base = (u8 *)&D_80126B58;

    func_8012AD80(param_1);
    if (*(u8 *)(param_1 + 0x74) != 0) {
        in[0] = gVecX;
        in[1] = gVecY;
        in[2] = gVecZ;
        func_8012F0BC((s32 *)(*(s32 *)(param_1 + 0x20) + 0x34), in, tmp);
        func_8012B2CC(param_1);
        func_8012F1A4((s32 *)(*(s32 *)(param_1 + 0x20) + 0x34), (s32)tmp, out);
        gVecX = out[0];
        gVecY = out[1];
        gVecZ = out[2];
        *(s16 *)(buf + 0) = *((u16 *)&gVecX + 1);
        *(s16 *)(buf + 2) = *((u16 *)&gVecY + 1);
        *(s16 *)(buf + 4) = *((u16 *)&gVecZ + 1);
        if ((func_80133784(1, base + 0x88, (s32)buf) & 0x8000) != 0) {
            gVecX = in[0];
            gVecY = in[1];
            gVecZ = in[2];
        }
    }
    return func_8012BEE8(param_1) != 0;
}


#include "common.h"

extern s32 D_80126B58;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80013478(s32 a0, s32 a1);

s32 func_8018567C(s32 a0, s32 a1) {
    s32 v1 = a0;
    s32 s1 = a1;
    s32 s0 = 0;
    extern u16 D_80126B62;
    s16 val = (s16) D_80126B62;
    s32 base = (s32) &D_80126B58;
    s32 dist;
    s32 v0;

    if (val < -0x981) {
        return 0;
    }

    dist = func_80013478(base + 4, v1 + 0x88);
    if (dist <= 0x190000) {
        dist -= 0x4000;
        s0 = 0x60;
        if (dist > 0xC7FFF) {
            register s32 tmp __asm__("$3") = dist - 0xC8000;  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
            v0 = tmp / 8533;
        } else {
            v0 = dist / 26425 - 31;
        }
        s0 -= v0;
    }

    func_8002D4C8(s1 & 0xFFFF, (s0 & 0x7F) | 0x1000);
    return 1;
}











void func_8018576C(u8 *vb)
{
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    u8 *p;
    s32 t1;
    register s32 i __asm__("$11");  // !FAKE: pin $11 — NEEDED DIFFERS (P36 rung B tus9)
    s32 t0;
    s32 k;
    u8 *pkt;
    u32 *ot;
    u32 *otp;
    u8 *v4;
    s32 flag, flag2, otz;
    s32 d;
    s32 z;
    u32 mAnd;
    u32 mOr;
    short vv[16];
    s16 vz0;

#define RS(o) (*(s16 *)((s32)vb + (o)))

    p = (u8 *)(((*(u32 *)((s32)vb + 0x58)) & 0xFFFFFFF) | 0x80000000);
    vv[1] = RS(0x8A) + *(u16 *)(p + 8) - 0x40;
    vv[5] = RS(0x8A) + *(u16 *)(p + 8) - 0x40;
    vv[9] = RS(0x8A) + *(u16 *)(p + 0xA) + 0x40;
    vv[13] = RS(0x8A) + *(u16 *)(p + 0xA) + 0x40;
    vz0 = RS(0x8C) - 0x50;
    ot = (u32 *)&D_800A6610[((u16)D_800B9A02) << 14];
    vv[14] = vz0;
    vv[10] = vz0;
    vv[6] = vz0;
    vv[2] = vz0;
    d = *(s16 *)(p + 4);
    if ((d - 0x20) >= 0) {
        z = (d - 0x20) / 2;
    } else {
        z = (0x20 - d) / 2;
    }
    i = -2;
    v4 = (u8 *)&vv[4];
    mOr = 0xFFFFFF;
    mAnd = 0xFF000000;
    k = -2 * z;
    t1 = k + z;
    t0 = k;
    for (; i < 2; i++) {
        pkt = D_800A5E60;
        D_800A5E60 = pkt + 0x18;
        *(u8 *)(pkt + 3) = 5;
        *(u32 *)(pkt + 4) = 0;
        *(u8 *)(pkt + 7) = 0x28;
        vv[0] = vv[8] = RS(0x88) + t0;
        vv[4] = vv[12] = RS(0x88) + t1;
        gte_ldv3(&vv[0], v4, &vv[8]);
        gte_rtpt();
        gte_stflg(&flag);
        gte_stsxy3(pkt + 8, pkt + 0xC, pkt + 0x10);
        gte_ldv0(&vv[12]);
        gte_rtps();
        gte_stflg(&flag2);
        flag |= flag2;
        gte_stsxy(pkt + 0x14);
        gte_avsz4();
        gte_stotz(&otz);
        if ((flag & ~0x1000) == 0) {
            s32 tt = otz + 0x29;
            if (tt > 0xFFF) {
                tt = 0x1000;
            }
            otp = (u32 *)(tt * 4 + (u32)ot);
            *(u32 *)pkt = (*(u32 *)pkt & mAnd) | (*(u32 *)otp & mOr);
            *(u32 *)otp = (*(u32 *)otp & mAnd) | ((u32)pkt & mOr);
        }
        t1 += z;
        t0 += z;
    }
#undef RS
}



extern void (*D_801958E8[])(void);

void func_801859E0(void *a0) {
    D_801958E8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern u8 D_801958D8[];
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);

void func_80185A1C(void *a0) {
    s32 ret;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(ret, 0);
    *(u16 *)((u8 *)a0 + 0x2) = 1;
    *(u16 *)((u8 *)a0 + 0x5C) = 0x40;
    *(s32 *)((u8 *)a0 + 0x58) = (u32)D_801958D8;
}


void func_80185A84(void) {
}

















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80185A8C(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 1);
  new_var = 0x100000;
}

void func_80185AAC(s32 arg0)
{
    extern u8 D_801958F0[];
    extern s32 D_801958F4;
    extern s32 D_801958F6;
    extern s32 D_801958F8;
    extern s32 D_801958FA;
    extern s32 D_801958FC;
    extern s32 D_801958FE;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern void func_80185BA4(void *a0);
    u8 *a2 = D_801958F0;
    s16 self6;
    s16 selfA;
    s16 selfE;

    self6 = *(s16 *)(arg0 + 0x6);
    if (self6 + *(s16 *)&D_801958F4 < *(s16 *)&D_80126B5E &&
        *(s16 *)&D_80126B5E < self6 + *(s16 *)&D_801958F6) {
        selfA = *(s16 *)(arg0 + 0xA);
        if (selfA + *(s16 *)&D_801958F8 < *(s16 *)&D_80126B62 &&
            *(s16 *)&D_80126B62 < selfA + *(s16 *)&D_801958FA) {
            selfE = *(s16 *)(arg0 + 0xE);
            if (selfE + *(s16 *)&D_801958FC < *(s16 *)&D_80126B66 &&
                *(s16 *)&D_80126B66 < selfE + *(s16 *)&D_801958FE) {
                *(u32 *)(arg0 + 0x58) = (u32)(a2 + 0x10) | 0x40000000;
                *(s16 *)(arg0 + 0x5C) = 0x800;
                func_80185BA4(arg0);
            }
        }
    }
}


extern void func_800D0C48(s32 a0);
extern void (*D_80195910[])(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80185BA4(s32 a0) {
    func_800D0C48(1);
    *(s32 *)(a0 + 0x1C) = 0x20;
    func_80178B18(a0, (s32) D_80195910);
    func_8012AD44((s32 *)a0, 2);
}


u16 func_80185BF4(s32 *a0) {
    return *(u16*)((s32)a0 + 0x34);
}


extern void func_8001AAA0(s32 arg);
    void func_80185C00(void) {
        func_8001AAA0(0x2F);
    }


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_80185C20(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 3);
  new_var = 0x51AB;
}


extern void (*D_80195948[])(void);

void func_80185C40(void *a0) {
    D_80195948[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012C194(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801865B0(s32 arg0);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801E5340;
extern u8 D_8019595C;
extern s32 D_801EB518;
extern u8 D_80195968;
extern u8 D_801959B8;
extern u8 D_80195998;
extern u8 D_80195A94;

void func_80185C7C(s32 a0) {
    s32 self = a0;
    s32 obj;
    s32 h;
    s32 v0;
    u16 v1;
    s32 pad[8];

    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(self + 0x20) = h;
    if (h == 0) {
        goto L_fail;
    }

    if (*(s16 *)(self + 0x70) != 0) {
        goto L_da8;
    }

    func_8001C214(h, (s32)&D_801E5340);
    obj = ((s32 (*)(void))func_8012C194)();
    *(s32 *)(self + 0xCC) = obj;
    if (obj != 0) {
        goto L_ce4;
    }

L_fail:
    func_8012CAE4((void *)self);
    return;

L_ce4:
    func_8001CB6C((u8 *)obj, (s32)&D_8019595C, 0x2F0, 0x138);
    func_801865B0(self);

    *(u16 *)(obj + 0x18) = 0x2200;
    *(u16 *)(obj + 0x1A) = 0x1600;
    *(u8 *)(obj + 0x27) = 0xED;
    *(u32 *)(obj + 4) |= 0x51000000;
    func_80128EA8(obj, (s32)&(*(u8 *)&D_801EB518), (s32)&D_80195968);

    *(u8 *)(self + 0xC0) = 1;
    *(s32 *)(self + 0xBC) = (s32)&D_801959B8;
    *(s32 *)(self + 0x58) = (s32)&D_80195998 | 0x40000000;
    *(u16 *)(self + 0x5C) = 0x8000;
    *(s16 *)(self + 0xAE) = -3;

    v0 = *(s32 *)(self + 0xC4);
    v1 = *(u16 *)(self + 0xA);
    *(s32 *)(self + 0xB4) = 0;
    *(u8 *)(self + 0xC1) = 0;
    *(s32 *)(self + 0xC4) = v0 | 2;
    *(u16 *)(self + 0xFE) = v1;
    func_8012AD50((void *)self);
    return;

L_da8:
    func_8001CA1C(h, 0);

    *(u16 *)(*(s32 *)(self + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)(self + 0x20) + 0x1A) = 0x3800;
    *(u32 *)(*(s32 *)(self + 0x20) + 4) |= 0x71000000;

    *(s32 *)(self + 0x14) = 0xFFFE0000;
    *(s32 *)(self + 0x18) = 0xFFFD0000;

    func_8012A828(self, &D_80195A94);
    func_8012AD44((s32 *)self, 0xA);
}


#include "common.h"

extern void func_8013CABC(void);
extern void func_80186728(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186070(s32 a0);
extern s32 func_80185FA0();
extern int func_80178970(void);
extern s32 func_80188114(void);
extern s32 D_801EB520;

void func_80185E20(s32 a0) {
    s32 t;
    u16 delta;
    u16 cnt;

    t = *(s32 *)(a0 + 0x1C);
    if (t == 0x30) {
        func_8013CABC();
    } else if (t == 0x10) {
        func_80186728(*(void **)(a0 + 0xD0));
    }

    if (*(u16 *)(a0 + 0x102) & 1) {
        *(u16 *)(*(s32 *)(a0 + 0x64) + 6) -= 3;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 8) -= 3;
        delta = *(u16 *)(a0 + 6) - 3;
    } else {
        *(u16 *)(*(s32 *)(a0 + 0x64) + 6) += 3;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 8) += 3;
        delta = *(u16 *)(a0 + 6) + 3;
    }
    *(u16 *)(a0 + 6) = delta;

    {
        u16 raw = *(u16 *)(a0 + 0x102);
        s32 old = D_801EB520;
        cnt = raw + 1;
        *(u16 *)(a0 + 0x102) = cnt;
        if (old == 0) {
            D_801EB520 = func_80188114();
        }
    }

    if (func_8012BEE8(a0) != 0 && D_801EB520 != 0) {
        func_80186070(a0);
    } else {
        t = *(s32 *)(a0 + 0x1C);
        if (t < 0x48 && (t & 3) == 0) {
            func_80185FA0(a0);
        }
    }
    ((s32 (*)(s32))func_80178970)(a0);
}


extern u16 D_800B99D8;
extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_80185FA0(s32 param_1)
{
    s32 q;
    s32 iVar5;
    s32 iVar4;
    s16 sVar1;

    iVar5 = 0;
    do {
        q = func_80132EF4(param_1, 0x22);
        if (q != 0) {
            iVar4 = iVar5 + (D_800B99D8 & 4) * 3 - 0x2A;
            *(s16 *)(q + 6) = *(u16 *)(q + 6) + iVar4;
            *(s16 *)(q + 0xA) = *(u16 *)(q + 0xA) - 0x20;
            *(s16 *)(q + 0xE) = *(u16 *)(q + 0xE) - 0x28;
            iVar4 = iVar4 << 16;
            if ((iVar4 >> 16) >= 0) {
                sVar1 = (s16)((iVar4 >> 16) << 7);
            } else {
                sVar1 = (s16)(-((iVar4 >> 16) << 7));
            }
            *(s16 *)(q + 0x34) = sVar1 + 0x1000;
            *(s32 *)(q + 0x14) = 0xFFFE0000;
            *(s32 *)(q + 0x18) = 0xFFFD0000;
        }
        iVar5 += 0x18;
    } while (iVar5 < 0x49);
}



extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018FE20(s32 a0);
extern void func_80186734(void *a0);
extern void func_8018ADE4(void);
extern void func_8018AE08(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186070(s32 a0) {

    extern u8 D_801959C8[];
    s32 obj;            /* $s0 */
    s32 self = a0;
    s32 t0;
    s32 t1;
    s32 t2;

    obj = *(s32 *)(self + 0x20);
    func_8001CA1C(obj, (s32)D_801959C8);

    *(u16 *)(self + 0xA) = *(u16 *)(self + 0xA) - 0xA0;
    *(u16 *)(self + 0xE) = *(u16 *)(self + 0xE) - 0x10;
    *(u16 *)(obj + 0x18) = 0x2C00;
    *(u16 *)(obj + 0x1A) = 0x1C00;
    do { *(u32 *)(obj + 4) = *(u32 *)(obj + 4) | 0x1000000; } while (0);  // !FAKE: do-while — a LOOP-note scheduling barrier (sched.c:2058-2074; P36 R7)

    t0 = *(s32 *)(self + 0xCC);
    *(u16 *)(t0) = 0;
    *(s32 *)(self + 0xCC) = func_80143970(self);

    *(s32 *)(self + 0x14) = 0xFFF80000;
    *(u16 *)(self + 0x5C) = 0;
    *(s32 *)(self + 0x1C) = 8;
    func_8012AD44((s32 *)self, 3);

    obj = *(s32 *)(self + 0x64);
    t1 = *(s32 *)(obj + 0x20);
    *(u32 *)(t1 + 4) = *(u32 *)(t1 + 4) | 0x80000000;
    func_8018FE20(obj);

    *(u16 *)(obj + 0x5C) = 0;
    func_8012AD44((s32 *)obj, 4);

    t2 = *(s32 *)(self + 0xD0);
    if (t2 != 0) {
        *(u16 *)(t2 + 0x2C) = 0;
        func_80186734((void *)t2);
    }

    func_8018ADE4();
    func_8018AE08(self + 4);

    func_8002D4C8(0x5ED, 0);
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186790(void *a0);
extern u8 D_80195A94;

void func_80186184(s32 a0) {
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2C00;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3800;
    func_8012A828(a0, &D_80195A94);
    *(u16 *)(a0 + 0xFC) = 0;
    *(s32 *)(a0 + 0x1C) = 0x10;
    func_8012AD44((s32 *)a0, 4);
    if (*(s32 *)(a0 + 0xD0) != 0) {
        func_80186790(*(void **)(a0 + 0xD0));
    }
}


#include "common.h"

extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801867BC(void *a0);

void func_801861FC(void *arg0) {
    s32 s0 = (s32)arg0;
    s32 val;

    *(s32 *)(s0 + 0x1C) = 4;
    func_8012B200((u8 *)s0);
    func_8012AD44((s32 *)s0, 5);

    val = *(s32 *)(s0 + 0xD0);
    if (val != 0) {
        func_801867BC((void *)val);
    }
}


void func_80186250(s32 arg0) {
    extern void func_80186548(s32 *a0);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern s8 D_801959A8[];

    *(s32 *)((s32)arg0 + 0x58) = (s32)&D_801959A8;
    func_80186548((s32 *)arg0);
    func_8012AD44((s32 *)arg0, 6);
}


s32 func_80186290(s32 arg0) {
        return *(u16*)(arg0 + 0x2) == 0x6;
    }


#include "common.h"

extern s32 func_801439C0(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801292C8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_801862A4(int a0)
{
    s32 s0 = a0;
    u8 *ptr;
    s32 val1;
    s32 val2;
    s32 t2;

    func_801439C0(*(s32 *)(s0 + 0xCC));
    func_8012B200((u8 *)s0);

    *(s32 *)(s0 + 0x14) = 0x80000;
    *(u16 *)(s0 + 0x6) = D_80126B5E;
    *(u16 *)(s0 + 0xE) = D_80126B66;

    ptr = *(u8 **)(s0 + 0x20);
    val1 = *(u16 *)(ptr + 0x18);
    *(s16 *)(s0 + 0xDC) = (val1 << 16) >> 19;

    ptr = *(u8 **)(s0 + 0x20);
    val2 = *(u16 *)(ptr + 0x1A);
    *(s16 *)(s0 + 0xDE) = (val2 << 16) >> 19;

    func_8012AD44((s32 *)s0, 7);

    t2 = *(s32 *)(s0 + 0xD0);
    if (t2 != 0) {
        func_801292C8((u8 *)t2);
    }

    func_8002D4C8(0x635, 0);
}


extern s32 func_80188168(void);
    void func_80186354(void) {
        func_80188168();
    }


extern s32 func_8013CAE8(void);
    void func_80186374(void) {
        func_8013CAE8();
    }


extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186394(s32 a0) {
    func_8012AD44((s32 *)a0, 8);
    *(s32 *)(a0 + 0x1C) = 0x40;
    func_8002D4C8(0x5EC, 0);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801863D4(void *a0) {
    func_8012AD44((s32 *)a0, 9);
}



extern void (*D_80195CC4[])(void);

void func_801863F4(void *a0) {
    D_80195CC4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_80195CF0[];
extern s32 D_801EB520;
extern void (*D_80195B5C[])(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001AAA0(s32 arg);

void func_80186430(s32 a0) {
    s32 self = a0;
    u32 idx;
    s32 t0;
    s32 t1;

    for (idx = 0; idx < 8; idx++) {
        if (*(u16 *)(self + 0x5E) == D_80195CF0[idx]) {
            {
                u16 tmp;
                t0 = *(s32 *)(self + 0x64);
                tmp = *(u16 *)(t0 + 6);
                D_801EB520 = 0;
                *(u16 *)(t0 + 6) = tmp + 1;
            }
            *(s32 *)(self + 0x1C) = 0x50;
            *(u16 *)(self + 0x102) = 0;
            *(u16 *)(self + 6) = *(u16 *)(self + 6) + 1;
            func_8012AD44((s32 *)self, 2);

            t1 = func_80132EF4(self, 0x32);
            *(s32 *)(self + 0xD0) = t1;
            if (t1 != 0) {
                u16 vE;
                *(u16 *)(t1 + 6) = *(u16 *)(self + 6);
                *(u16 *)(t1 + 0xA) = *(u16 *)(self + 0xA);
                vE = *(u16 *)(self + 0xE);
                *(s16 *)(t1 + 0x2C) = -0xA0;
                *(s32 *)(t1 + 0x34) = self;
                *(u16 *)(t1 + 0xE) = vE;
            }

            func_80178B18(self, (s32) D_80195B5C);

            *(u8 *)(self + 0xC1) = 0;
            *(u16 *)(self + 0x5C) = 0;
            *(u16 *)(self + 0x5E) = 0;
            func_8002D4C8(0x5EB, 0);
            func_8001AAA0(0x30);
            *(u16 *)(self + 0x5E) = 0;
            goto end;
        }
    }
    *(u16 *)(self + 0x5E) = 0;
end:
    func_8002D4C8(0x426, 0);
}


void func_80186548(s32 *a0) {
        *(s32 *)((s32)a0 + 0x48) = 0x1400;
        *(s32 *)((s32)a0 + 0x14) = 0;
    }


void func_80186558(s32 a0) {
    s32 v;

    func_8012AD80(a0);
    v = *(s32 *)(a0 + 0x14);
    if (v > 0x14000) {
        *(s32 *)(a0 + 0x48) = -0x1400;
    } else if (v < -0x14000) {
        *(s32 *)(a0 + 0x48) = 0x1400;
    }
}


void func_801865B0(s32 arg0) {
        s32 *p = *(s32 **)((s32)arg0 + 0xcc);
        *(u16 *)((s32)p + 0x8) = *(u16 *)((s32)arg0 + 0x6);
        *(s16 *)((s32)p + 0xa) = *(u16 *)((s32)arg0 + 0xa) - 0xe0;
        *(s16 *)((s32)p + 0xc) = *(u16 *)((s32)arg0 + 0xe) - 0x10;
    }


int func_801865E4(int a0, void* a1)
{
    s16 stack_buf[8];
    s16 v0;
    s32 result;
    s32 ret;

    v0 = ((s16 *)a1)[2];
    stack_buf[0] = v0;
    v0 = ((s16 *)a1)[3];
    stack_buf[4] = v0;
    v0 = ((s16 *)a1)[5];
    stack_buf[5] = v0;
    stack_buf[1] = v0;
    v0 = ((s16 *)a1)[6];
    stack_buf[6] = v0;
    stack_buf[2] = v0;

    result = func_80186680((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = ((s16 *)a1)[7];
        stack_buf[6] = v0;
        stack_buf[2] = v0;
        result = func_80186680((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}


extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

s32 func_80186680(s32 arg0, s32 arg1, s32 arg2)
{
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    struct { u16 x, y, z, w; } a;
    struct { u16 x, y, z, w; } b;

    func_8012F214(arg0, arg1, &a);
    func_8012F214(arg0, arg2, &b);
    func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b);
}


extern s32 func_8017E358();
    void func_801866E8(void) {
        func_8017E358();
    }


extern void func_8017E43C(void);
    void func_80186708(void) {
        func_8017E43C();
    }


void func_80186728(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }


void func_80186734(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x3;
    }


s32 func_80186740(void)
{
    typedef struct { unsigned char b[4]; } __attribute__((packed, aligned(1))) Block4;

    extern Block4 D_801EB524;
    extern unsigned char D_801EB525;
    extern unsigned char D_801EB526;

    unsigned char *p = (unsigned char *)&D_801EB524;

    if (*p < 0xF8U) {
        *p += 4;
        D_801EB525 += 4;
        D_801EB526 += 8;
    }
}



extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80186790(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x4;
        func_8002D4C8(0x634, 0);
    }


void func_801867BC(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0;
    }



// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_80186818();
extern void (*D_80195D18[])(int);

void func_801867CC(int param_1)
{
    ((void (*)(void))func_80186818)();
    D_80195D18[*(unsigned short *)(param_1 + 2)](param_1);
}


extern void func_80129350(s32 *a0, s32 a1);
extern void func_80133060(s32 *a0, s32 a1, s32 a2);

void func_80186818(s32 *a0) {
    s32 *s0;
    s32 a1;

    s0 = a0;
    a1 = *(s32 *)((u8 *)s0 + 0x34);
    func_80129350(s0, a1);

    a1 = (s32)((u8 *)s0 + 0x4);
    *(s16 *)((u8 *)s0 + 0xA) = *(u16 *)((u8 *)s0 + 0xA) + *(u16 *)((u8 *)s0 + 0x2C);
    func_80133060((s32 *)((u8 *)s0 + 0x4), a1, -0x180);
}


#include "common.h"

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern u8 D_80195D30[];
extern s32 func_800291B4(s32 arg);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80129374(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
void func_80186AA0(s32 a0);
s32 func_80186B1C(void *a0, void *a1);

void func_80186868(s32 a0)
{
    s32 self = a0;
    s32 flags;
    s32 v1;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 dx __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 dy __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 dz __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
    s32 t;
    s32 p, q;
    s32 sum;

    *(s32 *)(self + 0x1C) = *(s32 *)(self + 0x1C) + 1;
    if ((u8)func_800291B4(0xCE) == 1) {
        flags = *(s32 *)(self + 0x1C);
        if (flags & 0x20) {
            func_80186AA0(self);
            return;
        }
        v0 = D_80126B5E; v1 = *(u16 *)(self + 6); v1 = v0 - v1;
        v0 = v1 << 16;
        dx = v1; if (v0 < 0) { dx = -v1; }
        v0 = D_80126B62; v1 = *(u16 *)(self + 0xA); v1 = v0 - v1;
        v0 = v1 << 16;
        dy = v1; if (v0 < 0) { dy = -v1; }
        v0 = D_80126B66; v1 = *(u16 *)(self + 0xE); v1 = v0 - v1;
        v0 = v1 << 16;
        dz = v1; if (v0 < 0) { dz = -v1; }
        v0 = (s16)dx;
        if (v0 >= 0x201) { func_80186AA0(self); return; }
        v0 = (s16)dy;
        if (v0 >= 0x201) { func_80186AA0(self); return; }
        v0 = (s16)dz;
        if (v0 >= 0x201) { func_80186AA0(self); return; }
        if (flags & 1) {
            t = func_80132EF4(self, 0x22);
            if (t != 0) {
                func_80129374(t, self);
                *(s16 *)(*(s32 *)(t + 0x20) + 0x18) = 0x5000;
                *(s16 *)(*(s32 *)(t + 0x20) + 0x1A) = 0x5000;
            }
        }
        if ((*(s32 *)(self + 0x1C) & 3) == 0) {
            v0 = (s16)dx;
            p = v0 * v0;
            v0 = (s16)dz;
            q = v0 * v0;
            sum = p + q;
            if (sum <= 0x30000) {
                func_8002D4C8(0x646, (u16)((((0x30000 - sum) * 127) / 0x30000) | 0x1000));
                *(s16 *)(self + 0xFC) = 1;
            } else {
                func_80186AA0(self);
            }
        }
        if ((*(s32 *)(self + 0x1C) & 0x1F) >= 8) {
            if (func_80186B1C((void *)self, D_80195D30) != 0) {
                ((struct { u16 w; } *)&D_80126B96)->w |= 0x4000;
                D_80126B98 = 0xC;
            }
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186AA0(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        func_8002D4C8(4, 0x646);
        *(s16 *)(a0 + 0xFC) = 0;
    }
}



extern void (*D_80195D40[])(void);

void func_80186AE0(void *a0) {
    D_80195D40[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

s32 func_80186B1C(void *a0, void *a1) {
    s16 stack_buf[8];
    s16 v0;
    s32 result;
    s32 ret;

    v0 = ((s16 *)a1)[6];
    stack_buf[2] = v0;
    v0 = ((s16 *)a1)[7];
    stack_buf[5] = 0;
    stack_buf[1] = 0;
    stack_buf[6] = v0;
    v0 = ((s16 *)a1)[2];
    stack_buf[4] = v0;
    stack_buf[0] = v0;

    result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);

    if (result != 0) {
        ret = 1;
    } else {
        v0 = ((s16 *)a1)[3];
        stack_buf[4] = v0;
        stack_buf[0] = v0;
        result = func_8012DEB8((s32)a0, (s32)&stack_buf[0], (s32)&stack_buf[4]);
        ret = (result != 0);
    }
    return ret;
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_80186BB0(void *a0) {
    s32 v0;
    s32 sp10[3];

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (!v0) {
        func_8012CAE4(a0);
    } else {
        func_8001C2C4(v0);

        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x600;
        func_8012B2CC((s32)a0);

        sp10[1] = 0;
        sp10[0] = 0;
        sp10[2] = 0x240000;
        func_8012B14C((s32)a0, (s32)sp10);

        func_8012AD50(a0);
    }
}


void func_80186C30(s32 a0) {
    s32 self = a0;
    s32 v0;
    extern s32 func_80029178(s32);
    extern void func_8012C1B8(void);
    extern void func_8001C214(s32, s32);
    extern s32 func_8012C588(s32, s32);
    extern void func_8012CAE4(void *);
    extern void func_80185A8C(void);
    extern s32 D_801E4D54;

    if ((func_80029178(0x16) & 0xFF) != 0) {
        goto L88;
    }
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(self + 0x20) = v0;
    if (v0 == 0) {
        goto L88;
    }
    func_8001C214(v0, (s32)&D_801E4D54);
    do { v0 = func_8012C588(0x110, self); } while (0);
    if (v0 != 0) {
        goto L98;
    }
L88:
    func_8012CAE4((void *)self);
    goto LCA0;
L98:
    ((void (*)(s32))func_80185A8C)(self);
LCA0:
    return;
}


void func_80186CB4(s32 a0)
{
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_80185C20(void);

    s32 s0 = a0;
    s32 ret = func_80178970();

    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) += 1;
        }
        break;
    case 1:
        if (ret == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)(s0);
        ((void (*)(s32))func_80185C20)(s0);
        break;
    }
}


void func_80186D3C(void) {
}

void func_80186D44(void) {
}

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
    extern s32 D_801EB518;
    void func_80186D4C(void *arg0) {
        ((void (*)(s32, s32))func_80128ED8)(M2C_FIELD(arg0, s32 *, 0xCC), &D_801EB518);
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186184(s32 a0);
extern void func_80186548(s32 *a0);
extern void func_80186558(s32 a0);
extern int func_80178970(void);
extern void func_8018B1B0(void);

void func_80186D78(s32 *a0) {
    if (*(u16 *)((s32)a0 + 0x34) == 0) {
        func_8012AD80((s32)a0);
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((s32)a0 + 0x100) = 0x80;
            *(s32 *)((s32)a0 + 0x1C) = 0x30;
            (*(u16 *)((s32)a0 + 0x34))++;
            func_80186548(a0);
        }
    } else {
        if (func_8012BEE8((s32)a0) != 0) {
            func_80186184((s32)a0);
        } else {
            func_80186558((s32)a0);
        }
    }
    ((int (*)(s32))func_80178970)((s32)a0);
    func_8018B1B0();
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern int func_80178970(void);

void func_80186E24(s32 a0) {
    if (func_8012BEE8(a0) == 0) {
        if ((*(s32 *)(a0 + 0x1C) & 3) == 0) {
            func_8012C658(0x110, 1, a0);
        }
    }
    if (*(s16 *)(a0 + 0x98) == 0) {
        func_801861FC(a0);
    }
    ((s32 (*)(s32))func_80178970)(a0);
}


extern int func_80178970(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_80186250(s32 a0);

    void func_80186E94(s32 arg0) {
        u16 val_34;
        s16 val_fe, val_a;
        val_34 = *(u16 *)(arg0 + 0x34);
        if (val_34 == 0) {
            if (func_8012BEE8(arg0) != 0) {
                *(s32 *)(arg0 + 0x14) = 0x10000;
                *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            }
        } else {
            val_fe = *(s16 *)(arg0 + 0xFE);
            val_a = *(s16 *)(arg0 + 0xA);
            if (val_a < (val_fe - 0xA0)) {
                func_8012AD80(arg0);
            } else {
                func_80186250(arg0);
            }
        }
        ((void (*)(s32))func_80178970)(arg0);
    }


    extern int func_80178970(void);
    extern void func_80186558(int a0);
    extern int func_801865E4(int a0, void *a1);
    extern void func_801862A4(int a0);
    extern char D_801959A8[];
    void func_80186F24(int param_1)
    {
        ((void (*)(void))func_80178970)();
        func_80186558(param_1);
        if (func_801865E4(param_1, (void *)&D_801959A8) != 0) {
            func_801862A4(param_1);
        }
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern int func_80178970(void);

void func_80186F74(s32 a0) {
    s32 t0;
    s16 val0;

    t0 = *(s32 *)(a0 + 0x20);
    val0 = *(s16 *)(t0 + 0x18);

    if (val0 > 0) {
        s32 temp;
        s16 val;
        u16 a, b;
        u32 flags;

        func_8012AD80(a0);

        temp = *(s32 *)(a0 + 0x20);
        a = *(u16 *)(a0 + 0xDC);
        b = *(u16 *)(temp + 0x18);
        *(s16 *)(temp + 0x18) = (s16)(b - a);

        temp = *(s32 *)(a0 + 0x20);
        a = *(u16 *)(a0 + 0xDE);
        b = *(u16 *)(temp + 0x1A);
        *(s16 *)(temp + 0x1A) = (s16)(b - a);

        temp = *(s32 *)(a0 + 0x20);
        val = *(s16 *)(temp + 0x18);

        if (val == 0) {
            flags = *(u32 *)(temp + 0x04);
            flags |= 0x80000000;
            *(u32 *)(temp + 0x04) = flags;
        }
    }

    ((void (*)(s32))func_80178970)(a0);
}


#include "common.h"

extern int func_80178970(void);
extern void func_8013C9C4(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern void (*D_80195CAC[])(void);
extern void func_801863D4(void *a0);

void func_80187018(s32 a0)
{
    s32 s0 = a0;

    func_80178970();
    if ((*(u32 *)(s0 + 0x1C) & 0xF) == 0) {
        func_8013C9C4(&D_80195CAC);
    }
    if (func_8012BEE8(s0) != 0) {
        func_801863D4((void *)s0);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012C218(void *a0);

void func_8018707C(s32 a0)
{
    extern s16 D_801EBA08;

    if (func_80178970() == 0) return;
    if (D_801EBA08 != 0) return;
    ((void (*)(s32))func_80178D18)(a0);
    ((void (*)(s32))func_8012C218)(a0);
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_801870D0(s32 param_1) {
    s32 s0;

    s0 = param_1;
    func_8012AD80(s0);
    if (*(s16 *)(s0 + 0x98) == 0) {
        func_8012C218((void *)s0);
    }
}


#include "common.h"

extern void func_8001CD9C(s32, void *);
extern void func_800233CC(void *, u16);


extern Block4 D_801E9E30;
extern Block4 D_801EB524;
extern Block4 D_801EB528;

void func_80187110(s32 a0) {
    u8 *s0;
    s32 *s1;
    s32 *v1;
    s32 *a0_ptr;
    s8 pad[32];  /* Force larger stack frame */

    s1 = (s32 *)a0;
    s0 = (u8 *)&D_801EB524;

    // Call func_8001CD9C with field at offset 0x20 in s1, and s0
    func_8001CD9C(s1[8], (s32 *)s0);  // 0x20 / 4 = 8

    // Call func_800233CC with s0 and 0x80
    func_800233CC(s0, 0x80);

    // Copy 4 bytes from D_801E9E30 to D_801EB524
    *(Block4 *)s0 = D_801E9E30;

    // Copy 4 bytes from D_801E9E30 to D_801EB528
    D_801EB528 = D_801E9E30;

    // Set field at offset 0x18 to 0x800
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x18) = 0x800;

    // Set field at offset 0x1A to 0x1000
    v1 = s1[8];
    *(s16 *)((s8 *)v1 + 0x1A) = 0x1000;

    // OR field at offset 0x4 with 0x50000000
    a0_ptr = s1[8];
    *(s32 *)((s8 *)a0_ptr + 0x4) |= 0x50000000;

    // Set field at offset 0x2 in s1 to 1
    *(s16 *)((s8 *)s1 + 0x2) = 1;

    (void)pad;  /* Avoid warning */
}



extern Block4 D_801EB524;
extern u8 D_801EB525;
extern u8 D_801EB526;

void func_801871CC(void) {
    if (D_801EB524.b[0] < 0xc0) {
        D_801EB524.b[0] += 4;
    }
    if (D_801EB525 < 0xc0) {
        D_801EB525 += 4;
    }
    if (D_801EB526 < 0x20) {
        D_801EB526 += 4;
    }
}


extern s32 func_80186740(void);
    void func_80187234(void) {
        func_80186740();
    }


extern s32 func_80186740(void);

void func_80187254(s32 arg0) {
    s32 a0 = *(s32 *)(arg0 + 0x20);
    if (*(s16 *)(a0 + 0x18) < 0x6000) {
        *(s16 *)(a0 + 0x18) = *(s16 *)(a0 + 0x18) + 0x800;
    }
    if (*(s16 *)(a0 + 0x1A) < 0x6000) {
        *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x1A) + 0x800;
    }
    func_80186740();
}



extern Block4 D_801EB524;
extern unsigned char D_801EB525;
extern unsigned char D_801EB526;

void func_801872B4(s32 arg0) {
    s32 a0;
    u32 v1;

    a0 = *(s32 *)(arg0 + 0x20);
    if (*(s16 *)(a0 + 0x18) > 0x800) {
        *(s16 *)(a0 + 0x18) = *(s16 *)(a0 + 0x18) - 0x200;
    }
    if (*(s16 *)(a0 + 0x1A) > 0x800) {
        *(s16 *)(a0 + 0x1A) = *(s16 *)(a0 + 0x1A) - 0x200;
    }
    v1 = D_801EB524.b[0];
    if (v1 >= 0xC1) {
        D_801EB524.b[0] = v1 - 4;
        D_801EB525 -= 4;
        D_801EB526 -= 8;
    }
}



extern Block4 D_801EB524;
extern u8 D_801EB525;
extern u8 D_801EB526;

void func_8018734C(void *a0) {
    s16 *p;
    s32 t;
    u8 v;
    p = *(s16 **)((s32)a0 + 0x20);
    if (*(s16 *)((s32)p + 0x18) > 0x800) {
        *(s16 *)((s32)p + 0x18) = *(s16 *)((s32)p + 0x18) - 0x200;
    }
    if (*(s16 *)((s32)p + 0x1A) > 0x800) {
        *(s16 *)((s32)p + 0x1A) = *(s16 *)((s32)p + 0x1A) - 0x200;
    }
    t = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t & 0x10) {
        v = ((t & 0xF) >> 1) + 9;
    } else {
        v = 0x10 - ((t & 0xF) >> 1);
    }
    D_801EB524.b[0] = v * 12;
    D_801EB525 = v * 12;
    D_801EB526 = v * 2;
}



extern void (*D_80195D50[])(void);

void func_801873FC(void *a0) {
    D_80195D50[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 func_8014BF6C(void);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012AD50(void *a0);

void func_80187438(s32 a0) {
    s32 s1;
    u8 n;

    s1 = a0;
    n = func_8014BF6C();
    while (n != 0) {
        func_8012C658(0x112, n - 1, s1);
        n--;
    }
    func_8012AD50((void *)s1);
}


void func_801874A0(void) {
}


extern void (*D_80195D58[])(void);

void func_801874A8(void *a0) {
    D_80195D58[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80187654(u8 *a0);
extern s32 func_8012AD50(void *a0);
extern s32 D_801DF580;
extern s32 D_81195D48;

void func_801874E4(s32 a0)
{
    s32 s1 = a0;
    s32 s0;

    if ((*(s32 *)(s1 + 0x20) = s0 = ((s32 (*)(void))func_8012C1B8)()) == 0) goto L_end;
    func_8001C214(s0, (s32)&D_801DF580);
    *(s32 *)(s0 + 0x20) = (s32)&D_81195D48;
    func_80187654((u8 *)s1);
    func_8012AD50((void *)s1);
L_end:
    return;
}


#include "common.h"

/* Packed struct to trigger lwl/lwr unaligned block copy */
typedef struct {
    u32 field0;
    u32 field1;
} __attribute__((packed, aligned(1))) BlockData;

extern u8 func_8014BF6C(void);
extern void func_8012B23C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern void func_80187654(u8*);
extern void func_80187724();
extern u16 D_800B99DA;
extern BlockData D_801E9E34;

void func_8018754C(s32 *a0)
{
    u8 result;
    BlockData buffer;

    /* Struct assignment emits lwl/lwr + swl/swr for unaligned copy */
    buffer = D_801E9E34;

    result = func_8014BF6C();

    if (!(*(s16*)((u8*)a0 + 0x70) < (result & 0xFF))) {
        func_8012B23C((s32)a0);
        func_8002D4C8(0x580, 0);
        func_8012BF4C(a0, 0x10);
        func_8012AD50((void*)a0);
    } else {
        ((void (*)(s32))func_80187654)((s32)a0);
        if ((D_800B99DA & 0x3) == 0) {
            func_80187724((s32)a0, &buffer);
        }
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void *param_1);
void func_80187614(s32 a0) {
    func_8012AD80(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C098)(a0);
    }
}


#include "common.h"

typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_80187654;
typedef struct { s16 a, b, c; } SV3_80187654;

extern s32 *D_80126B78;
extern s32 D_80195DB0[];

extern u8 func_8014BF6C(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012B260(u8 *a0);

void func_80187654(u8 *param_1)
{
    u8 *obj;
    u8 idx;
    s16 off;
    SV3_80187654 out;

    obj = *(u8 **)(param_1 + 0x20);

    *(Mtx32_80187654 *)(obj + 0x34) = *(Mtx32_80187654 *)((u8 *)D_80126B78 + 0x34);

    idx = func_8014BF6C();
    off = *(s16 *)(param_1 + 0x70);

    func_8012F214((s32)param_1, D_80195DB0[idx] + off * 8, (s32)&out);

    *(s16 *)(param_1 + 0x6) = out.a;
    *(s16 *)(param_1 + 0xa) = out.b;
    *(s16 *)(param_1 + 0xe) = out.c;

    func_8012B260(param_1);
}




void func_80187724(u8 *a0, u8 *a1) {
    u16 temp[3];

    temp[0] = *(u16 *)(a0 + 0x6);
    temp[1] = *(u16 *)(a0 + 0xA);
    temp[2] = *(u16 *)(a0 + 0xE);

    temp[0] += *(u16 *)(a1 + 0x0);
    temp[1] += *(u16 *)(a1 + 0x2);
    temp[2] += *(u16 *)(a1 + 0x4);
}



extern void (*D_80195DC4[])(void);

void func_80187784(void *a0) {
    D_80195DC4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801877C0(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);
void func_801877C8(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8012AD50)(param_1);
    }
}


extern s32 func_800D0CE0(void);
extern void func_8012C098(void *param_1);
void func_80187800(int param_1)
{
    if (((int (*)(void))func_800D0CE0)() != 0) {
        ((void (*)(int))func_8012C098)(param_1);
    }
}


extern s32 func_8012E544(s32);
extern void func_800D0C48(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);

void func_80187838(void) {
    s32 *s0;
    s0 = (s32 *)func_8012E544(0x11f);
    if (s0 != 0) {
        func_800D0C48(1);
        func_8012AD44(s0, 1);
        func_8012BF4C(s0, 0x30);
    }
}



extern void (*D_80195F14[])(void);

void func_8018788C(void *a0) {
    D_80195F14[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 D_80195EFC[];
extern s32 rand(void);

void func_801878C8(s32 a0) {
    s32 idx;
    s32 *entry;

    idx = *(s32 *)(a0 + 0x2C);
    entry = &D_80195EFC[idx * 3];

    if (*(u16 *)((s32)entry + 0x6) != 0) {
        *(s32 *)(a0 + 0x1C) = rand() % *(u16 *)((s32)entry + 0x6);
    } else {
        *(s32 *)(a0 + 0x1C) = 0;
    }

    *(u16 *)(a0 + 0x2) += 1;
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

extern u8 D_80195DD0[];
extern s32 D_80195EFC[];


void func_8018797C(s32 a0) {
    s32 effect;
    s32 count;
    s32 idx;
    s32 *entry;
    Quad_8018797C tmp;
    s32 off[3];
    u16 reload;

    effect = *(s32 *)(a0 + 0x20);
    count = *(s32 *)(a0 + 0x1c) - 1;
    *(s32 *)(a0 + 0x1c) = count;
    if (count == -1) {
        func_8001CC3C(effect, (s32)D_80195DD0, 0, 0);
        *(u8 *)(effect + 0x27) = 0x9c;
        *(u16 *)(effect + 0x1a) = 0x4000;
        *(u16 *)(effect + 0x18) = 0x4000;
        *(u32 *)(effect + 4) = *(u32 *)(effect + 4) | 0x50000040;

        idx = *(s32 *)(a0 + 0x2c);
        entry = &D_80195EFC[idx * 3];
        func_80128EA8(effect, a0 + 0x24, entry[0]);

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C *)(entry[2] + 0x10);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x10) = *(s32 *)(entry[2] + 0) + off[0];
        *(s32 *)(a0 + 0x14) = *(s32 *)(entry[2] + 4) + off[1];
        *(s32 *)(a0 + 0x18) = *(s32 *)(entry[2] + 8) + off[2];

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C *)(entry[2] + 0x30);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x2c) = *(s32 *)(entry[2] + 0x20) + off[0];
        *(s32 *)(a0 + 0x30) = *(s32 *)(entry[2] + 0x24) + off[1];
        *(s32 *)(a0 + 0x34) = *(s32 *)(entry[2] + 0x28) + off[2];

        reload = *(u16 *)((s32)entry + 4);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        *(u32 *)(a0 + 0x1c) = reload;
    }
}


#include "common.h"

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_8012931C(struct vec*);
extern void func_801292C8(u8 *a0);

void func_80187CE8(s32 arg0)
{
    s32 obj;
    s32 v;
    s32 timer;

    obj = *(s32 *)(arg0 + 0x20);
    *(s32 *)(arg0 + 0x10) += *(s32 *)(arg0 + 0x2C);
    *(s32 *)(arg0 + 0x14) += *(s32 *)(arg0 + 0x30);
    *(s32 *)(arg0 + 0x18) += *(s32 *)(arg0 + 0x34);
    func_8012931C((struct vec *)arg0);
    v = *(u16 *)(obj + 0x1A) - 0x100;
    *(u16 *)(obj + 0x1A) = v;
    *(u16 *)(obj + 0x18) = v;
    if (func_80128ED8(obj, (s32 *)(arg0 + 0x24)) != 0) {
        func_801292C8((u8 *)arg0);
    } else {
        timer = *(s32 *)(arg0 + 0x1C);
        if (timer != 0) {
            timer--;
            *(s32 *)(arg0 + 0x1C) = timer;
            if (timer == 0) {
                func_801292C8((u8 *)arg0);
            }
        }
    }
}



// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_80195FD8[])();

void func_80187D90(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_80195FD8[*(u16 *)(param_1 + 2)]();
    }
}


extern s32 func_8012AD50(void *a0);
    void func_80187DDC(u8 *a0) {
        *(u16 *)(a0 + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


/* func_80187E08 -- screen-space gate + record-chain spawner.
 * GTE ops INLINE per cookbook §195-J (target has lwc2/rtps/swc2/cfc2, no jal).
 * Matrix macros = TU house style (L14091/L14847); stflg clobbers $12 (§179-D).
 * Zero-byte volatile barrier pins &D_800AF648 materialization AFTER the
 * D_80195FC0 table load; matrix base pinned $2, guard x-temp pinned $3.
 * BOTH screen-bound guards materialize their condition through the SAME
 * $2-pinned `ok2` temp: without it gcc reuses the x-temp's $v1 as the
 * destination of the second `slt` in each pair (target wants $v0 both times).
 * That single change closed the last 2-instruction REGALLOC-PERM/$v1>$v0. */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80187FA0(u8 *a0, u8 *a1);
extern void func_80188034(s32 a0);


void func_80187E08(s32 param_1)
{
    extern u8  D_800AF648;
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern s32 *D_80195FC0[];

    s32 mtx;
    register s32 xt __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 ok2 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 *rec;
    s16 sxy[2];     /* sp+0x10 */
    long flag;      /* sp+0x18 */
    s32 lim;
    s32 v;
    s16 first;

    rec = D_80195FC0[*(s16 *)((s8 *)param_1 + 0xFC)];
    __asm__ volatile("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)

    mtx = (s32)&D_800AF648;
    gte_SetRotMatrix(mtx);
    gte_SetTransMatrix(mtx);

    func_80015978(param_1 + 4, (s32 *)sxy);

    __asm__ volatile("lwc2 $0, 0(%0)\n\tlwc2 $1, 4(%0)" : : "r"(sxy) : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldv0_m) beyond Sony's (P36 T5 gte1)
    __asm__ volatile("nop\n\tnop\n\trtps" : : : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_rtps_m) beyond Sony's (P36 T5 gte1)
    gte_stsxy(sxy);
    __asm__ volatile("cfc2 $12, $31\n\tnop\n\tsw $12, 0(%0)" : : "r"(&flag) : "$12");  // !FAKE: gte direct — clobbers ['memory'] (gte_stflg_v) beyond Sony's (P36 T5 gte1)

    xt = sxy[0];
    lim = ((u32)D_800AF7BC >> 1) + 0x20;
    ok2 = -(s32)lim < xt;
    if (ok2) {
        ok2 = xt < lim;
        if (ok2) {
            xt = sxy[1];
            lim = ((u32)D_800AF7BE >> 1) + 0x20;
            ok2 = -(s32)lim < xt;
            if (ok2) {
                ok2 = xt < lim;
                if (ok2 && flag >= 0) {
                    v = *(s32 *)((s8 *)param_1 + 0x1C);
                    if (v == 0) {
                        first = *(s16 *)((s8 *)rec + 6);
                        while (first != 0xFF) {
                            func_80187FA0((u8 *)param_1, (u8 *)rec);
                            rec = (s32 *)((s8 *)rec + 8);
                            first = *(s16 *)((s8 *)rec + 6);
                        }
                        *(s32 *)((s8 *)param_1 + 0x1C) = *(s32 *)((s8 *)param_1 + 0xDC);
                        v = *(volatile s32 *)((s8 *)param_1 + 0x1C);
                    }
                    *(s32 *)((s8 *)param_1 + 0x1C) = v - 1;
                }
            }
        }
    }
    func_80188034(param_1);
}


#include "common.h"

extern u8 *func_801290DC(s32 a0, u8 *a1);

void func_80187FA0(u8 *a0, u8 *a1) {
    u16 temp[3];
    u16 v1_load;
    u8 *result;

    v1_load = *(u16 *)(a0 + 0x6);
    temp[0] = v1_load;

    temp[1] = *(u16 *)(a0 + 0xA);
    temp[2] = *(u16 *)(a0 + 0xE);

    temp[0] += *(u16 *)(a1 + 0x0);
    temp[1] += *(u16 *)(a1 + 0x2);
    temp[2] += *(u16 *)(a1 + 0x4);

    result = func_801290DC(0x3E, (u8 *)temp);

    if (result) {
        *(s32 *)(result + 0x2C) = *(s16 *)(a1 + 0x6);
    }
}


#include "common.h"

extern u8 D_80195FC8[];
extern s32 D_80126B58;
extern u16 D_80126B62;
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013294(void *a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80188034(s32 a0) {
    s32 idx;
    u8 *s0;
    s32 base;
    s16 buf[2];
    s16 sVar1;
    s32 q;
    s16 a1v;

    idx = *(s16 *)(a0 + 0xFC);
    s0 = D_80195FC8 + idx * 8;
    base = (s32)&D_80126B58;

    if (*(s16 *)(s0 + 6) != 0 && (s16)D_80126B62 >= -0x8FF) {
        func_80015978(base + 4, (s32 *)buf);
        buf[1] = *(u16 *)(s0 + 2);
        sVar1 = (s16)func_80013294((void *)buf, (void *)s0);
        if (sVar1 < 0x800) {
            q = (0x800 - sVar1) * 0x7F / 0x800;
            if (q < 0) {
                a1v = 0;
            } else {
                a1v = q;
            }
            if (a1v >= 0x80) {
                a1v = 0x7F;
            }
            func_8002D4C8(*(u16 *)(s0 + 6), (u16)(a1v | 0x1000));
        }
    }
}


#include "common.h"

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEF98;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80188114(void)
{
    int *p = &D_800C7C60;
    *p = 0x20;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEF98, 0, p);
}


extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEFA8;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

s32 func_80188168(void)
{
    int *p = &D_800C7C60;
    *p = 0x18;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEFA8, 0, p);
}



// @class: remat
// @stuck: none — MATCH. &D_800C7C60 CSE'd once via pointer local `p` so the same reg feeds the *p=0x18 store AND arg5; writing D_800C7C60=0x18 directly would emit a 2nd address materialization (+1 ins). Mirrors matched sibling func_80128998.

extern int D_800C7C60;
extern int *D_800C7C64;
extern int D_800A2E20;
extern int D_800AEFA0;
extern int D_801E8C34;

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);

int func_801881BC(int arg0)
{
    int *p = &D_800C7C60;
    *p = 0x18;
    D_800C7C64 = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))func_8001ABBC)(0, 0, &D_800AEFA0, D_801E8C34, p);
}


extern s32 D_8012704C;
    void func_80188214(void) {
        D_8012704C = 0x1;
    }



extern s32 D_801EBA74;

void func_80188228(void) {
    D_801EBA74 = 640;
}



extern s32 D_801EBA74;

void func_8018823C(void) {
    D_801EBA74 = 272;
}


#include "common.h"

/* func_80188250 -- same-class neighbour push-away over the 0x60-entry /
 * 0x10C-stride entity table D_801202A0. Banked twin: ov_SC06_018:func_80187320
 * (§193-A), minus its second switch case (no 0x2F4 clamp here) and with a
 * self-id equality guard instead of constant class ids.
 *
 * §37/§124 DEF-SIDE ESCAPE (_body spelling, cf. func_801810CC_body,
 * ov_SC07_007_jr_8017BEBC.c:6600): this TU already declares
 * `extern void func_80188250(s32 a0);` at file scope (the func_80188654 block),
 * while the target tail (`addiu $v0,$zero,1` / `addu $v0,$zero,$zero`) proves
 * an s32 return. A same-name s32 definition is a hard `conflicting types`;
 * a void definition cannot emit the $v0 constants. Define under a private C
 * identifier carrying an __asm__ label: emitted symbol unchanged, no collision,
 * the existing extern keeps compiling the caller at func_80188654.
 *
 * §8d: func_8012CEB0 is declared ONLY at block scope in this TU (the
 * func_80187844 block) -- its extern rides INSIDE the body, not at file scope.
 *
 * Load-bearing constructs (do NOT "clean up"):
 *  1. NO SECOND WALKED POINTER. All of +0x6/+0xA/+0xE written off the single
 *     biv `p` (twin note 1): an explicit q = p + 0xE excludes the bare *q from
 *     givs and yields THREE IVs / wrong anchor.
 *  2. `self4` and `sc` are REAL pre-loop locals, in that order (twin note 4):
 *     written inline at the calls they fold into the argument moves and the
 *     $s5/$s6 hoists never happen. Declaration ORDER (p, i, self4, sc) gives
 *     $s2/$s4/$s5/$s6 in the target's prologue emission order.
 *  3. do-while with `i++` BEFORE `p += 0x10C` (twin note 3): strength_reduce
 *     emits the giv addiu immediately before ITS biv increment =>
 *     addiu $s4,1 / addiu $s3,0x10C / (delay) addiu $s0,0x10C.
 *  4. NO `s16 y` scalar: the twin's short-local/dead-slot pair belongs to its
 *     second switch case, absent here. Frame is exactly 0x48 with no dead slot.
 *  5. §5a cross-jump barrier before the second `return 1`: the target keeps TWO
 *     [j .epi][addiu $v0,$zero,1] tails; without the barrier gcc merges them
 *     into one shared li (93 ins).
 */

extern u8   D_801202A0[];

extern s32  func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012ADE4(u8 *a0);

s32 func_80188250_body(s32 a0) __asm__("func_80188250");

s32 func_80188250_body(s32 a0) {
    extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
    u8 *p;
    s16 *self4;
    unsigned int *sc;
    s32 i;
    s32 ang;
    s16 v10[4];  /* sp+0x10 */
    s16 v18[4];  /* sp+0x18 */
    s32 sp20[2]; /* sp+0x20 - func_8012B0B4 output */

    p = D_801202A0;
    i = 0;
    self4 = (s16 *)(a0 + 4);
    sc = (unsigned int *)sp20;
    do {
        if (*(u16 *)a0 == *(u16 *)p && (u8 *)a0 != p) {
            if (func_8012BC60(self4, (struct Vec *)(p + 4)) < 0x1000) {
                ang = func_8012B6D4(self4, (s16 *)(p + 4));
                func_8012B0B4(sc, ang, 0x41);
                v18[0] = *(u16 *)(p + 6);
                v18[1] = *(u16 *)(p + 0xA);
                v18[2] = *(u16 *)(p + 0xE);
                v18[0] += sp20[0];
                v18[2] += sp20[0] >> 16;
                v10[0] = *(u16 *)(a0 + 0x3A);
                v10[1] = *(u16 *)(a0 + 0x3E);
                v10[2] = *(u16 *)(a0 + 0x42);
                if ((func_8012CEB0((s32)&v10[0], (s32)&v18[0], 0) & 0x2000) == 0) {
                    func_8012ADE4((u8 *)a0);
                    return 1;
                }
                *(u16 *)(a0 + 6) = v18[0];
                *(u16 *)(a0 + 0xA) = v18[1];
                do { *(u16 *)(a0 + 0xE) = v18[2]; } while (0);
                return 1;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);
    return 0;
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_801883C8(void) {
        func_8002D4C8(0x6AA, 0);
    }


#include "common.h"

extern void func_8002A04C(void);
extern void func_8012C098(void *param_1);

void func_801883EC(s32 a0) {
    if (*(s16 *)(a0 + 0x102) == 0) {
        func_8002A04C();
    }

    ((void (*)(s32))func_8012C098)(a0);
}


#include "common.h"
#include "../shared/engine_prelude.h"

void func_80188430(s32 a0) {
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern void func_8012B23C(s32 a0);
    extern void func_80188508(s32 a0);
    extern void func_80188554(s32 a0);

    SVECTOR in;
    SVECTOR out;
    s32 v0;

    in.vx = *(s16 *)(a0 + 0x6);
    in.vy = *(s16 *)(a0 + 0xA);
    in.vz = *(s16 *)(a0 + 0xE);
    out = in;
    out.vy += 8;

    if ((func_80133784(1, &in, (s32)&out) & 0x6000) != 0) {
        v0 = 1;
    } else {
        func_8012B23C(a0);
        v0 = 0;
    }

    if (v0 == 0) {
        *(s16 *)(a0 + 0x2) = 0x11;
        *(s16 *)(a0 + 0x98) = 0;
        return;
    }

    if (*(s32 *)(a0 + 0xC4) & 4) {
        func_80188508(a0);
    } else {
        func_80188554(a0);
    }
}


extern short D_801D40D4;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80188508(s32 a0) {
    *(s16 *)(a0 + 0x2) = 5;
    *(s16 *)(a0 + 0x34) = 0;
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    func_8012A828(a0, &D_801D40D4);
    func_8012B23C(a0);
}


#include "common.h"
#include "../shared/engine_prelude.h"

extern s32 rand(void);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern u8 D_801D3CBC[];

void func_80188554(s32 param_1) {
    LVec1CDC d;

    *(s16 *)(param_1 + 0x2) = 1;
    *(s16 *)(param_1 + 0x34) = 0;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    *(s32 *)(param_1 + 0x1C) = (rand() & 0x1F) + 0x28;

    {
        void *target = (void *)(param_1 + 0x88);

        d.vx = *(s16 *)(param_1 + 0x6) - *(s16 *)target;
        d.vy = 0;
        d.vz = *(s16 *)(param_1 + 0xE) - *(s16 *)(param_1 + 0x8C);
        Square0(&d.vx, &d.vx);

        if (d.vx + d.vz > 0x8FFFF) {
            *(s16 *)(param_1 + 0xFC) =
                func_8012B744((void *)(param_1 + 0x4), target);
        } else {
            s32 t = rand() & 0x3FF;
            s32 v1 = t - 0x200;

            if (v1 < 0) {
                v1 = t - 0x500;
            } else {
                v1 = t + 0x100;
            }
            *(s16 *)(param_1 + 0xFC) =
                (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + v1) & 0xFFF;
        }
    }

    func_8012A828(param_1, D_801D3CBC);
}


#include "common.h"

extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);            /* canonical void */
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void *param_1);
extern s32 func_8012C044(s32 a0);

extern void func_80188250(s32 a0);
extern void func_8018898C(s32 a0);
extern void func_801887C8(short *a0);

extern s32 D_80196098;

void func_80188654(s32 a0)
{
    s32 s0 = a0;
    s32 v0;
    s32 v1;

    if (*(s32 *)(s0 + 0x1C) >= 8) {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), *(s16 *)(s0 + 0xFC), 8);
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + r;
    }

    {
        s32 d[3];
        d[0] = *(s16 *)(s0 + 0x6) - *(s16 *)(s0 + 0x88);
        d[1] = 0;
        d[2] = *(s16 *)(s0 + 0xE) - *(s16 *)(s0 + 0x8C);
        Square0(d, d);
        if (d[0] + d[2] <= 0x8FFFF) {
            if (func_8012BD3C(s0, 0x300, 0x10000)) {
                func_8018898C(s0);
                return;
            }
        }
    }

    func_8012B178(s0, D_80196098);
    v1 = ((s32 (*)(s32))func_8012CBA4)(s0);
    if (v1 & 0x1000) {
        func_80131E00((struct S80131E00 *)s0, 0x12);
        v0 = 0;
    } else if (v1 == 0x2000) {
        v0 = 1;
    } else {
        func_8012ADE4((u8 *)s0);
        v0 = 1;
    }

    if (v0 == 0) {
        return;
    }

    func_80188250(s0);
    if (func_8012BEE8(s0) != 0) {
        func_801887C8((short *)s0);
        return;
    }

    if (func_8012C044(s0) != 0) {
        *(s16 *)(s0 + 0x102) = 1;
        ((void (*)(void *))func_8012C098)((void *)s0);
    }
}




extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801887C8(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        *(short *)((char *)a0 + 0x34) = 0;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801D3B74);
    }


#include "common.h"

extern s32 rand(void);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern u8 D_801D3CBC[];

typedef struct {
    s32 vx, vy, vz;
} Vec3_1887F8;

void func_801887F8(s32 a0) {
    Vec3_1887F8 d;
    Vec3_1887F8 *p;
    s32 v0;
    s32 v1;
    s32 r;
    s32 dx;
    s32 dz;
    void *s1_ptr;
    s32 tmp0;

    if ((*(u16 *)(a0 + 0x34) == 0) && ((*(u16 *)(a0 + 0x72) & 0x4000) != 0)) {
        d.vx = *(s16 *)(a0 + 0x6) - *(s16 *)(a0 + 0x88);
        d.vy = 0;
        d.vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
        Square0(&d.vx, &d.vx);

        if (d.vx + d.vz > 0x8FFFF) {
            v0 = 1;
        } else if (func_8012BCCC(a0) > 0x10000) {
            v0 = 1;
        } else {
            func_8018898C(a0);
            return;
        }

        *(s16 *)(a0 + 0x2) = v0;
        *(s16 *)(a0 + 0x34) = 0;
        *(u16 *)(a0 + 0x5C) = 0xAA10;
        r = rand();
        p = &d;
        r = r & 0x1F;
        dx = *(s16 *)(a0 + 0x6);
        tmp0 = a0 + 0x88;
        dz = *(s16 *)tmp0;
        *(s32 *)(a0 + 0x1C) = r + 0x28;

        p->vy = 0;
        p->vx = dx - dz;
        p->vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
        Square0(&p->vx, &p->vx);

        s1_ptr = (void *)(a0 + 0x88);
        if (d.vx + d.vz > 0x8FFFF) {
            *(s16 *)(a0 + 0xFC) = func_8012B744((void *)(a0 + 4), s1_ptr);
        } else {
            v0 = rand() & 0x3FF;
            v1 = v0 - 0x200;
            if (v1 >= 0) {
                v1 = v0 + 0x100;
            } else {
                v1 = v0 - 0x500;
            }
            v0 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            *(s16 *)(a0 + 0xFC) = (v0 + v1) & 0xFFF;
        }

        func_8012A828(a0, (void *)&(*(short *)D_801D3CBC));
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);

extern s16 D_801D3D64;
extern s16 D_801D3DEC;

void func_8018898C(s32 a0) {
    *(s16 *)(a0 + 0x2) = 3;
    if (*(u16 *)(a0 + 0x86) & 2) {
        *(s16 *)(a0 + 0x34) = 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
        func_8012A828(a0, &D_801D3D64);
        *(u16 *)(a0 + 0xFE) = 0;
    } else {
        *(s16 *)(a0 + 0x34) = 0;
        func_8012A828(a0, &D_801D3DEC);
        *(s32 *)(a0 + 0x1C) = 0x19;
        *(u16 *)(a0 + 0x86) |= 2;
    }
}


#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012ADE4(u8 *a0);
extern void func_80188250(s32 a0);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void Square0(s32 *a0, s32 *a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  rand(void);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80188D54(s32 a0);
extern void func_80188D80(s32 a0);

extern const s32 D_8019609C;
extern s16 D_801D3D64;
extern s16 D_801D3DEC;
extern u8  D_801D3CBC[];

void func_80188A10(s32 a0) {
    s32 d[3];
    s32 v0;
    s32 v1;
    void *target;
    s32 lim;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 4);
        if (*(s32 *)(a0 + 0x1C) == 0xF) {
            func_80142414(a0, -0x78);
            func_8002D4C8(0x6A9, 0);
        }
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 0x2) = 3;
            if (*(u16 *)(a0 + 0x86) & 2) {
                *(s16 *)(a0 + 0x34) = 1;
                *(s32 *)(a0 + 0x1C) = 0x28;
                func_8012A828(a0, &D_801D3D64);
                *(u16 *)(a0 + 0xFE) = 0;
            } else {
                *(s16 *)(a0 + 0x34) = 0;
                func_8012A828(a0, &D_801D3DEC);
                *(s32 *)(a0 + 0x1C) = 0x19;
                *(u16 *)(a0 + 0x86) |= 2;
            }
        }
        break;
    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 6);
        func_8012B178(a0, D_8019609C);
        v1 = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (v1 & 0x1000) {
            func_80131E00((struct S80131E00 *)a0, 0x12);
            v0 = 0;
        } else if (v1 == 0x2000) {
            v0 = 1;
        } else {
            func_8012ADE4((u8 *)a0);
            v0 = 1;
        }
        if (v0 == 0) {
            break;
        }
        func_80188250(a0);
        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s16)v0 <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }
        d[0] = *(s16 *)(a0 + 0x6) - *(s16 *)(a0 + 0x88);
        d[1] = 0;
        d[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
        Square0(d, d);
        lim = 0x8FFFF;
        target = (void *)(a0 + 0x88);
        if (d[0] + d[2] > lim || func_8012BCCC(a0) > 0x10000) {
            *(s16 *)(a0 + 0x2) = 1;
            *(s16 *)(a0 + 0x34) = 0;
            *(u16 *)(a0 + 0x5C) = 0xAA10;
            *(s32 *)(a0 + 0x1C) = (rand() & 0x1F) + 0x28;
            d[0] = *(s16 *)(a0 + 0x6) - *(s16 *)(a0 + 0x88);
            d[1] = 0;
            d[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
            Square0(d, d);
            if (d[0] + d[2] > lim) {
                *(s16 *)(a0 + 0xFC) = func_8012B744((void *)(a0 + 4), target);
            } else {
                v0 = rand() & 0x3FF;
                v1 = v0 - 0x200;
                if (v1 >= 0) {
                    v1 = v0 + 0x100;
                } else {
                    v1 = v0 - 0x500;
                }
                *(s16 *)(a0 + 0xFC) =
                    (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + v1) & 0xFFF;
            }
            func_8012A828(a0, D_801D3CBC);
        }
        if ((*(u16 *)(a0 + 0x70) & 0x100) == 0) {
            if (func_8012BD3C(a0, 0x200, 0x1000)) {
                func_80188D54(a0);
            }
        } else {
            if (func_8012BD3C(a0, 0x400, 0x40000)) {
                func_80188D80(a0);
            }
        }
        break;
    }
}


extern const void D_801D3EBC;
extern void func_80188DF4(s32 arg0, s32 arg1, s32 arg2, void *arg3);

void func_80188D54(arg0)
s32 arg0;
{
    extern const void D_801D3EBC;
    func_80188DF4(arg0, 0, 0x14, (void *)&D_801D3EBC);
}


extern void func_80188DC8(void*);
extern void func_80188DF4();
extern short D_801D4494;

void func_80188D80(s32 a0) {
    s32 a1 = 4;
    if (*(s16 *)((s32)a0 + 0x100) == 0) {
        ((void (*)(s32))func_80188DC8)(a0);
    } else {
        ((void (*)(s32, s32, s32, s32))func_80188DF4)(a0, a1, 0x1E, (s32)&D_801D4494);
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80188DC8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 8;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


extern void func_8012A828(s32 a0, void *a1);

void func_80188DF4(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    *(short *)((char *)arg0 + 0x34) = arg1;
    *(short *)((char *)arg0 + 0x2) = 4;
    func_8012A828(arg0, arg3);
    *(s32 *)((char *)arg0 + 0x1C) = arg2;
}


