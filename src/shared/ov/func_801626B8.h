/* func_801626B8 — shared body (overlay slot 0x80128158, h_exact c9b29013). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
int func_801626B8(void) {
    short local;
    int lo;
    local = func_800291DC(0x12) & 0x7FFF;
    local = func_800D0E30(&local);
    lo = *(unsigned char *)&local;
    return (short)(*((unsigned char *)&local + 1) * 100 + lo);
}
