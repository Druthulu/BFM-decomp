void func_801A4ACC(void *a0)
{
    register s32 *s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 s1 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus9)
    s32 *s2;
    s32 v0;
    s32 v1;
    s32 a0_;
    s32 a1;
    s32 a2;

    s0 = (s32 *)a0;
    v1 = *(u16 *)((s32)s0 + 0x34);
    s1 = *(s32 *)((s32)s0 + 0xCC);
    if ((u32)v1 >= 5) {
        goto end;
    }

    switch (v1) {
    case 0:
        v0 = *(s16 *)((s32)s0 + 0x70);
        if (v0 != 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        v0 = *(u16 *)&D_801F888C;
        v1 = *(u16 *)&D_801F888E;
        v0 |= v1;
        if (v0 != 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        func_80132288(s2, &D_801B00EC, D_801B75EC);
        if (s1 == 0) {
            a0_ = 4;
        } else {
            func_80132288(&D_801F8898, &D_801B00FC, *(s32 *)D_801B80FC);
            a0_ = 4;
        }
        func_8002D4C8(a0_, 0xABE);
        goto inc;
    case 1:
        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        v0 = D_801F8894;
        v0 &= 0x4000;
        if (v0 == 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        func_80132288(s2, &D_801B010C, D_801B75EC);
        if (s1 == 0) {
            goto inc;
        }
        a0_ = (s32)&D_801F8898;
        a2 = *(s32 *)D_801B80FC;
        a1 = (s32)&D_801B011C;
        goto cb4;
    case 2:
        s2 = &D_801F8888;
        func_8013240C((s32)s2);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        v0 = D_801F8894;
        v0 &= 0x4000;
        if (v0 == 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        func_80132288(s2, &D_801B012C, D_801B75EC);
        if (s1 == 0) {
            goto inc;
        }
        a0_ = (s32)&D_801F8898;
        a2 = *(s32 *)D_801B80FC;
        a1 = (s32)&D_801B013C;
    cb4:
        func_80132288((s32 *)a0_, (s32 *)a1, a2);
    inc:
        v0 = *(u16 *)((s32)s0 + 0x34);
        v0 += 1;
        *(u16 *)((s32)s0 + 0x34) = v0;
        goto end;
    case 3:
        func_8013240C((s32)&D_801F8888);
        if (s1 != 0) {
            func_8013240C((s32)&D_801F8898);
        }
        v0 = D_801F8894;
        v0 &= 0x4000;
        if (v0 == 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        v0 = *(u16 *)((s32)s0 + 0x34);
        v1 = *(s32 *)((s32)s0 + 0x6C);
        *(u16 *)((s32)s0 + 0x34) = v0 + 1;
        if (v1 == 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        *(u16 *)(v1 + 0x34) = 4;
        a0_ = (s32)s0;
        goto e58;
    case 4:
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x1A);
        v0 -= 0x80;
        *(u16 *)(v1 + 0x1A) = v0;
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x1A);
        *(u16 *)(v1 + 0x1C) = v0;
        v0 = *(s16 *)((s32)s0 + 0x70);
        if (v0 != 0) {
            goto dec;
        }
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x14);
        v0 -= 0x10;
        *(u16 *)(v1 + 0x14) = v0;
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x1A);
        *(u16 *)(v1 + 0x18) = v0;
        v0 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(s16 *)(v0 + 0x1A);
        if (v0 > 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        v0 = *(s32 *)((s32)s0 + 0x64);
        *(s32 *)(v0 + 0xCC) = 0;
        if (s1 != 0) {
            func_8012C218((void *)s1);
        }
        func_8012C218((void *)s0);
        D_8019FF8A &= 0xFFFD;
        return;
    dec:
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x14);
        v0 += 0x10;
        *(u16 *)(v1 + 0x14) = v0;
        v1 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x1A);
        v0 = -v0;
        *(u16 *)(v1 + 0x18) = v0;
        v0 = *(s32 *)((s32)s0 + 0x20);
        v0 = *(s16 *)(v0 + 0x1A);
        if (v0 > 0) {
            a0_ = (s32)s0;
            goto e58;
        }
        if (s1 != 0) {
            func_8012C218((void *)s1);
        }
        func_8012C218((void *)s0);
        return;
    }

end:
    a0_ = (s32)s0;
e58:
    func_80132784(a0_, *(s32 *)(a0_ + 0x64), 0);
}
