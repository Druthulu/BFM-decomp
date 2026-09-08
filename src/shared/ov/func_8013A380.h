/* func_8013A380 — shared body (overlay slot 0x80128158, h_exact 175c37a4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_8011DA80[];
extern void func_8013A530();
extern void func_8013A448(void *a0);
extern void func_8013A4C4(struct S8013A4C4 *a0);
void func_8013A380(void) {
    s16 *p;
    s32 i;
    p = (s16 *)D_8011DA80;
    i = 0;
    do {
        if (p != (s16 *)0) {
            switch (*p) {
            case 2:
                ((void (*)(void *))func_8013A530)(p);
                break;
            case 1:
                func_8013A448(p);
                break;
            case 3:
                func_8013A4C4((struct S8013A4C4 *)p);
                break;
            }
        }
        i += 1;
        p += 8;
    } while (i < 2);
}
