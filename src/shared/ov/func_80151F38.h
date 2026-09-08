/* func_80151F38 — shared body (overlay slot 0x80128158, h_exact 7627ebff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80151FB4(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);
void func_80151F38(s32 *a0) {
    func_80149020(a0);
    *(s16 *)((char *)a0 + 0x64) = *(u16 *)((char *)a0 + 0x64) - (*(u8 *)((char *)a0 + 0xDE) << 6);
    *(u8 *)((char *)a0 + 0xDE) = *(u8 *)((char *)a0 + 0xDE) + 8;
    if (*(s16 *)((char *)a0 + 0x64) < 0x1000) {
        func_80151FB4((s32)a0);
        func_80159B3C(a0);
        func_80165718((s32)a0);
    } else {
        func_80172630((u8 *)a0);
    }
}
