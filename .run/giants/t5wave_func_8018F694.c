// @class: other
// @stuck: none — MATCH (478 ins, relocation-masked byte-identical)

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

typedef struct { u16 vx, vy, vz, pad; } UVEC_8018F694;
typedef struct { u32 addr : 24; u8 len; } PTag_8018F694;
typedef struct {
    u32 addr : 24;
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0, x1, y1;
} LineF2_8018F694;
typedef struct {
    u32 addr : 24;
    u8 len;
    u32 code0;
} TPage_8018F694;
typedef struct {
    u8 r, g, b, pad0;
    u8 dr, dg, db, pad1;
    s16 vx, vy, vz, tm;
} Blip_8018F694;

void func_8018F694(void)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void *func_80010A08(s32);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blip_8018F694 D_801D57F0[];

    UVEC_8018F694 sxy;
    UVEC_8018F694 p0;
    UVEC_8018F694 p1;
    long flag;
    long otz;
    s32 i;
    PTag_8018F694 *ot;
    PTag_8018F694 *otp;
    Blip_8018F694 *bp;
    s32 t, c, d, z, x, n;

    ot = (PTag_8018F694 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    bp = D_801D57F0;

#define EMIT_8018F694() { \
    LineF2_8018F694 *pk = (LineF2_8018F694 *)func_80010A08(0x10); \
    pk->len = 3; \
    pk->code = 0x42; \
    pk->r0 = bp->r; \
    pk->g0 = bp->g; \
    pk->b0 = bp->b; \
    pk->x0 = p0.vx; \
    pk->y0 = p0.vy; \
    pk->x1 = p1.vx; \
    pk->y1 = p1.vy; \
    pk->addr = otp->addr; \
    otp->addr = (u32) pk; }

    for (i = 0; i < 32; i++, bp++) {
        t = bp->tm;
        __asm__ __volatile__ ("" : "=r" (t) : "0" (t));
        if (t != 0) {
            gte_ldv0(&bp->vx);
            gte_rtps();
            gte_stsxy((long *) &sxy);
            gte_stflg(&flag);
            gte_stszotz(&otz);
            if ((u16) (sxy.vx + 0x200) < 0x401 &&
                (u16) (sxy.vy + 0x180) < 0x301 &&
                (u32) (otz - 0x10) < 0x1000) {
                z = otz - 0x10;
                c = t >> 6;
                d = (t * 3) >> 8;
                otp = (PTag_8018F694 *) ((z << 2) + (s32) ot);

                p0.vx = sxy.vx - c;
                p0.vy = sxy.vy - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vx = sxy.vx + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vy = sxy.vy + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                p0.vx = sxy.vx - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                {
                    TPage_8018F694 *tp = (TPage_8018F694 *) func_80010A08(8);
                    tp->len = 1;
                    tp->code0 = 0xE100002A;
                    tp->addr = otp->addr;
                    otp->addr = (u32) tp;
                }

                n = bp->r;
                x = n - bp->dr;
                n = x;
                if (x < 0) { n = 0; }
                bp->r = n;
                n = bp->g;
                x = n - bp->dg;
                n = x;
                if (x < 0) { n = 0; }
                bp->g = n;
                n = bp->b;
                x = n - bp->db;
                n = x;
                if (x < 0) { n = 0; }
                bp->b = n;
                x = n | (bp->r | bp->g);
                if ((u8) x == 0) {
                    bp->tm = 0;
                }
            }
        }
    }
}
