/* func_8016A1CC — shared body (overlay slot 0x80128158, h_exact d4c8dd1e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80078EBF;
extern void func_80147324(s32 arg0);
extern void func_80147364();
extern void func_80146C3C();
void func_8016A1CC(int param_1)
{
    register int iVar1 __asm__("$2");
    if (D_80078EBF != 0) {
        iVar1 = D_80078EBF - 0x18;
        *(int *)(param_1 + 0x30) = iVar1;
        if (iVar1 >= 0) {
            iVar1 = *(int *)(param_1 + 0x1c) + 1;
            *(int *)(param_1 + 0x1c) = iVar1;
            if (iVar1 == 4) {
                func_80147324(0x44c);
            }
            if (D_80078EBF >= 0x80) {
                if (*(short *)(param_1 + 0x2a) == 0) {
                    *(short *)(param_1 + 0x2a) = 1;
                    *(int *)(param_1 + 0x1c) = 0x100;
                }
                if ((*(unsigned int *)(param_1 + 0x1c) & 0x1f) == 0) {
                    func_80147324(0x44d);
                }
            }
        }
    } else {
        ((void (*)(int, int))func_80147364)(4, 0x44c);
        ((void (*)(int))func_80146C3C)(param_1);
    }
}
