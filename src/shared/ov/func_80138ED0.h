/* func_80138ED0 — shared body (overlay slot 0x80128158, h_exact 241c3964). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8013914C(s32 a0, s32 a1);
extern void func_800599B8(u16 *);
extern u16 D_80127C0C[];
extern s32 D_80127548[];
s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3)
{
    u16 local[4];
    u16 uVar1;
    s32 result;
    u16 uVar4;
    u8 *pbVar7;
    u8 *pb;
    u16 *base;
    u16 *p;
    s32 iVar2;
    u32 s0acc;
    u32 tmp;
    s32 shift;
    pb = param_3;
    uVar1 = *(u8 *)(param_1 + 0x23) & 0xf;
    result = ((s32 (*)(u8 *, u16 *))func_8013914C)(param_1, local);
    if (result != 0) {
        return 1;
    }
    uVar4 = local[0] - *(u16 *)(param_1 + 0x38);
    pbVar7 = pb + (param_2 & 0xffff) * 0xc;
    base = D_80127C0C + uVar4;
    iVar2 = 0;
    if (uVar4 % 3 != 0) {
        u32 pv = uVar1;
        p = base;
        do {
            shift = 6;
            do {
                tmp = (s0acc & 0xffff) << 4;
                s0acc = tmp | pv;
                if ((((s32)*pbVar7 >> shift) & 1) == 0) {
                    s0acc = tmp;
                }
                shift++;
            } while (shift < 8);
            *p = *p | (s0acc << 8);
            p++;
            shift = 2;
            do {
                tmp = (s0acc & 0xffff) << 4;
                s0acc = tmp | pv;
                if ((((s32)*pbVar7 >> shift) & 1) == 0) {
                    s0acc = tmp;
                }
                shift++;
            } while (shift < 6);
            *p = s0acc;
            p += 0x35;
            iVar2++;
            pbVar7++;
        } while (iVar2 < 0xc);
        iVar2 = 0;
    } else {
        u32 pv = uVar1;
        p = base;
        do {
            shift = 4;
            do {
                tmp = (s0acc & 0xffff) << 4;
                s0acc = tmp | pv;
                if ((((s32)*pbVar7 >> shift) & 1) == 0) {
                    s0acc = tmp;
                }
                shift++;
            } while (shift < 8);
            *p = s0acc;
            p++;
            shift = 2;
            do {
                tmp = (s0acc & 0xffff) << 4;
                s0acc = tmp | pv;
                if ((((s32)*pbVar7 >> shift) & 1) == 0) {
                    s0acc = tmp;
                }
                shift++;
            } while (shift < 4);
            *p = s0acc & 0xff;
            p += 0x35;
            iVar2++;
            pbVar7++;
        } while (iVar2 < 0xc);
        iVar2 = 0;
    }
    {
        u16 *src = base;
        s32 dcount;
        s32 df;
        s32 decoy;
        s32 c36;
        u16 tv;
        register s32 *dp __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
        register u16 *ba __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B headers1)
        dp = D_80127548;
        dcount = *dp;
        c36 = 0x24;
        __asm__ ("" : : "r"(c36), "r"(dcount));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
        df = c36 - dcount;
        tmp = (df << 1) + df;
        tmp = tmp << 4;
        dp = dp + 1;
        ba = (u16 *)(tmp + (u8 *)dp);
        __asm__ ("" : "=r"(decoy) : "r"(ba));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B headers1)
        __asm__ ("" : : "r"(decoy));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
        {
            register u16 *dst __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
            dst = ba;
            do {
                tv = *src; src++;
                *dst = tv; dst++;
                tv = *src; src += 0x35;
                *dst = tv; dst++;
                iVar2++;
            } while (iVar2 < 0xc);
        }
    }
    local[2] = 2;
    local[3] = 0xc;
    func_800599B8(local);
    return 0;
}
