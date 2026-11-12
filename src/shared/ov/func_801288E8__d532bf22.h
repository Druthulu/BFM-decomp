/* func_801288E8 — shared body (overlay slot 0x80128158, h_exact d532bf22). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_801288E8(int arg0)
{
    int *p = &guess_g_CdReadList;
    *p = 0x60;
    guess_g_CdReadListDest = &D_800A2E20;
    ((void (*)(int, int, int *, int, int *))guess_RequestResourceLoad)(0, 0, &D_800AF558, D_8018D4F8, p);
}
