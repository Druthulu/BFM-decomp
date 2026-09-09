/* func_80146128 — shared body (overlay slot 0x80128158, h_exact b9a70482). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_80126B58;
extern s32 *D_80126B78;
extern u8 D_80078EC1;
extern s32 D_80078EC8;
extern s32 D_80126B9C;
extern s32 D_8011F730;
extern u16 D_801152B8;
extern u16 D_8012693A;
extern u8 D_80126BE0[];
extern u8 D_801150F0[];
extern void *memcpy(void *dst, const void *src, u32 n);
extern void func_80146FC4(s32 a0);
extern void func_80150A70(s32 a0);
extern void func_80147098(s32 *a0);
extern void func_8014A638(s32 arg0);
extern s32  func_80155458(s32 a0);
extern s32  func_80029104(void);
extern void func_80029344(void);
extern void func_8014ADE0(s32 a0);
extern void func_8014B350(s32 a0);
extern void func_8014B7A4(s16 *param_1);
extern s32 func_80161D58(s32 a0);
extern void func_80161A90(s32 a0);
extern void func_8014B504(u16 *a0);
extern void func_80149BEC(s32 a0);
extern void func_8014B5D0(s32 *a0);
extern void func_8014C99C(u8 *a0);
extern void func_8014B190(s32 s0);
extern void func_80148648(s32 a0, s32 a1);
extern s32 func_80149228(s32 a0);
extern void func_8014A59C(s32 a0);
extern void func_8016F14C(void *a0);
extern void func_80154418(void *a0);
extern void func_80154BE4(s32 a0);
extern void func_80165694(s32 arg0);
extern void func_801654A8(s32 a0);
extern void func_8014A680(s32 a0);
extern void func_8014A6A8(s32 a0);
extern void func_8014A71C(s32 a0);
extern void func_80172588(s32 *a0);
extern void func_801473DC(s32 *a0);
extern void func_80015978(s32 a0, s32 *a1);
s32 func_80146128(void)
{
    s32 base;
    s32 *p;
    p = D_80126B78;
    base = (s32)&D_80126B58;
    func_80146FC4(base);
    memcpy((void *)D_801150F0, (void *)D_80126BE0, 8);
    func_80150A70(base);
    ((void (*)(s32))func_80147098)(base);
    func_8014A638(base);
    D_8011F730 = 0;
    D_801152B8 = 0;
    D_8012693A = 0;
    if (D_80078EC1 == 0x10 && D_80078EC8 != 0) {
        *(u16 *)((s32)p + 2) = 6;
        D_80126B9C |= 0x800;
    } else {
        *(u16 *)((s32)p + 2) = 1;
        *(s32 *)(base + 0x44) &= ~0x800;
    }
    if (*(s32 *)(base + 0x1B0) != 0) {
        *(s32 *)(base + 0x1B0) = *(s32 *)(base + 0x1B0) - 1;
    }
    if (func_80155458(base) == 0 && (*(s32 *)(base + 0x44) & 0x4000000) == 0) {
        if ((func_80029104() & 0xFF) != 0) {
            func_8014ADE0(base);
            func_8014B350(base);
            ((void (*)(s32))func_8014B7A4)(base);
            ((void (*)(s32))func_80161D58)(base);
        }
        func_80029344();
        func_80161A90(base);
        ((void (*)(s32))func_8014B504)(base);
        func_80149BEC(base);
        ((void (*)(s32))func_8014B5D0)(base);
        ((void (*)(s32))func_8014C99C)(base);
        func_8014B190(base);
        func_80148648(base, 0);
        ((void (*)(s32))func_80149228)(base);
        func_8014A59C(base);
        ((void (*)(s32))func_8016F14C)(base);
        ((void (*)(s32))func_80154418)(base);
        func_80154BE4(base);
        func_80165694(base);
        func_801654A8(base);
        func_8014A680(base);
        func_8014A6A8(base);
        func_8014A71C(base);
        ((void (*)(s32))func_80172588)(base);
        ((void (*)(s32))func_801473DC)(base);
        ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
        return 1;
    }
    ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98);
    return 0;
}
