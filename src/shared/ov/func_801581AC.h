/* func_801581AC — shared body (overlay slot 0x80128158, h_exact 94a631a2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801473EC(s32 *a0);
extern void func_80161418(void *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern int func_80155FF8(int arg, int a1);
void func_801581AC(s32 a0) {
    s32 reserved[4];
    (void)reserved;
    *(s32 *)(a0 + 0x44) |= 2;
    func_80148038(a0, 0x10000);
    func_80147460(a0);
    func_80147AD4(a0, 0, 0, 0);
    func_801473EC((s32 *)a0);
    {
        register s32 ret __asm__("$2");
        func_80161418((void *)a0);
        __asm__ __volatile__("" : "=r"(ret));
        if (ret != 0) {
            return;
        }
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_801599A4((void *)a0);
        func_80159B3C((void *)a0);
    } else {
        func_80155FF8(a0, *(u8 *)(a0 + 0x1AA));
    }
}
