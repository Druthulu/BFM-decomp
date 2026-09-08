/* func_80151AE4 — shared body (overlay slot 0x80128158, h_exact d502e5b6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80151C54(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_8014E934(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8015BDD0(s32 *a0);
extern void func_80165718(s32 a0);
extern u8 D_800D46E4[];
extern M2C_UNK D_800D5880;
void func_80151AE4(s32 arg0)
{
    func_80149020(arg0);
    if (*(u16 *)((s32)arg0 + 0xB8) == 0x8000) {
        func_80151C54(arg0);
        func_80159B3C(arg0);
        if (*(s32 *)((s32)arg0 + 0xB4) == (s32)&D_800D5880) {
            ((void (*)(s32, s32, s32))func_801542DC)(arg0, (s32)D_800D46E4, 0xE);
        }
    } else {
        func_8014E934(arg0);
        if (((s32 (*)(s32))func_8014F3E8)(arg0) != 0) {
            return;
        }
        if (((s32 (*)(s32))func_8014CC28)(arg0) != 0) {
            return;
        }
        func_80151C54(arg0);
        func_8015BDD0(arg0);
    }
    func_80165718(arg0);
}
