/* func_80172310 — shared body (overlay slot 0x80128158, h_exact 9525ccbc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern s32 *D_80126B78;
extern void func_80172358(u8 *a0, u8 *a1);
void func_80172310(u8 *a0) {
    func_80172358((u8 *)&D_80126B58, a0);
    *(u16 *)((u8 *)D_80126B78 + 0x12) = *(u16 *)(a0 + 6);
}
