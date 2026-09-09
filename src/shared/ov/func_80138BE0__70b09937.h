/* func_80138BE0 — shared body (overlay slot 0x80128158, h_exact 70b09937). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80138BE0(int p)
{
    if (*(unsigned short *)(p + 0xe) != 0) {
        *(unsigned short *)(p + 0xe) -= 1;
    }
    D_8017F87C[*(short *)(p + 4)]();
}
