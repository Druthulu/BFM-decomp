
typedef struct {
    u8 pad0, pad1, pad2, len;
    u32 tpage;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 w, h;
} Sprt24;

extern s32 D_800EC690;
extern s32 D_800EC694;
extern s32 D_800EC68C;
extern s16 D_800EC678;
extern u16 D_800B9A02;
extern u8 D_800AA60C[];
typedef struct { u16 v; } S16_800CF3E8;
extern S16_800CF3E8 sD800B9A02 __asm__("D_800B9A02");
#define OTIDX ((fr = sD800B9A02), fr.v)
extern Sprt24 D_800EC7C8[];
extern Sprt24 D_800EC7F8[];
extern Sprt24 D_800EC828[];
extern Sprt24 D_800EC858[];
extern Sprt24 D_800EC6A8[];
extern Sprt24 D_800EC6D8[];
extern Sprt24 D_800EC708[];
extern Sprt24 D_800EC738[];
extern Sprt24 D_800EC768[];
extern Sprt24 D_800EC798[];
extern u16 D_800EC7DA[];
extern u16 D_800EC80A[];
extern u16 D_800EC83A[];
extern u16 D_800EC86A[];

#define OTG (*(u32 *)(D_800AA60C + OTIDX * 0x4000))
#define ADDPRIM(ot, p) \
    *(u32 *)(p) = (*(u32 *)(p) & 0xFF000000) | ((ot) & 0xFFFFFF); \
    (ot) = ((ot) & 0xFF000000) | ((u32)(p) & 0xFFFFFF);
#define ADDPRIM2(ot, p, LO, HI) \
    *(u32 *)(p) = (*(u32 *)(p) & (HI)) | ((ot) & (LO)); \
    (ot) = ((ot) & (HI)) | ((u32)(p) & (LO));

