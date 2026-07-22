// @class: schedule
// @stuck: none — MATCH (125 ins, relocation-masked)

typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct Cmd {
    /* 0x00 */ s32 c0;
    /* 0x04 */ s16 c4;
    /* 0x06 */ s16 c6;
} Cmd;

typedef struct Node {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s32 n20;
} Node;

typedef struct Obj {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ Node *o20;
    /* 0x24 */ u8 pad24[0x72 - 0x24];
    /* 0x72 */ u16 f72;
    /* 0x74 */ u8 pad74[0x90 - 0x74];
    /* 0x90 */ s32 o90;
    /* 0x94 */ s32 o94;
    /* 0x98 */ u16 o98;
    /* 0x9A */ s16 o9a;
    /* 0x9C */ s32 o9c;
} Obj;

void func_8012AAAC(Obj *o);

void func_8012AAAC(Obj *o) {
    Cmd *p;
    s32 t;
    s32 sav;
    s32 idx;
    s32 sv;
    s32 cur;
    s16 sel;

    o->f72 &= 0xBFFF;
    p = (Cmd *)o->o90 + o->o94;
    if (p->c4 < 0) {
        sel = p->c4 + 0x32;
        switch (sel) {
        case 0x30:
            cur = o->o9c;
            if (cur == 0) {
                o->o98 = 0;
                break;
            }
            goto shared;
        case 0x31:
            cur = o->o9c;
            if (cur != 0) {
            shared:
                sv = o->o9a;
                o->o90 = cur;
                o->o9c = 0;
                o->o9a = 0;
                o->o94 = sv;
                func_8012AAAC(o);
                break;
            }
            o->o94 = 0;
            func_8012AAAC(o);
            o->f72 |= 0x4000;
            break;
        case 0x2E:
            t = p->c0;
            o->o94 = 0;
            o->o9c = 0;
            o->o9a = 0;
            o->o90 = t;
            o->f72 &= 0xF9FF;
            func_8012AAAC(o);
            break;
        case 0x2F:
            idx = o->o94 + 1;
            o->o94 = idx;
            if (o->o9c != 0) {
                func_8012AAAC(o);
                break;
            }
            sav = o->o90;
            __asm__ __volatile__("" : : "r"(sav));
            t = p->c0;
            o->o94 = 0;
            o->o9c = 0;
            o->o9a = 0;
            o->o90 = t;
            o->f72 &= 0xF9FF;
            func_8012AAAC(o);
            o->o9c = sav;
            o->o9a = idx;
            break;
        case 0x0:
            o->o94 = o->o94 + 1;
            func_8012AAAC(o);
            o->f72 |= 0x2000;
            break;
        case 0x2D:
            o->f72 |= 0x400;
            o->o94 = o->o94 - 1;
            func_8012AAAC(o);
            break;
        }
    } else {
        o->o20->n20 = p->c0;
        o->o98 = (u16)p->c4;
    }
}
