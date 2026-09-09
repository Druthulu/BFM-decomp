/* include/gte_inline.h — the GTE coprocessor macros under Sony's names, ONE definition per signature (Phase 36 T5).
 *
 * Every macro here is the majority spelling the tree already carried in its per-TU definitions (byte-proven in the fleet),
 * named by PsyQ's inline_c.h convention; the signature of each (the bytes the build's maspsx → as tail makes of the template,
 * its operand counts, its clobbers) was computed by tools/gte_consolidate.py, which also deleted the per-TU duplicates.
 * A definition that differs from the one here only by an extra clobber (a scheduling steer) lives on in its TU as <name>_m
 * and is a marked lever, not a second spelling. Generated: do not edit by hand — regenerate with `tools/gte_consolidate.py --header`.
 */
#ifndef GTE_INLINE_H
#define GTE_INLINE_H

/* lw $12, 0( %0 );lw $13, 4( %0 );ctc2 $12, $0;ctc2 $13, $1;lw $12, 8( %0 );lw $13, 12( %0 ) …  (1016 definitions in 244 files) */
#define gte_SetRotMatrix(r0) \
    __asm__ volatile ( \
    "lw $12, 0( %0 );" \
    "lw $13, 4( %0 );" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8( %0 );" \
    "lw $13, 12( %0 );" \
    "lw $14, 16( %0 );" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14" )

/* lw $12, 0( %0 );lw $13, 4( %0 );ctc2 $12, $0;ctc2 $13, $1;lw $12, 8( %0 );lw $13, 12( %0 ) …  (1 definitions in 1 files; not a PsyQ name) */
#define gte_SetRotTransMatrix(r0) \
    __asm__ volatile ( \
    "lw $12, 0( %0 );" \
    "lw $13, 4( %0 );" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8( %0 );" \
    "lw $13, 12( %0 );" \
    "lw $14, 16( %0 );" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4;" \
    "lw $12, 20( %0 );" \
    "lw $13, 24( %0 );" \
    "ctc2 $12, $5;" \
    "lw $14, 28( %0 );" \
    "ctc2 $13, $6;" \
    "ctc2 $14, $7" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14" )

/* lw $12, 20( %0 );lw $13, 24( %0 );ctc2 $12, $5;lw $14, 28( %0 );ctc2 $13, $6;ctc2 $14, $7  (1010 definitions in 243 files) */
#define gte_SetTransMatrix(r0) \
    __asm__ volatile ( \
    "lw $12, 20( %0 );" \
    "lw $13, 24( %0 );" \
    "ctc2 $12, $5;" \
    "lw $14, 28( %0 );" \
    "ctc2 $13, $6;" \
    "ctc2 $14, $7" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14" )

/* nop;nop;avsz3  (28 definitions in 21 files) */
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

/* nop;nop;avsz4  (57 definitions in 34 files) */
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

/* nop\n\tnop\n\tdpcl  (136 definitions in 136 files) */
#define gte_dpcl() __asm__ __volatile__("nop\n\tnop\n\tdpcl")

/* mtc2 $0, $8  (136 definitions in 136 files; not a PsyQ name) */
#define gte_ldIR0z() __asm__ __volatile__("mtc2 $0, $8")

/* lwc2 $28, 0(%0)  (136 definitions in 136 files; not a PsyQ name) */
#define gte_ldIRGB(p) __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")

/* lhu $12, 0( %0 );lhu $13, 6( %0 );lhu $14, 12( %0 );mtc2 $12, $9;mtc2 $13, $10;mtc2 $14, $ …  (12 definitions in 6 files) */
#define gte_ldclmv(r0) \
    __asm__ volatile ( \
    "lhu $12, 0( %0 );" \
    "lhu $13, 6( %0 );" \
    "lhu $14, 12( %0 );" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14" )

/* lhu $13, 4( %0 );lhu $12, 0( %0 );sll $13, $13, 16;or $12, $12, $13;mtc2 $12, $0;lwc2 $1,  …  (145 definitions in 143 files) */
#define gte_ldlv0(r0) \
    __asm__ volatile ( \
    "lhu $13, 4( %0 );" \
    "lhu $12, 0( %0 );" \
    "sll $13, $13, 16;" \
    "or $12, $12, $13;" \
    "mtc2 $12, $0;" \
    "lwc2 $1, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "$13" )

/* lb $13, 1( %0 );lb $12, 0( %0 );sll $13, $13, 16;sll $12, $12, 16;srl $12, $12, 16;or $12, …  (1 definitions in 1 files; not a PsyQ name) */
#define gte_ldlvl_alt(r0) \
    __asm__ volatile ( \
    "lb $13, 1( %0 );" \
    "lb $12, 0( %0 );" \
    "sll $13, $13, 16;" \
    "sll $12, $12, 16;" \
    "srl $12, $12, 16;" \
    "or $12, $12, $13;" \
    "lb $13, 2( %0 );" \
    "mtc2 $12, $0;" \
    "mtc2 $13, $1" \
    : \
    : "r"( r0 ) \
    : "$12", "$13" )

/* lwc2 $6, 0( %0 )  (19 definitions in 2 files) */
#define gte_ldrgb(r0) \
    __asm__ volatile ( \
    "lwc2 $6, 0( %0 )" \
    : \
    : "r"( r0 ) )

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 )  (690 definitions in 307 files) */
#define gte_ldv0(r0) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 )" \
    : \
    : "r"( r0 ) )

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 0( %1 );lwc2 $3, 4( %1 );lwc2 $4, 0( %2 );lwc2  …  (227 definitions in 160 files) */
#define gte_ldv3(r0, r1, r2) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 );" \
    "lwc2 $2, 0( %1 );" \
    "lwc2 $3, 4( %1 );" \
    "lwc2 $4, 0( %2 );" \
    "lwc2 $5, 4( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 0( %1 );lwc2 $3, 4( %1 );lwc2 $4, 0( %1 );lwc2  …  (1 definitions in 1 files; not a PsyQ name) */
#define gte_ldv3_alt(r0, r1) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 );" \
    "lwc2 $2, 0( %1 );" \
    "lwc2 $3, 4( %1 );" \
    "lwc2 $4, 0( %1 );" \
    "lwc2 $5, 4( %1 )" \
    : \
    : "r"( r0 ), "r"( r1 ) )

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 8( %0 );lwc2 $3, 12( %0 );lwc2 $4, 16( %0 );lwc …  (163 definitions in 140 files) */
#define gte_ldv3c(r0) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 );" \
    "lwc2 $2, 8( %0 );" \
    "lwc2 $3, 12( %0 );" \
    "lwc2 $4, 16( %0 );" \
    "lwc2 $5, 20( %0 )" \
    : \
    : "r"( r0 ) )

