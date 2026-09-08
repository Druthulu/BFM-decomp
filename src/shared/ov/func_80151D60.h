/* func_80151D60 — shared body (overlay slot 0x80128158, h_exact 8a229bd3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_80151DB0(s32 a0);
extern void func_80146CA0(void *a0);
void func_80151D60(void *a0) {
    func_8014E934((s32)a0);
    func_8014CC28((s32)a0);
    func_8014F3E8((s32)a0);
    func_80151DB0((s32)a0);
    *(s8 *)((u8 *)a0 + 0xDE) = 0x20;
    func_80146CA0(a0);
}
