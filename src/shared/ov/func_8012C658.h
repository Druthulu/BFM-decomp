/* func_8012C658 — shared body (overlay slot 0x80128158, h_exact c0654b3f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80126720[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2) {
    struct S8012C658 sp;
    s32 var_v0;
    u16 *var_a1;
    u16 *end;
    u16 *param;
    if ((arg2 != 0) && (*(u16 *)(arg2 + 0x0) != 0)) {
        sp.unk0 = *(u16 *)(arg2 + 0x6);
        sp.unk2 = *(u16 *)(arg2 + 0xA);
        sp.unk4 = *(u16 *)(arg2 + 0xE);
    } else {
        sp.unk4 = 0;
        sp.unk2 = 0;
        sp.unk0 = 0;
    }
    sp.unk6 = (s16)arg0;
    sp.unk8 = (s16)arg1;
    sp.unkA = 0;
    sp.unk10 = 0;
    sp.unkE = 0;
    sp.unkC = 0x7FFF;
    param = &sp.unk0;
    end = (u16 *)D_80126720;
    if (arg2 == 0) {
        var_a1 = (u16 *)((u8 *)end - 0x6480);
    } else {
        var_a1 = (u16 *)(arg2 + 0x10C);
    }
    while (var_a1 != end) {
        if (*var_a1 == 0) {
            goto found;
        }
        var_a1 = (u16 *)((u8 *)var_a1 + 0x10C);
    }
    var_a1 = 0;
found:
    var_v0 = 0;
    if (var_a1 != 0) {
        var_v0 = ((s32 (*)(u16 *, u16 *))func_8012C890)(param, var_a1);
    }
    return var_v0;
}
