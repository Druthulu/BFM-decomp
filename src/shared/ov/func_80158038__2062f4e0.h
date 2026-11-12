/* func_80158038 — shared body (overlay slot 0x80128158, h_exact 2062f4e0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80158038(void * param)
{
    *(u8 *)(param + 0x1aa) = 0xe;
    guess_SetAnimScript((s32 *)param, (s32)&D_800D51E0);
    guess_SetTexAnim(param, 0x15);
    guess_SetMoveVector((s32 *)param, &D_80181598);
    *(s32 *)(param + 0x234) = 0;
    func_80146994(5, param, 0xc, 0);
    func_80147324(0x455);
    func_80146CA0((void *)param);
}
