/* func_801653F4 — shared body (overlay slot 0x80128158, h_exact 2f02778b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80165624(s32 a0);
extern u8 D_80078EC1;
extern u8 D_80078EC5;
extern s16 currentLocationId;
void func_801653F4(s32 a0) {
    s32 loc;
    s32 v;
    loc = currentLocationId;
    D_80078EC5 = 0;
    v = D_80078EC1 & 0x7F;
    D_80078EC1 = v;
    if (func_80165624(a0) != 0) {
        D_80078EC5 = 0x80;
        return;
    }
    if (D_80078EC1 != 0x1A) {
        return;
    }
    if ((u32)(loc - 0x305C) < 2) return;
    if ((u32)(loc - 0x305E) < 2) return;
    if ((u32)(loc - 0x3060) < 2) return;
    if ((u32)(loc - 0x3062) < 2) return;
    if ((u32)(loc - 0x3064) < 2) return;
    if (loc == 0x3066) return;
    D_80078EC5 = 0x80;
}
