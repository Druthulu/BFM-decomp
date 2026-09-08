/* func_80173EF8 — shared body (overlay slot 0x80128158, h_exact a861b6c2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126938;
extern s16 D_80126B3A;
extern void func_80147060(u8 *a0);
extern void func_800D128C(s32, s32);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern void func_80174158(s32 a0);
extern void func_8002A088(s32);
extern void func_8002A2D4(s32);
extern void func_8002A544(s32);
extern void func_8002A7B4(s32);
extern s32 func_80029178(s32 arg);
extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);
extern s32  func_800D0EC4(void);
extern void func_800D0F0C(s32, s32);
extern void func_80145EE8(s32);
extern void func_80171A1C(u8 *a0);
void func_80173EF8(void *param_1)
{
    if ((*(u16 *)((s32)param_1 + 0xB8) & 0x8000) == 0) {
        return;
    }
    D_80126938 = 1;
    ((void (*)(void))func_80147060)();
    switch (D_80126B3A) {
    case 0:
        break;
    case 0x70:
        func_800D128C((u8)D_80126B3A, 0);
        break;
    case 0x78:
        func_80029124(0x8A, 1);
        func_80029514(0xC8);
        ((void (*)(void *))func_80174158)(param_1);
        func_8002A088(0x64);
        func_8002A2D4(0x20);
        func_8002A544(0x20);
        func_8002A7B4(0x18);
        break;
    case 0x79:
        func_80029124(0x8B, 1);
        func_80029514(0x258);
        ((void (*)(void *))func_80174158)(param_1);
        func_8002A088(0xA0);
        func_8002A2D4(0x28);
        func_8002A544(0x40);
        func_8002A7B4(0x30);
        break;
    case 0x7A:
        func_80029124(0x8C, 1);
        func_80029514(0x384);
        ((void (*)(void *))func_80174158)(param_1);
        func_8002A088(0xF0);
        func_8002A2D4(0x30);
        func_8002A544(0x60);
        func_8002A7B4(0x48);
        break;
    case 0x7B:
        func_80029124(0x8D, 1);
        func_80029514(0x4B0);
        ((void (*)(void *))func_80174158)(param_1);
        func_8002A088(0x140);
        func_8002A2D4(0x40);
        func_8002A544(0x80);
        func_8002A7B4(0x60);
        break;
    case 0x7C:
        if ((u8)func_80029178(0x11D) == 0) {
            ((void (*)(void *))func_80174188)(param_1);
        }
        func_8002A088(0x190);
        func_8002A2D4(0x50);
        func_8002A544(0xA0);
        func_8002A7B4(0x80);
        ((void (*)(void *))func_801741A8)(param_1);
        func_80029124(0x8E, 1);
        break;
    default:
        func_800D0F0C(func_800D0EC4(), (s32)D_80126B3A);
        break;
    }
    func_80145EE8(0);
    ((void (*)(void *))func_80171A1C)(param_1);
}
