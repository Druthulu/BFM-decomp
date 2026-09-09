/* func_8017C5D8 — shared body (overlay slot 0x80128158, h_exact d1376796). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017C5D8(arg0)
void *arg0;
{
    if (func_80171A88((s32)arg0)) {
        if (*(s16 *)((u8 *)arg0 + 0x20C) == 0x60) {
            *(u8 *)((u8 *)arg0 + 0x216) = 4;
        } else {
            *(u16 *)((u8 *)arg0 + 0x20E) = 0;
            *(u8 *)((u8 *)arg0 + 0x216) = 1;
        }
    }
}
