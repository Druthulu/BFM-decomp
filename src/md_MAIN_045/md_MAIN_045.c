#include "common.h"

void func_800CCB20(void) {
}

extern void func_80149020(s32 *a0);
extern void (*D_800CD668[])(s32 *);

void func_800CCB28(s32 *param_1)
{
    s32 *s0;
    s32 idx;

    func_80149020(param_1);
    s0 = param_1;
    idx = *(u16 *)((u8 *)s0 + 2) - 2;
    D_800CD668[idx](s0);
}


extern void func_80147324(s32 a0);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);

void func_800CCB78(void *a0) {
    func_80147324(0x8DF);
    func_801466F0(0x10, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x11, (s32)a0, 0, 0, 0, 0, 0, 0);
    func_801466F0(0x11, (s32)a0, 0, 0, 0, 1, 0, 0);
    func_801466F0(0x11, (s32)a0, 0, 0, 0, 2, 0, 0);
    *(s16 *)((s32)a0 + 0x1C8) = 0xFF;
    func_801599A4(a0);
    func_80159B3C(a0);
}


extern void (*D_800CD684[])(void);
extern s16 D_800CE050;
extern s32 func_80012ABC(s32, s32, s32);
extern void func_8014ACC0(s32, s32);
extern s32 func_80161A00(s32 a0);
extern void func_80147364(s32 a, s32 b);
extern void func_800CCE60();

void func_800CCC54(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD684[*(u16 *)(param_1 + 2)]();
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= *(s32 *)(*(s32 *)(iVar1 + 0x20) + 4) & 0x80000000;
    *(u16 *)(param_1 + 0x60) = 0;
    D_800CE050 = func_80012ABC(D_800CE050, *(s16 *)(*(s32 *)(iVar1 + 0x20) + 0x12), 10);
    func_8014ACC0(iVar1, 1);
    if (func_80161A00(iVar1) == 0) {
        func_80147364(0x4, 0x8E0);
        ((void (*)(s32))func_800CCE60)(param_1);
    }
}


#include "common.h"

extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_800CCE80(void*);
extern void func_80146CA0(void *a0);
extern void func_800CCE60();
extern s32 D_800CE048;
extern s16 D_800CE050;

void func_800CCD2C(s32 s1) {
    s32 s2;
    s32 s0;

    s2 = *(s32 *)(s1 + 0x4C);
    s0 = ((s32 (*)())func_8014659C)();
    *(s32 *)(s1 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C810(s0, &D_800CE048);
        *(u32 *)(s0 + 4) |= 0x50020000;
        *(u16 *)(s0 + 0x1C) = 0;
        *(u16 *)(s0 + 0x1A) = 0;
        *(u16 *)(s0 + 0x18) = 0;
        ((void (*)(s32))func_800CCE80)(s1);
        D_800CE050 = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x12);
        func_80146CA0((void *)s1);
    } else {
        ((void (*)(s32))func_800CCE60)(s1);
    }
}


extern void func_800CCE80(void *);

void func_800CCDD8(s32 a0) {
    s16 flag;
    u8 *v1;
    u16 w;

    flag = *(s16 *)(a0 + 0x60);
    v1 = *(u8 **)(a0 + 0x20);
    if (flag != 0) {
        *(u16 *)(v1 + 0x18) = w = *(u16 *)(v1 + 0x18) + 0x100;
        if ((s16)w >= 0x1001) {
            *(u16 *)(v1 + 0x18) = 0x1000;
        }
    } else {
        *(u16 *)(v1 + 0x18) = w = *(u16 *)(v1 + 0x18) - 0x100;
        if ((s16)w < 0) {
            *(u16 *)(v1 + 0x18) = 0;
        }
    }
    w = *(u16 *)(v1 + 0x18);
    *(u16 *)(v1 + 0x1C) = w;
    *(u16 *)(v1 + 0x1A) = w;
    func_800CCE80((void *)a0);
}


extern void func_80162CCC(void);
void func_800CCE60(void) {
    func_80162CCC();
}


extern void func_80013F3C(void *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80020F34(s32 a0, s32 a1);

void func_800CCE80(void *arg0) {
    void *s2;
    void *s1;
    void *s0;
    void *p;

    s2 = *(void **)((u8 *)arg0 + 0x4C);
    p = *(void **)((u8 *)s2 + 0x20);
    s1 = *(void **)((u8 *)arg0 + 0x20);
    *(s16 *)((u8 *)arg0 + 0x06) = *(s32 *)((u8 *)p + 0x48);
    *(s16 *)((u8 *)arg0 + 0x0A) = *(s32 *)((u8 *)p + 0x4C) - 0x20;
    s0 = (void *)((u8 *)s1 + 0x34);
    *(s16 *)((u8 *)arg0 + 0x0E) = *(s32 *)((u8 *)p + 0x50);
    func_80013F3C(s0);
    RotMatrixY(*(s16 *)((u8 *)s1 + 0x12), s0);
    func_80048D9C(s0, (void *)((u8 *)*(void **)((u8 *)s2 + 0x20) + 0x34));
    func_80020F34((s32)s0, (s32)((u8 *)s1 + 0x18));
    *(u16 *)((u8 *)s1 + 0x2C) |= 1;
}


extern s32 func_8014C088(s32 a0, s32 a1);

void func_800CCF28(s32 a0) {
    s32 v1 = func_8014C088(a0, 0x10);
    if (v1 != 0) {
        *(s16 *)(v1 + 0x60) = 1;
    }
}


void func_800CCF58(void *arg0) {
    void *s0;

    s0 = arg0;
    func_800CCF84();
    *(s16 *)((u8 *)s0 + 0x1C8) = 0;
}


extern void func_80147364(s32 a, s32 b);
void func_800CCF84(void) {
    func_80147364(0x4, 0x8E0);
}


extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6B0[])(void);
extern void func_800CD1A8(void);

