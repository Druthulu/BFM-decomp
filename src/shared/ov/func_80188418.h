/* func_80188418 — shared body (overlay slot 0x80128158, h_exact cd77976e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_80187674(s32 a0);
void func_80188418(s32 a0)
{
    short cnt;
    s32 v1;
    *(short *)(a0 + 0x2) = 0x11;
    cnt = *(unsigned short *)(a0 + 0x70) + 1;
    *(unsigned short *)(a0 + 0x70) = cnt;
    if (cnt < 0x17) {
        v1 = func_8012C658(0x1EA, cnt, a0);
        if (v1 != 0) {
            *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            *(s32 *)(a0 + 0x6C) = v1;
            *(unsigned short *)(v1 + 0x108) = (*(unsigned short *)(a0 + 0x70) - 0x11) << 9;
        }
    }
    cnt = *(unsigned short *)(a0 + 0x70) - 1;
    *(unsigned short *)(a0 + 0x70) = cnt;
    func_80187674(a0);
}
