extern s32 D_800CDD30;
extern s32 D_800CDD34;

void func_800CD92C(s32, s32, s32);
void func_800116A0(void);

void func_800CD614(void) {
    s32 v0;
    
    func_800CD92C(D_800CDD30, 0, D_800CDD34);
    v0 = D_800CDD34 - 8;
    D_800CDD34 = v0;
    if (v0 > 0) {
        return;
    }
    func_800116A0();
}
