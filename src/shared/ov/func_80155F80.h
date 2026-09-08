/* func_80155F80 — shared body (overlay slot 0x80128158, h_exact 31791b27). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154A74(s32 a0, s32 a1);
s32 func_80155F80(s32 a0)
{
    *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2;
    func_80154A74(a0, 0x11);
}
