extern s32 D_800D1368;
extern s32 D_800D1374;
extern void func_800CF408(s32 a0, s32 a1);
extern void func_800167B8(s32 a0);

void func_800CF148(void) {
    // Redeclare with correct calling semantics
    extern s32 func_800CF3B0(void);
    
    if (func_800CF3B0()) {
        return;
    }
    
    func_800CF408(0, D_800D1368);
    
    D_800D1368--;
    if (D_800D1368 < -0x10F) {
        func_800167B8(0x4);
        D_800D1368 = -0x110;
        D_800D1374++;
    }
}
