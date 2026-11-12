/* guess_SetPlayerHit — shared body (overlay slot 0x80128158, h_exact d302f6ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *memcpy(void *, const void *, u32);
extern u8 D_80126C38;
extern u8 D_80126C40;
extern u16 D_80126B94;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s16 D_80126B9A;
/* guess_SetPlayerHit: records a contact on the player: ORs a0 into guess_g_PlayerActor +0x3C and stores a1-a3, the point a4 and the vector a5
 * Confidence low, xref chain: D_80126B94 |= a0; +0x3E = a1, +0x42 = a2, +0x40 = a3; 8 bytes of a4 to +0xE0, of a5 to +0xE8; callers pass guess_g_BoxHitNormalX as a5
 * Names ledger: config/names.tsv guess_SetPlayerHit */
void guess_SetPlayerHit(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6)
{
    do { memcpy(&D_80126C38, param_5, 8); } while (0);
    memcpy(&D_80126C40, param_6, 8);
    D_80126B96 = param_2;
    D_80126B9A = param_3;
    D_80126B98 = param_4;
    D_80126B94 = D_80126B94 | param_1;
}
