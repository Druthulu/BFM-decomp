/* func_80178840 — shared body (overlay slot 0x80128158, h_exact 9f65edc8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80178840(int param_1) {

    extern int D_80182308;
    extern int D_80182314[];
    register int p __asm__("$16");
    register int s1byte __asm__("$17");
    p = param_1;
    if ((*(unsigned short *)(p + 0x5c) & 1) != 0) {
        s1byte = *(unsigned char *)(p + 0x5e);
        if (s1byte == 0xc) {
            ((void (*)(int))func_80019064)((int)&D_80182308);
        }
        ((void (*)(int, int))func_80131E00)(p, D_80182314[s1byte]);
    }
}
