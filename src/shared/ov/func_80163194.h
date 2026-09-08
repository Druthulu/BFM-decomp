/* func_80163194 — shared body (overlay slot 0x80128158, h_exact a99f39f3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 aD_80127090 __asm__("D_80127090");
extern s32 aD_80127094 __asm__("D_80127094");
extern s32 aD_80127098 __asm__("D_80127098");
extern void func_80162F60(s32 arg0, s32 arg1);
extern void func_80162F80(s32 arg0, s32 arg1);
extern void func_80162FA0(s32 arg0, s32 arg1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_80146D30(s32 a0);
void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4) {
    s32 pad[4];
    s32 out[3];
    (void)pad;
    func_80162F60(a0, a1);
    func_80162F80(a0, a2);
    func_80162FA0(a0, a3);
    func_800484EC(arg4, a0 + 0x24, (s32)out);
    aD_80127090 = out[0];
    aD_80127094 = out[1];
    aD_80127098 = out[2];
    func_80146D30(a0);
}
