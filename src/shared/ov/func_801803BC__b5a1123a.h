/* func_801803BC — shared body (overlay slot 0x80128158, h_exact b5a1123a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012E88C(s32);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80184C90(s32);
extern void func_80184ED4(s32, s32, s32, s32);
extern void func_80185FB8(s32, s32, s32);
extern s32 D_801B9DF8;
extern short D_801B65C8;
void func_801803BC(void *arg0) {
    s32 s0 = (s32)arg0;
    *(short *)((char *)s0 + 0x2) = 3;
    func_8012E88C(s0);
    func_8012A828((s32 *)s0, (s32)&(*(short *)&D_801B9DF8));
    func_80184C90(s0);
    func_80184ED4(s0, (s32)&D_801B65C8, 0, 0x40);
    func_80185FB8(s0, 0xC, 0x1);
}