void func_800CCFA8(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6B0[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD1A8)(param_1);
    }
}


extern void func_80146578(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);
extern void func_800CD204();
extern void func_800CD1A8(void);

extern u8 D_800CD66C;

void func_800CD010(s32 param_1)
{
    register s32 p1 __asm__("$17");  /* $s1 */
    register s32 iVar1 __asm__("$16");  /* $s0 */

    p1 = param_1;
    iVar1 = ((s32 (*)(void))func_80146578)();
    *(s32 *)(p1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        func_8001CC3C(iVar1, (s32)&D_800CD66C, 0x220, 0x168);
        *(u8 *)(iVar1 + 0x27) = 0x24;
        *(u8 *)(iVar1 + 0x24) = 0xFF;
        *(u8 *)(iVar1 + 0x25) = 0x40;
        *(u8 *)(iVar1 + 0x26) = 0x40;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(s16 *)(iVar1 + 0x10) = *(s32 *)(p1 + 0x50) << 10;
        *(s16 *)(p1 + 0x60) = *(s32 *)(p1 + 0x50) << 10;
        ((void (*)(s32))func_800CD204)(p1);
        ((void (*)(void *))func_80146CA0)((void *)p1);
    } else {
        ((void (*)(s32))func_800CD1A8)(p1);
    }
}


extern void func_800CD204();
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern void func_8014ACC0(s32, s32);
extern u16 D_800CD690[];
extern u16 D_800CD692[];

void func_800CD0CC(s32 param_1)
{
    u16 *v1;
    s32 s1;
    s16 tmp;

    v1 = *(u16 **)(param_1 + 0x20);
    s1 = *(s32 *)(param_1 + 0x4C);
    *(u16 *)(v1 + 0x14) = D_800CD690[(*(s32 *)(param_1 + 0x1C) & 7) * 2];
    *(u16 *)(v1 + 0x15) = D_800CD692[(*(s32 *)(param_1 + 0x1C) & 7) * 2];
    (*(s32 *)(param_1 + 0x1C))++;
    tmp = *(s16 *)(s1 + 0x1C8) * 16 + 0x1000;
    *(u16 *)(v1 + 0xD) = tmp;
    *(u16 *)(v1 + 0xC) = tmp;
    func_800CD204();
    func_80163408(param_1, 0x24, 0x80, 4);
    func_80163328(param_1);
    if (func_801632F0(param_1) & 1) {
        func_8014ACC0(s1, 0xA);
    }
}


extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80162CCC(void);

void func_800CD1A8(void) {
    register void *a0r __asm__("$4");
    void *arg0 = a0r;

    func_80146A6C(3, arg0,
                  *(s16 *)((u8 *)arg0 + 6),
                  *(s16 *)((u8 *)arg0 + 0xA),
                  *(s16 *)((u8 *)arg0 + 0xE),
                  0x8880000, 0x1800A000);
    ((void (*)(void *))func_80162CCC)(arg0);
}


