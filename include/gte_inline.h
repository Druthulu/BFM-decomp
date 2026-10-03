/* include/gte_inline.h — the GTE coprocessor macros under Sony's names, ONE definition per signature (Phase 36 T5).
 *
 * Every macro here is the majority spelling the tree already carried in its per-TU definitions (byte-proven in the fleet),
 * named by PsyQ's inline_c.h convention; the signature of each (the bytes the build's maspsx → as tail makes of the template,
 * its operand counts, its clobbers) was computed by tools/gte_consolidate.py, which also deleted the per-TU duplicates.
 * A definition that differs from the one here only by its clobbers (a scheduling steer) is a LEVER VARIANT, <name>_m or
 * <name>_v<hash>: defined here once, right after its canonical, under a `// !FAKE:` line naming the pass that made the steer
 * and this instrument (3.39 T7.1); its uses are marked levers, not a second spelling. A signature only inline statements carried
 * has its own macro (outputs, then inputs, as parameters); a name a shared header uses with a canonical's expansion is an ALIAS.
 * Generated: do not edit by hand — regenerate with `tools/gte_consolidate.py --header`.
 */
#ifndef GTE_INLINE_H
#define GTE_INLINE_H

/* lw $12, 0( %0 );lw $13, 4( %0 );ctc2 $12, $0;ctc2 $13, $1;lw $12, 8( %0 );lw $13, 12( %0 ) …  (0 definitions in 0 files, 15 inline statements) */
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
// !FAKE: gte variant gte_SetRotMatrix_m — clobbers +memory vs `gte_SetRotMatrix` (a scheduling steer); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_SetRotMatrix_m(r0) \
    __asm__ __volatile__( \
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
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* lw $12, 0( %0 );lw $13, 4( %0 );ctc2 $12, $0;ctc2 $13, $1;lw $12, 8( %0 );lw $13, 12( %0 ) …  (0 definitions in 0 files, 7 inline statements; not a PsyQ name) */
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
// !FAKE: gte variant gte_SetRotTransMatrix_m — clobbers +memory vs `gte_SetRotTransMatrix` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_SetRotTransMatrix_m(r0) \
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
    "ctc2 $14, $7" :  : "r"( r0 ) : "$12", "$13", "$14", "memory" )
// !FAKE: gte variant gte_SetRotTransMatrix_v1da9 — clobbers +$2 vs `gte_SetRotTransMatrix` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_SetRotTransMatrix_v1da9(r0) \
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
    "ctc2 $14, $7" :  : "r"( r0 ) : "$12", "$13", "$14", "$2" )

