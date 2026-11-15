/* func_80167AE0 — shared body (overlay slot 0x80128158, h_exact 3e4eb49d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80167AE0(s32 param_1, s32 param_2, s32 param_3) {
    extern void guess_SetSegmentMatrixFacingCamera(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
    extern void guess_AddPolyG4(void *a0, void *a1);
    extern u8 D_80181BAC;
    extern u8 D_80181BC0[];

    struct Fr_80167AE0 fr;
    u8 *p;
    u16 i;
    u16 t;
    s32 flags;

    guess_SetSegmentMatrixFacingCamera(param_1, ((s16 *)param_2), ((s16 *)param_3), fr.matrix);

    fr.v[3].vz = 0;
    fr.v[2].vz = 0;
    fr.v[0].vz = 0;
    fr.v[1].vz = 0;
    fr.v[1].vy = 0;
    fr.v[1].vx = 0;
    flags = guess_g_FrameCounter;
    if (flags & 1) {
        fr.col[1].r = 0xa0;
    } else if (flags & 2) {
        fr.col[1].r = 0xc0;
    } else {
        fr.col[1].r = 0x80;
    }

    p = ((u8 *)&D_80181BAC);
    fr.col[0].b = 0;
    fr.col[0].g = 0;
    fr.col[0].r = 0;
    fr.col[2].b = 0;
    fr.col[2].g = 0;
    fr.col[2].r = 0;
    fr.col[3].b = 0;
    fr.col[3].g = 0;
    fr.col[3].r = 0;
    fr.code = 0x50000000;
    fr.col[1].b = fr.col[1].r >> 2;
    fr.col[1].g = fr.col[1].r >> 2;
    i = 0;
L1:
        fr.v[0].vx = (s8)*p++;
        fr.v[0].vy = (s8)*p++;
        fr.v[2].vx = (s8)*p++;
        fr.v[2].vy = (s8)*p++;
        fr.v[3].vx = (s8)*p++;
        fr.v[3].vy = (s8)*p--;
        guess_AddPolyG4(fr.v, fr.matrix);
        t = i + 1;
        i = t + 0;
        if ((s16)t < 4) goto L1;

    fr.v[3].vy = 0;
    fr.v[2].vy = 0;
    fr.v[0].vy = 0;
    fr.v[1].vy = 0;
    fr.v[1].vx = 0;
    fr.v[1].vz = -0x20;
    p = D_80181BC0;
    i = 0;
L2:
        fr.v[0].vx = (s8)*p++;
        fr.v[0].vz = (s8)*p++;
        fr.v[2].vx = (s8)*p++;
        fr.v[2].vz = (s8)*p++;
        fr.v[3].vx = (s8)*p++;
        fr.v[3].vz = (s8)*p--;
        guess_AddPolyG4(fr.v, fr.matrix);
        if ((s16)i == 1) {
            fr.v[1].vz = 0x20;
            p += 2;
        }
        t = i + 1;
        i = t + 0;
        if ((s16)t < 4) goto L2;

    p += 2;
    fr.v[0].vx = 0;
    fr.v[0].vz = -0x20;
    fr.col[0].r = fr.col[1].r;
    fr.col[0].b = fr.col[1].g;
    fr.col[0].g = fr.col[1].g;
    i = 0;
L3:
        fr.v[2].vx = (s8)*p++;
        fr.v[2].vz = (s8)*p++;
        fr.v[3].vx = (s8)*p++;
        fr.v[3].vz = (s8)*p++;
        guess_AddPolyG4(fr.v, fr.matrix);
        t = i + 1;
        i = t + 0;
        if ((s16)t < 2) goto L3;
}
