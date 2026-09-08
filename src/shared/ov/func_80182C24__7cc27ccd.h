/* func_80182C24 — shared body (overlay slot 0x80128158, h_exact 7cc27ccd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32*, s32);
extern void func_80184C90(s32);
extern void func_80184ED4(s32, s32, s32, s32);
void func_80182C24(void *arg0) {
    extern short D_80191F1C;
    extern short D_801B99A8;
    extern short D_801B670C;
    *(short *)((char *)arg0 + 0x2) = 6;
    func_8012E8E0((s32)arg0, (s32)&D_80191F1C);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B99A8);
    func_80184C90((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80184ED4((s32)arg0, (s32)&D_801B670C, 1, 0x60);
}
