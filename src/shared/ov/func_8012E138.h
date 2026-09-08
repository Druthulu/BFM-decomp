/* func_8012E138 — shared body (overlay slot 0x80128158, h_exact 11b77ce5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_80049CAC();
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888();
void func_8012E138(int model) {
    struct Cam8012E138 cam;
    int bufB[2];
    int bufA[2];
    int m;
    short s;
    cam.a = D_80126B5E;
    cam.b = D_80126B62;
    cam.c = D_80126B66;
    func_8012F038(*(int *)(model + 0x20) + 0x34, &cam, bufA);
    m = *(int *)(model + 0x20);
    if (m != 0) {
        int mm;
        func_80049CAC(m + 0x10, m + 0x34);
        mm = *(int *)(model + 0x20);
        s = *(u16 *)(model + 6) + *(u16 *)(model + 0x50);
        *(u16 *)(mm + 8) = s;
        *(int *)(mm + 0x48) = s;
        s = *(u16 *)(model + 0xA) + *(u16 *)(model + 0x52);
        *(u16 *)(mm + 0xA) = s;
        *(int *)(mm + 0x4C) = s;
        s = *(u16 *)(model + 0xE) + *(u16 *)(model + 0x54);
        *(u16 *)(mm + 0xC) = s;
        *(u16 *)(mm + 0x2C) = *(u16 *)(mm + 0x2C) | 1;
        *(int *)(mm + 0x50) = s;
    }
    func_8012F14C(*(int *)(model + 0x20) + 0x34, bufA, bufB);
    if (func_80135888(*(int *)(model + 0x20), *(int *)(model + 0x58), bufB, &cam)) {
        D_80126B5E = cam.a;
        D_80126B62 = cam.b;
        D_80126B66 = cam.c;
    }
}
