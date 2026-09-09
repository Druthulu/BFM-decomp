/* func_8017C528 — shared body (overlay slot 0x80128158, h_exact 7dc46946). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C528(s32 param_1)
{
    s16 phi_v0;

    if ((u16)(*(u16 *)(param_1 + 0x20E) - 0x44) < 0xD) {
        func_8017C6F4(param_1, *(u8 *)(param_1 + 0x218));
        func_801542A4(param_1, &D_800D5E18);
        *(u8 *)&D_80127058 = *(u8 *)(param_1 + 0x218) + 1;
        func_80147324(0x544);
    } else {
        phi_v0 = *(u16 *)(param_1 + 0x20C) - 0x10;
        *(s16 *)(param_1 + 0x20C) = phi_v0;
        if (phi_v0 < 0) {
            *(s16 *)(param_1 + 0x20C) = 0;
        }
    }
    func_80171A80(param_1, 0x10);
    func_80171990(param_1);
}
