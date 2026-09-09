/* func_8012DDA4 — shared body (overlay slot 0x80128158, h_exact 0f69dd9d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8012DDA4()
{
    extern Entry_8012DDA4 * D_8018E69C;
    extern Entry_8012DDA4 * D_8018E698;

    Entry_8012DDA4 *p;
    Entry_8012DDA4 *end = ((Entry_8012DDA4 *)D_80126720);

    while (D_8018E69C != end) {
        p = D_8018E69C;
        if (p->active != 0 && p != D_8018E698) {
            D_8018E69C = p + 1;
            return p;
        }
        D_8018E69C++;
    }
    D_8018E69C = 0;
    return 0;
}
