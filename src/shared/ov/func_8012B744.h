/* func_8012B744 — shared body (overlay slot 0x80128158, h_exact 6c580f8e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 x, s32 y);
s32 func_8012B744(void *a0, void *a1) {
    s32 ang;
    ang = ratan2(*(s16 *)((s32)a0 + 0xA) - *(s16 *)((s32)a1 + 0x4),
                 *(s16 *)((s32)a1 + 0x0) - *(s16 *)((s32)a0 + 0x2));
    return (ang - 0x400) & 0xFFF;
}
