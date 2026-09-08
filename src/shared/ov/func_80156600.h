/* func_80156600 — shared body (overlay slot 0x80128158, h_exact f3a9a8b6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern S8 D_80126AF0[];
extern s32 D_801151E0[];
s32 func_80156600(void* _arg0)
{
    u32 i = 0;
    s8 *ptr = &((s8 *)D_80126AF0)[0];
    do {
        if (D_801151E0[i] & 1) {
            return ptr;
        }
        ptr += 8;
        i++;
    } while (i < 3);
    return (s8 *)0;
}
