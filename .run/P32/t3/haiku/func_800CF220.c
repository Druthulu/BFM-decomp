extern void func_8001AA98(void *a0);
extern s32 D_800D1374;
extern void func_800167B8(s32 a0);

const char D_800CEE14[] = "C:\\TIMPACK\\OPDEMO1.PAT";

void func_800CF220(void) {
    func_8001AA98((void *)D_800CEE14);
    func_800167B8(0);
    D_800D1374++;
}
