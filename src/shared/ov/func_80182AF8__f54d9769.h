/* func_80182AF8 — shared body (overlay slot 0x80128158, h_exact f54d9769). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012A828(s32 *a0, s32 a1);
void func_80182AF8(void *a0) {
    extern s16 D_801E7020;
    extern s16 D_801E7022;
    extern s16 aD801B9AA8_80182AF8 __asm__("D_801B9AA8");
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(u16 *)((char *)a0 + 0x2) = D_801E7020;
        *(u16 *)((char *)a0 + 0x34) = D_801E7022;
        func_8012A828((s32 *)a0, (s32)&aD801B9AA8_80182AF8);
    }
}
