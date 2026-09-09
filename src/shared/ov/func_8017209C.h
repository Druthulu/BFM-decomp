/* func_8017209C — shared body (overlay slot 0x80128158, h_exact 90614cf0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172170(s32 a0, s32 a1);
s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 ret;
    s32 ang;    /* $v1 */
    s32 a3p;   /* $s3 = arg3 */
    register s32 a2p  __asm__("$20");   /* $s4 = arg2 */  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B headers1)
    a3p = arg3;
    a2p = arg2;
    ret = func_8017248C((s32)arg0, (s32)arg1);
    if (ret != 0) {
        func_80146D90((s32)arg0);
        return ret;
    }
    ang = (ratan2((s32)*(s16 *)((u8 *)arg1 + 0) - (s32)*(s16 *)((u8 *)arg0 + 6),
                         (s32)*(s16 *)((u8 *)arg1 + 4) - (s32)*(s16 *)((u8 *)arg0 + 0xE))
           + 0x800) & 0xFFF;
    if (a3p != 0) {
        ang = (s16)func_80012DBC((s32)*(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12),
                                 ang, (s16)a3p, 1);
    }
    *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) = ang;
    func_80172170((s32)arg0, a2p & 0xFF);
    return 0;
}
