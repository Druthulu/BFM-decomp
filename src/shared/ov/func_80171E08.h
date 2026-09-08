/* func_80171E08 — shared body (overlay slot 0x80128158, h_exact 363bc17b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8017248C(s32 a0, s32 a1);
extern void func_80146D90(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171EC8(s32 a0);
s32 func_80171E08(s32 arg0, s32 arg1, s32 arg2) {
    s32 r;
    s32 a1v;
    r = func_8017248C(arg0, arg1);
    if (r != 0) {
        func_80146D90(arg0);
        return r;
    }
    a1v = (ratan2((s32)*(s16 *)(arg1 + 0x0) - (s32)*(s16 *)(arg0 + 0x6),
                  (s32)*(s16 *)(arg1 + 0x4) - (s32)*(s16 *)(arg0 + 0xE)) + 0x800) & 0xFFF;
    if (arg2 != 0) {
        a1v = (s16)func_80012DBC((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12),
                                 a1v, (s32)(s16)arg2, 1);
    }
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = a1v;
    func_80171EC8(arg0);
    return 0;
}
