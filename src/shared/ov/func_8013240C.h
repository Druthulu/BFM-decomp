/* func_8013240C — shared body (overlay slot 0x80128158, h_exact 8dc27dfe). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_8013240C(s32 a0) {
    s32 *node;
    s32 ent;
    s32 v;
    s16 h6;
    ent = *(s32 *)(a0 + 0x0) + (*(s16 *)(a0 + 0x4) << 3);
    node = (s32 *)*(s32 *)(ent + 0);
    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) & 0xFFFF3FFF;
    if ((s32)node == -1) {
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) | 0x4000;
        return;
    }
    if (*(s16 *)(ent + 0x6) < 0) {
        v = 0x1000 - ((*(s16 *)(a0 + 0x6) << 12) / *(s16 *)(ent + 0x4));
    } else {
        v = (*(s16 *)(a0 + 0x6) << 12) / *(s16 *)(ent + 0x4);
    }
    func_801325B8(*(s32 *)(a0 + 0x8), node[0], node[1], node[2], v);
    h6 = *(s16 *)(ent + 0x6);
    if (h6 < 0) {
        *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) - h6;
    } else {
        *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + h6;
    }
    if (*(s16 *)(a0 + 0x6) < *(s16 *)(ent + 0x4)) {
        return;
    }
    *(s16 *)(a0 + 0x6) = 0;
    *(s16 *)(a0 + 0x4) = *(u16 *)(a0 + 0x4) + 1;
    {
        s32 *p = (s32 *)((*(s16 *)(a0 + 0x4) << 3) + *(s32 *)(a0 + 0x0));
        s32 w = p[0];
        s32 c;
        if (w != -1) {
            if (w != 0) {
                return;
            }
            *(s16 *)(a0 + 0x4) = 0;
            c = *(s32 *)(a0 + 0xC) | 0x8000;
        } else {
            c = *(s32 *)(a0 + 0xC) | 0x4000;
        }
        *(s32 *)(a0 + 0xC) = c;
    }
}
