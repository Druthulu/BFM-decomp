#include "common.h"

INCLUDE_ASM("asm/md_MAIN_031/nonmatchings/md_MAIN_031", func_800CAE0C);

extern s32 func_80029178(s32 arg0);

void func_800CAE74(s32 arg0, s32 arg1, s32 *arg2) {
    s32 base;
    s32 p;
    s32 z;
    s32 *iter;
    s32 s;

    extern void func_800183E0(s32 a0);

    base = *(s32 *)(arg1 + 0xC);
    *(u16 *)(arg1 + 0x2) = *(u16 *)(arg0 + 0x2);
    *(u16 *)(arg1 + 0x4) = *(u16 *)(arg0 + 0x4);
    *(u16 *)(arg1 + 0x6) = *(u16 *)(arg0 + 0x6);
    *(u16 *)(arg1 + 0x8) = *(u16 *)(arg0 + 0x8);
    *(u16 *)(arg1 + 0xA) = *(u16 *)(arg0 + 0xA);
    p = base;
    s = *(s32 *)(arg0 + 0xC);
    do {
        *(u8 *)p = *(u8 *)s;
        p += 1;
        s += 1;
    } while (p < base + 0x1F);
    s = *arg2;
    if (s != 0) {
        iter = arg2;
        z = base;
        do {
            if ((func_80029178(s) & 0xFF) == 0) {
                *(u8 *)z = 0;
                *(u8 *)(z + 1) = 0;
            }
            iter += 1;
            s = *iter;
            z += 2;
        } while (s != 0);
    }
    func_800183E0(arg1);
}




void func_800CAF58(void *a0) {

    extern void (*D_800CBFE4[])(void);
    *(u32 *)((s32)a0 + 0x44) |= 8;
    D_800CBFE4[*(u8 *)((s32)a0 + 0x197)]();
}


extern s32 func_80161104(void);
extern void func_800CAFE4(u8 *a0);
void func_800CAF9C(u8 *a0) {
    if (func_80161104()) {
        func_800CAFE4(a0);
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
    }
}


extern u16 D_801270C0;
extern void func_80154150(s32 a0, s32 a1);
extern void func_801655E4(s32 a0);
extern void func_800183E0(s32 a0);
extern void func_800CAE74();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147324(s32 a0);
extern u8 D_800CC09C[];
extern u8 D_800CBF3C[];
extern u8 D_800CBF7C[];
extern u8 D_800CC0DC[];
extern u8 D_800CBF5C[];
extern u8 D_800CBFA8[];
extern u8 D_800CC05C[];

void func_800CAFE4(u8 *a0) {
    D_801270C0 = 2;
    func_80154150((s32)a0, 3);
    func_801655E4((s32)a0);
    func_800CAE74((void *)&D_800CC09C, (void *)&D_800CBF3C, (void *)&D_800CBF7C);
    func_800CAE74((void *)&D_800CC0DC, (void *)&D_800CBF5C, (void *)&D_800CBFA8);
    func_800183E0((s32)&D_800CC05C);
    *(u16 *)(a0 + 0x234) = 0;
    *(u16 *)(a0 + 0x236) = 0x10;
    *(u32 *)(a0 + 0x238) = 0;
    *(u8 *)(a0 + 0xBE) = 0;
    *(u8 *)(a0 + 0xBF) = 0;
    func_80146E90((s32 *)a0, 0x10);
    func_80147324(0x8EA);
    *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1;
}


extern void func_800CB428();
extern void func_800CB6A0(void *a0, void *a1, void *a2, s32 a3);
extern void func_800CB964(void *a0, void *a1, void *a2);
extern void func_80147324(s32 a0);

