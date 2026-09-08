/* func_801494CC — shared body (overlay slot 0x80128158, h_exact 07fe2d7e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F038(int param_1, short *param_2, short *param_3);
void func_801494CC(s32 a0, u16 *a1, u16 *a2) {
    u16 dst[3];
    u16 src[3];
    src[0] = a1[1];
    src[1] = a1[3];
    src[2] = a1[5];
    ((void (*)(s32, u16 *, u16 *))func_8012F038)(*(s32 *)(a0 + 0x20) + 0x34, src, dst);
    a2[1] = dst[0];
    a2[3] = dst[1];
    a2[5] = dst[2];
}