void func_800CF3E8(void) {
    Sprt24 *pA, *pF, *pD, *p1, *p2, *p4;
    s32 c24;
    s32 w60;
    u32 tv0;
    u32 tv1;
    register u32 tv2 __asm__("$15");
    u32 tv3;
    u32 tv4;
    u32 b1a;
    u32 b1c;
    register s32 c5 __asm__("$6");
    register s32 q5 __asm__("$13");
    register u32 mq2 __asm__("$8");
    register Sprt24 *pC __asm__("$3");
    register Sprt24 *p3 __asm__("$9");
    register Sprt24 *p5 __asm__("$4");
    register Sprt24 *p6 __asm__("$3");
    register u32 *ot __asm__("$5");
    s32 idx = D_800B9A02;
    S16_800CF3E8 fr;

    if (D_800EC690 == 1) goto blk1;
    if (D_800EC690 < 2) goto final;
    if (D_800EC690 == 2) goto blk2;
    goto final;

blk1:
    if (D_800EC694 != 0) {
    b1a = 0xE100008A;
    mq2 = 0xFFFFFF;
    b1c = 0xE100008C;
    { Sprt24 *b_ = D_800EC7C8; pA = &b_[idx]; }
    q5 = 5;
    pA->len = q5;
    ((u32 *)&D_800EC7C8[idx])[1] = b1a;
    pA->code = 0x64;
    pA->r0 = pA->g0 = pA->b0 = D_800EC68C;
    pA->x0 = -0xB0;
    pA->y0 = 0x54;
    pA->u0 = 0;
    pA->v0 = 0;
    pA->clut = 0x7800;
    pA->w = 0x100;
    pA->h = 0x20;
    D_800EC7DA[idx * 12] = 0x7880;
    ADDPRIM2(OTG, pA, mq2, 0xFF000000);

    __asm__("");
    { Sprt24 *b_ = D_800EC7F8; pC = &b_[idx]; }
    pC->len = q5;
    ((u32 *)&D_800EC7F8[idx])[1] = b1c;
    pC->code = 0x64;
    pC->r0 = pC->g0 = pC->b0 = D_800EC68C;
    pC->x0 = 0x50;
    w60 = 0x60;
    pC->y0 = 0x54;
    pC->u0 = 0;
    pC->v0 = 0;
    __asm__("");
    pC->clut = 0x7800;
    pC->w = w60;
    pC->h = 0x20;
    D_800EC80A[idx * 12] = 0x7880;
    ADDPRIM2(OTG, pC, mq2, 0xFF000000);

    }
    goto final;
blk2:
    { Sprt24 *b_ = D_800EC828; pF = &b_[idx]; }
    pF->len = 5;
    ((u32 *)&D_800EC828[idx])[1] = 0xE100008F;
    mq2 = 0xFFFFFF;
    pF->code = 0x64;
    pF->r0 = pF->g0 = pF->b0 = D_800EC68C;
    pF->x0 = -0x40;
    pF->y0 = 0x44;
    pF->u0 = 0;
    pF->v0 = 0;
    pF->clut = 0x7800;
    pF->w = 0x80;
    pF->h = 0x40;
    D_800EC83A[idx * 12] = 0x7A80;
    ADDPRIM2(OTG, pF, mq2, 0xFF000000);

    { Sprt24 *b_ = D_800EC858; pD = &b_[idx]; }
    pD->len = 5;
    ((u32 *)&D_800EC858[idx])[1] = 0xE100008D;
    pD->code = 0x64;
    pD->r0 = pD->g0 = pD->b0 = D_800EC68C;
    pD->x0 = -0x70;
    pD->y0 = D_800EC678 * 32 + 0x44;
    pD->u0 = 0;
    pD->v0 = 0;
    pD->clut = 0x7800;
    pD->w = 0xE0;
    pD->h = 0x20;
    D_800EC86A[idx * 12] = 0x7800;
    ADDPRIM2(OTG, pD, mq2, 0xFF000000);

final:
    tv0 = 0xE100008A;
    tv1 = 0xE100008C;
    tv2 = 0xE100008E;
    tv3 = 0xE100009A;
    tv4 = 0xE100009C;
    { Sprt24 *b_ = D_800EC6A8; p1 = &b_[idx]; }
    c5 = 5;
    p1->len = c5;
    ((u32 *)&D_800EC6A8[idx])[1] = tv0;
    p1->code = 0x64;
    p1->r0 = p1->g0 = p1->b0 = D_800EC68C;
    p1->x0 = -0x140;
    p1->y0 = -0xDC;
    p1->u0 = 0;
    c24 = 0x24;
    p1->v0 = c24;
    p1->clut = 0x78C0;
    p1->w = 0x100;
    p1->h = 0xDC;
    { Sprt24 *b_ = D_800EC6D8; p2 = &b_[idx]; }
    p2->len = c5;
    ((u32 *)&D_800EC6D8[idx])[1] = tv1;
    p2->code = 0x64;
    p2->r0 = p2->g0 = p2->b0 = D_800EC68C;
    p2->x0 = -0x40;
    p2->y0 = -0xDC;
    p2->u0 = 0;
    p2->v0 = c24;
    p2->clut = 0x78C0;
    p2->w = 0x100;
    p2->h = 0xDC;
    { Sprt24 *b_ = D_800EC708; p3 = &b_[idx]; }
    p3->len = c5;
    ((u32 *)&D_800EC708[idx])[1] = tv2;
    p3->code = 0x64;
    p3->r0 = p3->g0 = p3->b0 = D_800EC68C;
    p3->x0 = 0xC0;
    p3->y0 = -0xDC;
    p3->u0 = 0;
    p3->v0 = c24;
    p3->clut = 0x78C0;
    p3->w = 0x80;
    p3->h = 0xDC;
    tv2 = 0xE100009E;
    { Sprt24 *b_ = D_800EC738; p4 = &b_[idx]; }
    p4->len = c5;
    ((u32 *)&D_800EC738[idx])[1] = tv3;
    p4->code = 0x64;
    p4->r0 = p4->g0 = p4->b0 = D_800EC68C;
    p4->x0 = -0x140;
    p4->y0 = 0;
    p4->u0 = 0;
    p4->v0 = 0;
    p4->clut = 0x78C0;
    p4->w = 0x100;
    p4->h = 0xDC;
    { Sprt24 *b_ = D_800EC768; p5 = &b_[idx]; }
    p5->len = c5;
    ((u32 *)&D_800EC768[idx])[1] = tv4;
    p5->code = 0x64;
    p5->r0 = p5->g0 = p5->b0 = D_800EC68C;
    p5->y0 = 0;
    p5->x0 = -0x40;
    p5->u0 = 0;
    p5->v0 = 0;
    __asm__("");
    { Sprt24 *b_ = D_800EC798; p6 = &b_[idx]; }
    p5->clut = 0x78C0;
    p5->w = 0x100;
    p5->h = 0xDC;
    p6->len = c5;
    p6->w = 0x80;
    ((u32 *)&D_800EC798[idx])[1] = tv2;
    __asm__("");
    p6->code = 0x64;
    p6->r0 = p6->g0 = p6->b0 = D_800EC68C;
    p6->x0 = 0xC0;
    p6->y0 = 0;
    p6->u0 = 0;
    p6->v0 = 0;
    p6->clut = 0x78C0;
    p6->h = 0xDC;
    ot = (u32 *)(D_800AA60C + idx * 0x4000);
    __asm__("" :: "r"(ot));
    ADDPRIM(*ot, p6);
    ADDPRIM(*ot, p5);
    ADDPRIM(*ot, p4);
    ADDPRIM(*ot, p3);
    ADDPRIM(*ot, p2);
    ADDPRIM(*ot, p1);
}
