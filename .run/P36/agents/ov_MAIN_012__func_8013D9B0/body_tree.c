void func_8013D9B0(int param_1)
{

    extern void *D_801841A4;
    extern s16 *D_801841AC;
    extern s32 D_801841BC;
    extern s32 D_801841C4;

    u8 buf[0x20];
    s32 uVar13;
    register u16 *psVar14 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus2)
    u16 *psVar15;
    s32 uVar16;
    void *r0;
    u16 *puVar10;
    register u16 *puVar9 __asm__("$10");  // !FAKE: pin $10 — NEEDED DIFFERS (P36 rung B tus2)
    s32 iVar11;
    register s32 iVar12 __asm__("$14");  // !FAKE: pin $14 — NEEDED DIFFERS (P36 rung B tus2)
    u16 sVar4;
    register u32 uVar5 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus2)
    register u32 uVar7 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus2)
    register u32 uVar1 __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus2)
    u32 uVar6;
    register u32 uVar8 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B tus2)
    register u32 uVar3 __asm__("$9");  // !FAKE: pin $9 — NEEDED DIFFERS (P36 rung B tus2)

    psVar15 = (*(u16 * *)&D_801841AC);
    if (psVar15 != 0) {
        sVar4 = *psVar15;
        *(u32 *)(buf + 8) = (*(u32 * *)&D_801841A4)[param_1];
        D_801841C4 = -1;
        uVar16 = 0;
        if (sVar4 != 0xff) {
            r0 = buf + 8;
            psVar14 = psVar15 + 6;
            do {
                iVar11 = 0;
                if (sVar4 == 9) {
                    *(s16 *)(buf + 0) = psVar14[-4];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
                    *(s16 *)(buf + 2) = psVar14[-3];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
                    *(s16 *)(buf + 4) = psVar14[-2];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
                    *(s16 *)(buf + 6) = psVar14[-1];
                    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus2)
                    {
                        register s32 mw __asm__("$3") = (s32)((s16 *)psVar14)[-2];  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus2)
                        s32 mh = (s32)((s16 *)psVar14)[-1];
                        iVar12 = mw * mh;
                    }
                    uVar13 = 0;
                    puVar10 = *(u16 **)psVar14;
                    {
                        register s32 boff __asm__("$2") = iVar12 * 2;  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                        register u16 *pi __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus2)
                        pi = (u16 *)((s32)puVar10 + boff);
                        __asm__ __volatile__("" : "=r"(pi) : "0"(pi));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus2)
                        puVar9 = pi;
                    }
                    if (0 < iVar12) {
                        do {
                            register u32 pix __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                            register u32 out __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                            u32 result;
                            *(u32 *)(buf + 0xc) = (u32)*puVar10;
                            pix = (u32)*puVar9;
                            uVar5 = pix & 0x1f;
                            uVar7 = pix & 0x3e0;
                            uVar1 = pix & 0x7c00;
                            {
                                void *p1;
                                register void *pa __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                                register void *pb __asm__("$12");  // !FAKE: pin $12 — NEEDED DIFFERS (P36 rung B tus2)
                                __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus2)
                                p1 = buf + 0xc;
                                __asm__ __volatile__("" : "=r"(p1) : "0"(p1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus2)
                                gte_ldIR0z();
                                gte_ldrgb(r0);
                                gte_ldIRGB(p1);
                                gte_dpcl();
                                pa = buf + 0x10;
                                __asm__ __volatile__("" : "=r"(pa) : "0"(pa));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus2)
                                pb = pa;
                                gte_stORGB(pb);
                            }
                            out = *(u32 *)(buf + 0x10);
                            uVar6 = out & 0x1f;
                            uVar8 = out & 0x3e0;
                            uVar3 = out & 0x7c00;
                            if (uVar5 != uVar6) {
                                s32 c;
                                uVar13 = 1;
                                if ((s32)uVar5 < (s32)uVar6) uVar5 = uVar5 + 1;
                                c = (s32)uVar6 < (s32)uVar5;
                                if (c) uVar5 = uVar5 - 1;
                            }
                            if (uVar7 != uVar8) {
                                register s32 c __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                                uVar13 = 1;
                                if ((s32)uVar7 < (s32)uVar8) uVar7 = uVar7 + 0x20;
                                c = (s32)uVar8 < (s32)uVar7;
                                if (c) uVar7 = uVar7 - 0x20;
                            }
                            if (uVar1 != uVar3) {
                                register s32 c __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus2)
                                uVar13 = 1;
                                if ((s32)uVar1 < (s32)uVar3) uVar1 = uVar1 + 0x400;
                                c = (s32)uVar3 < (s32)uVar1;
                                if (c) uVar1 = uVar1 - 0x400;
                            }
                            result = uVar5 | uVar7 | uVar1 | (*(u32 *)(buf + 0xc) & 0x8000);
                            if (result == 0 && *(u32 *)(buf + 0xc) != 0) {
                                result = 0x8000;
                            }
                            *puVar9 = (u16)result;
                            puVar9 = puVar9 + 1;
                            iVar11 = iVar11 + 1;
                            puVar10 = puVar10 + 1;
                        } while (iVar11 < iVar12);
                    }
                    if (uVar13 != 0) {
                        ((void (*)(void *))func_800599B8)(buf);
                    }
                    uVar16 = uVar16 | uVar13;
                }
                psVar15 = psVar15 + 8;
                sVar4 = *psVar15;
                psVar14 = psVar14 + 8;
            } while (sVar4 != 0xff);
        }
        D_801841BC = uVar16;
    }
    return;
}
