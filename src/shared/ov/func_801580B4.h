/* func_801580B4 — shared body (overlay slot 0x80128158, h_exact f8ce1b8a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800D524C[];
extern void guess_SetVertSpeed(s32 *a0, s32 a1);
extern void guess_AddVertSpeed(s32 a0, s32 a1);
extern void guess_ApplyVertSpeed(s32 a0);
extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void guess_ApplyVelocity(s32 *a0);
extern s32 func_80161418(void *a0);
extern void func_80156648(s32 *a0);
extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80146CA0(void *a0);
extern int func_80155FF8(int arg, int a1);
void func_801580B4(s32 a0) {
    s32 reserved[4];
    (void)reserved;
    *(s32 *)(a0 + 0x44) |= 2;
    if ((*(u16 *)(a0 + 0xB8) & 0x4000) != 0) {
        guess_SetVertSpeed((s32 *)a0, 0xFFF40000);
        *(s32 *)(a0 + 0x234) += 1;
    }
    if (*(s32 *)(a0 + 0x234) != 0) {
        guess_AddVertSpeed(a0, 0x10000);
        guess_ApplyVertSpeed(a0);
    }
    func_80147AD4(a0, 0, 0, 0);
    guess_ApplyVelocity((s32 *)a0);
    if (((s32 (*)(void *))func_80161418)((void *)a0) != 0) {
        return;
    }
    if (*(u16 *)(a0 + 0xB8) == 0x8000) {
        func_80156648((s32 *)a0);
        *(s8 *)(a0 + 0x1AA) = 0xF;
        guess_SetAnimScript((s32 *)a0, (s32)D_800D524C);
        func_80147324(0x455);
        func_80146CA0((void *)a0);
    } else {
        func_80155FF8(a0, *(u8 *)(a0 + 0x1AA));
    }
}
