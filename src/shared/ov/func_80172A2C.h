/* func_80172A2C — shared body (overlay slot 0x80128158, h_exact fd7fe640). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147060(u8 *a0);
extern void func_80149350(s32 arg0);
extern void func_80171A1C(u8 *a0);
extern void func_80172A8C(void *a0);
extern s16 D_80126B30;
void func_80172A2C(int param_1)
{
    ((void (*)(int))func_80147060)(param_1);
    *(short *)(param_1 + 0x136) = 2;
    *(short *)(param_1 + 0x132) = *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    ((void (*)(int, void *, void *))func_80149350)(param_1, &D_80126B30, &D_80126B30);
    ((void (*)(int))func_80171A1C)(param_1);
    ((void (*)(int))func_80172A8C)(param_1);
}
