/* func_80154150 — shared body (overlay slot 0x80128158, h_exact 2ad8c33c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154190(u8 *a0, s32 a1);
void func_80154150(s32 a0, s32 a1)
{
    if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 *)(a0 + 0xB0))[a1]) {
        func_80154190(a0, a1);
    }
}
