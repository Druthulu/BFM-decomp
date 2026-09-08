/* func_8015C030 — shared body (overlay slot 0x80128158, h_exact 6ff3d32f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80146CA0(void *a0);
void func_8015C030(s32 *a0, s32 a1)
{
    s32 t = *(s16 *)a1 << 7;
    *(s32 *)((s32)a0 + 0x238) = 0x80000;
    *(s32 *)((s32)a0 + 0x234) = t;
    *(s32 *)((s32)a0 + 0x23C) = *(s16 *)(a1 + 4) << 7;
    func_80154150((s32)a0, 0x11);
    func_801553A8(a0);
    func_80146CA0((void *)a0);
}
