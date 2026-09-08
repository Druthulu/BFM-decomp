/* func_801815DC — shared body (overlay slot 0x80128158, h_exact e8e5dd81). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_801B99A8;
extern u8 D_801B662C[];
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80184C90(s32 a0);
extern void func_80184ED4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80181998(void);
void func_801815DC(void *arg0) {
    s32 s0;
    s0 = (s32)arg0;
    *(s16*)((char *)arg0 + 0x2) = 2;
    func_8012E88C((s32)arg0);
    __asm__("" ::: "memory");
    func_8012A828((s32*)s0, (s32)&D_801B99A8);
    func_80184C90((s32)s0);
    *(s16*)((char *)arg0 + 0x34) = 0;
    func_80184ED4((s32)s0, (s32)D_801B662C, 0, 0x80);
    func_80181998();
}
