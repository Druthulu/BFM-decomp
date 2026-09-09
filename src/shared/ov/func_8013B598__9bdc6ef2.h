/* func_8013B598 — shared body (overlay slot 0x80128158, h_exact 9bdc6ef2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013B598(s32 a0, u16 *a1) {
    extern Spr_8013B598_8013B598 D_8018FA00[];

    D_8018FA00[a0].f0 = 1;
    D_8018FA00[a0].f4 = ((Src_8013B598_8013B598 *)a1)->f0;
    D_8018FA00[a0].f6 = ((Src_8013B598_8013B598 *)a1)->f2;
    D_8018FA00[a0].f8 = ((Src_8013B598_8013B598 *)a1)->f4;
    D_8018FA00[a0].fC = 0x100;
}