/* lhu $12, 0(%0)\nlhu $13, 6(%0)\nlhu $14, 12(%0)\nmtc2 $12, $9\nmtc2 $13, $10\nmtc2 $14, $1 …  (2 definitions in 2 files; not a PsyQ name) */
#define gte_mulcol(r0) \
    __asm__ __volatile__ ( \
    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
    "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* lhu $13, 4(%0)\nlhu $12, 0(%0)\nsll $13, $13, 16\nor $12, $12, $13\nmtc2 $12, $0\nlwc2 $1, …  (2 definitions in 2 files; not a PsyQ name) */
#define gte_multrans(r0) \
    __asm__ __volatile__ ( \
    "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n" \
    "sll $13, $13, 16\n" "or $12, $12, $13\n" \
    "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n" \
    "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n" \
    "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n" \
    : : "r"(r0) : "$12", "$13", "memory")

/* nop;nop;nccs  (15 definitions in 2 files) */
#define gte_nccs() __asm__ volatile ("nop;nop;nccs")

/* nop;nop;ncct  (10 definitions in 2 files) */
#define gte_ncct() __asm__ volatile ("nop;nop;ncct")

/* nop;nop;nclip  (186 definitions in 142 files) */
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

/* lwc2 $0, 0( %1 );lwc2 $1, 4( %1 );nop;nop;mvmva 1, 0, 0, 3, 0;swc2 $25, 0( %0 );swc2 $26,  …  (1 definitions in 1 files; not a PsyQ name) */
#define gte_rt_alt(r1, r0) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %1 );" \
    "lwc2 $1, 4( %1 );" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 0, 3, 0;" \
    "swc2 $25, 0( %0 );" \
    "swc2 $26, 4( %0 );" \
    "swc2 $27, 8( %0 )" \
    : \
    : "r"( r1 ), "r"( r0 ) \
    : "memory" )

/* nop;nop;mvmva 1, 0, 3, 3, 0  (9 definitions in 6 files) */
#define gte_rtir() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")

/* nop;nop;rtps  (681 definitions in 299 files) */
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

/* nop;nop;rtpt  (249 definitions in 163 files) */
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")

/* nop;nop;mvmva 1, 0, 0, 3, 0  (0 definitions in 0 files) */
#define gte_rtv0() \
    __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" )

/* nop;nop;mvmva 1, 0, 0, 0, 0  (11 definitions in 10 files) */
#define gte_rtv0tr() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")

/* swc2 $29, 0(%0)  (136 definitions in 136 files; not a PsyQ name) */
#define gte_stORGB(p) __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

/* mfc2 $12, $9;mfc2 $13, $10;mfc2 $14, $11;sh $12, 0( %0 );sh $13, 6( %0 );sh $14, 12( %0 )  (11 definitions in 6 files) */
#define gte_stclmv(r0) \
    __asm__ volatile ( \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0( %0 );" \
    "sh $13, 6( %0 );" \
    "sh $14, 12( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14", "memory" )

/* cfc2 $12, $31;nop;sw $12, 0( %0 )  (697 definitions in 309 files) */
#define gte_stflg(r0) \
    __asm__ volatile ( \
    "cfc2 $12, $31;" \
    "nop;" \
    "sw $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )

/* swc2 $25, 0( %0 );swc2 $26, 4( %0 );swc2 $27, 8( %0 )  (291 definitions in 283 files) */
#define gte_stlvnl(r0) \
    __asm__ volatile ( \
    "swc2 $25, 0( %0 );" \
    "swc2 $26, 4( %0 );" \
    "swc2 $27, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $24, 0( %0 )  (186 definitions in 142 files) */
#define gte_stopz(r0) \
    __asm__ volatile ( \
    "swc2 $24, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $7, 0( %0 )  (51 definitions in 19 files) */
#define gte_stotz(r0) \
    __asm__ volatile ( \
    "swc2 $7, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $22, 0( %0 )  (15 definitions in 2 files) */
#define gte_strgb(r0) \
    __asm__ volatile ( \
    "swc2 $22, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $20, 0( %0 );swc2 $21, 0( %1 );swc2 $22, 0( %2 )  (4 definitions in 2 files) */
#define gte_strgb3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $20, 0( %0 );" \
    "swc2 $21, 0( %1 );" \
    "swc2 $22, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $20, 4( %0 );swc2 $21, 12( %0 );swc2 $22, 20( %0 )  (6 definitions in 2 files) */
#define gte_strgb3_g3(r0) \
    __asm__ volatile ( \
    "swc2 $20, 4( %0 );" \
    "swc2 $21, 12( %0 );" \
    "swc2 $22, 20( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* mfc2 $12, $9\nmfc2 $13, $10\nmfc2 $14, $11\nsh $12, 0(%0)\nsh $13, 2(%0)\nsh $14, 4(%0)\n  (33 definitions in 21 files) */
#define gte_stsv(r0) \
    __asm__ __volatile__( \
    "mfc2 $12, $9\n" \
    "mfc2 $13, $10\n" \
    "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" \
    "sh $13, 2(%0)\n" \
    "sh $14, 4(%0)\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* swc2 $14, 0( %0 )  (679 definitions in 299 files) */
#define gte_stsxy(r0) \
    __asm__ volatile ( \
    "swc2 $14, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 )  (6 definitions in 5 files) */
#define gte_stsxy0(r0) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 0( %1 )  (1 definitions in 1 files) */
#define gte_stsxy01(r0, r1) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 )" \
    : \
    : "r"( r0 ), "r"( r1 ) \
    : "memory" )

/* swc2 $13, 0( %0 )  (6 definitions in 5 files) */
#define gte_stsxy1(r0) \
    __asm__ volatile ( \
    "swc2 $13, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 0( %1 );swc2 $14, 0( %2 )  (219 definitions in 159 files) */
#define gte_stsxy3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 );" \
    "swc2 $14, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $12, 8( %0 );swc2 $13, 12( %0 );swc2 $14, 16( %0 )  (250 definitions in 133 files) */
#define gte_stsxy3_f3(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 12( %0 );" \
    "swc2 $14, 16( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12,  8( %0 );swc2 $13, 16( %0 );swc2 $14, 24( %0 )  (155 definitions in 124 files) */
#define gte_stsxy3_ft3(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 16( %0 );" \
    "swc2 $14, 24( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 8( %0 );swc2 $13, 20( %0 );swc2 $14, 32( %0 )  (3 definitions in 2 files) */
#define gte_stsxy3_gt4(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 20( %0 );" \
    "swc2 $14, 32( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 4( %0 );swc2 $14, 8( %0 )  (163 definitions in 141 files) */
#define gte_stsxy3c(r0) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 4( %0 );" \
    "swc2 $14, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $19, 0( %0 )  (15 definitions in 12 files) */
#define gte_stsz(r0) \
    __asm__ volatile ( \
    "swc2 $19, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $17, 0( %0 );swc2 $18, 0( %1 );swc2 $19, 0( %2 )  (166 definitions in 142 files) */
#define gte_stsz3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $17, 0( %0 );" \
    "swc2 $18, 0( %1 );" \
    "swc2 $19, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $16, 0(%0);swc2 $17, 0(%1);swc2 $18, 0(%2);swc2 $19, 0(%3)  (156 definitions in 140 files) */
#define gte_stsz4(r0, r1, r2, r3) \
    __asm__ volatile ( \
    "swc2 $16, 0( %0 );" \
    "swc2 $17, 0( %1 );" \
    "swc2 $18, 0( %2 );" \
    "swc2 $19, 0( %3 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

/* mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0( %0 )  (209 definitions in 146 files) */
#define gte_stszotz(r0) \
    __asm__ volatile ( \
    "mfc2 $12, $19;" \
    "nop;" \
    "sra $12, $12, 2;" \
    "sw $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )

#endif /* GTE_INLINE_H */
