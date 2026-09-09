/* func_8017EA78 — shared body (overlay slot 0x80128158, h_exact afb31368). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017EA78(a0)
u8 *a0;
{
    if (func_8017EC2C(a0) == 0x12C) {
        if (*(u16 *)(a0 + 0xB8) & 0x8000) {
            *(u16 *)(a0 + 0xB8) = *(u16 *)(a0 + 0xBA);
            func_80171990(a0);
        }
    }
}
