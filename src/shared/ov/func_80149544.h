/* func_80149544 — shared body (overlay slot 0x80128158, h_exact 7b9ce63f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012EF70(s32 a0, s32 a1);
void func_80149544(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10[2];
    ((void(*)(s32,s32,s32))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x34, arg1, (s32)sp10);
    func_8012EF70((s32)sp10, arg2);
}
