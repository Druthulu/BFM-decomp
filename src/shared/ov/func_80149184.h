/* func_80149184 — shared body (overlay slot 0x80128158, h_exact 5a1468d0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_GetCameraYaw(s32 a0);
s32 func_80149184(s32 a0) {
    s32 v0;
    s32 v1;
    v0 = guess_GetCameraYaw(a0);
    v1 = *(u16*)(*(s32*)(a0 + 0x20) + 0x12);
    return (v1 - v0) & 0xFFF;
}
