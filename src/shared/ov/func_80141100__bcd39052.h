/* func_80141100 — shared body (overlay slot 0x80128158, h_exact bcd39052). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
int func_80141100(int param_1)
{
    short sVar1;
    int iVar7;

    if (D_80115128 == 0) {
        iVar7 = D_80115172 + 0x31;
        sVar1 = D_801800D6;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A1B4)(), func_8002A28C(), func_8002A27C(), (short)iVar7, (int)sVar1);
        sVar1 = D_801800DA;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A400)(), func_8002A4D8(), func_8002A4C8(), (short)iVar7, (int)sVar1);
        sVar1 = D_801800DE;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A8E0)(), func_8002A9B8(), func_8002A9A8(), (short)iVar7, (int)sVar1);
        sVar1 = D_801800E2;
        param_1 = func_801412A8(param_1, ((short (*)(void))func_8002A670)(), func_8002A748(), func_8002A738(), (short)iVar7, (int)sVar1);
    }
    return param_1;
}
