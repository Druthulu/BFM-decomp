/* func_8018B0AC — shared body (overlay slot 0x80128158, h_exact f9bb0ccf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012C588(s32, s32);
extern void func_8018A0B4(void);
void func_8018B0AC(void *a0) {
    s32 v0;
    u16 val;
    v0 = ((s32 (*)(void *))func_8012C1B8)(a0);
    *(s32 *)((char *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, 0);
    func_8012C588(0x13F, 0);
    func_8012C588(0x66, 0);
    func_8012C588(0x65, 0);
    func_8012C588(0x14C, 0);
    func_8012C588(0x335, 0);
    func_8012C588(0x3D9, 0);
    val = *(u16 *)((char *)a0 + 0x72);
    *(u16 *)((char *)a0 + 0x2) = 1;
    val |= 0x1000;
    *(u16 *)((char *)a0 + 0x72) = val;
    func_8018A0B4();
}
