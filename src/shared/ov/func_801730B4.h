/* func_801730B4 — shared body (overlay slot 0x80128158, h_exact 4477489a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014706C(void *arg0);
extern void func_801542A4();
extern void func_80171A1C(u8 *a0);
extern void func_801730FC(struct S801730FC *a0);
extern s32 D_80127508;
void func_801730B4(s32 a0) {
    func_8014706C((void *)a0);
    ((void (*)(s32, s32))func_801542A4)(a0, D_80127508);
    ((void (*)(void *))func_80171A1C)((void *)a0);
    ((void (*)(void *))func_801730FC)((void *)a0);
}