void func_800CB0B0(void *arg) {
    u16 sp10[3];
    u16 sp18[3];
    u16 temp;
    u16 cur;
    u8 b;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = 0;
    sp18[0] = *(u16 *)((u8 *)arg + 0x234);
    sp18[2] = *(u16 *)((u8 *)arg + 0x236);
    sp18[1] = sp18[2];
    func_800CB428(arg, sp10, sp18);
    func_800CB6A0(arg, sp10, sp18, 1);
    func_800CB6A0(arg, sp10, sp18, 0);
    func_800CB964(arg, sp10, sp18);
    if (*(s16 *)((u8 *)arg + 0x234) != 0x2000) {
        temp = *(volatile u16 *)((u8 *)arg + 0x238) + 0x100;
        cur = *(volatile u16 *)((u8 *)arg + 0x234) + temp;
        *(u16 *)((u8 *)arg + 0x234) = cur;
        *(u16 *)((u8 *)arg + 0x238) = temp;
        if ((s16)cur >= 0x2001) {
            func_80147324(0x8EB);
            *(u16 *)((u8 *)arg + 0x234) = 0x2000;
        }
    } else {
        temp = *(volatile u16 *)((u8 *)arg + 0x23A) + 0x200;
        cur = *(volatile u16 *)((u8 *)arg + 0x236) + temp;
        *(u16 *)((u8 *)arg + 0x236) = cur;
        *(u16 *)((u8 *)arg + 0x23A) = temp;
        if ((s16)cur >= 0x2001) {
            b = *(u8 *)((u8 *)arg + 0x197);
            *(u16 *)((u8 *)arg + 0x236) = 0x2000;
            *(u8 *)((u8 *)arg + 0x197) = b + 1;
        }
    }
}


extern u16 func_80148800(s32 *a0);
extern void func_80147324(s32 a0);
extern void func_800CB428();
extern void func_800CB6A0(void *a0, void *a1, void *a2, s32 a3);
extern void func_800CB964(void *a0, void *a1, void *a2);

void func_800CB1CC(void *arg0) {
    u16 sp10[3];
    u16 sp18[3];

    if (func_80148800((s32 *) arg0) & 0x20) {
        *(u32 *)((u8 *)arg0 + 0x238) = 0;
        *(u8 *)((u8 *)arg0 + 0x197) = *(u8 *)((u8 *)arg0 + 0x197) + 1;
        func_80147324(0x991);
    }
    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = 0;
    sp18[0] = *(u16 *)((u8 *)arg0 + 0x234);
    sp18[2] = *(u16 *)((u8 *)arg0 + 0x236);
    sp18[1] = sp18[2];
    func_800CB428(arg0, sp10, sp18);
    func_800CB6A0(arg0, sp10, sp18, 1);
    func_800CB6A0(arg0, sp10, sp18, 0);
    func_800CB964(arg0, sp10, sp18);
}


void func_800CB288(s32 arg0)
{
    s16 sp10[3];
    s16 sp18[3];
    u16 temp;
    u16 cur;
    register u16 temp2 __asm__("$2");
    register u16 cur2 __asm__("$3");

    if ((func_80146E98(arg0) == 0) || (!(func_80148800((s32 *) arg0) & 0x20))) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = 0;
        sp18[0] = *(u16 *) (arg0 + 0x234);
        sp18[2] = *(u16 *) (arg0 + 0x236);
        sp18[1] = sp18[2];
        func_800CB428(arg0, sp10, sp18);
        func_800CB6A0(arg0, sp10, sp18, 1);
        func_800CB6A0(arg0, sp10, sp18, 0);
        func_800CB964(arg0, sp10, sp18);
        if (*(s16 *) (arg0 + 0x236) != 0x10) {
            temp = *(volatile u16 *) (arg0 + 0x23A) + 0x100;
            cur = *(volatile u16 *) (arg0 + 0x236) - temp;
            *(u16 *) (arg0 + 0x236) = cur;
            *(u16 *) (arg0 + 0x23A) = temp;
            if ((s16) cur < 0x10) {
                *(u16 *) (arg0 + 0x236) = 0x10;
            }
            return;
        }
        temp2 = *(volatile u16 *) (arg0 + 0x238) + 0x200;
        cur2 = *(volatile u16 *) (arg0 + 0x234) - temp2;
        *(u16 *) (arg0 + 0x234) = cur2;
        *(u16 *) (arg0 + 0x238) = temp2;
        if ((s16) cur2 >= 0) {
            return;
        }
        *(u16 *) (arg0 + 0x234) = 0;
    }
    func_80165A78(arg0);
    func_80159B3C((void *) arg0);
}


