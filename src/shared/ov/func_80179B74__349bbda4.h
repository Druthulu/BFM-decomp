/* func_80179B74 — shared body (overlay slot 0x80128158, h_exact 349bbda4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80179B74(u16 *p) {
    s32 pad[10];
    s16 c;

    (void)&pad;
    c = *p++;
    D_8018F508[D_8018F90C] = c;
    D_8018F90C = (D_8018F90C + 1) & 0x1FF;
    switch (c) {
    case 0:
        break;
    case 1:
    case 5:
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        break;
    case 0x13:
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        break;
    case 2:
    case 3:
    case 4:
    case 6:
    case 0x12:
    case 0x14:
    case 0x1F:
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        break;
    case 0x17:
    case 0x1C:
    case 0x1D:
    case 0x20:
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        { s16 t = *p++; D_8018F508[D_8018F90C] = t; D_8018F90C = (D_8018F90C + 1) & 0x1FF; }
        break;
    case 0x22:
        break;
    }
}
