/* func_80172D68 — shared body (overlay slot 0x80128158, h_exact 214c5e8e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_g_PlayerActor; // Names ledger: config/names.tsv guess_g_PlayerActor
extern s32 D_80127508;
extern s32 func_80172DAC(void *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80174684(void *);
void func_80172D68(s32 a0)
{
    D_80127508 = func_8014C168(&guess_g_PlayerActor, a0);
    func_80174684(func_80172DAC);
}
