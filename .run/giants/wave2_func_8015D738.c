#include "common.h"

extern void func_80148AFC(void);
extern s32 func_80161B18(void *);
extern s32 func_80161B84(void *);
extern s32 func_80148800(void *);
extern s32 func_8014BEF8(void *);
extern s32 func_80165624(void *);
extern s32 func_801488A8(void *);
extern s32 func_8014D738(void *);
extern s32 func_80161208(void *);
extern void func_80154A74(void *, s32);
extern void func_8015DAC4(void *);
extern void func_8015DE24(void *);
extern void func_8015DA5C(void *);
extern void func_8015F948(void *);
extern void func_800CAF14(void *);
extern void func_80154150(void *, s32);
extern void func_80146DB8(void *, void *);
extern void func_80147A84(void *);
extern void func_801473EC(void *);
extern void func_80149374(void *, void *);
extern void func_80147078(void *, s32);
extern void func_80159B70(void *);
extern void func_8015C714(void *);
extern void func_801483E8(void *);

extern void (*D_801891B8[])(void *);
extern u8 D_80078E78[];
extern u8 D_801893FC[];
extern u8 D_8018917C[];
extern u8 D_8018918C[];

void func_8015D738(void *arg0) {
    u8 *p = D_80078E78;
    s32 s1;
    func_80148AFC();
    if (func_80161B18(arg0) != 0) return;
    if (func_80161B84(arg0) != 0) return;
    s1 = *(s32 *)((char *)arg0 + 0x178);
    if (s1 != 0) {
        if (*(u16 *)s1 == 0x360) goto block_808;
    }
    __asm__ __volatile__("");
    if (s1 != 0) {
        if (*(u16 *)s1 != 0) goto block_7F4;
    }
    D_801891B8[*(u16 *)arg0](arg0);
    func_80147078(arg0, 0);
    func_80159B70(arg0);
    return;
block_7F4:
    if (func_80148800(arg0) & 0x80) {
    block_808:
        func_80154A74(arg0, 0x11);
        func_8015DAC4(arg0);
        return;
    }
    if ((func_80148800(arg0) & 0x10) && func_8014BEF8(arg0) != 0) {
        func_80154A74(arg0, 0x11);
        func_8015DE24(arg0);
        return;
    }
    if ((func_80148800(arg0) & 0x20) && p[0x49] == 0xA) {
        if (func_80165624(arg0) != 0) {
            func_8015DA5C(arg0);
            func_8015F948(arg0);
            return;
        }
        func_80154A74(arg0, 0x11);
        func_800CAF14(arg0);
        return;
    }
    if (func_801488A8(arg0) != 0 && *(u16 *)(*(s32 *)((char *)arg0 + 0x178)) != 0x82) {
        func_80154150(arg0, 0x1B);
        func_80146DB8(arg0, &D_8018917C);
    } else {
        func_80154150(arg0, 0x1A);
        func_80146DB8(arg0, &D_8018918C);
    }
    func_80147A84(arg0);
    func_801473EC(arg0);
    s1 = *(s32 *)((char *)arg0 + 0x178);
    *(s16 *)(s1 + 6) = (s16)((s8)D_801893FC[*(s32 *)((char *)arg0 + 0x234)] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xc));
    *(s16 *)(s1 + 0xa) = (s16)((s8)D_801893FC[*(s32 *)((char *)arg0 + 0x234) + 1] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0xe));
    *(s16 *)(s1 + 0xe) = (s16)((s8)D_801893FC[*(s32 *)((char *)arg0 + 0x234) + 2] + *(u16 *)(*(s32 *)(s1 + 0x78) + 0x10));
    func_80149374(arg0, (void *)(s1 + 4));
    *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = (*(u16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x12) + 0x800) & 0xFFF;
    if (func_8014D738(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (func_80161208(arg0) != 0) return;
    func_801483E8(arg0);
}
