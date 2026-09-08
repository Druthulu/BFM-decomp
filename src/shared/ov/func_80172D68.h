/* func_80172D68 — shared body (overlay slot 0x80128158, h_exact 214c5e8e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern s32 D_80127508;
extern s32 func_80172DAC();
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80174684(void *);
void func_80172D68(s32 a0)
{
    D_80127508 = func_8014C168(&D_80126B58, a0);
    func_80174684(func_80172DAC);
}
