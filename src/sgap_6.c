#include "common.h"

void func_8003FA54(void) {
    extern u16 D_800A5F60;
    D_800A5F60 = 0;
}

extern s32 D_800BA1B0;
extern u8 D_800AE614;
extern u32 D_800C7EC0[16];
extern u16 D_8007958E;
extern u8 D_800BA100;
extern u8 D_800795A3;
extern u16 D_800C7F04;
extern u16 D_800C7F06;
extern s16 D_800795A4;
extern s16 D_800795B0;
extern u8 D_800A4620;
extern u16 D_80078D8C;
extern u16 D_80078D8E;
extern u16 D_80078D90;
extern u16 D_80078D92;
extern u16 D_800B9B58;
extern u16 D_800B9B5C;
extern u16 D_800B9B5E;
extern void (*D_800BA0D0)(s32);
extern void (*D_800AE828)(s32);
extern u16* D_8006B8FC;
extern void func_8003FE18(s32, u32);

void func_8003FA64(void) {
    s32 pad[2]; /* frame pad: target vars=16 (cookbook §226 / §162i1 dead-local lever) */
    s32 i = 0;
    s32 n;
    u32 mask;
    u32 off;
    u8* fp;
    u16* pa2;
    u16* pa3;
    u16* pt0;
    u16* pt1;
    u16* pend;
    u16* pb;
    u16 r1, r2, r3, r4, r5, r6;
    u16* dp;

    D_800BA1B0 = (D_800BA1B0 + 1) & 0xF;
    D_800C7EC0[D_800BA1B0] = 0;
    n = D_800AE614;
    if (n > 0) {
        u32* mp = &D_800C7EC0[D_800BA1B0];
        u32 one = 1;
        s32 count = D_800AE614;
        u16* vp = D_8006B8FC;
        u32 off0 = 0;
        do {
            u16 val = *(u16*)((char*)vp + 0xC);
            *(u16*)((char*)&D_8007958E + off0) = val;
            if (val == 0) {
                *mp |= one << i;
            }
            vp += 8;
            off0 += 0x34;
            i++;
        } while (i < count);
    }

    i = 0;
    if (D_800BA100 == 0) {
        mask = -1;
        do {
            mask &= D_800C7EC0[i];
            i++;
        } while (i < 0xF);
        for (i = 0; i < (s32)D_800AE614; i++) {
            u32 one = 1;
            u32 two = 2;
            off = i * 0x34;
            if ((mask & (one << i)) != 0) {
                if (*(u8*)((char*)&D_800795A3 + off) == two) {
                    func_8003FE18(0, 0xFFFFFF);
                }
                *(u8*)((char*)&D_800795A3 + off) = 0;
            }
        }
        i = 0;
    }

    D_80078D8C &= ~D_800C7F04;
    D_80078D8E &= ~D_800C7F06;

    off = 0;
    do {
        if (*(s16*)((char*)&D_800795A4 + off) != 0) {
            D_800BA0D0(i);
        }
        if (*(s16*)((char*)&D_800795B0 + off) != 0) {
            D_800AE828(i);
        }
        i++;
        off += 0x34;
    } while (i < 0x18);

    fp = &D_800A4620;
    pb = &D_800B9B58;
    pt1 = pb + 5;
    pt0 = pb + 4;
    {
        u32 off4 = 0;
        pa3 = pb + 1;
        pa2 = pb;
        pend = &D_800A4620 + 24;
        do {
            if ((*fp & 1) != 0) {
                u16* d1 = (u16*)(off4 + (u32)D_8006B8FC);
                *d1 = *pa2;
                *(u16*)((char*)d1 + 2) = *pa3;
            }
            if ((*fp & 4) != 0) {
                u16* d2 = (u16*)(off4 + (u32)D_8006B8FC);
                *(u16*)((char*)d2 + 4) = *(u16*)((char*)&D_800B9B5C + off4);
            }
            if ((*fp & 8) != 0) {
                u16* d3 = (u16*)(off4 + (u32)D_8006B8FC);
                *(u16*)((char*)d3 + 6) = *(u16*)((char*)&D_800B9B5E + off4);
            }
            if ((*fp & 0x10) != 0) {
                u16* d4 = (u16*)(off4 + (u32)D_8006B8FC);
                *(u16*)((char*)d4 + 8) = *pt0;
                *(u16*)((char*)d4 + 0xA) = *pt1;
            }
            *fp = 0;
            fp++;
            pt1 += 8;
            pt0 += 8;
            off4 += 0x10;
            pa3 += 8;
            pa2 += 8;
        } while ((s32)fp < (s32)pend);
    }

    dp = D_8006B8FC;
    r1 = D_800C7F04;
    r2 = D_800C7F06;
    r3 = D_80078D8C;
    r4 = D_80078D8E;
    r5 = D_80078D90;
    r6 = D_80078D92;
    D_800C7F04 = 0;
    D_800C7F06 = 0;
    D_80078D8C = 0;
    D_80078D8E = 0;
    *(u16*)((char*)dp + 0x18C) = r1;
    *(u16*)((char*)dp + 0x18E) = r2;
    *(u16*)((char*)dp + 0x188) = r3;
    *(u16*)((char*)dp + 0x18A) = r4;
    *(u16*)((char*)dp + 0x198) = r5;
    *(u16*)((char*)dp + 0x19A) = r6;
}
