/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 72, 585, 2226, 2534, 2640).
 * func_8012BDBC / D_801E32B0 appear nowhere in the TU (nor in include/), so
 * their externs below cannot collide.
 *
 * SPLICE FIX (cookbook §37/§124 ASM-LABEL ALIAS):
 * the TU already declares `extern void func_8018A224(void);` at L3183 and
 * takes its address at L3205 as `(s32)func_8018A224`.  That decl disagrees
 * with the real signature (s32 return, one pointer arg), so defining
 * func_8018A224 directly is "conflicting types".  Defining it under the
 * alias aF8018A224 with an asm label emits the identical `func_8018A224`
 * symbol while leaving the TU's own declaration untouched — zero blast
 * radius, zero emitted-instruction change.
 */
extern s32 *D_80126B78;                                          /* TU L72 */
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);        /* TU L585 */
extern void func_80172710(void);                                 /* TU L2226 */
extern s32 func_80178BF8();                                      /* TU L2534 */
extern void RotTransSV(void *a0, void *a1, void *a2);            /* TU L2640 */
extern s32 func_8012BDBC(s32 a0, s32 a1);                        /* not in TU */
extern u8 D_801E32B0[];                                          /* not in TU */

#define gte_SetRotMatrix(r0) __asm__ volatile (         \
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
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

s32 aF8018A224() __asm__("func_8018A224");

s32 aF8018A224(param_1)
    void *param_1;
{
    s32 *m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    m = (s32 *)((u8 *)D_80126B78 + 0x34);
    obj = *(s32 *)((s32)param_1 + 0x64);

    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(D_801E32B0, sv0, &flag);
    RotTransSV(D_801E32B0 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(obj + 0x20), *(s32 *)(obj + 0x58), (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}
