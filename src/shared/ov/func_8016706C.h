/* func_8016706C — shared body (overlay slot 0x80128158, h_exact e0963a4b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80146C3C(void);
void func_8016706C(s32 param_1)
{
    extern s32 D_8011D030;
    unsigned short *puVar1;
    short iVar2;
    iVar2 = 0;
    puVar1 = ((unsigned short *)&D_8011D030);
    do {
        if ((unsigned int)*puVar1 == ((short)param_1)) {
            ((void(*)(unsigned short *))func_80146C3C)(puVar1);
        }
        iVar2 = iVar2 + 1;
        puVar1 = puVar1 + 0x2c;
    } while (iVar2 < 0x1e);
}
