/* func_80145B24 — shared body (overlay slot 0x80128158, h_exact c2f43c61). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_GetStoryProgress(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void guess_SetGameFlag(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
extern u8 guess_g_RenderWork[];
extern u8 D_80078EC0;
extern s32 guess_g_PlayerActor;
void func_80145B24(void)
{
    s32 iVar1;
    s32 uVar2;
    u8 *p;
    p = &guess_g_RenderWork;
    iVar1 = guess_GetStoryProgress();
    uVar2 = func_800291DC(8);
    if ((uVar2 & 0x8000) != 0) {
        func_800291C8(8, 0);
        func_80162120();
    }
    if (iVar1 >= 0x6A4) {
        guess_SetGameFlag(0x1A, 0);
        guess_SetGameFlag(0x8E, 0);
        guess_SetGameFlag(0x143, 0);
        if ((D_80078EC0 & 0x7F) != 0) {
            D_80078EC0 = 1;
        }
        func_80165A50((s32)&guess_g_PlayerActor);
        func_80029514(0x4B0);
    }
    *(s16 *)(p + 0xA3DA) = 0x3000;
}
