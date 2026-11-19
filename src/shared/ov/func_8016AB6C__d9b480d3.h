/* func_8016AB6C — shared body (overlay slot 0x80128158, h_exact d9b480d3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of guess_FreeSmallObject or addiu $v0, $v0, 0x1 at ov_SC03_126:0x8016AE34; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x2A4, ov_SC03_126 objdump */
s32 func_8016AB6C(s32 arg0) {
    extern u32 guess_IntToBcd(s32 a0, s32 a1);
    extern s32 guess_SjisToGlyphCodes(u8 *a0, u8 *a1);
    extern void func_8001CE28(Obj_8016AB6C *a0, u8 *a1);
    extern u8 D_801823A4[];
    extern u8 D_801823B4[];
    extern u8 D_8018EC30[];
    extern u8 D_8018EC58[];

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
        obj = ((Obj_8016AB6C *(*)(s32))guess_AllocSpriteObject)(temp_v0);
        if (obj == 0) {
            ((void(*)(Unkstruct_8011D030 *))guess_FreeSmallObject)(((Unkstruct_8011D030 *)arg0));
            return;
        }
        sp10.vx = ((Unkstruct_8011D030 *)arg0)->unk6.u;
        sp10.vy = ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u - 0x18;
        sp10.vz = ((Unkstruct_8011D030 *)arg0)->unkE.u;
        ((void(*)(SVec_8016AB6C *, SVec_8016AB6C *, s32))func_800D20C0)(&sp10, &sp18, 6);
        ((Unkstruct_8011D030 *)arg0)->unk6.u = sp10.vx;
        ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.u = sp10.vy;
        ((Unkstruct_8011D030 *)arg0)->unkE.u = sp10.vz;
        if (((Unkstruct_8011D030 *)arg0)->unk2C.val.s == 6) {
            var_s3 = guess_SjisToGlyphCodes(D_801823A4, D_8018EC30) + 3;
            func_8001CE28(obj, D_8018EC30);
        } else {
            var_s3 = guess_SjisToGlyphCodes(D_801823B4, D_8018EC58) + 9;
            func_8001CE28(obj, D_8018EC58);
        }
        obj->unkE = var_s3;
        obj->unk4 |= 0x04000000;
        if (((Unkstruct_8011D030 *)arg0)->unk2C.val.s == 6) {
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
        ((Unkstruct_8011D030 *)arg0)->unk20 = obj;
        break;
    }
    ((Unkstruct_8011D030 *)arg0)->unk2A.s = 4 - (var_s0 * 4);
    ((Unkstruct_8011D030 *)arg0)->unk28.s = var_s0;
    ((Unkstruct_8011D030 *)arg0)->unk1C = 0xB;
    ((Unkstruct_8011D030 *)arg0)->unk2.u++;
}
