/* func_8014C43C — shared body (overlay slot 0x80128158, h_exact e7c6d050). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4)
{
    u16 v0;
    v0 = func_80156370((u16)a2);
    func_8014C4AC(a1, a2, v0 & 0xFFFF, a3, (s16)a4);
}
