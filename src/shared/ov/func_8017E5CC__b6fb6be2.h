/* func_8017E5CC — shared body (overlay slot 0x80128158, h_exact b6fb6be2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80184C90(s32);
extern short D_80191074;
extern short D_801B99A8;
void func_8017E5CC(void *arg0) {
    *(short *)((char *)arg0 + 0x2) = 5;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_80191074);
    func_8012E88C((s32)arg0);
    func_8012A828((s32 *)arg0, (s32)&D_801B99A8);
    func_80184C90((s32)arg0);
}
