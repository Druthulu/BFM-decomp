/* func_8013B6A0 — shared body (overlay slot 0x80128158, h_exact c008cc34). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013B6A0(s32 idx, u16 *src, s32 val)
{
    extern E_3B7AC_8013B7AC D_8018FA00[];

    D_8018FA00[idx].f0 = 1;
    D_8018FA00[idx].unk4 = ((Src_8013B598_8013B598 *)src)->f0;
    D_8018FA00[idx].unk6 = ((Src_8013B598_8013B598 *)src)->f2;
    D_8018FA00[idx].unk8 = ((Src_8013B598_8013B598 *)src)->f4;
    D_8018FA00[idx].unkC = val;
}
