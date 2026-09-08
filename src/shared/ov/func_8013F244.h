/* func_8013F244 — shared body (overlay slot 0x80128158, h_exact d65dd63c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_8011511A;
extern u16 D_8011511E;
extern void func_80141C0C(s32);
void func_8013F244(void)
{
    u16 *p = &D_8011511A;
    u16 uVar1;
    s32 iVar2;
    iVar2 = 0;
    if (*p < 3) {
        if ((D_8011511E & 0x2000) != 0) {
            uVar1 = *p + 1;
            iVar2 = 1;
            *p = *p + 1;
            if (2 < uVar1) {
                *p = 0;
            }
        }
        if ((D_8011511E & 0x8000) != 0) {
            D_8011511A = D_8011511A - 1;
            if (2 < D_8011511A) {
                D_8011511A = 2;
            }
            iVar2 = iVar2 + 1;
        }
        if ((D_8011511E & 0x5000) != 0) {
            D_8011511A = 3;
            iVar2 = iVar2 + 1;
        }
    } else {
        iVar2 = 0;
        if ((D_8011511E & 0x5000) == 0)
            goto done;
        *p = 0;
        iVar2 = 1;
    }
done:
    if ((iVar2 << 0x10) != 0) {
        func_80141C0C(2);
    }
    return;
}
