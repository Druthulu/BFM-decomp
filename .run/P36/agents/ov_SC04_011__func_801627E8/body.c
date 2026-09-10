void func_801627E8(void)
{

    extern s32 D_8011F750;                 /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_80192FD0[])(u8 *);     /* word-stride table of dispatch fn pointers; each takes the ctl block */
    u8 *p = (u8 *)&D_8011F750;
    s32 idx;

    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_80192FD0[idx](p);
    }
}
