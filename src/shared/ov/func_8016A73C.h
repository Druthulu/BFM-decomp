/* func_8016A73C — shared body (overlay slot 0x80128158, h_exact 02a5d43c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: sra $v0, $v0, 16 at ov_MAIN_012:0x8016A86C; no byte-neutral return: `return 0;` moved `lhu v1,10(s0)` at +0xEC, ov_MAIN_012 objdump */
s32 func_8016A73C(s32 arg0) {
    int sp10[8];
    short v[3];   /* sp30, sp32, sp34 */
    int r;
    short tmp;

    r = ((int(*)())rand)();
    v[1] = ((r & 0x7F) << 4) + 0x400;
    v[0] = ((unsigned)(r & 0x7F00) >> 5) - 0x300;
    v[2] = 0;
    ((void(*)(short *, void *))RotMatrixYXZ)(v, sp10);
    ((void(*)(int, void *))func_80048EAC)(((Unkstruct_8011D030 *)arg0)->unk34.a->unk34->unk20.val + 0x34, sp10);
    v[0] = 0;
    v[1] = 0;
    v[2] = -0x50;
    ((int(*)(void *, short *, short *))ApplyMatrixSV)(sp10, v, v);

    ((Unkstruct_8011D030 *)arg0)->unk38.mat = (*(Mat_8016A73C*)&D_800AE620);

    tmp = ((Unkstruct_8011D030 *)arg0)->unk4.i.hi.s + v[0];
    ((Unkstruct_8011D030 *)arg0)->unk4.i.hi.s = tmp;
    ((Unkstruct_8011D030 *)arg0)->unk38.mat.t[0] = tmp;
    tmp = ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.s + v[1];
    ((Unkstruct_8011D030 *)arg0)->unk8.i.hi.s = tmp;
    ((Unkstruct_8011D030 *)arg0)->unk38.mat.t[1] = tmp;
    tmp = ((Unkstruct_8011D030 *)arg0)->unkC.i.hi.s + v[2];
    ((Unkstruct_8011D030 *)arg0)->unkC.i.hi.s = tmp;
    ((Unkstruct_8011D030 *)arg0)->unk2.s = ((Unkstruct_8011D030 *)arg0)->unk2.s + 1;
    ((Unkstruct_8011D030 *)arg0)->unk38.mat.t[2] = tmp;
}
