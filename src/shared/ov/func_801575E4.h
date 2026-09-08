/* func_801575E4 — shared body (overlay slot 0x80128158, h_exact 0e84cbe4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80156648(s32 *a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8014B768(s32 a0, s32 a1);
extern void func_80147300(u16 arg0);
extern void func_80146CA0(void *a0);
extern u8 D_800D4F14[];
extern s32 D_8011F730;
void func_801575E4(void *a0) {
    s32 v;
    func_80154A74((s32)a0, 0x15);
    v = *(u8 *)((u8 *)a0 + 0x1AB) ^ 1;
    *(u8 *)((u8 *)a0 + 0x1AB) = v;
    if (v != 0) {
        *(u8 *)((u8 *)a0 + 0x1AA) = 0xA;
    } else {
        *(u8 *)((u8 *)a0 + 0x1AA) = 0xB;
    }
    func_80154274((s32 *)a0, (s32)D_800D4F14);
    func_80147324(0x455);
    func_80146E90((s32 *)a0, 0);
    func_80156648((s32 *)a0);
    func_80146994(0x5, (s32)a0, 0, 0);
    func_8014B768((s32)a0, 0x333);
    func_80147300(0x5F3);
    D_8011F730 |= 4;
    func_80146CA0(a0);
}