extern s16 func_8012A758(void);
extern s32 func_80013694(s16 a0, void *a1, void *a2);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_80015954(void *a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern u8 D_800CD6BC[];

void func_800CD204(s32 arg0) {
    u16 sp10[3];
    s32 y;
    s32 x;
    s32 w;
    s32 t;
    s32 v1;
    s16 ang;

    y = *(s32 *)(arg0 + 0x4C);
    x = *(s32 *)(arg0 + 0x20);
    ang = func_8012A758();
    func_80013694(*(s16 *)(x + 0x10), D_800CD6BC, sp10);
    func_800139C8((s16)(ang + 0x400), sp10, sp10);
    w = *(s32 *)(y + 0x20);
    sp10[0] = sp10[0] + *(s32 *)(w + 0x48);
    t = sp10[1] - 0x20;
    sp10[1] = t + *(s32 *)(w + 0x4C);
    sp10[2] = sp10[2] + *(s32 *)(w + 0x50);
    v1 = func_80047948(*(s16 *)(arg0 + 0x60));
    if (v1 < 0) {
        v1 += 0x1FF;
    }
    sp10[0] = sp10[0] + (v1 >> 9);
    v1 = func_8004787C(*(s16 *)(arg0 + 0x60));
    if (v1 < 0) {
        v1 += 0xFF;
    }
    sp10[1] = sp10[1] + (v1 >> 8);
    *(u16 *)(arg0 + 0x60) = (*(u16 *)(arg0 + 0x60) + 0x38) & 0xFFF;
    func_80015954(sp10, arg0 + 4);
}


extern s32 func_80161A00(s32 a0);
extern void (*D_800CD6C4[])(void);
extern void func_800CD5BC(void);

void func_800CD328(s32 param_1)
{
    s32 iVar1;
    iVar1 = *(s32 *)(param_1 + 0x4C);
    D_800CD6C4[*(u16 *)(param_1 + 2)]();
    if (func_80161A00(iVar1) == 0) {
        ((void (*)(s32))func_800CD5BC)(param_1);
    }
}


extern void func_80146578(void);
extern s32 func_8001CC3C(s32, s32, s32, s32);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_8014ACC0(s32 a0, s32 a1);
extern void func_800CD5BC(void);
extern u8 D_800CD66C;
extern s16 D_800CE050;

void func_800CD390(s32 param_1) {
    s32 s0;
    s32 s2;
    u16 temp;
    s2 = *(s32 *)(param_1 + 0x4C);
    s0 = ((s32 (*)(void))func_80146578)();
    *(s32 *)(param_1 + 0x20) = s0;
    if (s0 != 0) {
        ((s32 (*)(s32, void *, s32, s32))func_8001CC3C)(s0, ((u8 *)&D_800CD66C), 0x220, 0x168);
        *(u8 *)(s0 + 0x27) = 0x24;
        *(u8 *)(s0 + 0x24) = 0xFF;
        *(u8 *)(s0 + 0x25) = 0x40;
        *(u8 *)(s0 + 0x26) = 0x40;
        *(u32 *)(s0 + 4) |= 0x50000000;
        func_80149374(s2, param_1 + 4);
        temp = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x10);
        *(s16 *)(s0 + 0x12) = D_800CE050;
        *(u16 *)(s0 + 0x10) = temp;
        *(u16 *)(s0 + 0x14) = *(u16 *)(*(s32 *)(s2 + 0x20) + 0x14);
        *(u16 *)(param_1 + 0x60) = *(u16 *)(s2 + 0x100);
        *(u16 *)(param_1 + 0x62) = *(u16 *)(s2 + 0x102);
        *(u16 *)(param_1 + 0x64) = *(u16 *)(s2 + 0x104);
        *(u16 *)(s0 + 0x1A) = 0x1000;
        *(u16 *)(s0 + 0x18) = 0x1000;
        func_80146DE8((s32 *)param_1, 0, 0, 0xFFE80000);
        func_80146E90((s32 *)param_1, 8);
        func_80146CA0((void *)param_1);
        func_8014ACC0(s2, 1);
    } else {
        ((void (*)(s32))func_800CD5BC)(param_1);
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_800CD5DC();
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80162FC0(s32 *a0);
extern s32 func_80163408(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163328();
extern s32 func_801632F0();
extern u16 D_800CD690[];
extern u16 D_800CD692[];

void func_800CD4BC(s32 arg0) {
    s32 sp18[8];
    s32 temp_s2 = *(s32 *)(arg0 + 0x4C);
    s32 temp_s1 = *(s32 *)(arg0 + 0x20);

    if (func_80146E98(arg0) != 0) {
        func_80146CA0((void *)arg0);
        return;
    }
    *(u16 *)(temp_s1 + 0x28) = D_800CD690[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    *(u16 *)(temp_s1 + 0x2A) = D_800CD692[(*(u16 *)(temp_s2 + 0x1C8) & 7) * 2];
    func_800CD5DC(arg0, sp18);
    func_80163194(arg0, 0, -0x10000, 0, (s32)sp18);
    func_80162FC0((s32 *)arg0);
    *(u16 *)(temp_s1 + 0x18) = *(u16 *)(temp_s1 + 0x1A) =
        *(u16 *)(temp_s1 + 0x1A) + 0x200;
    func_80163408(arg0, 0x24, 0x80, 4);
    func_80163328(arg0);
    func_801632F0(arg0);
}


extern void func_80162CCC(void);
void func_800CD5BC(void) {
    func_80162CCC();
}


extern void func_80013F3C(void *a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);

void func_800CD5DC(s32 a0, s32 a1) {
    s32 q = *(s32 *)(a0 + 0x20);
    func_80013F3C((void *)a1);
    func_800126C4((s32)a1, *(s16 *)(a0 + 0x60));
    func_800123F0((s32)a1, *(s16 *)(a0 + 0x64));
    func_80012558((s32)a1, *(s16 *)(a0 + 0x62));
    func_80012558((s32)a1, *(s16 *)(q + 0x12));
    func_800126C4((s32)a1, *(s16 *)(q + 0x10));
    func_800123F0((s32)a1, *(s16 *)(q + 0x14));
}


INCLUDE_RODATA("asm/md_MAIN_045/nonmatchings/md_MAIN_045", D_800CCB1C);
