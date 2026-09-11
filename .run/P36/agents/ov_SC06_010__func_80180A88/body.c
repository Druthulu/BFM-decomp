s32 func_80180A88(void)
{
    switch (D_801B2BF4) {
    case 0:
        func_8013C0F8(D_801968BC);
        ((void (*)(void *))func_8017CA80)(D_801B2578);
        D_801B2594 = -0x480;
        D_801B2598 = 0x5F0;
        D_801B25CC += 0x700;
        func_8013C0F8(D_80197BE0);
        ((void (*)(void *))func_8017CA80)(D_801B25D0);
        D_801B25EC = -0x480;
        D_801B25F0 = 0x5F0;
        D_801B2624 += 0x700;
        func_8013C0F8(D_80199164);
        ((void (*)(void *))func_8017CA80)(D_801B2628);
        D_801B2644 = -0x480;
        D_801B2648 = 0x5F0;
        D_801B267C += 0x700;
        func_8013C0F8(D_8019A9D8);
        ((void (*)(void *))func_8017CA80)(D_801B2680);
        D_801B269C = -0x480;
        D_801B26A0 = 0x5F0;
        D_801B26D4 += 0x700;
        func_8013C0F8(D_8019C68C);
        ((void (*)(void *))func_8017CA80)(D_801B26D8);
        D_801B26F4 = -0x480;
        D_801B26F8 = 0x5F0;
        D_801B272C += 0x700;
        func_8013C0F8(D_8019F570);
        ((void (*)(void *))func_8017CA80)(D_801B2730);
        D_801B274C = -0x480;
        D_801B2750 = 0x5F0;
        D_801B2784 += 0x700;
        func_8013C0F8(D_801A0044);
        ((void (*)(void *))func_8017CA80)(D_801B2788);
        D_801B27A4 = -0x480;
        D_801B27A8 = 0x5F0;
        D_801B27DC += 0x700;
        func_8013C0F8(D_801A0A18);
        ((void (*)(void *))func_8017CA80)(D_801B27E0);
        D_801B27FC = -0x480;
        D_801B2800 = 0x5F0;
        D_801B2834 += 0x700;
        func_8013C0F8(D_801A13EC);
        ((void (*)(void *))func_8017CA80)(D_801B2838);
        D_801B2854 = -0x480;
        D_801B2858 = 0x5F0;
        D_801B288C += 0x700;
        func_8013C0F8(D_801A1FC0);
        ((void (*)(void *))func_8017CA80)(D_801B2890);
        D_801B28AC = -0x480;
        D_801B28B0 = 0x5F0;
        D_801B28E4 += 0x700;
        func_8013C0F8(D_801A2C24);
        ((void (*)(void *))func_8017CA80)(D_801B28E8);
        D_801B2904 = -0x480;
        D_801B2908 = 0x5F0;
        D_801B293C += 0xB00;
        func_8013C0F8(D_801A3B38);
        ((void (*)(void *))func_8017CA80)(D_801B2940);
        D_801B295C = -0x480;
        D_801B2960 = 0x5F0;
        D_801B2994 += 0x700;
        D_801B2BF4++;
        break;
    case 1:
        /* one block-scoped `p` per object: each dies once, so local-alloc takes it (into $s0) before
         * the shared &D_801B2C10 pseudo; a single function-scope `p` dies 12 times and loses $s0. */
        {
            s16 *p = &D_801B25CC;
            s32 *obj;

            *p = func_8017F098(0) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801968BC, (s32)obj);
        }
        {
            s16 *p = &D_801B2624;
            s32 *obj;

            *p = func_8017F098(1) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_80197BE0, (s32)obj);
        }
        {
            s16 *p = &D_801B267C;
            s32 *obj;

            *p = func_8017F098(2) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_80199164, (s32)obj);
        }
        {
            s16 *p = &D_801B26D4;
            s32 *obj;

            *p = func_8017F098(3) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_8019A9D8, (s32)obj);
        }
        {
            s16 *p = &D_801B272C;
            s32 *obj;

            *p = func_8017F098(4) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_8019C68C, (s32)obj);
        }
        {
            s16 *p = &D_801B2784;
            s32 *obj;

            *p = func_8017F098(5) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_8019F570, (s32)obj);
        }
        {
            s16 *p = &D_801B27DC;
            s32 *obj;

            *p = func_8017F098(6) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A0044, (s32)obj);
        }
        {
            s16 *p = &D_801B2834;
            s32 *obj;

            *p = func_8017F098(7) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A0A18, (s32)obj);
        }
        {
            s16 *p = &D_801B288C;
            s32 *obj;

            *p = func_8017F098(8) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A13EC, (s32)obj);
        }
        {
            s16 *p = &D_801B28E4;
            s32 *obj;

            *p = func_8017F098(9) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A1FC0, (s32)obj);
        }
        {
            s16 *p = &D_801B293C;
            s32 *obj;

            *p = func_8017F098(0xA) + 0xB00;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A2C24, (s32)obj);
        }
        {
            s16 *p = &D_801B2994;
            s32 *obj;

            *p = func_8017F098(0xB) + 0x700;
            func_80049CAC((s32)(p - 2), (s32)(p - 0x28));
            obj = (s32 *)(p - 0x2A);
            *obj = 0;
            func_8017CAD4((s32 *)D_801B2C10, (s32 *)D_801A3B38, (s32)obj);
        }
        break;
    }
}
