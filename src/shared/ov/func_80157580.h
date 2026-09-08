/* func_80157580 — shared body (overlay slot 0x80128158, h_exact d1046537). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014CC28(s32 a0);      /* defined  */
extern s32 func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
void func_80157580(s32 arg0) {
    s32 temp_s1;
    /* return-cast: canonical func_8014CC28 is void, but its $v0 is used here */
    temp_s1 = ((s32 (*)(s32))func_8014CC28)(arg0);
    /* return-cast: canonical func_8014F3E8 is void, but its $v0 is tested here */
    if ((((s32 (*)(s32))func_8014F3E8)(arg0) == 0) && (temp_s1 == 0)) {
        func_8015BDD0((s32 *)arg0);
        return;
    }
    func_801575E4((void *)arg0);
}
