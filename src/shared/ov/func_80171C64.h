/* func_80171C64 — shared body (overlay slot 0x80128158, h_exact e8f717a7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171EC8(s32 a0);
extern void func_80146D90(s32 a0);
s32 func_80171C64(s32 param_1, s32 param_2)
{
    s32 s = param_1;
    s32 d = param_2;
    u8 v;
    ((void (*)(void))func_80171EC8)();
    v = *(u8 *)(s + 0x20C);
    *(u8 *)(s + 0x20C) = v + 1;
    if ((v & 0xFF) == (d & 0xFF)) {
        func_80146D90(s);
        return 1;
    }
    return 0;
}
