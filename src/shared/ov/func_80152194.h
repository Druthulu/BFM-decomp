/* func_80152194 — shared body (overlay slot 0x80128158, h_exact 71fdce9c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80147A84(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80146CA0(void *a0);
void func_80152194(s32 *a0) {
    u8 v1;
    func_80149020(a0);
    func_80147A84((s32)a0);
    func_801473EC(a0);
    func_80148038((s32)a0, 0x4000);
    func_80147460((s32)a0);
    v1 = *((u8 *)a0 + 0xDE);
    *((u8 *)a0 + 0xDE) = v1 + 0xFF;
    if (v1 == 0) {
        func_801470B4((s32)a0);
        func_8015369C((s32)a0);
        func_80146CA0(a0);
    }
}
