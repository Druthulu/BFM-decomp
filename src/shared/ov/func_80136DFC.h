/* func_80136DFC — shared body (overlay slot 0x80128158, h_exact 6abee49e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
extern u16 guess_g_PlayerPosY; // Names ledger: config/names.tsv guess_g_PlayerPosY
extern u16 guess_g_PlayerPosZ; // Names ledger: config/names.tsv guess_g_PlayerPosZ
extern s32 *guess_g_PlayerModelPtr; // Names ledger: config/names.tsv guess_g_PlayerModelPtr
extern u16 D_80126CC4;
extern M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32);
void func_80136DFC(void) {
    ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xA, (*(s16 *)&guess_g_PlayerPosX), 0x110, 0x3C, 4, 0);
    ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xB, (*(s16 *)&guess_g_PlayerPosY), 0x110, 0x44, 4, 0);
    ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xC, (*(s16 *)&guess_g_PlayerPosZ), 0x110, 0x4C, 4, 0);
    ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xD, *(s16 *)((s32)guess_g_PlayerModelPtr + 0x12), 0x110, 0x54, 4, 0);
    ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xE, D_80126CC4, 0x110, 0x5C, 4, 0);
}
