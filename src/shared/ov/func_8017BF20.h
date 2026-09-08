/* func_8017BF20 — shared body (overlay slot 0x80128158, h_exact 52c88e35). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147060(u8*);
extern void func_80171A1C(u8*);
extern void func_8017BF58(void *a0);
void func_8017BF20(void *a0) {
    ((void (*)(void *))func_80147060)(a0);
    ((s32 (*)(struct S *))func_80171A1C)((struct S *)a0);
    func_8017BF58(a0);
}
