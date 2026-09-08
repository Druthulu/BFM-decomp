/* func_80181648 — shared body (overlay slot 0x80128158, h_exact de5da31c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32*, s32);
extern void func_80184C90(s32);
extern void func_80181998(void);
void func_80181648(void *a0) {
    extern s32 D_80191B3C;
    extern short D_801C0D40;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_80191B3C);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C0D40);
    func_80184C90((s32)a0);
    func_80181998();
}
