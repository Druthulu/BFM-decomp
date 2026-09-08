/* func_80157F64 — shared body (overlay slot 0x80128158, h_exact 4aed1621). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149CB4(void);
s32 func_80157F64(s32 *a0) {
    if ((func_80029178(0x87) & 0xFF) != 0) {
        if ((func_80148800(a0) & 0x80) != 0) {
            ((void (*)(s32 *, s32))func_80149CB4)(a0, 5);
            return 1;
        }
    }
    return 0;
}
