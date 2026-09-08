/* func_80182894 — shared body (overlay slot 0x80128158, h_exact d93adf00). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern Blk8 D_801E6C7C;
extern s32 D_8018EAE8;
extern s32 D_8018ECF0;
extern s32 func_80171CC4(void *a0, void *a1);
extern void func_8014BB0C(void);
extern void func_8014BDC8(void);
extern void func_8014BEC0(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154B4C(u8 *a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80182894(void *a0) {
    Blk8 buffer;
    s32 *v0;
    buffer = D_801E6C7C;
    if (func_80171CC4(a0, (void *)&buffer)) {
        func_8014BB0C();
        func_8014BDC8();
        ((void (*)(void *))func_8014BEC0)(a0);
        v0 = (s32 *)a0;
        func_80154274(v0, (s32)&D_8018EAE8);
        func_80154B4C((u8 *)a0, (s32)&D_8018ECF0);
        func_80146A6C(0x18, a0, 0, 0, 0, 0, 0);
        *(u8 *)((s32)a0 + 0x4D) += 1;
        *(u8 *)((s32)a0 + 0x214) += 1;
    }
}