/* lw $12, 20( %0 );lw $13, 24( %0 );ctc2 $12, $5;lw $14, 28( %0 );ctc2 $13, $6;ctc2 $14, $7  (0 definitions in 0 files, 12 inline statements) */
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
// !FAKE: gte variant gte_SetTransMatrix_m — clobbers +memory vs `gte_SetTransMatrix` (a scheduling steer); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_SetTransMatrix_m(r0) \
    __asm__ __volatile__( \
    "lw $12, 20(%0)\n" \
    "lw $13, 24(%0)\n" \
    "ctc2 $12, $5\n" \
    "lw $14, 28(%0)\n" \
    "ctc2 $13, $6\n" \
    "ctc2 $14, $7\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* nop;nop;avsz3  (0 definitions in 0 files) */
#define gte_avsz3() __asm__ volatile ("nop;nop;avsz3")

/* nop;nop;avsz4  (0 definitions in 0 files) */
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

/* cfc2 %0, $31; nop; sw %0, 0(%1)  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_cfc2_sw_4531( r0, r1 ) \
    __asm__ volatile ( \
    "cfc2 %0, $31; nop; sw %0, 0(%1)" \
    : "=&r"( r0 ) \
    : "r"( r1 ) \
    : "memory" )

/* nop\n\tnop\n\tdpcl  (0 definitions in 0 files) */
#define gte_dpcl() __asm__ __volatile__("nop\n\tnop\n\tdpcl")

/* mtc2 $0, $8  (0 definitions in 0 files; not a PsyQ name) */
#define gte_ldIR0z() __asm__ __volatile__("mtc2 $0, $8")

/* lwc2 $28, 0(%0)  (0 definitions in 0 files; not a PsyQ name) */
#define gte_ldIRGB(p) __asm__ __volatile__("lwc2 $28, 0(%0)" :: "r"(p) : "memory")

/* lhu $12, 0( %0 );lhu $13, 6( %0 );lhu $14, 12( %0 );mtc2 $12, $9;mtc2 $13, $10;mtc2 $14, $ …  (0 definitions in 0 files, 3 inline statements) */
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
// !FAKE: gte variant gte_ldclmv_m — clobbers +memory vs `gte_ldclmv` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_ldclmv_m(r0) \
    __asm__ volatile ( \
    "lhu $12, 0( %0 );" \
    "lhu $13, 6( %0 );" \
    "lhu $14, 12( %0 );" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11" :  : "r"( r0 ) : "$12", "$13", "$14", "memory" )

/* lhu $13, 4( %0 );lhu $12, 0( %0 );sll $13, $13, 16;or $12, $12, $13;mtc2 $12, $0;lwc2 $1,  …  (0 definitions in 0 files) */
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

/* lwc2 $9, 0(%0)\n\tlwc2 $10, 4(%0)\n\tlwc2 $11, 8(%0)  (0 definitions in 0 files, 1 inline statements) */
#define gte_ldlvl( r0 ) \
    __asm__ volatile ( \
    "lwc2 $9, 0(%0)\n\tlwc2 $10, 4(%0)\n\tlwc2 $11, 8(%0)" \
    : \
    : "r"( r0 ) )

/* lb $13, 1( %0 );lb $12, 0( %0 );sll $13, $13, 16;sll $12, $12, 16;srl $12, $12, 16;or $12, …  (0 definitions in 0 files; not a PsyQ name) */
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

/* lwc2 $6, 0( %0 )  (0 definitions in 0 files) */
#define gte_ldrgb(r0) \
    __asm__ volatile ( \
    "lwc2 $6, 0( %0 )" \
    : \
    : "r"( r0 ) )

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 )  (0 definitions in 0 files, 3 inline statements) */
#define gte_ldv0(r0) \
    __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" \
    "lwc2 $1, 4( %0 )" \
    : \
    : "r"( r0 ) )
// !FAKE: gte variant gte_ldv0_m — clobbers +memory vs `gte_ldv0` (a scheduling steer); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_ldv0_m(p) \
    __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(p) : "memory")

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 0( %1 );lwc2 $3, 4( %1 );lwc2 $4, 0( %2 );lwc2  …  (0 definitions in 0 files) */
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

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 0( %1 );lwc2 $3, 4( %1 );lwc2 $4, 0( %1 );lwc2  …  (0 definitions in 0 files; not a PsyQ name) */
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

/* lwc2 $0, 0( %0 );lwc2 $1, 4( %0 );lwc2 $2, 8( %0 );lwc2 $3, 12( %0 );lwc2 $4, 16( %0 );lwc …  (0 definitions in 0 files) */
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

/* lwc2 $9, 0($sp)\nlwc2 $10, 4($sp)\nlwc2 $11, 8($sp)\nnop\nnop\nsqr 0\n  (0 definitions in 0 files, 11 inline statements; not a PsyQ name) */
#define gte_lwc2x3_sqr_6a00() \
    __asm__ __volatile__ ( \
    "lwc2 $9, 0($sp)\n" \
    "lwc2 $10, 4($sp)\n" \
    "lwc2 $11, 8($sp)\n" \
    "nop\n" \
    "nop\n" \
    "sqr 0\n" \
    : \
    : \
    : "$10", "$11", "$9", "memory" )

/* lwc2 $9, 0(%0)\nlwc2 $10, 4(%0)\nlwc2 $11, 8(%0)\nnop\nnop\nsqr 1\n  (0 definitions in 0 files, 3 inline statements; not a PsyQ name) */
#define gte_lwc2x3_sqr_b502( r0 ) \
    __asm__ __volatile__ ( \
    "lwc2 $9, 0(%0)\n" \
    "lwc2 $10, 4(%0)\n" \
    "lwc2 $11, 8(%0)\n" \
    "nop\n" \
    "nop\n" \
    "sqr 1\n" \
    : \
    : "r"( r0 ) \
    : "$10", "$11", "$9", "memory" )

