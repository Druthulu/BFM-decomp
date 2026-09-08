/* func_801718AC — shared body (overlay slot 0x80128158, h_exact 42c81ec5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern s32 D_80126D50;
extern s32 D_80126D54;
extern u8 D_80126D6C;
extern void func_80171A1C(u8 *a0);
void func_801718AC(void *arg0) {
    D_80126D54 = (s32)arg0;
    D_80126D6C = 0;
    D_80126D50 = *(s32 *)arg0 | (D_80126D50 & 0x7F000000);
    func_80171A1C((u8 *)&D_80126B58);
}
