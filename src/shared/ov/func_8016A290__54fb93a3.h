/* func_8016A290 — shared body (overlay slot 0x80128158, h_exact 54fb93a3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8016A290(s32 param_1, void *param_2, void *param_3) {
    extern u8 D_80181BAC;
    extern u8 D_80181BC0[];

    struct Fr_8016A290 fr;
    u8 *p;
    u16 i;
    u16 t;
    s32 flags;
    s32 iVar3;

    iVar3 = *(s32 *)(param_1 + 0x34);

    fr.center.vx = (*((s16 *)param_2) + *((s16 *)param_3)) >> 1;
    fr.center.vy = (((s16 *)param_2)[1] + ((s16 *)param_3)[1]) >> 1;
    fr.center.vz = (((s16 *)param_2)[2] + ((s16 *)param_3)[2]) >> 1;
    ((void(*)(s32, void *, void *))guess_ObjRotTransSV)(iVar3, &fr.center, &fr.center);

    *(u16 *)(param_1 + 0x6) = *(u16 *)&fr.center.vx;
    *(u16 *)(param_1 + 0xA) = *(u16 *)&fr.center.vy;
    *(u16 *)(param_1 + 0xE) = *(u16 *)&fr.center.vz;
    func_800D20C0(&fr.center, &fr.diff, 8);
    func_80017E68(&fr.center, fr.mtx);

    fr.diff.vx = *(u16 *)((s16 *)param_3) - *(u16 *)((s16 *)param_2);
    fr.diff.vy = *(u16 *)(((s16 *)param_3) + 1) - *(u16 *)(((s16 *)param_2) + 1);
    fr.diff.vz = *(u16 *)(((s16 *)param_3) + 2) - *(u16 *)(((s16 *)param_2) + 2);
    ((void(*)(s32, void *, void *))ApplyMatrixSV)(*(s32 *)(iVar3 + 0x20) + 0x34, &fr.diff, &fr.diff);
    func_800D23D0(&fr.diff);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.pos[0] = guess_g_MainCameraAppliedViewPointX - fr.center.vx;
    fr.pos[1] = guess_g_MainCameraAppliedViewPointY - fr.center.vy;
    fr.pos[2] = guess_g_MainCameraAppliedViewPointZ - fr.center.vz;
    ApplyTransposeMatrixLV(fr.mtx, fr.pos, fr.pos);
    fr.diff.vz = -ratan2(fr.pos[0], fr.pos[1]);
    RotMatrixYXZ(&fr.diff, fr.mtx);

    fr.v[3].vz = 0;
    fr.v[2].vz = 0;
    fr.v[0].vz = 0;
    fr.v[1].vz = 0;
    fr.v[1].vy = 0;
    fr.v[1].vx = 0;
    flags = guess_g_FrameCounter;
    if (flags & 1) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x20;
    } else if (flags & 2) {
        fr.col[1].r = *(s32 *)(param_1 + 0x30) + 0x40;
    } else {
        fr.col[1].r = *(s32 *)(param_1 + 0x30);
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
    fr.col[1].b = fr.col[1].r >> 3;
    fr.col[1].g = fr.col[1].r >> 3;
    i = 0;
L1:
        fr.v[0].vx = (s8)*p++;
        fr.v[0].vy = (s8)*p++;
        fr.v[2].vx = (s8)*p++;
        fr.v[2].vy = (s8)*p++;
        fr.v[3].vx = (s8)*p++;
        fr.v[3].vy = (s8)*p--;
        guess_AddPolyG4(fr.v, fr.mtx);
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
        guess_AddPolyG4(fr.v, fr.mtx);
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
        guess_AddPolyG4(fr.v, fr.mtx);
        t = i + 1;
        i = t + 0;
        if ((s16)t < 2) goto L3;
}
