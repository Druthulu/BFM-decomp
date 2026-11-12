/* func_8017D6CC — shared body (overlay slot 0x80128158, h_exact 86843ed5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_AddVelocityToPos_4(s32 a0);
extern s32 guess_FreeSmallObject(u8 *a0);
extern void func_8017D728(void *a0);
void func_8017D6CC(void *a0)
{
    s32 t;
    t = *(s32 *)((s32)a0 + 0x1C);
    *(s32 *)((s32)a0 + 0x1C) = t + 1;
    if (t < 0xA) {
        ((void (*)(void))guess_AddVelocityToPos_4)();
        func_8017D728(a0);
    } else {
        ((void (*)(void *))guess_FreeSmallObject)(a0);
    }
}
