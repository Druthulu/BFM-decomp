extern s32 func_8001B244(s32);
extern void func_8001AD38(const char*);
extern void func_800116A0(void);

extern s32 D_800CDD2C;
extern s32 D_800CDD34;

const char D_800CD34C[] = "C:\\TIMPACK\\OPDEMO0.PAT";

void func_800CD3B8(void) {
    if (func_8001B244(0x8E) == 0) {
        return;
    }

    func_8001AD38(D_800CD34C);
    D_800CDD2C = 0;
    D_800CDD34 = 0;
    func_800116A0();
}
