/* func_8016A890 — shared body (overlay slot 0x80128158, h_exact b24f1263). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8016A8FC(s32 a0);
extern void func_80146C3C();
void func_8016A890(s32 arg0)
{
    s16 *p = *(s16 **)((u8 *)arg0 + 0x34);
    if (*(s32 *)((u8 *)arg0 + 0x1C) < 4 && *(u16 *)p == 0x14) {
        ((void (*)(void))func_8016A8FC)();
        *(s32 *)((u8 *)arg0 + 0x1C) = *(s32 *)((u8 *)arg0 + 0x1C) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(arg0);
    }
}
