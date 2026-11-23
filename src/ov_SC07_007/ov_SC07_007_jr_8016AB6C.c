#include "common.h"

/* $v0 at exit: result of guess_FreeSmallObject or addiu $v0, $v0, 0x1 at ov_SC07_007:0x8016AE34; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x2A4, ov_SC07_007 objdump */
s32 func_8016AB6C(s32 arg0) {

    extern u32 guess_IntToBcd(s32 a0, s32 a1);
    extern s32 guess_SjisToGlyphCodes(void *a0, void *a1);
    extern void func_8001CE28(void *a0, void *a1);
    extern s32 rand(void);
    extern void *guess_AllocSpriteObject(void);
    extern s32 guess_FreeSmallObject(u8 *a0);
    extern void func_800D20C0(Pos800D20C0 *arg0, SVECTOR_800 *arg1, s16 arg2);
    extern u8 D_8018605C[];
    extern u8 D_801C6A78[];
    extern u8 D_8018606C[];
    extern u8 D_801C6AA0[];

    SVec_8016AB6C sp10;
    SVec_8016AB6C sp18;
    s16 var_s0;
    s16 var_v1;
    s16 var_s3;
    s16 tmp;
    s32 temp_v0;
    u32 r;
    u8 var_c2;
    Unkstruct_800B5BD8 *obj;

    temp_v0 = guess_IntToBcd(((Unkstruct_8011D030 *)arg0)->unk30.val.s, 0);
    var_s0 = 3;
    var_v1 = -0x1000;
    ((Unkstruct_8011D030 *)arg0)->unk30.val.s = temp_v0;
    do {
        if (temp_v0 & var_v1) {
            goto lout;
        }
        var_s0--;
        var_v1 >>= 4;
    } while (var_s0 >= 0);
lout:
    switch (((Unkstruct_8011D030 *)arg0)->unk2C.val.s) {
    case 0:
        ((Unkstruct_8011D030 *)arg0)->unk26.s = 1;
        ((Unkstruct_8011D030 *)arg0)->unk24.s = 0x60;
        ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u -= 0x20;
        break;
    case 1:
    case 5:
        ((Unkstruct_8011D030 *)arg0)->unk14.val = 0xFFF60000;
        r = ((u32(*)())rand)();
        tmp = var_s0 + 1;
        var_s0 = tmp;
        ((Unkstruct_8011D030 *)arg0)->unk10.val = (r & 0xF) - 8 << 0xF;
        ((Unkstruct_8011D030 *)arg0)->unk18.val = ((r >> 4) & 0xF) - 8 << 0xF;
        ((Unkstruct_8011D030 *)arg0)->unk26.s = 4;
        ((Unkstruct_8011D030 *)arg0)->unk24.s = 0x80;
        ((Unkstruct_8011D030 *)arg0)->unk30.val.s |= 0xA << (tmp * 4);
        break;
    case 2:
    case 4:
        ((Unkstruct_8011D030 *)arg0)->unk26.s = 4;
        ((Unkstruct_8011D030 *)arg0)->unk24.s = 0x80;
        ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u -= 0x18;
        break;
    case 3:
        tmp = var_s0 + 1;
        var_s0 = tmp;
        var_s0++;
        ((Unkstruct_8011D030 *)arg0)->unk26.s = 4;
        ((Unkstruct_8011D030 *)arg0)->unk24.s = 0x80;
        ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u -= 0x18;
        ((Unkstruct_8011D030 *)arg0)->unk30.val.s = (((Unkstruct_8011D030 *)arg0)->unk30.val.s | (0xF << (tmp * 4))) * 0x10;
        break;
    case 6:
    case 7:
        obj = ((Unkstruct_800B5BD8 *(*)(s32))guess_AllocSpriteObject)(temp_v0);
        if (obj == 0) {
            ((void(*)(Unkstruct_8011D030 *))guess_FreeSmallObject)(((Unkstruct_8011D030 *)arg0));
            return;
        }
        sp10.vx = ((Unkstruct_8011D030 *)arg0)->unk4.i.hi.u;
        sp10.vy = ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u - 0x18;
        sp10.vz = ((Unkstruct_8011D030 *)arg0)->unkC.i.hi.u;
        ((void(*)(SVec_8016AB6C *, SVec_8016AB6C *, s32))func_800D20C0)(&sp10, &sp18, 6);
        ((Unkstruct_8011D030 *)arg0)->unk4.i.hi.u = sp10.vx;
        ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u = sp10.vy;
        ((Unkstruct_8011D030 *)arg0)->unkC.i.hi.u = sp10.vz;
        if (((Unkstruct_8011D030 *)arg0)->unk2C.val.s == 6) {
            var_s3 = ((s32(*)(void *, void *))guess_SjisToGlyphCodes)(D_8018605C, D_801C6A78) + 3;
            func_8001CE28(obj, D_801C6A78);
        } else {
            var_s3 = ((s32(*)(void *, void *))guess_SjisToGlyphCodes)(D_8018606C, D_801C6AA0) + 9;
            func_8001CE28(obj, D_801C6AA0);
        }
        obj->head.unkE.s = var_s3;
        obj->head.unk4.s |= 0x04000000;
        if (((Unkstruct_8011D030 *)arg0)->unk2C.val.s == 6) {
            obj->head.unk24.b.unk27.u = 0xB5;
            var_s0 = 0x70;
        } else {
            obj->head.unk24.b.unk27.u = 0xAE;
            var_s0 = 0xB0;
        }
        var_c2 = var_s0;
        var_s0 = var_s3 >> 2;
        obj->head.unk2E.s = -8;
        obj->unk30.s = 0;
        obj->head.unk24.b.unk26 = var_c2;
        obj->head.unk24.b.unk25.u = var_c2;
        obj->head.unk24.b.unk24.u = var_c2;
        ((Unkstruct_8011D030 *)arg0)->unk20 = obj;
        break;
    }
    ((Unkstruct_8011D030 *)arg0)->unk2A.s = 4 - (var_s0 * 4);
    ((Unkstruct_8011D030 *)arg0)->unk28.s = var_s0;
    ((Unkstruct_8011D030 *)arg0)->unk1C.s = 0xB;
    ((Unkstruct_8011D030 *)arg0)->unk2.u++;
}

