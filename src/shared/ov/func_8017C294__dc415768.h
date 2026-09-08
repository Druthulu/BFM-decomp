/* func_8017C294 — shared body (overlay slot 0x80128158, h_exact dc415768). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ReadRotMatrix(void *a0);
extern void PushMatrix(void);
extern void func_8004974C(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void PopMatrix(void);
void func_8017C294(u16 *a0, void *a1) {
    s32 mat[8];
    s32 buf[8];
    s16 sv[4];
    ReadRotMatrix((void *)mat);
    PushMatrix();
    sv[0] = (s16)(a0[0] - *(s32 *)((u8 *)mat + 0x14));
    sv[1] = (s16)(a0[1] - *(s32 *)((u8 *)mat + 0x18));
    sv[2] = (s16)(a0[2] - *(s32 *)((u8 *)mat + 0x1C));
    func_8004974C((void *)mat, (void *)buf);
    ApplyMatrixSV((void *)buf, (void *)sv, a1);
    PopMatrix();
}
