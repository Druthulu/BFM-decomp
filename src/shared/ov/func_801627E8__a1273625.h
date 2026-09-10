/* func_801627E8 — shared body (overlay slot 0x80128158, h_exact a1273625). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801627E8(void)
{

    extern s32 D_8011F750;                 /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_80181E1C[])(u8 *);     /* word-stride table of dispatch fn pointers; each takes the ctl block */
    u8 *p = (u8 *)&D_8011F750;
    s32 idx;

    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_80181E1C[idx](p);
    }
}
