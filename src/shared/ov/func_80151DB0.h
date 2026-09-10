/* func_80151DB0 — shared body (overlay slot 0x80128158, h_exact 955c85ce). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80019064(void *a0);
extern int func_80151204(int arg, int a1);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);
extern s32 func_80172630(u8 *a0);
extern s32 D_80062C14;
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
void func_80151DB0(s32 param_1)
{
    short sVar1;
    int iVar3;
    func_80019064(&D_80062C14);
    ((void (*)(int, int))func_80151204)(param_1, (int)*(short *)(param_1 + 0xf2));
    sVar1 = ((short (*)(int, int))func_80012A60)((int)*(short *)(*(int *)(param_1 + 0x20) + 0x12),
                          (int)*(short *)(param_1 + 0xf4));
    if (sVar1 >= 0x401) {
        ((void (*)(int, void *))func_80154274)(param_1, &D_800D5880);
        iVar3 = *(int *)(param_1 + 0x20);
        *(unsigned short *)(iVar3 + 0x10) = (0xc00);
    } else {
        ((void (*)(int, void *))func_80154274)(param_1, &D_800D58AC);
        iVar3 = *(int *)(param_1 + 0x20);
        *(unsigned short *)(iVar3 + 0x10) = (0x400);
    }
    *(unsigned short *)(param_1 + 100) = 0xcc;
    ((void (*)(int))func_80149020)(param_1);
    func_80147324(0x436);
    ((void (*)(int))func_80146CA0)(param_1);
    ((void (*)(int))func_80172630)(param_1);
}
