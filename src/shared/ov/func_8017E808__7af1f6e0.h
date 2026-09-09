/* func_8017E808 — shared body (overlay slot 0x80128158, h_exact 7af1f6e0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017E808(a0)
u8 *a0;
{
    s32 v0 = *(s32 *)(a0 + 0x200) - 1;
    *(s32 *)(a0 + 0x200) = v0;
    if (v0 == -1) {
        *(u16 *)(a0 + 0xB8) = 0;
        *(s32 *)(a0 + 0x200) = 0x10;
        func_80171990(a0);
    }
}