extern u16 D_8011F9D0[];
extern u16 D_801270C0;
extern void func_80162CCC(void);

void func_800CB3B4(void) {
    u16 *p;
    s32 i;
    s32 w;

    D_801270C0 = 1;
    i = 0;
    w = 0x17;
    p = D_8011F9D0;
    do {
        if (*p == w) {
            ((void (*)(void *))func_80162CCC)((void *)p);
        }
        i = i + 1;
        p = p + 0x34;
    } while (i < 0x14);
}


void func_800CB428(void *a0) {
    extern u32 func_80029204(s32 arg0);
    extern void func_800CB5C8(void *a0, void *a1);
    extern void func_800183E0(s32 a0);
    extern u8 D_800CC0FC[];
    extern u8 D_800CBF7C[];
    extern u8 D_800CC11C[];
    extern u8 D_800CBFA8[];
    extern u8 D_800CBF3C[];
    extern u8 D_800CBF5C[];
    u16 sp10[3];
    u16 *s0;
    s32 *s1;
    s32 id;
    s32 flag;
    s32 v;

    id = func_80029204(4);
    __asm__("" : "=r"(id) : "0"(id));

    flag = 0;
    s0 = (u16 *)D_800CC0FC;
    s1 = (s32 *)D_800CBF7C;
loop1:
    v = *s1;
    if (v == 0) {
        goto done1;
    }
    if (id == v) {
        sp10[0] = *s0 & 0x1F;
        sp10[1] = (*s0 >> 5) & 0x1F;
        sp10[2] = (*s0 >> 10) & 0x1F;
        func_800CB5C8(sp10, (u8 *)a0 + 0xBE);
        *s0 = ((sp10[2] << 10 | sp10[1] << 5) | sp10[0]) | 0x8000;
        flag = 1;
    }
    s0++;
    s1++;
    if (flag == 0) {
        goto loop1;
    }
done1:
    flag = 0;
    s0 = (u16 *)D_800CC11C;
    s1 = (s32 *)D_800CBFA8;
loop2:
    v = *s1;
    if (v == 0) {
        goto done2;
    }
    if (id == v) {
        sp10[0] = *s0 & 0x1F;
        sp10[1] = (*s0 >> 5) & 0x1F;
        sp10[2] = (*s0 >> 10) & 0x1F;
        func_800CB5C8(sp10, (u8 *)a0 + 0xBF);
        *s0 = ((sp10[2] << 10 | sp10[1] << 5) | sp10[0]) | 0x8000;
        flag = 1;
    }
    s0++;
    s1++;
    if (flag == 0) {
        goto loop2;
    }
done2:
    func_800183E0((s32)&D_800CBF3C);
    func_800183E0((s32)&D_800CBF5C);
}


void func_800CB5C8(s32 arg0, s32 arg1) {
    s32 count = 0;
    s16 t;
    if (*(u8 *)arg1 == 0) {
        (*(u16 *)arg0)++;
        (*(u16 *)((s8 *)arg0 + 2))++;
        count = *(s16 *)arg0 == 31;
        t = ++(*(u16 *)((s8 *)arg0 + 4));
        if (*(s16 *)((s8 *)arg0 + 2) == 31) count++;
        if (t == 31) count++;
    } else {
        (*(u16 *)arg0)--;
        (*(u16 *)((s8 *)arg0 + 2))--;
        t = --(*(u16 *)((s8 *)arg0 + 4));
        if (*(s16 *)arg0 == 0) count = 1;
        if (*(s16 *)((s8 *)arg0 + 2) == 0) count++;
        if (t == 0) count++;
    }
    if (count != 0) *(u8 *)arg1 ^= 1;
}


