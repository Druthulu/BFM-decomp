/* func_8017DCD8 — shared body (overlay slot 0x80128158, h_exact b2ff7ffd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_PlaySoundUnlessSkipped(s32 arg0);
extern void func_8017DF10(int);
void func_8017DCD8(Ent_8017BFE0_8017DCD8 *param_1)
{
    s32 t;
    t = param_1->unk1C.s;
    param_1->unk1C.s = t + 1;
    if (t < 0x20) {
        param_1->unk2A.u = param_1->unk2A.u - 0x10;
    } else {
        if (param_1->unk30.val.s == 0) {
            guess_PlaySoundUnlessSkipped(param_1->unk2C.i.lo.u);
        }
        param_1->unk1C.s = 0;
        param_1->unk2.u = param_1->unk2.u + 1;
    }
    ((void (*)(Ent_8017BFE0_8017DCD8 *))func_8017DF10)(param_1);
}
