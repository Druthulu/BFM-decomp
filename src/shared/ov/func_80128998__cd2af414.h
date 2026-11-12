/* func_80128998 — shared body (overlay slot 0x80128158, h_exact cd2af414). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80128998(void)
{
    int *p = &guess_g_CdReadList;
    *p = 13;
    guess_g_CdReadListDest = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))guess_RequestResourceLoad)(0, 0, &D_800AECB0, D_8018D4F8, p);
}
