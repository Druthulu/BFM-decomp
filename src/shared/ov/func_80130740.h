/* func_80130740 — shared body (overlay slot 0x80128158, h_exact f04c89c6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80130740(void *a0, u16 *a1) {
    u16 *p = (u16 *)a0;
    func_80146A6C(0x10, a0,
                  (s16)(p[3] + a1[0]),
                  (s16)(p[5] + a1[1]),
                  (s16)(p[7] + a1[2]),
                  0, 0);
}
