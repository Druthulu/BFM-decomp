/* func_8014C118 — shared body (overlay slot 0x80128158, h_exact d3691ae4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_801202A0[];
s32 func_8014C118(void * a0, s32 a1, s32 a2)
{
    Entry8014C118 *p;
    s32 i;
    i = 0;
    a2 = (s16)a2;
    p = (Entry8014C118 *)D_801202A0;
    do {
        if (p->unk0 == a1) {
            if (p->unk70 == a2) {
                return (s32)p;
            }
        }
        i++;
        p++;
    } while ((u32)i < 0x60);
    return 0;
}
