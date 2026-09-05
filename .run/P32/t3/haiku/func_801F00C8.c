extern s32 func_8012E544(s32 a0);
extern void func_800291A0(s32 a0, s32 a1);

void func_801F00C8(void) {
    s32 v0 = func_8012E544(0x11A);
    if (v0 != 0) {
        *(s16*)(v0 + 0xFC) = 2;
        func_800291A0(0xCC, 0x1);
    }
}
