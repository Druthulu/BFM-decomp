/* func_801466F0 — shared body (overlay slot 0x80128158, h_exact f24b6aa1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 *func_80146750(u16 *param_1);
extern u16 *func_8014680C(short *param_1);
void func_801466F0(a0, a1, a2, a3, sp5, sp6, sp7, sp8)
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
    rec.unk0 = a0;
    rec.unk8 = a1;
    rec.unk2 = a2;
    rec.unk4 = a3;
    rec.unk6 = sp5;
    rec.unkC = sp6;
    rec.unk10 = sp7;
    if (sp8 != 0) {
        func_80146750((u16 *)&rec);
    } else {
        func_8014680C((short *)&rec);
    }
}
