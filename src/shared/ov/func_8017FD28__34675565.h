/* func_8017FD28 — shared body (overlay slot 0x80128158, h_exact 34675565). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern void func_8012E88C(s32);
extern void func_8012A828(s32 *a0, s32 a1);
extern short D_801B99A8;
void func_8017FD28(s32 arg0) {
    s32 s0 = arg0;
    s32 result = func_801789AC(arg0);
    if (result != 0) {
        ((void (*)(s32))func_80178D18)((s32)s0);
        *(short *)((char *)s0 + 0x2) = 5;
        *(short *)((char *)s0 + 0x34) = 1;
        func_8012E88C((s32)s0);
        func_8012A828((s32 *)s0, (s32)&D_801B99A8);
    }
}
