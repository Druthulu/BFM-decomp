/* func_8017D0BC — shared body (overlay slot 0x80128158, h_exact fe5e6da3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017D0BC(Ent_8017BFE0_8017D0BC *param_1)
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
    ((void (*)(Ent_8017BFE0_8017D0BC *))func_8017D2F4)(param_1);
}
