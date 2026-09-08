/* func_80172C50 — shared body (overlay slot 0x80128158, h_exact d50cc510). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80174684(void *);
extern void func_80172CA0(void*);
void func_80172C50(void *a0) {
    extern s16 D_80126B30;
    *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0;
    func_80174684((void *)func_80172CA0);
}
