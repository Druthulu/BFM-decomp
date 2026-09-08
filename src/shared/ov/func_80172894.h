/* func_80172894 — shared body (overlay slot 0x80128158, h_exact 5b7bc6de). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80174684(void *);
extern s16 D_80126B30;
extern s32 func_801728E4();
void func_80172894(void *a0) {
    *(struct S8_80172894 *)&D_80126B30 = *(struct S8_80172894 *)a0;
    func_80174684((void *)func_801728E4);
}
