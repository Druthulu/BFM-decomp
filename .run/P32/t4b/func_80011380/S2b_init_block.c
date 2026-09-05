#include "common.h"

extern u8 D_800AF630[];
extern s32 D_80074784;
extern s32 D_8007478C;
extern u16 D_800B99E8;
extern s32 D_800629D4[];
extern u8 D_800629D6[];
extern u16 D_800629E8[];
extern u8 D_800D3A68[];
extern s32 D_800AE6A8;

extern void func_800295D4(void);
extern void func_80029664(void);
extern void func_80011DCC(void);
extern void func_80011E24(void);
extern void func_8005C4CC(s32);
extern void func_8002D4C8(s32, s32);
extern void func_80011B7C(s32);
extern void func_800118AC(void);
extern void func_80011EB4(void);
extern void func_800CEDFC(void);
extern s32 func_80014CAC(s32, s32);
extern void func_80011DA0(void);
extern void func_800D1724(s32);

/* NEAR (6/192, REGALLOC-LOCAL). The instruction STREAM is exact; the six
 * residual words differ only in register numbers inside the D_800629D6 index.
 * The target's index is TWO chained *2 expansions (`copy;sll;copy;sll`), which
 * -O0 only emits when an intermediate is a `register` local (an EXPAND_SUM
 * index multiply drops the operand copy -- see the note in the wave report).
 * Any such local is BORN AT ITS BLOCK ENTRY, so it takes $v1 ahead of the
 * loaded value and the temps spill onto $a1; the target colours the same
 * stream $v1/$a0 only. No C spelling reaches that colouring. */
void func_80011380(void) {
    typedef struct {
        u8 pad00[0x16];
        u8 unk16;
    } Unk;
    register u8 *p = D_800AF630;
    Unk *q = (Unk *)&D_800AE6A8;

    switch (*(u16 *)(p + 0xA3B4)) {
    case 0:
        D_800B99E8 = 0;
        func_800295D4();
        if (D_80074784 >= 5) {
            D_80074784 = 0;
        }
        *(u16 *)(p + 0xA3D8) = D_800629D4[D_80074784];
        *(u16 *)(p + 0xA3DA) = (u16)D_800629D4[D_80074784] & 0xF000;
        {
            register s32 t = D_80074784;
            t = t * 2;
            q->unk16 = D_800629D6[t * 2];
        }
        D_8007478C = D_800629E8[D_80074784];
        if (D_80074784 == 0) {
            func_80029664();
        }
        func_80011DCC();
        func_80011E24();
        func_8005C4CC(1);
        *(p + 0xA434) = 1;
        *(p + 0xA3E0) = 0;
        ++D_80074784;
        func_8002D4C8(0x28, 0);
        func_80011B7C(0);
        func_800118AC();
        break;
    case 1:
        if (*(p + 0xA3E0) != 0) {
            func_80011EB4();
        }
        func_800CEDFC();
        if ((s16)(++D_800B99E8) > D_8007478C ||
            ((s16)func_80014CAC(0, 0x840) != 0 && *(p + 0xA3E0) != 0)) {
            func_80011DA0();
            func_800D1724((s32)D_800D3A68);
            func_800118AC();
        }
        break;
    case 2:
        func_800CEDFC();
        break;
    }
}
