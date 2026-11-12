/* func_8017BD50 — shared body (overlay slot 0x80128158, h_exact 46531362). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_8018F914 = D_8018F914 + 1;
    if (D_8018F914 >= 0x19) {
        if (D_8018F958 != 0) {
            (*D_8018F958)();
        } else {
            guess_g_StoredRefPointX = guess_g_StoredRefPointX + D_8018F99C;
            guess_g_StoredRefPointY = guess_g_StoredRefPointY + D_8018F99E;
            guess_g_StoredRefPointZ = guess_g_StoredRefPointZ + D_8018F9A0;
            guess_g_StoredViewPointX = guess_g_StoredViewPointX + D_8018F99C;
            guess_g_StoredViewPointY = guess_g_StoredViewPointY + D_8018F99E;
            guess_g_StoredViewPointZ = guess_g_StoredViewPointZ + D_8018F9A0;
            guess_BlendToPresetCamera();
        }
        D_8018FAB0 = 0;
    }
}
