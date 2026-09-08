/* func_80151E78 — shared body (overlay slot 0x80128158, h_exact a12d8765). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s32 func_80172630(u8 *a0);
void func_80151E78(s32 *a0) {
    u8 *p = (u8 *)a0 + 0xDE;
    u8 v;
    func_80149020(a0);
    v = *p;
    *p = v + 0xFF;
    if (v == 0) {
        *p = 0x10;
        func_80146CA0(a0);
    }
    func_80172630((u8 *)a0);
}
