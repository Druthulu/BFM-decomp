/* func_80146750 — shared body (overlay slot 0x80128158, h_exact ee236ac9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern unsigned short D_8011FD10;
extern int D_8011FA1C;
extern unsigned short D_8011F9D6;
extern unsigned short D_8011F9DA;
extern unsigned short D_8011F9DE;
extern int D_8011FA20;
extern int D_8011FA24;
unsigned short *func_80146750(unsigned short *a0)
{
    register int a6 __asm__("6");
    register unsigned short *a7 __asm__("7");
    register int a5 __asm__("5");
    unsigned short *v1;
    unsigned short *v0;
    a6 = 0x8;
    a7 = &D_8011FD10;
    v1 = a7;
    a5 = 0x340;
    do {
        v0 = v1;
        if (*v0 != 0) {
            a7 = (unsigned short *)((char *)a7 + 0x68);
            v1 = (unsigned short *)((char *)v1 + 0x68);
            a6 = a6 + 1;
            a5 = a5 + 0x68;
        } else {
            *(int *)((char *)&D_8011FA1C + a5) = *(int *)((char *)a0 + 0x8);
            *v1 = *a0;
            *(unsigned short *)((char *)&D_8011F9D6 + a5) = *(unsigned short *)((char *)a0 + 0x2);
            *(unsigned short *)((char *)&D_8011F9DA + a5) = *(unsigned short *)((char *)a0 + 0x4);
            *(unsigned short *)((char *)&D_8011F9DE + a5) = *(unsigned short *)((char *)a0 + 0x6);
            *(int *)((char *)&D_8011FA20 + a5) = *(int *)((char *)a0 + 0xC);
            *(int *)((char *)&D_8011FA24 + a5) = *(int *)((char *)a0 + 0x10);
            return a7;
        }
    } while (a6 < 0x14);
    return (unsigned short *)0;
}
