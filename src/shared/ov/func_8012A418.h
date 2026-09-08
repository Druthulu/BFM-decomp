/* func_8012A418 — shared body (overlay slot 0x80128158, h_exact 2de4ec2a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801151D4;
extern struct BigCopy D_80114EE8;
void func_8012A418(void) {
    struct Q16 *src;
    struct Q16 *dst;
    struct Q16 *end;
    src = (struct Q16 *)D_801151D4;
    dst = &D_80114EE8;
    end = src + 10;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(s32 *)dst = *(s32 *)src;
}
