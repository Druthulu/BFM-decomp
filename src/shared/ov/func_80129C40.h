/* func_80129C40 — shared body (overlay slot 0x80128158, h_exact a2a5c189). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern BigCopy D_80126DB8;
extern u8 guess_g_MainCamera[]; // Names ledger: config/names.tsv guess_g_MainCamera
extern BigCopy D_80114EE8;
extern s32 D_80126E60[];
extern s8 D_801150D6;
extern s8 D_801152C0;
extern u8 D_80127504;
extern void guess_ZeroMemory(void *a0, s32 a1);
extern void func_800144D4(void);
void func_80129C40(s32 _arg0)
{
    guess_ZeroMemory(((u8 *)&D_80126DB8), 0xA4);
    guess_ZeroMemory(guess_g_MainCamera, 0xA4);
    guess_ZeroMemory(((u8 *)&D_80114EE8), 0xA4);
    guess_ZeroMemory(((u8 *)&D_80114EE8) + 0xA4, 0xA4);
    guess_ZeroMemory(((u8 *)&D_80114EE8) + 0x148, 0xA4);
    guess_ZeroMemory(((u8 *)D_80126E60), 0xA4);
    guess_ZeroMemory(((u8 *)D_80126E60) + 0xA4, 0xA4);
    guess_ZeroMemory(((u8 *)D_80126E60) + 0x148, 0xA4);
    D_801150D6 = 0;
    D_801152C0 = 0;
    (*(s8 *)&D_80127504) = 0;
    func_800144D4();
}
