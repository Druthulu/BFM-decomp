/* func_801580B4 — shared body (overlay slot 0x80128158, h_exact f8ce1b8a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D524C[];
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_801473EC(s32 *a0);
extern void func_80161418(void *a0);
extern void func_80156648(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);
void func_801580B4(s32 a0) {
    s32 reserved[4];
    (void)reserved;
    *(s32 *)(a0 + 0x44) |= 2;
    if ((*(u16 *)(a0 + 0xB8) & 0x4000) != 0) {
        func_801477E8((s32 *)a0, 0xFFF40000);
        *(s32 *)(a0 + 0x234) += 1;
    }
    if (*(s32 *)(a0 + 0x234) != 0) {
        func_80148038(a0, 0x10000);
        func_80147460(a0);
    }
    func_80147AD4(a0, 0, 0, 0);
    func_801473EC((s32 *)a0);
    {
        register s32 ret __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
        func_80161418((void *)a0);
        if (ret != 0) {
            return;
        }
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_80156648((s32 *)a0);
        *(s8 *)(a0 + 0x1AA) = 0xF;
        func_80154274((s32 *)a0, (s32)D_800D524C);
        func_80147324(0x455);
        func_80146CA0((void *)a0);
    } else {
        func_80155FF8(a0, *(u8 *)(a0 + 0x1AA));
    }
}
