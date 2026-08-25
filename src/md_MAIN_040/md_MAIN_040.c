#include "common.h"

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAE0C);



void func_800CAE44(void *a0) {

    extern void (*D_800CB8C8[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CB8C8[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAED0(u8 *a0);
void func_800CAE88(u8 *a0) {
    if (func_80161104()) {
        func_800CAED0(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CAED0);

#include "common.h"

extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3,
                          s32 a4, s32 a5, s32 a6, s32 a7);
extern s32 func_80161208();  /* canonical no-proto */

void func_800CAF18(void *a0) {
    u16 flag;

    flag = *(u16 *)((u8 *)a0 + 0xB8);
    if (flag == 0x8000) {
        func_801599A4(a0);
        func_80159B3C(a0);
    } else {
        if (flag & 0x4000) {
            func_801466F0(0x20, (s32)a0, 0, -0x40, 0, 0, 0, 0);
        }
        if (func_80161208(a0) == 0) {
            *(u32 *)((u8 *)a0 + 0x44) |= 2;
        }
    }
}


void func_800CAFB0(void *a0) {
    *(u32 *)((s32)a0 + 0x44) &= ~2;
}


#include "common.h"

extern u8 D_80078EC1;
extern void (*D_800CB8D4[])(void);
extern void func_800CB3BC(void);

void func_800CAFC4(s32 a0) {
    u16 index;
    s16 value;

    if (D_80078EC1 == 0x1D) {
        index = *(u16 *)(a0 + 2);
        D_800CB8D4[index]();

        value = *(s16 *)(a0 + 0xA);
        if (value < 0x401) {
            return;
        }
        ((void (*)(s32))func_800CB3BC)(a0);
    } else {
        ((void (*)(s32))func_800CB3BC)(a0);
    }
}


void func_800CB038(void *a0) {
    extern s32 D_800CBD74;
    extern void func_8014659C(void);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_80149374(s32 a0, s32 a1);
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
    extern void func_80146E90(s32 *a0, s32 a1);
    extern void func_80147324(s32 a0);
    extern void func_80146CA0(void *a0);
    extern void func_800CB3BC(void);

    void *s2 = *(void **)((s32)a0 + 0x4C);
    s32 s1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)((s32)a0 + 0x20) = s1;
    if (s1 != 0) {
        func_8001C214(s1, (s32)&D_800CBD74);
        *(u16 *)(s1 + 0x12) = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        func_80149374((s32)s2, (s32)a0 + 4);
        func_80146DE8((s32 *)a0, 0, -0xC0000, -0x100000);
        func_80146E90((s32 *)a0, 100);
        memcpy((void *)((s32)a0 + 0x58), (void *)(s1 + 0x10), 8);
        *(u16 *)((s32)a0 + 0x60) = 2;
        func_80147324(0x8F3);
        func_80146CA0(a0);
    } else {
        ((void (*)(s32))func_800CB3BC)(a0);
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB114);

void func_800CB304(void *a0) {
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern s32 func_80146E98(s32 a0);
    extern void func_80146CA0(void *a0);
    extern void func_800CB3DC(void *a0);
    s32 pad[2];
    s32 var_s2;
    s32 i;

    if (pad == NULL) {}
    var_s2 = *(s32 *)((s32)a0 + 0x20);
    for (i = 0; i < 6; i++) {
        func_80146A6C(0x4D, a0, *(s16 *)((s32)a0 + 0x6), *(s16 *)((s32)a0 + 0xA),
                      *(s16 *)((s32)a0 + 0xE), i, 1);
    }
    if (func_80146E98((s32)a0) != 0) {
        func_80146CA0(a0);
    } else {
        u16 var_v0;
        var_v0 = *(u16 *)(var_s2 + 0x1C);
        var_v0 = var_v0 - 0x80;
        *(u16 *)(var_s2 + 0x1C) = var_v0;
        *(u16 *)(var_s2 + 0x1A) = var_v0;
        *(u16 *)(var_s2 + 0x18) = var_v0;
        func_800CB3DC(a0);
    }
}


extern void func_80162CCC(void);
void func_800CB3BC(void) {
    func_80162CCC();
}


#include "common.h"

extern u8 D_801202A0[];
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_800CB3DC(s32 a0) {
    u8 *p;
    s16 buf[4];
    p = D_801202A0;
    if (p < p + 0x6480) {
        do {
            if (func_8014C308(a0, (s32)p, 0x2A, 0x20) != 0) {
                if (func_8014C278(a0, (s32)p, 0x80) != 0) {
                    func_80015978((s32)(p + 4), (s32 *)buf);
                    buf[3] = 0;
                    func_8014C3A4((void *)a0, (s32)p, 0x2A, (s32)buf);
                }
            }
            p += 0x10C;
        } while (p < D_801202A0 + 0x6480);
    }
}



extern void func_80146C3C(void);

void func_800CB488(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CB948[])(void);
    if (D_80078EC1 == 0x1d) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CB948[v0]();
    } else {
        func_80146C3C();
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB4E4);

extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 func_80146E98(s32 param_1);
extern void func_80146E90(s32 *param_1, s32 param_2);

void func_800CB710(s32 param_1) {
    s32 node;

    node = *(s32 *)(param_1 + 0x20);
    func_80128ED8(node, (s32 *)(param_1 + 0x24));
    *(u8 *)(node + 0x27) = *(u8 *)(param_1 + 0x28) - 0x70;
    func_800CB840(param_1);
    ((void (*)(s32, s32))func_800CB8A8)(param_1, 0x30);
    if (func_80146E98(param_1) != 0) {
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) >> 2;
        *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0x14) >> 2;
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) >> 2;
        func_80146E90((s32 *)param_1, 8);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800CB840(s32 param_1);
extern void func_800CB8A8(void*, s16);
extern s32 func_80146E98(s32 param_1);
extern void func_80146C3C(void);
extern void func_800CB874(s32 param_1);

void func_800CB7B8(s32 param_1) {
    s32 p;
    s32 node;

    p = param_1;
    node = *(s32 *)(p + 0x20);
    func_800CB874(param_1);
    func_80128ED8(node, (s32 *)(p + 0x24));
    *(u8 *)(node + 0x27) = *(u8 *)(p + 0x28) - 0x70;
    ((void (*)(s32, s32))func_800CB8A8)((void *)p, 0x40);
    *(s32 *)(p + 0x14) -= 0x4000;
    func_800CB840(p);
    if (func_80146E98(p) != 0) {
        ((void (*)(s32))func_80146C3C)(p);
    }
}


INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB840);

INCLUDE_ASM("asm/md_MAIN_040/nonmatchings/md_MAIN_040", func_800CB874);

void func_800CB8A8(void *arg0, s16 arg1) {
    u16 *ptr = *(u16 **)((s32)arg0 + 0x20);
    ptr[13] = ptr[13] - arg1;
    ptr[12] = ptr[13];
}

