/* func_801746A4 — shared body (overlay slot 0x80128158, h_exact fb33806f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80172710(void);
extern s32 func_80172760(s32 a0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_80174684(void *);
void func_801746A4(void)
{
    ((void (*)(void *, int))func_8016EDEC)(func_80172710, 0x1000000);
    func_80174684(func_80172760);
}
