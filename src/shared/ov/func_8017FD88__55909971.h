/* func_8017FD88 — shared body (overlay slot 0x80128158, h_exact 55909971). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern void func_8012E88C(s32);
extern void func_8012A828(s32 *a0, s32 a1);
void func_8017FD88(void *arg0) {
    extern short D_801B99A8;
    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 0xB;
        *(short *)((char *)arg0 + 0x34) = 0;
        func_8012E88C((s32)arg0);
        func_8012A828((s32 *)arg0, (s32)&D_801B99A8);
    }
}
