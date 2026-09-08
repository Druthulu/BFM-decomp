/* func_8015126C — shared body (overlay slot 0x80128158, h_exact 59d8e878). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8015126C(u16 *p)
{
    extern s32 D_80127078;
    extern s32 D_80126AE4;
    extern s32 D_801151FC;
    extern s32 D_80127518;
    extern s32 D_800AE6A8;       /* +0x8 == D_800AE6B0 (s32) */
    extern u8  D_80078E78[];     /* +0x49 == D_80078EC1 (u8) */
    extern s32 func_801470A0(void *a0);
    extern s32 func_8014A454(s32 a0);
    extern void func_80160368(s32 *a0);
    extern s32 func_801619D0(void *a0);
    extern s32 func_80151880(s32 a0);
    extern void func_800CCF68(void *);
    extern s32 func_80161A00(s32 a0);
    extern s32 func_801518D8(s32 a0);
    extern void func_800CCF58(void *);
    extern s32 func_80161A30(s32 a0);
    extern s32 func_80161A60(s32 a0);
    extern void func_801599A4(void *);
    extern void func_801607B8(s32 *a0);
    extern void func_80147084(s32 *a0);
    extern s32  func_80029D3C(void);
    extern s32 func_8014CB7C(void);
    extern void func_80153C9C(void);
    extern void func_8015173C(s32 *a0);
    extern s32 func_801725CC(u8 *a0);
    extern void func_8014B310(void);
    extern void func_8014B4D4(void *a0);
    extern void func_8014B944(s32 a0, s32 a1, s32 a2);
    extern void func_80146D80(s32 *a0);
    extern void func_801477E8(s32 *a0, s32 a1);
    extern void func_80147324(s32 arg0);
    extern void func_8014BD24(s32 a0, s32 a1);
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
    register u8  *r __asm__("$18") = D_80078E78;     /* $s2 */
    register s32 *q __asm__("$17") = &D_800AE6A8;   /* $s1 */
    register s32 sh16 __asm__("$2");                 /* $v0 */
    u16 uVar3;
    s32 angle;
    s32 v;
    D_80126AE4 = D_80127078;
    D_80127078 = 0;
    D_801151FC = 0;
    if (*(u8 *)(p + 0x54) != 0) {
        if (((p[0x1e] & 1) == 0) || ((p[0x1f] & 0x8000) == 0)) {
            p[0x1e] &= 0xfffe;
            p[0x1f] = 0;
            p[0x20] = 0;
            p[0x21] = 0;
        }
        {
            u8 bVar2 = *(u8 *)(p + 0x54) - 1;
            *(u8 *)(p + 0x54) = bVar2;
            if ((bVar2 & 1) != 0) {
                ((void (*)(void *))func_801470A0)(p);
            }
        }
    }
    uVar3 = p[0x1e];
    if ((uVar3 & 1) == 0) {
        goto L638;
    }
    if (((*(u32 *)(p + 0x1e) & 0x80008000) == 0) || ((q[2] & 0x80ffffff) != 0)) {
        p[0x1e] = uVar3 & 0xfffe;
        p[0x1f] = 0;
        p[0x20] = 0;
        p[0x21] = 0;
        goto L638;
    }
    {
        u16 uVar1 = p[0x1f];
        p[0x1e] = uVar3 & 0xfffe;
        p[0x1f] = uVar1 & 0x7fff;
        if (((uVar1 & 0x4000) == 0) && ((*(u32 *)(p + 0x22) & 1) != 0) &&
            (((s32 (*)(void *))func_8014A454)(p) != 0)) {
            ((void (*)(void *))func_80160368)(p);
            p[0x1f] = 0;
            p[0x20] = 0;
            p[0x21] = 0;
            p[0x1e] &= 0xfffe;
            return;
        }
    }
    if ((func_801619D0(p) != 0) && (((s32 (*)(void *))func_80151880)(p) != 0)) {
        p[0x20] = 0;
        p[0x79] = 0;
        func_800CCF68(p);
    }
    if ((((s32 (*)(void *))func_80161A00)(p) != 0) && (((s32 (*)(void *))func_801518D8)(p) != 0)) {
        func_800CCF58(p);
    }
    if (((s32 (*)(void *))func_80161A30)(p) != 0) {
        p[0xe4] = 0;
    }
    if (((s32 (*)(void *))func_80161A60)(p) != 0) {
        p[0xe4] = 0;
    }
    if (((u32)(p[0] - 0x19) < 2) ||
        ((*(u32 *)(p + 0xfc) != 0) && ((*(u32 *)(p + 0xfc) & 0x2000000) == 0))) {
        goto L620;
    }
    p[0x78] = p[0x1f];
    p[0x79] = p[0x20];
    p[0x7a] = p[0x21];
    func_801599A4(p);
    ((void (*)(void *))func_801607B8)(p);
    ((void (*)(void *))func_80147084)(p);
    {
        u16 t = p[0x1f];
        register s32 cmp79 __asm__("$4");
        *(u8 *)(p + 0x54) = 0;
        ((s8 *)p)[0xdd] = (s8)t;
        if (((t & 0xff) != 0x11) && ((cmp79 = *(s16 *)(p + 0x79)) != 1000)) {
            angle = func_80029D3C();
            p[0x79] = angle;
            if (r[0x49] == 5) {
                sh16 = angle << 16;
            } else {
                if (func_8014CB7C() == 0) {
                    goto LAB_8015152c;
                }
                sh16 = p[0x79] << 16;
            }
            p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1);
        }
    }
LAB_8015152c:
    func_80153C9C();
    func_8015173C(p);
    ((void (*)(void *))func_801725CC)(p);
    if ((p[0x1f] & 0x2000) != 0) {
        ((void (*)(void *))func_8014B310)(p);
    }
    if ((p[0x1f] & 0x1000) != 0) {
        func_8014B4D4(p);
    }
    if ((p[0x1f] & 0x800) != 0) {
        ((void (*)(void *, s32, s32))func_8014B944)(p, 0x50000, 1);
    }
    if ((p[0x1f] & 0x400) != 0) {
        ((void (*)(void *))func_80146D80)(p);
        ((void (*)(void *, s32))func_801477E8)(p, 0);
    }
    if (((s32 (*)(void *))func_80151880)(p) == 2) {
        func_80147324(0x676);
    }
    if (r[0x49] == 0x14) {
        ((void (*)(void *, s32))func_8014BD24)(p, 10);
        func_8014ACE8(p, 4, 10);
    }
    D_80127518 = D_80126AE4;
    v = D_80126AE4;
    goto L640;
L620:
    p[0x1f] = 0;
    p[0x20] = 0;
    p[0x21] = 0;
    p[0x1e] &= 0xfffe;
L638:
    v = D_80127518;
L640:
    D_801151FC = v;
}
