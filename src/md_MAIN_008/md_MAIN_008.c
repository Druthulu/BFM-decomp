#include "common.h"

#include "common.h"

extern void func_800CEF50(void);
extern u16 D_800B99E4;
extern void (*D_800CF0FC[])(void);

void func_800CEDFC(void) {
    func_800CEF50();
    D_800CF0FC[D_800B99E4]();
}


extern void func_8001C044(void);
extern void func_80015310(void);
extern u8 D_800B9A11;
extern s32 D_800CF13C;
extern void func_800167B8(s32);
extern void func_800118AC(void);

void func_800CEE44(void) {
    func_8001C044();
    func_80015310();
    D_800B9A11 = 0;
    D_800CF13C = 0;
    func_800167B8(0);
    func_800118AC();
}


void func_800CEE8C(void) {
    extern s32 func_800167F0(s32 a0);
    extern void func_800118AC(void);

    if (func_800167F0(0) & 0xFFFF) {
        func_800118AC();
    }
}


extern s32 D_800CF13C;
extern s32 func_800149E0(s32);
extern void func_800167B8(s32);
extern void func_800118AC(void);

void func_800CEEC0(void) {
    s32 ret = func_800149E0(0);
    D_800CF13C++;
    if (D_800CF13C >= 0x12D || (ret & 0x8F0)) {
        func_800167B8(4);
        func_800118AC();
    }
}


extern s32 func_800167F0(s32 a0);
extern void func_80011818(s32 arg0);

void func_800CEF1C(void) {
    if (func_800167F0(4) & 0xFFFF) {
        func_80011818(12);
    }
}


void func_800CEF50(void) {
    extern u8 D_800CF10C[3];
    extern u8 D_800CF10F;
    extern u32 D_800CF110;
    extern u8 D_800CF114;
    extern u8 D_800CF115;
    extern u8 D_800CF116;
    extern u8 D_800CF117;
    extern s16 D_800CF118;
    extern s16 D_800CF11A;
    extern u8 D_800CF11C;
    extern u8 D_800CF11D;
    extern u16 D_800CF11E;
    extern u16 D_800CF120;
    extern u16 D_800CF122;
    extern u8 D_800CF124[3];
    extern u8 D_800CF127;
    extern u32 D_800CF128;
    extern u8 D_800CF12C;
    extern u8 D_800CF12D;
    extern u8 D_800CF12E;
    extern u8 D_800CF12F;
    extern u16 D_800CF130;
    extern s16 D_800CF132;
    extern u8 D_800CF134;
    extern u8 D_800CF135;
    extern u16 D_800CF136;
    extern u16 D_800CF138;
    extern u16 D_800CF13A;
    extern s16 D_800B9A02;
    extern u8 D_800AA60C[];

    register s32 v __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 c __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u32 w;
    s32 x78;
    register s32 m __asm__("$7");  // !FAKE: pin $7 — NEEDED DIFFERS (P36 rung B tus9)
    s32 f;
    register s32 ten __asm__("$9");  // !FAKE: pin $9 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 neg __asm__("$10");  // !FAKE: pin $10 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 hundred __asm__("$11");  // !FAKE: pin $11 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 five __asm__("$12");  // !FAKE: pin $12 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 v2 __asm__("$13");  // !FAKE: pin $13 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 *p __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 pm __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)

    v = 0xE100008A;
    v2 = 0xE100008C;
    m = 0xFF0000;
    __asm__("" : "=r"(m) : "0"(m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    five = 5;
    __asm__("" : "=r"(five) : "0"(five));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    p = (u32 *)&D_800CF10C;
    m |= 0xFFFF;
    D_800CF10F = five;
    w = *p;
    __asm__ volatile("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
    hundred = 100;
    __asm__("" : "=r"(hundred) : "0"(hundred));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    D_800CF110 = v;
    v = -0xA0;
    neg = -0x6E;
    __asm__("" : "=r"(neg) : "0"(neg));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    c = 0x80;
    ten = 10;
    __asm__("" : "=r"(ten) : "0"(ten));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    D_800CF118 = v;
    v = 0x100;
    f = 0xF0;
    D_800CF116 = c;
    D_800CF115 = c;
    D_800CF114 = c;
    D_800CF12E = c;
    D_800CF12D = c;
    D_800CF12C = c;
    c = (s32)&D_800B9A02;
    c = *(u16 *)c;
    x78 = 0x7800;
    D_800CF120 = v;
    v = 0x60;
    D_800CF130 = v;
    v = 0x40;
    D_800CF122 = f;
    D_800CF13A = f;
    f = (s32)&D_800AA60C[0];
    D_800CF11E = x78;
    D_800CF136 = x78;
    x78 = 0xFF000000;
    D_800CF117 = hundred;
    D_800CF11A = neg;
    D_800CF11C = 0;
    D_800CF11D = ten;
    D_800CF127 = five;
    D_800CF128 = v2;
    D_800CF12F = hundred;
    D_800CF132 = neg;
    D_800CF134 = 0;
    D_800CF135 = ten;
    D_800CF138 = v;

    c = (c << 14) + f;
    v = *(u32 *)c;
    *p = (w & x78) | (v & m);
    v = *(u32 *)c;
    __asm__("and %0,%1,%2" : "=r"(pm) : "r"(p), "r"(m));  // !FAKE: instruction and — NEEDED DIFFERS (P36 rung B tus9)
    v = (v & x78) | pm;
    p = (u32 *)&D_800CF124;
    *(u32 *)c = v;

    c = (s32)&D_800B9A02;
    c = *(u16 *)c;
    w = *p;
    c = (c << 14) + f;
    v = *(u32 *)c;
    *p = (w & x78) | (v & m);
    v = *(u32 *)c;
    __asm__("and %0,%1,%2" : "=r"(pm) : "r"(p), "r"(m));  // !FAKE: instruction and — NEEDED DIFFERS (P36 rung B tus9)
    v = (v & x78) | pm;
    *(u32 *)c = v;
}


INCLUDE_RODATA("asm/md_MAIN_008/nonmatchings/md_MAIN_008", D_800CEDF8);
