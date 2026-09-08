/* func_8013F1BC — shared body (overlay slot 0x80128158, h_exact 4bfd5f8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_800D2624(void);
extern short D_800B9A02;
extern unsigned short D_80115114;
extern unsigned short D_80115112;
extern unsigned short D_80115118;
void func_8013F1BC(void) {
    unsigned short *p = &D_80115118;
    if (*p != 0) {
        *p -= 0x10;
        __asm__ __volatile__("" ::: "memory");
        if (*p != 0) {
            return;
        }
    }
    if (D_80115114 == ((unsigned short)D_800B9A02 ^ 1)) {
        func_800D2624();
    } else {
        D_80115112 += 1;
    }
}
