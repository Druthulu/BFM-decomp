/* func_8016216C — shared body (overlay slot 0x80128158, h_exact 8fca1d46). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016216C(void)
{
    int *p;
    int i;

    func_800291C8(8, 0);
    i = 0;
    p = D_8018E868;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}
