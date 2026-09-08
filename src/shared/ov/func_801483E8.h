/* func_801483E8 — shared body (overlay slot 0x80128158, h_exact e947d476). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(int a0, int *a1);
extern int func_80133784(int a0, void *a1, int a2);
void func_801483E8(unsigned char *self) {
    unsigned short src[4];
    short dst[4];
    int ret;
    func_80015978((int)(self + 4), (int *)src);
    dst[0] = src[0];
    dst[1] = src[1] + 8;
    dst[2] = src[2];
    ret = func_80133784(1, src, (int)dst);
    if (ret == 0x2000 &&
        *(short *)(self + 6) == dst[0] &&
        *(short *)(self + 0xA) == dst[1] &&
        *(short *)(self + 0xE) == dst[2] &&
        *(unsigned char *)&dst[3] == 0) {
        func_80015978((int)(self + 4), (int *)(self + 0xA0));
    }
}
