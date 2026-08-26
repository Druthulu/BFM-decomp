#include "common.h"
#include "psyq/libcd.h"
#include "shared/clearTbl40.h"  /* dedup group I0: func_80037004 / func_80037334 share one body */
typedef struct Ent30D80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 pad04[6];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 pad0C[0x34];
    /* 0x40 */ void (*unk40)(s32, s32);
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 pad48[6];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
} Ent30D80;
typedef struct { u8  v; } W8;
typedef struct { s32 a; s32 b[4]; } OtBlk_80016450;
typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 x;
    /* 0x06 */ u16 y;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ void *data;
} DispItem_800184F0;
typedef struct {
    /* 0x00 */ s16 flag;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ DispItem_800184F0 *list;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u16 unk0E;
} DispSlot_800184F0;
typedef struct Rec14 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u32 unk10;
} Rec14; /* 0x14 */
typedef struct Owner4EE8 {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ Rec14 **unk14;
} Owner4EE8;
    typedef struct {
        s16 flag;
        s16 pad02;
        s32 id;
        u16 x;
        u16 y;
        u8 c;
        u8 d;
        u16 pad0E;
    } Rec;
    typedef struct {
        u8 pad[0xA1A8];
        Rec rec[0x20];
    } Base;
typedef struct {
    s32 w[9];
} Blk36_800296F8;
typedef struct Slot {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 unk08[0xC];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 unk1A[0x26];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45[3];
} Slot;
typedef struct {
    u32 pad0;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0;
    u16 v0;
    u16 v1;
    u16 v2;
} TmdG3;
/* hoisted by gate_main so drafts above can reuse them (§181) */
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s16 unk0E;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    s32 unk14;
} Rsc24;                       /* 0x18 */
typedef struct {
    /* 0x00 */ u8 *unk00;
    /* 0x04 */ u8  pad04[2];
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} A12; /* 0x0C */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
} B12; /* 0x0C */
typedef struct {
    /* 0x00 */ u8  pad00[4];
    /* 0x04 */ u8  unk04;
    /* 0x05 */ u8  pad05[11];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8  pad14[2];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8  pad18[8];
} C24; /* 0x20 */
/* hoisted by gate_main so drafts above can reuse them (§181) */
typedef struct {               /* 0x18 stride; D_800A463C + k*0x18 */
    s32 unk00;
    u8  unk04[0x14];
} Ent24;
typedef struct {              /* base 0x80064D49, stride 0x0C */
    u8  unk00;
    u8  pad[11];
} Elm12;
/* hoisted by gate_main so drafts above can reuse them (§181) */
/* hoisted by gate_main so drafts above can reuse them (§181) */
typedef struct {              /* base 0x80076240, stride 0x10 */
    u16 unk00;
    u16 unk02;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Slot16A;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    u8  unk0C;
    u8  unk0D;
    u8  unk0E;
    u8  unk0F;
} Slot16;                      /* 0x10 */
typedef struct { s32 v; } W32;
/* hoisted by gate_main so drafts above can reuse them (§181) */
typedef struct { s16 vx, vy, vz, pad; } SVEC2;      /* 0x08 */
typedef struct {                                     /* 0x14 */
    u32 w0;      /* 0x00 */
    u32 rgb;     /* 0x04 */
    u16 n0;      /* 0x08 */
    u16 v0;      /* 0x0A */
    u16 n1;      /* 0x0C */
    u16 v1;      /* 0x0E */
    u16 n2;      /* 0x10 */
    u16 v2;      /* 0x12 */
} Face2;
typedef struct {                                     /* 0x1C */
    u32 tag;
    u32 rgb0;
    s16 x0, y0;
    u32 rgb1;
    s16 x1, y1;
    u32 rgb2;
    s16 x2, y2;
} G3P;
typedef struct {                                     /* 0x18 */
    u32 w0;      /* 0x00 */
    u32 rgb;     /* 0x04 */
    u16 n0;      /* 0x08 */
    u16 v0;      /* 0x0A */
    u16 n1;      /* 0x0C */
    u16 v1;      /* 0x0E */
    u16 n2;      /* 0x10 */
    u16 v2;      /* 0x12 */
    u16 n3;      /* 0x14 */
    u16 v3;      /* 0x16 */
} Face3;
typedef struct {                                     /* 0x24 */
    u32 tag;     /* 0x00 */
    u32 rgb0;    /* 0x04 */
    s16 x0, y0;  /* 0x08 */
    u32 rgb1;    /* 0x0C */
    s16 x1, y1;  /* 0x10 */
    u32 rgb2;    /* 0x14 */
    s16 x2, y2;  /* 0x18 */
    u32 rgb3;    /* 0x1C */
    s16 x3, y3;  /* 0x20 */
} G4P;
typedef struct Slot54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
} Slot54;
/* hoisted by gate_main so drafts above can reuse them (§181) */
typedef struct {
    u32 a, b, c, d;
} Blk16;
typedef struct {
    u32 a, b, c;
} Blk12;
typedef struct { u16 f0; } H2; /* 0x2 */
typedef struct {
    s32 unk00;
    u8  unk04;
    u8  unk05;
    u8  unk06;
    u8  unk07;
    u8  unk08;
    u8  unk09;
    u8  unk0A;
    u8  unk0B;
    s32 unk0C;
} Rsc16;                      /* 0x10 */

extern s32 func_8004787C(s32 angle);
extern s32 func_80047948(s32 angle);
extern void func_8001282C();

void func_800123F0(s32 param_1, s32 param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s32 sin_val;
    register s32 v1 __asm__("$3");
    s16 matrix[16];

    s1 = (s32)param_1;
    s0 = param_2;

    sin_val = func_8004787C(s0);
    cos_val = func_80047948(s0);

    /* Build Z-rotation matrix on stack */
    v1 = -sin_val;
    *(s16 *)((s32)matrix + 0x00) = cos_val;
    *(s16 *)((s32)matrix + 0x08) = cos_val;
    *(s16 *)((s32)matrix + 0x02) = v1;
    *(s16 *)((s32)matrix + 0x04) = 0;
    *(s16 *)((s32)matrix + 0x06) = sin_val;
    *(s16 *)((s32)matrix + 0x0A) = 0;
    *(s16 *)((s32)matrix + 0x0C) = 0;
    *(s16 *)((s32)matrix + 0x0E) = 0;
    *(s16 *)((s32)matrix + 0x10) = 0x1000;

    __asm__ __volatile__ (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 16;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 18;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 20;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2)"
        :
        : "r"(s1)
        : "$12", "$13", "$14", "$2"
    );

    func_8001282C(s1);
}

extern s32 func_8004787C(s32 angle);
extern s32 func_80047948(s32 angle);
extern void func_8001282C();

void func_80012558(s32 param_1, s32 param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix[16];

    s1 = (s32)param_1;
    s0 = param_2;

    sin_val = func_8004787C(s0);
    cos_val = func_80047948(s0);

    /* Build rotation matrix on stack */
    v1 = 0x1000;
    *(s16 *)((s32)matrix + 0x04) = sin_val;
    *(s16 *)((s32)matrix + 0x00) = cos_val;
    *(s16 *)((s32)matrix + 0x02) = 0;
    *(s16 *)((s32)matrix + 0x06) = 0;
    *(s16 *)((s32)matrix + 0x08) = v1;
    *(s16 *)((s32)matrix + 0x0A) = 0;
    *(s16 *)((s32)matrix + 0x0C) = -sin_val;
    *(s16 *)((s32)matrix + 0x0E) = 0;
    *(s16 *)((s32)matrix + 0x10) = cos_val;

    __asm__ __volatile__ (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 16;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 18;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 20;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2)"
        :
        : "r"(s1)
        : "$12", "$13", "$14", "$2"
    );

    func_8001282C(s1);
}

extern s32 func_8004787C(s32 angle);
extern s32 func_80047948(s32 angle);
extern void func_8001282C();

void func_800126C4(s32 param_1, s32 param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix[16];

    s1 = (s32)param_1;
    s0 = param_2;

    sin_val = func_8004787C(s0);
    cos_val = func_80047948(s0);

    /* Build X-rotation matrix on stack */
    v1 = 0x1000;
    *(s16 *)((s32)matrix + 0x00) = v1;
    *(s16 *)((s32)matrix + 0x02) = 0;
    *(s16 *)((s32)matrix + 0x04) = 0;
    *(s16 *)((s32)matrix + 0x06) = 0;
    *(s16 *)((s32)matrix + 0x08) = cos_val;
    *(s16 *)((s32)matrix + 0x0A) = -sin_val;
    *(s16 *)((s32)matrix + 0x0C) = 0;
    *(s16 *)((s32)matrix + 0x0E) = sin_val;
    *(s16 *)((s32)matrix + 0x10) = cos_val;

    __asm__ __volatile__ (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 16;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 18;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 20;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2)"
        :
        : "r"(s1)
        : "$12", "$13", "$14", "$2"
    );

    func_8001282C(s1);
}


extern void func_800128B4(void* a0);
extern void func_80013FE0(void* a0, void* a1);
extern void func_80013FBC(void* a0, void* a1);
extern void func_80013F98(void* a0, void* a1);
extern void func_80013ED0(void* a0, void* a1, void* a2, void* a3);

void func_8001282C(void *a0)
{
    s16 b10[4];
    s16 b18[4];
    s16 b20[4];

    func_80013FE0(a0, b20);
    func_800128B4(b20);
    func_80013FBC(a0, b18);
    func_800128B4(b18);
    func_80013F98(a0, b10);
    func_800128B4(b10);
    func_80013ED0(a0, b10, b18, b20);
}


extern void func_80014070(void* a0, void* a1);
extern void func_800128EC(void* a0, void* a1);

void func_800128B4(void* a0)
{
    s32 local_buffer[3];

    func_80014070(a0, local_buffer);
    func_800128EC(local_buffer, a0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_800128EC);


extern s32 ratan2(s32 a0, s32 a1);

void func_800129CC(s16 *s0, s16 *s1)
{
    if (s0[2] != 0) {
        s32 angle = ratan2(-s0[1], s0[2]);
        s1[0] = (s16)((angle - 0x400) & 0xFFF);
    } else {
        s1[0] = 0;
    }

    s1[1] = 0;

    if (s0[0] != 0) {
        s32 angle = ratan2(s0[1], s0[0]);
        s1[2] = (s16)((angle + 0x400) & 0xFFF);
    } else {
        s1[2] = 0;
    }
}

extern s32 func_80012AB0(s32 a0, s32 a1);

s32 func_80012A60(s16 a0, s16 a1) {
    s32 w = func_80012AB0(a0, a1);
    if ((s16)w > 0x7FF) {
        w = 0xFFF - w;
    }
    return (s16)w;
}

s32 func_80012AB0(s32 arg0, s32 arg1) {
    return (arg0 - arg1) & 0xFFF;
}

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);

s32 func_80012ABC(s32 a0, s32 a1, s32 a2)
{
    s32 s0 = a0;
    return (s0 + func_80012B04((s16)s0, (s16)a1, (s16)a2)) & 0xFFF;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012B04);

INCLUDE_ASM("asm/nonmatchings/800", func_80012B58);

extern s32 func_80012CB8(s32 a0, s32 a1, s32 a2);

s32 func_80012C6C(s32 a0, s32 a1, s32 a2)
{
    s32 s0 = a0;
    return (s16)(s0 + func_80012CB8((s16)s0, (s16)a1, (s16)a2));
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012CB8);

s16 func_80012D0C(s32 x0, s32 x1, s32 d, s16 *ctr)
{
    s32 diff;
    s32 q;

    diff = x1 - x0;
    if (*ctr == 0 || (s16)d == 0)
        return (s16)diff;
    q = (s16)((s16)diff / (s16)d);
    if (q != 0)
        return q;
    *ctr = *ctr - 1;
    return func_80012D0C((s16)x0, (s16)x1,
                         ((s16)d + (s32)(((u32)d << 16) >> 31)) >> 1,
                         ctr);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012DBC);

extern s16 func_80012E6C(s32 a0, s32 a1, s32 a2, s32 a3, s16 *a4);

s32 func_80012E0C(s16 a0, s16 a1, s32 a2, s32 a3) {
    s16 out = 4;

    if (a0 == a1) {
        return 0;
    }
    return func_80012E6C(a0, a1, (s16)a2, (s16)a3, &out);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012E6C);

extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_80012F74(s32 x, s32 y, s32 z, s32 w)
{
    return (s16)(x + func_80012FC8((s16)x, (s16)y, (s16)z, (s16)w));
}

INCLUDE_ASM("asm/nonmatchings/800", func_80012FC8);

s32 func_80013028(s32 x, s32 y, s16 n, s16 d, s16 *p) {
    s32 r;

    y -= x;
    if (*p == 0 || n == 0) {
        r = (s16)y;
    } else {
        r = (s16)((s16)y * d / n);
        if (r == 0) {
            r = -1;
            if ((s16)y > 0) {
                r = 1;
            }
        }
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800130D0);

extern s32 func_80013154(s32 a0, s32 a1, s32 a2);

s16 func_8001311C(s16 a0, s16 a1, s16 a2) {
    return func_80013154(a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80013154);


extern s32 func_80013228(s32 *a0, s32 *a1);
extern s32 func_80047D3C(s32 a0);

s32 func_80013200(s32 *a0, s32 *a1) {
    return func_80047D3C(func_80013228(a0, a1));
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_80013228(s32 *a0, s32 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0[0] - a1[0];
    diff[1] = a0[1] - a1[1];
    diff[2] = a0[2] - a1[2];

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_80013294;

s32 func_80013294(SVECTOR_80013294 *a0, SVECTOR_80013294 *a1) {
    return func_80047D3C(func_800132BC(a0, a1));
}


extern void Square0(s32 *a0, s32 *a1);

typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR;

s32 func_800132BC(SVECTOR *a0, SVECTOR *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0->vx - a1->vx;
    diff[1] = a0->vy - a1->vy;
    diff[2] = a0->vz - a1->vz;

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

void func_80013328(s32 *a0, s32 *a1) {
    s32 result;
    result = func_80013350(a0, a1);
    func_80047D3C(result);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_80013350(s32 *a0, s32 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = *(s16 *)((u8 *)a0 + 2) - *(s16 *)((u8 *)a1 + 2);
    diff[1] = *(s16 *)((u8 *)a0 + 6) - *(s16 *)((u8 *)a1 + 6);
    diff[2] = *(s16 *)((u8 *)a0 + 10) - *(s16 *)((u8 *)a1 + 10);

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80047D3C(s32 a0);

s32 func_800133BC(void) {
    s32 result = func_800133E4();
    return func_80047D3C(result);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_800133E4(s16 *a0, s16 *a1) {
    s32 diff[3];
    s32 result[3];

    diff[0] = a0[0] - a1[1];
    diff[1] = a0[1] - a1[3];
    diff[2] = a0[2] - a1[5];

    Square0(diff, result);

    return result[0] + result[1] + result[2];
}


extern s32 func_80013478(void);
extern s32 func_80047D3C(s32 a0);

s32 func_80013450(void) {
    s32 result = func_80013478();
    return func_80047D3C(result);
}

s32 func_80013478(void) {
    register s16 *a0 __asm__("$4");
    register s16 *a1 __asm__("$5");
    volatile s32 diff[3];
    s32 result[3];

    diff[0] = a0[1] - a1[0];
    diff[1] = a0[3] - a1[1];
    diff[2] = a0[5] - a1[2];

    __asm__ volatile("lwc2 $9, 0(%0)\n\tlwc2 $10, 4(%0)\n\tlwc2 $11, 8(%0)" : : "r"(diff));
    __asm__ volatile("nop\n\tnop\n\tsqr 0");
    __asm__ volatile("swc2 $25, 0(%0)\n\tswc2 $26, 4(%0)\n\tswc2 $27, 8(%0)" : : "r"(result) : "memory");

    return result[0] + result[1] + result[2];
}

INCLUDE_ASM("asm/nonmatchings/800", func_800134FC);

INCLUDE_ASM("asm/nonmatchings/800", func_80013694);

INCLUDE_ASM("asm/nonmatchings/800", func_8001382C);

INCLUDE_ASM("asm/nonmatchings/800", func_800139C8);

INCLUDE_ASM("asm/nonmatchings/800", func_80013B64);

INCLUDE_ASM("asm/nonmatchings/800", func_80013CFC);

void func_80013E94(u16 *src, u32 *dst) {
    *dst = ((((u32)src[0] << 19) >> 22) << 20)
         | ((((u32)src[1] << 19) >> 22) << 10)
         | (((u32)src[2] << 19) >> 22);
}

void func_80013ED0(void* a0, void* a1, void* a2, void* a3) {
    ((u16*)a0)[0] = ((u16*)a1)[0];
    ((u16*)a0)[1] = ((u16*)a2)[0];
    ((u16*)a0)[2] = ((u16*)a3)[0];
    ((u16*)a0)[3] = ((u16*)a1)[1];
    ((u16*)a0)[4] = ((u16*)a2)[1];
    ((u16*)a0)[5] = ((u16*)a3)[1];
    ((u16*)a0)[6] = ((u16*)a1)[2];
    ((u16*)a0)[7] = ((u16*)a2)[2];
    ((u16*)a0)[8] = ((u16*)a3)[2];
}


void func_80013F3C(void *ptr) {
    s16 *p = (s16 *)ptr;
    p[0] = 0x1000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0x1000;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0x1000;
}


void func_80013F68(s16 *a0) {
    s16 v0;

    v0 = -0x1000;
    a0[2] = v0;
    v0 = 0x1000;
    a0[0] = 0;
    a0[1] = 0;
    a0[3] = 0;
    a0[4] = v0;
    a0[5] = 0;
    a0[6] = v0;
    a0[7] = 0;
    a0[8] = 0;
}

void func_80013F98(void *a0, void *a1) {
    *(u16 *)((s32)a1 + 0x0) = *(u16 *)((s32)a0 + 0x0);
    *(u16 *)((s32)a1 + 0x2) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)((s32)a1 + 0x4) = *(u16 *)((s32)a0 + 0xC);
}

void func_80013FBC(void *a0, void *a1) {
    *(u16 *)((s32)a1 + 0x0) = *(u16 *)((s32)a0 + 0x2);
    *(u16 *)((s32)a1 + 0x2) = *(u16 *)((s32)a0 + 0x8);
    *(u16 *)((s32)a1 + 0x4) = *(u16 *)((s32)a0 + 0xE);
}

void func_80013FE0(void *a0, void *a1) {
    *(u16 *)((s32)a1 + 0x0) = *(u16 *)((s32)a0 + 0x4);
    *(u16 *)((s32)a1 + 0x2) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)((s32)a1 + 0x4) = *(u16 *)((s32)a0 + 0x10);
}

void func_80014004(unsigned short *a0, unsigned short *a1) {
    a0[0] = a1[0];
    a0[3] = a1[1];
    a0[6] = a1[2];
}

void func_80014028(s32 *a0, s32 *a1) {
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a1 + 0x0);
        *(u16 *)((s32)a0 + 0x8) = *(u16 *)((s32)a1 + 0x2);
        *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a1 + 0x4);
    }

void func_8001404C(s32 *a0, s32 *a1) {
        *(u16 *)((s32)a0 + 0x4) = *(u16 *)((s32)a1 + 0x0);
        *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a1 + 0x2);
        *(u16 *)((s32)a0 + 0x10) = *(u16 *)((s32)a1 + 0x4);
    }

void func_80014070(void* a0, void* a1)
{
    ((s32 *)a1)[0] = ((s16 *)a0)[1 - 1];
    ((s32 *)a1)[1] = ((s16 *)a0)[2 - 1];
    ((s32 *)a1)[2] = ((s16 *)a0)[3 - 1];
}

void func_80014094(s32 *arg0, void *arg1) {
    *(s16 *)((u8 *)arg1 + 0x0) = arg0[0];
    *(s16 *)((u8 *)arg1 + 0x2) = arg0[1];
    *(s16 *)((u8 *)arg1 + 0x4) = arg0[2];
}

void func_800140B8(s32 a0, s32 a1, s32 a2)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "lw     $12, 0($4)\n"
        "lw     $13, 4($4)\n"
        "ctc2   $12, $0\n"
        "ctc2   $13, $1\n"
        "lw     $12, 8($4)\n"
        "lw     $13, 12($4)\n"
        "lw     $14, 16($4)\n"
        "ctc2   $12, $2\n"
        "ctc2   $13, $3\n"
        "ctc2   $14, $4\n"
        "lwc2   $0, 0($5)\n"
        "lwc2   $1, 4($5)\n"
        "nop\n"
        "nop\n"
        "mvmva  1, 0, 0, 3, 0\n"
        "swc2   $25, 0($6)\n"
        "swc2   $26, 4($6)\n"
        "swc2   $27, 8($6)\n"
        ".set\treorder\n"
        : : : "$12", "$13", "$14", "memory");
    *(s32 *)a2 <<= 16;
    *(s32 *)(a2 + 4) <<= 16;
    *(s32 *)(a2 + 8) <<= 16;
}

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_80014128(void *a0, void *a1, void *a2) {
    ApplyMatrixSV(a0, a1, a2);
}

void func_80014148(s32 a0, s32 a1, s32 a2) {
    func_800484EC(a0, a1, a2);
}


typedef struct { u8 b[8]; } Blk8;

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);

void func_80014168(void *a0, void *a1) {
    Blk8 local;

    local = *(Blk8 *)a1;
    ApplyMatrixSV(a0, &local, a1);
}

void func_800141AC(s32 a0, void *a1)
{
    struct B16x { u32 a, b, c, d; } local;

    local = *(struct B16x *)a1;
    func_800484EC(a0, &local, a1);
}


extern void func_80059234(s32);
extern void func_800594CC(s32);
extern void func_80059658(s32);
extern void func_80016714(void *a0, s32 a1);
extern void func_800142C8(void);
extern u8 D_800BA118;

void func_800141F0(void) {
    func_80059234(0);
    func_800594CC(0);
    func_80059658(0);
    func_80016714(&D_800BA118, 0x98);
    func_800142C8();
}

extern u8 D_800AF630[];
void func_80014238(void) {
    func_80014928();
    func_80059234(1);
    func_80059658(0);
    VSync(0);
    func_80016714(&D_800AF630, 0xA444);
    func_800143AC();
    func_80014444();
    func_8001C044();
    func_80014588();
    func_80015310();
    func_80028A48();
    func_80028C50();
    func_800142C8();
    func_80059658(1);
}


extern void func_80029044(void);
extern void func_8002906C(void);
extern void func_80029094(void);
extern void func_80029218(void);
extern void func_8001903C(void);
extern void func_80018FC8(void);
extern void func_8001B324(void);
extern void func_80028FDC(s32);
extern void func_80029020(s32);
extern void func_80028DBC(s32);
extern void func_80028E00(s32);

void func_800142C8(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80029218();
    func_8001903C();
    func_80018FC8();
    func_8001B324();
    func_80028FDC(0x7);
    func_80029020(0x7);
    func_80028DBC(0);
    func_80028E00(0);
}


extern void func_80029044(void);
extern void func_8002906C(void);
extern void func_80029094(void);
extern void func_80028FDC(s32);
extern void func_80029020(s32);
extern void func_80028DBC(s32);
extern void func_80028E00(s32);
extern void func_80029274(void);

void func_80014338(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80028FDC(0x7);
    func_80029020(0x7);
    func_80028DBC(0);
    func_80028E00(0);
    func_80029274();
}

void func_80014390(void) {
    extern s16 D_800B9A04[];
    extern s32 D_800B9A18;
    D_800B9A04[0] = 0;
    D_800B9A18 = 2;
}


extern void func_800145EC(s32 a0);
extern int VSync(int mode);

extern u8 D_800AF7C4;
extern u8 D_800AF7C3;
extern u8 D_800AF7C2;
extern u8 D_800A6610[];
extern u8 D_800A6518[];
extern u8 D_800A6520[];
extern u8 D_800A6524[];


void func_800143AC(void)
{
    extern OtBlk_80016450 D_800A651C[];
    register s32 ptr __asm__("4");
    register s32 i __asm__("5");
    register s32 idx __asm__("3");
    register s32 c __asm__("6");

    func_800145EC(1);
    VSync(0);

    i = 0;
    c = 0xC;
    ptr = (s32)D_800A6610;
    idx = 0;

    D_800AF7C4 = 0;
    D_800AF7C3 = 0;
    D_800AF7C2 = 0;

    do {
        *(s32*)((u8*)D_800A651C + idx) = ptr;
        ptr += 0x4000;
        *(s32*)(D_800A6518 + idx) = c;
        *(s32*)(D_800A6520 + idx) = 0;
        *(s32*)(D_800A6524 + idx) = 0;
        idx += 0x14;
        i++;
    } while (i < 2);
}


extern void func_80047CB4(void);
extern void func_8004923C(s32 a0);
extern void func_80053218(void);
extern void func_800144D4(void);
extern void func_8001455C(void);
extern void func_8002850C(s32 a0, s32 a1, s32 a2);
extern void func_8002823C(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_800538EC(s32 a0);

extern s32 D_80126950;
extern u8 D_800AF630[0x300];

void func_80014444(void) {
    u8 *s0;

    func_80047CB4();
    D_80126950 = 0x3E8;
    func_8004923C(0x3E8);
    func_80053218();
    func_800144D4();
    func_8001455C();
    func_8002850C(0x800, 0x800, 0x800);
    func_8002823C();
    s0 = &D_800AF630[0];
    func_80052D90(0, s0 + 0x1A0);
    func_80052D90(1, s0 + 0x1F0);
    func_800538EC(0);
}

extern void func_80053308(s32);
extern void func_80053F6C();
extern s32 D_80126984;
extern s32 D_80126988;
extern s32 D_8012698C;
extern s32 D_80126990;
extern s32 D_80126994;
extern s32 D_80126998;
extern s32 D_8012699C;
extern s32 D_801269A0;

void func_800144D4(void)
{
    extern s32 D_80126950;

    D_80126950 = 300;
    func_80053308(300);
    D_80126984 = 0;
    D_80126988 = 0;
    D_8012698C = -300;
    D_80126990 = 0;
    D_80126994 = 0;
    D_80126998 = 0;
    D_8012699C = 0;
    D_801269A0 = 0;
    func_80053F6C(&D_80126984);
}

void func_80014554(void) {
}

void func_8001455C(void) {
}

void func_80014564(void *arg0) {
    extern void func_8005C358(void *a0, s32 a1, s32 a2);
    func_8005C358(arg0, 0, 0x10);
}

typedef struct {
    /* 0x00 */ s16 flag;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ void *list;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u16 unk0E;
} DispSlot_800184F0_80014588;

void func_80014588(void) {
    extern void func_8005C358(void *a0, s32 a1, s32 a2);
    extern DispSlot_800184F0_80014588 D_800B97D8[];
    DispSlot_800184F0_80014588 *slot;
    s16 i;

    slot = D_800B97D8;
    for (i = 0; i < 32; i++) {
        slot->flag = 0;
        func_8005C358(slot, 0, 0x10);
        slot++;
    }
}

void func_800145EC(s32 mode) {
    extern void func_800525DC(s32 w, s32 h, s32 mode2, s32 a3, s32 st);
    extern void func_80053178(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80059234(s32);
    extern void func_80053218(void);
    extern void func_80014774(void);
    extern void func_800147B8(void);
    extern u8 D_80062A3C[];
    extern u8 D_80062A3E[];
    extern u8 D_80062A40[];
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern u16 D_800AF7C0;
    s32 off;

    off = (mode & 0xFFFF) * 6;

    D_800AF7BC = *(u16 *) (D_80062A3C + off);
    D_800AF7BE = *(u16 *) (D_80062A3E + off);
    D_800AF7C0 = *(u16 *) (D_80062A40 + off);

    func_800525DC(D_800AF7BC, D_800AF7BE, D_800AF7C0 | 4, 0, 0);

    if (D_800AF7BE == 0x1E0) {
        func_80053178(0, 0, 0, 0);
    } else {
        func_80053178(0, D_800AF7BE, 0, 0);
    }

    func_80059234(1);
    func_80053218();
    func_80014774();
    func_800147B8();
}

void func_800146B0(s32 mode) {
    extern void GsInitGraph2(s32 w, s32 h, s32 mode, s32 a3, s32 st);
    extern void func_80053EEC(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_80059234(s32);
    extern void func_80053218(void);
    extern void func_80014774(void);
    extern void func_800147B8(void);
    extern u8 D_80062A3C[];
    extern u8 D_80062A3E[];
    extern u8 D_80062A40[];
    extern u16 D_800AF7BC;
    extern u16 D_800AF7BE;
    extern u16 D_800AF7C0;
    s32 off;

    off = (mode & 0xFFFF) * 6;

    D_800AF7BC = *(u16 *) (D_80062A3C + off);
    D_800AF7BE = *(u16 *) (D_80062A3E + off);
    D_800AF7C0 = *(u16 *) (D_80062A40 + off);

    GsInitGraph2(D_800AF7BC, D_800AF7BE, D_800AF7C0 | 4, 0, 0);

    if (D_800AF7BE == 0x1E0) {
        func_80053EEC(0, 0, 0, 0);
    } else {
        func_80053EEC(0, D_800AF7BE, 0, 0);
    }

    func_80059234(1);
    func_80053218();
    func_80014774();
    func_800147B8();
}


extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);

void func_80014774(void) {
    s16 local[4];

    local[0] = 0;
    local[1] = 0;
    local[2] = 0x280;
    local[3] = 0x1E0;

    func_80059888((void *)local, 0, 0, 0);
}


extern u8 D_800AF630[];
extern u16 D_800AF7BE;
extern u16 D_800AF7BC;

extern u16 D_800AF672;
extern u16 D_800AF670;
extern u16 D_800AF6CC;
extern u16 D_800AF6D6;
extern u16 D_800AF6D4;
extern u16 D_800AF67A;
extern u16 D_800AF678;
extern u16 D_800AF6CE;
extern u8 D_800AF6DA;
extern u8 D_800AF67E;
extern u8 D_800AF6DC;
extern u8 D_800AF680;

extern void *func_80058A4C(void *env, s32 x, s32 y, s32 w, s32 h);
extern void *SetDefDispEnv(void *env, s32 x, s32 y, s32 w, s32 h);
extern void func_80014960(void);

void func_800147B8(void) {
    u8 *base = D_800AF630;
    register s32 raw_h __asm__("$3") = D_800AF7BE;
    s32 h_offset = raw_h;
    u16 halfW;
    u16 halfH;
    s16 h;

    if (h_offset == 0x1E0) {
        h_offset = 0;
    }

    func_80058A4C(base + 0x38, 0, 0xA, D_800AF7BC, D_800AF7BE - 0x14);
    SetDefDispEnv(base + 0x14C, 0, 0, D_800AF7BC, D_800AF7BE);
    func_80058A4C(base + 0x94, 0, h_offset + 0xA, D_800AF7BC, D_800AF7BE - 0x14);
    SetDefDispEnv(base + 0x160, 0, h_offset, D_800AF7BC, D_800AF7BE);

    halfW = D_800AF7BC >> 1;
    halfH = D_800AF7BE >> 1;
    D_800AF672 = halfH;
    D_800AF670 = halfW;
    D_800AF6CC = halfW;

    h = (D_800AF7BE == 0xF0) ? 0x168 : 0xF0;

    D_800AF6D6 = 0x100;
    D_800AF6D4 = 0x100;
    D_800AF67A = 0x100;
    D_800AF678 = 0x100;
    D_800AF6CE = h;
    D_800AF6DA = 0;
    D_800AF67E = 0;
    D_800AF6DC = 1;
    D_800AF680 = 1;

    func_80014960();
}


extern void func_8005CF08(void);
extern void InitHeap(void *a0, s32 a1);
extern void func_8005CF18(void);

void func_80014928(void) {
    func_8005CF08();
    InitHeap((void *)0x801FF800, 0x800);
    func_8005CF18();
}


extern void func_80014998(void);
extern u8 D_800AF7C4;
extern u8 D_800AF7C3;
extern u8 D_800AF7C2;

void func_80014960(void) {
    D_800AF7C4 = 0;
    D_800AF7C3 = 0;
    D_800AF7C2 = 0;
    func_80014998();
}

extern u8 D_800AF630[];

void func_80014998(void) {
    u8 *p;
    s32 i;

    p = D_800AF630;
    for (i = 0; i < 2; i++) {
        p[i * 0x5C + 0x51] = p[0x192];
        p[i * 0x5C + 0x52] = p[0x193];
        p[i * 0x5C + 0x53] = p[0x194];
    }
}


extern u8 D_80078DD2;

extern u8 func_80014C28(u32 a0);
extern u8 func_80014CF8(u32 a0, u32 a1);
extern u8 func_80014D30(u32 a0, u32 a1);

s32 func_800149E0(s32 a0) {
    u8 b0;
    u16 val;
    s32 c;
    u16 h1;
    u16 h2;
    u16 m1;
    u16 m2;
    u16 v1;

    b0 = a0 & 0xFF;
    val = *(u16*)((u32)&D_80078DD2 + (u32)(b0 * 76));
    if (val != 0) {
        return val;
    }

    c = func_80014C28(b0) & 0xFF;
    if (c != 'S') {
        if (c < 'T') {
            return 0;
        }
        if (c != 's') {
            return 0;
        }
    }

    b0 = a0 & 0xFF;
    h1 = func_80014D30(b0, 5) & 0xFF;
    h2 = func_80014D30(b0, 4) & 0xFF;
    m1 = func_80014CF8(b0, 5) & 0xFF;
    m2 = func_80014CF8(b0, 4) & 0xFF;

    v1 = 0;
    if (h1 == 0x80) {
        if (m1 != h1) {
            if (m1 >= 0x80) {
                v1 = 0x4000;
            } else {
                v1 = 0x1000;
            }
        }
    }

    if (h2 != 0x80) {
        return v1;
    }
    if (m2 != h2) {
        if (m2 < 0x80) {
            v1 |= 0x8000;
        } else {
            v1 |= 0x2000;
        }
    }
    return v1;
}


extern u8 D_80078DCA;
extern u8 func_80014C28(u32 a0);
extern u8 func_80014CF8(u32 a0, u32 a1);

s32 func_80014B10(s32 a0) {
    u8 b0;
    u16 val;
    s32 c;
    u16 m1;
    u16 m2;
    u16 v1;

    b0 = a0 & 0xFF;
    val = *(u16 *)((u32)&D_80078DCA + (u32)(b0 * 76));
    if (val != 0) {
        return val;
    }

    c = func_80014C28(b0) & 0xFF;
    if (c != 'S') {
        if (c < 'T') {
            return 0;
        }
        if (c != 's') {
            return 0;
        }
    }

    b0 = a0 & 0xFF;
    m1 = func_80014CF8(b0, 5) & 0xFF;
    m2 = func_80014CF8(b0, 4) & 0xFF;

    v1 = 0;
    if (m1 != 0x80) {
        if (m1 >= 0x80) {
            v1 = 0x4000;
        } else {
            v1 = 0x1000;
        }
    }

    if (m2 == 0x80) {
        return v1;
    } else if (m2 < 0x80) {
        v1 |= 0x8000;
    } else {
        v1 |= 0x2000;
    }
    return v1;
}


extern u16 D_80078DDA;

u16 func_80014BFC(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    return *(u16*)((u32)&D_80078DDA + offset);
}


extern u8 D_80078D98;

u8 func_80014C28(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    return *(u8*)(offset);
}

extern u8 D_80078D98;

/* dual flag-half tester: selects unk32/unk3A of record (a0&0xFF)*76 by (a1&0xFF)==1,
 * returns ((sel & a2) == a2); gcc keeps one 'and' per arm, one riding the j delay slot */
s32 func_80014C54(s32 a0, s32 a1, s32 a2) {
    u8 *p;
    u16 result;

    p = (u8 *)((u32)&D_80078D98 + (a0 & 0xFF) * 76);
    a1 &= 0xFF;

    if (a1 == 1) {
        result = *(u16 *)(p + 0x32);
    } else {
        result = *(u16 *)(p + 0x3A);
    }

    return (u32)(((u32)result & (u32)a2) ^ (u32)a2) < 1;
}

extern u8 D_80078DCA;
extern u8 D_80078DD2;

u8 func_80014CAC(u32 arg0, u32 arg1)
{
    extern u16 D_80078E16;
    extern u16 D_80078E1E;
    u16 var_v0;

    if ((arg0 & 0xFF) == 1) {
        var_v0 = *(u16 *)&D_80078DCA | D_80078E16;
    } else {
        var_v0 = *(u16 *)&D_80078DD2 | D_80078E1E;
    }
    return (var_v0 & arg1) != 0;
}


extern u8 D_80078D98;

u8 func_80014CF8(u32 a0, u32 a1) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    a1 &= 0xFF;
    offset = offset + a1;
    return *(u8*)(offset + 0x32);
}


extern u8 D_80078D98;

u8 func_80014D30(u32 a0, u32 a1) {
    u32 v0;
    a0 = a0 & 0xFF;
    v0 = a0 << 2;
    v0 = v0 + a0;
    v0 = v0 << 2;
    v0 = v0 - a0;
    v0 = v0 << 2;
    v0 = v0 + (u32)&D_80078D98;
    a1 = a1 & 0xFF;
    v0 = v0 + a1;
    return *(u8*)(v0 + 0x42);
}


extern u8 D_80078DCA;

u16 func_80014D68(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078DCA;
    return *(u16*)offset;
}


extern u8 D_80078DD2;

s32 func_80014D94(s32 a0) {
    a0 &= 0xFF;
    return *(u16*)((u32)&D_80078DD2 + (a0 * 76));
}


extern u8 D_80078D98;

u8 func_80014DC0(u32 a0) {
    u32 offset;
    a0 &= 0xFF;
    offset = a0 * 76;
    offset = offset + (u32)&D_80078D98;
    return *(u8*)offset;
}


extern u8 D_80078D98;

u8 func_80014DEC(s32 a0, s32 a1) {
    register s32 v0 __asm__("$2");
    a0 = a0 & 0xFF;
    v0 = (a0 << 2) + a0;
    v0 = (v0 << 2) - a0;
    v0 = v0 << 2;
    v0 = v0 + (s32)&D_80078D98;
    a1 = a1 & 0xFF;
    v0 = v0 + a1;
    return *(u8 *)(v0 + 0x32);
}


extern s32 func_80015018(s32 a0);
extern s32 func_80014ED4(s32 a0);

s32 func_80014E24(s32 a0, s32 a1, s32 a2) {
    u16 result;
    s32 tmp;

    /* a0's masked-byte value is genuinely consumed as an argument to BOTH callees below
     * (their bodies happen to ignore it, but the caller must still materialize it) --
     * the opaque asm keeps gcc-2.7.2 from folding this into a per-branch recompute or
     * eliding it outright, which is what a plain "a0 &= 0xFF;" statement does when a0
     * is otherwise unused. See matching-cookbook.md L2916 (opaque asm-COPY) for the
     * precedent: a real, non-hard-reg opcode asm is used only when no pure-C spelling
     * reproduces the target's single, pre-branch materialization. */
    __asm__("andi %0, %1, 0xff" : "=r"(tmp) : "r"(a0));

    a1 &= 0xFF;

    if (a1 == 1) {
        result = func_80015018(tmp);
    } else {
        result = func_80014ED4(tmp);
    }

    result &= 0xFFFF;

    // Check if all bits of a2 are set in result
    return (u32)(((u32)result & (u32)a2) ^ (u32)a2) < 1;
}


extern s32 func_80015018(s32 a0);
extern s32 func_80014ED4(s32 a0);

s32 func_80014E80(s32 a0, s32 a1) {
    s32 result;
    a0 = a0 & 0xFF;
    if (a0 == 1) {
        result = func_80015018(0);
    } else {
        result = func_80014ED4(0);
    }
    result = result & 0xFFFF;
    result = result & a1;
    return (result != 0) ? 1 : 0;
}


extern u8 D_80078D98;
extern void func_80015118(u16 *a0);

s32 func_80014ED4(s32 a0) {
    u8 *p;
    u8 *p2;
    u16 val;
    s32 c;
    u16 buf[4];
    s32 flags;

    p = (u8 *)((u32)&D_80078D98 + (a0 & 0xFF) * 76);
    val = *(u16 *)(p + 0x3A);
    if (val != 0) {
        return val;
    }

    c = *p;
    if (c != 'S') {
        if (c < 'T') {
            return 0;
        }
        if (c != 's') {
            return 0;
        }
    }

    p2 = (u8 *)((u32)&D_80078D98 + (a0 & 0xFF) * 76);
    buf[0] = *(p2 + 0x47);
    buf[1] = *(p2 + 0x46);
    buf[2] = *(p2 + 0x37);
    buf[3] = *(p2 + 0x36);
    func_80015118(&buf[0]);
    func_80015118(&buf[1]);
    func_80015118(&buf[2]);
    func_80015118(&buf[3]);

    flags = 0;
    if (buf[0] == 0x80) {
        if (buf[2] != 0x80) {
            if (buf[2] >= 0x80) {
                flags = 0x4000;
            } else {
                flags = 0x1000;
            }
        }
    }
    if (buf[1] == 0x80) {
        if (buf[3] != 0x80) {
            flags |= (buf[3] < 0x80) ? 0x8000 : 0x2000;
        }
    }
    return flags & 0xFFFF;
}


extern u8 D_80078D98;
extern void func_80015118(u16 *arg);

s32 func_80015018(s32 a0) {
    u8 *p;
    u8 *q;
    u16 val;
    u16 tmp[2];
    s32 result;

    p = (u8 *)&D_80078D98 + (a0 & 0xFF) * 76;
    val = *(u16 *)(p + 0x32);
    if (val != 0) {
        return val;
    }

    {
        s32 c = *p;
        if (c != 0x53) {
            if (c < 0x54) {
                return 0;
            }
            if (c != 0x73) {
                return 0;
            }
        }
    }

    q = (u8 *)&D_80078D98 + (a0 & 0xFF) * 76;
    tmp[0] = *(q + 0x37);
    tmp[1] = *(q + 0x36);
    func_80015118(&tmp[0]);
    func_80015118(&tmp[1]);

    result = 0;
    if (tmp[0] != 0x80) {
        if (tmp[0] >= 0x80) {
            result = 0x4000;
        } else {
            result = 0x1000;
        }
    }

    if (tmp[1] != 0x80) {
        if (tmp[1] < 0x80) {
            result |= 0x8000;
        } else {
            result |= 0x2000;
        }
    }

    return result & 0xFFFF;
}

void func_80015118(u16 *a0) {
    if ((u32)(*a0 - 0x15) < 0xD7) {
        *a0 = 0x80;
    }
}

void func_8001513C(void) {
}


extern s32 CdQueueBusy(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8003500C(void);
extern void func_8002D034(void);
extern int VSync(int mode);
extern s32 func_8001AA78(void);
extern void func_8002F67C(void);
extern void LoaderResetReadState(void);

extern u8 D_800AF630[];
extern s16 D_800B9A04[];

s32 func_80015144(void) {
    u8* base = D_800AF630;

    if (CdQueueBusy() != 0) {
        func_8002D4C8(2, 0);

        while (1) {
            func_8003500C();
            func_8002D034();
            VSync(*(s32*)(base + 0xA3E8));
            if (CdQueueBusy() == 0) {
                break;
            }
        }

        *(s16*)(base + 0xA3D4) = 1;
    } else {
        if (func_8001AA78() != 0) {
            return 0;
        }
        D_800B9A04[0] = 1;
        func_8002D4C8(2, 0);
    }

    func_8002F67C();
    LoaderResetReadState();
    return 1;
}


extern u8 D_800B9A64;
extern u8 D_800B9A10;
extern u8 D_800B9A17;
extern u8 D_800B9A15;
extern u8 D_800B9A16;
extern u8 D_800B9A13;
extern u8 D_80078DD2;
extern s32 D_800A5E78;
extern u8 D_800AF630[];
extern void func_801281D8(void);

void func_80015208(void) {
    u8 flag0;
    s32 v;
    register u8 *base __asm__("$5");

    flag0 = D_800B9A64;
    base = D_800AF630;

    if (flag0) {
        return;
    }
    __asm__ __volatile__("" : "=r"(base) : "0"(base));
    if (D_800B9A10 != 1) {
        return;
    }
    if (D_800B9A17 != D_800B9A10) {
        return;
    }
    if (D_800B9A15 == D_800B9A17) {
        return;
    }
    if (D_800B9A16 != 0) {
        D_800B9A15 = 1;
        return;
    }
    if (D_800B9A13 != 0) {
        return;
    }

    {
        s32 mask = 0x800;

        __asm__ __volatile__("" : "=r"(mask) : "0"(mask));
        if ((*(u16 *)&D_80078DD2 & 0x800) == mask) {
            v = 1;
            __asm__ __volatile__("" : "=r"(v) : "0"(v));
        } else {
            v = 0;
        }
        if (!v) {
            if (D_800A5E78 != 0) {
                return;
            }
        }
        v = 1;
        base[0xA3E5] = v;
        func_801281D8();
    }
}

extern s16 D_800B93D8[];

void func_800152F4(s32 idx) {
    D_800B93D8[((idx << 16) >> 16) * 8] = 0;
}



extern s16 D_800B93D8[];

void func_80015310(void) {
    extern DispSlot_800184F0 D_800B97D8[];
    s32 pad[2];
    DispSlot_800184F0 *p;
    DispSlot_800184F0 *end;

    p = (DispSlot_800184F0 *)D_800B93D8;
    end = D_800B97D8;
    for (; p < end; p++) {
        p->flag = 0;
    }
}

extern u8 D_800AF630[];

void func_8001534C(s32 idx, s32 a1, s16 x, s16 y, u8 arg4, u8 arg5) {
    u8 *p;
    s32 off;

    p = D_800AF630;
    off = (s16)idx * 16 + 0x9DA8;
    func_800153A4(p + off, a1, x, y, arg4, arg5);
}


void func_800153A4(void *a0, s32 a1, s16 a2, s16 a3, u8 arg4, u8 arg5) {
    *(s16 *)(a0 + 0) = 1;
    *(s16 *)(a0 + 2) = a2;
    *(s16 *)(a0 + 4) = a3;
    *(s32 *)(a0 + 8) = a1;
    *(u8 *)(a0 + 12) = arg4;
    *(u8 *)(a0 + 13) = arg5;
}

extern u8 D_800AF630[];

void func_800153CC(s32 arg0, s32 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5) {
    u8 *base;
    base = D_800AF630;
    func_80015424(&base[((arg0 << 16) >> 12) + 0x9DA8], arg1, arg2, arg3, arg4, arg5);
}


void func_80015424(void *a0, s32 a1, s16 a2, s16 a3, s8 a4, s8 a5) {
    *(s16 *)a0 = 2;
    *(s16 *)(a0 + 2) = a2;
    *(s16 *)(a0 + 4) = a3;
    *(s32 *)(a0 + 8) = a1;
    *(s8 *)(a0 + 0xC) = a4;
    *(s8 *)(a0 + 0xD) = a5;
}


extern s16 D_800B93D8[];

s16 *func_8001544C(void) {
    extern DispSlot_800184F0 D_800B97D8[];
    s16 *p;
    s16 *end;
    s16 v;
    s32 pad[2];

    p = D_800B93D8;
    end = (s16 *)D_800B97D8;
    if (p >= end) {
        return 0;
    }
    do {
        v = *p;
        if (v == 0) {
            return p;
        }
        p += 8;
    } while (p < end);
    return 0;
}



extern u16 D_800B9A02;
extern u8 D_800B9A11;
extern u8 D_800AF630[];
extern u8 *D_800A5E60;
extern s32 GetTPage(s32, s32, s32, s32);
extern void func_80015608(s32, s32);
extern void func_80015760(s32, s32);

void func_80015498(void)
{
    extern OtBlk_80016450 D_800A651C[];
    u8 *base;
    u32 *ot;
    u8 *entry;
    u8 *end;
    u8 *p;
    s16 v1;
    s32 tp;
    register u32 tag0 __asm__("$4");
    register u32 maskLo __asm__("$5");

    base = D_800AF630;
    ot = (u32 *)D_800A651C[D_800B9A02].a;

    if (D_800B9A11 != 1) {
        entry = base + 0x9DA8;
        if (entry < base + 0xA1A8) {
            register s16 one __asm__("$20") = 1;
            register s16 two __asm__("$19") = 2;
            end = base + 0xA1A8;
            do {
                v1 = *(s16 *)entry;
                if (v1 == one) {
                    goto do_call1;
                }
                if (v1 < 2) {
                    goto incr_shared;
                }
                if (v1 == two) {
                    goto do_call2;
                }
                entry += 0x10;
                continue;
            do_call1:
                func_80015608((s32)entry, (s32)ot);
                entry += 0x10;
                continue;
            do_call2:
                func_80015760((s32)entry, (s32)ot);
            incr_shared:
                entry += 0x10;
            } while (entry < end);
        }

        p = D_800A5E60;
        p[3] = 1;
        tp = GetTPage(0, 0, 0x140, 0x100);
        maskLo = 0xFFFFFF;
        tag0 = *(u32 *)p;
        *(u32 *)(p + 4) = (tp & 0x9FF) | 0xE1000000;
        *(u32 *)p = (tag0 & 0xFF000000) | (*ot & maskLo);
        p = (u8 *)((u32)p & maskLo);
        {
            u32 g = (u32)D_800A5E60;
            u32 o = *ot;
            D_800A5E60 = (u8 *)(g + 8);
            *ot = (o & 0xFF000000) | (u32)p;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80015608);

INCLUDE_ASM("asm/nonmatchings/800", func_80015760);

INCLUDE_ASM("asm/nonmatchings/800", func_80015908);

void func_80015954(s32 a0, s32 a1) {
    *(u16 *)(a1 + 0x2) = *(u16 *)(a0 + 0x0);
    *(u16 *)(a1 + 0x6) = *(u16 *)(a0 + 0x2);
    *(u16 *)(a1 + 0xA) = *(u16 *)(a0 + 0x4);
}

void func_80015978(s32 *a0, s32 *a1) {
    *(u16 *)((s32)a1 + 0x0) = *(u16 *)((s32)a0 + 0x2);
    *(u16 *)((s32)a1 + 0x2) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)((s32)a1 + 0x4) = *(u16 *)((s32)a0 + 0xA);
}

void func_8001599C(s32 a0, s32 a1) {
    *(s32 *)(a1 + 0x0) = *(s32 *)(a0 + 0x0);
    *(s32 *)(a1 + 0x4) = *(s32 *)(a0 + 0x4);
    *(s32 *)(a1 + 0x8) = *(s32 *)(a0 + 0x8);
}

void func_800159C0(s32 a0, s32 a1) {
    *(s32 *)(a1 + 0x0) = *(s32 *)(a0 + 0x0);
    *(s32 *)(a1 + 0x4) = *(s32 *)(a0 + 0x4);
    *(s32 *)(a1 + 0x8) = *(s32 *)(a0 + 0x8);
}

void func_800159E4(s32 *a0, s32 *a1) {
    *(u16 *)((s32)a1 + 0x2) = *(u16 *)((s32)a0 + 0x2);
    *(u16 *)((s32)a1 + 0x6) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)((s32)a1 + 0xA) = *(u16 *)((s32)a0 + 0xA);
}

void func_80015A08(s32 *a0, s32 *a1) {
    *(u16 *)((s32)a1 + 0x0) = *(u16 *)((s32)a0 + 0x0);
    *(u16 *)((s32)a1 + 0x4) = *(u16 *)((s32)a0 + 0x4);
    *(u16 *)((s32)a1 + 0x8) = *(u16 *)((s32)a0 + 0x8);
}

void func_80015A2C(short* arg0, int* arg1) {
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
}

void func_80015A50(s32 *arg0, s16 *arg1) {
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
}

#ifdef NON_MATCHING
/* uint -> packed BCD (9 digits, ÷ powers of 10). All idioms match under the pinned
 * triple (divu+break div-by-zero via --expand-div, multu 0xCCCCCCCD + srl 3 for ÷10);
 * residual diff is a loop-setup instruction-scheduling permutation (li counter vs the
 * hoisted magic constant) — a decomp-permuter target. See docs/matching-cookbook.md. */
u32 func_80015A74(u32 param_1) {
    u32 result;
    s32 i;
    u32 divisor;

    divisor = 1000000000;
    result = 0;
    for (i = 9; i >= 0; i--) {
        result = (result << 4) | (param_1 / divisor);
        param_1 = param_1 % divisor;
        divisor = divisor / 10;
    }
    return result;
}
#else
unsigned int func_80015A74(unsigned int param_1) {
    unsigned int result;
    unsigned int divisor;
    int i;

    divisor = 1000000000;
    result = 0;
    for (i = 0; i < 10; i++) {
        result = (result << 4) | (param_1 / divisor);
        param_1 = param_1 % divisor;
        divisor = divisor / 10;
    }
    return result;
}
#endif

extern s32 catan(s32 a0);

s32 func_80015AD0(s16 param_1, s16 param_2) {
    s32 quotient;

    if (param_2 == 0) {
        param_2 = 1;
    }
    quotient = catan((param_1 << 12) / param_2);
    if (param_2 < 0) {
        if (param_1 < 0) {
            goto subtract;
        }
        quotient += 0x800;
    }
    return quotient;
subtract:
    quotient -= 0x800;
    return quotient;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80015B6C);


/* func_80015D4C — allocate an 0x18-byte flat-shaded quad GPU packet, fill its
 * tag/color/code bytes and the four (x,y) corners from (a0,a1,a2,a3) =
 * (x, y, w, h), then link it into the current double-buffer's OT at depth
 * arg7 via the open-coded PSY-Q `addPrim` RMW pair, and (only when arg8 < 4)
 * notify func_80016638.
 *
 * Sibling idiom: src/md_SC07_004/md_SC07_004.c func_801AADA8 (MATCHED) —
 * the addPrim pair over D_800A651C[bidx].a in ARRAY_REF form, and the
 * func_80016638(&D_800A6518[bidx*20], depth, flag) call form.
 *
 * SECOND-PASS FIXES (this file was NEAR/40 before; both were required):
 *
 *  1. BRANCH POLARITY WAS INVERTED.  The target is
 *         sltiu $t2, $s0, 0x4   ;  beqz $t2, <skip>
 *     i.e. the 0x2A code byte is written and func_80016638 is called when
 *     arg8 < 4, not when arg8 >= 4.  The first pass wrote `arg8 >= 4`, which
 *     emits the same sltiu but `bnez` — a real semantic difference that the
 *     instruction-shape diff hid inside the 40-instruction register cascade.
 *
 *  2. tag0 PINNED TO $4 ($a0) — the load-bearing regalloc fix.  Residual was
 *     a *uniform +1 register-slot shift*: target allocates the call-clobbered
 *     pseudo set {a0,a1,a2,a3,t0,t1,t2,t3}, the draft allocated
 *     {v1,a0,a1,a2,a3,t0,t1,t2}.  Root cause: gcc's sched1 placed the tag
 *     load (`lw <tag0>, 0(p)`) *after* the last use of the x+w temp, so tag0
 *     could reuse $v1; the target schedules the tag load 14 insns earlier, so
 *     the two live ranges overlap and tag0 must take $a0, pushing every later
 *     pseudo up one slot.
 *     Statement-order (lever A) is INERT here — sweeping the `tag0 = *(u32*)p`
 *     statement through all 6 legal source positions between the p[7]
 *     conditional and the addPrim pair gave 40 mismatched every time; sched1
 *     normalises the DAG regardless of source position.  The register pin is
 *     what changes the allocation, and pinning tag0 (the value whose slot
 *     *causes* the cascade) is the right handle — this is exactly the lever
 *     func_801AADA8's own header documents ("tag0 ... pinned to $4 ($a0) —
 *     needed to reproduce the target's exact a2/a3/t0/t1 register picks for
 *     the addPrim RMW pair").
 *     Pin sweep, for the record: $4 -> MATCH, $5 -> 9, $6 -> 16, $7 -> 16,
 *     $8 -> 31.  Note the first pass pinned temp_v0 instead ($8) and got a
 *     spurious extra move — pinning the *consumer* of the cascade rather than
 *     its cause (cookbook §175 lever B: pin the interloper, not the value you
 *     care about; here the interloper is the tag word aliasing $v1).
 *
 * vx/vy stay pinned to $18/$17 ($s2/$s1) from the first pass — the target's
 * `addu $s2,$s3,$zero` / `addu $s1,$s4,$zero` corner-copy pair.
 *
 * Symbol audit (§174 law 1c, done after MATCH): every symbol re-checked
 * against the target .s relocation lines — jal func_80010A08, jal
 * func_80016638, %hi/%lo(D_800B9A02) via lhu (u16, not s16), %hi/%lo
 * (D_800A651C) via lw, %lo(D_800A6518) via addiu (address-of).  Store sides
 * verified: `sw $a0,0($t0)` is the packet tag, `sw $v0,0($a1)` is the OT slot.
 * src/800.c declares none of these, so no TU-declaration conflict (law 2/3).
 */

extern void *func_80010A08(s32 a0);
extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern void func_80016638(void *a0, s32 a1, s32 a2);

void func_80015D4C(s32 a0, s32 a1, s32 a2, s32 a3, u8 arg4, u8 arg5, u8 arg6, u16 arg7, u16 arg8)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar in their own bodies */
    void *temp_v0;
    register s16 vx __asm__("$18");
    register s16 vy __asm__("$17");
    register u32 tag0 __asm__("$4");
    s32 depth4;

    temp_v0 = func_80010A08(0x18);
    *(u8 *)((u8 *)temp_v0 + 3) = 5;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x28;
    vx = a0;
    vy = a1;
    if (arg8 < 4) {
        *(u8 *)((u8 *)temp_v0 + 7) = 0x2A;
    }

    *(u8 *)((u8 *)temp_v0 + 4) = arg4;
    *(u8 *)((u8 *)temp_v0 + 5) = arg5;
    *(u8 *)((u8 *)temp_v0 + 6) = arg6;
    *(s16 *)((u8 *)temp_v0 + 8) = vx;
    *(s16 *)((u8 *)temp_v0 + 0xA) = vy;
    *(s16 *)((u8 *)temp_v0 + 0xC) = a0 + a2;
    *(s16 *)((u8 *)temp_v0 + 0xE) = vy;
    *(s16 *)((u8 *)temp_v0 + 0x10) = vx;
    tag0 = *(u32 *)temp_v0;
    *(s16 *)((u8 *)temp_v0 + 0x12) = a1 + a3;
    *(s16 *)((u8 *)temp_v0 + 0x14) = a0 + a2;
    *(s16 *)((u8 *)temp_v0 + 0x16) = a1 + a3;

    depth4 = arg7 * 4;
    *(u32 *)temp_v0 = (tag0 & 0xFF000000) |
        (*(u32 *)(depth4 + D_800A651C[D_800B9A02].a) & 0xFFFFFF);
    *(u32 *)(depth4 + D_800A651C[D_800B9A02].a) =
        (*(u32 *)(depth4 + D_800A651C[D_800B9A02].a) & 0xFF000000) |
        ((u32)temp_v0 & 0xFFFFFF);
    if (arg8 < 4) {
        func_80016638(&D_800A6518[D_800B9A02 * 20], arg7, arg8);
    }
}


/* func_80015F04 — main/800.  Build a 4-segment closed LINE_F2 wireframe
 * rectangle: fill an 8-halfword stack corner list from (x, y, w, h) =
 * (a0, a1, a2, a3), allocate one 0x40-byte GPU block (4 x 0x10 LINE_F2),
 * then loop i = 0..3 writing one segment per packet (corner i -> corner i+1,
 * code 0x40, or 0x42 = semi-transparent when arg8 < 4) and linking each packet
 * into the current OT at depth arg7 with the open-coded PSY-Q addPrim RMW
 * pair.  The i == 3 iteration reads pts[4] (one past the array — the original
 * code's own overrun); the segment is closed afterwards by rewriting the last
 * packet's (x1, y1) from pts[0].  Finally, when arg8 < 4, notify
 * func_80016638 with the env block.
 *
 * @class: MATCH — 131/131 byte-exact (relocation-masked), and
 *   tools/reloc_identity.py AGREE (relocs_checked=6): every jal / %hi / %lo
 *   names the same symbol the target .s names.
 *
 * ===================================================================
 * THE ENTRY-BLOCK FILLER PROBLEM AND THE THREE LEVERS THAT SOLVE IT
 *
 * The prologue is emitted as [addiu $sp][$v0=$a0][sw $s0][la $s0] then five
 * (save, stack-arg-load, FILLER) triples.  The five fillers are exactly
 *      A  = `addiu $a0,$zero,0x40`      (the func_80010A08 argument)
 *      X0 = `addu $t0,$v0,$zero`        (x0 = a0)
 *      Y0 = `addu $v1,$a1,$zero`        (y0 = a1)
 *      X1 = `addu $v0,$v0,$a2`          (a0 += a2)
 *      Y1 = `addu $a1,$a1,$a3`          (a1 += a3)
 * and the target order is A, X0, Y0, X1, Y1.  All five tie at INSN_PRIORITY 1,
 * so the order is decided in sched1 by `rank_for_schedule`'s LUID tie-break and
 * by `adjust_priority`'s BIRTHING BOOST (sched.c:2507 / birthing_insn_p:2469 —
 * a `SET(REG,…)` whose dest is live and has REG_N_SETS == 1 is raised to
 * max_priority, dump tell `(7f000001)`).  sched1 picks BACKWARD and emits in
 * reverse, so a boosted def is picked EARLY and therefore emitted LATE.
 *
 * Reading the `-dS` ready-list trace, the block resolves like this (AC probe):
 *      T-19 pick Y1  (Y1 is the anti-dep gate on Y0)
 *      T-20..T-24    the five boosted stack-arg loads
 *      T-25 pick X1  (X1 is the anti-dep gate on X0: X1 writes the pseudo X0
 *                     reads, so X0 cannot become ready until X1 is scheduled)
 *      T-26 pick ?   ready = {Y0, X0, A, base}
 *      T-27 pick ?
 *      T-28 A,  T-29 base
 * Emission is the reverse of the pick order, so the TARGET needs Y0 picked at
 * T-26 and X0 at T-27.  With both copies tying at priority 1 that falls out of
 * the LUID order (`x0 = a0;` written before `y0 = a1;`).  Any boost on X0
 * makes X0 win T-26 and the two swap — which is the entire residual the first
 * two passes were stuck on.
 *
 * LEVER 8 — PIN THE CALL ARGUMENT AND EMIT IT AS ASM.  gcc sets a call's
 *   argument registers immediately before the `jal`, so A always had the
 *   HIGHEST LUID in the block, was always picked first, and was therefore
 *   always emitted LAST (filler #5 instead of #1).  The call cannot be moved
 *   earlier — `flush_pending_lists` gives it a REG_DEP_ANTI on all eight `sh`
 *   stores — so the fix is to give the `li` a LUID at its SOURCE position:
 *       register s32 sz __asm__("$4");
 *       __asm__("addiu %0,$zero,0x40" : "=r"(sz));
 *   A plain `sz = 0x40;` does NOT work (cse copies REG_EQUAL 64 onto the
 *   call-site no-op `(set $a0 $a0)` and flow dead-store-eliminates the early
 *   set; `volatile` on the register var costs 25/131).  Emitting the
 *   instruction FROM the asm sticks: one RTL insn, the target's own bytes
 *   0x24040040, LUID at the source position, and the call's `$a0 = sz`
 *   collapses to a deleted no-op move.  Worth 2 instructions.
 *
 * LEVER 9 — KILL Y0's BOOST FOR FREE BY MERGING IT WITH `ob`.  y0 and the
 *   loop's second-addPrim OT base are BOTH $v1 with disjoint live ranges, so
 *   they are ONE variable.  That gives the pseudo a second SET, REG_N_SETS
 *   becomes 2, and the boost dies at zero instruction cost.  (This is why
 *   there is no `y0` local below — `ob` carries both roles.)
 *
 * LEVER 10 (THE THIRD PASS'S LEVER, the 2 -> 0) — KILL X0's BOOST WITH A
 *   RE-TIE THAT CARRIES A "memory" CLOBBER.
 *       __asm__("" : "=r"(x0) : "0"(x0) : "memory");
 *   The §30 #3 re-tie gives x0 a second SET and kills its boost, which fixes
 *   all five fillers — but a BARE re-tie then costs one swap somewhere else
 *   (`sw $ra,0x38($sp)` and `sh $t0,0x10($sp)` trade places, probes ACq1-ACq6,
 *   all 2/131).  Reason: the bare asm's only ordering constraint is the
 *   anti-dependence on the one store that reads the OLD x0, so sched2 is free
 *   to treat it as a SIXTH entry-block filler; with six fillers for five
 *   (save, load) triples the extra one drags `sh $t0,0x10($sp)` up past the
 *   `sw $ra` save.
 *   ADDING "memory" fixes exactly that: the clobber makes the asm a
 *   memory-ordering barrier, so `sched_analyze` ties it to the whole pending
 *   store list instead of to one register, it can no longer float into the
 *   (save, load, filler) interleave, and the five real fillers keep the
 *   triples to themselves.  It is a pure scheduling fence — zero emitted
 *   bytes, zero registers, no effect on allocation.
 *   Byte-verified: the "memory" re-tie MATCHes at every placement from before
 *   `pts[0].x` through before `pts[3].x` (probes Rm0-Rm6); the bare re-tie is
 *   2/131 at every one of those placements (Rp1-Rp6).  The `volatile` variant
 *   is 18/131 — do NOT reach for volatile here, the clobber is the lever.
 *
 * LEVERS 1-7 (inherited; each byte-verified by removal):
 *  1. `x0 = a0; ob = a1; a0 += a2; a1 += a3;` — the DESTRUCTIVE update of the
 *     parameter is what forces the target's two extra copies and lets the sums
 *     reuse the dying param registers.  It is also load-bearing for the
 *     LENGTH: writing `x1 = a0 + a2` into a fresh local makes that pseudo
 *     single-set, gcc coalesces it with $a0, both copies are copy-propagated
 *     away and the entry copy disappears — 129 ins (probe A), 130 even with
 *     $t0/$v1 pins (probe B).  The statement ORDER here is also load-bearing:
 *     it is the LUID order that decides the T-25/T-26 picks above.  All six
 *     legal interleavings were measured; only this one is right.
 *  2. ONE local `cb` carries 3 / 0x40 / 0x42.  Three separate literals are
 *     three single-set pseudos and loop.c HOISTS the invariant `li 3` and
 *     `li 0x40` out of the loop (2 extra preheader regs, +7 mismatched).
 *  3. `i = 0;` HOISTED OUT OF THE `for` HEADER, so `addu $a2,$zero,$zero` is
 *     the first preheader insn as in the target.
 *  4. THE MASK LOCALS ARE ASSIGNED INSIDE THE LOOP so they become loop.c
 *     movables hoisted AFTER the `addiu $t2,$sp,0x10` array-base movable —
 *     the target's preheader order (i=0, &pts, m24, mFF).  As explicit
 *     preheader statements they land BEFORE $t2 instead (probes AK/AL).
 *  5. `register s32 i4 __asm__("$9")` — with the masks hoisted, m24 and i4
 *     tie in global-alloc and land swapped; pinning i4 to $t1 lets m24 take
 *     $t0.
 *  6. ADDPRIM ASYMMETRY (inherited from the matched sibling func_80016450):
 *     the FIRST half inlines the OT-slot address expression fully, the SECOND
 *     half binds it.  Symmetric shapes cost 20+ instructions.
 *  7. `register s32 ob __asm__("$3")` for the second half's OT base, so the
 *     add is the target's self-accumulating `addu $v1,$t1,$v1`.
 *
 * SYMBOL AUDIT (§174 law 1c — match_one masks jal/HI16/LO16, so every symbol
 * was re-checked against this .s's own relocation lines; tools/reloc_identity.py
 * then confirmed all 6 relocations AGREE.  The .s names exactly five relocated
 * symbols: D_800AF630, D_800A6518, D_800A651C, func_80010A08, func_80016638):
 *   - `lui/addiu %hi/%lo(D_800AF630)` -> $s0 is the ONLY named data base; the
 *     OT-buffer index is reached as `*(u16 *)(base + 0xA3D2)`
 *     (`lui $at,0x1; addu $at,$s0,$at; lhu -0x5C2E($at)`; 0x10000-0x5C2E =
 *     0xA3D2, i.e. 0x800B9A02).  D_800B9A02 IS declared in src/800.c and IS
 *     used by the siblings, but it does NOT appear in THIS .s — do not
 *     substitute it here.  `lhu` => u16, not s16.
 *   - `jal func_80010A08` with $a0 = 0x40; `jal func_80016638` with
 *     $a0 = &D_800A6518[idx*20] (`lui %hi` + `addiu %lo` = address-of),
 *     $a1 = arg7 ($s5 from 0x5C($sp)), $a2 = arg8 (`andi $s4,0xFFFF`).
 *   - D_800A651C read with `lw %lo(...)($at)` = the `.a` member at offset 0;
 *     the index is scaled *20 (`sll 2; addu; sll 2`), which is exactly
 *     sizeof(OtBlk_80016450_80015F04) = {s32 a; s32 b[4]}.
 *   - Store sides: `sw $v1,0($a3)` is the packet tag word ($a3 = p),
 *     `sw $v0,0($v1)` is the OT slot.  With $a1 = p + 0xE: `sb -0xB` = len(3),
 *     `sb -0x7` = code(7), `sb -0xA/-0x9/-0x8` = r0/g0/b0 <- $s3/$s2/$s1 <-
 *     0x50/0x54/0x58 in that order; `sh -0x6/-0x4/-0x2/0x0` = x0/y0/x1/y1.
 *   - Epilogue reloads pts[0] FROM THE STACK (`lhu 0x10($sp)`, `lhu 0x12`),
 *     so the closing fixup must read `pts[0]`, never the x0/ob registers.
 *
 * TU CHECK (§174 laws 2/3) — src/800.c holds
 * `INCLUDE_ASM("asm/nonmatchings/800", func_80015F04);` at line 1166:
 *   - There is NO prototype for func_80015F04 in src/800.c or in include/, and
 *     src/800.c does not include shared/engine_core.h, so the parameter list
 *     below is unconstrained (no DEF-side wall here).
 *   - `extern void *func_80010A08(s32 a0);` (src/800.c:1119),
 *     `extern void func_80016638(void *a0, s32 a1, s32 a2);` (:1122),
 *     `extern u8 D_800A6518[];` (:1121), `extern u8 D_800AF630[];` (:930) and
 *     the block-scope `extern OtBlk_80016450_80015F04 D_800A651C[];` (:1126) all
 *     ALREADY exist at file scope ABOVE line 1166 and the declarations below
 *     are copied to agree with them exactly.  Duplicate compatible externs are
 *     legal, so they may stay or go when banking.
 *
 * >>> INTEGRATION NOTE: src/800.c ALREADY defines
 * >>>     typedef struct { s32 a; s32 b[4]; } OtBlk_80016450_80015F04;
 * >>> at FILE scope (src/800.c:1117, i.e. ABOVE this function's slot at 1166).
 * >>> DROP the duplicate typedef line below when banking — C89 rejects the
 * >>> redefinition.  It is present here only so the draft compiles standalone
 * >>> under match_one.  `Pt_80015F04` and `LineF2_80015F04` do not collide
 * >>> with anything in src/800.c.
 */
typedef struct { s32 a; s32 b[4]; } OtBlk_80016450_80015F04;   /* DUPLICATE — see note */

typedef struct { u16 x, y; } Pt_80015F04;             /* stack corner list */

typedef struct {                                      /* 0x10 LINE_F2 */
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
} LineF2_80015F04;

extern void *func_80010A08(s32);
extern void func_80016638(void *a0, s32 a1, s32 a2);
extern u8 D_800AF630[];
extern u8 D_800A6518[];

void func_80015F04(s32 a0, s32 a1, s32 a2, s32 a3, u8 arg4, u8 arg5, u8 arg6, u16 arg7, u16 arg8)
{
    extern OtBlk_80016450_80015F04 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar in their own bodies */
    Pt_80015F04 pts[4];
    LineF2_80015F04 *p;
    u8 *base;
    u32 *otp;
    register s32 ob __asm__("$3");    /* LEVER 9: y0 AND the 2nd addPrim OT   */
    s32 i;                            /* base — one $v1 variable, two roles,  */
    register s32 i4 __asm__("$9");    /* so REG_N_SETS==2 and the boost dies   */
    s32 x0;
    register s32 sz __asm__("$4");    /* LEVER 8: the func_80010A08 argument, */
    s32 semi;                         /* pinned to $a0 so its `li` gets a LUID */
    s32 cb;                           /* at THIS source position, not at the jal */
    register u32 m24;
    register u32 mFF;

    base = D_800AF630;

    /* LEVER 8.  Emitting the argument load from asm (rather than `sz = 0x40;`)
     * is what stops cse folding REG_EQUAL 64 onto the call-site no-op move and
     * dead-store-eliminating this insn.  Bytes are the target's own
     * 0x24040040 `addiu $a0,$zero,0x40`; the call's `$a0 = sz` becomes a
     * deleted no-op.  Removing this line costs 2 instructions. */
    __asm__("addiu %0,$zero,0x40" : "=r"(sz));

    /* LUID order below is load-bearing — see the ready-list trace in the
     * header.  x0 before ob, and each destructive update after its own copy. */
    x0 = a0;
    ob = a1;
    a0 += a2;
    a1 += a3;

    /* LEVER 10.  Second SET of x0 -> REG_N_SETS==2 -> no birthing boost, so
     * X0 stops out-ranking Y0 at the T-26 pick.  The "memory" clobber is the
     * load-bearing half: without it the asm becomes a sixth entry-block filler
     * and drags `sh $t0,0x10($sp)` above `sw $ra,0x38($sp)` (2/131).  With it
     * the asm is a store-ordering fence that cannot enter the
     * (save, load, filler) interleave.  Emits nothing. */
    __asm__("" : "=r"(x0) : "0"(x0) : "memory");

    pts[0].x = x0;
    pts[0].y = ob;
    pts[1].x = a0;
    pts[1].y = ob;
    pts[2].x = a0;
    pts[2].y = a1;
    pts[3].x = x0;
    pts[3].y = a1;

    p = (LineF2_80015F04 *)func_80010A08(sz);

    i = 0;
    semi = (arg8 < 4);
    i4 = arg7 * 4;
    for (; i < 4; i++) {
        cb = 3;
        p->len = cb;
        cb = 0x40;
        p->code = cb;
        if (semi) {
            cb = 0x42;
            p->code = cb;
        }
        p->r0 = arg4;
        p->g0 = arg5;
        p->b0 = arg6;
        p->x0 = pts[i].x;
        p->y0 = pts[i].y;
        p->x1 = pts[i + 1].x;
        p->y1 = pts[i + 1].y;
        m24 = 0x00FFFFFF;
        mFF = 0xFF000000;
        *(u32 *)p = (*(u32 *)p & mFF) |
                    (*(u32 *)(i4 + D_800A651C[*(u16 *)(base + 0xA3D2)].a) & m24);
        ob = D_800A651C[*(u16 *)(base + 0xA3D2)].a;
        otp = (u32 *)(i4 + ob);
        *otp = (*otp & mFF) | ((u32)p & m24);
        p++;
    }

    p[-1].x1 = pts[0].x;
    p[-1].y1 = pts[0].y;

    if (arg8 < 4) {
        func_80016638(&D_800A6518[*(u16 *)(base + 0xA3D2) * 20], arg7, arg8);
    }
}


/* Same shapes as the matched sibling func_80016450 (src/800.c) — a fixed
 * 0x18-byte POLY_F4 quad allocator + a single addPrim() into D_800A651C's OT
 * slot, then func_80016638. This one has no parameters: r0=g0=b0=0 (black),
 * code is always 0x2A (no branch), and the addPrim/func_80016638 call use
 * D_800A651C/D_800A6518 directly (matching the sibling's "else" arm shape,
 * but against D_800A651C instead of D_800AE7BC, and args (0,0) not (0,1)).
 * Field writes go through raw pointer arithmetic (not p->member) — a
 * struct-member store is MEM_IN_STRUCT_P and gcc-2.7.2's alias code treats
 * it as non-conflicting with the *(u32*)p full-word read, letting the
 * scheduler hoist that read arbitrarily early; plain casts keep everything
 * on the same alias footing so the load stays where source order puts it. */


extern void *func_80010A08(s32 a0);
extern void func_80016638(void *a0, s32 a1, s32 a2);
extern u16 D_800B9A02;
extern u8 D_800A6518[];

void func_80016110(void)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar in their own bodies */
    void *p;
    u32 *ot;
    register u32 m24 __asm__("$6");
    register u32 pv __asm__("$4");

    p = func_80010A08(0x18);
    m24 = 0x00FFFFFF;

    *(u8 *)((u8 *)p + 3) = 5;
    *(u8 *)((u8 *)p + 7) = 0x2A;
    *(s16 *)((u8 *)p + 8) = *(s16 *)((u8 *)p + 0x10) = -160;
    *(s16 *)((u8 *)p + 0xC) = *(s16 *)((u8 *)p + 0x14) = 160;
    *(s16 *)((u8 *)p + 0xA) = *(s16 *)((u8 *)p + 0xE) = -120;
    *(u8 *)((u8 *)p + 4) = *(u8 *)((u8 *)p + 5) = *(u8 *)((u8 *)p + 6) = 0;
    *(s16 *)((u8 *)p + 0x12) = *(s16 *)((u8 *)p + 0x16) = 120;

    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800A651C[D_800B9A02].a & m24);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
    ot = (u32 *)D_800A651C[D_800B9A02].a;
    *ot = (*ot & 0xFF000000) | ((u32)p & m24);
    func_80016638(&D_800A6518[D_800B9A02 * 20], 0, 0);
}

/* Bank-safe form: NO file-scope typedef (src/800.c:92 already defines
 * OtBlk_80016450; a second identical typedef is a redefinition there).
 * The OT-block externs instead carry an inline structurally-identical
 * anonymous struct, which only yields a benign redecl warning in-TU and
 * compiles standalone here. File-scope externs below reproduce decls that
 * already exist in src/800.c (:553/:652/:653/:1255/:1429/:1432) purely so
 * this unit compiles alone; compatible redeclaration is warning-only. */
extern u16 D_800AF7BE;
extern u16 D_800AF7BC;
extern u8 D_800A6518[];
extern u16 D_800B9A02;
extern void *func_80010A08(s32 a0);
extern void func_80016638(void *a0, s32 a1, s32 a2);

void func_80016224(s32 a0, s32 a1)
{
    extern struct { s32 a; s32 b[4]; } D_800A651C[];
    extern struct { s32 a; s32 b[4]; } D_800AE7BC[];
    extern u8 D_800AE7B8[];

    void *p;
    s16 xl;
    s16 xr;
    s16 yl;
    s16 yr;
    s32 idx;

    p = func_80010A08(0x18);
    *(u8 *)((u8 *)p + 3) = 5;
    *(u8 *)((u8 *)p + 7) = 0x2A;
    *(u8 *)((u8 *)p + 6) = a0;
    *(u8 *)((u8 *)p + 5) = a0;
    *(u8 *)((u8 *)p + 4) = a0;
    xl = -(s32)D_800AF7BC / 2;
    *(s16 *)((u8 *)p + 0x10) = xl;
    *(s16 *)((u8 *)p + 0x08) = xl;
    __asm__ __volatile__("" ::: "memory");
    xr = D_800AF7BC / 2;
    *(s16 *)((u8 *)p + 0x14) = xr;
    *(s16 *)((u8 *)p + 0x0C) = xr;
    yl = -(s32)D_800AF7BE / 2;
    *(s16 *)((u8 *)p + 0x0E) = yl;
    *(s16 *)((u8 *)p + 0x0A) = yl;
    __asm__ __volatile__("" ::: "memory");
    yr = D_800AF7BE / 2;
    idx = a1 & 0xFFFF;
    *(s16 *)((u8 *)p + 0x16) = yr;
    *(s16 *)((u8 *)p + 0x12) = yr;
    if (idx != 0) {
        register u32 m24 __asm__("$7") = 0x00FFFFFF;
        register u32 mFF __asm__("$8") = 0xFF000000;
        register s32 i4 __asm__("$6") = idx * 4;
        register u32 pv __asm__("$4");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & mFF) | (*(u32 *)(i4 + D_800A651C[D_800B9A02].a) & m24);
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & mFF) | ((u32)p & m24);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 2);
    } else {
        register u32 m24 = 0x00FFFFFF;
        register u32 pv __asm__("$3");
        u32 *ot;
        pv = *(u32 *)p;
        *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
        __asm__ __volatile__("" : "=r"(pv));
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & m24);
        func_80016638(&D_800AE7B8[D_800B9A02 * 20], 0, 2);
    }
}


/* func_80016450 — main/800: allocate a 0x18-byte flat semi-transparent quad
 * (POLY_F4, code 0x2A) covering the whole 320x240 screen at brightness a0,
 * PSY-Q addPrim() it onto one of two OT tables selected by (u16)a1, then hand
 * the owning env block to func_80016638.
 *
 * @class: (was regalloc-order / sched)
 * @stuck: none — MATCH, 122/122 instructions, byte-exact under match_one, and
 *   all 27 relocations hand-checked one-to-one against asm/nonmatchings/800/
 *   func_80016450.s (same offsets, same symbols, same order): func_80010A08,
 *   6x D_800B9A02, 2x D_800A651C, D_800A6518, 2x D_800AE7BC, D_800AE7B8,
 *   func_80016638.  Destination TU src/800.c already declares
 *   `extern void func_80016450(s32 a0, s32 a1);` (L680) — adopted verbatim.
 *   No other file-scope decl of any symbol used here exists in the
 *   preprocessed TU, so these externs merge silently.
 *
 * ---------------------------------------------------------------------------
 * WHAT THIS FUNCTION ACTUALLY IS
 *
 * The and-0xFF000000 / and-0x00FFFFFF / or triple is the libgpu P_TAG 24-bit
 * `addr` BITFIELD, i.e. the PSY-Q macro pair
 *     addPrim(ot, p) == setaddr(p, getaddr(ot)), setaddr(ot, p)
 * The macro argument `ot` is textually duplicated, which is why D_800B9A02 and
 * the OT-base load are each emitted TWICE per branch.  Recognising that is what
 * fixes the instruction count; the rest is register/schedule steering.
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-verified by removing it and re-scoring)
 *
 *  1. CHAINED ASSIGNMENT reproduces the reversed store pairs.
 *     `p->x0 = p->x2 = K` emits sh K,0x10 THEN sh K,0x8 and keeps K in ONE
 *     constant register across both stores.  Same for `p->r0=p->g0=p->b0=a0`.
 *     (Inherited from the first pass — natural source order gives four separate
 *     constant registers and the wrong store order.)
 *
 *  2. `*(u32 *)p`, NOT `p->tag`.  A struct-member store does NOT kill a plain
 *     global's CSE in gcc-2.7.2, so `p->tag` cached D_800B9A02/D_800A651C and
 *     produced 110 ins instead of 122.  A non-MEM_IN_STRUCT_P store kills
 *     everything and reproduces all six reloads exactly.  (First pass.)
 *
 *  3. ⚠ THE ONE THAT UNSTUCK THE 23-MISMATCH RESIDUAL — DO NOT bind the OT slot
 *     address to a function-scope local used in BOTH addPrim halves.  The first
 *     pass wrote `ot = <addr>; …*ot…; ot = <addr>; *ot = …;` in each arm.  One
 *     pseudo with two def/use pairs = ONE live range spanning the whole arm, so
 *     local-alloc gives it a DEDICATED register ($t0) and shifts every other
 *     temp one slot down.  The target instead computes the address into a
 *     register that DIES on the same insn (`addu $v0,$a2,$v0` in the first half,
 *     `addu $a2,$a2,$v0` in the second).  The fix is the HYBRID shape used by
 *     the sibling match func_80185944 (src/ov_SC03_119/..._jr_8017FB84.c):
 *       - first half: the address expression FULLY INLINED (no local at all);
 *       - second half: its own short-lived binding.
 *     This alone rebuilt the whole `addu/lw` shape (23 -> the register-name
 *     residual below).  Note the first pass had measured "fully inlining" (45)
 *     and "splitting it in two" (44) as WORSE — because it applied each to BOTH
 *     halves.  It is the ASYMMETRY that matches.
 *
 *  4. OPERAND ORDER IS SOURCE ORDER: `i4 + D_800A651C[…].a`, not
 *     `D_800A651C[…].a + i4`.  gcc-2.7.2 emits `addu $v0,$a2,$v0` from the
 *     former and `addu $v0,$v0,$a2` from the latter.  (13 -> ...)
 *
 *  5. SELF-ACCUMULATE TO REUSE THE DYING REGISTER.  The second half's
 *     `addu $a2,$a2,$v0` writes the OT address back into the SAME register that
 *     held idx*4.  A fresh local can never produce that (gcc will not clobber a
 *     still-named pinned value), but `i4 += D_800A651C[…].a;` — reusing the
 *     variable as its own accumulator — does, exactly.  9 -> 6.
 *
 *  6. THE ELSE ARM'S LAST 6 WERE A SCHEDULE SWAP, NOT ALLOCATION.  Target fills
 *     the `lhu D_800B9A02` load-delay slot with the tag load `lw $v1,0($t1)`
 *     and the `lw %lo(D_800AE7BC)` slot with `lui $a0,0xff00`; we had them
 *     exactly swapped, which also flipped D_800B9A02 $a0<->$v1.  This is
 *     gcc-2.7.2 sched.c's BIRTHING BOOST on a single-SET destination (the boost
 *     sinks the load to just before its consumer, and `potential_hazard` breaks
 *     the tie in the load's favour, so it is picked first = placed LAST).
 *     Cure = the func_80185944 recipe, both halves needed:
 *       (a) PIN the tag value (`register u32 pv __asm__("$3")`), and
 *       (b) give `pv` a SECOND SET with a zero-byte
 *           `__asm__ __volatile__("" : "=r"(pv));`  — REG_N_SETS != 1 kills the
 *           boost.  A plain C reassignment does NOT work (cse/flow removes it).
 *     PLACEMENT MATTERS: the dead asm must sit immediately after `pv`'s last
 *     use INSIDE the arm.  Putting it after the func_80016638 call (as the
 *     sibling does, where the call is in the same block) makes gcc keep $v1
 *     live across the jal here and costs +3 instructions (125 ins, 53 diff).
 *     6 -> 0.
 *
 *  PIN-TRIM LOG (all re-scored; three pins are the verified minimum):
 *    drop `m24` $a3 pin (then arm)   — MATCH   (kept as plain `register`)
 *    drop `mFF` $t0 pin (then arm)   — MATCH   (kept as plain `register`)
 *    drop `m24` $a2 pin (else arm)   — MATCH   (kept as plain `register`)
 *    all three dropped together      — MATCH   <= this file
 *    replace the mask LOCALS with bare literals — 3 mismatched (the locals are
 *      load-bearing: a literal is re-materialised per use and reschedules)
 *    drop `i4` $a2 pin               — 2 mismatched
 *    drop `pv` $a0 pin (then arm)    — 4 mismatched
 *    drop `pv` $v1 pin (else arm)    — 7 mismatched
 *    pin `p` to $t1                  — 123 ins, 113 mismatched (never pin p)
 */

/* engine_types.h-style OT block: 0x14 stride, the OT base pointer at +0 */

/* 0x18-byte POLY_F4 */
typedef struct {
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} F4_80016450;

extern void *func_80010A08(s32);
extern void func_80016638(void *a0, s32 a1, s32 a2);

extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern OtBlk_80016450 D_800AE7BC[];
extern u8 D_800AE7B8[];

void func_80016450(s32 a0, s32 a1)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: engine_core.h's DEFINE_ macros declare this symbol scalar inside their own bodies */
    F4_80016450 *p;
    u32 *ot;
    s32 idx;

    p = (F4_80016450 *)func_80010A08(0x18);

    p->len = 5;
    p->code = 0x2A;
    p->r0 = p->g0 = p->b0 = a0;
    p->x0 = p->x2 = -160;
    p->x1 = p->x3 = 160;
    p->y0 = p->y1 = -120;
    p->y2 = p->y3 = 120;
    idx = a1 & 0xFFFF;
    if (idx != 0) {
        register u32 m24 = 0x00FFFFFF;
        register u32 mFF = 0xFF000000;
        register s32 i4 __asm__("$6") = idx * 4;
        register u32 pv __asm__("$4");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & mFF) | (*(u32 *)(i4 + D_800A651C[D_800B9A02].a) & m24);
        i4 += D_800A651C[D_800B9A02].a;
        *(u32 *)i4 = (*(u32 *)i4 & mFF) | ((u32)p & m24);
        func_80016638(&D_800A6518[D_800B9A02 * 20], idx, 1);
    } else {
        register u32 m24 = 0x00FFFFFF;
        register u32 pv __asm__("$3");
        pv = *(u32 *)p;
        *(u32 *)p = (pv & 0xFF000000) | (*(u32 *)D_800AE7BC[D_800B9A02].a & m24);
        __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
        ot = (u32 *)D_800AE7BC[D_800B9A02].a;
        *ot = (*ot & 0xFF000000) | ((u32)p & m24);
        func_80016638(&D_800AE7B8[D_800B9A02 * 20], 0, 1);
    }
}


extern void *func_80010A08(s32 a0);

void func_80016638(void *a0, s32 a1, s32 a2)
{
    void *s2 = a0;
    s32 s1 = a1;
    s32 s0 = a2;
    void *v0;
    register u32 mask1 __asm__("$5");
    register u32 mask2 __asm__("$6");
    register u32 pv __asm__("$4");
    u32 v1;
    register u32 tmp __asm__("$2");

    v0 = func_80010A08(8);

    mask1 = 0xFFFFFF;
    {
        u32 one = 1;
        s0 = (s0 << 5) & 0x9FF;
        *(u8 *)((u8 *)v0 + 3) = (u8)one;
        __asm__ __volatile__("" : "=r"(one) : "0"(one));
    }
    s0 = s0 | 0xE1000000;

    s1 = s1 << 2;
    mask2 = 0xFF000000;

    *(u32 *)((u8 *)v0 + 4) = s0;

    /* First addPrim RMW: new primitive's link = OT slot's current low24,
     * primitive keeps its own top-byte tag. Mirrors func_80015D4C /
     * func_80016450's matched addPrim idiom in this same TU. */
    v1 = *(u32 *)((u8 *)s2 + 4);
    pv = *(u32 *)v0;
    v1 = *(u32 *)(s1 + v1);
    pv = pv & mask2;
    v1 = v1 & mask1;
    pv = pv | v1;
    *(u32 *)v0 = pv;

    /* Second addPrim RMW: OT slot := (OT slot's own top-byte tag) |
     * (new primitive's address, masked to low24) — head-insert the new
     * primitive into the OT chain. */
    v1 = *(u32 *)((u8 *)s2 + 4);
    s1 = s1 + v1;
    v1 = *(u32 *)s1;
    tmp = (u32)v0 & mask1;
    v1 = v1 & mask2;
    v1 = v1 | tmp;
    *(u32 *)s1 = v1;
}


void func_800166E8(void *a0, s32 a1) {
    s32 local_buffer[2];
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    __asm__ volatile("");  // Barrier to force stack allocation first

    if (a1 == 0)
        goto skip;

    v0 = a1 - 1;
    v1 = -1;

    do {
        *(u8 *)a0 = 0;
        v0--;
        a0 = (void *)((s32)a0 + 1);
    } while (v0 != v1);

skip:
    return;
}

#ifdef NON_MATCHING
/* bzero(p, n): n<4 byte path; else align-to-4 -> word-fill (sw) -> remainder bytes.
 * Logically correct and instruction-identical to the target EXCEPT gcc 2.7.2 emits a
 * phantom empty 16-byte stack frame here (target is frameless) — that one frame
 * prologue/epilogue is the entire residual. A decomp-permuter candidate (structural
 * permutation can flip frame allocation). See docs/matching-cookbook.md §4. */
void func_80016714(s8 *a0, s32 a1) {
    s32 v1;

    if (a1 < 4) {
        a1 = a1 - 1;
        if (a1 != -1) {
            do {
                *a0 = 0;
                a1 -= 1;
                a0 += 1;
            } while (a1 != -1);
        }
    } else {
        v1 = (s32)a0;
        if (((s32)a0 & 3) != 0) {
            do {
                *a0 = 0;
                a0 += 1;
                v1 += 1;
                a1 -= 1;
            } while ((v1 & 3) != 0);
        }
        v1 = (a1 >> 2) - 1;
        if (v1 != -1) {
            do {
                *(s32 *)a0 = 0;
                v1 -= 1;
                a0 += 4;
            } while (v1 != -1);
        }
        a1 = (a1 & 3) - 1;
        if (a1 != -1) {
            do {
                *a0 = 0;
                a1 -= 1;
                a0 += 1;
            } while (a1 != -1);
        }
    }
}
#else

void func_80016714(void *ptr, s32 len) {
    unsigned char *p = (unsigned char *)ptr;
    register s32 v0 __asm__("$2");
    s32 v1;

    if (len < 4) {
        v0 = -1;
        len--;
        if (len != v0) {
            do {
                p[0] = 0;
                p++;
                len--;
            } while (len != v0);
        }
    } else {
        // Align pointer to 4-byte boundary
        v1 = (s32)p;
        while ((v1 & 0x3) != 0) {
            p[0] = 0;
            p++;
            v1++;
            len--;
        }

        // Clear 4-byte words
        v1 = len >> 2;
        v1--;
        v0 = -1;
        if (v1 != v0) {
            do {
                *(unsigned int *)p = 0;
                p += 4;
                v1--;
            } while (v1 != v0);
        }

        // Clear remaining bytes
        len = len & 0x3;
        len--;
        v0 = -1;
        if (len != v0) {
            do {
                p[0] = 0;
                p++;
                len--;
            } while (len != v0);
        }
    }
}
#endif


extern void func_80016224(s32 a0, s32 a1);
extern u16 D_800AF7CE;

void func_800167B8(s32 a0) {
    a0 = ((u16)a0) < 4U ? 0xFF : 0x00;
    D_800AF7CE = 0;
    func_80016224(a0, 0);
}

extern u8 D_800AF630[];
extern u8 D_80062BA0[];
extern s32 D_800B9A18;
extern u16 D_800AF7CE;
extern void func_80016224(s32 a0, s32 a1);

s32 func_800167F0(s32 arg0) {
    register u32 zr __asm__("$0");
    register s32 v1 __asm__("$3");
    s32 x = arg0 + zr;
    u8 *s0 = D_800AF630;
    s32 mask = arg0 & 3;
    u32 raw;
    u32 a0;
    u32 v0;

    if (mask == 0) {
        v1 = D_80062BA0[D_800B9A18];
    } else {
        v1 = D_80062BA0[mask];
    }
    D_800AF7CE = D_800AF7CE + v1;
    __asm__ __volatile__("" ::: "memory");
    raw = *(u16 *)&s0[0x19E];
    a0 = raw + zr;
    if (a0 >= 0xFFU) {
        a0 = 0xFF;
    }
    v0 = ((x & 0xFFFFU) < 4U) ? 0xFF - a0 : a0;
    func_80016224(v0 & 0xFF, 0);
    return *(u16 *)&s0[0x19E] >= 0xFF;
}

extern u16 D_800AF7CE;
void func_800168B4(void) {
    D_800AF7CE = 0;
}

extern u8 D_800AF630[];
extern u16 D_800AF7CE;
extern s32 D_800B9A18;
extern u8 D_80062BA0[];

s32 func_800168C4(register s32 arg0) {
    register s32 t __asm__("$3");
    u8 *base = D_800AF630;

    arg0 &= 3;
    if (arg0 == 0) {
        t = D_80062BA0[D_800B9A18];
    } else {
        t = D_80062BA0[arg0];
    }
    D_800AF7CE += t;
    __asm__ __volatile__("" : : : "memory");

    t = *(u16 *) (base + 0x19E);
    if (t >= 0xFFU) {
        return *(u16 *) (base + 0x188) != 0;
    }
    return 0;
}


extern u16 D_800AF7CE;
extern void func_80016450(s32 a0, s32 a1);

void func_80016940(s32 a0) {
    s32 param = (((u32)a0 & 0xFFFF) < 4) ? 0xFF : 0x00;
    D_800AF7CE = 0;
    func_80016450(param, 0);
}

extern u8 D_800AF630[];
extern u8 D_80062BA0[];
extern s32 D_800B9A18;
extern u16 D_800AF7CE;
extern void func_80016450(s32 a0, s32 a1);

s32 func_80016978(s32 arg0) {
    register u32 zr __asm__("$0");
    register s32 v1 __asm__("$3");
    s32 x = arg0 + zr;
    u8 *s0 = D_800AF630;
    s32 mask = arg0 & 3;
    u32 raw;
    u32 a0;
    u32 v0;

    if (mask == 0) {
        v1 = D_80062BA0[D_800B9A18];
    } else {
        v1 = D_80062BA0[mask];
    }
    D_800AF7CE = D_800AF7CE + v1;
    __asm__ __volatile__("" ::: "memory");
    raw = *(u16 *)&s0[0x19E];
    a0 = raw + zr;
    if (a0 >= 0xFFU) {
        a0 = 0xFF;
    }
    v0 = ((x & 0xFFFFU) < 4U) ? 0xFF - a0 : a0;
    func_80016450(v0 & 0xFF, 0);
    return *(u16 *)&s0[0x19E] >= 0xFF;
}

void func_80016A3C(void *arg0)
{
    func_80016A7C(arg0, 0);
}

void func_80016A5C(void) {
    func_80016A7C();
}

typedef struct {
    u32 xy;   /* 0x0: vx (lo16) | vy (hi16) */
    s16 z;    /* 0x4 */
    s16 pad;  /* 0x6 */
} SV_80016A7C; /* 0x8 */

typedef struct {
    SV_80016A7C v[2];  /* 0x00 */
    u32 rgb0;          /* 0x10 */
    u32 rgb1;          /* 0x14 */
    u32 attr;          /* 0x18 */
} Src_80016A7C;

typedef struct {
    u32 tag;   /* 0x00 */
    u32 rgb0;  /* 0x04 */
    u32 xy0;   /* 0x08 */
    u32 rgb1;  /* 0x0C */
    u32 xy1;   /* 0x10 */
} LineG2_80016A7C; /* 0x14 */

extern void *func_80010A08(s32 size);
extern void SetLineG2(void *p);
extern void func_80017E8C(s32 arg0);
extern s32 RotTransPers3(void *v0, void *v1, void *v2,
                          s32 *sxy0, s32 *sxy1, s32 *sxy2,
                          s32 *p, s32 *flag);
extern void func_80018094(void *p, s32 otz, u32 flags);

void func_80016A7C(Src_80016A7C *arg0, s32 arg1)
{
    LineG2_80016A7C *p;
    s32 opz;
    s32 flag;
    s32 otz;

    p = (LineG2_80016A7C *)func_80010A08(0x14);
    p->rgb0 = arg0->rgb0;
    p->rgb1 = arg0->rgb1;
    SetLineG2(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        otz = RotTransPers3(&arg0->v[0], &arg0->v[1], &arg0->v[1],
                             (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy1,
                             &opz, &flag);
    } else {
        p->xy0 = arg0->v[0].xy;
        p->xy1 = arg0->v[1].xy;
        __asm__ volatile("");
        otz = arg0->v[0].z;
        flag = 0;
    }

    if ((flag & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->attr);
    }
}


typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_80016B60;

typedef struct {
    SVECTOR_80016B60 v[3];  /* 0x00 */
    u32 rgb0;               /* 0x18 */
    u32 rgb1;               /* 0x1C */
    u32 rgb2;               /* 0x20 */
    u32 flags;              /* 0x24 */
} Src_80016B60;

typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 rgb1;   /* 0x0C */
    u32 xy1;    /* 0x10 */
    u32 rgb2;   /* 0x14 */
    u32 xy2;    /* 0x18 */
    u32 otz;    /* 0x1C */
} LineG3_80016B60;

extern void *func_80010A08(s32);
extern void SetLineG3(LineG3_80016B60 *p);
extern void func_80017E8C(s32 arg0);
extern s32 RotTransPers3(void *v0, void *v1, void *v2,
                          s32 *sxy0, s32 *sxy1, s32 *sxy2,
                          s32 *p, s32 *flag);
extern void func_80018094(void *p, s32 otz, u32 flags);

void func_80016B60(Src_80016B60 *arg0, s32 arg1)
{
    LineG3_80016B60 *p;
    s32 flag;
    s32 otz_unused;
    s32 otz;

    p = (LineG3_80016B60 *)func_80010A08(0x20);
    p->rgb0 = arg0->rgb0;
    p->rgb1 = arg0->rgb1;
    p->rgb2 = arg0->rgb2;
    SetLineG3(p);
    func_80017E8C(arg1);

    otz = RotTransPers3(&arg0->v[0], &arg0->v[1], &arg0->v[2],
                         (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy2,
                         &otz_unused, &flag);

    if ((flag & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->flags);
    }
}


/* func_80016C28 — src/800.c (main, -O2).
 *
 * Builds one LINE_G4 (0x28 bytes) from a "src" descriptor:
 *   0x00..0x1F  four SVECTORs (v0..v3)
 *   0x20..0x2C  four rgb+code words
 *   0x30        extra word passed through to func_80018094 as "flags"
 * Runs the GTE unconditionally (RTPT on v0..v2, RTPS on v3, AVSZ4 -> otz),
 * then hands the prim to func_80018094 iff the combined GTE flag word is
 * clean of everything except bit 0x1000.
 *
 * Mirrors the already-matched func_80017930 (same file) almost exactly —
 * same 4-SVECTOR layout, same gte_ld/rtp/stsxy/avsz4/stotz macro sequence
 * and ordering — just building a LINE_G4 (SetLineG4) instead of a
 * POLY_GT4 (SetPolyGT4), and calling SetLineG4 right after the alloc
 * (before the rgb copies) instead of after them, and with the GTE call
 * unconditional (no "if (arg1 != 0)" guard around func_80017E8C/GTE block).
 */

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80016C28;

typedef struct {
    SV_80016C28 v[4]; /* 0x00 */
    u32 rgb0;          /* 0x20 */
    u32 rgb1;          /* 0x24 */
    u32 rgb2;          /* 0x28 */
    u32 rgb3;          /* 0x2C */
    u32 flags;         /* 0x30 */
} Src_80016C28;

typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 rgb1;   /* 0x0C */
    u32 xy1;    /* 0x10 */
    u32 rgb2;   /* 0x14 */
    u32 xy2;    /* 0x18 */
    u32 rgb3;   /* 0x1C */
    u32 xy3;    /* 0x20 */
    u32 term;   /* 0x24 */
} LineG4_80016C28; /* 0x28 */

extern void *func_80010A08(s32);
extern void SetLineG4(LineG4_80016C28 *p);
extern void func_80017E8C(s32 arg0);
extern void func_80018094(void *p, s32 otz, u32 flags);

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

void func_80016C28(Src_80016C28 *arg0, s32 arg1)
{
    LineG4_80016C28 *p;
    s32 flag;
    s32 flag2;
    s32 otz;

    p = (LineG4_80016C28 *)func_80010A08(0x28);
    SetLineG4(p);
    p->rgb0 = arg0->rgb0;
    p->rgb1 = arg0->rgb1;
    p->rgb2 = arg0->rgb2;
    p->rgb3 = arg0->rgb3;
    func_80017E8C(arg1);

    gte_ldv3(&arg0->v[0], &arg0->v[1], &arg0->v[2]);
    gte_rtpt();
    gte_stflg(&flag);
    gte_stsxy3(&p->xy0, &p->xy1, &p->xy2);
    gte_ldv0(&arg0->v[3]);
    gte_rtps();
    gte_stflg(&flag2);
    flag |= flag2;
    gte_stsxy(&p->xy3);
    gte_avsz4();
    gte_stotz(&otz);

    if ((flag & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->flags);
    }
}


/* Standalone draft for func_80016D78 (src/800.c, main, mass lane).
 * Fresh crack: sibling func_80016F18 in the same TU (already MATCHED) is the
 * FT4 / 4-vertex version of this exact shape (alloc via func_80010A08,
 * SetPolyFT4/FT3, GetTPage, GetClut, func_80018194). This function is the
 * FT3 / 3-vertex sibling: it always takes the GTE-hardware path (a single
 * unconditional RotTransPers3 call, no inline-GTE-macro branch) and always
 * passes tp=0 to GetTPage (no tpage-select branch either) -- matching the
 * target .s exactly (no branch until the final `sltiu`/`beqz` clut compare
 * and the trailing `bnez` flag test).
 */

/* 8-byte vertex entry, same shape as the matched sibling's V16F18. */
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 pad;
} V16D78;

typedef union {
    u32 w;
    u16 h[2];
} UV16D78;

/* input struct: 3 vertices + 3 uv words + rgbc + attr + clut byte */
typedef struct {
    /* 0x00 */ V16D78  v[3];
    /* 0x18 */ UV16D78 uv[3];
    /* 0x24 */ u32     rgbc;
    /* 0x28 */ u32     attr;
    /* 0x2C */ u8      clut;
} S16D78;

/* output POLY_FT3-shaped packet, 0x20 bytes, same field-by-field shape as
 * the matched sibling's FT4_16F18 (minus the 4th vertex). */
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgbc;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u8  u0;
    /* 0x0D */ u8  v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u8  u1;
    /* 0x15 */ u8  v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u8  u2;
    /* 0x1D */ u8  v2;
    /* 0x1E */ u16 pad0;
} FT3_16D78;

extern void *func_80010A08(s32);
extern void SetPolyFT3(FT3_16D78 *);
extern void func_80017E8C(s32);
extern s32 RotTransPers3(void *v0, void *v1, void *v2,
                          s32 *sxy0, s32 *sxy1, s32 *sxy2,
                          s32 *p, s32 *flag);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 GetClut(s32, s32);
extern void func_80018194(void *, s32, u32);

void func_80016D78(S16D78 *arg0, s32 arg1)
{
    FT3_16D78 *p;
    u32 t;
    u32 c;
    s32 otz_unused;
    s32 flag;
    s32 otz;

    p = (FT3_16D78 *)func_80010A08(0x20);
    p->rgbc = arg0->rgbc;
    SetPolyFT3(p);

    func_80017E8C(arg1);

    otz = RotTransPers3(&arg0->v[0], &arg0->v[1], &arg0->v[2],
                         (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy2,
                         &otz_unused, &flag);

    t = arg0->uv[0].w;
    p->u0 = t;
    p->v0 = t >> 16;
    t = arg0->uv[1].w;
    p->u1 = t;
    p->v1 = t >> 16;
    t = arg0->uv[2].w;
    p->u2 = t;
    p->v2 = t >> 16;

    p->tpage = GetTPage(0, (arg0->attr >> 28) & 3,
                         (arg0->uv[0].h[0] >> 2) & 0x3FC0,
                         arg0->uv[0].h[1] & 0xFF00);

    c = arg0->clut;
    p->clut = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((flag & ~0x1000) == 0) {
        func_80018194((void *)p, otz, (u32)arg0->attr);
    }
}

void func_80016EB0(void *arg0)
{
    func_80016F18(arg0, 0, 1);
}

void func_80016ED4(void *arg0)
{
    func_80016F18(arg0, 0, 0);
}

void func_80016EF8(void *arg0, s32 arg1)
{
    func_80016F18(arg0, arg1, 0);
}


/* ---- PsyQ GTE inline macros (same spelling as the matched ov_SC03_* TUs) ---- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

/* ---- types ---- */
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 pad;
} V16F18;   /* 8 bytes */

typedef union {
    u32 w;
    u16 h[2];
} UV16F18;

typedef struct {
    /* 0x00 */ V16F18   v[4];
    /* 0x20 */ UV16F18  uv[4];
    /* 0x30 */ u32      rgbc;
    /* 0x34 */ u32      attr;
    /* 0x38 */ u8       clut;
} S16F18;

typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgbc;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u8  u0;
    /* 0x0D */ u8  v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u8  u1;
    /* 0x15 */ u8  v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u8  u2;
    /* 0x1D */ u8  v2;
    /* 0x1E */ u16 pad0;
    /* 0x20 */ u32 xy3;
    /* 0x24 */ u8  u3;
    /* 0x25 */ u8  v3;
    /* 0x26 */ u16 pad1;
} FT4_16F18;

extern void *func_80010A08(s32);
extern void SetPolyFT4(FT4_16F18 *);
extern void func_80017E8C(s32);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 GetClut(s32, s32);
extern void func_80018194(void *, s32, u32);

void func_80016F18(S16F18 *arg0, s32 arg1, s32 arg2)
{
    s32 flag;
    s32 flag2;
    s32 otz;
    FT4_16F18 *p;
    u32 t;
    u32 c;

    p = (FT4_16F18 *)func_80010A08(0x28);
    p->rgbc = arg0->rgbc;
    SetPolyFT4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        gte_ldv3(&arg0->v[0], &arg0->v[1], &arg0->v[2]);
        gte_rtpt();
        gte_stflg(&flag);
        gte_stsxy3(&p->xy0, &p->xy1, &p->xy2);
        gte_ldv0(&arg0->v[3]);
        gte_rtps();
        gte_stflg(&flag2);
        flag |= flag2;
        gte_stsxy(&p->xy3);
        gte_avsz4();
        gte_stotz(&otz);
    } else {
        p->xy0 = arg0->v[0].xy;
        p->xy1 = arg0->v[1].xy;
        p->xy2 = arg0->v[2].xy;
        p->xy3 = arg0->v[3].xy;
        flag = 0;
        otz = arg0->v[0].z;
    }

    t = arg0->uv[0].w;
    p->u0 = t;
    p->v0 = t >> 16;
    t = arg0->uv[1].w;
    p->u1 = t;
    p->v1 = t >> 16;
    t = arg0->uv[2].w;
    p->u2 = t;
    p->v2 = t >> 16;
    t = arg0->uv[3].w;
    p->u3 = t;
    p->v3 = t >> 16;

    if (arg2 != 0) {
        p->tpage = GetTPage(2, (arg0->attr >> 28) & 3,
                            (arg0->uv[0].h[0] >> 2) & 0x3FC0, 0);
    } else {
        p->tpage = GetTPage(0, (arg0->attr >> 28) & 3,
                            (arg0->uv[0].h[0] >> 2) & 0x3FC0,
                            arg0->uv[0].h[1] & 0xFF00);
    }

    c = arg0->clut;
    p->clut = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((flag & ~0x1000) == 0) {
        func_80018194((void *)p, otz, (u32)arg0->attr);
    }
}

/* 8-byte vertex entry: vx/vy packed as one word (xy), then z, then pad.
 * Same layout convention as SVec3_800173DC above. */
typedef struct {
    u32 xy;   /* 0x0: vx (lo16) | vy (hi16) */
    s16 z;    /* 0x4 */
    s16 pad;  /* 0x6 */
} SVec_80017168; /* 0x8 */

/* Source descriptor: three vertices + packed rgb/code word + trailing attr
 * word forwarded verbatim to func_80018094. */
typedef struct {
    SVec_80017168 v[3];  /* 0x00 */
    u32 rgbc;            /* 0x18 */
    u32 attr;            /* 0x1C */
} Src_80017168;

/* POLY_F3 (libgpu), 0x14 bytes. */
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgbc0;  /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 xy1;    /* 0x0C */
    u32 xy2;    /* 0x10 */
} F3_80017168; /* 0x14 */

extern void *func_80010A08(s32 size);
extern void SetPolyF3(F3_80017168 *p);
extern void func_80017E8C(s32 arg0);
extern s32 RotTransPers3(void *v0, void *v1, void *v2,
                          s32 *sxy0, s32 *sxy1, s32 *sxy2,
                          s32 *p, s32 *flag);
extern void func_80018094(void *p, s32 otz, u32 flags);

void func_80017168(Src_80017168 *arg0, s32 arg1)
{
    F3_80017168 *p;
    s32 flag;
    s32 otzp;
    s32 otz;

    p = (F3_80017168 *)func_80010A08(0x14);
    p->rgbc0 = arg0->rgbc;
    SetPolyF3(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        otz = RotTransPers3(&arg0->v[0], &arg0->v[1], &arg0->v[2],
                             (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy2,
                             &otzp, &flag);
    } else {
        p->xy0 = arg0->v[0].xy;
        p->xy1 = arg0->v[1].xy;
        p->xy2 = arg0->v[2].xy;
        __asm__ volatile("");
        otz = arg0->v[0].z;
        flag = 0;
    }

    if ((flag & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->attr);
    }
}

void func_80017254(void *arg0)
{
    func_80017294(arg0, 0);
}

void func_80017274(void)
{
    func_80017294();
}


/* func_80017294 (main, src/800.c) — mass-lane fresh crack.
 *
 * Builds one POLY_F4 (0x18 bytes) from a "quad descriptor" arg0:
 *   0x00..0x1F  four SVECTOR-ish V0 entries (v0..v3), each { u32 xy; s16 z; s16 pad; }
 *   0x20        rgbc word (r0,g0,b0,code packed)
 *   0x24        flags word (passed straight through to func_80018094)
 * arg1 != 0  -> func_80017E8C(arg1) then RotTransPers4 projects v0..v3 into the
 *               poly's xy0..xy3 and returns otz, with a separate `flag` out-param.
 * arg1 == 0  -> copy the xy words straight through, otz = arg0->v[0].z, flag = 0.
 * Finally, if (flag & ~0x1000) == 0, hand the poly to func_80018094(p, otz, flags).
 *
 * Structurally identical in shape to func_80017930/func_80016F18 in this same TU
 * (both already-matched siblings), and to func_8018F734 (src/ov_SC03_117/...) which
 * is the RotTransPers4-based POLY_G4 exemplar this draft's call shape is modeled on.
 */

extern void *func_80010A08(s32);
extern void SetPolyF4(void *);
extern void func_80017E8C(s32);   /* src/800.c already declares this as (s32) at L1122/L1244 */
extern s32 RotTransPers4(void *, void *, void *, void *,
                          s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void func_80018094(void *, s32, u32);

typedef struct {
    u32 xy;
    s16 z;
    s16 pad;
} V0_80017294;   /* 8 bytes */

typedef struct {
    V0_80017294 v[4];  /* 0x00 */
    u32 rgbc;           /* 0x20 */
    u32 flags;           /* 0x24 */
} Src_80017294;

typedef struct {
    u32 tag;
    u32 rgbc;
    u32 xy0;
    u32 xy1;
    u32 xy2;
    u32 xy3;
} F4_80017294;   /* 0x18 bytes, POLY_F4 layout */

void func_80017294(Src_80017294 *arg0, s32 arg1)
{
    F4_80017294 *p;
    s32 otz;
    s32 flag;
    s32 opz;

    p = (F4_80017294 *)func_80010A08(0x18);
    p->rgbc = arg0->rgbc;
    SetPolyF4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        otz = RotTransPers4(&arg0->v[0], &arg0->v[1], &arg0->v[2], &arg0->v[3],
                             (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy2, (s32 *)&p->xy3,
                             &opz, &flag);
    } else {
        p->xy0 = arg0->v[0].xy;
        p->xy1 = arg0->v[1].xy;
        p->xy2 = arg0->v[2].xy;
        p->xy3 = arg0->v[3].xy;
        otz = arg0->v[0].z;
        /* zero-byte scheduling barrier: without it gcc-2.7.2's sched1 hoists
         * `flag = 0` into the load-delay slot after the xy3 load (sched1
         * normalises statement order away, cf. func_80015D4C's note in this
         * same TU); the barrier keeps the store in its natural last position,
         * leaving a genuine nop in that slot as the target has. */
        __asm__ __volatile__("" ::: "memory");
        flag = 0;
    }

    if ((flag & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->flags);
    }
}

void func_8001739C(void *arg0)
{
    func_800173DC(arg0, 0);
}

void func_800173BC(void)
{
    func_800173DC();
}


/* SVECTOR-shaped vertex: vx/vy packed as one word (xy), then z, then pad.
 * Same layout convention as V16F18 in func_80016F18 (src/800.c). */
typedef struct {
    u32 xy;   /* 0x0: vx (lo16) | vy (hi16) */
    s16 z;    /* 0x4 */
    s16 pad;  /* 0x6 */
} SVec3_800173DC; /* 0x8 */

/* Source descriptor: three vertices + three Gouraud colour words + a trailing
 * flags/attr word (only ever read, never as a vertex). */
typedef struct {
    SVec3_800173DC v0;      /* 0x00 */
    SVec3_800173DC v1;      /* 0x08 */
    SVec3_800173DC v2;      /* 0x10 */
    u32 rgbc0;               /* 0x18 */
    u32 rgbc1;               /* 0x1C */
    u32 rgbc2;               /* 0x20 */
    u32 attr;                /* 0x24 */
} Src_800173DC;

/* POLY_G3 (libgpu), 0x1C bytes. */
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgbc0;  /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 rgbc1;  /* 0x0C */
    u32 xy1;    /* 0x10 */
    u32 rgbc2;  /* 0x14 */
    u32 xy2;    /* 0x18 */
} G3_800173DC; /* 0x1C */

extern void *func_80010A08(s32 size);
extern void SetPolyG3(G3_800173DC *p);
extern void func_80017E8C(s32 arg0);
extern s32 RotTransPers3(void *v0, void *v1, void *v2,
                          s32 *sxy0, s32 *sxy1, s32 *sxy2,
                          s32 *p, s32 *flag);
/* §183 TYPE-adopted-TU: src/800.c declares (and defines at 0x80018094) the
 * third parameter as u32; adopt the TU's spelling verbatim. arg0->attr is
 * already u32, so no cast is needed at the use site and codegen is unchanged. */
extern void func_80018094(void *a0, s32 a1, u32 a2);

void func_800173DC(Src_800173DC *arg0, s32 arg1)
{
    G3_800173DC *p;
    s32 otzp;
    s32 flg;
    s32 otz;

    p = (G3_800173DC *)func_80010A08(0x1C);
    p->rgbc0 = arg0->rgbc0;
    p->rgbc1 = arg0->rgbc1;
    p->rgbc2 = arg0->rgbc2;
    SetPolyG3(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        otz = RotTransPers3(&arg0->v0, &arg0->v1, &arg0->v2,
                             (s32 *)&p->xy0, (s32 *)&p->xy1, (s32 *)&p->xy2,
                             &otzp, &flg);
    } else {
        p->xy0 = arg0->v0.xy;
        p->xy1 = arg0->v1.xy;
        p->xy2 = arg0->v2.xy;
        __asm__ volatile("");
        otz = arg0->v0.z;
        flg = 0;
    }

    if ((flg & ~0x1000) == 0) {
        func_80018094(p, otz, arg0->attr);
    }
}

void func_800174DC(void *arg0)
{
    func_8001751C(arg0, 0);
}

void func_800174FC(void)
{
    func_8001751C();
}

/* func_8001751C (POLY_GT3 builder) -- splat tags the target "Handwritten
 * function": hand-placed cop2 nops and delay-slot fills no -O2 C emits.
 * The GTE ops are written as single-statement inline asm (NO backslash-
 * continued macros, NO typedefs, externs block-scoped with the canonical
 * def-sigs) so the body is self-contained and liftable to any splice point
 * (cookbook recover_giant shape).
 *
 * Recovered semantics: alloc 0x28 POLY_GT3 via func_80010A08; copy the three
 * colour words; SetPolyGT3; if arg1: func_80017E8C + rtpt over the three
 * vertices (sxy -> p+8/0x14/0x20, IR0 -> sz, FLAG -> flag, SZ3>>2 -> otz),
 * else copy the xy words through, otz = (s16)v0.vz, sz = 0; split the three
 * uv words into u/v bytes; tpage/clut via GetTPage/GetClut; finally
 * if ((sz & ~0x1000) == 0) func_80018194(p, otz, attr).
 */
void func_8001751C(s32 *arg0, s32 arg1)
{
    extern void *func_80010A08(s32);
    extern void SetPolyGT3();
    extern void func_80017E8C(s32);
    extern s32 GetTPage(s32, s32, s32, s32);
    extern s32 GetClut(s32, s32);
    extern void func_80018194(void *, s32, u32);

    u8 *p;
    s32 *va1, *va2;
    u8 *d0, *d1, *d2;
    s32 sz, flag, otz;
    u32 t, c;

    p = (u8 *)func_80010A08(0x28);
    *(u32 *)(p + 4) = *(u32 *)(arg0 + 9);
    *(u32 *)(p + 16) = *(u32 *)(arg0 + 10);
    *(u32 *)(p + 28) = *(u32 *)(arg0 + 11);
    SetPolyGT3(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        va1 = arg0 + 2;
        va2 = arg0 + 4;
        __asm__ volatile (
            "lwc2 $0, 0( %0 );"
            "lwc2 $1, 4( %0 );"
            "lwc2 $2, 0( %1 );"
            "lwc2 $3, 4( %1 );"
            "lwc2 $4, 0( %2 );"
            "lwc2 $5, 4( %2 )"
            : : "r"(arg0), "r"(va1), "r"(va2));
        __asm__ volatile ("nop;nop;rtpt");
        d0 = p + 8;
        d1 = p + 20;
        d2 = p + 32;
        __asm__ volatile (
            "swc2 $12, 0( %0 );"
            "swc2 $13, 0( %1 );"
            "swc2 $14, 0( %2 )"
            : : "r"(d0), "r"(d1), "r"(d2) : "memory");
        __asm__ volatile ("swc2 $8, 0( %0 )" : : "r"(&sz) : "memory");
        __asm__ volatile (
            "cfc2 $12, $31;nop;sw $12, 0( %0 )"
            : : "r"(&flag) : "$12", "memory");
        __asm__ volatile (
            "mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0( %0 )"
            : : "r"(&otz) : "$12", "memory");
    } else {
        *(u32 *)(p + 8) = *(u32 *)(arg0 + 0);
        *(u32 *)(p + 20) = *(u32 *)(arg0 + 2);
        *(u32 *)(p + 32) = *(u32 *)(arg0 + 4);
        otz = *(s16 *)((s8 *)arg0 + 4);
        sz = 0;
    }

    t = *(u32 *)(arg0 + 6);
    *(p + 12) = t;
    *(p + 13) = t >> 16;
    t = *(u32 *)(arg0 + 7);
    *(p + 24) = t;
    *(p + 25) = t >> 16;
    t = *(u32 *)(arg0 + 8);
    *(p + 36) = t;
    *(p + 37) = t >> 16;

    *(u16 *)(p + 26) = GetTPage(((*(u32 *)(arg0 + 12)) >> 24) & 3,
                                ((*(u32 *)(arg0 + 12)) >> 28) & 3,
                                ((*(u16 *)((s8 *)arg0 + 24)) >> 2) & 0x3FC0,
                                *(u16 *)((s8 *)arg0 + 26) & 0xFF00);

    c = *((u8 *)arg0 + 52);
    *(u16 *)(p + 14) = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((sz & ~0x1000) == 0) {
        func_80018194((void *)p, otz, *(u32 *)(arg0 + 12));
    }
}

void func_800176F0(void *arg0)
{
    func_80017778(arg0, 0, 1);
}

void func_80017714(void *arg0) {
    extern void func_80017778();
    ((void (*)(void *, s32, s32))func_80017778)(arg0, 0, 0);
}

void func_80017738(void *a0, s32 a1)
{
    func_80017778(a0, a1, 1);
}

void func_80017758(void *a0, s32 a1)
{
    func_80017778(a0, a1, 0);
}


/* func_80017778 — src/800.c (main, -O2).
 *
 * Builds one POLY_G4 (0x24 bytes) from a "vector-quad" descriptor (arg0):
 *   0x00..0x1F  four SVECTORs (v0..v3)
 *   0x20..0x2F  four packed rgb+code words
 *   0x30        a flags-ish word forwarded verbatim to the submit call
 * arg1 != 0 -> run RotTransPers4 on v0..v3 (perspective project into the
 *              packet's xy0..xy3), func_80017E8C(arg1) primes the matrix;
 * arg1 == 0 -> copy the already-projected xy words straight through and use
 *              v0.vz as otz.
 * Then, unless the RotTransPers4 clip flag (bit 0x1000 masked off) is set,
 * hand the packet to func_80017F14 (arg2 != 0) or func_80018094 (arg2 == 0).
 *
 * Mirrors the already-matched sibling func_80017930 (same file) which builds
 * a POLY_GT4 the same way; here there is no uv/tpage/clut section and the GTE
 * work goes through the SDK helper RotTransPers4 instead of raw gte_* macros.
 */

extern void *func_80010A08(s32);
extern void SetPolyG4(void *);
extern void func_80017E8C(s32);
extern s32 RotTransPers4(void *, void *, void *, void *,
                          s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void func_80017F14(void *, s32, s32);
extern void func_80018094(void *, s32, u32);

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80017778;

typedef struct {
    SV_80017778 v[4]; /* 0x00 */
    u32 rgb[4];        /* 0x20 */
    u32 flags;          /* 0x30 */
} Src_80017778;

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
    u8 r3, g3, b3, pad3;
    s16 x3, y3;
} G4_80017778;

void func_80017778(Src_80017778 *arg0, s32 arg1, s32 arg2)
{
    G4_80017778 *p;
    s32 otz;
    s32 opz;
    s32 flag;

    p = (G4_80017778 *)func_80010A08(0x24);
    *(u32 *)&p->r0 = arg0->rgb[0];
    *(u32 *)&p->r1 = arg0->rgb[1];
    *(u32 *)&p->r2 = arg0->rgb[2];
    *(u32 *)&p->r3 = arg0->rgb[3];
    SetPolyG4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        otz = RotTransPers4(&arg0->v[0], &arg0->v[1], &arg0->v[2], &arg0->v[3],
                             (s32 *)&p->x0, (s32 *)&p->x1, (s32 *)&p->x2, (s32 *)&p->x3,
                             &opz, &flag);
    } else {
        *(u32 *)&p->x0 = *(u32 *)&arg0->v[0];
        *(u32 *)&p->x1 = *(u32 *)&arg0->v[1];
        *(u32 *)&p->x2 = *(u32 *)&arg0->v[2];
        *(u32 *)&p->x3 = *(u32 *)&arg0->v[3];
        otz = arg0->v[0].vz;
        flag = 0;
    }

    if ((flag & ~0x1000) == 0) {
        if (arg2 != 0) {
            func_80017F14(p, otz, arg0->flags);
        } else {
            func_80018094(p, otz, arg0->flags);
        }
    }
}

void func_800178C8(void *arg0)
{
    func_80017930(arg0, 0, 1);
}

void func_800178EC(s32 a0) {
    func_80017930(a0, 0, 0);
}

void func_80017910(void *a0, s32 a1) {
    func_80017930(a0, a1, 0);
}


/* func_80017930 — src/800.c (main, -O2).
 *
 * Builds one POLY_GT4 (0x34 bytes) from a 0x48-byte "sprite/quad descriptor":
 *   0x00..0x1F  four SVECTORs (v0..v3)
 *   0x20..0x2F  four packed u/v words (u in bits 0..15, v in bits 16..31)
 *   0x30..0x3F  four rgb+code words
 *   0x40        flag/tpage word (bits 24-25 = tp, bits 28-29 = abr)
 *   0x44        clut index byte
 * arg1 != 0 -> run the GTE (RTPT on v0..v2, RTPS on v3, AVSZ4 -> otz);
 * arg1 == 0 -> copy the xy pairs straight through and use v0.vz as otz.
 * Finally GetTPage/GetClut and hand the prim to func_8001820C (arg2 != 0) or func_80018194.
 */

extern void *func_80010A08(s32 size);
extern void SetPolyGT4(void *p);
extern void func_80017E8C(s32 arg0);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern s32 GetClut(s32 x, s32 y);
extern void func_8001820C(void *p, s32 otz, u32 flags);
extern void func_80018194(void *p, s32 otz, u32 flags);

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80017930;

typedef struct {
    SV_80017930 v[4]; /* 0x00 */
    u32 uv[4];        /* 0x20 */
    u32 rgb[4];       /* 0x30 */
    u32 flags;        /* 0x40 */
    u8 clut;          /* 0x44 */
} Src_80017930;

typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    s16 x0, y0; /* 0x08 */
    u8 u0, v0;  /* 0x0C */
    u16 clut;   /* 0x0E */
    u32 rgb1;   /* 0x10 */
    s16 x1, y1; /* 0x14 */
    u8 u1, v1;  /* 0x18 */
    u16 tpage;  /* 0x1A */
    u32 rgb2;   /* 0x1C */
    s16 x2, y2; /* 0x20 */
    u8 u2, v2;  /* 0x24 */
    u16 pad2;   /* 0x26 */
    u32 rgb3;   /* 0x28 */
    s16 x3, y3; /* 0x2C */
    u8 u3, v3;  /* 0x30 */
    u16 pad3;   /* 0x32 */
} GT4_80017930; /* 0x34 */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

void func_80017930(Src_80017930 *arg0, s32 arg1, s32 arg2)
{
    s32 flag1;
    s32 flag2;
    s32 otz;
    GT4_80017930 *p;
    u32 w;
    u32 f;
    u32 c;

    p = (GT4_80017930 *)func_80010A08(0x34);
    p->rgb0 = arg0->rgb[0];
    p->rgb1 = arg0->rgb[1];
    p->rgb2 = arg0->rgb[2];
    p->rgb3 = arg0->rgb[3];
    SetPolyGT4(p);

    if (arg1 != 0) {
        func_80017E8C(arg1);
        gte_ldv3(&arg0->v[0], &arg0->v[1], &arg0->v[2]);
        gte_rtpt();
        gte_stflg(&flag1);
        gte_stsxy3(&p->x0, &p->x1, &p->x2);
        gte_ldv0(&arg0->v[3]);
        gte_rtps();
        gte_stflg(&flag2);
        flag1 |= flag2;
        gte_stsxy(&p->x3);
        gte_avsz4();
        gte_stotz(&otz);
    } else {
        *(u32 *)&p->x0 = *(u32 *)&arg0->v[0];
        *(u32 *)&p->x1 = *(u32 *)&arg0->v[1];
        *(u32 *)&p->x2 = *(u32 *)&arg0->v[2];
        *(u32 *)&p->x3 = *(u32 *)&arg0->v[3];
        flag1 = 0;
        otz = arg0->v[0].vz;
    }

    w = arg0->uv[0];
    p->u0 = w;
    p->v0 = w >> 16;
    w = arg0->uv[1];
    p->u1 = w;
    p->v1 = w >> 16;
    w = arg0->uv[2];
    p->u2 = w;
    p->v2 = w >> 16;
    w = arg0->uv[3];
    p->u3 = w;
    p->v3 = w >> 16;

    f = arg0->flags;
    p->tpage = GetTPage((f >> 24) & 3, (f >> 28) & 3,
                        (*(u16 *)&arg0->uv[0] >> 2) & 0x3FC0,
                        *((u16 *)&arg0->uv[0] + 1) & 0xFF00);

    c = arg0->clut;
    p->clut = GetClut(c < 0xE0 ? 0x160 : 0x100, c | 0x100);

    if ((flag1 & ~0x1000) == 0) {
        if (arg2 != 0) {
            func_8001820C(p, otz, arg0->flags);
        } else {
            func_80018194(p, otz, arg0->flags);
        }
    }
}


/* func_80017B98 — main/800: build one 0x2C-byte GPU packet holding a PSY-Q SPRT
 * (code 0x64) preceded by an E1 draw-mode word, fill it from the caller's
 * 0x1C-byte sprite-request block (== engine_types.h T8016EC0C, the struct
 * func_8016EC0C fills before calling here), then link it into the current
 * double-buffer's OT at depth `otz` with the open-coded PSY-Q addPrim() RMW pair.
 *
 * Packet layout (prim = the 0x2C alloc; sp = (SPRT *)(prim + 4)):
 *   prim+0x00  u32 tag        = 0x05000000   (len 5, addr filled by addPrim)
 *   sp +0x00   u32 tag        = 0xE1000000 | tpage bits   (GP0 E1 draw mode)
 *   sp +0x04   r0,g0,b0,code  = 0x64<<24 | b<<16 | g<<8 | b   (NOTE: r0 == b0 ==
 *                               src->b at +0x12; src->r at +0x10 is never read)
 *   sp +0x08   x0,y0          = src->x - src->w/2, src->y - src->h/2
 *   sp +0x0C   u0,v0,clut
 *   sp +0x10   w,h
 *
 * @class: was regalloc-order + IOR-tree reassociation
 * @stuck: none — MATCH (128 ins), byte-exact under match_one.
 *
 * LEVERS (each verified by removing it and re-scoring):
 *  1. `sp->code = 0x64;` must sit AFTER the `sp->tag = ...` statement (51 -> 36).
 *     Source order is the sched1 tie-break that lets the three tag operand loads
 *     hoist above the code sb, which is what fixes the whole temp-register naming
 *     of the tag chain.  (cookbook §175 lever A: statement order.)
 *  2. THE CONSTANT 0x64000000 MUST BE A LOCAL VARIABLE, NOT A LITERAL.  Written
 *     literally, gcc-2.7.2's fold `associate` rewrites  X | (Y | C)  into
 *     (X | C) | Y  — it emits `or (b<<16), C` first, where the target emits
 *     `or (g<<8), C` first.  split_tree() only pulls a constant that is a DIRECT
 *     operand, so binding it to `u32 code` (a VAR_DECL at tree level, folded back
 *     to the same `lui` by RTL cse) leaves the source tree untouched.  51 -> 35
 *     with the correct or-tree.  (`+ 0x64000000` also blocks the rewrite but
 *     emits `addu` instead of `or` — 1 permanent mismatch.)
 *  3. `t = (n + 0x100) << 6;` must be its own local.  Inline in the ternary, gcc
 *     folds (n+0x100)<<6 | 0x16 into `sll n,6` + `ori 0x4016` (2 ins, wrong
 *     shape); the shared temp keeps the target's addiu/sll/ori triple.
 *  4. The clut value needs its own local `cl` too — otherwise cse carries the
 *     `sp = prim+4` equivalence into the join block and rewrites the store as
 *     0x12(prim) instead of the target's 0xE(sp).  (1 ins.)
 *  5. The 0xFF000000 / 0x00FFFFFF masks must be LOCALS (m24/mFF), not literals:
 *     as locals their `lui` is a join-block insn that delay-slot-fills the otz
 *     clamp branch; as literals they are rematerialised per use and reorg
 *     duplicates `sll d4,2` into the delay slot instead.  Same lever as
 *     func_80016450 in this file.
 *  6. `d4 += D_800A651C[...].a;` (self-accumulate) reproduces `addu $a1,$a1,$v0`
 *     — the second addPrim half reusing the depth*4 register.  Operand order
 *     `d4 + D_800A651C[...].a` (not the reverse) gives `addu $v0,$a1,$v0`.
 *     Both inherited from func_80016450's header.
 *  7. `*(u32 *)prim` / `*(u32 *)&sp->r0`, never a struct member, wherever the
 *     store has to kill CSE — that is what forces the two reloads of
 *     `s->flags` (0x14) and the two reloads of the D_800AF630 index.
 *
 * PIN-TRIM LOG (all re-scored; four pins are the verified minimum):
 *   drop `m24` $6 pin                 — MATCH  (dropped)
 *   drop `mFF` $7 pin                 — MATCH  (dropped)
 *   drop both mask pins together      — MATCH  <= this file
 *   drop `d4` $5 pin alone            — MATCH, but 13/11/16 mismatched in every
 *                                       combination with a mask pin dropped, so
 *                                       it is kept (it is what makes otz land in
 *                                       $a1 and the masks in $a2/$a3)
 *   drop `pv` $4 pin                  — 4 mismatched
 *   drop `bb` $5 pin                  — 5 mismatched
 *   drop `pbase` $17 pin              — 126 ins, 124 mismatched (D_800AF630 base
 *                                       must live in a callee-saved reg)
 *   pin `prim` to $8                  — 28 mismatched (never pin prim; it lands
 *                                       in $t0 by itself once d4/masks are pinned)
 *
 * SYMBOL AUDIT (§174 law 1c, done after MATCH) — every symbol re-checked against
 * asm/nonmatchings/800/func_80017B98.s's own relocation lines:
 *   jal func_80010A08 (0x83AC)  •  %hi/%lo(D_800AF630) -> $s1 (0x8468/0x846C),
 *   dereferenced at $s1+0x10000-0x5C2E == 0x800B9A02, the same u16 frame index
 *   src/boot.c reads as `*(u16 *)(p + 0xA3D2)`  •  %hi/%lo(D_800A651C) via `lw`,
 *   twice (0x8514/0x851C and 0x8558/0x8560).  No other relocations exist.
 *   Store sides: `sw $a0,0($t0)` is the packet tag, `sw $v0,0($a1)` is the OT
 *   slot, `sw $v1,0x8($t0)`/`sw $v0,4($a0)` are both the r0g0b0code word.
 *   Load sides: the colour word takes 0x12 ($a1) TWICE (low byte and byte 2) and
 *   0x11 ($v0) once — src->r at 0x10 is genuinely never read by this function.
 *
 * BANK NOTE (§174 law 2): src/800.c already defines
 *     typedef struct { s32 a; s32 b[4]; } OtBlk_80016450;      (file scope)
 * and both func_80015D4C and func_80016450 declare
 *     extern OtBlk_80016450 D_800A651C[];                      (block scope)
 * This draft reuses THAT name so the third block-scope extern agrees with them
 * (a differently-named but structurally identical typedef only produces
 * "type mismatch with previous external decl" warnings, but agreeing is free).
 * ==> DROP the OtBlk_80016450 typedef line below when banking into src/800.c;
 *     it is present only so this file compiles standalone under match_one.
 * src/800.c also already declares `extern void *func_80010A08(s32 a0);` (L694)
 * — adopted verbatim.  D_800AF630 is not declared anywhere in that TU nor in any
 * header it includes, so the `extern u8 D_800AF630[];` below is the canonical
 * repo-wide form (src/boot.c L14/L37, every ov_* sibling).
 * src/800.c contains no prototype for func_80017B98 itself, so the definition's
 * `void func_80017B98(void *arg0)` is unconstrained (law 3 clear); it matches the
 * callers' `extern void func_80017B98(void *a0);`.
 */

/* DROP WHEN BANKING — already defined at file scope in src/800.c */

/* PSY-Q SPRT laid at prim+4; its `tag` word doubles as the E1 draw-mode command */
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u8  r0, g0, b0, code;
    /* 0x08 */ s16 x0, y0;
    /* 0x0C */ u8  u0, v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u16 w, h;
} Sprt_80017B98;

/* the caller's request block == engine_types.h T8016EC0C */
typedef struct {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
    /* 0x04 */ s32 otz;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ u16 u;
    /* 0x0E */ u16 v;
    /* 0x10 */ u8  r;
    /* 0x11 */ u8  g;
    /* 0x12 */ u8  b;
    /* 0x13 */ u8  pad13;
    /* 0x14 */ u32 flags;
    /* 0x18 */ u8  tp;
    /* 0x19 */ u8  pad19[3];
} Src_80017B98;

extern void *func_80010A08(s32 a0);
extern u8 D_800AF630[];

void func_80017B98(void *arg0)
{
    extern OtBlk_80016450 D_800A651C[];   /* block scope: matches func_80015D4C / func_80016450 in this TU */
    Src_80017B98 *s = (Src_80017B98 *)arg0;
    u8 *prim;
    Sprt_80017B98 *sp;
    register u8 *pbase __asm__("$17");
    u32 n;
    u32 t;
    u32 m24;
    u32 mFF;
    register u32 pv __asm__("$4");
    register s32 d4 __asm__("$5");

    prim = (u8 *)func_80010A08(0x2C);
    *(u32 *)prim = 0x05000000;
    sp = (Sprt_80017B98 *)(prim + 4);
    sp->tag = ((s->flags >> 23) & 0x60) | ((s->v >> 4) & 0x10) |
              ((s->u >> 8) & 0xF) | ((s->v & 0x200) << 2) | 0xE1000000;
    sp->code = 0x64;
    {
        u32 code = 0x64000000;
        register u32 bb __asm__("$5") = s->b;
        *(u32 *)&sp->r0 = (bb << 16) | ((s->g << 8) | code) | bb;
    }
    sp->x0 = s->x - (s->w >> 1);
    sp->y0 = s->y - (s->h >> 1);
    sp->u0 = s->u;
    pbase = D_800AF630;
    sp->v0 = s->v;
    n = s->tp;
    t = (n + 0x100) << 6;
    {
        u16 cl = (n < 0xE0) ? (t | 0x16) : (t | 0x10);
        sp->clut = cl;
    }
    sp->w = s->w;
    sp->h = s->h;
    if (s->flags & 0x40000000) {
        *(u32 *)&sp->r0 = *(u32 *)&sp->r0 | 0x02000000;
    }
    d4 = s->otz;
    if (d4 >= 0x1000) {
        d4 = 0xFFF;
    }
    m24 = 0x00FFFFFF;
    mFF = 0xFF000000;
    d4 = d4 * 4;
    pv = *(u32 *)prim;
    *(u32 *)prim = (pv & mFF) |
        (*(u32 *)(d4 + D_800A651C[*(u16 *)(pbase + 0xA3D2)].a) & m24);
    d4 += D_800A651C[*(u16 *)(pbase + 0xA3D2)].a;
    *(u32 *)d4 = (*(u32 *)d4 & mFF) | ((u32)prim & m24);
}


void func_80017D98(void *a0)
{
    s16 val = 0x1000;
    s16 *p = (s16 *)a0;
    p[0] = val;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = val;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = val;
}

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
} Dst17DC4;

void func_80017DC4(u16 *a0, Dst17DC4 *a1) {
    a1->unk00 = a0[0];
    a1->unk02 = 0;
    a1->unk04 = 0;
    a1->unk06 = 0;
    a1->unk08 = a0[1];
    a1->unk0A = 0;
    a1->unk0C = 0;
    a1->unk0E = 0;
    a1->unk10 = a0[2];
}


extern void func_8004978C(s16 *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);

void func_80017DF8(s16 *a0, void *a1) {
    s16 temp[16];
    func_8004978C(a0, temp);
    func_80048EAC(temp, a1);
}


extern void func_80049CAC(s32 a0, s32 a1);
extern void func_80048EAC(void *a0, void *a1);

void func_80017E30(s32 a0, s32 a1) {
    s32 local_buf[8]; /* 0x20 bytes at sp+0x10 */

    func_80049CAC(a0, (s32)local_buf);
    func_80048EAC(local_buf, (void *)a1);
}

void func_80017E68(short *arg0, int *arg1) {
    arg1[5] = arg0[0];
    arg1[6] = arg0[1];
    arg1[7] = arg0[2];
}

typedef struct { s32 w[8]; } Blk32_80017E8C;

extern u8 D_800AF648;
extern void CompMatrix(void *, void *, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);

void func_80017E8C(s32 arg0)
{
    Blk32_80017E8C m;

    m = *(Blk32_80017E8C *)arg0;
    CompMatrix(&D_800AF648, &m, &m);
    func_8004914C(&m);
    func_800491AC(&m);
}

/* func_80017F14 · m12 · cache-bust resubmission of the converged body.
 * Semantics identical to the wave_m10/shard4 leftover; text is fresh so any
 * hash-keyed verdict cache must re-gate rather than replay. Full ledger in
 * submit notes: guard covers ONLY the |=2; both tpage sequences unconditional;
 * sig unified to the TU's own (void*, s32, s32); anon inline struct = the
 * OtBlk_80016450 layout; scalar rival spelling measured worse (99 ins). */
void func_80017F14(void *a0, s32 a1, s32 a2)
{
    extern u16 D_800B9A02;
    extern struct { s32 a; s32 b[4]; } D_800A651C[];
    extern void *func_80010A08(s32);
    extern s32 AddPrim(s32, void *);
    extern s32 GetTPage(s32, s32, s32, s32);
    extern s32 func_8005A600(s32, s32, s32, s32, s32);

    void *p2;
    s32 sz;
    s32 tp;

    /* sz clamp: >= 0x1000 saturates to 0xFFF (sltiu/bnez/addiu triple) */
    sz = a1;
    if ((u32)sz >= 0x1000) {
        sz = 0xFFF;
    }

    p2 = func_80010A08(0xC);
    tp = GetTPage(2, ((u32)a2 >> 28) & 3, 0x280, 0);
    func_8005A600((s32)p2, 0, 0, (u16)tp, 0);
    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, p2);

    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, a0);

    /* guard covers ONLY the code |=2 — the second tpage packet follows
     * UNCONDITIONALLY (beqz target sits before its jal func_80010A08) */
    if ((u32)a2 & 0x40000000) {
        *(u8 *)((u8 *)a0 + 7) = *(u8 *)((u8 *)a0 + 7) | 2;
    }

    p2 = func_80010A08(0xC);
    tp = GetTPage(2, ((u32)a2 >> 28) & 3, 0x280, 0);
    func_8005A600((s32)p2, 0, 1, (u16)tp, 0);
    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, p2);
}



extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);
extern u16 D_800B9A02;

void func_80018094(void *a0, s32 a1, u32 a2_p) {
    s32 a2 = (s32)a2_p;
    extern OtBlk_80016450 D_800A651C[];
    void *p2;
    s32 sz;
    s32 tp;

    sz = a1;
    if ((u32)sz >= 0x1000) {
        sz = 0xFFF;
    }

    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, a0);

    if (a2 & 0x40000000) {
        *(u8 *)((u8 *)a0 + 7) = *(u8 *)((u8 *)a0 + 7) | 2;
        p2 = func_80010A08(0xC);
        tp = GetTPage(2, ((u32)a2 >> 28) & 3, 0x280, 0);
        func_8005A600((s32)p2, 0, 0, (u16)tp, 0);
        AddPrim(D_800A651C[D_800B9A02].a + sz * 4, p2);
    }
}

void func_80018194(void *arg0, s32 arg1, u32 arg2)
{
    extern s32 AddPrim(s32, void *);
    extern u16 D_800B9A02;
    extern struct { s32 a; s32 b[4]; } D_800A651C[];
    void *a3;
    s32 sz;

    a3 = arg0;
    if (arg2 & 0x40000000) {
        *(u32 *)((u8 *)a3 + 4) |= 0x02000000;
    }

    sz = arg1;
    if ((u32)sz >= 0x1000) {
        sz = 0xFFF;
    }

    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, a3);
}


void func_8001820C(void *a0, s32 a1, u32 a2)
{
    extern void *func_80010A08(s32);
    extern s32 AddPrim(s32, void *);
    extern s32 GetTPage(s32, s32, s32, s32);
    extern s32 func_8005A600(s32, s32, s32, s32, s32);
    extern u16 D_800B9A02;
    extern OtBlk_80016450 D_800A651C[];

    void *p2;
    s32 sz;
    s32 tp;

    sz = a1;
    if ((u32)a2 & 0x40000000) {
        *(u32 *)((u8 *)a0 + 4) = *(u32 *)((u8 *)a0 + 4) | 0x02000000;
    }
    if ((u32)sz >= 0x1000) {
        sz = 0xFFF;
    }

    p2 = func_80010A08(0xC);
    tp = GetTPage(2, ((u32)a2 >> 28) & 3, 0x280, 0);
    func_8005A600((s32)p2, 0, 0, (u16)tp, 0);
    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, p2);

    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, a0);

    p2 = func_80010A08(0xC);
    tp = GetTPage(2, ((u32)a2 >> 28) & 3, 0x280, 0);
    func_8005A600((s32)p2, 0, 1, (u16)tp, 0);
    AddPrim(D_800A651C[D_800B9A02].a + sz * 4, p2);
}

extern u32 D_800AE610;

void func_80018384(void *a0, void *a1) {
    u32 *a2 = (u32 *)a0;
    u32 *a3 = (u32 *)a1;

    if ((u32)&D_800AE610 < (u32)a2) {
        for (;;)
            ;
    }
    *a3 = (*a3 & 0xFF000000) | (*a2 & 0x00FFFFFF);
    *a2 = (*a2 & 0xFF000000) | ((u32)a3 & 0x00FFFFFF);
}

extern u8 D_800AF630[];

s32 func_800183E0(s32 a0)
{

    Base *b = (Base *)D_800AF630;
    s32 i;
    s32 ret;

    ret = 0;
    i = 0;
    do {
        if (b->rec[i].flag == 0) {
            b->rec[i].flag = 1;
            b->rec[i].id = a0;
            b->rec[i].d = 0;
            ret = 1;
            goto out;
        }
        i++;
    } while (i < 0x20);
out:
    return ret;
}

s32 func_80018450(void *a0, s32 a1)
{
    extern u8 D_800AF630[];
    Base *b = (Base *)D_800AF630;
    s32 i;
    s32 ret;

    ret = 0;
    i = 0;
    do {
        if (b->rec[i].flag != 0) {
            i++;
        } else {
            b->rec[i].flag = 1;
            b->rec[i].id = a1;
            b->rec[i].d = 0;
            b->rec[i].x = *(u16 *)((u8 *)a0 + 0x28);
            b->rec[i].y = *(u16 *)((u8 *)a0 + 0x2A);
            b->rec[i].c = *(u8 *)((u8 *)a0 + 0x27);
            ret = 1;
            break;
        }
    } while (i < 0x20);
    return ret;
}


typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} SpadRect_800184F0;


typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 x;
    /* 0x06 */ u16 y;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ void *data;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} TexInfo_800184F0;


extern DispSlot_800184F0 D_800B97D8[];

extern void func_800599B8(SpadRect_800184F0 *rect, void *data);
extern void func_80053D44(void *data, TexInfo_800184F0 *out);
extern void func_80058890(void *data, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_800184F0(void) {
    SpadRect_800184F0 *rect = (SpadRect_800184F0 *)0x1F800000;
    TexInfo_800184F0 tmp;
    DispSlot_800184F0 *e;
    DispItem_800184F0 *p;
    s32 i;
    s32 done;
    s32 t;

    for (i = 0, e = D_800B97D8; i < 32; i++, e++) {
        if (e->flag == 0) {
            continue;
        }
        p = e->list;
        done = 0;
        do {
            t = p->type;
            if (t == 9) {
                goto b9;
            }
            if (t < 10) {
                if (t == 0) {
                    goto b0;
                }
                if (t == 5) {
                    goto b5;
                }
                done = 1;
                goto cont;
            }
            if (t == 11) {
                goto b11;
            }
            if (t < 11) {
                goto cont;
            }
            goto dflt;

        b9:
            if (e->unk0D == 0) {
                rect->x = p->x;
                rect->y = p->y;
                goto tail;
            }
            rect->x = ((u32)e->unk0C > 0x20) << 8;
            rect->y = e->unk0C | 0x1E0;
            goto tail;

        b0:
            if (e->unk0D == 0) {
                rect->x = p->x;
                rect->y = p->y;
                goto tail;
            }
            rect->x = e->unk08;
            rect->y = e->unk0A;
        tail:
            rect->w = p->w;
            rect->h = p->h;
            func_800599B8(rect, p->data);
            goto cont;

        b5:
            func_80053D44(p->data, &tmp);
            rect->x = tmp.x;
            rect->y = tmp.y;
            rect->w = tmp.w;
            rect->h = tmp.h;
            func_800599B8(rect, tmp.data);
            goto cont;

        b11:
            func_80058890(p->data, 1, 0, (s16)p->x, (s16)p->y, (s16)p->w * 2, (s16)p->h);
            goto cont;
        dflt:
            done = 1;
        cont:
            p++;
        } while (!done);
        e->flag = 0;
    }
}

extern unsigned int lzss_state;          /* 0x800C7D24 */
extern unsigned char *lzss_outPtr;       /* 0x800747AC */

/* LZSS sector-state reset: state = 1 (fresh), outPtr = destination buffer.
 * Sole caller: CdReadSectorReadyCB PAC-type-4 case (passes cdReq_dest).
 * K&R unprototyped definition ON PURPOSE: compatible with the stale
 * `extern void func_80018714(void);` further down the TU, while still
 * reading $a0. Types spelled as builtins so this compiles both
 * standalone and inside src/800.c (u32==unsigned int, u8==unsigned char). */
void func_80018714(arg0) void *arg0; {
    lzss_state = 1;
    lzss_outPtr = (unsigned char *)arg0;
}

/* LZSS streaming sector decompressor (resumable coroutine state machine).
 * Decodes up to 0x800 input bytes per call out of an LZSS stream into a 0x400-byte
 * scratchpad ring (lzss_ringBuffer @ 0x1F800000) and to lzss_outPtr. lzss_state is the
 * resume point (0=idle/done, 1=fresh, 2=token loop, 3=have code low byte, 4=advance bit).
 * Returns 1 if the input sector was consumed mid-stream (resume next call), 0 at the
 * stream terminator (back-ref offset 0) or when idle. */
/* MATCHED — asm-differ score 0, full-binary SHA1 green (Phase 7, session F, 2026-06-15).
 * Five constructs below are LOAD-BEARING for the byte-for-byte match against gcc 2.7.2 -O2; a
 * future reader who "cleans them up" WILL break the match. Each is annotated inline and the
 * compiler-internal root cause is in docs/matching-cookbook.md §10 (+ §5a). All five were
 * ground-truthed against the pinned gcc-2.7.2 source (reorg.c, jump.c, local-alloc.c). */
extern u8 lzss_curMask;        /* 0x800747A0 */
extern u8 lzss_curToken;       /* 0x800747A4 */
extern u8 *lzss_outPtr;        /* 0x800747AC */
extern u32 lzss_ringIndex;     /* 0x800747B0 */
extern u16 lzss_partialCode;   /* 0x800747B4 */
extern u32 lzss_state;         /* 0x800C7D24 */

s32 LzssDecodeSector(u8 *src) {
    s32 count = 0x800;
    u32 ringIdx = lzss_ringIndex;
    u8 mask = lzss_curMask;
    u8 token = lzss_curToken;
    u8 *out = lzss_outPtr;
    u16 code = lzss_partialCode;
    u8 *ring = (u8 *)0x1F800000;   /* scratchpad ring; original uses the literal (lui 0x1f80), not the symbol */
    u32 readIdx;
    s32 len;
    u8 b;
    u8 nb;   /* low-byte (state-3) source byte */
    u8 cb;
    u8 nh;   /* LOAD-BEARING #1 (residual A): a SEPARATE high-byte source var, NOT a reuse of `nb`.
              * `nb` is shared between the low- and high-byte paths; reusing it couples their
              * register allocation, so any high-byte reshaping shoves `nb` out of $v1. A distinct
              * `nh` decouples them. Cookbook §10/A. */
    s32 newState;
    s32 result; /* return-1 value carried in $v0 from each save predecessor (state-3/state-4) */

    /* LOAD-BEARING #2 (residual B3): NO `default:` case and NO statement after the switch. The
     * switch's own range check (`sltiu $v0,state,5; beqz $v0,<epilogue>`) is the ONLY state>=5
     * guard; the `beqz` REUSES the sltiu result ($v0==0 when state>=5) as the return-0 value by
     * threading straight to `jr ra`. An explicit `if(state>=5)return 0;`, a `default:`, or a
     * trailing `return 0;` each makes gcc emit a separate `move $v0,$zero` (+1 insn / wrong branch
     * target). Falling off the end here is deliberate (and matches the original). Cookbook §10/B3. */
    switch (lzss_state) {
    case 0:
        goto term_ret;
    case 1:
        ringIdx = 1;
        mask = 1;
        token = *src++;
        count--;
    case 2:
        for (;;) {
            if (token & mask) {
                b = *src++;
                ring[ringIdx] = b;
                ringIdx = (ringIdx + 1) & 0x3FF;
                count--;
                *out++ = b;
            } else {
                nb = *src++;
                count--;
                code = (code & 0xFF00) | nb;
                if (count != 0) {
                    goto have_low;
                }
                /* LOAD-BEARING #3 (residual B): `result` is set in the state-3 PREDECESSOR (here,
                 * before `goto save`), not inside the shared `save:` tail. This makes gcc emit a
                 * distinct `li $v0,1` per return site instead of cross-jumping/sinking one copy into
                 * the tail's branch delay slot (reorg.c fill_simple_delay_slots). Cookbook §10/B. */
                result = 1;
                newState = 3;
                goto save;
    have_low:
    case 3:
                nh = *src++;
                count--;
                /* LOAD-BEARING #1 (residual A), cont.: operand order `(code & 0xFF) | (nh << 8)`,
                 * NOT `(nh<<8)|(code&0xFF)`. gcc local-alloc.c combine_regs ties a commutative OR's
                 * result to the FIRST RTL operand that dies; writing `code & 0xFF` first ties the
                 * result to $v0 (the target reg) → `or $v0,$v0,$v1`. Cookbook §10/A. */
                code = (code & 0xFF) | (nh << 8);
                readIdx = code & 0x3FF;
                if (readIdx == 0) {
                    lzss_state = 0;
                term_ret:
                    return 0;
                }
                len = (code >> 10) + 2;
                while (len != 0) {
                    cb = ring[readIdx];
                    readIdx = (readIdx + 1) & 0x3FF;
                    ring[ringIdx] = cb;
                    ringIdx = (ringIdx + 1) & 0x3FF;
                    *out++ = cb;
                    len--;
                }
            }
            if (count != 0) {
                goto next_bit;
            }
            result = 1;     /* state-4 save predecessor — see LOAD-BEARING #3 */
            newState = 4;
        save:
            lzss_state = newState;
            lzss_ringIndex = ringIdx;
            lzss_curMask = mask;
            lzss_curToken = token;
            lzss_outPtr = out;
            lzss_partialCode = code;
            return result;
    next_bit:
    case 4:
            if (mask == 0x80) {
                mask = 1;
                token = *src++;
                count--;
                if (count == 0) {
                    /* state-2 reload save. The original keeps this as a SEPARATE copy of the 6
                     * stores (not shared with `save:`). Two more load-bearing constructs: */
                    register s32 r __asm__("$2");
                    /* LOAD-BEARING #4 (residual B, state-2): an explicit $v0 local pinned early by a
                     * read-only input-asm. This forces `li $v0,1` to materialise BEFORE the stores
                     * (the target schedules the return value first; gcc otherwise, since `li $v0,1`'s
                     * only use is the shared epilogue, defers it to just before `jr ra`). Cookbook §10/B. */
                    r = 1;
                    __asm__ __volatile__("" : : "r"(r));
                    newState = 2;
                    lzss_state = newState;
                    lzss_ringIndex = ringIdx;
                    lzss_curMask = mask;
                    lzss_curToken = token;
                    lzss_outPtr = out;
                    lzss_partialCode = code;
                    /* LOAD-BEARING #5 (the cross-jump barrier): a zero-byte volatile asm. gcc 2.7.2
                     * -O2 jump.c find_cross_jump would otherwise MERGE this save with the identical
                     * `save:` tail (→111 insns); an ASM_INPUT node makes it bail (lose=1) so both
                     * survive (→122, the correct count). No -fno-crossjumping before gcc 3.3. Cookbook §5a. */
                    __asm__ __volatile__("" ::: "memory");
                    return r;
                }
            } else {
                mask <<= 1;
            }
        }
    }
}

extern u8 D_80078D98;
extern u32 D_800AE610;
extern u8 D_80078DA0;
extern void ResetCallback(void);
extern void func_8005F0C8(void *a0, void *a1);
extern void func_8005D0F8(void);

void func_80018918(void) {
    u8 *p;
    u32 i;
    u32 w;

    i = 0;
    w = 8;
    p = &D_80078D98;
    D_800AE610 = 0;
    do {
        func_80016714(p, 0x4C);
        *(u32 *)(p + 4) = w;
        i++;
        p += 0x4C;
    } while (i < 2);
    func_80018FC8();
    ResetCallback();
    func_8005F0C8(&D_80078DA0, &D_80078DA0 + 0x4C);
    func_8005D0F8();
}

extern s32 func_80018A20(s32 arg0);
extern void func_80018C64(void *a0);
extern void func_80018CE8(u8 *p);
extern void func_80018E9C(s32 a0);
extern u8 D_80078D98;
extern s32 D_800A5E78;

void func_800189A8(void) {
    u32 i;
    u8 *p;

    D_800A5E78 = 1;
    i = 0;
    p = &D_80078D98;
    do {
        if (func_80018A20((s32)i) != 0) {
            func_80018C64(p);
        }
        func_80018CE8(p);
        func_80018E9C((s32)p);
        i++;
        p += 0x4C;
    } while (i < 2);
}


extern u8 D_80078D98;
extern u32 D_800AE610;
extern s32 D_800A5E78;
extern u8 D_80062BAC;
extern u8 D_80062BB4;
extern u8 D_80062BBC;
extern u8 D_80062BBD;
extern u8 D_800747B8;
extern u8 D_800747B9;

extern s32 func_8005D184(s32);
extern s32 func_8005D244(s32, s32, s32);
extern void func_8005D4B8(s32, void*);
extern void func_8005D538(s32, void*, s32);
extern s32 func_80028D58(void);
extern void func_80018F88(void*);
extern void func_80018FC8(void);

s32 func_80018A20(s32 arg0) {
    u8* p;
    s32 chan;

    p = (u8*)((u32)&D_80078D98 + arg0 * 76);

    switch (arg0) {
    case 0:
        chan = 0;
        break;
    case 1:
        chan = 16;
        break;
    }

    switch (func_8005D184(chan)) {
    case 0:
        if (arg0 == 0) {
            if (D_800AE610++ >= 10) {
                D_800AE610 = 0;
                D_800A5E78 = 0;
            }
        }
        /* fallthrough */
    case 1:
        func_80018F88(p);
        return 0;

    case 2:
        if (arg0 != 0) {
            return 1;
        }
        D_800AE610 = 0;
        if (func_8005D244(chan, 2, 0) != 0) {
            return 1;
        }
        if (func_80028D58() == 0) {
            if (p[0x4A] | p[0x4B]) {
                D_80062BBD = 1;
            } else {
                D_80062BBD = 0;
            }
            p[0x4B] = 0;
            p[0x4A] = 0;
        } else {
            func_80018FC8();
        }
        func_8005D538(chan, &D_80062BBC, 2);
        func_8005D4B8(chan, &D_80062BAC);
        return 1;

    case 6:
        if (arg0 != 0) {
            return 1;
        }
        D_800AE610 = 0;
        if (func_8005D244(chan, 2, 0) == 0) {
            return 1;
        }
        if (func_80028D58() == 0) {
            D_800747B8 = p[0x4A];
            D_800747B9 = p[0x4B];
            p[0x4B] = 0;
            p[0x4A] = 0;
        } else {
            func_80018FC8();
        }
        func_8005D538(chan, &D_800747B8, 2);
        func_8005D4B8(chan, &D_80062BB4);
        return 1;
    }
}

void func_80018C64(void *a0)
{
    s32 i;
    u8 *q;
    u8 *p = (u8 *)a0;

    if (p[8] != 0) {
        func_80018F88(a0);
        return;
    }
    p[0] = p[9];
    i = 0;
    q = &p[0x2B];
    while (i < 2) {
        *q = ~*(p + i + 10);
        i++;
        q--;
    }
    i = 2;
    while (i < 6) {
        *(p + i + 0x2A) = *(p + i + 10);
        i++;
    }
}


extern void func_80016714(void *a0, s32 a1);
extern void func_80018F20(s32 param_1);
extern u8 D_80078DE4;

void func_80018CE8(u8 *p) {
    s32 i;

    if (p == &D_80078DE4) {
        func_80016714(p, 0x4C);
        return;
    }
    switch (*p) {
    case 'A':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        return;
    case 'S':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        for (; i < 8; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x32] = (p + i)[0x2A];
        }
        func_80018F20((s32) p);
        return;
    case 's':
        for (i = 0; i < 2; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x3A] = (p + i)[0x2A] & ((p + i)[0x2A] ^ (p + i)[0x32]);
            (p + i)[0x32] = (p + i)[0x2A];
        }
        for (; i < 8; i++) {
            (p + i)[0x42] = (p + i)[0x32];
            (p + i)[0x32] = (p + i)[0x2A];
        }
        func_80018F20((s32) p);
        return;
    }
    func_80016714(p, 0x4C);
}

void func_80018E78(void) {
    extern void func_800291A0(s32, s32);
    func_800291A0(0xE2, 0);
}

extern u8 D_80078D98;
extern u8 D_80078DCA;
extern s32 func_800291B4(s32);
extern void func_800291A0(s32, s32);
extern void func_80028D78(s32);

void func_80018E9C(s32 a0)
{
    s32 s0;

    if (a0 == (s32)&D_80078D98) {
        if (*(u16 *)&D_80078DCA & 0x100) {
            s0 = func_800291B4(0xE2) + 1;
            if ((u32)(s0 & 0xFF) >= 0x5A) {
                s0 = 0;
                func_80028D78(1);
            }
            func_800291A0(0xE2, s0 & 0xFF);
        } else {
            func_800291A0(0xE2, 0);
        }
    }
}

void func_80018F20(s32 param_1) {
    u32 uVar3;
    s32 iVar2;
    u32 uVar1;

    uVar3 = 2;
    do {
        iVar2 = param_1 + uVar3;
        uVar1 = *(u8 *)(iVar2 + 0x32);
        if (uVar1 - 0x51 < 0x5f) {
            *(u8 *)(iVar2 + 0x32) = 0x80;
        } else if ((uVar1 & 0xff) < 8) {
            *(u8 *)(iVar2 + 0x32) = 0;
        } else if ((uVar1 & 0xff) >= 0xf8) {
            *(u8 *)(iVar2 + 0x32) = 0xff;
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 < 8);
}

void func_80018F88(void* arg0) {
    int i;
    unsigned char* p;

    i = 1;
    p = (unsigned char*)arg0 + 1;
    do {
        p[0x2A] = 0;
        i--;
        p--;
    } while (i >= 0);

    for (i = 2; i < 6; i++) {
        ((unsigned char*)arg0 + i)[0x2A] = 0x80;
    }
}

extern u8 D_80078D98;
extern u8 D_80062BBC;
extern u8 D_80062BBD;
extern u8 D_800747B8;
extern u8 D_800747B9;

void func_80018FC8(void) {
    u8 *p;
    s32 i;

    D_800747B9 = 0;
    D_800747B8 = 0;
    D_80062BBC = 0x40;
    D_80062BBD = 0;

    for (i = 0; i < 2; i++) {
        p = (u8 *)&D_80078D98 + i * 0x4C;
        p[0x4B] = 0;
        p[0x4A] = 0;
    }
}

extern s32 D_800747C8;
void func_80019018(void) {
    D_800747C8 = 0;
}

extern s32 D_800747C8;
void func_80019028(void) {
    D_800747C8 = 1;
}


extern void func_80016714(void *a0, s32 a1);
extern s32 D_800747C0;

void func_8001903C(void) {
    func_80016714(&D_800747C0, 8);
}

extern s32 D_800747C8;
extern u8 D_800B9A64;
extern s32 D_800747C0;
extern u8 D_800747C4;
extern u8 D_800747C5;

void func_80019064(void *a0)
{
    if (D_800747C8 != 0) return;
    if (D_800B9A64 != 0) return;
    D_800747C0 = a0;
    D_800747C4 = 0xFF;
    D_800747C5 = 0;
}


extern s32 D_800747C0;
extern u8 D_800747C4;
extern u8 D_800747C5;
extern u8 D_80078DE2;
extern u8 D_80078DE3;

void func_800190AC(void) {
    s32 *p = &D_800747C0;
    u8 last;

    if (*p == 0) {
        return;
    }

    last = D_800747C5;
    if (last == 0) {
        u8 *q;
        s32 idx;

        idx = D_800747C4 + 1;
        D_800747C4 = idx;
        idx = idx & 0xff;
        q = (u8 *)((idx * 3) + D_800747C0);
        D_80078DE2 = q[1];
        D_80078DE3 = q[0];
        D_800747C5 = q[2];
        if (D_800747C5 == 0) {
            D_80078DE2 = 0;
            D_80078DE3 = 0;
            D_800747C4 = 0xFF;
            *p = 0;
        }
    } else {
        u8 *r;
        u8 t;

        r = (u8 *)((D_800747C4 * 3) + D_800747C0);
        D_80078DE2 = r[1];
        t = r[0];
        D_800747C5 = last - 1;
        D_80078DE3 = t;
    }
}

extern s32 D_800747C0;
s32 func_80019198(void) {
    return D_800747C0;
}

extern s32 D_80078E30;

void func_800191A8(void) {
    D_80078E30 = -1;
}

extern s32 D_80078E30;

void func_800191BC(s16 arg0) {
    D_80078E30 = arg0;
}

s32 func_800191D4(s32 a0) {
    extern s32 D_80078E30;
    extern s32 func_8001923C();
    s32 *p = &D_80078E30;

    if (*p < 0) {
        return 1;
    }
    if (func_8001923C(a0) == 0) {
        return *p != a0;
    }
    return 1;
}


s32 func_8001923C(s32 a0)
{
    if (a0 == 0xB3) return 0;
    if (a0 == 0xB4) return 0;
    if (a0 == 0x12E) return 0;
    if (a0 == 0x12F) return 0;
    if (a0 == 0x150) return 0;
    if (a0 == 0x152) return 0;
    if (a0 == 0x16E) return 0;
    if (a0 == 0x16F) return 0;
    if (a0 == 0xB9) return 0;
    if (a0 == 0xA1) return 0;
    if (a0 == 0xA2) return 0;
    if (a0 == 0xA3) return 0;
    if (a0 == 0x10B) return 0;
    if (a0 == 0x10C) return 0;
    if (a0 == 0x10D) return 0;
    if (a0 == 0x10F) return 0;
    if (a0 == 0x110) return 0;
    if (a0 == 0x111) return 0;
    if (a0 == 0x112) return 0;
    if (a0 == 0x113) return 0;
    if (a0 == 0x114) return 0;
    if (a0 == 0xAA) return 0;
    if (a0 == 0x115) return 0;
    if (a0 == 0x116) return 0;
    if (a0 != 0x117) return a0 != 0x118;
    return 0;
}

extern s32 D_800BA1B4;
extern s32 D_800747E4;
extern s32 D_800747E8;
extern void func_8002D4C8(s32 a0, s32 a1);

/* stream-state reset: clears loader phase 5 */
void func_8001931C(void) {
    if (D_800BA1B4 == 5) {
        if (D_800747E4 != 0) {
            func_8002D4C8(0x16, 0);
        }
        D_800BA1B4 = 0;
        D_800747E8 = 0;
        D_800747E4 = 0;
    }
}

extern s32 debugBinPresent;
s32 func_80019378(void) {
    return debugBinPresent;
}

extern s32 debugBinPresent;
void func_80019388(s32 arg0) {
    debugBinPresent = arg0;
}

extern s32 D_800747D4;
s32 func_80019398(void) {
    return D_800747D4;
}

extern s32 D_800747D4;
void func_800193A8(s32 arg0) {
    D_800747D4 = arg0;
}


extern void LoaderResetReadState(void);
extern int VSync(int mode);
extern s32 CdReadRequest(int *cdlFile, void *dest, s32 size, s32 mode);

extern u8 D_80062C38;       /* CdPathTable[0].file; entries stride 0x30 */
extern u8 D_80062C68;       /* CdPathTable[1].file.pos (CdlLOC), stride 0x30 */
extern u8 D_80062DE8;       /* CdPathTable[9].file; second entry at +0x210 */
extern s32 debugBinPresent;
extern s32 D_80063074;
extern s32 D_800747D8;
extern u8 cdFileLocTable[]; /* {CdlLOC pos; u32 size} per sub-file, 8B stride */
extern u8 D_800AE834;       /* cdFileLocTable + 4 (the size field) */

/* LIST.CD staging buffer @0x80180000 (== listCdBuffer). The original source used the
 * raw address, not the symbol: every reference is a bare `lui reg,0x8018` (one insn),
 * which is what a literal produces (`&listCdBuffer` would emit lui+addiu). */
#define LIST_BUF 0x80180000

void func_800193B8(s32 arg0) {
    CdlLOC loc;
    u8 hdr[0x90];
    register s32 sector __asm__("$18");
    s32 rdy;
    register s32 tmp __asm__("$3");
    register u8 *q __asm__("$16");
    register u8 *r __asm__("$17");
    register int i __asm__("$23");
    int base;
    int n;
    int fileIdx;
    int bufIdx;
    register int j __asm__("$19");
    register int outer __asm__("$23");
    int locOff;
    u8 *tbl;
    u8 *lbv;
    int dstOff;
    int srcOff;
    s32 *pCount;
    s32 *pOff;
    CdlLOC *p;
    register CdlLOC *pp __asm__("$5");

    LoaderResetReadState();
    sector = arg0 + 1;
    debugBinPresent = 0;
    D_80063074 = 0;
    D_800747D8 = 0;
    CdIntToPos(sector, &loc);
    do {
        rdy = CdReadRequest((int *)&loc, (void *)LIST_BUF, 0x800, 0);
        if (rdy != 0) {
            break;
        }
        VSync(0);
    } while (1);

    memcpy(hdr, (void *)LIST_BUF, 0x88);
    tmp = sector + 1;
    sector = tmp + ((*(u32 *)(hdr + 0x1C) + 0x7FF) >> 11);
    CdIntToPos(sector, &loc);
    do {
        rdy = CdReadRequest((int *)&loc, (void *)LIST_BUF, 0x800, 0);
        if (rdy != 0) {
            break;
        }
        VSync(0);
    } while (1);
    i = 2;

    sector += 1;
    q = &D_80062C38;
    pp = (CdlLOC *)q;
    /* sched fence: forces the `a1 = q` copy to be scheduled before the loop-pointer
     * init; without it gcc's list scheduler emits `addiu s1,s0,0x60` first. */
    __asm__ ("" : "=r"(q) : "0"(q));
    r = q + 0x60;
    CdIntToPos(sector + *(s32 *)(LIST_BUF + 0x00), pp);
    CdIntToPos(sector + *(s32 *)(LIST_BUF + 0x08), (CdlLOC *)(q + 0x30));
    do {
        pp = (CdlLOC *)r;
        r += 0x30;
        i++;
        CdIntToPos(sector + *(s32 *)(LIST_BUF + 0x10), pp);
    } while (i < 9);

    q = &D_80062DE8;
    CdIntToPos(sector + *(s32 *)(LIST_BUF + 0x18), (CdlLOC *)q);
    CdIntToPos(sector + *(s32 *)(LIST_BUF + 0x20), (CdlLOC *)(q + 0x210));

    do {
        rdy = CdReadRequest((int *)&D_80062C38, (void *)LIST_BUF, 0xE40, 0);
        if (rdy != 0) {
            break;
        }
        VSync(0);
    } while (1);

    tbl = cdFileLocTable;
    lbv = (u8 *)LIST_BUF;
    fileIdx = 0;
    bufIdx = 0;
    outer = 0;
    locOff = 0;
    pCount = (s32 *)LIST_BUF;
    do {
        base = CdPosToInt((CdlLOC *)(&D_80062C68 + locOff));
        n = *pCount;
        pCount += 2;
        bufIdx++;
        j = 0;
        if (n > 0) {
            p = (CdlLOC *)((u32)(fileIdx * 8) + (u32)tbl);
            dstOff = fileIdx * 8;
            pOff = (s32 *)((u32)(bufIdx * 8) + (u32)lbv);
            srcOff = bufIdx * 8;
            do {
                if (*pOff != 0) {
                    CdIntToPos(*pOff + base, p);
                    *(s32 *)(&D_800AE834 + dstOff) = *(s32 *)(0x80180004 + srcOff);
                }
                pOff += 2;
                srcOff += 8;
                pCount += 2;
                bufIdx++;
                p += 2;
                dstOff += 8;
                j++;
                fileIdx++;
            } while (j < n);
        }
        outer++;
        locOff += 0x30;
    } while (outer < 8);
}

#ifdef NON_MATCHING
extern void LoaderResetReadState(void);
extern int VSync(int mode);
extern CdlFILE D_80063058;
extern char cdpath_DEBUG_BIN[];
extern u8 D_80062C38;     /* path table entry[0].file (CdlFILE), entries stride 0x30; names at -0x14 */
extern u8 D_80062C68;     /* path entry[1].file.pos (CdlLOC), the 8 .CD files, stride 0x30 */
extern s32 debugBinPresent;
extern s32 D_800747D4;
extern s32 D_80063074;
extern s32 D_800747D8;
extern u8 cdFileLocTable[]; /* out: {CdlLOC pos; u32 size} per sub-file, 8B stride */
extern u8 D_800AE834;       /* cdFileLocTable + 4 (the size field) */
extern s32 listCdBuffer;    /* LIST.CD content: 8B records {value; size} */
extern u8 D_80180004;       /* listCdBuffer + 4 (the size field) */
/* file-loader directory resolver (boot @0x800101fc): probe \DEBUG.BIN;1, resolve the 21
 * CdPathTable entries via CdSearchFile, read LIST.CD (0xE40 B) into listCdBuffer, then build
 * cdFileLocTable (CdlLOC+size per sub-file) over the 8 .CD files. Phase 3 T2.
 * NON_MATCHING: logically faithful, structurally close (138 vs 133 ins) but not byte-exact.
 * Residual is register allocation / loop-invariant hoisting — the target keeps &D_80063058,
 * &D_80062C38, &D_80062C68 in callee-saved regs and derives the name arg as (base - 0x14)
 * rather than a separate symbol; a multi-iteration / decomp-permuter target for a later pass. */
void LoaderInitFileTable(void) {
    CdlFILE *res;
    int tries;
    int pathOff;
    int pathN;
    int base;
    int n;
    int fileIdx;
    int bufIdx;
    int j;
    int outer;
    int locOff;
    int dstOff;
    int srcOff;
    int *pCount;
    int *pOff;
    CdlLOC *p;

    LoaderResetReadState();
    tries = 0;
    do {
        res = CdSearchFile(&D_80063058, cdpath_DEBUG_BIN);
        tries++;
        if (res != (CdlFILE *)-1) {
            break;
        }
    } while (tries < 0x10);
    pathN = 0;
    pathOff = 0;
    debugBinPresent = (res != (CdlFILE *)0);
    D_800747D4 = 1;
    D_80063074 = 0;
    D_800747D8 = 0;
    do {
        do {
            res = CdSearchFile((CdlFILE *)(&D_80062C38 + pathOff), (char *)(&D_80062C38 - 0x14 + pathOff));
        } while ((u32)((int)res + 1) < 2);
        pathN++;
        pathOff += 0x30;
    } while (pathN < 0x15);
    do {
        fileIdx = 0;
        n = CdReadRequest(&D_80062C38, &listCdBuffer, 0xE40, 0);
        if (n != 0) {
            break;
        }
        VSync(0);
    } while (1);
    bufIdx = 0;
    outer = 0;
    locOff = 0;
    pCount = &listCdBuffer;
    do {
        base = CdPosToInt((CdlLOC *)(&D_80062C68 + locOff));
        n = *pCount;
        pCount += 2;
        bufIdx++;
        j = 0;
        if (n > 0) {
            dstOff = fileIdx * 8;
            p = (CdlLOC *)(cdFileLocTable + dstOff);
            srcOff = bufIdx * 8;
            pOff = &listCdBuffer + bufIdx * 2;
            do {
                if (*pOff != 0) {
                    CdIntToPos(*pOff + base, p);
                    *(s32 *)(&D_800AE834 + dstOff) = *(s32 *)(&D_80180004 + srcOff);
                }
                pOff += 2;
                srcOff += 8;
                pCount += 2;
                bufIdx++;
                p += 2;
                dstOff += 8;
                j++;
                fileIdx++;
            } while (j < n);
        }
        outer++;
        locOff += 0x30;
    } while (outer < 8);
}
#else

extern void LoaderResetReadState(void);
extern int VSync(int mode);
extern s32 CdReadRequest(int *cdlFile, void *dest, s32 size, s32 mode);

extern CdlFILE D_80063058;  /* CdPathTable[22].file (\DEBUG.BIN;1); its name is at -0x14 */
extern u8 D_80062C38;       /* CdPathTable[0].file; entries stride 0x30, names at -0x14      */
extern u8 D_80062C68;       /* CdPathTable[1].file.pos (CdlLOC) — the 8 .CD files, stride 0x30 */
extern s32 debugBinPresent;
extern s32 D_800747D4;
extern s32 D_80063074;
extern s32 D_800747D8;
extern u8 cdFileLocTable[]; /* out: {CdlLOC pos; u32 size} per sub-file, 8B stride */
extern u8 D_800AE834;       /* cdFileLocTable + 4 (the size field)                */

/* LIST.CD staging buffer @0x80180000 (== listCdBuffer), 0xE40 bytes of 8B records
 * {startOffset; size}.  The original source used the raw address, not the symbol:
 * every reference in the target is a bare `lui reg,0x8018` (one instruction), which is
 * what a literal produces — `&listCdBuffer` would emit lui+addiu.  */
#define LIST_BUF 0x80180000

/* File-loader directory resolver (0x8001971C).
 *   1. probe \DEBUG.BIN;1 (up to 16 tries) -> debugBinPresent
 *   2. resolve the 21 CdPathTable entries via CdSearchFile (retry while res is -1 or 0)
 *   3. read LIST.CD (0xE40 B) into the staging buffer, VSync-spinning until accepted
 *   4. walk the 8 .CD containers: for each, CdPosToInt the container start, then convert
 *      every non-zero sub-file offset into cdFileLocTable[k].pos / .size.
 *
 * Register pins (cookbook §17): this function's live set is exactly 9 callee-saved values
 * plus two caller-saved ones, so gcc's allocno priority order is one place off by default —
 * `n` wins a callee-saved reg and `outer` spills.  The pins restore the target's split
 * (outer/tries/pathN share $s5, `n` -> $v1 with caller-save, base -> $a2).
 * `dead[4]` is load-bearing: the target frame is 0x58 and its locals start at 0x20, i.e.
 * 16 bytes below the first live slot.  `tbl`/`lbv` are set once from constants so
 * update_equiv_regs marks them rematerializable — reload then re-emits each address into
 * the spill register $t0 (the same $t0 the locOff reloads use), which is what the target does.
 */
void LoaderInitFileTable(void) {
    CdlFILE *res;
    register int tries __asm__("$21");
    register u8 *pathBase __asm__("$18");
    register char *nameBase __asm__("$19");
    register int pathOff __asm__("$17");
    int offCopy;
    int dead[4];
    register u32 pathN __asm__("$21");
    int base;
    int n;
    int rdy;
    int fileIdx;
    int bufIdx;
    register int j __asm__("$19");
    register int outer __asm__("$21");
    int locOff;
    u8 *tbl;
    u8 *lbv;
    int dstOff;
    int srcOff;
    s32 *pCount;
    s32 *pOff;
    CdlLOC *p;

    LoaderResetReadState();
    tries = 0;
    do {
        res = CdSearchFile(&D_80063058, (char *)&D_80063058 - 0x14);
        tries++;
        if (res != (CdlFILE *)-1) {
            break;
        }
    } while (tries < 0x10);

    pathN = 0;
    pathBase = &D_80062C38;
    nameBase = (char *)pathBase - 0x14;
    pathOff = 0;
    debugBinPresent = (res != (CdlFILE *)0);
    D_800747D4 = 1;
    D_80063074 = 0;
    D_800747D8 = 0;
    do {
        offCopy = pathOff;
        do {
            res = CdSearchFile((CdlFILE *)(&D_80062C38 + offCopy), nameBase + offCopy);
        } while ((u32)((int)res + 1) < 2);
        pathN++;
        pathOff += 0x30;
    } while (pathN < 0x15);

    do {
        rdy = CdReadRequest((int *)&D_80062C38, (void *)LIST_BUF, 0xE40, 0);
        if (rdy != 0) {
            break;
        }
        VSync(0);
    } while (1);

    tbl = cdFileLocTable;
    lbv = (u8 *)LIST_BUF;
    fileIdx = 0;
    bufIdx = 0;
    outer = 0;
    locOff = 0;
    pCount = (s32 *)LIST_BUF;
    do {
        base = CdPosToInt((CdlLOC *)(&D_80062C68 + locOff));
        n = *pCount;
        pCount += 2;
        bufIdx++;
        j = 0;
        if (n > 0) {
            p = (CdlLOC *)((u32)(fileIdx * 8) + (u32)tbl);
            dstOff = fileIdx * 8;
            pOff = (s32 *)((u32)(bufIdx * 8) + (u32)lbv);
            srcOff = bufIdx * 8;
            do {
                if (*pOff != 0) {
                    CdIntToPos(*pOff + base, p);
                    *(s32 *)(&D_800AE834 + dstOff) = *(s32 *)(0x80180004 + srcOff);
                }
                pOff += 2;
                srcOff += 8;
                pCount += 2;
                bufIdx++;
                p += 2;
                dstOff += 8;
                j++;
                fileIdx++;
            } while (j < n);
        }
        outer++;
        locOff += 0x30;
    } while (outer < 8);
}
#endif

extern s32 cdReq_sink;
extern s32 cdReq_state;
extern s32 D_800AE6F8;
extern s32 D_800AE6FC;
extern s32 D_800AE700;
extern s32 cdReq_wordsRemaining;
extern s32 cdReq_drainPhase;
extern u8 D_800AE798;
extern u8 D_800AE799;
extern s32 D_800AE70C;

void func_80019930(void) {
    cdReq_sink = 0x80010000;
    cdReq_state = 0;
    D_800AE6F8 = 0;
    D_800AE6FC = 0;
    D_800AE700 = 0;
    cdReq_wordsRemaining = 1;
    cdReq_drainPhase = 0;
    D_800AE798 = 0;
    D_800AE799 = 0;
    D_800AE70C = 0;
}

extern s32 cdReq_sink;
extern s32 cdReq_curSector;
extern s32 D_800BA1B4;
extern s32 D_800747F0;
extern s32 D_800747F4;
extern s32 cdReq_state;
extern s32 D_800AE6F8;
extern s32 D_800AE6FC;
extern s32 D_800AE700;
extern s32 cdReq_wordsRemaining;
extern s32 cdReq_drainPhase;
extern u8 D_800AE798;
extern u8 D_800AE799;
extern s32 D_800AE70C;
void LoaderResetReadState(void) {
    cdReq_sink = 0x80010000;
    cdReq_curSector = 0;
    D_800BA1B4 = 0;
    D_800747F0 = 0;
    D_800747F4 = 0;
    cdReq_state = 0;
    D_800AE6F8 = 0;
    D_800AE6FC = 0;
    D_800AE700 = 0;
    cdReq_wordsRemaining = 1;
    cdReq_drainPhase = 0;
    D_800AE798 = 0;
    D_800AE799 = 0;
    D_800AE70C = 0;
}

void func_80019A10(void) {
    extern s32 D_80078E30;
    D_80078E30 = -1;
}

extern s32 CdQueueBusy(void);
extern void CdReadStateMachine(int);
extern s32 cdReq_curSector;
extern void *cdReq_dest;
extern s32 cdReq_size;
extern void *cdReq_cdlFile;
extern s32 cdReq_result;
extern s32 D_800AE720;
extern s32 D_800AE724;
/* Read-request dispatcher (Phase 3 T2). Refuse while CdQueueBusy(); dedup on the request's
 * start sector (*cdlFile) vs the in-flight cdReq_curSector; stash dest/size/cdlFile/mode into
 * the control block, set the "first read" flag D_800AE720 = (mode == 0), drive the state
 * machine, return cdReq_result. */
s32 CdReadRequest(int *cdlFile, void *dest, s32 size, s32 mode) {
    s32 sector;
    if (CdQueueBusy() != 0) {
        return 0;
    }
    if (cdReq_curSector == 0) {
        sector = *cdlFile;
    } else {
        sector = *cdlFile;
        if (sector != cdReq_curSector) {
            return 0;
        }
    }
    cdReq_dest = dest;
    cdReq_size = size;
    cdReq_cdlFile = cdlFile;
    D_800AE724 = mode;
    D_800AE720 = 0;
    cdReq_curSector = sector;
    if (mode == 0) {
        D_800AE720 = 1;
    }
    CdReadStateMachine(0);
    return cdReq_result;
}

#ifdef NON_MATCHING
/* libcd low-level command API (the loader uses raw CdControl, NOT the PsyQ CdRead() wrapper;
 * not in psyq/libcd.h yet). */
extern int   CdControl(u8 com, u8 *param, u8 *result);
extern int   CdSync(int mode, u8 *result);
extern void  CdFlush(void);
extern void *CdReadyCallback(void *func);
extern void  CdReadSectorReadyCB(char);        /* the CdlReadN data-ready callback @0x8001A338 */
extern void  start(void);                       /* EXE entry — used as the idle "sink" sentinel */
extern int   func_8002FD14(int buf, int len);   /* per-sector consumer (drains the queued list) */
extern void  func_8001A0FC(void);
extern int   func_8001A114(void);

/* cdReq_* async-read control block (Phase 3 T2); the D_800AE* are its unnamed members. */
extern int     cdReq_state;
extern int     cdReq_retry;
extern int     cdReq_result;        /* return-by-global: 0 = still busy, 1 = done */
extern u8      cdReq_cdResult;      /* CdControl status byte (bit 0x10 = error) */
extern void   *cdReq_cdlFile;       /* seek target (a CdlLOC*) */
extern int     cdReq_posInt;
extern int     cdReq_timeout;
extern int     cdReq_size;          /* bytes to read */
extern void   *cdReq_dest;          /* read destination */
extern s32     cdReq_sink;          /* sector sink address (dest while reading, &start idle) */
extern int     cdReq_wordsRemaining;
extern int     cdReq_drainPhase;    /* 0 = reading, 1 = drained, 2 = finished */
extern void   *cdReq_savedReadyCB;  /* prior CdReadyCallback, restored on stop */
extern int     cdReq_curSector;
extern u8      D_800AE740;          /* CdlSetmode mode-byte buffer (0xA0) */
extern int     D_800AE6E8;          /* CdSync result scratch */
extern int     D_800AE6F8;
extern s32     D_800AE70C;          /* last/idle CdlLOC (held as a word) */
extern int     D_800AE71C;          /* count of queued sectors to drain (state 7) */
extern int     D_800AE724;          /* base of the queued {ptr,len} sector list */
extern int     D_800AE6FC;
extern int     D_800AE700;
extern u8      D_800AE798;
extern u8      D_800AE799;

/* Hand-rolled polled async CD reader: one state step per call, switch(cdReq_state). Sequence
 *   SetMode(0xA0) -> SeekL(+CdPosToInt) -> ReadN(+CdReadSectorReadyCB sector drain) -> Pause/Flush.
 * Progress is returned via cdReq_result (0 busy / 1 done). The game does NOT use PsyQ CdRead()/
 * CdReadSync(). pauseAfterSeek != 0 stops after the seek (state 8) instead of reading.
 * Provenance: static trace, Phase 3 T2 (verified).
 * NON_MATCHING: logically faithful to the Ghidra decompile; not byte-exact — a large switch state
 * machine whose register allocation + jump-table placement are a later byte-match pass. */
void CdReadStateMachine(int pauseAfterSeek) {
    int n;
    int i;
    int off;

    switch (cdReq_state) {
    case 0:
        cdReq_retry = 0;
        D_800AE71C = 0;
        D_800AE70C = 0;
        D_800AE740 = 0xA0;
        CdControl(0x0E, &D_800AE740, &cdReq_cdResult);             /* CdlSetmode */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state++;
            goto state1;
        }
        break;
    case 1:
    state1:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 0) { cdReq_result = 0; return; }
        if (D_800AE6E8 == 5) { cdReq_state = 0; cdReq_result = 0; return; }
        if (D_800AE6E8 != 2) { cdReq_result = 0; return; }
        cdReq_retry = 0;
        cdReq_state++;
        D_800AE6E8 = 2;
    state2:
        if (cdReq_retry + 1 < 3) {
            cdReq_retry++;
            cdReq_result = 0;
            return;
        }
        cdReq_state++;
        cdReq_retry = 0;
        cdReq_result = 0;
        return;
    case 2:
        goto state2;
    case 3:
        CdControl(0x15, (u8 *)cdReq_cdlFile, &cdReq_cdResult);    /* CdlSeekL */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_timeout = 0;
            cdReq_posInt = CdPosToInt((CdlLOC *)cdReq_cdlFile);
            cdReq_state++;
            goto state4;
        }
        break;
    case 4:
    state4:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 5) {
            cdReq_retry++;
        flushRetry:
            CdFlush();
            cdReq_state = 3;
            cdReq_result = 0;
            return;
        }
        if (D_800AE6E8 == 0) { cdReq_result = 0; return; }
        if (D_800AE6E8 != 2) {
            cdReq_result = 0;
            cdReq_timeout++;
            if (cdReq_timeout < 0xB5) { cdReq_result = 0; return; }
            goto flushRetry;
        }
        if (pauseAfterSeek == 0) {
            cdReq_state++;
            goto state5;
        }
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state = 8;
            D_800AE70C = *(s32 *)cdReq_cdlFile;
            cdReq_result = 0;
            return;
        }
        break;
    case 5:
    state5:
        cdReq_drainPhase = 0;
        if (cdReq_size < 1) {
            D_800AE6F8 = 0;
        } else {
            int bytes = cdReq_size + 3;
            D_800AE6F8 = 3;
            if (bytes < 0) bytes = cdReq_size + 6;                /* round-up word count, neg-safe */
            cdReq_wordsRemaining = bytes >> 2;
            D_800AE798 = 1;
            cdReq_sink = (s32)cdReq_dest;
        }
        cdReq_savedReadyCB = CdReadyCallback(CdReadSectorReadyCB);
        CdControl(0x06, (u8 *)0, &cdReq_cdResult);                /* CdlReadN */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_retry = 0;
            cdReq_state++;
            goto state6;
        }
        break;
    case 6:
    state6:
        if (cdReq_drainPhase != 1) {
            if (cdReq_drainPhase == 2) {
                CdReadyCallback(cdReq_savedReadyCB);
                cdReq_state = 0;
                cdReq_result = 0;
                return;
            }
            cdReq_retry++;
            if (cdReq_retry > 299) {
                CdReadyCallback(cdReq_savedReadyCB);
                cdReq_state = 0;
                CdFlush();
                cdReq_result = 0;
                return;
            }
            cdReq_result = 0;
            return;
        }
        CdReadyCallback(cdReq_savedReadyCB);
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) {
            cdReq_state += (D_800AE71C == 0) ? 2 : 1;             /* -> 8 (no drain) or 7 (drain) */
            cdReq_result = 0;
            return;
        }
        break;
    case 7:
        n = 0;
        if (D_800AE71C > 0) {
            off = 0;
            do {
                do {
                    i = func_8002FD14(*(int *)(D_800AE724 + off),
                                      *(int *)(D_800AE724 + off + 4));
                } while (i == 0);
                n++;
                off = n * 8;
            } while (n < D_800AE71C);
        }
        cdReq_state++;
        cdReq_result = 0;
        return;
    case 8:
        D_800AE6E8 = CdSync(1, &cdReq_cdResult);
        if (D_800AE6E8 == 2) {
            cdReq_sink = (s32)start;
            cdReq_state = 0;
            D_800AE6F8 = 0;
            D_800AE6FC = 0;
            D_800AE700 = 0;
            cdReq_curSector = 0;
            D_800AE70C = 0;
            cdReq_wordsRemaining = 1;
            cdReq_drainPhase = 0;
            D_800AE798 = 0;
            D_800AE799 = 0;
            cdReq_result = 1;
            return;
        }
        if (D_800AE6E8 != 5) { cdReq_result = 0; return; }
        CdFlush();
        CdControl(0x09, (u8 *)0, &cdReq_cdResult);                /* CdlPause */
        if ((cdReq_cdResult & 0x10) == 0) { cdReq_result = 0; return; }
        break;
    case 9:
        func_8001A0FC();
        cdReq_state++;
        /* fall through to state 10 */
    case 10:
        D_800AE6E8 = func_8001A114();
        if (D_800AE6E8 != 0) {
            cdReq_state = 0;
            cdReq_result = 0;
            return;
        }
        cdReq_result = 0;
        return;
    default:
        goto setDefault;
    }
    cdReq_state = 9;
setDefault:
    cdReq_result = 0;
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", CdReadStateMachine);
#endif

extern s32 D_800AE6F4;
extern s32 D_800AE70C;
void func_8001A0FC(void) {
    D_800AE6F4 = 0;
    D_800AE70C = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001A114);

#ifdef NON_MATCHING
typedef struct { short x, y, w, h; } RECT;          /* libgpu RECT (VRAM rectangle) */
extern int   CdGetSector(void *madr, int nsector);
extern void  LoadImage(RECT *rect, u32 *data);      /* libgpu VRAM upload */
extern int   func_8002FC64(int nbytes, u32 *src);   /* stage/copy a payload run */
extern int   func_8002FB08(int entry);              /* kick off a queued list entry */
extern void  func_8002FDC8(void);                   /* finalize the queued transfer */
extern void  func_80018714(void);                   /* reset LZSS sector state */

/* shared cdReq_ control block (see CdReadStateMachine) + this callback's members */
extern int   cdReq_posInt;
extern int   cdReq_size;
extern int   cdReq_wordsRemaining;
extern int   cdReq_drainPhase;
extern void *cdReq_dest;
extern s32   cdReq_sink;
extern u32   lzss_sectorStagingBuf[];  /* 0x80079A70 — PAC header lands here ([0] = 'PAC' magic) */
extern u8    cdReq_sectorHdrBuf[];     /* sub-header scratch (3 words -> CdPosToInt) */
extern u8    D_80079A74;               /* PAC type */
extern u8    D_80079A75;               /* PAC flags -> D_800AE798 */
extern int   D_80079A78;               /* PAC sub-count (textures) */
extern int   D_80079A7C;               /* PAC payload size (bytes) */
extern int   D_800AE6F8;               /* load phase (PAC-type dispatcher state) */
extern u8    D_800AE798;               /* saved PAC flags (nonzero = more sectors follow) */
extern int   D_800AE704;               /* texture sector index (0..3, round-robin) */
extern short D_800AE710, D_800AE712;   /* VRAM dst x,y of the current tile (a RECT @0xAE710) */
extern short D_800AE714, D_800AE716;   /* tile w,h (0x20 x 0x20) */
extern u8    D_800AE758[];             /* 64-byte present bitmask (which tiles are sent) */
extern u8    D_800AE79A, D_800AE79B;   /* bit / byte cursor into the bitmask */
extern RECT *D_800AE718;               /* current texture-rect pointer (PAC type 6) */
extern int   D_800AE71C;               /* queued-entry count */
extern int   D_800AE720;               /* "transfer already in progress" guard */
extern int   D_800AE724;               /* base of the queued {ptr,len} list */
extern void *D_80072C80;               /* a fixed destination pointer (PAC type 7) */
extern u32   D_8007A280[];             /* texture RECT array (read from CD) */
extern u32   D_8007A310[];             /* texture pixel data (read from CD) */

/* CdReadyCallback for CdReadStateMachine (registered in its state 5). Per CD data-ready interrupt,
 * drain one sector and dispatch on the load phase D_800AE6F8: parse the PAC header, then per PAC
 * type either upload tiles to VRAM (LoadImage), copy raw sectors to cdReq_sink, or decompress via
 * LzssDecodeSector (this is its ONLY caller). reason: 1 = data-ready, 5 = end/error.
 * Provenance: static trace, Phase 3 T2/T4 (verified).
 * NON_MATCHING: faithful translation of the Ghidra decompile — logically faithful, not byte-verified
 * (large interrupt callback; register allocation + jump-table placement are a later byte-match pass). */
void CdReadSectorReadyCB(char reason) {
    void *dst;
    int pos;
    int i, n;

    if (reason != 1) goto endReason;
    CdGetSector(cdReq_sectorHdrBuf, 3);
    pos = CdPosToInt((CdlLOC *)cdReq_sectorHdrBuf);
    if (pos != cdReq_posInt) {                  /* sector out of order -> abort the drain */
        if (D_800AE6F8 == 4) func_8002FDC8();
        cdReq_drainPhase = 2;
        return;
    }
    cdReq_posInt = pos + 1;
    switch (D_800AE6F8) {
    case 0:                                      /* expect a PAC header */
        CdGetSector(lzss_sectorStagingBuf, 4);
        if (lzss_sectorStagingBuf[0] != 0x434150) goto abortDrain;   /* "PAC" magic? */
        D_800AE798 = D_80079A75;
        switch (D_80079A74) {                    /* PAC type */
        case 0:
        case 5:                                  /* tiled texture: scan the present-bitmask */
            D_800AE704 = 0;
            CdGetSector(D_800AE758, 0x10);
            D_800AE716 = 0x20; D_800AE714 = 0x20;
            D_800AE712 = 0; D_800AE710 = 0;
            D_800AE79A = 1; D_800AE79B = 0;
            while (D_800AE79B < 0x40) {
                if ((D_800AE79A & D_800AE758[D_800AE79B]) != 0) goto tilePhase;
                if (D_800AE79A == 0x80) { D_800AE79A = 1; D_800AE79B++; }
                else                     D_800AE79A <<= 1;
                D_800AE710 += 0x20;
                if (D_800AE710 > 0x3FF) { D_800AE710 = 0; D_800AE712 += 0x20; }
            }
            D_800AE6F8 = (D_800AE798 == 0) ? 0 : 2;
        tilePhase:
            D_800AE6F8++;
            break;
        case 1:
            dst = cdReq_dest;
            goto setSink;
        case 2:
            if (D_800AE720 != 0) goto phaseDone;
            dst = *(void **)(D_800AE71C * 8 + D_800AE724 + 4);
            goto setSink;
        case 3:
            if (D_800AE720 != 0) goto phaseDone;
            do { i = func_8002FB08(*(int *)(D_800AE71C * 8 + D_800AE724)); } while (i == 0);
            D_800AE6F8 = 4;
            cdReq_wordsRemaining = D_80079A7C - 0x800;
            break;
        case 4:
            D_800AE6F8 = 5;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            cdReq_sink = (s32)cdReq_dest;
            func_80018714();
            break;
        case 6:                                  /* multiple TIMs: LoadImage each */
            CdGetSector(D_8007A280, 0x1FC);
            n = D_80079A78;
            {
                u32 *p = D_8007A310;
                i = 0;
                D_800AE718 = (RECT *)D_8007A280;
                if (n > 0) {
                    do {
                        LoadImage(D_800AE718, p);
                        i++;
                        p += D_800AE718->w / 2;
                        D_800AE718++;
                    } while (i < n);
                }
            }
            goto sectorDone;
        case 7:
            dst = D_80072C80;
            if (cdReq_size < 0) goto phaseDone;
        setSink:
            D_800AE6F8 = 3;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            cdReq_sink = dst;
            break;
        case 8:
            D_800AE6F8 = 6;
            cdReq_wordsRemaining = (D_80079A7C - 0x7FD) >> 2;
            break;
        }
        break;
    case 1:                                      /* stream tile pixels to VRAM */
        i = D_800AE704 * 0x200;
        CdGetSector(&lzss_sectorStagingBuf[i], 0x200);
        LoadImage((RECT *)&D_800AE710, &lzss_sectorStagingBuf[i]);
        D_800AE704 = (D_800AE704 + 1) & 3;
        do {
            if (D_800AE79A == 0x80) { D_800AE79A = 1; D_800AE79B++; }
            else                     D_800AE79A <<= 1;
            if (D_800AE79B > 0x3F) goto sectorDone;
            D_800AE710 += 0x20;
            if (D_800AE710 > 0x3FF) { D_800AE710 = 0; D_800AE712 += 0x20; }
        } while ((D_800AE79A & D_800AE758[D_800AE79B]) == 0);
        break;
    case 3:                                      /* raw copy to cdReq_sink */
        if (cdReq_wordsRemaining < 0x201) {
            CdGetSector((void *)cdReq_sink, cdReq_wordsRemaining);
        sectorDone:
            D_800AE6F8 = (D_800AE798 == 0) ? 0 : 2;
        } else {
            CdGetSector((void *)cdReq_sink, 0x200);
            cdReq_wordsRemaining -= 0x200;
            cdReq_sink += 0x800;
        }
        break;
    case 4:                                      /* staged copy via func_8002FC64 */
        if (cdReq_wordsRemaining < 0x801) {
            n = cdReq_wordsRemaining + 3;
            if (n < 0) n = cdReq_wordsRemaining + 6;
            CdGetSector(lzss_sectorStagingBuf, n >> 2);
            if (func_8002FC64(cdReq_wordsRemaining, lzss_sectorStagingBuf) == 0) {
            stageFail:
                func_8002FDC8();
                D_800AE6F8 = 7;
            } else {
                D_800AE71C++;
                if (D_800AE798 != 0) goto phaseDone;
                D_800AE6F8 = 0;
            }
        } else {
            CdGetSector(lzss_sectorStagingBuf, 0x200);
            i = func_8002FC64(0x800, lzss_sectorStagingBuf);
            cdReq_sink += 0x800;
            cdReq_wordsRemaining -= 0x800;
            if (i == 0) goto stageFail;
        }
        break;
    case 5:                                      /* LZSS decompress one sector */
        CdGetSector(lzss_sectorStagingBuf, 0x200);
        if (LzssDecodeSector(lzss_sectorStagingBuf) == 0) goto sectorDone;
        break;
    case 6:                                      /* countdown the remaining words */
        cdReq_wordsRemaining -= 0x200;
        if (cdReq_wordsRemaining < 1) {
            if (D_800AE798 != 0) goto phaseDone;
            D_800AE6F8 = 0;
        }
        break;
    }
    if (D_800AE6F8 == 2) {
    phaseDone:                                   /* (reached by the switch above or by goto) */
        D_800AE6F8 = 2;
        cdReq_drainPhase = 1;
    } else if (D_800AE6F8 == 7) {
        cdReq_drainPhase = 2;
    }
endReason:
    if (reason == 5) {
        if (D_800AE6F8 == 4) func_8002FDC8();
    abortDrain:
        cdReq_drainPhase = 2;
    }
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", CdReadSectorReadyCB);
#endif

extern s32 CdQueueBusy(void);

void func_8001A9D8(void) {
    CdQueueBusy();
}


void func_8001A9F8(s32 a0)
{
    extern u16 D_800B9A02;
    extern u8 D_800A6610[];
    extern u32 D_80063108;
    extern u32 D_80063120;

    u32 *p = (u32 *)(D_800A6610 + (D_800B9A02 << 14));
    u32 *q1;
    u32 *q2;

    q1 = &D_80063108;
    *q1 = (p[1] & 0xFFFFFF) | 0x5000000;
    p[1] = (p[1] & 0xFF000000) | ((u32)q1 & 0xFFFFFF);

    q2 = &D_80063120;
    *q2 = (p[1] & 0xFFFFFF) | 0x5000000;
    p[1] = (p[1] & 0xFF000000) | ((u32)q2 & 0xFFFFFF);
}

extern s32 cdReq_curSector;
s32 func_8001AA78(void) {
    return cdReq_curSector;
}

extern s32 cdReq_curSector;
void func_8001AA88(s32 arg0) {
    cdReq_curSector = arg0;
}

void func_8001AA98(void) {
}


extern s32 func_8001ABBC(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_8001AAA0(s32 arg0) {
    func_8001ABBC(1, arg0, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001AAD0);

void func_8001ABB4(void) {
}


extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern u8 resourceIdMap[];
extern u8 D_8006313C;
extern s32 D_800BA1B4;
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8001AE90(s32 a0, s32 a1, s32 a2);
extern s32 func_8001ACF0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4);

s32 func_8001ABBC(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s16 val;

    if (a0 == 1) {
        if (a1 == resLoad_lastId) {
            return 1;
        }
        if (*(s16 *)(resourceIdMap + a1 * 6) == resLoad_loadedFileIdx) {
            val = *(s16 *)(&D_8006313C + a1 * 6);
            if (val != 0) {
                func_8002D4C8((u16)val, 0);
                resLoad_lastId = a1;
            }
            return 1;
        }
    }

    if (D_800BA1B4 != 0) {
        if (D_800BA1B4 != 3) {
            return 0;
        }
        if (func_8001AE90(a0, a1, a2) != 0) {
            D_800BA1B4 = 0;
            return 1;
        }
    }

    if (func_8001ACF0(a0, a1, (s32 *)a2, a3, a4) == 0) {
        return 0;
    }

    D_800BA1B4 = 0;
    return 1;
}


extern s32 D_800747F0;
extern s32 D_800747F4;
extern s32 D_800747E4;
extern s32 D_800747E8;
extern s32 D_800C6D2C;
extern s32 D_800AE6E4;
extern s32 D_800BA318;
extern s32 D_800A6550;
extern s32 D_800BA1B4;
extern s32 D_800AE640;
extern s32 D_800A6430;
extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern u8 resourceIdMap[];
extern u8 D_8006313C;
extern void func_8002D4C8(int arg0, int arg1);

s32 func_8001ACF0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    D_800747F0 = arg0;

    switch (arg0) {
    case 0: {
        s32 tmp;
        D_800C6D2C = arg1;
        D_800AE6E4 = (s32)arg2;
        D_800BA318 = arg3;
        D_800A6550 = arg4;
        tmp = *arg2;
        D_800BA1B4 = 1;
        D_800747F4 = tmp;
        break;
    }

    case 1: {
        s16 v;
        D_800BA1B4 = 2;
        if (arg1 == resLoad_lastId) {
            return 1;
        }
        if (*(s16 *)(resourceIdMap + arg1 * 6) == resLoad_loadedFileIdx) {
            v = *(s16 *)(&D_8006313C + arg1 * 6);
            if (v != 0) {
                func_8002D4C8((u16)v, 0);
                resLoad_lastId = arg1;
            }
            return 1;
        }
        D_800AE640 = arg1;
        D_800747F4 = arg1;
        break;
    }

    case 2: {
        s32 tmp;
        D_800AE6E4 = (s32)arg2;
        tmp = *arg2;
        D_800BA1B4 = 4;
        D_800747F4 = tmp;
        break;
    }

    case 3:
        D_800A6430 = arg1;
        D_800AE6E4 = (s32)arg2;
        D_800747F4 = arg1;
        D_800BA1B4 = 5;
        D_800747E4 = 0;
        D_800747E8 = 1;
        break;
    }
    return 0;
}

extern s32 D_800747F4;

s32 func_8001AE90(s32 a1, s32 a2, s32 a3) {
    switch (a1) {
    case 0:
    case 2:
        return *(s32 *) a3 == D_800747F4;
    case 1:
        return a2 == D_800747F4;
    }
    return 0;
}


extern s32 D_800BA1B4;

s32 func_8001AF04(void) {
    s32 value = D_800BA1B4;
    if (value == 0) {
        return 0;
    }
    if (value == 3) {
        return 1;
    }
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001AF34);

INCLUDE_ASM("asm/nonmatchings/800", func_8001B0D4);

extern s32 D_800747E8;
s32 func_8001B22C(void) {
    return D_800747E8;
}


extern s32 resLoad_curId;
extern s32 resLoad_result;
extern void func_8001B26C(void);

s32 func_8001B23C(s32 a0) {
    resLoad_curId = a0;
    func_8001B26C();
    return resLoad_result;
}


extern s32 D_800BA1B4;
extern s32 resLoad_curId;
extern s32 resLoad_result;
extern s32 D_800C7C60;
extern s32 *D_800C7C64;
extern s32 D_800A2E20;
extern s32 D_800AEC78;
extern s32 func_8001AE90(s32 a0, s32 a1, s32 a2);
extern s32 func_8001ACF0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4);

void func_8001B26C(void) {
    register s32 *s0 __asm__("$16");
    s32 v1;
    s32 tmp;

    if (resLoad_curId != 0) {
        goto exit;
    }

    s0 = &D_800C7C60;
    tmp = D_800BA1B4;
    *s0 = 0x8;
    D_800C7C64 = &D_800A2E20;

    if (tmp != 0) {
        if (tmp != 3) {
            v1 = 0;
            goto exit;
        }
        if (func_8001AE90(0, 0, (s32)&D_800AEC78) != 0) {
            goto set_flag;
        }
    }

    if (func_8001ACF0(0, 0, (s32 *)&D_800AEC78, 0, (s32)s0) == 0) {
        v1 = 0;
        goto exit;
    }

set_flag:
    D_800BA1B4 = 0;
    v1 = 1;

exit:
    resLoad_result = v1;
}


extern void func_8001B34C(void);
extern s32 resLoad_state;

void func_8001B324(void) {
    resLoad_state = 0;
    func_8001B34C();
}


extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern s32 D_800A2B70;
extern s32 D_800BA0FC;

void func_8001B34C(void) {
    resLoad_lastId = 0;
    resLoad_loadedFileIdx = 0;
    D_800A2B70 = 0;
    D_800BA0FC = 0;
}

extern s32 resLoad_lastId;
s32 func_8001B374(void) {
    return resLoad_lastId;
}

extern s32 resLoad_state;
void func_8001B384(void) {
    resLoad_state = 0;
}


extern s32 resLoad_curId;
extern s32 resLoad_result;
extern void ResourceLoadStateMachine(void);

s32 func_8001B394(s32 a0) {
    resLoad_curId = a0;
    ResourceLoadStateMachine();
    return resLoad_result;
}

#ifdef NON_MATCHING
extern int func_8001A114(void);
extern void func_8001B710(void);
extern void func_8002D4C8(int arg0, int arg1);
extern void func_80036D58(int arg0);
extern int StreamLoadStateMachine(int arg0, void *loc, int n);
extern s32 CdQueueBusy(void);          /* defined later in this file */
extern s32 ResourceGetCdLoc(s16 arg0); /* defined later in this file */
extern s32 resLoad_state;
extern s32 resLoad_curId;
extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern s32 resLoad_result;
extern s32 cdReq_curSector;
extern u8 resourceIdMap[]; /* 6B entries {s16 fileIdx; s16 D_8006313A; s16 D_8006313C} */
extern u8 D_8006313A;
extern u8 D_8006313C;
extern u8 cdFileLocTable[];
extern s32 D_800AE6F4;
extern s32 D_800AE70C;
/* loads a resource by resLoad_curId via resourceIdMap; load-once cache
 * (resLoad_lastId/resLoad_loadedFileIdx). field0<0 -> non-CD path func_80036D58; else
 * ResourceGetCdLoc -> StreamLoadStateMachine -> func_8002D4C8 post-process. Polled on
 * resLoad_state; done flag resLoad_result. Phase 3 T3.
 * NON_MATCHING: logically faithful (Ghidra-derived), body close but not byte-exact. Residuals:
 * (1) block placement — the target lays state blocks 0->1->2->3 in order under a top beq-chain
 * dispatch (order 1,0,2,3); this nested-if emits the state-2/3 block inline. (2) frame 0x38 vs
 * 0x28 (~16B reserved locals the original keeps). (3) func_8002D4C8 arg is field2 & 0xFFFF.
 * A switch() risks a rodata jump table (target has none). A later structural / permuter pass. */
void ResourceLoadStateMachine(void) {
    int result;

    result = 0;
    if (resLoad_state != 1) {
        if (resLoad_state != 0) {
            if (resLoad_state == 2) {
                D_800AE6F4 = 0;
                D_800AE70C = 0;
                resLoad_state = 3;
            } else if (resLoad_state != 3) {
                goto done;
            }
            if (func_8001A114() != 0) {
                resLoad_state = 0;
            }
            goto done;
        }
        if (resLoad_curId == resLoad_lastId) {
            resLoad_result = 1;
            return;
        }
        if (*(s16 *)(resourceIdMap + resLoad_curId * 6) == resLoad_loadedFileIdx &&
            *(s16 *)(&D_8006313C + resLoad_curId * 6) != 0) {
            func_8002D4C8(*(s16 *)(&D_8006313C + resLoad_curId * 6), 0);
            resLoad_lastId = resLoad_curId;
            resLoad_result = 1;
            return;
        }
        if (CdQueueBusy() != 0) {
            goto done;
        }
        if (*(s16 *)(resourceIdMap + resLoad_curId * 6) < 0) {
            func_80036D58(*(s16 *)(&D_8006313A + resLoad_curId * 6));
            resLoad_result = 1;
            return;
        }
        if (ResourceGetCdLoc((s16)resLoad_curId) == 0) {
            resLoad_result = 1;
            return;
        }
        if (cdReq_curSector != 0 &&
            *(s32 *)(cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8) != cdReq_curSector) {
            goto done;
        }
        cdReq_curSector = *(s32 *)(cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8);
        resLoad_state++;
    }
    result = StreamLoadStateMachine(*(s16 *)(&D_8006313A + resLoad_curId * 6),
                                    cdFileLocTable + *(s16 *)(resourceIdMap + resLoad_curId * 6) * 8, 0x10);
    if (result == 2) {
        resLoad_state++;
        result = 0;
    }
done:
    if (result != 0) {
        resLoad_loadedFileIdx = *(s16 *)(resourceIdMap + resLoad_curId * 6);
        if (*(s16 *)(&D_8006313C + resLoad_curId * 6) > 0) {
            func_8002D4C8(*(s16 *)(&D_8006313C + resLoad_curId * 6), 0);
            resLoad_lastId = resLoad_curId;
            if (resLoad_curId == 0x3D) {
                func_8001B710();
            }
        }
        resLoad_state = 0;
        cdReq_curSector = 0;
    }
    resLoad_result = result;
}
#else

/* resourceIdMap is a table of 6-byte rows. The destination TU (src/800.c) already declares this
 * column set as three byte-typed externs (u8 resourceIdMap[], u8 D_8006313A, u8 D_8006313C) in two
 * other functions (func_8001ACF0, ResourceGetCdLoc) — a second, differently-typed file-scope
 * extern of the same symbols is a hard C constraint violation, so those exact declarations are
 * adopted verbatim below. See the use-site comment for how the byte match is kept despite that. */
extern int func_8001A114(void);
extern void func_8001B710(void);
extern void func_8002D4C8(int arg0, int arg1);
extern void func_80036D58(int arg0);
extern int StreamLoadStateMachine(int arg0, void *loc, int n);
extern s32 CdQueueBusy(void);
extern s32 ResourceGetCdLoc(s16 arg0);
extern s32 resLoad_state;
extern s32 resLoad_curId;
extern s32 resLoad_lastId;
extern s32 resLoad_loadedFileIdx;
extern s32 resLoad_result;
extern s32 cdReq_curSector;
extern u8 resourceIdMap[]; /* 6B entries {s16 fileIdx; s16 D_8006313A; s16 D_8006313C} */
extern u8 D_8006313A;
extern u8 D_8006313C;
extern u8 cdFileLocTable[]; /* 8B rows {s32 startSector; s32 size}; sites carry an explicit *8 */
extern s32 D_800AE6F4;
extern s32 D_800AE70C;

/* Byte-measured (both tried literally, both NON-MATCH at the same 109/211 site): a raw
 * u8-pointer-arithmetic use site (mirroring the other functions' own idiom), AND a
 * `(ResMapCol *) resourceIdMap` cast of the u8[] object, both leave gcc treating the address as a
 * computed POINTER value — it gets CSE'd into a callee-saved reg (`la $s0,resourceIdMap` hoisted
 * across the 6 uses) instead of rematerialising `lui %hi / addu / lo_sum` at every site the way the
 * target does. Only a genuine array-of-struct OBJECT TYPE avoids this (gcc builds a true ARRAY_REF
 * off the symbol instead of an INDIRECT_REF off a pointer expression) — but declaring `resourceIdMap`
 * that way conflicts with the u8[] extern already load-bearing elsewhere in this TU (func_8001ACF0,
 * ResourceGetCdLoc): two file-scope externs of one identifier with incompatible types is a hard C
 * constraint violation, which is exactly what the reconciler's refuse-TYPE caught.
 * The resolution (cookbook §37/§124 "data asm-label alias"): declare a SEPARATE C identifier bound
 * to the SAME linker symbol via `__asm__("resourceIdMap")`. A distinct identifier sidesteps the
 * redeclaration-type conflict entirely (the TU's own u8[] declarations, wherever they occur, are
 * untouched and still visible under their own name), while this alias gets the true array-of-struct
 * type gcc needs to avoid the CSE. Byte-measured MATCH. */
typedef struct {
    s16 v;
    s16 pad[2];
} ResMapCol;
extern ResMapCol aResourceIdMap[] __asm__("resourceIdMap");
extern ResMapCol aD_8006313A[] __asm__("D_8006313A");
extern ResMapCol aD_8006313C[] __asm__("D_8006313C");
#define RES_FILE aResourceIdMap
#define RES_ARG aD_8006313A
#define RES_POST aD_8006313C

/* Loads the resource named by resLoad_curId. Polled state machine (resLoad_state 0..3); the
 * caller reads the done flag out of resLoad_result.
 *   state 0  arbitrate: load-once cache hit (resLoad_lastId / resLoad_loadedFileIdx), non-CD
 *            resources (file index < 0), CD-queue busy, and the in-flight-sector dedup; on success
 *            latch cdReq_curSector and FALL THROUGH into state 1.
 *   state 1  pump StreamLoadStateMachine until it reports 2 (done).
 *   state 2  reset the stream bookkeeping and FALL THROUGH into state 3.
 *   state 3  poll func_8001A114 for the tail work, then idle.
 *
 * The switch index is read UNSIGNED: that is what makes gcc's case tree degrade to the target's
 * bare equality chain (tested 1,0,2,3 = balance_case_nodes' root-then-bounded-left order). Signed
 * (`switch (resLoad_state)`) inserts an `slti v0,v1,2` range test the target does not have.
 * resLoad_state itself keeps the TU-canonical s32 type; the cast lives at the use site (§20). */
void ResourceLoadStateMachine(void) {
    s32 result;
    /* The original keeps 8 bytes of frame the emitted code never touches (target frame 0x38, an
     * empty-locals build gets 0x30). Reserved as a local so the prologue/epilogue offsets match. */
    s32 sp10[2];

    result = 0;
    switch ((u32)resLoad_state) {
    case 0:
        if (resLoad_curId == resLoad_lastId) {
            resLoad_result = 1;
            return;
        }
        if (RES_FILE[resLoad_curId].v == resLoad_loadedFileIdx && RES_POST[resLoad_curId].v != 0) {
            func_8002D4C8((u16)RES_POST[resLoad_curId].v, 0);
            resLoad_lastId = resLoad_curId;
            resLoad_result = 1;
            return;
        }
        if (CdQueueBusy() != 0) {
            break;
        }
        if (RES_FILE[resLoad_curId].v < 0) {
            func_80036D58(RES_ARG[resLoad_curId].v);
            resLoad_result = 1;
            return;
        }
        if (ResourceGetCdLoc((s16)resLoad_curId) == 0) {
            resLoad_result = 1;
            return;
        }
        if (cdReq_curSector != 0 && *(s32 *)(cdFileLocTable + RES_FILE[resLoad_curId].v * 8) != cdReq_curSector) {
            break;
        }
        cdReq_curSector = *(s32 *)(cdFileLocTable + RES_FILE[resLoad_curId].v * 8);
        resLoad_state++;
        /* fallthrough */
    case 1:
        result = StreamLoadStateMachine(RES_ARG[resLoad_curId].v,
                                        &cdFileLocTable[RES_FILE[resLoad_curId].v * 8], 0x10);
        if (result == 2) {
            resLoad_state++;
            result = 0;
        }
        break;
    case 2:
        D_800AE6F4 = 0;
        D_800AE70C = 0;
        resLoad_state = 3;
        /* fallthrough */
    case 3:
        if (func_8001A114() != 0) {
            resLoad_state = 0;
        }
        break;
    }
    if (result != 0) {
        resLoad_loadedFileIdx = RES_FILE[resLoad_curId].v;
        if (RES_POST[resLoad_curId].v > 0) {
            func_8002D4C8((u16)RES_POST[resLoad_curId].v, 0);
            resLoad_lastId = resLoad_curId;
            if (resLoad_curId == 0x3D) {
                func_8001B710();
            }
        }
        resLoad_state = 0;
        cdReq_curSector = 0;
    }
    resLoad_result = result;
}
#endif

void func_8001B710(void) {
    if ((func_800291B4(0x44) & 0xFF) > 1) {
        func_8002D4C8(0x24, 0);
    }
    if ((func_800291B4(0x56) & 0xFF) > 1) {
        func_8002D4C8(0x25, 0);
    }
    if ((func_800291B4(0x5C) & 0xFF) > 1) {
        func_8002D4C8(0x26, 0);
    }
}

extern u8 resourceIdMap[];
extern u8 cdFileLocTable[];
s32 ResourceGetCdLoc(s16 arg0) {
    s32 idx = *(s16 *)(resourceIdMap + arg0 * 6);
    return *(s32 *)(cdFileLocTable + idx * 8);
}


extern s32 CdQueueBusy(void);
extern void CdReadStateMachine(int);
extern s32 cdReq_curSector;
extern void *cdReq_cdlFile;
extern s32 cdReq_result;
extern s32 D_800AE70C;

s32 func_8001B7C4(void *a0) {
    void *s0;
    s32 curSector;
    s32 result;

    if (CdQueueBusy() != 0) {
        return 0;
    }

    s0 = a0;
    curSector = cdReq_curSector;
    if (curSector == 0) {
        goto L8001B804;
    }
    if (curSector == -1) {
        goto L8001B804;
    }
    return 0;

L8001B804:
    cdReq_curSector = -1;
    cdReq_cdlFile = s0;
    D_800AE70C = 0;

    CdReadStateMachine(1);

    result = cdReq_result;
    if (result == 1) {
        D_800AE70C = *(s32 *)s0;
    }
    return result;
}

extern s32 D_800747FC;
void func_8001B85C(void) {
    D_800747FC = 0;
}


/* func_8001B86C — main/800: the 4-state "start a new frame" state machine driven
 * by D_800747FC.  State 0 initialises the double-buffer OT block for the current
 * buffer index D_800B9A02 and kicks func_80059BFC/func_8001BA84; state 1 arms the
 * frame counter; state 2 runs the per-frame work; states 2 and 3 share the tail
 * that ticks D_80074804 and drives func_8001BADC.
 *
 * Three byte-verified levers were required (all measured, none guessed):
 *
 * 1. UNSIGNED SWITCH INDEX (cookbook §135-1 / §163b).  The dispatch is a pure
 *    equality chain `beq 1 / beqz / beq 2 / beq 3` with NO `slti` range test.
 *    `switch (D_800747FC)` (signed) emits the median-split tree with an `slti`;
 *    only an index whose type is still unsigned after the default promotions
 *    reaches the no-range-test form, so the subject is cast to u32.  src/800.c
 *    already declares `extern s32 D_800747FC;` (L2770) — adopted verbatim and the
 *    unsignedness moved into the switch subject (§174 law 3, DEF-side wall).
 *
 * 2. `break` + ONE trailing `return 0`, NOT `return 0` per arm.  With a `return`
 *    in every arm gcc gives the DECL_RESULT pseudo a live range that reaches into
 *    each arm, it lands in $2, and two things break at once: the case-0 tail
 *    allocates $v1/$a0 instead of the target's $v0/$v1, and reorg refuses to fill
 *    the `beqz` delay slot with the following `addiu $v0,$zero,2` (a stray `nop`,
 *    135 ins vs 134).  Writing `break` and a single `return 0` after the switch
 *    frees $2 and both residuals close together — one source edit, 12 -> 0.
 *
 * 3. The OT table is touched through TWO declarations of the SAME symbol.  The
 *    target reloads D_800B9A02 three times inside case 0, which only happens when
 *    the stores are plain INDIRECT_REFs: an ARRAY_REF store sets MEM_IN_STRUCT_P
 *    and gcc-2.7.2's true_dependence() then drops the dependence against the
 *    not-in-struct constant-address `lhu` (cookbook §135-2), collapsing the three
 *    loads into one.  But a plain store to `SYM+reg` *plus any read of the same
 *    DECL* makes gcc allocate a dead 8-byte stack temp (frame 0x20 vs the target's
 *    0x18) — measured, and it survives every re-spelling of either access.  Two
 *    distinct DECLs of the same assembler symbol avoid the temp while keeping the
 *    plain-store aliasing, so the byte view drives the stores and the s32 view
 *    (`otTbl`, asm-labelled to D_800A651C) drives the loads.  reloc_identity.py
 *    reports AGREE / 34 relocations: every symbol here is the one the target's own
 *    relocation lines name (§174 law 1c).
 *
 * @class: MATCH (was LENGTH-DRIFT/+1 -> ADDRESSING -> MATCH)
 */

extern s32 D_800747FC;
extern s32 D_80074800;
extern s32 D_80074804;
extern s32 D_8007480C;
extern u16 D_800B9A02;
extern u8 D_800A6610[];
extern u8 *D_800A5E60;
extern u8 D_8007BA70[];
extern u8 D_800AF630[];

extern void func_80059BFC(s32 a0, s32 a1);
extern void func_8001BA84(void);
extern void func_80059FC0(u8 *a0);
extern void func_8001BB60(void);
extern s32 func_8001BADC(s32 a0, s32 a1);

s32 func_8001B86C(void)
{
    /* block scope: src/800.c declares D_800A651C as OtBlk_80016450[] inside
     * func_80015D4C, so the byte view has to stay local too. */
    extern u8 otBytes[] __asm__("D_800A651C");
    extern u8 D_800A6528[];                      /* = D_800A651C + 12 */
    extern s32 otTbl[] __asm__("D_800A651C");    /* s32 view of D_800A651C — see note 3 */
    u8 *p = D_800AF630;

    switch ((u32)D_800747FC) {
    case 0: {
        u8 *q = D_8007BA70 + D_800B9A02 * 80000;

        *(s32 *)(otBytes + D_800B9A02 * 20) =
            (s32)(D_800A6610 + (D_800B9A02 << 14));
        *(s32 *)(D_800A6528 + D_800B9A02 * 20) =
            (s32)(D_800A6610 + 4 + (D_800B9A02 << 14));
        D_800A5E60 = q;
        func_80059BFC(otTbl[D_800B9A02 * 5], 2);
        func_8001BA84();
        D_80074800 = 0x80;
        D_800747FC++;
        break;
    }
    case 1:
        D_80074804 = 1;
        D_800747FC = 2;
        break;
    case 2:
        func_80059FC0(p + 0x160);
        func_80059BFC(otTbl[D_800B9A02 * 5], 2);
        func_8001BB60();
        D_800747FC++;
        /* fallthrough */
    case 3:
        if (D_80074804++ >= 2) {
            D_80074804 = 1;
            if (func_8001BADC(D_8007480C, 1) != 0) {
                return 1;
            }
            D_8007480C++;
        } else {
            func_8001BADC(D_8007480C, 0);
        }
        break;
    }
    return 0;
}


extern void func_8001BC6C(s32 a0, s32 a1);
extern u8 D_800630E8[];

void func_8001BA84(void) {
    s32 addr = (s32)&D_800630E8;

    func_8001BC6C(addr, 0x80);
    func_8001BC6C(addr + 8, 0x80);
    func_8001BC6C(addr + 16, 0x80);
    func_8001BC6C(addr + 24, 0x80);
}

extern s32 D_80074808;

s32 func_8001BADC(s32 arg0, s32 arg1) {
    register s32 orig    __asm__("$10");
    register s32 i       __asm__("$8");
    register s32 mask    __asm__("$11");
    register s32 off     __asm__("$9");
    register s32 c29     __asm__("$12");
    register s32 colbase __asm__("$13");
    register s32 c       __asm__("$6");
    register s32 p       __asm__("$5");
    s32 color;
    s32 idx;
    s32 *addr;

    orig = arg0;
    i = 0;
    mask = -(arg1 != 0);
    colbase = 0x62000000;
    c29 = 29;
    off = 0;
    while (i < 15) {
        c = 0;
        if (i < orig) {
            c = mask & 8;
        }
        color = (c << 16) | ((c << 8) | colbase) | c;
        idx = c29 - i;
        p = D_80074808;
        addr = (s32 *)(p + off);
        addr[2] = color;
        addr = (s32 *)(p + idx * 20);
        addr[2] = color;
        i++;
        off += 20;
    }
    return orig >= 44;
}

extern u8 *D_800A5E60;
extern s32 D_80074808;
extern s32 D_8007480C;
extern void func_8001BBBC(s32 a0, s32 a1, u8 a2);

void func_8001BB60(void)
{
    s32 i;

    D_80074808 = (s32)D_800A5E60;
    for (i = 0; i < 30; i++) {
        func_8001BBBC(0, i * 8, 0);
    }
    D_8007480C = 0;
}


/* func_8001BBBC — main/800: build the 0x14-byte "scanline band" primitive at the
 * head of the current prim buffer (D_800A5E60) — a GPU draw-mode word (0xE1000040)
 * followed by a TILE (code 0x62, 0x140x8 at (a0-160, a1-120), colour a2) — then
 * PSY-Q addPrim() it onto OT entry 1 of the current buffer's table
 * (D_800A6610 + (D_800B9A02 << 14)) and bump D_800A5E60 past it.
 *
 * @class: MATCH (was SCHEDULE-REORDER/2)
 *
 * THE RESIDUAL AND ITS MECHANISM (the only non-obvious thing here; cookbook
 * material — sched.md S1/S2 + §37's 2-instruction-constant note):
 *
 *   The target materialises the 24-bit mask as `lui $t1,0xff / addiu $v0,4 /
 *   ori $t1,$t1,0xffff` — the independent `li 4` sits BETWEEN the two halves of
 *   the mask.  Written as one constant (`mFF = 0xFFFFFF`) that is UNREACHABLE:
 *   mips.md:3208's `large_int` define_split fires inside sched1's try_split
 *   (sched.c:4830), so the lui/ori get CONSECUTIVE LUIDs, and rank_for_schedule's
 *   only tie-break among the priority-1 constants is exactly that LUID
 *   (sched.c:2428).  No statement order can put a third insn between two
 *   consecutive LUIDs — a 63-variant statement-order sweep confirmed it (every
 *   one scored the same 2).  So the target's two halves are NOT a split pair:
 *   they are two insns from expand.  Two edits reproduce that:
 *
 *   1. Build the mask in two steps with a zero-byte re-tie between them
 *      (`__asm__("" : "=r"(mFF) : "0"(mFF))`, the §30-#3 idiom already used by
 *      func_80016110/func_80016450 in this file) so cse cannot fold
 *      `0xFF0000 | 0xFFFF` back into one CONST_INT.  Now the `ori` carries its
 *      own LUID, taken at the point the `|=` is written.
 *   2. Route the len byte's 4 through the already-multi-set `tmp` ($2) instead of
 *      an anonymous temp.  An anonymous temp is single-set, so birthing_insn_p
 *      (sched.c:2469) boosts it to LAUNCH_PRIORITY and it sinks BELOW the mask's
 *      low half; a hard-reg pseudo with reg_n_sets>1 gets no boost and floats up
 *      with the other priority-1 constants in plain ascending-LUID order — which,
 *      with the `|=` written after the store, lands it exactly between the halves.
 *
 *   Both are required: the split alone still scores 2, the boost-kill alone
 *   moves the `li 4` one slot too far (ahead of the `lui`).
 *
 * Symbols hand-checked against asm/nonmatchings/800/func_8001BBBC.s (§174 law 1c):
 * D_800A5E60 (lw %lo + sw %lo), D_800B9A02 (lhu %lo), D_800A6610 (addiu %lo);
 * no calls.  All three externs are copied verbatim from src/800.c L4489-4491
 * (the same file-scope spellings func_8001B86C and func_8001D3FC already use).
 */

extern u16 D_800B9A02;
extern u8 D_800A6610[];
extern u8 *D_800A5E60;

void func_8001BBBC(s32 a0, s32 a1, u8 a2)
{
    register u8 *p __asm__("$7");
    register u32 tblAddr __asm__("$8");
    register u32 tmp __asm__("$2");
    register u32 val __asm__("$3");
    register u32 mFF __asm__("$9");
    register u32 m24 __asm__("$4");
    register u32 tag0 __asm__("$10");
    u32 *tbl;

    tag0 = 0xE1000040;
    mFF = 0xFF0000;
    __asm__("" : "=r"(mFF) : "0"(mFF));   /* zero-byte re-tie: keeps the mask's two
                                           * halves as two expand insns (see header) */
    a0 -= 0xA0;

    p = D_800A5E60;
    tblAddr = D_800B9A02;
    a1 -= 0x78;

    tmp = 4;
    *(u8 *)(p + 3) = tmp;
    mFF |= 0xFFFF;

    *(u8 *)(p + 11) = 0x62;
    *(u16 *)(p + 16) = 0x140;
    *(u16 *)(p + 18) = 8;

    val = *(u32 *)p;
    tblAddr = (tblAddr << 14) + (u32)&D_800A6610;
    tbl = (u32 *)tblAddr;

    *(u16 *)(p + 12) = (u16)a0;
    *(u32 *)(p + 4) = tag0;
    *(u8 *)(p + 10) = a2;
    *(u8 *)(p + 9) = a2;
    *(u8 *)(p + 8) = a2;
    *(u16 *)(p + 14) = (u16)a1;
    tmp = tbl[1];
    m24 = 0xFF000000;
    val = (val & m24) | (tmp & mFF);
    *(u32 *)p = val;

    val = (u32)(p + 0x14);
    D_800A5E60 = (u8 *)val;
    tmp = tbl[1];
    tmp = (tmp & m24) | ((u32)p & mFF);
    tbl[1] = tmp;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001BC6C);

extern s32 CdQueueBusy(void);

s32 SsGetMute(void) {
    return CdQueueBusy() != 0;
}

extern void func_8002CCD8(void);
extern void func_800596F4(s32);
extern void DrawSyncCallback(s32);
extern void func_80059234(s32);
extern void func_80059658(s32);
extern int VSync(int mode);
extern void func_8005D118(void);
extern void StopRCnt(void);
extern void func_80043300(void);
extern void ResetCallback(void);
extern void StopCallback(void);

void func_8001BDA0(void) {
    func_8002CCD8();
    func_800596F4(0);
    DrawSyncCallback(0);
    func_80059234(0);
    func_80059658(0);
    VSync(0);
    func_800596F4(0);
    func_80059234(3);
    func_8005D118();
    StopRCnt();
    func_80043300();
    ResetCallback();
    StopCallback();
}

extern s32 D_800747EC;
void func_8001BE20(void) {
    D_800747EC = 0;
}


extern s32 D_800747EC;
extern s32 D_800747E4;
extern s32 D_800747E8;
extern s32 D_800BA1B4;
extern s32 cdReq_curSector;
extern s32 CdQueueBusy(void);
extern void func_8002D4C8(int arg0, int arg1);

s32 func_8001BE30(void) {
    s32 state = D_800747EC;
    s32 busy;
    s32 v0;

    if (state == 1) {
        goto L_case1;
    }
    if (state < 2) {
        if (state != 0) {
            return 0;
        }
        goto L_case0;
    }
    if (state == 2) {
        goto L_case2;
    }
    if (state == 3) {
        goto L_case3;
    }
    return 0;

L_case0:
    busy = CdQueueBusy();
    if (D_800BA1B4 != 5) {
        goto L_busy;
    }
    if (D_800747E4 != 0) {
        func_8002D4C8(0x16, 0);
    }
    D_800BA1B4 = 0;
    D_800747E8 = 0;
    D_800747E4 = 0;
    D_800747EC = 3;
    goto L_ret0;

L_busy:
    if (busy == 1 || busy == 4 || busy == 2) {
        func_8002D4C8(0x16, 0);
        D_800747EC = D_800747EC + 1;
        goto L_ret0;
    }
    if (cdReq_curSector == 0) {
        return 1;
    }
    D_800747EC = 2;
    return 0;

L_case1:
    v0 = CdQueueBusy();
    goto L_shared;

L_case2:
    v0 = cdReq_curSector;
    goto L_shared;

L_case3:
    v0 = D_800747E8;

L_shared:
    if (v0 == 0) {
        __asm__ __volatile__("");
        return 1;
    }
L_ret0:
    return 0;
}

extern s32 D_80063074;
s32 func_8001BFA0(void) {
    return D_80063074 & 0x1;
}

extern s32 D_80063074;
void func_8001BFB0(void) {
    D_80063074++;
}

extern s32 D_800A2B70;
extern s32 D_800BA0FC;

void func_8001BFD0(void) {
    D_800A2B70 = 0;
    D_800BA0FC = 0;
}

extern s32 D_800747D8;
s32 func_8001BFE8(void) {
    return D_800747D8;
}

extern s32 D_800747D8;

s32 func_8001BFF8(void) {
    return D_800747D8 = 1;
}


extern u8 D_800B9A11;
extern void func_8001F9F8(void);
extern void func_8001D1C4(void);

void func_8001C00C(void) {
    if (D_800B9A11 != 1) {
        func_8001F9F8();
        func_8001D1C4();
    }
}

void func_8001C044(void) {
    extern void func_80016714(void *a0, s32 a1);
    extern u8 D_800AF630[];

    u8 *base;
    u8 *p;
    s32 i;

    base = D_800AF630;
    p = &base[0x65A8];
    i = 0;
    do {
        func_80016714(p, 0x38);
        i++;
        p += 0x38;
    } while (i < 0x100);

    p = &base[0x2A8];
    i = 0;
    do {
        func_80016714(p, 0x84);
        i++;
        p += 0x84;
    } while (i < 0xC0);

    *(u16 *)&base[0x19C] = 0;
}

void func_8001C0C8(void) {
    extern void func_80016714(void *a0, s32 a1);
    extern u8 D_800AF630[];

    u8 *base;
    u8 *p;
    s32 i;

    base = D_800AF630;
    p = &base[0x65A8];
    i = 0;
    do {
        func_80016714(p, 0x38);
        i++;
        p += 0x38;
    } while (i < 0x100);

    p = &base[0x2A8];
    i = 0;
    do {
        func_80016714(p, 0x84);
        i++;
        p += 0x84;
    } while (i < 0xC0);

    *(u16 *)&base[0x19C] = 0;
}

extern void func_80016714(void *a0, s32 a1);
extern u8 D_800AF630[];

void func_8001C14C(void) {
    u8 *base;
    u8 *p;

    base = D_800AF630;
    p = base + 0x65A8;
    while (p < base + 0x6688) {
        func_80016714(p, 0x38);
        p += 0x38;
    }

    p = base + 0x2A8;
    while (p < base + 0x4B8) {
        func_80016714(p, 0x84);
        p += 0x84;
    }
}


extern void func_80054514(s32 a0, s32 a1);

void func_8001C1E4(void* a0, s32 a1) {
    s32 local_buf[8];

    *(s32 *)(a0 + 0x78) = a1 + 0x30;
    *(s32 *)(a0 + 0x30) = 0;

    func_80054514((s32)(a0 + 0x30), (s32)local_buf);
}

void func_8001C214(s32 a0, s32 a1)
{
    extern void func_8001C9D0(void);
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern void GsMapModelingData(u32 *p);
    extern u8 D_80063548[];

    s32 sp10[8];

    func_8001C9D0();
    *(u16 *)a0 = 1;
    *(u16 *)(a0 + 2) = 0;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514(a0 + 0x30, (s32)&sp10[0]);
    *(s32 *)(a0 + 0x24) = a1;
    if (a1 != 0) {
        *(s32 *)(a0 + 0x20) = (s32)D_80063548;
        if (*(s32 *)a1 != 0) {
            do {
                GsMapModelingData((u32 *)((*(s32 *)a1 & 0x80FFFFFF) + 4));
                a1 += 4;
            } while (*(s32 *)a1 != 0);
        }
    }
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C2C4(s32 a0) {
    s32 stack_buf[8];
    s32 *s1;

    func_8001C9D0();

    s1 = (s32 *)(a0 + 0x30);

    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 0;
    func_80052D90(0, s1);

    func_80054514((s32)s1, (s32)stack_buf);

    *(s32 *)(a0 + 0x24) = 0;
}

void func_8001C320(s32 a0, s32 a1)
{
    extern void func_8001C9D0(void);
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern void GsMapModelingData(u32 *p);
    extern void GsLinkObject5();
    extern void *GsPresetObject();
    extern u8 D_800AF630[];
    extern u8 D_80063548[];
    extern u16 D_800AF7CC;
    extern s32 *D_800AF7C8;
    extern u8 D_800A5BD0[];

    s32 sp10[8];
    register s32 obj __asm__("$17");
    register s32 next __asm__("$19");
    register s32 work __asm__("$20");
    s32 entry;
    u16 c2;

    obj = a0;
    func_8001C9D0();
    *(u16 *)obj = 1;
    *(u16 *)(obj + 2) = 1;
    func_80052D90(0, (void *)(obj + 0x30));
    func_80054514(obj + 0x30, (s32)&sp10[0]);
    work = (s32)D_800AF630;
    *(s32 *)(obj + 0x24) = a1;
    if (a1 != 0) {
        *(s32 *)(obj + 0x20) = (s32)D_80063548;
        next = (s32)D_800AF7C8;
        *(u16 *)(obj + 0x2E) = D_800AF7CC;
        if (*(s32 *)a1 != 0) {
            do {
                entry = (*(s32 *)a1 & 0x80FFFFFF) + 4;
                a1 += 4;
                __asm__ __volatile__("" : "=r"(entry) : "0"(entry));
                GsMapModelingData((u32 *)entry);
                c2 = *(u16 *)(work + 0x19C);
                *(u16 *)(work + 0x19C) = c2 + 1;
                GsLinkObject5((u32 *)(entry + 8),
                              (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], 0);
                next = (s32)GsPresetObject(
                    (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], (void *)next);
            } while (*(s32 *)a1 != 0);
        }
        *(s32 *)(work + 0x198) = next;
    }
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C448(s32 a0) {
    s32 local_10[8];
    s32 s0_val = a0;
    s32 s1_val;

    func_8001C9D0();

    s1_val = s0_val + 0x30;
    *(s16 *)s0_val = 1;
    *(s16 *)(s0_val + 0x2) = 1;

    func_80052D90(0, (void *)s1_val);
    func_80054514(s1_val, (s32)&local_10[0]);

    *(s32 *)(s0_val + 0x24) = 0;
}

void func_8001C4A4(s32 a0, u32 *a1)
{
    extern void func_8001C9D0(void);
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern void GsMapModelingData(u32 *p);
    extern u8 D_80063548[];

    s32 sp10[8];

    func_8001C9D0();
    *(u16 *)a0 = 1;
    *(u16 *)(a0 + 2) = 7;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514(a0 + 0x30, (s32)&sp10[0]);
    *(s32 *)(a0 + 0x24) = (s32)a1;
    if (a1 != 0) {
        *(s32 *)(a0 + 0x20) = (s32)D_80063548;
        if (*a1 != 0) {
            do {
                GsMapModelingData((u32 *)((*a1 & 0x80FFFFFF) + 4));
                a1 += 1;
            } while (*a1 != 0);
        }
    }
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C558(s32 a0) {
    u8 local_var[32];

    func_8001C9D0();
    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 7;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514((s32)(a0 + 0x30), (s32)&local_var[0]);
    *(s32 *)(a0 + 0x24) = 0;
}

void func_8001C5B8(s32 a0, s32 a1)
{
    extern void func_8001C9D0(void);
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_80054514(s32 a0, s32 a1);
    extern void GsMapModelingData(unsigned long *p);
    extern void GsLinkObject5();
    extern void *GsPresetObject();
    extern u8 D_800AF630[];
    extern u8 D_80063548[];
    extern u16 D_800AF7CC;
    extern s32 *D_800AF7C8;
    extern u8 D_800A5BD0[];

    s32 sp10[8];
    register s32 obj __asm__("$17");
    register s32 next __asm__("$19");
    register s32 work __asm__("$20");
    s32 entry;
    u16 c2;

    obj = a0;
    func_8001C9D0();
    *(u16 *)obj = 1;
    *(u16 *)(obj + 2) = 8;
    func_80052D90(0, (void *)(obj + 0x30));
    func_80054514(obj + 0x30, (s32)&sp10[0]);
    work = (s32)D_800AF630;
    *(s32 *)(obj + 0x24) = a1;
    if (a1 != 0) {
        *(s32 *)(obj + 0x20) = (s32)D_80063548;
        next = (s32)D_800AF7C8;
        *(u16 *)(obj + 0x2E) = D_800AF7CC;
        if (*(s32 *)a1 != 0) {
            do {
                entry = (*(s32 *)a1 & 0x80FFFFFF) + 4;
                a1 += 4;
                __asm__ __volatile__("" : "=r"(entry) : "0"(entry));
                GsMapModelingData((unsigned long *)entry);
                c2 = *(u16 *)(work + 0x19C);
                *(u16 *)(work + 0x19C) = c2 + 1;
                GsLinkObject5((u32 *)(entry + 8),
                              (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], 0);
                next = (s32)GsPresetObject(
                    (void *)&D_800A5BD0[(c2 << 2) + c2 << 2], (void *)next);
            } while (*(s32 *)a1 != 0);
        }
        *(s32 *)(work + 0x198) = next;
    }
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C6E4(void *a0) {
    s32 sp_buf[8];

    ((void (*)(void *))func_8001C9D0)(a0);

    *(s16 *)a0 = 1;
    *(s16 *)((s32)a0 + 2) = 8;

    func_80052D90(0, (void *)((s32)a0 + 0x30));
    func_80054514((s32)a0 + 0x30, (s32)sp_buf);

    *(s32 *)((s32)a0 + 0x24) = 0;
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C744(s32 a0, s32 a1) {
    char local_buf[32];

    func_8001C9D0();

    *(s16 *)a0 = 1;
    *(s16 *)(a0 + 2) = 2;

    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514(a0 + 0x30, (s32)(&local_buf[0]));

    *(s32 *)(a0 + 0x24) = a1;
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C7B0(void *arg0) {
    s32 local_s1;
    u8 local_array[0x20];

    ((void (*)(void *))func_8001C9D0)(arg0);

    local_s1 = (s32)((char *)arg0 + 0x30);

    *(s16 *)((char *)arg0 + 0x0) = 1;
    *(s16 *)((char *)arg0 + 0x2) = 2;

    func_80052D90(0, (void *)local_s1);

    func_80054514(local_s1, (s32)local_array);

    *(s32 *)((char *)arg0 + 0x24) = 0;
}

extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);
extern void GsMapModelingData(unsigned long *p);
extern u8 D_80063548[];

void func_8001C810(s32 a0, s32 *a1) {
    s32 local_buf[8];
    s32 base;

    func_8001C9D0();

    base = a0 + 0x30;
    *(s16 *)(a0 + 0) = 1;
    *(s16 *)(a0 + 2) = 5;
    func_80052D90(0, (void *)base);
    func_80054514(base, (s32)local_buf);

    *(s32 *)(a0 + 0x24) = (s32)a1;
    if (a1 != 0) {
        *(s32 *)(a0 + 0x20) = (s32)&D_80063548;
        if (*a1 != 0) {
            do {
                GsMapModelingData((unsigned long *)((*a1 & 0x80FFFFFF) + 4));
                a1++;
            } while (*a1 != 0);
        }
    }
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001C8C4(s32 a0) {
    s32 local_10[4];
    s32 local_20[4];

    ((void (*)(s32))func_8001C9D0)(a0);
    *(s16 *)(a0 + 0x0) = 1;
    *(s16 *)(a0 + 0x2) = 5;
    func_80052D90(0, (void *)(a0 + 0x30));
    func_80054514(a0 + 0x30, (s32)local_10);
    *(s32 *)(a0 + 0x24) = 0;
}


extern void GsMapModelingData(unsigned long *p);

void func_8001C924(void *a0, s32 *a1) {
    s32 *s0;
    s32 v0;

    s0 = a1;
    *(s32 **)(a0 + 0x24) = s0;

    v0 = *s0;
    while (v0 != 0) {
        s32 tmp = *s0;
        s0++;
        GsMapModelingData((unsigned long *)((u32)tmp + 4));
        v0 = *s0;
    }
}


extern void GsMapModelingData(unsigned long *p);

void func_8001C97C(s32 *a0) {
    s32 *ptr = a0;
    s32 val;

    val = *ptr;
    if (val != 0) {
        do {
            s32 item = *ptr;
            ptr++;
            GsMapModelingData((unsigned long *)(item + 4));
            val = *ptr;
        } while (val != 0);
    }
}

void func_8001C9D0(void) {
    register s32 a0v __asm__("$4");
    s32 v;

    v = 0x1000;
    *(s16 *)(a0v + 0x1C) = v;
    *(s16 *)(a0v + 0x1A) = v;
    *(s16 *)(a0v + 0x18) = v;
    v = 0xC8;
    *(s16 *)(a0v + 0x14) = 0;
    *(s16 *)(a0v + 0x12) = 0;
    *(s16 *)(a0v + 0x10) = 0;
    *(s16 *)(a0v + 0x0C) = 0;
    *(s16 *)(a0v + 0x0A) = 0;
    *(s16 *)(a0v + 0x08) = 0;
    *(s32 *)(a0v + 0x04) = 0;
    *(s32 *)(a0v + 0x20) = 0;
    *(s16 *)(a0v + 0x28) = v;
    *(s16 *)(a0v + 0x2A) = v;
    *(s16 *)(a0v + 0x2C) = 0;
    *(s16 *)(a0v + 0x2E) = 0;
    *(s32 *)(a0v + 0x80) = 0;
}


extern void func_8001C9D0(void);
extern void func_80052D90(s32, void *);
extern void func_80054514(s32 a0, s32 a1);

void func_8001CA1C(void *a0, void *a1)
{
    register void *s0 __asm__("$16");
    register void *s1 __asm__("$17");
    register void *s2 __asm__("$18");
    u32 local_pad[7];

    s0 = a0;
    s2 = a1;

    func_8001C9D0();

    s1 = (void *)((s32)s0 + 0x30);

    *(s16 *)s0 = 1;
    *(s16 *)((s32)s0 + 2) = 3;

    func_80052D90(0, s1);
    func_80054514((s32)s1, (s32)local_pad);

    *(s32 *)((s32)s0 + 0x20) = (s32)s2;
}

extern void func_8001C9D0(void);
extern void func_80052D90(s32 a0, void *a1);
extern void func_80054514(s32 a0, s32 a1);

void func_8001CA88(s32 a0, s32 a1)
{
    s32 local_10[8];
    s32 s0_val = a0;
    s32 s2_val = a1;
    s32 s1_val;

    func_8001C9D0();

    s1_val = s0_val + 0x30;
    *(s16 *)s0_val = 1;
    *(s16 *)(s0_val + 0x2) = 4;

    func_80052D90(0, (void *)s1_val);
    func_80054514(s1_val, (s32)&local_10[0]);

    *(s32 *)(s0_val + 0x20) = s2_val;
    *(s32 *)(s0_val + 0x74) = 0;
    *(s16 *)(s0_val + 0xE) = 0;
    *(s16 *)(s0_val + 0x1E) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CB00(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 1;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s32 *)(a0 + 0x4) = 0x8000000;
    *(s16 *)(a0 + 0x2C) = 0;
}

extern void func_8001CF48(s32 a0);

void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 2;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s32 *)(a0 + 0x4) = 0xC000040;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CBDC(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CC3C(s32 a0, void *a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = (s32)a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CCA0(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x9;
    *(s16 *)(a0 + 0x28) = (s16)a2;
    *(s16 *)(a0 + 0x2A) = (s16)a3;
    *(s32 *)(a0 + 0x20) = a1;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32);

void func_8001CD04(s32 a0, s32 a1)
{
    func_8001CF48(a0);
    *(s16*)(a0 + 0x2) = 4;
    *(s32*)(a0 + 0x20) = a1;
    *(s16*)(a0 + 0xE) = 0;
    *(s16*)(a0 + 0x1E) = 0;
    *(s16*)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CD50(s32 a0, s32 a1) {
    s32 s0 = a0;
    s32 s1 = a1;
    func_8001CF48(s0);
    *(s16 *)((u8 *)s0 + 0x2) = 5;
    *(s32 *)((u8 *)s0 + 0x20) = s1;
    *(s16 *)((u8 *)s0 + 0xE) = 0;
    *(s16 *)((u8 *)s0 + 0x1E) = 0;
    *(s16 *)((u8 *)s0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CD9C(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 6;
    *(s32 *)(a0 + 0x20) = a1;
    *(s16 *)(a0 + 0xE) = 0;
    *(s16 *)(a0 + 0x1E) = 0;
    *(s16 *)(a0 + 0x2C) = 0;
}


extern void func_8001CF48(s32 a0);

void func_8001CDE8(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x7;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CE28(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x8;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CE68(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0x8;
    *(u8 *)(a0 + 0x27) = 0xBA;
    *(s32 *)(a0 + 0x4) |= 0x400000;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CEC0(s32 a0, s32 a1) {
    func_8001CF48(a0);
    *(s16 *)(a0 + 0x2) = 0xA;
    *(s32 *)(a0 + 0x20) = a1;
}


extern void func_8001CF48(s32 a0);

void func_8001CF00(s32 a0) {
    s32 s0 = a0;
    func_8001CF48(a0);
    *(s16 *)(s0 + 0x2) = 0xB;
}

void func_8001CF30(s32 *a0) {
    a0[1] = (a0[1] & ~0x40) | 0x1000;
}

void func_8001CF48(s32 a0) {
    *(s16 *)a0 = 2;
    *(s16 *)(a0 + 0x1C) = 0x1000;
    *(s16 *)(a0 + 0x1A) = 0x1000;
    *(s16 *)(a0 + 0x18) = 0x1000;
    *(s16 *)(a0 + 0x32) = 0;
    *(s16 *)(a0 + 0x30) = 0;
    *(s16 *)(a0 + 0x2E) = 0;
    *(s16 *)(a0 + 0x2C) = 0;
    *(u8 *)(a0 + 0x27) = 0;
    *(s16 *)(a0 + 0x1E) = 0;
    *(s16 *)(a0 + 0x14) = 0;
    *(s16 *)(a0 + 0x12) = 0;
    *(s16 *)(a0 + 0x10) = 0;
    *(s16 *)(a0 + 0x0E) = 0;
    *(s16 *)(a0 + 0x0C) = 0;
    *(s16 *)(a0 + 0x0A) = 0;
    *(s16 *)(a0 + 0x08) = 0;
    *(s32 *)(a0 + 0x04) = 0;
    *(s32 *)(a0 + 0x20) = 0;
    *(u8 *)(a0 + 0x26) = 0x80;
    *(u8 *)(a0 + 0x25) = 0x80;
    *(u8 *)(a0 + 0x24) = 0x80;
    *(s32 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x2C) = 0;
}

extern void func_8001CFDC(s32 a0, s32 a1);

void func_8001CFB8(void) {
    func_8001CFDC(0, 4);
}

extern u8 D_800AF630[];

void *func_8001CFDC_impl(s32 start, s32 end) __asm__("func_8001CFDC");

void *func_8001CFDC_impl(s32 start, s32 end) {
    u8 *base = D_800AF630;
    u8 *p;
    s32 off;
    s32 i;

    if ((u32)start >= 0xC0)
        return 0;
    if ((u32)end >= 0xC1)
        return 0;
    if (start < end) {
        p = base + start * 0x84;
        off = start * 0x84;
        for (i = start; i < end; i++) {
            if (*(u16 *)(p + 0x2A8) == 0)
                return base + (off + 0x2A8);
            p += 0x84;
            off += 0x84;
        }
    }
    return 0;
}

extern void func_8001D074(s32 a, s32 b);

void func_8001D050(void) {
    func_8001D074(0, 4);
}

extern u8 D_800AF630[];

s32 func_8001D074_impl(s32 arg0, s32 arg1) __asm__("func_8001D074");

s32 func_8001D074_impl(s32 arg0, s32 arg1) {
    u8* base = D_800AF630;
    s32 off;
    u8* ptr;

    if ((u32)arg0 >= 0x100U) {
        goto ret0;
    }
    if ((u32)arg1 >= 0x101U) {
        return 0;
    }
    if (arg0 >= arg1) {
        goto ret0;
    }

    ptr = base + arg0 * 56;
    off = arg0 * 56;
    do {
        if (*(u16*)(ptr + 0x65A8) == 0) {
            return base + (off + 0x65A8);
        }
        ptr += 0x38;
        arg0 += 1;
        off += 0x38;
    } while (arg0 < arg1);

ret0:
    return 0;
}

void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2) {
    *(s16 *)(arg0 + 0x28) = arg1;
    *(s16 *)(arg0 + 0x2A) = arg2;
}

void func_8001D0F4(s32 *a0)
{
    while (*a0 != 0) {
        *a0 &= 0x80FFFFFF;
        a0 += 1;
    }
}

void func_8001D130(s32 arg0, s32 arg1) {
    *(s32 *)(arg0 + arg1 * 4) &= 0x80FFFFFF;
}

s32 func_8001D150(s32 *arg0, s32 arg1) {
    arg1 *= 4;
    arg1 += (s32) arg0;
    *(s32 *) arg1 |= 0x1000000;
    return *(s32 *) arg1;
}

void func_8001D16C(s32 *arg0, s32 *arg1)
{
    s32 *a2;
    s32 v0;

    a2 = arg0 + 0x20;
    v0 = *a2 & 0x80FFFFFF;
    if (v0 != 0) {
        do {
            a2 = (s32 *)((s32)a2 & 0x80FFFFFF);
            v0 = *a2 & 0x80FFFFFF;
        } while (v0 != 0);
    }
    *a2 = ((s32)arg1 & 0x80FFFFFF) | 0x01000000;
    *arg1 = 0;
}

extern u8 D_800B9A11;
extern u8 D_800B5CB8;
extern u8 D_800B5D28;
extern u8 D_800B60A8;
extern u8 D_800B6968;
extern u8 D_800B7768;
void func_8001D388();

void func_8001D1C4(void) {
    u8 *base;
    u8 *p;
    s32 sp10;
    u8 flags;

    base = &D_800B9A11;
    sp10 = 0;
    flags = *base;
    p = base - 0x3E39;
    if (p < base - 0x3D59) {
        do {
            func_8001D388(p, &sp10);
            p += 0x38;
        } while (p < base - 0x3D59);
    }
    if (!(flags & 4)) {
        p = &D_800B5CB8;
        if (p < &D_800B5CB8 + 0x70) {
            do {
                func_8001D388(p, &sp10);
                p += 0x38;
            } while (p < &D_800B5CB8 + 0x70);
        }
    }
    if (!(flags & 0x10)) {
        p = &D_800B5D28;
        if (p < &D_800B5D28 + 0x380) {
            do {
                func_8001D388(p, &sp10);
                p += 0x38;
            } while (p < &D_800B5D28 + 0x380);
        }
    }
    if (!(flags & 0x20)) {
        p = &D_800B60A8;
        if (p < &D_800B60A8 + 0x8C0) {
            do {
                func_8001D388(p, &sp10);
                p += 0x38;
            } while (p < &D_800B60A8 + 0x8C0);
        }
    }
    if (!(flags & 0x40)) {
        p = &D_800B6968;
        if (p < &D_800B6968 + 0xE00) {
            do {
                func_8001D388(p, &sp10);
                p += 0x38;
            } while (p < &D_800B6968 + 0xE00);
        }
    }
    if (!(flags & 0x80)) {
        p = &D_800B7768;
        if (p < &D_800B7768 + 0x1C70) {
            do {
                func_8001D388(p, &sp10);
                p += 0x38;
            } while (p < &D_800B7768 + 0x1C70);
        }
    }
}

extern void (*D_8006351C[])(void *);

void func_8001D388(void *param_1)
{
    if ((*(s32 *)((char *)param_1 + 4) >= 0) &&
        (*(s32 *)((char *)param_1 + 0x20) != 0) &&
        (*(u16 *)param_1 == 2) &&
        (*(u16 *)((char *)param_1 + 2) < 11)) {
        D_8006351C[*(u16 *)((char *)param_1 + 2)](param_1);
    }
}


/* POLY_FT4 sprite-strip builder: walks a 12-byte record list at arg0+0x20, pulls
 * 0x28-byte prims off the D_800A5E60 bump allocator, builds tpage/clut/UVs with
 * X/Y flip, calls func_8001D8C4, and addPrim's each prim into the OT slot
 * &((PTag *)(D_800A6610 + (D_800B9A02 << 14)))[pri].
 *
 * Five levers were needed (see cookbook notes in the wave report):
 *  1. libgpu addPrim bitfield `struct { u32 addr:24; u32 len:8; }` -> hoists 0x00FFFFFF into $s7.
 *  2. ONE record pointer (not two): gcc's giv combination emits the `addiu $s2,$s3,3`
 *     preheader init and the -1/0/1/3 offsets off it.
 *  3. Chained store `*(u8 *)(cur+0x14) = *(u8 *)(cur+0x24) = u;` -> the SI->QI
 *     `addu $v0,$a0,$zero` before each sb pair, one copy shared across both flip arms.
 *  4. `ut` is a SINGLE-SET temp: birthing-boost (sched.c adjust_priority /
 *     birthing_insn_p, REG_N_SETS(dest)==1) sinks the sllv chain BELOW the
 *     `cur[7] |= abe` block, which is what the target does. Folding ut into ub
 *     (ub = expr; u = ub; ub = ub + w - 1) gives ub 3 sets, kills the boost, and
 *     schedules the whole u-chain before the abe block instead (closeness 31).
 *  5. `u`/`ub` are u16: the mode-changing copy `u = ut` is NOT a plain reg-reg copy,
 *     so cse/coalescing cannot propagate `ut` into u's later uses and delete it.
 *     That single instruction (`addu $a0,$v1,$zero`) is what fixes the whole
 *     $a0<->$v1 allocation of both the U and the V half. Same mechanism keeps the
 *     V-flip diamond's else arm (`addu $a0,$v1,$zero`) alive and shares `(u16)vy`
 *     across both arms.
 *  6. The explicit intermediate `tt` makes the U-half accumulator reuse $v1
 *     (`addu $v1,$v1,$v0`) instead of the dying rec[2] register $v0.
 */

typedef struct { u32 addr : 24; u32 len : 8; } PTag_8001D3FC;

extern u8 D_800A6610[];
extern u16 D_800B9A02;
extern u8 *D_800A5E60;

extern void func_8001D70C(s32 arg0);
extern void func_8001D8C4(s32 arg0, u8 *rec, u8 *prim);

void func_8001D3FC(s32 arg0)
{
    u32 pri;
    u32 attr;
    u8 *rec;
    PTag_8001D3FC *slot;
    u32 sc;
    s32 mode;
    s32 shift;
    u8 *cur;
    u16 id;
    u32 sx, sy;
    s32 xs;
    u16 vx, vy;
    s32 tpage;
    u16 u;
    u16 ub;
    s32 ut, vt;
    s32 tt;
    s32 clut;

    pri = *(u16 *)(arg0 + 0x2C) & 0x3FFF;
    if (pri < 0x1000) {
        attr = *(u32 *)(arg0 + 4);
        rec = *(u8 **)(arg0 + 0x20);
        sc = (u32)(u16)D_800B9A02;
        mode = (attr >> 24) & 3;
        shift = 2 - mode;
        slot = &((PTag_8001D3FC *)(D_800A6610 + (sc << 14)))[pri];
        func_8001D70C(arg0);
        do {
            cur = D_800A5E60;
            id = *(u16 *)rec;
            xs = *(s16 *)(rec + 4);
            sx = *(u16 *)(arg0 + 0x28) + (xs >> shift);
            vx = sx;
            sy = *(u16 *)(arg0 + 0x2A) + *(u16 *)(rec + 6);
            vy = sy;
            D_800A5E60 = cur + 0x28;
            *(u8 *)(cur + 3) = 9;
            *(u8 *)(cur + 7) = 0x2C;
            if (attr & 0x40000000) {
                *(u8 *)(cur + 7) = 0x2E;
                tpage = (mode << 7) | (((attr >> 28) & 3) << 5) |
                        ((sy & 0x100) >> 4) | ((sx & 0x3C0) >> 6) |
                        ((sy & 0x200) << 2);
            } else {
                tpage = (mode << 7) | (1 << 5) |
                        ((sy & 0x100) >> 4) | ((sx & 0x3C0) >> 6) |
                        ((sy & 0x200) << 2);
            }
            *(s16 *)(cur + 0x16) = tpage;
            *(u8 *)(cur + 7) |= (attr & 0x40) >> 6;

            ut = (vx - ((tpage & 0xF) << 6)) << shift;
            u = ut;
            tt = ut + *(u8 *)(rec + 2);
            ub = tt - 1;
            if ((u16)ub >= 0x100) {
                ub = 0xFF;
            }
            if (id & 0x100) {
                *(u8 *)(cur + 0x14) = *(u8 *)(cur + 0x24) = u;
                *(u8 *)(cur + 0x0C) = *(u8 *)(cur + 0x1C) = ub;
            } else {
                *(u8 *)(cur + 0x0C) = *(u8 *)(cur + 0x1C) = u;
                *(u8 *)(cur + 0x14) = *(u8 *)(cur + 0x24) = ub;
            }

            vt = vy;
            if (tpage & 0x10) {
                u = vt - 0x100;
            } else {
                u = vt;
            }
            ub = u + *(u8 *)(rec + 3) - 1;
            if ((u16)ub >= 0x100) {
                ub = 0xFF;
            }
            if (id & 0x200) {
                *(u8 *)(cur + 0x1D) = *(u8 *)(cur + 0x25) = u;
                *(u8 *)(cur + 0x0D) = *(u8 *)(cur + 0x15) = ub;
            } else {
                *(u8 *)(cur + 0x0D) = *(u8 *)(cur + 0x15) = u;
                *(u8 *)(cur + 0x1D) = *(u8 *)(cur + 0x25) = ub;
            }

            clut = ((*(u8 *)(arg0 + 0x27) + 0x100) << 6) |
                   ((*(u8 *)(arg0 + 0x27) < 0xE0) ? 0x16 : 0x10);
            *(s16 *)(cur + 0xE) = clut;
            *(u8 *)(cur + 4) = *(u8 *)(arg0 + 0x24);
            *(u8 *)(cur + 5) = *(u8 *)(arg0 + 0x25);
            *(u8 *)(cur + 6) = *(u8 *)(arg0 + 0x26);
            func_8001D8C4(arg0, rec, cur);

            ((PTag_8001D3FC *)cur)->addr = slot->addr;
            slot->addr = (u32)cur;
            rec += 0xC;
        } while ((id & 0xFF) != 0xFF);
    }
}

void func_8001D70C(s32 param_1)
{
    s32 matrix[8];  /* sp+0x10 */
    s16 sc[20];     /* sp+0x30 */

    func_8004978C((s16 *)(param_1 + 0x10), (void *)matrix);

    /* build the diagonal scale matrix at sp+0x30 */
    sc[0] = *(u16 *)(param_1 + 0x18);
    sc[1] = 0;
    sc[2] = 0;
    sc[3] = 0;
    sc[4] = *(u16 *)(param_1 + 0x1A);
    sc[5] = 0;
    sc[6] = 0;
    sc[7] = 0;
    sc[8] = 0x1000;

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 0x30;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 0x32;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, $sp, 0x12;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 0x34;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, $sp, 0x14;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        : : "r"((s32)matrix) : "$12", "$13", "$14", "$2", "memory");

    *(s32 *)((u8 *)matrix + 0x14) = *(s16 *)(param_1 + 8);
    *(s32 *)((u8 *)matrix + 0x18) = *(s16 *)(param_1 + 10);
    *(s32 *)((u8 *)matrix + 0x1C) = *(s16 *)(param_1 + 12);

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "lw $12, 20(%0);"
        "lw $13, 24(%0);"
        "ctc2 $12, $5;"
        "lw $14, 28(%0);"
        "ctc2 $13, $6;"
        "ctc2 $14, $7"
        : : "r"((s32)matrix) : "$12", "$13", "$14", "$2");
}


/* ---- PsyQ GTE inline macros (same spelling as func_8001F730 / ov_SC03_* / 800.c gte_ldv0) ---- */
#define LDV0_8001D8C4(r0) __asm__ volatile (             \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define MVMVA_8001D8C4() __asm__ volatile (              \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 0, 0"                                \
    : : : "memory" )

#define STMAC123_8001D8C4(r0) __asm__ volatile (         \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

void func_8001D8C4(s32 a0, u8 * a1_p, u8 * a2_p) {
    s32 a1 = (s32)a1_p;
    s32 a2 = (s32)a2_p;
    s16 sv[4][4];   /* 4 SVECTORs: sp+0x00..0x1F */
    s32 out[4];     /* MAC1/2/3 scratch: sp+0x20..0x2F */
    s32 cx, cy, dx, dy, z;

    cx = *(u16 *)(a0 + 0x2E) + *(u16 *)(a1 + 0x08);
    cy = *(u16 *)(a0 + 0x30) + *(u16 *)(a1 + 0x0A);
    sv[0][0] = sv[2][0] = cx;
    sv[0][1] = sv[1][1] = cy;

    dx = *(u8 *)(a1 + 0x02) + cx;
    sv[3][0] = dx;
    sv[1][0] = dx;

    dy = *(u8 *)(a1 + 0x03) + cy;
    sv[3][1] = dy;
    sv[2][1] = dy;

    z = *(u16 *)(a0 + 0x32);
    sv[3][2] = z;
    sv[2][2] = z;
    sv[1][2] = z;
    sv[0][2] = z;

    LDV0_8001D8C4(sv[0]);
    MVMVA_8001D8C4();
    STMAC123_8001D8C4(out);
    *(s16 *)(a2 + 0x08) = out[0];
    *(s16 *)(a2 + 0x0A) = out[1];

    LDV0_8001D8C4(sv[1]);
    MVMVA_8001D8C4();
    STMAC123_8001D8C4(out);
    *(s16 *)(a2 + 0x10) = out[0];
    *(s16 *)(a2 + 0x12) = out[1];

    LDV0_8001D8C4(sv[2]);
    MVMVA_8001D8C4();
    STMAC123_8001D8C4(out);
    *(s16 *)(a2 + 0x18) = out[0];
    *(s16 *)(a2 + 0x1A) = out[1];

    LDV0_8001D8C4(sv[3]);
    MVMVA_8001D8C4();
    STMAC123_8001D8C4(out);
    *(s16 *)(a2 + 0x20) = out[0];
    *(s16 *)(a2 + 0x22) = out[1];
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001DA34);


extern u8 D_800AF648;

void func_8001E094(s32 arg0)
{
    s16 sc[16];
    s16 res[16];
    s32 g;
    s32 t;

    sc[0] = *(u16 *)(arg0 + 0x18);
    sc[1] = 0;
    sc[2] = 0;
    sc[3] = 0;
    sc[4] = *(u16 *)(arg0 + 0x1A);
    sc[5] = 0;
    sc[6] = 0;
    sc[7] = 0;
    sc[8] = *(u16 *)(arg0 + 0x1C);

    g = (s32)&D_800AF648;

    /* gte_SetRotMatrix(obj->mat) */
    __asm__ __volatile__(
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"(*(s32 *)(arg0 + 0x34)) : "$12", "$13", "$14", "memory");

    /* res = obj->mat * sc, column by column */
    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)sc) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)sc + 2) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res + 2) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)sc + 4) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res + 4) : "$12", "$13", "$14", "memory");

    *(s32 *)((u8 *)res + 0x14) = *(s32 *)(*(s32 *)(arg0 + 0x34) + 0x14);
    *(s32 *)((u8 *)res + 0x18) = *(s32 *)(*(s32 *)(arg0 + 0x34) + 0x18);
    *(s32 *)((u8 *)res + 0x1C) = *(s32 *)(*(s32 *)(arg0 + 0x34) + 0x1C);

    /* gte_SetRotMatrix(&D_800AF648) */
    __asm__ __volatile__(
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)res) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)res + 2) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res + 2) : "$12", "$13", "$14", "memory");

    __asm__ __volatile__(
        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
        : : "r"((s32)res + 4) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
        : : "r"((s32)res + 4) : "$12", "$13", "$14", "memory");

    /* gte_SetTransMatrix(&D_800AF648) */
    __asm__ __volatile__(
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n"
        : : "r"(g) : "$12", "$13", "$14", "memory");

    t = (s32)res + 0x14;
    __asm__ __volatile__(
        "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
        "sll $13, $13, 16\n" "or $12, $12, $13\n"
        "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
        "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(t) : "$12", "$13", "memory");
    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n"
        : : "r"(t) : "memory");

    /* gte_SetRotMatrix(res) ; gte_SetTransMatrix(res) */
    __asm__ __volatile__(
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
        : : "r"((s32)res) : "$12", "$13", "$14", "memory");
    __asm__ __volatile__(
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n"
        : : "r"((s32)res) : "$12", "$13", "$14", "memory");
}

extern void func_8004978C(s16 *a0, void *a1);
extern u8 D_800AF648;

void func_8001E378(s32 param_1)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $29, $29, -96\n"
        "sw $16, 80($29)\n"
        "addu $16, $4, $0\n"
        "sw $17, 84($29)\n"
        "addiu $17, $29, 48\n"
        "addiu $4, $16, 16\n"
        "sw $31, 88($29)\n"
        "jal func_8004978C\n"
        "addu $5, $17, $0\n"
        "lhu $2, 24($16)\n"
        "sh $0, 18($29)\n"
        "sh $0, 20($29)\n"
        "sh $0, 22($29)\n"
        "sh $2, 16($29)\n"
        "lhu $2, 26($16)\n"
        "sh $0, 26($29)\n"
        "sh $0, 28($29)\n"
        "sh $0, 30($29)\n"
        "sh $2, 24($29)\n"
        "lhu $2, 28($16)\n"
        "lui $5, %hi(D_800AF648)\n"
        "addiu $5, $5, %lo(D_800AF648)\n"
        "sh $2, 32($29)\n"
        "lw $12, 0($17)\n"
        "lw $13, 4($17)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8($17)\n"
        "lw $13, 12($17)\n"
        "lw $14, 16($17)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        "addiu $2, $29, 16\n"
        "lhu $12, 0($2)\n"
        "lhu $13, 6($2)\n"
        "lhu $14, 12($2)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($17)\n"
        "sh $13, 6($17)\n"
        "sh $14, 12($17)\n"
        "addiu $2, $29, 18\n"
        "lhu $12, 0($2)\n"
        "lhu $13, 6($2)\n"
        "lhu $14, 12($2)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "addiu $4, $29, 50\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($4)\n"
        "sh $13, 6($4)\n"
        "sh $14, 12($4)\n"
        "addiu $2, $29, 20\n"
        "lhu $12, 0($2)\n"
        "lhu $13, 6($2)\n"
        "lhu $14, 12($2)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "addiu $3, $29, 52\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($3)\n"
        "sh $13, 6($3)\n"
        "sh $14, 12($3)\n"
        "lh $2, 8($16)\n"
        "nop\n"
        "sw $2, 68($29)\n"
        "lh $2, 10($16)\n"
        "nop\n"
        "sw $2, 72($29)\n"
        "lh $2, 12($16)\n"
        "nop\n"
        "sw $2, 76($29)\n"
        "lw $12, 0($5)\n"
        "lw $13, 4($5)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8($5)\n"
        "lw $13, 12($5)\n"
        "lw $14, 16($5)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        "lhu $12, 0($17)\n"
        "lhu $13, 6($17)\n"
        "lhu $14, 12($17)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($17)\n"
        "sh $13, 6($17)\n"
        "sh $14, 12($17)\n"
        "lhu $12, 0($4)\n"
        "lhu $13, 6($4)\n"
        "lhu $14, 12($4)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($4)\n"
        "sh $13, 6($4)\n"
        "sh $14, 12($4)\n"
        "lhu $12, 0($3)\n"
        "lhu $13, 6($3)\n"
        "lhu $14, 12($3)\n"
        "mtc2 $12, $9\n"
        "mtc2 $13, $10\n"
        "mtc2 $14, $11\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 3, 3, 0\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0($3)\n"
        "sh $13, 6($3)\n"
        "sh $14, 12($3)\n"
        "lw $12, 20($5)\n"
        "lw $13, 24($5)\n"
        "ctc2 $12, $5\n"
        "lw $14, 28($5)\n"
        "ctc2 $13, $6\n"
        "ctc2 $14, $7\n"
        "addiu $2, $29, 68\n"
        "lhu $13, 4($2)\n"
        "lhu $12, 0($2)\n"
        "sll $13, $13, 16\n"
        "or $12, $12, $13\n"
        "mtc2 $12, $0\n"
        "lwc2 $1, 8($2)\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        "swc2 $25, 0($2)\n"
        "swc2 $26, 4($2)\n"
        "swc2 $27, 8($2)\n"
        "lw $12, 0($17)\n"
        "lw $13, 4($17)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8($17)\n"
        "lw $13, 12($17)\n"
        "lw $14, 16($17)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        "lw $12, 20($17)\n"
        "lw $13, 24($17)\n"
        "ctc2 $12, $5\n"
        "lw $14, 28($17)\n"
        "ctc2 $13, $6\n"
        "ctc2 $14, $7\n"
        "lw $31, 88($29)\n"
        "lw $17, 84($29)\n"
        "lw $16, 80($29)\n"
        "addiu $29, $29, 96\n"
        ".set\treorder\n"
    );
}


/* ---- PsyQ GTE inline macros (same spelling as func_80016F18, this TU) ---- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

/* GTE input vertex: {vx, vy, vz, pad} */
typedef struct {
    /* 0x0 */ s16 vx;
    /* 0x2 */ s16 vy;
    /* 0x4 */ s16 vz;
    /* 0x6 */ s16 pad;
} GTESVec; /* 8 bytes */

/* GTE screen-space output slot: {xy; z; pad} */
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 pad;
} GTEOutV; /* 8 bytes */

s32 func_8001E668(s32 a0, s32 a1, GTEOutV *a2, s32 *a3)
{
    GTESVec v[4];
    s32 flag2;
    s32 otz;

    v[0].vx = *(u16 *)(a0 + 0x2E) + *(u16 *)(a1 + 0x8);
    v[0].vy = *(u16 *)(a0 + 0x30) + *(u16 *)(a1 + 0xA);
    v[1].vx = *(u16 *)(a0 + 0x2E) + *(u16 *)(a1 + 0x8) + *(u8 *)(a1 + 0x2);
    v[1].vy = *(u16 *)(a0 + 0x30) + *(u16 *)(a1 + 0xA);
    v[2].vx = *(u16 *)(a0 + 0x2E) + *(u16 *)(a1 + 0x8);
    v[2].vy = *(u16 *)(a0 + 0x30) + *(u16 *)(a1 + 0xA) + *(u8 *)(a1 + 0x3);
    v[3].vx = *(u16 *)(a0 + 0x2E) + *(u16 *)(a1 + 0x8) + *(u8 *)(a1 + 0x2);
    v[3].vy = *(u16 *)(a0 + 0x30) + *(u16 *)(a1 + 0xA) + *(u8 *)(a1 + 0x3);
    v[0].vz = v[1].vz = v[2].vz = v[3].vz = *(u16 *)(a0 + 0x32);

    gte_ldv3(&v[0], &v[1], &v[2]);
    gte_rtpt();
    gte_stflg(a3);
    gte_stsxy3(&a2[1].xy, &a2[2].xy, &a2[3].xy);

    gte_ldv0(&v[3]);
    gte_rtps();
    gte_stflg(&flag2);
    *a3 |= flag2;
    a2 += 4;
    gte_stsxy(&a2[0].xy);

    gte_avsz4();
    gte_stotz(&otz);

    return otz;
}


extern u16 D_800B9A02;
extern u8 D_800A6518[];
extern s32 func_80052460(s32 a0, s32 a1, s32 a2);

void func_8001E7E0(u8 *arg0)
{
    s32 buf[9];
    u16 ox, oy;
    u8 *otp;
    u8 *p;
    u32 attr;
    u32 pri;
    s32 shift;
    s32 mode;
    u32 sx, sy;
    u16 vx, vy;
    s32 vv;
    u16 tv;
    s32 tpage;
    u16 id;

    pri = *(u16 *)(arg0 + 0x2C) & 0x3FFF;
    if (pri < 0x1000) {
        p = *(u8 **)(arg0 + 0x20);
        ox = *(u16 *)(arg0 + 0x8);
        oy = *(u16 *)(arg0 + 0xA);
        attr = *(u32 *)(arg0 + 0x4);
        mode = (attr >> 24) & 3;
        shift = 2 - mode;
        otp = &D_800A6518[(u16)D_800B9A02 * 20];
        do {
            id = *(u16 *)p;
            sx = *(u16 *)(arg0 + 0x28) + (*(s16 *)(p + 4) >> shift);
            vx = sx;
            sy = *(u16 *)(arg0 + 0x2A) + *(u16 *)(p + 6);
            vy = sy;
            if (attr & 0x40000000) {
                tpage = (mode << 7) | (((attr >> 28) & 3) << 5) | ((sy & 0x100) >> 4) |
                        ((sx & 0x3C0) >> 6) | ((sy & 0x200) << 2);
            } else {
                tpage = (mode << 7) | (1 << 5) | ((sy & 0x100) >> 4) |
                        ((sx & 0x3C0) >> 6) | ((sy & 0x200) << 2);
            }
            buf[0] = attr;
            *(s16 *)((u8 *)buf + 0x04) =
                *(u16 *)(p + 8) + (ox + *(u16 *)(arg0 + 0x2E));
            *(s16 *)((u8 *)buf + 0x06) =
                *(u16 *)(p + 10) + (oy + *(u16 *)(arg0 + 0x30));
            *(s16 *)((u8 *)buf + 0x08) = *(u8 *)(p + 2);
            *(s16 *)((u8 *)buf + 0x0A) = *(u8 *)(p + 3);
            *(s16 *)((u8 *)buf + 0x0C) = tpage;
            *(u8 *)((u8 *)buf + 0x0E) = (vx - ((tpage & 0xF) << 6)) << shift;
            vv = vy;
            if (tpage & 0x10) {
                tv = vv - 0x100;
                *(u8 *)((u8 *)buf + 0x0F) = tv;
            } else {
                tv = vv;
                *(u8 *)((u8 *)buf + 0x0F) = tv;
            }
            *(s16 *)((u8 *)buf + 0x10) =
                (*(u8 *)(arg0 + 0x27) < 0xE0) ? 0x160 : 0x100;
            p += 12;
            *(s16 *)((u8 *)buf + 0x12) = *(u8 *)(arg0 + 0x27) + 0x100;
            *(u8 *)((u8 *)buf + 0x16) = 0x80;
            *(u8 *)((u8 *)buf + 0x15) = 0x80;
            *(u8 *)((u8 *)buf + 0x14) = 0x80;
            func_80052460((s32)buf, (s32)otp, (u16)pri);
        } while ((id & 0xFF) != 0xFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001EA14);

INCLUDE_ASM("asm/nonmatchings/800", func_8001EFE0);


/* func_8001F730 — rotate the four corners of a POLY_FT4-shaped primitive
 * (x/y pairs at +0x08, +0x10, +0x18, +0x20) about a u16 centre point (a1)
 * using the rotation matrix built by func_80020DA4(a0, &m).
 * Fully unrolled in the source: gcc-2.7.2 -O2 does not unroll loops. */

extern void func_80020DA4(s32 a0, s32 a1);

#define SRM_8001F730(r0) __asm__ volatile (              \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define LDV0_8001F730(r0) __asm__ volatile (             \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define RTV0_8001F730() __asm__ volatile (               \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 3, 0"                                \
    : : : "memory" )

#define STLVNL_8001F730(r0) __asm__ volatile (           \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

void func_8001F730(s32 a0, void *a1, void *a2)
{
    s32  matrix[8];   /* sp+0x10 */
    s16  sv[4][4];    /* sp+0x30 */
    s32  out[4][4];   /* sp+0x50 */
    u16 *c = (u16 *)a1;
    u8  *p = (u8 *)a2;

    func_80020DA4(a0, (s32)matrix);
    SRM_8001F730(matrix);

    sv[0][0] = *(u16 *)(p + 0x08) - c[0];
    sv[0][1] = *(u16 *)(p + 0x0A) - c[1];
    sv[0][2] = 0;
    sv[1][0] = *(u16 *)(p + 0x10) - c[0];
    sv[1][1] = *(u16 *)(p + 0x12) - c[1];
    sv[1][2] = 0;
    sv[2][0] = *(u16 *)(p + 0x18) - c[0];
    sv[2][1] = *(u16 *)(p + 0x1A) - c[1];
    sv[2][2] = 0;
    sv[3][0] = *(u16 *)(p + 0x20) - c[0];
    sv[3][1] = *(u16 *)(p + 0x22) - c[1];
    sv[3][2] = 0;

    LDV0_8001F730(sv[0]);
    RTV0_8001F730();
    STLVNL_8001F730(out[0]);

    LDV0_8001F730(sv[1]);
    RTV0_8001F730();
    STLVNL_8001F730(out[1]);

    LDV0_8001F730(sv[2]);
    RTV0_8001F730();
    STLVNL_8001F730(out[2]);

    LDV0_8001F730(sv[3]);
    RTV0_8001F730();
    STLVNL_8001F730(out[3]);

    *(u16 *)(p + 0x08) = c[0] + out[0][0];
    *(u16 *)(p + 0x0A) = c[1] + out[0][1];
    *(u16 *)(p + 0x10) = c[0] + out[1][0];
    *(u16 *)(p + 0x12) = c[1] + out[1][1];
    *(u16 *)(p + 0x18) = c[0] + out[2][0];
    *(u16 *)(p + 0x1A) = c[1] + out[2][1];
    *(u16 *)(p + 0x20) = c[0] + out[3][0];
    *(u16 *)(p + 0x22) = c[1] + out[3][1];
}

void func_8001F974(void) {
}

void func_8001F97C(void *a0)
{
    extern void func_80020F34(s32 a0, s32 a1);
    s32 t1, t2, t3;

    func_80020DA4((s32)((u8 *)a0 + 0x10), (s32)((u8 *)a0 + 0x34));

    if (*(u16 *)((u8 *)a0 + 0x2C) & 0x10) {
        func_80020F34((s32)((u8 *)a0 + 0x34), (s32)((u8 *)a0 + 0x18));
    }

    t1 = *(s16 *)((u8 *)a0 + 0x08);
    t2 = *(s16 *)((u8 *)a0 + 0x0A);
    t3 = *(s16 *)((u8 *)a0 + 0x0C);
    *(s32 *)((u8 *)a0 + 0x48) = t1;
    *(s32 *)((u8 *)a0 + 0x4C) = t2;
    *(s32 *)((u8 *)a0 + 0x50) = t3;
    *(u16 *)((u8 *)a0 + 0x2C) |= 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001F9F8);

extern void (*D_80063500[])();

void func_8001FB8C(s32 *a0, s32 *a1)
{
    if (a0[1] < 0) return;
    if (*(u16 *)a0 != 1) return;
    if (*(u16 *)((u8 *)a0 + 2) < 9) {
        D_80063500[*(u16 *)((u8 *)a0 + 2)](a0);
        a1[0]++;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8001FC08);


/* func_80020248 — build the per-object rotation/translation matrices for a
 * NULL-terminated list of objects.  If the list is short (< 8 entries) the two
 * output matrix arrays live in the scratchpad (0x1F800000 / 0x1F8000E0) and the
 * function returns 1; otherwise they go to the main-RAM buffers D_80074818 /
 * D_80075018 and it returns 0.
 *
 * All the GTE work is the usual libgte inline-asm block set (SetRotMatrix /
 * MulMatrix0 column loop / SetTransMatrix / RotTrans). */

typedef struct {
    /* 0x00 */ s16 m[3][3];
    /* 0x14 */ s32 t[3];
} MTX_80020248; /* 0x20 */

typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 rot[3];
} OBJ_80020248; /* 0xC */

extern MTX_80020248 D_80074818[];
extern MTX_80020248 D_80075018[];

extern void func_80020DA4(s32 a0, s32 a1);

#define SRM_80020248(r0) __asm__ volatile (              \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define STM_80020248(r0) __asm__ volatile (              \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define LDCLMV_80020248(r0) __asm__ volatile (           \
    "lhu $12, 0( %0 );"                                  \
    "lhu $13, 6( %0 );"                                  \
    "lhu $14, 12( %0 );"                                 \
    "mtc2 $12, $9;"                                      \
    "mtc2 $13, $10;"                                     \
    "mtc2 $14, $11"                                      \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define RTIR_80020248() __asm__ volatile (               \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 3, 3, 0"                                \
    : : : "memory" )

#define STCLMV_80020248(r0) __asm__ volatile (           \
    "mfc2 $12, $9;"                                      \
    "mfc2 $13, $10;"                                     \
    "mfc2 $14, $11;"                                     \
    "sh $12, 0( %0 );"                                   \
    "sh $13, 6( %0 );"                                   \
    "sh $14, 12( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14", "memory" )

#define LDLVL_80020248(r0) __asm__ volatile (            \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define RT_80020248() __asm__ volatile (                 \
    "nop;"                                               \
    "nop;"                                               \
    "mvmva 1, 0, 0, 0, 0"                                \
    : : : "memory" )

#define STLVNL_80020248(r0) __asm__ volatile (           \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

s32 func_80020248(s32 *a0, OBJ_80020248 *a1, MTX_80020248 *a2, MTX_80020248 *a3, s32 a4)
{
    MTX_80020248 lm;            /* sp+0x10 */
    MTX_80020248 *rm;
    MTX_80020248 *om;
    u32 w;
    s32 n;
    s32 ret;

    ret = 0;
    n = 0;
    while (*a0++ != 0) {
        n++;
    }

    if (n >= 8) {
        rm = D_80074818;
        om = D_80075018;
    } else {
        rm = (MTX_80020248 *)0x1F800000;
        om = (MTX_80020248 *)0x1F8000E0;
        ret = 1;
    }

    while (--n != -1) {
        func_80020DA4((s32)a1->rot, (s32)&lm);

        w = a1->xy;
        lm.t[0] = w & 0xFFFF;
        lm.t[1] = w >> 16;
        lm.t[2] = a1->z;

        if (a4 == 0) {
            SRM_80020248(a2);
            LDCLMV_80020248(&lm.m[0][0]);
            RTIR_80020248();
            STCLMV_80020248(&rm->m[0][0]);
            LDCLMV_80020248(&lm.m[0][1]);
            RTIR_80020248();
            STCLMV_80020248(&rm->m[0][1]);
            LDCLMV_80020248(&lm.m[0][2]);
            RTIR_80020248();
            STCLMV_80020248(&rm->m[0][2]);
            rm++;
        }

        SRM_80020248(a3);
        LDCLMV_80020248(&lm.m[0][0]);
        RTIR_80020248();
        STCLMV_80020248(&om->m[0][0]);
        LDCLMV_80020248(&lm.m[0][1]);
        RTIR_80020248();
        STCLMV_80020248(&om->m[0][1]);
        LDCLMV_80020248(&lm.m[0][2]);
        RTIR_80020248();
        STCLMV_80020248(&om->m[0][2]);

        STM_80020248(a3);
        LDLVL_80020248(&lm.t[0]);
        RT_80020248();
        STLVNL_80020248(&om->t[0]);

        om++;
        a1++;
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80020598);

INCLUDE_ASM("asm/nonmatchings/800", func_80020A28);

INCLUDE_ASM("asm/nonmatchings/800", func_80020DA4);


/* func_80020F34 — handwritten GTE routine (PSYQ libgte-class ScaleMatrix-style op).
 * a0 = MATRIX* (3x3 short matrix, rows at +0x0/+0x6/+0xC/... , 3 columns per row),
 * a1 = SVECTOR-like short[3] scale vector.
 * Column-by-column: IR0=a1[col], IR1..3 = a0 column; GPF sf=1 computes
 * (IR0*IR1..3)>>12, results written back into the same column of a0.
 * Software-pipelined by hand: each column's input loads are issued right after the
 * previous column's GPF (to hide its latency) before that column's result is read back. */

void func_80020F34(s32 a0, s32 a1)
{
    __asm__ __volatile__(
        "lh $8, 0(%1)\n"
        "lh $9, 0(%0)\n"
        "lh $10, 6(%0)\n"
        "lh $11, 12(%0)\n"
        "mtc2 $8, $8\n"
        "mtc2 $9, $9\n"
        "mtc2 $10, $10\n"
        "mtc2 $11, $11\n"
        "nop\n"
        "nop\n"
        "gpf 1\n"

        "lh $8, 2(%1)\n"
        "lh $9, 2(%0)\n"
        "lh $10, 8(%0)\n"
        "lh $11, 14(%0)\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 0(%0)\n"
        "sh $13, 6(%0)\n"
        "sh $14, 12(%0)\n"
        "mtc2 $8, $8\n"
        "mtc2 $9, $9\n"
        "mtc2 $10, $10\n"
        "mtc2 $11, $11\n"
        "nop\n"
        "nop\n"
        "gpf 1\n"

        "lh $8, 4(%1)\n"
        "lh $9, 4(%0)\n"
        "lh $10, 10(%0)\n"
        "lh $11, 16(%0)\n"
        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 2(%0)\n"
        "sh $13, 8(%0)\n"
        "sh $14, 14(%0)\n"
        "mtc2 $8, $8\n"
        "mtc2 $9, $9\n"
        "mtc2 $10, $10\n"
        "mtc2 $11, $11\n"
        "nop\n"
        "nop\n"
        "gpf 1\n"

        "mfc2 $12, $9\n"
        "mfc2 $13, $10\n"
        "mfc2 $14, $11\n"
        "sh $12, 4(%0)\n"
        "sh $13, 10(%0)\n"
        "sh $14, 16(%0)\n"
        :
        : "r"(a0), "r"(a1)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "memory");
}


extern void func_80028620(s32 a0, void *a1);

void func_80021008(void *a0)
{
    void *s0 = a0;
    func_80028620(0, s0);
    func_80028620(1, (u8 *)s0 + 0x10);
    func_80028620(2, (u8 *)s0 + 0x20);
}


extern void func_80028620(s32 a0, void *a1);
extern u8 D_800A5E88;

void func_80021050(void) {
    u8 *s0 = &D_800A5E88;
    func_80028620(0, s0);
    func_80028620(1, s0 + 0x10);
    func_80028620(2, s0 + 0x20);
}

extern void func_800491FC(s32 a0, s32 a1, s32 a2);

void func_8002109C(s32 a0, s16 **a1)
{
    s16 *v1 = *a1;

    if (v1[3] == -2) {
        func_800491FC(v1[0], v1[1], v1[2]);
        return;
    }
    if (a0 == v1[3]) {
        func_800491FC(v1[0], v1[1], v1[2]);
        *a1 += 4;
    }
}


extern s16 D_800AE7E0;
extern s16 D_800AE7E2;
extern s16 D_800AE7E4;

extern void func_80053AF8(s32 a0, s32 a1, s32 a2);

void func_80021120(s32 *arg0) {
    func_80053AF8(D_800AE7E0, D_800AE7E2, D_800AE7E4);
    *arg0 = *arg0 + 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80021174);

INCLUDE_ASM("asm/nonmatchings/800", func_80021284);

INCLUDE_ASM("asm/nonmatchings/800", func_800215F4);

INCLUDE_ASM("asm/nonmatchings/800", func_80021D38);

INCLUDE_ASM("asm/nonmatchings/800", func_800221A8);

INCLUDE_ASM("asm/nonmatchings/800", func_800226C0);


extern u8 *D_800A5E60;

void func_80023138(s32 *arg0, u8 *col, u8 *pts, u32 *ot)
{
    s32 frame_pad[12];
    u32 flags;
    u8 *p;
    s32 i;
    u32 maskAddr;
    u32 maskLen;
    u8 code;
    register u32 x __asm__("$3");
    u32 y;
    s32 h;
    register s32 *zp __asm__("$4");

    (void)&frame_pad;

    p = D_800A5E60;
    flags = arg0[1];
    D_800A5E60 = p + 0x1B0;
    code = (flags & 0x40000000) ? 0x3A : 0x38;

    i = 0;
    maskAddr = 0x00FFFFFF;
    maskLen = 0xFF000000;

    do {
        p[0x03] = 8;
        p[0x07] = code;
        p[0x04] = col[4];
        p[0x05] = col[5];
        p[0x06] = col[6];
        p[0x0C] = col[4];
        p[0x0D] = col[5];
        p[0x0E] = col[6];
        p[0x14] = col[0];
        p[0x15] = col[1];
        p[0x16] = col[2];
        p[0x1C] = col[0];
        p[0x1D] = col[1];
        p[0x1E] = col[2];
        *(u16 *)(p + 0x08) = *(u16 *)(pts + i * 4 + 0x4C);
        *(u16 *)(p + 0x0A) = *(u16 *)(pts + i * 4 + 0x4E);
        *(u16 *)(p + 0x10) = *(u16 *)(pts + i * 4 + 0x50);
        *(u16 *)(p + 0x12) = *(u16 *)(pts + i * 4 + 0x52);
        *(u16 *)(p + 0x18) = *(u16 *)(pts + i * 4 + 0x04);
        *(u16 *)(p + 0x1A) = *(u16 *)(pts + i * 4 + 0x06);
        *(u16 *)(p + 0x20) = *(u16 *)(pts + i * 4 + 0x08);
        *(u16 *)(p + 0x22) = *(u16 *)(pts + i * 4 + 0x0A);
        h = i >> 1;
        i++;
        zp = (s32 *)((h << 2) + (u32)pts);
        x = *(u32 *)p;
        y = ot[zp[13]];
        x &= maskLen;
        y &= maskAddr;
        x |= y;
        *(u32 *)p = x;
        ot[zp[13]] = (ot[zp[13]] & maskLen) | ((u32)p & maskAddr);
        p += 0x24;
    } while (i < 12);

    *(u16 *)(p - 0x14) = *(u16 *)(pts + 0x4C);
    *(u16 *)(p - 0x12) = *(u16 *)(pts + 0x4E);
    *(u16 *)(p - 0x04) = *(u16 *)(pts + 0x04);
    *(u16 *)(p - 0x02) = *(u16 *)(pts + 0x06);

    if (flags & 0x40000000) {
        u8 *r;
        register s32 j __asm__("$11");
        u32 e1;
        register u32 mA __asm__("$9");
        register u32 mL __asm__("$10");
        u8 one;

        r = p;
        j = 0;
        one = 1;
        e1 = ((flags >> 23) & 0x60) | 0xE1000000;
        mA = 0x00FFFFFF;
        mL = 0xFF000000;
        D_800A5E60 = D_800A5E60 + 0x60;
        do {
            h = j >> 1;
            j++;
            zp = (s32 *)((h << 2) + (u32)pts);
            r[0x03] = one;
            *(u32 *)(r + 4) = e1;
            x = *(u32 *)r;
            y = ot[zp[13]];
            x &= mL;
            y &= mA;
            x |= y;
            *(u32 *)r = x;
            ot[zp[13]] = (ot[zp[13]] & mL) | ((u32)r & mA);
            r += 8;
        } while (j < 12);
    }
}


extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */

typedef struct {
    u16 x;
    u16 y;
} Poly12Pt;

typedef struct {
    u8 pad_00[0x10];
    Poly12Pt pts[12];
} Poly12Obj;

/* Builds a 12-gon of radius a1 into the u16{x,y} table at obj+0x10:
 * quarter arc (4 pts, angle step 0x155), mirrored in y, then in x. */
void func_800233CC(Poly12Obj *a0, u16 a1) {
    s32 i = 0;
    s32 radius = a1;

    /* `i * 0x155` must stay a DERIVED induction variable (no explicit `ang`
     * local): loop_strength_reduce then emits its preheader init alongside the
     * hoisted &pts[0] copy, giving the target's s2-before-s1 init order and the
     * s1-before-s0 increment order.  An explicit pre-loop `ang = 0` statement
     * sits ahead of the LSR-inserted init instead -> 6-instruction residual. */
    for (; i < 4; i++) {
        a0->pts[i].x = (func_8004787C(i * 0x155) * radius) >> 12;
        a0->pts[i].y = (func_80047948(i * 0x155) * radius) >> 12;
    }

    for (i = 4; i < 7; i++) {
        a0->pts[i].x = a0->pts[6 - i].x;
        a0->pts[i].y = -a0->pts[6 - i].y;
    }

    for (i = 7; i < 12; i++) {
        a0->pts[i].x = -a0->pts[12 - i].x;
        a0->pts[i].y = a0->pts[12 - i].y;
    }
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_800234E4(void *a0, u16 a1, u16 a2) {
    s32 k = 0;
    s32 rad = a1;

    /* Struct-free spelling of the func_800233CC sibling: the only dependencies
     * are common.h types and the two callee externs, so the body survives any
     * splice model (whole-snippet or function-only extraction).  Addresses are
     * written as a0 + k*4 + 0x10/0x12 so LSR keeps the incoming pointer as the
     * IV base (addu s1,a0,zero) and folds the member offset into the sh
     * displacements, exactly as the struct form did. */
    while (k < 12) {
        *(u16 *)((u8 *)a0 + k * 4 + 0x10) = (func_8004787C(a2 + k * 0x155) * rad) >> 12;
        *(u16 *)((u8 *)a0 + k * 4 + 0x12) = (func_80047948(a2 + k * 0x155) * rad) >> 12;
        k++;
    }
}


typedef struct { u32 addr : 24; u32 len : 8; } PTag_80023570;

extern u8 D_800A6610[];
extern u16 D_800B9A02;
extern u8 *D_800A5E60;
extern s32 GetTPage(s32, s32, s32, s32);
extern s32 func_8005A600(s32, s32, s32, s32, s32);

void func_80023570(s32 arg0)
{
    u32 *ot;
    register u32 flags __asm__("$5");
    u16 idx;
    PTag_80023570 *slot2;
    u8 *cur;
    u8 *nxt;

    {
        register u8 *rec0 __asm__("$8");
        register u8 *p __asm__("$7");
        register u16 addX __asm__("$14");
        register u16 addY __asm__("$13");
        register u8 code __asm__("$11");
        register u32 tagconst __asm__("$15");
        register u32 *slot __asm__("$10");
        register u32 maskAddr __asm__("$9");
        register u32 maskLen __asm__("$12");
        register u8 *rec3 __asm__("$6");
        register u8 *q __asm__("$4");
        register u32 sc __asm__("$2");
        u8 last;
        u32 x, y;
        u16 t16;

        rec0 = *(u8 **)(arg0 + 0x20);
        sc = (u32)(u16)D_800B9A02;
        p = D_800A5E60;
        flags = *(u32 *)(arg0 + 4);
        addX = *(u16 *)(arg0 + 8);
        addY = *(u16 *)(arg0 + 0xA);
        idx = *(u16 *)(arg0 + 0x2C);
        ot = (u32 *)(D_800A6610 + (sc << 14));
        code = (flags & 0x40000000) ? 0x62 : 0x60;
        tagconst = 0x03000000;
        sc = idx << 2;
        slot = (u32 *)(sc + (u32)ot);
        maskAddr = 0x00FFFFFF;
        maskLen = 0xFF000000;
        rec3 = rec0 + 3;
        q = p + 0xE;

        do {
            q[-7] = code;
            *(u32 *)p = tagconst;
            q[-0xA] = rec0[0];
            q[-9] = rec3[-2];
            q[-8] = rec3[-1];
            *(u16 *)(q - 6) = addX + *(u16 *)(rec3 + 1);
            cur = D_800A5E60;
            *(u16 *)(q - 4) = addY + *(u16 *)(rec3 + 3);
            t16 = *(u16 *)(rec3 + 5);
            rec0 += 0xC;
            *(u16 *)(q - 2) = t16;
            t16 = *(u16 *)(rec3 + 7);
            nxt = cur + 0x10;
            D_800A5E60 = nxt;
            *(u16 *)(q) = t16;
            q += 0x10;

            x = *(u32 *)p;
            y = *slot;
            x = x & maskLen;
            y = y & maskAddr;
            x = x | y;
            *(u32 *)p = x;
            x = (u32)p & maskAddr;
            p += 0x10;
            y = *slot;
            y = y & maskLen;
            y = y | x;
            *slot = y;

            last = rec3[0];
            rec3 += 0xC;
        } while (last == 0);
    }

    if (flags & 0x40000000) {
        s32 tp;

        D_800A5E60 = cur + 0x1C;
        tp = GetTPage(2, (flags >> 28) & 3, 0x280, 0);
        func_8005A600((s32)nxt, 0, 0, (u16)tp, 0);

        slot2 = (PTag_80023570 *)(((u32)idx << 2) + (u32)ot);
        ((PTag_80023570 *)nxt)->addr = slot2->addr;
        slot2->addr = (u32)nxt;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002374C);

INCLUDE_ASM("asm/nonmatchings/800", func_80023BF0);

INCLUDE_ASM("asm/nonmatchings/800", func_80024054);

INCLUDE_ASM("asm/nonmatchings/800", func_800241C0);

INCLUDE_ASM("asm/nonmatchings/800", func_800242D0);

extern s32 D_80078D88[];
extern s32 D_800A2B78;
extern void func_80026D64();
extern void func_80024448();

void func_800243EC(s32 *a0) {
    s32 v = *a0;

    D_80078D88[0] = v;
    D_800A2B78 = (v >> 28) & 7;

    if (v & 0x40) {
        func_80026D64();
    } else {
        func_80024448();
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80024448);

extern s32 D_800A2B78;

/* func_800249F0 — HANDWRITTEN assembly (splat marks it "Handwritten function").
 * Loop-carried state lives in $t1/$t2/$t5/$t6/$t8/$t9 with hand-placed latency
 * nops -- not reachable from gcc-2.7.2 codegen -- so the body is reproduced
 * verbatim as one .set noreorder asm block (same idiom as func_80027200 above);
 * gcc supplies only jr $ra + delay nop.
 *
 * Semantics: TMD F3 mesh emitter. Per face: RTPT 3 verts -> GTE flag cull ->
 * NCLIP cull -> store SXY0..2 -> AVSZ3 depth -> NCCS colour from normal p[0]
 * -> OT insert (tag code 0x04) -> if D_800A2B78 != 0 and the rgb word just
 * written has bit 1 set, append a 2-word semi-transparency primitive
 * (0xE100000A | ((D_800A2B78 & 3) << 5)) into the OT (tag code 0x01).
 * Returns the advanced packet pointer. */
long *func_800249F0(char *f, s32 verts, s32 norms, long *prim, s32 count,
                    s32 shift, s32 ot)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -8\n"
        "lw    $t5, 24($sp)\n"
        "lw    $t9, 28($sp)\n"
        "lw    $t8, 32($sp)\n"
        "beq   $t5, $zero, 3f\n"
        "addu  $t6, $a0, $zero\n"
        "addiu $t7, $sp, 4\n"
        "lui   $t3, 0xFF\n"
        "ori   $t3, $t3, 0xFFFF\n"
        "addiu $t2, $a0, 8\n"
        "addiu $t1, $a3, 4\n"
        "1:\n"
        "lhu   $a0, 2($t2)\n"
        "lhu   $v1, 4($t2)\n"
        "lhu   $v0, 6($t2)\n"
        "sll   $a0, $a0, 3\n"
        "addu  $a0, $a1, $a0\n"
        "sll   $v1, $v1, 3\n"
        "addu  $v1, $a1, $v1\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a1, $v0\n"
        "lwc2  $0, 0($a0)\n"
        "lwc2  $1, 4($a0)\n"
        "lwc2  $2, 0($v1)\n"
        "lwc2  $3, 4($v1)\n"
        "lwc2  $4, 0($v0)\n"
        "lwc2  $5, 4($v0)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "cfc2  $t4, $31\n"
        "nop\n"
        "sw    $t4, 0($sp)\n"
        "lw    $v0, 0($sp)\n"
        "addiu $v1, $zero, -0x1001\n"
        "and   $v0, $v0, $v1\n"
        "bne   $v0, $zero, 2f\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2  $24, 0($t7)\n"
        "lw    $v0, 4($sp)\n"
        "nop\n"
        "blez  $v0, 2f\n"
        "nop\n"
        "swc2  $12, 8($a3)\n"
        "swc2  $13, 12($a3)\n"
        "swc2  $14, 16($a3)\n"
        "nop\n"
        "nop\n"
        "avsz3\n"
        "swc2  $7, 0($t7)\n"
        "addiu $v0, $t6, 4\n"
        "lwc2  $6, 0($v0)\n"
        "lhu   $v0, 0($t2)\n"
        "nop\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a2, $v0\n"
        "lwc2  $0, 0($v0)\n"
        "lwc2  $1, 4($v0)\n"
        "nop\n"
        "nop\n"
        "nccs\n"
        "swc2  $22, 0($t1)\n"
        "lw    $v0, 4($sp)\n"
        "addiu $t1, $t1, 20\n"
        "srav  $v0, $v0, $t9\n"
        "sll   $v0, $v0, 2\n"
        "addu  $t0, $t8, $v0\n"
        "lw    $v1, 0($t0)\n"
        "lui   $v0, 0x400\n"
        "and   $v1, $v1, $t3\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t3\n"
        "sw    $v1, 0($a3)\n"
        "sw    $v0, 0($t0)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "nop\n"
        "beq   $v0, $zero, 2f\n"
        "addiu $a3, $a3, 20\n"
        "lbu   $v0, -17($t1)\n"
        "nop\n"
        "andi  $v0, $v0, 0x2\n"
        "beq   $v0, $zero, 2f\n"
        "lui   $a0, 0xE100\n"
        "ori   $a0, $a0, 0xA\n"
        "lw    $v1, 4($sp)\n"
        "addiu $v0, $zero, 1\n"
        "sb    $v0, -1($t1)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "srav  $v1, $v1, $t9\n"
        "sll   $v1, $v1, 2\n"
        "addu  $t0, $t8, $v1\n"
        "andi  $v0, $v0, 0x3\n"
        "sll   $v0, $v0, 5\n"
        "or    $v0, $v0, $a0\n"
        "sw    $v0, 0($t1)\n"
        "addiu $t1, $t1, 8\n"
        "lw    $v1, 0($t0)\n"
        "lui   $v0, 0x100\n"
        "and   $v1, $v1, $t3\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t3\n"
        "sw    $v1, 0($a3)\n"
        "addiu $a3, $a3, 8\n"
        "sw    $v0, 0($t0)\n"
        "2:\n"
        "addiu $t5, $t5, -1\n"
        "addiu $t2, $t2, 16\n"
        "bne   $t5, $zero, 1b\n"
        "addiu $t6, $t6, 16\n"
        "3:\n"
        "addu  $v0, $a3, $zero\n"
        "addiu $sp, $sp, 8\n"
        ".set\treorder\n"
    );
}


/* ---- PsyQ GTE inline macros (the subset this routine uses) --------------- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

/* ---- types --------------------------------------------------------------- */
typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_80024BC0;

typedef struct {
    u32 tag;                    /* 0x00 */
    u8  r0, g0, b0, code;       /* 0x04 */
    s16 x0, y0;                 /* 0x08 */
    s16 x1, y1;                 /* 0x0C */
    s16 x2, y2;                 /* 0x10 */
    s16 x3, y3;                 /* 0x14 */
} POLY_F4;                      /* 0x18 */

typedef struct {
    u32 tag;                    /* 0x00 */
    u32 code0;                  /* 0x04 */
} DR_MODE;                      /* 0x08 */

typedef struct {
    s32 unk00;                  /* 0x00 */
    u32 rgb;                    /* 0x04 */
    u16 n0;                     /* 0x08 */
    u16 v0;                     /* 0x0A */
    u16 v1;                     /* 0x0C */
    u16 v2;                     /* 0x0E */
    u16 v3;                     /* 0x10 */
    u16 pad;                    /* 0x12 */
} Face;                         /* 0x14 */

extern s32 D_800A2B78;

POLY_F4 *func_80024BC0(Face *f, SVECTOR_80024BC0 *sv, SVECTOR_80024BC0 *nv, POLY_F4 *poly0,
                       s32 n, s32 shift, u32 *ot)
{
    POLY_F4 *poly = poly0;
    s32 flag;
    s32 otz;
    u32 *p;

    if (n != 0) {
    do {
        gte_ldv3(&sv[f->v0], &sv[f->v1], &sv[f->v2]);
        gte_rtpt();
        gte_stflg(&flag);
        if ((flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_f4(poly);
                gte_ldv0(&sv[f->v3]);
                gte_rtps();
                gte_stflg(&flag);
                if ((flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy(&poly->x3);
                    gte_avsz4();
                    gte_stotz(&otz);
                    gte_ldrgb(&f->rgb);
                    gte_ldv0(&nv[f->n0]);
                    gte_nccs();
                    gte_strgb(&poly->r0);
                    p = &ot[otz >> shift];
                    poly->tag = (*p & 0x00FFFFFF) | 0x05000000;
                    *p = (u32)poly & 0x00FFFFFF;
                    poly++;
                    if (D_800A2B78 != 0 && (poly[-1].code & 2) != 0) {
                        s32 z = otz;
                        *((u8 *)poly + 3) = 1;
                        p = &ot[z >> shift];
                        *(u32 *)((u8 *)poly + 4) =
                            0xE100000A | ((D_800A2B78 & 3) << 5);
                        poly->tag = (*p & 0x00FFFFFF) | 0x01000000;
                        *p = (u32)poly & 0x00FFFFFF;
                        poly = (POLY_F4 *)((u8 *)poly + 8);
                    }
                }
            }
        }
        n--;
        f++;
    } while (n != 0);
    }
    return poly;
}


/* ---- PsyQ inline_c.h GTE macros ---- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                         \
    "lwc2 $1, 4( %0 );"                         \
    "lwc2 $2, 0( %1 );"                         \
    "lwc2 $3, 4( %1 );"                         \
    "lwc2 $4, 0( %2 );"                         \
    "lwc2 $5, 4( %2 )"                          \
    :                                           \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                         \
    "lwc2 $1, 4( %0 )"                          \
    :                                           \
    : "r"( r0 ) )

#define gte_ldrgb(r0) __asm__ volatile (        \
    "lwc2 $6, 0( %0 )"                          \
    :                                           \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (        \
    "cfc2 $12, $31;"                            \
    "nop;"                                      \
    "sw   $12, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (        \
    "swc2 $24, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (        \
    "swc2 $7, 0( %0 )"                          \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (        \
    "swc2 $22, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (    \
    "swc2 $12,  8( %0 );"                       \
    "swc2 $13, 16( %0 );"                       \
    "swc2 $14, 24( %0 )"                        \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )


extern s32 D_800A2B78;

u8 *func_80024DE8(TmdG3 *prim, u8 *vtx, u8 *nrm, u8 *pkt, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 z;
    u32 *otp;

    if (n != 0) {
        /* Identity no-op (emits nothing). It must sit in the loop PREHEADER (inside the
           `if (n != 0)`), not before the guard branch.
           Why: loop.c `record_initial`/`valid_initial_value_p` otherwise take the biv's
           initial value to be the raw incoming hard reg $a3, so the `pkt + 4` giv is
           emitted as `addiu giv,$a3,4`.  That keeps $a3 live past the parameter copy, so
           the pkt pseudo CONFLICTS with $a3 and can never live there (costing an extra
           `move`).  An asm_operands src makes valid_initial_value_p reject it, the giv is
           computed from the pseudo, and pkt keeps $a3.
           In the preheader it also stays clear of reorg's backward delay-slot scan, which
           breaks on any asm and would otherwise lose `addu $t5,$a0,$zero` from the guard's
           delay slot. */
        __asm__("" : "=r"(pkt) : "0"(pkt));
        do {
            gte_ldv3(vtx + prim->v0 * 8, vtx + prim->v1 * 8, vtx + prim->v2 * 8);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&z);
                if (z > 0) {
                    gte_stsxy3_g3(pkt);
                    gte_avsz3();
                    gte_stotz(&z);
                    gte_ldv0(nrm + prim->n0 * 8);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(pkt + 4);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(pkt + 0xC);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(pkt + 0x14);
                    pkt[7] = (pkt[7] & 2) | 0x30;
                    otp = ot + (z >> shift);
                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x6000000;
                    *otp = (u32)pkt & 0xFFFFFF;
                    pkt += 0x1C;
                    if (D_800A2B78 != 0) {
                        if (pkt[7 - 0x1C] & 2) {
                            otp = ot + (z >> shift);
                            pkt[3] = 1;
                            *(u32 *)(pkt + 4) = ((D_800A2B78 & 3) << 5) | 0xE100000A;
                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x1000000;
                            *otp = (u32)pkt & 0xFFFFFF;
                            pkt += 8;
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return pkt;
}


/* ------------------------------------------------------------------ *
 * func_80025000 — gouraud-quad (POLY_G4) transform + light + OT link.
 * GTE inline-asm dialect copied from the proven ov_SC03_099 TUs.
 * ------------------------------------------------------------------ */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC_80025000;    /* 0x08 */
typedef struct { u8  r, g, b, code; }   RGBC;    /* 0x04 */

typedef struct {            /* 0x20 — source quad description */
    u32  unk0;
    RGBC c0;
    RGBC c1;
    RGBC c2;
    RGBC c3;
    u16  n;
    u16  v0;
    u16  v1;
    u16  v2;
    u16  v3;
    u16  unk1E;
} SRCQ;

typedef struct {            /* 0x24 — POLY_G4 */
    u32  tag;
    RGBC c0;
    u32  xy0;
    RGBC c1;
    u32  xy1;
    RGBC c2;
    u32  xy2;
    RGBC c3;
    u32  xy3;
} PG4;

typedef struct { u32 tag; u32 code0; } DRM;      /* 0x08 */

extern s32 D_800A2B78;

PG4 *func_80025000(SRCQ *p, SVEC_80025000 *verts, SVEC_80025000 *norms, PG4 *poly0, s32 n,
                   s32 shift, u32 *ot)
{
    struct { s32 flag; s32 z; } g;
    u32 *otp;
    PG4 *prim;
    PG4 *poly = poly0;
    

    while (n != 0) {
        gte_ldv3(&verts[p->v0], &verts[p->v1], &verts[p->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if ((g.flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&g.z);
            if (g.z > 0) {
                gte_stsxy3_g4(poly);
                gte_ldv0(&verts[p->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if ((g.flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy(&poly->xy3);
                    gte_avsz4();
                    gte_stotz(&g.z);

                    gte_ldv0(&norms[p->n]);
                    gte_ldrgb(&p->c0);
                    gte_nccs();
                    gte_strgb(&poly->c0);
                    gte_ldrgb(&p->c1);
                    gte_nccs();
                    gte_strgb(&poly->c1);
                    gte_ldrgb(&p->c2);
                    gte_nccs();
                    gte_strgb(&poly->c2);
                    gte_ldrgb(&p->c3);
                    gte_nccs();
                    gte_strgb(&poly->c3);

                    poly->c0.code = (poly->c0.code & 2) | 0x38;

                    otp = &ot[g.z >> shift];
                    poly->tag = (*otp & 0xFFFFFF) | 0x08000000;
                    *otp = (u32)poly & 0xFFFFFF;

                    prim = poly;
                    poly = (PG4 *)((u8 *)poly + 0x24);

                    if (D_800A2B78 != 0) {
                        if ((prim->c0.code & 2) != 0) {
                            otp = &ot[g.z >> shift];
                            ((u8 *)poly)[3] = 1;
                            ((DRM *)poly)->code0 =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            ((DRM *)poly)->tag = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)poly & 0xFFFFFF;
                            poly = (PG4 *)((u8 *)poly + 8);
                        }
                    }
                }
            }
        }
        n--;
        p++;
    }
    return poly;
}


/* --- PsyQ inline_c.h GTE macros (verbatim bodies, project spelling) --- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_g3(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_80078D88[];
extern s32 D_800A2B78;

typedef struct { s16 vx, vy, vz, pad; } Vec8;
typedef struct {
    u32 unk0;
    u32 rgbc;
    u16 n0, v0, n1, v1, n2, v2;
} Prim;

u8 *func_8002528C(Prim *pr, Vec8 *vtx, Vec8 *nrm, void *arg3, s32 n, s32 shift, u32 *ot)
{
    struct { s32 flag, opz, sz1, sz2, sz3; } g;
    u8 *pk = (u8 *)arg3;
    u32 *otp;
    s32 z;

    if (n != 0) {
        do {
            gte_ldv3(&vtx[pr->v0], &vtx[pr->v1], &vtx[pr->v2]);
            gte_rtpt();
            gte_stflg(&g.flag);
            if (!(g.flag & ~0x1000)) {
                gte_nclip();
                gte_stopz(&g.opz);
                if (g.opz > 0) {
                    gte_stsxy3_g3(pk);
                    if (D_80078D88[0] & 0x8000) {
                        gte_stsz3(&g.sz1, &g.sz2, &g.sz3);
                        if (g.sz1 > g.sz2) {
                            z = g.sz1;
                            if (z < g.sz3) {
                                z = g.sz3;
                            }
                        } else {
                            z = g.sz2;
                            if (z < g.sz3) {
                                z = g.sz3;
                            }
                        }
                        g.opz = z >> 2;
                    } else {
                        gte_avsz3();
                        gte_stotz(&g.opz);
                    }
                    gte_ldrgb(&pr->rgbc);
                    gte_ldv3(&nrm[pr->n0], &nrm[pr->n1], &nrm[pr->n2]);
                    gte_ncct();
                    gte_strgb3_g3(pk);
                    otp = &ot[g.opz >> shift];
                    *(u32 *)pk = (*otp & 0xFFFFFF) | 0x6000000;
                    *otp = (u32)pk & 0xFFFFFF;
                    pk += 0x1C;
                    if (D_800A2B78 != 0 && (pk[-0x15] & 2)) {
                        otp = &ot[g.opz >> shift];
                        pk[3] = 1;
                        *(u32 *)(pk + 4) = 0xE100000A | ((D_800A2B78 & 3) << 5);
                        *(u32 *)pk = (*otp & 0xFFFFFF) | 0x1000000;
                        *otp = (u32)pk & 0xFFFFFF;
                        pk += 8;
                    }
                }
            }
            n--;
            pr++;
        } while (n != 0);
    }
    return pk;
}


/* func_80025504 - POLY_G4 mesh transform + OT insert (GTE, PsyQ inline macros).
 *
 * Two non-obvious constructs are REQUIRED for the byte match (both emit ZERO
 * instructions); do not "clean them up":
 *
 *  1) __asm__("" : "=r"(poly) : "0"(poly));
 *     loop.c:3509 valid_initial_value_p() accepts a HARD reg as a biv's initial
 *     value when no call intervenes, so gcc would emit the poly+4 giv init as
 *     `addiu giv,$a3,4` reading the INCOMING $a3.  That keeps hard $a3 live past
 *     the param copy, so the poly pseudo CONFLICTS with $7 (see .greg
 *     "75 conflicts: ... 7"), loses the copy-preference, and gcc emits a spurious
 *     `move t1,$a3`.  Re-tying poly through an empty asm makes the biv init_set
 *     src an ASM_OPERANDS -> valid_initial_value_p() fails -> the pseudo is used,
 *     $a3 dies at the param copy, poly gets $a3, the copy folds away.
 *
 *  2) register GFace *p0 __asm__("$4") = prim;  +  fp = p0;
 *     prim needs the OPPOSITE treatment: its giv init must read the hard $a0
 *     (`addiu $t1,$a0,0x14`), but its copy `addu $t6,$a0,$zero` must schedule
 *     AFTER the three stack-arg loads.  Assigning through an $a0-pinned local
 *     gives the copy a late LUID while keeping (reg 4) as the biv's initial value.
 */

/* ---- PsyQ-style inline GTE macros (inline_c.h shapes) ---------------------- */
#define gte_ldv0(r0)  __asm__ volatile("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(r0))
#define gte_ldv3(r0, r1, r2) __asm__ volatile(                              \
    "lwc2 $0, 0(%0);lwc2 $1, 4(%0);"                                        \
    "lwc2 $2, 0(%1);lwc2 $3, 4(%1);"                                        \
    "lwc2 $4, 0(%2);lwc2 $5, 4(%2)" : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldrgb(r0) __asm__ volatile("lwc2 $6, 0(%0)" : : "r"(r0))

#define gte_rtpt()  __asm__ volatile("nop;nop;cop2 0x0280030")
#define gte_rtps()  __asm__ volatile("nop;nop;cop2 0x0180001")
#define gte_nclip() __asm__ volatile("nop;nop;cop2 0x1400006")
#define gte_avsz4() __asm__ volatile("nop;nop;cop2 0x168002e")
#define gte_ncct()  __asm__ volatile("nop;nop;cop2 0x118043f")
#define gte_nccs()  __asm__ volatile("nop;nop;cop2 0x108041b")

#define gte_stflg(r0) __asm__ volatile("cfc2 $12, $31;nop;sw $12, 0(%0)" : : "r"(r0) : "$12", "memory")
#define gte_stopz(r0) __asm__ volatile("swc2 $24, 0(%0)" : : "r"(r0) : "memory")
#define gte_stotz(r0) __asm__ volatile("swc2 $7, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy2(r0) __asm__ volatile("swc2 $14, 0(%0)" : : "r"(r0) : "memory")
#define gte_strgb2(r0) __asm__ volatile("swc2 $22, 0(%0)" : : "r"(r0) : "memory")
#define gte_stsxy3_g4(r0) __asm__ volatile(                                 \
    "swc2 $12, 8(%0);swc2 $13, 16(%0);swc2 $14, 24(%0)" : : "r"(r0) : "memory")
#define gte_strgb3_g4(r0) __asm__ volatile(                                 \
    "swc2 $20, 4(%0);swc2 $21, 12(%0);swc2 $22, 20(%0)" : : "r"(r0) : "memory")
#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile(                         \
    "swc2 $16, 0(%0);swc2 $17, 0(%1);swc2 $18, 0(%2);swc2 $19, 0(%3)"       \
    : : "r"(r0), "r"(r1), "r"(r2), "r"(r3) : "memory")

/* ---- local types ----------------------------------------------------------- */
typedef struct {
    s16 vx, vy, vz, pad;
} GVec8; /* 0x08 */

typedef struct {
    s32 unk0;
    u32 rgb;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} GFace; /* 0x18 */

typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    u32 xy0;
    u32 rgb1;
    u32 xy1;
    u32 rgb2;
    u32 xy2;
    u32 rgb3;
    u32 xy3;
} GPolyG4; /* 0x24 */

typedef struct {
    u8 addr0, addr1, addr2, len;
    u32 code0;
} GDrMode; /* 0x08 */

extern s32 D_80078D88[];
extern s32 D_800A2B78;

void *func_80025504(GFace *prim, GVec8 *vtx, GVec8 *nrm, GPolyG4 *poly, s32 n, s32 shift,
                    u32 *ot)
{
    s32 flag;
    s32 p;
    s32 sz0, sz1, sz2, sz3;
    s32 zmax, ztmp;
    u32 *op;
    GDrMode *dm;
    GFace *fp;
    register GFace *p0 __asm__("$4") = prim;

    __asm__("" : "=r"(poly) : "0"(poly));
    fp = p0;
    for (; n != 0; n--, fp++) {
            gte_ldv3(&vtx[fp->v0], &vtx[fp->v1], &vtx[fp->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if (flag & 0xffffefff) {
                continue;
            }
            gte_nclip();
            gte_stopz(&p);
            if (p <= 0) {
                continue;
            }
            gte_stsxy3_g4(poly);
            gte_ldv0(&vtx[fp->v3]);
            gte_rtps();
            gte_stflg(&flag);
            if (flag & 0xffffefff) {
                continue;
            }
            gte_stsxy2(&poly->xy3);
            if (D_80078D88[0] & 0x8000) {
                gte_stsz4(&sz0, &sz1, &sz2, &sz3);
                zmax = sz2;
                if (zmax < sz3) {
                    zmax = sz3;
                }
                ztmp = sz0;
                if (ztmp < sz1) {
                    ztmp = sz1;
                }
                if (ztmp < zmax) {
                    ztmp = zmax;
                }
                p = ztmp >> 2;
            } else {
                gte_avsz4();
                gte_stotz(&p);
            }
            gte_ldrgb(&fp->rgb);
            gte_ldv3(&nrm[fp->n0], &nrm[fp->n1], &nrm[fp->n2]);
            gte_ncct();
            gte_strgb3_g4(poly);
            gte_ldv0(&nrm[fp->n3]);
            gte_nccs();
            gte_strgb2(&poly->rgb3);

            op = &ot[p >> shift];
            poly->tag = (*op & 0xffffff) | 0x08000000;
            *op = (u32)poly & 0xffffff;
            poly++;
            if (D_800A2B78 != 0) {
                if (poly[-1].code & 2) {
                    dm = (GDrMode *)poly;
                    op = &ot[p >> shift];
                    dm->len = 1;
                    dm->code0 = 0xe100000a | ((D_800A2B78 & 3) << 5);
                    *(u32 *)dm = (*op & 0xffffff) | 0x01000000;
                    *op = (u32)dm & 0xffffff;
                    poly = (GPolyG4 *)((u8 *)dm + 8);
                }
            }
    }
    return poly;
}


/* ---- PsyQ inline GTE macros ------------------------------------------------
 * Raw `.word` forms: include/gte_macros.inc is not on the standalone match_one
 * assembler path, so the cop2 opcodes are spelled as their encoded words, taken
 * verbatim from the target .s:
 *     rtpt 0x4A280030 · nclip 0x4B400006 · avsz3 0x4B58002D · nccs 0x4B08041B
 * Everything else is the stock PSY-Q 4.7 inline_c.h text (gte_stflg's $12 scratch
 * is exactly the target's `cfc2 $t4,$31`).
 * --------------------------------------------------------------------------- */
#define gte_ldv0(r0) __asm__ volatile (                  \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 );"                                  \
    "lwc2 $2, 0( %1 );"                                  \
    "lwc2 $3, 4( %1 );"                                  \
    "lwc2 $4, 0( %2 );"                                  \
    "lwc2 $5, 4( %2 )"                                   \
    :                                                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_ldrgb(r0) __asm__ volatile (                 \
    "lwc2 $6, 0( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )
#define gte_rtpt()  __asm__ volatile ("nop;nop;.word 0x4A280030")
#define gte_nclip() __asm__ volatile ("nop;nop;.word 0x4B400006")
#define gte_avsz3() __asm__ volatile ("nop;nop;.word 0x4B58002D")
#define gte_nccs()  __asm__ volatile ("nop;nop;.word 0x4B08041B")
#define gte_stflg(r0) __asm__ volatile (                 \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )
#define gte_stopz(r0) __asm__ volatile (                 \
    "swc2 $24, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_stotz(r0) __asm__ volatile (                 \
    "swc2 $7, 0( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_strgb(r0) __asm__ volatile (                 \
    "swc2 $22, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )
#define gte_stsxy3_g3(r0) __asm__ volatile (             \
    "swc2 $12, 8( %0 );"                                 \
    "swc2 $13, 16( %0 );"                                \
    "swc2 $14, 24( %0 )"                                 \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

/* 8-byte SVECTOR: vertex / normal table entry (index scaled by 8 => sll 3). */
typedef struct {
    s16 vx, vy, vz, pad;
} SVEC8_80025818;

/* 0x1C POLY_G3 packet (tag + 6 words => tag length nibble 0x06). */
typedef struct {
    u32 tag;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    u8  r1, g1, b1, pad1;
    s16 x1, y1;
    u8  r2, g2, b2, pad2;
    s16 x2, y2;
} PG3;

/* 0x1C TMD gouraud-3 (3 colours, no texture) primitive record. */
typedef struct {
    u32 hdr;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
} TPRIM_80025818;

extern s32 D_800A2B78;

PG3 *func_80025818(TPRIM_80025818 *prim, SVEC8_80025818 *vtx, SVEC8_80025818 *nrm, PG3 *poly,
                   s32 n, s32 shift, u32 *ot)
{
    s32 otz;
    s32 flag;
    u32 *otp;

    if (n != 0) {
        /* Zero-instruction launder of the `poly` biv's initial value.
         * Without it, loop.c's record_initial (loop.c:3454-3511) takes the biv's
         * initial value straight from the parameter copy `poly = $a3`, so the GIV
         * preheader init is emitted as `giv = (hard $a3) + 4`.  That keeps hard
         * $a3 live to the preheader, which makes the `poly` pseudo CONFLICT with
         * $a3 (dump: `75 conflicts: ... 7`), so $a3 goes to the GIV and `poly`
         * needs an extra `move`.  An asm_operands SET_SRC fails
         * valid_initial_value_p, so bl->initial_value stays the pseudo and $a3
         * stays free for `poly` -- byte-exact, 135 -> 134 instructions.
         * It MUST sit below the `n != 0` guard: above it the #APP/#NO_APP pair
         * blocks the `prim` parameter copy from hopping into the beqz delay slot
         * (cookbook RC-11). */
        __asm__ ("" : "=r"(poly) : "0"(poly));
        do {
            gte_ldv3(&vtx[prim->v0], &vtx[prim->v1], &vtx[prim->v2]);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&otz);
                if (otz > 0) {
                    gte_stsxy3_g3(poly);
                    gte_avsz3();
                    gte_stotz(&otz);
                    gte_ldv0(&nrm[prim->n0]);
                    gte_ldrgb(&prim->rgb0);
                    gte_nccs();
                    gte_strgb(&poly->r0);
                    gte_ldrgb(&prim->rgb1);
                    gte_nccs();
                    gte_strgb(&poly->r1);
                    gte_ldrgb(&prim->rgb2);
                    gte_nccs();
                    gte_strgb(&poly->r2);
                    poly->code = (poly->code & 2) | 0x30;
                    otp = ot + (otz >> shift);
                    *(u32 *)poly = (*otp & 0xFFFFFF) | 0x06000000;
                    *otp = (u32)poly & 0xFFFFFF;
                    poly++;
                    if (D_800A2B78 != 0) {
                        if (poly[-1].code & 2) {
                            /* 2-word DR_MODE packet chained in front of the G3 */
                            otp = ot + (otz >> shift);
                            *((u8 *)poly + 3) = 1;
                            *(u32 *)((u8 *)poly + 4) =
                                0xE100000A | ((D_800A2B78 & 3) << 5);
                            *(u32 *)poly = (*otp & 0xFFFFFF) | 0x01000000;
                            *otp = (u32)poly & 0xFFFFFF;
                            poly = (PG3 *)((u8 *)poly + 8);
                        }
                    }
                }
            }
            n--;
            prim++;
        } while (n != 0);
    }
    return poly;
}


/* func_80025A30 (main / src/800.c) -- TMD "quad, flat normal, gradation" emitter.
 * Per prim (stride 0x24): RTPT 3 verts -> flag/nclip cull -> RTPS 4th vert -> AVSZ4 -> 4x NCCS
 * (one shared normal, 4 base colours) -> POLY_G4 (code 0x38) -> OT insert (len 8).
 * If D_800A2B78 != 0 and the poly kept its bit-1 flag, a second 2-word 0xE100000A draw-mode
 * packet (len 1) is appended and linked into the same OT slot.
 *
 * MATCH 163/163. Two non-obvious levers (both were byte-decisive):
 *  1. ONE `pkt` pointer, not pkt+q. loop.c strength-reduces it into biv $a3 + giv($a3+4)=$t1;
 *     that is where the -0x21 / -0x1D style offsets come from. Writing an explicit `q = pkt+4`
 *     variable instead makes gcc build a THIRD register (giv q+3) -> +4 insns. Same for `prim`:
 *     one pointer -> biv $t3 + giv($a0+0x10)=$t2. (cookbook loop.md L1)
 *  2. The zero-byte `__asm__("" : "=r"(pkt) : "0"(pkt))` in the preheader. Without it loop.c's
 *     record_initial/valid_initial_value_p takes the biv's initial value from the HARD reg $a3
 *     (`addiu giv, a3, 4` reads hard a3 in the preheader), which keeps hard $a3 live past the
 *     param copy -> the pkt pseudo CONFLICTS with $a3 and can never be granted it: gcc then
 *     emits biv=$t1 / giv=$a3 plus an extra `move t1,a3` (164 ins, whole-loop register swap).
 *     A set whose SET_SRC is an asm_operands makes the initial value "complex" (loop.c:3509),
 *     so the giv init reads the PSEUDO, hard $a3 dies at the copy, and the biv wins $a3.
 *     It must sit INSIDE `if (n != 0)` so it lands in the preheader: an early `return` instead
 *     plants a CODE_LABEL that halts record_initial's backward scan for EVERY biv, which also
 *     robs `prim` of its hard-$a0 initial value (`addiu t2,t3,16` != `addiu t2,a0,0x10`).
 *  3. `o = &ot[z >> shift];` must precede `pkt[3] = 1;` -- the scheduler cannot hoist the
 *     `lw z` above an aliasing `sb`, so source order decides those 4 instructions (§175 lever A).
 *
 * PsyQ inline_c.h GTE macro bodies (same spelling as the matched
 * ov_SC01_000 renderer in src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c). */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_800A2B78;

u8 *func_80025A30(u8 *prim, u8 *vtx, u8 *nrm, u8 *pkt, s32 n, s32 shift, u32 *ot)
{
    long flag;
    long z;
    u32 *o;

    if (n != 0) {
    __asm__ volatile ("" : "=r"(pkt) : "0"(pkt));
    for (; n != 0; n--, prim += 0x24) {
        gte_ldv3(vtx + (*(u16 *)(prim + 0x16) << 3),
                 vtx + (*(u16 *)(prim + 0x1A) << 3),
                 vtx + (*(u16 *)(prim + 0x1E) << 3));
        gte_rtpt();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&z);
        if (z <= 0) {
            continue;
        }
        gte_stsxy3_g4(pkt);
        gte_ldv0(vtx + (*(u16 *)(prim + 0x22) << 3));
        gte_rtps();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(pkt + 0x20);
        gte_avsz4();
        gte_stotz(&z);

        gte_ldv0(nrm + (*(u16 *)(prim + 0x14) << 3));
        gte_ldrgb(prim + 0x4);
        gte_nccs();
        gte_strgb(pkt + 0x4);
        gte_ldrgb(prim + 0x8);
        gte_nccs();
        gte_strgb(pkt + 0xC);
        gte_ldrgb(prim + 0xC);
        gte_nccs();
        gte_strgb(pkt + 0x14);
        gte_ldrgb(prim + 0x10);
        gte_nccs();
        gte_strgb(pkt + 0x1C);

        pkt[7] = (pkt[7] & 2) | 0x38;

        o = &ot[z >> shift];
        *(u32 *)pkt = (*o & 0xFFFFFF) | 0x08000000;
        *o = (u32)pkt & 0xFFFFFF;
        pkt += 0x24;

        if (D_800A2B78 == 0) {
            continue;
        }
        if ((pkt[-0x1D] & 2) == 0) {
            continue;
        }
        o = &ot[z >> shift];
        pkt[3] = 1;
        *(u32 *)(pkt + 4) = ((D_800A2B78 & 3) << 5) | 0xE100000A;
        *(u32 *)pkt = (*o & 0xFFFFFF) | 0x01000000;
        *o = (u32)pkt & 0xFFFFFF;
        pkt += 8;
    }
    }
    return pkt;
}


/* Handwritten GTE polygon-transform loop (cookbook: handwritten inline-asm wrapper form).
 * The whole body is written in asm because the original is hand-written assembly: the
 * loop-carried values live in $t1/$t2/$t3/$t5/$t6/$t7/$t8/$t9 (gcc-2.7.2 would never
 * allocate caller-saved temporaries that way), and the two `lw 0x10($sp)` copies plus the
 * duplicated `sra $v0,$v1,2` on both arms of the min() are hand-scheduled.
 *
 * maspsx notes: `.set noreorder` must be the FIRST line so maspsx stops auto-filling
 * branch-delay slots / load-delay nops (we write every nop ourselves, exactly as in the
 * target), and `.set reorder` must be the LAST so the compiler-emitted `j $31` still gets
 * its delay-slot nop. All memory offsets are DECIMAL: maspsx int()s them.
 */

extern u32 D_8006387C;
extern s32 D_80078D88[];

void *func_80025CBC(void *prims, void *scr, void *cols, void *packets,
                    s32 count, s32 otshift, u32 *ot)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu $sp, $sp, -32\n"
        "lw $11, 48($sp)\n"
        "sw $17, 28($sp)\n"
        "lui $17, %hi(D_8006387C)\n"
        "addiu $17, $17, %lo(D_8006387C)\n"
        "sw $16, 24($sp)\n"
        "lw $16, 52($sp)\n"
        "lw $25, 56($sp)\n"
        "lwc2 $6, 0($17)\n"
        "beq $11, $0, .LfnEnd\n"
        "addu $2, $7, $0\n"
        "addiu $14, $sp, 4\n"
        "addiu $24, $sp, 8\n"
        "addiu $15, $sp, 12\n"
        "lui $13, 255\n"
        "ori $13, $13, 65535\n"
        "addiu $9, $4, 16\n"
        "addiu $10, $7, 4\n"
        ".LfnLoop:\n"
        "lhu $4, 2($9)\n"
        "lhu $3, 4($9)\n"
        "lhu $2, 6($9)\n"
        "sll $4, $4, 3\n"
        "addu $4, $5, $4\n"
        "sll $3, $3, 3\n"
        "addu $3, $5, $3\n"
        "sll $2, $2, 3\n"
        "addu $2, $5, $2\n"
        "lwc2 $0, 0($4)\n"
        "lwc2 $1, 4($4)\n"
        "lwc2 $2, 0($3)\n"
        "lwc2 $3, 4($3)\n"
        "lwc2 $4, 0($2)\n"
        "lwc2 $5, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "lw $2, -12($9)\n"
        "nop\n"
        "sw $2, 8($10)\n"
        "lw $2, -8($9)\n"
        "nop\n"
        "sw $2, 16($10)\n"
        "lw $2, -4($9)\n"
        "nop\n"
        "sw $2, 24($10)\n"
        "cfc2 $12, $31\n"
        "nop\n"
        "sw $12, 0($sp)\n"
        "lw $2, 0($sp)\n"
        "addiu $3, $0, -4097\n"
        "and $2, $2, $3\n"
        "bne $2, $0, .LfnNext\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2 $24, 0($14)\n"
        "lw $2, 4($sp)\n"
        "nop\n"
        "blez $2, .LfnNext\n"
        "nop\n"
        "swc2 $12, 8($7)\n"
        "swc2 $13, 16($7)\n"
        "swc2 $14, 24($7)\n"
        "lui $2, %hi(D_80078D88)\n"
        "lw $2, %lo(D_80078D88)($2)\n"
        "nop\n"
        "andi $2, $2, 32768\n"
        "beq $2, $0, .LfnAvsz\n"
        "addiu $2, $sp, 16\n"
        "swc2 $17, 0($24)\n"
        "swc2 $18, 0($15)\n"
        "swc2 $19, 0($2)\n"
        "lw $8, 8($sp)\n"
        "lw $3, 12($sp)\n"
        "nop\n"
        "slt $2, $3, $8\n"
        "beq $2, $0, .LfnMinB\n"
        "nop\n"
        "lw $4, 16($sp)\n"
        "j .LfnMinJ\n"
        "addu $3, $8, $0\n"
        ".LfnMinB:\n"
        "lw $4, 16($sp)\n"
        ".LfnMinJ:\n"
        "nop\n"
        "slt $2, $3, $4\n"
        "beq $2, $0, .LfnMinC\n"
        "sra $2, $3, 2\n"
        "addu $3, $4, $0\n"
        "sra $2, $3, 2\n"
        ".LfnMinC:\n"
        "j .LfnJoin\n"
        "sw $2, 4($sp)\n"
        ".LfnAvsz:\n"
        "nop\n"
        "nop\n"
        "avsz3\n"
        "swc2 $7, 0($14)\n"
        ".LfnJoin:\n"
        "lhu $2, 0($9)\n"
        "nop\n"
        "sll $2, $2, 3\n"
        "addu $2, $6, $2\n"
        "lwc2 $0, 0($2)\n"
        "lwc2 $1, 4($2)\n"
        "nop\n"
        "nop\n"
        "nccs\n"
        "swc2 $22, 0($10)\n"
        "lw $4, 4($sp)\n"
        "addiu $10, $10, 32\n"
        "srav $4, $4, $16\n"
        "sll $4, $4, 2\n"
        "addu $4, $25, $4\n"
        "lw $3, 0($4)\n"
        "lui $2, 1792\n"
        "and $3, $3, $13\n"
        "or $3, $3, $2\n"
        "and $2, $7, $13\n"
        "sw $3, 0($7)\n"
        "addiu $7, $7, 32\n"
        "sw $2, 0($4)\n"
        ".LfnNext:\n"
        "addiu $11, $11, -1\n"
        "bne $11, $0, .LfnLoop\n"
        "addiu $9, $9, 24\n"
        "addu $2, $7, $0\n"
        ".LfnEnd:\n"
        "lw $17, 28($sp)\n"
        "lw $16, 24($sp)\n"
        "addiu $sp, $sp, 32\n"
        ".set\treorder\n"
    );
}


/* func_80025EB8 — POLY_FT4 (0x28) mesh emitter, main / src/800.c   [MATCH 156/156]
 *
 * Per prim (0x20 bytes): RTPT the first 3 verts -> GTE flag cull -> NCLIP cull ->
 * RTPS the 4th vert -> flag cull -> depth (max(sz0..sz3)>>2 when D_80078D88 & 0x8000,
 * else AVSZ4) -> NCCS colour from the prim's normal -> OT insert (tag code 0x09).
 * Returns the advanced packet pointer.
 *
 * GTE ops are verbatim PsyQ inline_c.h macro bodies, spelled with the project gas
 * macros from include/gte_macros.inc (pulled in by common.h) — same idiom as the
 * already-matched func_8017BEBC family in the overlays.
 *
 * TWO NON-OBVIOUS LEVERS (both cost zero bytes, both were the whole residual):
 *
 * 1. `D_80078D88` is declared as an ARRAY, not a scalar.  gcc-2.7.2 alias.c refuses
 *    to reorder two memory refs only if they can conflict; its rule exempts a
 *    MEM_IN_STRUCT_P ref with a varying address from a NON-struct ref with a constant
 *    address.  With `extern s32 D_80078D88;` the global load is a plain scalar at a
 *    symbol_ref, so sched1 hoisted `lui/lw D_80078D88` above the `pkt->uv3` store and
 *    swallowed both load-delay nops (-2 insns).  An ARRAY_REF sets MEM_IN_STRUCT_P on
 *    the load, the exemption no longer applies, the pair is ordered, and the two nops
 *    come back exactly as in the target.
 *
 * 2. The packet cursor is a LOCAL (`pkt`) seeded from the parameter (`pkt0`), not the
 *    parameter itself.  loop.c's record_initial() takes the biv's initial_value from
 *    its last pre-loop set: with the parameter used directly that set is
 *    `(set P (reg:SI 7 a3))`, so the +4 giv's preheader init is emitted against the
 *    HARD register — which keeps $a3 live into the preheader and makes it CONFLICT
 *    with P (`;; 75 conflicts: ... 7` in .greg).  P then can never be granted $a3, so
 *    it took $t2, the giv took $a3, and the dead param copy `move t2,a3` survived
 *    (+1 insn, and every packet reference register-swapped).  Seeding a local makes
 *    initial_value a pseudo, $a3 dies at the param copy, the conflict disappears and
 *    the copy preference puts the cursor back in $a3.
 */

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_ft4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 16( %0 );"                         \
    "swc2 $14, 24( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                          \
    "swc2 $17, 0( %1 );"                          \
    "swc2 $18, 0( %2 );"                          \
    "swc2 $19, 0( %3 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) )

#define gte_strgb2(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_80025EB8;

typedef struct {
    u32 pad0;  /* 0x00 */
    u32 uv0;   /* 0x04 */
    u32 uv1;   /* 0x08 */
    u32 uv2;   /* 0x0C */
    u32 uv3;   /* 0x10 */
    u16 n0;    /* 0x14 */
    u16 v0;    /* 0x16 */
    u16 v1;    /* 0x18 */
    u16 v2;    /* 0x1A */
    u16 v3;    /* 0x1C */
    u16 pad1;  /* 0x1E */
} Prim20;

typedef struct {           /* libgpu POLY_FT4, 0x28 bytes */
    u32 tag;   /* 0x00 */
    u32 rgb;   /* 0x04 */
    u32 xy0;   /* 0x08 */
    u32 uv0;   /* 0x0C */
    u32 xy1;   /* 0x10 */
    u32 uv1;   /* 0x14 */
    u32 xy2;   /* 0x18 */
    u32 uv2;   /* 0x1C */
    u32 xy3;   /* 0x20 */
    u32 uv3;   /* 0x24 */
} Ft4;

extern u32 D_80063880;
extern s32 D_80078D88[];

u32 *func_80025EB8(Prim20 *prim, SVEC8_80025EB8 *verts, SVEC8_80025EB8 *norms, Ft4 *pkt0,
                   s32 n, s32 shift, u32 *ot)
{
    struct { long flag, otz, sz0, sz1, sz2, sz3; } g;
    s32 a, b;
    u32 *otp;
    Ft4 *pkt;

    pkt = pkt0;
    gte_ldrgb(&D_80063880);

    while (n != 0) {
        gte_ldv3(&verts[prim->v0], &verts[prim->v1], &verts[prim->v2]);
        gte_rtpt();
        pkt->uv0 = prim->uv0;
        pkt->uv1 = prim->uv1;
        pkt->uv2 = prim->uv2;
        gte_stflg(&g.flag);
        if (!(g.flag & 0xFFFFEFFF)) {
            gte_nclip();
            gte_stopz(&g.otz);
            if (g.otz > 0) {
                gte_stsxy3_ft4(pkt);
                gte_ldv0(&verts[prim->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & 0xFFFFEFFF)) {
                    gte_stsxy(&pkt->xy3);
                    pkt->uv3 = prim->uv3;
                    if (D_80078D88[0] & 0x8000) {
                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                        a = g.sz2;
                        if (a < g.sz3) a = g.sz3;
                        b = g.sz0;
                        if (b < g.sz1) b = g.sz1;
                        if (b < a) b = a;
                        g.otz = b >> 2;
                    } else {
                        gte_avsz4();
                        gte_stotz(&g.otz);
                    }
                    gte_ldv0(&norms[prim->n0]);
                    gte_nccs();
                    gte_strgb2(&pkt->rgb);
                    otp = &ot[g.otz >> shift];
                    pkt->tag = (*otp & 0xFFFFFF) | 0x09000000;
                    *otp = (u32)pkt & 0xFFFFFF;
                    pkt++;
                }
            }
        }
        n--;
        prim++;
    }

    return (u32 *)pkt;
}

typedef struct { s16 vx, vy, vz, pad; } SVEC8_80026128;

typedef struct {                                        /* 0x1C */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
} FaceGT3;

typedef struct {                                        /* 0x28 */
    u32 tag;
    u32 rgb0, xy0, uv0;
    u32 rgb1, xy1, uv1;
    u32 rgb2, xy2, uv2;
} PktGT3;

extern u32 D_80063884;

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb3_gt3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $20, 0( %0 );"                          \
    "swc2 $21, 0( %1 );"                          \
    "swc2 $22, 0( %2 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )             \
    : "memory" )

/* func_80026128 — main/800 — textured-GT3 (POLY_GT3) triangle emitter with per-vertex
 * normal-colour lighting. Sibling of the matched func_800262D8 in this TU (same loop
 * shape, same pkt->uvN = face->uvN copy); NOT a twin of the Gouraud-only func_800CBC2C.
 * Vertex type carries the function suffix per TU convention (cf. SVEC8_800262D8) since
 * gcc-2.7.2 rejects typedef redefinition and SVEC2 already exists at line 93. The SXY
 * store trio is written inline rather than as gte_stsxy3_gt3 because the TU already
 * binds that name to the 8/16/24 G3-shape macro further down (func_800277DC block);
 * offsets here are the true GT3 slot xy words 8/20/32. Splice: replace INCLUDE_ASM at
 * src/800.c:8983. Base macros above are byte-identical to the in-scope func_8002528C
 * block (lines 8001-8063); drop this duplicate set when pasting into the TU.
 *
 * NOTE: the target .s carries splat's "/* Handwritten function * /" marker (and marks
 * the bare `cfc2 $t4,$31` as a handwritten instruction). That label is a spimdisasm
 * heuristic firing on the raw cop2 discipline — the pinned cc1 REACHES all 108 words
 * from this C (oracle MATCH, repeatedly reproduced), unlike func_80027200 where the
 * same marker was genuine. If the whole-binary gate still refuses this byte-perfect
 * body, suspect the extract/prune layer special-casing Handwritten-marked .s files
 * (duplicate-symbol link), not this function's codegen. */
PktGT3 *func_80026128(FaceGT3 *face, SVEC8_80026128 *vtx, SVEC8_80026128 *nrm, PktGT3 *arg3,
                      s32 count, s32 shift, u32 *ot)
{
    long flag;
    long otz;
    u32 *otp;
    PktGT3 *pkt = arg3;

    gte_ldrgb(&D_80063884);

    while (count != 0) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        pkt->uv0 = face->uv0;
        pkt->uv1 = face->uv1;
        pkt->uv2 = face->uv2;
        gte_stflg(&flag);
        if (!(flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                __asm__ volatile (
                    "swc2 $12, 8( %0 );"
                    "swc2 $13, 20( %0 );"
                    "swc2 $14, 32( %0 )"
                    :
                    : "r"( pkt )
                    : "memory" );
                gte_avsz3();
                gte_stotz(&otz);
                gte_ldv3(&nrm[face->n0], &nrm[face->n1], &nrm[face->n2]);
                gte_ncct();
                otp = &ot[otz >> shift];
                pkt->tag = (*otp & 0x00FFFFFF) | 0x09000000;
                gte_strgb3_gt3(&pkt->rgb0, &pkt->rgb1, &pkt->rgb2);
                *otp = (u32)pkt & 0x00FFFFFF;
                pkt++;
            }
        }
        face++;
        count--;
    }
    return pkt;
}


/* func_800262D8 — main/800 — GT4 quad emitter with per-vertex normal-colour lighting.
 * GTE ops spelled as verbatim PsyQ inline_c.h macro bodies (project gas macros from
 * include/gte_macros.inc, pulled in via common.h -> include_asm.h -> macro.inc). */

#define gte_ldrgb(r0) __asm__ volatile (          \
    "lwc2 $6, 0( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv0(r0) __asm__ volatile (           \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 )"                            \
    :                                             \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (   \
    "lwc2 $0, 0( %0 );"                           \
    "lwc2 $1, 4( %0 );"                           \
    "lwc2 $2, 0( %1 );"                           \
    "lwc2 $3, 4( %1 );"                           \
    "lwc2 $4, 0( %2 );"                           \
    "lwc2 $5, 4( %2 )"                            \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (          \
    "cfc2 $12, $31;"                              \
    "nop;"                                        \
    "sw $12, 0( %0 )"                             \
    :                                             \
    : "r"( r0 )                                   \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (          \
    "swc2 $24, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (          \
    "swc2 $7, 0( %0 )"                            \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (          \
    "swc2 $14, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_stsxy3_gt4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                          \
    "swc2 $13, 20( %0 );"                         \
    "swc2 $14, 32( %0 )"                          \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (          \
    "swc2 $22, 0( %0 )"                           \
    :                                             \
    : "r"( r0 )                                   \
    : "memory" )

#define gte_strgb3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $20, 0( %0 );"                          \
    "swc2 $21, 0( %1 );"                          \
    "swc2 $22, 0( %2 )"                           \
    :                                             \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )             \
    : "memory" )

typedef struct { s16 vx, vy, vz, pad; } SVEC8_800262D8;          /* 0x08 */

typedef struct {                                        /* 0x24 */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u32 uv3;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} FaceGT4;

typedef struct {                                        /* 0x34 */
    u32 tag;
    u32 rgb0, xy0, uv0;
    u32 rgb1, xy1, uv1;
    u32 rgb2, xy2, uv2;
    u32 rgb3, xy3, uv3;
} PktGT4;

extern u32 D_80063888;

/* NOTE (§RC-10 preference cascade): `pkt` MUST be a body-local copy of the 4th
 * parameter. If the loop's biv IS the parameter pseudo, loop.c's record_initial
 * takes the biv's initial value straight from the incoming HARD reg, so the
 * preheader giv is emitted as `(set giv (plus (reg $a3) 0x28))` — that keeps $a3
 * live to the preheader (biv pseudo CONFLICTS with $7) and hands the giv the $7
 * set_preference. Result: giv->$a3, pkt->$t1 + a spurious `move t1,a3` (144 ins).
 * With the local copy the initial value is a PSEUDO: $a3 dies at the param copy,
 * pkt takes $a3 by preference, the giv falls to $t1, and the move disappears. */
PktGT4 *func_800262D8(FaceGT4 *face, SVEC8_800262D8 *vtx, SVEC8_800262D8 *nrm, PktGT4 *arg3,
                      s32 count, s32 shift, u32 *ot)
{
    long flag;
    long otz;
    u32 *otp;
    PktGT4 *pkt = arg3;

    gte_ldrgb(&D_80063888);

    while (count != 0) {
        gte_ldv3(&vtx[face->v0], &vtx[face->v1], &vtx[face->v2]);
        gte_rtpt();
        pkt->uv0 = face->uv0;
        pkt->uv1 = face->uv1;
        pkt->uv2 = face->uv2;
        gte_stflg(&flag);
        if (!(flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_gt4(pkt);
                gte_ldv0(&vtx[face->v3]);
                gte_rtps();
                pkt->uv3 = face->uv3;
                gte_stflg(&flag);
                if (!(flag & ~0x1000)) {
                    gte_stsxy(&pkt->xy3);
                    gte_avsz4();
                    gte_stotz(&otz);
                    gte_ldv3(&nrm[face->n0], &nrm[face->n1], &nrm[face->n2]);
                    gte_ncct();
                    otp = &ot[otz >> shift];
                    pkt->tag = (*otp & 0x00FFFFFF) | 0x0C000000;
                    gte_strgb3(&pkt->rgb0, &pkt->rgb1, &pkt->rgb2);
                    gte_ldv0(&nrm[face->n3]);
                    gte_nccs();
                    gte_strgb(&pkt->rgb3);
                    *otp = (u32)pkt & 0x00FFFFFF;
                    pkt++;
                }
            }
        }
        face++;
        count--;
    }
    return pkt;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80026514);

INCLUDE_ASM("asm/nonmatchings/800", func_800268D0);

INCLUDE_ASM("asm/nonmatchings/800", func_80026D64);

extern s32 D_800A2B78;

void func_80027058()
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        "addiu  $29, $29, -8\n"
        "lw     $11, 24($29)\n"
        "lw     $15, 28($29)\n"
        "lw     $14, 32($29)\n"
        "beqz   $11, 100f\n"
        "addu   $2, $7, $0\n"
        "addiu  $13, $29, 4\n"
        "lui    $10, 0xFF\n"
        "ori    $10, $10, 0xFFFF\n"
        "addiu  $9, $4, 4\n"
        "addiu  $8, $7, 4\n"
        "98:\n"
        "lhu    $4, 6($9)\n"
        "lhu    $3, 8($9)\n"
        "lhu    $2, 10($9)\n"
        "sll    $4, $4, 3\n"
        "addu   $4, $5, $4\n"
        "sll    $3, $3, 3\n"
        "addu   $3, $5, $3\n"
        "sll    $2, $2, 3\n"
        "addu   $2, $5, $2\n"
        "lwc2   $0, 0($4)\n"
        "lwc2   $1, 4($4)\n"
        "lwc2   $2, 0($3)\n"
        "lwc2   $3, 4($3)\n"
        "lwc2   $4, 0($2)\n"
        "lwc2   $5, 4($2)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "cfc2   $12, $31\n"
        "nop\n"
        "sw     $12, 0($29)\n"
        "lw     $2, 0($29)\n"
        "addiu  $3, $0, -4097\n"
        "and    $2, $2, $3\n"
        "bnez   $2, 99f\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2   $24, 0($13)\n"
        "lw     $2, 4($29)\n"
        "nop\n"
        "blez   $2, 99f\n"
        "nop\n"
        "swc2   $12, 8($7)\n"
        "swc2   $13, 12($7)\n"
        "swc2   $14, 16($7)\n"
        "nop\n"
        "nop\n"
        "avsz3\n"
        "swc2   $7, 0($13)\n"
        "lw     $2, 0($9)\n"
        "nop\n"
        "sw     $2, 0($8)\n"
        "lw     $2, 4($29)\n"
        "addiu  $8, $8, 20\n"
        "srav   $2, $2, $15\n"
        "sll    $2, $2, 2\n"
        "addu   $6, $14, $2\n"
        "lw     $3, 0($6)\n"
        "lui    $2, 0x400\n"
        "and    $3, $3, $10\n"
        "or     $3, $3, $2\n"
        "and    $2, $7, $10\n"
        "sw     $3, 0($7)\n"
        "sw     $2, 0($6)\n"
        "lui    $2, %hi(D_800A2B78)\n"
        "lw     $2, %lo(D_800A2B78)($2)\n"
        "nop\n"
        "beqz   $2, 99f\n"
        "addiu  $7, $7, 20\n"
        "lbu    $2, -17($8)\n"
        "nop\n"
        "andi   $2, $2, 0x2\n"
        "beqz   $2, 99f\n"
        "lui    $4, 0xE100\n"
        "ori    $4, $4, 0xA\n"
        "lw     $3, 4($29)\n"
        "addiu  $2, $0, 1\n"
        "sb     $2, -1($8)\n"
        "lui    $2, %hi(D_800A2B78)\n"
        "lw     $2, %lo(D_800A2B78)($2)\n"
        "srav   $3, $3, $15\n"
        "sll    $3, $3, 2\n"
        "addu   $6, $14, $3\n"
        "andi   $2, $2, 0x3\n"
        "sll    $2, $2, 5\n"
        "or     $2, $2, $4\n"
        "sw     $2, 0($8)\n"
        "addiu  $8, $8, 8\n"
        "lw     $3, 0($6)\n"
        "lui    $2, 0x100\n"
        "and    $3, $3, $10\n"
        "or     $3, $3, $2\n"
        "and    $2, $7, $10\n"
        "sw     $3, 0($7)\n"
        "addiu  $7, $7, 8\n"
        "sw     $2, 0($6)\n"
        "99:\n"
        "addiu  $11, $11, -1\n"
        "bnez   $11, 98b\n"
        "addiu  $9, $9, 16\n"
        "addu   $2, $7, $0\n"
        "100:\n"
        "addiu  $29, $29, 8\n"
        ".set\treorder\n"
    );
}


/* func_80027200 — HANDWRITTEN assembly (splat marks it "Handwritten function").
 * The register discipline (loop counter in $t3, live args in $a0/$a1/$a3, no
 * callee-saved registers at all, raw GTE cop2 ops with hand-placed latency nops)
 * is not reachable from gcc-2.7.2 codegen, so the body is reproduced verbatim as
 * a single .set noreorder asm block.  gcc supplies only the `jr $ra` + delay nop.
 */

extern s32 D_800A2B78;

void func_80027200(void)
{
    __asm__ __volatile__(
        ".set\tnoreorder\n"
        
        "addiu $sp, $sp, -0x8\n"
        "lw    $t3, 24($sp)\n"
        "lw    $t8, 28($sp)\n"
        "lw    $t7, 32($sp)\n"
        "beq   $t3, $zero, 3f\n"
        "addu  $v0, $a3, $zero\n"
        "addiu $t6, $zero, -0x1001\n"
        "addiu $t5, $sp, 0x4\n"
        "lui   $t2, 0xFF\n"
        "ori   $t2, $t2, 0xFFFF\n"
        "addiu $t1, $a0, 0x4\n"
        "addiu $t0, $a3, 0x4\n"
        "1:\n"
        "lhu   $a0, 6($t1)\n"
        "lhu   $v1, 8($t1)\n"
        "lhu   $v0, 10($t1)\n"
        "sll   $a0, $a0, 3\n"
        "addu  $a0, $a1, $a0\n"
        "sll   $v1, $v1, 3\n"
        "addu  $v1, $a1, $v1\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a1, $v0\n"
        "lwc2  $0, 0($a0)\n"
        "lwc2  $1, 4($a0)\n"
        "lwc2  $2, 0($v1)\n"
        "lwc2  $3, 4($v1)\n"
        "lwc2  $4, 0($v0)\n"
        "lwc2  $5, 4($v0)\n"
        "nop\n"
        "nop\n"
        "rtpt\n"
        "cfc2  $t4, $31\n"
        "nop\n"
        "sw    $t4, 0($sp)\n"
        "lw    $v0, 0($sp)\n"
        "nop\n"
        "and   $v0, $v0, $t6\n"
        "bne   $v0, $zero, 2f\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nclip\n"
        "swc2  $24, 0($t5)\n"
        "lw    $v0, 4($sp)\n"
        "nop\n"
        "blez  $v0, 2f\n"
        "nop\n"
        "swc2  $12, 8($a3)\n"
        "swc2  $13, 12($a3)\n"
        "swc2  $14, 16($a3)\n"
        "lhu   $v0, 12($t1)\n"
        "nop\n"
        "sll   $v0, $v0, 3\n"
        "addu  $v0, $a1, $v0\n"
        "lwc2  $0, 0($v0)\n"
        "lwc2  $1, 4($v0)\n"
        "nop\n"
        "nop\n"
        "rtps\n"
        "cfc2  $t4, $31\n"
        "nop\n"
        "sw    $t4, 0($sp)\n"
        "lw    $v0, 0($sp)\n"
        "nop\n"
        "and   $v0, $v0, $t6\n"
        "bne   $v0, $zero, 2f\n"
        "addiu $v0, $a3, 0x14\n"
        "swc2  $14, 0($v0)\n"
        "nop\n"
        "nop\n"
        "avsz4\n"
        "swc2  $7, 0($t5)\n"
        "lw    $v0, 0($t1)\n"
        "nop\n"
        "sw    $v0, 0($t0)\n"
        "lw    $v0, 4($sp)\n"
        "addiu $t0, $t0, 0x18\n"
        "srav  $v0, $v0, $t8\n"
        "sll   $v0, $v0, 2\n"
        "addu  $a2, $t7, $v0\n"
        "lw    $v1, 0($a2)\n"
        "lui   $v0, 0x500\n"
        "and   $v1, $v1, $t2\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t2\n"
        "sw    $v1, 0($a3)\n"
        "sw    $v0, 0($a2)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "nop\n"
        "beq   $v0, $zero, 2f\n"
        "addiu $a3, $a3, 0x18\n"
        "lbu   $v0, -21($t0)\n"
        "nop\n"
        "andi  $v0, $v0, 0x2\n"
        "beq   $v0, $zero, 2f\n"
        "lui   $a0, 0xE100\n"
        "ori   $a0, $a0, 0xA\n"
        "lw    $v1, 4($sp)\n"
        "addiu $v0, $zero, 0x1\n"
        "sb    $v0, -1($t0)\n"
        "lui   $v0, %hi(D_800A2B78)\n"
        "lw    $v0, %lo(D_800A2B78)($v0)\n"
        "srav  $v1, $v1, $t8\n"
        "sll   $v1, $v1, 2\n"
        "addu  $a2, $t7, $v1\n"
        "andi  $v0, $v0, 0x3\n"
        "sll   $v0, $v0, 5\n"
        "or    $v0, $v0, $a0\n"
        "sw    $v0, 0($t0)\n"
        "addiu $t0, $t0, 0x8\n"
        "lw    $v1, 0($a2)\n"
        "lui   $v0, 0x100\n"
        "and   $v1, $v1, $t2\n"
        "or    $v1, $v1, $v0\n"
        "and   $v0, $a3, $t2\n"
        "sw    $v1, 0($a3)\n"
        "addiu $a3, $a3, 0x8\n"
        "sw    $v0, 0($a2)\n"
        "2:\n"
        "addiu $t3, $t3, -0x1\n"
        "bne   $t3, $zero, 1b\n"
        "addiu $t1, $t1, 0x14\n"
        "addu  $v0, $a3, $zero\n"
        "3:\n"
        "addiu $sp, $sp, 0x8\n"
        
        ".set\treorder\n"
    );
}

/* ---- PsyQ inline_c.h GTE macros ---- */
#define gte_ldv3(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                         \
    "lwc2 $1, 4( %0 );"                         \
    "lwc2 $2, 0( %1 );"                         \
    "lwc2 $3, 4( %1 );"                         \
    "lwc2 $4, 0( %2 );"                         \
    "lwc2 $5, 4( %2 )"                          \
    :                                           \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

#define gte_stflg(r0) __asm__ volatile (        \
    "cfc2 $12, $31;"                            \
    "nop;"                                      \
    "sw   $12, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (        \
    "swc2 $24, 0( %0 )"                         \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile (        \
    "swc2 $7, 0( %0 )"                          \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (    \
    "swc2 $12,  8( %0 );"                       \
    "swc2 $13, 16( %0 );"                       \
    "swc2 $14, 24( %0 )"                        \
    :                                           \
    : "r"( r0 )                                 \
    : "memory" )


extern s32 D_800A2B78;

u8 *func_800273F4(TmdG3 *f, u8 *vtx, u8 *nrm, u8 *pkt, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 z;
    u32 *otp;

    if (n != 0) {
        __asm__("" : "=r"(pkt) : "0"(pkt));
        do {
            gte_ldv3(vtx + f->v0 * 8, vtx + f->v1 * 8, vtx + f->v2 * 8);
            gte_rtpt();
            gte_stflg(&flag);
            if ((flag & ~0x1000) == 0) {
                gte_nclip();
                gte_stopz(&z);
                if (z > 0) {
                    gte_stsxy3_g3(pkt);
                    gte_avsz3();
                    gte_stotz(&z);
                    *(u32 *)(pkt + 4) = f->rgb0;
                    *(u32 *)(pkt + 0xC) = f->rgb1;
                    *(u32 *)(pkt + 0x14) = f->rgb2;
                    pkt[7] = (pkt[7] & 2) | 0x30;
                    otp = ot + (z >> shift);
                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x6000000;
                    *otp = (u32)pkt & 0xFFFFFF;
                    pkt += 0x1C;
                    if (D_800A2B78 != 0) {
                        if (pkt[7 - 0x1C] & 2) {
                            otp = ot + (z >> shift);
                            pkt[3] = 1;
                            *(u32 *)(pkt + 4) = ((D_800A2B78 & 3) << 5) | 0xE100000A;
                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x1000000;
                            *otp = (u32)pkt & 0xFFFFFF;
                            pkt += 8;
                        }
                    }
                }
            }
            n--;
            f++;
        } while (n != 0);
    }
    return pkt;
}


/* ---- PsyQ inline GTE macros (inline_c.h forms) ------------------------- */
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :: "r"(r0))

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :: "r"(r0), "r"(r1), "r"(r2))

#define gte_rtps()  __asm__ volatile ("nop;nop;.word 0x4a180001")
#define gte_rtpt()  __asm__ volatile ("nop;nop;.word 0x4a280030")
#define gte_nclip() __asm__ volatile ("nop;nop;.word 0x4b400006")
#define gte_avsz4() __asm__ volatile ("nop;nop;.word 0x4b68002e")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :: "r"(r0) : "$12", "memory")

#define gte_stsxy2(r0) __asm__ volatile (        \
    "swc2 $14, 0( %0 )"                          \
    :: "r"(r0) : "memory")

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :: "r"(r0) : "memory")

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :: "r"(r0) : "memory")

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :: "r"(r0) : "memory")

/* ---- data ------------------------------------------------------------- */
extern s32 D_800A2B78;

typedef struct {
    s16 vx, vy, vz, pad;
} SVEC_800275BC;                        /* 8 bytes */

typedef struct {               /* TMD G4 flat-normal primitive, 0x20 bytes */
    u32 tag;                   /* 0x00 */
    u32 c0;                    /* 0x04 */
    u32 c1;                    /* 0x08 */
    u32 c2;                    /* 0x0C */
    u32 c3;                    /* 0x10 */
    u16 n0;                    /* 0x14 */
    u16 v0;                    /* 0x16 */
    u16 v1;                    /* 0x18 */
    u16 v2;                    /* 0x1A */
    u16 v3;                    /* 0x1C */
    u16 pad;                   /* 0x1E */
} TPRIM_800275BC;

void *func_800275BC(TPRIM_800275BC *prim, SVEC_800275BC *vp, void *nrm, u8 *pk, s32 n,
                    s32 shift, u32 *ot)
{
    s32 flag;
    s32 otz;
    u32 *op;

    if (n == 0) {
        return pk;
    }

    do {
        gte_ldv3(&vp[prim->v0], &vp[prim->v1], &vp[prim->v2]);
        gte_rtpt();
        gte_stflg(&flag);
        if ((flag & 0xFFFFEFFF) == 0) {
            gte_nclip();
            gte_stopz(&otz);
            if (otz > 0) {
                gte_stsxy3_g4(pk);
                gte_ldv0(&vp[prim->v3]);
                gte_rtps();
                gte_stflg(&flag);
                if ((flag & 0xFFFFEFFF) == 0) {
                    gte_stsxy2(pk + 0x20);
                    gte_avsz4();
                    gte_stotz(&otz);
                    *(u32 *)(pk + 0x04) = prim->c0;
                    *(u32 *)(pk + 0x0C) = prim->c1;
                    *(u32 *)(pk + 0x14) = prim->c2;
                    *(u32 *)(pk + 0x1C) = prim->c3;
                    *(u8 *)(pk + 7) = (*(u8 *)(pk + 7) & 2) | 0x38;
                    op = &ot[otz >> shift];
                    *(u32 *)pk = (*op & 0xFFFFFF) | 0x08000000;
                    *op = (u32)pk & 0xFFFFFF;
                    pk += 0x24;
                    if (D_800A2B78 != 0) {
                        if (*(u8 *)(pk - 0x1D) & 2) {
                            op = &ot[otz >> shift];
                            *(u8 *)(pk + 3) = 1;
                            *(u32 *)(pk + 4) =
                                ((D_800A2B78 & 3) << 5) | 0xE100000A;
                            *(u32 *)pk = (*op & 0xFFFFFF) | 0x01000000;
                            *op = (u32)pk & 0xFFFFFF;
                            pk += 8;
                        }
                    }
                }
            }
        }
        prim++;
    } while (--n != 0);
    return pk;
}


/* GTE inline-asm idioms, verbatim PsyQ inline_c.h macro bodies (see cookbook §-GTE and e.g.
 * src/ov_SC01_000/ov_SC01_000_jr_8017BEBC.c for the established shape of this idiom family).
 * NOTE gte_stsxy3_gt3: the target stores SXY0/1/2 at 8/16/24 off ONE base register ($a3, the
 * POLY_GT3 being built), not off three separate pointers -- that is the PsyQ `_gt3` variant.
 * Using the 3-pointer gte_stsxy3 costs three extra `addiu` and was the first agent's length drift. */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_gt3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

extern s32 D_80078D88[];

typedef struct { s16 vx, vy, vz, pad; } SVECTOR800277DC;

void *func_800277DC(void *a0, SVECTOR800277DC *a1, void *a2, u8 *a3,
                     s32 count, s32 shift, s32 *ot)
{
    /* The five GTE scratch slots MUST be ONE array, not five scalars.  gcc-2.7.2 assigns a
     * stack slot at the point each addressable local's address is first taken, NOT in
     * declaration order; hoisting &otz/&sz0/&sz1 into pre-loop pointer temps (needed to put
     * their three `addiu $sp` ahead of the mask/t0/t1 setup, see below) therefore stole slot 0
     * from `flag` and shifted the whole frame.  One array pins the layout:
     *   st[0]=flag @sp+0   st[1]=otz @sp+4   st[2]=sz0 @sp+8   st[3]=sz1 @sp+0xC  st[4]=sz2 @sp+0x10
     * &st[0] folds to plain $sp, which is why `flag` is touched as 0($sp) with no address reg. */
    s32 st[5];
    /* t0/t1 pins ARE load-bearing (unpinning them re-drifts to 124 ins): they reproduce the
     * hand-budgeted src/dst induction-variable allocation so every field offset stays a direct
     * displacement off $t0 / $t1.  cnt/mask/shiftAmt/otp need no pin -- gcc lands them on
     * $t2/$t3/$t9/$t8 on its own, and pinning `otp` to $24 actively BREAKS the match (below). */
    register u8 *t0 __asm__("$8");
    register u8 *t1 __asm__("$9");
    s32 cnt;
    s32 mask;
    s32 shiftAmt;
    s32 *otp;
    s32 *potz, *psz0, *psz1;
    s32 idx0, idx1, idx2;
    s32 idx;
    s32 m;

    cnt = count;
    shiftAmt = shift;
    otp = ot;

    if (cnt == 0) {
        return a3;
    }

    /* Explicit pre-loop pointer temps, ordered ahead of mask/t0/t1: loop-invariant motion
     * APPENDS hoisted insns after the preheader's own statements, so leaving these implicit
     * emitted them last (`lui/ori, addiu t0, addiu t1, addiu sp+4/8/0xC`) -- the target is the
     * reverse order. */
    potz = &st[1];
    psz0 = &st[2];
    psz1 = &st[3];
    mask = 0xFFFFFF;
    t0 = (u8 *)a0 + 3;
    t1 = a3 + 4;

    do {
        idx0 = *(u16 *)(t0 + 0x11);
        idx1 = *(u16 *)(t0 + 0x13);
        idx2 = *(u16 *)(t0 + 0x15);

        gte_ldv3(&a1[idx0], &a1[idx1], &a1[idx2]);
        gte_rtpt();

        *(u32 *)(t1 + 8)    = *(u32 *)(t0 + 1);
        *(u32 *)(t1 + 0x10) = *(u32 *)(t0 + 5);
        *(u32 *)(t1 + 0x18) = *(u32 *)(t0 + 9);

        gte_stflg(&st[0]);
        if (!(st[0] & ~0x1000)) {
            gte_nclip();
            gte_stopz(potz);
            if (st[1] > 0) {
                gte_stsxy3_gt3(a3);

                if (D_80078D88[0] & 0x8000) {
                    gte_stsz3(psz0, psz1, &st[4]);
                    /* `m` must NOT be the address-taken otz slot: assigning otz in each arm
                     * makes gcc spill to sp+4 three times.  The target keeps the running max
                     * in $v1 and stores ONCE, so the max needs a plain (non-addressable) temp.
                     * `st[2] > st[3]` (not `st[3] < st[2]`) is what loads sz0 first and emits
                     * `slt $v0, $v1, $a2`. */
                    if (st[2] > st[3]) {
                        m = st[2];
                        if (m < st[4]) m = st[4];
                    } else {
                        m = st[3];
                        if (m < st[4]) m = st[4];
                    }
                    st[1] = m >> 2;
                } else {
                    gte_avsz3();
                    gte_stotz(potz);
                }

                *(u32 *)t1 = (*(u32 *)(t0 + 0xD) & mask) | ((u32)t0[0] << 24);
                t1 += 0x20;

                idx = st[1] >> shiftAmt;
                {
                    u32 old = (u32)a3 & mask;
                    /* `s32 *p = otp + idx;` -- writing `otp[idx]` inline emits the address
                     * plus with the SCALED INDEX first (`addu $a0,$a0,$t8`); an explicit
                     * pointer temp emits it base-first (`addu $a0,$t8,$a0`) like the target.
                     * The second half of that fix is that `otp` must be an ordinary pseudo:
                     * with `register s32 *otp __asm__("$24")` local-alloc will not tie the
                     * dying index register to the address destination and the chain lands in
                     * $v0 instead of $a0.  Base-first + unpinned base = the last instruction. */
                    s32 *p = otp + idx;
                    *(u32 *)a3 = (*p & mask) | 0x7000000;
                    a3 += 0x20;
                    *p = old;
                }
            }
        }

        t0 += 0x1C;
    } while (--cnt);

    return a3;
}


/* ---- PsyQ inline GTE macros (inline_c.h style) ---- */
#define gte_ldv3(r0, r1, r2) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 );"  \
    "lwc2 $2, 0( %1 );"  \
    "lwc2 $3, 4( %1 );"  \
    "lwc2 $4, 0( %2 );"  \
    "lwc2 $5, 4( %2 )"   \
    :                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldv0(r0) __asm__ __volatile__ ( \
    "lwc2 $0, 0( %0 );"  \
    "lwc2 $1, 4( %0 )"   \
    :                    \
    : "r"( r0 ) )

#define gte_rtpt() __asm__ __volatile__ ("nop;nop;rtpt")
#define gte_rtps() __asm__ __volatile__ ("nop;nop;rtps")
#define gte_nclip() __asm__ __volatile__ ("nop;nop;nclip")
#define gte_avsz4() __asm__ __volatile__ ("nop;nop;avsz4")

#define gte_stflg(r0) __asm__ __volatile__ ( \
    "cfc2 $12, $31;"     \
    "nop;"               \
    "sw $12, 0( %0 )"    \
    :                    \
    : "r"( r0 )          \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ __volatile__ ( \
    "swc2 $24, 0( %0 )"  \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stotz(r0) __asm__ __volatile__ ( \
    "swc2 $7, 0( %0 )"   \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stsxy(r0) __asm__ __volatile__ ( \
    "swc2 $14, 0( %0 )"  \
    :                    \
    : "r"( r0 )          \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ __volatile__ ( \
    "swc2 $12, 8( %0 );"  \
    "swc2 $13, 16( %0 );" \
    "swc2 $14, 24( %0 )"  \
    :                     \
    : "r"( r0 )           \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ __volatile__ ( \
    "swc2 $16, 0( %0 );" \
    "swc2 $17, 0( %1 );" \
    "swc2 $18, 0( %2 );" \
    "swc2 $19, 0( %3 )"  \
    :                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

typedef struct {
    s16 vx, vy, vz, pad;
} Vtx8;

typedef struct {
    u8  pad0;
    u8  pad1;
    u8  pad2;
    u8  code;   /* +0x03 */
    u32 rgb1;   /* +0x04 */
    u32 rgb2;   /* +0x08 */
    u32 rgb3;   /* +0x0C */
    u32 term;   /* +0x10 */
    u32 rgb0;   /* +0x14 */
    u16 i0;     /* +0x18 */
    u16 i1;     /* +0x1A */
    u16 i2;     /* +0x1C */
    u16 i3;     /* +0x1E */
} SrcQ;

typedef struct {
    u32 tag;    /* +0x00 */
    u32 rgb0;   /* +0x04 */
    u32 xy0;    /* +0x08 */
    u32 rgb1;   /* +0x0C */
    u32 xy1;    /* +0x10 */
    u32 rgb2;   /* +0x14 */
    u32 xy2;    /* +0x18 */
    u32 rgb3;   /* +0x1C */
    u32 xy3;    /* +0x20 */
    u32 term;   /* +0x24 */
} LineG4;

extern s32 D_80078D88[];

LineG4 *func_800279AC(SrcQ *src, Vtx8 *vb, s32 unused, LineG4 *prim, s32 n, s32 shift, u32 *ot)
{
    s32 flag;
    s32 otz;

    /* cookbook §21 zero-byte re-tie: without it loop.c's record_initial takes the biv's
     * initial value straight from the parameter COPY (set prim (reg $a3)), so the +4 giv is
     * emitted as (plus (reg $a3) 4) -- $a3 then stays live past the copy, conflicts with the
     * prim pseudo, and prim/giv land in $t1/$a3 (target: $a3/$t1). The re-tie makes the
     * pre-loop set non-invariant so the giv is derived from the PSEUDO and prim coalesces
     * into $a3. Emits nothing. */
    __asm__ ("" : "=r"(prim) : "0"(prim));
    for (; n != 0; n--, src++) {
        gte_ldv3(&vb[src->i0], &vb[src->i1], &vb[src->i2]);
        gte_rtpt();
        prim->rgb1 = src->rgb1;
        prim->rgb2 = src->rgb2;
        prim->rgb3 = src->rgb3;
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_nclip();
        gte_stopz(&otz);
        if (otz <= 0) {
            continue;
        }
        gte_stsxy3_g4(prim);
        gte_ldv0(&vb[src->i3]);
        gte_rtps();
        gte_stflg(&flag);
        if (flag & 0xFFFFEFFF) {
            continue;
        }
        gte_stsxy(&prim->xy3);
        prim->term = src->term;
        /* §5a zero-byte barrier: else sched2 hoists the D_80078D88 load above this store and
         * eats the two load-delay nops the target keeps (the -2 length drift). */
        __asm__ __volatile__ ("" : : : "memory");
        if (D_80078D88[0] & 0x8000) {
            s32 sz[4];
            s32 m, k;
            gte_stsz4(&sz[0], &sz[1], &sz[2], &sz[3]);
            m = sz[2];
            if (m < sz[3]) {
                m = sz[3];
            }
            k = sz[0];
            if (k < sz[1]) {
                k = sz[1];
            }
            if (k < m) {
                k = m;
            }
            otz = k >> 2;
        } else {
            gte_avsz4();
            gte_stotz(&otz);
        }
        prim->rgb0 = (src->rgb0 & 0xFFFFFF) | ((u32)src->code << 24);
        /* §5a zero-byte barrier: keeps the rgb0 store ahead of the OT-link block instead of
         * letting sched2 interleave the `otz` reload into the rgb0 chain. */
        __asm__ __volatile__ ("" : : : "memory");
        {
            u32 *p = &ot[otz >> shift];
            prim->tag = (*p & 0xFFFFFF) | 0x09000000;
            *p = (u32)prim & 0xFFFFFF;
        }
        prim++;
    }
    return prim;
}

void func_80027BF0(void)
{
    func_80027C10();
}







extern G3P *func_80027D20(Face2 *f, SVEC2 *verts, SVEC2 *norms, G3P *prims,
                           s32 count, s32 shift, s32 ot);
extern G4P *func_80027F4C(Face3 *f, SVEC2 *verts, SVEC2 *norms, G4P *prims,
                           s32 count, s32 shift, s32 ot);

void func_80027C10(void *a0, void *a1, s32 a2)
{
    void *geo;
    SVEC2 *verts;
    SVEC2 *norms;
    Face2 *f;
    G3P *p;
    u32 w0;
    s32 cnt;
    u32 opc;
    u32 masked;

    geo = *(void **)((s32)a0 + 0x8);
    p = *(G3P **)((s32)a0 + 0xC);
    verts = *(SVEC2 **)((s32)geo + 0x0);
    norms = *(SVEC2 **)((s32)geo + 0x8);
    f = *(Face2 **)((s32)geo + 0x10);

    do {
        w0 = p->tag;
        cnt = p->rgb0;
        p = (G3P *)((s32)p + 8);
        opc = (w0 >> 24) & 0xFC;
        switch (opc) {
        case 0x30:
            func_80027D20(f, verts, norms, p, cnt, a2, *(s32 *)((s32)a1 + 4));
            f = (Face2 *)((s32)f + cnt * 20);
            break;
        case 0x38:
            func_80027F4C((Face3 *)f, verts, norms, (G4P *)p, cnt, a2, *(s32 *)((s32)a1 + 4));
            f = (Face2 *)((s32)f + cnt * 24);
            break;
        }
        masked = w0 & 0xFFFFFF;
        p = (G3P *)(masked | 0x80000000);
    } while (masked != 0);
}


/* ---- PsyQ inline GTE macros (same spellings as the matched ov_SC03_006 body) ---- */

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stsxy3_g3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_g3(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )




extern s16 D_800C7C74;
extern void func_80028200(s32 a0, s32 a1, s32 a2, s32 a3, s32 stack_arg);

G3P *func_80027D20(Face2 *f, SVEC2 *verts, SVEC2 *norms, G3P *prims,
                   s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz, sz0, sz1, sz2; } g;
    G3P *prim;
    s32 z;
    s32 w;
    s32 i;

    prim = &prims[D_800C7C74];

    for (i = count; i != 0; i--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_g3(prim);
                gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                if (g.sz0 < g.sz1) { w = g.sz2; z = g.sz0; } else { w = g.sz2; z = g.sz1; }
                if (w < z) z = w;
                g.opz = (z >> 2) - 1;
                if (g.opz < 0) {
                    g.opz = 0;
                }
                gte_ldrgb(&f->rgb);
                gte_ldv3(&norms[f->n0], &norms[f->n1], &norms[f->n2]);
                gte_ncct();
                gte_strgb3_g3(prim);
                func_80028200(ot, g.opz, shift, (s32)prim, 0x06000000);
            }
        }
    }

    return prim;
}


/* ---- PsyQ inline GTE macros (same spellings as the matched func_80027D20 / func_800279AC) ---- */

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_ldrgb(r0) __asm__ volatile (         \
    "lwc2 $6, 0( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt()  __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
#define gte_ncct()  __asm__ volatile ("nop;nop;ncct")
#define gte_nccs()  __asm__ volatile ("nop;nop;nccs")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb(r0) __asm__ volatile (         \
    "swc2 $22, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

#define gte_stsxy3_g4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_strgb3_g4(r0) __asm__ volatile (     \
    "swc2 $20, 4( %0 );"                         \
    "swc2 $21, 12( %0 );"                        \
    "swc2 $22, 20( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )




extern s16 D_800C7C74;
extern void func_80028200(s32 a0, s32 a1, s32 a2, s32 a3, s32 stack_arg);

G4P *func_80027F4C(Face3 *f, SVEC2 *verts, SVEC2 *norms, G4P *prims,
                   s32 count, s32 shift, s32 ot)
{
    struct { s32 flag, opz, sz0, sz1, sz2, sz3; } g;
    G4P *prim;
    s32 z;
    s32 w;
    s32 i;

    prim = &prims[D_800C7C74];

    for (i = count; i != 0; i--, f++, prim += 2) {
        gte_ldv3(&verts[f->v0], &verts[f->v1], &verts[f->v2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        if (!(g.flag & ~0x1000)) {
            gte_nclip();
            gte_stopz(&g.opz);
            if (g.opz > 0) {
                gte_stsxy3_g4(prim);
                gte_ldv0(&verts[f->v3]);
                gte_rtps();
                gte_stflg(&g.flag);
                if (!(g.flag & ~0x1000)) {
                    gte_stsxy(&prim->x3);
                    gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                    w = g.sz2;
                    if (g.sz3 < w) { w = g.sz3; }
                    z = g.sz0;
                    if (g.sz1 < z) { z = g.sz1; }
                    if (w < z) { z = w; }
                    g.opz = (z >> 2) - 1;
                    if (g.opz < 0) {
                        g.opz = 0;
                    }
                    gte_ldrgb(&f->rgb);
                    gte_ldv3(&norms[f->n0], &norms[f->n1], &norms[f->n2]);
                    gte_ncct();
                    gte_strgb3_g4(prim);
                    gte_ldv0(&norms[f->n3]);
                    gte_nccs();
                    gte_strgb(&prim->rgb3);
                    func_80028200(ot, g.opz, shift, (s32)prim, 0x08000000);
                }
            }
        }
    }

    return prim;
}


void func_80028200(s32 a0, s32 a1, s32 a2, s32 a3, s32 stack_arg) {
    s32 mask;
    s32 shifted_index;
    s32 *array_ptr;
    s32 loaded;
    s32 masked_a3;

    mask = 0xFFFFFF;
    shifted_index = (a1 >> a2) << 2;
    array_ptr = (s32 *)(a0 + shifted_index);
    loaded = *array_ptr;

    loaded = (loaded & mask) | stack_arg;
    *(s32 *)a3 = loaded;

    masked_a3 = (a3 & mask);
    *array_ptr = masked_a3;
}

void func_80028234(void) {
}

extern u8 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern void func_80028620(s32 a0, void *a1);

void func_8002823C(void) {
    s32 i;
    s32 a;
    s32 b;
    u8 *p;
    s32 off;

    i = 0;
    a = 0x800;
    b = 0x20;
    p = &D_800A5E88;
    off = 0;
    do {
        *(s32 *)((s32)&D_800A5E88 + off) = a;
        *(s32 *)((s32)&D_800A5E8C + off) = a;
        *(s32 *)((s32)&D_800A5E90 + off) = 0;
        *(u8 *)((s32)&D_800A5E94 + off) = b;
        *(u8 *)((s32)&D_800A5E95 + off) = b;
        *(u8 *)((s32)&D_800A5E96 + off) = b;
        func_80028620(i, p);
        p += 0x10;
        i++;
        off += 0x10;
    } while (i < 3);
}

void func_800282FC(void) {
}

extern u8 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern void func_80028620(s32 a0, void *a1);

void func_80028304(s32 a0, s32 a1, s32 a2, s32 a3, u8 a4, u8 a5, u8 a6) {
    s32 offset;

    a0 &= 0xFFFF;
    if ((u16)a0 >= 3) {
        return;
    }

    offset = a0 << 4;

    *(s32 *)((s32)&D_800A5E88 + offset) = a1;
    *(s32 *)((s32)&D_800A5E8C + offset) = a2;
    *(s32 *)((s32)&D_800A5E90 + offset) = a3;
    *(u8 *)((s32)&D_800A5E94 + offset) = a4;
    *(u8 *)((s32)&D_800A5E95 + offset) = a5;
    *(u8 *)((s32)&D_800A5E96 + offset) = a6;

    func_80028620(a0, (void *)((s32)&D_800A5E88 + offset));
}


extern u8 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern void func_80028620(s32, void *);

void func_80028394(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 offset;

    a0 &= 0xFFFF;
    if ((u16)a0 >= 3) {
        return;
    }

    offset = a0 << 4;

    *(s32 *)((s32)&D_800A5E88 + offset) += a1;
    *(s32 *)((s32)&D_800A5E8C + offset) += a2;
    *(s32 *)((s32)&D_800A5E90 + offset) += a3;

    func_80028620(a0, (void *)((s32)&D_800A5E88 + offset));
}


extern void func_80028620(s32, void *);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern u8 D_800A5E88;

void func_80028428(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 offset;

    a0 &= 0xFFFF;
    if ((u16)a0 >= 3) {
        return;
    }

    offset = a0 << 4;

    *(u8 *)((s32)&D_800A5E94 + offset) = (u8)a1;
    *(u8 *)((s32)&D_800A5E95 + offset) = (u8)a2;
    *(u8 *)((s32)&D_800A5E96 + offset) = (u8)a3;

    func_80028620(a0, (void *)((s32)&D_800A5E88 + offset));
}

extern u8 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern void func_80028620(s32 a0, void *a1);

void func_80028488(s32 a0) {
    s32 offset;

    a0 &= 0xFFFF;
    if ((u16)a0 >= 3) {
        return;
    }

    offset = a0 << 4;

    *(s32 *)((s32)&D_800A5E90 + offset) = 100;
    *(s32 *)((s32)&D_800A5E88 + offset) = 0;
    *(s32 *)((s32)&D_800A5E8C + offset) = 0;
    *(u8 *)((s32)&D_800A5E94 + offset) = 0;
    *(u8 *)((s32)&D_800A5E95 + offset) = 0;
    *(u8 *)((s32)&D_800A5E96 + offset) = 0;

    func_80028620(a0, (void *)((s32)&D_800A5E88 + offset));
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002850C);


extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern u8 D_800A5E88;
extern void func_80028620(s32, void *);

void func_80028558(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 v0;

    a0 &= 0xFFFF;
    v0 = a0 << 4;

    *(u8 *)((u32)&D_800A5E94 + v0) = a1;
    *(u8 *)((u32)&D_800A5E95 + v0) = a2;
    *(u8 *)((u32)&D_800A5E96 + v0) = a3;

    func_80028620(a0, (u8 *)&D_800A5E88 + v0);
}

extern void func_800538EC(s32 param);

void SsUtReverbOff(void) {
    func_800538EC(0);
}


extern s16 D_800C6D18;
extern s32 D_800C6D1C;
extern s8 D_800C6D20;
extern s8 D_800C6D22;

extern void GsSetFogParam(s32 *param);
extern void func_800538EC(s32 param);

void func_800285CC(void) {
    s32 *fog = (s32 *)&D_800C6D18;
    *(s16 *)fog = -0x106;
    D_800C6D1C = 0x1F40000;
    D_800C6D20 = 0;
    D_800C6D22 = 0;
    GsSetFogParam(fog);
    func_800538EC(1);
}

void func_80028620(s32 a0, void *a1) {
    struct { u32 a, b, c, d; } buf, *src = (void *)a1;

    buf = *src;
    if ((buf.a | buf.b | buf.c) == 0) {
        buf.a = 0x1000;
        ((u8 *)&buf)[14] = 0;
        ((u8 *)&buf)[13] = 0;
        ((u8 *)&buf)[12] = 0;
    }
    func_80053328(a0, &buf);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80028694);

void func_80028A30(void) {
}

void func_80028A38(void) {
}

void func_80028A40(void) {
}


typedef void (*GsTMDfastFn)(void);

extern void GsTMDfastF3L(void);
extern void GsTMDfastF3NL(void);
extern void GsTMDfastNF3(void);
extern void GsTMDfastG3L(void);
extern void GsTMDfastG3NL(void);
extern void GsTMDfastNG3(void);
extern void GsTMDfastTF3L(void);
extern void GsTMDfastTF3NL(void);
extern void GsTMDfastTNF3(void);
extern void GsTMDfastTG3L(void);
extern void GsTMDfastTG3NL(void);
extern void GsTMDfastTNG3(void);
extern void GsTMDfastF4L(void);
extern void GsTMDfastF4NL(void);
extern void GsTMDfastNF4(void);
extern void GsTMDfastG4L(void);
extern void GsTMDfastG4NL(void);
extern void GsTMDfastNG4(void);
extern void GsTMDfastTF4L(void);
extern void GsTMDfastTF4NL(void);
extern void GsTMDfastTNF4(void);
extern void GsTMDfastTG4L(void);
extern void GsTMDfastTG4NL(void);
extern void GsTMDfastTNG4(void);
extern void GsTMDfastF3GL(void);
extern void GsTMDfastF3GNL(void);
extern void GsTMDfastG3GL(void);
extern void GsTMDfastG3GNL(void);
extern void GsTMDfastF4GL(void);
extern void GsTMDfastF4GNL(void);
extern void GsTMDfastG4GL(void);
extern void GsTMDfastG4GNL(void);

extern GsTMDfastFn D_800A2BC0;
extern GsTMDfastFn D_800A2BC8;
extern GsTMDfastFn D_800A2BD8;
extern GsTMDfastFn D_800A2BE0;
extern GsTMDfastFn D_800A2BE8;
extern GsTMDfastFn D_800A2BF8;
extern GsTMDfastFn D_800A2C00;
extern GsTMDfastFn D_800A2C08;
extern GsTMDfastFn D_800A2C18;
extern GsTMDfastFn D_800A2C20;
extern GsTMDfastFn D_800A2C28;
extern GsTMDfastFn D_800A2C38;
extern GsTMDfastFn D_800A2C40;
extern GsTMDfastFn D_800A2C48;
extern GsTMDfastFn D_800A2C58;
extern GsTMDfastFn D_800A2C60;
extern GsTMDfastFn D_800A2C68;
extern GsTMDfastFn D_800A2C78;
extern GsTMDfastFn D_800A2C80;
extern GsTMDfastFn D_800A2C88;
extern GsTMDfastFn D_800A2C98;
extern GsTMDfastFn D_800A2CA0;
extern GsTMDfastFn D_800A2CA8;
extern GsTMDfastFn D_800A2CB8;
extern GsTMDfastFn D_800A2CC0;
extern GsTMDfastFn D_800A2CC8;
extern GsTMDfastFn D_800A2CCC;
extern GsTMDfastFn D_800A2CD4;
extern GsTMDfastFn D_800A2CD8;
extern GsTMDfastFn D_800A2CE0;
extern GsTMDfastFn D_800A2CE4;
extern GsTMDfastFn D_800A2CEC;

void func_80028A48(void)
{
    D_800A2BC0 = GsTMDfastF3L;
    D_800A2BC8 = GsTMDfastF3NL;
    D_800A2BD8 = GsTMDfastNF3;
    D_800A2BE0 = GsTMDfastG3L;
    D_800A2BE8 = GsTMDfastG3NL;
    D_800A2BF8 = GsTMDfastNG3;
    D_800A2C00 = GsTMDfastTF3L;
    D_800A2C08 = GsTMDfastTF3NL;
    D_800A2C18 = GsTMDfastTNF3;
    D_800A2C20 = GsTMDfastTG3L;
    D_800A2C28 = GsTMDfastTG3NL;
    D_800A2C38 = GsTMDfastTNG3;
    D_800A2C40 = GsTMDfastF4L;
    D_800A2C48 = GsTMDfastF4NL;
    D_800A2C58 = GsTMDfastNF4;
    D_800A2C60 = GsTMDfastG4L;
    D_800A2C68 = GsTMDfastG4NL;
    D_800A2C78 = GsTMDfastNG4;
    D_800A2C80 = GsTMDfastTF4L;
    D_800A2C88 = GsTMDfastTF4NL;
    D_800A2C98 = GsTMDfastTNF4;
    D_800A2CA0 = GsTMDfastTG4L;
    D_800A2CA8 = GsTMDfastTG4NL;
    D_800A2CB8 = GsTMDfastTNG4;
    D_800A2CC0 = GsTMDfastF3GL;
    D_800A2CC8 = GsTMDfastF3GNL;
    D_800A2CCC = GsTMDfastG3GL;
    D_800A2CD4 = GsTMDfastG3GNL;
    D_800A2CD8 = GsTMDfastF4GL;
    D_800A2CE0 = GsTMDfastF4GNL;
    D_800A2CE4 = GsTMDfastG4GL;
    D_800A2CEC = GsTMDfastG4GNL;
}


extern void *GsPrstF3L();
extern void *GsPrstF3NL();
extern void *GsPrstG3L();
extern void *GsPrstG3NL();
extern void *GsPrstTF3L();
extern void *GsPrstTF3NL();
extern void *GsPrstTG3L();
extern void *GsPrstTG3NL();
extern void *GsPrstF4L();
extern void *GsPrstF4NL();
extern void *GsPrstG4L();
extern void *GsPrstG4NL();
extern void *GsPrstTF4L();
extern void *GsPrstTF4NL();
extern void *GsPrstTG4L();
extern void *GsPrstTG4NL();

extern void *D_800A2CF0;
extern void *D_800A2CF8;
extern void *D_800A2D10;
extern void *D_800A2D18;
extern void *D_800A2D30;
extern void *D_800A2D38;
extern void *D_800A2D50;
extern void *D_800A2D58;
extern void *D_800A2D70;
extern void *D_800A2D78;
extern void *D_800A2D90;
extern void *D_800A2D98;
extern void *D_800A2DB0;
extern void *D_800A2DB8;
extern void *D_800A2DD0;
extern void *D_800A2DD8;

void func_80028C50(void) {
    D_800A2CF0 = GsPrstF3L;
    D_800A2CF8 = GsPrstF3NL;
    D_800A2D10 = GsPrstG3L;
    D_800A2D18 = GsPrstG3NL;
    D_800A2D30 = GsPrstTF3L;
    D_800A2D38 = GsPrstTF3NL;
    D_800A2D50 = GsPrstTG3L;
    D_800A2D58 = GsPrstTG3NL;
    D_800A2D70 = GsPrstF4L;
    D_800A2D78 = GsPrstF4NL;
    D_800A2D90 = GsPrstG4L;
    D_800A2D98 = GsPrstG4NL;
    D_800A2DB0 = GsPrstTF4L;
    D_800A2DB8 = GsPrstTF4NL;
    D_800A2DD0 = GsPrstTG4L;
    D_800A2DD8 = GsPrstTG4NL;
}

extern s32 func_80029178();

s32 func_80028D58(void) {
    return func_80029178(0xB) & 0xFF;
}

extern void func_80029124(s32, s32);

void func_80028D78(s32 a0) {
    func_80029124(0xB, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028D9C(void) {
    return func_80029178(0xC);
}

extern void func_80029124(s32, s32);

void func_80028DBC(s32 a0) {
    func_80029124(0xC, a0 & 0xFF);
}

extern s32 func_80029178();

s32 func_80028DE0(void) {
    return func_80029178(0xD) & 0xFF;
}

extern void func_80029124(s32, s32);

void func_80028E00(s32 a0) {
    func_80029124(0xD, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028E24(void) {
    return func_80029178(0xE);
}

extern void func_80029124(s32, s32);

void func_80028E44(s32 a0) {
    func_80029124(0xE, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028E68(void) {
    return func_80029178(0xF);
}

extern void func_80029124(s32, s32);

void func_80028E88(s32 a0) {
    func_80029124(0xF, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028EAC(void) {
    return func_80029178(0x10);
}

extern void func_80029124(s32, s32);

void func_80028ECC(s32 a0) {
    func_80029124(0x10, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028EF0(void) {
    return func_80029178(0x11);
}

extern void func_80029124(s32, s32);

void func_80028F10(s32 a0) {
    func_80029124(0x11, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028F34(void) {
    return func_80029178(0x12);
}

extern void func_80029124(s32, s32);

void func_80028F54(s32 a0) {
    func_80029124(0x12, a0 & 0xFF);
}

extern s32 func_80029178();

u8 func_80028F78(void) {
    return func_80029178(0x13);
}

extern void func_80029124(s32, s32);

void func_80028F98(s32 a0) {
    func_80029124(0x13, a0 & 0xFF);
}

extern s32 func_800291B4(s32);

u8 func_80028FBC(void)
{
    return func_800291B4(0x2C);
}

extern void func_800291A0(s32, s32);

void func_80028FDC(s32 a0) {
    func_800291A0(0x2C, a0 & 0xFF);
}

extern s32 func_800291B4(s32);

u8 func_80029000(void)
{
    return func_800291B4(0x2D);
}

extern void func_800291A0(s32, s32);

void func_80029020(s32 a0)
{
    func_800291A0(0x2D, a0 & 0xFF);
}


extern u8 D_800AE648[];

void func_80029044(void) {
    register s32 v1 __asm__("$3");

    v1 = 0;

    do {
        D_800AE648[v1] = 0;
        v1 += 1;
    } while ((u32)v1 < 0x40);
}


extern u8 D_800BA1B8[];

void func_8002906C(void) {
    register s32 v1 __asm__("$3");

    v1 = 0;
    do {
        D_800BA1B8[v1] = 0;
        v1 += 1;
    } while ((u32)v1 < 0x100);
}


extern void func_80016714(void *a0, s32 a1);
extern u8 D_800BA2B8[];

void func_80029094(void) {
    func_80016714(D_800BA2B8, 0x60);
}

extern void func_80029124(s32, s32);

void func_800290BC(void) {
    func_80029124(0x7F, 1);
}

extern void func_80029124(s32, s32);

void func_800290E0(void) {
    func_80029124(0x7F, 0);
}

extern s32 func_80029178();

u8 func_80029104(void) {
    return func_80029178(0x7F);
}

extern u8 D_800AE648[];

void func_80029124(s32 arg0, s32 arg1) {
    s32 idx = (u32)arg0 >> 3;
    s32 mask = 1 << (arg0 & 7);

    if ((arg1 & 0xFF) != 0)
        D_800AE648[idx] |= mask;
    else
        D_800AE648[idx] &= ~mask;
}

extern u8 D_800AE648[];

s32 func_80029178(u32 arg0) {
    u32 idx = arg0 >> 3;
    u32 bit = arg0 & 7;
    u32 m = 1 << bit;
    return (D_800AE648[idx] & m) != 0;
}

extern u8 D_800BA1B8[];
void func_800291A0(s32 arg0, s32 arg1) {
    D_800BA1B8[arg0] = arg1;
}

extern u8 D_800BA1B8[];
s32 func_800291B4(s32 arg0) {
    return D_800BA1B8[arg0];
}

extern u8 D_800BA1B8[];

void func_800291C8(s32 arg0, s32 arg1) {
    *(u16 *) &D_800BA1B8[arg0] = arg1;
}

extern u8 D_800BA1B8[];

s32 func_800291DC(s32 index) {
    return *(s16 *)&D_800BA1B8[index];
}

extern u8 D_800BA1B8[];

void func_800291F0(s32 a0, s32 a1)
{
    *(s32 *)&D_800BA1B8[a0] = a1;
}

extern u8 D_800BA1B8[];

u32 func_80029204(s32 arg0) {
    return *(u32 *) &D_800BA1B8[arg0];
}


extern s32 D_800AE6A8;
extern void func_80016714(void *a0, s32 a1);

void func_80029218(void) {
    func_80016714(&D_800AE6A8, 0x3C);
}

extern s32 D_80075838;

void func_80029240(void) {
    D_80075838 = 1;
}

extern s32 D_80075838;
void func_80029254(void) {
    D_80075838 = 0;
}

extern s32 D_80075838;
s32 func_80029264(void) {
    return D_80075838;
}


typedef struct {
    s32 words[38];
} Blk98_80029274;

extern Blk98_80029274 D_80072C84;
extern Blk98_80029274 D_80078E78;

void func_80029274(void) {
    Blk98_80029274 buffer;

    buffer = D_80072C84;
    D_80078E78 = buffer;
}


extern void func_80029344(void);
extern s32 D_80078E90;

void func_8002931C(s32 a0) {
    D_80078E90 = a0;
    func_80029344();
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029344);


extern void func_80016714(void *a0, s32 a1);
extern u16 D_800A6588[];

void func_8002941C(void) {
    func_80016714(D_800A6588, 0x2);
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029444);

extern s32 D_80078E80;
s32 func_80029504(void) {
    return D_80078E80;
}

extern s32 D_80078E80;
void func_80029514(s32 arg0) {
    D_80078E80 = arg0;
}

extern s32 D_80078E80;
s32 func_80029524(void) {
    return (u32)(D_80078E80 - 200) < 400;
}

extern s32 D_80078E84;
s32 func_8002953C(void) {
    return D_80078E84;
}

extern s32 D_80078E84;
void func_8002954C(s32 arg0) {
    D_80078E84 = arg0;
}

extern s32 D_80078E84;
void func_8002955C(void) {
    D_80078E84 += 1;
}

extern s32 D_80078E88;
s32 func_8002957C(void) {
    return D_80078E88;
}

extern s32 D_80078E88;
void func_8002958C(s32 arg0) {
    D_80078E88 = arg0;
}


extern void func_8002A544(s32);
extern s32 D_80078E88;

void func_8002959C(void) {
    func_8002A544(0x32);
    D_80078E88 = D_80078E88 + 1;
}


extern void func_80029124(s32, s32);

extern s16 D_80078EB4;
extern u16 D_80078EB2;
extern s16 D_80078EB8;
extern u16 D_80078EB6;
extern u8 D_80078EC0;
extern s32 D_80078E8C;

void func_800295D4(void) {
    D_80078EB4 = 0xFA;
    D_80078EB2 = 0xFA;
    D_80078EB8 = 0xFA;
    D_80078EB6 = 0xFA;
    func_80029124(0x1E, 1);

    D_80078EC0 = 1;
    func_80029124(0x80, 1);

    D_80078E8C = 0x64;
    func_80029124(0x82, 1);

    func_80029124(0x83, 1);
    func_80029124(0x85, 1);
}


extern void func_80029344(void);
extern s32 D_80078E90;

void func_80029664(void) {
    D_80078E90 = 0x528;
    func_80029344();
}

void func_80029690(void) {
    extern void func_80016714(void *a0, s32 a1);
    extern u8 D_80078F28[];
    extern s32 D_800A5E58[];
    s32 i;
    u8 *p;
    s32 *q;

    i = 0;
    p = D_80078F28;
    q = D_800A5E58;
    do {
        *q = 0;
        func_80016714(p, 0x5B8);
        p += 0x2DC;
        i++;
        q++;
    } while (i < 2);
}


extern void func_80029774(s32);
extern Blk36_800296F8 D_80079204;
extern s32 D_800A5E5C;

s32 func_800296F8(s32 arg0) {
    func_80029774(1);
    D_80079204 = *(Blk36_800296F8 *)arg0;
    return D_800A5E5C = 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029774);


extern Blk36_800296F8 D_80079204;
extern void func_8002992C(s32);

void func_800298BC(Blk36_800296F8 *arg0) {
    func_8002992C(1);
    *arg0 = D_80079204;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002992C);

extern u8 D_80078F28[];

void func_80029A58(s32 arg0) {
    u32 *p = (u32 *)(D_80078F28 + arg0 * 0x2DC);
    p[0xE] >>= 1;
}

extern s32 D_800A5E58[];

s32 func_80029A94(s32 arg0) {
    return D_800A5E58[arg0];
}

s32 func_80029AAC(void) {
    extern s32 func_8002A2B0(void);
    s32 ret;

    ret = func_8002A2B0();
    return ret * 75 / 100;
}


extern s32 func_80029E30(void);
extern s32 func_80029CD4(s32);

s32 func_80029AF4(void) {
    s32 s0;

    s0 = func_80029E30();
    s0 = s0 * (func_80029CD4(0x28) + 0xC8);
    return s0 / 100;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029B4C);

INCLUDE_ASM("asm/nonmatchings/800", func_80029BC8);

extern s32 func_80029DB4(void);

s32 func_80029C44(s16 a0, s16 a1) {
    s32 b;
    s32 c;
    s32 d;

    b = func_80029DB4();
    c = func_80029E30();
    d = func_80029CD4(a1);
    return (b + c) * (a0 + d) / 100;
}


extern s32 rand(void);

s32 func_80029CD4(s32 a0) {
    if (a0 == 0)
        return 0;
    return rand() % a0;
}

/* func_80029D3C — banked candidate, rounds 1-9.
 * Canonical s32(void) def per engine_core.h caller macros; incoming $a0
 * bridged via register pins ($4 -> $16) because the prototype takes no
 * named parameters. Clamp MUST stay a ternary: an if/else spelling moves
 * ret into $a0 and breaks the early-exit delay-slot chain (verified R9).
 * Divisor 4800 forced by choose_multiplier arithmetic on M=0x1B4E81B5,l=9.
 */
extern s32 func_8002A4FC(s32 a0);

s32 func_80029D3C(void) {
    register s32 n __asm__("$4");
    register s32 s0 __asm__("$16");
    s32 p;
    s32 q;
    s32 ret;

    __asm__("" : "=r"(n));
    s0 = n;
    if (s0 <= 0) {
        ret = 0;
    } else {
        p = func_8002A4FC(s0) * 60;
        q = s0 - s0 * p / 4800;
        ret = q > 0 ? q : 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80029DB4);


extern s32 func_8002A76C(void);
extern s32 func_8002A2B0(void);

s32 func_80029E30(void) {
    register s32 v1 __asm__("$3");
    s32 a, b, sum, v0, sign;

    a = func_8002A76C();
    b = func_8002A2B0();

    // Load magic constant directly into v1
    __asm__("lui %0, 0x51eb; ori %0, %0, 0x851f" : "=r"(v1));

    sum = a + b;

    // Compute sum * 175 via shifts
    v0 = sum << 1;      // sum * 2
    v0 = v0 + sum;      // sum * 3
    v0 = v0 << 2;       // sum * 12
    v0 = v0 - sum;      // sum * 11
    v0 = v0 << 4;       // sum * 176
    v0 = v0 - sum;      // sum * 175

    // Multiply by magic constant
    __asm__ __volatile__("mult %0, %1" : : "r"(v0), "r"(v1) : "hi", "lo");

    // Sign of v0 for division correction (happens in parallel)
    sign = v0 >> 31;

    // Get high word of multiplication into a hard-pinned $a0, scoped
    // narrowly so the pin doesn't bleed backward and swallow v1's
    // (magic-constant) live range into the same physical register.
    {
        register s32 a0 __asm__("$4");
        __asm__ __volatile__("mfhi %0" : "=r"(a0) : : "hi", "lo");
        // Final result: (high >> 5) - sign
        v1 = a0 >> 5;
    }
    return v1 - sign;
}

s32 func_80029E94(s32 arg0, s32 arg1) {
    s32 result = 0;
    s16 val;

    val = *(s16 *)(*(s32 *)(arg0 + 0x78) + 0x30);
    if (val != 0) {
        result = (val * arg1) >> 12;
    }
    return result;
}

s32 func_80029EC0(s32 a0) {
    return *(s16 *)(*(s32 *)(a0 + 0x78) + 0x2E);
}


extern s32 func_80029504(void);
extern s32 D_80078F04;
extern s32 D_80078F08;
extern s32 D_80078F0C;
extern void func_8002A2D4(s32);

void func_80029ED4(s32 arg0) {
    s32 v0;

    if (func_80029504() < 10) {
        return;
    }

    D_80078F04 += arg0;
    if ((u32)D_80078F04 < 0x66) {
        return;
    }
    D_80078F04 = (u32)D_80078F04 % 102u;

    D_80078F08 += 1;
    if ((u32)D_80078F08 > 9999999u) {
        D_80078F08 = 9999999;
    }

    v0 = D_80078F08 - D_80078F0C;
    if (v0 < 10) {
        return;
    }
    D_80078F0C = D_80078F08;
    func_8002A2D4(v0 / 10);
}

extern s32 D_80078F08;
s32 func_80029FD4(void) {
    return D_80078F08;
}

extern s32 func_8002A26C(void);
extern s32 func_8002A4B8(void);
extern s32 func_8002A728(void);
extern s32 func_8002A998(void);

s32 func_80029FE4(void) {
    s32 a;
    s32 b;
    s32 c;
    s32 d;

    a = func_8002A26C();
    b = func_8002A4B8();
    c = func_8002A728();
    d = func_8002A998();
    return (a + b + c + d) / 4;
}


extern s32 func_8002A088(s32);

s32 func_8002A04C(s32 a0) {
    s32 v0 = *(s32 *)(a0 + 0x78);

    if (v0) {
        return func_8002A088(*(s16 *)(v0 + 0x2E));
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A088);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A108);


extern s32 func_8002A26C(void);
extern s32 func_8002AA00(s32 a0);
extern s32 func_8002A27C(void);
extern s32 func_8002A28C(void);

s32 func_8002A1B4(void) {
    s32 temp;
    s32 check;
    s32 val1;
    s32 val2;
    s32 s0_val;

    temp = func_8002A26C();
    check = func_8002AA00(temp + 1);

    if (check == 0) {
        return 0;
    }

    val1 = func_8002A27C();
    val2 = func_8002A28C();
    s0_val = val1 ^ val2;

    if (s0_val == 0) {
        return 1;
    }

    return 0;
}


extern s32 func_8002A28C(void);
extern s32 func_8002A27C(void);

s32 func_8002A200(void) {
    s32 val_28C = func_8002A28C();
    s32 val_27C = func_8002A27C();
    return (val_27C >= val_28C) ? 1 : 0;
}


extern s32 D_80078EE4;
extern s32 D_80078EE8;

void func_8002A234(void) {
    s32 v1 = D_80078EE4 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EE4 = v1;
    D_80078EE8 = 0;
}

extern s32 D_80078EE4;
s32 func_8002A26C(void) {
    return D_80078EE4;
}

extern s32 D_80078EE8;
s32 func_8002A27C(void) {
    return D_80078EE8;
}

extern s32 D_80078EE4;
extern u8 D_800638F8[];

s32 func_8002A28C(void) {
    return *(u16 *)(D_800638F8 + D_80078EE4 * 16);
}

extern s32 D_80078EE4;
extern u8 D_800638FA[];

s32 func_8002A2B0(void) {
    return *(u16 *)(D_800638FA + D_80078EE4 * 16);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A2D4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A354);


extern s32 func_8002AA00(s32);
extern s32 func_8002A4D8(void);

s32 func_8002A400(void) {
    s32 a, b;

    a = func_8002A4B8();
    b = func_8002AA00(a + 1);

    if (!b) {
        return 0;
    }

    a = func_8002A4C8();
    a ^= func_8002A4D8();

    if (a == 0) {
        return 1;
    }
    return 0;
}


extern s32 func_8002A4D8(void);
extern s32 func_8002A4C8(void);

s32 func_8002A44C(void) {
    s32 result1 = func_8002A4D8();
    s32 result2 = func_8002A4C8();
    return !(result2 < result1);
}


extern s32 D_80078EEC;
extern s32 D_80078EF0;

void func_8002A480(void) {
    s32 v0 = D_80078EEC;
    s32 v1 = v0 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EEC = v1;
    D_80078EF0 = 0;
}

extern s32 D_80078EEC;
s32 func_8002A4B8(void) {
    return D_80078EEC;
}

extern s32 D_80078EF0;
s32 func_8002A4C8(void) {
    return D_80078EF0;
}

extern s32 D_80078EEC;
extern u8 D_800638FC[];

s32 func_8002A4D8(void) {
    return *(u16 *)(D_800638FC + D_80078EEC * 16);
}

extern s32 D_80078EEC;
extern u8 D_800638FE[];

s32 func_8002A4FC(s32 a0) {
    return *(u16 *)(D_800638FE + D_80078EEC * 16);
}

extern void func_8002A544(s32);

void func_8002A520(s32 arg0) {
    func_8002A544(*(u8 *) (arg0 + 200));
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A544);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A5C4);


extern s32 func_8002A728(void);
extern s32 func_8002A738(void);
extern s32 func_8002A748(void);
extern s32 func_8002AA00(s32 a0);

s32 func_8002A670(void) {
    s32 s0;

    if (func_8002AA00(func_8002A728() + 1) != 0) {
        s0 = func_8002A738();
        return s0 == func_8002A748();
    } else {
        return 0;
    }
}


extern s32 func_8002A748(void);

s32 func_8002A6BC(void) {
    s32 a = func_8002A748();
    s32 b = func_8002A738();
    return !(b < a);
}


extern s32 D_80078EFC;
extern s32 D_80078F00;

void func_8002A6F0(void) {
    register s32 loaded asm("$2");  // $v0
    register s32 result asm("$3");  // $v1

    loaded = D_80078EFC;
    result = loaded + 1;
    if (result >= 0x1F) {
        result = 0x1E;
    }
    D_80078EFC = result;
    D_80078F00 = 0;
}

extern s32 D_80078EFC;
s32 func_8002A728(void) {
    return D_80078EFC;
}

extern s32 D_80078F00;
s32 func_8002A738(void) {
    return D_80078F00;
}

extern s32 D_80078EFC;
extern u16 D_80063900[][8];

s32 func_8002A748(void) {
    return D_80063900[D_80078EFC][0];
}

extern s32 D_80078EFC;
extern u16 D_80063902[][8];

s32 func_8002A76C(void) {
    return D_80063902[D_80078EFC][0];
}

extern void func_8002A7B4(s32);

void func_8002A790(u8 *a0)
{
    func_8002A7B4(a0[0xC9]);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002A7B4);

INCLUDE_ASM("asm/nonmatchings/800", func_8002A834);


extern s32 func_8002A998(void);
extern s32 func_8002A9A8(void);
extern s32 func_8002A9B8(void);
extern s32 func_8002AA00(s32);

s32 func_8002A8E0(void) {
    s32 s0, v0;

    v0 = func_8002AA00(func_8002A998() + 1);
    if (!v0) {
        return 0;
    }

    s0 = func_8002A9A8();
    s0 = s0 ^ func_8002A9B8();
    if (s0 == 0) {
        return 1;
    }
    return 0;
}


extern s32 func_8002A9B8(void);

s32 func_8002A92C(void) {
    s32 val1 = func_8002A9B8();
    s32 val2 = func_8002A9A8();
    s32 cmp = (val2 < val1) ? 1 : 0;
    return cmp ^ 1;
}


extern s32 D_80078EF4;
extern s32 D_80078EF8;

void func_8002A960(void) {
    s32 v1 = D_80078EF4 + 1;
    if (v1 >= 0x1F) {
        v1 = 0x1E;
    }
    D_80078EF4 = v1;
    D_80078EF8 = 0;
}

extern s32 D_80078EF4;
s32 func_8002A998(void) {
    return D_80078EF4;
}

extern s32 D_80078EF8;
s32 func_8002A9A8(void) {
    return D_80078EF8;
}

extern s32 D_80078EF4;
extern u16 D_80063904[][8];

s32 func_8002A9B8(void) {
    return D_80063904[D_80078EF4][0];
}

typedef struct {
    u16 unk00;
    u8  pad[14];
} T16;  /* 0x10 */

extern T16 D_80063906[];
extern s32 D_80078EF4;

s32 func_8002A9DC(void) {
    return D_80063906[D_80078EF4].unk00;
}

extern s32 func_8002AA3C(void);

s32 func_8002AA00(s32 a0) {
    s32 ret;

    ret = func_8002AA3C();
    if (ret != 0) {
        return !(a0 < ret);
    }
    return -1;
}

extern s32 func_80029504(void);

s32 func_8002AA3C(void) {
    s32 v1 = func_80029504();

    if (v1 >= 1200) {
        return 99;
    }
    if (v1 >= 900) {
        return 27;
    }
    if (v1 >= 600) {
        return 22;
    }
    if (v1 >= 200) {
        return 16;
    }
    if (v1 >= 10) {
        return 8;
    }
    return 0;
}

void func_8002AAAC(void) {
}


extern s32 func_8002A26C(void);
extern s32 func_8002A4B8(void);
extern s32 func_8002A728(void);
extern s32 func_8002A998(void);

extern s32 D_800638A0[];
extern s32 D_800638EC;

s32 func_8002AAB4(void) {
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register s32 v0 __asm__("$2");
    register s32 *v1 __asm__("$3");
    register s32 a0;
    register s32 *a1;

    // Get values from the four functions
    s0 = func_8002A26C();
    s2 = func_8002A4B8();
    s1 = func_8002A728();
    v0 = func_8002A998();

    // Sum them: s0 = s0 + s2 + s1; v0 = s0 + v0
    s0 = s0 + s2;
    s0 = s0 + s1;
    v0 = s0 + v0;

    // Rounding: if v0 < 0, add 3 before dividing by 4
    if (v0 < 0) {
        v0 = v0 + 3;
    }

    // Divide by 4 using arithmetic right shift
    s0 = v0 >> 2;

    // Initialize pointer to table
    v1 = D_800638A0;
    a0 = v1[0];

    // If the first threshold is 0, return the default
    if (a0 == 0) {
        return D_800638EC;
    }

    a1 = v1 + 1;

    // Search through the table
    while (1) {
        if (s0 >= a0) {
            return a1[0];
        }

        v1 = v1 + 2;
        a0 = v1[0];

        if (a0 == 0) {
            return D_800638EC;
        }

        a1 = a1 + 2;
    }
}

void func_8002AB64(void) {
    extern s32 func_800291B4(s32);
    extern void func_800291A0(s32, s32);
    extern void func_8002AC00(s32);

    u8 c;
    s16 i;

    c = func_800291B4(0x2E) + 1;
    func_800291A0(0x2E, c);

    if (c == 1) {
        for (i = 1; i < 7; i++) {
            func_8002AC00(i & 0xFF);
        }
        for (i = 0x3B; i < 0x40; i++) {
            func_800291A0(i, 3);
        }
    }
}


extern s32 func_800291B4(s32);
extern void func_800291A0(s32, s32);
extern u16 D_800A6588[];
extern u8 D_8010F46E[];
extern u8 D_8010F46C[];

void func_8002AC00(s32 a0)
{
    register s32 s2 __asm__("$18"); /* $s2 */
    register s32 s0 __asm__("$16"); /* $s0 */
    register s32 s3 __asm__("$19"); /* $s3 */
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 zr __asm__("$0");
    register s32 arg1 __asm__("$4"); /* $a0 */
    s32 s1, tmp;

    v0 = a0;
    v1 = v0 + 0x62;
    s2 = v1 & 0xFF;
    __asm__("" : "=r"(s2) : "0"(s2));
    arg1 = s2;
    s0 = v0 + zr;
    s3 = (s32)D_800A6588;
    __asm__("" : "=r"(s3) : "0"(s3));

    v0 = func_800291B4(arg1);
    s0 = s0 & 0xFF;

    if (v0 & 0x80) {
        return;
    }

    s1 = s0 << 3;
    tmp = D_8010F46E[s1];
    tmp = tmp | 0x80;
    func_800291A0(s2, tmp);

    s0 = s0 << 1;
    v0 = *(u16*)&D_8010F46C[s1];
    s0 = s0 + s3;
    *(u16*)(s0 - 2) = (u16)v0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002AC98);

INCLUDE_ASM("asm/nonmatchings/800", func_8002AE60);

extern s32 D_800760C8;
void func_8002AED0(void) {
    D_800760C8 = 1;
}

extern s32 D_800760C8;
void func_8002AEE4(void) {
    D_800760C8 = 2;
}

extern s32 D_800760C8;
void func_8002AEF8(void) {
    D_800760C8 = 0;
}

s32 func_8002AF08(void) {
    return D_800760C8;
}


extern s32 D_800760AC;
extern s32 D_8007609C;
extern s32 D_800760A0;
extern s32 D_800760A4;
extern s32 D_800760A8;

void func_8002AF18(void) {
    D_800760AC = 0;
    D_8007609C = 0;
    D_800760A0 = 0;
    D_800760A4 = 0;
    D_800760A8 = 0;
}

extern u8 D_80075A50[];

u8 *func_8002AF48(s32 a0) {
    return &D_80075A50[(a0 + 1) * 0x80];
}

extern s32 D_80075A40;
s32 func_8002AF60(void) {
    return D_80075A40;
}


extern void func_80016714(void *a0, s32 a1);



extern Blk16 D_80075CC0[];
extern u32 D_80076040;

void func_8002AF70(void *a0, u32 a1) {
    register Blk16 *src __asm__("$17") = (Blk16 *)a0;
    register u32 val __asm__("$18") = a1;
    register Blk16 *dest __asm__("$16");
    Blk16 *end;

    __asm__(
        "lui %0, %%hi(D_80075CC0)\n\taddiu %0, %0, %%lo(D_80075CC0)"
        : "=r"(dest)
        : "r"(val)
    );

    func_80016714(dest, 0x300);
    end = src + 0x2D0 / 0x10;

    do {
        *dest = *src;
        src++;
        dest++;
    } while (src != end);

    __asm__ volatile("" : "=r"(src) : "0"(src));

    *(Blk12 *)dest = *(Blk12 *)src;

    D_80076040 = val;
}




extern Blk16 D_80075CC0[];

void func_8002B00C(void *dest) {
    Blk16 *d = (Blk16 *)dest;
    Blk16 *s = D_80075CC0;
    Blk16 *end = s + (0x2D0 / 0x10);

    do {
        *d = *s;
        s++;
        d++;
    } while (s != end);

    *(Blk12 *)d = *(Blk12 *)s;
}


u16 func_8002B064(u8 *a0) {
    u32 sum = 0;
    s32 a1 = (s32)a0 + 0x70;

    do {
        sum += *a0;
        a0++;
    } while ((s32)a0 < a1);

    return sum & 0xFFFF;
}


u16 func_8002B08C(s32 a0) {
    s32 v1 = 0;
    s32 a1 = a0 + 0x300;

    do {
        v1 += *(u8 *)a0;
        a0++;
    } while (a0 < a1);

    return v1 & 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002B0B4);

/* DEFERRED: SaveLoadRoutine (0x8002B154) — Phase 7 (session G), per Drew, to Q#5.
 * Original intent: the save / PS1 memory-card handler. Referenced by saveHeaderTemplate
 *   (0x80072DF0) via THREE entry-point pointers: 0x8002B154 / 0x8002B1AC / 0x8002BEA4.
 *   Dispatch branches on (selector & 7) (case 0 -> +1 counter; 1 -> 7; 2 -> 0x1E; 3 -> 0x23).
 * Why deferred (NOT a clean state machine like the 3 CD loaders drafted this session):
 *   - splat emits ONE 1139-instruction stub spanning 0x8002B154-0x8002C31C with a SINGLE `jr $ra`
 *     => it is effectively one large MULTI-ENTRY function (the 3 saveHeaderTemplate entries share a
 *     return; the caller passes args in $s0/$s3) — awkward to express in C at all.
 *   - Ghidra mis-analyses it: get_code(0x8002B154) returns only a tiny fragment using unaff_s0/
 *     unaff_s3 (caller-set regs), so there is no faithful whole-function decompile to translate.
 *   - It is the save-data/memcard format, explicitly Phase-3 Q#5 "format still TBD" — a different
 *     subsystem from the file/overlay loader cluster (which IS drafted: CdReadStateMachine,
 *     CdReadSectorReadyCB, StreamLoadStateMachine here + the matched CdReadRequest/CdQueueBusy/…).
 *   - External helpers it calls (uncharacterised): func_800603BC (x20), func_80060614, func_8006023C,
 *     func_80060D9C, func_80060AE0, func_8005FFB4, func_8005FD58, func_80061114/524, func_80016714(bzero).
 * Re-enable / revisit when Q#5 (save/memcard format) is studied: FIRST fix the Ghidra function
 *   boundary (make 0x8002B154 span the whole 1139 ins, or model the 3 entry points), re-decompile,
 *   characterise the func_80060xxx memcard helpers, THEN draft. A wrong faithful-looking draft here
 *   would be worse than this honest stub (P9/G3). The default build is byte-identical via this stub. */
INCLUDE_ASM("asm/nonmatchings/800", SaveLoadRoutine);


extern u8 D_80075AC0[];

u32 func_8002C320(void) {
    register u32 result __asm__("$8") = 0;
    int count = 0;
    register u32 bit1 __asm__("$14") = 1;
    register u32 bit2 __asm__("$13") = 2;
    register u32 shift __asm__("$7") = 0;
    u8 *base = D_80075AC0;
    u8 *ptr_data = base + 0x10;
    u8 *ptr_check = base + 0x2;
    u8 *ptr_byte = base;
    u32 sum;
    u32 masked;
    int j;
    u16 val;

    for (; count < 4; count++) {
        if (*ptr_byte != 0) {
            val = *(u16 *)ptr_check;
            sum = 0;

            for (j = 0; j < 0x70; j++) {
                sum += ptr_data[j];
            }
            masked = sum & 0xFFFF;

            if (val == masked) {
                result |= bit1 << shift;
            } else {
                result |= bit2 << shift;
            }
        }

        shift += 8;
        ptr_data += 0x80;
        ptr_check += 0x80;
        ptr_byte += 0x80;
    }

    return result;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002C3B0);

INCLUDE_ASM("asm/nonmatchings/800", func_8002C410);


extern s16 D_800C5328[];
extern s16 D_800C532A[];

void func_8002C8BC(void) {
    register s32 a0 __asm__("$4");
    register s32 v1 __asm__("$3");

    a0 = -1;
    v1 = 0;

    do {
        *(s16 *)((u8 *)D_800C5328 + v1) = a0;
        *(s16 *)((u8 *)D_800C532A + v1) = a0;
        v1 += 4;
    } while ((u32)v1 < 0x1E4);
}


/* ---- callees ---- */
extern void func_8003A424(void);
extern void func_8003D518(void);
extern void func_8003C598(s32 *);
extern void func_8003BE24(s32);
extern void func_8002D1F0(s32);
extern void func_8003B280(s32);
extern void func_80037D98(void);
extern void func_8002CC4C(void);
extern void func_8002FAE0(void);
extern void func_80037CC8(void);
extern void func_8003BE74(s32, s32);
extern void func_8003B1EC(s32 *);
extern void func_80034C24(void);
extern void func_80037004(void);

/* src/800.c (func_80032048) already declares `extern Owner4EE8 *D_800A4EE8;`
 * where Owner4EE8 is `typedef struct Owner4EE8 {...} Owner4EE8;` defined later
 * in the TU. Spell the extern EXACTLY like the TU (bare typedef name, no
 * `struct` keyword) via a forward typedef so this compiles standalone too;
 * the incomplete typedef is later completed by the TU's own full definition
 * (identical redeclaration is legal). This is a pointer-only use here, so the
 * type's spelling has no effect on codegen. */
extern Owner4EE8 *D_800A4EE8;

/* ---- data ---- */
extern s32 D_800A4EA4;
extern s16 D_800A4EA8;
extern s16 D_800A4EAA;
extern s16 D_800A4EAC;
extern s16 D_800A4EAE;
extern s16 D_800A4EB4;
extern s16 D_800A4EB6;
extern s32 D_800A4EB8;
extern s32 D_800A4EBC;
extern s32 D_800A4EC8;

extern s32 D_800A4E68;
extern s16 D_800A4E6C;
extern s16 D_800A4E6E;
extern u8  D_800A4E70;
extern u8  D_800A4F18;
extern u8  D_800A4F19;
extern s16 D_800A4EF6;

/* D_800A463C is reached as (&D_800A4638)[1]: src/800.c declares that symbol as
 * `extern Ent24 D_800A463C[];` (anonymous typedef, defined further down the TU),
 * so a scalar redeclaration here would conflict.  Byte-identical relocation. */
extern s32 D_800A4638;

extern u8  D_800A4E7A;
extern u8  D_800A46E4;
extern s32 D_800A4654;
extern s32 D_800A466C;
extern s32 D_800A4684;
extern s32 D_800A469C;

extern s32 D_800A64B0;
extern u8  D_800A4650[];
extern s16 D_800A4644[];
extern s16 D_800A4642[];
extern u16 D_800A46E8[];

extern u8  D_800A4988[];
extern s32 D_800A4C68[];
extern u8  D_800A4C6C[];
extern u8  D_800A4C6D[];

extern s16 D_800A4EF8;
extern s16 D_800A4EFA;
extern u8  D_800A4F1B;
extern u8  D_800A46BA;
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;
extern s8  D_800A4F17;
extern u16 D_800A4E8E;
extern u16 D_800A4EA2;
extern s16 D_800A4EF0;
extern s16 D_800A4EFC;
extern u16 D_800A4F20;
extern u16 D_800A4F22;
extern u8  D_800A4F1D;
extern s32 D_800A4EEC;
extern u8  D_800A4EE6;
extern u16 D_800A4EE0;
extern u16 D_800A4EE4;
extern void (*D_800A4F24)(void);
extern u8  D_800A4F16;
extern u8  D_800A4F1C;
extern u8  D_800A4F1E;

void func_8002C8F4(void)
{
    s32 sp10[2];
    s32 *p;
    u8 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 m;

    func_8003A424();
    func_8003D518();

    p = &D_800A4EA4;
    *p = 0x23CF;
    D_800A4EA8 = 0x3FFF;
    D_800A4EAA = 0x3FFF;
    D_800A4EB4 = 0x3FFF;
    D_800A4EB6 = 0x3FFF;
    D_800A4EAC = 0;
    D_800A4EAE = 0;
    D_800A4EB8 = 0;
    D_800A4EBC = 1;
    D_800A4EC8 = 0;

    func_8003C598(p);
    func_8003BE24(1);
    func_8002D1F0(4);
    func_8003B280(1);
    func_80037D98();

    D_800A4E68 = 0x3C;
    D_800A4E6C = 0x2F;
    D_800A4E6E = 0x2F;
    D_800A4E70 = 1;
    D_800A4F18 = 1;
    D_800A4F19 = 1;
    D_800A4EF6 = 1;
    (&D_800A4638)[1] = 0x1010;
    D_800A4638 = 0;
    D_800A4E7A = 0;
    D_800A46E4 = 0;
    D_800A4654 = 0x10000;
    D_800A466C = 0x14000;
    D_800A4684 = 0x18000;
    D_800A469C = 0x39F00;

    for (j = 0x54; j >= 0; j -= 0xC) {
        *(s32 *)((u8 *)&D_800A64B0 + j) = 0;
    }

    for (i = 0; i < 5; i++) {
        k = i * 0x18;
        D_800A4650[k] = 1;
        *(s16 *)((u8 *)D_800A4644 + k) = 0;
        *(s16 *)((u8 *)D_800A4642 + k) = -1;
    }

    for (n = 0x24C; n >= 0; n -= 0x54) {
        *(u16 *)((u8 *)D_800A46E8 + n) = 0;
    }

    m = 0x10;
    for (i = 0, q = D_800A4988 + 0x4F; i < 8; i++, m++, q += 0x54) {
        k = i * 0x48;
        q[2] = i;
        *(s16 *)(q - 0x45) = m;
        q[-1] = 0;
        *(s32 *)(q - 0x4B) = 0;
        *(s32 *)(q - 0xF) = 0;
        q[1] = 0;
        *(s32 *)((u8 *)D_800A4C68 + k) = m;
        D_800A4C6C[k] = 0;
        D_800A4C6D[k] = 0;
    }

    func_8002CC4C();

    D_800A4EFA = 0x7F;
    D_800A4EF8 = 0x7F;
    D_800A4F1B = 1;
    D_800A46BA = 0;
    D_800A2B98 = 0;
    D_800C7D20 = 0;
    D_800C7D2C = 0;
    D_800A2BA0 = 0;
    D_800A4F17 = 0;
    D_800A4E8E = 0;
    D_800A4EA2 = 0;
    D_800A4EF0 = 0;
    D_800A4EE8 = 0;
    D_800A4EFC = 0;
    D_800A4F20 = 0;
    D_800A4F22 = 0;
    D_800A4F1D = 0;
    D_800A4EEC = 0;
    D_800A4EE6 = 0;
    D_800A4EE0 = 0x4000;
    D_800A4EE4 = 0x4000;
    D_800A4F24 = 0;
    D_800A4F16 = 0;

    func_8002FAE0();
    func_80037CC8();
    func_8003BE74(0, 0xFFFFFF);

    sp10[0] = 1;
    sp10[1] = 0;
    func_8003B1EC(sp10);

    D_800A4F1C = 0;
    D_800A4F1E = 0;
    func_80034C24();
    func_80037004();
}


extern B12 *D_8006A970[];
extern s32 D_80065504[];

void func_8002CC4C(void) {
    B12 **pp;
    s32 *cnt;
    s32 off;
    register B12 *p __asm__("$3");
    register s32 i __asm__("$4");
    register s32 *cp __asm__("$5");
    s32 pad;

    (void)&pad;
    pp = D_8006A970;
    cnt = D_80065504;
    for (off = 0; off < 0x10; off += 4) {
        p = *pp;
        i = 0;
        if (*cnt > 0) {
            cp = cnt;
            do {
                i++;
                p->unk0A = 0;
                p++;
            } while (i < *cp);
        }
        cnt++;
        pp++;
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_8002CCB4(void) {
    func_8002D4C8(2, 0);
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002CCD8);


extern s32 D_800A4638;
extern u16 D_800A4F22;
extern s16 D_8006A990;
extern u8  D_800A4EE6;
extern u16 D_800A4EE0;
extern u16 D_800A4EE2;
extern u16 D_800A4EE4;
extern u8  D_800A4F16;
extern u8  D_800A4EFE[];
extern u16 D_800A4E8E;
extern u16 D_800A4E8A;
extern s16 D_800A4E86;
extern s8  D_800A4F17;
extern u8  D_800A4F18;
extern u8  D_8006AEF4;

extern void func_8002D904(s32);
extern s32  func_8003D25C(s32, s32, u8 *);
extern void func_80037FC4(void);
extern void func_8002EC10(void);
extern s32  func_8003836C(s32 a0);
extern void func_8002CFE4(void);
extern s32  func_8003C4F0(s32);

void func_8002CDD8(void)
{
    s32 *ctr;
    u16 tmp;
    u16 cur;
    u16 tgt;
    u8  fl;
    s16 t;

    ctr = &D_800A4638;
    tmp = D_800A4F22;
    *ctr = *ctr + 1;
    if (tmp != 0) {
        D_8006A990 = tmp;
        func_8002D904(tmp);
        D_800A4F22 = 0;
    }

    fl = D_800A4EE6;
    if (fl & 1) {
        tgt = D_800A4EE4;
        cur = D_800A4EE0;
        D_800A4F16 = 1;
        if (tgt < cur) {
            D_800A4EE0 = cur - D_800A4EE2;
            if (tgt >= D_800A4EE0) {
                D_800A4EE0 = tgt;
                D_800A4EE6 = fl & 0xFE;
            }
        } else {
            D_800A4EE0 = cur + D_800A4EE2;
            if (D_800A4EE0 >= tgt) {
                D_800A4EE0 = tgt;
                D_800A4EE6 = fl & 0xFE;
            }
        }
    }

    func_8003D25C(0, 0x17, D_800A4EFE);

    if (D_800A4E8E & 8) {
        func_80037FC4();
        t = *(s16 *)&D_800A4E8A;
        if (t != 0) {
            t--;
            D_800A4E8A = t;
            if (t == 0) {
                func_8002EC10();
            }
        }
        if ((s16)func_8003836C(D_800A4E86) == 0) {
            D_800A4E8E &= 0xFFF7;
        }
    }

    if (*(u8 *)&D_800A4F17 == 0) {
        D_800A4F18 = 0;
        func_8002CFE4();
    } else {
        D_800A4F18 = 1;
    }

    if ((D_8006AEF4 & 1) && !(D_8006AEF4 & 2)) {
        if (func_8003C4F0(0) != 0) {
            D_8006AEF4 &= 0xFE;
        }
    }
}

extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

extern s16 D_800A4EFC;

void func_8002CFE4(void) {
    s16 *ptr = &D_800A4EFC;

    if (*ptr != 0) {
        *ptr = *ptr - 1;
    }
    func_80030F80();
    func_8002D320();
    func_80031BE0();
}

extern u8 D_800A46BA;
extern void func_8002D29C(void);

extern s32 D_800A64B0;

extern u8 D_8006A980;
extern void func_8002DF80(void);

extern void (*D_800A4F24)(void);

extern u8 D_800A4E70;
extern s32 D_800A4E68;
extern s16 D_800A4E6C;
extern void func_8002D240(s32 a0);

extern u8 D_800A4E7A;
extern s16 D_800A4E76;
extern u16 D_800A4E74;
extern s16 D_800A4E78;

void func_8002D034(void) {
    s32 *ptr;
    s32 i;

    if (D_800A46BA) {
        func_8002D29C();
    }

    ptr = &D_800A64B0;
    for (i = 0; i < 8; i++, ptr = (s32 *)((u8 *)ptr + 0xC)) {
        if (ptr[0] != 0 && --ptr[0] == 0) {
            void (*func)(void *) = (void (*)(void *))ptr[2];
            func(ptr);
        }
    }

    if ((D_8006A980 & 0xEF) != 0) {
        func_8002DF80();
    }

    if (D_800A4F24 != NULL) {
        D_800A4F24();
    }

    if (D_800A4E70 != 0) {
        if (--D_800A4E68 == 0) {
            s32 a0 = D_800A4E6C;
            D_800A4E70 = 0;
            func_8002D240(a0);
        }
    }

    {
        register u8 *flagPtr __asm__("$8");
        flagPtr = &D_800A4E7A;
    if (*flagPtr != 0) {
        if (D_800A4E76 > (s16)D_800A4E74) {
            s16 delta = D_800A4E78;
            if ((s16)D_800A4E74 < D_800A4E76 - delta) {
                D_800A4E74 = (s16)D_800A4E74 + delta;
            } else {
                D_800A4E74 = D_800A4E76;
                *flagPtr = 0;
            }
        } else {
            s16 delta = D_800A4E78;
            if (D_800A4E76 + delta < (s16)D_800A4E74) {
                D_800A4E74 = (s16)D_800A4E74 - delta;
            } else {
                D_800A4E74 = D_800A4E76;
                *flagPtr = 0;
            }
        }

        func_8002D240((s16)D_800A4E74);
    }
    }
}


extern void func_8003B45C(s32 *);

extern s32 D_800A4ECC;
extern s32 D_800A4ED0;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;

void func_8002D1F0(s32 arg0) {
    s32 *v1 = &D_800A4ECC;
    *v1 = 1;
    D_800A4ED0 = (s16)arg0;
    D_800A4ED4 = 0;
    D_800A4ED6 = 0;
    func_8003B45C(v1);
}


extern s32 D_800A4ECC;
extern u16 D_8006ADD8[];
extern u16 D_800A4E74;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;
extern void func_8003B45C(s32 *a0);

void func_8002D240(s32 a0) {
    s32 index = (a0 << 16) >> 15;
    s32 *p = &D_800A4ECC;
    u16 value = *(u16 *)((u8 *)D_8006ADD8 + index);

    *p = 0x6;
    D_800A4E74 = (u16)a0;
    D_800A4ED4 = value;
    D_800A4ED6 = value;

    func_8003B45C(p);
}

extern s32 D_800A46B4;
extern u16 D_800A46B8;
extern u16 D_800A4EF4;
extern u8 D_800A46BA;

extern int func_8003EDE8(int a0, int a1, int a2);
extern void func_8002EE90(void);

void func_8002D29C(void) {
    s32 *s1;
    s32 s0;
    s16 v0;
    s16 v1;

    s1 = &D_800A46B4;
    s0 = *s1;
    v0 = D_800A4EF4;
    func_8003EDE8(0, (s0 * v0) >> 16, (s0 * v0) >> 16);
    v1 = D_800A46B8;
    s0 -= v1;
    if (s0 <= 0) {
        D_800A46BA = 0;
        func_8002EE90();
        s0 = 0;
    }
    *s1 = s0;
}

extern u8  D_800A4C6D[];
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;

void func_8002D320(void)
{
    /* TU-absent names, block scope */
    extern Slot D_800A4C28[];
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003BE74(s32, s32);
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");
    register u32 mask __asm__("$17");
    register s32 i __asm__("$18");

    i = 0;
    mask = 0x60000;
    p = D_800A4C6D;
    do {
        if (*p != 0) {
            if (p[-1] == 0 || (*(u32 *)(p - 0x41) & mask) == 0) {
                func_8003D3B4(*(s32 *)(p - 5), 1);
            }
            *p = 0;
        }
        i++;
        p += 0x48;
    } while (i < 8);

    if ((D_800A2B98 & 0xFF0000) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFF0000);
        D_800A2B98 = *(u16 *)&D_800A2B98;
    }
    if ((D_800A2BA0 & 0xFF0000) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFF0000);
        D_800A2BA0 = *(u16 *)&D_800A2BA0;
    }

    mask = (u32)D_800A4C28;
    i = 0;
    p = (u8 *)mask + 4;
    do {
        if (p[0x40] != 0) {
            Slot *b2 = (Slot *)mask;
            s32 id = *(s32 *)(p + 0x3C);
            p[0x40] = 0;
            func_8003B250(id, b2);
            *(s32 *)p = 0;
        }
        p += 0x48;
        i++;
        mask += 0x48;
    } while (i < 8);

    if ((D_800C7D20 & 0xFF0000) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFF0000);
        D_800C7D20 = *(u16 *)&D_800C7D20;
    }
    if ((D_800C7D2C & 0xFF0000) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFF0000);
        D_800C7D2C = *(u16 *)&D_800C7D2C;
    }
}

extern u8 D_800A46BA;
u8 func_8002D4B8(void) {
    return D_800A46BA;
}

extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;
extern void func_8002D904(s32);
extern void func_8002DC68(s32 a0, s32 a1);
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002D4C8(s32 arg0, s32 arg1) {
    u8 v0;
    s8 *p;

    D_800A4F17 = 1;
    if ((u16)arg0 < 0x80) {
        func_8002E138((u16)arg0, arg1 & 0xFFFF, 0);
    } else if ((u16)arg0 >= 0x100) {
        if ((u16)arg0 < 0x400) {
            func_8002D904((u16)arg0);
        } else {
            func_8002DC68((u16)arg0, arg1 & 0xFFFF);
        }
    }

    p = &D_800A4F17;
    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 cnt = D_800A4EFC;
        if (cnt != 0) {
            D_800A4EFC = cnt - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

void func_8002D59C(s32 arg0, s32 arg1, s32 arg2) {
    u16 id;
    u8 v0;
    s8 *p;

    *(u8 *)&D_800A4F17 = 1;
    id = arg0 & 0xFFFF;
    if (id < 0x80) {
        func_8002E138(id, arg1 & 0xFFFF, arg2 & 0xFFFF);
    } else if (id >= 0x100) {
        if (id < 0x400) {
            func_8002D904(id);
        } else {
            func_8002DC68(id | (arg2 << 16), arg1 & 0xFFFF);
        }
    }

    p = &D_800A4F17;
    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 cnt = D_800A4EFC;
        if (cnt != 0) {
            D_800A4EFC = cnt - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

extern s8 D_800A4F17;

s32 func_8002D678(s32 a0, s32 a1) {
    extern void func_8002DC68(s32 a0, s32 a1);

    u32 id;
    s32 ret;

    D_800A4F17 = 1;
    id = a0 & 0xFFFF;
    if (id >= 0x400) {
        ret = ((s32 (*)())func_8002DC68)(id, a1 & 0xFFFF);
        if (ret != 0) {
            ret |= id << 16;
        }
        return ret;
    }
    return 0;
}


extern u8 D_8006451C[];
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

extern s32 func_8002F4E4(u8 *);
extern void func_8003324C(s32);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002D6D8(u32 a0) {
    s32 id;
    u8 v0;
    s8 *p = &D_800A4F17;

    *p = 1;
    id = a0 >> 16;
    a0 = (u16)a0;
    if ((u16)id < 0x100) {
        return;
    }
    {
        u8 *q = &D_8006451C[(u16)id * 4];
        if ((*q & 0x7F) == 6) {
            id = func_8002F4E4(q);
            if ((u16)id == 0) {
                return;
            }
        }
    }

    if (a0 == 0) {
        return;
    }
    a0--;
    if (*(u16 *)((u8 *)&D_800A4F17 + a0 * 0x54 - 0x82B) == (u16)id) {
        func_8003324C((u16)a0);
    }

    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 v0s = D_800A4EFC;
        if (v0s != 0) {
            D_800A4EFC = v0s - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

void func_8002D7F4(void) {
}

extern s32 D_800A4E7C;
void func_8002D7FC(s32 arg0) {
    D_800A4E7C = arg0;
}

extern u16 D_800A4E8E;
extern s16 D_8006A990;

u16 func_8002D80C(void) {
    return (D_800A4E8E & 1) ? D_8006A990 : 0;
}

extern s16 D_8006A990;
void func_8002D834(void) {
    D_8006A990 = 0;
}

extern s32 D_800760E0;

s32 func_8002D844(s32 arg0) {
    D_800760E0 = arg0;
    return arg0;
}

extern s16 D_800760E4;
extern void func_8003D650(int a0, int a1, int a2);
extern int func_8003EDE8(int a0, int a1, int a2);

int func_8002D858(void) {
    D_800760E4 = 100;
    func_8003D650(0, 1, 0);
    func_8003EDE8(0, D_800760E4, D_800760E4);
    return D_800760E4;
}

s32 func_8002D8A8(void) {
    extern void (*D_800A4F24)(void);
    extern s16 D_800760EC;
    extern s16 D_800760E8;
    extern void func_8002FA3C(void);

    D_800760EC = 6;
    D_800A4F24 = func_8002FA3C;
    D_800760E8 = 0;
    return 0x10;
}

extern void (*D_800A4F24)(void);
extern int func_8003EDE8(int a0, int a1, int a2);

int func_8002D8D4(void) {
    D_800A4F24 = NULL;
    func_8003EDE8(0, 0, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002D904);

INCLUDE_ASM("asm/nonmatchings/800", func_8002DC68);


extern u8 D_8006A980;
extern s16 D_8006A982;
extern u8 D_8006A984;
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

extern void func_8002DC68(s32 a0, s32 a1);
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002DF80(void) {
    u8 v1;

    v1 = D_8006A980;
    if ((v1 & 0x7) != 0) {
        if ((v1 & 0x1) != 0 && (v1 & 0x2) != 0) {
            func_8002DC68(0x719, 0);
            D_8006A980 &= 0xF8;
        }

        if ((D_8006A980 & 0x7) != 0) {
            s16 val = D_8006A982;
            s32 a0;

            if (val <= 0) {
                a0 = 0x710;
            } else if (val >= 4) {
                a0 = 0x712;
            } else {
                a0 = 0x711;
            }

            func_8002DC68(a0, 0);
            D_8006A982 = 0;
            D_8006A980 &= 0xF8;
        }
    }

    v1 = D_8006A980;
    if ((v1 & 0x8) != 0) {
        u8 a1 = D_8006A984;

        if (a1 != 0) {
            func_8002DC68(0xA75, a1 | 0x1000);
            D_8006A984 = 0;
            D_8006A980 |= 0x10;
        } else {
            u8 v0;

            D_8006A980 = v1 & 0xEF;
            D_800A4F17 = 1;
            func_8002E138(4, 0xA75, 0);
            v0 = D_800A4F18;
            D_800A4F17 = v0;

            if (v0 != 0) {
                s16 v0s = D_800A4EFC;

                if (v0s != 0) {
                    D_800A4EFC = v0s - 1;
                }

                func_80030F80();
                func_8002D320();
                func_80031BE0();
                D_800A4F18 = 0;
                D_800A4F17 = 0;
            }
        }

        D_8006A980 &= 0xF7;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002E138);

extern u8 D_800A4F19;
extern void CdMix(u8 *);

void func_8002E5BC(void) {
    u8 sp10[4];

    sp10[0] = 0x5A;
    sp10[1] = 0x5A;
    sp10[2] = 0x5A;
    sp10[3] = 0x5A;
    CdMix(sp10);
    D_800A4F19 = 0;
}

extern u8 D_800A4F19;
extern void CdMix(u8 *);

void func_8002E5F8(void) {
    u8 sp10[4];

    sp10[0] = 0x80;
    sp10[1] = 0;
    sp10[2] = 0x80;
    sp10[3] = 0;
    CdMix(sp10);
    D_800A4F19 = 1;
}


extern u16 D_800A4E8E;
extern s16 D_800A4E86;
extern s32 D_80078F10;
extern u16 D_8006A99C[];
extern u16 D_800A46B8;
extern u8 D_8006AEEC;
extern s32 D_800A46B4;
extern u8 D_800A46BA;
extern u16 D_800A4EF4;

extern s32 func_8003836C(s32 a0);
extern void func_8002E700(s32 a0);

void func_8002E638(s32 a0) {
    s32 s0;
    s16 temp;
    u16 a0_masked;
    u16 v1;

    s0 = a0;

    if ((D_800A4E8E & 4) != 0) {
        temp = D_800A4E86;
        if ((func_8003836C(temp) << 16) != 0) {
            func_8002E700(s0 & 0xFFFF);
            return;
        }
    }

    if (D_80078F10 == 0) {
        return;
    }

    a0_masked = s0 & 0xFFFF;

    if (a0_masked < 5) {
        v1 = *(u16 *)((u8 *)D_8006A99C + a0_masked * 4);
    } else {
        v1 = 0x1F;
    }

    D_800A46B8 = v1;
    v1 = D_8006AEEC;
    D_800A46B4 = 0xFFFF;
    D_800A46BA = 1;
    D_800A4EF4 = v1;
}


extern u16 D_800A4E8E;
extern u16 D_800A4E8A;
extern s16 D_800A4E86;
extern s16 D_8006A9BC[];
extern u16 D_8006A9B0[];

extern s32 func_8003836C(s32 a0);
extern void func_8003819C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8002E700(s32 a0)
{
    u16 index;

    if ((D_800A4E8E & 0x4) == 0)
        return;

    if ((s16)func_8003836C(D_800A4E86) == 0)
        return;

    index = (u16)a0;
    if (index >= 5)
        index = 4;

    func_8003819C(D_800A4E86, 0, 0, D_8006A9BC[index]);
    D_800A4E8A = D_8006A9B0[index];
}

void func_8002E79C(s32 a0)
{
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE0;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9C8[];
    u8 *fl;
    u16 v;

    fl = &D_800A4EE6;
    if (!(*fl & 2)) {
        *fl |= 2;
        if (!(*fl & 4)) {
            v = (u16)a0;
            if (v >= 5) {
                v = 4;
            }
            D_800A4EE0 = 0x4000;
            D_800A4EE4 = 0x2FFF;
            D_800A4EE2 = D_8006A9C8[v];
            *fl |= 3;
        }
    }
}

void func_8002E818(s32 a0)
{
    extern u16 D_800A4E8E;
    extern u16 D_800A4E8C;
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE0;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9D4[];
    extern void func_8002EA10(void);
    register u8 *a1 __asm__("$5");
    u8 fl;
    u8 nw;
    u16 v;

    if ((D_800A4E8E & 0x4) != 0 && D_800A4E8C == 0x3E) {
        func_8002EA10();
    }

    a1 = &D_800A4EE6;
    fl = *a1;
    if (!(fl & 4)) {
        nw = fl | 4;
        *a1 = nw;
        if (!(nw & 2)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE0 = 0x4000;
            D_800A4EE4 = 0x2000;
            v = D_8006A9D4[(u16)a0];
            *a1 = fl | 5;
            D_800A4EE2 = v;
        }
    }
}

void func_8002E8DC(s32 a0)
{
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9E0[];
    register u8 *p __asm__("$6");
    u8 fl;
    u8 nw;
    u16 v;

    p = &D_800A4EE6;
    fl = *p;
    if (fl & 2) {
        nw = fl & 0xFD;
        *p = nw;
        if (!(fl & 4)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE4 = 0x4000;
            v = D_8006A9E0[(u16)a0];
            *p = nw | 1;
            D_800A4EE2 = v;
        }
    }
}

void func_8002E94C(s32 a0)
{
    extern u16 D_800A4E8E;
    extern u16 D_800A4E8C;
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE4;
    extern u16 D_800A4EE2;
    extern u16 D_8006A9EC[];
    extern void func_8002EAB0(void);
    register u8 *a1 __asm__("$5");
    u8 fl;
    u8 clr;
    u16 v;

    if ((D_800A4E8E & 0x4) != 0 && D_800A4E8C == 0x3E && (D_800A4E8E & 0x10) != 0) {
        func_8002EAB0();
    }

    a1 = &D_800A4EE6;
    fl = *a1;
    if (fl & 0x4) {
        clr = fl & 0xFB;
        *a1 = clr;
        if (!(fl & 0x2)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE4 = 0x4000;
            v = D_8006A9EC[(u16)a0];
            *a1 = clr | 0x1;
            D_800A4EE2 = v;
        }
    }
}

extern u16 D_800A4E8E;
extern s16 D_800A4E86;

extern s32  func_8003836C(s32 a0);
extern s32  func_800381E4(s32 a0, s32 a1);
extern void func_8002EC10(void);
extern void func_800383A4(s16 a0);

void func_8002EA10(void) {
    register u16 *s0 __asm__("$16");
    u16 v0;
    s32 ret;

    s0 = &D_800A4E8E;
    v0 = *s0;
    if (v0 & 4) {
        ret = func_8003836C(D_800A4E86);
        if ((ret << 16) != 0) {
            if (func_800381E4(D_800A4E86, 0) != 0) {
                func_8002EC10();
            } else {
                func_800383A4(D_800A4E86);
                *s0 = *s0 | 0x10;
            }
        }
    }
}


extern u16   D_800A4E8E;
extern s16   D_800A4E86;
extern void func_80038308(s16 a0);

void func_8002EAB0(void) {
    register u16 *s0 __asm__("$16");
    u16 v0;

    s0 = &D_800A4E8E;
    v0 = *s0;
    if ((v0 & 0x10) != 0) {
        func_80038308(D_800A4E86);
        v0 = *s0;
        v0 = (v0 | 0x9) & 0xFFEF;
        *s0 = v0;
    }
}

extern u16 D_800A4E8E;
extern s16 D_800A4E86;

extern s32  func_8003836C(s32 a0);
extern s32  func_800381E4(s32 a0, s32 a1);
extern void func_8002EC10(void);
extern void func_800383A4(s16 a0);
extern void func_80036F18(void);

void func_8002EB10(void) {
    u16 v0;
    s32 ret;

    v0 = D_800A4E8E;
    if (v0 & 4) {
        ret = func_8003836C(D_800A4E86);
        if ((ret << 16) != 0) {
            if (func_800381E4(D_800A4E86, 0) != 0) {
                func_8002EC10();
            } else {
                func_800383A4(D_800A4E86);
                D_800A4E8E = D_800A4E8E | 0x10;
            }
        }
    }
    func_80036F18();
}


extern void func_80036D58(int arg0);
extern void func_80038308(s16 arg0);
extern u16 D_800A4E8E;
extern s16 D_800A4E86;

void func_8002EBAC(void) {
    u16 v0;

    func_80036D58(0);

    if (D_800A4E8E & 0x10) {
        func_80038308(D_800A4E86);

        v0 = D_800A4E8E;
        v0 |= 0x9;
        v0 &= 0xFFEF;
        D_800A4E8E = v0;
    }
}


extern u16 D_800A4E8E;
extern s16 D_800A4E86;
extern u16 D_800A4E8C;
extern u16 D_800A4F20;
extern u16 D_800A4F22;
extern u16 D_800A4E8A;
extern u16 D_80068B66[][8];
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;
extern u16 D_800A4EA0;

extern s32 func_8003836C(s32 a0);
extern void func_800383A4(s16 a0);
extern void func_800384A8(s16 a0);
extern void func_800385C0(s16 a0);

void func_8002EC10(void) {
    u16 v0;
    s16 *s0;

    D_800A4F20 = 0;
    D_800A4F22 = 0;
    D_800A4E8A = 0;

    if (D_800A4E8E & 4) {
        if ((s16)func_8003836C(D_800A4E86) && (D_80068B66[D_800A4E8C][0] & 1)) {
            if (D_800A4EA2 & 4) {
                func_800385C0(D_800A4E9A);
                D_800A4EA2 &= 0xFEE8;
            }

            func_800383A4(D_800A4E86);

            v0 = D_800A4E8E;
            D_800A4E8E = v0 & 0xFFFD;
            D_800A4EA2 = v0 & 0xFFFD;
            D_800A4E9A = D_800A4E86;
            D_800A4EA0 = D_800A4E8C;
            D_800A4E8E = v0 & 0xFEF9;
            return;
        }

        s0 = &D_800A4E86;
        if ((s16)func_8003836C(*s0)) {
            func_800384A8(*s0);
        }

        D_800A4E8E &= 0xFEE8;
        func_800385C0(*s0);
    }
}


extern void func_8002EC10(void);
extern void func_800385C0(s16);
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;

void func_8002ED90(void) {
    u16* ptr;

    func_8002EC10();

    ptr = &D_800A4EA2;
    if (*ptr & 0x4) {
        func_800385C0(D_800A4E9A);
        *ptr = 0;
    }
}

extern void func_8002EE90(void);
extern void func_80031CC8(void);
extern void func_8002EC10(void);
extern void func_800385C0(s16);
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;
extern u8  D_800A4EE6;
extern s16 D_800A4EF6;

void func_8002EDE4(void) {
    func_8002EE90();
    func_80031CC8();
    func_8002EC10();

    if (D_800A4EA2 & 0x4) {
        func_800385C0(D_800A4E9A);
        D_800A4EA2 = 0;
    }

    D_800A4EF6 = 1;
    D_800A4EE6 &= 0xF9;
}

extern void func_80036EB4(void);
extern void func_8002EC10(void);

struct func_8002EE64_b { u8 c; };

void func_8002EE64(void) {
    s32 g1, g2, g3, g4;
    struct func_8002EE64_b b;

    b.c = 0x88;
    ((void (*)(s32, s32, s32, s32, struct func_8002EE64_b))func_80036EB4)(g1, g2, g3, g4, b);
    func_8002EC10();
}


extern void func_80036EE8(void);
extern void func_8002EC10(void);

void func_8002EE90(void) {
    func_80036EE8();
    func_8002EC10();
}

void func_8002EEB8(void) {
    func_80036EE8();
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002EED8);


extern void func_80034844(void);
extern void func_80031B7C(void);

void func_8002EFD0(void)
{
    func_80034844();
    func_80031B7C();
}


extern s32 D_800A2B98;
extern s32 D_800C7D20;

void func_8002EFF8(s32 a0, s32 a1)
{
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0_tmp __asm__("$4");

    v0 = 1;

    if (a0 == v0) {
        v0 = ~a1;
        v1 = D_800A2B98;
        a0_tmp = D_800C7D20;
        v1 = v1 & v0;
        a0_tmp = a0_tmp | a1;
        D_800A2B98 = v1;
        D_800C7D20 = a0_tmp;
    } else {
        v0 = ~a1;
        v1 = D_800C7D20;
        a0_tmp = D_800A2B98;
        v1 = v1 & v0;
        a0_tmp = a0_tmp | a1;
        D_800C7D20 = v1;
        D_800A2B98 = a0_tmp;
    }
}


extern s32 D_800A2BA0;
extern s32 D_800C7D2C;

void func_8002F064(s32 a0, s32 a1) {
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 out_a0 __asm__("$4");

    if (a0 == 1) {
        v0 = ~a1;
        v1 = D_800A2BA0;
        out_a0 = D_800C7D2C;
        v1 = v1 & v0;
        out_a0 = out_a0 | a1;
        D_800A2BA0 = v1;
        D_800C7D2C = out_a0;
    } else {
        v0 = ~a1;
        v1 = D_800C7D2C;
        out_a0 = D_800A2BA0;
        v1 = v1 & v0;
        out_a0 = out_a0 | a1;
        D_800C7D2C = v1;
        D_800A2BA0 = out_a0;
    }
}

extern s32 D_800A64B0;

void func_8002F0D0(void) {
    s32 i = 0x54;
    do {
        *(s32 *)((s32)&D_800A64B0 + i) = 0;
        i -= 0xC;
    } while (i >= 0);
}


extern s32 D_800A64B0;

void *func_8002F0F4(void) {
    s32 *ptr = (s32 *)&D_800A64B0;
    s32 i = 0;

    while (i < 8) {
        s32 val = *ptr;
        if (val == 0) {
            return (void *)ptr;
        }
        i++;
        ptr = (s32 *)((s32)ptr + 0xC);
    }

    return 0;
}

void func_8002F12C(s32 a0) {
    extern void func_8002DC68(s32 a0, s32 a1);
    func_8002DC68(*(s32 *)(a0 + 4), 0);
}

extern u8 D_800A4694[];

void func_8002F150(s32 arg0) {
    struct F150Rec {
        u8 pad[0x0E];
        u8 flg[8];
        u8 tail[0x3E];
    };
    struct F150Slot {
        u8 pad[0x20];
        u32 u20;
        u32 u24;
        u32 u28;
        u32 u2C;
        u16 u30;
        u8 mid[5];
        u8 u37;
        u8 u38;
        u8 tail[0x1B];
    };

    struct F150Rec *rec = (struct F150Rec *)D_800A4694 + arg0;
    struct F150Slot *slots = (struct F150Slot *)(D_800A4694 + 0x2F4);
    s32 i;
    s32 val;

    for (i = 0, val = -0x18; i < 8; i++) {
        if (rec->flg[i]) {
            slots[i].u28 = slots[i].u20 - 0x100;
            slots[i].u37 |= 1;
            slots[i].u30 = 0;
            slots[i].u38 = 0;
            slots[i].u2C = val;
        }
    }
}

typedef struct F1ccRec {
    u8 pad[0x0E];
    u8 flg[8];
    u8 tail[0x3E];
} F1ccRec;

typedef struct F1ccSlot {
    u8 pad[0x20];
    u32 u20;
    u32 u24;
    u32 u28;
    u32 u2C;
    u16 u30;
    u8 mid[5];
    u8 u37;
    u8 u38;
    u8 tail[0x1B];
} F1ccSlot;

extern u8 D_800A4694[];

void func_8002F1CC(s32 arg0) {
    F1ccRec *sp = (F1ccRec *)D_800A4694 + arg0;
    F1ccSlot *slots = (F1ccSlot *)(D_800A4694 + 0x2F4);
    s32 i;
    s32 val;

    for (i = 0, val = 0x18; i < 8; i++) {
        if (sp->flg[i]) {
            slots[i].u28 = slots[i].u20 + 0x100;
            slots[i].u37 |= 1;
            slots[i].u30 = 0;
            slots[i].u38 = 0;
            slots[i].u2C = val;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002F248);


/* func_8002F4E4 -- 6-level gauntlet lookup into the D_800A4EE8 owner block.
 *
 * TU-placement note (src/800.c): this function's INCLUDE_ASM sits at ~line 9410,
 * BEFORE the file declares `typedef struct Owner4EE8 {...}` (~9756, whose first
 * 0x14 bytes are an opaque pad00 that THIS function is the one to break out into
 * fields) and BEFORE `typedef ... Rsc24` / `extern Rsc24 D_800A4640[];` (~10860/10885).
 * So local equivalents are declared here.
 *
 * The two object externs are declared at BLOCK scope on purpose. A second
 * FILE-scope declaration of D_800A4640 / D_800A4EE8 with a different (local)
 * struct type is a hard error under the pinned cc1 ("conflicting types for
 * `D_800A4640'", rc=33) once the real ones appear later in the TU; the same
 * pair at block scope is only a warning ("type mismatch with previous external
 * decl") and compiles clean. Codegen is identical either way -- verified.
 */

/* D_800A4640 element -- same layout as the TU's own `Rsc24` (src/800.c ~13288,
 * declared later in the file than this function's INCLUDE_ASM slot, so it
 * can't be named directly here). Spelled with the TU's own typedef NAME
 * ("Rsc24", block-scoped -- shadows harmlessly, since the file-scope typedef
 * of the same name/shape doesn't exist yet at this point in the TU) and the
 * TU's own field-list TEXT verbatim, with no inline offset comments: the
 * reconciler's cosmetic-typedef check is a literal body-text comparison
 * against src/800.c's `Rsc24`, and per-field offset comments here (the TU's
 * copy has only one trailing offset tag, after the closing brace, not one
 * per field) made the two bodies textually differ and tripped
 * refuse-DIFFERENT-STRUCT even though the layouts are identical
 * field-for-field. */

/* opaque — matches the TU's `typedef struct Owner4EE8 Owner4EE8;` spelling
 * (src/800.c ~13559) exactly so this local decl is droppable at bank time in
 * favor of the TU's real `typedef struct Owner4EE8 { u8 pad00[0x14]; Rec14
 * **unk14; } Owner4EE8;`. This function only ever touches fields that live
 * inside pad00, so it pointer-casts through the opaque type at each byte
 * offset (same pattern as func_80034314 / func_8002C8F4) rather than naming
 * a same-named struct with a conflicting layout. */

extern s16 D_800A4EF0;

s32 func_8002F4E4(u8 *a0) {
    extern Rsc24 D_800A4640[];
    extern Owner4EE8 *D_800A4EE8;
    Owner4EE8 *a2;
    s32 idx;
    s32 lvl;
    s32 val;
    s32 idx2;
    s32 word;
    s32 rowBytes;
    u16 *row;

    if (D_800A4EF0 == 0) {
        return 0;
    }

    a2 = D_800A4EE8;
    if (a2 == 0) {
        return 0;
    }

    idx = a0[2];
    lvl = D_800A4640[idx].unk00;

    if (lvl < *(s16 *)((u8 *)a2 + 0x04)) {
        return 0;
    }
    lvl -= *(s16 *)((u8 *)a2 + 0x04);

    if (lvl >= *(s16 *)((u8 *)a2 + 0x02)) {
        return 0;
    }

    val = (*(s16 **)((u8 *)a2 + 0x08))[lvl];
    if (val == 0) {
        return 0;
    }

    idx2 = a0[3];
    if (idx2 >= *(s16 *)((u8 *)a2 + 0x0C)) {
        return 0;
    }
    val -= 1;

    /* Row stride is in BYTES and must stay bound to unk0E: writing
     * idx2 * (unk0E * 2) inline lets gcc reassociate it to
     * (idx2 * 2) * unk0E (sll a0 then mult) -- the separate rowBytes
     * local pins mult $a0,$v0 with $v0 = unk0E*2, as the target has.
     * The `row` pointer temp is also load-bearing: it is what keeps val
     * in $a1 and puts val*2 into a fresh $v0. NO register pins -- pinning
     * val to $5 (first-pass attempt) makes the shift go in-place into $a1
     * and reorders the mult delay shadow (sll before lw). Cookbook lever C:
     * the fix was to UNPIN.
     */
    rowBytes = *(s16 *)((u8 *)a2 + 0x0E) * 2;
    row = (u16 *)((u8 *)(*(u16 **)((u8 *)a2 + 0x10)) + idx2 * rowBytes);
    word = row[val];

    if (word != 0x7F) {
        return word;
    }

    return 0;
}


extern s16 D_800A4EF0;
extern void func_8002F620(void);

void func_8002F5C8(u8 *a0) {
    extern Owner4EE8 *D_800A4EE8;
    s16 *p = &D_800A4EF0;
    u16 temp;

    if (*p != 0) {
        func_8002F620();
    }
    temp = *(u16 *)a0;
    D_800A4EE8 = a0;
    *p = temp;
}


extern s16 D_800A4EF0;
extern void func_80031D70(void);

void func_8002F620(void) {
    D_800A4EF0 = 0;
    func_80031D70();
}

extern s16 D_800A4EF0;
s16 func_8002F648(void) {
    return D_800A4EF0;
}

extern u8  D_800A4698;
extern s16 D_800A4688;

s32 func_8002F658(void) {
    if (D_800A4698 != 0) {
        return -1;
    }
    return D_800A4688;
}


extern u8  D_800A4698;
extern s16 D_800A4688;
extern s16 D_800C5328[];
extern s16 D_800A46A2;
extern u8  D_800A46B0;

extern void func_800415A8(s32);

void func_8002F67C(void) {
    u8 *p = &D_800A4698;
    s32 v0;
    s32 t;

    if (*p == 0) {
        v0 = D_800A4688;
        *(s16 *)((u8 *)D_800C5328 + (v0 << 2)) = -1;
        *p = 1;
    }

    t = D_800A46A2;
    if (t >= 0) {
        func_800415A8(t);
        D_800A46A2 = -1;
    }

    if (D_800A46B0 == 0) {
        D_800A46B0 = 1;
    }
}


extern u8 D_800760D0;
extern u8 D_800760D4;
extern u8 D_800760D8;
extern u8 D_800760DC;
extern u8 D_8006A96E;
extern void (*D_800A4F24)(void);

extern void func_8002F80C(void);

void func_8002F714(s32 a0, s32 a1) {
    switch (a0 & 0xFFFF) {
        case 0:
            D_800760D0 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 1;
            break;
        case 1:
            D_800760D4 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 2;
            break;
        case 2:
            D_800760D8 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 4;
            break;
        case 3:
            D_800760DC = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 8;
            break;
    }
}

extern u8 D_8006A96E;
extern s16 D_8006A96C;
extern u8 D_800760D0;
extern u8 D_800760D4;
extern u8 D_800760D8;
extern u8 D_800760DC;
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;
extern void (*D_800A4F24)(void);

extern void func_8002DC68(s32 a0, s32 a1);
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002F80C(void) {
    u8 flag;
    s16 max;
    u8 a0;
    u8 v0;

    flag = 0;
    max = 0;
    if ((D_8006A96E & 1) != 0) {
        flag = 1;
        max = D_800760D0;
    }
    if ((D_8006A96E & 2) != 0) {
        flag = 1;
        if (max < D_800760D4) {
            max = D_800760D4;
        }
    }
    if ((D_8006A96E & 4) != 0) {
        flag = 1;
        if (max < D_800760D8) {
            max = D_800760D8;
        }
    }
    if ((D_8006A96E & 8) != 0) {
        flag = 1;
        if (max < D_800760DC) {
            max = D_800760DC;
        }
    }

    a0 = D_8006A96E;
    D_8006A96E = a0 & 0xF0;

    if (flag != 0) {
        D_8006A96C = 0x10;
        if (max != 0) {
            func_8002DC68(0xBEB, max | 0x1000);
            D_8006A96E |= 0x10;
            return;
        }
        if ((a0 & 0x10) == 0) {
            return;
        }
        D_800A4F17 = 1;
        func_8002E138(4, 0xBEB, 0);
        v0 = D_800A4F18;
        D_800A4F17 = v0;
        if (v0 != 0) {
            s16 c = D_800A4EFC;
            if (c != 0) {
                D_800A4EFC = c - 1;
            }
            func_80030F80();
            func_8002D320();
            func_80031BE0();
            D_800A4F18 = 0;
            D_800A4F17 = 0;
        }
    } else {
        s16 t = D_8006A96C;
        if (t == 0) {
            return;
        }
        t = t - 1;
        D_8006A96C = t;
        if (t != 0) {
            return;
        }
        if ((a0 & 0x10) == 0) {
            return;
        }
        D_800A4F17 = 1;
        func_8002E138(4, 0xBEB, 0);
        v0 = D_800A4F18;
        D_800A4F17 = v0;
        if (v0 != 0) {
            s16 c = D_800A4EFC;
            if (c != 0) {
                D_800A4EFC = c - 1;
            }
            func_80030F80();
            func_8002D320();
            func_80031BE0();
            D_800A4F18 = 0;
            D_800A4F17 = 0;
        }
    }

    D_800A4F24 = 0;
    D_8006A96E = D_8006A96E & 0xEF;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002FA3C);


extern s16 D_800A46CC;

void func_8002FAE0(void) {
    D_800A46CC = 0;
    func_8002C8BC();
}



extern void func_800301A4(void);
extern int  func_80037CD8(void *arg);
extern void func_80031A98(void);
extern void func_8002EC10(void);
extern void func_800415A8(s32);



extern Elm12 D_80064D49[];
extern u8    D_80064D4D[];
extern Ent24 D_800A463C[];
extern Rsc24 D_800A4640[];
extern s16   D_800A4642[];
extern u8    D_800A4650[];
extern s32   D_800A46C8;
extern s16   D_800A46CC;
extern s16   D_800C5328[];
extern u8    D_8006AEF4;

int func_8002FB08(int entry) {
    s32 idx12;
    s32 b;
    s32 idx24;
    s16 h;
    s32 b2;
    s32 idx24b;
    s16 v;
    s16 a4;

    if (func_80037CD8((void *)func_800301A4) == 0) {
        return 0;
    }
    idx12 = entry * 12;
    b = D_80064D49[entry].unk00;
    idx24 = b * 24;
    D_800A46C8 = *(s32 *)((u8 *)D_800A463C + idx24);
    if (D_800A4650[idx24] == 0) {
        h = *(s16 *)((u8 *)D_800A4640 + idx24);
        D_800C5328[h * 2] = -1;
    }
    func_80031A98();
    b2 = D_80064D4D[idx12];
    if (b2 != 0) {
        idx24b = b2 * 24;
        v = *(s16 *)((u8 *)D_800A4642 + idx24b);
        if (v >= 0) {
            func_8002EC10();
            a4 = *(s16 *)((u8 *)D_800A4642 + idx24b);
            func_800415A8(a4);
            *(s16 *)((u8 *)D_800A4642 + idx24b) = -1;
            *(s16 *)((u8 *)D_800A4640 + idx24b) = -1;
        }
        D_800A4650[idx24b] = 1;
    }
    D_800A46CC = 0;
    D_8006AEF4 |= 2;
    return 1;
}


extern s32  func_8003C4F0(s32);
extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);
extern void func_80037D74(void);
extern u8   D_8006AEF4;
extern s32  D_800A46C8;

int   func_8002FC64(int nbytes, u32 *src);   /* stage/copy a payload run */
int   func_8002FC64(int nbytes, u32 *src)
{
    register s32 s2 __asm__("$18") = nbytes;
    register u32 *s1 __asm__("$17") = src;
    register s32 *s0;
    s32 result;

    if (D_8006AEF4 & 1) {
        if (func_8003C4F0(0) == 0) {
            func_80037D74();
            return 0;
        }
    }

    s0 = (s32 *)(&D_800A46C8);
    result = ((s32 (*)(s32))func_8003C498)(*s0);

    if (result != 0) {
        SpuWrite((s32)s1, s2);
        *s0 += s2;
        D_8006AEF4 |= 1;
        return 1;
    }

    func_80037D74();
    return 0;
}


extern s16 D_800A46CC;
extern u8  D_8006AEF4;

extern void  func_80037D74(void);
extern s32   func_8003C4F0(s32);
extern s32   func_8002FF0C(s32, s32);
extern void  func_8002D240(s32 a0);

int func_8002FD14(int buf, int len) {
    s32 result;
    s32 temp;

    if (D_800A46CC == 0) {
        func_80037D74();
        temp = func_8003C4F0(0);
        if (temp != 0) {
            D_8006AEF4 &= 0xFE;
            result = func_8002FF0C(buf, len);
        } else {
            result = 0;
        }
    } else {
        result = func_8002FF0C(buf, len);
    }

    if (result != 0) {
        if (buf == 0x1A) {
            func_8002D240(0x28);
        }
        return result;
    }

    return 0;
}

extern void func_80037D74(void);

void func_8002FDC8(void) {
    func_80037D74();
}

INCLUDE_ASM("asm/nonmatchings/800", func_8002FDE8);

INCLUDE_ASM("asm/nonmatchings/800", func_8002FF0C);

extern u8  D_8006AEF4;
extern s16 D_800A46CC;

s32 aF800301A4(void) __asm__("func_800301A4");
s32 aF800301A4(void) {
    u8 t;

    t = D_8006AEF4;
    D_800A46CC = 0;
    D_8006AEF4 = t & ~2;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800301C8);

extern void func_800301A4(void);
extern s32 func_80037CD8(void *arg);
extern s16 D_800A46CC;
extern u8 D_8006AEF4;

s32 func_80030470(void) {
    s16 *p;

    if (func_80037CD8((void *) func_800301A4) != 0) {
        p = &D_800A46CC;
        *p += 1;
        D_8006AEF4 |= 2;
    }
    return 0;
}

extern u8  D_8006AEF4;
extern s16 D_800A46CC;
extern s32 func_8003C4F0(s32);

s32 func_800304C8(void) {
    s16 *p;

    if (D_8006AEF4 & 1) {
        if (func_8003C4F0(0) != 0) {
            D_8006AEF4 &= 0xFE;
        }
    } else {
        p = &D_800A46CC;
        (*p)++;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80030538);

INCLUDE_ASM("asm/nonmatchings/800", func_80030634);





typedef struct {
    u8  unk00[4];
    u8  unk04;
    u8  unk05[11];
    u16 unk10;
    u16 unk12;
    u8  unk14[2];
    s16 unk16;
    u8  unk18[8];
} Blk28;                       /* 0x20 */

extern u8    D_8006AEF4;
extern s16   D_800A46CC;
extern s16   D_800A46CE[];
extern s16   D_800A46D2[];
extern Rsc24 D_800A4640[];
extern A12   D_80064D44[];
extern s32   D_80065504[];
extern B12 *D_8006A970[];
extern s32   D_800760F0;
extern s32   D_800760F4;
extern s16   D_800C5328[];
extern s16   D_800C532A[];

extern s16  func_80042374(s32);
extern void func_80037D74(void);
extern s16  func_8003F144(s32, s32, s32, C24 *);
extern s32  func_8003F380(s32, s32);

s32 func_80030730(void) {
    Blk28 sp10;
    A12 *e;
    B12 *p;
    u8 *q;
    s16 *pd;
    s16 *pcc;
    s32 n;
    s32 n0;
    s32 k;
    s32 i;
    s32 res;

    if (func_80042374(0) == 0) {
        return 0;
    }
    D_8006AEF4 &= 0xFC;
    func_80037D74();

    k = D_800A46CE[0] * 24;
    D_800760F0 = 0;
    e = &D_80064D44[D_800A46CE[1]];
    n0 = e->pad04[0];
    D_800760F4 = n0;
    if (n0 == 0) {
        *(u8 *)((u8 *)D_800A4640 + k + 0x10) = 0;
        D_800A46CC = 0;
        return 1;
    }
    q = e->unk00;
    if (D_80065504[D_800A46CE[0]] < n0) {
        D_800760F4 = D_80065504[D_800A46CE[0]];
    }
    p = D_8006A970[D_800A46CE[0]];
    n = 10;
    if (D_800760F4 < 11) {
        if (e->unk06 != 0) {
            *(s16 *)((u8 *)D_800A4640 + k + 0x06) = e->unk07;
            D_800A4640[D_800A46CE[0]].unk04 = e->unk06;
            D_800A4640[D_800A46CE[0]].unk08 = e->unk08;
            D_800C532A[e->unk08 * 2] = D_800A46CE[0];
        }
        n = D_800760F4;
        D_800760F4 = 0;
        D_800C5328[D_800A46CE[1] * 2] = D_800A46CE[0];
    } else {
        D_800760F4 -= 10;
    }

    for (i = 0; i < n; i++, q += 2, p++) {
        pd = D_800A46D2;
        if (func_8003F144(*pd, q[0], q[1], (C24 *)&sp10) == 0) {
            res = func_8003F380(*pd, sp10.unk16);
            if (res >= 0) {
                p->unk0A = 1;
                p->unk04 = sp10.unk04 << 8;
                p->unk00 = res;
                p->unk06 = sp10.unk10;
                p->unk08 = sp10.unk12;
            }
        }
    }

    if (D_800760F4 == 0) {
        D_800A4640[D_800A46CE[0]].unk10 = 0;
        D_800A46CC = 0;
        return 1;
    }
    pcc = &D_800A46CC;
    D_800760F0 = D_800760F0 + 10;
    (*pcc)++;
    return 0;
}


/* 0x0C stride record at D_80064D44 (D_80064D4A == this + 6, cf. src/800.c Rsc12) */

/* 0x0C stride record pointed at by D_8006A970[] */

/* 0x18 scratch filled by func_8003F144 */

extern s16 D_800A46CC;
extern s16 D_800A46CE[];
extern s16 D_800A46D0;
extern s16 D_800A46D2[];

extern s16 D_800A4644[];
extern s16 D_800A4646[];
extern s16 D_800A4648[];
extern u8  D_800A4650[];

extern s16 D_800C5328[];
extern s16 D_800C532A[];

extern A12  D_80064D44[];
extern B12 *D_8006A970[];

extern s32 D_800760F0;
extern s32 D_800760F4;

extern s16 func_80042374(s32);
extern s16 func_8003F144(s32, s32, s32, C24 *);
extern s32 func_8003F380(s32, s32);

s32 func_80030A14(void) {
    C24 sp10;
    A12 *e;
    u8 *p;
    B12 *q;
    s32 count;
    s32 i;
    s32 r;
    s32 t;

    if (func_80042374(0) == 0) {
        return 0;
    }

    e = &D_80064D44[D_800A46D0];
    p = e->unk00 + D_800760F0 * 2;
    q = &D_8006A970[D_800A46CE[0]][D_800760F0];
    t = D_800A46CE[0] * 24;

    if (D_800760F4 < 11) {
        if (e->unk06 != 0) {
            *(s16 *)((u8 *)D_800A4646 + t) = e->unk07;
            D_800A4644[D_800A46CE[0] * 12] = e->unk06;
            D_800A4648[D_800A46CE[0] * 12] = e->unk08;
            D_800C532A[e->unk08 * 2] = D_800A46CE[0];
        }
        count = D_800760F4;
        D_800760F4 = 0;
        D_800C5328[D_800A46D0 * 2] = D_800A46CE[0];
    } else {
        count = 10;
        D_800760F4 -= 10;
    }

    for (i = 0; i < count; i++, p += 2, q++) {
        if (func_8003F144(D_800A46D2[0], p[0], p[1], &sp10) == 0) {
            r = func_8003F380(D_800A46D2[0], sp10.unk16);
            if (r >= 0) {
                q->unk0A = 1;
                q->unk04 = sp10.unk04 << 8;
                q->unk00 = r;
                q->unk06 = sp10.unk10;
                q->unk08 = sp10.unk12;
            }
        }
    }

    if (D_800760F4 == 0) {
        D_800A4650[D_800A46CE[0] * 24] = 0;
        D_800A46CC = 0;
        return 1;
    }

    D_800760F0 += 10;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80030CA4);



typedef struct Blk48_30D80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 pad04[0x3D];
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 pad42[6];
} Blk48_30D80;

extern s8 D_800A4F17;
extern s32 D_800C7D20;
extern s32 D_80073140[];
extern Blk48_30D80 D_800A4C2C[];

extern void func_8002EFF8(s32 a0, s32 a1);
extern void func_80031988(Ent30D80 *arg0);

void func_80030D80(Ent30D80 *arg0, s16 arg1) {
    u8 old;
    u8 flag;

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    if (arg0->unk00 != 0) {
        flag = 1;
        arg0->unk00 = 0;
    } else if (arg0->unk4E >= 2 && (D_800C7D20 & D_80073140[arg0->unk0A])) {
        D_800A4C2C[arg0->unk51].unk41 = 1;
        D_800A4C2C[arg0->unk51].unk00 &= 0xFFF9FFFF;
        flag = 1;
        func_8002EFF8(0, D_80073140[arg0->unk0A]);
    } else {
        flag = 0;
        if (arg1 != 0) {
            arg0->unk50 = 1;
            D_800A4C2C[arg0->unk51].unk41 = 1;
            D_800A4C2C[arg0->unk51].unk00 &= 0xFFF9FFFF;
            func_8002EFF8(0, D_80073140[arg0->unk0A]);
        } else {
            s32 mask = D_80073140[arg0->unk0A];
            arg0->unk50 = 0;
            func_8002EFF8(0, mask);
            func_80031988(arg0);
        }
    }

    if (arg0->unk40 != 0) {
        arg0->unk40(arg0->unk51, arg0->unk44);
    }
    arg0->unk40 = 0;
    if (flag) {
        arg0->unk4E = 0;
    }

    *(u8 *)&D_800A4F17 = old;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80030F80);


typedef struct Obj {
    /* 0x00 */ u8 unk00[0xA];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 unk12[0x12];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u8 unk32[0x5];
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E[0x13];
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52[2];
} Obj;


/* 0x0C stride record pointed at by D_8006A970[] -- must match src/800.c's B12
   (same name, same offsets/widths) since the destination TU already declares
   this struct and symbol. */

extern Slot D_800A4C28[];
extern s32 D_80073140[];
extern B12 *D_8006A970[];
extern u16 D_8006AB30[];
extern u16 D_8006AB32[];

void func_800314DC(Obj *p) {
    Slot *e;
    /* dead local: the target frame is `vars= 8` with no $sp reference. */
    s32 pad[2];
    u16 h;
    u32 t;
    /* $2 pin #1 -- `base` is a LOCAL qty in the D_800A4C28 block. Unpinned,
       local-alloc.c:1825 combine_regs TIES its dest into operand 0 of the
       addu (the dying `t & 0xFF00` temp, which lives in $v1), so base lands
       in $v1; the target keeps it in $v0. A hard-reg dest cannot be tied, so
       the pin materialises base in $v0 exactly where the target has it. */
    register s32 base __asm__("$2");
    u32 d;
    u32 res;
    /* $2 pin #2 (disjoint lifetime from `base`) -- see the lerp comment. */
    register u32 q __asm__("$2");

    if (!(p->unk37 & 1)) {
        return;
    }

    if (p->unk30 != 0) {
        p->unk30--;
        return;
    }

    if (p->unk2C < 0) {
        p->unk24 += p->unk2C;
        if (p->unk24 <= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    } else {
        p->unk24 += p->unk2C;
        if (p->unk24 >= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    }

    if (!(p->unk37 & 1) && p->unk38 != 0) {
        if (p->unk24 != p->unk3C) {
            p->unk28 = p->unk3C;
            if (p->unk3C < p->unk24) {
                p->unk2C = -p->unk3A;
            } else {
                p->unk2C = p->unk3A;
            }
        }
        p->unk38 = 0;
        p->unk37 |= 1;
    }

    e = &D_800A4C28[p->unk51];
    e->unk00 = D_80073140[p->unk0A];
    h = D_8006A970[p->unk10][p->unk0C].unk04;
    /* `t` MUST be a separate SImode local: a HImode `h` used both by the
       0x18 store and by SImode arithmetic is what keeps the otherwise
       redundant `andi $v0,$a0,0xFFFF` alive (folding it away costs an insn). */
    t = h;
    /* splitting the -0x3C00 off keeps the sh scheduled AFTER the andi/sll/sra
       chain: as one expression the store's memory dependence on the 0x24 load
       gives it enough sched1 priority to hoist into the load-delay region. */
    base = (t & 0xFF00) + ((s8)t * 2);
    e->unk18 = h;
    base -= 0x3C00;
    /* in-place update: the target reuses $a1 for both the 0x24 load and the
       difference, and global.c has no coalescing (K8) -- cross-block sharing
       has to be ONE pseudo in the source. */
    d = p->unk24;
    d -= base;
    if (d >= 0x5300) {
        res = 0x3FFF;
    } else {
        /* `q` merges the D_8006AB30 load with the first product into one
           $v0-pinned range. That blocks $v0 across insns 4..11 of this block,
           which is what pushes 0x100 -> $v1, the index -> $a0, the D_8006AB32
           load -> $v1, and (via the global pass) the second mflo -> $v1. */
        q = D_8006AB30[d >> 8];
        q = q * (0x100 - (d & 0xFF));
        res = (q + D_8006AB32[d >> 8] * (d & 0xFF)) >> 8;
    }
    e->unk14 = res;
    e->unk40 = p->unk0A;
    if (e->unk44 != 0) {
        e->unk04 |= 0x10;
    } else {
        e->unk44 = 1;
        e->unk04 = 0x10;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_800316F8);

INCLUDE_ASM("asm/nonmatchings/800", func_80031988);

INCLUDE_ASM("asm/nonmatchings/800", func_80031A98);


extern u8 D_800A49D2[];

void func_80031B7C() {
    register s32 a0 asm("$4") = 0;
    register u8 a2 asm("$6") = 1;
    register u16 a1 asm("$5") = 0x7FFF;
    register u8 *v1 asm("$3");

    v1 = D_800A49D2;

    do {
        if (v1[4] && !v1[2] && v1[3]) {
            v1[2] = a2;
            *(u16 *)v1 = a1;
        }
        v1 += 0x54;
        a0++;
    } while (a0 < 8);
}


extern s8 D_800A4F17;
extern u16 D_800A2BB0[];
extern u16 D_800BA108[];

extern void func_8003388C(void *a0, s32 a1);

void func_80031BE0(void)
{
    u8 *e;
    s32 i;

    if (*(u8 *)&D_800A4F17 != 0) {
        return;
    }

    e = (u8 *)&D_800A4F17 - 0x82F;

    for (i = 0; i < 8; i++, e += 0x54) {
        u16 v1;

        D_800A2BB0[i] = *(u16 *)(e + 4);
        D_800BA108[i] = *(u16 *)(e + 6);

        v1 = *(u16 *)(e + 0) & 0x3F;
        switch (v1) {
        case 1:
            if (*(u16 *)(e + 8) != 0) {
                *(u16 *)(e + 8) = *(u16 *)(e + 8) - 1;
            }
            break;
        case 0:
            break;
        case 5:
            func_8003388C(e, i);
            break;
        }
    }
}

void func_80031CC8(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    extern void func_80034650(u8 *a0, s32 a1);
    u8 *p;
    s32 i;

    p = (u8 *)D_800A46E8;
    i = 0;
    do {
        switch (*(u16 *)p & 0x3F) {
        case 1:
            if (p[0xA] != 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034650(p, 0);
            break;
        }
        i += 1;
        p += 0x54;
    } while (i < 8);
}

void func_80031D70(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        if (((*p & 0x3F) == 1) && (*(u8 *)(p + 5) != 0)) {
            func_8003350C(i, 0);
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

void func_80031DEC(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    extern void func_80034A54(s32 a0);
    u16 *p;
    s32 i;
    p = D_800A46E8;
    i = 0;
    do {
        switch (*p & 0x3F) {
        case 1:
            if ((*p & 0x40) == 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034A54((s32)p);
            break;
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

void func_80031E94(void) {
    extern u16 D_800A46E8[];
    extern void func_80034A9C(void *a0);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        if ((*p & 0x3F) != 1 && (*p & 0x3F) == 5) {
            func_80034A9C(p);
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

extern u16 D_800A46E8[];
extern void func_8003350C(s32, s32);
extern void func_80034AE0(void *);

void func_80031F14(void) {
    u8 *p;
    s32 i;

    p = (u8 *)D_800A46E8;
    i = 0;
    do {
        switch (*(u16 *)p & 0x3F) {
        case 1:
            if (p[0xA] != 0 && (*(u16 *)p & 0x40) == 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034AE0(p);
            break;
        }
        i += 1;
        p += 0x54;
    } while (i < 8);
}

void func_80031FC8(void) {
    extern u16 D_800A46E8[];
    extern void func_80034B0C(s32 a0);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        switch (*p & 0x3F) {
        case 1:
            break;
        case 5:
            func_80034B0C((s32)p);
            break;
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}


/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

extern s32 func_800331D4(s32);
extern s32 func_8003310C(s32);
extern void func_800335B8(s32, s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_80032048(u32 arg0, u8 *p, u32 flags) {
    Rec14 *rec;
    Slot54 *e;
    s32 idx;
    s32 ret;
    u32 x;
    u32 y;
    u32 v;
    u8 old;
    u8 b1;
    u8 b2;
    u32 b3;
    u32 b0;

    y = arg0 >> 16;
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    ret = 0;
    v = rec->unk00;
    if ((u16)flags == 0xFFFF) {
        flags = 0;
        x = (u16)y;
        y = 0;
    } else {
        x = arg0;
    }

    idx = func_800331D4(x);
    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        } else if (flags & 0x1000) {
            if ((flags & 0x7F) < 0x30) {
                v >>= 1;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
    } else {
        if (flags & 0x4000) {
            func_800335B8(idx - 1, (u16)flags);
            goto done;
        }
        idx--;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    *(u8 *)&D_800A4F17 = old;
    return ret;
}


/* ---- declarations copied verbatim from the destination TU (src/800.c, the
 * block that precedes the already-matched sibling func_80032048) ----
 *
 * BANKING NOTE: src/800.c ALREADY has every typedef (Rec14 / Slot54 /
 * Owner4EE8, lines 7327-7350) and every extern below (lines 7353-7363),
 * immediately above `INCLUDE_ASM(... func_800322A8)` at line 7456.  They are
 * reproduced here only so this file compiles standalone under match_one.
 * When banking, replace the INCLUDE_ASM with the FUNCTION BODY ONLY (plus the
 * SLOT_BASE #define) -- re-emitting the typedefs would be a C89 redefinition
 * error.  src/800.c has NO prior declaration of func_800322A8, so there is no
 * DEF-side signature wall (cookbook Sec.20). */

/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

extern s32 func_800331D4(s32);
extern s32 func_8003310C(s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

/* The slot table base D_800A46E8 sits 0x82F bytes below the D_800A4F17 lock
 * byte and the original code derives one from the other (`addiu v1,s1,-0x82F`),
 * i.e. they live in one object.  Spelling it this way is what makes gcc CSE the
 * two symbol addresses into a single base register instead of emitting a second
 * lui/addiu pair (worth 2 instructions plus the whole callee-save ranking). */
#define SLOT_BASE ((u8 *)&D_800A4F17 - 0x82F)

/* SECOND-PASS LEVER (sched.md S13, the bb0 head-skip escape).  A first pass got
 * to 3-off with a pure prologue-schedule residual: sched2 emitted
 * `sw s5 / move s5 / srl` where the target has `srl / sw s5 / move s5`.
 * Cause (read off the -dS dumps, not guessed): sched.c:3189-3213 pins the
 * LEADING RUN of `pseudo = hard-arg-reg` param copies out of sched1's pool, so
 * the a2->flags copy always kept a LOWER LUID than the `srl`; at sched2's T-15
 * all three candidates tie at priority 1 and rank_for_schedule falls through to
 * the LUID tie-break (2.7.2 sched.c:2428, highest LUID picked first = placed
 * last), which put the srl last of the three.
 * Fix: take the third parameter through a BODY-LOCAL copy declared AFTER
 * `y = arg0 >> 16`.  The head copy `pseudo = $a2` becomes a nop-move at reload
 * (local-alloc ties the once-used incoming pseudo to $a2) and the REAL
 * `move s5,a2` materialises at its statement position, where the S2 birthing
 * boost sinks it below the srl -- giving it the HIGHER LUID.  sched2 then picks
 * it first, `sw s5` follows on the potential-hazard rule, and the srl lands at
 * position 3.  Do NOT reorder `flags = arg2;` above `y = arg0 >> 16;`. */
s32 func_800322A8(u32 arg0, u8 *p, u32 arg2) {
    Rec14 *rec;
    Slot54 *e;
    s32 idx;
    s32 ret;
    u16 y;
    u32 x;
    u32 flags;
    u32 v;
    u8 old;
    u8 b1;
    u8 b2;
    u32 b3;
    u32 b0;

    y = arg0 >> 16;
    flags = arg2;
    x = arg0;
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    ret = 0;
    v = rec->unk00;

    idx = func_800331D4((u16)arg0);
    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)(SLOT_BASE + idx * 0x54);
    } else {
        idx--;
        e = (Slot54 *)(SLOT_BASE + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    *(u8 *)&D_800A4F17 = old;
    return ret;
}


/* MATCH: 180/180 instructions, byte-exact (relocation-masked).
 *
 * S53 RECOVERY (compile conflict on func_80032A74's signature): the reported
 * conflict was func_80032774's draft, which independently invented a
 * DIFFERENT-WIDTH Slot54 (u16/u16/u16 fields + 0x48 pad, vs. this draft's
 * s16/s16/s16/u16/s8).  Three drafts (func_800322A8, func_800324A4 here, and
 * func_80032774) all declare `extern void func_80032A74(Slot54 *, s32,
 * Rec14 *, s32);`, so all three Slot54 spellings must be textually identical
 * for the merged TU to compile.  This draft's Slot54/Rec14/Owner4EE8 and the
 * func_80032A74 prototype were ALREADY the canonical spelling (byte-identical
 * to src/800.c's incumbent, banked for the sibling func_80032048) -- no
 * change was needed here.  func_80032774's recovered draft (S53) was the one
 * fixed: it now reuses this canonical Slot54 for the extern prototype and
 * keeps its own different-width view under a separate name (Slot54View),
 * cast at use.  All three now agree with each other and with the TU.
 *
 * Notes for the banker:
 *   - src/800.c ALREADY declares Rec14 / Slot54 / Owner4EE8, D_80068304,
 *     D_800A4EE8, D_800A4EF0, D_800A46E8, D_800A4F17, func_8003310C,
 *     func_8003324C and func_80032A74 (they were added for the matched
 *     func_80032048, immediately above this function's INCLUDE_ASM).  Delete
 *     the duplicated declaration block below when banking; keep only the
 *     LOCKBYTE / SLOTBASE macros (or inline them).
 *   - src/800.c has NO prior prototype for func_800324A4, so the signature
 *     below is unconstrained (no DEF-side wall here).
 *
 * The three levers that made it match (pass 2; pass 1 stopped at 4 diffs):
 *   1. ONE-SYMBOL BASE (kept from pass 1, but re-spelled).  The target derives
 *      the slot array AND the lock byte from a single lui/addiu pair
 *      ("addiu $a2,$v1,-0x82F" / "addiu $a0,$v1,-0x824"), which gcc-2.7.2's
 *      cse.c can only do when both constants share a symbol_ref
 *      (related_value chains are per-symbol).  Pass 1 used D_800A46E8 as the
 *      base and wrote the lock byte as +0x82F; that links to the same bytes
 *      but emits the relocation against the WRONG symbol.  The target's own
 *      relocation lines are %hi/%lo(D_800A4F17) for the shared base and for
 *      the closing sb, and %hi/%lo(D_800A46E8) for the two `e` computations,
 *      so the base is spelled &D_800A4F17 here and the array is derived from
 *      it (-0x82F, register-relative, no relocation).  Verified with
 *      `objdump -dr`: la $3,D_800A4F17 / la $3,D_800A46E8 x2 / sb $12,D_800A4F17,
 *      no addends anywhere.
 *   2. STATEMENT ORDER, NOT A PIN, for the prologue weave (target idx 5/6:
 *      "sw $s4" before "srl").  sched2 is a BACKWARD list scheduler; every
 *      insn in bb0 has priority 1, so the order is decided by
 *      potential_hazard (stores win) then by LUID.  `sw $s4,0x30($sp)` only
 *      becomes ready once `maxp = 0` (the insn that clobbers $s4) is
 *      scheduled, so moving `maxp = 0;` ABOVE `y = t >> 16;` swaps their
 *      LUIDs, delays the store's readiness by one tick and puts the srl in
 *      the target's slot.  (cookbook S1/S7; 4 diffs -> 2.)
 *   3. NO $5 PIN ON b1 -- widen b3 instead.  Pass 1 pinned b1 to $a1 to fix
 *      the b1/b3 register pair, but a pinned hard-reg dest fails
 *      birthing_insn_p's `reg_n_sets == 1` gate, so b1's lbu lost the sched1
 *      birthing boost while b2's kept it; b2's load then sank BELOW b1's and
 *      the two lbu's came out swapped (idx 16/17) -- unfixable by statement
 *      order (all 120 permutations tried, floor of 2).  The real cause is a
 *      global-alloc density tie (K2): with `u8 b3` the sll/addu uses are
 *      subregs and b3's allocno loses to b1's, so b1 grabs $a0 first.
 *      Declaring b3 as u32 (like the sibling func_80032048 does) makes the
 *      uses full-SI, raises b3's allocno density above b1's, and b3 wins $a0
 *      / b1 gets $a1 with NO pin at all -- which also restores the natural
 *      lbu order.  (Prompt lever B: the interloper was the narrow type.)
 *
 * The `t` pin on $4 is still required -- see its comment below.
 */

/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

/* D_800A4F17 == (u8 *)D_800A46E8 + 0x82F.  Both the lock byte and the slot
 * array walked by the search loop must come off the SAME symbol_ref or cse
 * emits a second lui/addiu pair (181 insns).  The target's relocation is on
 * D_800A4F17, so that is the base here. */
#define LOCKBYTE (*(u8 *)&D_800A4F17)
#define SLOTBASE ((u8 *)&D_800A4F17 - 0x82F)

extern s32 func_8003310C(s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_800324A4(u32 arg0, u8 *p, u32 flags, s32 arg3) {
    Rec14 *rec;
    Slot54 *e;
    u8 *q;
    s32 i;
    s32 idx;
    s32 ret;
    s32 count;
    s32 minp;
    s32 maxp;
    s32 pr;
    u32 x;
    /* t: keeps the raw incoming arg0 in $a0 so the "srl $t4, $a0, 16" that
     * feeds the y spill reads $a0 and not $fp.  Without it cse collapses
     * x into the parameter pseudo, the shift reads the callee-saved home and
     * the $s7/$fp pair flips (v <-> arg0) -- 9 diffs.  Emits no instruction. */
    register u32 t __asm__("$4");
    u16 y;
    s32 v;
    u8 old;
    u8 b0;
    u8 b1;
    u8 b2;
    /* b3 is u32, NOT u8: the width is what wins it $a0 ahead of b1.  See the
     * header note (lever 3) -- with u8 it loses the allocno density race and
     * the b1/b3 pair comes out swapped. */
    u32 b3;

    t = arg0;
    x = arg0;
    b2 = p[2];
    b1 = p[1];
    b3 = p[3];
    /* maxp = 0 must precede the shift: it gates when "sw $s4" becomes ready
     * in sched2 (lever 2). */
    maxp = 0;
    y = t >> 16;

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    ret = 0;
    idx = 0;
    count = 0;

    old = LOCKBYTE;
    LOCKBYTE = 1;

    v = rec->unk00;

    q = SLOTBASE;
    minp = 0x80;
    for (i = 0; i < 8; i++, q += 0x54) {
        if ((*(u16 *)q & 0x3F) == 1 && *(u16 *)(q + 4) == (u16)x) {
            pr = q[0xB] & 0x7F;
            if (pr < minp) {
                idx = i + 1;
                minp = pr;
            }
            if (pr >= maxp) {
                maxp = pr;
            }
            count++;
        }
    }

    if (count <= arg3) {
        idx = 0;
    } else if ((s32)(flags & 0x7F) < minp) {
        goto done;
    }

    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
    } else {
        idx--;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    if (flags & 0x1000) {
        ((u8 *)e)[0xB] = flags & 0x7F;
        if ((s32)(flags & 0x7F) < maxp) {
            flags |= 0x8000;
        }
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    LOCKBYTE = old;
    return ret;
}


/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. Identical to the TU's already-banked
 * Rec14 (src/800.c, func_80032048's block) — kept verbatim, not renamed. */

/* Canonical TU spelling of the slot record inside D_800A46E8 (stride 0x54),
 * as already banked by func_80032048 in src/800.c. This function's own view
 * of the same bytes needs different field widths/signs (see Slot54View
 * below), so THIS typedef only exists to keep func_80032A74's prototype
 * byte-identical to the TU's — the callee is called through a cast, never
 * accessed directly as `Slot54` in this file. */

/* This function's own overlay of the same 0x54-byte slot record: it needs
 * unsigned 16-bit loads (lhu, not lh) on unk00/unk04/unk06 to byte-match, and
 * an extra unk0B field the TU's Slot54 doesn't expose. Different tag name so
 * it does NOT collide with the TU's `Slot54` typedef above; pointers are
 * cast to `Slot54 *` only at the func_80032A74 call site. */
typedef struct Slot54View {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[0x48];
} Slot54View; /* 0x54 */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];

#define SLOTS ((Slot54View *)D_800A46E8)
/* &D_800A4F17 expressed as an offset inside the D_800A46E8 object: the target
 * derives both loop pointers from this one materialised address
 * (addiu $a2,$v1,-0x82F / addiu $a1,$v1,-0x824). */
#define PFLAG ((s8 *)((u8 *)D_800A46E8 + 0x82F))

extern s32 func_8003310C(s32);
extern void func_800335B8(s32, s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_80032774(u32 arg0, u8 *p, u32 flags)
{
    Rec14 *rec;
    Slot54View *e;
    Slot54View *q;
    s32 ret;
    s32 best;
    s32 cnt;
    s32 i;
    s32 mn;
    s32 mx;
    s32 t;
    s32 yy;
    s32 f4000;
    u32 x;
    u16 y;
    u16 v;
    u8 old;
    u8 b0;
    u8 b1;
    u8 b2;
    s32 b3;

    b2 = p[2];
    b1 = p[1];
    b3 = p[3];
    mx = 0;
    y = arg0 >> 16;
    x = arg0;

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    yy = y;
    ret = 0;
    best = 0;
    cnt = 0;
    old = *PFLAG;
    *PFLAG = 1;
    q = SLOTS;
    mn = 0x80;
    v = rec->unk00;
    for (i = 0, f4000 = flags & 0x4000; i < 8; i++, q++) {
        if ((q->unk00 & 0x3F) == 1 && q->unk04 == (u16)x) {
            if (yy == 0 || q->unk06 == yy) {
                if (f4000) {
                    func_800335B8(i, (u16)flags);
                }
                goto done;
            }
            t = q->unk0B & 0x7F;
            if (t < mn) {
                best = i + 1;
                mn = t;
            }
            if (mx <= t) {
                mx = t;
            }
            cnt++;
        }
    }

    if (cnt < 2) {
        best = 0;
    } else if ((s32)(flags & 0x7F) < mn) {
        goto done;
    }

    if (best == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        best = func_8003310C(v);
        if (best == 0) {
            goto done;
        }
        ret = best;
        best = ret - 1;
        e = &SLOTS[best];
    } else {
        ret = best;
        best = ret - 1;
        e = &SLOTS[best];
        if (e->unk08 != 0) {
            goto done;
        }
        func_8003324C((u16)best);
    }

    if (flags & 0x1000) {
        e->unk0B = flags & 0x7F;
        if ((s32)(flags & 0x7F) < mx) {
            flags |= 0x8000;
        }
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74((Slot54 *)e, best, rec, (u16)flags);

done:
    *PFLAG = old;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80032A74);

INCLUDE_ASM("asm/nonmatchings/800", func_8003310C);

INCLUDE_ASM("asm/nonmatchings/800", func_800331D4);


/* func_8003324C — MATCH (54 ins).
 *
 * D_800A46E8 is an array of 0x54-byte slot records; records [8..15] (base
 * +0x2A0 == 8 * 0x54) are Ent30D80 entities. Switch on (rec->flags & 0x3F):
 * case 1 walks the 8 per-slot "dirty" bytes at e[i + 0xE], clearing each set
 * one, blanking the matching entity's unk40 callback, and calling
 * func_80030D80 on it when unk4E is set; then zeroes the flags halfword.
 * case 5 tail-calls func_80034650(e, 0).
 *
 * Second pass over the 2-instruction NEAR draft (target: `sw $zero,0x40($s0)`
 * in the beqz delay slot, then `addu $a0,$s0,$zero`; the first draft emitted
 * the pair in the opposite order with $a0 as the store base). It was NOT a
 * scheduler tie-break — four independent source-level levers, each verified
 * load-bearing by ablation:
 *
 *  1. `p->unk40 = 0;` sits BEFORE the `if (p->unk4E)`, not inside it. reorg
 *     may only steal a store into a delay slot BACKWARD (from before the
 *     branch) — a forward/fall-through steal of a store is unsafe. So the
 *     target's `sw` in the beqz slot proves the store precedes the test in
 *     source order. (Cookbook §175 lever A: statement order.)
 *  2. `register Ent30D80 *p __asm__("$16")`. Hoisting the store out of the
 *     inner `if` gives p three in-loop uses, and loop.c then splits it into
 *     two induction variables (+0x2A0 for the call argument, +0x2EE for the
 *     0x40/0x4E address giv) — 58 ins. loop.c's biv/giv detection only
 *     considers PSEUDO registers, so pinning p to a hard reg disables strength
 *     reduction for it outright and leaves the single `addiu $s0,$s0,0x54`.
 *     This also drops the first draft's copy-fence: every access now goes
 *     through $s0 and the `addu $a0,$s0,$zero` is emitted last, as the target
 *     has it. Ablating the pin: 58 ins.
 *  3. `__asm__ ("" :: "r"(base));` after p's initialisation. With p pinned,
 *     `addiu p, base, 0x2A0` is base's last use, so the allocator ties base to
 *     $s0 and performs the add in place ("lui $s0 / addiu $s0,$s0,0x2A0"),
 *     wrecking the prologue. The zero-instruction asm extends base past the
 *     add and breaks the tie. Ablating it: 8 mismatches.
 *  4. `off` computed into its own local BEFORE `base` is loaded. Otherwise the
 *     %hi/%lo pair is scheduled above the `andi $a0,$a0,0xFFFF`, base then
 *     conflicts with the incoming argument's live range and lands in $a1
 *     instead of $a0. Ablating it: 8 mismatches.
 *
 * Banking note for src/800.c: `typedef struct Ent30D80`, `extern u16
 * D_800A46E8[];` and `void func_80030D80(Ent30D80 *, s16)` already exist
 * ABOVE the INCLUDE_ASM line — do not duplicate them. Only
 * `extern void func_80034650(u8 *, s32);` is new (func_80034650 is still
 * INCLUDE_ASM further down the TU). The TU's existing
 * `extern void func_8003324C(s32);` matches this definition's signature.
 */


extern u16 D_800A46E8[];

extern void func_80030D80(Ent30D80 *arg0, s16 arg1);
extern void func_80034650(u8 *, s32);

void func_8003324C(s32 arg0) {
    u8 *base;
    u8 *e;
    s32 off;
    s32 code;

    off = (u16)arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;
    code = *(u16 *)e & 0x3F;

    switch (code) {
    case 1: {
        register Ent30D80 *p __asm__("$16");
        s32 i;

        i = 0;
        p = (Ent30D80 *)(base + 0x2A0);
        __asm__ ("" :: "r"(base));
        for (; i < 8; i++, p++) {
            u8 *q = e + i;

            if (q[0xE] != 0) {
                q[0xE] = 0;
                p->unk40 = 0;
                if (p->unk4E != 0) {
                    func_80030D80(p, 0);
                }
            }
        }
        *(u16 *)e = 0;
        break;
    }
    case 5:
        func_80034650(e, 0);
        break;
    }
}

extern u16 D_800A46E8[];

void func_80033324(s32 a0, s32 a1) {
    u8 *e = (u8 *)D_800A46E8 + a1 * 0x54;
    u16 t;

    if ((*(u16 *)e & 0x3F) == 1) {
        *(u8 *)(e + a0 + 0xE) = 0;
        t = *(u16 *)(e + 0xC) - 1;
        *(u16 *)(e + 0xC) = t;
        if (t != 0) {
            return;
        }
        if (*(u8 *)(e + 0xA) != 5) {
            *(u8 *)(e + 0xA) = 0;
            *(u16 *)e = 0;
        }
    }
}


/* TU decls (src/800.c): `typedef struct Ent30D80 { ... } Ent30D80;` and
 * `extern void func_80030D80(Ent30D80 *arg0, s16 arg1);` already exist
 * above this function's INCLUDE_ASM line (see func_80030D80's own
 * definition and func_8003324C's banking note) — reproduced here verbatim
 * for standalone compilation. Do not duplicate in the TU when banking. */

extern u16 D_800A46E8[];

extern void func_80030D80(Ent30D80 *arg0, s16 arg1);
/* TU already declares func_80034650 as (u8 *, s32) above func_8003324C
 * (src/800.c) — a `void *` redeclaration here would conflict with it. */
extern void func_80034650(u8 *a0, s32 a1);

void func_80033398(u32 arg0)
{
    /* RC-12 / cookbook §136d-1: the $0-add OPAQUE COPY.
     * The target's `addu $s7,$a0,$zero` must NOT be cse-linked to the
     * parameter, so that `srl $s6,$a0,16` keeps reading the raw incoming
     * $a0 (the parm pseudo dies at the srl and local-alloc gives it $a0,
     * deleting the real parm copy).  A plain `s7v = arg0;` makes
     * cse.c make_regs_eqv head-promote s7v to canonical and canon_reg
     * rewrites the srl to `srl $s6,$s7,16` (the 1-ins residual). */
    register s32 zr __asm__("$0");
    u32 s7v;
    u8 *s5v;
    s32 s4v;
    u32 s6v;
    u8 *fpv;
    register u8 *s3v __asm__("$19");
    u8 *s2v;
    register s32 s1v __asm__("$17");
    register u8 *s0v __asm__("$16");
    s32 t0;

    s7v = arg0 + zr;
    s5v = (u8 *)D_800A46E8;
    s4v = 0;
    s6v = arg0 >> 16;
    fpv = s5v + 0x2A0;
    s3v = s5v + 6;

    for (; s4v < 8; s3v += 0x54, s5v += 0x54) {
        if ((*(u16 *)s5v & 0x3F) == 1 &&
            *(u16 *)(s3v - 2) == (u16)s7v &&
            (s6v == 0 || *(u16 *)s3v == s6v)) {
            s2v = (u8 *)D_800A46E8 + (u32)(u16)s4v * 0x54;
            t0 = *(u16 *)s2v & 0x3F;
            switch (t0) {
            case 1:
                s1v = 0;
                s0v = fpv;
                for (; s1v < 8; s1v++, s0v += 0x54) {
                    u8 *p = s2v + s1v;
                    if (p[0xE] != 0) {
                        p[0xE] = 0;
                        *(u32 *)(s0v + 0x40) = 0;
                        if (s0v[0x4E] != 0) {
                            func_80030D80((Ent30D80 *)s0v, 0);
                        }
                    }
                }
                *(u16 *)s2v = 0;
                break;
            case 5:
                func_80034650(s2v, 0);
                break;
            default:
                s4v++;
                continue;
            }
        }
        s4v++;
    }
}


extern u16 D_800A46E8[];
extern void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_8003350C(s32 arg0, s32 arg1) {
    register Ent30D80 *p __asm__("$16");
    register s32 t __asm__("$19");
    u8 *base;
    u8 *e;
    s32 off;
    s32 i;

    off = arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;
    i = 0;
    t = arg1 << 16;
    __asm__ ("" :: "r"(t));
    p = (Ent30D80 *)(base + 0x2A0);
    __asm__ ("" :: "r"(base));
    for (; i < 8; i++, p++) {
        u8 *q = e + i;
        if (q[0xE] != 0) {
            q[0xE] = 0;
            p->unk40 = 0;
            if (p->unk4E != 0) {
                func_80030D80(p, t >> 16);
            }
        }
    }
    *(u16 *)e = 0;
}


/* TU decls (src/800.c): `extern u16 D_800A46E8[];`, `extern void func_800335B8(s32, s32);` */
extern u16 D_800A46E8[];

void func_800335B8(s32 a0, s32 a1) {
    u8 *e = (u8 *)D_800A46E8 + a0 * 0x54;
    u8 *p;
    s32 a2;
    s32 v1;
    s32 t0;

    if ((*(u16 *)e & 0x3F) != 1) {
        return;
    }

    /* copy-fence: keeps the `addu $t0,$a1,$zero` param copy alive (cse would
       otherwise propagate $a1 into branch 2's `andi $a1,$t0,0x7F`). */
    t0 = a1;
    __asm__ ("" : "=r"(t0) : "0"(t0));

    if (a1 & 0x1000) {
        v1 = 0;
        a2 = *(u16 *)(e + 0xC);
        a1 = a1 & 0x7F;
        t0 = 1;
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (; v1 < 8; v1++, p += 0x54) {
            u8 *rec;
            if (a2 == 0) {
                return;
            }
            if (*(u8 *)(e + v1 + 0xE) != 0) {
                /* copy-fence: materialises the target's in-loop
                   `addu $v0,$a0,$zero` (reorg then steals it for the
                   beqz delay slot). Walking pointer, NOT p + v1*0x54,
                   so loop strength reduction still owns $a0. */
                rec = p;
                __asm__ ("" : "=r"(rec) : "0"(rec));
                a2--;
                *(u16 *)(rec + 0x48) = a1;
                *(u8 *)(rec + 0x4F) = t0;
            }
        }
    } else if (a1 & 0x2000) {
        a2 = *(u16 *)(e + 0xC);
        v1 = 0;
        a1 = t0 & 0x7F;
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (; v1 < 8; v1++) {
            u8 *rec;
            if (a2 == 0) {
                return;
            }
            if (*(u8 *)(e + v1 + 0xE) != 0) {
                rec = p + v1 * 0x54;
                if (*(u8 *)(rec + 0x35) != 0) {
                    *(u8 *)(rec + 0x53) = a1;
                }
                a2--;
            }
        }
    }
}


/* func_800336A8 — MATCH (121 ins).
 *
 * Second-pass fix over the 49/-1 NEAR draft. The whole residual was ONE unfilled
 * branch-delay slot: the target leaves `beqz $v0, .L80033818` (the D_800A4F19 test)
 * with a `nop`, our build let reorg.c's EAGER FALLTHROUGH STEAL pull the then-arm's
 * head insn `sll $v0,$v1,1` into it (dbr dump: insn 241 folded into a SEQUENCE with
 * jump_insn 234).
 *
 * Lever: reorg.c `stop_search_p` (2.7.2:675) returns TRUE for an `ASM_INPUT` insn, so
 * `fill_slots_from_thread`'s trial loop terminates on the FIRST insn of the thread and
 * never reaches the `sll`. A zero-byte `__asm__ __volatile__("")` planted as the first
 * statement of the then-arm therefore kills the steal and restores the `nop` — with no
 * emitted instruction of its own (cookbook D3 lever (c), "make the join head ineligible",
 * generalised: make it un-searchable).
 *
 * Also removed the first draft's `register u16 *p __asm__("$6")` pin — byte-verified
 * unnecessary once the slot is fixed, so this body is PIN-FREE (§42e sibling-TU safe).
 *
 * Structural levers kept from pass 1 (each byte-load-bearing):
 *  - byte-arithmetic index `(Chan336A8 *)(D_800A4988 + i*0x54)` keeps the t1/t3/t4 layout;
 *  - `q = D_8007319E + 1; q[0x7F - n]` reproduces cse's related-value `addiu $t6,$t5,2`;
 *  - inverted clamp `if (n >= 0x42) ... else n = 1;` for the bnez/else-last layout;
 *  - one `v` funnelling all three store paths so cross-jumping merges the trailing `sh`;
 *  - `extern const u16 D_8007319E[]` (D_8007321E must stay non-const) lets the second
 *    table load hoist across `sh $v0,0xA($a3)` and interleave into the first mult.
 */

typedef struct {
    /* 0x00 */ u8 pad00[0x0A];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 pad0C[0x28];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 pad36[0x1C];
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[1];
} Chan336A8; /* size 0x54 */

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 pad0C[0x34];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45[3];
} Voice336A8; /* size 0x48 */

typedef struct {
    /* 0x00 */ u8 pad00[0x16];
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 pad17[1];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ u16 unk1C[12];
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 pad39[1];
    /* 0x3A */ u8 unk3A[8];
} Req336A8;

extern u8 D_800A4988[];
extern s32 D_80073140[];
extern u16 D_8006AA30[];
extern const u16 D_8007319E[];
extern u16 D_8007321E;
extern u8 D_800A4F19;

void func_800336A8(Req336A8 *arg)
{
    Chan336A8 *ch;
    Voice336A8 *vo;
    u16 *p;
    const u16 *q;
    u32 m;
    u32 n;
    u32 v;
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        if (arg->unk3A[i] == 0) {
            continue;
        }
        ch = (Chan336A8 *)(D_800A4988 + i * 0x54);
        vo = (Voice336A8 *)(D_800A4988 + 0x2A0 + i * 0x48);
        vo->unk00 = D_80073140[ch->unk0A];
        m = ch->unk34;
        m = D_8006AA30[m];
        m = m * *(s16 *)(D_800A4988 + 0x572);
        m = m >> 7;
        if (arg->unk16 != 0) {
            m = m * arg->unk18;
            m = m >> 15;
        }
        p = arg->unk1C;
        for (j = 2; j >= 0; j--, p += 4) {
            m = m * *p;
            m = m >> 14;
        }
        n = ch->unk35;
        if (n == 0) {
            v = m;
            vo->unk0A = v;
            vo->unk08 = v;
        } else {
            if (arg->unk38 != 0) {
                n += arg->unk38;
                if (n >= 0x42) {
                    n -= 0x40;
                    if (n >= 0x80) {
                        n = 0x7F;
                    }
                } else {
                    n = 1;
                }
            }
            ch->unk52 = n;
            if (D_800A4F19 != 0) {
                /* zero-byte dbr fence: ASM_INPUT stops reorg's fallthrough trial scan
                 * (stop_search_p), so the beqz above keeps its `nop` delay slot. */
                __asm__ __volatile__("");
                v = (m * D_8007319E[n]) >> 14;
                vo->unk0A = v;
                q = D_8007319E + 1;
                v = (m * q[0x7F - n]) >> 14;
                vo->unk08 = v;
            } else {
                v = (m * D_8007321E) >> 14;
                vo->unk0A = v;
                vo->unk08 = v;
            }
        }
        vo->unk40 = ch->unk0A;
        if (vo->unk44 != 0) {
            vo->unk04 |= 3;
        } else {
            vo->unk04 = 3;
            vo->unk44 = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_8003388C);

extern u16 D_800A46E8[];

void func_800342E8(u8 *a0, s32 a1) {
    u32 t = a1 * 84 + (u32)D_800A46E8;
    *(u8 *)(t + (u32)a0 + 0x3A) = 0;
}


/* TU decls already present in src/800.c (do NOT duplicate at bank time):
 *   extern u16 D_800A46E8[];
 *   extern s16 D_800A4EF0;
 *   extern Owner4EE8 *D_800A4EE8;   (typedef `Owner4EE8`, defined in src/800.c
 *       as { u8 pad00[0x14]; Rec14 **unk14; } — this function never touches
 *       unk14; it reads offset 0x18 via a raw (u8*) pointer-cast, so it needs
 *       Owner4EE8 only as an OPAQUE type. refuse-BROKE-MATCH note: the batch
 *       reconciler tried to canonicalize this offset-0x18 access into a named
 *       struct field (extending Owner4EE8's size), which shifted bytes in a
 *       sibling already-matched user of the struct — do NOT add a field for
 *       0x18 to Owner4EE8; keep the byte-offset cast below instead.)
 *   extern s32 func_8003310C(s32);
 */

/* 0xC-byte sound-instrument record, indexed by p[3]. */
typedef struct Rec12 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} Rec12; /* 0xC */

typedef struct Snd54Sub {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  pad07;
} Snd54Sub; /* 0x8 */

/* the 0x54-stride voice slot inside D_800A46E8 */
typedef struct Snd54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u8  pad0A[2];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ Snd54Sub unk1C[3];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3A */ u8  unk3A[8];
    /* 0x42 */ u8  pad42[6];
    /* 0x48 */ u8  unk48;
    /* 0x49 */ u8  pad49[7];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
} Snd54; /* 0x54 */

/* opaque — matches the TU's `typedef struct Owner4EE8 Owner4EE8;` spelling
 * exactly so this local decl is droppable at bank time in favor of the TU's;
 * this function only pointer-casts through it (offset 0x18), never names a
 * field, so the incomplete type is sufficient and adds no struct layout. */

extern Rec12 D_80068A54[];
extern u8 D_8006AED8[];
extern u16 D_800A46E8[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;

extern s32 func_8003310C(s32);
extern s32 func_800348A8(u32);
extern void func_80034650(u8 *, s32);

s32 func_80034314(u32 arg0, u8 *p, u32 arg2) {
    u32 flags;
    Snd54 *e;
    Rec12 *rec;
    u8 *q;
    s16 *pa;
    register s32 idx __asm__("$3");
    s32 ret;
    s32 i;
    s32 j;
    s32 b1;
    u32 x;
    u32 y;

    y = arg0 >> 16;
    flags = arg2;
    x = arg0;
    b1 = p[1];
    if (b1 == 0) {
        rec = &D_80068A54[p[3]];
    } else {
        if (D_800A4EE8 == 0) {
            return 0;
        }
        if (D_800A4EF0 != b1) {
            return 0;
        }
        rec = *(Rec12 **)((u8 *)D_800A4EE8 + 0x18) + p[3];
    }

    idx = func_800348A8(arg0);
    ret = idx;
    if (idx != 0) {
        idx = ret - 1;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (flags & 0x1000) {
            e->unk1C[0].unk06 = 1;
            e->unk1C[0].unk02 = 0x100;
            e->unk1C[0].unk04 = ((s32)(flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                e->unk38 = D_8006AED8[(flags >> 8) & 0xF];
            } else {
                e->unk38 = 0;
                e->unk39 = 0;
            }
            return ret;
        }
        if (e->unk08 != 0) {
            return 0;
        }
        func_80034650(e, 0);
    } else {
        idx = func_8003310C(rec->unk04);
        ret = idx;
        if (idx == 0) {
            return 0;
        }
        idx = ret - 1;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
    }

    /* dbr fence (zero-byte, non-volatile asm -> reorg stop_search_p): keeps the
     * `j .L800344B4` delay slot a nop; without it reorg eagerly steals + duplicates
     * the merge block's first store. */
    __asm__ ("" : "=r"(e) : "0"(e));
    e->unk37 = rec->unk08;
    e->unk34 = b1;
    e->unk0C = rec->unk00;
    e->unk02 = rec->unk04;
    e->unk10 = e->unk0C;
    e->unk04 = x;
    e->unk06 = y;
    e->unk14 = 1;
    e->unk17 = p[2];
    e->unk16 = 0;
    e->unk18 = 0x7FFF;
    e->unk08 = rec->unk06;
    e->unk50 = 0;
    e->unk52 = 0;

    if (rec->unk08 & 0x10) {
        e->unk48 = 1;
    } else {
        e->unk48 = 0;
    }

    if (rec->unk08 & 4) {
        e->unk1A = 0x400;
    } else if (rec->unk08 & 8) {
        e->unk1A = 0x200;
    } else {
        e->unk1A = 0x5F;
    }
    e->unk36 = 0;
    /* sched fence: without it the two stores (memory-unit users) sink below the
     * whole loop preheader (potential_hazard beats the LUID tie-break). */
    __asm__ ("" : "=r"(e) : "0"(e));

    pa = &e->unk1C[0].unk00;
    for (i = 0; i < 3; i++, pa = (s16 *)((u8 *)pa + 8)) {
        pa[1] = 0x100;
        *((u8 *)pa + 6) = 0;
        if (i != 0) {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
        } else if (flags & 0x1000) {
            pa[0] = ((flags & 0x7F) * 0x3FFF) >> 7;
            pa[2] = ((flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                u8 tv = D_8006AED8[(flags >> 8) & 0xF];
                e->unk38 = tv;
                e->unk39 = tv;
            }
        } else {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
            e->unk38 = 0;
            e->unk39 = 0;
        }
    }

    q = e->unk3A;
    for (j = 7; j >= 0; j--) {
        *q++ = 0;
    }

    e->unk00 = 5;
    return ret;
}


extern u8 D_800A4988[];

void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_80034650(u8 *param_1, s32 param_2)
{
    s32 i;
    s32 pm;

    pm = (param_2 & 0xFF) << 16;
    for (i = 0; i < 8; i++) {
        if (*(param_1 + i + 0x3A) != 0) {
            func_80030D80((Ent30D80 *)(D_800A4988 + i * 0x54), pm >> 16);
        }
    }
    *(u16 *)param_1 = 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800346D0);

typedef struct {
    u16 state;      /* 0x00 */
    u16 unk02;
    u16 id;         /* 0x04 */
    u16 group;      /* 0x06 */
    u16 unk08;
    s8  unk0A;
    u8  unk0B;
    u8  pad0C[0xA];
    u8  active;     /* 0x16 */
    u8  pad17[0x3D];
} Sl;               /* 0x54 */

extern u16 D_800A46E8[];

void func_800347C8(s32 arg0) {
    Sl *e;
    s32 i;

    e = (Sl *)D_800A46E8;
    for (i = 0; i < 8; i++, e++) {
        if (e->state == 5 && e->id == (s16)arg0 &&
            ((arg0 >> 16) == 0 || (arg0 >> 16) == e->group)) {
            e->active = 1;
        }
    }
}


extern u16 D_800A46E8[];

void func_80034844(void)
{
    register u8 *a0 __asm__("$4") = (u8 *)D_800A46E8;
    register int a1 __asm__("$5") = 0;
    register int t0 __asm__("$8") = 0x5;
    register int a3 __asm__("$7") = 0x1;
    register int a2 __asm__("$6") = 0x220;
    register u8 *v1 __asm__("$3") = (u8 *)D_800A46E8 + 0x1A;

    while (a1 < 8) {
        if (*(u16 *)a0 == t0) {
            u8 b = *(u8 *)(v1 + 0x1D);
            if ((b & 0x2) == 0) {
                *(u8 *)(v1 - 0x4) = a3;
                *(u16 *)v1 = a2;
            }
        }
        a1++;
        v1 += 0x54;
        a0 += 0x54;
    }
}

extern u16 D_800A46E8[];

s32 func_800348A8(u32 arg0) {
    u16 *p;
    u16 *q;
    s32 i;
    u32 lo;
    u32 hi;
    s32 five;

    p = D_800A46E8;
    i = 0;
    five = 5;
    lo = arg0 & 0xFFFF;
    hi = arg0 >> 16;
    q = p + 3;
    do {
        __asm__ ("" :: "r"(i), "r"(i));
        if (p[0] == five && q[-1] == lo) {
            if (hi == 0 || q[0] == hi) {
                return i + 1;
            }
        }
        i++;
        q += 0x2A;
        p += 0x2A;
    } while (i < 8);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8003491C);


extern s8 D_800A4F17;

void func_80034A54(s32 a0) {
    s32 self = a0;
    u8 v0 = *(u8 *)(self + 0x37);

    if ((v0 & 0x1) != 0) {
        s8 *p = &D_800A4F17;
        s8 old = *p;
        *p = 1;
        *(u8 *)(self + 0x32) = 1;
        *(s16 *)(self + 0x2E) = 0x3FF;
        *(s16 *)(self + 0x30) = 0xFFF;
        *p = old;
    }
}


extern s8 D_800A4F17;

void func_80034A9C(void *a0) {
    register void *a1 __asm__("$5") = a0;
    u8 *v1;
    u8 old;

    if (*(u16 *)((u8 *)a1 + 0x30) == 0x3FFF) {
        return;
    }
    v1 = (u8 *)&D_800A4F17;
    old = *v1;
    *v1 = 1;
    *(s8 *)((u8 *)a1 + 0x32) = 1;
    *(s16 *)((u8 *)a1 + 0x2E) = 0x3FF;
    *(s16 *)((u8 *)a1 + 0x30) = 0x3FFF;
    *v1 = old;
}


extern s8 D_800A4F17;

void func_80034AE0(void *a0)
{
    s8 *v1;
    s8 orig;

    v1 = &D_800A4F17;
    orig = *v1;
    *v1 = 1;
    *(s8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0;
    *v1 = orig;
}


extern s8 D_800A4F17;

void func_80034B0C(s32 a0) {
    s8 *p = &D_800A4F17;
    s8 old = *p;
    *p = 1;
    *(u8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0x3FFF;
    *p = old;
}

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8007620C;

s32 func_80034B3C(void)
{
    u8 flags;

    if (D_8006AEF8 != D_8006AEFC) {
        flags = D_8007620C;
        if (flags & 0x80) {
            return 2;
        }
        if (flags & 0x20) {
            return 4;
        }
        return 1;
    }
    D_8007620C = 0;
    return 0;
}

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076214;
extern u8 D_8007620C;
/* CD read-queue status: head==tail (D_8006AEF8/FC equal) => idle; flags D_80076214 (a
 * pending/error byte) and D_8007620C (bit7/bit5) classify the busy/result state.
 * Returns 0=idle done, 8=had pending, 2/4/1=busy variants. */
s32 CdQueueBusy(void) {
    if (D_8006AEF8 != D_8006AEFC) {
        if (D_80076214 == 0) {
            if (D_8007620C & 0x80) {
                return 2;
            }
            if (D_8007620C & 0x20) {
                return 4;
            }
            return 1;
        }
    } else {
        D_8007620C = 0;
        if (D_80076214 == 0) {
            return 0;
        }
    }
    D_80076214 = 0;
    return 8;
}


extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8006AEF4;
extern u8 D_800A63E4;
extern void *streamLoad_savedReadyCB;
extern u8 streamLoad_cbActive;
extern int streamLoad_state;
extern int D_800A6544;
extern s32 D_8006AEE8;
extern s32 D_800A63E8;
extern s32 D_8007610C;
extern u8 D_8006AEF5;
extern u8 D_8007620C;
extern s32 D_80076114;
extern u8 D_80076214;
extern s32 D_80078F10;
extern void D_800C7D30();
extern int DecDCToutCallback(void (*func)());
extern s32 D_800A5BC8;
extern s32 D_800C6D28;

void func_80034C24(void) {
    s32 *p = &D_80078F10;
    s32 i;

    D_8006AEF8 = 0;
    D_8006AEFC = 0;
    D_8006AEF4 = 0;
    D_800A63E4 = 0;
    streamLoad_savedReadyCB = 0;
    streamLoad_cbActive = 0;
    streamLoad_state = 0;
    D_800A6544 = 0;
    D_8006AEE8 = 0;
    D_800A63E8 = 0;
    D_8007610C = 0;
    D_8006AEF5 = 0;
    D_8007620C = 0;
    D_80076114 = 0;
    D_80076214 = 0;

    for (i = 0; i < 5; i++) {
        p[i] = 0;
    }

    D_800A5BC8 = DecDCToutCallback(D_800C7D30);
    D_800C6D28 = 0;
}


extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];

s32 func_80034CF0(u8 *p) {
    s32 idx = D_8006AEFC;
    u8 saved = D_8006AEF5;
    s32 limit = D_8006AEF8;
    u8 *self;
    s32 f28;
    s32 oldIdx;
    s32 ret;

    D_8006AEF5 = 1;
    idx = idx + 1;
    if (idx >= 4) {
        idx = 0;
    }

    if (idx == limit) {
        D_8006AEF5 = saved;
        return 0;
    }

    self = D_80076118 + D_8006AEFC * 0x30;

    *(s32 *)(self + 0x8) = *(s32 *)(p + 0x8);
    *(s32 *)(self + 0xC) = *(s32 *)(p + 0xC);
    *(s32 *)(self + 0x10) = *(s32 *)(p + 0x10);
    *(s32 *)(self + 0x14) = *(s32 *)(p + 0x14);
    *(s32 *)(self + 0x18) = *(s32 *)(p + 0x18);
    *(s32 *)(self + 0x1C) = *(s32 *)(p + 0x1C);
    *(s32 *)(self + 0x20) = *(s32 *)(p + 0x20);
    *(s32 *)(self + 0x24) = *(s32 *)(p + 0x24);
    f28 = *(s32 *)(p + 0x28);

    self[0] = 1;
    self[1] = 0;
    self[2] = 0;
    self[3] = 0;
    self[7] = 1;

    oldIdx = D_8006AEFC;
    D_8006AEFC = idx;
    D_8006AEF5 = saved;

    ret = oldIdx + 1;
    *(s32 *)(self + 0x28) = f28;
    *(s32 *)(self + 0x2C) = oldIdx;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80034DFC);


extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];
extern u8 D_80076138[];
extern s32 D_80076114;
extern u8 D_8007620C;

void func_8003500C(void) {
    if (D_8006AEF5 != 0) {
        return;
    }

    if (D_8006AEFC != D_8006AEF8) {
        s32 idx = D_8006AEF8;
        u8 *self = D_80076118 + idx * 0x30;

        if (self[0] != 0) {
            register s32 (*fn8)(void *) __asm__("$3") = *(s32 (**)(void *))(self + 8);
            register s32 type __asm__("$2") = self[4];

            D_80076114 = type;
            if (fn8(self) == 0) {
                return;
            }

            {
                register s32 (*fn1C)(s32) __asm__("$6") = *(s32 (**)(s32))(self + 0x1C);
                register s32 type2 __asm__("$5") = self[4];

                D_80076114 = type2;
                if (fn1C != NULL) {
                    fn1C(*(s32 *)(D_80076138 + D_8006AEF8 * 0x30));
                }
            }

            self[0] = 0;
            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            }
            return;
        } else {
            if (self[1] != 0 && self[7] == 0) {
                s32 (*fn24)(void *) = *(s32 (**)(void *))(self + 0x24);

                if (fn24 != NULL) {
                    fn24(self);
                }
                if (self[2] != 0) {
                    return;
                }
            }

            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            } else {
                D_80076114 = 1;
            }
            return;
        }
    } else {
        D_8007620C = 0;
    }
}

extern s32 D_80076218;

s32 func_800351E8(s32 arg0)
{
    D_80076218 = arg0;
    return arg0 & -((u32)(arg0 - 0x1010) <= 0x7EFF0);
}


extern s32 D_80076218;

extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);

void func_80035210(s32 a0, s32 a1)
{
    register s32 v1 __asm__("$3");

    v1 = D_80076218;
    func_8003C498(v1);
    SpuWrite(a0, a1);
    v1 = D_80076218;
    D_80076218 = v1 + a1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80035270);

INCLUDE_ASM("asm/nonmatchings/800", func_800359B0);

INCLUDE_ASM("asm/nonmatchings/800", func_80035C4C);

INCLUDE_ASM("asm/nonmatchings/800", func_8003602C);


extern u8 D_800A63E4;
extern s32 D_8007610C;
extern s32 D_800A63E8;

void func_80036130(s32 a0, u8 *a1) {
    u8 v1;
    s32 temp;
    s32 v3;
    s32 v0;
    s32 byte_val;
    s32 low;

    v1 = D_800A63E4;
    if (v1 != 0xC) {
        return;
    }

    v1 = a0 & 0xFF;
    if (v1 != 0x1) {
        return;
    }

    temp = D_8007610C;
    if (temp < 0xA) {
        D_8007610C = temp + 1;
        return;
    }

    if ((a1[4] & 0x80) != 0) {
        return;
    }

    byte_val = a1[1];
    v1 = byte_val >> 4;
    v0 = v1 << 2;
    v0 = v0 + v1;
    v0 = v0 << 1;
    low = byte_val & 0xF;
    v3 = D_800A63E8;
    v0 = v0 + low;

    if (v0 != v3) {
        D_800A63E4 = 0xD;
    }
}

extern void *streamLoad_savedReadyCB;
extern u8 streamLoad_cbActive;
extern void *CdReadyCallback(void *func);

void func_800361CC(void) {
    if (streamLoad_cbActive == 0) {
        streamLoad_savedReadyCB = ((void *(*)(void))CdReadyCallback)();
    } else {
        ((void *(*)(void))CdReadyCallback)();
    }
    streamLoad_cbActive = 1;
}


extern void *CdReadyCallback(void *func);
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;

void func_8003621C(void) {
    if (streamLoad_cbActive != 0) {
        CdReadyCallback(streamLoad_savedReadyCB);
        streamLoad_savedReadyCB = 0;
        streamLoad_cbActive = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80036260);

#ifdef NON_MATCHING
extern int   CdControl(u8 com, u8 *param, u8 *result);
extern int   CdSync(int mode, u8 *result);
extern u32   CdMode(void);
extern void  CdFlush(void);
extern void *CdReadyCallback(void *func);
extern void  func_800377D8(void);   /* this loader's CdlReadN ready-callback */
extern void  func_80036260(void);   /* sub-handler passed to func_80037CD8 */
extern void  func_8002EC10(void);
extern void  func_80037334(void);
extern void  func_80037358(int posInt);
extern void  func_80037144(int idx);
extern int   func_80037CD8(void *arg);
extern int   func_8003750C(void);
extern int   func_800374CC(int *out);
extern int   func_8003775C(void);
extern void  func_80037D74(void);
extern void *func_80037368(int *out);

extern int   streamLoad_state;          /* 0x8006AF00 */
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;
extern int   D_800A4F28;            /* tick / timeout counter */
extern int   D_800A4F2C;            /* CdMode-derived retry budget */
extern int   D_800A4F30;            /* remaining sub-stream repeat count (from param_3) */
extern int   D_800A4F34;            /* last sector position (stall detection) */
extern int   D_800A4F38;            /* end/abort flag */
extern int   D_800A6544;
extern u16   D_800A4E8E;            /* 16-bit status flags */
extern u8    D_8006AEF4;            /* 8-bit status flags */
extern u8    D_80068B60[];          /* per-resource descriptor table (0x10 stride) */

/* Second CD loader, DISTINCT from CdReadStateMachine: an 18-state machine (streamLoad_state) with
 * its OWN ready-callback (func_800377D8). Runs SetMode(0xA0)/SeekL/ReadN with retry + CdMode
 * handling, looping param_3 (D_800A4F30) times over sub-streams. Returns 0 = busy, 1 = done,
 * 2 = error/abort. Driven by ResourceLoadStateMachine. Provenance: static trace, Phase 3 T4 (fn id
 * verified; full semantics partial).
 * NON_MATCHING: faithful translation of the Ghidra decompile — logically faithful, not byte-verified. */
int StreamLoadStateMachine(int param_1, void *param_2, int param_3) {  /* param_2 is a CdlLOC* */
    short sVar1;
    int iVar4;
    u32 uVar2;
    char *pcVar3;
    u8 local_28[8];
    u8 local_20[8];
    int local_18;
    int local_14;

    sVar1 = *(short *)(D_80068B60 + (param_1 - 0x100) * 0x10);
    D_800A4F28++;
    switch (streamLoad_state) {
    case 0:
        D_800A4F38 = 0;
        D_800A6544 = 0;
        D_800A4F30 = param_3;
        func_8002EC10();
        streamLoad_state++;
        D_800A4E8E &= 0xFFDF;
        return 0;
    case 1:
        func_80037334();
        iVar4 = CdPosToInt((CdlLOC *)param_2);
        func_80037358(iVar4);
        func_80037144(sVar1);
        streamLoad_state++;
        /* fall through */
    case 2:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        uVar2 = CdMode();
        D_800A4F2C = ((uVar2 & 0x80) == 0) ? 3 : 0;
        streamLoad_state++;
        /* fall through */
    case 3:
        local_28[0] = 0xA0;
        iVar4 = CdControl(0x0E, local_28, local_20);     /* CdlSetmode */
        if (iVar4 == 0) {
            if ((local_20[0] & 0x10) != 0) { func_80037334(); streamLoad_state = 0; return 2; }
            return 0;
        }
        D_800A4F28 = 0;
        streamLoad_state++;
        /* fall through */
    case 4:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5) {
            if (iVar4 == 2) {
                streamLoad_state++;
                local_14 = 2;
            modeWait:
                if (D_800A4F2C != 0) { D_800A4F2C--; return 0; }
                streamLoad_state++;
                goto issueSeek;
            }
            if (D_800A4F28 < 0x3D) return 0;
        }
        streamLoad_state = 3;
        return 0;
    case 5:
        goto modeWait;
    case 6:
    issueSeek:
        iVar4 = func_80037CD8((void *)func_80036260);
        if (iVar4 == 0) return 0;
        streamLoad_state = 7;
        /* fall through */
    case 7:
        iVar4 = func_8003750C();
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 8:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        streamLoad_state++;
        /* fall through */
    case 9:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x15, (u8 *)param_2, local_20);      /* CdlSeekL */
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 10:
        local_14 = CdSync(1, local_20);
        if (local_14 == 5) {
            iVar4 = CdControl(0x01, (u8 *)0, local_20);        /* CdlNop */
            if (iVar4 == 0) { streamLoad_state = 9; return 0; }
            if ((local_20[0] & 0x10) != 0) {
                func_80037334();
                D_8006AEF4 &= 0xFD;
                streamLoad_state = 0;
                return 2;
            }
            streamLoad_state = 9;
            return 0;
        }
        if (local_14 != 2) {
            if (D_800A4F28 < 0x12D) return 0;
            CdFlush();
            streamLoad_state = 9;
            return 2;
        }
        streamLoad_state++;
        local_14 = 2;
        /* fall through */
    case 0xB:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x06, (u8 *)param_2, local_20);      /* CdlReadN */
        if (iVar4 != 0) {
            if (streamLoad_cbActive == 0)
                streamLoad_savedReadyCB = CdReadyCallback((void *)func_800377D8);
            else
                CdReadyCallback((void *)func_800377D8);
            streamLoad_state++;
            streamLoad_cbActive = 1;
            return 0;
        }
        if ((local_20[0] & 0x10) == 0) return 0;
        D_8006AEF4 &= 0xFD;
        func_80037334();
        streamLoad_state = 0;
        return 2;
    case 0xC:
        iVar4 = func_800374CC(&local_18);
        if (iVar4 == 0) {
            if (local_18 != D_800A4F34) { D_800A4F34 = local_18; D_800A4F28 = 0; }
            if (D_800A4F28 > 300) {
                if (streamLoad_cbActive != 0) {
                    CdReadyCallback(streamLoad_savedReadyCB);
                    streamLoad_savedReadyCB = 0;
                    streamLoad_cbActive = 0;
                }
                streamLoad_state++;
            }
            return 0;
        }
        if (streamLoad_cbActive != 0) {
            CdReadyCallback(streamLoad_savedReadyCB);
            streamLoad_savedReadyCB = 0;
            streamLoad_cbActive = 0;
        }
        streamLoad_state++;
        /* fall through */
    case 0xD:
        iVar4 = func_8003775C();
        if (iVar4 == 0) return 0;
        func_80037D74();
        streamLoad_state++;
        return 0;
    case 0xE:
        pcVar3 = (char *)func_80037368(&local_14);
        if (local_14 != 1) { streamLoad_state = 0x11; return 0; }
        if (*pcVar3 != 1) {
            if (*pcVar3 == 2) { streamLoad_state = 0x11; D_800A4F38 = 1; return 0; }
            if (D_800A4F30 != 0) {
                if (D_800A4F30 - 1 == 0) { streamLoad_state = 0x11; D_800A4F30 = 0; return 0; }
                streamLoad_state = 1;
                D_800A4F30--;
                return 0;
            }
            streamLoad_state = 1;
            return 0;
        }
        streamLoad_state++;
        break;                                                 /* -> CdlPause (post-switch) */
    case 0xF:
        break;                                                 /* -> CdlPause (post-switch) */
    case 0x10:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5 && iVar4 != 2) return 0;
        if (D_800A4F38 == 0) { streamLoad_state = 0; return 1; }
        streamLoad_state = 0;
        D_800A4F38 = 0;
        return 2;
    case 0x11:
        iVar4 = CdControl(0x09, (u8 *)0, local_20);            /* CdlPause */
        if (iVar4 != 0) { streamLoad_state = 0x10; return 0; }
        return 0;
    default:
        return 0;
    }
    /* shared tail for states 0xE (advance) and 0xF: pause, then wait for it */
    iVar4 = CdControl(0x09, (u8 *)0, local_20);                /* CdlPause */
    if (iVar4 != 0) { streamLoad_state++; return 0; }
    if ((local_20[0] & 0x10) != 0) { streamLoad_state = 0; return 1; }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/800", StreamLoadStateMachine);
#endif

INCLUDE_ASM("asm/nonmatchings/800", func_80036AF8);

extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern u8 D_800A4F1A;

void func_80036D24(void) {
    s32 v0 = D_8006AEE8;
    D_80078F10 = 0;
    if (v0 < 2) {
        D_8006AEE8 = 0;
        D_800A4F1A = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_80036D58);


extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EB4(void) {
    if (!D_800A4F1A) {
        func_80036F18();
        D_800C6D28 = 0;
    }
}


extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EE8(void) {
    func_80036F18();
    D_800C6D28 = 0;
    D_800A4F1A = 0;
}

extern s32 D_800C6D28;
extern s32 D_80078F10;
extern s32 D_800A63E8;
extern s32 D_8006AEE8;
extern void func_80034DFC(short);

void func_80036F18(void) {
    s32 i;

    if (D_8006AEE8 != 0) {
        D_800C6D28 = D_800A63E8;
        for (i = 0; i < D_8006AEE8; i++) {
            func_80034DFC(*(short *)(&D_80078F10 + i));
            (&D_80078F10)[i] = 0;
        }
        D_8006AEE8 = 0;
    }
}

extern s32 D_80078F10;
extern s32 D_8006AEE8;

void func_80036F98(void) {
    D_80078F10 = 0;
    D_8006AEE8 = 0;
}

void func_80036FB0(s32 arg0, s32 arg1) {
    extern s32 D_8006AEE8;
    extern s32 D_80078F10;
    f64 hole;
    s32 count;
    s32 i;
    s32 *p;

    __asm__ volatile("" ::
                     "m"(hole));
    if (D_8006AEE8 > 0) {
        i = 0;
        count = D_8006AEE8;
        p = &D_80078F10;
        do {
            if (*p == arg0) {
                *p = arg1;
            }
            p++;
            i++;
        } while (i < count);
    }
}

CLEAR_TBL40(func_80037004)  /* dedup I0: shared body (src/shared/clearTbl40.h) */


/* func_80037028 -- resource-slot allocator (5 slots x 0x10 bytes at 0x80076244).
 *
 * MATCHING NOTES (P31 second pass, cookbook §31 / sched.md S1+S5):
 *
 * 1) The slot table MUST be modelled as struct arrays with symbol+scaled-index
 *    addressing (`sw $5,D_80076240+4($4)`), not as six independent `u8 X[]`
 *    externs indexed by a byte offset.  With separate symbols gcc hoists the
 *    D_80064D49 load chain to the top of the block and sinks the mark-used
 *    store (37 mismatches); with the struct form the block is exact.
 *
 * 2) TWO overlapping bases are used on purpose (D_80076240 for the words,
 *    D_80076244 for the bytes) so that EVERY field access has a NON-ZERO
 *    constant offset from its base symbol.  sched.c:memrefs_conflict_p reaches
 *    find_symbolic_term() -- and therefore proves "distinct symbols, no alias"
 *    -- only for the plain `(plus reg symbol_ref)` form.  A zero-offset store
 *    thus loses its dependence on the later D_80064D49 / D_800A463C loads,
 *    becomes ready immediately and floats to the bottom of the block.  With a
 *    single base at D_80076244 the `unk00 = val` store did exactly that
 *    (19 mismatches).  Every offset here is non-zero, so all four leading
 *    stores stay pinned behind the loads and are emitted in source order.
 *    Final addresses are unchanged: D_80076240+4 == D_80076244, +8 == 248,
 *    +12 == 24C; D_80076244+12 == D_80076250, +13 == 251, +14 == 252.
 *
 * 3) `D_8007622C[0]` (not a plain scalar) is required by the /s asymmetry in
 *    sched.c:true_dependence -- a non-MEM_IN_STRUCT_P, non-varying store is
 *    assumed not to alias a MEM_IN_STRUCT_P varying load, so the D_800A463C
 *    reload hoisted above it.  Making the store an ARRAY_REF sets /s, kills
 *    the exclusion clause, and pins the reload after it.
 *
 * 4) D_80076248 is deliberately never named: src/800.c already declares it as
 *    `extern Rsc16 D_80076248[]`, and a second `extern u8 D_80076248[]` here
 *    would be a conflicting-types error at bank time.
 */





extern Slot16A D_80076240[];
extern Slot16 D_80076244[];
extern Elm12   D_80064D49[];
extern Ent24   D_800A463C[];
extern u8  D_80076251;
extern s32 D_8007622C[];
extern W32 D_80076228;
extern W8  D_80076243;
extern W8  D_80076242;
extern W32 D_80076294;
extern W32 D_80076238;
extern s32 D_8007629C;

void func_80037028(s32 base, s32 val) {
    s32 slot;
    s32 i;
    s32 b;

    for (slot = 0, i = 0; slot < 5; slot++, i += 0x10) {
        if ((&D_80076251)[i] == 0) {
            break;
        }
    }

    if (slot < 5) {
        D_80076244[slot].unk0D = 1;
        D_80076240[slot].unk04 = val;
        D_80076244[slot].unk0C = 0;
        D_80076240[slot].unk08 = base;
        b = D_80064D49[base].unk00;
        D_80076244[slot].unk0E = b;
        D_80076240[slot].unk0C = D_800A463C[b].unk00;

        if (slot == 0) {
            s32 r;
            D_8007622C[0] = val;
            r = D_800A463C[b].unk00;
            D_80076228.v = val;
            D_80076240[0].unk00 = 0;
            D_80076243.v = 2;
            D_80076242.v = 0;
            D_80076294.v = 0;
            D_80076238.v = r;
        }
    }

    D_8007629C = 0;
}


/* The 5-entry, 0x10-stride CD-resource slot table.  src/800.c already declares the SAME
 * memory as `Rsc16 D_80076248[]` (base = 0x80076248, .unk09 = D_80076251, .unk0A = D_80076252);
 * this function also touches the word 4 bytes BELOW that base, so the array is spelled from
 * D_80076244 here (offsets shift by -4; the emitted %lo values are identical, and every one of
 * D_80076244/48/4C/50/51/52 is a relocation symbol in this function's own .s).
 *      .unk00 = D_80076244   .unk04 = D_80076248   .unk08 = D_8007624C
 *      .unk0C = D_80076250   .unk0D = D_80076251   .unk0E = D_80076252
 * 0x80076244 + 5*0x10 == 0x80076294, which is the next scalar this function clears. */

/* 2-byte stride u16 table.  Declared as an array-of-STRUCT (cookbook §18) so gcc folds
 * %lo(D_80065438) into each indexed load instead of materialising the base into a register
 * (a plain `extern u16 D_80065438[]` CSEs the two accesses into one lui/addiu/addu base). */


/* THE TAIL SCHEDULE LEVER (gcc-2.7.2 sched.c:817 true_dependence / :845 anti_dependence).
 * The `if (i == 0)` block interleaves the varying-address load `D_800A463C[k].unk00`
 * (MEM_IN_STRUCT_P=1, rtx_addr_varies_p=1) with fixed-address stores to these scalars.
 * true_dependence's last guard reads
 *      ! (MEM_IN_STRUCT_P (x) && rtx_addr_varies_p (x) && GET_MODE (x) != QImode
 *         && ! MEM_IN_STRUCT_P (mem) && ! rtx_addr_varies_p (mem))
 * so a /s VARYING load and a plain NON-/s FIXED store are declared non-aliasing — every
 * store/load edge disappears, the load floats to the top of the block and the whole tail
 * comes out permuted.  Declaring these scalars as single-field structs sets MEM_IN_STRUCT_P
 * on their MEMs too, which fails `! MEM_IN_STRUCT_P (mem)` and restores the real
 * store->load / load->store edges.  The symbol names are untouched (offset 0 of a 1-field
 * struct), so every relocation is still exactly D_8007622C / D_80076228 / ... as in the .s. */
typedef struct { s16 v; } W16;

extern Slot16 D_80076244[];
extern W32   D_80076228;
extern s32   D_8007622C[];
extern W32   D_80076238;
extern Slot16A D_80076240[];
extern W8    D_80076242;
extern W8    D_80076243;
extern W32   D_80076294;
extern s32   D_8007629C;       /* src/800.c already declares this one as `extern s32` */
extern u8    D_800BA320[];
extern H2    D_80065438[];
extern s32   D_800652F0[];
extern Ent24 D_800A463C[];
extern s32   D_800A469C;
extern s16   D_800A46A0;
extern s16   D_800A46A2;
extern u8    D_800A46B0;

extern void  func_800415A8(s32);

void func_80037144(s32 idx) {
    s32 i;
    s32 k;
    s32 t;
    s32 v;
    s32 one;
    s32 ent;

    for (i = 0; i < 5; i++) {
        if (D_80076244[i].unk0D == 0) {
            break;
        }
    }
    if (i < 5) {
        one = 1;
        D_80076244[i].unk00 = (s32)D_800BA320;
        /* scheduling barrier: the slot stores and the D_80065438 load DO disambiguate here
         * (both /s and both varying -> memrefs_conflict_p:614 falls through to
         * find_symbolic_term and the two symbols differ), so without this gcc hoists the
         * D_80065438 load above all the slot stores and permutes the head block.
         * Emits zero instructions. */
        __asm__ __volatile__("" ::: "memory");
        D_80076244[i].unk0C = 0;
        D_80076244[i].unk0D = one;
        D_80076244[i].unk04 = idx | 0x2000;
        D_80076244[i].unk0E = 4;
        v = D_800652F0[D_80065438[idx].f0];
        D_800A469C = v;
        D_80076244[i].unk08 = v;
        k = 4;
        if (D_800A46B0 == 0) {
            if (D_800A46A0 == (D_80065438[idx].f0 | 0x4000)) {
                D_80076244[i].unk04 |= 0x1000;
                goto after;
            }
            t = D_800A46A2;
            D_800A46B0 = one;
        } else {
            t = D_800A46A2;
        }
        if (t >= 0) {
            func_800415A8(t);
            D_800A46A2 = -1;
        }
    after:
        if (i == 0) {
            D_8007622C[0] = (s32)D_800BA320;
            ent = D_800A463C[k].unk00;
            D_80076228.v = (s32)D_800BA320;
            D_80076240[0].unk00 = 0;
            D_80076243.v = 1;
            D_80076242.v = 0;
            D_80076294.v = 0;
            D_80076238.v = ent;
        }
    }
    D_8007629C = 0;
}

CLEAR_TBL40(func_80037334)  /* dedup I0: shared body (src/shared/clearTbl40.h) */

extern s32 D_8007623C;
void func_80037358(int posInt) {
    D_8007623C = posInt;
}


extern u8 D_80076251;   /* Law 2: exact form from src/shared/clearTbl40.h */
extern u8 D_80076220[];
extern u8 D_80076250[];

void *func_80037368(int *out) {
    int count = 0;
    u8 *ptr = D_80076220;
    int i;

    for (i = 0; i < 0x50; i += 0x10) {
        *ptr = 0;
        ptr++;

        if ((&D_80076251)[i] != 0) {
            D_80076220[count] = D_80076250[i];
            count++;
        }
    }

    *out = count;
    return D_80076220;
}



typedef struct {
    s16 unk00;
    u8  pad02[4];
    u16 unk06;
} StructA4E88;

/* Law 2: the destination TU (src/800.c) already declares D_80065438 as an array-of-struct
 * (H2 = { u16 f0; }) rather than a plain u16[] — refuse-TYPE(D_80065438, u16 vs H2).
 * Adopt the TU's spelling verbatim; the use site indexes .f0 instead of dereferencing a u16*. */

extern StructA4E88 D_800A4E88;
extern u8           D_800BA320[];
extern Rsc16        D_80076248[];    /* .unk09 = D_80076251, .unk0A = D_80076252 */
extern u8           D_80076251;      /* Law 2: exact form from src/shared/clearTbl40.h (see func_80037368) */
extern u8           D_80076250[];
extern u8           D_80076298;
extern H2           D_80065438[];

extern void func_8002D7FC(s32 arg0);
extern void func_8002FDE8(s32 arg0, void *arg1);

void func_800373D0(void) {
    register StructA4E88 *sp2 __asm__("$18");
    register u8          *sp3 __asm__("$19");
    register Rsc16 *p __asm__("$16");
    register s32 i __asm__("$17");

    sp2 = &D_800A4E88;
    sp3 = D_800BA320;

    p = D_80076248;
    i = 0;
    do {
        if ((&D_80076251)[i] != 0) {
            if (D_80076250[i] != 0) {
                if (p->unk00 & 0x3000) {
                    sp2->unk00 = p->unk00 & 0xFFF;
                    sp2->unk06 |= 0x20;
                    func_8002D7FC((s32) sp3);
                    if (!(p->unk00 & 0x1000)) {
                        func_8002FDE8(D_80065438[sp2->unk00].f0, sp3 + 0x7000);
                    }
                }
            }
        }
        p++;
        i += 0x10;
    } while ((s32) p < (s32) &D_80076298);
}

int func_800374CC(int *out)
{
    extern W8 D_80076243;
    extern s32 D_8007623C;

    s32 x = D_80076243.v;
    if (x != 4 && x != 0 && x != 5) {
        *out = D_8007623C;
        return 0;
    }
    return 1;
}




typedef struct {
    u8  unk00;
    u8  unk01[11];
} Rsc12;                      /* 0x0C */

extern s32  D_8007629C;
extern u8   D_8006AEF4;
extern u8   D_80076298;
extern Rsc16 D_80076248[];    /* .unk09 = D_80076251, .unk0A = D_80076252 */
extern Rsc12 D_80064D4A[];
extern Rsc24  D_800A4640[];
extern s16  D_800C5328[];
extern s16  D_800C532A[];

extern s32  func_8003C4F0(s32);
extern void func_800415A8(s32);
extern void func_80031A98(void);

s32 func_8003750C(void) {
    s32 i;
    s32 val;
    s32 k;
    s32 h;

    switch (D_8007629C) {
    case 0:
        if (D_8006AEF4 & 2) {
            return 0;
        }
        D_8006AEF4 |= 2;
        D_8007629C = 1;
        /* fallthrough */
    case 1:
        if (D_8006AEF4 & 1) {
            if (func_8003C4F0(0) == 0) {
                return 0;
            }
        }
        D_8007629C = D_8007629C + 1;
        /* fallthrough */
    case 2:
        for (i = 0; i < 5; i++) {
            if (D_80076248[i].unk09 == 0) {
                continue;
            }
            val = D_80076248[i].unk00;
            k = D_80076248[i].unk0A;
            if (val & 0x6000) {
                continue;
            }
            h = D_800A4640[k].unk04;
            if (h != 0 && h != D_80064D4A[val].unk00) {
                D_800C532A[D_800A4640[k].unk08 * 2] = -1;
                D_800A4640[k].unk04 = 0;
                D_800A4640[k].unk08 = 0;
            }
            if (D_800A4640[k].unk10 != 0) {
                continue;
            }
            D_800A4640[k].unk10 = 1;
            D_800C5328[D_800A4640[k].unk00 * 2] = -1;
            if (D_800A4640[i].unk02 >= 0) {
                func_800415A8(D_800A4640[i].unk02);
                D_800A4640[i].unk02 = -1;
            }
            func_80031A98();
        }
        D_8007629C = 0;
        D_80076298 = 0;
        return 1;
    default:
        return 0;
    }
}

typedef struct { u8 v; } W8_;
extern W8_ D_80076242_ __asm__("D_80076242");

extern u8  D_8006AEF4;
extern s32 func_8003C4F0(s32);
extern void func_800373D0(void);

int func_8003775C(void) {
    u32 t;

    if (D_80076242_.v != 0) {
        if (func_8003C4F0(0) == 0) {
            return 0;
        }
        D_80076242_.v = 0;
        t = D_8006AEF4;
    } else {
        t = D_8006AEF4;
    }
    D_8006AEF4 = t & 0xFC;
    func_800373D0();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_800377D8);

extern s32 D_800BA0F8;
void func_80037CC8(void) {
    D_800BA0F8 = 0;
}


extern u8 D_8006AEF4;
extern s32 D_800BA0F8;

int func_80037CD8(void *arg) {
    if ((D_8006AEF4 & 0x2) != 0) {
        s32 *handler = (s32 *)&D_800BA0F8;

        if (*handler != 0) {
            int result = ((int (*)(void *))*handler)(arg);

            if (result != 0) {
                u8 flags = D_8006AEF4;
                *handler = (s32)arg;
                D_8006AEF4 = flags & 0xFD;
                return 1;
            }
            return 0;
        }
    }

    D_800BA0F8 = (s32)arg;
    D_8006AEF4 &= 0xFD;
    return 1;
}

extern u8 D_8006AEF4;
extern s32 D_800BA0F8;

void func_80037D74(void) {
    D_8006AEF4 &= 0xFD;
    D_800BA0F8 = 0;
}


extern u8 *D_800762B0;
extern u8 D_800A4EFE[];
extern s32 D_80073140[];

extern u8 D_800C6DE0[];
extern u8 D_800C6DE4[];
extern u8 D_800C6DEC[];
extern u8 D_800C6DEE[];
extern u8 D_800C6E2A[];
extern u8 D_800C6E2B[];
extern u8 D_800C6E2C[];
extern u8 D_800C6E2D[];
extern u8 D_800C6E2E[];

extern u8 D_800B9EC8[];
extern u8 D_800B9ED2[];
extern u8 D_800B9ED3[];

extern s32 D_80079A68;
extern void func_8003D424(s32 *);

void func_80037D98(void) {
    s32 i;
    s32 offset;
    s32 val;
    s32 *table;

    D_800762B0 = D_800A4EFE;

    i = 0;
    table = D_80073140;
    offset = 0;
    while (i < 0x10) {
        val = *table;
        table++;
        i++;
        D_800C6E2A[offset] = 0;
        D_800C6E2B[offset] = 0;
        D_800C6E2C[offset] = 0;
        D_800C6E2D[offset] = 0;
        *(s16 *)&D_800C6DEC[offset] = 0;
        *(s16 *)&D_800C6DEE[offset] = 0;
        *(s32 *)&D_800C6DE4[offset] = 0;
        D_800C6E2E[offset] = 0;
        *(s32 *)&D_800C6DE0[offset] = val;
        offset += 0x60;
    }

    i = 0;
    offset = 0;
    for (; i < 2; i++) {
        D_800B9ED3[offset] = 0;
        D_800B9ED2[offset] = 0;
        *(s16 *)&D_800B9EC8[offset] = i;
        offset += 0x1FC;
    }

    func_8003D424(&D_80079A68);
}

extern u8 D_800C6E2E[];

void func_80037EA0(void)
{
    extern void func_8003D3B4(s32, s32);
    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    register u32 mask __asm__("$18");

    i = 0;
    mask = 0xFFF9FFFF;
    p = D_800C6E2E;
    do {
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= mask;
            p[0] = 0;
        }
        i++;
        p += 0x60;
    } while (i < 0x10);
}

void func_80037F3C(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    u8 *base;

    base = D_800C6DD0;
    i = 0;
    p = base + 0x5E;
    do {
        if (p[-4] != 0 && p[-1] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(p - 0x4A) = 0;
            p[-1] = 0;
            p[0] = 0;
        }
        i++;
        p += 0x60;
        base += 0x60;
    } while (i < 0x10);
}

/* --- TU context as in src/800.c (file-scope, verbatim spellings) --- */
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;
extern u8  D_800A4F1D;
extern u8 D_800C6E2E[];
extern void func_8003BE74(s32, s32);
extern void func_80037FC4(void);

void func_80037FC4(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_80038A58(void);
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    register u32 mask __asm__("$18");
    u8 *base;

    if (D_800A4F1D == 0) {
        func_80038A58();
    }

    i = 0;
    mask = 0xFFF9FFFF;
    p = D_800C6E2E;
    do {
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= mask;
            p[0] = 0;
        }
        i++;
        p += 0x60;
    } while (i < 0x10);

    if ((D_800A2B98 & 0xFFFF) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFFFF);
        D_800A2B98 &= 0xFF0000;
    }

    if ((D_800A2BA0 & 0xFFFF) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFFFF);
        D_800A2BA0 &= 0xFF0000;
    }

    base = D_800C6DD0;
    i = 0;
    p = base + 0x5E;
    do {
        if (p[-4] != 0 && p[-1] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(p - 0x4A) = 0;
            p[-1] = 0;
            p[0] = 0;
        }
        i++;
        p += 0x60;
        base += 0x60;
    } while (i < 0x10);

    if ((D_800C7D20 & 0xFFFF) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFFFF);
        D_800C7D20 &= 0xFF0000;
    }

    if ((D_800C7D2C & 0xFFFF) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFFFF);
        D_800C7D2C &= 0xFF0000;
    }
}

extern u8 D_800B9CD8[];

void func_8003819C(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 *base;
    s16 idx;

    idx = (s16)a1;
    if (idx <= 0) {
        base = &D_800B9CD8[((a0 << 7) - a0) << 2];
        *(s16 *)(base + (idx << 3) + 0x16) = a2;
        *(s16 *)(base + (idx << 3) + 0x14) = a3;
        *(u8 *)(base + (idx << 3) + 0x18) = 1;
        *(u8 *)(base + 0x1F4) = 1;
    }
}


extern u8 D_800B9CF0[];

s32 func_800381E4(s32 a0, s32 a1) {
    s32 v0;

    a1 = (a1 << 16) >> 13;
    v0 = (a0 << 7) - a0;
    v0 = v0 << 2;
    a1 = a1 + v0;
    return D_800B9CF0[a1];
}


extern u8 D_800B9CD8[];
extern u8 D_800C1320[];
extern u8 *D_800A6428;

extern s32 func_80038698(void *arg0);
extern s32 func_800387C0(void *arg0);
extern void func_80038838(void *arg0);

s32 func_80038210(s32 a0, s16 a1, s32 a2)
{
    u8 *entry;
    s32 i;
    s32 k;
    u8 *q;
    s32 v1;

    entry = D_800B9CD8;
    for (i = 0; i < 2; i++, entry += 0x1FC) {
        if (entry[0x1FB] == 0) {
            D_800A6428 = entry + 0x1BA;
            *(s32 *)entry = a0;
            *(s16 *)(entry + 0x1EC) = a1;
            *(s32 *)(entry + 0x1E8) = a2;
            *(u8 **)(entry + 0x1D8) = D_800C1320;
            *(u8 **)(entry + 0x1DC) = D_800C1320 + 0x20;
            *(u8 **)(entry + 0x1E0) = D_800C1320 + 0x820;
            if (func_80038698(entry) != 0) {
                return -1;
            }
            if (func_800387C0(entry) != 0) {
                return -1;
            }
            func_80038838(entry);
            v1 = *(s32 *)entry;
            entry[0x1FB] = 1;
            *(s32 *)(entry + 4) = v1;
            entry[0x1FA] = 0;
            for (k = 0xF, q = entry + 0xF; k >= 0; k--, q--) {
                q[0x1BA] = 0;
            }
            return i;
        }
    }
    return -1;
}

extern u8 D_800B9ED2[];
extern u8 D_800B9CD8[];

typedef s32 a32;

void func_80038308(s16 a0)
{
    register a32 arg0 asm("$4");
    s32 offset;

    offset = arg0 * 127;
    offset = offset * 4;
    D_800B9ED2[offset] = 1;
    func_80038908(&D_800B9CD8[offset]);
}

extern u8 D_800B9ECA[];

void func_8003834C(s32 a0, s16 a1) {
    s32 offset = ((a0 << 7) - a0) << 2;
    *(s16 *)&D_800B9ECA[offset] = a1;
}


extern u8 D_800B9ED3[];
extern u8 D_800B9ED2[];

s32 func_8003836C(s32 a0) {
    s32 index;
    u8 val;
    index = a0 * 127;
    index = index * 4;
    val = D_800B9ED3[index];
    if (val == 0) {
        return 0;
    }
    return D_800B9ED2[index];
}

INCLUDE_ASM("asm/nonmatchings/800", func_800383A4);

INCLUDE_ASM("asm/nonmatchings/800", func_800384A8);

void func_800385C0(s16 a0)
{
    extern u8 D_800C6E2A[];
    extern u8 D_800B9ED2[];
    extern u8 D_800B9ED3[];
    register s32 a0v __asm__("$4");
    register u8 *v1 __asm__("$3");
    s32 a1;

    for (a1 = 0, v1 = D_800C6E2A; a1 < 0x10; a1++, v1 += 0x60) {
        if (v1[2] != 0 && *(s16 *)(*(s32 *)(v1 - 0xA) + 0x1F0) == a0v) {
            v1[2] = 0;
            v1[0] = 0;
        }
    }

    D_800B9ED2[((a0v << 7) - a0v) << 2] = 0;
    D_800B9ED3[((a0v << 7) - a0v) << 2] = 0;
}


extern u8 D_800B9E92[];

void func_80038638(s32 a0, s32 a1) {
    u8 *ptr;
    s32 offset;
    offset = a0 * 127;
    offset = offset * 4;
    ptr = D_800B9E92 + offset;
    *(ptr + a1) |= 1;
}


extern u8 D_800B9E92[];

void func_80038668(s32 a0, s32 a1) {
    s32 offset = ((a0 << 7) - a0) << 2;
    char *baseptr = (char *)D_800B9E92 + offset;
    *(baseptr + a1) &= 0xFE;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80038698);

INCLUDE_ASM("asm/nonmatchings/800", func_800387C0);


void func_80038838(void *arg0)
{
    register unsigned char *a3 asm("$7");
    register unsigned char *a1 asm("$5");
    register unsigned char *v1;
    register unsigned char *v0 asm("$2");
    register int a2 asm("$6");
    register int v0_c;
    register int const1 asm("$8");
    register int const2 asm("$9");
    register int const3 asm("$3");

    a3 = (unsigned char *)arg0 + 0x1A;
    a2 = 0;
    const1 = 0x40;
    const2 = 0x7F;
    a1 = (unsigned char *)arg0 + 0x1B;

    do {
        v1 = a3 + 0x9;
        v0_c = 0xF;
        a3[0x0] = a2;
        *(unsigned short *)(a1 + 0x1) = const1;
        a1[0x3] = const1;
        a1[0x6] = 0;
        a1[0x0] = const2;

        do {
            v1[0x0] = 0;
            v0_c--;
            v1++;
        } while (v0_c >= 0);

        a2++;
        a1 += 0x1A;
        a3 += 0x1A;
    } while (a2 < 0x10);

    a2 = 0;
    const3 = 0x4000;
    v0 = (unsigned char *)arg0;
    do {
        v0[0x18] = 0;
        *(unsigned short *)(v0 + 0x12) = const3;
        v0 += 0x8;
        a2++;
    } while (a2 <= 0);

    *(int *)((unsigned long)arg0 + 0x8) = 1;
    *(int *)((unsigned long)arg0 + 0x1D0) = 0xE10;
    *(int *)((unsigned long)arg0 + 0x1D4) = 0xE10;
    *(int *)((unsigned long)arg0 + 0x1CC) = 0xE10;
    *(unsigned char *)((unsigned long)arg0 + 0x1F4) = 0;
    *(unsigned short *)((unsigned long)arg0 + 0x1E4) = 0x78;
    *(unsigned char *)((unsigned long)arg0 + 0x1F7) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F8) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F9) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1FA) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F6) = 0;
}

s32 func_800388E8(void *arg0, s16 arg1) {
    return arg1 * *(s16 *)((u8 *)arg0 + 0x10) * 4 >> 16;
}

void func_80038908(unsigned char *arg0) {
    extern short D_800A4EF8;
    extern unsigned short D_800A4EE0;
    int counter;
    int acc;
    unsigned short *ptr;

    acc = D_800A4EF8 << 7;
    acc *= D_800A4EE0;
    ptr = (unsigned short *)(arg0 + 0x12);
    counter = 0;
    acc >>= 14;
    do {
        acc *= *ptr;
        acc >>= 14;
        counter--;
        ptr += 4;
    } while (counter >= 0);
    *(unsigned short *)(arg0 + 0x10) = (unsigned short)acc;
}


extern u8 *D_800762B0;
extern u8 D_800762B4[];
extern u8 D_800C6E2A[];

void func_80038958(void) {
    register u8 *a3 __asm__("$7");
    register u8 *a2 __asm__("$6");
    register s32 a1 __asm__("$5");
    register u8 *a0 __asm__("$4");
    register s32 t0 __asm__("$8");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    a3 = D_800762B0;
    a2 = D_800762B4;
    a1 = 0;
    t0 = 3;
    a0 = D_800C6E2A;

    while (a1 < 0x10) {
        v0 = *a3;
        if (v0 == 0 || v0 == t0) {
            if (*a2 == 0) {
                v0 = *a0;
                a0[1] = 0;
                if (v0 != 0) {
                    v0 = *(s16 *)(a0 - 0x54);
                    v1 = v0 << 1;
                    v1 = v1 + v0;
                    v1 = v1 << 2;
                    v1 = v1 + v0;
                    v0 = *(s32 *)(a0 - 0xA);
                    v1 = v1 << 1;
                    v0 = v0 + v1;
                    v0 = v0 + a1;
                    *(u8 *)(v0 + 0x23) = 0;
                    a0[0] = 0;
                }
            }
        }
        a1++;
        a0 += 0x60;
        a3++;
        a2++;
    }
}


extern u8 *D_800762B0;
extern u8 D_800762B4[];

s32 func_80038A00(void) {
    u8 *ptr1 = D_800762B0;
    u8 *ptr2 = D_800762B4;
    s32 i = 0;

    while (i < 0x10) {
        if (*ptr1 == 0x2 && *ptr2 == 0) {
            return i;
        }
        i++;
        ptr1++;
        ptr2++;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80038A58);

INCLUDE_ASM("asm/nonmatchings/800", func_80038FC4);

INCLUDE_ASM("asm/nonmatchings/800", func_80038FFC);

void func_8003916C(s16 arg0)
{
    extern u8 D_800C6DD0[];
    u8 *a1;
    s32 off;

    a1 = &D_800C6DD0[arg0 * 0x60];
    if (a1[0x5A] != 0) {
        off = *(s16 *)&a1[6] * 26;
        *(u8 *)(*(u32 *)&a1[0x50] + off + arg0 + 0x23) = 0;
        a1[0x5A] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800", func_800391D4);

void func_80039300(void) {
}

INCLUDE_ASM("asm/nonmatchings/800", func_80039308);

INCLUDE_ASM("asm/nonmatchings/800", func_80039B20);

void func_80039C5C(s32 *param_1) {
    *param_1 += 2;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80039C70);

INCLUDE_ASM("asm/nonmatchings/800", func_80039DEC);

void func_80039F14(u8 *arg0, s16 arg1, u8 arg2) {
    u8 b;

    arg0 += arg1 * 26;
    b = arg0[0x21];
    arg0[0x20] = arg2;
    arg0[0x22] = arg2 + 1;
    arg0[0x21] = b | 2;
}

INCLUDE_ASM("asm/nonmatchings/800", func_80039F50);

typedef struct {
    u8 b0;
    u8 pad[25];
} A098Rec;

typedef struct {
    u8 *stream;
    u8 pad04[0x16];
    A098Rec rec[1];
} A098Ctx;

void func_8003A098(A098Ctx *arg0, s16 arg1) {
    u8 *v1;

    v1 = arg0->stream;
    arg0->stream = v1 + 1;
    arg0->rec[arg1].b0 = *v1;
}

void func_8003A0D0(s32 *arg0) {
    (*arg0)++;
}

INCLUDE_ASM("asm/nonmatchings/800", func_8003A0E4);


typedef struct {
    /* 0x000 */ u8 *ptr;
    /* 0x004 */ u8 pad_004[0x1D0 - 0x004];
    /* 0x1D0 */ s32 unk1D0;
    /* 0x1D4 */ u8 pad_1D4[0x1E4 - 0x1D4];
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ u8 pad_1E8[0x1F9 - 0x1E8];
    /* 0x1F9 */ u8 unk1F9;
} func_8003A234_Ctx;

void func_8003A234(func_8003A234_Ctx *a0) {
    u8 *a2 = a0->ptr;
    u8 v1;

    a0->ptr = a2 + 1;
    v1 = *a2;

    switch (v1) {
    case 0x20:
        a0->ptr = a2 + 3;
        break;

    case '/':
        a0->ptr = a2 + 2;
        a0->unk1F9 = 1;
        break;

    case 'Q':
        {
            register s32 num __asm__("$4");
            s32 den;
            s32 b3;
            s32 b4;
            s32 q;

            a0->ptr = a2 + 2;
            den = a2[1];
            if (den != 3) {
                a0->unk1F9 = 1;
                break;
            }
            num = 0x3938700;
            a0->ptr = a2 + 3;
            den = a2[2];
            a0->ptr = a2 + 4;
            b3 = a2[3];
            a0->ptr = a2 + 5;
            b4 = a2[4];
            den = den << 16;
            den += b3 << 8;
            den += b4;
            q = num / den;
            a0->unk1E4 = (s16)q;
            a0->unk1D0 = q * a0->unk1E6;
        }
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 'T':
    case 0x58:
    case 0x59:
    case 0x7F:
        {
            register u8 *p __asm__("$3") = a0->ptr;
            u8 *np = p + 1;
            a0->ptr = np;
            {
                register s32 byte __asm__("$5") = p[0];
                a0->ptr = np + byte;
            }
        }
        break;

    case 0:
        a0->ptr = a2 + 2;
        {
            register s32 b1 __asm__("$5") = a2[1];
            if (b1 != 2) {
                a0->unk1F9 = 1;
                break;
            }
        }
        a0->ptr = a2 + 4;
        break;

    default:
        a0->unk1F9 = 1;
        break;
    }
}

u32 func_8003A3D8(u32 a) {
    return ((a & 0xFF) << 24) + (((a >> 8) & 0xFF) << 16) + (((a >> 16) & 0xFF) << 8) | (a >> 24);
}

s32 func_8003A404(u32 arg)
{
    u32 h = arg >> 8;
    u32 l = (arg & 0xFF) << 8;
    return (s16)((h & 0xFF) + l);
}

extern void _SpuInit(s32);

void func_8003A424(void) {
    _SpuInit(0);
}
