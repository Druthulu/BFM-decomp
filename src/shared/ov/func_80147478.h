/* func_80147478 — shared body (overlay slot 0x80128158, h_exact 0ae6570e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147514();  // K&R: 0 of 1 args (P37 rung D t4_HD7)
extern void func_80147628(s32 a0);
void func_80147478(s32 a0) {
    if ((*(s32 *)(a0 + 0x44) & 0x40000000) == 0) {
        func_80147514();
        func_80147628(a0);
        *(s32 *)(a0 + 0x44) |= 0x40000000;
    }
}
