/* func_80170DE0 — shared body (overlay slot 0x80128158, h_exact 9b32f76e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern s32 func_80029178(s32 arg);
extern void func_801718AC(void *a0);
void func_80170DE0(u8 * _arg0)
{
    s32 arg;
    if (((u8 (*)(s32))func_80029178)(D_8011F738)) {
        arg = D_8011F740;
    } else {
        arg = D_8011F73C;
    }
    ((void (*)(s32))func_801718AC)(arg);
}
