/* func_8017AD0C — shared body (overlay slot 0x80128158, h_exact ef683a34). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void MoveImage(void *a0, s32 a1, s32 a2);
s32 func_8017AD0C(s32 arg0)
{
    Rect rect;
    s32 var_v0;
    s32 var_v1;
    arg0 = arg0 - 1;
    rect.x = ((arg0 & 3) * 0x10) + 0x280;
    var_v0 = arg0;
    if (arg0 < 0) {
        var_v0 = arg0 + 3;
    }
    rect.y = (var_v0 >> 2) + 0x1F8;
    rect.w = 0x10;
    rect.h = 1;
    MoveImage(&rect, 0x160, 0x1C9);
    if (arg0 == 0x18) {
        rect.x = 0x2C0;
        rect.y = 0x1D0;
    } else {
        rect.x = ((arg0 & 7) * 8) + 0x280;
        var_v1 = arg0;
        if (arg0 < 0) {
            var_v1 = arg0 + 7;
        }
        rect.y = (var_v1 >> 3) * 0x28 + 0x180;
    }
    rect.w = 0x20;
    do { rect.h = 0x28; } while (0);
    MoveImage(&rect, 0x1C8, 0x190);
}
