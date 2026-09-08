/* func_801519C8 — shared body (overlay slot 0x80128158, h_exact 74a72f91). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80062BF4[];
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern void func_80019064(void *a0);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern int func_80151204(int arg, int a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);
void func_801519C8(s32 arg0) {
    s16 r;
    u8 v1;
    u8 de;
    s32 v0w;
    func_80019064(&D_80062BF4);
    v1 = *(u8 *)(arg0 + 0xDD);
    if (v1 != 1 && v1 == 0x11) {
        s16 v0 = *(s16 *)(arg0 + 0xF2);
        if (v0 != 0) {
            func_8014ACE8((void *)arg0, 5, (s32)v0 & 0x7FFF);
        }
    } else {
        func_80151204(arg0, *(s16 *)(arg0 + 0xF2));
    }
    v0w = *(s32 *)(arg0 + 0x20);
    r = (s16)func_80012A60(*(s16 *)(v0w + 0x12), *(s16 *)(arg0 + 0xF4));
    if (r >= 0x401) {
        func_80154274((s32 *)arg0, (s32)&D_800D5880);
    } else {
        func_80154274((s32 *)arg0, (s32)&D_800D58AC);
    }
    func_80154A74(arg0, 0x16);
    func_80149020((s32 *)arg0);
    func_80147324(0x451);
    de = *(u8 *)(arg0 + 0xDE);
    if (de == 2 || de == 3 || (de & 0xFF) == 0xB) {
        func_80146CA0((void *)arg0);
    }
    func_80146CA0((void *)arg0);
}
