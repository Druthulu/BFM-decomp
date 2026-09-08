/* func_801516F0 — shared body (overlay slot 0x80128158, h_exact e86c328e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014C8F0(s32 arg0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80151780(s32 a0);
void func_801516F0(s32 *a0) {
    func_8014C8F0((s32)a0);
    *((u8 *)a0 + 0xDE) = (u8)*(u16 *)a0;
    func_80147078(a0, 0x19);
    *(s16 *)((u8 *)a0 + 0x2) = 1;
    func_80151780((s32)a0);
}
