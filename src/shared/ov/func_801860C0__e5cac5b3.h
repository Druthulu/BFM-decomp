/* func_801860C0 — shared body (overlay slot 0x80128158, h_exact e5cac5b3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern s32 D_801B8A2C;
void func_801860C0(void *a0)
{
    s32 v0;
    u16 v0_2;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(void *))func_8012CAE4)(a0);
    } else {
        ((void (*)(s32, s32))func_8001C214)(v0, 0);
        *(s32 *)((u8 *)a0 + 0x58) = (s32)&D_801B8A2C | 0x40000000;
        v0_2 = *(u16 *)((u8 *)a0 + 0x2);
        *(u16 *)((u8 *)a0 + 0x34) = 0;
        *(s32 *)((u8 *)a0 + 0x1C) = 0;
        *(u16 *)((u8 *)a0 + 0x5C) = 0x800;
        *(u16 *)((u8 *)a0 + 0x2) = v0_2 + 1;
    }
}
