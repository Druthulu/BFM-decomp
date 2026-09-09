/* func_8017DE8C — shared body (overlay slot 0x80128158, h_text 56bde5a7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017DE8C(u8 *a0) {
    u16 flags = *(u16 *)(a0 + 0xB8);

    if (flags & 0x4000) {
        func_80147324(0x445);
        return;
    }
    if (!(flags & 0x8000)) {
        return;
    }
    func_80147060(a0);
    switch ((s16)(*(u16 *)&D_80126B3A - 2)) {
    case 0:
        func_80029124(0x16, 1);
        func_80029514(0x85);
        break;
    case 1:
        func_80029124(0x17, 1);
        break;
    case 2:
        func_80029124(0x18, 1);
        break;
    case 3:
        func_80029124(0x19, 1);
        break;
    case 4:
        func_80029124(0x1A, 1);
        break;
    }
    (*(s32 *)&D_8011F9C8) = 1;
    func_80174650((s32)a0);
    func_80171A1C(a0);
}
