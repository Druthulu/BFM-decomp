/* func_8012E778 — shared body (overlay slot 0x80128158, h_exact fba658ee). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_800AF648;
s32 func_8012E778(int param_1, int param_2)
{
    MATRIX_L48 *r0;
    int iVarX;
    int iVarY;
    int iVar3;
    int iVar4;
    int sp[6];
    sp[0] = (int)*(short *)(param_1 + 6);
    sp[1] = (int)*(short *)(param_1 + 10);
    sp[2] = (int)*(short *)(param_1 + 0xe);
    r0 = (MATRIX_L48 *)&D_800AF648;
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
    gte_ldlv0((VECTOR *)sp);
    gte_rtps();
    gte_stsxy((long *)((int)sp + 0x10));
    iVarX = (int)*(short *)((int)sp + 0x10);
    iVar3 = (short)param_2;
    if (iVarX >= 0) {
        if (iVar3 >= iVarX) goto cy;
        return 0;
    }
    if (iVar3 < -iVarX) return 0;
cy:
    iVarY = (int)*(short *)((int)sp + 0x12);
    iVar4 = param_2 >> 0x10;
    if (iVarY >= 0) {
        if (iVar4 >= iVarY) goto c1;
        return 0;
    }
    if (iVar4 < -iVarY) return 0;
c1:
    return 1;
}
