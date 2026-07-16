typedef unsigned int u32;
typedef int s32;
extern void g();
void f(int param_1)
{
    register u32 a __asm__("$3");
    register u32 b __asm__("$4");
    g();
    if (a != b) {
        if ((s32)a < (s32)b) a = a + 1;
    }
}
