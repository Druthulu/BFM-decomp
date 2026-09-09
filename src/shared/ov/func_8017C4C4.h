/* func_8017C4C4 — shared body (overlay slot 0x80128158, h_exact e099fe9e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C4C4(arg0)
void *arg0;
{
    if (func_80148800((s32 *)arg0) & 0x10) {
        *(u8 *)((s32)arg0 + 0x216) = 5;
    } else {
        func_8017C6B8((s32)arg0, *(u8 *)((s32)arg0 + 0x218));
        if (func_80148800((s32 *)arg0) & 0x40) {
            func_80171990((u8 *)arg0);
        }
    }
}
