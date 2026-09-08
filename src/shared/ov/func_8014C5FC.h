/* func_8014C5FC — shared body (overlay slot 0x80128158, h_exact e2aa596f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80047D3C(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
s32 func_8014C5FC(s32 a0, s32 a1, void * a2)
{
    s32 dx;
    s32 dz;
    s32 dy;
    s32 r;
    dz = (s16)(*(u16 *)((s32)a1 + 0xE) + *(u16 *)((s32)a2 + 0x4) - *(u16 *)((s32)a0 + 0xE));
    dx = (s16)(*(u16 *)((s32)a1 + 0x6) + *(u16 *)((s32)a2 + 0x0) - *(u16 *)((s32)a0 + 0x6));
    r = func_80047D3C(dz * dz + dx * dx);
    dy = *(s16 *)((s32)a1 + 0xA) + *(s16 *)((s32)a2 + 0x2) - *(s16 *)((s32)a0 + 0xA);
    return ratan2(dy, (s16)r) & 0xFFF;
}
