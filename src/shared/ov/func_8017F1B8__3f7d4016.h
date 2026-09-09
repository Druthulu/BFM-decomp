/* func_8017F1B8 — shared body (overlay slot 0x80128158, h_exact 3f7d4016). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017F1B8(void *arg0) {
    s32 result;
    s32 v0;
    s32 a0;

    result = func_80014C54(0, 0, 0x800);
    if ((result << 16) != 0) {
        v0 = func_800CF8B4();
        if (v0 != 0) {
            a0 = *(s32 *)((s32)arg0 + 0xDC);
            D_8018FB28 = 1;
            func_800D1724(a0);
            func_8012AD50(arg0);
        }
    }
}
