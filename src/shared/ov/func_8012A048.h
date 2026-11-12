/* func_8012A048 — shared body (overlay slot 0x80128158, h_exact dee370ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
extern u16 guess_g_PlayerPosY; // Names ledger: config/names.tsv guess_g_PlayerPosY
extern u16 guess_g_PlayerPosZ; // Names ledger: config/names.tsv guess_g_PlayerPosZ
extern s16 guess_g_CameraFollowPos; // Names ledger: config/names.tsv guess_g_CameraFollowPos
extern s16 D_80126942;
extern s16 D_80126944;
s32 func_8012A048(void *a0, s32 a1, u8 a2) {
    *(s32 *)((s32)a0 + 0x0) = a1;
    *(u8 *)((s32)a0 + 0x4) = a2;
    *(s32 *)((s32)a0 + 0x9C) = 0;
    *(s16 *)((s32)a0 + 0xA0) = 0;
    *(s16 *)((s32)a0 + 0xA2) = 0;
    guess_g_CameraFollowPos = guess_g_PlayerPosX;
    D_80126942 = guess_g_PlayerPosY;
    D_80126944 = guess_g_PlayerPosZ; return guess_g_PlayerPosX;
}
