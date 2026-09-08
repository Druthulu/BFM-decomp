/* func_8014B6F0 — shared body (overlay slot 0x80128158, h_exact dc277271). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80078E9C;
extern s32 D_80078ED0;
void func_8014B6F0(s32 a0, s32 a1) {
    D_80078E9C += a1;
    if (*(s16*)((s32)&D_80078E9C + 2) >= 0xA1) {
        D_80078E9C = 0xA00000;
    }
    D_80078ED0 += a1;
    if (*(s16*)((s32)&D_80078ED0 + 2) >= 0xA1) {
        D_80078ED0 = 0xA00000;
    }
}
