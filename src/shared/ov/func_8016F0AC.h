/* func_8016F0AC — shared body (overlay slot 0x80128158, h_exact 8eaa5e59). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016F0E4(void);
extern void func_80165770(void);
void func_8016F0AC(void) {
    extern u8 aD80126B58 __asm__("D_80126B58");
    ((void (*)(void *))func_8016F0E4)(&aD80126B58);
    ((void (*)(void *))func_80165770)(&aD80126B58);
}
