/* func_8012C2D0 — shared body (overlay slot 0x80128158, h_exact 4516d044). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80120194[];
extern u8 D_801202A0[];
s32 func_8012C2D0(void)
{
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    __asm__ __volatile__("" : "=r"(it) : "0"(it));
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    __asm__ __volatile__("" : "=r"(it) : "0"(it));
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    return 0;
}
