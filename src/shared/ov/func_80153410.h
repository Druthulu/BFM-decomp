/* func_80153410 — shared body (overlay slot 0x80128158, h_exact 61c07dc9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80146CA0(void *a0);
void func_80153410(s32 *a0) {
    func_80149020(a0);
    func_80148038((s32)a0, 0x18000);
    func_80147460((s32)a0);
    if (*(s16 *)((u8 *)a0 + 0xA) < 0x201) {
        u8 v1 = *(u8 *)((u8 *)a0 + 0xDE);
        *(u8 *)((u8 *)a0 + 0xDE) = v1 + 0xFF;
        if (v1 != 0) {
            return;
        }
    }
    func_801470B4((s32)a0);
    func_8015369C((s32)a0);
    func_80146CA0(a0);
}
