extern void func_8012C588(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_801EB318;
extern s32 D_801F1468;

void func_801F0048(s32 a0) {
    s32 v1;
    s32 v0;

    func_8012C588(0x8D, a0);

    v1 = *(s32 *)(a0 + 0x20);
    v0 = (s32)&D_801EB318;
    *(s32 *)(v1 + 0x24) = v0;

    func_8012A828(a0, (s32)&D_801F1468);
}