typedef struct { s16 m[3][4]; } Mat_CB6A0;

#define SETROT_A(p) __asm__ __volatile__( \
    "lw $12, 0(%0)\n" \
    "lw $13, 4(%0)\n" \
    "ctc2 $12, $0\n" \
    "ctc2 $13, $1\n" \
    "lw $12, 8(%0)\n" \
    "lw $13, 12(%0)\n" \
    "lw $14, 16(%0)\n" \
    "ctc2 $12, $2\n" \
    "ctc2 $13, $3\n" \
    "ctc2 $14, $4\n" \
    : : "r"(p) : "$12", "$13", "$14", "memory")

#define LDV_A(p) __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(p) : "memory")

#define MVMVA_A() __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" \
    : : : "memory")

#define STSV_A(p) __asm__ __volatile__( \
    "mfc2 $12, $9\n" \
    "mfc2 $13, $10\n" \
    "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" \
    "sh $13, 2(%0)\n" \
    "sh $14, 4(%0)\n" \
    : : "r"(p) : "$12", "$13", "$14", "memory")

extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80016ED4(void *a0);
extern u16 D_800CBFFC[];
extern u16 D_800CBFF8[];

void func_800CB6A0(void *a0, void *a1, void *a2, s32 a3) {
    s16 mat[4][4];
    u16 vin[3];
    u16 vec[4][4];
    u16 tc[8];
    u8 tail[10];
    register u16 *o0 __asm__("$4");
    u16 *tp;
    s32 idx;
    u16 w;

    idx = a3;
    tp = (u16 *)D_800CBFFC + idx * 4;
    func_80017DC4(a2, mat);
    o0 = &vec[0][0];

    vin[2] = 0;
    vin[0] = *(u16 *)((u8 *)a1 + 0) - 0x30;
    vin[1] = *(u16 *)((u8 *)a1 + 2) - 0x20;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(o0);

    vin[0] = *(u16 *)((u8 *)a1 + 0) + 0x30;
    vin[1] = *(u16 *)((u8 *)a1 + 2) - 0x20;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[1]);

    vin[0] = *(u16 *)((u8 *)a1 + 0) - 0x30;
    vin[1] = *(u16 *)((u8 *)a1 + 2) + 0x20;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[2]);

    vin[0] = *(u16 *)((u8 *)a1 + 0) + 0x30;
    vin[1] = *(u16 *)((u8 *)a1 + 2) + 0x20;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[3]);

    tc[0] = tp[0];
    tc[1] = tp[1];
    tc[2] = tp[2];
    tc[3] = tp[1];
    tc[4] = tp[0];
    tc[5] = tp[3];
    tc[6] = tp[2];
    tc[7] = tp[3];

    w = *(u16 *)((u8 *)D_800CBFF8 + idx * 2);
    tail[2] = 0x80;
    tail[1] = 0x80;
    tail[0] = 0x80;
    *(u32 *)(tail + 4) = 0x40000000;
    tail[8] = w;
    func_80016ED4(o0);
}




#define SETROT_A(p) __asm__ __volatile__( \
    "lw $12, 0(%0)\n" \
    "lw $13, 4(%0)\n" \
    "ctc2 $12, $0\n" \
    "ctc2 $13, $1\n" \
    "lw $12, 8(%0)\n" \
    "lw $13, 12(%0)\n" \
    "lw $14, 16(%0)\n" \
    "ctc2 $12, $2\n" \
    "ctc2 $13, $3\n" \
    "ctc2 $14, $4\n" \
    : : "r"(p) : "$12", "$13", "$14", "memory")

#define LDV_A(p) __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(p) : "memory")

#define MVMVA_A() __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" \
    : : : "memory")

