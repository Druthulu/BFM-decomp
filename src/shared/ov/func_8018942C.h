/* func_8018942C — shared body (overlay slot 0x80128158, h_exact 10e3ce27). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BEE8(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_80188C60(s32 a0);
extern int func_80178970(void);
void func_8018942C(s32 arg0) {
    u16 val_34;
    s16 val_fe, val_a;
    val_34 = *(u16 *)(arg0 + 0x34);
    if (val_34 == 0) {
        if (func_8012BEE8(arg0) != 0) {
            *(s32 *)(arg0 + 0x14) = 0x10000;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
    } else {
        val_fe = *(s16 *)(arg0 + 0xFE);
        val_a = *(s16 *)(arg0 + 0xA);
        if (val_a < (val_fe - 0xA0)) {
            func_8012AD80(arg0);
        } else {
            func_80188C60(arg0);
        }
    }
    ((void (*)(s32))func_80178970)(arg0);
}
