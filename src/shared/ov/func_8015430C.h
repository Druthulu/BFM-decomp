/* func_8015430C — shared body (overlay slot 0x80128158, h_exact b574296a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801549F8(s32 a0, s32 a1, s32 a2);
extern void func_80154418(void *a0);
void func_8015430C(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0xB4) = arg1;
    *(s16 *)(arg0 + 0xBA) = 1;
    *(s16 *)(arg0 + 0xB8) = 1;
    *(s8 *)(arg0 + 0xBC) = arg2;
    *(s8 *)(arg0 + 0xBD) = arg2;
    *(s8 *)(arg0 + 0xDC) = func_801549F8((s32)arg0, arg1, arg2);
    func_80154418(arg0);
}
