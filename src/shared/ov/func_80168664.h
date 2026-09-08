/* func_80168664 — shared body (overlay slot 0x80128158, h_exact b5c37d41). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
void func_80168664(void *arg0) {
    s32 iVar3;
    void *blk;
    iVar3 = *(s32 *)((u8 *)arg0 + 0x34);
    *(s32 *)((u8 *)arg0 + 0x1c) = 0x20;
    *(s16 *)((u8 *)arg0 + 0x10) = 0x80;
    *(s16 *)((u8 *)arg0 + 0x12) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0x1800;
    *(Blk20 *)((u8 *)arg0 + 0x38) = D_800AE620;
    blk = (u8 *)arg0 + 0x38;
    RotMatrixX(0x400, blk);
    func_80048EAC((void *)(*(s32 *)((u8 *)iVar3 + 0x20) + 0x34), blk);
    func_801670E4((s32)arg0, -6, -0x44, -0x18);
    *(s16 *)((u8 *)arg0 + 2) = *(s16 *)((u8 *)arg0 + 2) + 1;
}
