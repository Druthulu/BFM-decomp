/* func_80153C44 — shared body (overlay slot 0x80128158, h_exact a4684ceb). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80153C74(s16 a0, s16 a1);
extern s16 D_8011DB18;
void func_80153C44(int a0, int a1, s16 a2)
{
    ((void (*)(int, int))func_80153C74)(a0, a1);
    D_8011DB18 = a2;
}
