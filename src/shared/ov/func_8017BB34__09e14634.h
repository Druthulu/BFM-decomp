/* func_8017BB34 — shared body (overlay slot 0x80128158, h_exact 09e14634). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : RotMatrixZYX arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_8018F93C)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_8018F934) = svec;

    v0.vx = -*(s16 *)(param_2 + 0xc);
    v0.vy = *(u16 *)(param_2 + 8);
    v0.vz = 0;
    v1.vx = 0;
    v1.vy = 0;
    v1.vz = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))RotMatrixZYX)(&v0, &mtx);

    mtx.t[0] = (s32)svec.vx;
    mtx.t[1] = (s32)svec.vy;
    mtx.t[2] = (s32)svec.vz;
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_8018F93C) = buf1;
}
