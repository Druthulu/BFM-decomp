typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

extern s32 D_80126B5C;
/* derived from asm %hi/%lo refs (not present in sig_hints) */
extern s32 D_80126B60;
extern s32 D_80126B64;

extern void func_80049CAC(s32, s32);
void func_8012F0BC(s32*, s32*, s32*);
void func_8012F1A4(s32*, s32, s32*);

void func_8012E014(s32 arg0) {
    typedef struct { s32 vx, vy, vz, pad; } Vec_8012E014;
    Vec_8012E014 sp10;
    Vec_8012E014 sp20;
    Vec_8012E014 sp30;
    s32 obj;
    s16 t;

    sp10.vx = D_80126B5C;
    sp10.vy = D_80126B60;
    sp10.vz = D_80126B64;
    func_8012F0BC((s32*)(*(s32*)(arg0 + 0x20) + 0x34), (s32*)&sp10, (s32*)&sp30);
    obj = *(s32*)(arg0 + 0x20);
    if (obj != 0) {
        register s32 obj2 __asm__("$4");
        func_80049CAC(obj + 0x10, obj + 0x34);
        obj2 = *(s32*)(arg0 + 0x20);
        t = *(u16*)(arg0 + 6) + *(u16*)(arg0 + 0x50);
        *(s16*)(obj2 + 8) = t;
        *(s32*)(obj2 + 0x48) = t;
        t = *(u16*)(arg0 + 0xA) + *(u16*)(arg0 + 0x52);
        *(s16*)(obj2 + 0xA) = t;
        *(s32*)(obj2 + 0x4C) = t;
        t = *(u16*)(arg0 + 0xE) + *(u16*)(arg0 + 0x54);
        *(s16*)(obj2 + 0xC) = t;
        *(u16*)(obj2 + 0x2C) |= 1;
        *(s32*)(obj2 + 0x50) = t;
    }
    func_8012F1A4((s32*)(*(s32*)(arg0 + 0x20) + 0x34), (s32)&sp30, (s32*)&sp20);
    D_80126B5C = sp20.vx;
    D_80126B60 = sp20.vy;
    D_80126B64 = sp20.vz;
}
