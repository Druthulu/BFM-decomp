/* func_8012CC88 — shared body (overlay slot 0x80128158, h_exact b65d6403). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
s32 func_8012CC88(s32 a0, s32 a1, s32 a2) {
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;
    sp10.vx = *(u16*)(a0 + 0x3A);
    sp10.vy = *(u16*)(a0 + 0x3E);
    sp10.vz = *(u16*)(a0 + 0x42);
    sp10.vx += *(u16*)(a2 + 0);
    sp10.vy += *(u16*)(a2 + 2);
    sp10.vz += *(u16*)(a2 + 4);
    *(s32*)(a0 + 0x10) += *(s32*)(a0 + 0x44);
    *(s32*)(a0 + 0x14) += *(s32*)(a0 + 0x48);
    *(s32*)(a0 + 0x18) += *(s32*)(a0 + 0x4C);
    *(s32*)(a0 + 0x04) += *(s32*)(a0 + 0x10);
    *(s32*)(a0 + 0x08) += *(s32*)(a0 + 0x14);
    *(s32*)(a0 + 0x0C) += *(s32*)(a0 + 0x18);
    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a2 + 0);
    sp18.vy += *(u16*)(a2 + 2);
    sp18.vz += *(u16*)(a2 + 4);
    v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, a1);
    sp18.vx -= *(u16*)(a2 + 0);
    sp18.vy -= *(u16*)(a2 + 2);
    sp18.vz -= *(u16*)(a2 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;
    if (v0 & 0x6000) {
        *(s32*)(a0 + 0x14) = 0;
    }
    return v0;
}
