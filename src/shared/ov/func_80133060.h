/* func_80133060 — shared body (overlay slot 0x80128158, h_exact d59a1687). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801330E0(void * param_1, s16 * param_2, s32 param_3);
void func_80133060(u8 *a0, s32 *a1, s32 a2) {
    s16 tmp[3];
    tmp[0] = *(u16 *)(a0 + 2);
    tmp[1] = *(u16 *)(a0 + 6);
    tmp[2] = *(u16 *)(a0 + 0xA);
    func_801330E0(tmp, tmp, (s16)a2);
    a1[0] = tmp[0] << 16;
    a1[1] = tmp[1] << 16;
    a1[2] = tmp[2] << 16;
}
