/* func_80131CA8 — shared body (overlay slot 0x80128158, h_exact 2c9ae3cd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 aF80131CA8(int a0)
{
    s32 (*fp)(int) = (s32 (*)(int))func_80131CF4(*(s32 *)((u8 *)a0 + 0xBC));
    if (fp != 0) {
        fp(a0);
        return 1;
    }
    return 0;
}
