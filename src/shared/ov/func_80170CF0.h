/* func_80170CF0 — shared body (overlay slot 0x80128158, h_exact 763e8b3b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801718AC(void *a0);
void func_80170CF0(void* a0)
{
    extern void *D_8011F738;
    extern s32 D_8011F73C;
    extern s32 D_8011F740;
    s32 v1;
    void *p;
    ((void (*)(s32))D_8011F738)(a0);
    v1 = *(u8 *)(a0 + 0x217);
    if (v1 == 1) {
        goto case_1;
    }
    if (v1 <= 1) {
        goto done;
    }
    if (v1 == 2) {
        goto case_2;
    }
    goto done;
case_1:
    p = (*(void * *)&D_8011F73C);
    goto call;
case_2:
    p = (*(void * *)&D_8011F740);
call:
    func_801718AC(p);
done:
    ;
}
