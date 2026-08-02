/* §37 data asm-label alias: the TU already declares
 *   extern struct B16_80185794 D_800A5E88;
 * at file scope (that tag is defined next to func_80185794).  Re-declaring the
 * symbol with this function's own 16-byte record tag is a `conflicting types`
 * error, and the tag cannot be re-defined either.  Aliasing a private C
 * identifier onto the same linker symbol sidesteps the collision at zero blast
 * radius and emits the identical %hi/%lo(D_800A5E88) pair. */

struct B16_8018584C { s32 w[4]; };

extern struct B16_8018584C aD800A5E88 __asm__("D_800A5E88");
extern struct B16_8018584C D_801CCC80;
extern s32 D_800A5E90;
extern s32 func_8004787C(s32 a0);
extern void func_80028620(s32 a0, void *a1);

void func_8018584C(void *a0) {
    s32 t;

    aD800A5E88 = D_801CCC80;
    t = func_8004787C(*(s16 *)((s32)a0 + 0xFE));
    if (t < 0) t += 0x1FF;
    D_800A5E90 = (t >> 9) + 8;
    *(u16 *)((s32)a0 + 0xFE) = (*(u16 *)((s32)a0 + 0xFE) + 0x71) & 0xFFF;
    func_80028620(0, &aD800A5E88);
}
