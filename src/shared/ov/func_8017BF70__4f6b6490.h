/* func_8017BF70 — shared body (overlay slot 0x80128158, h_exact 4f6b6490). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8*);
void func_8017BF70(void *arg0) {
    s32 p;
    s32 q;
    *(s32 *)((u8 *)arg0 + 0x208) += 0x1c000;
    p = *(s32 *)((u8 *)arg0 + 0x20);
    *(u16 *)((u8 *)p + 0x10) = (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x20A)) & 0xfff;
    q = *(s32 *)((u8 *)arg0 + 0x20);
    if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
        *(u16 *)((u8 *)q + 0x10) = 0xc00;
        *(u16 *)((u8 *)arg0 + 0xb8) = 1;
        ((void (*)(void *))func_80171A1C)(arg0);
    }
}
