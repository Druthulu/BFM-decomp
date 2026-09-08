/* func_8018623C — shared body (overlay slot 0x80128158, h_exact e7ce2fe1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801E8010;
extern void func_8002D4C8(s32 arg0, s32 arg1);
void func_8018623C(u16 arg0, u16 arg1) {
    if (D_801E8010 == 0) {
        func_8002D4C8(arg0 & 0xFFFF, arg1 & 0xFFFF);
    }
}
