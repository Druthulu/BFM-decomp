/* func_8012D4B4 — shared body (overlay slot 0x80128158, h_exact c5e872b0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 AddPrim(s32, void *);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void SetLineF2(void *);
extern void *func_80010A08(s32);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern s32 D_800A651C;
extern u8 D_800AF648;
extern s16 D_800B9A02;
void func_8012D4B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10[2];
    s32 sp18[2];
    s32 sp20;
    s32 sp24;
    s32 temp_v0_2;
    void *temp_v0;
    func_8012F214(arg0, arg1, (s32)sp10);
    func_8012F214(arg0, arg2, (s32)sp18);
    temp_v0 = func_80010A08(0x10);
    (*(s32 *)((s8 *)(temp_v0) + (4))) = arg3;
    SetLineF2(temp_v0);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    temp_v0_2 = RotTransPers((s32)sp10, temp_v0 + 8, &sp20, &sp24);
    if ((temp_v0_2 > 0) && (sp24 >= 0) &&
        (RotTransPers((s32)sp18, temp_v0 + 0xC, &sp20, &sp24) > 0) && (sp24 >= 0)) {
        AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + (temp_v0_2 * 4), temp_v0);
    }
}
