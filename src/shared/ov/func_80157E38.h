/* func_80157E38 — shared body (overlay slot 0x80128158, h_exact a5907402). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SetAnimScript(s32 *a0, s32 a1);
extern void guess_SetTexAnim(s32 a0, s32 a1);
extern s32 guess_SpawnSmallObjectAtOrigin(s32 a0, s32 a1, s32 a2, s32 a3);
extern void guess_PlaySoundUnlessSkipped(s32 a0);
extern void guess_NextStep(void *a0);
extern u8 D_800D4F14[];
void func_80157E38(void * a0)
{
    *((u8 *)a0 + 0x1AA) = 0xD;
    guess_SetAnimScript(a0, (s32)D_800D4F14);
    guess_SetTexAnim((s32)a0, 0x15);
    guess_SpawnSmallObjectAtOrigin(5, (s32)a0, 0, 0);
    guess_PlaySoundUnlessSkipped(0x455);
    *(s16 *)((u8 *)a0 + 0x244) = 0;
    guess_NextStep((void *)a0);
}
