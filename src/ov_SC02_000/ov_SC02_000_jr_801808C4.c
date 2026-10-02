#include "common.h"
#include "../shared/engine_prelude.h"


typedef void (*Handler)(struct Entry_8016E95C *);
extern s32 func_801506A4(s32 a0, s32 a1);
extern s32 func_80161CD0(s32 a0, s32 a1);
#include "../shared/ov/func_801808C4__088fcd06.h"


// @class: plumbing
// @unstuck(P36): none — MATCH expected (param in $s0 across call, stores in source order)

extern void func_80130740(void *a0, u16 *a1);
extern unsigned char D_8018E78C[];

void func_80180A18(int param)
{
    ((int (*)(int, void *))func_80130740)(param, &D_8018E78C);
    ((Unkstruct_800B5CB8 *)param)->unk1C = 0x1e;
    CAST_WIDTH(int, param, 0x18) = 0;
    CAST_WIDTH(int, param, 0x10) = 0;
    ((Unkstruct_800B5CB8 *)param)->unk2 = 0xf;
    ((Unkstruct_800B5CB8 *)param)->unk5C = 0;
}



// @class: plumbing
// @unstuck(P36): none — MATCH expected (simple struct-field init + two calls, natural schedule)

extern void func_8012A828(s32, void *);
extern void func_8002D4C8(s32, s32);
extern unsigned char D_801A6F44;

void func_80180A64(s32 param_1)
{
    ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x10;
    ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unk5C = 0;
    ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0;
    ((void (*)(s32, u8 *))func_8012A828)(param_1, ((u8 *)&D_801A6F44));
    ((Unkstruct_800B5CB8 *)param_1)->unk98 = 0;
    ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk2C |= 0x10;
    ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk1A = 0x100;
    func_8002D4C8(0x436, 0);
}



extern s32 D_80126B58;
extern s32 func_8012E544(s32 a0);
extern void func_8012A828(s32, void *);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern s32 func_8012CBA4(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_801803B0(void);
extern s32 rand(void);
extern s16 D_8018E794;
extern s16 D_8018E796;
extern unsigned char D_8018E68C[];
extern unsigned char D_801A648C[];
extern unsigned char D_801A6F44;

void func_80180AD4(s32 param_1)
{
    u8 *base = (u8 *)&D_80126B58;
    s32 flag;
    s32 cond;
    s32 t;
    s32 d;
    s32 y;
    u16 mode;
    s32 p;

    mode = CAST_SIGN(u16, param_1, 0x70);
    cond = 1;
    if ((u32)(mode - 0x505) >= 2) {
        cond = ((mode & 0xff00) == 0x700);
    }
    if (cond == 0) {
        flag = 0;
    } else {
        p = func_8012E544(0x298);
        if (p != 0) {
            if (CAST_SIGN(u16, p, 2) != 2) {
                flag = 0;
            } else {
                d = CAST_SIGN(s16, p, 0xe) - CAST_SIGN(s16, param_1, 0xe);
                if (d < 0) {
                    d = -d;
                }
                flag = d < 0x20;
            }
        }
    }

    if (flag != 0) {
        ((Unkstruct_800B5CB8 *)param_1)->unk2 = 0x10;
        ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
        ((Unkstruct_800B5CB8 *)param_1)->unk5C = 0;
        ((Unkstruct_800B5CB8 *)param_1)->unk1C = 0;
        ((void (*)(s32, u8 *))func_8012A828)(param_1, ((u8 *)&D_801A6F44));
        ((Unkstruct_800B5CB8 *)param_1)->unk98 = 0;
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk2C |= 0x10;
        ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk1A = 0x100;
        func_8002D4C8(0x436, 0);
    } else {
        switch (((Unkstruct_800B5CB8 *)param_1)->unk34) {
        case 0:
            if (((Unkstruct_80126B58 *)base)->unkE > D_8018E794) {
                ((Unkstruct_800B5CB8 *)param_1)->unk34 = 1;
                func_8012B178(param_1, 0xfff60000);
            }
            break;
        case 1:
            t = CAST_SIGN(u16, param_1, 0xfc) - 1;
            ((Unkstruct_800B5CB8 *)param_1)->unkFC = t;
            if ((t << 0x10) <= 0) {
                func_80143B6C(param_1, 0);
                ((Unkstruct_800B5CB8 *)param_1)->unkFC = 8;
            }
            func_8012CBA4(param_1);
            y = CAST_SIGN(s16, param_1, 0xe);
            if ((y < D_8018E796) || ((y - ((Unkstruct_80126B58 *)base)->unkE) < 0x80)) {
                ((Unkstruct_800B5CB8 *)param_1)->unk70 = 0;
                ((Unkstruct_800B5CB8 *)param_1)->unkC1 = 0;
                ((Unkstruct_800B5CB8 *)param_1)->unk2 = 1;
                ((Unkstruct_800B5CB8 *)param_1)->unk34 = 0;
                ((Unkstruct_800B5CB8 *)param_1)->unk1C = (rand() & 0x1f) + 0x46;
                CAST_WIDTH(u16, param_1, 0xe0) = 0;
                *(u16 *)(param_1 + 0xe2) = ((Unkstruct_800B5CB8 *)*(s32 *)(param_1 + 0x20))->unk12;
                switch ((s32)((u32)CAST_SIGN(u16, param_1, 0x70) << 0x10) >> 0x18) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    if ((CAST_SIGN(u16, param_1, 0xfe) & 2) != 0) {
                        *(u16 *)(param_1 + 0xe2) = 0;
                    }
                    goto seq;
                case 5:
                    ((void (*)(s32))func_801803B0)(param_1);
                    break;
                case 4:
                case 6:
                default:
                seq:
                    CAST_WIDTH(u16, param_1, 0xe4) = 0x1e;
                    CAST_WIDTH(u16, param_1, 0x5e) = 0;
                    ((Unkstruct_800B5CB8 *)param_1)->unk5C = 0xaa10;
                    func_8012B2CC(param_1);
                    func_8012B23C(param_1);
                    func_8012B14C(param_1, (s32)&D_8018E68C);
                    func_8012A828(param_1, &D_801A648C);
                    break;
                }
            }
            break;
        }
    }
}
