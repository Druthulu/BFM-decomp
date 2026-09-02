#include "common.h"

s32 func_8016AB6C(s32 arg0) {
    typedef struct Obj_8016AB6C {
        s32 unk0;
        s32 unk4;
        u8  pad8[0xE - 0x8];
        s16 unkE;
        u8  pad10[0x24 - 0x10];
        u8  unk24, unk25, unk26, unk27;
        u8  pad28[0x2E - 0x28];
        s16 unk2E;
        s16 unk30;
    } Obj_8016AB6C;
    typedef struct Ent_8016AB6C {
        u16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
        s32 unk10, unk14, unk18, unk1C;
        Obj_8016AB6C *unk20;
        s16 unk24, unk26, unk28, unk2A;
        s32 unk2C;
        s32 unk30;
    } Ent_8016AB6C;
    typedef struct SVec_8016AB6C {
        s16 vx, vy, vz, pad;
    } SVec_8016AB6C;

    extern s32 func_801783D0(s32 a0, s32 a1);
    extern void func_80024054(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern s32 rand(void);
    extern void func_801465C0(void);
    extern void func_80146C3C(u8 *a0);
    extern void func_800D20C0(void *a0, void *a1, s32 a2);
    extern u8 D_801850EC[];
    extern u8 D_801A6F70[];
    extern u8 D_801850FC[];
    extern u8 D_801A6F98[];

    SVec_8016AB6C sp10;
    SVec_8016AB6C sp18;
    s16 var_s0;
    s16 var_v1;
    s16 var_s3;
    s16 tmp;
    s32 temp_v0;
    u32 r;
    u8 var_c2;
    Obj_8016AB6C *obj;

    temp_v0 = func_801783D0(((Ent_8016AB6C *)arg0)->unk30, 0);
    var_s0 = 3;
    var_v1 = -0x1000;
    ((Ent_8016AB6C *)arg0)->unk30 = temp_v0;
    do {
        if (temp_v0 & var_v1) {
            goto lout;
        }
        var_s0--;
        var_v1 >>= 4;
    } while (var_s0 >= 0);
lout:
    switch (((Ent_8016AB6C *)arg0)->unk2C) {
    case 0:
        ((Ent_8016AB6C *)arg0)->unk26 = 1;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x60;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x20;
        break;
    case 1:
    case 5:
        ((Ent_8016AB6C *)arg0)->unk14 = 0xFFF60000;
        r = ((u32(*)())rand)();
        tmp = var_s0 + 1;
        var_s0 = tmp;
        ((Ent_8016AB6C *)arg0)->unk10 = (r & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk18 = ((r >> 4) & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unk30 |= 0xA << (tmp * 4);
        break;
    case 2:
    case 4:
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        break;
    case 3:
        tmp = var_s0 + 1;
        var_s0 = tmp;
        var_s0++;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        ((Ent_8016AB6C *)arg0)->unk30 = (((Ent_8016AB6C *)arg0)->unk30 | (0xF << (tmp * 4))) * 0x10;
        break;
    case 6:
    case 7:
        obj = ((Obj_8016AB6C *(*)(s32))func_801465C0)(temp_v0);
        if (obj == 0) {
            ((void(*)(Ent_8016AB6C *))func_80146C3C)(((Ent_8016AB6C *)arg0));
            return;
        }
        sp10.vx = ((Ent_8016AB6C *)arg0)->unk6;
        sp10.vy = ((Ent_8016AB6C *)arg0)->unkA - 0x18;
        sp10.vz = ((Ent_8016AB6C *)arg0)->unkE;
        ((void(*)(SVec_8016AB6C *, SVec_8016AB6C *, s32))func_800D20C0)(&sp10, &sp18, 6);
        ((Ent_8016AB6C *)arg0)->unk6 = sp10.vx;
        ((Ent_8016AB6C *)arg0)->unkA = sp10.vy;
        ((Ent_8016AB6C *)arg0)->unkE = sp10.vz;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            var_s3 = ((s32(*)(void *, void *))func_80024054)(D_801850EC, D_801A6F70) + 3;
            func_8001CE28(obj, D_801A6F70);
        } else {
            var_s3 = ((s32(*)(void *, void *))func_80024054)(D_801850FC, D_801A6F98) + 9;
            func_8001CE28(obj, D_801A6F98);
        }
        obj->unkE = var_s3;
        obj->unk4 |= 0x04000000;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            obj->unk27 = 0xB5;
            var_s0 = 0x70;
        } else {
            obj->unk27 = 0xAE;
            var_s0 = 0xB0;
        }
        var_c2 = var_s0;
        var_s0 = var_s3 >> 2;
        obj->unk2E = -8;
        obj->unk30 = 0;
        obj->unk26 = var_c2;
        obj->unk25 = var_c2;
        obj->unk24 = var_c2;
        ((Ent_8016AB6C *)arg0)->unk20 = obj;
        break;
    }
    ((Ent_8016AB6C *)arg0)->unk2A = 4 - (var_s0 * 4);
    ((Ent_8016AB6C *)arg0)->unk28 = var_s0;
    ((Ent_8016AB6C *)arg0)->unk1C = 0xB;
    ((Ent_8016AB6C *)arg0)->unk2++;
}

