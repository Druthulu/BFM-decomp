/* func_801578C0 — shared body (overlay slot 0x80128158, h_exact 69854285). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801578C0(s32 param_1)
{
    ((void (*)(void))func_80156648)();
    *(u8 *)(param_1 + 0x1AA) = 9;
    guess_SetAnimScript((s32 *)param_1, (s32)&D_800D5128);
    ((void (*)(s32 *, s32))guess_SetTexAnim)((s32 *)param_1, 0x15);
    func_80147324(0xC20);
    ((void (*)(s32 *, s32))guess_SetMoveVector)((s32 *)param_1, (s32)&D_80181564);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(4, (s32 *)param_1, 7, 0);
    ((void (*)(s32, s32 *, s32, s32))func_80146994)(5, (s32 *)param_1, 9, 0);
    ((void (*)(s32 *))func_80146CA0)((s32 *)param_1);
    ((void (*)(s32 *))func_801725A4)((s32 *)param_1);
}
