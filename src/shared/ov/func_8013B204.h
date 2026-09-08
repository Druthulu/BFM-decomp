/* func_8013B204 — shared body (overlay slot 0x80128158, h_exact 13888a34). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8013B274(s32 a0, s32 a1, void *a2);
extern short D_800B9A02;
extern s32 D_800A651C;
void func_8013B204(s32 a0, s32 a1)
{
    void *a2;
    s32 idx;
    a2 = a1;
    if (*(s16 *)((u8 *)a2 + 0xC) != 0) {
        return;
    }
    if (*(s16 *)a2 != 2) {
        return;
    }
    a2 = (u8 *)a2 + 8;
    idx = (u16)D_800B9A02;
    func_8013B274(
        (&D_800A651C)[idx * 5] + ((u16)(*(u16 *)((u8 *)a0 + 0x1A)) << 2),
        *(s16 *)((u8 *)a0 + 0x1C),
        a2);
}
