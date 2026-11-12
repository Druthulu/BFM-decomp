/* func_80136A94 — shared body (overlay slot 0x80128158, h_exact b58271ec). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80136A94(s32 a0, s32 a1, s32 a2, s32 a3) {
    extern void ApplyMatrixSV(void *m, void *v0, void *v1);
    extern void ApplyRotMatrix(void *v0, void *v1);
    extern u16 guess_g_BoxHitCenterY; // Names ledger: config/names.tsv guess_g_BoxHitCenterY
    extern s16 guess_g_BoxHitCenterZ; // Names ledger: config/names.tsv guess_g_BoxHitCenterZ
    extern s16 guess_g_BoxHitNormalY; // Names ledger: config/names.tsv guess_g_BoxHitNormalY
    extern s16 guess_g_BoxHitNormalZ; // Names ledger: config/names.tsv guess_g_BoxHitNormalZ

    s32 out[4];
    u16 *pb4;

    if (a0) {
        ApplyMatrixSV((void *)a3, *(void **)&D_8017F05C, *(void **)&D_8017F05C);
        ApplyMatrixSV((void *)a3, (void *)guess_g_BoxHitCenterX, (void *)guess_g_BoxHitCenterX);
        ApplyRotMatrix((void *)guess_g_BoxHitNormalX, (void *)out);
        *(s16 *)guess_g_BoxHitNormalX = out[0];
        guess_g_BoxHitNormalY = out[1];
        guess_g_BoxHitNormalZ = out[2];
    }

    pb4 = *(u16 **)&D_8017F05C;
    *(s16 *)(a2)     = pb4[0] + *(s32 *)(a1 + 0x48);
    *(s16 *)(a2 + 2) = pb4[1] + *(s32 *)(a1 + 0x4C);
    *(s16 *)(a2 + 4) = pb4[2] + *(s32 *)(a1 + 0x50);

    *(u16 *)guess_g_BoxHitCenterX = *(u16 *)guess_g_BoxHitCenterX + *(s32 *)(a1 + 0x48);
    guess_g_BoxHitCenterY = guess_g_BoxHitCenterY + *(s32 *)(a1 + 0x4C);
    guess_g_BoxHitCenterZ = guess_g_BoxHitCenterZ + *(s32 *)(a1 + 0x50);
}
