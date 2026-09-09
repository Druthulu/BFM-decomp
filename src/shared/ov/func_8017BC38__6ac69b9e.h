/* func_8017BC38 — shared body (overlay slot 0x80128158, h_exact 6ac69b9e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BC38(int param_1)
{
    int i;
    void (**p)(int);

    i = 0;
    p = D_8018F95C;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}
