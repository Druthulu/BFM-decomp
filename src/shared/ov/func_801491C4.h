/* func_801491C4 — shared body (overlay slot 0x80128158, h_exact da28bc5e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 D_801151D4;
s32 func_801491C4(s32 a0) {
    s32 p;
    s32 v0;
    p = D_801151D4;
    v0 = ratan2(*(s32*)(p + 0x3C) - *(s32*)(p + 0x48), *(s32*)(p + 0x44) - *(s32*)(p + 0x50));
    return (s16)v0;
}
