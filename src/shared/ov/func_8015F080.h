/* func_8015F080 — shared body (overlay slot 0x80128158, h_exact 5fbc6a60). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80149048(s32 *a0);
extern void func_80156648(s32 *a0);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
void func_8015F080(s32 a0) {
    func_80154150(a0, 0x17);
    func_80154A74(a0, 0x15);
    func_80146994(0x5, a0, 0x7, 0);
    *(s32 *)(a0 + 0x238) = -1;
    *(s32 *)(a0 + 0x234) = 0;
    *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & -2;
    func_80149048((s32 *)a0);
    func_80156648((s32 *)a0);
    *(s8 *)(a0 + 0x1AA) = 8;
    func_80149020((s32 *)a0);
    *(s16 *)(a0 + 0xF6) = 0x19EB;
    func_80146CA0((void *)a0);
}
