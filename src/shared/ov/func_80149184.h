/* guess_GetCameraRelativeYaw — shared body (overlay slot 0x80128158, h_exact 5a1468d0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_GetCameraYaw(s32 a0);
/* guess_GetCameraRelativeYaw: returns the facing yaw (+0x12 of the +0x20 model) minus the camera yaw, & 0xFFF
 * Confidence medium, xref chain: (model +0x12 - guess_GetCameraYaw(a0)) & 0xFFF; the value func_8015AE2C stores in guess_g_CameraRelativeYaw
 * Names ledger: config/names.tsv guess_GetCameraRelativeYaw */
s32 guess_GetCameraRelativeYaw(s32 a0) {
    s32 v0;
    s32 v1;
    v0 = guess_GetCameraYaw(a0);
    v1 = *(u16*)(*(s32*)(a0 + 0x20) + 0x12);
    return (v1 - v0) & 0xFFF;
}