#define STSV_A(p) __asm__ __volatile__( \
    "mfc2 $12, $9\n" \
    "mfc2 $13, $10\n" \
    "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" \
    "sh $13, 2(%0)\n" \
    "sh $14, 4(%0)\n" \
    : : "r"(p) : "$12", "$13", "$14", "memory")

extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017714(void *a0);

void func_800CB964(void *a0, void *a1, void *a2) {
    s16 mat[4][4];
    u16 vin[4];
    u16 vec[4][4];
    u8 tail[20];
    register u16 *o0 __asm__("$4");

    func_80017DC4(a2, mat);
    o0 = &vec[0][0];

    vin[2] = 0;
    vin[0] = *(u16 *)((u8 *)a1 + 0) - 0x38;
    vin[1] = *(u16 *)((u8 *)a1 + 2) - 0x28;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(o0);

    vin[0] = *(u16 *)((u8 *)a1 + 0) + 0x38;
    vin[1] = *(u16 *)((u8 *)a1 + 2) - 0x28;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[1]);

    vin[0] = *(u16 *)((u8 *)a1 + 0) - 0x38;
    vin[1] = *(u16 *)((u8 *)a1 + 2) + 0x28;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[2]);

    vin[0] = *(u16 *)((u8 *)a1 + 0) + 0x38;
    vin[1] = *(u16 *)((u8 *)a1 + 2) + 0x28;
    SETROT_A(mat);
    LDV_A(vin);
    MVMVA_A();
    STSV_A(vec[3]);

    tail[0xE] = 0x80;
    tail[0xD] = 0x80;
    tail[0xC] = 0x80;
    tail[2] = 0;
    tail[1] = 0;
    tail[0] = 0;
    tail[6] = 0;
    tail[5] = 0;
    tail[4] = 0;
    tail[0xA] = 0;
    tail[9] = 0;
    tail[8] = 0;
    *(u32 *)(tail + 0x10) = 0x40000000;
    func_80017714(o0);
}



extern void func_800CBEB8(void);

void func_800CBBB8(void *arg0) {

    extern u8 D_80078EC1;
    extern void (*D_800CC030[])(void);
    if (D_80078EC1 == 0x1a) {
        u16 v0 = *(u16 *)((u8 *)arg0 + 2);
        D_800CC030[v0]();
    } else {
        func_800CBEB8();
    }
}


void func_800CBC14(void *arg0) {
    extern void func_80146578(void);
    extern void func_8001CB00(s32, void *, s32, s32);
    extern void func_80146DE8(s32 *, s32, s32, s32);
    extern void func_80146CA0(void *);
    extern void func_800CBEB8(void);
    extern u8 D_800CC00C;
    s32 v0;

    v0 = ((s32 (*)(void))func_80146578)();
    *(s32 *)((s32)arg0 + 0x20) = v0;
    if (v0 != 0) {
        func_8001CB00(v0,
            (void *)((s32)&D_800CC00C + (*(s32 *)((s32)arg0 + 0x50)) * 12),
            0x200, 0x100);
        *(s16 *)(v0 + 0x2C) = 1;
        *(u8 *)(v0 + 0x27) = 8;
        *(u8 *)(v0 + 0x25) = 0x20;
        *(u8 *)(v0 + 0x24) = 0x20;
        *(s32 *)(v0 + 0x4) |= 0x40000000;
        func_80146DE8((s32 *)arg0, 0, 0xFFFC0000, 0);
        func_80146CA0(arg0);
    } else {
        ((void (*)(void *))func_800CBEB8)(arg0);
    }
}


typedef struct { char c[8]; } Blk8;

