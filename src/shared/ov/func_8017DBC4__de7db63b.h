/* func_8017DBC4 — shared body (overlay slot 0x80128158, h_exact de7db63b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 func_80171AB0(s32 a0, void *a1);
extern void func_80171A1C(u8*);
void func_8017DBC4(u8 * a0)
{
    extern s32 D_801151D4;
    s16 buf[3];
    s32 *p;
    p = (s32 *)D_801151D4;
    buf[0] = (s16)p[0xF];   /* 0x3C */
    buf[1] = (s16)p[0x10];  /* 0x40 */
    buf[2] = (s16)p[0x11];  /* 0x44 */
    if (func_80171AB0(a0, buf) == 0) {
        ((void (*)(void *))func_80171A1C)((void *)a0);
    }
}
