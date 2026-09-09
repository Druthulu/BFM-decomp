/* func_8017EE68 — shared body (overlay slot 0x80128158, h_exact 34856783). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8017EE68(s32 a0)
{
    s32 s0 = (s32)&D_80126E60;
    s32 t0;

    *(s32*)&D_80126E6C = 0x1F4;
    *(s32*)&D_80126E74 = 0x320;
    *(s16*)&D_80126E80 = 0xAA;
    *(s16*)&D_80126E82 = 0x400;
    *(s16*)&D_80126E84 = 0;
    *(s16*)&D_80126E8E = 0;
    *(s16*)&D_80126E90 = -0x32;
    *(s16*)&D_80126E92 = 0;

    func_8012A094(s0);
    t0 = s0;  /* Move s0 to t0 to emit a register move */
    func_8012A048(s0, (s32)&func_8017EF10, 0x1);
    ((s32 (*)(s32))func_8017EF10)(s0);
    func_8012A100(0x1);
}