/* lwc2 $9, 0(%0)\nlwc2 $10, 4(%0)\nlwc2 $11, 8(%0)\nnop\nnop\nsqr 0\n  (0 definitions in 0 files, 141 inline statements; not a PsyQ name) */
#define gte_lwc2x3_sqr_e416( r0 ) \
    __asm__ __volatile__ ( \
    "lwc2 $9, 0(%0)\n" \
    "lwc2 $10, 4(%0)\n" \
    "lwc2 $11, 8(%0)\n" \
    "nop\n" \
    "nop\n" \
    "sqr 0\n" \
    : \
    : "r"( r0 ) \
    : "$10", "$11", "$9", "memory" )

/* lwc2 $9, 0( %0 );lwc2 $10, 4( %0 );lwc2 $11, 8( %0 );nop;nop;sqr 0;swc2 $25, 0( %0 );swc2  …  (0 definitions in 0 files, 2 inline statements; not a PsyQ name) */
#define gte_lwc2x3_sqr_swc2x3_c9fc( r0 ) \
    __asm__ volatile ( \
    "lwc2 $9, 0( %0 );" \
    "lwc2 $10, 4( %0 );" \
    "lwc2 $11, 8( %0 );" \
    "nop;" \
    "nop;" \
    "sqr 0;" \
    "swc2 $25, 0( %0 );" \
    "swc2 $26, 4( %0 );" \
    "swc2 $27, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "$10", "$11", "$9", "memory" )

/* lw $12, 0(%0);lw $13, 4(%0);ctc2 $12, $0;ctc2 $13, $1;lw $12, 8(%0);lw $13, 12(%0);lw $14, …  (0 definitions in 0 files, 17 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_2c4d( r0, r1 ) \
    __asm__ volatile ( \
    "lw $12, 0(%0);" \
    "lw $13, 4(%0);" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8(%0);" \
    "lw $13, 12(%0);" \
    "lw $14, 16(%0);" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4;" \
    "addiu $2, $sp, 0x10;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0(%0);" \
    "sh $13, 6(%0);" \
    "sh $14, 12(%0);" \
    "addiu $2, $sp, 0x12;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, %0, 0x2;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2);" \
    "addiu $2, $sp, 0x14;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu %0, %0, 4;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0(%0);" \
    "sh $13, 6(%0);" \
    "sh $14, 12(%0)" \
    : "=r"( r0 ) \
    : "0"( r1 ) \
    : "$12", "$13", "$14", "$2" )

/* lw $12, 0(%0);lw $13, 4(%0);ctc2 $12, $0;ctc2 $13, $1;lw $12, 8(%0);lw $13, 12(%0);lw $14, …  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_3eb0( r0, r1 ) \
    __asm__ __volatile__ ( \
    "lw $12, 0(%0);" \
    "lw $13, 4(%0);" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8(%0);" \
    "lw $13, 12(%0);" \
    "lw $14, 16(%0);" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4;" \
    "lhu $12, 0(%1);" \
    "lhu $13, 6(%1);" \
    "lhu $14, 12(%1);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0(%0);" \
    "sh $13, 6(%0);" \
    "sh $14, 12(%0);" \
    "addiu $2, $sp, 50;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, $sp, 18;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2);" \
    "addiu $2, $sp, 52;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, $sp, 20;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2)" \
    : \
    : "r"( r0 ), "r"( r1 ) \
    : "$12", "$13", "$14" )

/* lw %0, 0(%3);lw %1, 4(%3);ctc2 %0, $0;ctc2 %1, $1;lw %0, 8(%3);lw %1, 12(%3);lw %2, 16(%3) …  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_42e3( r0, r1, r2, r3 ) \
    __asm__ volatile ( \
    "lw %0, 0(%3);" \
    "lw %1, 4(%3);" \
    "ctc2 %0, $0;" \
    "ctc2 %1, $1;" \
    "lw %0, 8(%3);" \
    "lw %1, 12(%3);" \
    "lw %2, 16(%3);" \
    "ctc2 %0, $2;" \
    "ctc2 %1, $3;" \
    "ctc2 %2, $4;" \
    "lw %0, 20(%3);" \
    "lw %1, 24(%3);" \
    "ctc2 %0, $5;" \
    "lw %2, 28(%3);" \
    "ctc2 %1, $6;" \
    "ctc2 %2, $7" \
    : "=&r"( r0 ), "=&r"( r1 ), "=&r"( r2 ) \
    : "r"( r3 ) )

/* lw $12, 0(%0);lw $13, 4(%0);ctc2 $12, $0;ctc2 $13, $1;lw $12, 8(%0);lw $13, 12(%0);lw $14, …  (0 definitions in 0 files, 3 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_8b56( r0 ) \
    __asm__ __volatile__ ( \
    "lw $12, 0(%0);" \
    "lw $13, 4(%0);" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8(%0);" \
    "lw $13, 12(%0);" \
    "lw $14, 16(%0);" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4;" \
    "addiu $2, $sp, 16;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0(%0);" \
    "sh $13, 6(%0);" \
    "sh $14, 12(%0);" \
    "addiu $2, $sp, 18;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, %0, 2;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2);" \
    "addiu $2, $sp, 20;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, %0, 4;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2)" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14", "$2" )

/* lw $12, 0(%0);lw $13, 4(%0);ctc2 $12, $0;ctc2 $13, $1;lw $12, 8(%0);lw $13, 12(%0);lw $14, …  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_b751( r0 ) \
    __asm__ volatile ( \
    "lw $12, 0(%0);" \
    "lw $13, 4(%0);" \
    "ctc2 $12, $0;" \
    "ctc2 $13, $1;" \
    "lw $12, 8(%0);" \
    "lw $13, 12(%0);" \
    "lw $14, 16(%0);" \
    "ctc2 $12, $2;" \
    "ctc2 $13, $3;" \
    "ctc2 $14, $4;" \
    "addiu $2, $sp, 0x30;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0(%0);" \
    "sh $13, 6(%0);" \
    "sh $14, 12(%0);" \
    "addiu $2, $sp, 0x32;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, $sp, 0x12;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2);" \
    "addiu $2, $sp, 0x34;" \
    "lhu $12, 0($2);" \
    "lhu $13, 6($2);" \
    "lhu $14, 12($2);" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0;" \
    "addiu $2, $sp, 0x14;" \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0($2);" \
    "sh $13, 6($2);" \
    "sh $14, 12($2);" \
    : \
    : "r"( r0 ) \
    : "$12", "$13", "$14", "$2", "memory" )

/* .set\tnoreorder\nlw     $12, 0($4)\nlw     $13, 4($4)\nctc2   $12, $0\nctc2   $13, $1\nlw  …  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_lwx2_ctc2x2_lwx3_ctc2x3_fc24() \
    __asm__ __volatile__ ( \
    ".set\tnoreorder\n" \
    "lw     $12, 0($4)\n" \
    "lw     $13, 4($4)\n" \
    "ctc2   $12, $0\n" \
    "ctc2   $13, $1\n" \
    "lw     $12, 8($4)\n" \
    "lw     $13, 12($4)\n" \
    "lw     $14, 16($4)\n" \
    "ctc2   $12, $2\n" \
    "ctc2   $13, $3\n" \
    "ctc2   $14, $4\n" \
    "lwc2   $0, 0($5)\n" \
    "lwc2   $1, 4($5)\n" \
    "nop\n" \
    "nop\n" \
    "mvmva  1, 0, 0, 3, 0\n" \
    "swc2   $25, 0($6)\n" \
    "swc2   $26, 4($6)\n" \
    "swc2   $27, 8($6)\n" \
    ".set\treorder\n" \
    : \
    : \
    : "$12", "$13", "$14", "memory" )

/* move $12, %0\n\tswc2 $29, 0($12)  (0 definitions in 0 files, 134 inline statements; not a PsyQ name) */
#define gte_move_swc2_e610( r0 ) \
    __asm__ __volatile__ ( \
    "move $12, %0\n\tswc2 $29, 0($12)" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )

/* mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)  (0 definitions in 0 files, 134 inline statements; not a PsyQ name) */
#define gte_mtc2_lwc2x2_1fc7( r0, r1 ) \
    __asm__ __volatile__ ( \
    "mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)" \
    : \
    : "r"( r0 ), "r"( r1 ) \
    : "memory" )

/* lhu $12, 0(%0)\nlhu $13, 6(%0)\nlhu $14, 12(%0)\nmtc2 $12, $9\nmtc2 $13, $10\nmtc2 $14, $1 …  (0 definitions in 0 files; not a PsyQ name) */
#define gte_mulcol(r0) \
    __asm__ __volatile__ ( \
    "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
    "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
    "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
    "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* lhu $13, 4(%0)\nlhu $12, 0(%0)\nsll $13, $13, 16\nor $12, $12, $13\nmtc2 $12, $0\nlwc2 $1, …  (0 definitions in 0 files; not a PsyQ name) */
#define gte_multrans(r0) \
    __asm__ __volatile__ ( \
    "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n" \
    "sll $13, $13, 16\n" "or $12, $12, $13\n" \
    "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n" \
    "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n" \
    "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n" \
    : : "r"(r0) : "$12", "$13", "memory")

/* nop;nop;nccs  (0 definitions in 0 files) */
#define gte_nccs() __asm__ volatile ("nop;nop;nccs")

/* nop;nop;ncct  (0 definitions in 0 files) */
#define gte_ncct() __asm__ volatile ("nop;nop;ncct")

/* nop;nop;nclip  (0 definitions in 0 files) */
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")

/* lwc2 $0, 0( %1 );lwc2 $1, 4( %1 );nop;nop;mvmva 1, 0, 0, 3, 0;swc2 $25, 0( %0 );swc2 $26,  …  (0 definitions in 0 files; not a PsyQ name) */
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

/* lhu $12, 0( %0 );lhu $13, 6( %0 );lhu $14, 12( %0 );mtc2 $12, $9;mtc2 $13, $10;mtc2 $14, $ …  (1 definitions in 1 files; not a PsyQ name) */
#define gte_rt_alt2(p) \
    __asm__ volatile ( \
    "lhu $12, 0( %0 );" \
    "lhu $13, 6( %0 );" \
    "lhu $14, 12( %0 );" \
    "mtc2 $12, $9;" \
    "mtc2 $13, $10;" \
    "mtc2 $14, $11;" \
    "nop;" \
    "nop;" \
    "mvmva 1, 0, 3, 3, 0" \
    : \
    : "r"( p ) \
    : "$12", "$13", "$14", "memory"); \
    __asm__ volatile ( \
    "mfc2 $12, $9;" \
    "mfc2 $13, $10;" \
    "mfc2 $14, $11;" \
    "sh $12, 0( %0 );" \
    "sh $13, 6( %0 );" \
    "sh $14, 12( %0 )" \
    : \
    : "r"( p ) \
    : "$12", "$13", "$14", "memory")

/* nop;nop;mvmva 1, 0, 3, 3, 0  (0 definitions in 0 files) */
#define gte_rtir() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")
// !FAKE: gte variant gte_rtir_m — clobbers +memory vs `gte_rtir` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_rtir_m() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0" :  :  : "memory" )

/* nop;nop;rtps  (0 definitions in 0 files, 1 inline statements) */
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
// !FAKE: gte variant gte_rtps_m — clobbers +memory vs `gte_rtps` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_rtps_m() __asm__ volatile ("nop;nop;rtps" :  :  : "memory" )

/* nop;nop;rtpt  (0 definitions in 0 files) */
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")

/* nop\nnop\nmvmva 1, 0, 0, 3, 0\n  (0 definitions in 0 files, 2 inline statements) */
#define gte_rtv0() \
    __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" )
// !FAKE: gte variant gte_rtv0_m — clobbers +memory vs `gte_rtv0` (a scheduling steer); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_rtv0_m() \
    __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" \
    : : : "memory")

/* nop;nop;mvmva 1, 0, 0, 0, 0  (0 definitions in 0 files) */
#define gte_rtv0tr() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")
// !FAKE: gte variant gte_rtv0tr_m — clobbers +memory vs `gte_rtv0tr` (a scheduling steer); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_rtv0tr_m() \
    __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")
// !FAKE: gte variant alias gte_mvmva0 = `gte_rtv0tr_m` — clobbers memory vs `gte_rtv0tr` (a scheduling steer, under the name a shared header uses); pass: P36 T5 GTE consolidation (per-TU definitions; moved to this header 3.39 T7.1); instrument: tools/gte_consolidate.py --header
#define gte_mvmva0() \
    __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")

/* nop\n\tnop\n\tsqr 0  (0 definitions in 0 files, 1 inline statements; not a PsyQ name) */
#define gte_sqr_a07d() \
    __asm__ volatile ( \
    "nop\n\tnop\n\tsqr 0" )

/* swc2 $29, 0(%0)  (0 definitions in 0 files; not a PsyQ name) */
#define gte_stORGB(p) __asm__ __volatile__("swc2 $29, 0(%0)" :: "r"(p) : "memory")

/* mfc2 $12, $9;mfc2 $13, $10;mfc2 $14, $11;sh $12, 0( %0 );sh $13, 6( %0 );sh $14, 12( %0 )  (0 definitions in 0 files) */
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

/* swc2 $8, 0( %0 )  (0 definitions in 0 files, 2 inline statements) */
#define gte_stdp( r0 ) \
    __asm__ volatile ( \
    "swc2 $8, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* cfc2 $12, $31;nop;sw $12, 0( %0 )  (0 definitions in 0 files, 1 inline statements) */
#define gte_stflg(r0) \
    __asm__ volatile ( \
    "cfc2 $12, $31;" \
    "nop;" \
    "sw $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )
// !FAKE: gte variant gte_stflg_v845d — clobbers -memory vs `gte_stflg` (a scheduling steer); pass: 3.39 T7.1 inline GTE statements (exact clobbers); instrument: tools/gte_consolidate.py --header
#define gte_stflg_v845d(r0) \
    __asm__ volatile ( \
    "cfc2 $12, $31;" \
    "nop;" \
    "sw $12, 0( %0 )" :  : "r"( r0 ) : "$12" )

/* swc2 $25, 0( %0 );swc2 $26, 4( %0 );swc2 $27, 8( %0 )  (0 definitions in 0 files) */
#define gte_stlvnl(r0) \
    __asm__ volatile ( \
    "swc2 $25, 0( %0 );" \
    "swc2 $26, 4( %0 );" \
    "swc2 $27, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $24, 0( %0 )  (0 definitions in 0 files) */
#define gte_stopz(r0) \
    __asm__ volatile ( \
    "swc2 $24, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $7, 0( %0 )  (0 definitions in 0 files) */
#define gte_stotz(r0) \
    __asm__ volatile ( \
    "swc2 $7, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $22, 0( %0 )  (0 definitions in 0 files) */
#define gte_strgb(r0) \
    __asm__ volatile ( \
    "swc2 $22, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $20, 0( %0 );swc2 $21, 0( %1 );swc2 $22, 0( %2 )  (0 definitions in 0 files) */
#define gte_strgb3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $20, 0( %0 );" \
    "swc2 $21, 0( %1 );" \
    "swc2 $22, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $20, 4( %0 );swc2 $21, 12( %0 );swc2 $22, 20( %0 )  (0 definitions in 0 files) */
#define gte_strgb3_g3(r0) \
    __asm__ volatile ( \
    "swc2 $20, 4( %0 );" \
    "swc2 $21, 12( %0 );" \
    "swc2 $22, 20( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* mfc2 $12, $9\nmfc2 $13, $10\nmfc2 $14, $11\nsh $12, 0(%0)\nsh $13, 2(%0)\nsh $14, 4(%0)\n  (0 definitions in 0 files) */
#define gte_stsv(r0) \
    __asm__ __volatile__( \
    "mfc2 $12, $9\n" \
    "mfc2 $13, $10\n" \
    "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" \
    "sh $13, 2(%0)\n" \
    "sh $14, 4(%0)\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

/* swc2 $14, 0( %0 )  (0 definitions in 0 files) */
#define gte_stsxy(r0) \
    __asm__ volatile ( \
    "swc2 $14, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 )  (0 definitions in 0 files) */
#define gte_stsxy0(r0) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 0( %1 )  (0 definitions in 0 files) */
#define gte_stsxy01(r0, r1) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 )" \
    : \
    : "r"( r0 ), "r"( r1 ) \
    : "memory" )

/* swc2 $13, 0( %0 )  (0 definitions in 0 files) */
#define gte_stsxy1(r0) \
    __asm__ volatile ( \
    "swc2 $13, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 0( %1 );swc2 $14, 0( %2 )  (0 definitions in 0 files) */
#define gte_stsxy3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 0( %1 );" \
    "swc2 $14, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $12, 8( %0 );swc2 $13, 12( %0 );swc2 $14, 16( %0 )  (80 definitions in 80 files) */
#define gte_stsxy3_f3(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 12( %0 );" \
    "swc2 $14, 16( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )
/* alias: `gte_stsxy3_f4` is `gte_stsxy3_f3` under the name a shared header uses (80 definitions in 80 files) */
#define gte_stsxy3_f4(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 12( %0 );" \
    "swc2 $14, 16( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 8( %0 );swc2 $13, 16( %0 );swc2 $14, 24( %0 )  (0 definitions in 0 files) */
#define gte_stsxy3_ft3(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 16( %0 );" \
    "swc2 $14, 24( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 8( %0 );swc2 $13, 20( %0 );swc2 $14, 32( %0 )  (0 definitions in 0 files) */
#define gte_stsxy3_gt4(r0) \
    __asm__ volatile ( \
    "swc2 $12, 8( %0 );" \
    "swc2 $13, 20( %0 );" \
    "swc2 $14, 32( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $12, 0( %0 );swc2 $13, 4( %0 );swc2 $14, 8( %0 )  (0 definitions in 0 files) */
#define gte_stsxy3c(r0) \
    __asm__ volatile ( \
    "swc2 $12, 0( %0 );" \
    "swc2 $13, 4( %0 );" \
    "swc2 $14, 8( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $19, 0( %0 )  (0 definitions in 0 files, 1 inline statements) */
#define gte_stsz(r0) \
    __asm__ volatile ( \
    "swc2 $19, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "memory" )

/* swc2 $17, 0( %0 );swc2 $18, 0( %1 );swc2 $19, 0( %2 )  (0 definitions in 0 files) */
#define gte_stsz3(r0, r1, r2) \
    __asm__ volatile ( \
    "swc2 $17, 0( %0 );" \
    "swc2 $18, 0( %1 );" \
    "swc2 $19, 0( %2 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) \
    : "memory" )

/* swc2 $16, 0( %0 );swc2 $17, 0( %1 );swc2 $18, 0( %2 );swc2 $19, 0( %3 )  (0 definitions in 0 files) */
#define gte_stsz4(r0, r1, r2, r3) \
    __asm__ volatile ( \
    "swc2 $16, 0( %0 );" \
    "swc2 $17, 0( %1 );" \
    "swc2 $18, 0( %2 );" \
    "swc2 $19, 0( %3 )" \
    : \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
    : "memory" )

/* mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0( %0 )  (0 definitions in 0 files, 1 inline statements) */
#define gte_stszotz(r0) \
    __asm__ volatile ( \
    "mfc2 $12, $19;" \
    "nop;" \
    "sra $12, $12, 2;" \
    "sw $12, 0( %0 )" \
    : \
    : "r"( r0 ) \
    : "$12", "memory" )

/* swc2 $25, 0($sp)\nswc2 $26, 4($sp)\nswc2 $27, 8($sp)\n  (0 definitions in 0 files, 11 inline statements; not a PsyQ name) */
#define gte_swc2x3_66ca() \
    __asm__ __volatile__ ( \
    "swc2 $25, 0($sp)\n" \
    "swc2 $26, 4($sp)\n" \
    "swc2 $27, 8($sp)\n" \
    : \
    : \
    : "memory" )

#endif /* GTE_INLINE_H */
