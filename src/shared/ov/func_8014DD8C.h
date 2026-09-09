/* func_8014DD8C — shared body (overlay slot 0x80128158, h_exact 50046563). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2) {
    extern u8 D_801202A0[];
    extern u8 D_80126720[];
    extern s32 ratan2(s32 a0, s32 a1);
    extern s32 func_80012A60(s32 a0, s32 a1);
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
    s16 temp_s0;
    s32 temp_s0_2;
    s16 temp_s1;
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_a1;
    s8 *var_s2;
    s8 *var_s3;
    __asm__ __volatile__("" :: "r"(((void *)arg0)));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
    temp_v0 = M2C_FIELD(arg2, u16 *, 0) - M2C_FIELD(arg1, u16 *, 0);
    temp_v1 = M2C_FIELD(arg2, u16 *, 4) - M2C_FIELD(arg1, u16 *, 4);
    if (((temp_v0 | temp_v1) << 0x10) != 0) {
        var_s3 = (s8 *) D_801202A0;
        if (var_s3 < var_s3 + 0x6480) {
            var_s2 = var_s3 + 0xE;
            __asm__ __volatile__("" :: "r"(var_s2));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
loop_3:
            if (M2C_FIELD(var_s3, u16 *, 0) != 0) {
                temp_a1 = M2C_FIELD(var_s2, s32 *, 0x4A);
                if ((temp_a1 != 0) && (M2C_FIELD(var_s2, u16 *, 0x4E) & 0x1000) && (func_80135A4C(M2C_FIELD(var_s2, s32 *, 0x12), temp_a1, (s32 *)arg1, (s32)arg2) != 0)) {
                    temp_s1 = M2C_FIELD(var_s2, u16 *, -8) - M2C_FIELD(((void *)arg0), u16 *, 6);
                    temp_s0 = M2C_FIELD(var_s2, u16 *, 0) - M2C_FIELD(((void *)arg0), u16 *, 0xE);
                    temp_s0_2 = (s16) ratan2(temp_v1, temp_v0);
                    if ((s16) func_80012A60(temp_s0_2, (s16) ratan2(temp_s0, temp_s1)) < 0x400) {
                        M2C_FIELD(((void *)arg0), s8 **, 0x170) = var_s3;
                        M2C_FIELD(((void *)arg0), u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 0);
                        M2C_FIELD(((void *)arg0), s16 *, 0xA) = (s16) (M2C_FIELD(arg2, u16 *, 2) + 0x10);
                        M2C_FIELD(((void *)arg0), u16 *, 0xE) = (u16) M2C_FIELD(arg2, u16 *, 4);
                        return 1;
                    }
                }
            }
            var_s3 += 0x10C;
            var_s2 += 0x10C;
            if ((u32) var_s3 >= (u32) D_80126720) {
                goto block_10;
            }
            goto loop_3;
        }
        return 0;
    }
block_10:
    return 0;
}
