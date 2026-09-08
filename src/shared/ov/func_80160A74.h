/* func_80160A74 — shared body (overlay slot 0x80128158, h_exact 335b0014). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80160B00();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 D_80078EBF;
void func_80160A74(s32 *a0) {
    if (D_80078EBF == 0x80) {
        func_80160B00();
    } else {
        func_80147078(a0, 0);
        func_80159B70(a0);
    }
}
