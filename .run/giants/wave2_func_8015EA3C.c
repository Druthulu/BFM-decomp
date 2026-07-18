#include "common.h"

extern s32 func_801487F4(void);
extern void func_80147078(void *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80149D10(void *a0);
extern void func_80175150(void *a0);
extern void func_8016EE40(s32 a0, s32 a1);
extern s32 func_80149744(void *a0);
extern void func_80149788(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_8014A4B4(void *a0);
extern void func_8014A4FC(void *a0);
extern s32 func_80149AA8(void *a0);
extern void func_80149AD4(void *a0);
extern s32 func_80149B54(void *a0);
extern void func_80149BAC(void *a0);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(void *a0);
extern s32 func_80148E54(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(void *a0, void *a1);
extern void func_80147A84(void *a0);
extern void func_801473EC(void *a0);
extern void func_80154150(void *a0, s32 a1);
extern s32 func_8014D738(void *a0);
extern void func_8015C714(void *a0);
extern s32 func_80161208(void *a0);
extern void func_801483E8(void *a0);

extern void (*D_801891B8[])(void *);
extern u16 D_801152A0;

void func_8015EA3C(void *arg0) {
    s32 invec[4];
    s32 outbuf[4];
    s32 temp;
    s32 r;

    if (!(func_801487F4() & 8)) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    r = func_80149D10(arg0);
    if (r == 1) goto Lcase1;
    if (r < 2) goto Ldefault;
    if (r == 2) goto Lcase2;
    goto Ldefault;
Lcase1:
    D_801891B8[*(u16 *)arg0](arg0);
    func_80175150(arg0);
    return;
Lcase2:
    func_8016EE40(*(s32 *)((u8 *)arg0 + 0x21C), 0x01000000);
    return;
Ldefault:
    if (func_80149744(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80149788(arg0);
        return;
    }
    if (func_80161B84(arg0) != 0) {
        return;
    }
    if (func_8014A4B4(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_8014A4FC(arg0);
        return;
    }
    if (func_80149AA8(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80149AD4(arg0);
        return;
    }
    if (func_80149B54(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80149BAC(arg0);
        return;
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) =
            (D_801152A0 + func_801491C4(arg0)) & 0xFFF;
    }
    temp = func_80148E54(arg0);
    if ((s16)temp >= 0) {
        s32 d = temp - *(u16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12);
        invec[0] = 0;
        invec[1] = 0;
        invec[2] = 0xFFFC0000;
        func_8001382C((s16)d, invec, outbuf);
        func_80146DB8(arg0, outbuf);
        func_80147A84(arg0);
        func_801473EC(arg0);
        func_80154150(arg0, 0x1E);
    } else {
        func_80154150(arg0, 0x1D);
    }
    if (func_8014D738(arg0) != 0) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 9);
        func_8015C714(arg0);
        return;
    }
    if (func_80161208(arg0) == 0) {
        func_801483E8(arg0);
    }
}
