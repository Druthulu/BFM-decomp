/* func_80178D40 — shared body (overlay slot 0x80128158, h_exact 7a0f8b4c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_80178D40(s32 arg0, s32 arg1)
{
    extern void func_80179B28(s32);
    extern s32 func_80137614(s32 a0, s32 a1, s32 a2);
    extern void func_8012F214(void *, void *, void *);
    extern void func_8012F40C(void *, void *);
    extern void func_80179D30(void *);
    extern void func_80179D78(void *);
    extern void func_80179EA0(void *);
    extern void func_80179DCC(s32);
    extern void func_80179DF8(void);
    extern void func_80179E1C(s32);
    extern void func_80179E48(s32);
    extern void func_80179E74(s32);
    extern void func_80179EE8(s32);
    extern void func_80179F14(s32, s32);
    extern void func_80179F44(void);
    extern void func_80179F6C(s32);
    extern void func_80179F98(s32);
    extern void func_80179FEC(s32);
    extern void func_8017A040(s32);
    extern void func_8017A094(s32);
    extern void func_8017A0C4(s32);
    extern void func_8017A0F4(void);
    extern void func_8017A11C(void);
    extern void func_8017A144(s32);
    extern void func_8017A180(void);
    extern void func_8017A1A8(void);
    extern void func_8017A1D0(void);
    extern void func_8017A1F8(void);
    extern void func_8017A220(void);
    extern void func_8017A248(void);
    extern void func_8017A270(void);
    extern void func_8017A298(void);
    extern void func_8017A2C0(void);
    extern void func_8017A2E8(void);
    extern void func_8017A310(void);
    extern void func_8017A338(void);
    extern void func_8017A360(void);
    extern void func_8017A388(void);
    extern void func_8017A3B0(void);
    extern void func_8017A3D8(void);
    extern void func_8017AD0C(s32);
    extern void func_8017B238(void *, s32);
    extern void func_8017B614(void *, s32);
    extern void func_8017B7A8(void *);
    extern void func_8017B824(void);
    extern void func_8017B880(void);
    extern void func_8017B940(void *);
    extern void func_8017BA3C(void *, s32);
    extern void func_8017BB34(void *, s32);
    extern void func_8012A828(void *, s32);
    extern s32 func_8012B8A4(void *);
    extern void func_8012E88C(void *);
    extern void func_8012E8A8(void *);
    extern void func_8001AAD0(s32, s32);
    extern s32 D_8018F504;
    extern s32 D_8018F918;
    extern s16 D_8018F91C;
    extern s16 D_8018F920;
    extern s16 D_8018F924;
    extern s16 D_8018F928;
    extern s32 D_8018F930;
    extern s32 D_8018F934;
    extern s32 D_8018F944;
    extern s16 D_8018F948;
    extern s16 D_8018F94C;
    extern s32 D_8018F950;
    extern s32 D_8018F958;
    extern s32 D_8018F95C[10];
    extern s32 D_8018F9C8;
    extern s16 D_8018FA80;
    extern s32 D_8018FAAC;


    SV3_80178D40 v10, v18, v20, v28, v30, v38, v40, v48;
    s32 out50[2];
    SV3_80178D40 v58, v60;
    Actor_80178D40 *pv = &(*(Actor_80178D40*)&D_80126B58);
    s32 i5b, i5c, fp5b, fp5c;
    s32 *q5b, *q5c, *p5c, *r5c;
    s16 *g = &D_8018FA80;

    switch (((Cmd_80178D40 *)arg1)->op) {
    case 1:
        func_80179B28(D_8018F918);
        D_8018F918 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_8018F924, D_8018F928 ? 0x48 : 0x40);
        (*(s16*)&D_8018FB24) = 2;
        break;
    case 0:
        func_80179B28(D_8018F918);
        D_8018F918 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_8018F91C, D_8018F920 ? 0x48 : 0x40);
        (*(s16*)&D_8018FB24) = 1;
        break;
    case 0x45:
        ((void (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0));
        if (D_8018F9C8 != 0) {
            func_80179B28(D_8018F918);
            D_8018F918 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[1], D_8018F91C, D_8018F920 ? 0x48 : 0x40);
            (*(s16*)&D_8018FB24) = 1;
        } else {
            (*(s16*)&D_8018FB24) = 3;
        }
        break;
    case 0x32:
        func_80179B28(D_8018F918);
        D_8018F918 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w], D_8018F91C,
                                   D_8018F920 ? 0x48 : 0x40);
        (*(s16*)&D_8018FB24) = 1;
        break;
    case 2:
        func_80179B28(D_8018F918);
        if (D_8018F930 != 0) {
            D_8018F500 = D_8018F930;
            D_8018F930 = 0;
            (*(s16*)&D_8018FB24) = 3;
            return;
        }
        (*(s16*)&D_8018FB24) = 6;
        break;
    case 6:
        func_80179DF8();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 3:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179D30(&v10);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 4:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x4C:
        func_80179D78((void *)((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x4D:
        v10.vx = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f0;
        v10.vy = 0;
        v10.vz = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f4;
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        v18.pad = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f6;
        func_80179D78(&v18);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x15:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0)->unkD4, &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 5:
        func_80179DCC(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 7:
        func_80179E1C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 8:
        func_80179E74(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 9:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179EA0(&v10);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0xA:
        v10.vx = ((Actor_80178D40 *)arg0)->unk6;
        v10.vy = ((Actor_80178D40 *)arg0)->unkA;
        v10.vz = ((Actor_80178D40 *)arg0)->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x16: {
        Actor_80178D40 *p = ((Actor_80178D40 *)arg0)->unkD4;
        v10.vx = p->unk6;
        v10.vy = p->unkA;
        v10.vz = p->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_8018FB24) = 3;
        break;
    }
    case 0xB:
        func_8017A0F4();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0xC:
        func_8017A11C();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0xD:
        func_8017A180();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0xE:
        func_8017A1A8();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x10:
        func_8017A1D0();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x46:
        func_8017A1F8();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x59:
        func_8017A220();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x5A:
        func_8017A248();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x49:
        func_8017A144(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x47:
        func_8017A270();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x17:
        func_80179EE8(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x18:
        func_80179F14(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x19:
        func_80179F6C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x1A:
        func_80179F98(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x51:
        func_8017A040(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x1B:
        D_8018F950 = ((Cmd_80178D40 *)arg1)->a.w;
        func_80179F44();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x1C:
        func_8017A338();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x52:
        func_8017A360();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x1D:
        func_8017A388();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x3B:
        func_8017A094(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x3C:
        func_8017A0C4(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0xF:
    case 0x3F:
        (*(s16*)&D_8018FB24) = 4;
        D_8018F504 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3E:
        (*(s16*)&D_8018FB24) = 5;
        D_8018F944 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x40:
        D_8018F944 = (s32)func_8017A3B0;
        (*(s16*)&D_8018FB24) = 5;
        break;
    case 0x23:
        func_8012A828(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x31:
        func_8012A828(((Actor_80178D40 *)arg0), ((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x24:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unk20->unk12 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x25:
        g[0] = 1;
        g[2] = ((Actor_80178D40 *)arg0)->unk20->unk12 + ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_8018FB24) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x48:
        g[0] = 1;
        g[2] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_8018FB24) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x26:
        g[0] = 1;
        g[2] = func_8012B8A4(((Actor_80178D40 *)arg0));
        g[1] = 0x1E;
        (*(s16*)&D_8018FB24) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3D:
        ((void(*)(void *, s32))func_8012E8E0)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x27:
        g[0] = 2;
        g[4] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8018FB24) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x4F:
        g[5] = 1;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8018FB24) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        /* fallthrough */
    case 0x28:
        g[5] = 0;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_8018FB24) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        break;
    case 0x29:
        v20.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v20.vy = ((Actor_80178D40 *)arg0)->unkA;
        v20.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v20, &v28);
        g[5] = 0;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v28;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x50:
        v30.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v30.vy = ((Actor_80178D40 *)arg0)->unkA;
        v30.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v30, &v38);
        g[5] = 1;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v38;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x2A:
        g[0] = 4;
        (*(s16*)&D_8018FB24) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x1E:
        func_8017B238(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x21:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_8018F934);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x54:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_8018F934);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x1F:
        func_8017B614(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x22:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_8018F934);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x55:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_8018F934);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x20:
        func_8017B7A8(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x4E:
        D_8018F958 = ((Cmd_80178D40 *)arg1)->a.w;
        func_8017B940(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x57:
        func_8017B824();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x58:
        func_8017B880();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x2B:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unk2 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2C:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unk34 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2D:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unkD8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2F:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unk10A = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2E:
        (*(s16*)&D_8018FB24) = 3;
        ((Actor_80178D40 *)arg0)->unkF8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x11:
        func_8017A298();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x12:
        func_8017A2C0();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x13:
        func_8017A2E8();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x14:
        func_8017A310();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x33: {
        void (*f)(Actor_80178D40 *) = (void (*)(Actor_80178D40 *))((Cmd_80178D40 *)arg1)->a.w;
        D_8018FAAC = (s32)&((Cmd_80178D40 *)arg1)[1];
        f(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8018FB24) = 3;
        break;
    }
    case 0x30:
        if (((Cmd_80178D40 *)arg1)->a.w == 0) {
            func_8012E8A8(((Actor_80178D40 *)arg0));
            (*(s16*)&D_8018FB24) = 3;
        } else {
            func_8012E88C(((Actor_80178D40 *)arg0));
            (*(s16*)&D_8018FB24) = 3;
        }
        break;
    case 0x4A:
        ((void(*)())func_80175414)();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x4B:
        func_80175454();
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x34:
        (*(s16*)&D_8018FB24) = 3;
        D_8018F500 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x35:
        D_8018F930 = (s32)&((Cmd_80178D40 *)arg1)[1];
        (*(s16*)&D_8018FB24) = 3;
        D_8018F500 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x36:
        (*(s16*)&D_8018FB24) = 3;
        D_8018F500 += 8;
        if (((s32 (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0)) == 0) {
            break;
        }
        D_8018F500 = *(s32 *)(D_8018F500 + 4);
        return;
    case 0x37:
        (*(s16*)&D_8018FB24) = 3;
        D_8018F91C = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_8018F920 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x38:
        (*(s16*)&D_8018FB24) = 3;
        D_8018F924 = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_8018F928 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x39: {
        s32 w1, w2;
        v40.vx = ((Actor_80178D40 *)arg0)->unk6;
        v40.vy = ((Actor_80178D40 *)arg0)->unkA;
        v40.vz = ((Actor_80178D40 *)arg0)->unkE;
        v48.vx = pv->unk6;
        v48.vy = pv->unkA;
        v48.vz = pv->unkE;
        func_8012F40C(out50, &v40);
        w1 = out50[0];
        func_8012F40C(out50, &v48);
        w2 = out50[0];
        (*(s16*)&D_8018FB24) = 3;
        D_8018F91C = w1;
        D_8018F920 = (s16)w1 >= (s16)w2;
        break;
    }
    case 0x3A: {
        s32 w1, w2;
        v58.vx = ((Actor_80178D40 *)arg0)->unk6;
        v58.vy = ((Actor_80178D40 *)arg0)->unkA;
        v58.vz = ((Actor_80178D40 *)arg0)->unkE;
        v60.vx = pv->unk6;
        v60.vy = pv->unkA;
        v60.vz = pv->unkE;
        func_8012F40C(out50, &v58);
        w1 = out50[0];
        func_8012F40C(out50, &v60);
        w2 = out50[0];
        (*(s16*)&D_8018FB24) = 3;
        D_8018F924 = w2;
        D_8018F928 = (s16)w1 < (s16)w2;
        break;
    }
    case 0x41:
        ((void(*)(s32, s32))func_8002D4C8)(((Cmd_80178D40 *)arg1)->a.uh[0], ((Cmd_80178D40 *)arg1)->a.uh[1]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x42:
        func_8017AD0C(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x43:
        D_8018F944 = (s32)func_8017A3D8;
        D_8018F94C = 0;
        (*(s16*)&D_8018FB24) = 5;
        D_8018F948 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x44:
        func_8001AAD0(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x53:
        func_80179E48(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x56:
        func_80179FEC(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_8018FB24) = 3;
        break;
    L5B_found:
        fp5b = ((Cmd_80178D40 *)arg1)->a.w;
        *q5b = fp5b;
        ((void (*)(Actor_80178D40 *))fp5b)(((Actor_80178D40 *)arg0));
        (*(s16*)&D_8018FB24) = 3;
        break;
    case 0x5B:
        i5b = 0;
        q5b = D_8018F95C;
        do {
            i5b++;
            if (*q5b == 0) {
                goto L5B_found;
            }
            q5b++;
        } while (i5b < 10);
        (*(s16*)&D_8018FB24) = 3;
        break;
    L5C_found1:
        *q5c = 0;
        goto L5C_join;
    case 0x5C:
        i5c = 0;
        if (((Cmd_80178D40 *)arg1)->a.w != 0) {
            fp5c = ((Cmd_80178D40 *)arg1)->a.w;
            q5c = D_8018F95C;
            do {
                if (*q5c == fp5c) {
                    goto L5C_found1;
                }
                i5c++;
                q5c++;
            } while (i5c < 10);
        L5C_join:
            if (i5c != 10) {
                (*(s16*)&D_8018FB24) = 3;
                break;
            }
            i5c = 0;
            do {
                p5c = &D_8018F95C[i5c];
                if (*p5c != 0) {
                    goto L5C_found2;
                }
                i5c++;
            } while (i5c < 10);
            (*(s16*)&D_8018FB24) = 3;
            break;
        L5C_found2:
            *p5c = 0;
            goto L5D;
        }
        r5c = D_8018F95C;
        do {
            i5c++;
            if (*r5c != 0) {
                *r5c = 0;
                goto L5D;
            }
            r5c++;
        } while (i5c < 10);
        /* fallthrough */
    case 0x5D:
    L5D:
        (*(s16*)&D_8018FB24) = 3;
        break;
    default:
        break;
    }
Lend:
    D_8018F500 += 8;
}
