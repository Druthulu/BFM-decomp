/* func_80162760 — shared body (overlay slot 0x80128158, h_exact e8f6604d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80162760(void)
{
    int *p;
    int i;

    func_800291C8(0x12, 0);
    i = 0;
    p = D_8018E8C0;
    do {
        int v = *p;
        ((void (*)(int, int))func_80016714)(v, 0x38);
        p = p + 1;
        i = i + 1;
    } while (i < 3);
}
