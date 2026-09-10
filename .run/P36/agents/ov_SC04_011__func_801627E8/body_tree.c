void func_801627E8(void)
{

    extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
    extern void (*D_80192FD0[])(void);   /* word-stride table of dispatch fn pointers */
    register u8 *p __asm__("$4") = (u8 *)&D_8011F750;  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 idx;

    __asm__ __volatile__("" : "=r"(p) : "0"(p));   /* materialize &D_8011F750 into $a0 (defeat %lo-fold of the lbu) */  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
    idx = *p;
    if (idx != 0) {
        idx = idx - 1;
        D_80192FD0[idx]();
    }
}