void func_800CBCD4(u8 *s0) {
    extern s32 func_80012ABC(s32, s32, s32);
    extern void func_80162F08(s32, s32, s32, s32);
    extern void func_80013B64(s32, s32, s32);
    extern void func_80162FC0(s32 *);
    extern void func_800CBED8(s32 *);
    extern void func_80146DE8(s32 *, s32, s32, s32);
    extern s32 rand(void);
    extern u8 D_800CC13C[];
    extern u8 D_800CC140[];
    s32 v0, v1, flag;
    u8 *s1;
    s32 i;
    s32 sp10[3];
    u8 *a2, *a3;
    u16 w;

    v0 = *(s32 *)(s0 + 0x54);
    s1 = *(u32 **)(s0 + 0x20);
    if (v0 == 0) {
        v0 = func_80012ABC(*(s16 *)(s1 + 0x14), *(s16 *)(s0 + 0x60), 0xA);
        *(s16 *)(s1 + 0x14) = v0;
        func_80162F08(s0, 0, 0xC00, 0);
        func_80013B64(*(s16 *)(s1 + 0x14), s0 + 0x24, sp10);
        *(s32 *)(s0 + 0x10) = sp10[0];
        *(s32 *)(s0 + 0x14) = sp10[1];
        *(s32 *)(s0 + 0x18) = sp10[2];
        func_80162FC0(s0);
        func_800CBED8(s0);
        flag = *(s32 *)(s0 + 0x28) >= (s32)0xFFFE0000;
        if (flag) {
            func_80146DE8(s0, 0, 0xFFFC0000, 0);
            v0 = rand();
            v0 = v0 & 0x1F;
            v0 = v0 << 6;
            v1 = *(u16 *)(s0 + 0x60);
            v0 = v0 - 0xC00;
            v1 = v1 - v0;
            v1 = v1 & 0xFFF;
            *(u16 *)(s0 + 0x60) = v1;
        }
        i = 0xF;
        v0 = (s32)D_800CC13C;
        a3 = (u8 *)v0 + 0x78;
        a2 = (u8 *)v0 + 0x70;
        do {
            *(Blk8 *)a3 = *(Blk8 *)a2;
            a3 -= 8;
            i--;
            a2 -= 8;
        } while (i > 0);
        *(u16 *)D_800CC13C = *(u16 *)(s0 + 0x6);
        *(u16 *)(D_800CC13C + 2) = *(u16 *)(s0 + 0xA);
        *(u16 *)D_800CC140 = *(u16 *)(s0 + 0xE);
        *(u16 *)(D_800CC140 + 2) = *(u16 *)(s1 + 0x14);
    } else {
        v0 = *(s32 *)(s0 + 0x54);
        v0 = (v0 - 1) << 4;
        v1 = *(u16 *)(D_800CC13C + v0);
        *(u16 *)(s0 + 0x6) = v1;
        v0 = *(s32 *)(s0 + 0x54);
        v0 = (v0 - 1) << 4;
        v1 = *(u16 *)(D_800CC13C + 2 + v0);
        *(u16 *)(s0 + 0xA) = v1;
        v0 = *(s32 *)(s0 + 0x54);
        v0 = (v0 - 1) << 4;
        v1 = *(u16 *)(D_800CC140 + v0);
        *(u16 *)(s0 + 0xE) = v1;
        v0 = *(s32 *)(s0 + 0x54);
        v0 = (v0 - 1) << 4;
        w = *(u16 *)(D_800CC140 + 2 + v0);
        *(u16 *)(s1 + 0x14) = w;
    }
}


extern void func_80162CCC(void);
void func_800CBEB8(void) {
    func_80162CCC();
}


s32 func_800CBED8(s32 *arg0) {
    s16 *p;
    s32 ret;
    p = (s16 *) arg0;
    ret = 0;
    if (p[3] < -0x60) {
        p[3] = -0x60;
        ret = 1;
    } else if (p[3] > 0x60) {
        p[3] = 0x60;
        ret = 1;
    }
    if (p[5] < -0x40) {
        p[5] = -0x40;
        ret++;
    } else if (p[5] > 0x40) {
        p[5] = 0x40;
        ret++;
    }
    return ret;
}

