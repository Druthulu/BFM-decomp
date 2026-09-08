/* func_8017849C — shared body (overlay slot 0x80128158, h_exact f9ea4ce3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801787D4(void);
extern void func_8012A908(void);
extern void func_8017869C(s32 a0);
extern void func_80130D0C(s32 a0);
extern void func_8013E370(void);
extern u8 D_801202A0[];
extern u16 D_801270C0;
extern s32 D_8011DB08;
void func_8017849C(void) {
    register u8 *p __asm__("$17");   /* $s1 base */
    register u8 *q __asm__("$16");   /* $s0 = base + 0x54 */
    register s32 i __asm__("$18");   /* $s2 counter */
    p = (u8 *)D_801202A0;
    func_801787D4();
    i = 0;
    func_8012A908();
    q = p + 0x54;
    do {
        if (*(u16 *)p != 0 &&
            (*(s16 *)&D_801270C0 == 1 || (*(u16 *)(q + 0x1E) & 0x1000) != 0)) {
            register s32 tbl __asm__("$3"); register s32 c6c __asm__("$2");
            func_8017869C((s32)p);
            *(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);
            if (c6c != 0 && *(u8 *)(q + 0x6D) != 0) {
                func_80130D0C((s32)p);
            } else {
                (*(void (**)(s32))(tbl + *(u16 *)p * 4))((s32)p);
            }
            if (*(s32 *)(q - 0x34) != 0) {
                *(s16 *)(*(s32 *)(q - 0x34) + 8) =
                    *(u16 *)(q - 0x4E) + *(u16 *)(q - 0x4);
                *(s16 *)(*(s32 *)(q - 0x34) + 10) =
                    *(u16 *)(q - 0x4A) + *(u16 *)(q - 0x2);
                *(s16 *)(*(s32 *)(q - 0x34) + 0xC) =
                    *(u16 *)(q - 0x46) + *(u16 *)q;
            }
        }
        i++;
        q += 0x10C;
        p += 0x10C;
    } while (i < 0x60);
    if (*(s16 *)&D_801270C0 == 1) {
        func_8013E370();
    }
}
