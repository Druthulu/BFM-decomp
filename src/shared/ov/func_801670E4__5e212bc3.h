/* func_801670E4 — shared body (overlay slot 0x80128158, h_exact 5e212bc3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_801670E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    extern u8  D_801819C8[];
    extern u8  D_801819B4[];
    extern u8  D_801819DC[];
    extern s32 guess_g_MainCameraAppliedViewPointX; // Names ledger: config/names.tsv guess_g_MainCameraAppliedViewPointX
    extern s32 guess_g_MainCameraAppliedViewPointY; // Names ledger: config/names.tsv guess_g_MainCameraAppliedViewPointY
    extern s32 guess_g_MainCameraAppliedViewPointZ; // Names ledger: config/names.tsv guess_g_MainCameraAppliedViewPointZ
    extern u16 D_80126CE0;
    Fr_801670E4 f;
    u8 *p;   /* $s2 */
    s32 ent;   /* $s3 */
    s16 i;
    s32 d;
    s32 node;
    u16 c;
    u8 cv;
    u8 cv2;

    ent = arg0;
    node = *(s32 *)(ent + 0x34);
    f.v[1].z = 0;
    f.v[1].y = 0;
    f.v[1].x = 0;
    f.v[3].z = 0;
    f.v[2].z = 0;
    f.v[0].z = 0;
    f.col[1].b = 0x70;
    cv = *(u8 *)(ent + 0x12);
    f.cx = arg1;
    f.cy = arg2;
    f.col[0].b = 0;
    f.col[0].g = 0;
    f.col[0].r = 0;
    f.col[2].b = 0;
    f.col[2].g = 0;
    f.col[2].r = 0;
    f.col[3].b = 0;
    f.col[3].g = 0;
    f.col[3].r = 0;
    f.code = 0x50000000;
    f.cz = arg3;
    f.col[1].g = cv;
    f.col[1].r = cv;
    ((void (*)(s32, void *, void *))guess_ObjRotTransSV)(node, &f.cx, &f.cx);

    c = f.cx;
    *(s16 *)(ent + 0x06) = c;
    *(s32 *)(ent + 0x4C) = (s16)c;
    c = f.cy;
    *(s16 *)(ent + 0x0A) = c;
    *(s32 *)(ent + 0x50) = (s16)c;
    c = f.cz;
    *(s16 *)(ent + 0x0E) = c;
    *(s32 *)(ent + 0x54) = (s16)c;
    func_800D20C0(&f.cx, f.a8, 7);
    func_80017E68(&f.cx, f.m1);
    func_800D23D0(f.a8);
    RotMatrixYXZ(f.a8, f.m1);
    p = D_801819C8;
    i = 0;

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].y = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].y = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].y = (s8)*p--;
        guess_AddPolyG4(f.v, f.m1);
    } while ((i = i + 1) < 4);

    p = D_801819B4;
    i = 0;
    f.v[3].y = 0;
    f.v[2].y = 0;
    f.v[0].y = 0;
    f.col[1].g = 0xA0;
    f.col[1].b = 0x10;
    f.col[1].r = 0x10;
    f.pos[0] = guess_g_MainCameraAppliedViewPointX - (s16)f.cx;
    f.pos[1] = guess_g_MainCameraAppliedViewPointY - (s16)f.cy;
    f.pos[2] = guess_g_MainCameraAppliedViewPointZ - (s16)f.cz;

    do {
        f.v[0].x = (s8)*p++;
        f.v[0].z = (s8)*p++;
        f.v[2].x = (s8)*p++;
        f.v[2].z = (s8)*p++;
        f.v[3].x = (s8)*p++;
        f.v[3].z = (s8)*p--;
        guess_AddPolyG4(f.v, (void *)(ent + 0x38));
    } while ((i = i + 1) < 4);

    if (*(s32 *)(ent + 0x30) > 0) {
        d = (s16)f.a8[0] >> 6;
        f.cx += d;
        f.cy += d;
        f.cz += d;
        func_80017E68(&f.cx, f.m1);
        f.cx = f.cy = f.cz = ((u32)*(s32 *)(ent + 0x30) >> 1) + D_80126CE0 * 0x20;
        func_80017DC4(&f.cx, f.m2);
        func_80048EAC(f.m2, f.m1);
        f.v[3].z = 0;
        f.v[2].z = 0;
        f.v[0].z = 0;
        cv2 = *(u8 *)(ent + 0x12);
        f.col[1].b = 0x20;
        f.col[1].r = 0x20;
        f.col[3].b = 0;
        f.col[3].r = 0;
        f.col[2].b = 0;
        f.col[2].r = 0;
        f.col[0].b = 0;
        f.col[0].r = 0;
        f.col[3].g = 0;
        f.col[2].g = 0;
        f.col[0].g = 0;
        f.col[1].g = cv2 + 0x60;
        p = D_801819DC;
        i = 0;
        do {
            f.v[0].x = (s8)*p++;
            f.v[0].y = (s8)*p++;
            f.v[2].x = (s8)*p++;
            f.v[2].y = (s8)*p++;
            f.v[3].x = (s8)*p++;
            f.v[3].y = (s8)*p--;
            guess_AddPolyG4(f.v, f.m1);
        } while ((i = i + 1) < 8);
    }
}
