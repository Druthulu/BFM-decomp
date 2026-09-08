/* func_801630C4 — shared body (overlay slot 0x80128158, h_exact b8527142). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162F60(s32 arg0, s32 arg1);
extern void func_80162F80(s32 arg0, s32 arg1);
extern void func_80162FA0(s32 arg0, s32 arg1);
extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_80146D30(s32 a0);
extern s32 aD_80127090 __asm__("D_80127090");
extern s32 aD_80127094 __asm__("D_80127094");
extern s32 aD_80127098 __asm__("D_80127098");
void func_801630C4(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 sp[16];
    s32 s2 = a0;
    s32 s0 = a2;
    s32 s3 = a3;
    s32 s1 = *(s32 *)(s2 + 0x20);
    s32 *q;
    func_80162F60(a0, a1);
    func_80162F80(s2, s0);
    func_80162FA0(s2, s3);
    q = &sp[8];
    func_80013F3C((s32)q);
    func_80012558((s32)q, *(s16 *)(s1 + 0x12));
    func_800126C4((s32)q, *(s16 *)(s1 + 0x10));
    func_800123F0((s32)q, *(s16 *)(s1 + 0x14));
    func_800484EC((s32)q, s2 + 0x24, (s32)&sp[4]);
    aD_80127090 = sp[4];
    aD_80127094 = sp[5];
    aD_80127098 = sp[6];
    func_80146D30(s2);
}
