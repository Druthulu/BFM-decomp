/* func_8015773C — shared body (overlay slot 0x80128158, h_exact 75da6917). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801553C0(s32 a0);
extern void func_801553A8(s32 *a0);
s32 func_8015773C(u8 * arg0)
{
    *(s32 *)((u8 *)arg0 + 0x44) = *(s32 *)((u8 *)arg0 + 0x44) & ~2;
    func_80154A74((s32)arg0, 0x11);
    func_801553C0((s32)arg0);
    func_801553A8(arg0);
}
