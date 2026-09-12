/* func_80149584 — shared body (overlay slot 0x80128158, h_exact 050bd704). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012EFB8(void *param_1, void *param_2);
void func_80149584(s32 arg0, s32 arg1, s32 arg2) {
    s8 buf[8];
    ((void(*)(s32,s32,s32))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x34, arg1, (s32)buf);
    ((void(*)(s32,s32))func_8012EFB8)((s32)buf, arg2);
}
