/* func_80160BB4 — shared body (overlay slot 0x80128158, h_exact 002c706b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
void func_80160BB4(s32 *a0) {
    s32 *v1;
    a0[0x44 / 4] |= 0x80;
    func_801553A8(a0);
    func_80155440(a0);
    func_80154150((s32)a0, 0x26);
    func_80154A74((s32)a0, 0x1E);
    v1 = (s32 *)a0[0x20 / 4];
    a0[0x234 / 4] = 0;
    *(s16 *)((u8 *)v1 + 0x10) = 0xFE9;
    a0[0x238 / 4] = 0;
    func_80146CA0(a0);
}
