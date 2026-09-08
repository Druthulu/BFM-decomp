/* func_80151ECC — shared body (overlay slot 0x80128158, h_exact bc1cdab4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
extern s32 func_80172630(u8 *a0);
void func_80151ECC(struct S80151ECC *a0) {
    func_80149020((s32 *)a0);
    a0->f64 = a0->f64 + (a0->fDE << 6);
    a0->fDE = a0->fDE + 5;
    if (a0->f64 >= 0x1556) {
        a0->fDE = 0x10;
        func_80146CA0(a0);
    }
    func_80172630((u8 *)a0);
}
