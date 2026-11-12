/* guess_SpawnObject — shared body (overlay slot 0x80128158, h_exact f24b6aa1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 *func_80146750(u16 *param_1);
extern u16 *func_8014680C(short *param_1);
/* guess_SpawnObject: packs kind a0, parameter a1, x/y/z and two words into a record and starts an object in the 0x68-byte array D_8011F9D0 (slots 8-19, or 0-7 when the last argument is 0)
 * Confidence medium, xref chain: rec {kind, x, y, z, a1, sp6, sp7}; sp8 ? func_80146750 (slots 8..19) : func_8014680C (slots 0..7); each takes the first record with u16 +0 == 0
 * Names ledger: config/names.tsv guess_SpawnObject */
void guess_SpawnObject(a0, a1, a2, a3, sp5, sp6, sp7, sp8)
    u16 a0;
    s32 a1;
    u16 a2;
    u16 a3;
    u16 sp5;
    s32 sp6;
    s32 sp7;
    s32 sp8;
{
    Rec801466F0 rec;
    rec.x = a0;
    rec.vx = a1;
    rec.pad_2 = a2;
    rec.z = a3;
    rec.pad_6 = sp5;
    rec.vy = sp6;
    rec.vz = sp7;
    if (sp8 != 0) {
        func_80146750((u16 *)&rec);
    } else {
        func_8014680C((short *)&rec);
    }
}
