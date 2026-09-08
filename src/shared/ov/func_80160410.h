/* func_80160410 — shared body (overlay slot 0x80128158, h_exact 6a51c7ff). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80019064(void *a0);
extern void func_80149020(s32 *a0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 arg0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern s32 func_80149184(s32 a0);
extern void func_80146CA0(void *a0);
extern u8 D_80062BD0;
extern s16 D_801152A0;
void func_80160410(s32 * a0)
{
    register s32 angle __asm__("$17");
    s32 m1[3];
    s32 out[12];
    u32 buf[2];
    func_80019064((void *)&D_80062BD0);
    func_80149020(a0);
    {
        s32 t = (s32)(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12));
        angle = (s32)(*(u16 *)((s32)a0 + 0x42)) - t;
    }
    func_80013E94((void *)((s32)a0 + 0xE8), buf);
    {
        s32 a2v = (s32)*(s16 *)((s32)a0 + 0xE0);
        u32 v6 = buf[0] | 0x80000000;
        s32 a3v = (s32)*(s16 *)((s32)a0 + 0xE2);
        s32 a5v = (s32)*(s16 *)((s32)a0 + 0xE4);
        buf[0] = v6;
        func_80146A6C(6, a0, a2v, a3v, a5v, v6, 0);
    }
    func_80147324(0x43D);
    angle = (s32)(angle << 16) >> 16;
    m1[0] = 0;
    m1[1] = 0;
    m1[2] = 0xFFFA0000;
    func_8001382C(angle, m1, out);
    func_80146DB8(a0, out);
    m1[0] = 0;
    m1[1] = 0;
    m1[2] = 0x8000;
    func_8001382C(angle, m1, (void *)((s32)a0 + 0x234));
    func_80146E90(a0, 8);
    func_801553A8(a0);
    D_801152A0 = func_80149184((s32)a0);
    func_80146CA0(a0);
}
