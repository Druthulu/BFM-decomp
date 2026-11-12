/* func_8016706C — shared body (overlay slot 0x80128158, h_exact e0963a4b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_FreeSmallObject();  // K&R: ? of 1 args (P37 rung D t4_HD7)
void func_8016706C(s32 param_1)
{
    extern s32 guess_g_SmallObjectPool; // Names ledger: config/names.tsv guess_g_SmallObjectPool
    unsigned short *puVar1;
    short iVar2;
    iVar2 = 0;
    puVar1 = ((unsigned short *)&guess_g_SmallObjectPool);
    do {
        if ((unsigned int)*puVar1 == ((short)param_1)) {
            ((void(*)(unsigned short *))guess_FreeSmallObject)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
}
