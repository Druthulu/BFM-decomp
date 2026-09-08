/* func_8018042C — shared body (overlay slot 0x80128158, h_exact 52a02918). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32*, s32);
extern void func_80184C90(s32 a0);
extern void func_80184ED4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 D_801B9DF8;
extern short D_801B65B8;
void func_8018042C(s32 a0) {
    *(u16 *)(a0 + 2) = 6;
    func_8012E88C(a0);
    ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B9DF8);
    func_80184C90(a0);
    func_80184ED4(a0, (s32)&(*(s32 *)&D_801B65B8), 1, 0x60);
}
