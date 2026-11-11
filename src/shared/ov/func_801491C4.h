/* guess_GetCameraYaw — shared body (overlay slot 0x80128158, h_exact da28bc5e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 guess_g_ActiveCamera;
/* guess_GetCameraYaw: returns the active camera's yaw from its reference point to its view point
 * Confidence medium, code inference: (s16)ratan2 of the active camera's view-point minus reference-point x/z words, the words guess_UpdateCamera passes to GsSetRefView2L
 * Names ledger: config/names.tsv guess_GetCameraYaw */
s32 guess_GetCameraYaw(s32 a0) {
    s32 p;
    s32 v0;
    p = guess_g_ActiveCamera;
    v0 = ratan2(*(s32*)(p + 0x3C) - *(s32*)(p + 0x48), *(s32*)(p + 0x44) - *(s32*)(p + 0x50));
    return (s16)v0;
}
