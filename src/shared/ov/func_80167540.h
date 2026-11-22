/* func_80167540 — shared body (overlay slot 0x80128158, h_exact 145695c0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: result of guess_FreeSmallObject or andi $v0, $v0, 0x20 at ov_MAIN_012:0x801676D4 or addiu $v0, $v0, 0x1 at ov_MAIN_012:0x801676E8; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x1BC, ov_MAIN_012 objdump */
s32 func_80167540(s32 arg0) {

    struct Node_80167540 *node;
    Unkstruct_8011D030 *ent;
    s32 v;

    node = ((Unkstruct_8011D030 *)arg0)->unk34.n;
    if (node->unk0 == 1) {
        if (((Unkstruct_8011D030 *)arg0)->unk10.i.hi.s > ((Unkstruct_8011D030 *)arg0)->unk10.i.lo.s) {
            if (((Unkstruct_8011D030 *)arg0)->unk1C.s > 0) {
                ((Unkstruct_8011D030 *)arg0)->unk10.i.lo.s = (s16) (rand() & 0x30);
                v = -0x30;
                goto shared;
            }
        } else if (((Unkstruct_8011D030 *)arg0)->unk1C.s < 0) {
            ((Unkstruct_8011D030 *)arg0)->unk10.i.lo.s = (s16) ((rand() & 0x30) + 0x40);
            v = 0x30;
shared:
            ((Unkstruct_8011D030 *)arg0)->unk1C.s = v;
        }
        ((Unkstruct_8011D030 *)arg0)->unk10.i.hi.s = (s16) (((Unkstruct_8011D030 *)arg0)->unk10.i.hi.s + ((Unkstruct_8011D030 *)arg0)->unk1C.s);
        ((Unkstruct_8011D030 *)arg0)->unk38.mat = node->unk20->mat;
        ((void (*)(Unkstruct_8011D030 *, s32, s32, s32))func_801670E4)(((Unkstruct_8011D030 *)arg0), 0, 0, 0);
        ent = ((Unkstruct_8011D030 *(*)(s32, Unkstruct_8011D030 *, s16, s16, s32, s32, s32))guess_SpawnSmallObject)(0xE, ((Unkstruct_8011D030 *)arg0), node->unk6, node->unkA, node->unkE, 0, 0);
        if (ent != 0) {
            ent->unk38.mat = node->unk20->mat;
        }
        if (((Unkstruct_8011D030 *)arg0)->unk34.n->unk4C->unk44 & 0x20) {
            ((Unkstruct_8011D030 *)arg0)->unk30.val.s = 0x600;
            ((Unkstruct_8011D030 *)arg0)->unk2.u = (u16) (((Unkstruct_8011D030 *)arg0)->unk2.u + 1);
        }
    } else {
        ((void(*)(Unkstruct_8011D030 *))guess_FreeSmallObject)(((Unkstruct_8011D030 *)arg0));
    }
}
