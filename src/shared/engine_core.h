/* src/shared/engine_core.h — Phase 15 shared engine-core bodies (cross-overlay dedup, §14).
 * Each DEFINE_func_XXXX() expands to the WHOLE matched body once; instantiated in place at the
 * func_XXXX site in every overlay that shares it (address order preserved). Registry +
 * byte-honesty: config/dedup.us.yaml + tools/dedup_integrate.py. Tool-generated; do not hand-edit. */
#ifndef SHARED_ENGINE_CORE_H
#define SHARED_ENGINE_CORE_H
#include "common.h"
#include "engine_types.h"   /* shared engine struct/union types (§14c struct follow-up) */

/* ENGINE_SHB — the sign-extension barrier some shared bodies were matched with (§75b).
 * A body's preamble may carry file-scope `#define`s as well as `extern`s, but extraction lifts
 * only the externs, so a `#define` left behind in the source overlay makes the macro compile
 * ONLY where that overlay's define happens to be in scope ABOVE the splice point. func_80165CA0
 * was capped at ×3 by exactly that: its `#define SHB` sits between its two externs and its
 * instantiation, and the other 132 overlays define SHB only ~300 lines further down the file.
 * Owning it here (under a distinct name, so the overlays' own SHB — which exists in BOTH a
 * volatile and a non-volatile spelling — can never collide) makes the body self-contained.
 * Volatile form: that is what the 3 banked members compile with today. */
#ifndef ENGINE_SHB
#define ENGINE_SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#endif

#define DEFINE_func_80128EA8() \
    void func_80128EA8(s32 a0, s32 a1, s32 a2) { \
        *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */ \
        *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */ \
        *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */ \
        *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */ \
        *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */ \
    }

#define DEFINE_func_8012A568() \
    extern void func_8012A598(void *a0); \
    void func_8012A568(void (*a0)(void)) { \
        func_8012A598(a0); \
        a0(); \
    }

#define DEFINE_func_80132EC4() \
    void func_80132EC4(void *a0, s16 a1) { \
        while (*(s32 *)a0 != 0) { \
            *(s16 *)((s32)a0 + 4) = a1; \
            a0 = (void *)((s32)a0 + 8); \
        } \
    }

#define DEFINE_func_80138C30() \
    void func_80138C30(void *a0) { \
        if (*(s16 *)((s32)a0 + 4) == 4) { \
            *(s16 *)((s32)a0 + 4) = 2; \
        } else { \
            *(u32 *)((s32)a0 + 8) |= 0x800; \
        } \
    }

#define DEFINE_func_8012D3AC() \
    void func_8012D3AC(void) { \
    }

#define DEFINE_func_8012D5DC() \
    void func_8012D5DC(void) { \
    }

#define DEFINE_func_8012DFCC() \
    void func_8012DFCC(void) { \
    }

#define DEFINE_func_8012E284() \
    void func_8012E284(void) { \
    }

#define DEFINE_func_80131EE4() \
    void func_80131EE4(void) { \
    }

#define DEFINE_func_801320D0() \
    void func_801320D0(void) { \
    }

#define DEFINE_func_8013277C() \
    void func_8013277C(void) { \
    }

#define DEFINE_func_80136C3C() \
    void func_80136C3C(void) { \
    }

#define DEFINE_func_80136C44() \
    void func_80136C44(void) { \
    }

#define DEFINE_func_80136C4C() \
    void func_80136C4C(void) { \
    }

#define DEFINE_func_80136D00() \
    void func_80136D00(void) { \
    }

#define DEFINE_func_80136EC4() \
    void func_80136EC4(void) { \
    }

#define DEFINE_func_80139DEC() \
    void func_80139DEC(void) { \
    }

#define DEFINE_func_8013A378() \
    void func_8013A378(void) { \
    }

#define DEFINE_func_80141C04() \
    void func_80141C04(void) { \
    }

#define DEFINE_func_801427DC() \
    void func_801427DC(void) { \
    }

#define DEFINE_func_801427E4() \
    void func_801427E4(void) { \
    }

#define DEFINE_func_80142C7C() \
    void func_80142C7C(void) { \
    }

#define DEFINE_func_80143EA4() \
    void func_80143EA4(void) { \
    }

#define DEFINE_func_80143EAC() \
    void func_80143EAC(void) { \
    }

#define DEFINE_func_80143EB4() \
    void func_80143EB4(void) { \
    }

#define DEFINE_func_80144A90() \
    void func_80144A90(void) { \
    }

#define DEFINE_func_801458E0() \
    void func_801458E0(void) { \
    }

#define DEFINE_func_80146074() \
    void func_80146074(void) { \
    }

#define DEFINE_func_80146C98() \
    void func_80146C98(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x2) = a1; \
    }

#define DEFINE_func_80146E90() \
    void func_80146E90(s32 *a0, s32 a1) { \
        *(s32*)((s32)a0 + 0x1C) = a1; \
    }

#define DEFINE_func_8014704C() \
    void func_8014704C(s32 *a0) { \
        *(s8*)((s32)a0 + 0x4C) = 0; \
    }

#define DEFINE_func_80147084() \
    void func_80147084(s32 *a0) { \
        *(s8*)((s32)a0 + 0x221) = 0; \
    }

#define DEFINE_func_80147098() \
    void func_80147098(s32 *a0) { \
        *(s8*)((s32)a0 + 0x220) = 0; \
    }

#define DEFINE_func_801470AC() \
    void func_801470AC(s32 *a0) { \
        *(s8*)((s32)a0 + 0x222) = 0; \
    }

#define DEFINE_func_80148C18() \
    s32 func_80148C18(void) { \
        return 0; \
    }

#define DEFINE_func_80148C7C() \
    s32 func_80148C7C(void) { \
        return 0; \
    }

#define DEFINE_func_80148CE4() \
    s32 func_80148CE4(void) { \
        return 0; \
    }

#define DEFINE_func_80148CEC() \
    s32 func_80148CEC(void) { \
        return 0; \
    }

#define DEFINE_func_80148D3C() \
    s32 func_80148D3C(void) { \
        return 0; \
    }

#define DEFINE_func_80148F60() \
    s32 func_80148F60(void) { \
        return -1; \
    }

#define DEFINE_func_80148F98() \
    s32 func_80148F98(void) { \
        return -1; \
    }

#define DEFINE_func_80148FD0() \
    s32 func_80148FD0(void) { \
        return -1; \
    }

#define DEFINE_func_80148FD8() \
    s32 func_80148FD8(void) { \
        return -1; \
    }

#define DEFINE_func_80149004() \
    s32 func_80149004(void) { \
        return -1; \
    }

#define DEFINE_func_801490E0() \
    void func_801490E0(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x108) = a1; \
    }

#define DEFINE_func_801490E8() \
    void func_801490E8(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x10A) = a1; \
    }

#define DEFINE_func_801490F0() \
    void func_801490F0(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x10C) = a1; \
    }

#define DEFINE_func_80149FA8() \
    void func_80149FA8(void) { \
    }

#define DEFINE_func_8014B5B0() \
    void func_8014B5B0(s32 *a0) { \
        *(s8*)((s32)a0 + 0x1C4) = 0; \
    }

#define DEFINE_func_8014B5D0() \
    void func_8014B5D0(s32 *a0) { \
        *(s8*)((s32)a0 + 0x1C7) = 0; \
    }

#define DEFINE_func_8014BDE0() \
    void func_8014BDE0(void) { \
    }

#define DEFINE_func_80150B9C() \
    void func_80150B9C(void) { \
    }

#define DEFINE_func_80150F78() \
    void func_80150F78(void) { \
    }

#define DEFINE_func_801510B8() \
    void func_801510B8(void) { \
    }

#define DEFINE_func_801510C0() \
    void func_801510C0(void) { \
    }

#define DEFINE_func_80151130() \
    void func_80151130(void) { \
    }

#define DEFINE_func_8015115C() \
    void func_8015115C(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x16C) = a1; \
    }

#define DEFINE_func_80151878() \
    void func_80151878(void) { \
    }

#define DEFINE_func_80155F58() \
    void func_80155F58(void) { \
    }

#define DEFINE_func_80156A14() \
    void func_80156A14(s32 *a0) { \
        *(s8*)((s32)a0 + 0xDA) = 0; \
    }

#define DEFINE_func_801585A4() \
    void func_801585A4(s32 *a0) { \
        *(s16*)((s32)a0 + 0x244) = 0; \
    }

#define DEFINE_func_80158794() \
    void func_80158794(void) { \
    }

#define DEFINE_func_80159874() \
    s32 func_80159874(void) { \
        return 0; \
    }

#define DEFINE_func_80159A18() \
    void func_80159A18(void) { \
    }

#define DEFINE_func_8015C6A4() \
    void func_8015C6A4(void) { \
    }

#define DEFINE_func_8015CBCC() \
    void func_8015CBCC(void) { \
    }

#define DEFINE_func_8015CBD4() \
    void func_8015CBD4(void) { \
    }

#define DEFINE_func_8015CBDC() \
    void func_8015CBDC(void) { \
    }

#define DEFINE_func_8015CBE4() \
    void func_8015CBE4(void) { \
    }

#define DEFINE_func_8015CBEC() \
    void func_8015CBEC(void) { \
    }

#define DEFINE_func_8015CBF4() \
    void func_8015CBF4(void) { \
    }

#define DEFINE_func_8015CBFC() \
    void func_8015CBFC(void) { \
    }

#define DEFINE_func_8015CC04() \
    void func_8015CC04(void) { \
    }

#define DEFINE_func_8015EF9C() \
    void func_8015EF9C(void) { \
    }

#define DEFINE_func_8016032C() \
    void func_8016032C(void) { \
    }

#define DEFINE_func_801610FC() \
    void func_801610FC(void) { \
    }

#define DEFINE_func_80162CC4() \
    void func_80162CC4(void) { \
    }

#define DEFINE_func_80164410() \
    void func_80164410(void) { \
    }

#define DEFINE_func_80165A18() \
    void func_80165A18(void) { \
    }

#define DEFINE_func_80165B08() \
    void func_80165B08(void) { \
    }

#define DEFINE_func_80165B10() \
    void func_80165B10(void) { \
    }

#define DEFINE_func_80165B18() \
    void func_80165B18(void) { \
    }

#define DEFINE_func_80165B20() \
    void func_80165B20(void) { \
    }

#define DEFINE_func_80167AD8() \
    void func_80167AD8(void) { \
    }

#define DEFINE_func_8016F4F4() \
    void func_8016F4F4(void) { \
    }

#define DEFINE_func_80171A80() \
    void func_80171A80(s32 *a0, s32 a1) { \
        *(s32*)((s32)a0 + 0x200) = a1; \
    }

#define DEFINE_func_80171B44() \
    void func_80171B44(s32 *a0) { \
        *(s8*)((s32)a0 + 0x20C) = 0; \
    }

#define DEFINE_func_80172588() \
    void func_80172588(s32 *a0) { \
        *(s32*)((s32)a0 + 0x1F4) = 0; \
    }

#define DEFINE_func_8017288C() \
    void func_8017288C(void) { \
    }

#define DEFINE_func_801729A8() \
    void func_801729A8(void) { \
    }

#define DEFINE_func_80172B0C() \
    void func_80172B0C(void) { \
    }

#define DEFINE_func_80172C48() \
    void func_80172C48(void) { \
    }

#define DEFINE_func_80172D60() \
    void func_80172D60(void) { \
    }

#define DEFINE_func_80172E8C() \
    void func_80172E8C(void) { \
    }

#define DEFINE_func_8017316C() \
    void func_8017316C(void) { \
    }

#define DEFINE_func_80173294() \
    void func_80173294(void) { \
    }

#define DEFINE_func_801736A8() \
    void func_801736A8(void) { \
    }

#define DEFINE_func_801737B0() \
    void func_801737B0(void) { \
    }

#define DEFINE_func_801738D4() \
    void func_801738D4(void) { \
    }

#define DEFINE_func_80173A20() \
    void func_80173A20(void) { \
    }

#define DEFINE_func_80174274() \
    void func_80174274(void) { \
    }

#define DEFINE_func_80174354() \
    void func_80174354(void) { \
    }

#define DEFINE_func_80174430() \
    void func_80174430(void) { \
    }

#define DEFINE_func_80174524() \
    void func_80174524(void) { \
    }

#define DEFINE_func_8017481C() \
    void func_8017481C(void) { \
    }

#define DEFINE_func_801748E4() \
    void func_801748E4(void) { \
    }

#define DEFINE_func_80175798() \
    void func_80175798(void) { \
    }

#define DEFINE_func_8017BE9C() \
    void func_8017BE9C(void) { \
    }

#define DEFINE_func_8017BEA4() \
    void func_8017BEA4(void) { \
    }

#define DEFINE_func_8017BEAC() \
    void func_8017BEAC(void) { \
    }

#define DEFINE_func_8017BEB4() \
    void func_8017BEB4(void) { \
    }

#define DEFINE_func_8012AD44() \
    void func_8012AD44(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x2) = a1; \
        *(s16*)((s32)a0 + 0x34) = 0; \
    }

#define DEFINE_func_8013A8B0() \
    void func_8013A8B0(s32 *a0) { \
        *(s16*)((s32)a0 + 0x0) = 0; \
        *(s32*)((s32)a0 + 0x4) = 0; \
    }

#define DEFINE_func_80142DB8() \
    s32 func_80142DB8(s32 *a0) { \
        return *(u16*)((s32)a0 + 0x5C) & 0x1; \
    }

#define DEFINE_func_80147078() \
    void func_80147078(s32 *a0, s16 a1) { \
        *(s16*)((s32)a0 + 0x0) = a1; \
        *(s16*)((s32)a0 + 0x2) = 0; \
    }

#define DEFINE_func_801487F4() \
    u16 func_801487F4(s32 *a0) { \
        return *(u16*)((s32)a0 + 0xAA); \
    }

#define DEFINE_func_80148800() \
    u16 func_80148800(s32 *a0) { \
        return *(u16*)((s32)a0 + 0xAC); \
    }

#define DEFINE_func_8014880C() \
    u8 func_8014880C(s32 *a0) { \
        return *(u8*)((s32)a0 + 0xAE); \
    }

#define DEFINE_func_80148818() \
    u16 func_80148818(s32 *a0) { \
        return *(u16*)((s32)a0 + 0xAE) >> 8; \
    }

#define DEFINE_func_80148F68() \
    s32 func_80148F68(s32 a0) { \
        return (s16)a0; \
    }

#define DEFINE_func_80148F74() \
    s32 func_80148F74(s32 a0) { \
        return (a0 + 0x400) & 0xFFF; \
    }

#define DEFINE_func_80148F80() \
    s32 func_80148F80(s32 a0) { \
        return (a0 + 0x200) & 0xFFF; \
    }

#define DEFINE_func_80148F8C() \
    s32 func_80148F8C(s32 a0) { \
        return (a0 + 0x800) & 0xFFF; \
    }

#define DEFINE_func_80148FA0() \
    s32 func_80148FA0(s32 a0) { \
        return (a0 + 0x600) & 0xFFF; \
    }

#define DEFINE_func_80148FAC() \
    s32 func_80148FAC(s32 a0) { \
        return (a0 + 0x400) & 0xFFF; \
    }

#define DEFINE_func_80148FB8() \
    s32 func_80148FB8(s32 a0) { \
        return (a0 - 0x400) & 0xFFF; \
    }

#define DEFINE_func_80148FC4() \
    s32 func_80148FC4(s32 a0) { \
        return (a0 - 0x200) & 0xFFF; \
    }

#define DEFINE_func_80148FE0() \
    s32 func_80148FE0(s32 a0) { \
        return (a0 - 0x600) & 0xFFF; \
    }

#define DEFINE_func_80148FEC() \
    s32 func_80148FEC(s32 a0) { \
        return (a0 - 0x400) & 0xFFF; \
    }

#define DEFINE_func_80148FF8() \
    s32 func_80148FF8(s32 a0) { \
        return (a0 - 0x800) & 0xFFF; \
    }

#define DEFINE_func_80149204() \
    void func_80149204(s32 *a0) { \
        *(s32*)((s32)a0 + 0x1E4) = 0; \
        *(s32*)((s32)a0 + 0x1DC) = 0; \
    }

#define DEFINE_func_80149284() \
    s32 func_80149284(s32 *a0, s32 a1) { \
        return *(s32*)((s32)a0 + 0x1DC) & a1; \
    }

#define DEFINE_func_8014A674() \
    s32 func_8014A674(s32 *a0) { \
        return *(u8*)((s32)a0 + 0x1BC) < 1; \
    }

#define DEFINE_func_8014A69C() \
    s32 func_8014A69C(s32 *a0) { \
        return *(u8*)((s32)a0 + 0x1BD) == 0; \
    }

#define DEFINE_func_8014B154() \
    s32 func_8014B154(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x44) & 0x80; \
    }

#define DEFINE_func_8014B5B8() \
    u8 func_8014B5B8(s32 *a0) { \
        return *(u8*)((s32)a0 + 0x1C4); \
    }

#define DEFINE_func_8014B5C4() \
    void func_8014B5C4(s32 *a0, s32 a1, s32 a2) { \
        *(s8*)((s32)a0 + 0x1C7) = a1 | a2; \
    }

#define DEFINE_func_80162AC0() \
    void func_80162AC0(s32 *a0, s8 a1) { \
        *(s8*)((s32)a0 + 0x0) = a1; \
        *(s8*)((s32)a0 + 0x1) = 0; \
    }

#define DEFINE_func_80171A04() \
    void func_80171A04(s32 *a0) { \
        *(s8*)((s32)a0 + 0x217) = 1; \
    }

#define DEFINE_func_80171A10() \
    void func_80171A10(s32 *a0) { \
        *(s8*)((s32)a0 + 0x217) = 2; \
    }

#define DEFINE_func_80172304() \
    void func_80172304(s32 *a0) { \
        *(s16*)((s32)a0 + 0xAA) = 0x40; \
    }

#define DEFINE_func_80172658() \
    s32 func_80172658(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x1; \
    }

#define DEFINE_func_80172664() \
    s32 func_80172664(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x2; \
    }

#define DEFINE_func_80172670() \
    s32 func_80172670(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x4; \
    }

#define DEFINE_func_8017267C() \
    s32 func_8017267C(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x8; \
    }

#define DEFINE_func_80172688() \
    s32 func_80172688(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x10; \
    }

#define DEFINE_func_80172694() \
    s32 func_80172694(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x20; \
    }

#define DEFINE_func_801726A0() \
    s32 func_801726A0(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x40; \
    }

#define DEFINE_func_801726AC() \
    s32 func_801726AC(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x80; \
    }

#define DEFINE_func_801726B8() \
    s32 func_801726B8(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x100; \
    }

#define DEFINE_func_801726C4() \
    s32 func_801726C4(s32 *a0) { \
        return *(s32*)((s32)a0 + 0x1F4) & 0x200; \
    }

#define DEFINE_func_801285D4() \
    extern u8 D_800B9A11; \
    void func_801285D4(void) { \
        D_800B9A11 = 0; \
    }

#define DEFINE_func_80129248() \
    extern s16 D_8011DB2C; \
    void func_80129248(s16 a0) { \
        D_8011DB2C = a0; \
    }

#define DEFINE_func_8012943C() \
    extern s16 D_80114EE0; \
    void func_8012943C(void) { \
        D_80114EE0 = 0; \
    }

#define DEFINE_func_8012A100() \
    extern s8 D_801150D6; \
    void func_8012A100(s8 a0) { \
        D_801150D6 = a0; \
    }

#define DEFINE_func_8012A2F4() \
    extern s8 D_801152C0; \
    void func_8012A2F4(void) { \
        D_801152C0 = 0; \
    }

#define DEFINE_func_801379EC() \
    extern s16 D_8012752E; \
    void func_801379EC(void) { \
        D_8012752E = 0; \
    }

#define DEFINE_func_80139A34() \
    extern s32 D_80127520; \
    void func_80139A34(s32 a0) { \
        D_80127520 = a0; \
    }

#define DEFINE_func_80146D80() \
    void func_80146D80(s32 *a0) { \
        *(s32*)((s32)a0 + 0x18) = 0; \
        *(s32*)((s32)a0 + 0x14) = 0; \
        *(s32*)((s32)a0 + 0x10) = 0; \
    }

#define DEFINE_func_80146DE8() \
    void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3) { \
        *(s32*)((s32)a0 + 0x24) = a1; \
        *(s32*)((s32)a0 + 0x28) = a2; \
        *(s32*)((s32)a0 + 0x2C) = a3; \
    }

#define DEFINE_func_801472F0() \
    extern void *D_8012707C; \
    void func_801472F0(void *a0) { \
        D_8012707C = a0; \
    }

#define DEFINE_func_801473DC() \
    void func_801473DC(s32 *a0) { \
        *(s32*)((s32)a0 + 0x18) = 0; \
        *(s32*)((s32)a0 + 0x14) = 0; \
        *(s32*)((s32)a0 + 0x10) = 0; \
    }

#define DEFINE_func_8014B4C4() \
    extern s32 D_80078E98; \
    void func_8014B4C4(void) { \
        D_80078E98 = 0; \
    }

#define DEFINE_func_8014C6C0() \
    extern u8 D_80126D17; \
    void func_8014C6C0(void) { \
        D_80126D17 = 0; \
    }

#define DEFINE_func_8014C6D0() \
    extern u8 D_80126D1E; \
    void func_8014C6D0(void) { \
        D_80126D1E = 0; \
    }

#define DEFINE_func_8014C968() \
    extern s32 D_80126B50; \
    void func_8014C968(void) { \
        D_80126B50 = 0; \
    }

#define DEFINE_func_8014C98C() \
    extern s32 D_80126B50; \
    s32 func_8014C98C(void) { \
        return D_80126B50; \
    }

#define DEFINE_func_8014CAFC() \
    extern s32 D_80126B9C; \
    s32 func_8014CAFC(void) { \
        return D_80126B9C & 0x400; \
    }

#define DEFINE_func_8014CB0C() \
    extern s32 D_80126B9C; \
    s32 func_8014CB0C(void) { \
        return D_80126B9C & 0x80; \
    }

#define DEFINE_func_8014CB1C() \
    extern s32 D_80078E94; \
    s32 func_8014CB1C(void) { \
        return D_80078E94; \
    }

#define DEFINE_func_8014CB58() \
    extern u8 D_80078EC0; \
    s32 func_8014CB58(void) { \
        return D_80078EC0 & 0x7F; \
    }

#define DEFINE_func_8014CB7C() \
    extern s32 D_80126B9C; \
    s32 func_8014CB7C(void) { \
        return D_80126B9C & 0x800; \
    }

#define DEFINE_func_8014CB8C() \
    extern s32 D_80126B9C; \
    s32 func_8014CB8C(void) { \
        return D_80126B9C & 0x1000; \
    }

#define DEFINE_func_8014CBD8() \
    extern s32 D_80126CDC; \
    void func_8014CBD8(void) { \
        D_80126CDC = 0; \
    }

#define DEFINE_func_8014CBE8() \
    extern s16 D_80126CC4; \
    void func_8014CBE8(void) { \
        D_80126CC4 = 0; \
    }

#define DEFINE_func_80153C8C() \
    extern s32 D_80115210; \
    void func_80153C8C(void) { \
        D_80115210 = 0; \
    }

#define DEFINE_func_80153CBC() \
    extern s32 D_80115210; \
    s32 func_80153CBC(void) { \
        return D_80115210; \
    }

#define DEFINE_func_801632E0() \
    extern s32 D_80115100; \
    s32 func_801632E0(void) { \
        return D_80115100; \
    }

#define DEFINE_func_801658DC() \
    extern s8 D_80078EC4; \
    void func_801658DC(void) { \
        D_80078EC4 = 0; \
    }

#define DEFINE_func_80165978() \
    extern s32 D_8012672C; \
    s32 func_80165978(void) { \
        return D_8012672C; \
    }

#define DEFINE_func_801659A8() \
    extern s32 D_8012811C; \
    s32 func_801659A8(void) { \
        return D_8012811C; \
    }

#define DEFINE_func_801659CC() \
    extern s32 D_80126B08; \
    s32 func_801659CC(void) { \
        return D_80126B08; \
    }

#define DEFINE_func_8016F388() \
    extern u8 D_800B9A17; \
    void func_8016F388(void) { \
        D_800B9A17 = 0; \
    }

#define DEFINE_func_8017196C() \
    void func_8017196C(s32 *a0, s8 a1) { \
        *(s8*)((s32)a0 + 0x214) = a1; \
        *(s8*)((s32)a0 + 0x215) = 0; \
        *(s8*)((s32)a0 + 0x216) = 0; \
    }

#define DEFINE_func_80171A34() \
    void func_80171A34(s32 *a0, s8 a1) { \
        *(s8*)((s32)a0 + 0x214) = a1; \
        *(s8*)((s32)a0 + 0x215) = 0; \
        *(s8*)((s32)a0 + 0x216) = 0; \
    }

#define DEFINE_func_80174674() \
    extern s32 D_801270BC; \
    void func_80174674(void) { \
        D_801270BC = 0; \
    }

#define DEFINE_func_80174754() \
    extern s32 D_801270BC; \
    s32 func_80174754(void) { \
        return D_801270BC; \
    }

#define DEFINE_func_80174764() \
    extern s16 D_8011F9C8; \
    s16 func_80174764(void) { \
        return D_8011F9C8; \
    }

#define DEFINE_func_80174774() \
    extern s16 D_80126938; \
    s16 func_80174774(void) { \
        return D_80126938; \
    }

#define DEFINE_func_8012BF68() \
    void func_8012BF68(void *a0) { \
        *(u16 *)((s32)a0 + 0x5C) &= 0x7FFF; \
    }

#define DEFINE_func_801379D8() \
    extern s16 D_8012752E; \
    void func_801379D8(void) { \
        D_8012752E = 1; \
    }

#define DEFINE_func_80138948() \
    void func_80138948(void *a0) { \
        *(s16 *)((s32)a0 + 0x4)  = 7; \
        *(s8  *)((s32)a0 + 0x1F) = 0; \
        *(s8  *)((s32)a0 + 0xD)  = 0; \
    }

#define DEFINE_func_80146CA0() \
    void func_80146CA0(void *a0) { \
        *(u16 *)((s32)a0 + 0x2) += 1; \
    }

#define DEFINE_func_80146CB4() \
    void func_80146CB4(void *a0) { \
        *(u16 *)((s32)a0 + 0x2) -= 1; \
    }

#define DEFINE_func_801472B4() \
    void func_801472B4(void *a0) { \
        *(u16 *)((s32)a0 + 0x7E) &= 0xFFFD; \
    }

#define DEFINE_func_801474D8() \
    void func_801474D8(s32 *a0) { \
        *(s16*)((s32)a0 + 0x136) = 0; \
        *(s16*)((s32)a0 + 0x134) = 0; \
        *(s16*)((s32)a0 + 0x132) = 0; \
        *(s16*)((s32)a0 + 0x130) = 0; \
    }

#define DEFINE_func_80148634() \
    void func_80148634(void *a0) { \
        *(u16 *)((s32)a0 + 0xAA) = 0; \
        *(u16 *)((s32)a0 + 0xAC) = 0; \
        *(u16 *)((s32)a0 + 0xAE) = 0x8080; \
    }

#define DEFINE_func_80148C20() \
    s32 func_80148C20(s32 a0, s16 a1) { \
        s32 *p = *(s32 **)((s32)a0 + 0x20); \
        *(s16*)((s32)p + 0x12) = a1; \
        return 1; \
    }

#define DEFINE_func_8014900C() \
    void func_8014900C(s32 *a0) { \
        *(u16*)((s32)a0 + 0x3C) |= 0x8000; \
    }

#define DEFINE_func_80149020() \
    void func_80149020(s32 *a0) { \
        *(u16*)((s32)a0 + 0x3C) &= 0x7FFF; \
    }

#define DEFINE_func_80149034() \
    void func_80149034(s32 *a0) { \
        *(u16*)((s32)a0 + 0x3C) |= 0x4000; \
    }

#define DEFINE_func_80149048() \
    void func_80149048(s32 *a0) { \
        *(u16*)((s32)a0 + 0x3C) &= 0xBFFF; \
    }

#define DEFINE_func_8014B33C() \
    extern s32 D_80078E94; \
    void func_8014B33C(void) { \
        D_80078E94 = 0x80000000; \
    }

#define DEFINE_func_8014C6AC() \
    extern u8 D_80126D17; \
    void func_8014C6AC(void) { \
        D_80126D17 = 1; \
    }

#define DEFINE_func_8014C6E0() \
    extern u8 D_80126D1E; \
    void func_8014C6E0(void) { \
        D_80126D1E = 1; \
    }

#define DEFINE_func_8014C978() \
    extern s32 D_80126B50; \
    void func_8014C978(void) { \
        D_80126B50 = 1; \
    }

#define DEFINE_func_8014CA00() \
    s32 func_8014CA00(s32 a0) { \
        s32 *p = *(s32 **)((s32)a0 + 0x78); \
        return *(s16*)((s32)p + 0x2C); \
    }

#define DEFINE_func_80171A58() \
    s32 func_80171A58(u8 *a0) { \
        s32 v0 = a0[0x216] + 1; \
        a0[0x216] = v0; \
        return v0; \
    }

#define DEFINE_func_80171A6C() \
    s32 func_80171A6C(u8 *a0) { \
        s32 v0 = a0[0x216] - 1; \
        a0[0x216] = v0; \
        return v0; \
    }

#define DEFINE_func_80172590() \
    s32 func_80172590(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x1; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_801725A4() \
    s32 func_801725A4(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x2; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_801725B8() \
    s32 func_801725B8(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x4; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_801725CC() \
    s32 func_801725CC(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x8; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_801725E0() \
    s32 func_801725E0(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x10; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_801725F4() \
    s32 func_801725F4(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x20; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_80172608() \
    s32 func_80172608(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x40; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_8017261C() \
    s32 func_8017261C(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x80; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_80172630() \
    s32 func_80172630(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x100; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_80172644() \
    s32 func_80172644(u8 *a0) { \
        s32 v0 = *(u32 *)((s32)a0 + 0x1F4) | 0x200; \
        *(u32 *)((s32)a0 + 0x1F4) = v0; \
        return v0; \
    }

#define DEFINE_func_80174808() \
    s32 func_80174808(u8 *a0) { \
        s32 v = (s32)a0[0x214] + 1; \
        a0[0x214] = (u8)v; \
        return v; \
    }

#define DEFINE_func_80175494() \
    extern u8 D_8011F7A8; \
    void func_80175494(void) { \
        D_8011F7A8 = 2; \
    }

#define DEFINE_func_80142C84() \
    void func_80142C84(s32 a0) { \
        *(s32 *)(a0 + 0x14) = 0xFFF40000; \
        *(s32 *)(a0 + 0x48) = 0x20000; \
        *(s16 *)(a0 + 0x102) = 0; \
    }

#define DEFINE_func_80147460() \
    void func_80147460(s32 a0) { \
        *(s32 *)(a0 + 0x8) += *(s32 *)(a0 + 0x34); \
    }

#define DEFINE_func_80148C34() \
    s32 func_80148C34(s32 a0, s32 a1) { \
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x400) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148C4C() \
    s32 func_80148C4C(s32 a0, s32 a1) { \
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x200) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148C64() \
    s32 func_80148C64(s32 a0, s32 a1) { \
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x800) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148C84() \
    s32 func_80148C84(s32 a0, s32 a1) { \
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (a1 + 0x600) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148CB4() \
    s32 func_80148CB4(s32 a0, s32 a1) { \
        s32 v0 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148CCC() \
    s32 func_80148CCC(s32 a0, s32 a1) { \
        s32 v0 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(v0 + 0x12) = (a1 - 0x200) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148CF4() \
    s32 func_80148CF4(s32 a0, s32 a1) { \
        s32 v0 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(v0 + 0x12) = (a1 - 0x600) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80148D0C() \
    s32 func_80148D0C(s32 a0, s32 a1) { \
        s32 v0 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(v0 + 0x12) = (a1 - 0x400) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_80149210() \
    void func_80149210(s32 a0, s32 a1) { \
        *(s32 *)((s32)a0 + 0x1E4) = a1 | (a1 << 16); \
        *(s16 *)((s32)a0 + 0x1E4) = a1; \
        *(s16 *)((s32)a0 + 0x1E6) = a1; \
    }

#define DEFINE_func_8014B2F8() \
    extern s32 D_80078E94; \
    extern s32 D_80078ECC; \
    void func_8014B2F8(void) { \
        D_80078E94 = 0; \
        D_80078ECC = 0; \
    }

#define DEFINE_func_8014B598() \
    extern u8 D_80126D1C; \
    extern s32 D_80126D74; \
    void func_8014B598(s32 a0, s32 a1) { \
        D_80126D1C = a0; \
        D_80126D74 = a1; \
    }

#define DEFINE_func_8014BB0C() \
    extern u16 D_80078EB2; \
    extern s16 D_80078EB4; \
    void func_8014BB0C(void) { \
        D_80078EB4 = D_80078EB2; \
    }

#define DEFINE_func_8014BDC8() \
    extern u16 D_80078EB6; \
    extern s16 D_80078EB8; \
    void func_8014BDC8(void) { \
        D_80078EB8 = D_80078EB6; \
    }

#define DEFINE_func_8014CA70() \
    u16 func_8014CA70(s32 a0, s32 a1) { \
        s32 base = *(s32 *)((s32)a0 + 0x78); \
        return *(u16 *)((a1 << 1) + base + 0x14); \
    }

#define DEFINE_func_8014CAE4() \
    u16 func_8014CAE4(s32 *a0, s32 a1) { \
        s32 base = a0[0x78 / 4]; \
        return *(u16 *)(base + a1 * 2 + 0x1C); \
    }

#define DEFINE_func_80153BD8() \
    extern s32 D_801151FC; \
    s32 func_80153BD8(s32 a0) { \
        return (a0 ^ D_801151FC) == 0; \
    }

#define DEFINE_func_80153C18() \
    extern s32 D_80127518; \
    extern s32 D_801151FC; \
    void func_80153C18(void) { \
        D_80127518 = 0; \
        D_801151FC = 0; \
    }

#define DEFINE_func_80153C74() \
    extern s16 D_8011DB0C; \
    extern s16 D_8011DB1A; \
    void func_80153C74(s16 a0, s16 a1) { \
        D_8011DB0C = a0; \
        D_8011DB1A = a1; \
    }

#define DEFINE_func_801553A8() \
    void func_801553A8(s32 *a0) { \
        *(s32 *)((s32)a0 + 0x44) &= 0xDFFFFFFF; \
    }

#define DEFINE_func_80155440() \
    void func_80155440(s32 *a0) { \
        *(s32 *)((s32)a0 + 0x44) &= 0xEFFFFFFF; \
    }

#define DEFINE_func_8016F094() \
    void func_8016F094(s32 *a0) { \
        *(s32 *)((s32)a0 + 0x1F8) &= 0xFBFFFFFF; \
    }

#define DEFINE_func_8016F1AC() \
    extern s32 D_80126D50; \
    s32 func_8016F1AC(void) { \
        return D_80126D50 & 0x80FFFFFF; \
    }

#define DEFINE_func_80171A1C() \
    void func_80171A1C(u8 *a0) { \
        a0[0x215] = 0; \
        a0[0x216] = 0; \
        a0[0x214] = a0[0x214] + 1; \
    }

#define DEFINE_func_8012ADE4() \
    void func_8012ADE4(u8 *a0) { \
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38); \
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C); \
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40); \
    }

#define DEFINE_func_8012B200() \
    void func_8012B200(u8 *a0) { \
        *(s32 *)(a0 + 0x18) = 0; \
        *(s32 *)(a0 + 0x14) = 0; \
        *(s32 *)(a0 + 0x10) = 0; \
        *(s32 *)(a0 + 0x4C) = 0; \
        *(s32 *)(a0 + 0x48) = 0; \
        *(s32 *)(a0 + 0x44) = 0; \
    }

#define DEFINE_func_8012E88C() \
    void func_8012E88C(u8 *a0) { \
        s32 *p = *(s32 **)(a0 + 0x20); \
        p[1] = p[1] & 0x7FFFFFFF; \
    }

#define DEFINE_func_8012E8A8() \
    void func_8012E8A8(u8 *a0) { \
        s32 *p = *(s32 **)(a0 + 0x20); \
        p[1] = p[1] | 0x80000000; \
    }

#define DEFINE_func_8012E8C4() \
    void func_8012E8C4(u8 *a0) { \
        s32 *p = *(s32 **)(a0 + 0x20); \
        p[1] = p[1] ^ 0x80000000; \
    }

#define DEFINE_func_8014905C() \
    void func_8014905C(u8 *a0) { \
        *(s16 *)(a0 + 0x104) = 0; \
        *(s16 *)(a0 + 0x102) = 0; \
        *(s16 *)(a0 + 0x100) = 0; \
        *(s16 *)(a0 + 0x10C) = 0; \
        *(s16 *)(a0 + 0x10A) = 0; \
        *(s16 *)(a0 + 0x108) = 0; \
    }

#define DEFINE_func_80149BEC() \
    void func_80149BEC(s32 a0) { \
        u8 v = *(u8 *)(a0 + 0x223); \
        if (v != 0) { \
            *(u8 *)(a0 + 0x223) = v - 1; \
        } \
    }

#define DEFINE_func_8014A680() \
    void func_8014A680(s32 a0) { \
        u8 v = *(u8 *)(a0 + 0x1BC); \
        if (v != 0) { \
            *(u8 *)(a0 + 0x1BC) = v - 1; \
        } \
    }

#define DEFINE_func_8014A6A8() \
    void func_8014A6A8(s32 a0) { \
        u8 v = *(u8 *)(a0 + 0x1BD); \
        if (v != 0) { \
            *(u8 *)(a0 + 0x1BD) = v - 1; \
        } \
    }

#define DEFINE_func_8014A71C() \
    void func_8014A71C(s32 a0) { \
        u8 v = *(u8 *)(a0 + 0x1BE); \
        if (v != 0) { \
            *(u8 *)(a0 + 0x1BE) = v - 1; \
        } \
    }

#define DEFINE_func_8014BFF4() \
    void func_8014BFF4(s32 a0, s32 a1) { \
        if (*(u8 *)(a0 + 0x4E) == 0) { \
            *(u8 *)(a0 + 0x4E) = a1; \
        } \
    }

#define DEFINE_func_801511A8() \
    void func_801511A8(u8 *a0) { \
        u16 v = *(u16 *)(a0 + 0x3C); \
        *(s16 *)(a0 + 0x3E) = 0; \
        *(s16 *)(a0 + 0x40) = 0; \
        *(s16 *)(a0 + 0x42) = 0; \
        *(u16 *)(a0 + 0x3C) = v & 0xFFFE; \
    }

#define DEFINE_func_801511C4() \
    void func_801511C4(u8 *a0) { \
        *(u16 *)(a0 + 0xF0) = *(u16 *)(a0 + 0x3E); \
        *(u16 *)(a0 + 0xF2) = *(u16 *)(a0 + 0x40); \
        *(u16 *)(a0 + 0xF4) = *(u16 *)(a0 + 0x42); \
    }

#define DEFINE_func_80154134() \
    void func_80154134(u8 *a0) { \
        *(s32 *)(a0 + 0xB4) = 0; \
        *(s16 *)(a0 + 0xBA) = 0; \
        *(s16 *)(a0 + 0xB8) = 0; \
        a0[0xBD] = 0; \
        a0[0xBC] = 0; \
        a0[0xDC] = 0; \
    }

#define DEFINE_func_80154B7C() \
    void func_80154B7C(u8 *a0, s32 a1) { \
        *(s32 *)(a0 + 0xD0) = a1; \
        *(s16 *)(a0 + 0xD6) = 1; \
        *(s16 *)(a0 + 0xD4) = 1; \
        a0[0xD8] = 0; \
        a0[0xD9] = 0; \
    }

#define DEFINE_func_80154BC8() \
    void func_80154BC8(void *a0, s32 a1, s32 a2) { \
        *(s32 *)((s32)a0 + 0xD0) = a1; \
        *(s16 *)((s32)a0 + 0xD6) = 1; \
        *(s16 *)((s32)a0 + 0xD4) = 1; \
        *(s8 *)((s32)a0 + 0xD8) = a2; \
        *(s8 *)((s32)a0 + 0xD9) = a2; \
    }

#define DEFINE_func_801596D4() \
    s32 func_801596D4(void *a0) { \
        *(s32 *)((s32)a0 + 0x28) = 0x10; \
        *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1; \
        return 0; \
    }

#define DEFINE_func_80165124() \
    void func_80165124(void *a0) { \
        *(s8 *)((s32)a0 + 0x50) = *(u16 *)((s32)a0 + 0x62); \
        *(s8 *)((s32)a0 + 0x51) = *(u16 *)((s32)a0 + 0x62); \
        *(s8 *)((s32)a0 + 0x52) = *(u16 *)((s32)a0 + 0x62); \
    }

#define DEFINE_func_8016BF34() \
    void func_8016BF34(void *a0) { \
        *(s16 *)((s32)a0 + 0x12) = *(u16 *)((s32)a0 + 0x6); \
        *(s16 *)((s32)a0 + 0x16) = *(u16 *)((s32)a0 + 0xA); \
        *(s16 *)((s32)a0 + 0x1A) = *(u16 *)((s32)a0 + 0xE); \
    }

#define DEFINE_func_80174ED4() \
    extern u16 D_80126980; \
    s32 func_80174ED4(void) { \
        return (s16)(D_80126980 & 0x8000); \
    }

#define DEFINE_func_80128158() \
    extern void func_80128288(void); \
    void func_80128158(void) { \
        func_80128288(); \
    }

#define DEFINE_func_80128178() \
    extern void func_801285E4(void); \
    void func_80128178(void) { \
        func_801285E4(); \
    }

#define DEFINE_func_80128198() \
    extern void func_80128678(void); \
    void func_80128198(void) { \
        func_80128678(); \
    }

#define DEFINE_func_801281B8() \
    extern void func_80128714(void); \
    void func_801281B8(void) { \
        func_80128714(); \
    }

#define DEFINE_func_801281D8() \
    extern void func_8013E67C(void); \
    void func_801281D8(void) { \
        func_8013E67C(); \
    }

#define DEFINE_func_801281F8() \
    extern void func_8013E558(void); \
    void func_801281F8(void) { \
        func_8013E558(); \
    }

#define DEFINE_func_80128228() \
    extern void func_80128A28(void); \
    void func_80128228(void) { \
        func_80128A28(); \
    }

#define DEFINE_func_80128248() \
    extern void func_80128AF4(void); \
    void func_80128248(void) { \
        func_80128AF4(); \
    }

#define DEFINE_func_80128268() \
    extern void func_801282EC(void); \
    void func_80128268(void) { \
        func_801282EC(); \
    }

#define DEFINE_func_801282CC() \
    extern void func_80011B7C(int); \
    void func_801282CC(void) { \
        func_80011B7C(0x11); \
    }

#define DEFINE_func_8012A8E8() \
    extern void func_8012AAAC(void); \
    void func_8012A8E8(void) { \
        func_8012AAAC(); \
    }

#define DEFINE_func_8012B21C() \
    void func_8012B21C(void *a0) { \
        *(s32 *)((s32)a0 + 0x18) = 0; \
        *(s32 *)((s32)a0 + 0x14) = 0; \
        *(s32 *)((s32)a0 + 0x10) = 0; \
        *(s32 *)((s32)a0 + 0x4C) = 0; \
        *(s32 *)((s32)a0 + 0x44) = 0; \
        *(s32 *)((s32)a0 + 0x48) = 0xC000; \
    }

#define DEFINE_func_8012D38C() \
    extern void func_8012D098(); \
    void func_8012D38C(int a0) { \
        func_8012D098(a0, 0); \
    }

#define DEFINE_func_8012FCA4() \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FCA4(int a0) { \
        func_80131CA8(a0, 0x1B); \
    }

#define DEFINE_func_80136C1C() \
    extern void func_80136C3C(void); \
    void func_80136C1C(void) { \
        func_80136C3C(); \
    }

#define DEFINE_func_801376C8() \
    extern void func_801376E8(int a0, int a1); \
    void func_801376C8(int a0) { \
        func_801376E8(a0, 0); \
    }

#define DEFINE_func_80146534() \
    extern s32 D_80127098; \
    extern s32 D_80127094; \
    extern s32 D_80127090; \
    void func_80146534(void) { \
        D_80127098 = 0; \
        D_80127094 = 0; \
        D_80127090 = 0; \
    }

#define DEFINE_func_80147788() \
    void func_80147788(void *a0, s32 a1) { \
        void *v1 = *(void **)((s32)a0 + 0x20); \
        *(s16 *)((s32)v1 + 0x10) = (*(u16 *)((s32)v1 + 0x10) + a1) & 0xFFF; \
    }

#define DEFINE_func_801477A8() \
    void func_801477A8(void *a0, s32 a1) { \
        void *v1 = *(void **)((s32)a0 + 0x20); \
        *(s16 *)((s32)v1 + 0x12) = (*(u16 *)((s32)v1 + 0x12) + a1) & 0xFFF; \
    }

#define DEFINE_func_801477C8() \
    void func_801477C8(void *a0, s32 a1) { \
        void *v1 = *(void **)((s32)a0 + 0x20); \
        *(s16 *)((s32)v1 + 0x14) = (*(u16 *)((s32)v1 + 0x14) + a1) & 0xFFF; \
    }

#define DEFINE_func_80147928() \
    extern void func_80147948(int a0, int a1, int a2); \
    void func_80147928(int a0, int a1) { \
        func_80147948(a0, a1, 0x1F0000); \
    }

#define DEFINE_func_8014799C() \
    extern void func_801479BC(int a0, int a1, int a2); \
    void func_8014799C(int a0, int a1) { \
        func_801479BC(a0, a1, 0x1F0000); \
    }

#define DEFINE_func_80147A10() \
    extern void func_80147A30(int a0, int a1, int a2); \
    void func_80147A10(int a0, int a1) { \
        func_80147A30(a0, a1, 0x1F0000); \
    }

#define DEFINE_func_80149704() \
    extern void func_8015AD08(); \
    void func_80149704(void) { \
        func_8015AD08(); \
    }

#define DEFINE_func_80149724() \
    extern void func_8015ACC4(); \
    void func_80149724(void) { \
        func_8015ACC4(); \
    }

#define DEFINE_func_80149788() \
    extern void func_8015F7A0(); \
    void func_80149788(void) { \
        func_8015F7A0(); \
    }

#define DEFINE_func_80149864() \
    extern void func_801653B8(); \
    void func_80149864(void) { \
        func_801653B8(); \
    }

#define DEFINE_func_801498C0() \
    extern void func_80160B00(); \
    void func_801498C0(void) { \
        func_80160B00(); \
    }

#define DEFINE_func_80149C94() \
    extern void func_801577C8(); \
    void func_80149C94(void) { \
        func_801577C8(); \
    }

#define DEFINE_func_80149CB4() \
    extern void func_80157D20(void); \
    void func_80149CB4(void) { \
        func_80157D20(); \
    }

#define DEFINE_func_8014A218() \
    extern void func_8015D4B4(); \
    void func_8014A218(void) { \
        func_8015D4B4(); \
    }

#define DEFINE_func_8014A4FC() \
    extern void func_8015EDD4(); \
    void func_8014A4FC(void) { \
        func_8015EDD4(); \
    }

#define DEFINE_func_8014A830() \
    extern void func_8015E184(); \
    void func_8014A830(void) { \
        func_8015E184(); \
    }

#define DEFINE_func_8014AB5C() \
    extern void func_8014AB7C(); \
    void func_8014AB5C(void) { \
        func_8014AB7C(); \
    }

#define DEFINE_func_8014ABF0() \
    extern void func_8014AC10(); \
    void func_8014ABF0(void) { \
        func_8014AC10(); \
    }

#define DEFINE_func_8014BEF8() \
    extern s32 func_80029178(s32 arg); \
    u8 func_8014BEF8(void) { \
        return func_80029178(0x80); \
    }

#define DEFINE_func_8014BF6C() \
    extern s32 func_800291B4(s32 arg); \
    u8 func_8014BF6C(void) { \
        return func_800291B4(0xCF); \
    }

#define DEFINE_func_8014BFD4() \
    extern s32 func_800291B4(s32 arg); \
    u8 func_8014BFD4(void) { \
        return func_800291B4(0xD0); \
    }

#define DEFINE_func_80150150() \
    extern s32 func_80134510(s32 arg); \
    s32 func_80150150(s32 a, s32 b) { \
        return func_80134510(b) != 0; \
    }

#define DEFINE_func_80150460() \
    extern s32 func_80134510(s32 arg); \
    s32 func_80150460(s32 a, s32 b) { \
        return func_80134510(b) != 0; \
    }

#define DEFINE_func_80150CC4() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150CC4(s32 a) { \
        func_80150EC4(a, 0); \
    }

#define DEFINE_func_80150CE4() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150CE4(s32 a) { \
        func_80150EC4(a, 1); \
    }

#define DEFINE_func_80150D04() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150D04(s32 a) { \
        func_80150EC4(a, 2); \
    }

#define DEFINE_func_80150D24() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150D24(s32 a) { \
        func_80150EC4(a, 3); \
    }

#define DEFINE_func_80150D44() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150D44(s32 a) { \
        func_80150EC4(a, 4); \
    }

#define DEFINE_func_80150D64() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150D64(s32 a) { \
        func_80150EC4(a, 5); \
    }

#define DEFINE_func_80150D84() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150D84(s32 a) { \
        func_80150EC4(a, 6); \
    }

#define DEFINE_func_80150DA4() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150DA4(s32 a) { \
        func_80150EC4(a, 7); \
    }

#define DEFINE_func_80150DC4() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150DC4(s32 a) { \
        func_80150EC4(a, 8); \
    }

#define DEFINE_func_80150DE4() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150DE4(s32 a) { \
        func_80150EC4(a, 9); \
    }

#define DEFINE_func_80150E04() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150E04(s32 a) { \
        func_80150EC4(a, 10); \
    }

#define DEFINE_func_80150E24() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150E24(s32 a) { \
        func_80150EC4(a, 11); \
    }

#define DEFINE_func_80150E44() \
    extern void func_80150EC4(s32 a, s32 b); \
    void func_80150E44(s32 a) { \
        func_80150EC4(a, 12); \
    }

#define DEFINE_func_80150E64() \
    extern void func_80150EC4(s32 a0, s32 a1); \
    void func_80150E64(s32 a0) { \
        func_80150EC4(a0, 0xD); \
    }

#define DEFINE_func_80151110() \
    extern s32 func_8012DB84(void); \
    s32 func_80151110(void) { \
        return func_8012DB84(); \
    }

#define DEFINE_func_80151164() \
    extern s32 func_80151184(s32 a0, s32 a1, s32 a2); \
    s32 func_80151164(s32 a0, s32 a1) { \
        return func_80151184(a0, a1, 0xA); \
    }

#define DEFINE_func_80151924() \
    extern s32 func_80151944(void); \
    s32 func_80151924(void) { \
        return func_80151944(); \
    }

#define DEFINE_func_80153C9C() \
    extern s32 D_80115210; \
    void func_80153C9C(void) { \
        D_80115210 = D_80115210 + 1; \
    }

#define DEFINE_func_80155F60() \
    extern s32 func_80155F80(); \
    s32 func_80155F60(void) { \
        return func_80155F80(); \
    }

#define DEFINE_func_8015771C() \
    extern s32 func_8015773C(u8 *a0); \
    s32 func_8015771C(u8 *a0) { \
        a0[0x1AA] = 0; \
        return func_8015773C(a0); \
    }

#define DEFINE_func_8015BE74() \
    extern s32 func_8015BE94(); \
    s32 func_8015BE74(void) { \
        return func_8015BE94(); \
    }

#define DEFINE_func_8015BEC4() \
    extern s32 func_8015AE2C(); \
    s32 func_8015BEC4(void) { \
        return func_8015AE2C(); \
    }

#define DEFINE_func_8015BEE4() \
    extern s32 func_8015B950(void); \
    s32 func_8015BEE4(void) { \
        return func_8015B950(); \
    }

#define DEFINE_func_8015CCB0() \
    extern s32 func_8015CCD0(); \
    s32 func_8015CCB0(void) { \
        return func_8015CCD0(); \
    }

#define DEFINE_func_8015CFFC() \
    extern void func_8015D01C(); \
    void func_8015CFFC(void) { \
        func_8015D01C(); \
    }

#define DEFINE_func_8015D524() \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015D524(s32 arg0) { \
        func_80154A74(arg0, 0x11); \
    }

#define DEFINE_func_8015F360() \
    extern void func_8015F380(); \
    void func_8015F360(void) { \
        func_8015F380(); \
    }

#define DEFINE_func_8015FA24() \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015FA24(s32 arg0) { \
        func_80154A74(arg0, 0x11); \
    }

#define DEFINE_func_80160EE0() \
    extern void func_80160F00(); \
    void func_80160EE0(void) { \
        func_80160F00(); \
    }

#define DEFINE_func_80161104() \
    extern s32 func_80161208(); \
    s32 func_80161104(void) { \
        return func_80161208() == 0; \
    }

#define DEFINE_func_80162F60() \
    extern void func_80147948(s32 a0, s32 a1, s32 a2); \
    void func_80162F60(s32 arg0, s32 arg1) { \
        func_80147948(arg0, arg1, 0x7F0000); \
    }

#define DEFINE_func_80162F80() \
    extern void func_801479BC(s32 a0, s32 a1, s32 a2); \
    void func_80162F80(s32 arg0, s32 arg1) { \
        func_801479BC(arg0, arg1, 0x7F0000); \
    }

#define DEFINE_func_80162FA0() \
    extern void func_80147A30(s32 a0, s32 a1, s32 a2); \
    void func_80162FA0(s32 arg0, s32 arg1) { \
        func_80147A30(arg0, arg1, 0x7F0000); \
    }

#define DEFINE_func_80164DB0() \
    extern void func_80162CCC(void); \
    void func_80164DB0(void) { \
        func_80162CCC(); \
    }

#define DEFINE_func_80165938() \
    extern s32 D_8012672C; \
    extern s32 D_8012811C; \
    extern s32 D_80126B08; \
    void func_80165938(void) { \
        D_8012672C = 0; \
        D_8012811C = 0; \
        D_80126B08 = 0; \
    }

#define DEFINE_func_80165958() \
    extern s32 D_8012672C; \
    void func_80165958(void) { \
        D_8012672C = D_8012672C + 1; \
    }

#define DEFINE_func_80165988() \
    extern s32 D_8012811C; \
    void func_80165988(void) { \
        D_8012811C = D_8012811C + 1; \
    }

#define DEFINE_func_80165C58() \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_80165C58(s32 arg0) { \
        func_80154A74(arg0, 0x11); \
    }

#define DEFINE_func_80168A88() \
    extern void func_80146C3C(void); \
    void func_80168A88(void) { \
        func_80146C3C(); \
    }

#define DEFINE_func_8016B428() \
    extern s32 func_8016B448(s32, s32); \
    s32 func_8016B428(s32 a0) { \
        return func_8016B448(a0, 0); \
    }

#define DEFINE_func_8016BA48() \
    extern s32 func_8016BA68(s32, s32); \
    s32 func_8016BA48(s32 a0) { \
        return func_8016BA68(a0, 0); \
    }

#define DEFINE_func_8016ED6C() \
    extern void func_80146C3C(void); \
    void func_8016ED6C(void) { \
        func_80146C3C(); \
    }

#define DEFINE_func_8016EFA8() \
    extern s32 func_8016EFC8(); \
    s32 func_8016EFA8(s32 a0) { \
        return func_8016EFC8(a0); \
    }

#define DEFINE_func_8016F288() \
    extern s32 D_80126D50; \
    void func_8016F288(void) { \
        D_80126D50 = D_80126D50 | 0x1000000; \
    }

#define DEFINE_func_8016F2A8() \
    extern s32 D_80126D50; \
    void func_8016F2A8(void) { \
        D_80126D50 = D_80126D50 | 0x2000000; \
    }

#define DEFINE_func_8016F2EC() \
    extern s32 D_80126D50; \
    void func_8016F2EC(void) { \
        D_80126D50 = D_80126D50 | 0x8000000; \
    }

#define DEFINE_func_8016F330() \
    extern s32 D_80126D50; \
    void func_8016F330(void) { \
        D_80126D50 = D_80126D50 | 0x10000000; \
    }

#define DEFINE_func_801724EC() \
    extern s32 func_80013450(s32); \
    s32 func_801724EC(s32 a0) { \
        return func_80013450(a0 + 4) < 0x10; \
    }

#define DEFINE_func_80172760() \
    extern s32 func_80174650(s32); \
    s32 func_80172760(s32 a0) { \
        return func_80174650(a0); \
    }

#define DEFINE_func_80174188() \
    extern s32 func_8014BCEC(s32, s32); \
    s32 func_80174188(s32 a0) { \
        return func_8014BCEC(a0, 0x19); \
    }

#define DEFINE_func_80174630() \
    extern s32 D_801270BC; \
    void func_80174630(void) { \
        D_801270BC = D_801270BC | 0x1; \
    }

#define DEFINE_func_801747AC() \
    extern s32 func_8016F0AC(); \
    s32 func_801747AC(s32 a0) { \
        return func_8016F0AC(a0); \
    }

#define DEFINE_func_801748C4() \
    void func_801748C4(s32 a0) { \
        u8 v = *(u8 *)(a0 + 0x214) + 1; \
        *(s32 *)(a0 + 0x44) |= 0x4000000; \
        *(u8 *)(a0 + 0x214) = v; \
    }

#define DEFINE_func_801749A8() \
    extern s32 func_801749C8(); \
    s32 func_801749A8(s32 a0) { \
        return func_801749C8(a0); \
    }

#define DEFINE_func_80174C60() \
    extern s32 func_80174CB0(); \
    s32 func_80174C60(s32 a0) { \
        return func_80174CB0(a0, 0); \
    }

#define DEFINE_func_8017ADE8() \
    extern s32 func_8017AD0C(s32); \
    s32 func_8017ADE8(s32 a0) { \
        return func_8017AD0C(a0); \
    }

#define DEFINE_func_80129258() \
    extern s16 D_8011DB30; \
    void func_80129258(void) { \
        s16 *p = &D_8011DB30; \
        s32 i = 0x7F; \
        do { \
            *p = 0; \
            p = (s16 *)((s32)p + 0x38); \
            i--; \
        } while (i >= 0); \
    }

#define DEFINE_func_80129350() \
    void func_80129350(s32 a0, s32 a1) { \
        *(s32 *)(a0 + 0x4) = *(s32 *)(a1 + 0x4); \
        *(s32 *)(a0 + 0x8) = *(s32 *)(a1 + 0x8); \
        *(s32 *)(a0 + 0xC) = *(s32 *)(a1 + 0xC); \
    }

#define DEFINE_func_80129374() \
    void func_80129374(s32 a0, s32 a1) { \
        *(s32 *)(a0 + 0x10) = *(s32 *)(a1 + 0x10); \
        *(s32 *)(a0 + 0x14) = *(s32 *)(a1 + 0x14); \
        *(s32 *)(a0 + 0x18) = *(s32 *)(a1 + 0x18); \
    }

#define DEFINE_func_80129FF4() \
    extern void func_8012A018(s32 a, s32 b); \
    void func_80129FF4(void) { \
        func_8012A018(0, 0); \
    }

#define DEFINE_func_8012B23C() \
    void func_8012B23C(s32 a0) { \
        *(s32 *)(a0 + 0x18) = 0; \
        *(s32 *)(a0 + 0x14) = 0; \
        *(s32 *)(a0 + 0x10) = 0; \
        *(s32 *)(a0 + 0x4C) = 0; \
        *(s32 *)(a0 + 0x44) = 0; \
        *(s32 *)(a0 + 0x48) = 0x18000; \
    }

#define DEFINE_func_8012C194() \
    extern void func_8001D074(s32 a, s32 b); \
    void func_8012C194(void) { \
        func_8001D074(0x3E, 0x7D); \
    }

#define DEFINE_func_8012C1B8() \
    extern void func_8001CFDC(s32 a, s32 b); \
    void func_8012C1B8(void) { \
        func_8001CFDC(0x26, 0x85); \
    }

#define DEFINE_func_8012CC1C() \
    extern s32 func_8012CC88(); \
    void func_8012CC1C(s32 arg0, s32 arg1) { \
        func_8012CC88(arg0, 0, arg1); \
    }

#define DEFINE_func_8012CC40() \
    extern s32 func_8012CC88(); \
    void func_8012CC40(s32 arg0, s32 arg1) { \
        func_8012CC88(arg0, 1, arg1); \
    }

#define DEFINE_func_80139A44() \
    extern s32 D_80127530[4]; \
    void func_80139A44(s32 a0, u16 a1) { \
        if (a1 < 4) { \
            D_80127530[a1] = a0; \
        } \
    }

#define DEFINE_func_80139A68() \
    extern s16 D_80127540[4]; \
    void func_80139A68(s32 a0, u16 a1) { \
        if (a1 < 4) { \
            D_80127540[a1] = (s16)a0; \
        } \
    }

#define DEFINE_func_80139DC8() \
    extern s16 D_8012811A; \
    void func_80139DC8(void) { \
        s32 i = 0x287; \
        s16 *p = &D_8012811A; \
        do { \
            *p = 0; \
            i--; \
            p = (s16 *)((s32)p - 2); \
        } while (i >= 0); \
    }

#define DEFINE_func_80143970() \
    extern s32 func_8012C588(s32 a0, s32 a1); \
    s32 func_80143970(s32 a0) { \
        return func_8012C588(0x1B, a0); \
    }

#define DEFINE_func_80146554() \
    extern void func_8001D074(s32 a0, s32 a1); \
    void func_80146554(void) { \
        func_8001D074(4, 6); \
    }

#define DEFINE_func_80146578() \
    extern void func_8001D074(s32 a0, s32 a1); \
    void func_80146578(void) { \
        func_8001D074(6, 0x16); \
    }

#define DEFINE_func_8014659C() \
    extern void func_8001CFDC(s32, s32); \
    void func_8014659C(void) { \
        func_8001CFDC(6, 0x16); \
    }

#define DEFINE_func_801465C0() \
    extern void func_8001D074(s32, s32); \
    void func_801465C0(void) { \
        func_8001D074(0x16, 0x3E); \
    }

#define DEFINE_func_801465E4() \
    extern void func_8001CFDC(s32, s32); \
    void func_801465E4(void) { \
        func_8001CFDC(0x16, 0x26); \
    }

#define DEFINE_func_80147290() \
    extern s16 D_80126BB8; \
    extern s16 D_80126BBA; \
    extern s16 D_80126BBC; \
    void func_80147290(void) { \
        D_80126BB8 = 0x1000; \
        D_80126BBA = 0x1000; \
        D_80126BBC = 0x1000; \
    }

#define DEFINE_func_80147300() \
    extern void func_80147364(u16, s32); \
    void func_80147300(u16 arg0) { \
        func_80147364(arg0, 0); \
    }

#define DEFINE_func_80149350() \
    extern void func_8012F14C(s32); \
    void func_80149350(s32 arg0) { \
        func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34); \
    }

#define DEFINE_func_8014942C() \
    extern void func_8012F038(s32); \
    void func_8014942C(s32 arg0) { \
        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34); \
    }

#define DEFINE_func_8014AA04() \
    extern u8 D_80078EC0; \
    void func_8014AA04(s32 a0) { \
        D_80078EC0 = a0 | (D_80078EC0 & 0x80); \
    }

#define DEFINE_func_8014BE78() \
    extern void func_80029124(s32, s32); \
    void func_8014BE78(void) { \
        func_80029124(0x12F, 1); \
    }

#define DEFINE_func_8014BE9C() \
    extern void func_80029124(s32, s32); \
    void func_8014BE9C(void) { \
        func_80029124(0x12F, 0); \
    }

#define DEFINE_func_8014BF48() \
    extern void func_800291A0(s32, s32); \
    void func_8014BF48(void) { \
        func_800291A0(0xCF, 0); \
    }

#define DEFINE_func_8014BF8C() \
    extern void func_800291A0(s32, s32); \
    void func_8014BF8C(u8 arg0) { \
        func_800291A0(0xD0, arg0); \
    }

#define DEFINE_func_8014BFB0() \
    extern void func_800291A0(s32, s32); \
    void func_8014BFB0(void) { \
        func_800291A0(0xD0, 0); \
    }

#define DEFINE_func_80150CA0() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80150CA0(int arg) { \
        return func_80151184(arg, 0xE001, 0x10); \
    }

#define DEFINE_func_80150FB4() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80150FB4(int arg) { \
        return func_80151184(arg, 0x8, 0); \
    }

#define DEFINE_func_80151014() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80151014(int arg) { \
        return func_80151184(arg, 0xC00B, 0x20); \
    }

#define DEFINE_func_80151070() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80151070(int arg) { \
        return func_80151184(arg, 0xE003, 0x10); \
    }

#define DEFINE_func_80151094() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80151094(int arg) { \
        return func_80151184(arg, 0xC00D, 0x18); \
    }

#define DEFINE_func_801510C8() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_801510C8(int arg) { \
        return func_80151184(arg, 0x4018, 0x20); \
    }

#define DEFINE_func_801510EC() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_801510EC(int arg) { \
        return func_80151184(arg, 0xE016, 0x10); \
    }

#define DEFINE_func_80151138() \
    extern int func_80151184(int arg, int a1, int a2); \
    int func_80151138(int arg) { \
        return func_80151184(arg, 0xC01F, 0x10); \
    }

#define DEFINE_func_801511E0() \
    extern int func_80151204(int arg, int a1); \
    int func_801511E0(int arg) { \
        return func_80151204(arg, *(short *)((int)arg + 0xF2)); \
    }

#define DEFINE_func_80155FB0() \
    extern int func_80155FF8(int arg, int a1); \
    int func_80155FB0(int arg, int a1) { \
        return func_80155FF8(arg, a1 | 0x10000); \
    }

#define DEFINE_func_80155FD4() \
    extern int func_80155FF8(int arg, int a1); \
    int func_80155FD4(int arg, int a1) { \
        return func_80155FF8(arg, a1 | 0x20000); \
    }

#define DEFINE_func_801598BC() \
    extern int func_800167F0(int arg); \
    int func_801598BC(void) { \
        return (func_800167F0(4) & 0xFFFF) != 0; \
    }

#define DEFINE_func_80162414() \
    extern s32 func_800167F0(s32 a0); \
    s32 func_80162414(void) { \
        return (func_800167F0(4) & 0xffff) != 0; \
    }

#define DEFINE_func_80168640() \
    void func_80168640(s32 a0) { \
        *(s32 *)(a0 + 0x1C) = 0x20; \
        *(u16 *)(a0 + 0x12) = 0; \
        *(u16 *)(a0 + 0x10) = 0x80; \
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1; \
    }

#define DEFINE_func_8016F264() \
    extern s32 D_80126D50; \
    void func_8016F264(void) { \
        D_80126D50 &= 0xFEFFFFFF; \
    }

#define DEFINE_func_8016F2C8() \
    extern s32 D_80126D50; \
    void func_8016F2C8(void) { \
        D_80126D50 &= 0xFDFFFFFF; \
    }

#define DEFINE_func_8016F30C() \
    extern s32 D_80126D50; \
    void func_8016F30C(void) { \
        D_80126D50 &= 0xF7FFFFFF; \
    }

#define DEFINE_func_8016F350() \
    extern s32 D_80126D50; \
    void func_8016F350(void) { \
        D_80126D50 &= 0xEFFFFFFF; \
    }

#define DEFINE_func_8016F44C() \
    extern s32 func_80029178(s32 a0); \
    s32 func_8016F44C(s32 a0) { \
        return (func_80029178(a0 + 0x125) & 0xff) != 0; \
    }

#define DEFINE_func_8016F470() \
    extern void func_80029124(s32 a0, s32 a1); \
    void func_8016F470(s32 a0) { \
        func_80029124(a0 + 0x125, 0); \
    }

#define DEFINE_func_80171904() \
    extern s32 D_80126D50; \
    void func_80171904(s32 a0) { \
        D_80126D50 = a0 | (D_80126D50 & 0x7F000000); \
    }

#define DEFINE_func_80179DF8() \
    extern void func_80179B74(s16 *a0); \
    void func_80179DF8(void) { \
        s16 local; \
        local = 0; \
        func_80179B74(&local); \
    }

#define DEFINE_func_8012853C() \
    extern void func_80146074(void); \
    extern void func_80011C10(void); \
    void func_8012853C(void) { \
        func_80146074(); \
        func_80011C10(); \
    }

#define DEFINE_func_8012BD14() \
    extern void func_80013350(s32 a0, void *a1); \
    extern u8 D_80126B5C; \
    void func_8012BD14(s32 a0) { \
        func_80013350(a0 + 4, &D_80126B5C); \
    }

#define DEFINE_func_801375EC() \
    extern void func_80137614(s32 a0, s32 a1, s32 a2); \
    void func_801375EC(s32 a0, s16 a1) { \
        func_80137614(a0, a1, 0); \
    }

#define DEFINE_func_80138DB8() \
    extern s32 func_80014E80(s32 a0, s32 a1); \
    s16 func_80138DB8(s32 a0, u8 a1, s32 a2) { \
        return (s16)func_80014E80(a1, a2); \
    }

#define DEFINE_func_80139788() \
    extern void func_8001931C(void); \
    extern s16 D_8012752C; \
    void func_80139788(void) { \
        func_8001931C(); \
        D_8012752C = 0; \
    }

#define DEFINE_func_8013E814() \
    extern void func_800D24A0(s32 arg); \
    extern void func_8013E6AC(void); \
    void func_8013E814(void) { \
        func_800D24A0(0); \
        func_8013E6AC(); \
    }

#define DEFINE_func_80144A04() \
    extern void func_80144A04(s32 *a0); \
    void func_80144A04(s32 *a0) { \
        void (*fp)(void); \
        fp = (void (*)(void))*(s32 *)((s32)a0 + 0xDC); \
        fp(); \
    }

#define DEFINE_func_80144AEC() \
    extern void func_80144B14(void); \
    void func_80144AEC(s32 *a0) { \
        s32 old; \
        old = *(s32 *)((s32)a0 + 0xDC); \
        *(s32 *)((s32)a0 + 0xDC) = (s32)&func_80144B14; \
        *(s16 *)((s32)a0 + 0x0) = 0x83; \
        *(s16 *)((s32)a0 + 0x2) = 1; \
        *(s32 *)((s32)a0 + 0xCC) = old; \
    }

#define DEFINE_func_801474EC() \
    void func_801474EC(s32 *a0) { \
        *(s16 *)((s32)a0 + 0x11C) = 0; \
        *(s16 *)((s32)a0 + 0x11A) = 0; \
        *(s16 *)((s32)a0 + 0x118) = 0; \
        *(s16 *)((s32)a0 + 0x124) = 0; \
        *(s16 *)((s32)a0 + 0x122) = 0; \
        *(s16 *)((s32)a0 + 0x120) = 0; \
        *(s16 *)((s32)a0 + 0x12C) = 0; \
        *(s16 *)((s32)a0 + 0x12A) = 0; \
        *(s16 *)((s32)a0 + 0x128) = 0; \
    }

#define DEFINE_func_80147A84() \
    extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    void func_80147A84(s32 arg0) { \
        func_80147AD4(arg0, 0, 0, 0); \
    }

#define DEFINE_func_80147AAC() \
    extern void func_80147C30(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    void func_80147AAC(s32 arg0) { \
        func_80147C30(arg0, 0, 0, 0); \
    }

#define DEFINE_func_80147F50() \
    extern void func_80147F78(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    void func_80147F50(s32 arg0) { \
        func_80147F78(arg0, 0, 0, 0); \
    }

#define DEFINE_func_8014ACC0() \
    void func_8014ACC0(s32 a0, s32 a1) { \
        s16 v0; \
        v0 = *(u16 *)((s32)a0 + 0x1C8) - a1; \
        *(s16 *)((s32)a0 + 0x1C8) = v0; \
        if (v0 < 0) { \
            *(s16 *)((s32)a0 + 0x1C8) = 0; \
        } \
    }

#define DEFINE_func_8014B00C() \
    extern void func_8014B034(s32 arg0); \
    void func_8014B00C(s32 arg0) { \
        func_8014B034(arg0 * 60); \
    }

#define DEFINE_func_80153BF0() \
    extern s32 D_801151FC; \
    extern s32 D_80127518; \
    s32 func_80153BF0(s32 a0) { \
        if (a0 == D_801151FC) { \
            D_80127518 = 0; \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8015410C() \
    extern void func_80151664(void); \
    extern s32 D_80127518; \
    void func_8015410C(void) { \
        D_80127518 = 0; \
        func_80151664(); \
    }

#define DEFINE_func_801627C0() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s32 D_8011F750; \
    void func_801627C0(void) { \
        func_80016714(&D_8011F750, 0x58); \
    }

#define DEFINE_func_80162AF4() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s32 D_8011F9D0; \
    void func_80162AF4(void) { \
        func_80016714(&D_8011F9D0, 0x820); \
    }

#define DEFINE_func_80163234() \
    extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_80163234(s32 a0) { \
        func_8016325C(a0, 0, 0, 0); \
    }

#define DEFINE_func_80165C78() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s32 D_8011D030; \
    void func_80165C78(void) { \
        func_80016714(&D_8011D030, 0xA50); \
    }

#define DEFINE_func_8016E8F0() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s32 D_80115218; \
    void func_8016E8F0(void) { \
        func_80016714(&D_80115218, 0x80); \
    }

#define DEFINE_func_80171238() \
    extern void func_801718AC(void *a0); \
    extern void *D_8011F738; \
    void func_80171238(void) { \
        func_801718AC(D_8011F738); \
    }

#define DEFINE_func_80171884() \
    extern void func_80171928(void *a0); \
    extern s32 D_80126B58; \
    void func_80171884(void) { \
        func_80171928(&D_80126B58); \
    }

#define DEFINE_func_80172710() \
    extern void (*D_80127088)(void); \
    void func_80172710(void) { \
        D_80127088(); \
    }

#define DEFINE_func_80172ED4() \
    extern void func_8017303C(void *); \
    extern u8 D_800D59EC[]; \
    void func_80172ED4(void) { \
        func_8017303C(D_800D59EC); \
    }

#define DEFINE_func_80172EFC() \
    extern void func_8017303C(void *); \
    extern u8 D_800D599C[]; \
    void func_80172EFC(void) { \
        func_8017303C(D_800D599C); \
    }

#define DEFINE_func_80172F24() \
    extern void func_8017303C(void *); \
    extern u8 D_800D5934[]; \
    void func_80172F24(void) { \
        func_8017303C(D_800D5934); \
    }

#define DEFINE_func_8017329C() \
    extern void func_80174684(void *); \
    extern void func_801732C4(); \
    void func_8017329C(void) { \
        func_80174684(func_801732C4); \
    }

#define DEFINE_func_801732F4() \
    extern void func_80174684(void *); \
    extern void func_8017331C(); \
    void func_801732F4(void) { \
        func_80174684(func_8017331C); \
    }

#define DEFINE_func_8017334C() \
    extern void func_80174684(void *); \
    extern void func_80173374(); \
    void func_8017334C(void) { \
        func_80174684(func_80173374); \
    }

#define DEFINE_func_801733A4() \
    extern void func_80174684(void *); \
    extern void func_8017331C(); \
    void func_801733A4(void) { \
        func_80174684(func_8017331C); \
    }

#define DEFINE_func_8017452C() \
    extern void func_80174684(void *); \
    extern void func_80174554(); \
    void func_8017452C(void) { \
        func_80174684(func_80174554); \
    }

#define DEFINE_func_80174584() \
    extern void func_80174684(void *); \
    extern void func_801745AC(); \
    void func_80174584(void) { \
        func_80174684(func_801745AC); \
    }

#define DEFINE_func_801745DC() \
    extern void func_80174604(void); \
    extern void func_80174684(void *); \
    void func_801745DC(void) { \
        func_80174684(func_80174604); \
    }

#define DEFINE_func_80175668() \
    extern short D_800B9A02; \
    extern void func_801757E0(int); \
    void func_80175668(void) { \
        func_801757E0(D_800B9A02); \
    }

#define DEFINE_func_80179F44() \
    extern void func_80179B74(short *); \
    void func_80179F44(void) { \
        short sp10; \
        sp10 = 0x18; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A0F4() \
    extern void func_80179B74(short *); \
    void func_8017A0F4(void) { \
        short sp10; \
        sp10 = 0x7; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A11C() \
    extern void func_80179B74(short *); \
    void func_8017A11C(void) { \
        short sp10; \
        sp10 = 0x8; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A180() \
    extern void func_80179B74(short *); \
    void func_8017A180(void) { \
        short sp10; \
        sp10 = 0x9; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A1A8() \
    extern void func_80179B74(short *); \
    void func_8017A1A8(void) { \
        short sp10; \
        sp10 = 0xA; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A1D0() \
    extern void func_80179B74(short *); \
    void func_8017A1D0(void) { \
        short sp10; \
        sp10 = 0xB; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A1F8() \
    extern void func_80179B74(short *); \
    void func_8017A1F8(void) { \
        short sp10; \
        sp10 = 0xC; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A298() \
    extern void func_80179B74(short *); \
    void func_8017A298(void) { \
        short sp10; \
        sp10 = 0xE; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A2C0() \
    extern void func_80179B74(short *); \
    void func_8017A2C0(void) { \
        short sp10; \
        sp10 = 0xF; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A2E8() \
    extern void func_80179B74(short *); \
    void func_8017A2E8(void) { \
        short sp10; \
        sp10 = 0x10; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A310() \
    extern void func_80179B74(short *); \
    void func_8017A310(void) { \
        short sp10; \
        sp10 = 0x11; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A338() \
    extern void func_80179B74(short *); \
    void func_8017A338(void) { \
        short sp10; \
        sp10 = 0x19; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A360() \
    extern void func_80179B74(short *); \
    void func_8017A360(void) { \
        short sp10; \
        sp10 = 0x1E; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8017A388() \
    extern void func_80179B74(short *); \
    void func_8017A388(void) { \
        short sp10; \
        sp10 = 0x1A; \
        func_80179B74(&sp10); \
    }

#define DEFINE_func_8012B14C() \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    void func_8012B14C(s32 a0, s32 a1) { \
        func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, a1, (s32)a0 + 0x10); \
    }

#define DEFINE_func_8012BF7C() \
    extern s16 D_80126CB0; \
    s32 func_8012BF7C(s16 *a0) { \
        s32 diff; \
        diff = a0[7] - D_80126CB0; \
        if (diff < 0) { \
            diff = -diff; \
        } \
        return diff >= 0x360; \
    }

#define DEFINE_func_8012C724() \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    void func_8012C724(s32 a0, s32 a1) { \
        *(u16 *)((s32)a0 + 0xA) |= 0x8000; \
        func_8012C890(a0, a1, 0); \
    }

#define DEFINE_func_8013E298() \
    extern s16 D_80126CB0; \
    s32 func_8013E298(s16 *a0) { \
        s32 diff; \
        diff = a0[2] - D_80126CB0; \
        if (diff < 0) { \
            diff = -diff; \
        } \
        return (u32)(diff - 0x2C1) < 0x3F; \
    }

#define DEFINE_func_80143994() \
    extern s32 func_8012C658(s32 a0, s32 a1, s32 a2); \
    void func_80143994(s32 a0, s32 a1) { \
        func_8012C658(0x1B, (s16)a1, a0); \
    }

#define DEFINE_func_801477E8() \
    void func_801477E8(s32 *a0, s32 a1) { \
        a0[0xD] = a1; \
        if (a1 < -0x1F0000) { \
            a0[0xD] = -0x1F0000; \
        } else if (a1 > 0x1F0000) { \
            a0[0xD] = 0x1F0000; \
        } \
    }

#define DEFINE_func_80149AA8() \
    s32 func_80149AA8(s32 *a0) { \
        s32 v0; \
        if (a0[0x44 / 4] & 0x404) { \
            v0 = 0; \
        } else { \
            v0 = *(u16 *)((s32)a0 + 0xAC) & 0x80; \
            v0 = v0 != 0; \
        } \
        return v0; \
    }

#define DEFINE_func_8014B310() \
    extern void func_8014B33C(void); \
    extern s32 D_80078ECC; \
    void func_8014B310(void) { \
        func_8014B33C(); \
        D_80078ECC = 0x80000000; \
    }

#define DEFINE_func_8014C3A4() \
    extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5); \
    s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3) { \
        return func_8014C43C(a0, a1, a2, a3, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)); \
    }

#define DEFINE_func_8014CB2C() \
    extern u8 D_80126D1F; \
    s32 func_8014CB2C(void) { \
        s32 v1 = D_80126D1F; \
        if (v1 & 0x80) { \
            v1 = (v1 & 0x7F) | 0x80000000; \
        } \
        return v1; \
    }

#define DEFINE_func_80154AB4() \
    void func_80154AB4(s32 a0, s32 a1) { \
        s32 *base = *(s32 **)(a0 + 0xCC); \
        s32 v1 = base[a1]; \
        *(s16 *)(a0 + 0xD6) = 1; \
        *(s16 *)(a0 + 0xD4) = 1; \
        *(s8 *)(a0 + 0xD8) = 0; \
        *(s8 *)(a0 + 0xD9) = 0; \
        *(s32 *)(a0 + 0xD0) = v1; \
    }

#define DEFINE_func_80154B20() \
    void func_80154B20(s32 a0, s32 a1, s32 a2) { \
        s32 *base = *(s32 **)(a0 + 0xCC); \
        s32 v1 = base[a1]; \
        *(s16 *)(a0 + 0xD6) = 1; \
        *(s16 *)(a0 + 0xD4) = 1; \
        *(s8 *)(a0 + 0xD8) = a2; \
        *(s8 *)(a0 + 0xD9) = a2; \
        *(s32 *)(a0 + 0xD0) = v1; \
    }

#define DEFINE_func_801607B8() \
    extern void func_80149048(s32 *a0); \
    void func_801607B8(s32 *a0) { \
        a0[0x11] &= ~1; \
        func_80149048(a0); \
    }

#define DEFINE_func_801619A4() \
    extern u8 D_80078EC0; \
    s32 func_801619A4(s32 *a0) { \
        if (*(s16 *)((s32)a0 + 0x1C8) == 0) { \
            return 0; \
        } \
        return D_80078EC0 & 0x7F; \
    }

#define DEFINE_func_8016DA04() \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    s32 func_8016DA04(s32 a0) { \
        return func_80146994(0x31, a0, 0, 0); \
    }

#define DEFINE_func_8016FB50() \
    extern void func_80171928(void *a0); \
    void func_8016FB50(void *a0) { \
        s32 v1 = *(s32 *)((s32)a0 + 0x20); \
        u16 v0 = *(u16 *)((s32)a0 + 0x132); \
        *(s16 *)((s32)a0 + 0x136) = 0; \
        *(s16 *)(v1 + 0x12) = v0; \
        func_80171928(a0); \
    }

#define DEFINE_func_8016FC64() \
    extern void func_80171928(void *a0); \
    void func_8016FC64(void *a0) { \
        s32 v1 = *(s32 *)((s32)a0 + 0x20); \
        u16 v0 = *(u16 *)((s32)a0 + 0x132); \
        *(s16 *)((s32)a0 + 0x136) = 0; \
        *(s16 *)(v1 + 0x12) = v0; \
        func_80171928(a0); \
    }

#define DEFINE_func_8017051C() \
    extern u16 D_800AE6DC; \
    extern void func_80171928(void *a0); \
    void func_8017051C(void *a0) { \
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = D_800AE6DC; \
        func_80171928(a0); \
    }

#define DEFINE_func_80174604() \
    extern s32 D_801150F8; \
    extern void func_80174630(void); \
    void func_80174604(void) { \
        D_801150F8 = 1; \
        func_80174630(); \
    }

#define DEFINE_func_80179DCC() \
    extern void func_80179B74(short *); \
    void func_80179DCC(short a0) { \
        short sp10[2]; \
        sp10[1] = a0; \
        sp10[0] = 2; \
        func_80179B74(sp10); \
    }

#define DEFINE_func_80179E1C() \
    extern void func_80179B74(short *); \
    void func_80179E1C(short a0) { \
        short sp10[2]; \
        sp10[1] = a0; \
        sp10[0] = 3; \
        func_80179B74(sp10); \
    }

#define DEFINE_func_80179EE8() \
    extern void func_80179B74(short *p); \
    void func_80179EE8(short a0) { \
        short sp[2]; \
        sp[1] = a0; \
        sp[0] = 0x12; \
        func_80179B74(sp); \
    }

#define DEFINE_func_80179F6C() \
    extern void func_80179B74(short *p); \
    void func_80179F6C(short a0) { \
        short sp[2]; \
        sp[1] = a0; \
        sp[0] = 0x14; \
        func_80179B74(sp); \
    }

#define DEFINE_func_801391F0() \
    extern void func_80139634(void *); \
    extern void func_80139DC8(void); \
    void func_801391F0(void *a0) { \
        *(s16 *)((s32)a0 + 0x12) = 0; \
        *(s16 *)((s32)a0 + 0x14) = 0; \
        *(s16 *)((s32)a0 + 0x16) = 0; \
        func_80139634(a0); \
        func_80139DC8(); \
    }

#define DEFINE_func_8013E558() \
    extern void func_800D24A0(s32 a0); \
    extern void func_80141788(void); \
    extern void *D_8011DB24; \
    void func_8013E558(void) { \
        func_800D24A0(2); \
        D_8011DB24 = (void *)func_80141788; \
    }

#define DEFINE_func_8013E67C() \
    extern void func_800D24A0(s32 a0); \
    extern void func_8013E5E8(void); \
    extern void *D_8011DB24; \
    void func_8013E67C(void) { \
        func_800D24A0(0); \
        D_8011DB24 = (void *)func_8013E5E8; \
    }

#define DEFINE_func_801496D4() \
    s32 func_801496D4(void *a0) { \
        s32 v0 = 0; \
        if (*(s32 *)((s32)a0 + 0x178)) { \
            return v0; \
        } \
        v0 = *(u16 *)((s32)a0 + 0xAC) & 0x40; \
        if (v0) { \
            v0 = 1; \
        } \
        return v0; \
    }

#define DEFINE_func_8014B4D4() \
    extern void func_80166244(); \
    extern s32 D_80078E98; \
    void func_8014B4D4(void *a0) { \
        *(u16 *)((s32)a0 + 0x1C8) = 0; \
        D_80078E98 = 0x80000000; \
        func_80166244(); \
    }

#define DEFINE_func_8014BD98() \
    extern u16 D_80078EB6; \
    extern s16 D_80078EB8; \
    void func_8014BD98(s32 a0, u16 a1) { \
        D_80078EB8 = a1; \
        if (D_80078EB6 < a1) { \
            D_80078EB8 = D_80078EB6; \
        } \
    }

#define DEFINE_func_8014BF18() \
    extern void func_800291A0(s32, s32); \
    void func_8014BF18(s32 a0) { \
        if (a0 < 0) { \
            a0 = 0; \
        } \
        func_800291A0(0xCF, a0 & 0xFF); \
    }

#define DEFINE_func_8014CBF8() \
    void func_8014CBF8(void *a0) { \
        s32 v1 = *(s32 *)((s32)a0 + 0x174); \
        if (v1 != 0) { \
            if (*(u16 *)(v1 + 0) != 0) { \
                *(s32 *)((s32)a0 + 0x174) = 0; \
                *(s8 *)(v1 + 0x74) = 0; \
            } \
        } \
    }

#define DEFINE_func_80154274() \
    extern void func_801542A4(); \
    void func_80154274(s32 *a0, s32 a1) { \
        if (*(s32 *)((s32)a0 + 0xB4) != a1) { \
            func_801542A4(); \
        } \
    }

#define DEFINE_func_801542DC() \
    extern void func_8015430C(); \
    void func_801542DC(s32 *a0, s32 a1) { \
        if (*(s32 *)((s32)a0 + 0xB4) != a1) { \
            func_8015430C(); \
        } \
    }

#define DEFINE_func_80159404() \
    s32 func_80159404(s32 a0, s32 a1) { \
        s32 a2 = *(s32 *)((s32)a0 + 0x20); \
        u16 v1 = *(u16 *)((s32)a0 + 0x236); \
        u16 v0 = *(u16 *)((s32)a2 + 0x12); \
        *(u16 *)((s32)a2 + 0x12) = (v0 + v1) & 0xFFF; \
        return (*(s32 *)((s32)a0 + 0x234) -= a1); \
    }

#define DEFINE_func_80159434() \
    s32 func_80159434(s32 a0, s32 a1) { \
        s32 a2 = *(s32 *)((s32)a0 + 0x20); \
        u16 v1 = *(u16 *)((s32)a0 + 0x23A); \
        u16 v0 = *(u16 *)((s32)a2 + 0x10); \
        *(u16 *)((s32)a2 + 0x10) = (v0 - v1) & 0xFFF; \
        return (*(s32 *)((s32)a0 + 0x238) += a1); \
    }

#define DEFINE_func_8016004C() \
    extern u8 D_800B9A17; \
    void func_8016004C(s32 a0) { \
        *(s32 *)((s32)a0 + 0x184) = 0; \
        *(s16 *)((s32)a0 + 0x18A) = 0; \
        *(s16 *)((s32)a0 + 0x188) = 0; \
        *(s32 *)((s32)a0 + 0x44) &= ~0x10; \
        D_800B9A17 = 1; \
    }

#define DEFINE_func_801619D0() \
    extern u8 D_80078EC0; \
    s32 func_801619D0(void *a0) { \
        s32 v0; \
        if (*(s16 *)((s32)a0 + 0x1C8) == 0) { \
            v0 = 0; \
        } else { \
            v0 = ((D_80078EC0 & 0x7F) ^ 3) == 0; \
        } \
        return v0; \
    }

#define DEFINE_func_80161D58() \
    extern void func_80161E08(s32); \
    extern s32 func_80162438(s32); \
    s32 func_80161D58(s32 a0) { \
        func_80161E08(a0); \
        return func_80162438(a0); \
    }

#define DEFINE_func_80165770() \
    extern u8 D_80078EC1; \
    extern void func_800CAF6C(void); \
    void func_80165770(void) { \
        if (D_80078EC1 == 0xC) { \
            func_800CAF6C(); \
        } \
    }

#define DEFINE_func_80165A20() \
    extern void func_80165A78(s32); \
    extern s32 func_80165A50(s32); \
    s32 func_80165A20(s32 a0) { \
        func_80165A78(a0); \
        return func_80165A50(a0); \
    }

#define DEFINE_func_8016A05C() \
    extern u8 D_80078EC0; \
    void func_8016A05C(void *a0) { \
        s32 v0; \
        if (D_80078EC0 & 0x7F) { \
            v0 = *(u16 *)((s32)a0 + 2) + 1; \
        } else { \
            v0 = 2; \
        } \
        *(s16 *)((s32)a0 + 2) = v0; \
    }

#define DEFINE_func_8016ED8C() \
    extern s32 D_80126D70; \
    extern void func_8016EDEC(s32 a0, s32 a1, s32 a2); \
    void func_8016ED8C(s32 a0, s32 a1, s32 a2) { \
        func_8016EDEC(a0, a1, a2); \
        D_80126D70 = a2; \
    }

#define DEFINE_func_8016EDBC() \
    extern s32 D_80126D70; \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    void func_8016EDBC(s32 a0, s32 a1, s32 a2) { \
        func_8016EE40(a0, a1, a2); \
        D_80126D70 = a2; \
    }

#define DEFINE_func_8016F494() \
    extern void func_80175414(s32); \
    extern s32 func_8016F4C4(s32); \
    s32 func_8016F494(s32 a0) { \
        func_80175414(a0); \
        return func_8016F4C4(a0); \
    }

#define DEFINE_func_8016F804() \
    extern void func_80171928(void *); \
    void func_8016F804(void *a0) { \
        if (*(u8 *)((s32)a0 + 0x1C2) != 0) { \
            *(u8 *)((s32)a0 + 0x1C2) = 0; \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_8012A5F8() \
    extern void func_8012A62C(s32); \
    void func_8012A5F8(void (*a0)(void), s32 a1) { \
        func_8012A62C(a1 & 0xFF); \
        a0(); \
    }

#define DEFINE_func_801392C8() \
    extern void func_801395D4(void *); \
    void func_801392C8(void *a0) { \
        func_801395D4(a0); \
        *(s8 *)((s32)a0 + 0x1E) = 0; \
        *(s16 *)((s32)a0 + 0x4) = 5; \
    }

#define DEFINE_func_801417C4() \
    extern void func_8001903C(void); \
    extern u16 D_80115112; \
    void func_801417C4(void) { \
        u16 *p = &D_80115112; \
        func_8001903C(); \
        *p = *p + 1; \
    }

#define DEFINE_func_8014C59C() \
    extern s32 ratan2(s32 dx, s32 dy); \
    s32 func_8014C59C(void *a0, void *a1) { \
        s32 dx = *(s16 *)((s32)a0 + 0x6) - *(s16 *)((s32)a1 + 0x6); \
        s32 dy = *(s16 *)((s32)a0 + 0xE) - *(s16 *)((s32)a1 + 0xE); \
        return ratan2(dx, dy) & 0xFFF; \
    }

#define DEFINE_func_80151238() \
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
    void func_80151238(void *a0) { \
        s16 v0 = *(s16 *)((s32)a0 + 0xF2); \
        if (v0 != 0) { \
            func_8014ACE8(a0, 5, (s32)v0 & 0x7FFF); \
        } \
    }

#define DEFINE_func_80154418() \
    extern void func_8015444C(void *a0, s32 *a1, s32 *a2, s32 *a3); \
    void func_80154418(void *a0) { \
        s32 sp10 = 0; \
        s32 sp14 = 0; \
        s32 sp18 = 0; \
        func_8015444C(a0, &sp10, &sp14, &sp18); \
    }

#define DEFINE_func_8015DC84() \
    extern void func_80154A74(int, int); \
    extern int func_8015DD74(int); \
    int func_8015DC84(int a0) { \
        func_80154A74(a0, 0x11); \
        return func_8015DD74(a0); \
    }

#define DEFINE_func_8015DFE4() \
    extern void func_80154A74(int, int); \
    extern int func_8015E0D4(int); \
    int func_8015DFE4(int a0) { \
        func_80154A74(a0, 0x11); \
        return func_8015E0D4(a0); \
    }

#define DEFINE_func_8015ED6C() \
    extern u8 D_80078EBF; \
    extern void func_80149048(s32 *a0); \
    void func_8015ED6C(s32 *a0) { \
        D_80078EBF = 0; \
        *(s32 *)((s32)a0 + 0x44) &= -2; \
        func_80149048(a0); \
    }

#define DEFINE_func_80162FC0() \
    void func_80162FC0(s32 *a0) { \
        a0[1] += a0[4]; \
        a0[2] += a0[5]; \
        a0[3] += a0[6]; \
    }

#define DEFINE_func_80165840() \
    extern u8 D_80078EC3; \
    extern void func_80165874(void); \
    void func_80165840(void) { \
        if (D_80078EC3 != 0) { \
            D_80078EC3 = 0; \
            func_80165874(); \
        } \
    }

#define DEFINE_func_80170B14() \
    extern void func_801719A4(int a0, int a1); \
    extern void func_80170B48(int a0); \
    void func_80170B14(int a0) { \
        func_801719A4(a0, 1); \
        func_80170B48(a0); \
    }

#define DEFINE_func_80171B10() \
    extern s32 func_8014C568(void *a0); \
    void func_80171B10(void *a0) { \
        s32 ret = func_8014C568(a0); \
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = ret; \
    }

#define DEFINE_func_8012A79C() \
    extern s32 ratan2(s32 a0, s32 a1); \
    s16 func_8012A79C(s16 *a0, s16 *a1) { \
        s16 x0 = a0[0]; \
        s16 x1 = a1[0]; \
        s16 y0 = a0[2]; \
        s16 y1 = a1[2]; \
        return ratan2(x0 - x1, y0 - y1); \
    }

#define DEFINE_func_8012B6D4() \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012B6D4(s16 *a0, s16 *a1) { \
        s16 ax = a0[5]; \
        s16 bx = a1[5]; \
        s16 by = a1[1]; \
        s16 ay = a0[1]; \
        return (ratan2(ax - bx, by - ay) - 0x400) & 0xFFF; \
    }

#define DEFINE_func_8012B70C() \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012B70C(s16 *a0, s16 *a1) { \
        s16 ax = a0[2]; \
        s16 bx = a1[2]; \
        s16 by = a1[0]; \
        s16 ay = a0[0]; \
        return (ratan2(ax - bx, by - ay) - 0x400) & 0xFFF; \
    }

#define DEFINE_func_8012B744() \
    extern s32 ratan2(s32 x, s32 y); \
    s32 func_8012B744(void *a0, void *a1) { \
        s32 ang; \
        ang = ratan2(*(s16 *)((s32)a0 + 0xA) - *(s16 *)((s32)a1 + 0x4), \
                     *(s16 *)((s32)a1 + 0x0) - *(s16 *)((s32)a0 + 0x2)); \
        return (ang - 0x400) & 0xFFF; \
    }

#define DEFINE_func_8012E32C() \
    extern u8 D_800AF648; \
    extern void func_8004914C(void *a0); \
    extern void func_800491AC(void *a0); \
    void func_8012E32C(void) { \
        func_8004914C(&D_800AF648); \
        func_800491AC(&D_800AF648); \
    }

#define DEFINE_func_801484B0() \
    extern void func_801485B8(s32 a0, s32 a1, s32 a2); \
    extern s32 *D_80126B78; \
    void func_801484B0(s32 a0, s32 a1) { \
        func_801485B8(*(s32 *)((s32)D_80126B78 + 0x20) - 0x10, a0, a1); \
    }

#define DEFINE_func_80148534() \
    extern void func_801485B8(s32 a0, s32 a1, s32 a2); \
    extern s32 *D_80126B78; \
    void func_80148534(s32 a0, s32 a1) { \
        func_801485B8(*(s32 *)((s32)D_80126B78 + 0x20) - 0x8, a0, a1); \
    }

#define DEFINE_func_8014ADA8() \
    extern s32 D_80078E8C; \
    void func_8014ADA8(s32 a0, s32 a1) { \
        s32 v0; \
        v0 = D_80078E8C + a1; \
        D_80078E8C = v0; \
        if (0x1869F < (u32)v0) { \
            D_80078E8C = 0x1869F; \
        } \
    }

#define DEFINE_func_8014BEC0() \
    extern void func_80029124(s32 a0, s32 a1); \
    extern u8 D_80078EC0; \
    void func_8014BEC0(void) { \
        D_80078EC0 |= 1; \
        func_80029124(0x80, 1); \
    }

#define DEFINE_func_801599E0() \
    extern void func_80159A20(void *a0); \
    void func_801599E0(void *a0) { \
        func_80159A20(a0); \
        *(u8 *)((s32)a0 + 0x4D) += 1; \
    }

#define DEFINE_func_80161240() \
    extern s32 func_801612B8(void *a0, s32 a1); \
    extern void func_8016130C(void *a0, s32 a1); \
    void func_80161240(void *a0) { \
        func_8016130C(a0, func_801612B8(a0, 1)); \
    }

#define DEFINE_func_80161418() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_8016163C(void *a0, s32 a1); \
    void func_80161418(void *a0) { \
        func_8016163C(a0, func_801615C4(a0, 0)); \
    }

#define DEFINE_func_80161450() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_80161774(void *a0, s32 a1); \
    void func_80161450(void *a0) { \
        func_80161774(a0, func_801615C4(a0, 0)); \
    }

#define DEFINE_func_801614E4() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_80161888(void *a0, s32 a1); \
    void func_801614E4(void *a0) { \
        func_80161888(a0, func_801615C4(a0, 0)); \
    }

#define DEFINE_func_8016151C() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_8016191C(void *a0, s32 a1); \
    void func_8016151C(void *a0) { \
        func_8016191C(a0, func_801615C4(a0, 0)); \
    }

#define DEFINE_func_80161554() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_8016163C(void *a0, s32 a1); \
    void func_80161554(void *a0) { \
        func_8016163C(a0, func_801615C4(a0, 1)); \
    }

#define DEFINE_func_8016158C() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_80161774(void *a0, s32 a1); \
    void func_8016158C(void *a0) { \
        func_80161774(a0, func_801615C4(a0, 1)); \
    }

#define DEFINE_func_801657A0() \
    extern void func_801657D8(void); \
    extern u8 D_80078EC3; \
    void func_801657A0(void) { \
        if (D_80078EC3 == 0) { \
            D_80078EC3 = 1; \
            func_801657D8(); \
        } \
    }

#define DEFINE_func_80173A28() \
    extern s32 D_8012750C; \
    extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4); \
    void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) { \
        func_80173A60(a0, a1, a2, a3, a4); \
        D_8012750C = a5; \
    }

#define DEFINE_func_80174BBC() \
    void func_80174BBC(void *a0) { \
        *(s32 *)((s32)a0 + 0xC) = 0x12C; \
        *(s32 *)((s32)a0 + 0x14) = 0x12C; \
        *(s16 *)((s32)a0 + 0x20) = 0x155; \
        *(s16 *)((s32)a0 + 0x22) = 0x800; \
        *(s16 *)((s32)a0 + 0x24) = 0; \
        *(s16 *)((s32)a0 + 0x2E) = 0; \
        *(s16 *)((s32)a0 + 0x30) = -0x28; \
        *(s16 *)((s32)a0 + 0x32) = 0; \
        *(s32 *)((s32)a0 + 0x54) = 0; \
    }

#define DEFINE_func_80177784() \
    void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3) { \
        *(u32 *)((s32)a0 + 0x0) = (((s32)a0 - 0x14) & 0xFFFFFF) | 0x3000000; \
        *(u32 *)((s32)a0 + 0x4) = 0x74808080; \
        *(s32 *)((s32)a0 + 0x8) = a1; \
        *(s32 *)((s32)a0 + 0xC) = a2; \
        return (void *)((s32)a0 + 0x14); \
    }

#define DEFINE_func_801466B4() \
    void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5) { \
        func_801466F0(a0, a1, 0, 0, 0, a2, a3, arg5); \
    }

#define DEFINE_func_8014A638() \
    void func_8014A638(s32 arg0) { \
        s16 v; \
        if (*(s32 *)((s32)arg0 + 0x44) & 0x10) { \
            v = *(u16 *)((s32)arg0 + 0x188) - 4; \
            *(s16 *)((s32)arg0 + 0x188) = v; \
            if (v < 0) { \
                *(s16 *)((s32)arg0 + 0x188) = 0; \
            } \
        } \
    }

#define DEFINE_func_8014B768() \
    extern s32 D_80078E9C; \
    void func_8014B768(s32 a0, s32 a1) { \
        D_80078E9C -= a1; \
        if (*(s16 *)((s32)&D_80078E9C + 2) < 0) { \
            D_80078E9C = 0; \
        } \
    }

#define DEFINE_func_8014BC44() \
    extern u16 D_80078EB2; \
    extern void func_8014BC80(s32 a0, s32 a1); \
    void func_8014BC44(s32 a0, s32 a1) { \
        if (*(s32 *)((s32)a0 + 0x44) & 0x2000000) { \
            a1 = D_80078EB2; \
        } \
        func_8014BC80(a0, a1); \
    }

#define DEFINE_func_8014C88C() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8014C8C8(s32 a0, s32 *a1); \
    void func_8014C88C(s32 a0) { \
        s32 sp10; \
        func_80015978(a0 + 4, &sp10); \
        func_8014C8C8(a0, &sp10); \
    }

#define DEFINE_func_80157A8C() \
    extern void func_80161D20(s32 a0, s32 a1); \
    extern void func_8014C010(s32 a0, s32 a1); \
    void func_80157A8C(s32 a0) { \
        func_80161D20(a0, *(u16 *)(a0 + 0x16E)); \
        func_8014C010(a0, 1); \
    }

#define DEFINE_func_80165694() \
    extern s32 D_80078EC8; \
    void func_80165694(s32 arg0) { \
        if (*(s32 *)((s32)arg0 + 0x1F8) & 0x80FFFFFF) { \
            return; \
        } \
        if (D_80078EC8 != 0) { \
            D_80078EC8 = D_80078EC8 - 1; \
        } \
    }

#define DEFINE_func_8012D624() \
    extern int func_8012D664(); \
    void func_8012D624(s32 a0) { \
        u16 sp[3]; \
        sp[0] = *(u16 *)(a0 + 0x6); \
        sp[1] = *(u16 *)(a0 + 0xA); \
        sp[2] = *(u16 *)(a0 + 0xE); \
        func_8012D664((void *)sp); \
    }

#define DEFINE_func_8015369C() \
    extern void (*D_8011DB28)(s32 a0); \
    void func_8015369C(s32 a0) { \
        if (D_8011DB28 != 0) { \
            D_8011DB28(a0 + 0xA0); \
        } \
        *(u8 *)(a0 + 0xDE) = 0x5A; \
    }

#define DEFINE_func_80154BE4() \
    void func_80154BE4(s32 a0) { \
        s32 sp10; \
        s32 sp14; \
        sp10 = 0; \
        sp14 = 0; \
        func_80154C24(a0, &sp10, &sp14); \
        func_80154F9C(a0); \
    }

#define DEFINE_func_8015987C() \
    extern void func_800167B8(s32 a0); \
    s32 func_8015987C(s32 a0) { \
        func_800167B8(4); \
        *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1; \
        return 0; \
    }

#define DEFINE_func_80178BB8() \
    void func_80178BB8(s32 a0, s32 a1) { \
        func_80178BF8(a0, a1); \
        func_80178CBC(a0, a1); \
    }

#define DEFINE_func_8012BE54() \
    extern void func_8012BE98(s32 a0, u16 *a1); \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    void func_8012BE54(s32 a0) { \
        u16 sp[3]; \
        sp[0] = D_80126B5E; \
        sp[1] = D_80126B62; \
        sp[2] = D_80126B66; \
        func_8012BE98(a0, sp); \
    }

#define DEFINE_func_8013A9B4() \
    extern void func_8013A9F8(s32 a0, s32 a1); \
    void func_8013A9B4(s32 a0, s32 a1) { \
        *(s16 *)(a1 + 0x2) = 0; \
        *(s32 *)(a1 + 0x4) = a0; \
        *(s32 *)(a0 + 0x40) = a1; \
        *(s16 *)(a1 + 0x0) = 1; \
        *(s16 *)(a1 + 0xC) = 0; \
        *(s16 *)(a1 + 0xE) = 0; \
        func_8013A9F8(a1, *(u16 *)(a0 + 0x18)); \
    }

#define DEFINE_func_80175624() \
    extern s16 D_800B9A02; \
    extern void func_801757A0(s32); \
    void func_80175624(void *a0) { \
        func_801757A0(D_800B9A02); \
        *((u8 *)a0 + 1) = *((u8 *)a0 + 1) + 1; \
    }

#define DEFINE_func_8014168C() \
    extern u8 D_80115148[]; \
    extern u8 D_80115149[]; \
    extern u8 D_80115158[]; \
    s16 func_8014168C(s16 a0) { \
        s32 i = a0 * 2; \
        return D_80115148[i] + D_80115149[i] * D_80115158[i]; \
    }

#define DEFINE_func_8012A048() \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    extern s16 D_80126940; \
    extern s16 D_80126942; \
    extern s16 D_80126944; \
    void func_8012A048(void *a0, s32 a1, u8 a2) { \
        *(s32 *)((s32)a0 + 0x0) = a1; \
        *(u8 *)((s32)a0 + 0x4) = a2; \
        *(s32 *)((s32)a0 + 0x9C) = 0; \
        *(s16 *)((s32)a0 + 0xA0) = 0; \
        *(s16 *)((s32)a0 + 0xA2) = 0; \
        D_80126940 = D_80126B5E; \
        D_80126942 = D_80126B62; \
        D_80126944 = D_80126B66; \
    }

#define DEFINE_func_80150E84() \
    extern void func_80150EC4(s32 a0, s32 a1); \
    void func_80150E84(s32 a0) { \
        func_80150EC4(a0, 0xE); \
    }

#define DEFINE_func_80150EA4() \
    extern void func_80150EC4(s32 a0, s32 a1); \
    void func_80150EA4(s32 a0) { \
        func_80150EC4(a0, 0xF); \
    }

#define DEFINE_func_8012CC64() \
    extern s32 func_8012CC88(); \
    void func_8012CC64(s32 a0, s32 a1) { \
        func_8012CC88(a0, 0x11, a1); \
    }

#define DEFINE_func_80143C74() \
    extern s32 func_8012C658(s32 a0, s32 a1, s32 a2); \
    void func_80143C74(s32 a0, s32 a1) { \
        func_8012C658(0x205, a1, a0); \
    }

#define DEFINE_func_8012BEE8() \
    s32 func_8012BEE8(s32 a0) { \
        s32 v0; \
        v0 = *(s32*)(a0 + 0x1C); \
        if (!v0) goto ret1; \
        *(s32*)(a0 + 0x1C) = v0 - 1; \
        return (u32)(v0 - 1) < 1; \
    ret1: \
        return 1; \
    }

#define DEFINE_func_80146E98() \
    s32 func_80146E98(s32 a0) { \
        s32 v0; \
        v0 = *(s32*)(a0 + 0x1C); \
        if (v0 != 0) { \
            v0 = v0 - 1; \
            *(s32*)(a0 + 0x1C) = v0; \
            return (u32)v0 < 1; \
        } \
        return 1; \
    }

#define DEFINE_func_8016197C() \
    s32 func_8016197C(s32 a0, s32 a1) { \
        s32 v0; \
        if (a1 & 1) { \
            v0 = 1; \
        } else if (a1 & 0x4000) { \
            v0 = 2; \
        } else { \
            v0 = ((u32)a1 >> 11) & 4; \
        } \
        return v0; \
    }

#define DEFINE_func_80171A88() \
    s32 func_80171A88(s32 a0) { \
        s32 v0; \
        v0 = *(s32*)(a0 + 0x200); \
        if (!v0) goto ret1; \
        *(s32*)(a0 + 0x200) = v0 - 1; \
        return (u32)(v0 - 1) < 1; \
    ret1: \
        return 1; \
    }

#define DEFINE_func_80130AC4() \
    void func_80130AC4(s32 a0) { \
        s16 v0; \
        v0 = *(u16*)(a0 + 0xAC) - 1; \
        *(u16*)(a0 + 0xAC) = v0; \
        if (v0 == 0) { \
            *(u8*)(a0 + 0xC1) = 0; \
            *(s16*)(a0 + 0x5E) = 0; \
        } \
    }

#define DEFINE_func_8013A9F8() \
    void func_8013A9F8(s32 a0, s32 a1) { \
        s32 orig = a1; \
        a1 -= 2; \
        a1 &= 0xFFFF; \
        if ((u32)a1 < 5) { \
            s32 b = orig & 0xFFFF; \
            b -= 2; \
            b <<= 10; \
            *(s16*)(a0 + 0xE) = b; \
        } \
    }

#define DEFINE_func_80131C78() \
    extern void func_80131CA8(s32 a0, s32 a1); \
    void func_80131C78(s32 a0) { \
        s32 v0 = *(s32*)(a0 + 0x20); \
        *(s8*)(a0 + 0xC1) = 0; \
        *(s16*)(v0 + 0x10) = 0; \
        *(s16*)(a0 + 0x5E) = 0; \
        func_80131CA8(a0, 0xE); \
    }

#define DEFINE_func_80161A00() \
    extern u8 D_80078EC0; \
    s32 func_80161A00(s32 a0) { \
        if (*(s16*)(a0 + 0x1C8) != 0) { \
            return ((D_80078EC0 & 0x7F) ^ 0x4) == 0; \
        } \
        return 0; \
    }

#define DEFINE_func_80161A30() \
    extern u8 D_80078EC0; \
    s32 func_80161A30(s32 a0) { \
        if (*(s16*)(a0 + 0x1C8) != 0) { \
            return ((D_80078EC0 & 0x7F) ^ 0x5) == 0; \
        } \
        return 0; \
    }

#define DEFINE_func_80161A60() \
    extern u8 D_80078EC0; \
    s32 func_80161A60(s32 a0) { \
        s32 v0; \
        if (*(s16*)(a0 + 0x1C8) != 0) { \
            v0 = ((D_80078EC0 & 0x7F) ^ 6) == 0; \
            return v0; \
        } \
        return 0; \
    }

#define DEFINE_func_8015A1C8() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015A1C8(s32 a0) { \
        func_801553C0(a0); \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_8015AC90() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015AC90(s32 a0) { \
        func_801553C0(a0); \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_8015CF24() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015CF24(s32 a0) { \
        func_801553C0(a0); \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_801284B8() \
    extern s32 func_800D0588(void); \
    extern void func_80015310(void); \
    extern void func_80011C10(void); \
    void func_801284B8(void) { \
        if (func_800D0588()) { \
            func_80015310(); \
            func_80011C10(); \
        } \
    }

#define DEFINE_func_8012C31C() \
    extern u8 D_80120194[]; \
    s32 func_8012C31C(void) { \
        s32 a0; \
        s32 v1; \
        a0 = (s32)D_80120194; \
        v1 = a0 + 0x6480; \
        if (v1 != a0) { \
            do { \
                if (*(u16 *)v1 == 0) { \
                    return v1; \
                } \
                v1 -= 0x10C; \
            } while (v1 != a0); \
        } \
        return 0; \
    }

#define DEFINE_func_8012E544() \
    extern u8 D_801202A0[]; \
    s32 func_8012E544(s32 a0) { \
        s32 a1; \
        s32 v1; \
        v1 = (s32)D_801202A0; \
        a1 = v1 + 0x6480; \
        if (v1 != a1) { \
            do { \
                if (*(u16 *)v1 == a0) { \
                    return v1; \
                } \
                v1 += 0x10C; \
            } while (v1 != a1); \
        } \
        return 0; \
    }

#define DEFINE_func_8013E410() \
    extern u8 D_801202A0[]; \
    s32 func_8013E410(void) { \
        s32 a0; \
        s32 v1; \
        v1 = (s32)D_801202A0; \
        for (a0 = 0; a0 < 0x60; a0++, v1 += 0x10C) { \
            if (*(u16 *)v1 == 0) { \
                return v1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8014BC0C() \
    extern u16 D_80078EB2; \
    void func_8014BC0C(s32 a0, s32 a1) { \
        D_80078EB2 += a1; \
        if ((u16)D_80078EB2 >= 0x1F5) { \
            D_80078EB2 = 0x1F4; \
        } \
    }

#define DEFINE_func_8014C278() \
    extern s32 func_80013328(s32 a0, s32 a1); \
    s32 func_8014C278(s32 a0, s32 a1, s32 a2) { \
        return func_80013328(a0 + 4, a1 + 4) < (s32)(a2 & 0xFFFF); \
    }

#define DEFINE_func_801632F0() \
    extern s32 D_80115200; \
    s32 func_801632F0(void) { \
        s32 i = 0; \
        s32 *p = &D_80115200; \
        s32 v0; \
        do { \
            v0 = p[0]; \
            if (v0 != 0) { \
                return v0; \
            } \
            i++; \
            p++; \
        } while (i < 3); \
        return 0; \
    }

#define DEFINE_func_8012B178() \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    void func_8012B178(s32 a0, s32 a1) { \
        s32 sp10[3]; \
        sp10[2] = a1; \
        sp10[1] = 0; \
        sp10[0] = 0; \
        func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp10, a0 + 0x10); \
    }

#define DEFINE_func_8012BF10() \
    s32 func_8012BF10(s32 a0, s32 a1) { \
        s32 v0; \
        v0 = *(s32*)(a0 + 0x1C); \
        if (v0 == 0) { \
            v0 = 1; \
        } else { \
            v0 -= 1; \
            *(s32*)(a0 + 0x1C) = v0; \
            v0 = (u32)v0 < 1; \
        } \
        if (v0 != 0) { \
            *(s32*)(a0 + 0x1C) = a1; \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8012C1DC() \
    extern u8 D_800B3DF0[]; \
    s32 func_8012C1DC(s32 a0) { \
        u8 *p; \
        u8 *end; \
        p = (u8 *)(*(s32 *)(a0 + 0x20) + 0x84); \
        end = D_800B3DF0; \
        if (p != end) { \
            do { \
                if (*(u16 *)p == 0) { \
                    return (s32)p; \
                } \
                p += 0x84; \
            } while (p != end); \
        } \
        return 0; \
    }

#define DEFINE_func_8012E4C8() \
    void func_8012E4C8(s32 a0) { \
        s32 v1; \
        s32 t; \
        v1 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(v1 + 0x1C) = 0x1000; \
        *(s16 *)(v1 + 0x18) = 0x1000; \
        *(s16 *)(a0 + 0x60) = 0; \
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 1; \
        t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12); \
        *(s16 *)(a0 + 0x5E) = 1; \
        *(s16 *)(a0 + 0x62) = t + 0x800; \
    }

#define DEFINE_func_8012EF34() \
    extern void func_8012EFB8(s32 a0); \
    void func_8012EF34(s32 a0, s32 a1) { \
        s32 sp10; \
        register s32 v1 __asm__("$3"); \
        func_8012EFB8(a0); \
        { \
            register s32 *p __asm__("$3") = &sp10; \
            __asm__ __volatile__("swc2 $19, 0(%0)" : : "r"(p) : "memory"); \
        } \
        v1 = sp10; \
        *(s16 *)(a1 + 4) = v1; \
    }

#define DEFINE_func_80149884() \
    extern s16 currentLocationId; \
    extern s32 func_8016F1AC(void); \
    s32 func_80149884(void) { \
        s32 ret; \
        if (currentLocationId == 0x308F) { \
            ret = 0; \
        } else { \
            ret = func_8016F1AC() == 0; \
        } \
        return ret; \
    }

#define DEFINE_func_80149CD4() \
    s32 func_80149CD4(s32 a0) { \
        s32 v0; \
        if (*(s32*)(a0 + 0x44) & 0x404) { \
            v0 = 0; \
        } else if (*(s16*)(a0 + 0x1C8) != 0) { \
            v0 = 0; \
        } else { \
            v0 = *(u16*)(a0 + 0xAA) & 8; \
            v0 = v0 != 0; \
        } \
        return v0; \
    }

#define DEFINE_func_80149D9C() \
    extern s32 func_80149E94(s32 a0); \
    extern s32 func_80149DD8(s32 a0); \
    s32 func_80149D9C(s32 a0) { \
        s32 v0; \
        if (func_80149E94(a0) != 0) { \
            v0 = 1; \
        } else { \
            v0 = func_80149DD8(a0) != 0; \
        } \
        return v0; \
    }

#define DEFINE_func_8016F410() \
    extern s32 func_8016F44C(s32 a0); \
    extern void func_8016F470(s32 a0); \
    s32 func_8016F410(s32 a0) { \
        if (func_8016F44C(a0) == 0) { \
            return 0; \
        } \
        func_8016F470(a0); \
        return 1; \
    }

#define DEFINE_func_801282EC() \
    extern void func_8001C0C8(void); \
    extern void func_80015310(void); \
    extern void func_80129258(void); \
    extern void func_801378F0(void); \
    extern void func_80010E14(void); \
    void func_801282EC(void) { \
        func_8001C0C8(); \
        func_80015310(); \
        func_80129258(); \
        func_801378F0(); \
        func_80010E14(); \
    }

#define DEFINE_func_8012B864() \
    extern s16 D_80126CB8; \
    extern s16 D_80126CB4; \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012B864(s32 a0) { \
        s32 dx = *(s16*)(a0 + 0xE) - D_80126CB8; \
        s32 dy = D_80126CB4 - *(s16*)(a0 + 0x6); \
        return (ratan2(dx, dy) - 0x400) & 0xFFF; \
    }

#define DEFINE_func_8012D5E4() \
    extern s16 D_80126B98; \
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2); \
    s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3) { \
        if (func_8012DEB8(a0, a1, a2) != 0) { \
            D_80126B98 = a3; \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8012E504() \
    extern u8 D_801202A0[]; \
    s32 func_8012E504(s32 a0, s32 a1) { \
        s32 p; \
        s32 end; \
        p = (s32)D_801202A0; \
        end = (s32)D_801202A0 + 0x6480; \
        for (; p != end; p += 0x10C) { \
            if (p != a0) { \
                if (*(u16*)p == a1) { \
                    return p; \
                } \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80130360() \
    extern void func_80131CA8(s32 a0, s32 a1); \
    void func_80130360(s32 a0) { \
        *(u8*)(a0 + 0xC1) = 2; \
        if (*(s32*)(a0 + 0xB4) & 2) { \
            *(s16*)(a0 + 0x5C) = 0; \
            *(s16*)(a0 + 0x98) = 0; \
            *(s32*)(a0 + 0x1C) = 0; \
        } \
        func_80131CA8(a0, 1); \
    }

#define DEFINE_func_80130858() \
    extern void func_8012AD80(s32 a0); \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_801319E0(s32 a0); \
    void func_80130858(s32 a0) { \
        func_8012AD80(a0); \
        if (func_8012BEE8(a0)) { \
            func_801319E0(a0); \
        } \
    }

#define DEFINE_func_8013A8BC() \
    extern u8 D_8011DA80[]; \
    s32 func_8013A8BC(void) { \
        s32 p; \
        s32 i; \
        p = (s32)D_8011DA80; \
        for (i = 0; i < 0x20; i += 0x10) { \
            if (*(s16*)((s32)D_8011DA80 + i) == 0) { \
                return p; \
            } \
            p += 0x10; \
        } \
        return 0; \
    }

#define DEFINE_func_80142414() \
    extern s32 func_8012C588(s32 a0, s32 a1); \
    void func_80142414(s32 a0, s16 a1) { \
        s32 v0; \
        v0 = func_8012C588(0x13, a0); \
        if (v0 != 0) { \
            *(s16*)(v0 + 0x52) = a1; \
        } \
    }

#define DEFINE_func_80144988() \
    void func_80144988(s32 a0) { \
        s32 t; \
        *(u16*)(a0 + 0xA) = *(u16*)(a0 + 0xA) - 0x40; \
        *(s32*)(a0 + 0x10) = *(s32*)(*(s32*)(a0 + 0x64) + 0x10); \
        *(s32*)(a0 + 0x14) = *(s32*)(*(s32*)(a0 + 0x64) + 0x14); \
        t = *(s32*)(*(s32*)(a0 + 0x64) + 0x18); \
        *(u16*)(a0 + 0x2) = *(u16*)(a0 + 0x2) + 1; \
        *(s32*)(a0 + 0x18) = t; \
    }

#define DEFINE_func_80149184() \
    extern s32 func_801491C4(s32 a0); \
    s32 func_80149184(s32 a0) { \
        s32 v0; \
        s32 v1; \
        v0 = func_801491C4(a0); \
        v1 = *(u16*)(*(s32*)(a0 + 0x20) + 0x12); \
        return (v1 - v0) & 0xFFF; \
    }

#define DEFINE_func_801491C4() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 D_801151D4; \
    s32 func_801491C4(s32 a0) { \
        s32 p; \
        s32 v0; \
        p = D_801151D4; \
        v0 = ratan2(*(s32*)(p + 0x3C) - *(s32*)(p + 0x48), *(s32*)(p + 0x44) - *(s32*)(p + 0x50)); \
        return (s16)v0; \
    }

#define DEFINE_func_801526D4() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_80152714(s32 a0); \
    void func_801526D4(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_80152714(a0); \
    }

#define DEFINE_func_801565C0() \
    extern s32 D_801151E0[]; \
    s32 func_801565C0(void) { \
        s32 result; \
        u32 i; \
        result = 0; \
        for (i = 0; i < 3; i++) { \
            if (D_801151E0[i] & 1) { \
                result |= 1; \
            } \
        } \
        return result; \
    }

#define DEFINE_func_80175454() \
    extern u8 D_8011F7A8; \
    extern u8 D_8011F7A9; \
    extern u8 D_8011F7AD; \
    extern u8 D_8011F7AE; \
    void func_80175454(void) { \
        u8 *p = &D_8011F7A8; \
        if (*p == 0) { \
            *p = 1; \
            D_8011F7A9 = 0; \
            D_8011F7AD = 0xA; \
            D_8011F7AE = 0; \
        } \
    }

#define DEFINE_func_801757A0() \
    extern void func_80175DA8(s32 a0); \
    extern void func_80175AB8(s32 a0); \
    extern void func_80176144(s32 a0); \
    void func_801757A0(s32 a0) { \
        s32 v = (s16)a0; \
        func_80175DA8(v); \
        func_80175AB8(v); \
        func_80176144(v); \
    }

#define DEFINE_func_801757E0() \
    extern void func_80176734(s32 a0); \
    extern void func_80176218(s32 a0); \
    extern void func_80176D00(s32 a0); \
    void func_801757E0(s32 a0) { \
        s32 v = (s16)a0; \
        func_80176734(v); \
        func_80176218(v); \
        func_80176D00(v); \
    }

#define DEFINE_func_801399F0() \
    s32 func_801399F0(s32 a0) { \
        s32 v1; \
        if (*(s32*)(a0 + 0x0) == 0) return -1; \
        v1 = *(s16*)(a0 + 0x4); \
        if (v1 == 0) return -1; \
        if (v1 == 0xE) return -1; \
        if (v1 == 0xD) return *(s8*)(a0 + 0x1F); \
        return 0; \
    }

#define DEFINE_func_80134A28() \
    s32 func_80134A28(s32 a0, s32 a1, s32 a2) { \
        return *(s16*)(a0 + 0x0) * *(s16*)(a1 + 0x0) \
             + *(s16*)(a0 + 0x2) * *(s16*)(a1 + 0x2) \
             + *(s16*)(a0 + 0x4) * *(s16*)(a1 + 0x4) \
             + a2; \
    }

#define DEFINE_func_80134FB8() \
    s32 func_80134FB8(s32 a0, s32 a1, s32 a2) { \
        return *(s16*)(a0 + 0x0) * *(s16*)(a1 + 0x0) \
             + *(s16*)(a0 + 0x2) * *(s16*)(a1 + 0x2) \
             + *(s16*)(a0 + 0x4) * *(s16*)(a1 + 0x4) \
             + a2; \
    }

#define DEFINE_func_80147814() \
    void func_80147814(s32 a0, s32 a1) { \
        s32 v0 = *(s32*)(a0 + 0x34) + a1; \
        *(s32*)(a0 + 0x34) = v0; \
        if (a1 < 0) { \
            if (v0 < (s32)0xFFE10000) { \
                *(s32*)(a0 + 0x34) = (s32)0xFFE10000; \
                return; \
            } \
        } \
        if (a1 > 0) { \
            if ((s32)0x1F0000 < *(s32*)(a0 + 0x34)) { \
                *(s32*)(a0 + 0x34) = 0x1F0000; \
            } \
        } \
    }

#define DEFINE_func_801518D8() \
    s32 func_801518D8(s32 a0) { \
        u8 v1 = *(u8*)(a0 + 0x3E); \
        if (v1 == 0x1B) return 1; \
        if (v1 == 0x1C) return 1; \
        if (v1 == 0xF) return 1; \
        if (v1 == 0x10) return 1; \
        if (v1 == 0x3) return 1; \
        if (v1 != 0x13) return v1 == 0x17; \
        return 1; \
    }

#define DEFINE_func_80147948() \
    void func_80147948(s32 a0, s32 a1, s32 a2) { \
        s32 v0 = *(s32*)(a0 + 0x24) + a1; \
        *(s32*)(a0 + 0x24) = v0; \
        if (a1 < 0) { \
            if (!(-a2 < v0)) { \
                *(s32*)(a0 + 0x24) = -a2; \
                return; \
            } \
        } \
        if (a1 > 0) { \
            if (!(*(s32*)(a0 + 0x24) < a2)) { \
                *(s32*)(a0 + 0x24) = a2; \
            } \
        } \
    }

#define DEFINE_func_801479BC() \
    void func_801479BC(s32 a0, s32 a1, s32 a2) { \
        s32 v0 = *(s32*)(a0 + 0x28) + a1; \
        *(s32*)(a0 + 0x28) = v0; \
        if (a1 < 0) { \
            if (!(-a2 < v0)) { \
                *(s32*)(a0 + 0x28) = -a2; \
                return; \
            } \
        } \
        if (a1 > 0) { \
            if (!(*(s32*)(a0 + 0x28) < a2)) { \
                *(s32*)(a0 + 0x28) = a2; \
            } \
        } \
    }

#define DEFINE_func_80147A30() \
    void func_80147A30(s32 a0, s32 a1, s32 a2) { \
        s32 v0 = *(s32*)(a0 + 0x2C) + a1; \
        *(s32*)(a0 + 0x2C) = v0; \
        if (a1 < 0) { \
            if (-a2 >= v0) { \
                *(s32*)(a0 + 0x2C) = -a2; \
                return; \
            } \
        } \
        if (a1 > 0) { \
            if (*(s32*)(a0 + 0x2C) >= a2) { \
                *(s32*)(a0 + 0x2C) = a2; \
            } \
        } \
    }

#define DEFINE_func_8012E470() \
    s32 func_8012E470(s32 a0) { \
        s32 a1 = *(s32*)(a0 + 0x20); \
        s32 v1 = *(s16*)(a1 + 0x18); \
        s32 v0 = v1 + (0x1000 - v1) / 4; \
        *(s16*)(a1 + 0x18) = (*(s16*)(a1 + 0x1C) = v0); \
        v0 = *(s32*)(a0 + 0x1C); \
        if (v0 != 0) { \
            v0 -= 1; \
            *(s32*)(a0 + 0x1C) = v0; \
            v1 = v0; \
            return (u32)v1 < 1; \
        } \
        return 1; \
    }

#define DEFINE_func_80136BC4() \
    void func_80136BC4(s32 a0) { \
        if (*(s32*)(a0 + 0x8) == 0x20) { \
            *(s32*)(a0 + 0x8) = a0 + 0x20; \
            *(s32*)(a0 + 0xC) += a0; \
            *(s32*)(a0 + 0x10) += a0; \
            *(s32*)(a0 + 0x14) += a0; \
            *(s32*)(a0 + 0x18) += a0; \
            *(s32*)(a0 + 0x1C) += a0; \
        } \
    }

#define DEFINE_func_80138B88() \
    void func_80138B88(s32 a0) { \
        s32 a1; \
        if (*(s32*)(a0 + 0x8) & 0x2000) { \
            *(s16*)(a0 + 0x4) = 0xD; \
        } else { \
            *(s16*)(a0 + 0x4) = 0xC; \
            *(s32*)(a0 + 0x8) &= ~0x1000; \
            a1 = *(s32*)(a0 + 0x40); \
            if (a1 != 0) { \
                if (*(u16*)(a0 + 0x18) != 0) { \
                    *(s16*)a1 = 3; \
                } \
            } \
        } \
    }

#define DEFINE_func_801470C0() \
    void func_801470C0(s32 a0) { \
        s32 a1; \
        a1 = *(s32*)(a0 + 0x20); \
        if (a1 != 0) { \
            if ((*(u8*)(a0 + 0x221) | *(u8*)(a0 + 0x220) | *(u8*)(a0 + 0x222)) != 0) { \
                *(s32*)(a1 + 0x4) |= 0x80000000; \
            } else { \
                *(s32*)(a1 + 0x4) &= 0x7FFFFFFF; \
            } \
        } \
    }

#define DEFINE_func_80151880() \
    s32 func_80151880(s32 a0) { \
        u16 h; \
        s32 v1; \
        h = *(u16*)(a0 + 0x3E); \
        v1 = h & 0xFF; \
        if (v1 == 0x1B) return 1; \
        if (v1 == 0x1C) return 1; \
        if (v1 == 0xF) return 1; \
        if (v1 == 0x10) return 1; \
        if (v1 == 0xB) return 2; \
        if (v1 != 0x1F) return (h >> 8) & 2; \
        return 1; \
    }

#define DEFINE_func_80148038() \
    void func_80148038(s32 a0, s32 a1) { \
        s32 v1 = *(s32*)(a0 + 0x34); \
        if (v1 < 0) { \
            if (a1 < 0) { \
                if ((s32)0xFFE10000 < v1) { \
                } else { \
                    a1 = 0; \
                } \
            } \
        } else { \
            if (a1 > 0) { \
                if (0x1EFFFF < v1) { \
                    a1 = 0; \
                } \
            } \
        } \
        *(s32*)(a0 + 0x34) += a1; \
    }

#define DEFINE_func_80149228() \
    s32 func_80149228(s32 a0) { \
        u32 a1; \
        s32 v0; \
        if (*(s16*)(a0 + 0x1E4) == 0) { \
            *(s32*)(a0 + 0x1DC) = 0; \
            *(s32*)(a0 + 0x1E0) = 0; \
            *(s16*)(a0 + 0x1E4) = *(u16*)(a0 + 0x1E6); \
        } \
        a1 = *(u16*)(a0 + 0xAC); \
        if (a1 != 0) { \
            s32 v0t = *(s32*)(a0 + 0x1E0); \
            u16 v1t = *(u16*)(a0 + 0x1E6); \
            s32 r; \
            *(s32*)(a0 + 0x1E0) = a1; \
            r = a1 & v0t; \
            *(s16*)(a0 + 0x1E4) = v1t; \
            *(s32*)(a0 + 0x1DC) = r; \
        } \
        v0 = *(u16*)(a0 + 0x1E4); \
        v0 -= 1; \
        *(s16*)(a0 + 0x1E4) = v0; \
        return v0; \
    }

#define DEFINE_func_801489E8() \
    s32 func_801489E8(s32 a0) { \
        u8 v1; \
        v1 = *(u8*)(a0 + 0xA9); \
        switch (v1) { \
        case 0x41: \
            return *(u16*)(a0 + 0xAA) & 0x8000; \
        case 0x53: \
        case 0x73: \
            return *(u8*)(a0 + 0xAE) < 0x40; \
        } \
        return 0; \
    }

#define DEFINE_func_8012AD80() \
    void func_8012AD80(s32 a0) { \
        *(s32*)(a0 + 0x10) += *(s32*)(a0 + 0x44); \
        *(s32*)(a0 + 0x14) += *(s32*)(a0 + 0x48); \
        *(s32*)(a0 + 0x18) += *(s32*)(a0 + 0x4C); \
        *(s32*)(a0 + 0x4) += *(s32*)(a0 + 0x10); \
        *(s32*)(a0 + 0x8) += *(s32*)(a0 + 0x14); \
        *(s32*)(a0 + 0xC) += *(s32*)(a0 + 0x18); \
    }

#define DEFINE_func_8014891C() \
    s32 func_8014891C(s32 a0) { \
        u8 v1; \
        v1 = *(u8*)(a0 + 0xA9); \
        switch (v1) { \
        case 0x41: \
            return *(u16*)(a0 + 0xAA) & 0x1000; \
        case 0x53: \
        case 0x73: \
            return (*(u16*)(a0 + 0xAE) >> 8) < 0x40; \
        } \
        return 0; \
    }

#define DEFINE_func_80148A48() \
    s32 func_80148A48(s32 a0) { \
        u8 v1; \
        v1 = *(u8*)(a0 + 0xA9); \
        switch (v1) { \
        case 0x41: \
            return *(u16*)(a0 + 0xAA) & 0x2000; \
        case 0x53: \
        case 0x73: \
            return *(u8*)(a0 + 0xAE) >= 0xC1; \
        } \
        return 0; \
    }

#define DEFINE_func_8013435C() \
    s32 func_8013435C(s16 *a0, s16 *a1, s32 a2, s16 *a3) { \
        s32 t1; \
        s32 sum; \
        if (a3[1] < -0xE00) { \
            t1 = -0x1800; \
        } else { \
            t1 = -0x2F00; \
        } \
        sum = a0[0] * a1[0] + a0[1] * a1[1]; \
        sum = sum + a0[2] * a1[2]; \
        sum = sum + a2; \
        return sum < t1; \
    }

#define DEFINE_func_80148980() \
    s32 func_80148980(u8 *a0) { \
        u8 c; \
        s32 v0; \
        c = a0[0xA9]; \
        switch (c) { \
        case 0x41: \
            v0 = *(u16 *)(a0 + 0xAA) & 0x4000; \
            break; \
        case 0x53: \
        case 0x73: \
            v0 = ((u32)*(u16 *)(a0 + 0xAE) >> 8) < 0xC1; \
            v0 = v0 ^ 1; \
            break; \
        default: \
            v0 = 0; \
            break; \
        } \
        return v0; \
    }

#define DEFINE_func_801783D0() \
    u32 func_801783D0(s32 a0, s32 a1) { \
        s32 t0; \
        s32 a2; \
        s32 a3; \
        t0 = 0; \
        a2 = a0; \
        a3 = 0; \
        while (a2 >= 10) { \
            a0 = a0 / 10; \
            t0 = t0 | ((a2 - (a0 * 2 + a0 * 8)) << a3); \
            a2 = a0; \
            a3 += 4; \
        } \
        t0 = t0 | (a2 << a3); \
        return t0 << a1; \
    }

#define DEFINE_func_8012B260() \
    void func_8012B260(u8 *a0) { \
        u8 *a1; \
        s32 a, b, c; \
        u16 t; \
        a1 = *(u8 **)(a0 + 0x20); \
        a = (u16)*(u16 *)(a0 + 6) + (u16)*(u16 *)(a0 + 0x50); \
        *(u16 *)(a1 + 8) = a; \
        *(s32 *)(a1 + 0x48) = (s16)a; \
        b = (u16)*(u16 *)(a0 + 0xA) + (u16)*(u16 *)(a0 + 0x52); \
        *(u16 *)(a1 + 0xA) = b; \
        *(s32 *)(a1 + 0x4C) = (s16)b; \
        c = (u16)*(u16 *)(a0 + 0xE); \
        t = *(u16 *)(a1 + 0x2C) | 1; \
        c = c + (u16)*(u16 *)(a0 + 0x54); \
        *(u16 *)(a1 + 0xC) = c; \
        *(u16 *)(a1 + 0x2C) = t; \
        *(s32 *)(a1 + 0x50) = (s16)c; \
    }

#define DEFINE_func_801473EC() \
    void func_801473EC(s32 *a0) { \
        s32 *a2; \
        a2 = a0; \
        a2[1] += a2[4]; \
        a2[2] += a2[5]; \
        a2[3] += a2[6]; \
        if (a2[4] != 0 || a2[5] != 0 || a2[6] != 0) { \
            a2[0x11] |= 0x80000000; \
        } \
    }

#define DEFINE_func_801488A8() \
    s32 func_801488A8(u8 *a0) { \
        u8 c; \
        s32 v0; \
        u32 h; \
        s32 lo; \
        c = a0[0xA9]; \
        switch (c) { \
        case 0x41: \
            v0 = *(u16 *)(a0 + 0xAA) & 0xF000; \
            break; \
        case 0x53: \
        case 0x73: \
            h = *(u16 *)(a0 + 0xAE); \
            lo = h & 0xFF; \
            if (lo != 0x80) { \
                return 1; \
            } \
            if ((s32)(h >> 8) != lo) { \
                return 1; \
            } \
            v0 = 0; \
            break; \
        default: \
            v0 = 0; \
            break; \
        } \
        return v0; \
    }

#define DEFINE_func_8017509C() \
    s32 func_8017509C(u8 *a0, s32 a1, u8 *a2, u8 *a3) { \
        a1 = (s16)a1; \
        a0 = a0 + a1 * 14; \
        if (*(s16 *)(a0 + 0xC) == 0x7FFF) { \
            return 1; \
        } \
        *(u16 *)(a2 + 0) = *(u16 *)(a0 + 0); \
        *(u16 *)(a2 + 2) = *(u16 *)(a0 + 2); \
        *(u16 *)(a2 + 4) = *(u16 *)(a0 + 4); \
        *(u16 *)(a3 + 0) = *(u16 *)(a0 + 6); \
        *(u16 *)(a3 + 2) = *(u16 *)(a0 + 8); \
        *(u16 *)(a3 + 4) = *(u16 *)(a0 + 0xA); \
        return 0; \
    }

#define DEFINE_func_80139C7C() \
    void func_80139C7C(u8 *a0) { \
        s32 a1; \
        if (*(u8 *)(a0 + 0x20) != 0) { \
            if (*(u8 *)(a0 + 0x22) & 0x8) { \
                a1 = (*(s16 *)(a0 + 0x34) + 0x28) >> 1; \
            } else { \
                a1 = ((*(s16 *)(a0 + 0x34) + 0x28) >> 1) - 0x28; \
            } \
        } else { \
            a1 = (s32)(*(u16 *)(a0 + 0x34) << 16) >> 17; \
        } \
        *(s16 *)(a0 + 0x30) = *(u16 *)(a0 + 0x24) - a1; \
        *(s16 *)(a0 + 0x32) = *(u16 *)(a0 + 0x26) - ((s32)(*(u16 *)(a0 + 0x36) << 16) >> 17); \
    }

#define DEFINE_func_80175014() \
    s32 func_80175014(u8 *a0, u8 *a1, s32 a2) { \
        a2 = (s16)a2; \
        a1 = a1 + a2 * 14; \
        if (*(s16 *)(a1 + 0xC) == 0x7FFF) { \
            return 1; \
        } \
        *(s32 *)(a0 + 0x3C) = *(s16 *)(a1 + 0); \
        *(s32 *)(a0 + 0x40) = *(s16 *)(a1 + 2); \
        *(s32 *)(a0 + 0x44) = *(s16 *)(a1 + 4); \
        *(s32 *)(a0 + 0x48) = *(s16 *)(a1 + 6); \
        *(s32 *)(a0 + 0x4C) = *(s16 *)(a1 + 8); \
        *(s32 *)(a0 + 0x50) = *(s16 *)(a1 + 0xA); \
        *(s32 *)(a0 + 0x54) = *(s16 *)(a1 + 0xC) << 5; \
        return 0; \
    }

#define DEFINE_func_80146DF8() \
    void func_80146DF8(s32 *a0, s32 a1, s32 a2, s32 a3, s32 t0) { \
        if (a1 < 0) { \
            if (a1 < -t0) a1 = -t0; \
        } else { \
            if (t0 < a1) a1 = t0; \
        } \
        if (a2 < 0) { \
            if (a2 < -t0) a2 = -t0; \
        } else { \
            if (t0 < a2) a2 = t0; \
        } \
        if (a3 < 0) { \
            if (a3 < -t0) a3 = -t0; \
        } else { \
            if (t0 < a3) a3 = t0; \
        } \
        *(s32 *)((s32)a0 + 0x24) = a1; \
        *(s32 *)((s32)a0 + 0x28) = a2; \
        *(s32 *)((s32)a0 + 0x2C) = a3; \
    }

#define DEFINE_func_8012B608() \
    s32 func_8012B608(s32 a0, s32 a1, s32 a2) { \
        s32 v1; \
        s32 t; \
        a0 &= 0xFFF; \
        a1 &= 0xFFF; \
        v1 = a1 - a0; \
        if (a0 == a1) { \
            return 0; \
        } \
        if (v1 >= 0x801) { \
            t = a0 + 0x1000; \
            v1 = a1 - t; \
        } \
        if (v1 < -0x800) { \
            t = a0 - 0x1000; \
            v1 = a1 - t; \
        } \
        if (v1 >= 0) { \
            v1 = v1 / a2; \
            if (v1 != 0) { \
                return v1; \
            } \
            v1 = 1; \
        } else { \
            v1 = v1 / a2; \
            if (v1 != 0) { \
                return v1; \
            } \
            v1 = -1; \
        } \
        return v1; \
    }

#define DEFINE_func_8013361C() \
    s32 func_8013361C(s16 *a0, s16 *a1, s16 *a2, s16 *a3) { \
        if ((*(s16 *)((s32)a0 + 4) + *(s16 *)((s32)a2 + 0) > *(s16 *)((s32)a1 + 6) + *(s16 *)((s32)a3 + 0)) || \
            (*(s16 *)((s32)a0 + 6) + *(s16 *)((s32)a2 + 0) < *(s16 *)((s32)a1 + 4) + *(s16 *)((s32)a3 + 0)) || \
            (*(s16 *)((s32)a0 + 0xC) + *(s16 *)((s32)a2 + 4) > *(s16 *)((s32)a1 + 0xE) + *(s16 *)((s32)a3 + 4)) || \
            (*(s16 *)((s32)a0 + 0xE) + *(s16 *)((s32)a2 + 4) < *(s16 *)((s32)a1 + 0xC) + *(s16 *)((s32)a3 + 4)) || \
            (*(s16 *)((s32)a0 + 8) + *(s16 *)((s32)a2 + 2) > *(s16 *)((s32)a1 + 0xA) + *(s16 *)((s32)a3 + 2)) || \
            (*(s16 *)((s32)a0 + 0xA) + *(s16 *)((s32)a2 + 2) < *(s16 *)((s32)a1 + 8) + *(s16 *)((s32)a3 + 2))) { \
            return 0; \
        } \
        return 1; \
    }

#define DEFINE_func_80137FD8() \
    void func_80137FD8(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 v; \
        u16 h30; \
        *(u8 *)(a2 + 0x3) = 8; \
        *(u8 *)(a2 + 0x7) = 0x3A; \
        *(u8 *)(a2 + 0x4) = *(u8 *)(a1 + 0x0); \
        *(u8 *)(a2 + 0x5) = *(u8 *)(a1 + 0x1); \
        *(u8 *)(a2 + 0x6) = *(u8 *)(a1 + 0x2); \
        *(u8 *)(a2 + 0xC) = *(u8 *)(a1 + 0x0); \
        *(u8 *)(a2 + 0xD) = *(u8 *)(a1 + 0x1); \
        *(u8 *)(a2 + 0xE) = *(u8 *)(a1 + 0x2); \
        *(u8 *)(a2 + 0x14) = 0xFF; \
        *(u8 *)(a2 + 0x15) = 0xFF; \
        *(u8 *)(a2 + 0x16) = 0xFF; \
        *(u8 *)(a2 + 0x1C) = 0xFF; \
        *(u8 *)(a2 + 0x1D) = 0xFF; \
        *(u8 *)(a2 + 0x1E) = 0xFF; \
        h30 = *(u16 *)(a0 + 0x30); \
        *(u16 *)(a2 + 0x18) = h30; \
        *(u16 *)(a2 + 0x8) = h30; \
        if (*(u32 *)(a0 + 0x8) & 0x2000) { \
            v = (*(u16 *)(a0 + 0x30) + *(u16 *)(a0 + 0x34)) - 0xC; \
            *(u16 *)(a2 + 0x20) = v; \
            *(u16 *)(a2 + 0x10) = v; \
        } else { \
            s32 w = *(u16 *)(a0 + 0x30) + *(u16 *)(a0 + 0x34); \
            *(u16 *)(a2 + 0x20) = w; \
            *(u16 *)(a2 + 0x10) = w; \
        } \
        if (*(u8 *)(a1 + 0x3) == 0) { \
            s32 hi = a3 + 0x5; \
            *(u16 *)(a2 + 0x12) = a3; \
            *(u16 *)(a2 + 0xA) = a3; \
            *(u16 *)(a2 + 0x22) = hi; \
            *(u16 *)(a2 + 0x1A) = hi; \
            return; \
        } \
        { \
            s32 lo = a3 + 0xC; \
            register s32 hi __asm__("$3") = a3 + 0x5; \
            *(u16 *)(a2 + 0x12) = lo; \
            *(u16 *)(a2 + 0xA) = lo; \
            *(u16 *)(a2 + 0x22) = hi; \
            *(u16 *)(a2 + 0x1A) = hi; \
        } \
        __asm__ __volatile__("" ::: "memory"); \
    }

#define DEFINE_func_8016C374() \
    s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 v; \
        *(u16 *)(a1 + 0x0) = *(u16 *)(a1 + 0x0) - 0xA; \
        if ((s16)*(u16 *)(a1 + 0x0) < 0) { \
            *(u16 *)(a1 + 0x0) = 0; \
        } \
        *(u16 *)(a1 + 0x2) = *(u16 *)(a1 + 0x2) - 0xA; \
        if ((s16)*(u16 *)(a1 + 0x2) < 0) { \
            *(u16 *)(a1 + 0x2) = 0; \
        } \
        *(u16 *)(a1 + 0x4) = *(u16 *)(a1 + 0x4) - 0xA; \
        if ((s16)*(u16 *)(a1 + 0x4) < 0) { \
            *(u16 *)(a1 + 0x4) = 0; \
        } \
        *(u16 *)(a2 + 0x0) = *(u16 *)(a2 + 0x0) - 0xA; \
        if ((s16)*(u16 *)(a2 + 0x0) < 0) { \
            *(u16 *)(a2 + 0x0) = 0; \
        } \
        *(u16 *)(a2 + 0x2) = *(u16 *)(a2 + 0x2) - 0xA; \
        if ((s16)*(u16 *)(a2 + 0x2) < 0) { \
            *(u16 *)(a2 + 0x2) = 0; \
        } \
        *(u16 *)(a2 + 0x4) = *(u16 *)(a2 + 0x4) - 0xA; \
        if ((s16)*(u16 *)(a2 + 0x4) < 0) { \
            *(u16 *)(a2 + 0x4) = 0; \
        } \
        *(u8 *)(a3 + 0x0) = *(u16 *)(a1 + 0x0); \
        *(u8 *)(a3 + 0x1) = *(u16 *)(a1 + 0x2); \
        *(u8 *)(a3 + 0x2) = *(u16 *)(a1 + 0x4); \
        *(u8 *)(a3 + 0x4) = *(u16 *)(a2 + 0x0); \
        *(u8 *)(a3 + 0x5) = *(u16 *)(a2 + 0x2); \
        *(u8 *)(a3 + 0x6) = *(u16 *)(a2 + 0x4); \
        v = *(u16 *)(a2 + 0x4) | (*(u16 *)(a2 + 0x0) | *(u16 *)(a2 + 0x2)); \
        return (s16)v; \
    }

#define DEFINE_func_80147118() \
    void func_80147118(s32 a0) { \
        s32 vec[3]; \
        vec[0] = ((s32)(*(s16 *)(a0 + 0x60) * *(s16 *)(a0 + 0x68)) / 4096); \
        vec[0] = ((s32)(vec[0] * *(s16 *)(a0 + 0x70)) / 4096); \
        vec[1] = ((s32)(*(s16 *)(a0 + 0x62) * *(s16 *)(a0 + 0x6A)) / 4096); \
        vec[1] = ((s32)(vec[1] * *(s16 *)(a0 + 0x72)) / 4096); \
        vec[2] = ((s32)(*(s16 *)(a0 + 0x64) * *(s16 *)(a0 + 0x6C)) / 4096); \
        vec[2] = ((s32)(vec[2] * *(s16 *)(a0 + 0x74)) / 4096); \
        if (0xFFFF < vec[0]) { \
            vec[0] = 0xFFFF; \
        } \
        if (0xFFFF < vec[1]) { \
            vec[1] = 0xFFFF; \
        } \
        if (0xFFFF < vec[2]) { \
            vec[2] = 0xFFFF; \
        } \
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = vec[0]; \
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = vec[1]; \
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = vec[2]; \
    }

#define DEFINE_func_80129220() \
    extern void func_80129258(void); \
    extern void func_80129248(s16 a0); \
    void func_80129220(void) { \
        func_80129258(); \
        func_80129248(1); \
    }

#define DEFINE_func_8012CBA4() \
    extern s32 func_8012CC88(); \
    extern u8 D_800D3918[]; \
    void func_8012CBA4(s32 a0) { \
        func_8012CC88(a0, 0, (s32)D_800D3918); \
    }

#define DEFINE_func_8012CBCC() \
    extern s32 func_8012CC88(); \
    extern u8 D_800D3918[]; \
    void func_8012CBCC(s32 a0) { \
        func_8012CC88(a0, 1, (s32)D_800D3918); \
    }

#define DEFINE_func_80179E48() \
    extern void func_80179B74(s16 *a0); \
    void func_80179E48(s16 a0) { \
        s16 sp[2]; \
        sp[0] = 0x1F; \
        sp[1] = a0; \
        func_80179B74(sp); \
    }

#define DEFINE_func_80179E74() \
    extern void func_80179B74(s16 *a0); \
    void func_80179E74(s16 a0) { \
        s16 sp[2]; \
        sp[0] = 0x4; \
        sp[1] = a0; \
        func_80179B74(sp); \
    }

#define DEFINE_func_80170718() \
    extern void func_80129FF4(void); \
    extern void func_80171928(void *a0); \
    void func_80170718(void *a0) { \
        func_80129FF4(); \
        func_80171928(a0); \
    }

#define DEFINE_func_80170C14() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170C44(u8 *a0); \
    void func_80170C14(u8 *a0) { \
        func_80171990(a0); \
        func_80170C44(a0); \
    }

#define DEFINE_func_8017115C() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8017118C(u8 *a0); \
    void func_8017115C(u8 *a0) { \
        func_80171990(a0); \
        func_8017118C(a0); \
    }

#define DEFINE_func_801717F4() \
    extern void func_8013E588(void *a0); \
    extern void func_80171928(void *a0); \
    void func_801717F4(void *a0) { \
        func_8013E588(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_80171824() \
    extern void func_80175414(s32); \
    extern void func_80171928(void *a0); \
    void func_80171824(void *a0) { \
        func_80175414((s32)a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_80171854() \
    extern void func_80175454(void); \
    extern void func_80171928(void *a0); \
    void func_80171854(void *a0) { \
        func_80175454(); \
        func_80171928(a0); \
    }

#define DEFINE_func_80172B14() \
    extern s16 D_80126B32; \
    extern s32 func_80172B44(void *a0); \
    extern void func_80174684(void *); \
    void func_80172B14(s16 a0) { \
        D_80126B32 = a0; \
        func_80174684((void *)func_80172B44); \
    }

#define DEFINE_func_801733CC() \
    extern void func_8016F30C(void); \
    extern s32 func_80174650(s32); \
    void func_801733CC(s32 a0) { \
        func_8016F30C(); \
        func_80174650(a0); \
    }

#define DEFINE_func_801737B8() \
    extern s16 D_80126B30; \
    extern s32 func_801737E8(void *a0); \
    extern void func_80174684(void *); \
    void func_801737B8(s16 a0) { \
        D_80126B30 = a0; \
        func_80174684((void *)func_801737E8); \
    }

#define DEFINE_func_801738DC() \
    extern s16 D_80126B30; \
    extern s32 func_8017390C(void *a0); \
    extern void func_80174684(void *); \
    void func_801738DC(s16 a0) { \
        D_80126B30 = a0; \
        func_80174684((void *)func_8017390C); \
    }

#define DEFINE_func_80174158() \
    extern s32 func_80174188(s32 a0); \
    extern void func_801741A8(s32 a0); \
    void func_80174158(s32 a0) { \
        func_80174188(a0); \
        func_801741A8(a0); \
    }

#define DEFINE_func_801743C0() \
    extern void func_80171A1C(u8 *a0); \
    extern void func_801743F0(u8 *a0); \
    void func_801743C0(u8 *a0) { \
        func_80171A1C(a0); \
        func_801743F0(a0); \
    }

#define DEFINE_func_801744B0() \
    extern void func_80171A1C(u8 *a0); \
    extern void func_801744E0(u8 *a0); \
    void func_801744B0(u8 *a0) { \
        func_80171A1C(a0); \
        func_801744E0(a0); \
    }

#define DEFINE_func_80174C80() \
    extern s32 func_80174CB0(); \
    void func_80174C80(s32 a0) { \
        s32 v; \
        v = (*(u16 *)(a0 + 0xA0) - 0x16) & 0xFFF; \
        *(s16 *)(a0 + 0xA0) = v; \
        func_80174CB0(a0, v); \
    }

#define DEFINE_func_80179F14() \
    extern void func_80179B74(s16 *a0); \
    void func_80179F14(s16 a0, s16 a1) { \
        s16 sp[3]; \
        sp[0] = 0x13; \
        sp[1] = a0; \
        sp[2] = a1; \
        func_80179B74(sp); \
    }

#define DEFINE_func_8015F2F0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015F324(s32 *a0); \
    void func_8015F2F0(s32 *a0) { \
        func_80147078(a0, 0x14); \
        func_8015F324(a0); \
    }

#define DEFINE_func_8015F738() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015F738(s32 *a0) { \
        func_801553A8(a0); \
        func_80154A74((s32)a0, 0x11); \
    }

#define DEFINE_func_8015F76C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015F848(s32 *a0); \
    void func_8015F76C(s32 *a0) { \
        func_80147078(a0, 0x15); \
        func_8015F848(a0); \
    }

#define DEFINE_func_8015FA44() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015FBE0(s32 *a0); \
    void func_8015FA44(s32 *a0) { \
        func_80147078(a0, 0x16); \
        func_8015FBE0(a0); \
    }

#define DEFINE_func_8015FA78() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015FAAC(s32 *a0); \
    void func_8015FA78(s32 *a0) { \
        func_80147078(a0, 0x16); \
        func_8015FAAC(a0); \
    }

#define DEFINE_func_801600D0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_801601AC(s32 *a0); \
    void func_801600D0(s32 *a0) { \
        func_80147078(a0, 0x18); \
        func_801601AC(a0); \
    }

#define DEFINE_func_80160104() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80160138(s32 *a0); \
    void func_80160104(s32 *a0) { \
        func_80147078(a0, 0x18); \
        func_80160138(a0); \
    }

#define DEFINE_func_80160334() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80160410(s32 *a0); \
    void func_80160334(s32 *a0) { \
        func_80147078(a0, 0x1B); \
        func_80160410(a0); \
    }

#define DEFINE_func_80160368() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8016039C(s32 *a0); \
    void func_80160368(s32 *a0) { \
        func_80147078(a0, 0x1B); \
        func_8016039C(a0); \
    }

#define DEFINE_func_801607E4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_801608C0(s32 *a0); \
    void func_801607E4(s32 *a0) { \
        func_80147078(a0, 0x1C); \
        func_801608C0(a0); \
    }

#define DEFINE_func_80160818() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8016084C(s32 *a0); \
    void func_80160818(s32 *a0) { \
        func_80147078(a0, 0x1C); \
        func_8016084C(a0); \
    }

#define DEFINE_func_80160ACC() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80160BB4(s32 *a0); \
    void func_80160ACC(s32 *a0) { \
        func_80147078(a0, 0x1D); \
        func_80160BB4(a0); \
    }

#define DEFINE_func_8012F75C() \
    extern void func_80131B14(); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F75C(s32 a0) { \
        *(u8 *)(a0 + 0xC1) = 3; \
        if (*(s32 *)(a0 + 0xB4) & 0x4) { \
            func_80131B14(); \
            *(s32 *)(a0 + 0x1C) = 0x10; \
            *(s16 *)(a0 + 0x98) = 0; \
        } \
        func_80131CA8(a0, 6); \
    }

#define DEFINE_func_80132E6C() \
    extern void Square0(s32 *a0, s32 *a1); \
    extern s16 D_80126CAC; \
    extern s16 D_80126CB0; \
    s32 func_80132E6C(s16 *a0) { \
        s32 in[3]; \
        s32 out[3]; \
        in[0] = a0[3] - D_80126CAC; \
        in[1] = 0; \
        in[2] = a0[7] - D_80126CB0; \
        Square0(in, out); \
        return out[0] + out[2]; \
    }

#define DEFINE_func_80147860() \
    extern void func_80147928(int a0, int a1); \
    extern void func_8014799C(int a0, int a1); \
    extern void func_80147A10(int a0, int a1); \
    void func_80147860(int a0, int a1, int a2, int a3) { \
        func_80147928(a0, a1); \
        func_8014799C(a0, a2); \
        func_80147A10(a0, a3); \
    }

#define DEFINE_func_8014C2B0() \
    extern s32 func_8014C59C(void *a0, void *a1); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    s32 func_8014C2B0(void *a0, void *a1, s32 a2) { \
        s16 r1 = (s16)func_8014C59C(a0, a1); \
        s32 v1 = *(s32 *)((u8 *)a0 + 0x20); \
        s16 r2 = (s16)func_80012A60(r1, *(s16 *)(v1 + 0x12)); \
        return r2 < (a2 & 0xFFFF); \
    }

#define DEFINE_func_80165BFC() \
    extern s32 func_80161208(); \
    extern void func_80165C58(s32 arg0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    void func_80165BFC(void *a0) { \
        if (func_80161208() == 0) { \
            if (*(u16 *)((u8 *)a0 + 0xB8) & 0x8000) { \
                func_80165C58((s32)a0); \
                func_801599A4(a0); \
                func_80159B3C(a0); \
            } \
        } \
    }

#define DEFINE_func_8016E688() \
    extern void func_8016E778(); \
    void func_8016E688(void *a0) { \
        u16 *p = (u16 *)a0; \
        s16 v; \
        p[0x10/2] += 0x200; \
        v = p[0x12/2] + p[0x10/2]; \
        p[0x12/2] = v; \
        if (v >= 0x3000) { \
            *(s32 *)((u8 *)a0 + 0x1C) = 4; \
            *(s16 *)((u8 *)a0 + 0x2) += 1; \
        } \
        func_8016E778(); \
    }

#define DEFINE_func_801735EC() \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s16 D_80126B40; \
    extern s16 D_80126B32; \
    void func_801735EC(void *a0) { \
        if (D_80126B40 != 0) { \
            *(s32 *)((u8 *)a0 + 0x44) |= 0x40000; \
        } \
        func_801477E8((s32 *)a0, D_80126B32 << 16); \
        func_80171A1C((u8 *)a0); \
    }

#define DEFINE_func_801290DC() \
    extern u8 *func_8012913C(s32 a0); \
    u8 *func_801290DC(s32 a0, u8 *a1) { \
        u8 *v1 = func_8012913C(a0 & 0xFFFF); \
        if (v1 != 0) { \
            *(u16 *)(v1 + 0x6) = *(u16 *)(a1 + 0x0); \
            *(u16 *)(v1 + 0xA) = *(u16 *)(a1 + 0x2); \
            *(u16 *)(v1 + 0xE) = *(u16 *)(a1 + 0x4); \
        } \
        return v1; \
    }

#define DEFINE_func_80142778() \
    extern void func_8012C218(void *a0); \
    void func_80142778(u8 *a1) { \
        u8 *a0 = *(u8 **)(a1 + 0x20); \
        *(u16 *)(a0 + 0x18) = *(u16 *)(a0 + 0x18) - 0x800; \
        *(u16 *)(a0 + 0x1A) = *(u16 *)(a0 + 0x1A) - 0x800; \
        *(u16 *)(a1 + 0xA) = *(u16 *)(a1 + 0xA) + 0x10; \
        if (*(s16 *)(a0 + 0x18) <= 0) { \
            func_8012C218(a1); \
        } \
    }

#define DEFINE_func_8014C99C() \
    extern s32 func_80029178(s32 arg); \
    extern s32 func_8016F1AC(void); \
    extern void func_80139914(s32 a0); \
    extern void func_80029124(s32, s32); \
    void func_8014C99C(u8 *a0) { \
        if ((func_80029178(0x119) & 0xFF) != 0) { \
            if (func_8016F1AC() != 0) { \
                func_80139914(*(s32 *)(a0 + 0x198)); \
                *(s32 *)(a0 + 0x198) = 0; \
                func_80029124(0x119, 0); \
            } \
        } \
    }

#define DEFINE_func_8017084C() \
    extern void func_801719A4(int a0, int a1); \
    extern void func_8014706C(void *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_8016BADC(void *a0, s32 a1, s32 a2); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801708B0(void *a0); \
    extern u8 D_800D5DA8; \
    void func_8017084C(s32 a0) { \
        func_801719A4(a0, 1); \
        func_8014706C((void *)a0); \
        func_80154274((s32 *)a0, (s32)&D_800D5DA8); \
        func_8016BADC((void *)a0, -0x40, 0x40); \
        func_80171990((u8 *)a0); \
        func_801708B0((void *)a0); \
    }

#define DEFINE_func_8016F95C() \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern s32 func_80171D1C(void *a0, void *a1, s32 a2); \
    extern void func_80171928(void *a0); \
    extern u16 D_8011F73E; \
    void func_8016F95C(void *a0) { \
        u16 *p = &D_8011F73E; \
        u16 v = *p; \
        s32 r; \
        if (v == 0) { \
            r = func_80171CC4(a0, p - 3); \
        } else { \
            r = func_80171D1C(a0, p - 3, v & 0xFF); \
        } \
        if (r != 0) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_801722CC() \
    extern s32 func_80172664(s32 *a0); \
    void func_801722CC(s32 *a0) { \
        if (func_80172664(a0) == 0) { \
            *(s16 *)((u8 *)a0 + 0xAC) = 0x40; \
            *(s16 *)((u8 *)a0 + 0xAA) = 0x40; \
        } \
    }

#define DEFINE_func_8017280C() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172844(u8 *a0); \
    void func_8017280C(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80172844(a0); \
    }

#define DEFINE_func_80172920() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172958(u8 *a0); \
    void func_80172920(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80172958(a0); \
    }

#define DEFINE_func_80172CDC() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172D14(u8 *a0); \
    void func_80172CDC(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80172D14(a0); \
    }

#define DEFINE_func_80172DE8() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172E20(u8 *a0); \
    void func_80172DE8(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80172E20(a0); \
    }

#define DEFINE_func_80173580() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_801735B8(u8 *a0); \
    void func_80173580(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_801735B8(a0); \
    }

#define DEFINE_func_80173738() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80173770(u8 *a0); \
    void func_80173738(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80173770(a0); \
    }

#define DEFINE_func_80173824() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_8017385C(u8 *a0); \
    void func_80173824(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_8017385C(a0); \
    }

#define DEFINE_func_80173948() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80173980(u8 *a0); \
    void func_80173948(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80173980(a0); \
    }

#define DEFINE_func_80173B88() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80173BC0(u8 *a0); \
    void func_80173B88(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80173BC0(a0); \
    }

#define DEFINE_func_801742E0() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80174318(u8 *a0); \
    void func_801742E0(u8 *a0) { \
        func_80147060(a0); \
        func_80171A1C(a0); \
        func_80174318(a0); \
    }

#define DEFINE_func_8012DFD4() \
    extern void func_8012E014(void); \
    extern void func_8012E138(); \
    void func_8012DFD4(u8 *a0) { \
        if (a0[0x74]) { \
            func_8012E014(); \
        } else { \
            func_8012E138(); \
        } \
    }

#define DEFINE_func_80165374() \
    extern void func_801653F4(s32 a0); \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80165580(s32 a0); \
    void func_80165374(s32 a0) { \
        func_801653F4(a0); \
        func_80147078((s32 *)a0, 0x17); \
        *(u8 *)(a0 + 0x197) = 1; \
        func_80165580(a0); \
    }

#define DEFINE_func_8016E6E4() \
    extern void func_8016E778(); \
    void func_8016E6E4(s32 a0) { \
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1; \
        *(s32 *)(a0 + 0x1C) = v0; \
        if (v0 == -1) { \
            *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1; \
        } \
        func_8016E778(); \
    }

#define DEFINE_func_8016FA00() \
    extern void func_801719A4(int a0, int a1); \
    extern void func_80171B44(s32 *a0); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FA44(s32 a0); \
    void func_8016FA00(s32 a0) { \
        func_801719A4(a0, 1); \
        func_80171B44((s32 *)a0); \
        func_80171990((u8 *)a0); \
        func_8016FA44(a0); \
    }

#define DEFINE_func_801744E0() \
    extern void func_800D1724(s32 a0); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s32 D_80127508; \
    void func_801744E0(u8 *a0) { \
        func_800D1724(D_80127508); \
        func_80171A1C(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_801284F0() \
    extern void func_80175308(); \
    extern void func_8016E8F0(void); \
    extern void func_80175494(void); \
    extern void func_80011C10(void); \
    extern u8 D_800B9A64; \
    void func_801284F0(void) { \
        func_80175308(); \
        func_8016E8F0(); \
        if (D_800B9A64 != 0) { \
            func_80175494(); \
        } \
        func_80011C10(); \
    }

#define DEFINE_func_8012B1B4() \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    void func_8012B1B4(s32 a0, s32 a1) { \
        s32 sp10[4]; \
        func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, a1, (s32)sp10); \
        *(s32 *)(a0 + 0x10) = sp10[0]; \
        *(s32 *)(a0 + 0x18) = sp10[2]; \
    }

#define DEFINE_func_8012F87C() \
    extern void func_80131340(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F87C(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x8) { \
            func_80131340(a0); \
        } \
        func_80131CA8(a0, 0xA); \
    }

#define DEFINE_func_8012F91C() \
    extern void func_80131340(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F91C(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x80) { \
            func_80131340(a0); \
        } \
        func_80131CA8(a0, 0x17); \
    }

#define DEFINE_func_8012FF00() \
    extern void func_80131340(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FF00(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x200) { \
            func_80131340(a0); \
        } \
        func_80131CA8(a0, 0x1F); \
    }

#define DEFINE_func_8012FF4C() \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FF4C(s32 a0) { \
        *(s8 *)(a0 + 0xC1) = 5; \
        if (*(s32 *)(a0 + 0xB4) & 0x20) { \
            s32 v1 = *(s32 *)(a0 + 0x20); \
            *(s16 *)(a0 + 0x5C) = 0; \
            *(s32 *)(a0 + 0x1C) = 0x1E; \
            *(s16 *)(a0 + 0x98) = 0; \
            *(s16 *)(v1 + 0x10) = 0; \
        } \
        func_80131CA8(a0, 0xF); \
    }

#define DEFINE_func_80130314() \
    extern void func_80131340(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_80130314(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x800) { \
            func_80131340(a0); \
        } \
        func_80131CA8(a0, 0x2D); \
    }

#define DEFINE_func_80160DEC() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_80160DEC(u8 *a0) { \
        *(s32 *)(a0 + 0x1AC) = 0; \
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0; \
        func_801553C0((s32)a0); \
        *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & -0x181; \
        func_80154A74((s32)a0, 0x11); \
    }

#define DEFINE_func_80172F4C() \
    extern void func_8017303C(void *); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80174650(s32); \
    extern u8 D_800D47F4[]; \
    extern s32 D_80126B58; \
    extern s16 D_80126B30; \
    void func_80172F4C(void) { \
        func_8017303C(D_800D47F4); \
        func_80154A74((s32)&D_80126B58, 0x13); \
        D_80126B30 = 0; \
        func_80174650((s32)&D_80126B58); \
    }

#define DEFINE_func_80172F9C() \
    extern void func_8017303C(void *); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80174650(s32); \
    extern u8 D_800D46E4[]; \
    extern s32 D_80126B58; \
    extern s16 D_80126B30; \
    void func_80172F9C(void) { \
        func_8017303C(D_800D46E4); \
        func_80154A74((s32)&D_80126B58, 0x11); \
        D_80126B30 = 0; \
        func_80174650((s32)&D_80126B58); \
    }

#define DEFINE_func_80172FEC() \
    extern void func_8017303C(void *); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80174650(s32); \
    extern u8 D_800D5C6C[]; \
    extern s32 D_80126B58; \
    extern s16 D_80126B30; \
    void func_80172FEC(void) { \
        func_8017303C(D_800D5C6C); \
        func_80154A74((s32)&D_80126B58, 0x11); \
        D_80126B30 = 0; \
        func_80174650((s32)&D_80126B58); \
    }

#define DEFINE_func_80174B6C() \
    extern void func_80174BBC(void *a0); \
    extern void func_8012A018(s32 a, s32 b); \
    extern void func_8012A0E0(void); \
    extern void func_80174BF4(void *a0); \
    extern u8 D_80126948[]; \
    void func_80174B6C(void) { \
        func_80174BBC(D_80126948); \
        func_8012A018((s32)func_80174BF4, 0); \
        func_8012A0E0(); \
        func_80174BF4(D_80126948); \
    }

#define DEFINE_func_80151E78() \
    extern void func_80149020(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_80172630(u8 *a0); \
    void func_80151E78(s32 *a0) { \
        u8 *p = (u8 *)a0 + 0xDE; \
        u8 v; \
        func_80149020(a0); \
        v = *p; \
        *p = v + 0xFF; \
        if (v == 0) { \
            *p = 0x10; \
            func_80146CA0(a0); \
        } \
        func_80172630((u8 *)a0); \
    }

#define DEFINE_func_80157CCC() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801553A8(s32 *a0); \
    void func_80157CCC(s32 a0) { \
        s32 s0 = a0; \
        *(u8 *)(s0 + 0x223) = 0x10; \
        *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) & ~2; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801553A8((s32 *)s0); \
    }

#define DEFINE_func_8016007C() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern u8 D_800B9A17; \
    extern u16 D_801270C0; \
    void func_8016007C(s32 a0) { \
        *(s32 *)(a0 + 0x184) = 0; \
        *(s16 *)(a0 + 0x18A) = 0; \
        *(s16 *)(a0 + 0x188) = 0; \
        *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & ~0x10; \
        D_800B9A17 = 1; \
        func_80154A74(a0, 0x11); \
        D_801270C0 = 1; \
    }

#define DEFINE_func_80160FE0() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80160FE0(s32 *a0) { \
        s32 *s0 = a0; \
        func_80149020(a0); \
        if (func_801399F0(*(s32 *)((u8 *)s0 + 0x198)) != 0) { \
            func_80139914(*(s32 *)((u8 *)s0 + 0x198)); \
            *(s32 *)((u8 *)s0 + 0x198) = 0; \
            func_80146CA0(s0); \
        } \
    }

#define DEFINE_func_80179D78() \
    extern void func_80179B74(s16 *a0); \
    void func_80179D78(u16 *a0) { \
        s16 sp[5]; \
        sp[0] = 0x1C; \
        sp[1] = a0[0]; \
        sp[2] = a0[1]; \
        sp[3] = a0[2]; \
        sp[4] = a0[3]; \
        func_80179B74(sp); \
    }

#define DEFINE_func_801608C0() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_801608C0(s32 *a0) { \
        *(s32 *)((s32)a0 + 0x44) |= 0x41; \
        func_801553A8(a0); \
        func_80155440(a0); \
        func_80154150((s32)a0, 0x24); \
        func_80154A74((s32)a0, 0x1D); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80162D28() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80162D28(s32 *a0) { \
        s16 *s0 = (s16 *)a0[8]; \
        s32 s1 = (s32)s0 + 0x34; \
        func_80013F3C(s1); \
        func_800126C4(s1, s0[8]); \
        func_80012558(s1, s0[9]); \
        func_800123F0(s1, s0[10]); \
    }

#define DEFINE_func_80162D88() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80162D88(s32 *a0) { \
        s16 *s0 = (s16 *)a0[8]; \
        s32 s1 = (s32)s0 + 0x34; \
        func_80013F3C(s1); \
        func_80012558(s1, s0[9]); \
        func_800126C4(s1, s0[8]); \
        func_800123F0(s1, s0[10]); \
    }

#define DEFINE_func_80162DE8() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80162DE8(s32 *a0) { \
        s16 *s0 = (s16 *)a0[8]; \
        s32 s1 = (s32)s0 + 0x34; \
        func_80013F3C(s1); \
        func_800123F0(s1, s0[10]); \
        func_800126C4(s1, s0[8]); \
        func_80012558(s1, s0[9]); \
    }

#define DEFINE_func_80162E48() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80162E48(s32 *a0) { \
        s16 *s0 = (s16 *)a0[8]; \
        s32 s1 = (s32)s0 + 0x34; \
        func_80013F3C(s1); \
        func_800123F0(s1, s0[10]); \
        func_80012558(s1, s0[9]); \
        func_800126C4(s1, s0[8]); \
    }

#define DEFINE_func_80162EA8() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80162EA8(s32 *a0) { \
        s16 *s0 = (s16 *)a0[8]; \
        s32 s1 = (s32)s0 + 0x34; \
        func_80013F3C(s1); \
        func_80012558(s1, s0[9]); \
        func_800123F0(s1, s0[10]); \
        func_800126C4(s1, s0[8]); \
    }

#define DEFINE_func_80165064() \
    extern void func_80146CA0(void *a0); \
    extern void func_80165124(void *a0); \
    extern void func_801651B8(void *a0); \
    void func_80165064(s32 *a0) { \
        s16 v = *(u16 *)((s32)a0 + 0x62) + 0x10; \
        *(u16 *)((s32)a0 + 0x62) = v; \
        if (v >= 0x100) { \
            *(u16 *)((s32)a0 + 0x62) = 0xFF; \
            func_80146CA0(a0); \
        } \
        func_80165124(a0); \
        func_801651B8(a0); \
    }

#define DEFINE_func_801650C4() \
    extern void func_80162CCC(void); \
    extern void func_80165124(void *a0); \
    extern void func_801651B8(void *a0); \
    void func_801650C4(s32 *a0) { \
        s16 v = *(u16 *)((s32)a0 + 0x62) - 0x10; \
        *(u16 *)((s32)a0 + 0x62) = v; \
        if (v < 0) { \
            func_80162CCC(); \
        } else { \
            func_80165124(a0); \
            func_801651B8(a0); \
        } \
    }

#define DEFINE_func_8014C3D0() \
    extern s32 func_8014C59C(void *a0, void *a1); \
    extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5); \
    s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3) { \
        s16 v = (s16)func_8014C59C(a0, a1); \
        return func_8014C43C(a0, a1, a2, a3, v); \
    }

#define DEFINE_func_80152194() \
    extern void func_80149020(s32 *a0); \
    extern void func_80147A84(s32 arg0); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_801470B4(s32 a0); \
    extern void func_8015369C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152194(s32 *a0) { \
        u8 v1; \
        func_80149020(a0); \
        func_80147A84((s32)a0); \
        func_801473EC(a0); \
        func_80148038((s32)a0, 0x4000); \
        func_80147460((s32)a0); \
        v1 = *((u8 *)a0 + 0xDE); \
        *((u8 *)a0 + 0xDE) = v1 + 0xFF; \
        if (v1 == 0) { \
            func_801470B4((s32)a0); \
            func_8015369C((s32)a0); \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_80164CD4() \
    extern s32 func_80164E40(void); \
    extern void func_80146CA0(void *a0); \
    void func_80164CD4(u8 *a0) { \
        u8 *s0 = *(u8 **)(a0 + 0x20); \
        u16 v1; \
        func_80164E40(); \
        v1 = *(u16 *)(a0 + 0x60) + *(u16 *)(a0 + 0x62); \
        *(u16 *)(a0 + 0x60) = v1; \
        *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + v1; \
        *(u16 *)(s0 + 0x18) = *(u16 *)(s0 + 0x1A); \
        if (*(s16 *)(a0 + 0x60) < 0) { \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_8016D464() \
    extern void func_800D22E4(s32 a0); \
    extern short func_8016CF04(); \
    void func_8016D464(u8 *a0) { \
        u8 *s1 = *(u8 **)(a0 + 0x34); \
        s32 v0; \
        func_800D22E4((s32)a0); \
        func_8016CF04((s32)a0, 1); \
        v0 = *(s32 *)(a0 + 0x1C) - 1; \
        *(s32 *)(a0 + 0x1C) = v0; \
        if (v0 == -1 || *(u16 *)s1 != 1) { \
            *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1; \
        } \
    }

#define DEFINE_func_8012A0E0() \
    extern void func_8012A100(s8 a0); \
    void func_8012A0E0(void) { \
        func_8012A100(0); \
    }

#define DEFINE_func_80150BA4() \
    extern s32 func_80151184(s32 a0, s32 a1, s32 a2); \
    s32 func_80150BA4(s32 a0) { \
        return func_80151184(a0, 1, 0x10); \
    }

#define DEFINE_func_8017A220() \
    extern void func_80179B74(s16 *a0); \
    void func_8017A220(void) { \
        s16 v = 0x21; \
        func_80179B74(&v); \
    }

#define DEFINE_func_8017A248() \
    extern void func_80179B74(s16 *a0); \
    void func_8017A248(void) { \
        s16 v = 0x22; \
        func_80179B74(&v); \
    }

#define DEFINE_func_8017A270() \
    extern void func_80179B74(s16 *a0); \
    void func_8017A270(void) { \
        s16 v = 0xD; \
        func_80179B74(&v); \
    }

#define DEFINE_func_801303EC() \
    extern void func_801319E0(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_801303EC(void *a0) { \
        if (*(s32 *)((u8 *)a0 + 0xB4) & 0x10) { \
            func_801319E0((s32)a0); \
        } \
        func_80131CA8((int)a0, 0xC); \
    }

#define DEFINE_func_8013767C() \
    extern s32 func_801399A8(void); \
    extern void func_801377B4(s32 a0, s32 a1, s32 a2); \
    s32 func_8013767C(s32 a0) { \
        s32 s0 = func_801399A8(); \
        if (s0 != 0) { \
            func_801377B4(a0, 0, s0); \
        } \
        return s0; \
    }

#define DEFINE_func_801458E8() \
    extern s32 D_800AE6AC; \
    extern s32 D_800AE6B0; \
    extern s16 D_800B9A0A; \
    extern u8 D_80078E50; \
    extern void func_800D185C(u8 *a0); \
    void func_801458E8(void) { \
        D_800AE6B0 = D_800AE6AC | 0x1000000; \
        func_800D185C(&D_80078E50); \
        D_800B9A0A = 0x3000; \
    }

#define DEFINE_func_801516F0() \
    extern void func_8014C8F0(s32 arg0); \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80151780(s32 a0); \
    void func_801516F0(s32 *a0) { \
        func_8014C8F0((s32)a0); \
        *((u8 *)a0 + 0xDE) = (u8)*(u16 *)a0; \
        func_80147078(a0, 0x19); \
        *(s16 *)((u8 *)a0 + 0x2) = 1; \
        func_80151780((s32)a0); \
    }

#define DEFINE_func_80128D60() \
    extern void func_80018450(s32 a0, s32 a1); \
    extern void func_800183E0(s32 a0); \
    void func_80128D60(s32 a0, s32 *a1, s32 *a2) { \
        a1[0] = (s32)a2; \
        *(s16 *)((u8 *)a1 + 4) = 0; \
        *(s16 *)((u8 *)a1 + 6) = a2[1] & 0x3F; \
        if (a0 != 0) { \
            func_80018450(a0, a2[0]); \
        } else { \
            func_800183E0(a2[0]); \
        } \
    }

#define DEFINE_func_801292C8() \
    extern void func_80016714(void *a0, s32 a1); \
    void func_801292C8(u8 *a0) { \
        u16 *p = *(u16 **)(a0 + 0x20); \
        if (p != 0) { \
            func_80016714(p, (p[0] == 1) ? 0x84 : 0x38); \
        } \
        *(s16 *)a0 = 0; \
    }

#define DEFINE_func_80139954() \
    extern void func_8013A8B0(s32 *a0); \
    extern u16 D_80126A08; \
    extern s16 D_801269F4; \
    extern s32 D_801269F0; \
    extern s32 *D_80126A30; \
    void func_80139954(void) { \
        u16 v = D_80126A08; \
        D_801269F4 = 0; \
        D_801269F0 = 0; \
        if (v != 0) { \
            if (D_80126A30 != 0) { \
                func_8013A8B0(D_80126A30); \
            } \
        } \
    }

#define DEFINE_func_80141C50() \
    extern s32 func_80015144(void); \
    extern u16 D_8011511C; \
    extern u16 D_8011511E; \
    s32 func_80141C50(void) { \
        if (D_8011511C != 0x90F) { \
            return 0; \
        } \
        if ((D_8011511E & 0x800) == 0) { \
            return 0; \
        } \
        return func_80015144() != 0; \
    }

#define DEFINE_func_80143CD4() \
    extern s32 func_8012C658(s32 a0, s32 a1, s32 a2); \
    void func_80143CD4(s32 a0) { \
        func_8012C658(0x39, 0, a0); \
        func_8012C658(0x39, 1, a0); \
        func_8012C658(0x39, 2, a0); \
    }

#define DEFINE_func_80173980() \
    extern void func_80171A1C(u8 *a0); \
    extern s16 D_80126B30; \
    void func_80173980(u8 *a0) { \
        if (D_80126B30 == 0) { \
            *(u16 *)(a0 + 0xAC) |= 0x80; \
            *(u16 *)(a0 + 0xAA) |= 0x80; \
        } else { \
            *(u16 *)(a0 + 0xAC) |= 0x10; \
        } \
        func_80171A1C(a0); \
    }

#define DEFINE_func_80174F64() \
    extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2); \
    void func_80174F64(u8 *a0) { \
        s32 r; \
        u16 *p = (u16 *)(a0 + 0x38); \
        r = func_80175014(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF); \
        if (r != 0) { \
            *p = *p | 0x8000; \
        } else { \
            *p = *p + 1; \
        } \
    }

#define DEFINE_func_80174FBC() \
    extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2); \
    void func_80174FBC(u8 *a0) { \
        u16 *p = (u16 *)(a0 + 0x38); \
        if ((*p & 0x7FFF) != 0) { \
            func_80175014(a0, *(u8 **)(a0 + 0x34), *p & 0x7FFF); \
            *p = *p - 1; \
        } else { \
            *p = *p | 0x8000; \
        } \
    }

#define DEFINE_func_8012F214() \
    extern void func_8004914C(void *a0); \
    extern void func_800491AC(void *a0); \
    extern void RotTransSV(s32 a0, s32 a1, void *a2); \
    void func_8012F214(s32 a0, s32 a1, s32 a2) { \
        s32 *p = (s32 *)(*(s32 *)(a0 + 0x20) + 0x34); \
        s32 buf[2]; \
        func_8004914C(p); \
        func_800491AC(p); \
        RotTransSV(a1, a2, buf); \
    }

#define DEFINE_func_801428CC() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_80142D38(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    void func_801428CC(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
        } else if (func_80142D38(a0) == 1) { \
            func_80142BB4(a0, 0, 3); \
        } \
    }

#define DEFINE_func_80142FFC() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_80142D38(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    void func_80142FFC(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
        } else if (func_80142D38(a0) == 1) { \
            func_80142BB4(a0, 0, 3); \
        } \
    }

#define DEFINE_func_80143188() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_80142D38(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    void func_80143188(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
        } else if (func_80142D38(a0) == 1) { \
            func_80142BB4(a0, 0, 3); \
        } \
    }

#define DEFINE_func_80143390() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_80142D38(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    void func_80143390(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
        } else if (func_80142D38(a0) == 1) { \
            func_80142BB4(a0, 0, 3); \
        } \
    }

#define DEFINE_func_80147478() \
    extern void func_80147514(); \
    extern void func_80147628(s32 a0); \
    void func_80147478(s32 a0) { \
        if ((*(s32 *)(a0 + 0x44) & 0x40000000) == 0) { \
            func_80147514(); \
            func_80147628(a0); \
            *(s32 *)(a0 + 0x44) |= 0x40000000; \
        } \
    }

#define DEFINE_func_8014A380() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    void func_8014A380(s32 a0, s32 a1) { \
        s16 buf[4]; \
        func_80015978(a0 + 4, (s32 *)buf); \
        buf[3] = 0; \
        func_8014C4AC(a1, 0x1F, 0, buf, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)); \
    }

#define DEFINE_func_8017C908() \
    extern void ReadGeomOffset(s32 *a0, s32 *a1); \
    extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3); \
    extern void func_8004921C(s32 a0, s32 a1); \
    void func_8017C908(s32 a0, s32 a1) { \
        s32 ofx; \
        s32 ofy; \
        s32 sxy; \
        s32 p; \
        ReadGeomOffset(&ofx, &ofy); \
        func_8004921C(0, 0); \
        RotTransPers(a0, a1, &sxy, &p); \
        func_8004921C(ofx, ofy); \
    }

#define DEFINE_func_80130740() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80130740(void *a0, u16 *a1) { \
        u16 *p = (u16 *)a0; \
        func_80146A6C(0x10, a0, \
                      (s16)(p[3] + a1[0]), \
                      (s16)(p[5] + a1[1]), \
                      (s16)(p[7] + a1[2]), \
                      0, 0); \
    }

#define DEFINE_func_80160BB4() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_80160BB4(s32 *a0) { \
        s32 *v1; \
        a0[0x44 / 4] |= 0x80; \
        func_801553A8(a0); \
        func_80155440(a0); \
        func_80154150((s32)a0, 0x26); \
        func_80154A74((s32)a0, 0x1E); \
        v1 = (s32 *)a0[0x20 / 4]; \
        a0[0x234 / 4] = 0; \
        *(s16 *)((u8 *)v1 + 0x10) = 0xFE9; \
        a0[0x238 / 4] = 0; \
        func_80146CA0(a0); \
    }

#define DEFINE_func_801628F4() \
    extern void func_80162968(s32 a0); \
    void func_801628F4(s32 *a0) { \
        s16 *a2 = (s16 *)a0[0x4 / 4]; \
        s32 *a1 = (s32 *)a0[0x8 / 4]; \
        if (*(s16 *)((u8 *)a2 + 0x7E) != 0) { \
            a1[0x4 / 4] |= 0x80000000; \
        } else { \
            a1[0x4 / 4] &= 0x7FFFFFFF; \
        } \
        a0[0x20 / 4] = *(s16 *)((u8 *)a2 + 0x78); \
        a0[0x24 / 4] = *(s16 *)((u8 *)a2 + 0x7A); \
        a0[0x28 / 4] = *(s16 *)((u8 *)a2 + 0x7C); \
        func_80162968((s32)a0); \
    }

#define DEFINE_func_8016F398() \
    extern void func_80029124(s32, s32); \
    void func_8016F398(void) { \
        func_80029124(0x125, 0); \
        func_80029124(0x126, 0); \
        func_80029124(0x127, 0); \
        func_80029124(0x128, 0); \
        func_80029124(0x129, 0); \
        func_80029124(0x12A, 0); \
        func_80029124(0x12B, 0); \
        func_80029124(0x12C, 0); \
    }

#define DEFINE_func_80172414() \
    extern void func_80161C24(s32, s32); \
    extern void func_8014C010(s32 a0, s32 a1); \
    extern u16 D_800B99DA; \
    void func_80172414(s32 a0) { \
        if (*(u16 *)(a0 + 0xB8) & 0x2000) { \
            func_80161C24(a0, *(u16 *)(a0 + 0x16E)); \
        } \
        if (*(s32 *)(a0 + 0x2C) < (s32)0xFFF90000) { \
            if ((D_800B99DA & 7) == 0) { \
                func_8014C010(a0, 2); \
            } \
        } \
    }

#define DEFINE_func_80131AC8() \
    extern s32 func_80131CF4(s32 a0); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    s32 func_80131AC8(void *a0) { \
        s32 s0 = func_80131CF4(*(s32 *)((u8 *)a0 + 0xBC)) & 0xFFFF; \
        if (s0 != 0) { \
            func_8002D4C8(s0, 0); \
            return s0; \
        } \
        return 0; \
    }

#define DEFINE_func_8014A454() \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    s32 func_8014A454(s32 a0) { \
        s32 v0; \
        if (*(u16 *)(a0 + 0x3C) & 0x4000) { \
            v0 = (s16)func_80012A60(*(s16 *)(a0 + 0x42), \
                                    (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800) & 0xFFF); \
            if (v0 < 0x2AA) { \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_801426D4() \
    extern s32 func_8012AD50(void *a0); \
    void func_801426D4(s32 a0) { \
        s32 s0 = *(s32 *)(a0 + 0x20); \
        s16 fc = *(s16 *)(a0 + 0xFC); \
        if (fc != 0) { \
            *(s16 *)(a0 + 0xFC) = fc - 0x10; \
            *(u16 *)(s0 + 0x18) += 0x800; \
            *(u16 *)(s0 + 0x1A) += 0x800; \
        } else { \
            *(s32 *)(a0 + 0x1C) = 0xC; \
            func_8012AD50((void *)a0); \
            *(u16 *)(s0 + 0x1A) = 0x1800; \
            *(u16 *)(s0 + 0x18) = 0x1800; \
        } \
    }

#define DEFINE_func_80146F58() \
    extern s16 func_8012A68C(void); \
    extern s16 func_8012A758(void); \
    extern void func_8004978C(s16 *a0, void *a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    void func_80146F58(s32 a0, s32 a1) { \
        s16 vec[3]; \
        u8 mat[0x20]; \
        vec[0] = func_8012A68C(); \
        vec[1] = func_8012A758(); \
        vec[2] = 0; \
        func_8004978C(vec, mat); \
        ApplyMatrixSV(mat, (void *)a0, (void *)a1); \
    }

#define DEFINE_func_80147718() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80147718(s32 a0) { \
        s32 s1 = *(s32 *)(a0 + 0x20); \
        s32 s0 = s1 + 0x34; \
        func_80013F3C(s0); \
        func_800126C4(s0, *(s16 *)(s1 + 0x10)); \
        func_80012558(s0, *(s16 *)(s1 + 0x12)); \
        func_800123F0(s0, *(s16 *)(s1 + 0x14)); \
        *(u16 *)(s1 + 0x2C) |= 1; \
    }

#define DEFINE_func_801478B8() \
    extern void func_80147948(s32 a0, s32 a1, s32 a2); \
    extern void func_801479BC(s32 a0, s32 a1, s32 a2); \
    extern void func_80147A30(s32 a0, s32 a1, s32 a2); \
    void func_801478B8(s32 a0, s32 a1, s32 a2, s32 a3) { \
        func_80147948(a0, a1, 0x7FFFFFFF); \
        func_801479BC(a0, a2, 0x7FFFFFFF); \
        func_80147A30(a0, a3, 0x7FFFFFFF); \
    }

#define DEFINE_func_80147CC8() \
    extern void func_80147928(int a0, int a1); \
    extern void func_8014799C(int a0, int a1); \
    extern void func_80147A10(int a0, int a1); \
    extern void func_80147DC0(s32 a0, s32 a1); \
    void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) { \
        func_80147928(a0, a1); \
        func_8014799C(a0, a2); \
        func_80147A10(a0, a3); \
        func_80147DC0(a0, a4); \
    }

#define DEFINE_func_80155B9C() \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern void func_80147324(s32 a0); \
    extern s32 D_800D4DB4; \
    void func_80155B9C(s32 a0) { \
        *(s32 *)(a0 + 0x44) |= 2; \
        func_80148038(a0, 0x30000); \
        func_80147460(a0); \
        if (*(s32 *)(a0 + 0x34) >= 0) { \
            func_80154274((s32 *)a0, (s32)&D_800D4DB4); \
            func_80146CA0((void *)a0); \
            func_80147324(0x447); \
        } \
    }

#define DEFINE_func_80164DD0() \
    extern void func_80148534(s32 a0, s32 a1); \
    extern void func_80015954(s32 a0, s32 a1); \
    extern void func_80149374(s32 a0, s32 a1); \
    void func_80164DD0(s32 a0) { \
        s32 sp10[2]; \
        s32 sp18[2]; \
        s32 s2 = *(s32 *)(a0 + 0x4C); \
        func_80148534((s32)sp10, (s32)sp18); \
        func_80015954((s32)sp10, a0 + 4); \
        func_80149374(s2, a0 + 4); \
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40; \
    }

#define DEFINE_func_8012F7B4() \
    extern s32 func_8012BEE8(s32); \
    extern s32 func_80131A34(s32, s32); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F7B4(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 4) { \
            func_8012BEE8(a0); \
            if (*(s32 *)(a0 + 0x1C) == 1) { \
                if (func_80131A34(a0, 8) == 0) { \
                    func_80131A34(a0, 0x20); \
                } \
            } \
        } \
        func_80131CA8(a0, 7); \
    }

#define DEFINE_func_80154218() \
    extern s32 func_801549F8(s32 a0, s32 a1, s32 a2); \
    extern void func_80154418(void *a0); \
    void func_80154218(u8 *a0, s32 a1, s32 a2) { \
        u8 *s0 = a0; \
        s32 *base = *(s32 **)(s0 + 0xB0); \
        s32 v1 = base[a1]; \
        *(u16 *)(s0 + 0xBA) = 1; \
        *(u16 *)(s0 + 0xB8) = 1; \
        *(s8 *)(s0 + 0xBC) = a2; \
        *(s8 *)(s0 + 0xBD) = a2; \
        *(s32 *)(s0 + 0xB4) = v1; \
        s0[0xDC] = func_801549F8((s32)a0, (s32)&base[a1], a2); \
        func_80154418(s0); \
    }

#define DEFINE_func_8012F1A4() \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    void func_8012F1A4(s32 *a0, s32 a1, s32 *a2) { \
        func_800484EC((s32)a0, a1, (s32)a2); \
        a2[0] += a0[0x14 / 4] << 16; \
        a2[1] += a0[0x18 / 4] << 16; \
        a2[2] += a0[0x1C / 4] << 16; \
    }

#define DEFINE_func_8012FC30() \
    extern void func_80131B14(); \
    extern void func_8012B23C(s32 a0); \
    extern s32 func_80131A34(s32, s32); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FC30(s32 a0) { \
        *(s8 *)(a0 + 0xC1) = 0xA; \
        if (*(s32 *)(a0 + 0xB4) & 0x400) { \
            func_80131B14(); \
            *(s8 *)(a0 + 0xC2) = 0; \
            *(u16 *)(a0 + 0x98) = 0; \
            func_8012B23C(a0); \
            func_80131A34(a0, 8); \
            func_8002D4C8(0xA74, 0); \
        } \
        func_80131CA8(a0, 0x1A); \
    }

#define DEFINE_func_801746DC() \
    extern void func_8016EE94(); \
    extern void func_80174684(void *); \
    extern void func_80172710(void); \
    extern s32 func_80172760(s32 a0); \
    void func_801746DC(void) { \
        func_8016EE94((s32)func_80172710, 0x1000000); \
        func_80174684((void *)func_80172760); \
    }

#define DEFINE_func_8012B8A4() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern u16 D_80126B66; \
    extern u16 D_80126B5E; \
    s32 func_8012B8A4(s16 *a0) { \
        s16 cx = a0[7]; \
        s16 dx = D_80126B66; \
        s16 dy = D_80126B5E; \
        s16 cy = a0[3]; \
        return (ratan2(cx - dx, dy - cy) - 0x400) & 0xFFF; \
    }

#define DEFINE_func_80160B70() \
    extern s32 func_80161104(void); \
    extern void func_80160BB4(s32 *a0); \
    void func_80160B70(s32 a0) { \
        if (func_80161104()) { \
            func_80160BB4(a0); \
        } else { \
            *(s32 *)(a0 + 0x1AC) = 0; \
        } \
    }

#define DEFINE_func_8016F4FC() \
    extern void func_801719A4(int a0, int a1); \
    extern void func_800D1724(s32 a0); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_8016F4FC(void *a0) { \
        func_801719A4((int)a0, 1); \
        func_800D1724(D_8011F738); \
        func_80171928(a0); \
    }

#define DEFINE_func_801702B8() \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_801702B8(s32 a0) { \
        if (func_80171AB0(a0, &D_8011F738) == 0) { \
            func_80171928((void *)a0); \
        } \
    }

#define DEFINE_func_80132EF4() \
    extern u8 *func_8012913C(s32 a0); \
    extern void func_80129350(s32 a0, s32 a1); \
    s32 func_80132EF4(s32 a0, s32 a1) { \
        s32 s0 = func_8012913C(a1 & 0xFFFF); \
        if (s0 != 0) { \
            func_80129350(s0, a0); \
        } \
        return s0; \
    }

#define DEFINE_func_801484E8() \
    extern s32 func_80154358(void *a0); \
    extern void func_801485B8(s32 a0, s32 a1, s32 a2); \
    extern s32 D_80126B58; \
    void func_801484E8(s32 a0, s32 a1) { \
        s32 v0 = func_80154358(&D_80126B58); \
        func_801485B8(v0 - 0x10, a0, a1); \
    }

#define DEFINE_func_8014856C() \
    extern s32 func_80154358(void *a0); \
    extern void func_801485B8(s32 a0, s32 a1, s32 a2); \
    extern s32 D_80126B58; \
    void func_8014856C(s32 a0, s32 a1) { \
        s32 v0 = func_80154358(&D_80126B58); \
        func_801485B8(v0 - 0x8, a0, a1); \
    }

#define DEFINE_func_80150C48() \
    extern s32 func_80150480(s32 a0); \
    extern s32 D_800AE6B0; \
    extern u16 D_800AE6DC; \
    void func_80150C48(s32 a0) { \
        if (func_80150480(a0) != 0) { \
            s32 p = *(s32 *)(a0 + 0x1A4); \
            D_800AE6B0 = *(s32 *)(p + 0xDC); \
            p = *(s32 *)(a0 + 0x1A4); \
            D_800AE6DC = *(u16 *)(p + 0xFC); \
        } \
    }

#define DEFINE_func_801291C0() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s16 D_8011DB30; \
    u8 *func_801291C0(void) { \
        u8 *p = (u8 *)&D_8011DB30; \
        s32 i = 0; \
    loop: \
        if (*(u16 *)p == 0) { \
            func_80016714(p, 0x38); \
            return p; \
        } \
        if (++i < 0x80) { \
            p += 0x38; \
            goto loop; \
        } \
        return 0; \
    }

#define DEFINE_func_80173648() \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern s32 func_80172664(s32 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B3E; \
    void func_80173648(u8 *a0) { \
        u8 *s0 = a0; \
        s16 *p = &D_80126B3E; \
        if (*p != 0) { \
            func_80171CC4(s0, (u8 *)p - 6); \
        } \
        if (func_80172664((s32 *)s0) == 0) { \
            func_80171A1C(s0); \
            func_80174650((s32)s0); \
        } \
    }

#define DEFINE_func_80160F70() \
    extern s32 func_80146E98(s32 a0); \
    extern void func_800D0F4C(s32 a0); \
    extern void func_8014BB24(s32 a0, s32 a1, s32 a2); \
    extern void func_8014BD24(s32 a0, s32 a1); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_80110EC0; \
    void func_80160F70(s32 a0) { \
        if (func_80146E98(a0) != 0) { \
            func_800D0F4C(0xA); \
            func_8014BB24(a0, 0x96, 0); \
            func_8014BD24(a0, 0x96); \
            *(s32 *)(a0 + 0x198) = func_8013767C(&D_80110EC0); \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_80168A14() \
    extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80168A14(s32 *a0) { \
        func_80168BDC((s32)a0, 8, 1, 2); \
        func_80146A6C(3, (s32)a0, \
                      *(s16 *)((u8 *)a0 + 0x6), \
                      *(s16 *)((u8 *)a0 + 0xA), \
                      *(s16 *)((u8 *)a0 + 0xE), \
                      -5, 0xC0009C00); \
        *(u16 *)((u8 *)a0 + 0x2) += 1; \
    }

#define DEFINE_func_8014462C() \
    extern void func_8012AD80(s32 a0); \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_8012C218(void *a0); \
    void func_8014462C(u8 *a0) { \
        u8 *s1 = *(u8 **)(a0 + 0xCC); \
        func_8012AD80((s32)a0); \
        *(u16 *)(s1 + 8) = *(u16 *)(a0 + 6); \
        *(u16 *)(s1 + 0xA) = *(u16 *)(a0 + 0xA); \
        *(u16 *)(s1 + 0xC) = *(u16 *)(a0 + 0xE); \
        if (func_80128ED8(s1, a0 + 0xD0)) { \
            func_80016714(s1, 0x38); \
            func_8012C218(a0); \
        } \
    }

#define DEFINE_func_80152254() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_80153800(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_801522CC(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_80152254(s32 *a0) { \
        /* reserved stack local sets frame 0x28 (16-byte local region) */ \
        volatile s32 pad[4]; \
        func_80149020(a0); \
        if (func_80153800((s32)a0) == 0) { \
            *(u16 *)((u8 *)a0 + 0x4) = 0; \
            *(u16 *)((u8 *)a0 + 0x8) = 0; \
            *(u16 *)((u8 *)a0 + 0xC) = 0; \
            *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88); \
            *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A); \
            *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C); \
            func_80146D90((s32)a0); \
            func_801522CC((s32)a0); \
            func_80159B3C((s32)a0); \
            func_80165718((s32)a0); \
        } \
    }

#define DEFINE_func_80152A50() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_80153800(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_80152AC8(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_80152A50(s32 *a0) { \
        /* reserved stack local sets frame 0x28 (16-byte local region) */ \
        volatile s32 pad[4]; \
        func_80149020(a0); \
        if (func_80153800((s32)a0) == 0) { \
            *(u16 *)((u8 *)a0 + 0x4) = 0; \
            *(u16 *)((u8 *)a0 + 0x8) = 0; \
            *(u16 *)((u8 *)a0 + 0xC) = 0; \
            *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88); \
            *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A); \
            *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C); \
            func_80146D90((s32)a0); \
            func_80152AC8((s32)a0); \
            func_80159B3C((s32)a0); \
            func_80165718((s32)a0); \
        } \
    }

#define DEFINE_func_80152F44() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_80153800(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_80152FBC(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_80152F44(s32 *a0) { \
        /* reserved stack local sets frame 0x28 (16-byte local region) */ \
        volatile s32 pad[4]; \
        func_80149020(a0); \
        if (func_80153800((s32)a0) == 0) { \
            *(u16 *)((u8 *)a0 + 0x4) = 0; \
            *(u16 *)((u8 *)a0 + 0x8) = 0; \
            *(u16 *)((u8 *)a0 + 0xC) = 0; \
            *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88); \
            *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A); \
            *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C); \
            func_80146D90((s32)a0); \
            func_80152FBC((s32)a0); \
            func_80159B3C((s32)a0); \
            func_80165718((s32)a0); \
        } \
    }

#define DEFINE_func_80153204() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_80153800(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_8015327C(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_80153204(s32 *a0) { \
        /* reserved stack local sets frame 0x28 (16-byte local region) */ \
        volatile s32 pad[4]; \
        func_80149020(a0); \
        if (func_80153800((s32)a0) == 0) { \
            *(u16 *)((u8 *)a0 + 0x4) = 0; \
            *(u16 *)((u8 *)a0 + 0x8) = 0; \
            *(u16 *)((u8 *)a0 + 0xC) = 0; \
            *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88); \
            *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A); \
            *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C); \
            func_80146D90((s32)a0); \
            func_8015327C((s32)a0); \
            func_80159B3C((s32)a0); \
            func_80165718((s32)a0); \
        } \
    }

#define DEFINE_func_801534D8() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_80153800(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_80153550(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_801534D8(s32 *a0) { \
        /* reserved stack local sets frame 0x28 (16-byte local region) */ \
        volatile s32 pad[4]; \
        func_80149020(a0); \
        if (func_80153800((s32)a0) == 0) { \
            *(u16 *)((u8 *)a0 + 0x4) = 0; \
            *(u16 *)((u8 *)a0 + 0x8) = 0; \
            *(u16 *)((u8 *)a0 + 0xC) = 0; \
            *(u16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a0 + 0x88); \
            *(u16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A); \
            *(u16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C); \
            func_80146D90((s32)a0); \
            func_80153550((s32)a0); \
            func_80159B3C((s32)a0); \
            func_80165718((s32)a0); \
        } \
    }

#define DEFINE_func_8017AE08() \
    extern s16 func_80174764(void); \
    s32 func_8017AE08(void) { \
        return ((s32 (*)(void))func_80174764)() == 1; \
    }

#define DEFINE_func_8012CBF4() \
    extern u8 D_800D3918[]; \
    extern s32 func_8012CC88(); \
    void func_8012CBF4(s32 a0) { \
        func_8012CC88(a0, 0x11, (s32)D_800D3918); \
    }

#define DEFINE_func_80144A68() \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    void func_80144A68(s32 *a0) { \
        *(s16 *)a0 = 0xC6; \
        func_8012AD44(a0, 0); \
    }

#define DEFINE_func_8014B12C() \
    extern s32 D_80126B58; \
    extern s32 func_8014B154(s32 *a0); \
    void func_8014B12C(void) { \
        func_8014B154(&D_80126B58); \
    }

#define DEFINE_func_8014B2A8() \
    extern s32 D_80126B58; \
    extern void func_8014B2F8(void); \
    void func_8014B2A8(void) { \
        ((void (*)(s32 *))func_8014B2F8)(&D_80126B58); \
    }

#define DEFINE_func_8014B2D0() \
    extern s32 D_80126B58; \
    extern void func_8014B310(void); \
    void func_8014B2D0(void) { \
        ((void (*)(s32 *))func_8014B310)(&D_80126B58); \
    }

#define DEFINE_func_80156648() \
    extern void func_80156A14(s32 *a0); \
    void func_80156648(s32 *a0) { \
        *((u8 *)a0 + 0x1A8) = 0; \
        *((u8 *)a0 + 0x1A9) = 0; \
        *((u8 *)a0 + 0x1C0) = 0; \
        func_80156A14(a0); \
    }

#define DEFINE_func_80172560() \
    extern s32 func_80013450(s32); \
    s32 func_80172560(u8 *a0, u8 *a1) { \
        *(s16 *)(a1 + 2) = *(u16 *)(a0 + 0xA); \
        return func_80013450((s32)(a0 + 4)) < 0x10; \
    }

#define DEFINE_func_8014AD7C() \
    extern s32 D_80126B58; \
    extern void func_8014ADA8(s32 a0, s32 a1); \
    void func_8014AD7C(s32 a0) { \
        func_8014ADA8((s32)&D_80126B58, a0); \
    }

#define DEFINE_func_80146DB8() \
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3); \
    void func_80146DB8(s32 *a0, s32 *a1) { \
        func_80146DE8(a0, a1[0], a1[1], a1[2]); \
    }

#define DEFINE_func_80154B4C() \
    extern void func_80154B7C(u8 *a0, s32 a1); \
    void func_80154B4C(u8 *a0, s32 a1) { \
        if (*(s32 *)(a0 + 0xD0) != a1) { \
            func_80154B7C(a0, a1); \
        } \
    }

#define DEFINE_func_80154B98() \
    extern void func_80154BC8(void *a0, s32 a1, s32 a2); \
    void func_80154B98(void *a0, s32 a1, s32 a2) { \
        if (*(s32 *)((s32)a0 + 0xD0) != a1) { \
            func_80154BC8(a0, a1, a2); \
        } \
    }

#define DEFINE_func_80158AB4() \
    extern void func_80158AE4(void *a0); \
    extern void func_80146CA0(void *a0); \
    void func_80158AB4(void *a0) { \
        func_80158AE4(a0); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_8016EF78() \
    extern s32 func_8016EFC8(); \
    extern void func_801726D0(void *a0); \
    extern s32 D_80126B58; \
    void func_8016EF78(s32 a0) { \
        func_8016EFC8(a0); \
        func_801726D0(&D_80126B58); \
    }

#define DEFINE_func_8016F5B0() \
    extern void func_8014706C(void *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F5B0(void *a0) { \
        func_8014706C(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F5E0() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F5E0(u8 *a0) { \
        func_80147060(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F7D4() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016F804(void *a0); \
    void func_8016F7D4(u8 *a0) { \
        func_80171990(a0); \
        func_8016F804(a0); \
    }

#define DEFINE_func_8017041C() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8017044C(u8 *a0); \
    void func_8017041C(u8 *a0) { \
        func_80171990(a0); \
        func_8017044C(a0); \
    }

#define DEFINE_func_801704EC() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8017051C(void *a0); \
    void func_801704EC(u8 *a0) { \
        func_80171990(a0); \
        func_8017051C(a0); \
    }

#define DEFINE_func_801706E8() \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170718(void *a0); \
    void func_801706E8(u8 *a0) { \
        func_80171990(a0); \
        func_80170718(a0); \
    }

#define DEFINE_func_80170C44() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171928(void *a0); \
    void func_80170C44(u8 *a0) { \
        func_80147060(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_80150F80() \
    extern s32 func_80151184(s32 a0, s32 a1, s32 a2); \
    extern u8 D_80078EC1; \
    void func_80150F80(s32 a0) { \
        if (D_80078EC1 != 0xC) { \
            func_80151184(a0, 0xC007, 0x20); \
        } \
    }

#define DEFINE_func_80155518() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_801555F4(void *a0); \
    void func_80155518(s32 *a0) { \
        func_80147078(a0, 5); \
        func_801555F4(a0); \
    }

#define DEFINE_func_8015554C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80155580(void *a0); \
    void func_8015554C(s32 *a0) { \
        func_80147078(a0, 5); \
        func_80155580(a0); \
    }

#define DEFINE_func_801574DC() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_801575E4(void *a0); \
    void func_801574DC(s32 *a0) { \
        func_80147078(a0, 6); \
        func_801575E4(a0); \
    }

#define DEFINE_func_80157510() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80157544(void *a0); \
    void func_80157510(s32 *a0) { \
        func_80147078(a0, 6); \
        func_80157544(a0); \
    }

#define DEFINE_func_8015A230() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015A264(void *a0); \
    void func_8015A230(s32 *a0) { \
        func_80147078(a0, 0x1); \
        func_8015A264(a0); \
    }

#define DEFINE_func_8015BF7C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015BFF4(void *a0); \
    void func_8015BF7C(s32 *a0) { \
        func_80147078(a0, 0x4); \
        func_8015BFF4(a0); \
    }

#define DEFINE_func_8015C6E0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015C714(void *a0); \
    void func_8015C6E0(s32 *a0) { \
        func_80147078(a0, 0x9); \
        func_8015C714(a0); \
    }

#define DEFINE_func_8015CC40() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015CC74(s32 *a0); \
    void func_8015CC40(s32 *a0) { \
        func_80147078(a0, 0xB); \
        func_8015CC74(a0); \
    }

#define DEFINE_func_8015CF8C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015CFC0(s32 *a0); \
    void func_8015CF8C(s32 *a0) { \
        func_80147078(a0, 0xC); \
        func_8015CFC0(a0); \
    }

#define DEFINE_func_8015DA5C() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern int func_8015E0D4(int); \
    void func_8015DA5C(s32 a0) { \
        func_80154A74(a0, 0x11); \
        func_8015E0D4(a0); \
    }

#define DEFINE_func_8015DAC4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015DAF8(s32 *a0); \
    void func_8015DAC4(s32 *a0) { \
        func_80147078(a0, 0xE); \
        func_8015DAF8(a0); \
    }

#define DEFINE_func_8015DE24() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015DE58(s32 *a0); \
    void func_8015DE24(s32 *a0) { \
        func_80147078(a0, 0xF); \
        func_8015DE58(a0); \
    }

#define DEFINE_func_8015E880() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015E8E8(s32 *a0); \
    void func_8015E880(s32 *a0) { \
        func_80147078(a0, 0x11); \
        func_8015E8E8(a0); \
    }

#define DEFINE_func_8015E8B4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015E9B8(s32 *a0); \
    void func_8015E8B4(s32 *a0) { \
        func_80147078(a0, 0x11); \
        func_8015E9B8(a0); \
    }

#define DEFINE_func_8015EFD8() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015F00C(s32 *a0); \
    void func_8015EFD8(s32 *a0) { \
        func_80147078(a0, 0x13); \
        func_8015F00C(a0); \
    }

#define DEFINE_func_8015F2BC() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015F380(); \
    void func_8015F2BC(s32 *a0) { \
        func_80147078(a0, 0x14); \
        func_8015F380(a0); \
    }

#define DEFINE_func_80160E3C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80160F00(); \
    void func_80160E3C(s32 *a0) { \
        func_80147078(a0, 0x1E); \
        func_80160F00(a0); \
    }

#define DEFINE_func_80160E70() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80160EA4(); \
    void func_80160E70(s32 *a0) { \
        func_80147078(a0, 0x1E); \
        func_80160EA4(a0); \
    }

#define DEFINE_func_80165624() \
    extern u8 func_80165658(s32 a0, s32 a1); \
    extern u8 D_80078EC1; \
    extern s16 D_80078EB8; \
    s32 func_80165624(s32 a0) { \
        return (u32)(u16)D_80078EB8 < (u32)(func_80165658(a0, D_80078EC1 & 0x7F) & 0x7F); \
    }

#define DEFINE_func_8016B3F4() \
    extern s32 func_8016B448(s32, s32); \
    extern s32 func_8016BA48(s32 a0); \
    void func_8016B3F4(s32 a0) { \
        func_8016B448(a0, 1); \
        func_8016BA48(a0); \
    }

#define DEFINE_func_8016F764() \
    extern void func_80171928(void *a0); \
    void func_8016F764(void *a0) { \
        s32 v0 = *(s32 *)((u8 *)a0 + 0x200) - 1; \
        *(s32 *)((u8 *)a0 + 0x200) = v0; \
        if (v0 == -1) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_8016FFA8() \
    extern s32 func_80171990(u8 *a0); \
    void func_8016FFA8(u8 *a0) { \
        *(u16 *)(a0 + 0xAC) |= 0x40; \
        *(u16 *)(a0 + 0xAA) |= 0x40; \
        func_80171990(a0); \
    }

#define DEFINE_func_801735B8() \
    extern void func_80171A1C(u8 *a0); \
    void func_801735B8(u8 *a0) { \
        *(u16 *)(a0 + 0xAC) |= 0x40; \
        *(u16 *)(a0 + 0xAA) |= 0x40; \
        func_80171A1C(a0); \
    }

#define DEFINE_func_80175150() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80175184(); \
    void func_80175150(s32 *a0) { \
        func_80147078(a0, 0x8); \
        func_80175184(a0); \
    }

#define DEFINE_func_8012A8B0() \
    extern void func_8012AAAC(void); \
    void func_8012A8B0(u8 *a0, s32 a1) { \
        u16 v0 = *(u16 *)(a0 + 0x72); \
        *(s32 *)(a0 + 0x90) = a1; \
        *(s32 *)(a0 + 0x94) = 0; \
        *(s32 *)(a0 + 0x9C) = 0; \
        *(s16 *)(a0 + 0x9A) = 0; \
        *(u16 *)(a0 + 0x72) = v0 & 0xF9FF; \
        func_8012AAAC(); \
    }

#define DEFINE_func_80151038() \
    extern s32 func_80151184(s32 a0, s32 a1, s32 a2); \
    extern s16 currentLocationId; \
    void func_80151038(s32 a0) { \
        s32 a2 = 0x18; \
        if (currentLocationId == 0x30A0) { \
            a2 = 0x30; \
        } \
        func_80151184(a0, 0xC00C, a2); \
    }

#define DEFINE_func_801555BC() \
    extern s32 func_80161104(void); \
    extern void func_801555F4(void *); \
    void func_801555BC(void *a0) { \
        if (func_80161104()) { \
            func_801555F4(a0); \
        } \
    }

#define DEFINE_func_80157E00() \
    extern s32 func_80161104(void); \
    extern void func_80157E38(void *); \
    void func_80157E00(void *a0) { \
        if (func_80161104()) { \
            func_80157E38(a0); \
        } \
    }

#define DEFINE_func_80158000() \
    extern s32 func_80161104(void); \
    extern void func_80158038(void *); \
    void func_80158000(void *a0) { \
        if (func_80161104()) { \
            func_80158038(a0); \
        } \
    }

#define DEFINE_func_80158288() \
    extern s32 func_80161104(void); \
    extern void func_801582C0(void *); \
    void func_80158288(void *a0) { \
        if (func_80161104()) { \
            func_801582C0(a0); \
        } \
    }

#define DEFINE_func_80159BAC() \
    extern s32 func_80161104(void); \
    extern void func_80159BE4(s32); \
    void func_80159BAC(s32 a0) { \
        if (func_80161104() != 0) { \
            func_80159BE4(a0); \
        } \
    }

#define DEFINE_func_8015A2A0() \
    extern s32 func_80161104(void); \
    extern void func_8015A2D8(s32); \
    void func_8015A2A0(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015A2D8(a0); \
        } \
    }

#define DEFINE_func_8015AD78() \
    extern s32 func_80161104(void); \
    extern void func_8015ADB0(s32); \
    void func_8015AD78(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015ADB0(a0); \
        } \
    }

#define DEFINE_func_8015C08C() \
    extern s32 func_80161104(void); \
    extern void func_8015C0C4(s32); \
    void func_8015C08C(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015C0C4(a0); \
        } \
    }

#define DEFINE_func_8015C750() \
    extern s32 func_80161104(void); \
    extern void func_8015C788(s32); \
    void func_8015C750(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015C788(a0); \
        } \
    }

#define DEFINE_func_8015CB94() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015CB94(s32 a0) { \
        *(s32 *)(a0 + 0x170) = 0; \
        func_801553C0(a0); \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_8015D544() \
    extern s32 func_80161104(void); \
    extern void func_8015D57C(s32); \
    void func_8015D544(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015D57C(a0); \
        } \
    }

#define DEFINE_func_8015DB34() \
    extern s32 func_80161104(void); \
    extern void func_8015DB6C(s32); \
    void func_8015DB34(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015DB6C(a0); \
        } \
    }

#define DEFINE_func_8015DE94() \
    extern s32 func_80161104(void); \
    extern void func_8015DECC(s32); \
    void func_8015DE94(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015DECC(a0); \
        } \
    }

#define DEFINE_func_8015E1F4() \
    extern s32 func_80161104(void); \
    extern void func_8015E22C(s32); \
    void func_8015E1F4(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015E22C(a0); \
        } \
    }

#define DEFINE_func_8015E924() \
    extern s32 func_80161104(void); \
    extern void func_8015E95C(s32); \
    void func_8015E924(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015E95C(a0); \
        } \
    }

#define DEFINE_func_8015EE44() \
    extern s32 func_80161104(void); \
    extern void func_8015EE7C(s32); \
    void func_8015EE44(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015EE7C(a0); \
        } \
    }

#define DEFINE_func_8015F048() \
    extern s32 func_80161104(void); \
    extern void func_8015F080(s32); \
    void func_8015F048(s32 a0) { \
        if (func_80161104() != 0) { \
            func_8015F080(a0); \
        } \
    }

#define DEFINE_func_8015F810() \
    extern s32 func_80161104(void); \
    extern void func_8015F848(s32 *a0); \
    void func_8015F810(s32 *a0) { \
        if (func_80161104() != 0) { \
            func_8015F848(a0); \
        } \
    }

#define DEFINE_func_80160174() \
    extern s32 func_80161104(void); \
    extern void func_801601AC(s32 *a0); \
    void func_80160174(s32 *a0) { \
        if (func_80161104()) { \
            func_801601AC(a0); \
        } \
    }

#define DEFINE_func_801601AC() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80146C98(s32 *a0, s16 a1); \
    void func_801601AC(s32 *a0) { \
        func_80154150((s32)a0, 0x21); \
        func_80146C98(a0, 1); \
    }

#define DEFINE_func_801603D8() \
    extern s32 func_80161104(void); \
    extern void func_80160410(s32 *a0); \
    void func_801603D8(s32 *a0) { \
        if (func_80161104()) { \
            func_80160410(a0); \
        } \
    }

#define DEFINE_func_80160888() \
    extern s32 func_80161104(void); \
    extern void func_801608C0(s32 *a0); \
    void func_80160888(s32 *a0) { \
        if (func_80161104()) { \
            func_801608C0(a0); \
        } \
    }

#define DEFINE_func_8016533C() \
    extern u8 D_80078EC1; \
    extern s32 D_80126B58; \
    extern u8 D_80126CF8; \
    extern s32 func_801659DC(u8 *a0); \
    void func_8016533C(void) { \
        D_80126CF8 = D_80078EC1; \
        func_801659DC((u8 *)&D_80126B58); \
    }

#define DEFINE_func_8016F578() \
    extern void func_80147084(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F578(s32 *a0) { \
        func_80147084(a0); \
        func_801472B4(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F610() \
    extern void func_8016F288(void); \
    extern void func_80148634(void *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F610(void *a0) { \
        func_8016F288(); \
        func_80148634(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F648() \
    extern void func_8016F264(void); \
    extern void func_80148634(void *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F648(void *a0) { \
        func_8016F264(); \
        func_80148634(a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F8AC() \
    extern void *D_8011F738; \
    extern void func_80172358(u8 *a0, u8 *a1); \
    extern void func_80171928(void *a0); \
    void func_8016F8AC(u8 *a0) { \
        func_80172358(a0, (u8 *)&D_8011F738); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016FD7C() \
    extern s32 func_80172658(s32 *a0); \
    extern void func_80171928(void *a0); \
    void func_8016FD7C(s32 *a0) { \
        if (func_80172658(a0)) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_801439C0() \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_8012C218(void *a0); \
    void func_801439C0(u8 *a0) { \
        if (a0 != 0) { \
            func_80016714(*(void **)(a0 + 0xCC), 0x38); \
            func_8012C218(a0); \
        } \
    }

#define DEFINE_func_80150FD8() \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u16 D_800B99DA; \
    void func_80150FD8(s32 a0) { \
        if (D_800B99DA & 7) { \
            func_80146994(0x34, a0, 0, 0); \
        } \
    }

#define DEFINE_func_80164270() \
    extern void func_80162D88(s32 *a0); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_80164270(s32 *a0) { \
        s32 *s = a0; \
        func_80162D88(s); \
        func_80146E90(s, 0x20); \
        func_80146CA0(s); \
    }

#define DEFINE_func_8016F870() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016F8AC(u8 *a0); \
    void func_8016F870(u8 *a0) { \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_8016F8AC(a0); \
    }

#define DEFINE_func_8016F920() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016F95C(void *a0); \
    void func_8016F920(u8 *a0) { \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_8016F95C(a0); \
    }

#define DEFINE_func_8016FCCC() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FD08(u8 *a0); \
    void func_8016FCCC(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_8016FD08(a0); \
    }

#define DEFINE_func_8016FDF0() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FE2C(u8 *a0); \
    void func_8016FDF0(u8 *a0) { \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_8016FE2C(a0); \
    }

#define DEFINE_func_8016FF6C() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FFA8(u8 *a0); \
    void func_8016FF6C(u8 *a0) { \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_8016FFA8(a0); \
    }

#define DEFINE_func_8017018C() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801701C8(u8 *a0); \
    void func_8017018C(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_801701C8(a0); \
    }

#define DEFINE_func_8017027C() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801702B8(s32 a0); \
    void func_8017027C(u8 *a0) { \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_801702B8((s32)a0); \
    }

#define DEFINE_func_80170338() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170374(u8 *a0); \
    void func_80170338(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_80170374(a0); \
    }

#define DEFINE_func_80170584() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801705C0(u8 *a0); \
    void func_80170584(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_801705C0(a0); \
    }

#define DEFINE_func_80170670() \
    extern void *D_8011F738; \
    extern void func_8012A568(void (*a0)(void)); \
    extern void func_80171928(void *a0); \
    void func_80170670(void *a0) { \
        func_8012A568((void (*)(void))D_8011F738); \
        func_80171928(a0); \
    }

#define DEFINE_func_801707D4() \
    extern s32 func_80174ED4(void); \
    extern void func_80171928(void *a0); \
    void func_801707D4(void *a0) { \
        if ((s16)func_80174ED4() != 0) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_80170DA4() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170DE0(u8 *a0); \
    void func_80170DA4(u8 *a0) { \
        func_801719A4((int)a0, 3); \
        func_80171990(a0); \
        func_80170DE0(a0); \
    }

#define DEFINE_func_80170E70() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170EAC(u8 *a0); \
    void func_80170E70(u8 *a0) { \
        func_801719A4((int)a0, 3); \
        func_80171990(a0); \
        func_80170EAC(a0); \
    }

#define DEFINE_func_80170F74() \
    extern void *D_8011F738; \
    extern void func_80029124(s32, s32); \
    extern void func_80171928(void *a0); \
    void func_80170F74(void *a0) { \
        func_80029124((s32)D_8011F738, 1); \
        func_80171928(a0); \
    }

#define DEFINE_func_80171028() \
    extern void *D_8011F738; \
    extern void func_80029124(s32, s32); \
    extern void func_80171928(void *a0); \
    void func_80171028(void *a0) { \
        func_80029124((s32)D_8011F738, 0); \
        func_80171928(a0); \
    }

#define DEFINE_func_801710A0() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801710DC(u8 *a0); \
    void func_801710A0(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_801710DC(a0); \
    }

#define DEFINE_func_8017484C() \
    extern s32 func_8016F0AC(); \
    extern s32 D_80126B9C; \
    void func_8017484C(s32 a0) { \
        func_8016F0AC(a0); \
        D_80126B9C &= 0xFBFFFFFF; \
    }

#define DEFINE_func_80175114() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80175184(s32 *a0); \
    void func_80175114(s32 *a0) { \
        func_80147078(a0, 8); \
        *(s16 *)((s32)a0 + 2) = 1; \
        func_80175184(a0); \
    }

#define DEFINE_func_80152C40() \
    extern void func_80149020(s32 *a0); \
    extern void func_80152C80(s32 *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    void func_80152C40(s32 *a0) { \
        func_80149020(a0); \
        func_80152C80(a0); \
        func_80159B3C(a0); \
        func_80165718((s32)a0); \
    }

#define DEFINE_func_801541D8() \
    extern void func_80154218(u8 *a0, s32 a1, s32 a2); \
    void func_801541D8(u8 *a0, s32 a1, s32 a2) { \
        if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 **)(a0 + 0xB0))[a1]) { \
            func_80154218(a0, a1, a2); \
        } \
    }

#define DEFINE_func_80154A74() \
    extern void func_80154AB4(s32 a0, s32 a1); \
    void func_80154A74(s32 a0, s32 a1) { \
        if (*(s32 *)(a0 + 0xD0) != ((s32 *)*(s32 **)(a0 + 0xCC))[a1]) { \
            func_80154AB4(a0, a1); \
        } \
    }

#define DEFINE_func_80154AE0() \
    extern void func_80154B20(s32 a0, s32 a1, s32 a2); \
    void func_80154AE0(s32 a0, s32 a1, s32 a2) { \
        if (*(s32 *)(a0 + 0xD0) != ((s32 *)*(s32 **)(a0 + 0xCC))[a1]) { \
            func_80154B20(a0, a1, a2); \
        } \
    }

#define DEFINE_func_80157880() \
    extern void func_8014ED28(s32 a0); \
    extern void func_8014D3E0(s32 a0); \
    extern void func_8014FA04(s32 a0); \
    extern void func_801578C0(s32 a0); \
    void func_80157880(s32 a0) { \
        func_8014ED28(a0); \
        func_8014D3E0(a0); \
        func_8014FA04(a0); \
        func_801578C0(a0); \
    }

#define DEFINE_func_801585AC() \
    extern u16 func_80148800(s32 *a0); \
    s32 func_801585AC(s32 *a0) { \
        u16 r = func_80148800(a0); \
        u16 v = *(u16 *)((u8 *)a0 + 0x244) | r; \
        s32 m; \
        *(u16 *)((u8 *)a0 + 0x244) = v; \
        m = v & 0x10; \
        return m != 0; \
    }

#define DEFINE_func_80161278() \
    extern s32 D_801152BC; \
    extern s32 func_801612B8(void *a0, s32 a1); \
    extern void func_80161374(void *a0, s32 a1); \
    void func_80161278(void *a0) { \
        s32 r; \
        D_801152BC = 0; \
        r = func_801612B8(a0, 1); \
        func_80161374(a0, r); \
    }

#define DEFINE_func_80165024() \
    extern s32 func_80146E98(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern void func_801651B8(void *a0); \
    void func_80165024(void *a0) { \
        if (func_80146E98((s32)a0)) { \
            func_80146CA0(a0); \
        } \
        func_801651B8(a0); \
    }

#define DEFINE_func_801655E4() \
    extern u8 D_80078EC1; \
    extern u8 func_80165658(s32 a0, s32 a1); \
    extern void func_8014BD60(s32 a0, s32 a1); \
    void func_801655E4(s32 a0) { \
        func_8014BD60(a0, func_80165658(a0, D_80078EC1 & 0x7F) & 0x7F); \
    }

#define DEFINE_func_8016FA44() \
    extern void *D_8011F738; \
    extern s32 func_80171C64(s32 a0, s32 a1); \
    extern void func_80171928(void *a0); \
    void func_8016FA44(s32 a0) { \
        if (func_80171C64(a0, *(u8 *)&D_8011F738)) { \
            func_80171928((void *)a0); \
        } \
    }

#define DEFINE_func_8016FB10() \
    extern void *D_8011F738; \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern s32 func_80171990(u8 *a0); \
    void func_8016FB10(void *a0) { \
        if (func_80171CC4(a0, &D_8011F738)) { \
            func_80171990((u8 *)a0); \
        } \
    }

#define DEFINE_func_8016FC24() \
    extern void *D_8011F738; \
    extern s32 func_80171B4C(s32 a0, s32 a1); \
    extern s32 func_80171990(u8 *a0); \
    void func_8016FC24(s32 a0) { \
        if (func_80171B4C(a0, *(u8 *)&D_8011F738)) { \
            func_80171990((u8 *)a0); \
        } \
    }

#define DEFINE_func_80170CB0() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_8017197C(u8 *a0); \
    extern void func_80170CF0(void *a0); \
    void func_80170CB0(u8 *a0) { \
        func_801719A4((int)a0, 3); \
        a0[0x217] = 0; \
        func_8017197C(a0); \
        func_80170CF0(a0); \
    }

#define DEFINE_func_80172A8C() \
    extern s16 D_80126B30; \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern void func_80171A1C(u8 *a0); \
    void func_80172A8C(void *a0) { \
        if (func_80171CC4(a0, &D_80126B30)) { \
            func_80171A1C((u8 *)a0); \
        } \
    }

#define DEFINE_func_80172ACC() \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_80172ACC(u8 *a0) { \
        u8 *p = *(u8 **)(a0 + 0x20); \
        u16 v = *(u16 *)(a0 + 0x132); \
        *(s16 *)(a0 + 0x136) = 0; \
        *(u16 *)(p + 0x12) = v; \
        func_80171A1C(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_80172E94() \
    extern u8 D_800D5A34[]; \
    extern s32 D_80126B58; \
    extern s16 D_80126B30; \
    extern void func_8017303C(void *); \
    extern s32 func_80174650(s32); \
    void func_80172E94(void) { \
        func_8017303C((void *)D_800D5A34); \
        D_80126B30 = 0; \
        func_80174650((s32)&D_80126B58); \
    }

#define DEFINE_func_80173770() \
    extern s32 D_80127508; \
    extern void func_801723C4(s32 a0, s32 a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_80173770(u8 *a0) { \
        func_801723C4((s32)a0, D_80127508); \
        func_80171A1C(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_80174714() \
    extern s32 func_800CF8CC(void); \
    extern void func_80147060(u8 *a0); \
    extern s32 func_8016F0AC(); \
    extern s32 D_80126B58; \
    void func_80174714(void) { \
        if (func_800CF8CC() == 0) { \
            func_80147060((u8 *)&D_80126B58); \
            func_8016F0AC(); \
        } \
    }

#define DEFINE_func_801751D8() \
    extern s32 func_80161104(void); \
    extern s32 func_80175218(void *a0); \
    extern void func_80146CA0(void *a0); \
    void func_801751D8(void *a0) { \
        void *s = a0; \
        if (func_80161104()) { \
            func_80175218(s); \
            func_80146CA0(s); \
        } \
    }

#define DEFINE_func_8012A68C() \
    extern void func_8012A7D4(void *a0, void *a1); \
    extern s32 func_8012A6D0(void *a0, void *a1); \
    s16 func_8012A68C(void) { \
        s16 a[4]; \
        s16 b[4]; \
        func_8012A7D4(a, b); \
        return (s16)func_8012A6D0(a, b); \
    }

#define DEFINE_func_8012A758() \
    extern void func_8012A7D4(void *a0, void *a1); \
    extern s16 func_8012A79C(s16 *a0, s16 *a1); \
    s16 func_8012A758(void) { \
        s16 a[4]; \
        s16 b[4]; \
        func_8012A7D4(a, b); \
        return func_8012A79C(a, b); \
    }

#define DEFINE_func_80130898() \
    extern void func_80131CA8(int a0, int a1); \
    void func_80130898(u8 *a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x4000) { \
            *(s16 *)(a0 + 0xAA) = 0x100; \
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE; \
        } \
        func_80131CA8((int)a0, 0x28); \
    }

#define DEFINE_func_80131E38() \
    extern void func_80131CA8(int a0, int a1); \
    void func_80131E38(u8 *a0) { \
        *(s8 *)(a0 + 0xC1) = 0xF; \
        if (*(s32 *)(a0 + 0xB4) & 0x40000) { \
            *(s32 *)(a0 + 0x1C) = 6; \
            *(s16 *)(a0 + 0x5C) = 0; \
        } \
        func_80131CA8((int)a0, 0x39); \
    }

#define DEFINE_func_8012EF70() \
    extern void func_8012EFB8(s32 a0); \
    void func_8012EF70(s32 a0, s32 a1) { \
        s32 sp10; \
        register s32 v1 __asm__("$3"); \
        func_8012EFB8(a0); \
        { \
            register s32 *p __asm__("$3") = &sp10; \
            __asm__ __volatile__( \
                "mfc2 $12, $19\n" \
                "nop\n" \
                "sra $12, $12, 2\n" \
                "sw $12, 0(%0)\n" \
                : : "r"(p) : "memory", "$12"); \
        } \
        v1 = sp10; \
        *(s16 *)(a1 + 4) = v1; \
    }

#define DEFINE_func_80151980() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801519C8(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80151980(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801519C8(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80152094() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801520DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152094(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801520DC(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8015220C() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801536DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015220C(s32 a0) { \
        func_80149020((s32 *)a0); \
        if (!func_801536DC(a0)) { \
            *(s8 *)(a0 + 0xDE) = 1; \
            *(s8 *)(a0 + 0xDF) = 0; \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_801523AC() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801523F4(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_801523AC(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801523F4(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80152868() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801528B0(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152868(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801528B0(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80152A08() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801536DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152A08(s32 a0) { \
        func_80149020((s32 *)a0); \
        if (!func_801536DC(a0)) { \
            *(s8 *)(a0 + 0xDE) = 1; \
            *(s8 *)(a0 + 0xDF) = 0; \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_80152BA8() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_80152BF0(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152BA8(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_80152BF0(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80152D60() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_80152DA8(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152D60(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_80152DA8(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80152EFC() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801536DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152EFC(s32 a0) { \
        func_80149020((s32 *)a0); \
        if (!func_801536DC(a0)) { \
            *(s8 *)(a0 + 0xDE) = 1; \
            *(s8 *)(a0 + 0xDF) = 0; \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_8015309C() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801530E4(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015309C(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801530E4(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_801531BC() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801536DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_801531BC(s32 a0) { \
        func_80149020((s32 *)a0); \
        if (!func_801536DC(a0)) { \
            *(s8 *)(a0 + 0xDE) = 1; \
            *(s8 *)(a0 + 0xDF) = 0; \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_8015335C() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_801533A4(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015335C(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_801533A4(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80153490() \
    extern void func_80149020(s32 *a0); \
    extern s32 func_801536DC(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80153490(s32 a0) { \
        func_80149020((s32 *)a0); \
        if (!func_801536DC(a0)) { \
            *(s8 *)(a0 + 0xDE) = 1; \
            *(s8 *)(a0 + 0xDF) = 0; \
            func_80146CA0((void *)a0); \
        } \
    }

#define DEFINE_func_80153D34() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_80153D7C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80153D34(s32 a0) { \
        func_8014E934(a0); \
        func_8014CC28(a0); \
        func_8014F3E8(a0); \
        func_80153D7C(a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80154190() \
    extern void func_80154418(void *a0); \
    void func_80154190(u8 *a0, s32 a1) { \
        s32 v1 = *(s32 *)((a1 << 2) + *(s32 *)(a0 + 0xB0)); \
        *(s16 *)(a0 + 0xBA) = 1; \
        *(s16 *)(a0 + 0xB8) = 1; \
        *(s8 *)(a0 + 0xBC) = 0; \
        *(s8 *)(a0 + 0xBD) = 0; \
        *(s8 *)(a0 + 0xDC) = 0; \
        *(s32 *)(a0 + 0xB4) = v1; \
        func_80154418((void *)a0); \
    }

#define DEFINE_func_80165B6C() \
    extern s32 func_80161104(void); \
    extern void func_80165BB4(u8 *a0); \
    void func_80165B6C(u8 *a0) { \
        if (func_80161104()) { \
            func_80165BB4(a0); \
            *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1; \
        } \
    }

#define DEFINE_func_80165BB4() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_80165BB4(u8 *a0) { \
        func_80154150((s32)a0, 0x22); \
        func_80154A74((s32)a0, 0x1A); \
        *(u8 *)(a0 + 0x197) = *(u8 *)(a0 + 0x197) + 1; \
    }

#define DEFINE_func_8016DBD8() \
    extern void func_80149374(s32 a0, s32 a1); \
    extern void func_800D1FC8(s32 a0, s32 a1); \
    void func_8016DBD8(u8 *a0) { \
        *(s32 *)(a0 + 0x4) = 0; \
        *(s32 *)(a0 + 0x8) = 0; \
        *(s32 *)(a0 + 0xC) = 0; \
        func_80149374(*(s32 *)(a0 + 0x34), (s32)(a0 + 0x4)); \
        func_800D1FC8((s32)a0, 5); \
    }

#define DEFINE_func_801700B8() \
    extern void *D_8011F738; \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_80171928(void *a0); \
    void func_801700B8(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_8011F738); \
        func_80171928((void *)a0); \
    }

#define DEFINE_func_80170B90() \
    extern void func_80147060(u8 *a0); \
    extern void func_80171928(void *a0); \
    void func_80170B90(u8 *a0) { \
        if (*(u16 *)(a0 + 0xB8) & 0x8000) { \
            func_80147060(a0); \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_80172310() \
    extern s32 D_80126B58; \
    extern s32 *D_80126B78; \
    extern void func_80172358(u8 *a0, u8 *a1); \
    void func_80172310(u8 *a0) { \
        func_80172358((u8 *)&D_80126B58, a0); \
        *(u16 *)((u8 *)D_80126B78 + 0x12) = *(u16 *)(a0 + 6); \
    }

#define DEFINE_func_80172844() \
    extern s16 D_80126B30; \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_80172844(u8 *a0) { \
        if (func_80171CC4(a0, &D_80126B30)) { \
            func_80171A1C(a0); \
            func_80174650((s32)a0); \
        } \
    }

#define DEFINE_func_80172B80() \
    extern s32 D_801150F8; \
    extern void func_80147060(u8 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172BC8(void *a0); \
    void func_80172B80(u8 *a0) { \
        if (D_801150F8 == 0) { \
            func_80147060(a0); \
        } \
        func_80171A1C(a0); \
        func_80172BC8(a0); \
    }

#define DEFINE_func_801731D8() \
    extern u8 D_800D5AA0[]; \
    extern void func_8014706C(void *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80173220(void *a0); \
    void func_801731D8(s32 *a0) { \
        func_8014706C(a0); \
        func_80154274(a0, (s32)D_800D5AA0); \
        func_80171A1C((u8 *)a0); \
        func_80173220(a0); \
    }

#define DEFINE_func_801739D8() \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_801739D8(u8 *a0) { \
        if ((*(s32 *)(a0 + 0x44) & 2) == 0) { \
            func_80171A1C(a0); \
            func_80174650((s32)a0); \
        } \
    }

#define DEFINE_func_80179D30() \
    extern void func_80179B74(s16 *a0); \
    void func_80179D30(u16 *a0) { \
        s16 buf[4]; \
        buf[0] = 1; \
        buf[1] = a0[0]; \
        buf[2] = a0[1]; \
        buf[3] = a0[2]; \
        func_80179B74(buf); \
    }

#define DEFINE_func_80179EA0() \
    extern void func_80179B74(s16 *a0); \
    void func_80179EA0(u16 *a0) { \
        s16 buf[4]; \
        buf[0] = 5; \
        buf[1] = a0[0]; \
        buf[2] = a0[1]; \
        buf[3] = a0[2]; \
        func_80179B74(buf); \
    }

#define DEFINE_func_8012927C() \
    extern void func_801292C8(u8 *a0); \
    extern s16 D_8011DB30; \
    void func_8012927C(void) { \
        s32 i; \
        u8 *p = (u8 *)&D_8011DB30; \
        for (i = 0; i < 0x80; i++) { \
            func_801292C8(p); \
            p += 0x38; \
        } \
    }

#define DEFINE_func_80150820() \
    extern void func_8014BD24(s32 a0, s32 a1); \
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
    void func_80150820(s32 a0, s32 a1) { \
        if (a1 != 0) { \
            func_8014BD24(a0, a1); \
            func_8014ACE8((void *)a0, 4, a1); \
        } \
    }

#define DEFINE_func_80155FF8() \
    extern int func_80156044(int arg, int a1); \
    int func_80155FF8(int arg, int a1) { \
        __asm__ __volatile__( \
            ".set noreorder\n" \
            "addiu $sp, $sp, -24\n" \
            "sw    $ra, 16($sp)\n" \
            "lui   $v0, 0x1f80\n" \
            "ori   $v0, $v0, 0x03fc\n" \
            "addu  $t0, $v0, $zero\n" \
            "lw    $t1, 0($t0)\n" \
            "nop\n" \
            "sw    $sp, 0($t1)\n" \
            "addiu $t1, $t1, -4\n" \
            "addu  $sp, $t1, $zero\n" \
            "jal   func_80156044\n" \
            "addiu $sp, $sp, 4\n" \
            "lw    $sp, 0($sp)\n" \
            "nop\n" \
            "lw    $ra, 16($sp)\n" \
            "addiu $sp, $sp, 24\n" \
            : : : "memory"); \
    }

#define DEFINE_func_801585EC() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801553A8(s32 *a0); \
    void func_801585EC(u8 *a0) { \
        *(s32 *)(a0 + 0x44) &= ~2; \
        func_80154A74((s32)a0, 0x11); \
        func_801553C0((s32)a0); \
        func_801553A8((s32 *)a0); \
    }

#define DEFINE_func_80160A28() \
    extern void func_801553C0(s32 a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_80160A28(s32 a0) { \
        s32 v0; \
        func_801553C0(a0); \
        v0 = *(s32 *)(a0 + 0x44); \
        v0 &= ~0x40; \
        v0 &= ~1; \
        *(s32 *)(a0 + 0x44) = v0; \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_8016236C() \
    extern void func_8014706C(void *a0); \
    extern s32 D_80126B58; \
    s32 func_8016236C(u8 *a0) { \
        func_8014706C(&D_80126B58); \
        *(s32 *)(a0 + 0x28) = 0xA; \
        *(u8 *)(a0 + 0x15) += 1; \
        return 0; \
    }

#define DEFINE_func_80162714() \
    extern s32 func_800291DC(s32); \
    extern s32 func_800D0D7C(s32, s32); \
    extern void func_800291C8(s32, s32); \
    void func_80162714(void) { \
        s32 v0; \
        if ((s16)func_800291DC(0x12) == 0) { \
            v0 = func_800D0D7C(0xC, 0); \
            func_800291C8(0x12, (s16)(v0 | 0x8000)); \
        } \
    }

#define DEFINE_func_80168780() \
    extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_801687CC(s32 a0); \
    void func_80168780(s32 a0) { \
        func_80168BDC(a0, 8, 0, 2); \
        func_801687CC(a0); \
        *(u16 *)(a0 + 2) += 1; \
    }

#define DEFINE_func_801752BC() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_801752BC(s32 *a0) { \
        *(s16 *)((u8 *)a0 + 0xF6) = 0x1000; \
        func_801553A8(a0); \
        func_80154A74((s32)a0, 0x11); \
        *(s32 *)((u8 *)a0 + 0x44) &= ~2; \
    }

#define DEFINE_func_80179B28() \
    extern void func_80139914(s32 a0); \
    void func_80179B28(s32 a0) { \
        s32 v1; \
        if (a0 == 0) return; \
        if (*(s32 *)a0 == 0) return; \
        v1 = *(s16 *)(a0 + 4); \
        if (v1 == 0) return; \
        if (v1 == 0xE) return; \
        func_80139914(a0); \
    }

#define DEFINE_func_8013A860() \
    extern void func_80016714(void *a0, s32 a1); \
    extern u8 D_8011DA80[]; \
    void func_8013A860(void) { \
        s32 i; \
        u8 *p; \
        i = 0; \
        p = D_8011DA80; \
        do { \
            func_80016714(p, 0x10); \
            i++; \
            p += 0x10; \
        } while (i < 2); \
    }

#define DEFINE_func_80148AAC() \
    extern int func_80148AFC(void *a0); \
    void func_80148AAC(u8 *a0) { \
        u8 *v1; \
        if ((func_80148AFC(a0) & 0xff) != 0) { \
            v1 = *(u8 **)(a0 + 0x20); \
            *(u16 *)(v1 + 0x12) = (*(u16 *)(v1 + 0x12) + 0xFA) & 0xFF8; \
        } \
    }

#define DEFINE_func_80151D60() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_80151DB0(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80151D60(void *a0) { \
        func_8014E934((s32)a0); \
        func_8014CC28((s32)a0); \
        func_8014F3E8((s32)a0); \
        func_80151DB0((s32)a0); \
        *(s8 *)((u8 *)a0 + 0xDE) = 0x20; \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80157D74() \
    extern void func_80157DC4(void *a0); \
    extern void func_80157FC4(void *a0); \
    void func_80157D74(u16 *a0) { \
        switch (a0[0]) { \
        case 0x24: \
            func_80157DC4(a0); \
            break; \
        case 0x25: \
            func_80157FC4(a0); \
            break; \
        } \
    }

#define DEFINE_func_8016E728() \
    extern void func_80146C3C(void); \
    extern void func_8016E778(); \
    void func_8016E728(u8 *a0) { \
        s32 v0; \
        s32 v1; \
        v0 = (u16)*(u16 *)(a0 + 0x12) + 0x400; \
        v1 = (u16)*(u16 *)(a0 + 0x16) - 8; \
        *(u16 *)(a0 + 0x12) = v0; \
        *(u16 *)(a0 + 0x16) = v1; \
        if ((s16)v1 <= 0) { \
            func_80146C3C(); \
        } else { \
            func_8016E778(); \
        } \
    }

#define DEFINE_func_80170018() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_8013767C(s32 a0); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170068(u8 *a0); \
    extern void *D_8011F738; \
    void func_80170018(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_8011F738); \
        func_80171990(a0); \
        func_80170068(a0); \
    }

#define DEFINE_func_80170068() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern void func_80171928(void *a0); \
    void func_80170068(u8 *a0) { \
        if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) { \
            func_80139914(*(s32 *)(a0 + 0x198)); \
            *(s32 *)(a0 + 0x198) = 0; \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_80170100() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern void func_80171928(void *a0); \
    void func_80170100(u8 *a0) { \
        if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) { \
            func_80139914(*(s32 *)(a0 + 0x198)); \
            *(s32 *)(a0 + 0x198) = 0; \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_80173C64() \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s16 D_80126B36; \
    void func_80173C64(u8 *a0) { \
        s16 *p = &D_80126B36; \
        if (*p != 0) { \
            if (func_80171CC4(a0, p - 3) == 0) { \
                return; \
            } \
        } \
        func_80171A1C(a0); \
    }

#define DEFINE_func_8012C044() \
    extern s32 D_801274D4; \
    extern s16 D_80126CAC; \
    extern s32 D_801274E0; \
    extern s32 func_80013478(s32 a0, s32 a1); \
    s32 func_8012C044(s32 a0) { \
        s32 (*fp)(void) = (s32 (*)(void))D_801274D4; \
        if (fp != 0) { \
            return fp(); \
        } \
        return func_80013478(a0 + 4, (s32)&D_80126CAC) >= D_801274E0; \
    }

#define DEFINE_func_80144A98() \
    extern void func_8012C1B8(void); \
    extern void func_8012CAE4(void *a0); \
    extern void func_8001C214(s32 a0, s32 a1); \
    void func_80144A98(u8 *a0) { \
        s32 v0; \
        v0 = ((s32 (*)(void))func_8012C1B8)(); \
        *(s32 *)(a0 + 0x20) = v0; \
        if (v0 == 0) { \
            func_8012CAE4(a0); \
        } else { \
            func_8001C214(v0, 0); \
            *(s16 *)(a0 + 0x2) = 1; \
        } \
    }

#define DEFINE_func_8015F848() \
    extern s32 D_8011F730; \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_8015F848(s32 *a0) { \
        func_801553A8(a0); \
        func_80154150((s32)a0, 0x1F); \
        D_8011F730 |= 0x5; \
        func_80146CA0(a0); \
    }

#define DEFINE_func_801685EC() \
    extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80166690(); \
    extern void func_80146C3C(void); \
    void func_801685EC(s32 a0) { \
        func_80166994(a0, 2, 2, 0); \
        if ((short)func_80166690(2, 1) == 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_801717A0() \
    extern void func_801719A4(int a0, int a1); \
    extern int func_800D0F8C(int a0); \
    extern int func_800D0FE0(int a0); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_801717A0(void *a0) { \
        int v0; \
        func_801719A4((int)a0, 1); \
        v0 = func_800D0F8C(*(u8 *)&D_8011F738); \
        if (v0 != 0) { \
            func_800D0FE0(v0); \
        } \
        func_80171928(a0); \
    }

#define DEFINE_func_80179F98() \
    extern void func_80179B74(s16 *a0); \
    void func_80179F98(u16 *a0) { \
        s16 sp[5]; \
        sp[0] = 0x17; \
        sp[1] = a0[0]; \
        sp[2] = a0[1]; \
        sp[3] = a0[2]; \
        sp[4] = a0[3]; \
        func_80179B74(sp); \
    }

#define DEFINE_func_80179FEC() \
    extern void func_80179B74(s16 *a0); \
    void func_80179FEC(u16 *a0) { \
        s16 sp[5]; \
        sp[0] = 0x20; \
        sp[1] = a0[0]; \
        sp[2] = a0[1]; \
        sp[3] = a0[2]; \
        sp[4] = a0[3]; \
        func_80179B74(sp); \
    }

#define DEFINE_func_8017A040() \
    extern void func_80179B74(s16 *a0); \
    void func_8017A040(u16 *a0) { \
        s16 sp[5]; \
        sp[0] = 0x1D; \
        sp[1] = a0[0]; \
        sp[2] = a0[1]; \
        sp[3] = a0[2]; \
        sp[4] = a0[3]; \
        func_80179B74(sp); \
    }

#define DEFINE_func_80155C0C() \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_800D4DD4[]; \
    void func_80155C0C(s32 *a0) { \
        u8 sp10[0x40]; \
        (void)sp10; \
        a0[0x44 / 4] |= 2; \
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
            func_80154274(a0, (s32)D_800D4DD4); \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_80160A74() \
    extern void func_80160B00(); \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80159B70(void *a0); \
    extern u8 D_80078EBF; \
    void func_80160A74(s32 *a0) { \
        if (D_80078EBF == 0x80) { \
            func_80160B00(); \
        } else { \
            func_80147078(a0, 0); \
            func_80159B70(a0); \
        } \
    }

#define DEFINE_func_80162F08() \
    extern void func_80162F60(s32 arg0, s32 arg1); \
    extern void func_80162F80(s32 arg0, s32 arg1); \
    extern void func_80162FA0(s32 arg0, s32 arg1); \
    void func_80162F08(s32 a0, s32 a1, s32 a2, s32 a3) { \
        func_80162F60(a0, a1); \
        func_80162F80(a0, a2); \
        func_80162FA0(a0, a3); \
    }

#define DEFINE_func_80164A74() \
    extern void func_80148534(s32 a0, s32 a1); \
    extern void func_80015954(s32 a0, s32 a1); \
    extern void func_80149374(s32 a0, s32 a1); \
    void func_80164A74(s32 *a0) { \
        s32 sp10[2]; \
        s32 sp18[2]; \
        s32 s1 = a0[0x4C / 4]; \
        func_80148534((s32)sp10, (s32)sp18); \
        func_80015954((s32)sp10, (s32)a0 + 4); \
        func_80149374(s1, (s32)a0 + 4); \
    }

#define DEFINE_func_80165718() \
    extern s32 func_80165A20(s32 a0); \
    extern u8 D_80078EC1; \
    void func_80165718(s32 a0) { \
        switch (D_80078EC1) { \
        case 3: \
        case 0xC: \
        case 0x18: \
            func_80165A20(a0); \
            break; \
        } \
    }

#define DEFINE_func_8016629C() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_8016629C(void *a0) { \
        func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6), \
                      (s16)(*(u16 *)((s32)a0 + 0xA) - 0x10), \
                      *(s16 *)((s32)a0 + 0xE), 0xF88FFF2, 0xE000C000); \
    }

#define DEFINE_func_801662F4() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_801662F4(void *a0) { \
        func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6), \
                      (s16)(*(u16 *)((s32)a0 + 0xA) - 0x10), \
                      *(s16 *)((s32)a0 + 0xE), 0x8FEFFF4, 0xE000C000); \
    }

#define DEFINE_func_8016634C() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_8016634C(void *a0) { \
        func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6), \
                      (s16)(*(u16 *)((s32)a0 + 0xA) - 0x10), \
                      *(s16 *)((s32)a0 + 0xE), 0xEEEFFF8, 0x6800B000); \
    }

#define DEFINE_func_801663A4() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_801663A4(void *a0) { \
        func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6), \
                      (s16)(*(u16 *)((s32)a0 + 0xA) - 0x10), \
                      *(s16 *)((s32)a0 + 0xE), 0xCCCFFF8, 0xE000C000); \
    }

#define DEFINE_func_8016FE78() \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern s32 func_80171990(u8 *a0); \
    extern u16 D_8011F73E; \
    s32 func_8016FE78(s32 *a0) { \
        *(u16 *)((s32)a0 + 0xAA) |= 0x40; \
        if (D_8011F73E != 0) { \
            func_801477E8(a0, D_8011F73E << 16); \
        } \
        return func_80171990((u8 *)a0); \
    }

#define DEFINE_func_80145BF8() \
    extern s32 func_80028FBC(void); \
    extern s32 func_80029000(void); \
    extern s32 func_80028D9C(void); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_80145BF8(void) { \
        func_8002D4C8(0x21, func_80028FBC() & 0xFFFF); \
        func_8002D4C8(0x22, func_80029000() & 0xFFFF); \
        func_8002D4C8(func_80028D9C() == 0 ? 0xC : 0xB, 0); \
    }

#define DEFINE_func_8014CA14() \
    extern u16 func_8014CA70(s32 a0, s32 a1); \
    extern void func_80147364(u16, s32); \
    extern void *D_8012707C; \
    s32 func_8014CA14(s32 a0, s32 a1) { \
        u16 x = func_8014CA70(a0, a1); \
        if (x == 0) { \
            return 1; \
        } \
        if (x != (s32)D_8012707C) { \
            func_80147364(x, 0); \
            return 0; \
        } \
        D_8012707C = 0; \
        return 0; \
    }

#define DEFINE_func_8014CA88() \
    extern u16 func_8014CAE4(s32 *a0, s32 a1); \
    extern void func_80147364(u16, s32); \
    extern void *D_8012707C; \
    s32 func_8014CA88(s32 *a0, s32 a1) { \
        u16 x = func_8014CAE4(a0, a1); \
        if (x == 0) { \
            return 1; \
        } \
        if (x != (s32)D_8012707C) { \
            func_80147364(x, 0); \
            return 0; \
        } \
        D_8012707C = 0; \
        return 0; \
    }

#define DEFINE_func_8015C788() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553A8(s32 *a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_8015C788(s32 a0) { \
        func_80154150(a0, 0x12); \
        func_80154A74(a0, 0x17); \
        func_801553A8((s32 *)a0); \
        func_80155440((s32 *)a0); \
        func_80146E90((s32 *)a0, 0xA); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8015E22C() \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_800D4FF4[]; \
    void func_8015E22C(s32 a0) { \
        func_80154274((s32 *)a0, (s32)D_800D4FF4); \
        *(s32 *)(a0 + 0x234) = 0; \
        func_80146994(5, a0, 0xA, 0); \
        *(s32 *)(a0 + 0x44) |= 2; \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8015F260() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80149048(s32 *a0); \
    void func_8015F260(s32 *a0) { \
        s32 v; \
        func_801553A8(a0); \
        func_80154A74((s32)a0, 0x11); \
        v = a0[0x11]; \
        v &= -0x3; \
        v &= -0x2; \
        a0[0x11] = v; \
        func_80149048(a0); \
        *(s16 *)((u8 *)a0 + 0xF6) = 0x1000; \
    }

#define DEFINE_func_80160CB4() \
    extern s32 func_80161208(); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_80160CB4(s32 *a0) { \
        if (func_80161208() == 0) { \
            if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
                func_80154150((s32)a0, 0x27); \
                func_80154A74((s32)a0, 0x1F); \
                func_80146CA0(a0); \
            } \
        } \
    }

#define DEFINE_func_80161488() \
    extern s32 func_801615C4(void *a0, s32 a1); \
    extern void func_80161774(void *a0, s32 a1); \
    extern s32 func_8016197C(s32 a0, s32 a1); \
    s32 func_80161488(void *a0) { \
        s32 v0 = func_801615C4(a0, 0); \
        if (*(u8 *)((u8 *)a0 + 0x1C6) == 0) { \
            func_80161774(a0, v0); \
        } else { \
            return func_8016197C((s32)a0, v0) & -0x8; \
        } \
        /* fall off end: returns clobbered v0 (matches original) */ \
    }

#define DEFINE_func_801623B8() \
    extern void func_800D0C48(s32 a0); \
    extern void func_800167B8(s32 a0); \
    s32 func_801623B8(s32 *a0) { \
        if (--a0[0xA] == -1) { \
            func_800D0C48(1); \
            func_800167B8(4); \
            *((u8 *)a0 + 0x15) += 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80157F64() \
    extern s32 func_80029178(s32 a0); \
    extern u16 func_80148800(s32 *a0); \
    extern void func_80149CB4(void); \
    s32 func_80157F64(s32 *a0) { \
        if ((func_80029178(0x87) & 0xFF) != 0) { \
            if ((func_80148800(a0) & 0x80) != 0) { \
                ((void (*)(s32 *, s32))func_80149CB4)(a0, 5); \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_801601E4() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_80161208(); \
    void func_801601E4(s32 *a0) { \
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
            func_80154150((s32)a0, 0x22); \
            func_80154A74((s32)a0, 0x1A); \
            func_80146CA0(a0); \
        } else { \
            ((s32 (*)(s32 *))func_80161208)(a0); \
        } \
    }

#define DEFINE_func_80160244() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_80161208(); \
    void func_80160244(s32 *a0) { \
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
            func_80154150((s32)a0, 0x23); \
            func_80154A74((s32)a0, 0x1B); \
            func_80146CA0(a0); \
        } else { \
            ((s32 (*)(s32 *))func_80161208)(a0); \
        } \
    }

#define DEFINE_func_8016D5EC() \
    extern short func_8016CF04(); \
    extern void func_80146C3C(void); \
    void func_8016D5EC(s32 *a0) { \
        u16 *rec = (u16 *)a0[8];   /* lw 0x20(s0) */ \
        rec[0xC] -= 0x60;          /* 0x18 */ \
        rec[0xD] -= 0x60;          /* 0x1A */ \
        if ((s16)((s32 (*)(s32, s32))func_8016CF04)((s32)a0, 2) != 0) { \
            ((void (*)(s32 *))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_8016F14C() \
    extern void func_80148634(void *a0); \
    void func_8016F14C(void *a0) { \
        s32 v1 = *(s32 *)((u8 *)a0 + 0x1F8); \
        s32 fp = v1 & 0x80FFFFFF; \
        if (v1 != 0) { \
            if (v1 & 0x1000000) { \
                func_80148634(a0); \
            } \
            ((void (*)(void *))fp)(a0); \
        } \
    }

#define DEFINE_func_8016FED0() \
    extern s32 func_80172664(s32 *a0); \
    extern s32 func_80171CC4(void *a0, void *a1); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_8016FED0(s32 *a0) { \
        if (func_80172664(a0) != 0) { \
            *(u16 *)((u8 *)a0 + 0xAA) |= 0x40; \
        } \
        if (func_80171CC4(a0, &D_8011F738) != 0) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_8015C0C4() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_801553A8(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    extern s16 D_801152B0; \
    extern s16 D_801152B4; \
    void func_8015C0C4(s32 a0) { \
        s32 t = D_801152B0 << 6; \
        *(s32 *)(a0 + 0x238) = 0x80000; \
        *(s32 *)(a0 + 0x234) = t; \
        *(s32 *)(a0 + 0x23C) = D_801152B4 << 6; \
        func_80154150(a0, 0x11); \
        func_801553A8((s32 *)a0); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8012EECC() \
    extern s32 func_8002A4FC(s32 a0); \
    s32 func_8012EECC(s32 a0) { \
        s32 n = a0 * func_8002A4FC(a0); \
        return a0 - (n * 100) / 7680; \
    }

#define DEFINE_func_8013A1E8() \
    extern s32 D_80127524; \
    extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2); \
    extern void func_80138B88(s32 a0); \
    void func_8013A1E8(s32 a0) { \
        s32 v = D_80127524; \
        if (v == a0) { \
            if (func_80138DB8(v, 0, 0x70) != 0 || (*(s32 *)(v + 8) & 0x800)) { \
                func_80138B88(v); \
            } \
        } \
    }

#define DEFINE_func_80149078() \
    extern void func_801490E0(s32 *a0, s16 a1); \
    extern void func_801490E8(s32 *a0, s16 a1); \
    extern void func_801490F0(s32 *a0, s16 a1); \
    void func_80149078(s32 *a0, s32 a1, s32 a2, s32 a3) { \
        func_801490E0(a0, (s16)a1); \
        func_801490E8(a0, (s16)a2); \
        func_801490F0(a0, (s16)a3); \
    }

#define DEFINE_func_8015DB6C() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_8015DCB8(s32 a0); \
    extern void func_80147300(u16 arg0); \
    extern void func_801553A8(s32 *a0); \
    extern void func_8014BD60(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_8015DB6C(s32 a0) { \
        func_80154150(a0, 0x1C); \
        func_80154A74(a0, 0x19); \
        *(s32 *)(a0 + 0x234) = 0; \
        func_8015DCB8(a0); \
        func_80147300(0x5F5); \
        func_801553A8((s32 *)a0); \
        func_8014BD60(a0, 4); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8015DECC() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_8015E018(s32 a0); \
    extern void func_80147300(u16 arg0); \
    extern void func_801553A8(s32 *a0); \
    extern void func_8014BD60(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_8015DECC(s32 a0) { \
        func_80154150(a0, 0x1C); \
        func_80154A74(a0, 0x19); \
        *(s32 *)(a0 + 0x234) = 0; \
        func_8015E018(a0); \
        func_80147300(0x5F5); \
        func_801553A8((s32 *)a0); \
        func_8014BD60(a0, 4); \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80161094() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern void func_80129248(s16 a0); \
    extern u16 D_801270C0; \
    extern u8 D_800B9A17; \
    void func_80161094(s32 a0) { \
        if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) { \
            func_80139914(*(s32 *)(a0 + 0x198)); \
            *(s32 *)(a0 + 0x198) = 0; \
        } \
        D_801270C0 = 1; \
        func_80129248(1); \
        D_800B9A17 = 1; \
    }

#define DEFINE_func_8012C218() \
    extern void func_80016714(void *a0, s32 a1); \
    void func_8012C218(void *a0) { \
        u16 *p = ((u16 **)a0)[8];   /* 0x20/4 */ \
        if (p) { \
            s32 a1; \
            switch (*p) { \
            case 2:  a1 = 0x38; break; \
            case 1:  a1 = 0x84; break; \
            default: goto skip; \
            } \
            func_80016714(p, a1); \
        } \
    skip: \
        func_80016714(a0, 0x10C); \
    }

#define DEFINE_func_80161B18() \
    extern s32 D_800AE6B0; \
    extern void func_801599A4(void *a0); \
    extern void func_8015FA78(s32 *a0); \
    s32 func_80161B18(void *a0) { \
        if ((D_800AE6B0 & 0x80FFFFFF) != 0) return 0; \
        if (*(s32 *)((u8 *)a0 + 0x44) & 0x10) { \
            func_801599A4(a0); \
            func_8015FA78((s32 *)a0); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80163664() \
    extern void func_80157158(); \
    void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12) { \
        func_80157158(a0, a1 & 0xFFFF, a2 & 0xFFFF, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); \
    }

#define DEFINE_func_8016FBB8() \
    extern void func_801719A4(int a0, int a1); \
    extern void func_80171B44(s32 *a0); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FC24(); \
    void func_8016FBB8(s32 a0) { \
        u8 *p; \
        *(s16 *)(a0 + 0x136) = 2; \
        p = *(u8 **)(a0 + 0x20); \
        *(s16 *)(a0 + 0x132) = *(u16 *)(p + 0x12); \
        p = *(u8 **)(a0 + 0x20); \
        *(s16 *)(p + 0x12) = (*(u16 *)(p + 0x12) + 0x800) & 0xFFF; \
        func_801719A4(a0, 1); \
        func_80171B44((s32 *)a0); \
        func_80171990((u8 *)a0); \
        func_8016FC24(a0); \
    }

#define DEFINE_func_801787D4() \
    extern u8 D_801202A0[]; \
    extern void func_80178840(); \
    void func_801787D4(void) { \
        u8 *p = D_801202A0; \
        s32 i; \
        for (i = 0; i < 0x60; i++) { \
            if (*(u16 *)(p + 0) != 0 && p[0xC0] != 0) { \
                func_80178840(p); \
            } \
            p += 0x10C; \
        } \
    }

#define DEFINE_func_8012C820() \
    extern u8 D_80120194[]; \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    s32 func_8012C820(u8 *a0) { \
        u8 *base = D_80120194; \
        u8 *p = base + 0x6480; \
        if (p != base) { \
            do { \
                if (*(u16 *)p == 0) goto found; \
                p -= 0x10C; \
            } while (p != base); \
        } \
        p = 0; \
    found: \
        if (p != 0) { \
            *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000; \
            func_8012C890((s32)a0, (s32)p, 0); \
        } else { \
            return 0; \
        } \
    }

#define DEFINE_func_80146924() \
    extern s32 D_8011D030; \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    s32 func_80146924(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5) { \
        s32 count = 0; \
        u8 *v1 = (u8 *)&D_8011D030; \
        u8 *end = v1 + 0xA50; \
        while (v1 < end) { \
            if (*(u16 *)v1 == (a0 & 0xFFFF)) count++; \
            v1 += 0x58; \
        } \
        if ((u32)count < (u32)arg5) { \
            return func_80146994(a0 & 0xFFFF, a1, a2, a3); \
        } \
        return 0; \
    }

#define DEFINE_func_801498E0() \
    extern s32 func_80149AA8(s32 *a0); \
    extern s32 func_80149B54(s32 *a0); \
    extern void func_80146750(void *a0); \
    s32 func_801498E0(s32 *a0) { \
        s16 st[4]; \
        s32 stw[3]; \
        if (func_80149AA8(a0) != 0 || func_80149B54(a0) != 0) { \
            st[0] = 8; \
            stw[0] = (s32)a0; \
            st[1] = 0; \
            st[2] = -0x1E; \
            st[3] = 0; \
            stw[1] = 0; \
            stw[2] = 0; \
            func_80146750(st); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8014CD0C() \
    extern void func_8014CF04(s32 a0, void *a1, void *a2); \
    extern int func_8014CD80(s32 a0, u16 *a1, u16 *a2); \
    void func_8014CD0C(u8 *a0) { \
        u16 sp10[3]; \
        u16 sp18[3]; \
        u16 b; \
        u16 c; \
        u16 d; \
        b = *(u16 *)(a0 + 0x6); \
        sp18[0] = b; \
        sp10[0] = b; \
        c = *(u16 *)(a0 + 0xA); \
        sp10[1] = c - 3; \
        d = *(u16 *)(a0 + 0xE); \
        sp18[1] = c + 5; \
        sp18[2] = d; \
        sp10[2] = d; \
        if (*(s32 *)(a0 + 0x174) == 0) { \
            func_8014CF04((s32)a0, sp10, sp18); \
        } else { \
            func_8014CD80((s32)a0, sp10, sp18); \
        } \
    }

#define DEFINE_func_8015ABD4() \
    extern s32 func_8016F1AC(void); \
    extern s32 func_80029178(s32 a0); \
    extern s32 D_8011F9C4; \
    s32 func_8015ABD4(s32 a0, s32 a1, s32 a2) { \
        if (func_8016F1AC() != 0) { \
            return 0; \
        } \
        if (a2 < a1) { \
            if (D_8011F9C4 == 0) { \
                return 0; \
            } \
            if ((func_80029178(0x21) & 0xFF) != 0) { \
                return 0; \
            } \
        } \
        return 1; \
    }

#define DEFINE_func_8016FD08() \
    extern s32 func_80172658(s32 *a0); \
    extern void func_80146D90(s32 a0); \
    extern s32 func_80171990(u8 *a0); \
    extern void *D_8011F738; \
    void func_8016FD08(u8 *s0) { \
        s32 *p; \
        if (func_80172658((s32 *)s0)) { \
            func_80146D90((s32)s0); \
            *(u16 *)(s0 + 0xAC) = *(u16 *)(s0 + 0xAC) | 0x40; \
            *(u16 *)(s0 + 0xAA) = *(u16 *)(s0 + 0xAA) | 0x40; \
            p = (s32 *)&D_8011F738; \
            if ((*p = *p - 1) == 0) { \
                func_80171990(s0); \
            } \
        } \
    }

#define DEFINE_func_8017385C() \
    extern s16 D_80126B30; \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_8017385C(u8 *a0) { \
        switch (D_80126B30) { \
        case 0: \
        default: \
            *(u16 *)(a0 + 0xAC) |= 0x80; \
            *(u16 *)(a0 + 0xAA) |= 0x80; \
            break; \
        case 1: \
            *(u16 *)(a0 + 0xAC) |= 0x10; \
            *(u16 *)(a0 + 0xAA) |= 0x10; \
            break; \
        } \
        func_80171A1C(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_8012DEB8() \
    extern void func_8012F214(s32 a0, s32 a1, s32 a2); \
    extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2); \
    extern s16 D_80126B9A; \
    s32 func_8012DEB8(s32 a0, s32 a1, s32 a2) { \
        s32 sp10[2]; \
        s32 sp18[2]; \
        func_8012F214(a0, a1, (s32)sp10); \
        func_8012F214(a0, a2, (s32)sp18); \
        if (func_8012DF34(a0, (s32)sp10, (s32)sp18) != 0) { \
            D_80126B9A = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8013A448() \
    extern void func_8013A530(); \
    void func_8013A448(void *a0) { \
        s16 *a1 = *(s16 **)((char *)a0 + 0x4); \
        if (*(u16 *)((char *)a0 + 0x2) == 0) { \
            *(s16 *)((char *)a1 + 0x2A) = 0x400; \
            *(s16 *)((char *)a1 + 0x28) = 0x400; \
            *(s16 *)((char *)a0 + 0x2) = *(u16 *)((char *)a0 + 0x2) + 1; \
        } else { \
            *(s16 *)((char *)a1 + 0x28) = *(u16 *)((char *)a1 + 0x28) + 0x200; \
            *(s16 *)((char *)a1 + 0x2A) = *(u16 *)((char *)a1 + 0x2A) + 0x200; \
            if (*(s16 *)((char *)a1 + 0x28) == 0x1000) { \
                *(s16 *)((char *)a0 + 0x0) = 2; \
                *(s16 *)((char *)a0 + 0x2) = 0; \
            } \
        } \
        func_8013A530(); \
    }

#define DEFINE_func_801417F8() \
    extern void func_800D2624(void); \
    extern u8 D_800B9A15; \
    extern u8 D_800B9A16; \
    extern short D_800B9A02; \
    extern u16 D_80115114; \
    extern u16 D_80115112; \
    void func_801417F8(void) { \
        if (D_800B9A15 == 0 || D_800B9A16 != 0) { \
            if (D_80115114 == (u16)(D_800B9A02 ^ 1)) { \
                func_800D2624(); \
            } else { \
                D_80115112 += 1; \
            } \
        } \
    }

#define DEFINE_func_80151F38() \
    extern void func_80149020(s32 *a0); \
    extern void func_80151FB4(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    extern s32 func_80172630(u8 *a0); \
    void func_80151F38(s32 *a0) { \
        func_80149020(a0); \
        *(s16 *)((char *)a0 + 0x64) = *(u16 *)((char *)a0 + 0x64) - (*(u8 *)((char *)a0 + 0xDE) << 6); \
        *(u8 *)((char *)a0 + 0xDE) = *(u8 *)((char *)a0 + 0xDE) + 8; \
        if (*(s16 *)((char *)a0 + 0x64) < 0x1000) { \
            func_80151FB4((s32)a0); \
            func_80159B3C(a0); \
            func_80165718((s32)a0); \
        } else { \
            func_80172630((u8 *)a0); \
        } \
    }

#define DEFINE_func_80152714() \
    extern void func_80019064(void *a0); \
    extern int func_80151204(int arg, int a1); \
    extern void func_80152790(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    extern u8 D_80062BF4[]; \
    extern u8 D_80078EC1; \
    void func_80152714(s32 a0) { \
        s32 sp[8]; \
        func_80019064((void *)D_80062BF4); \
        func_80151204(a0, *(s16 *)(a0 + 0xF2)); \
        if (D_80078EC1 != 2) { \
            *(s32 *)(a0 + 0x1AC) = 0x3C0000; \
            *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) | 0x100; \
        } \
        func_80152790(a0); \
        func_80159B3C((void *)a0); \
        func_80165718(a0); \
        (void)sp; \
    }

#define DEFINE_func_80155B20() \
    extern int func_80161208(); \
    extern void func_80146D80(s32 *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_800D4DA8[]; \
    void func_80155B20(s32 *a0) { \
        a0[0x44 / 4] |= 2; \
        if (func_80161208() == 0) { \
            if (*(u16 *)((char *)a0 + 0xB8) == 0x8000) { \
                func_80146D80(a0); \
                func_801477E8(a0, 0xFFF00000); \
                func_80154274(a0, (s32)D_800D4DA8); \
                func_80146CA0(a0); \
            } \
        } \
    }

#define DEFINE_func_8016345C() \
    extern u16 func_80156370(u16 a0); \
    extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5); \
    void func_8016345C(s32 a0, u16 a1, s32 a2, u16 a3, s32 a4) { \
        s32 r; \
        r = func_80156370(a1); \
        func_80163534(a0, a1, (u16)r, a2, a3, a4); \
    }

#define DEFINE_func_8016E26C() \
    extern void func_8016E3CC(s32 a0); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_8016E26C(s32 *a0) { \
        func_8016E3CC((s32)a0); \
        if (--a0[0x1C / 4] != 0) { \
            func_80146A6C(0x48, a0, 0, 0, 0, 0x8000, 0); \
        } else { \
            a0[0x1C / 4] = 0x10; \
            *(u16 *)((char *)a0 + 2) += 1; \
        } \
    }

#define DEFINE_func_8012A908() \
    extern u8 D_801202A0[]; \
    extern u16 D_801270C0; \
    extern void func_8012A988(u8 *a0); \
    void func_8012A908(void) { \
        u8 *p = D_801202A0; \
        s32 i; \
        for (i = 0; i < 0x60; i++) { \
            if (((s16)D_801270C0 == 1) || (*(u16 *)(p + 0x72) & 0x1000)) { \
                func_8012A988(p); \
            } \
            p += 0x10C; \
        } \
    }

#define DEFINE_func_80133060() \
    extern void func_801330E0(s16 *a0, s16 *a1, s32 a2); \
    void func_80133060(u8 *a0, s32 *a1, s32 a2) { \
        s16 tmp[3]; \
        tmp[0] = *(u16 *)(a0 + 2); \
        tmp[1] = *(u16 *)(a0 + 6); \
        tmp[2] = *(u16 *)(a0 + 0xA); \
        func_801330E0(tmp, tmp, (s16)a2); \
        a1[0] = tmp[0] << 16; \
        a1[1] = tmp[1] << 16; \
        a1[2] = tmp[2] << 16; \
    }

#define DEFINE_func_80142D38() \
    extern s32 func_8012BEE8(s32 a0); \
    s32 func_80142D38(s32 *a0) { \
        if (func_8012BEE8((s32)a0) == 1) { \
            return 1; \
        } \
        if (a0[0x1C / 4] & 1) { \
            ((s32 *)a0[0x20 / 4])[1] |= 0x80000000; \
        } else { \
            ((s32 *)a0[0x20 / 4])[1] &= 0x7FFFFFFF; \
        } \
        return 0; \
    }

#define DEFINE_func_80150BC8() \
    extern u16 D_800B99DA; \
    extern s32 func_801619D0(void *a0); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u8 func_8014BF6C(void); \
    extern s32 func_80151184(s32 a0, s32 a1, s32 a2); \
    void func_80150BC8(s32 *a0) { \
        if (func_801619D0(a0) != 0) { \
            if (D_800B99DA & 0x7) { \
                func_80146994(0x34, (s32)a0, 0, 0); \
            } \
        } else { \
            if ((func_8014BF6C() & 0xFF) == 0) { \
                func_80151184((s32)a0, 0xC003, 0x10); \
            } \
        } \
    }

#define DEFINE_func_80153410() \
    extern void func_80149020(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_801470B4(s32 a0); \
    extern void func_8015369C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80153410(s32 *a0) { \
        func_80149020(a0); \
        func_80148038((s32)a0, 0x18000); \
        func_80147460((s32)a0); \
        if (*(s16 *)((u8 *)a0 + 0xA) < 0x201) { \
            u8 v1 = *(u8 *)((u8 *)a0 + 0xDE); \
            *(u8 *)((u8 *)a0 + 0xDE) = v1 + 0xFF; \
            if (v1 != 0) { \
                return; \
            } \
        } \
        func_801470B4((s32)a0); \
        func_8015369C((s32)a0); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80153B58() \
    extern u16 D_800B99DA; \
    extern s32 func_8016DA04(s32 a0); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80153B58(s32 *a0) { \
        if ((D_800B99DA & 0x3) == 0) { \
            func_8016DA04((s32)a0); \
        } \
        if ((D_800B99DA & 0x1) == 0) { \
            func_80146A6C(3, a0, \
                          *(s16 *)((u8 *)a0 + 6), \
                          *(s16 *)((u8 *)a0 + 0xA), \
                          *(s16 *)((u8 *)a0 + 0xE), \
                          0x8880000, 0x18009000); \
        } \
    }

#define DEFINE_func_801592CC() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_80146C98(s32 *a0, s16 a1); \
    extern u8 D_80110C3C[]; \
    void func_801592CC(s32 *a0) { \
        s32 *s0 = a0; \
        s32 *v1 = (s32 *)s0[0x20 / 4]; \
        *(s16 *)((char *)v1 + 0x12) = (*(u16 *)((char *)v1 + 0x12) + 0x16) & 0xFFF; \
        if (func_801399F0(s0[0x198 / 4]) != 0) { \
            func_80139914(s0[0x198 / 4]); \
            s0[0x198 / 4] = func_8013767C((s32)D_80110C3C); \
            func_80146C98(s0, 9); \
        } \
    }

#define DEFINE_func_801642AC() \
    extern void func_80164418(); \
    extern s32 func_80013328(s32 a0, s32 a1); \
    extern s32 func_80146E98(s32 a0); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern void func_80163764(s32 a0); \
    void func_801642AC(s32 a0) { \
        s32 s1 = a0; \
        s32 s0 = *(s32 *)(s1 + 0x4C); \
        func_80164418(); \
        if (func_80013328(s0 + 4, s1 + 4) < 0x28 || func_80146E98(s1) != 0) { \
            func_80146E90((s32 *)s1, 8); \
            func_80147324(0x44A); \
            func_80146CA0((void *)s1); \
        } \
        func_80163764(s1); \
    }

#define DEFINE_func_8016D984() \
    extern void func_80146C3C(void); \
    extern void func_800D22E4(s32 a0); \
    void func_8016D984(s32 *a0) { \
        if ((--*(s32 *)((char *)a0 + 0x1C)) == 0) { \
            func_80146C3C(); \
        } else { \
            func_800D22E4((s32)a0); \
            *(s32 *)((char *)a0 + 0x10) -= *(s32 *)((char *)a0 + 0x10) >> 4; \
            *(s32 *)((char *)a0 + 0x14) -= *(s32 *)((char *)a0 + 0x14) >> 4; \
            *(s32 *)((char *)a0 + 0x18) -= *(s32 *)((char *)a0 + 0x18) >> 4; \
        } \
    }

#define DEFINE_func_8017162C() \
    extern void *D_8011F738; \
    extern s32 func_801716AC(s32 a0, void *a1, s32 *a2); \
    extern void func_80171928(void *a0); \
    void func_8017162C(void *a0) { \
        void *s1 = a0; \
        void *s0 = D_8011F738; \
        s32 local; \
        local = 0; \
        func_801716AC(0, s0, &local); \
        func_801716AC(1, s0, &local); \
        func_801716AC(2, s0, &local); \
        if (local == 0) { \
            func_80171928(s1); \
        } \
    }

#define DEFINE_func_80128C14() \
    extern void func_80010AE0(s32 a0); \
    extern s16 currentLocationId; \
    void func_80128C14(void) { \
        s32 a0; \
        switch (currentLocationId) { \
        case 0x3023: \
            a0 = 0x4E0; \
            break; \
        case 0x3081: \
            a0 = 0x420; \
            break; \
        case 0x3067: \
            a0 = 0x480; \
            break; \
        case 0x3093: \
            a0 = 0xFFB; \
            break; \
        case 0x30A5: \
            a0 = 0xFFB; \
            break; \
        default: \
            a0 = 0x3E0; \
            break; \
        } \
        func_80010AE0(a0); \
    }

#define DEFINE_func_8012B030() \
    extern s32 func_80134510(s32 arg); \
    s32 func_8012B030(u8 *a0) { \
        u16 local[3]; \
        local[0] = *(u16 *)(a0 + 0x6); \
        local[1] = *(u16 *)(a0 + 0xA); \
        local[2] = *(u16 *)(a0 + 0xE); \
        if (func_80134510((s32)local) == 0) { \
            return 0; \
        } \
        *(u16 *)(a0 + 0x6) = local[0]; \
        *(u16 *)(a0 + 0xA) = local[1]; \
        *(u16 *)(a0 + 0xE) = local[2]; \
        *(u16 *)(a0 + 0xC) = 0; \
        *(u16 *)(a0 + 0x8) = 0; \
        *(u16 *)(a0 + 0x4) = 0; \
        return 1; \
    }

#define DEFINE_func_8012FF98() \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_80130D48(s32 a0); \
    extern void func_801319E0(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FF98(u8 *a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x20) { \
            s32 p = *(s32 *)(a0 + 0x20); \
            if (p != 0) { \
                *(u32 *)(p + 4) ^= 0x80000000; \
            } \
            if (func_8012BEE8((s32)a0)) { \
                func_80130D48((s32)a0); \
                func_801319E0((s32)a0); \
            } \
        } \
        func_80131CA8((int)a0, 0x10); \
    }

#define DEFINE_func_801305CC() \
    extern s32 func_80131A34(s32, s32); \
    extern void func_80131CA8(int a0, int a1); \
    void func_801305CC(u8 *a0) { \
        *(u8 *)(a0 + 0xC1) = 0xC; \
        if (*(s32 *)(a0 + 0xB4) & 0x1000) { \
            *(s32 *)(a0 + 0x1C) = 0x3C; \
            *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) & ~4; \
            if (func_80131A34((s32)a0, 0x20)) { \
                *(s32 *)(a0 + 0xC4) = *(s32 *)(a0 + 0xC4) | 4; \
            } else { \
                *(u16 *)(a0 + 0x98) = 0; \
            } \
        } \
        func_80131CA8((int)a0, 0x22); \
    }

#define DEFINE_func_8015E9B8() \
    extern u8 D_80078EC0; \
    extern s16 D_801152A0; \
    extern void func_80160818(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80149034(s32 *a0); \
    extern void func_801553A8(s32 *a0); \
    extern s32 func_80149184(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015E9B8(s32 *a0) { \
        if (D_80078EC0 & 0x80) { \
            func_80160818(a0); \
        } else { \
            func_80154150((s32)a0, 0x1D); \
            a0[0x44 / 4] |= 1; \
            func_80149034(a0); \
            func_801553A8(a0); \
            D_801152A0 = func_80149184((s32)a0); \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_8012DF34() \
    extern s32 D_80126B58; \
    extern u8 D_801152A8[]; \
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5); \
    s32 func_8012DF34(s32 a0, s32 a1, s32 a2) { \
        s32 s0 = a2; \
        s32 *p = &D_80126B58; \
        if (a0 != 0) { \
            if (*(s16 *)(a0 + 0xAA) != 0) { \
                return 0; \
            } \
        } \
        if (func_80135888(*(s32 *)((s32)p + 0x20), *(s32 *)((s32)p + 0x38), a1, s0) != 0) { \
            func_8012F568(1, 1, 0, 0xA, s0, (s32)D_801152A8); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80139E84() \
    extern void func_80139A8C(s32 a0); \
    extern void func_80139B18(s32 a0); \
    void func_80139E84(s32 a0) { \
        s32 s0 = a0; \
        if (*(u16 *)(s0 + 0xE) == 0) { \
            *(s16 *)(s0 + 0x4) = 2; \
        } else { \
            func_80139A8C(s0); \
            if ((*(s32 *)(s0 + 0x8) & 0x80020) != 0) { \
                *(s16 *)(s0 + 0x4) = 2; \
                *(s16 *)(s0 + 0xE) = 0; \
                if ((*(s32 *)(s0 + 0x8) & 0x20000) == 0) { \
                    *(s32 *)(s0 + 0x8) = *(s32 *)(s0 + 0x8) & -0x21; \
                } \
            } \
        } \
        func_80139B18(s0); \
    }

#define DEFINE_func_80146FC4() \
    extern u8 D_80126DB0[]; \
    extern u16 D_80126DB6; \
    extern void func_80015954(s32 a0, s32 a1); \
    extern void *memcpy(void *dst, const void *src, u32 n); \
    void func_80146FC4(s32 a0) { \
        s32 s1 = a0; \
        s32 s0; \
        if (*(s16 *)(s1 + 0xA) >= 0x401) { \
            s0 = (s32)D_80126DB0; \
            func_80015954(s0, s1 + 0x4); \
            memcpy((void *)(s1 + 0x88), (void *)s0, 8); \
            *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6; \
        } \
    }

#define DEFINE_func_8014D0A4() \
    extern s32 func_8014D2A0(s32 a0, void *a1, void *a2); \
    extern s32 func_8014D12C(); \
    void func_8014D0A4(s32 a0) { \
        s16 buf1[4]; \
        s16 buf2[4]; \
        buf1[0] = *(u16 *)(a0 + 0x88); \
        buf1[1] = *(u16 *)(a0 + 0x8A); \
        buf1[2] = *(u16 *)(a0 + 0x8C); \
        buf2[0] = *(u16 *)(a0 + 0x6); \
        buf2[1] = *(u16 *)(a0 + 0xA); \
        buf2[2] = *(u16 *)(a0 + 0xE); \
        if (*(s32 *)(a0 + 0x174) == 0) { \
            func_8014D2A0(a0, buf1, buf2); \
        } else { \
            func_8014D12C(a0, buf1, buf2); \
        } \
    }

#define DEFINE_func_8014D438() \
    extern void func_8014D610(s32 a0, void *a1, void *a2); \
    extern s32 func_8014D4C0(s32 a0, void *a1, void *a2); \
    void func_8014D438(s32 a0) { \
        s16 buf1[4]; \
        s16 buf2[4]; \
        buf1[0] = *(u16 *)(a0 + 0x88); \
        buf1[1] = *(u16 *)(a0 + 0x8A); \
        buf1[2] = *(u16 *)(a0 + 0x8C); \
        buf2[0] = *(u16 *)(a0 + 0x6); \
        buf2[1] = *(u16 *)(a0 + 0xA); \
        buf2[2] = *(u16 *)(a0 + 0xE); \
        if (*(s32 *)(a0 + 0x174) == 0) { \
            func_8014D610(a0, buf1, buf2); \
        } else { \
            func_8014D4C0(a0, buf1, buf2); \
        } \
    }

#define DEFINE_func_80158CD8() \
    extern u16 func_801487F4(s32 *a0); \
    extern s32 func_80146E98(s32 a0); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80158CD8(s32 *a0) { \
        s32 i = 1; \
        if (func_801487F4(a0) & 0xF0) { \
            i = 4; \
        } \
        while (i > 0) { \
            if (func_80146E98((s32)a0)) { \
                func_80147324(0x453); \
                *(s32 *)((s32)a0 + 0x238) = 0x5B0000; \
                func_80146CA0((void *)a0); \
                i = 0; \
            } \
            i--; \
        } \
    }

#define DEFINE_func_801598E0() \
    extern void func_80159968(void *a0); \
    void func_801598E0(u8 *a0) { \
        switch (a0[0xA9]) { \
        case 0x41: \
            *(u16 *)(a0 + 0xAA) &= 0xAFFF; \
            *(u16 *)(a0 + 0xAC) &= 0xAFFF; \
            break; \
        case 0x53: \
        case 0x73: \
            *(u16 *)(a0 + 0xAE) = a0[0xAE] | 0x8000; \
            break; \
        } \
        func_80159968((void *)a0); \
    }

#define DEFINE_func_801741EC() \
    extern s32 func_80012B04(s32 a0, s32 a1, s32 a2); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B3C; \
    extern s16 D_8011F9C8; \
    void func_801741EC(u8 *a0) { \
        s32 v0; \
        s32 s1; \
        s32 t; \
        v0 = *(s32 *)(a0 + 0x20); \
        s1 = func_80012B04(*(s16 *)(v0 + 0x12), D_80126B3C, 4); \
        if ((s16)s1 == 0) { \
            D_8011F9C8 = 1; \
            func_80171A1C(a0); \
            func_80174650((s32)a0); \
        } \
        t = *(s32 *)(a0 + 0x20); \
        *(u16 *)(t + 0x12) = (*(u16 *)(t + 0x12) + s1) & 0xFFF; \
    }

#define DEFINE_func_8012F2E8() \
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2); \
    void func_8012F2E8(s32 a0, s32 a1, s32 a2) { \
        s32 s0 = a2; \
        s32 in[3]; \
        s32 out[3]; \
        s32 mtx; \
        mtx = *(s32 *)(a0 + 0x20); \
        in[0] = *(s16 *)(a1 + 0x0) - *(s32 *)(mtx + 0x48); \
        in[1] = *(s16 *)(a1 + 0x2) - *(s32 *)(mtx + 0x4C); \
        in[2] = *(s16 *)(a1 + 0x4) - *(s32 *)(mtx + 0x50); \
        ApplyTransposeMatrixLV((void *)(mtx + 0x34), in, out); \
        *(s16 *)(s0 + 0x0) = out[0]; \
        *(s16 *)(s0 + 0x2) = out[1]; \
        *(s16 *)(s0 + 0x4) = out[2]; \
    }

#define DEFINE_func_801377B4() \
    extern s32 D_80127524; \
    extern s32 D_80127528; \
    extern void func_80137840(s32 a0); \
    void func_801377B4(s32 a0, s32 a1, s32 a2) { \
        s32 s1 = a0; \
        s32 s0 = a1; \
        s32 s2 = a2; \
        s32 *p; \
        s32 v1; \
        func_80137840(s2); \
        *(s16 *)(s2 + 0x4) = 1; \
        *(s32 *)(s2 + 0x0) = s1; \
        *(s32 *)(s2 + 0x8) = (s16)s0; \
        if ((s0 & 0x2000) == 0) { \
            p = &D_80127524; \
            v1 = *p; \
            if (v1 != 0) { \
                D_80127528 = v1; \
                *(s16 *)(v1 + 0x1A) = 2; \
            } \
            *p = s2; \
        } \
    }

#define DEFINE_func_80139A8C() \
    extern s32 func_80014E80(s32 a0, s32 a1); \
    extern void func_8001931C(void); \
    extern s16 D_8012752C; \
    void func_80139A8C(s32 a0) { \
        s32 s0 = a0; \
        s32 v0; \
        s32 v1; \
        v0 = *(s32 *)(s0 + 0x8); \
        if ((v0 & 0x2021) != 0) { \
            return; \
        } \
        if ((s16)func_80014E80(0, 0x20) == 0) { \
            return; \
        } \
        v0 = *(s32 *)(s0 + 0x8); \
        v1 = v0 | 0x20; \
        *(s32 *)(s0 + 0x8) = v1; \
        if ((v1 & 0x10000) == 0) { \
            return; \
        } \
        *(s32 *)(s0 + 0x8) = (v1 & 0xFFFEFFFF) | 0x20000; \
        func_8001931C(); \
        D_8012752C = 0; \
    }

#define DEFINE_func_801490F8() \
    extern s32 func_80012B04(s32 a0, s32 a1, s32 a2); \
    void func_801490F8(s32 a0, s32 a1) { \
        s32 s0 = a0; \
        s32 s1 = (s16)a1; \
        *(s16 *)(s0 + 0x100) = \
            *(u16 *)(s0 + 0x100) + \
            func_80012B04(*(s16 *)(s0 + 0x100), *(s16 *)(s0 + 0x108), s1); \
        *(s16 *)(s0 + 0x102) = \
            *(u16 *)(s0 + 0x102) + \
            func_80012B04(*(s16 *)(s0 + 0x102), *(s16 *)(s0 + 0x10A), s1); \
        *(s16 *)(s0 + 0x104) = \
            *(u16 *)(s0 + 0x104) + \
            func_80012B04(*(s16 *)(s0 + 0x104), *(s16 *)(s0 + 0x10C), s1); \
    }

#define DEFINE_func_8016829C() \
    extern void func_80146C3C(void); \
    extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_8016829C(s32 a0) { \
        s32 *s0 = (s32 *)a0; \
        if ((*(s32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 0x2) == 0) { \
            func_80146C3C(); \
        } else { \
            s16 v0 = *(u16 *)(a0 + 0x2A) - 1; \
            *(s16 *)(a0 + 0x2A) = v0; \
            if (v0 == 0) { \
                func_80166994(a0, 0, *(s16 *)(a0 + 0x2C), 0); \
                *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1; \
            } \
        } \
        (void)s0; \
    }

#define DEFINE_func_801684B4() \
    extern void func_80146C3C(void); \
    extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_801684B4(s32 a0) { \
        if ((*(s32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 0x2) == 0) { \
            func_80146C3C(); \
        } else { \
            s16 v0 = *(u16 *)(a0 + 0x2A) - 1; \
            *(s16 *)(a0 + 0x2A) = v0; \
            if (v0 == 0) { \
                func_80166994(a0, 0, 2, 0); \
                *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1; \
            } \
        } \
    }

#define DEFINE_func_80168AE4() \
    extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80168AE4(s32 a0) { \
        s32 s0 = a0; \
        func_80168BDC(s0, 9, 3, 2); \
        func_80168BDC(s0, 9, 2, 1); \
        func_80146A6C(3, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA), \
                      *(s16 *)(s0 + 0xE), -5, 0xC0009C00); \
        *(s32 *)(s0 + 0x1C) = 1; \
        *(s16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1; \
    }

#define DEFINE_func_8012F0BC() \
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2); \
    void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2) { \
        s32 in[3]; \
        s32 out[3]; \
        in[0] = a1[0] - (a0[5] << 16); \
        in[1] = a1[1] - (a0[6] << 16); \
        in[2] = a1[2] - (a0[7] << 16); \
        ApplyTransposeMatrixLV(a0, in, out); \
        a2[0] = out[0]; \
        a2[1] = out[1]; \
        a2[2] = out[2]; \
    }

#define DEFINE_func_8014D790() \
    extern s32 func_8014DD8C(s32 a0, void *a1, void *a2); \
    extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2); \
    void func_8014D790(s32 a0) { \
        s16 l1[3]; \
        s16 l2[3]; \
        l1[0] = *(u16 *)(a0 + 0x88); \
        l1[1] = *(u16 *)(a0 + 0x8A) - 0x10; \
        l1[2] = *(u16 *)(a0 + 0x8C); \
        l2[0] = *(u16 *)(a0 + 0x6); \
        l2[1] = *(u16 *)(a0 + 0xA) - 0x10; \
        l2[2] = *(u16 *)(a0 + 0xE); \
        if (*(s32 *)(a0 + 0x170) == 0) { \
            func_8014DD8C(a0, l1, l2); \
        } else { \
            func_8014D820(a0, l1, l2); \
        } \
    }

#define DEFINE_func_80178744() \
    extern void func_80178744(s32 a0, s32 a1); \
    void func_80178744(s32 a0, s32 a1) { \
        s32 v0; \
        s16 sv; \
        if (*(s32 *)(a0 + 0x6C) != 0) { \
            func_80178744(*(s32 *)(a0 + 0x6C), a1); \
        } \
        v0 = *(s32 *)(a0 + 0x20); \
        sv = a1; \
        *(s16 *)(v0 + 0x1C) = sv; \
        *(s16 *)(v0 + 0x1A) = sv; \
        *(s16 *)(v0 + 0x18) = sv; \
        if (a1 == 0x1000) { \
            s32 v1 = *(s32 *)(a0 + 0x20); \
            *(u16 *)(v1 + 0x2C) = *(u16 *)(v1 + 0x2C) & 0xFFEF; \
        } else { \
            s32 v1 = *(s32 *)(a0 + 0x20); \
            *(u16 *)(v1 + 0x2C) = *(u16 *)(v1 + 0x2C) | 0x10; \
        } \
    }

#define DEFINE_func_80142838() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_8012C0EC(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    extern void func_80142C9C(s32 *a0); \
    extern s32 func_8012BF10(s32 a0, s32 a1); \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    void func_80142838(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
            return; \
        } \
        if (*(s16 *)((u8 *)a0 + 0x100) != 0) { \
            if (func_8012C0EC(a0) == 0) { \
                return; \
            } \
            func_80142BB4(a0, 0, 3); \
            return; \
        } \
        func_80142C9C(a0); \
        if (func_8012BF10((s32)a0, 0x30) != 0) { \
            func_8012AD44(a0, 2); \
        } \
    }

#define DEFINE_func_80142F68() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_8012C0EC(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    extern void func_80142C9C(s32 *a0); \
    extern s32 func_8012BF10(s32 a0, s32 a1); \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    void func_80142F68(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
            return; \
        } \
        if (*(s16 *)((u8 *)a0 + 0x100) != 0) { \
            if (func_8012C0EC(a0) == 0) { \
                return; \
            } \
            func_80142BB4(a0, 0, 3); \
            return; \
        } \
        func_80142C9C(a0); \
        if (func_8012BF10((s32)a0, 0x30) != 0) { \
            func_8012AD44(a0, 2); \
        } \
    }

#define DEFINE_func_801430F4() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_8012C0EC(s32 *a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    extern void func_80142C9C(s32 *a0); \
    extern s32 func_8012BF10(s32 a0, s32 a1); \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    void func_801430F4(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
            return; \
        } \
        if (*(s16 *)((u8 *)a0 + 0x100) != 0) { \
            if (func_8012C0EC(a0) == 0) { \
                return; \
            } \
            func_80142BB4(a0, 0, 3); \
            return; \
        } \
        func_80142C9C(a0); \
        if (func_8012BF10((s32)a0, 0x30) != 0) { \
            func_8012AD44(a0, 2); \
        } \
    }

#define DEFINE_func_8014B504() \
    extern s32 func_8016F1AC(void); \
    extern s16 D_80078E9A; \
    extern s32 D_80078E98; \
    void func_8014B504(u16 *a0) { \
        s32 v1; \
        if (func_8016F1AC() != 0) { \
            return; \
        } \
        if (*a0 == 0x1E || *a0 == 0x1A) { \
            return; \
        } \
        if ((D_80078E9A & 0x8000) == 0) { \
            return; \
        } \
        v1 = D_80078E98 + 0x1555; \
        D_80078E98 = v1; \
        if (0x257F6A < (v1 & 0x7FFF0000)) { \
            D_80078E98 = 0; \
        } \
    }

#define DEFINE_func_801636D0() \
    extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3); \
    extern u16 D_80126B18[]; \
    extern s32 D_80115200; \
    void func_801636D0(s32 a0, s32 a1) { \
        u32 i; \
        s32 v; \
        u16 *p; \
        s32 *q; \
        i = 0; \
        v = a1 & 0x7FFF; \
        p = D_80126B18; \
        q = &D_80115200; \
        do { \
            if (*q & 1) { \
                func_8014AD30(a0, p, 0, v & 0xFFFF); \
            } \
            p += 4; \
            i++; \
            q += 1; \
        } while (i < 3); \
    }

#define DEFINE_func_80176D00() \
    extern s32 func_80178004(s32 a0, s32 a1, s32 a2); \
    extern u8 D_8011F7B1; \
    extern u8 D_8011F7A8; \
    extern u16 D_80078EA6; \
    extern u16 D_8011F7B4; \
    extern u16 D_8011F7B6; \
    extern s16 D_8011F81E; \
    void func_80176D00(s32 a0) { \
        u8 *arr = (u8 *)&D_8011F7A8; \
        u8 *base; \
        s32 tmp; \
        s32 a1v, a2v; \
        if (D_8011F7B1 != 0) { \
            return; \
        } \
        base = arr + (s16)a0 * 4; \
        tmp = *(s32 *)(base + 0x20) + 0x14; \
        *(s32 *)(base + 0x38) = tmp; \
        a1v = (s16)(D_8011F7B4 - 0x17); \
        a2v = (s16)(D_8011F7B6 + 0x65); \
        D_8011F81E = D_80078EA6; \
        *(s32 *)(base + 0x40) = func_80178004(tmp, a1v, a2v) - 0x14; \
    }

#define DEFINE_func_80178608() \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_8013E4B4(void); \
    extern u8 D_801202A0[]; \
    extern u16 D_801270C0; \
    extern s16 D_801270C4; \
    extern s32 D_801274D8; \
    extern s16 D_801270C2; \
    extern u8 D_801270C6; \
    extern u8 D_801270C7; \
    extern s32 D_801274DC; \
    extern s32 D_801274E0; \
    void func_80178608(void) { \
        u16 *p = &D_801270C0; \
        func_80016714(D_801202A0, 0x6480); \
        *p = 1; \
        D_801270C4 = 1; \
        D_801274D8 = 0x240000; \
        D_801270C2 = 0; \
        D_801270C6 = 0; \
        D_801270C7 = 0; \
        D_801274DC = 0x271000; \
        D_801274E0 = 0x400000; \
        func_80016714((u8 *)p + 8, 0x400); \
        func_8013E4B4(); \
    }

#define DEFINE_func_8017C0BC() \
    extern void func_80146C3C(void); \
    void func_8017C0BC(u8 *p) { \
        u8 *q; \
        s32 t; \
        s32 b; \
        q = *(u8 **)(p + 0x20); \
        *(u16 *)(p + 0x16) = *(u16 *)(p + 0x16) + *(u16 *)(p + 0x14); \
        if (*(s32 *)(p + 0x1C) < 8) { \
            *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x200; \
        } else { \
            *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x51; \
        } \
        b = *(u8 *)(q + 0x26) - 2; \
        *(s16 *)(q + 0x1A) = *(u16 *)(p + 0x16); \
        *(s8 *)(q + 0x26) = b; \
        *(s8 *)(q + 0x25) = b; \
        *(s8 *)(q + 0x24) = b; \
        t = *(s32 *)(p + 0x1C); \
        *(s32 *)(p + 0x1C) = t + 1; \
        if (t >= 0x1E) { \
            ((void (*)(u8 *))func_80146C3C)(p); \
        } \
    }

#define DEFINE_func_80128420() \
    extern void func_80129220(void); \
    extern void func_801378F0(void); \
    extern void func_80011E24(void); \
    extern void func_80128C14(void); \
    extern void func_8002AEF8(void); \
    extern void func_800CFBBC(void); \
    extern void func_80015310(void); \
    extern void SsUtReverbOff(void); \
    extern void func_8013C98C(void); \
    extern void func_80129C40(s32 a0); \
    extern void func_800D0630(void); \
    extern void func_80145CEC(void); \
    extern void func_80144B9C(void); \
    extern void func_80011C10(void); \
    extern u8 D_800B9A17; \
    extern u8 D_800B9A10; \
    void func_80128420(void) { \
        func_80129220(); \
        func_801378F0(); \
        func_80011E24(); \
        func_80128C14(); \
        func_8002AEF8(); \
        func_800CFBBC(); \
        func_80015310(); \
        SsUtReverbOff(); \
        D_800B9A17 = 0; \
        D_800B9A10 = 0; \
        func_8013C98C(); \
        func_80129C40(0); \
        func_800D0630(); \
        func_80145CEC(); \
        func_80144B9C(); \
        func_80011C10(); \
    }

#define DEFINE_func_8012BDBC() \
    extern s16 D_80126CB8; \
    extern s16 D_80126CB4; \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012BDBC(s32 a0, s32 a1) { \
        s32 s0 = a0; \
        s32 v0; \
        s32 angle; \
        v0 = ratan2(*(s16 *)(s0 + 0xE) - D_80126CB8, D_80126CB4 - *(s16 *)(s0 + 0x6)); \
        v0 = (v0 - 0x400) & 0xFFF; \
        v0 = v0 - *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12); \
        angle = v0 & 0xFFF; \
        if (angle < 0x800) { \
            return angle < (s16)a1; \
        } \
        return (0x1000 - angle) < (s16)a1; \
    }

#define DEFINE_func_8013E064() \
    extern int SquareRoot12(int a0); \
    int func_8013E064(s16 *a0, s16 *a1) { \
        s32 d[3]; \
        s32 sq[3]; \
        d[0] = a0[1] - a1[1]; \
        d[1] = a0[3] - a1[3]; \
        d[2] = a0[5] - a1[5]; \
        __asm__ __volatile__("" ::: "memory"); \
        { \
            register s32 *pd __asm__("$2") = &d[0]; \
            __asm__ __volatile__( \
                "lwc2 $9, 0(%0)\n" \
                "lwc2 $10, 4(%0)\n" \
                "lwc2 $11, 8(%0)\n" \
                "nop\n" \
                "nop\n" \
                "sqr 1\n" \
                : : "r"(pd) : "$9", "$10", "$11", "memory"); \
        } \
        { \
            register s32 *pq __asm__("$2") = &sq[0]; \
            __asm__ __volatile__( \
                "swc2 $25, 0(%0)\n" \
                "swc2 $26, 4(%0)\n" \
                "swc2 $27, 8(%0)\n" \
                : : "r"(pq) : "memory"); \
        } \
        return SquareRoot12(sq[0] + sq[1] + sq[2]); \
    }

#define DEFINE_func_8013E0FC() \
    extern int SquareRoot12(int a0); \
    int func_8013E0FC(s16 *a0, s16 *a1) { \
        s32 d[3]; \
        s32 sq[3]; \
        d[0] = a0[1] - a1[0]; \
        d[1] = a0[3] - a1[1]; \
        d[2] = a0[5] - a1[2]; \
        __asm__ __volatile__("" ::: "memory"); \
        { \
            register s32 *pd __asm__("$2") = &d[0]; \
            __asm__ __volatile__( \
                "lwc2 $9, 0(%0)\n" \
                "lwc2 $10, 4(%0)\n" \
                "lwc2 $11, 8(%0)\n" \
                "nop\n" \
                "nop\n" \
                "sqr 1\n" \
                : : "r"(pd) : "$9", "$10", "$11", "memory"); \
        } \
        { \
            register s32 *pq __asm__("$2") = &sq[0]; \
            __asm__ __volatile__( \
                "swc2 $25, 0(%0)\n" \
                "swc2 $26, 4(%0)\n" \
                "swc2 $27, 8(%0)\n" \
                : : "r"(pq) : "memory"); \
        } \
        return SquareRoot12(sq[0] + sq[1] + sq[2]); \
    }

#define DEFINE_func_8013E194() \
    extern int SquareRoot12(int a0); \
    int func_8013E194(s16 *a0, s16 *a1) { \
        s32 d[3]; \
        s32 sq[3]; \
        d[0] = a0[0] - a1[0]; \
        d[1] = a0[1] - a1[1]; \
        d[2] = a0[2] - a1[2]; \
        __asm__ __volatile__("" ::: "memory"); \
        { \
            register s32 *pd __asm__("$2") = &d[0]; \
            __asm__ __volatile__( \
                "lwc2 $9, 0(%0)\n" \
                "lwc2 $10, 4(%0)\n" \
                "lwc2 $11, 8(%0)\n" \
                "nop\n" \
                "nop\n" \
                "sqr 1\n" \
                : : "r"(pd) : "$9", "$10", "$11", "memory"); \
        } \
        { \
            register s32 *pq __asm__("$2") = &sq[0]; \
            __asm__ __volatile__( \
                "swc2 $25, 0(%0)\n" \
                "swc2 $26, 4(%0)\n" \
                "swc2 $27, 8(%0)\n" \
                : : "r"(pq) : "memory"); \
        } \
        return SquareRoot12(sq[0] + sq[1] + sq[2]); \
    }

#define DEFINE_func_80146EC0() \
    extern void func_80015954(s32 a0, s32 a1); \
    extern void func_80149374(s32 a0, s32 a1); \
    extern void func_80146F58(s32 a0, s32 a1); \
    void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 s2 = a0; \
        s32 s0 = a1; \
        s32 s1 = a3; \
        u16 buf[3]; \
        func_80015954(a2, a1); \
        func_80149374(s2, s0); \
        func_80146F58(s1, (s32)&buf[0]); \
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + buf[0]; \
        *(u16 *)(s0 + 6) = *(u16 *)(s0 + 6) + buf[1]; \
        *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + buf[2]; \
    }

#define DEFINE_func_80158C40() \
    extern u16 func_801487F4(s32 *a0); \
    extern s32 func_80159404(s32 a0, s32 a1); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    void func_80158C40(s32 *a0) { \
        s32 n; \
        s32 c; \
        c = 0x3C000; \
        n = 1; \
        if (func_801487F4(a0) & 0xF0) { \
            n = 4; \
        } \
        while (n > 0) { \
            func_80159404((s32)a0, c); \
            if (a0[0x234 / 4] < 0) { \
                func_80146E90(a0, 4); \
                func_80146CA0(a0); \
                n = 0; \
            } \
            n--; \
        } \
    }

#define DEFINE_func_80128678() \
    extern void func_80029444(void); \
    extern void func_8014607C(void); \
    extern void func_801287B8(void); \
    extern void func_800D1754(void); \
    void func_80128678(void) { \
        __asm__ __volatile__( \
            ".set noreorder\n" \
            "addiu $sp, $sp, -24\n" \
            "sw    $ra, 16($sp)\n" \
            "lui   $v0, 0x1f80\n" \
            "ori   $v0, $v0, 0x03fc\n" \
            "addu  $t0, $v0, $zero\n" \
            "sw    $sp, 0($t0)\n" \
            "addiu $t0, $t0, -4\n" \
            "addu  $sp, $t0, $zero\n" \
            "jal   func_80029444\n" \
            "addiu $sp, $sp, 4\n" \
            "lw    $sp, 0($sp)\n" \
            "jal   func_8014607C\n" \
            "lui   $v0, 0x1f80\n" \
            "ori   $v0, $v0, 0x03fc\n" \
            "addu  $t0, $v0, $zero\n" \
            "sw    $sp, 0($t0)\n" \
            "addiu $t0, $t0, -4\n" \
            "addu  $sp, $t0, $zero\n" \
            "jal   func_801287B8\n" \
            "addiu $sp, $sp, 4\n" \
            "lw    $sp, 0($sp)\n" \
            "lui   $v0, 0x1f80\n" \
            "ori   $v0, $v0, 0x03fc\n" \
            "addu  $t0, $v0, $zero\n" \
            "sw    $sp, 0($t0)\n" \
            "addiu $t0, $t0, -4\n" \
            "addu  $sp, $t0, $zero\n" \
            "jal   func_800D1754\n" \
            "addiu $sp, $sp, 4\n" \
            "lw    $sp, 0($sp)\n" \
            "nop\n" \
            "lw    $ra, 16($sp)\n" \
            "addiu $sp, $sp, 24\n" \
            : : : "memory"); \
    }

#define DEFINE_func_80152790() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80152790(s32 a0) { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_8013E370() \
    extern void *D_801274CC; \
    extern s32 func_8013E410(void); \
    extern s32 func_8013E448(s32 a0); \
    extern void func_8012C724(s32 a0, s32 a1); \
    void func_8013E370(void) { \
        u8 *s0; \
        u8 *s2; \
        s32 r; \
        s0 = (u8 *)D_801274CC; \
        if (s0 == 0) return; \
        if (*(u16 *)(s0 + 6) == 0) return; \
        s2 = s0 + 6; \
        do { \
            if ((*(u16 *)(s2 + 4) & 0x8000) == 0) { \
                r = func_8013E410(); \
                if (r == 0) return; \
                if (func_8013E448((s32)s0) != 0) { \
                    func_8012C724((s32)s0, r); \
                } \
            } \
            s2 += 0x14; \
            s0 += 0x14; \
        } while (*(u16 *)s2 != 0); \
    }

#define DEFINE_func_8014E514() \
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); \
    s32 func_8014E514(u8 *a0, s32 a1, s32 a2) { \
        u8 *p; \
        s32 q; \
        p = *(u8 **)(a0 + 0x17C); \
        if (*(u16 *)p != 0 && \
            (*(u16 *)(p + 0x5C) & 0x40) != 0 && \
            (q = *(s32 *)(p + 0x58)) != 0 && \
            func_80135888(*(s32 *)(p + 0x20), q, a1, a2) != 0) { \
            goto success; \
        } \
        *(s32 *)(a0 + 0x17C) = 0; \
        return 0; \
    success: \
        *(u16 *)(a0 + 6) = *(u16 *)(p + 6); \
        *(u16 *)(a0 + 0xE) = *(u16 *)(p + 0xE); \
        return 1; \
    }

#define DEFINE_func_8015B858() \
    extern u8 D_800D4BE0[]; \
    extern s32 D_8011F730; \
    extern s32 func_8014A51C(); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    s32 func_8015B858(u8 *a0) { \
        if (*(u8 *)(a0 + 0x1C6) != 0) return 0; \
        if (*(s32 *)(a0 + 0x240) != 0) return 0; \
        if (func_8014A51C() == 0) return 0; \
        *(s32 *)(a0 + 0x23C) = *(s32 *)(a0 + 0xB4); \
        *(u8 *)(a0 + 0x244) = *(u8 *)(a0 + 0xBC); \
        func_801477E8((s32 *)a0, 0xFFF20000); \
        func_80154274((s32 *)a0, (s32)D_800D4BE0); \
        D_8011F730 |= 2; \
        return 1; \
    }

#define DEFINE_func_80163194() \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    extern void func_80162F60(s32 arg0, s32 arg1); \
    extern void func_80162F80(s32 arg0, s32 arg1); \
    extern void func_80162FA0(s32 arg0, s32 arg1); \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    extern void func_80146D30(s32 a0); \
    void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4) { \
        s32 pad[4]; \
        s32 out[3]; \
        (void)pad; \
        func_80162F60(a0, a1); \
        func_80162F80(a0, a2); \
        func_80162FA0(a0, a3); \
        func_800484EC(arg4, a0 + 0x24, (s32)out); \
        D_80127090 = out[0]; \
        D_80127094 = out[1]; \
        D_80127098 = out[2]; \
        func_80146D30(a0); \
    }

#define DEFINE_func_8012B370() \
    extern void RotMatrixYXZ(void *m, void *p); \
    void func_8012B370(int a0) { \
        int q; \
        int p; \
        q = *(int *)(a0 + 0x20); \
        if (q != 0) { \
            RotMatrixYXZ((void *)(q + 0x10), (void *)(q + 0x34)); \
            p = *(int *)(a0 + 0x20); \
            *(s16 *)(p + 0x8) = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50); \
            *(s32 *)(p + 0x48) = *(s16 *)(p + 0x8); \
            *(s16 *)(p + 0xA) = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52); \
            *(s32 *)(p + 0x4C) = *(s16 *)(p + 0xA); \
            { \
                u16 e = *(u16 *)(a0 + 0xE); \
                u16 t2c = *(u16 *)(p + 0x2C) | 0x1; \
                s16 sum = e + *(u16 *)(a0 + 0x54); \
                *(s16 *)(p + 0xC) = sum; \
                *(u16 *)(p + 0x2C) = t2c; \
                *(s32 *)(p + 0x50) = sum; \
            } \
        } \
    }

#define DEFINE_func_8012B414() \
    extern void func_8004978C(s16 *a0, void *a1); \
    void func_8012B414(int a0) { \
        int q; \
        int p; \
        q = *(int *)(a0 + 0x20); \
        if (q != 0) { \
            func_8004978C((s16 *)(q + 0x10), (void *)(q + 0x34)); \
            p = *(int *)(a0 + 0x20); \
            *(s16 *)(p + 0x8) = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50); \
            *(s32 *)(p + 0x48) = *(s16 *)(p + 0x8); \
            *(s16 *)(p + 0xA) = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52); \
            *(s32 *)(p + 0x4C) = *(s16 *)(p + 0xA); \
            { \
                u16 e = *(u16 *)(a0 + 0xE); \
                u16 t2c = *(u16 *)(p + 0x2C) | 0x1; \
                s16 sum = e + *(u16 *)(a0 + 0x54); \
                *(s16 *)(p + 0xC) = sum; \
                *(u16 *)(p + 0x2C) = t2c; \
                *(s32 *)(p + 0x50) = sum; \
            } \
        } \
    }

#define DEFINE_func_801469C8() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern s32 D_8011D030; \
    s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8) { \
        int count; \
        int p; \
        int end; \
        count = 0; \
        p = (int)&D_8011D030; \
        end = p + 0xA50; \
        if ((u32)p < (u32)end) { \
            int key = a0 & 0xFFFF; \
            do { \
                if (*(u16 *)(p + 0x0) == key) { \
                    count++; \
                } \
                p += 0x58; \
            } while ((u32)p < (u32)end); \
        } \
        if ((u32)count < (u32)arg8) { \
            return func_80146A6C(a0 & 0xFFFF, a1, (s16)a2, (s16)a3, (s16)arg5, arg6, arg7); \
        } \
        return 0; \
    }

#define DEFINE_func_80152AC8() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80152AC8(s32 a0) { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        *(s8 *)(s0 + 0xA8) = 0x20; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_80152FBC() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80152FBC(s32 a0) { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        *(s8 *)(s0 + 0xA8) = 0x20; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_8015327C() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_8015327C(s32 a0) { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        *(s8 *)(s0 + 0xA8) = 0x20; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_80153550() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80153550(s32 a0) { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        *(s8 *)(s0 + 0xA8) = 0x20; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_8015640C() \
    extern s32 func_801564B0(s32 a0); \
    extern s32 func_80029178(s32 a0); \
    s32 func_8015640C(s32 a0, s32 a1) { \
        if ((func_801564B0(a0) & 0xFFFF) != 0) { \
            if ((func_80029178(0x1C) & 0xFF) != 0) { \
                return (((175 * (a1 & 0xFFFF)) / 100) & 0xFFFF) | 0x8000; \
            } else { \
                return (((150 * (a1 & 0xFFFF)) / 100) & 0xFFFF) | 0x8000; \
            } \
        } \
        return a1 & 0xFFFF; \
    }

#define DEFINE_func_8015B7B4() \
    extern s32 func_80149B54(s32 *a0); \
    extern void func_80156648(s32 *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80147324(s32 a0); \
    extern void func_80147300(u16 arg0); \
    extern u8 D_800D4F8C[]; \
    s32 func_8015B7B4(s32 a0) { \
        s32 s0 = a0; \
        if (func_80149B54((s32 *)s0) != 0) { \
            func_80156648((s32 *)s0); \
            *(s8 *)(s0 + 0x1AA) = 0xC; \
            *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 0x2; \
            *(s32 *)(s0 + 0x23C) = *(s32 *)(s0 + 0xB4); \
            *(s8 *)(s0 + 0x244) = *(u8 *)(s0 + 0xBC); \
            func_80154274((s32 *)s0, (s32)D_800D4F8C); \
            func_80154A74(s0, 0x22); \
            *(s8 *)(s0 + 0xDA) = 0; \
            func_80146994(5, s0, 5, 0); \
            func_80147324(0x455); \
            func_80147300(0x5F3); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8015E40C() \
    extern void func_80148534(s32 a0, s32 a1); \
    extern void func_80149374(s32 a0, s32 a1); \
    void func_8015E40C(s32 a0) { \
        s32 s1 = a0; \
        s32 s0; \
        s16 sp10[4]; \
        u16 sp18[4]; \
        s0 = *(s32 *)(s1 + 0x18C); \
        if (s0 == 0) { \
            return; \
        } \
        if (*(u16 *)(s0 + 0x0) == 0) { \
            return; \
        } \
        func_80148534((s32)sp10, (s32)sp18); \
        *(s16 *)(s0 + 0x6) = sp18[0] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0xC); \
        *(s16 *)(s0 + 0xA) = sp18[1] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0xE); \
        *(s16 *)(s0 + 0xE) = sp18[2] + *(u16 *)(*(s32 *)(s0 + 0x78) + 0x10); \
        func_80149374(s1, s0 + 0x4); \
    }

#define DEFINE_func_8015FDCC() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80147324(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern s32 func_80028DE0(void); \
    extern u8 func_80165700(s32 a0, s32 a1); \
    extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8); \
    extern void func_80146CA0(void *a0); \
    void func_8015FDCC(s32 a0) { \
        s32 s0 = a0; \
        if (func_801399F0(*(s32 *)(s0 + 0x198)) != 0) { \
            func_80147324(0x19); \
            func_80139914(*(s32 *)(s0 + 0x198)); \
            *(s32 *)(s0 + 0x198) = 0; \
            if (func_80028DE0() == 0) { \
                if ((func_80165700(s0, *(u8 *)(s0 + 0x1A0)) & 0xFF) != 0) { \
                    func_801466F0(0x24, s0, 0, 0, 0, 0, 0, 0); \
                    func_80147324(0x989); \
                } \
            } \
            func_80146CA0((void *)s0); \
        } \
    }

#define DEFINE_func_8017C66C() \
    extern void ReadRotMatrix(void *a0); \
    extern void PushMatrix(void); \
    extern void func_8004974C(void *a0, void *a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    extern void PopMatrix(void); \
    void func_8017C66C(u16 *a0, void *a1) { \
        s32 mat[8]; \
        s32 buf[8]; \
        s16 sv[4]; \
        ReadRotMatrix((void *)mat); \
        PushMatrix(); \
        sv[0] = (s16)(a0[0] - *(s32 *)((u8 *)mat + 0x14)); \
        sv[1] = (s16)(a0[1] - *(s32 *)((u8 *)mat + 0x18)); \
        sv[2] = (s16)(a0[2] - *(s32 *)((u8 *)mat + 0x1C)); \
        func_8004974C((void *)mat, (void *)buf); \
        ApplyMatrixSV((void *)buf, (void *)sv, a1); \
        PopMatrix(); \
    }

#define DEFINE_func_801307B0() \
    extern s32 func_801312D0(s32 a0, void *a1); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_801307B0(s32 a0) { \
        s16 local[3]; \
        *(s8 *)(a0 + 0xC1) = 0x10; \
        *(s16 *)(a0 + 0x5C) = 0; \
        func_801312D0(a0, &local[0]); \
        func_80146A6C(0x10, (void *)a0, \
                      (s16)(*(u16 *)(a0 + 0x6) + (u16)local[0]), \
                      (s16)(*(u16 *)(a0 + 0xA) + (u16)local[1]), \
                      (s16)(*(u16 *)(a0 + 0xE) + (u16)local[2]), \
                      0, 0); \
        *(s32 *)(a0 + 0x1C) = 0x1E; \
        *(s32 *)(a0 + 0x18) = 0; \
        *(s32 *)(a0 + 0x10) = 0; \
        func_8002D4C8(0x531, 0); \
    }

#define DEFINE_func_80132DC4() \
    extern s32 VectorNormalSS(void *a0, void *a1); \
    void func_80132DC4(s32 a0, s32 a1, s32 a2) { \
        s16 in[3]; \
        s16 out[4]; \
        in[0] = (u16)*(u16 *)(a1 + 0x0) - *(u16 *)(a0 + 0x6); \
        in[1] = (u16)*(u16 *)(a1 + 0x2) - *(u16 *)(a0 + 0xA); \
        in[2] = (u16)*(u16 *)(a1 + 0x4) - *(u16 *)(a0 + 0xE); \
        VectorNormalSS(&in[0], &out[0]); \
        *(s32 *)(a0 + 0x10) = out[0] * a2; \
        *(s32 *)(a0 + 0x14) = out[1] * a2; \
        *(s32 *)(a0 + 0x18) = out[2] * a2; \
    }

#define DEFINE_func_80139220() \
    extern void func_80139DC8(void); \
    extern void func_801392C8(void *a0); \
    s32 func_80139220(s32 a0) { \
        s32 v1; \
        *(s16 *)(a0 + 0x14) = 0; \
        *(s16 *)(a0 + 0x12) = (*(u16 *)(a0 + 0x12) + 1) % (*(s16 *)(a0 + 0x2E) + 1); \
        func_80139DC8(); \
        v1 = *(u16 *)(a0 + 0x12) - *(u16 *)(a0 + 0x16); \
        if (v1 != -1) { \
            if (v1 < *(s16 *)(a0 + 0x2E)) { \
                return 0; \
            } \
        } \
        func_801392C8((void *)a0); \
        return 1; \
    }

#define DEFINE_func_8017869C() \
    extern void func_80178744(s32 a0, s32 a1); \
    void func_8017869C(s32 a0) { \
        s32 v1; \
        s32 a1; \
        if (*(s16 *)(a0 + 0xAA) == 0) { \
            return; \
        } \
        *(s16 *)(a0 + 0xAA) = *(s16 *)(a0 + 0xAA) - 1; \
        v1 = *(s16 *)(a0 + 0xAA); \
        if (v1 == 0) { \
            a1 = 0x1000; \
            if (*(u16 *)(a0 + 0x5E) == 0x1E) { \
                *(s16 *)(a0 + 0x5E) = 0; \
            } \
        } else if (v1 >= 0xF1) { \
            a1 = 0x1000 - (0x100 - v1) * 0x90; \
        } else { \
            if (v1 < 0x10) { \
                a1 = 0x1000 - v1 * 0x90; \
            } else { \
                a1 = 0x700; \
            } \
        } \
        func_80178744(a0, a1); \
    }

#define DEFINE_func_80146608() \
    extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8); \
    extern s32 D_8011F9D0; \
    s32 func_80146608(s32 a0, s32 a1, s32 a2, s32 a3, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13) { \
        u8 *p; \
        u8 *end; \
        s32 cnt; \
        cnt = 0; \
        p = (u8 *)&D_8011F9D0; \
        end = p + 0x820; \
        while (p < end) { \
            if (*(u16 *)p == (a0 & 0xFFFF)) { \
                cnt++; \
            } \
            p += 0x68; \
        } \
        if ((u32)cnt >= (u32)arg12) { \
            return 0; \
        } \
        func_801466F0(a0 & 0xFFFF, a1, (s16)a2, (s16)a3, arg9, arg10, arg11, arg13); \
    }

#define DEFINE_func_80137840() \
    extern void func_80139634(void *); \
    extern void func_80139DC8(void); \
    void func_80137840(s32 a0) { \
        s32 s0 = a0; \
        *(u8 *)(s0 + 0xC) = 1; \
        *(u8 *)(s0 + 0x23) = 1; \
        *(s16 *)(s0 + 0x1A) = 1; \
        *(s16 *)(s0 + 0x2A) = 0x1000; \
        *(s16 *)(s0 + 0x28) = 0x1000; \
        *(s16 *)(s0 + 0x2C) = 0x24; \
        *(s16 *)(s0 + 0x2E) = 3; \
        *(s16 *)(s0 + 0x4) = 0; \
        *(s16 *)(s0 + 0x6) = 0; \
        *(s16 *)(s0 + 0x1C) = 0; \
        *(s16 *)(s0 + 0x10) = 0; \
        *(s16 *)(s0 + 0x14) = 0; \
        *(s16 *)(s0 + 0x12) = 0; \
        *(s16 *)(s0 + 0x16) = 0; \
        *(s16 *)(s0 + 0x30) = 0; \
        *(s16 *)(s0 + 0x32) = 0; \
        *(s16 *)(s0 + 0x34) = 0; \
        *(s16 *)(s0 + 0x36) = 0; \
        *(u8 *)(s0 + 0x22) = 0; \
        *(u8 *)(s0 + 0x20) = 0; \
        *(s32 *)(s0 + 0x40) = 0; \
        *(s8 *)(s0 + 0x1F) = -1; \
        *(s16 *)(s0 + 0x44) = 0; \
        *(s16 *)(s0 + 0x46) = 0; \
        *(s16 *)(s0 + 0x48) = 0; \
        *(s16 *)(s0 + 0x4A) = 0; \
        func_80139634((void *)s0); \
        *(u8 *)(s0 + 0xD) = 0; \
        func_80139DC8(); \
    }

#define DEFINE_func_80139F0C() \
    extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80139B18(s32 a0); \
    extern s32 D_80127524; \
    void func_80139F0C(s32 a0) { \
        s32 s0 = a0; \
        s32 a2; \
        if (D_80127524 != s0 && (*(s32 *)(s0 + 8) & 0x2000) == 0) { \
            *(s16 *)(s0 + 4) = 4; \
            return; \
        } \
        if (*(s32 *)(s0 + 8) & 0x4000) { \
            a2 = 0x70; \
        } else { \
            a2 = 0x60; \
        } \
        if (func_80138DB8(s0, 0, a2) != 0) { \
            s32 v1; \
            *(s16 *)(s0 + 4) = 2; \
            v1 = *(s32 *)(s0 + 8); \
            if ((v1 & 0x20000) == 0) { \
                *(s32 *)(s0 + 8) = v1 & ~0x20; \
            } \
            func_8002D4C8(0x88D, 0); \
        } \
        func_80139B18(s0); \
    }

#define DEFINE_func_80159070() \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_80110C94[]; \
    extern u8 D_80110CD4[]; \
    void func_80159070(void *a0) { \
        s32 obj; \
        s32 r; \
        s32 v; \
        u8 *tbl; \
        obj = *(s32 *)((u8 *)a0 + 0x20); \
        *(u16 *)(obj + 0x12) = (*(u16 *)(obj + 0x12) + 0x16) & 0xFFF; \
        r = func_801399F0(*(s32 *)((u8 *)a0 + 0x198)); \
        *(s16 *)((u8 *)a0 + 0x244) = r; \
        if ((s16)r != 0) { \
            func_80139914(*(s32 *)((u8 *)a0 + 0x198)); \
            v = *(s16 *)((u8 *)a0 + 0x244); \
            *(s32 *)((u8 *)a0 + 0x198) = 0; \
            switch (v) { \
            default: \
            case 1: \
                tbl = D_80110C94; \
                break; \
            case 2: \
                tbl = D_80110CD4; \
                break; \
            } \
            *(s32 *)((u8 *)a0 + 0x198) = func_8013767C((s32)tbl); \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_801638A0() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80135004(s32 a0, void *a1, s32 a2); \
    extern void func_80015954(s32 a0, s32 a1); \
    extern s16 D_801152AA; \
    extern void *memcpy(void *dst, void *src, s32 n); \
    s32 func_801638A0(u8 *a0, s32 a1) { \
        u8 buf[8]; \
        s16 d; \
        s32 p; \
        __builtin_memcpy(buf, a0 + 0x44, 8); \
        p = (s32)(a0 + 4); \
        func_80015978(p, (s32 *)a1); \
        if (func_80135004(1, buf, a1) != 0) { \
            func_80015954(a1, p); \
            d = D_801152AA; \
            if (d >= -0x578) { \
                return 0x8000; \
            } \
            if (d >= -0xBCB) { \
                return 0x4000; \
            } \
            return 0x2000; \
        } \
        return 0; \
    }

#define DEFINE_func_80139FE8() \
    extern s32 func_8001B22C(void *a0); \
    extern void func_8001931C(void); \
    extern void func_80139788(void); \
    extern void func_80139A8C(s32 a0); \
    extern void func_80139B18(s32 a0); \
    void func_80139FE8(void *a0) { \
        s32 v1; \
        s32 a0v; \
        v1 = func_8001B22C(a0); \
        if (v1 == 2 || v1 == 4) { \
            *(s16 *)((u8 *)a0 + 4) = 2; \
        } else if (v1 == 0) { \
            a0v = *(s32 *)((u8 *)a0 + 8); \
            if (a0v & 1) { \
                func_8001931C(); \
            } else { \
                *(s32 *)((u8 *)a0 + 8) = (a0v & 0xFFFEFFFF) | 0x20020; \
                func_80139788(); \
            } \
            *(s16 *)((u8 *)a0 + 4) = 2; \
        } else { \
            func_80139A8C((s32)a0); \
            if (*(s32 *)((u8 *)a0 + 8) & 0x20) { \
                *(s16 *)((u8 *)a0 + 4) = 2; \
            } \
        } \
        func_80139B18((s32)a0); \
    }

#define DEFINE_func_8015E288() \
    extern u8 D_800D5098[]; \
    extern u8 D_800D5060[]; \
    extern s32 func_80161208(); \
    extern s32 func_8014A850(s32 a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_8015E40C(s32 a0); \
    extern void func_8015E588(void); \
    extern void func_8015E4B0(s32 a0); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80146CA0(void *a0); \
    extern void func_80146C98(s32 *a0, s16 a1); \
    void func_8015E288(s32 a0) { \
        if (func_80161208() != 0) { \
            return; \
        } \
        if (func_8014A850(a0) != 0) { \
            func_80154274((s32 *)a0, (s32)D_800D5098); \
            func_8015E40C(a0); \
            ((void (*)(s32))func_8015E588)(a0); \
            func_8015E4B0(a0); \
            func_80146994(5, a0, 0xB, 0); \
            func_80146CA0((void *)a0); \
            return; \
        } \
        if (*(u16 *)(a0 + 0xB8) & 0x8000) { \
            func_80154274((s32 *)a0, (s32)D_800D5060); \
            func_80146C98((s32 *)a0, 3); \
        } \
    }

#define DEFINE_func_80169E44() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80146C3C(void); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80169E44(s32 a0) { \
        s32 r; \
        s32 p; \
        if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
            return; \
        } \
        r = *(s32 *)(a0 + 0x1C); \
        *(s32 *)(a0 + 0x1C) = r + 1; \
        if (r < 3) { \
            p = func_80146A6C(9, (void *)a0, *(s16 *)(a0 + 0x6), \
                              *(s16 *)(a0 + 0xA), \
                              *(s16 *)(a0 + 0xE), \
                              *(s32 *)(a0 + 0x1C) & 1, 0); \
            if (p != 0) { \
                *(s16 *)(p + 0x12) = *(u16 *)(a0 + 0x12); \
                *(s16 *)(p + 0x16) = *(u16 *)(a0 + 0x16); \
                *(s16 *)(p + 0x1A) = *(u16 *)(a0 + 0x1A); \
            } \
        } \
    }

#define DEFINE_func_80149290() \
    extern void func_80149350(s32 arg0); \
    void func_80149290(s32 a0) { \
        volatile s32 a; \
        volatile s32 b; \
        volatile s32 c; \
        a = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48); \
        b = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C); \
        c = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C); \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = *(s16 *)(a0 + 6); \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = *(s16 *)(a0 + 0xA); \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = *(s16 *)(a0 + 0xE); \
        func_80149350(a0); \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = a; \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = b; \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = c; \
    }

#define DEFINE_func_80157EA4() \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern s32 func_80157F64(s32 *a0); \
    extern int func_80155FF8(int arg, int a1); \
    extern s32 func_80156600(void *a0); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80157EA4(void *a0) { \
        s32 *v1; \
        *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2; \
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
            func_801599A4(a0); \
            func_80159B3C(a0); \
            return; \
        } \
        if (func_80157F64((s32 *)a0) != 0) { \
            return; \
        } \
        func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA)); \
        v1 = (s32 *)func_80156600(a0); \
        if (v1 == 0) { \
            return; \
        } \
        if (*(s16 *)((u8 *)a0 + 0x244) != 0) { \
            return; \
        } \
        *(s16 *)((u8 *)a0 + 0x244) = 1; \
        func_80146A6C(0x54, a0, *(s16 *)v1, *(s16 *)((u8 *)v1 + 2), *(s16 *)((u8 *)v1 + 4), 0, 0); \
    }

#define DEFINE_func_80154ED8() \
    extern s16 D_80078E96; \
    extern u8 D_800D8D10[]; \
    extern s16 D_80078E9E; \
    extern u16 D_80078EA6; \
    extern void func_801550FC(s32 a0); \
    void func_80154ED8(s32 a0, s32 a1) { \
        *(s32 *)(a0 + 0xC8) = a1; \
        if (D_80078E96 & 0x8000) { \
            *(s32 *)(a0 + 0xC8) = a1 | 0x1000000; \
            func_801550FC((s32)D_800D8D10); \
            return; \
        } \
        if (D_80078E9E >= 0x10) { \
            if (*(s16 *)&D_80078EA6 >= 0x10) { \
                goto and_path; \
            } \
        } \
        if ((*(s32 *)(a0 + 0x44) & 0xC0) != 0) { \
            goto and_path; \
        } \
        *(s32 *)(a0 + 0xC8) = a1 | 0x1000000; \
        func_801550FC(0x40000002); \
        return; \
    and_path: \
        *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) & 0xC0FFFFFF; \
        func_801550FC(a1); \
    }

#define DEFINE_func_80158D60() \
    extern u16 func_801487F4(s32 *a0); \
    extern s32 func_80159434(s32 a0, s32 a1); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80158D60(s32 a0) { \
        s32 count; \
        s32 i; \
        s32 arg; \
        arg = 0x4C000; \
        count = 1; \
        if (func_801487F4((s32 *)a0) & 0xF0) { \
            count = 4; \
        } \
        for (i = count; i > 0; i--) { \
            func_80159434(a0, arg); \
            if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) < 0xC00) { \
                func_80147324(0x454); \
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00; \
                *(s32 *)(a0 + 0x238) = 0xFFEA0000; \
                func_80146CA0((void *)a0); \
                i = 0; \
            } \
        } \
    }

#define DEFINE_func_80139B18() \
    extern s16 D_8012752C; \
    extern s32 func_80014E80(s32 a0, s32 a1); \
    extern void func_8001931C(void); \
    void func_80139B18(s32 a0) { \
        s32 m; \
        s32 p; \
        if (*(s32 *)(a0 + 8) & 0x6000) { \
            return; \
        } \
        if ((s16)func_80014E80(0, 0x10) == 0) { \
            return; \
        } \
        m = *(s32 *)(a0 + 8); \
        if (m & 0x10000) { \
            *(s32 *)(a0 + 8) = m & 0xFFFEFFFF; \
            func_8001931C(); \
            D_8012752C = 0; \
        } \
        if (*(s32 *)(a0 + 8) & 0x2000) { \
            *(s16 *)(a0 + 4) = 0xD; \
            return; \
        } \
        *(s16 *)(a0 + 4) = 0xC; \
        p = *(s32 *)(a0 + 0x40); \
        *(s32 *)(a0 + 8) = *(s32 *)(a0 + 8) & 0xFFFFEFFF; \
        if (p == 0) { \
            return; \
        } \
        if (*(u16 *)(a0 + 0x18) == 0) { \
            return; \
        } \
        *(s16 *)p = 3; \
    }

#define DEFINE_func_80164864() \
    extern void func_80164ACC(); \
    extern void func_80146CA0(void *a0); \
    void func_80164864(void *a0) { \
        s32 s = (s32)a0; \
        s32 p = *(s32 *)(s + 0x20); \
        s32 sum; \
        s32 v; \
        s32 w; \
        s32 limit; \
        sum = *(u16 *)(s + 0x60) + *(u16 *)(s + 0x62); \
        *(u16 *)(s + 0x60) = sum; \
        *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) + sum; \
        if (*(s32 *)(s + 0x50) == 0) { \
            limit = 0x4000; \
            v = *(u16 *)(p + 0x1C) + 0x100; \
            w = *(u16 *)(p + 0x12) + 0x71; \
            *(u16 *)(p + 0x1C) = v; \
            *(u16 *)(p + 0x18) = v; \
            *(u16 *)(p + 0x12) = w; \
            func_80164ACC(); \
        } else { \
            limit = 0x2000; \
            v = *(u16 *)(p + 0x1C) + 0x200; \
            w = *(u16 *)(p + 0x12) - 0x71; \
            *(u16 *)(p + 0x1C) = v; \
            *(u16 *)(p + 0x18) = v; \
            *(u16 *)(p + 0x12) = w; \
        } \
        if (limit < *(s16 *)(p + 0x1A)) { \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_80162FF4() \
    extern void func_80162F60(s32 arg0, s32 arg1); \
    extern void func_80162F80(s32 arg0, s32 arg1); \
    extern void func_80162FA0(s32 arg0, s32 arg1); \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    extern void func_80146D30(s32 a0); \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 sp[16]; \
        s32 s2 = a0; \
        s32 s0 = a2; \
        s32 s3 = a3; \
        s32 s1 = *(s32 *)(s2 + 0x20); \
        s32 *q; \
        func_80162F60(a0, a1); \
        func_80162F80(s2, s0); \
        func_80162FA0(s2, s3); \
        q = &sp[8]; \
        func_80013F3C((s32)q); \
        func_800126C4((s32)q, *(s16 *)(s1 + 0x10)); \
        func_80012558((s32)q, *(s16 *)(s1 + 0x12)); \
        func_800123F0((s32)q, *(s16 *)(s1 + 0x14)); \
        func_800484EC((s32)q, s2 + 0x24, (s32)&sp[4]); \
        D_80127090 = sp[4]; \
        D_80127094 = sp[5]; \
        D_80127098 = sp[6]; \
        func_80146D30(s2); \
    }

#define DEFINE_func_801630C4() \
    extern void func_80162F60(s32 arg0, s32 arg1); \
    extern void func_80162F80(s32 arg0, s32 arg1); \
    extern void func_80162FA0(s32 arg0, s32 arg1); \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    extern void func_80146D30(s32 a0); \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_801630C4(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 sp[16]; \
        s32 s2 = a0; \
        s32 s0 = a2; \
        s32 s3 = a3; \
        s32 s1 = *(s32 *)(s2 + 0x20); \
        s32 *q; \
        func_80162F60(a0, a1); \
        func_80162F80(s2, s0); \
        func_80162FA0(s2, s3); \
        q = &sp[8]; \
        func_80013F3C((s32)q); \
        func_80012558((s32)q, *(s16 *)(s1 + 0x12)); \
        func_800126C4((s32)q, *(s16 *)(s1 + 0x10)); \
        func_800123F0((s32)q, *(s16 *)(s1 + 0x14)); \
        func_800484EC((s32)q, s2 + 0x24, (s32)&sp[4]); \
        D_80127090 = sp[4]; \
        D_80127094 = sp[5]; \
        D_80127098 = sp[6]; \
        func_80146D30(s2); \
    }

#define DEFINE_func_8016D778() \
    extern void func_80146C3C(void); \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern s32 D_80126B9C; \
    void func_8016D778(s32 a0) { \
        s32 s0 = a0; \
        s32 p; \
        s16 sp[6]; \
        if (*(s16 *)(s0 + 0x28) == *(s16 *)(*(s32 *)(s0 + 0x30) + 0x36)) { \
            if ((D_80126B9C & 0x20) != 0) { \
                goto main; \
            } \
        } \
        ((void (*)(s32))func_80146C3C)(s0); \
        return; \
    main: \
        p = *(s32 *)(s0 + 0x20); \
        *(u16 *)(p + 0x18) = *(u16 *)(p + 0x18) ^ 0x400; \
        *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) ^ 0x200; \
        sp[0] = *(u16 *)(s0 + 0x12); \
        sp[1] = *(u16 *)(s0 + 0x16); \
        sp[2] = *(u16 *)(s0 + 0x1A); \
        func_800D20C0(&sp[0], &sp[4], 6); \
        *(u16 *)(s0 + 6) = sp[0]; \
        *(u16 *)(s0 + 0xA) = sp[1]; \
        *(u16 *)(s0 + 0xE) = sp[2]; \
    }

#define DEFINE_func_80164ACC() \
    extern u8 D_801202A0[]; \
    extern u8 D_80126720[]; \
    extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_8014C278(s32 a0, s32 a1, s32 a2); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3); \
    void func_80164ACC(s32 a0) { \
        u8 *p; \
        s16 buf[4]; \
        p = D_801202A0; \
        if (p < p + 0x6480) { \
            do { \
                if (func_8014C308(a0, (s32)p, 0xB, 2) != 0) { \
                    if (func_8014C278(a0, (s32)p, 0x50) != 0) { \
                        func_80015978((s32)(p + 4), (s32 *)buf); \
                        buf[3] = 0; \
                        func_8014C3A4((void *)a0, (s32)p, 0xB, (s32)buf); \
                        *(s16 *)(p + 0x60) = (s16)(*(s16 *)(p + 0x60)) / 2; \
                    } \
                } \
                p += 0x10C; \
            } while (p < D_80126720); \
        } \
    }

#define DEFINE_func_8012FB54() \
    extern void func_801319E0(s32 a0); \
    extern s32 func_80143B6C(s32 a0, s32 a1); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FB54(s32 a0) { \
        s32 s0 = a0; \
        s32 v1; \
        s32 p; \
        if ((*(s32 *)(s0 + 0xB4) & 0x10000) != 0) { \
            *(s32 *)(s0 + 0x4) = *(s32 *)(s0 + 0x4) + *(s32 *)(s0 + 0x10); \
            *(s32 *)(s0 + 0x8) = *(s32 *)(s0 + 0x8) + *(s32 *)(s0 + 0x14); \
            *(s32 *)(s0 + 0xC) = *(s32 *)(s0 + 0xC) + *(s32 *)(s0 + 0x18); \
            v1 = *(s32 *)(s0 + 0x1C) - 1; \
            *(s32 *)(s0 + 0x1C) = v1; \
            if (v1 == 0) { \
                func_801319E0(s0); \
            } else { \
                p = func_80143B6C(s0, 1); \
                if (p != 0) { \
                    *(s16 *)(p + 0xA) = *(u16 *)(p + 0xA) + *(u16 *)(s0 + 0xAC); \
                } \
                if (*(s32 *)(s0 + 0x1C) == 0x13) { \
                    func_8002D4C8(0x8F2, 0); \
                } \
            } \
        } \
        func_80131CA8(s0, 0x36); \
    }

#define DEFINE_func_80156A88() \
    extern void func_80147324(s32 a0); \
    extern s32 func_8014CA88(s32 *a0, s32 a1); \
    extern s32 func_8014CA14(s32 a0, s32 a1); \
    extern s32 D_801150E0[]; \
    extern s32 D_801151E0[]; \
    void func_80156A88(s32 a0, s32 a1) { \
        s32 v1 = *(s32 *)(a1 + 0xC); \
        s32 s3 = v1 & 0xF0FFFFFF; \
        s32 s5, s4; \
        s32 *s0; \
        s32 *s1; \
        u32 s2; \
        if (v1 == 0x80000000) { \
            return; \
        } \
        s2 = 0; \
        s5 = v1 & 0x1000000; \
        s4 = v1 & 0x2000000; \
        s0 = D_801150E0; \
        s1 = D_801151E0; \
        do { \
            if (*s1 & 1) { \
                if (s5 != 0) { \
                    func_80147324(s3 & 0xFFFF); \
                } else if (s4 != 0) { \
                    func_8014CA88((s32 *)*s0, s3); \
                } else { \
                    func_8014CA14(*s0, s3); \
                } \
            } \
            s0++; \
            s2++; \
            s1++; \
        } while (s2 < 3); \
    }

#define DEFINE_func_80176FF4() \
    extern u32 func_801783D0(s32 a0, s32 a1); \
    extern void func_801778A8(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u16 D_8011F82C; \
    extern u16 D_8011F82A; \
    void func_80176FF4(s32 a0) { \
        s32 v0; \
        a0 += 0x50; \
        func_801778A8(a0, (s16)func_801783D0(D_8011F82C, 4), 3, 0xFF); \
        a0 += 0x3C; \
        func_801778A8(a0, (s16)func_801783D0(D_8011F82A, 4), 3, 0xFF); \
        a0 += 0x3C; \
        *(s16 *)(a0 + 0xC) = (u32)(D_8011F82C * 10355) >> 15; \
        a0 += 0x14; \
        v0 = ((s32)(D_8011F82A * 10355) << 1) >> 16; \
        *(s16 *)(a0 + 0xC) = v0; \
        *(s16 *)(a0 + 0x20) = v0 + 2; \
    }

#define DEFINE_func_80177340() \
    extern u32 func_801783D0(s32 a0, s32 a1); \
    extern void func_801778A8(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u16 D_8011F830; \
    extern u16 D_8011F82E; \
    void func_80177340(s32 a0) { \
        s32 v0; \
        a0 += 0x50; \
        func_801778A8(a0, (s16)func_801783D0(D_8011F830, 4), 3, 0xFF); \
        a0 += 0x3C; \
        func_801778A8(a0, (s16)func_801783D0(D_8011F82E, 4), 3, 0xFF); \
        a0 += 0x3C; \
        *(s16 *)(a0 + 0xC) = (u32)(D_8011F830 * 10355) >> 15; \
        a0 += 0x14; \
        v0 = ((s32)(D_8011F82E * 10355) << 1) >> 16; \
        *(s16 *)(a0 + 0xC) = v0; \
        *(s16 *)(a0 + 0x20) = v0 + 2; \
    }

#define DEFINE_func_80147628() \
    extern void func_80013F3C(s32 a0); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    void func_80147628(s32 a0) { \
        s32 s2 = *(s32 *)(a0 + 0x20); \
        s32 s1 = s2 + 0x34; \
        func_80013F3C(s1); \
        func_80012558(s1, *(s16 *)(a0 + 0x102)); \
        func_800126C4(s1, *(s16 *)(a0 + 0x100)); \
        func_800123F0(s1, *(s16 *)(a0 + 0x104)); \
        if (*(u16 *)(a0 + 0x136) & 2) { \
            func_80012558(s1, *(s16 *)(a0 + 0x132)); \
        } else { \
            func_80012558(s1, *(s16 *)(s2 + 0x12)); \
        } \
        if (*(u16 *)(a0 + 0x136) & 1) { \
            func_800126C4(s2 + 0x34, *(s16 *)(a0 + 0x130)); \
        } else { \
            func_800126C4(s2 + 0x34, *(s16 *)(s2 + 0x10)); \
        } \
        if (*(u16 *)(a0 + 0x136) & 4) { \
            func_800123F0(s2 + 0x34, *(s16 *)(a0 + 0x134)); \
        } else { \
            func_800123F0(s2 + 0x34, *(s16 *)(s2 + 0x14)); \
        } \
    }

#define DEFINE_func_80158344() \
    extern s32 func_80161208(); \
    extern s32 func_801585AC(s32 *a0); \
    extern void func_80156648(s32 *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80147324(s32 a0); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern int func_80155FF8(int arg, int a1); \
    extern u8 D_800D52E8[]; \
    void func_80158344(s32 *a0) { \
        volatile s32 spill[4]; \
        *(s32 *)((s32)a0 + 0x44) |= 2; \
        if (func_80161208() == 0) { \
            if (func_801585AC(a0) != 0) { \
                func_80156648(a0); \
                *(s8 *)((s32)a0 + 0x1AA) = 0x11; \
                func_80154274(a0, (s32)D_800D52E8); \
                *(s32 *)((s32)a0 + 0x234) = 0; \
                func_80147324(0x455); \
                func_80146994(4, (s32)a0, 9, 0); \
                func_80146994(5, (s32)a0, 0xD, 0); \
                func_80146E90(a0, 0x12C); \
                func_80146CA0(a0); \
            } \
            if (*(u16 *)((s32)a0 + 0xB8) & 0x8000) { \
                func_801599A4(a0); \
                func_80159B3C(a0); \
            } else { \
                func_80155FF8((int)a0, *(u8 *)((s32)a0 + 0x1AA)); \
            } \
        } \
    }

#define DEFINE_func_8012CEB0() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    s32 func_8012CEB0(s32 a0, s32 a1, s32 a2) { \
        s32 sp10[2]; \
        s32 r; \
        s32 v; \
        s32 t; \
        if ((a2 & 1) != 0) { \
            s32 u; \
            r = func_80133784((s16)a2, (void *)a0, a1); \
            u = *(u8 *)(a1 + 6); \
            r |= u; \
            if (u == 2 || u == 0x1B) { \
                r |= 0x1000; \
            } \
            return r; \
        } else { \
            r = func_80133784(0, (void *)a0, a1); \
            if (r == 0) { \
                return 0; \
            } \
            v = func_80133784(2, (void *)a1, (s32)sp10); \
            if ((v & 0x6000) == 0) { \
                return 0; \
            } \
            v &= 0xFFFF7FFF; \
            v |= (r & 0x8000); \
            t = *(u8 *)(a1 + 6); \
            *(s16 *)(a1 + 2) = *(u16 *)((s32)sp10 + 2); \
            v |= t; \
            if (t == 2 || t == 0x1B) { \
                v |= 0x1000; \
            } \
            return v; \
        } \
    }

#define DEFINE_func_801580B4() \
    extern u8 D_800D524C[]; \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80161418(void *a0); \
    extern void func_80156648(s32 *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern int func_80155FF8(int arg, int a1); \
    void func_801580B4(s32 a0) { \
        s32 reserved[4]; \
        (void)reserved; \
        *(s32 *)(a0 + 0x44) |= 2; \
        if ((*(u16 *)(a0 + 0xB8) & 0x4000) != 0) { \
            func_801477E8((s32 *)a0, 0xFFF40000); \
            *(s32 *)(a0 + 0x234) += 1; \
        } \
        if (*(s32 *)(a0 + 0x234) != 0) { \
            func_80148038(a0, 0x10000); \
            func_80147460(a0); \
        } \
        func_80147AD4(a0, 0, 0, 0); \
        func_801473EC((s32 *)a0); \
        { \
            register s32 ret __asm__("$2"); \
            func_80161418((void *)a0); \
            __asm__ __volatile__("" : "=r"(ret)); \
            if (ret != 0) { \
                return; \
            } \
        } \
        if (*(u16 *)(a0 + 0xB8) == 0x8000) { \
            func_80156648((s32 *)a0); \
            *(s8 *)(a0 + 0x1AA) = 0xF; \
            func_80154274((s32 *)a0, (s32)D_800D524C); \
            func_80147324(0x455); \
            func_80146CA0((void *)a0); \
        } else { \
            func_80155FF8(a0, *(u8 *)(a0 + 0x1AA)); \
        } \
    }

#define DEFINE_func_80157BC8() \
    extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_8014ED28(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_8016158C(void *a0); \
    extern void func_80161D20(s32 a0, s32 a1); \
    extern void func_8014C010(s32 a0, s32 a1); \
    extern void func_8016706C(s32 a0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8015BE04(s32 *a0); \
    extern s32 func_801725A4(u8 *a0); \
    void func_80157BC8(s32 a0) { \
        s32 s1; \
        func_80147AD4(a0, 0, 0, 0x10000); \
        func_801473EC((s32 *)a0); \
        func_80148038(a0, 0x1A000); \
        func_80147460(a0); \
        { \
            register s32 ret __asm__("$2"); \
            func_8014ED28(a0); \
            __asm__ __volatile__("" : "=r"(ret)); \
            if (ret != 0) { \
                func_80146D90(a0); \
            } \
        } \
        { \
            register s32 r __asm__("$2"); \
            func_8016158C((void *)a0); \
            __asm__ __volatile__("" : "=r"(r)); \
            s1 = r; \
        } \
        if ((s1 & 5) != 0) { \
            func_80161D20(a0, *(u16 *)(a0 + 0x16E)); \
            func_8014C010(a0, 1); \
            func_8016706C(4); \
            func_8016706C(5); \
            func_801599A4((void *)a0); \
            func_80159B3C((void *)a0); \
        } \
        if (s1 != 0) { \
            return; \
        } \
        if (*(s32 *)(a0 + 0x34) > 0) { \
            func_801599A4((void *)a0); \
            func_80146D90(a0); \
            func_8015BE04((s32 *)a0); \
        } else { \
            func_801725A4((u8 *)a0); \
        } \
    }

#define DEFINE_func_80163950() \
    extern u8 D_801202A0[]; \
    extern u8 D_80126720[]; \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    extern void func_80015954(s32 a0, s32 a1); \
    s32 func_80163950(s32 a0) { \
        s32 sp10[2]; \
        s32 sp18[2]; \
        u8 *p; \
        func_80015978(a0 + 4, sp10); \
        func_80015978(a0 + 4, sp18); \
        *(s16 *)((s32)sp10 + 0x2) = *(u16 *)((s32)sp10 + 0x2) - 0x20; \
        *(s16 *)((s32)sp18 + 0x2) = *(u16 *)((s32)sp18 + 0x2) + 0x8; \
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) { \
            if (*(u16 *)p == 0) continue; \
            if ((*(u16 *)(p + 0x5C) & 0x400) == 0) continue; \
            if (*(s32 *)(p + 0x58) == 0) continue; \
            if (func_80135A4C(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), sp10, (s32)sp18) != 0) { \
                func_80015954((s32)sp18, a0 + 4); \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80149954() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_8012E5CC(s32 a0, s32 a1, s32 a2); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80147364(u16 a0, s32 a1); \
    extern s32 func_800CCF28(s32 a0); \
    extern void func_80146750(void *a0); \
    extern u8 D_80126B5C; \
    extern void *D_8012707C; \
    extern s16 currentLocationId; \
    s32 func_80149954(s32 s0) { \
        s32 sp10[2]; \
        s16 buf[10]; \
        if (*(s32 *)(s0 + 0x44) & 0x404) { \
            return 0; \
        } \
        if ((*(u16 *)(s0 + 0xAA) & 0x90) == 0) { \
            if (currentLocationId == 0x308D) { \
                func_80015978((s32)&D_80126B5C, sp10); \
                func_8012E5CC((s32)sp10, 0x4, 0x8E0); \
                return 0; \
            } \
            func_8002D4C8(0x4, 0x8E0); \
            return 0; \
        } \
        if (*(u16 *)(s0 + 0xAC) & 0x90) { \
            if ((s32)D_8012707C == 0x8E0) { \
                D_8012707C = 0; \
            } else { \
                func_80147364(0x8E0, 0); \
            } \
        } \
        func_800CCF28(s0); \
        *(s16 *)((s32)buf + 0x0) = 0x12; \
        *(s32 *)((s32)buf + 0x8) = s0; \
        *(s16 *)((s32)buf + 0x2) = 0; \
        *(s16 *)((s32)buf + 0x4) = -0x1E; \
        *(s16 *)((s32)buf + 0x6) = 0; \
        *(s32 *)((s32)buf + 0xC) = 0; \
        *(s32 *)((s32)buf + 0x10) = 0; \
        func_80146750(buf); \
        return 1; \
    }

#define DEFINE_func_801564B0() \
    extern s32 rand(void); \
    extern s32 func_8002A1B4(void); \
    extern s32 func_8002A400(void); \
    extern s32 func_8002A670(void); \
    extern s32 func_8002A8E0(void); \
    extern u8 D_80078E78[]; \
    s32 func_801564B0(s32 a0) { \
        s32 s0 = (s32)D_80078E78; \
        s32 v1; \
        if (*(s32 *)(a0 + 0x44) & 0x200) { \
            if (rand() & 0x1) { \
                return 0x8000; \
            } \
        } \
        if (func_8002A1B4() || func_8002A400() || func_8002A670() || func_8002A8E0()) { \
            if ((rand() & 0x3) == 0) { \
                return 0x8000; \
            } \
        } \
        if ((rand() & 0x3) != 0) { \
            return 0; \
        } \
        v1 = rand() % 160 & 0xFFFF; \
        if ((u32)v1 < 0x51) { \
            return 0; \
        } \
        if (v1 >= *(s16 *)(s0 + 0x2E)) { \
            /* LOAD-BEARING: empty volatile asm blocks gcc's noce store-flag \
               if-conversion (it would fold "cond ? 0x8000 : 0" to (slt)<<15); \
               the original kept the slt+branch form. */ \
            __asm__ __volatile__(""); \
            return 0; \
        } \
        return 0x8000; \
    }

#define DEFINE_func_8016D4DC() \
    extern s32 D_80126B58; \
    extern void func_8016C83C(s32 a0); \
    extern s32 VectorNormalSS(void *a0, void *a1); \
    extern short func_8016CF04(); \
    extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4); \
    extern void func_800D22E4(s32 a0); \
    void func_8016D4DC(s32 a0) { \
        s16 d[20]; \
        s32 a1 = *(s32 *)(a0 + 0x34); \
        s32 dist; \
        s32 idx; \
        if (*(u16 *)a1 != 1) { \
            *(s16 *)(a0 + 2) = 3; \
            *(s32 *)(a0 + 0x34) = (s32)&D_80126B58; \
            *(s32 *)(a0 + 0x1C) = 0x40; \
            func_8016C83C(a0); \
            return; \
        } \
        d[0] = *(u16 *)(a1 + 6) - *(u16 *)(a0 + 6); \
        d[1] = *(u16 *)(a1 + 0xA) - *(u16 *)(a0 + 0xA); \
        d[2] = *(u16 *)(a1 + 0xE) - *(u16 *)(a0 + 0xE); \
        dist = VectorNormalSS(d, d); \
        if (dist < 0x510) { \
            func_8016CF04(a0, 2); \
            *(s16 *)(a0 + 2) = 4; \
            return; \
        } \
        if (dist < 0x1900) { \
            idx = 6; \
        } else if (dist < 0x6400) { \
            idx = 5; \
        } else { \
            idx = 4; \
        } \
        func_8016C74C(a0, (s32)d, idx, 9, 0x400); \
        func_800D22E4(a0); \
        func_8016CF04(a0, 1); \
    }

#define DEFINE_func_80165E90() \
    extern void func_801484B0(s32 a0, s32 a1); \
    extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2); \
    extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2); \
    extern void func_80148534(s32 a0, s32 a1); \
    extern s32 func_80167AE0(); \
    extern s32 D_80126B9C; \
    extern s32 D_80126B58; \
    extern s32 *D_80126B78; \
    void func_80165E90(void) { \
        s32 s1 = (s32)&D_80126B58; \
        s32 buf1[2]; \
        s32 buf2[2]; \
        s32 v1; \
        if ((D_80126B9C & 0x10000400) == 0x10000000) { \
            v1 = (s32)D_80126B78; \
            if (*(s32 *)(v1 + 0x4) >= 0) { \
                if (*(s32 *)(v1 + 0x20) != 0) { \
                    func_801484B0((s32)buf1, (s32)buf2); \
                    func_80165FA4(s1, (s32)buf1, (s32)buf2); \
                    func_80167DBC(s1, (s32)buf1, (s32)buf2); \
                } \
            } \
        } \
        if ((*(s32 *)(s1 + 0x44) & 0x20020400) == 0x20000000) { \
            v1 = *(s32 *)(s1 + 0x20); \
            if (*(s32 *)(v1 + 0x4) >= 0) { \
                if (*(s32 *)(v1 + 0x20) != 0) { \
                    func_80148534((s32)buf1, (s32)buf2); \
                    func_80165FA4(s1, (s32)buf1, (s32)buf2); \
                    func_80167AE0(s1, (s32)buf1, (s32)buf2); \
                } \
            } \
        } \
    }

#define DEFINE_func_8014B190() \
    extern s32 func_8016F1C4(void); \
    extern u8 D_80078E78[]; \
    extern s16 D_80078E96; \
    extern s16 D_80078EB8; \
    extern u16 D_80078EA6; \
    extern u8 D_80078EC1; \
    void func_8014B190(s32 s0) { \
        s16 *s1 = (s16 *)D_80078E78; \
        s32 v0; \
        *(s16 *)(s0 + 0x68) = 0x1000; \
        *(s16 *)(s0 + 0x6A) = 0x1000; \
        *(s16 *)(s0 + 0x6C) = 0x1000; \
        v0 = *(s32 *)(s0 + 0x44) & -0x201; \
        v0 = v0 & -0x401; \
        *(s32 *)(s0 + 0x44) = v0; \
        v0 = func_8016F1C4(); \
        if (v0) { \
            return; \
        } \
        if (*(u16 *)(s0 + 0x0) == 0x1E) { \
            return; \
        } \
        if (*(u16 *)(s0 + 0x0) == 0x1A) { \
            return; \
        } \
        if ((D_80078E96 & 0x8000) || \
            ((u16)D_80078EB8 < 0xB) || \
            ((s16)D_80078EA6 < 0x10) || \
            (D_80078EC1 == 0x1)) { \
            *(s32 *)(s0 + 0x44) |= 0x200; \
        } \
        if (*(s16 *)((s32)s1 + 0x22) & 0x8000) { \
            *(s16 *)(s0 + 0x68) = 0x555; \
            *(s16 *)(s0 + 0x6A) = 0x555; \
            *(s16 *)(s0 + 0x6C) = 0x555; \
            *(s32 *)(s0 + 0x44) |= 0x400; \
        } \
    }

#define DEFINE_func_8014B5D8() \
    extern s32 func_8016F1C4(void); \
    extern s32 func_80029178(s32 a0); \
    extern void func_8014BC80(s32 a0, s32 a1); \
    extern u8 D_80078E78[]; \
    void func_8014B5D8(s32 s1) { \
        s32 *s0 = (s32 *)D_80078E78; \
        s32 v0; \
        s32 a0; \
        v0 = func_8016F1C4(); \
        if (v0) { \
            return; \
        } \
        if (*(u16 *)(s1 + 0x0) == 0x1E) { \
            return; \
        } \
        if (*(u16 *)(s1 + 0x0) == 0x1A) { \
            return; \
        } \
        if (*(s32 *)(s1 + 0x44) & 0x10) { \
            return; \
        } \
        if (*(s32 *)(s1 + 0x44) & 0x80) { \
            if ((func_80029178(0x1B) & 0xFF) != 0) { \
                a0 = 0x2D8; \
            } else { \
                a0 = 0x5B0; \
            } \
        } else { \
            a0 = 0x16C; \
        } \
        if (*(u8 *)((s32)s0 + 0x49) == 0x12) { \
            a0 = a0 << 1; \
        } \
        v0 = *(s32 *)((s32)s0 + 0x24) - a0; \
        *(s32 *)((s32)s0 + 0x24) = v0; \
        if (v0 < 0) { \
            *(s32 *)((s32)s0 + 0x24) = 0; \
            if (*(s32 *)(s1 + 0x44) & 0x80) { \
                *(s32 *)((s32)s0 + 0x28) = *(s32 *)((s32)s0 + 0x28) + 0xAAA8; \
            } else { \
                *(s32 *)((s32)s0 + 0x28) = *(s32 *)((s32)s0 + 0x28) + 0x1555; \
            } \
            if (*(s16 *)((s32)s0 + 0x2A) < 0x3C) { \
                return; \
            } \
            *(s32 *)((s32)s0 + 0x28) = 0; \
            func_8014BC80(s1, 0x4); \
        } else { \
            *(s32 *)((s32)s0 + 0x28) = 0; \
            *(s8 *)((s32)s0 + 0x43) = 0; \
        } \
    }

#define DEFINE_func_80137BD8() \
    extern void func_801392FC(); \
    extern void func_801397B0(s32 a0); \
    extern void func_80137DD4(s32 a0, u8 *a1, u8 *a2); \
    extern void func_80139680(s32 a0, u8 *a1); \
    extern short D_800B9A02; \
    extern u8 D_800A6518[]; \
    extern s32 D_80127524; \
    extern u16 D_800B99D8; \
    void func_80137BD8(s32 a0) { \
        u8 buf[8]; \
        if ((*(s32 *)(a0 + 8) & 0x1000) != 0) { \
            func_801392FC(a0, *(u8 *)(a0 + 0x1E), \
                          &D_800A6518[(u16)D_800B9A02 * 20]); \
            if (*(u8 *)(a0 + 0x20) != 0) { \
                func_801397B0(a0); \
            } \
        } \
        if (D_80127524 == a0) { \
            if (*(s16 *)(a0 + 4) == 7) { \
                buf[0] = 0x39; \
                buf[1] = 0xFF; \
                buf[2] = 0x71; \
                func_80137DD4(a0, buf, &D_800A6518[(u16)D_800B9A02 * 20]); \
            } else if (*(s16 *)(a0 + 4) == 3) { \
                if ((D_800B99D8 & 4) != 0) { \
                    func_80139680(a0, &D_800A6518[(u16)D_800B9A02 * 20]); \
                } \
            } \
        } \
    }

#define DEFINE_func_8013AA24() \
    extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3); \
    extern void func_8013B204(s32 a0, s32 a1); \
    extern void func_8013AF20(); \
    extern short D_800B9A02; \
    extern s32 D_800A651C; \
    void func_8013AA24(s32 a0, s32 a1) { \
        s32 s2 = a0; \
        s32 s0 = a1; \
        u8 buf[0xE0];          /* spans 0x10 .. 0xF0 */ \
        s16 m00 = *(u16 *)(s0 + 8); \
        s16 m11; \
        *(s16 *)(buf + 0x02) = 0;                       /* 0x12 */ \
        *(s16 *)(buf + 0x04) = 0;                       /* 0x14 */ \
        *(s16 *)(buf + 0x06) = 0;                       /* 0x16 */ \
        *(s16 *)(buf + 0x00) = m00;                     /* 0x10 */ \
        m11 = *(u16 *)(s0 + 0xA); \
        *(s16 *)(buf + 0x0A) = 0;                       /* 0x1A */ \
        *(s16 *)(buf + 0x0C) = 0;                       /* 0x1C */ \
        *(s16 *)(buf + 0x0E) = 0;                       /* 0x1E */ \
        *(s16 *)(buf + 0x10) = 0x1000;                  /* 0x20 */ \
        *(s16 *)(buf + 0x08) = m11;                     /* 0x18 */ \
        *(s32 *)(buf + 0x14) = *(s16 *)(s2 + 0x24);    /* 0x24 */ \
        *(s32 *)(buf + 0x18) = *(s16 *)(s2 + 0x26);    /* 0x28 */ \
        *(s32 *)(buf + 0x1C) = 0;                       /* 0x2C */ \
        { \
            register s32 *p __asm__("$2") = (s32 *)(buf + 0x00); \
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
                "lw $12, 20(%0)\n" \
                "lw $13, 24(%0)\n" \
                "ctc2 $12, $5\n" \
                "lw $14, 28(%0)\n" \
                "ctc2 $13, $6\n" \
                "ctc2 $14, $7\n" \
                : : "r"(p) : "$12", "$13", "$14", "memory"); \
        } \
        func_8013AD38((void *)(s0 + 8), *(s16 *)(s0 + 0xC), buf + 0x20, buf + 0xA0); \
        func_8013B204(s2, s0); \
        func_8013AF20(*(s32 *)((u8 *)&D_800A651C + (u16)D_800B9A02 * 20) + \
                          *(u16 *)(s2 + 0x1A) * 4, \
                      s2 + 0x24, buf + 0x20, buf + 0xA0); \
    }

#define DEFINE_func_8014AA28() \
    extern s32 D_80126B58; \
    extern u8 D_80078EC1; \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern s32 func_80165A20(s32 a0); \
    extern void func_8014AB7C(); \
    extern void func_8014AC10(); \
    void func_8014AA28(void) { \
        s32 base = (s32)&D_80126B58; \
        u16 v1 = *(u16 *)base; \
        s32 s0 = D_80078EC1; \
        if ((u32)(v1 - 0x19) >= 2 && (u32)(v1 - 0x1D) >= 2) { \
            func_801599A4((void *)base); \
            func_80159B3C((void *)base); \
            if (s0 == 0xC || s0 == 0x18 || s0 == 0xA) { \
                func_80165A20(base); \
            } \
        } \
        *(s16 *)(base + 0x1C8) = 0; \
        *(s16 *)(base + 0x1CA) = 0; \
        *(s16 *)(base + 0x1CC) = 0; \
        *(s16 *)(base + 0x1CE) = 0; \
        *(s16 *)(base + 0x1D0) = 0; \
        *(s32 *)(base + 0x1D4) = 0; \
        *(s32 *)(base + 0x1D8) = 0; \
        func_8014AB7C(5); \
        func_8014AB7C(6); \
        func_8014AB7C(7); \
        func_8014AB7C(8); \
        func_8014AB7C(9); \
        func_8014AC10(0x26); \
        func_8014AC10(0x27); \
        func_8014AC10(0x39); \
        func_8014AC10(0x3A); \
        func_8014AB7C(0x10); \
        func_8014AB7C(0x11); \
        func_8014AB7C(0x12); \
        func_8014AB7C(0x13); \
        func_8014AB7C(0x14); \
        func_8014AC10(0x3B); \
        func_8014AC10(0x3C); \
        *(u8 *)(base + 0x223) = 0x10; \
    }

#define DEFINE_func_8015E714() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    extern void func_801553C0(s32 a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015E714(s32 *a0) { \
        s16 sp18[4]; \
        s16 sp20[4]; \
        s32 s0; \
        if (*(s32 *)((s32)a0 + 0x234) == 0) { \
            s0 = *(s32 *)((s32)a0 + 0x18C); \
            if (s0 != 0) { \
                sp18[0] = *(u16 *)((s32)a0 + 0x6); \
                sp18[1] = *(u16 *)((s32)a0 + 0xA) - 0x14; \
                sp18[2] = *(u16 *)((s32)a0 + 0xE); \
                sp20[0] = *(u16 *)(s0 + 0x6); \
                sp20[1] = *(u16 *)(s0 + 0xA); \
                sp20[2] = *(u16 *)(s0 + 0xE); \
                if (func_80133784(0, sp18, (s32)sp20) != 0) { \
                    *(s16 *)(s0 + 0x6) = sp20[0]; \
                    *(s16 *)(s0 + 0xA) = sp20[1]; \
                    *(s16 *)(s0 + 0xE) = sp20[2]; \
                } \
                func_80015978(s0 + 0x4, (s32 *)sp18); \
                sp18[3] = 0; \
                func_8014C4AC(s0, 0x1C, 0, sp18, *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)); \
                *(s32 *)((s32)a0 + 0x18C) = 0; \
            } \
        } \
        func_801553C0((s32)a0); \
        func_80155440(a0); \
        *(s32 *)((s32)a0 + 0x44) = *(s32 *)((s32)a0 + 0x44) & -3; \
        func_80154A74((s32)a0, 0x11); \
        *(s32 *)((s32)a0 + 0x44) = *(s32 *)((s32)a0 + 0x44) & -3; \
    }

#define DEFINE_func_8016D848() \
    extern void func_80146C3C(void); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_800D20C0(); \
    void func_8016D848(s32 *a0) { \
        s16 sp20[4]; \
        s16 sp28[4]; \
        s32 s2; \
        s32 cnt; \
        s16 i; \
        s32 p; \
        cnt = *(s32 *)((s32)a0 + 0x1C) - 1; \
        *(s32 *)((s32)a0 + 0x1C) = cnt; \
        if (cnt == 0) { \
            func_80146C3C(); \
            return; \
        } \
        if (cnt < 4) { \
            s2 = -0xC00; \
        } else { \
            s2 = 0x800; \
            i = 0; \
            do { \
                func_80146A6C(0x33, a0, 0, 0, 0, 0x8000, 0); \
                i = i + 1; \
            } while (i < 5); \
        } \
        p = *(s32 *)((s32)a0 + 0x20); \
        if ((s2 << 16) == 0) { \
            *(s16 *)(p + 0x18) = *(u16 *)(p + 0x18) ^ 0x400; \
            *(s16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) ^ 0x200; \
        } else { \
            *(s16 *)(p + 0x18) = *(u16 *)(p + 0x18) + s2; \
            *(s16 *)(p + 0x1A) = *(u16 *)(p + 0x1A) + s2; \
        } \
        sp20[0] = *(u16 *)((s32)a0 + 0x12); \
        sp20[1] = *(u16 *)((s32)a0 + 0x16); \
        sp20[2] = *(u16 *)((s32)a0 + 0x1A); \
        func_800D20C0((s32)sp20, (s32)sp28, 0x6); \
        *(s16 *)((s32)a0 + 0x6) = sp20[0]; \
        *(s16 *)((s32)a0 + 0xA) = sp20[1]; \
        *(s16 *)((s32)a0 + 0xE) = sp20[2]; \
    }

#define DEFINE_func_8013895C() \
    extern s32 D_80127524; \
    extern s16 func_80138DB8(s32 a0, u8 a1, s32 a2); \
    extern void func_80138B88(s32 a0); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_8013895C(s32 a0) { \
        if ((s32)D_80127524 == a0 || (*(s32 *)(a0 + 8) & 0x2000)) { \
            if ((s16)func_80138DB8(a0, 0, 0x40)) { \
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) + 1; \
                func_80138B88(a0); \
                func_8002D4C8(0x630, 0); \
            } else if ((s16)func_80138DB8(a0, 0, 0x1000)) { \
                *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x1F) - 1; \
                if ((s8)*(s8 *)(a0 + 0x1F) < 0) { \
                    *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1; \
                } \
                func_8002D4C8(0x62F, 0); \
            } else if ((s16)func_80138DB8(a0, 0, 0x4000)) { \
                u8 cur = *(u8 *)(a0 + 0x1F); \
                u8 lim = *(u8 *)(a0 + 0x21); \
                *(s8 *)(a0 + 0x1F) = cur + 1; \
                if (!((s32)(s8)(*(s8 *)(a0 + 0x1F)) < (s32)lim)) { \
                    *(s8 *)(a0 + 0x1F) = 0; \
                } \
                func_8002D4C8(0x62F, 0); \
            } else if (*(s32 *)(a0 + 8) & 0x2) { \
                if ((s16)func_80138DB8(a0, 0, 0x30)) { \
                    *(s8 *)(a0 + 0x1F) = *(u8 *)(a0 + 0x21) - 1; \
                    func_8002D4C8(0x62F, 0); \
                } \
            } \
        } \
    }

#define DEFINE_func_80154F9C() \
    extern u8 D_80078E78[]; \
    extern s16 D_80078E96; \
    extern s16 D_80078E9E; \
    extern u16 D_80078EA6; \
    extern u8 D_800D8D10[]; \
    extern s32 func_8016F1AC(void); \
    extern void func_801550FC(s32 a0); \
    void func_80154F9C(s32 a0) { \
        u8 *base = D_80078E78; \
        if (*(s32 *)(a0 + 0xC8) & 0x1000000) { \
            if ((D_80078E96 & 0x8000) || D_80078E9E < 0x10 || (s16)D_80078EA6 < 0x10) { \
                if (func_8016F1AC() == 0) { \
                    return; \
                } \
            } \
            *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) & 0xC0FFFFFF; \
            func_801550FC(*(s32 *)(a0 + 0xC8)); \
        } else { \
            if ((D_80078E96 & 0x8000) && func_8016F1AC() == 0) { \
                *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) | 0x1000000; \
                func_801550FC((s32)D_800D8D10); \
                return; \
            } \
            if (!(*(s16 *)(base + 0x26) < 0x10) && !(*(s16 *)(base + 0x2E) < 0x10)) { \
                return; \
            } \
            if (*(s32 *)(a0 + 0x44) & 0xC0) { \
                return; \
            } \
            if (func_8016F1AC() != 0) { \
                return; \
            } \
            *(s32 *)(a0 + 0xC8) = *(s32 *)(a0 + 0xC8) | 0x1000000; \
            func_801550FC(0x40000002); \
        } \
    }

#define DEFINE_func_80171384() \
    extern void *D_8011F738; \
    extern void func_80171928(void *a0); \
    extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_80171384(void *a0) { \
        u8 *p = D_8011F738; \
        s32 last; \
        s32 sum; \
        p[0xC] = func_80012F74(p[0xC], 0, 0xA, 1); \
        p[0xD] = func_80012F74(p[0xD], 0, 0xA, 1); \
        p[0xE] = func_80012F74(p[0xE], 0, 0xA, 1); \
        p[0x1C] = func_80012F74(p[0x1C], 0, 0xA, 1); \
        p[0x1D] = func_80012F74(p[0x1D], 0, 0xA, 1); \
        p[0x1E] = func_80012F74(p[0x1E], 0, 0xA, 1); \
        p[0x2C] = func_80012F74(p[0x2C], 0, 0xA, 1); \
        p[0x2D] = func_80012F74(p[0x2D], 0, 0xA, 1); \
        last = func_80012F74(p[0x2E], 0, 0xA, 1); \
        p[0x2E] = last; \
        sum = p[0xC] + p[0xD] + p[0xE] + p[0x1C] + p[0x1D] + p[0x1E] + p[0x2C] + p[0x2D] + (last & 0xff); \
        if (sum == 0) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_8016986C() \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern void func_800D23D0(void *a0); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32 rand(void); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    void func_8016986C(s32 a0) { \
        s32 s1 = a0; \
        s16 v10[4];   /* sp+0x10 SVECTOR */ \
        s16 v18[4];   /* sp+0x18 SVECTOR */ \
        s16 v20[16];  /* sp+0x20 MATRIX_L48 */ \
        s16 v40[16];  /* sp+0x40 MATRIX_L48 */ \
        s32 v1; \
        s32 t; \
        v10[0] = *(u16 *)(s1 + 0x6); \
        v10[1] = *(u16 *)(s1 + 0xA); \
        v10[2] = *(u16 *)(s1 + 0xE); \
        func_800D20C0(v10, v18, 1); \
        func_800D23D0(v18); \
        RotMatrixYXZ(v18, (void *)(s1 + 0x38)); \
        v10[0] = *(u16 *)(s1 + 0x12); \
        v10[1] = *(u16 *)(s1 + 0x16); \
        v10[2] = *(u16 *)(s1 + 0x1A); \
        RotMatrixYXZ(v10, v40); \
        v1 = rand(); \
        v10[0] = (v1 & 0x1FC) + 0x180; \
        if (*(s32 *)(s1 + 0x2C) & 0x2) { \
            v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0x200; \
        } else { \
            v10[1] = (((u32)(v1 & 0x7F00)) >> 6) + 0xC00; \
        } \
        v10[2] = 0; \
        RotMatrixYXZ(v10, v20); \
        func_80048EAC(v40, v20); \
        if ((*(s32 *)(s1 + 0x2C) & 0x1) == 0) { \
            *(s32 *)(s1 + 0x2C) = 0xE00; \
        } else { \
            *(s32 *)(s1 + 0x2C) = 0xA00; \
        } \
        v10[0] = 0; \
        v10[1] = 0; \
        v10[2] = 0xA; \
        ApplyMatrixSV(v20, v10, v10); \
        *(u16 *)(s1 + 0x12) = v10[0]; \
        *(u16 *)(s1 + 0x16) = v10[1]; \
        { \
            s32 tmp = *(u16 *)(s1 + 0x2); \
            s32 z = (u16)v10[2]; \
            *(s32 *)(s1 + 0x1C) = 0; \
            *(u16 *)(s1 + 0x2) = tmp + 1; \
            *(u16 *)(s1 + 0x1A) = z; \
        } \
    }

#define DEFINE_func_8016AFB0() \
    extern void func_8016B234(); \
    extern void func_800D22E4(s32 a0); \
    void func_8016AFB0(s32 a0) { \
        s32 s0 = a0; \
        s32 s1 = *(s32 *)(s0 + 0x20); \
        s32 v1; \
        s32 v0; \
        if ((u32)*(s32 *)(s0 + 0x2C) < 6) { \
            func_8016B234(); \
        } \
        v1 = *(s32 *)(s0 + 0x2C); \
        if (v1 == 5) goto L9C; \
        if ((u32)v1 < 6) { \
            if (v1 == 1) goto L9C; \
            goto LB8; \
        } \
        if (v1 == 6) goto L38; \
        if (v1 != 7) goto LB8; \
        if (*(s32 *)(s0 + 0x1C) & 0x1) { \
            v1 = 0xAE; \
        } else { \
            v1 = 0xB4; \
        } \
        *(s8 *)(s1 + 0x27) = v1; \
    L38: \
        v0 = *(u8 *)(s1 + 0x26) - 0x8; \
        *(s8 *)(s1 + 0x26) = v0; \
        *(s8 *)(s1 + 0x25) = v0; \
        *(s8 *)(s1 + 0x24) = v0; \
        v0 = *(s32 *)(s0 + 0x1C) - 1; \
        *(s32 *)(s0 + 0x1C) = v0; \
        if (v0 != 0) goto LFC; \
        *(s8 *)(s1 + 0x26) = 0x70; \
        *(s8 *)(s1 + 0x25) = 0x70; \
        *(s8 *)(s1 + 0x24) = 0x70; \
        *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x4) | 0x50000000; \
        *(s32 *)(s0 + 0x1C) = 0x7; \
        *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1; \
        goto LFC; \
    L9C: \
        func_800D22E4(s0); \
        *(s32 *)(s0 + 0x14) = *(s32 *)(s0 + 0x14) + 0x18000; \
    LB8: \
        v0 = *(u16 *)(s0 + 0x24) - 0x8; \
        v1 = *(s32 *)(s0 + 0x1C) - 1; \
        *(u16 *)(s0 + 0x24) = v0; \
        *(s32 *)(s0 + 0x1C) = v1; \
        if (v1 != 0) goto LFC; \
        *(u16 *)(s0 + 0x24) = 0x70; \
        *(s32 *)(s0 + 0x1C) = 0x7; \
        *(u16 *)(s0 + 0x26) = *(u16 *)(s0 + 0x26) + 1; \
        *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1; \
    LFC: \
        return; \
    }

#define DEFINE_func_80166438() \
    extern u8 D_800D387C[]; \
    extern u8 D_800D3888[]; \
    extern s32 func_800D21C4(s32 a0, void *a1, s32 a2); \
    extern void func_800D1FC8(s32 a0, s32 a1); \
    extern void func_80128EA8(s32 a0, s32 a1, s32 a2); \
    extern void func_801665B4(); \
    extern void func_80146C3C(); \
    void func_80166438(u8 *a0) { \
        u8 *s0; \
        s32 v0; \
        s32 v1; \
        v0 = 0x9B; \
        if ((*(s32 *)(a0 + 0x30) & 0x10000000) == 0) { \
            v0 = 0x9C; \
        } \
        s0 = (u8 *)func_800D21C4((s32)a0, D_800D387C, v0); \
        if (s0 == 0) goto tail; \
        *(s32 *)(a0 + 0x20) = (s32)s0; \
        { \
            register s32 r asm("$2"); \
            r = *(s32 *)(a0 + 0x30) & 0x7FFF; \
            *(u16 *)(s0 + 0x1A) = r; \
            *(u16 *)(s0 + 0x18) = r; \
        } \
        if (*(s32 *)(a0 + 0x30) & 0x8000) { \
            func_800D1FC8((s32)a0, 6); \
        } \
        v1 = *(s32 *)(a0 + 0x30); \
        if (v1 < 0) { \
            *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x50000000; \
        } else { \
            if (v1 & 0x8000000) { \
                *(s32 *)(s0 + 4) = 0x60000000; \
            } \
        } \
        if ((*(s32 *)(a0 + 0x30) & 0x40000000) == 0) { \
            *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x40; \
        } else { \
            *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & -0x41; \
        } \
        if (*(s32 *)(a0 + 0x30) & 0x20000000) { \
            u32 h; \
            *(s8 *)(s0 + 0x24) = ((u32)*(s32 *)(a0 + 0x2C) >> 20) & 0xF0; \
            h = *(u16 *)(a0 + 0x2E); \
            *(s8 *)(s0 + 0x25) = h & 0xF0; \
            *(s8 *)(s0 + 0x26) = ((u32)*(s32 *)(a0 + 0x2C) >> 12) & 0xF0; \
        } \
        func_80128EA8((s32)s0, (s32)(a0 + 0x24), (s32)D_800D3888); \
        { \
            register s32 r asm("$2"); \
            r = *(u16 *)(a0 + 2) + 1; \
            *(u16 *)(a0 + 0x16) = *(s32 *)(a0 + 0x2C); \
            *(u16 *)(a0 + 2) = r; \
        } \
        func_801665B4((s32)a0); \
        return; \
    tail: \
        func_80146C3C((s32)a0); \
    }

#define DEFINE_func_8013240C() \
    extern void func_801325B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4); \
    void func_8013240C(s32 a0) { \
        s32 *node; \
        s32 ent; \
        s32 v; \
        s16 h6; \
        ent = *(s32 *)(a0 + 0x0) + (*(s16 *)(a0 + 0x4) << 3); \
        node = (s32 *)*(s32 *)(ent + 0); \
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) & 0xFFFF3FFF; \
        if ((s32)node == -1) { \
            *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) | 0x4000; \
            return; \
        } \
        if (*(s16 *)(ent + 0x6) < 0) { \
            v = 0x1000 - ((*(s16 *)(a0 + 0x6) << 12) / *(s16 *)(ent + 0x4)); \
        } else { \
            v = (*(s16 *)(a0 + 0x6) << 12) / *(s16 *)(ent + 0x4); \
        } \
        func_801325B8(*(s32 *)(a0 + 0x8), node[0], node[1], node[2], v); \
        h6 = *(s16 *)(ent + 0x6); \
        if (h6 < 0) { \
            *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) - h6; \
        } else { \
            *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + h6; \
        } \
        if (*(s16 *)(a0 + 0x6) < *(s16 *)(ent + 0x4)) { \
            return; \
        } \
        *(s16 *)(a0 + 0x6) = 0; \
        *(s16 *)(a0 + 0x4) = *(u16 *)(a0 + 0x4) + 1; \
        { \
            s32 *p = (s32 *)((*(s16 *)(a0 + 0x4) << 3) + *(s32 *)(a0 + 0x0)); \
            s32 w = p[0]; \
            s32 c; \
            if (w != -1) { \
                if (w != 0) { \
                    return; \
                } \
                *(s16 *)(a0 + 0x4) = 0; \
                c = *(s32 *)(a0 + 0xC) | 0x8000; \
            } else { \
                c = *(s32 *)(a0 + 0xC) | 0x4000; \
            } \
            *(s32 *)(a0 + 0xC) = c; \
        } \
    }

#define DEFINE_func_80148648() \
    extern u8 D_800B9A64; \
    extern s32 func_80014DC0(); \
    extern s32 func_80014D68(); \
    extern s32 func_80014D94(); \
    extern s32 func_80014CF8(); \
    extern void func_800120DC(); \
    extern s32 func_800CF8B4(); \
    void func_80148648(s32 a0, s32 a1) { \
        s32 v; \
        if (D_800B9A64 == 0) { \
            s32 b = a1 & 0xFF; \
            *(u8 *)(a0 + 0xA9) = func_80014DC0(b); \
            *(s16 *)(a0 + 0xAA) = func_80014D68(b); \
            *(s16 *)(a0 + 0xAC) = func_80014D94(b); \
            { \
                s32 r4 = func_80014CF8(b, 4); \
                s32 r5 = func_80014CF8(b, 5); \
                *(s16 *)(a0 + 0xAE) = (r4 & 0xFF) | ((r5 & 0xFF) << 8); \
            } \
        } else { \
            *(u8 *)(a0 + 0xA9) = 0x41; \
            func_800120DC(a0 + 0xAA, a0 + 0xAC); \
        } \
        if (*(u8 *)(a0 + 0x1C5) != 0) { \
            *(s16 *)(a0 + 0xAA) = 0; \
            *(s16 *)(a0 + 0xAC) = 0; \
            *(u16 *)(a0 + 0xAE) = 0x8080; \
        } \
        if (func_800CF8B4() == 0) { \
            u16 mode = *(u16 *)(a0 + 0x0); \
            if (mode != 0x1E && mode != 0x1A) { \
                *(s16 *)(a0 + 0xAA) = 0; \
                *(s16 *)(a0 + 0xAC) = 0; \
                *(u16 *)(a0 + 0xAE) = 0x8080; \
            } \
        } \
        { \
            s32 act = *(u8 *)(a0 + 0xA9); \
            if (act == 0x53 || (act >= 0x54 && act == 0x73)) { \
                if ((*(u16 *)(a0 + 0xAA) & 0xF000) != 0) { \
                    *(u8 *)(a0 + 0xA9) = 0x41; \
                } \
            } \
        } \
        if (*(s32 *)(a0 + 0x1B0) != 0) { \
            s32 vAA = *(u16 *)(a0 + 0xAA); \
            s32 vAE = *(u16 *)(a0 + 0xAE); \
            s32 vAC = *(u16 *)(a0 + 0xAC); \
            s32 t; \
            t = ((vAA & 0x2000) << 2) | ((vAA & 0x8000) >> 2); \
            t = t | (vAA & 0x5FFF); \
            *(s16 *)(a0 + 0xAA) = t; \
            t = ((vAC & 0x2000) << 2) | ((vAC & 0x8000) >> 2); \
            t = t | (vAC & 0x5FFF); \
            *(s16 *)(a0 + 0xAC) = t; \
            if ((vAE & 0xFF) != 0x80) { \
                vAE = (~(vAE & 0xFF) & 0xFF) | (vAE & 0xFF00); \
            } \
            *(s16 *)(a0 + 0xAE) = vAE; \
        } \
    }

#define DEFINE_func_80159120() \
    extern s32 func_80029504(void); \
    extern s32 func_801399F0(s32); \
    extern void func_80139914(s32 a0); \
    extern s32 func_80029A94(s32); \
    extern void func_80175454(void); \
    extern void func_801458E0(void); \
    extern void func_800298BC(void *); \
    extern void func_801458E8(void); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_8002992C(s32); \
    extern void func_80145A2C(void); \
    extern void func_80146C98(s32 *a0, s16 a1); \
    extern void func_800CF804(void); \
    extern void func_800CF818(void); \
    extern u8 D_80078E50; \
    extern s32 D_80078E8C; \
    extern u8 D_80110D0C[]; \
    extern u8 D_80110C3C[]; \
    void func_80159120(s32 a0) { \
        s32 r; \
        s32 v1; \
        s32 base; \
        func_80029504(); \
        base = *(s32 *)(a0 + 0x20); \
        *(u16 *)(base + 0x12) = (*(u16 *)(base + 0x12) + 0x16) & 0xFFF; \
        r = func_801399F0(*(s32 *)(a0 + 0x198)); \
        if (r == 0) { \
            return; \
        } \
        func_80139914(*(s32 *)(a0 + 0x198)); \
        *(s32 *)(a0 + 0x198) = 0; \
        if (r != 1) { \
            if (r == 2) { \
                goto L290; \
            } \
        } \
        v1 = *(s16 *)(a0 + 0x244); \
        if (v1 != 1) { \
            if (v1 == 2) { \
                goto L224; \
            } \
        } \
        if (func_80029A94(1) != 0) { \
            s32 t; \
            func_80175454(); \
            func_801458E0(); \
            t = D_80078E8C; \
            func_800298BC(&D_80078E50); \
            func_801458E8(); \
            D_80078E8C = t / 2; \
            goto L270; \
        } \
        *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110D0C); \
        func_80146C98((s32 *)a0, 0xB); \
        return; \
    L224: \
        if (func_80029A94(0) != 0) { \
            func_80175454(); \
            func_8002992C(0); \
            func_80145A2C(); \
            goto L270; \
        } \
        *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110D0C); \
        func_80146C98((s32 *)a0, 0xB); \
        return; \
    L270: \
        func_80146C98((s32 *)a0, 0xC); \
        func_800CF804(); \
        func_800CF818(); \
        return; \
    L290: \
        *(s32 *)(a0 + 0x198) = func_8013767C((s32)D_80110C3C); \
        func_80146C98((s32 *)a0, 0x9); \
    }

#define DEFINE_func_8013AB54() \
    extern void func_8013AD38(void *a0, s32 a1, void *a2, void *a3); \
    extern void func_8013B274(s32 a0, s32 a1, void *a2); \
    extern void func_8013AF20(); \
    extern s32 D_800A5E60; \
    s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3) { \
        u8 buf[0xE4];          /* spans 0x10 .. 0xF4 */ \
        s32 neg; \
        s32 a, b; \
        s32 t4, t6; \
        t4 = *(s16 *)(a2 + 4) * 12; \
        *(s16 *)(buf + 0xE0) = t4 + 0x10;   /* sp+0xF0 */ \
        neg = a3 & 0x8000; \
        t6 = *(s16 *)(a2 + 6) * 12 + (*(s16 *)(a2 + 6) - 1) * 2; \
        *(s16 *)(buf + 0xE2) = t6 + 8; \
        if (neg == 0) { \
            *(s16 *)(buf + 0xE0) = t4 + 0x38; \
            *(s16 *)(buf + 0xE2) = t6 + 0x10; \
        } \
        a = ((s32)*(s16 *)(buf + 0xE0) << 12) / 154; \
        b = ((s32)*(s16 *)(buf + 0xE2) << 12) / 42; \
        *(s16 *)(buf + 0xE0) = a; \
        *(s16 *)(buf + 0xE2) = b; \
        if (neg != 0) { \
            *(s16 *)(buf + 0xE0) = -a; \
        } \
        *(s16 *)(buf + 0xC8) = b;          /* 0xD8 */ \
        *(s16 *)(buf + 0xC2) = 0;          /* 0xD2 */ \
        *(s16 *)(buf + 0xC4) = 0;          /* 0xD4 */ \
        *(s16 *)(buf + 0xC6) = 0;          /* 0xD6 */ \
        *(s16 *)(buf + 0xCA) = 0;          /* 0xDA */ \
        *(s16 *)(buf + 0xCC) = 0;          /* 0xDC */ \
        *(s16 *)(buf + 0xCE) = 0;          /* 0xDE */ \
        *(s16 *)(buf + 0xD0) = 0x1000;     /* 0xE0 */ \
        *(s16 *)(buf + 0xC0) = *(u16 *)(buf + 0xE0);   /* 0xD0 */ \
        *(s32 *)(buf + 0xD4) = *(s16 *)(a2 + 0);       /* 0xE4 */ \
        *(s32 *)(buf + 0xD8) = *(s16 *)(a2 + 2);       /* 0xE8 */ \
        *(s32 *)(buf + 0xDC) = 0;                       /* 0xEC */ \
        __asm__ __volatile__("" ::: "memory"); \
        { \
            register s32 *p __asm__("$2") = (s32 *)(buf + 0xC0); \
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
                "lw $12, 20(%0)\n" \
                "lw $13, 24(%0)\n" \
                "ctc2 $12, $5\n" \
                "lw $14, 28(%0)\n" \
                "ctc2 $13, $6\n" \
                "ctc2 $14, $7\n" \
                : : "r"(p) : "$12", "$13", "$14", "memory"); \
        } \
        func_8013AD38(buf + 0xE0, 0, buf + 0x00, buf + 0x80); \
        D_800A5E60 = a0; \
        if (a3 != 0) { \
            func_8013B274(a1, 0x80, buf + 0xE0); \
        } \
        func_8013AF20(a1, a2, buf + 0x00, buf + 0x80); \
        return D_800A5E60; \
    }

#define DEFINE_func_80172738() \
    extern void func_80174684(void *); \
    extern s32 func_80172760(s32 a0); \
    void func_80172738(void) { \
        func_80174684((void *)func_80172760); \
    }

#define DEFINE_func_80173174() \
    extern void func_80174684(void *); \
    extern s32 func_8017319C(void *a0); \
    void func_80173174(void) { \
        func_80174684((void *)func_8017319C); \
    }

#define DEFINE_func_8017427C() \
    extern void func_80174684(void *); \
    extern s32 func_801742A4(void *a0); \
    void func_8017427C(void) { \
        func_80174684((void *)func_801742A4); \
    }

#define DEFINE_func_8017435C() \
    extern void func_80174684(void *); \
    extern s32 func_80174384(void *a0); \
    void func_8017435C(void) { \
        func_80174684((void *)func_80174384); \
    }

#define DEFINE_func_80174784() \
    extern void func_8016EDEC(s32 a0, s32 a1, s32 a2); \
    extern s32 func_801747CC(void *a0); \
    void func_80174784(void) { \
        ((void (*)(void *, s32))func_8016EDEC)((void *)func_801747CC, 0x1000000); \
    }

#define DEFINE_func_80174824() \
    extern void func_8016EDEC(s32 a0, s32 a1, s32 a2); \
    extern s32 func_80174888(void *a0); \
    void func_80174824(void) { \
        ((void (*)(void *, s32))func_8016EDEC)((void *)func_80174888, 0x1000000); \
    }

#define DEFINE_func_80159B08() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80159BE4(s32); \
    void func_80159B08(s32 *a0) { \
        func_80147078(a0, 0); \
        func_80159BE4(a0); \
    }

#define DEFINE_func_8015A1FC() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015A2D8(s32); \
    void func_8015A1FC(s32 *a0) { \
        func_80147078(a0, 1); \
        func_8015A2D8(a0); \
    }

#define DEFINE_func_8015BF48() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015C0C4(s32 a0); \
    void func_8015BF48(s32 *a0) { \
        func_80147078(a0, 0x4); \
        func_8015C0C4(a0); \
    }

#define DEFINE_func_8015C6AC() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015C788(s32 a0); \
    void func_8015C6AC(s32 *a0) { \
        func_80147078(a0, 0x9); \
        func_8015C788(a0); \
    }

#define DEFINE_func_8015D480() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015D57C(s32); \
    void func_8015D480(s32 *a0) { \
        func_80147078(a0, 0xD); \
        func_8015D57C(a0); \
    }

#define DEFINE_func_8015DA90() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015DB6C(s32 a0); \
    void func_8015DA90(s32 *a0) { \
        func_80147078(a0, 0xE); \
        func_8015DB6C(a0); \
    }

#define DEFINE_func_8015DDF0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015DECC(s32 a0); \
    void func_8015DDF0(s32 *a0) { \
        func_80147078(a0, 0xF); \
        func_8015DECC(a0); \
    }

#define DEFINE_func_8015E150() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015E22C(s32 a0); \
    void func_8015E150(s32 *a0) { \
        func_80147078(a0, 0x10); \
        func_8015E22C(a0); \
    }

#define DEFINE_func_8015E84C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015E95C(s32); \
    void func_8015E84C(s32 *a0) { \
        func_80147078(a0, 0x11); \
        func_8015E95C(a0); \
    }

#define DEFINE_func_8015EDA0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015EE7C(s32); \
    void func_8015EDA0(s32 *a0) { \
        func_80147078(a0, 0x12); \
        func_8015EE7C(a0); \
    }

#define DEFINE_func_8015EFA4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015F080(s32); \
    void func_8015EFA4(s32 *a0) { \
        func_80147078(a0, 0x13); \
        func_8015F080(a0); \
    }

#define DEFINE_func_80174E9C() \
    extern void func_8012A018(s32 a, s32 b); \
    extern s32 D_8012697C; \
    extern u16 D_80126980; \
    extern s32 func_80174F28(void *a0); \
    void func_80174E9C(s32 a0) { \
        D_8012697C = a0; \
        D_80126980 = 0; \
        func_8012A018((s32)func_80174F28, 0); \
    }

#define DEFINE_func_80174EF0() \
    extern void func_8012A018(s32 a, s32 b); \
    extern s32 D_8012697C; \
    extern u16 D_80126980; \
    extern s32 func_80174F28(void *a0); \
    void func_80174EF0(s32 a0, s16 a1) { \
        D_8012697C = a0; \
        D_80126980 = a1; \
        func_8012A018((s32)func_80174F28, 1); \
    }

#define DEFINE_func_80170634() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170670(void *a0); \
    void func_80170634(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_80170670(a0); \
    }

#define DEFINE_func_80170F38() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80170F74(void *a0); \
    void func_80170F38(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_80170F74(a0); \
    }

#define DEFINE_func_80170FEC() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_80171028(void *a0); \
    void func_80170FEC(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        func_80171990(a0); \
        func_80171028(a0); \
    }

#define DEFINE_func_80174438() \
    extern void func_80174684(void *); \
    extern s32 func_80174474(void *a0); \
    extern s32 D_80127508; \
    void func_80174438(s32 a0) { \
        func_80174684((void *)func_80174474); \
        D_80127508 = a0; \
    }

#define DEFINE_func_801729B0() \
    extern void func_80174684(void *); \
    extern s32 func_801729F0(void *a0); \
    extern s16 D_80126B34; \
    extern s16 D_80126B30; \
    extern s16 D_80126B32; \
    void func_801729B0(s32 a0) { \
        D_80126B34 = a0; \
        D_80126B30 = 0; \
        D_80126B32 = 0; \
        func_80174684((void *)func_801729F0); \
    }

#define DEFINE_func_80147AD4() \
    extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4); \
    extern void func_80147B5C(s32 a0, void *a1); \
    void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3) { \
        u8 buf[16]; \
        func_80147CC8(a0, a1, a2, a3, (s32)buf); \
        func_80147B5C(a0, (s32)buf); \
    }

#define DEFINE_func_8016F71C() \
    extern void *D_8011F738; \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016F764(void *a0); \
    void func_8016F71C(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        *(void **)(a0 + 0x200) = D_8011F738; \
        func_80171990(a0); \
        func_8016F764((s32)a0); \
    }

#define DEFINE_func_80170928() \
    extern u8 D_800D5A34[]; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_80170928(void) { \
        D_8011F738 = D_800D5A34; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_80170970() \
    extern u8 D_800D59EC[]; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_80170970(void) { \
        D_8011F738 = D_800D59EC; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_801709B8() \
    extern u8 D_800D599C[]; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_801709B8(void) { \
        D_8011F738 = D_800D599C; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_80170A00() \
    extern u8 D_800D5934[]; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_80170A00(void) { \
        D_8011F738 = D_800D5934; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_80170A48() \
    extern u8 D_800D5DA8; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_80170A48(void) { \
        D_8011F738 = &D_800D5DA8; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_80170A90() \
    extern u8 D_800D5DC0[]; \
    extern void *D_8011F738; \
    extern s32 D_80126B58; \
    extern void func_80170AD8(void *a0); \
    extern void func_80171904(s32 a0); \
    extern void func_80170B48(int a0); \
    void func_80170A90(void) { \
        D_8011F738 = D_800D5DC0; \
        func_80171904((s32)func_80170AD8); \
        func_80170B48((int)&D_80126B58); \
    }

#define DEFINE_func_801736B0() \
    extern s32 func_8014C118(void *a0, s32 a1, s32 a2); \
    extern void func_80174684(void *); \
    extern s32 func_801736FC(void *a0); \
    extern s32 D_80126B58; \
    extern s32 D_80127508; \
    void func_801736B0(s32 a0, s32 a1) { \
        D_80127508 = func_8014C118(&D_80126B58, a0, (s16)a1); \
        func_80174684(func_801736FC); \
    }

#define DEFINE_func_8016FAC0() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8016FB10(void *a0); \
    void func_8016FAC0(u8 *a0) { \
        u8 *v1; \
        *(s16 *)(a0 + 0x136) = 2; \
        v1 = *(u8 **)(a0 + 0x20); \
        *(s16 *)(a0 + 0x132) = *(u16 *)(v1 + 0x12); \
        func_801719A4((int)a0, 2); \
        func_80171990(a0); \
        func_8016FB10(a0); \
    }

#define DEFINE_func_80170784() \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_801707D4(void *a0); \
    extern void *D_8011F738; \
    void func_80170784(u8 *a0) { \
        func_801719A4((int)a0, 1); \
        (*(void (*)(void))D_8011F738)(); \
        func_80171990(a0); \
        func_801707D4(a0); \
    }

#define DEFINE_func_8017250C() \
    extern s32 func_80172560(u8 *a0, u8 *a1); \
    int func_8017250C(short *a0, short *a1) { \
        if (func_80172560(a0, a1) == 0) { \
            return 0; \
        } \
        a0[3] = a1[0];   /* sh v0,6(s1) <- lhu 0(s0) */ \
        a0[7] = a1[2];   /* sh v1,0xE(s1) <- lhu 4(s0) */ \
        return 1; \
    }

#define DEFINE_func_8015E95C() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_8015E9B8(s32 *a0); \
    extern u8 D_80078EC0; \
    void func_8015E95C(s32 a0) { \
        if ((D_80078EC0 & 0x80) == 0) { \
            func_80146A6C(0x14, (void *)a0, 0, 0, 0, 0, 0); \
        } \
        func_8015E9B8(a0); \
    }

#define DEFINE_func_8014A1B0() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern u16 func_80156370(u16 a0); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    void func_8014A1B0(s32 a0, s32 a1) { \
        s16 sp18[4]; \
        u16 tmp; \
        func_80015978(a0 + 4, (s32 *)sp18); \
        sp18[3] = 0; \
        tmp = func_80156370(0xA); \
        func_8014C4AC(a1, 0xA, tmp, sp18, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)); \
    }

#define DEFINE_func_801748EC() \
    extern void func_8012A018(s32 a, s32 b); \
    extern s32 func_8017496C(void *a0); \
    extern s32 D_80126954; \
    extern s32 D_80126950; \
    extern s32 D_8012695C; \
    extern s16 D_80126968; \
    extern s16 D_8012696A; \
    extern s16 D_8012696C; \
    extern s16 D_80126976; \
    extern s16 D_80126978; \
    extern s16 D_8012697A; \
    void func_801748EC(void) { \
        D_80126954 = 0x1F4; \
        D_80126950 = 0x1F4; \
        D_8012695C = 0x384; \
        D_80126968 = 0x1C7; \
        D_8012696A = 0x600; \
        D_8012696C = 0; \
        D_80126976 = 0; \
        D_80126978 = 0; \
        D_8012697A = 0; \
        func_8012A018((s32)func_8017496C, 0); \
    }

#define DEFINE_func_8014E48C() \
    extern void func_8014E5B4(s32 a0, void *a1, void *a2); \
    extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2); \
    void func_8014E48C(s32 a0) { \
        s16 buf1[4]; \
        s16 buf2[4]; \
        buf1[0] = *(u16 *)(a0 + 0x88); \
        buf1[1] = *(u16 *)(a0 + 0x8A); \
        buf1[2] = *(u16 *)(a0 + 0x8C); \
        buf2[0] = *(u16 *)(a0 + 0x6); \
        buf2[1] = *(u16 *)(a0 + 0xA); \
        buf2[2] = *(u16 *)(a0 + 0xE); \
        if (*(s32 *)(a0 + 0x17C) == 0) { \
            func_8014E5B4(a0, buf1, buf2); \
        } else { \
            func_8014E514(a0, buf1, buf2); \
        } \
    }

#define DEFINE_func_80149D10() \
    extern u8 func_8014B5B8(s32 *a0); \
    extern u8 D_80078EBF; \
    extern u8 D_80078EC0; \
    s32 func_80149D10(s32 a0) { \
        if (*(s32 *)(a0 + 0x44) & 0x400) { \
            return 0; \
        } \
        if (D_80078EBF != 0x80) { \
            return 0; \
        } \
        if ((D_80078EC0 & 0x7F) == 0) { \
            return 0; \
        } \
        if (*(u16 *)(a0 + 0xAC) & 0x10) { \
            if ((func_8014B5B8((s32 *)a0) & 0xFF) != 0) { \
                return 2; \
            } \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_801432FC() \
    extern s32 func_80142DB8(s32 *a0); \
    extern s32 func_8012C044(s32 a0); \
    extern void func_80142BB4(s32 *a0, s32 a1, s32 a2); \
    extern void func_80142C9C(s32 *a0); \
    extern s32 func_8012BF10(s32 a0, s32 a1); \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    void func_801432FC(s32 *a0) { \
        if (func_80142DB8(a0) == 1) { \
            func_80142BB4(a0, 1, 3); \
            return; \
        } \
        if (*(s16 *)((u8 *)a0 + 0x100) != 0) { \
            if (func_8012C044(a0) == 0) { \
                return; \
            } \
            func_80142BB4(a0, 0, 3); \
            return; \
        } \
        func_80142C9C(a0); \
        if (func_8012BF10((s32)a0, 0x30) != 0) { \
            func_8012AD44(a0, 2); \
        } \
    }

#define DEFINE_func_801472C8() \
    s32 func_801472C8(struct S *a0) { \
        return a0->f7E = a0->f7E | 0x2; \
    }

#define DEFINE_func_8014C8F0() \
    void func_8014C8F0(s32 arg0) { \
        *(struct UnalignedPair *)(arg0 + 0x15c) = *(struct UnalignedPair *)(arg0 + 0x90); \
    }

#define DEFINE_func_80139FBC() \
    void func_80139FBC(struct obj *a0) { \
        if (a0->unk8 & 0x800) { \
            a0->unk8 &= ~0x800; \
            a0->unk4 = 2; \
        } \
    }

#define DEFINE_func_8014C860() \
    s32 func_8014C860(s32 a0, s32 a1) { \
        s32 r = 1; \
        *(struct S8 *)(a0 + 0x154) = *(struct S8 *)a1; \
        *(s16*)(a0 + 0x15A) = r; \
        return r; \
    }

#define DEFINE_func_8012931C() \
    void func_8012931C(struct vec *a0) { \
        a0->unk4 += a0->unk10; \
        a0->unk8 += a0->unk14; \
        a0->unkC += a0->unk18; \
    }

#define DEFINE_func_8015BE04() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015BE38(struct Obj *a0); \
    void func_8015BE04(s32 *a0) { \
        func_80147078(a0, 0x3); \
        func_8015BE38((struct Obj *)a0); \
    }

#define DEFINE_func_8016F540() \
    extern void func_8014708C(void *a0); \
    extern s32 func_801472C8(struct S *a0); \
    extern void func_80171928(void *a0); \
    void func_8016F540(void *a0) { \
        func_8014708C(a0); \
        func_801472C8((struct S *)a0); \
        func_80171928(a0); \
    }

#define DEFINE_func_8014C010() \
    extern void func_80146AFC(void *a0); \
    void func_8014C010(s32 a0, s32 a1) { \
        struct S8014C010 sp; \
        sp.w8 = a0; \
        sp.h0 = 2; \
        sp.h1 = 0; \
        sp.h2 = 0; \
        sp.h3 = 0; \
        sp.wC = a1; \
        sp.w10 = 0; \
        func_80146AFC(&sp); \
    }

#define DEFINE_func_8014AD30() \
    extern void func_80146AFC(void *a0); \
    void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3) { \
        struct S_8014AD30 sp; \
        s16 b = a1[0]; \
        s16 c = a1[1]; \
        s16 d = a1[2]; \
        sp.h0 = 0x1D; \
        sp.w0 = a0; \
        sp.w1 = a2; \
        sp.w2 = a3; \
        sp.h1 = b; \
        sp.h2 = c; \
        sp.h3 = d; \
        func_80146AFC(&sp); \
    }

#define DEFINE_func_801504D8() \
    extern s32 func_80150528(void *a0, void *a1, void *a2); \
    void func_801504D8(u16 *a0) { \
        struct V3 a; \
        struct V3 b; \
        s32 t6 = a0[3];   /* 0x6 */ \
        s32 ta; \
        s32 te; \
        b.x = t6; \
        a.x = t6; \
        ta = a0[5];       /* 0xA */ \
        a.y = ta - 3; \
        te = a0[7];       /* 0xE */ \
        b.y = ta + 1; \
        b.z = te; \
        a.z = te; \
        func_80150528(a0, &a, &b); \
    }

#define DEFINE_func_80172780() \
    extern void func_80174684(void *); \
    extern s16 D_80126B30; \
    extern s32 func_801727D0(void *a0); \
    void func_80172780(void *a0) { \
        *(struct S8_80172780 *)&D_80126B30 = *(struct S8_80172780 *)a0; \
        func_80174684((void *)func_801727D0); \
    }

#define DEFINE_func_80172894() \
    extern void func_80174684(void *); \
    extern s16 D_80126B30; \
    extern s32 func_801728E4(void *a0); \
    void func_80172894(void *a0) { \
        *(struct S8_80172894 *)&D_80126B30 = *(struct S8_80172894 *)a0; \
        func_80174684((void *)func_801728E4); \
    }

#define DEFINE_func_80143BDC() \
    extern s32 func_8012C51C(void *a0, s32 a1); \
    void func_80143BDC(u16 *a0) { \
        struct S80143BDC sp; \
        u16 t; \
        sp.f0 = a0[0]; \
        sp.f2 = a0[1]; \
        t = a0[2]; \
        sp.f6 = 0x1C; \
        sp.f8 = 1; \
        sp.fA = 0; \
        sp.f10 = 0; \
        sp.fE = 0; \
        sp.f4 = t; \
        func_8012C51C(&sp, 0); \
    }

#define DEFINE_func_80173460() \
    extern void func_801734BC(s32 a0, s32 a1); \
    extern struct S80126B38 D_80126B38; \
    extern s16 D_80126B3E; \
    void func_80173460(s32 a0, s32 a1) { \
        func_801734BC(a0, a1); \
        D_80126B38 = *(struct S80126B38 *)a1; \
        D_80126B3E = 1; \
    }

#define DEFINE_func_80131E7C() \
    extern s32 func_8012E470(s32 a0); \
    extern void func_8012E4C8(s32 a0); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern void func_80131CA8(int a0, int a1); \
    void func_80131E7C(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x40000) { \
            if (func_8012E470(a0)) { \
                func_8012E4C8(a0); \
                func_80131E00((struct S80131E00 *)a0, 1); \
            } \
        } \
        func_80131CA8(a0, 0x3A); \
    }

#define DEFINE_func_801433F0() \
    extern void func_80143458(); \
    extern void func_8012931C(struct vec *a0); \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_801292C8(u8 *a0); \
    void func_801433F0(s32 a0) { \
        if (*(u16 *)(a0 + 2) == 0) { \
            func_80143458(); \
        } else { \
            func_8012931C((struct vec *)a0); \
            if (func_80128ED8(*(void **)(a0 + 0x20), (u8 *)a0 + 0x24) != 0) { \
                func_801292C8((u8 *)a0); \
            } \
        } \
    }

#define DEFINE_func_8012BC60() \
    extern void Square0(s32 *a0, s32 *a1); \
    s32 func_8012BC60(struct Vec *a0, struct Vec *a1) { \
        s32 d[3]; \
        d[0] = a0->unk2 - a1->unk2; \
        d[1] = a0->unk6 - a1->unk6; \
        d[2] = a0->unkA - a1->unkA; \
        Square0(d, d); \
        return d[0] + d[1] + d[2]; \
    }

#define DEFINE_func_8013A250() \
    extern void func_80139A8C(s32 a0); \
    extern void func_80139B18(s32 a0); \
    extern void func_80138B88(s32 a0); \
    void func_8013A250(struct S8013A250 *a0) { \
        if (a0->unkC != 0) { \
            a0->unkC = a0->unkC - 1; \
            func_80139A8C((s32)a0); \
            if ((a0->unk8 & 0x80020) == 0) { \
                func_80139B18((s32)a0); \
                return; \
            } \
        } \
        func_80138B88((s32)a0); \
    }

#define DEFINE_func_8013A4C4() \
    extern void func_8013A530(); \
    void func_8013A4C4(struct S8013A4C4 *a0) { \
        struct Inner8013A4C4 *a1 = a0->unk4; \
        a0->unkE = 0; \
        a1->unk28 -= 0x400; \
        a1->unk2A -= 0x400; \
        if (a1->unk28 < 0x401) { \
            a1->unk2A = 0; \
            a1->unk28 = 0; \
            a0->unk0 = 4; \
            a0->unk2 = 0; \
            a0->unk4 = 0; \
        } else { \
            func_8013A530(); \
        } \
    }

#define DEFINE_func_8013E22C() \
    extern void Square12(s32 *a0, s32 *a1); \
    s32 func_8013E22C(struct VecA *a0, struct VecB *a1) { \
        s32 d[3]; \
        s32 sq[3]; \
        d[0] = a0->unk2 - a1->unk0; \
        d[1] = a0->unk6 - a1->unk2; \
        d[2] = a0->unkA - a1->unk4; \
        Square12(d, sq); \
        return sq[0] + sq[1] + sq[2]; \
    }

#define DEFINE_func_8014FDF4() \
    extern s32 func_80150170(void *a0); \
    extern s32 func_8014FE60(); \
    void func_8014FDF4(struct S8014FDF4 *a0) { \
        if (a0->f6 != a0->f88 || a0->fA != a0->f8A || a0->fE != a0->f8C) { \
            func_80150170(a0); \
        } else { \
            func_8014FE60(a0); \
        } \
    }

#define DEFINE_func_80151ECC() \
    extern void func_80149020(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_80172630(u8 *a0); \
    void func_80151ECC(struct S80151ECC *a0) { \
        func_80149020((s32 *)a0); \
        a0->f64 = a0->f64 + (a0->fDE << 6); \
        a0->fDE = a0->fDE + 5; \
        if (a0->f64 >= 0x1556) { \
            a0->fDE = 0x10; \
            func_80146CA0(a0); \
        } \
        func_80172630((u8 *)a0); \
    }

#define DEFINE_func_80153150() \
    extern void func_80149020(s32 *a0); \
    extern void func_801470B4(s32 a0); \
    extern void func_8015369C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80153150(struct S80153150 *a0) { \
        s16 nv; \
        func_80149020((s32 *)a0); \
        nv = (s16)(a0->f64 - 0x100); \
        a0->f64 = nv; \
        a0->f62 = nv; \
        a0->f60 = nv; \
        if (nv <= 0) { \
            a0->fDE = 0x10; \
            func_801470B4((s32)a0); \
            func_8015369C((s32)a0); \
            func_80146CA0(a0); \
        } \
    }

#define DEFINE_func_80172358() \
    void func_80172358(u8 *a0, u8 *a1) { \
        *(u16 *)(a0 + 6) = *(u16 *)(a1 + 0); \
        *(u16 *)(a0 + 0xA) = *(u16 *)(a1 + 2); \
        *(u16 *)(a0 + 0xE) = *(u16 *)(a1 + 4); \
        *(struct U8 *)(a0 + 0x90) = *(struct U8 *)(a1 + 0); \
        *(struct U8 *)(a0 + 0x88) = *(struct U8 *)(a0 + 0x90); \
    }

#define DEFINE_func_80136ECC() \
    extern short D_800B9A02; \
    extern u8 D_800A6518[]; \
    extern void GsSortLine(void *a0, void *a1, s32 a2); \
    void func_80136ECC(s16 a0, s16 a1, s16 a2, s16 a3, u8 r, u8 g, u8 b) { \
        struct { \
            u32 tag; \
            s16 x0; \
            s16 y0; \
            s16 x1; \
            s16 y1; \
            u8 r; \
            u8 g; \
            u8 b; \
        } line; \
        line.x0 = a0; \
        line.tag = 0; \
        line.y0 = a1; \
        line.x1 = a2; \
        line.y1 = a3; \
        line.r = r; \
        line.g = g; \
        line.b = b; \
        GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0); \
    }

#define DEFINE_func_801730FC() \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80147060(u8 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B30; \
    void func_801730FC(struct S801730FC *a0) { \
        if (a0->unkB8 & 0x8000) { \
            func_80171A1C((u8 *)a0); \
            if (D_80126B30 != 0) { \
                func_80147060(a0); \
                func_80154150(a0, 0); \
            } \
            func_80174650((s32)a0); \
        } \
    }

#define DEFINE_func_8014350C() \
    extern void func_8014358C(void); \
    extern void func_8012931C(struct vec *a0); \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_801292C8(u8 *a0); \
    void func_8014350C(s32 *a0) { \
        if (*(u16 *)((u8 *)a0 + 2) == 0) { \
            func_8014358C(); \
            return; \
        } \
        func_8012931C((struct vec *)a0); \
        if (func_80128ED8((void *)a0[0x20 / 4], (void *)((u8 *)a0 + 0x24)) != 0) { \
            func_801292C8((u8 *)a0); \
            return; \
        } \
        *(u8 *)(a0[0x20 / 4] + 0x27) = *(u8 *)((u8 *)a0 + 0x28) - 0x70; \
    }

#define DEFINE_func_8012FE70() \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern void func_80131170(s32 a0, s32 a1, s32 a2); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012FE70(s32 a0) { \
        s32 v1 = *(s32 *)(a0 + 0xC4); \
        *(u8 *)(a0 + 0xC1) = 9; \
        if (v1 & 2) { \
            *(u8 *)(a0 + 0xC1) = 1; \
            func_80131CA8(a0, 3); \
        } else if (v1 & 1) { \
            func_80131E00((struct S80131E00 *)a0, 1); \
        } else { \
            if (*(s32 *)(a0 + 0xB4) & 0x200) { \
                func_80131170(a0, 0, 0); \
            } \
            func_80131CA8(a0, 0x1E); \
        } \
    }

#define DEFINE_func_8014ED80() \
    extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2); \
    s32 func_8014ED80(struct SubED80 *a0) { \
        s16 g1[3]; \
        s16 g2[3]; \
        if (a0->f44 & 0x80000) { \
            return 0; \
        } \
        if (a0->f1F8 & 0x4000000) { \
            return 0; \
        } \
        g1[0] = a0->f88; \
        g1[1] = a0->f8A - 0x10; \
        g1[2] = a0->f8C; \
        g2[0] = a0->f6; \
        g2[1] = a0->fA - 0x10; \
        g2[2] = a0->fE; \
        func_8014EE14((s32)a0, g1, g2); \
    }

#define DEFINE_func_8014F24C() \
    extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2); \
    s32 func_8014F24C(struct SubF24C *a0) { \
        s16 g1[3]; \
        s16 g2[3]; \
        if (a0->f44 & 0x80000) { \
            return 0; \
        } \
        if (a0->f1F8 & 0x4000000) { \
            return 0; \
        } \
        g1[0] = a0->f88; \
        g1[1] = a0->f8A - 0x10; \
        g1[2] = a0->f8C; \
        g2[0] = a0->f6; \
        g2[1] = a0->fA - 0x10; \
        g2[2] = a0->fE; \
        func_8014F2E0((s32)a0, g1, g2); \
    }

#define DEFINE_func_8016380C() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern void func_80015954(s32 a0, s32 a1); \
    s32 func_8016380C(struct S8016380C *a0, s32 a1) { \
        struct M8 local; \
        s32 ret; \
        local = a0->m; \
        func_80015978((s32)((u8 *)a0 + 4), (s32 *)a1); \
        ret = func_80133784(1, &local, a1); \
        if (ret != 0) { \
            func_80015954(a1, (s32)((u8 *)a0 + 4)); \
            return ret; \
        } \
        return 0; \
    }

#define DEFINE_func_8014E6F8() \
    extern s32 func_8014E83C(s32 a0, s16 *a1, s16 *a2); \
    extern s32 func_8014E790(s32 a0, s16 *a1, s16 *a2); \
    void func_8014E6F8(struct SubE6F8 *a0) { \
        s16 g1[3]; \
        s16 g2[3]; \
        u16 t8A; \
        u16 tA; \
        g1[0] = a0->f88; \
        t8A = a0->f8A; \
        g1[1] = t8A; \
        g1[2] = a0->f8C; \
        g2[0] = a0->f6; \
        tA = a0->fA; \
        g2[1] = tA; \
        g2[2] = a0->fE; \
        if (a0->f180 == 0) { \
            g1[1] = t8A - 0x54; \
            g2[1] = tA - 0x54; \
            func_8014E83C((s32)a0, g1, g2); \
        } else { \
            func_8014E790((s32)a0, g1, g2); \
        } \
    }

#define DEFINE_func_80152E4C() \
    extern void func_80149020(s32 *a0); \
    extern void func_80153B58(s32 *a0); \
    extern void func_80147A84(s32 arg0); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern s32 func_801472C8(struct S *a0); \
    extern void func_801470B4(s32 a0); \
    extern void func_8015369C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152E4C(s32 a0) { \
        s32 s0 = a0; \
        s32 v0; \
        func_80149020((s32 *)s0); \
        func_80153B58((s32 *)s0); \
        func_80147A84(s0); \
        func_801473EC((s32 *)s0); \
        v0 = *(u8 *)(s0 + 0xDF); \
        if (v0 == 0) { \
            func_80148038(s0, 0x18000); \
        } else { \
            *(u8 *)(s0 + 0xDF) = v0 - 1; \
        } \
        func_80147460(s0); \
        { \
            u8 dv = *(u8 *)(s0 + 0xDE); \
            *(u8 *)(s0 + 0xDE) = dv + 0xFF; \
            if (dv != 0) return; \
        } \
        { \
            *(u8 *)(s0 + 0xDE) = 0x10; \
            func_801472C8(s0); \
            func_801470B4(s0); \
            func_8015369C(s0); \
            func_80146CA0((void *)s0); \
        } \
    }

#define DEFINE_func_8015294C() \
    extern u16 D_800B99DA; \
    extern void func_80149020(s32 *a0); \
    extern void func_801470B4(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_80147A84(s32 arg0); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern s32 func_801472C8(struct S *a0); \
    extern void func_8015369C(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015294C(s32 a0) { \
        s32 s0 = a0; \
        func_80149020((s32 *)s0); \
        if (D_800B99DA & 1) { \
            func_801470B4(s0); \
        } else { \
            func_801470AC((s32 *)s0); \
        } \
        func_80147A84(s0); \
        func_801473EC((s32 *)s0); \
        func_80148038(s0, 0x18000); \
        func_80147460(s0); \
        { \
            u8 v = *(u8 *)(s0 + 0xDE); \
            *(u8 *)(s0 + 0xDE) = v + 0xFF; \
            if (v == 0) { \
                *(u8 *)(s0 + 0xDE) = 0x10; \
                func_801472C8((s32 *)s0); \
                func_801470B4(s0); \
                func_8015369C(s0); \
                func_80146CA0((void *)s0); \
            } \
        } \
    }

#define DEFINE_func_8012AE00() \
    extern s32 *D_80126B78; \
    extern s32 *D_80126B90; \
    extern s32 D_80126B58; \
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80013478(s32 a0, s32 a1); \
    s32 func_8012AE00(s32 a0) { \
        s16 sp10[3]; \
        s16 sp18[4]; \
        struct V8 sp20; \
        s32 r1, r2; \
        s32 base; \
        s32 p18 = (s32)sp18; \
        sp10[0] = *(u16 *)(a0 + 0x3A); \
        sp10[1] = *(u16 *)(a0 + 0x3E); \
        sp10[2] = *(u16 *)(a0 + 0x42); \
        sp18[0] = *(u16 *)(a0 + 0x6); \
        sp18[1] = *(u16 *)(a0 + 0xA); \
        sp18[2] = *(u16 *)(a0 + 0xE); \
        base = (s32)&D_80126B58; \
        sp20 = *(struct V8 *)sp18; \
        if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)sp10, (s32)&sp20) == 0) { \
            return 0; \
        } \
        base += 4; \
        r1 = func_80013478(base, (s32)sp10); \
        r2 = func_80013478(base, p18); \
        if (r1 < r2) { \
            return 0; \
        } \
        *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x38); \
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0x3C); \
        *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40); \
        return 1; \
    }

#define DEFINE_func_80171520() \
    extern void *D_8011F738; \
    extern struct B16 D_800A5E88; \
    extern struct B16 D_800A5E98; \
    extern struct B16 D_800A5EA8; \
    extern void func_801719A4(int a0, int a1); \
    extern s32 func_80171990(u8 *a0); \
    extern void func_8017162C(void *a0); \
    void func_80171520(s32 a0) { \
        u8 *v1; \
        s32 p; \
        func_801719A4(a0, 1); \
        v1 = (u8 *)D_8011F738; \
        *(struct B16 *)(v1 + 0x0) = D_800A5E88; \
        *(struct B16 *)(v1 + 0x10) = D_800A5E98; \
        *(struct B16 *)(v1 + 0x20) = D_800A5EA8; \
        v1[0xE] = 0; \
        v1[0xD] = 0; \
        v1[0xC] = 0; \
        v1[0x1E] = 0; \
        v1[0x1D] = 0; \
        v1[0x1C] = 0; \
        v1[0x2E] = 0; \
        v1[0x2D] = 0; \
        v1[0x2C] = 0; \
        p = *(s32 *)(a0 + 0x20); \
        *(u16 *)(p + 0x2C) = *(u16 *)(p + 0x2C) | 0x20; \
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x80) = (s32)v1; \
        func_80171990((u8 *)a0); \
        func_8017162C((void *)a0); \
    }

#define DEFINE_func_8012AF0C() \
    s32 func_8012AF0C(s32 a0, s32 a1) { \
        s32 s1 = a0; \
        s32 s2 = a1; \
        s16 spA[4];                /* sp+0x10 */ \
        struct M8012AF0C spB;      /* sp+0x18 (src) */ \
        struct M8012AF0C spC;      /* sp+0x20 (dst) */ \
        s16 spD[4];                /* sp+0x28 */ \
        spA[0] = *(u16 *)(s1 + 0x3A); \
        spA[1] = *(u16 *)(s1 + 0x3E); \
        spA[2] = *(u16 *)(s1 + 0x42); \
        spB.a = *(u16 *)(s1 + 0x6); \
        spB.b = *(u16 *)(s1 + 0xA); \
        spB.c = *(u16 *)(s1 + 0xE); \
        spC = spB; \
        if (func_80135888(*(s32 *)(s2 + 0x20), *(s32 *)(s2 + 0x58), (s32)spA, (s32)&spC) != 0) { \
            s32 r0, r1; \
            spD[0] = *(u16 *)(s2 + 0x6); \
            spD[1] = *(u16 *)(s2 + 0xA); \
            spD[2] = *(u16 *)(s2 + 0xE); \
            r0 = func_800132BC((s32)spD, (s32)spA); \
            r1 = func_800132BC((s32)spD, (s32)&spB); \
            if (r0 < r1) return 0; \
            *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x38); \
            *(s32 *)(s1 + 0x8) = *(s32 *)(s1 + 0x3C); \
            *(s32 *)(s1 + 0xC) = *(s32 *)(s1 + 0x40); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80138D58() \
    extern void func_8013A9F8(s32 a0, s32 a1); \
    void func_80138D58(s32 a0, u16 a1) { \
        if (*(s32 *)(a0 + 0x40) == 0) { \
            return; \
        } \
        if ((u32)(*(u16 *)(a0 + 0x18) - 2) >= 5) { \
            return; \
        } \
        if ((u32)(u16)(a1 - 2) >= 5) { \
            return; \
        } \
        *(s16 *)(a0 + 0x18) = a1; \
        func_8013A9F8(*(s32 *)(a0 + 0x40), a1); \
    }

#define DEFINE_func_80146014() \
    extern void MoveImage(void *a0, s32 a1, s32 a2); \
    void func_80146014(s32 a0) { \
        s32 *r = (s32 *)a0; \
        if (r[3] == 0) { \
            return; \
        } \
        do { \
            MoveImage(r, r[2], r[3]); \
            r += 4; \
        } while (r[3] != 0); \
    }

#define DEFINE_func_801582C0() \
    extern u8 D_800D52A8[]; \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801585A4(s32 *a0); \
    extern void func_8016706C(s32 a0); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    void func_801582C0(void *a0) { \
        s32 s0 = (s32)a0; \
        *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 2; \
        *(s8 *)(s0 + 0x1AA) = 0x10; \
        func_80154274((s32 *)s0, (s32)D_800D52A8); \
        func_80154A74(s0, 0x15); \
        func_801585A4((s32 *)s0); \
        func_8016706C(5); \
        func_80146994(4, s0, 8, 0); \
        func_80147324(0x446); \
        func_80146CA0((void *)s0); \
    }

#define DEFINE_func_80139DF4() \
    extern void func_80139A8C(s32 a0); \
    void func_80139DF4(s32 a0) { \
        s32 c; \
        s32 v; \
        c = *(u8 *)(a0 + 0xC); \
        if (c != 0) { \
            c = c - 1; \
            *(s8 *)(a0 + 0xC) = (s8)c; \
            if ((c & 0xFF) != 0) { \
                goto calls; \
            } \
        } \
        *(s16 *)(a0 + 0x4) = 2; \
        return; \
    calls: \
        func_80139A8C(a0); \
        if (*(s32 *)(a0 + 0x8) & 0x20) { \
            *(s16 *)(a0 + 0x4) = 2; \
            v = *(s32 *)(a0 + 0x8); \
            *(s8 *)(a0 + 0xC) = 0; \
            if ((v & 0x20000) == 0) { \
                *(s32 *)(a0 + 0x8) = v & -0x21; \
            } \
        } \
    }

#define DEFINE_func_8016E3CC() \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern void func_800D23D0(void *a0); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    void func_8016E3CC(s32 a0) { \
        s16 src[4]; \
        u8 mtx[8]; \
        s32 p; \
        p = *(s32 *)(a0 + 0x34); \
        src[0] = *(u16 *)(p + 0x6); \
        src[1] = *(u16 *)(p + 0xA) - 0x28; \
        src[2] = *(u16 *)(p + 0xE); \
        func_800D20C0((void *)src, (void *)mtx, 6); \
        *(s16 *)(a0 + 0x6) = src[0]; \
        *(s16 *)(a0 + 0xA) = src[1]; \
        *(s16 *)(a0 + 0xE) = src[2]; \
        func_800D23D0((void *)mtx); \
        RotMatrixYXZ((void *)mtx, (void *)(a0 + 0x38)); \
    }

#define DEFINE_func_8012F374() \
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2); \
    extern s16 D_80126CB4; \
    extern s16 D_80126CB6; \
    extern s16 D_80126CB8; \
    void func_8012F374(s32 a0, s32 a1) { \
        s32 s0 = a1; \
        s32 in[3]; \
        s32 out[3]; \
        s32 mtx; \
        mtx = *(s32 *)(a0 + 0x20); \
        in[0] = D_80126CB4 - *(s32 *)(mtx + 0x48); \
        in[1] = D_80126CB6 - *(s32 *)(mtx + 0x4C); \
        in[2] = D_80126CB8 - *(s32 *)(mtx + 0x50); \
        ApplyTransposeMatrixLV((void *)(mtx + 0x34), in, out); \
        *(s16 *)(s0 + 0x0) = out[0]; \
        *(s16 *)(s0 + 0x2) = out[1]; \
        *(s16 *)(s0 + 0x4) = out[2]; \
    }

#define DEFINE_func_801308DC() \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80131CA8(int a0, int a1); \
    void func_801308DC(s32 a0) { \
        *(u8 *)(a0 + 0xC1) = 0xE; \
        if ((*(s32 *)(a0 + 0xB4) & 0x8000) != 0) { \
            *(s32 *)(a0 + 0x1C) = 0x10; \
            *(s16 *)(a0 + 0xAA) = 0; \
            *(s16 *)(a0 + 0x5C) = 0; \
            *(s16 *)(a0 + 0x98) = 0; \
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x400; \
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x400; \
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x200; \
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10; \
            func_8002D4C8(0x68A, 0); \
        } \
        func_80131CA8(a0, 0x2A); \
    }

#define DEFINE_func_8015F080() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80149048(s32 *a0); \
    extern void func_80156648(s32 *a0); \
    extern void func_80149020(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015F080(s32 a0) { \
        func_80154150(a0, 0x17); \
        func_80154A74(a0, 0x15); \
        func_80146994(0x5, a0, 0x7, 0); \
        *(s32 *)(a0 + 0x238) = -1; \
        *(s32 *)(a0 + 0x234) = 0; \
        *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & -2; \
        func_80149048((s32 *)a0); \
        func_80156648((s32 *)a0); \
        *(s8 *)(a0 + 0x1AA) = 8; \
        func_80149020((s32 *)a0); \
        *(s16 *)(a0 + 0xF6) = 0x19EB; \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8012A110() \
    extern s32 D_80120204; \
    extern s32 D_80120200; \
    extern s32 D_8012020C; \
    extern s32 D_80120208; \
    extern s16 D_80120218; \
    extern s16 D_80120210; \
    extern s16 D_8012021A; \
    extern s16 D_80120212; \
    extern s16 D_8012021C; \
    extern s16 D_80120214; \
    extern s16 D_80120226; \
    extern s16 D_80120220; \
    extern s16 D_80120228; \
    extern s16 D_80120222; \
    extern s16 D_8012022A; \
    extern s16 D_80120224; \
    extern s32 D_80120294; \
    extern s16 D_80120298; \
    extern s16 D_8012029A; \
    void func_8012A110(void) { \
        D_80120204 = 0x1F4; \
        D_80120200 = 0x1F4; \
        D_8012020C = 0x5DC; \
        D_80120208 = 0x5DC; \
        D_80120218 = 0x238; \
        D_80120210 = 0x238; \
        D_8012021A = 0; \
        D_80120212 = 0; \
        D_8012021C = 0; \
        D_80120214 = 0; \
        D_80120226 = 0; \
        D_80120220 = 0; \
        D_80120228 = 0; \
        D_80120222 = 0; \
        D_8012022A = 0; \
        D_80120224 = 0; \
        D_80120294 = 0; \
        D_80120298 = 0; \
        D_8012029A = 0; \
    }

#define DEFINE_func_801653F4() \
    extern s32 func_80165624(s32 a0); \
    extern u8 D_80078EC1; \
    extern u8 D_80078EC5; \
    extern s16 currentLocationId; \
    void func_801653F4(s32 a0) { \
        s32 loc; \
        s32 v; \
        loc = currentLocationId; \
        D_80078EC5 = 0; \
        v = D_80078EC1 & 0x7F; \
        D_80078EC1 = v; \
        if (func_80165624(a0) != 0) { \
            D_80078EC5 = 0x80; \
            return; \
        } \
        if (D_80078EC1 != 0x1A) { \
            return; \
        } \
        if ((u32)(loc - 0x305C) < 2) return; \
        if ((u32)(loc - 0x305E) < 2) return; \
        if ((u32)(loc - 0x3060) < 2) return; \
        if ((u32)(loc - 0x3062) < 2) return; \
        if ((u32)(loc - 0x3064) < 2) return; \
        if (loc == 0x3066) return; \
        D_80078EC5 = 0x80; \
    }

#define DEFINE_func_80129010() \
    extern s16 D_8011DB2C; \
    extern s16 D_8011DB30; \
    extern s32 D_80126AEC; \
    void func_80129010(void) { \
        s32 i; \
        s32 s1; \
        s32 idx; \
        void (*fp)(s32); \
        s1 = (s32)&D_8011DB30; \
        if (D_8011DB2C == 0) { \
            return; \
        } \
        i = 0; \
        do { \
            idx = *(u16 *)s1; \
            if (idx != 0) { \
                fp = (void (*)(s32))(*(s32 *)((idx << 2) + (*(s32 *)&D_80126AEC))); \
                fp(s1); \
                if (*(s32 *)(s1 + 0x20) != 0) { \
                    *(s16 *)(*(s32 *)(s1 + 0x20) + 0x8) = *(u16 *)(s1 + 0x6); \
                    *(s16 *)(*(s32 *)(s1 + 0x20) + 0xA) = *(u16 *)(s1 + 0xA); \
                    *(s16 *)(*(s32 *)(s1 + 0x20) + 0xC) = *(u16 *)(s1 + 0xE); \
                } \
            } \
            i++; \
            s1 += 0x38; \
        } while (i < 0x80); \
    }

#define DEFINE_func_80138AB4() \
    extern s16 D_80127540[4]; \
    extern s32 func_80139D04(s32 a0, s32 a1); \
    extern s32 func_80138DE0(s32 a0, s32 a1, s32 a2); \
    extern void func_80139B18(s32 a0); \
    void func_80138AB4(s32 a0) { \
        u8 sp10[8]; \
        s32 s0 = a0; \
        s32 s1; \
        s32 a0v; \
        s1 = func_80139D04((s32)sp10, (u16)D_80127540[*(u16 *)(s0 + 0x48)]) & 0xFFFF; \
        do { \
            s32 v1 = *(u16 *)(s0 + 0x44); \
            a0v = 0; \
            if ((s32)v1 < s1) { \
                s32 a1v = (sp10[v1] + 0x30) & 0xFF; \
                a0v = func_80138DE0(s0, a1v, 0); \
                if (*(s32 *)(s0 + 0x8) & 0x80220) { \
                    /* a0v stays */ \
                } else { \
                    a0v = 0; \
                } \
            } else { \
                s32 t = *(u16 *)(s0 + 0x48); \
                if ((u32)t < 3) { \
                    *(s16 *)(s0 + 0x48) = t + 1; \
                } \
                *(s16 *)(s0 + 0x4) = 2; \
            } \
        } while (a0v != 0); \
        func_80139B18(s0); \
    }

#define DEFINE_func_8014B350() \
    extern u8 D_80078E78[]; \
    extern s16 D_80078E96; \
    extern s32 D_80078E94; \
    extern u8 D_80062BF4[]; \
    extern s32 func_8016F1C4(void); \
    extern void func_8014BC80(s32 a0, s32 a1); \
    extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3); \
    extern void func_80019064(void *a0); \
    void func_8014B350(s32 a0) { \
        s32 s0 = a0; \
        s32 s1 = (s32)&D_80078E78; \
        s32 v0; \
        s32 v1; \
        u16 buf[4]; \
        if (func_8016F1C4() != 0) { \
            return; \
        } \
        v1 = *(u16 *)(s0 + 0x0); \
        if (v1 == 0x1E || v1 == 0x1A) { \
            return; \
        } \
        if (D_80078E96 & 0x8000) { \
            if (*(s32 *)(s0 + 0x44) & 0x80) { \
                D_80078E94 = D_80078E94 + 0xAAA8; \
            } else { \
                D_80078E94 = D_80078E94 + 0x1555; \
            } \
            v0 = *(u16 *)(s1 + 0x1E) & 0x7FFF; \
            if (v0 < 0x3D) { \
            } else { \
                *(s32 *)(s1 + 0x1C) = 0x80000000; \
                func_8014BC80(s0, 8); \
                buf[0] = *(u16 *)(s0 + 0x6); \
                buf[1] = *(u16 *)(s0 + 0xA) - 0x20; \
                buf[2] = *(u16 *)(s0 + 0xE); \
                func_8014AD30(s0, buf, 6, 0); \
                func_80019064(&D_80062BF4); \
            } \
        } \
        if (*(s16 *)(s1 + 0x56) & 0x8000) { \
            if (*(s32 *)(s0 + 0x44) & 0x80) { \
                *(s32 *)(s1 + 0x54) = *(s32 *)(s1 + 0x54) + 0xAAA8; \
            } else { \
                *(s32 *)(s1 + 0x54) = *(s32 *)(s1 + 0x54) + 0x1555; \
            } \
            v0 = *(u16 *)(s1 + 0x56) & 0x7FFF; \
            if (v0 < 0x3D) { \
            } else { \
                *(s32 *)(s1 + 0x54) = 0x80000000; \
            } \
        } \
    }

#define DEFINE_func_80143640() \
    extern u8 *func_8012913C(s32 a0); \
    extern s32 rand(void); \
    void func_80143640(s32 a0, s32 a1, s32 a2, s32 a3) { \
        u8 *s0; \
        s32 r; \
        s32 d0, d1, d2; \
        s32 t; \
        s32 pad[6]; \
        (void)pad; \
        if ((*(u16 *)(a0 + 0) & (s16)((1 << a3) - 1)) == 0) { \
            s0 = func_8012913C(0x22); \
            if (s0 != 0) { \
                r = rand(); \
                d0 = *(s16 *)(a2 + 0); \
                *(s16 *)(s0 + 6) = (*(u16 *)(a1 + 0) + (r % (d0 << 1))) - d0; \
                r = rand(); \
                d1 = *(s16 *)(a2 + 2); \
                *(s16 *)(s0 + 0xA) = (*(u16 *)(a1 + 2) + (r % (d1 << 1))) - d1; \
                r = rand(); \
                d2 = *(s16 *)(a2 + 4); \
                t = *(u16 *)(a1 + 4); \
                *(s32 *)(s0 + 0x18) = 0; \
                *(s32 *)(s0 + 0x14) = 0; \
                *(s32 *)(s0 + 0x10) = 0; \
                *(s16 *)(s0 + 0xE) = (t + (r % (d2 << 1))) - d2; \
                *(s16 *)(s0 + 0x34) = *(u16 *)(a1 + 6); \
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = 0xC008; \
            } \
        } \
        *(u16 *)(a0 + 0) += 1; \
    }

#define DEFINE_func_801437D8() \
    extern u8 *func_8012913C(s32 a0); \
    extern s32 rand(void); \
    void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3) { \
        u8 *s0; \
        s32 r; \
        s32 d0, d1, d2; \
        s32 t; \
        s32 pad[6]; \
        (void)pad; \
        if ((*(u16 *)(a0 + 0) & (s16)((1 << a3) - 1)) == 0) { \
            s0 = func_8012913C(0x23); \
            if (s0 != 0) { \
                r = rand(); \
                d0 = *(s16 *)(a2 + 0); \
                *(s16 *)(s0 + 6) = (*(u16 *)(a1 + 0) + (r % (d0 << 1))) - d0; \
                r = rand(); \
                d1 = *(s16 *)(a2 + 2); \
                *(s16 *)(s0 + 0xA) = (*(u16 *)(a1 + 2) + (r % (d1 << 1))) - d1; \
                r = rand(); \
                d2 = *(s16 *)(a2 + 4); \
                t = *(u16 *)(a1 + 4); \
                *(s32 *)(s0 + 0x18) = 0; \
                *(s32 *)(s0 + 0x14) = 0; \
                *(s32 *)(s0 + 0x10) = 0; \
                *(s16 *)(s0 + 0xE) = (t + (r % (d2 << 1))) - d2; \
                *(s16 *)(s0 + 0x34) = *(u16 *)(a1 + 6); \
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = 0xC008; \
            } \
        } \
        *(u16 *)(a0 + 0) += 1; \
    }

#define DEFINE_func_80143EBC() \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_8012C218(void *a0); \
    extern s32 func_80134510(s32 arg); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_8004787C(s32 a0); \
    extern s16 D_801152AC; \
    extern s16 D_801152AA; \
    extern u8 D_801152A8[]; \
    void func_80143EBC(s32 a0) { \
        s32 s1 = *(s32 *)(a0 + 0x64); \
        s32 s0 = *(s32 *)(a0 + 0xCC); \
        s16 sp[3]; \
        s32 v0; \
        if (*(s16 *)(s1 + 0x36) != *(s16 *)(a0 + 0xFC)) { \
            if (a0 == 0) { \
                return; \
            } \
            func_80016714((void *)s0, 0x38); \
            func_8012C218((void *)a0); \
            return; \
        } \
        sp[0] = *(u16 *)(s1 + 6); \
        sp[1] = *(u16 *)(s1 + 0xA) - 0x10; \
        sp[2] = *(u16 *)(s1 + 0xE); \
        if (func_80134510((s32)&sp[0]) == 0) { \
            *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x80000000; \
            return; \
        } \
        *(s16 *)(s0 + 8) = sp[0]; \
        *(s16 *)(s0 + 0xA) = sp[1]; \
        *(s16 *)(s0 + 0xC) = sp[2]; \
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & 0x7FFFFFFF; \
        if (*(s16 *)(a0 + 0x70) == 1) { \
            *(s16 *)(s0 + 0x10) = 0x400; \
            *(s16 *)(s0 + 0x12) = 0; \
        } else { \
            *(s16 *)(s0 + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400; \
            *(s16 *)(s0 + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA); \
        } \
        v0 = *(s32 *)(s1 + 0x20); \
        *(s16 *)(s0 + 0x14) = -(*(u16 *)(v0 + 0x12)); \
        v0 = *(s32 *)(s1 + 0x20); \
        *(s16 *)(s0 + 0x18) = func_8004787C((*(u16 *)(v0 + 0x14) & 0x3FF) << 1) + 0x4000; \
        v0 = *(s32 *)(s1 + 0x20); \
        *(s16 *)(s0 + 0x1A) = func_8004787C((*(u16 *)(v0 + 0x10) & 0x3FF) << 1) + 0x4000; \
    }

#define DEFINE_func_80162B1C() \
    extern void func_80162CC4(void); \
    extern s32 D_80126D40; \
    extern s32 D_8011F9D0; \
    void func_80162B1C(void) { \
        s32 s3 = *(s32 *)&D_80126D40; \
        s32 s2 = 0; \
        s32 s1 = 0; \
        s32 s0; \
        s32 a0; \
        s32 p; \
        s32 fp; \
        void (*f)(s32); \
        do { \
            s0 = s1 + (s32)&D_8011F9D0; \
            *(s16 *)(s0 + 0x44) = *(u16 *)(s0 + 0x6); \
            *(s16 *)(s0 + 0x46) = *(u16 *)(s0 + 0xA); \
            *(s16 *)(s0 + 0x48) = *(u16 *)(s0 + 0xE); \
            if (*(u16 *)(s0 + 0x0) != 0) { \
                fp = *(s32 *)((*(u16 *)(s0 + 0x0) << 2) + s3 - 4); \
                if (fp != 0) { \
                    f = (void (*)(s32))fp; \
                    f(s0); \
                } else { \
                    ((void (*)(s32))func_80162CC4)(s0); \
                } \
                a0 = *(s32 *)(s0 + 0x20); \
                if (a0 != 0) { \
                    if (*(u16 *)a0 == 1) { \
                        s32 b0 = *(u16 *)(s0 + 0x6); \
                        *(s16 *)(a0 + 0x8) = b0; \
                        *(s32 *)(a0 + 0x48) = (s16)b0; \
                        b0 = *(u16 *)(s0 + 0xA); \
                        *(s16 *)(a0 + 0xA) = b0; \
                        *(s32 *)(a0 + 0x4C) = (s16)b0; \
                        { \
                            s32 m = *(u16 *)(a0 + 0x2C) | 1; \
                            s32 c0 = *(u16 *)(s0 + 0xE); \
                            *(s16 *)(a0 + 0xC) = c0; \
                            *(s16 *)(a0 + 0x2C) = m; \
                            *(s32 *)(a0 + 0x50) = (s16)c0; \
                        } \
                    } else if ((p = *(s32 *)(a0 + 0x34)) != 0) { \
                        s32 b0 = *(u16 *)(s0 + 0x6); \
                        *(s16 *)(a0 + 0x8) = b0; \
                        *(s32 *)(p + 0x14) = (s16)b0; \
                        b0 = *(u16 *)(s0 + 0xA); \
                        *(s16 *)(a0 + 0xA) = b0; \
                        *(s32 *)(*(s32 *)(a0 + 0x34) + 0x18) = (s16)b0; \
                        b0 = *(u16 *)(s0 + 0xE); \
                        *(s16 *)(a0 + 0xC) = b0; \
                        *(s32 *)(*(s32 *)(a0 + 0x34) + 0x1C) = (s16)b0; \
                    } else { \
                        *(s16 *)(a0 + 0x8) = *(u16 *)(s0 + 0x6); \
                        *(s16 *)(a0 + 0xA) = *(u16 *)(s0 + 0xA); \
                        *(s16 *)(a0 + 0xC) = *(u16 *)(s0 + 0xE); \
                    } \
                } \
            } \
            s2 += 1; \
            s1 += 0x68; \
        } while (s2 < 0x14); \
    }

#define DEFINE_func_80147054() \
    s32 func_80147054(void *a0) { \
        s32 r = 1; \
        *(signed char *)((char *)a0 + 0x4C) = r; \
        return r; \
    }

#define DEFINE_func_801470A0() \
    s32 func_801470A0(void *a0) { \
        s32 r = 1; \
        *(signed char *)((char *)a0 + 0x220) = r; \
        return r; \
    }

#define DEFINE_func_8012DFBC() \
    void func_8012DFBC(void) { \
        char buf[16]; \
    }

#define DEFINE_func_80165900() \
    extern s8 D_80078EC4; \
    s32 func_80165900(void) { \
        return (unsigned char)D_80078EC4; \
    }

#define DEFINE_func_80129428() \
    extern s16 D_80114EE0; \
    void func_80129428(void) { \
        D_80114EE0 = 1; \
    }

#define DEFINE_func_8012AD6C() \
    void func_8012AD6C(void *a0) { \
        *(short *)((char *)a0 + 0x34) = *(unsigned short *)((char *)a0 + 0x34) + 1; \
    }

#define DEFINE_func_8012BF54() \
    void func_8012BF54(void *a0) { \
        *(short *)((char *)a0 + 0x5C) = *(unsigned short *)((char *)a0 + 0x5C) | 0x8000; \
    }

#define DEFINE_func_801472DC() \
    extern void *D_8012707C; \
    void func_801472DC(void) { \
        D_8012707C = (void *)0x451; \
    }

#define DEFINE_func_801658EC() \
    extern s8 D_80078EC4; \
    void func_801658EC(void) { \
        D_80078EC4 = 1; \
    }

#define DEFINE_func_80148D24() \
    s32 func_80148D24(void *a0, int a1) { \
        int p = *(int *)((char *)a0 + 0x20); \
        *(short *)(p + 0x12) = (a1 - 0x800) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_8012A304() \
    extern s8 D_801152C0; \
    extern s16 D_80127080; \
    extern s16 D_801152C2; \
    void func_8012A304(s32 a0, s32 a1) { \
        D_801152C0 = 1; \
        D_80127080 = a0; \
        D_801152C2 = a1; \
    }

#define DEFINE_func_80147264() \
    extern s16 D_80126BB8; \
    extern s16 D_80126BBA; \
    extern s16 D_80126BBC; \
    void func_80147264(s32 a0) { \
        D_80126BB8 = *(u16 *)(a0 + 0x0); \
        D_80126BBA = *(u16 *)(a0 + 0x2); \
        D_80126BBC = *(u16 *)(a0 + 0x4); \
    }

#define DEFINE_func_8016F680() \
    extern void func_8016F350(void); \
    extern void func_80171928(void *a0); \
    void func_8016F680(void *a0) { \
        func_8016F350(); \
        func_80171928(a0); \
    }

#define DEFINE_func_8016F6B0() \
    extern void func_8016F330(void); \
    extern void func_80171928(void *a0); \
    void func_8016F6B0(void *a0) { \
        func_8016F330(); \
        func_80171928(a0); \
    }

#define DEFINE_func_8015BDD0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_8015BE94(); \
    void func_8015BDD0(s32 *a0) { \
        func_80147078(a0, 3); \
        ((s32 (*)(void *))func_8015BE94)(a0); \
    }

#define DEFINE_func_8014C050() \
    extern s32 D_8011D030; \
    s32 func_8014C050(s32 a0, s32 a1) { \
        u32 i = 0; \
        s32 p = (s32)&D_8011D030; \
        for (; i < 0x1E; i++) { \
            if (*(u16 *)p == a1) { \
                return p; \
            } \
            p += 0x58; \
        } \
        return 0; \
    }

#define DEFINE_func_8014BD24() \
    extern s16 D_80078EB8; \
    extern u16 D_80078EB6; \
    void func_8014BD24(s32 a0, s32 a1) { \
        u16 v; \
        v = *(u16 *)&D_80078EB8 + a1; \
        D_80078EB8 = v; \
        if (D_80078EB6 < v) { \
            D_80078EB8 = D_80078EB6; \
        } \
    }

#define DEFINE_func_80149AD4() \
    extern void func_8015DAC4(s32 *a0); \
    extern void func_8015554C(s32 *a0); \
    void func_80149AD4(s32 *a0) { \
        s32 pad[6]; \
        (void)pad; \
        if (*(s32 *)((s32)a0 + 0x178) != 0) { \
            func_8015DAC4(a0); \
        } else { \
            *(s8 *)((s32)a0 + 0x1AA) = 1; \
            func_8015554C(a0); \
        } \
    }

#define DEFINE_func_80149B14() \
    extern void func_8015DAC4(s32 *a0); \
    extern void func_8015554C(s32 *a0); \
    void func_80149B14(s32 *a0) { \
        s32 pad[6]; \
        (void)pad; \
        if (*(s32 *)((s32)a0 + 0x178) != 0) { \
            func_8015DAC4(a0); \
        } else { \
            func_8015554C(a0); \
        } \
    }

#define DEFINE_func_80149BAC() \
    extern void func_8015DE24(s32 *a0); \
    extern void func_80157510(s32 *a0); \
    void func_80149BAC(s32 *a0) { \
        if (*(s32 *)((s32)a0 + 0x178) != 0) { \
            func_8015DE24(a0); \
        } else { \
            *(s8 *)((s32)a0 + 0x1AA) = 1; \
            func_80157510(a0); \
        } \
    }

#define DEFINE_func_8014BC80() \
    extern s16 D_80078EB4; \
    extern u8 D_800B9A17; \
    void func_8014BC80(s32 a0, s32 a1) { \
        s32 v; \
        v = *(u16 *)&D_80078EB4; \
        if (v < a1) { \
            D_80078EB4 = 0; \
            D_800B9A17 = 0; \
        } else { \
            D_80078EB4 = v - a1; \
        } \
    }

#define DEFINE_func_8014C088() \
    extern s32 D_8011F9D0; \
    s32 func_8014C088(s32 a0, s32 a1) { \
        u8 *p; \
        u8 *end; \
        p = (u8 *)&D_8011F9D0; \
        end = p + 0xC30; \
        if (p >= end) { \
            return 0; \
        } \
        do { \
            if (*(u16 *)p == a1) { \
                return (s32)p; \
            } \
            p += 0x68; \
        } while (p < end); \
        return 0; \
    }

#define DEFINE_func_80169FE0() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80146C3C(void); \
    void func_80169FE0(s32 a0) { \
        if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_8016DEE0() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80146C3C(void); \
    void func_8016DEE0(s32 a0) { \
        if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_80149A64() \
    extern s32 func_80149AA8(s32 *a0); \
    extern s32 func_80149B54(s32 *a0); \
    s32 func_80149A64(s32 *a0) { \
        if (func_80149AA8(a0) || func_80149B54(a0)) { \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8012BCCC() \
    extern s32 func_80013478(s32 a0, s32 a1); \
    extern s16 D_80126CBA; \
    extern s32 D_80126B58; \
    s32 func_8012BCCC(s32 a0) { \
        s32 *p = &D_80126B58; \
        if (D_80126CBA != 0) { \
            return 0x7FFFFFFF; \
        } \
        return func_80013478(a0 + 4, (s32)p + 0x15C); \
    }

#define DEFINE_func_80146AB4() \
    extern s32 func_80146B9C(void *a0); \
    void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6) { \
        u8 sp[0x18]; \
        *(s16 *)(sp + 0x0) = a0; \
        *(s32 *)(sp + 0x8) = a1; \
        *(s16 *)(sp + 0x2) = a2; \
        *(s16 *)(sp + 0x4) = a3; \
        *(s16 *)(sp + 0x6) = a4; \
        *(s32 *)(sp + 0xC) = a5; \
        *(s32 *)(sp + 0x10) = a6; \
        func_80146B9C(sp); \
    }

#define DEFINE_func_8014A4B4() \
    extern s32 func_80029178(s32 a0); \
    s32 func_8014A4B4(void *a0) { \
        if ((func_80029178(0x1E) & 0xFF) != 0) { \
            u32 v = *(u16 *)((s32)a0 + 0xAC) & 0x40; \
            return v != 0; \
        } \
        return 0; \
    }

#define DEFINE_func_8014ACE8() \
    extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3); \
    void func_8014ACE8(void *a0, s32 a1, s32 a2) { \
        u16 sp[4]; \
        sp[0] = *(u16 *)((s32)a0 + 0x6); \
        sp[1] = *(u16 *)((s32)a0 + 0xA) - 0x20; \
        sp[2] = *(u16 *)((s32)a0 + 0xE); \
        func_8014AD30((s32)a0, sp, a1, a2); \
    }

#define DEFINE_func_8012A094() \
    extern void *memcpy(void *, const void *, unsigned int); \
    void func_8012A094(s32 a0) { \
        *(s32 *)(a0 + 0x8) = *(s32 *)(a0 + 0xC); \
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x14); \
        memcpy((void *)(a0 + 0x18), (void *)(a0 + 0x20), 8); \
        *(u16 *)(a0 + 0x28) = *(u16 *)(a0 + 0x2E); \
        *(u16 *)(a0 + 0x2A) = *(u16 *)(a0 + 0x30); \
        *(u16 *)(a0 + 0x2C) = *(u16 *)(a0 + 0x32); \
    }

#define DEFINE_func_80139634() \
    extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3); \
    void func_80139634(void *a0) { \
        s16 sp[4]; \
        sp[0] = *(u16 *)((u8 *)a0 + 0x38); \
        sp[1] = *(u16 *)((u8 *)a0 + 0x3A); \
        sp[2] = 0x38; \
        sp[3] = 0x30; \
        func_80059888(&sp[0], 0, 0, 0); \
    }

#define DEFINE_func_80162120() \
    extern s32 func_800291DC(s32); \
    extern s32 func_800D0D7C(s32, s32); \
    extern void func_800291C8(s32, s32); \
    void func_80162120(void) { \
        s32 v0; \
        if ((s16)func_800291DC(8) == 0) { \
            v0 = func_800D0D7C(0, 1); \
            func_800291C8(8, (s16)(v0 | 0x8000)); \
        } \
    }

#define DEFINE_func_8012A860() \
    extern int func_8012ACE0(void *a0); \
    extern void func_8012AAAC(void); \
    void func_8012A860(void *a0, int a1) { \
        int v0; \
        register char *p asm("$4"); \
        *(int *)((char *)a0 + 0x90) = a1; \
        v0 = func_8012ACE0(a0); \
        p = (char *)a0; \
        *(unsigned short *)(p + 0x72) = *(unsigned short *)(p + 0x72) | 0x200; \
        *(int *)(p + 0x94) = v0 - 1; \
        *(int *)(p + 0x9C) = 0; \
        *(short *)(p + 0x9A) = 0; \
        func_8012AAAC(); \
    }

#define DEFINE_func_8012E57C() \
    extern u8 D_801202A0[]; \
    s32 func_8012E57C(s32 a0, s32 a1) { \
        u8 *p = D_801202A0; \
        u8 *end = D_801202A0 + 0x6480; \
        if (p != end) { \
            s32 key = (s16)a1; \
            do { \
                if (*(u16 *)(p + 0x0) == a0) { \
                    if (*(s16 *)(p + 0x70) == key) { \
                        return (s32)p; \
                    } \
                } \
                p += 0x10C; \
            } while (p != end); \
        } \
        return 0; \
    }

#define DEFINE_func_80146D30() \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_80146D30(s32 a0) { \
        s32 *p = &D_80127090; \
        *(s32 *)(a0 + 0x10) = *p; \
        *(s32 *)(a0 + 0x14) = D_80127094; \
        *(s32 *)(a0 + 0x18) = D_80127098; \
        *p = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
    }

#define DEFINE_func_8014C0C8() \
    extern u8 D_801202A0[]; \
    s32 func_8014C0C8(s32 a0_unused, s32 a1, s32 a2) { \
        s32 i = 0; \
        s32 key = (s16)a2; \
        u8 *p = D_801202A0; \
        do { \
            if (*(u16 *)(p + 0x0) == a1) { \
                if (*(s16 *)(p + 0xFC) == key) { \
                    return (s32)p; \
                } \
            } \
            i += 1; \
            p += 0x10C; \
        } while ((u32)i < 0x60); \
        return 0; \
    }

#define DEFINE_func_8014C918() \
    extern u8 D_801151F0[]; \
    s32 func_8014C918(s32 a0, s32 a1) { \
        s32 v1; \
        s32 ret; \
        if (a1 == 0x18) { \
            return 0x8; \
        } \
        v1 = 0; \
        goto search; \
    found: \
        return ret; \
    search: \
        do { \
            ret = v1 & 0xFF; \
            if (D_801151F0[ret] == a1) { \
                goto found; \
            } \
            v1 += 1; \
        } while ((u32)(v1 & 0xFF) < 0x8); \
        return 0; \
    }

#define DEFINE_func_801552F4() \
    extern s32 D_800DE2A4[]; \
    void func_801552F4(s32 a0) { \
        s32 *p = D_800DE2A4; \
        s32 v0 = *p; \
        if (v0 != 0) { \
            do { \
                v0 &= 0x80FFFFFF; \
                *p = v0; \
                p += 1; \
                v0 = *p; \
            } while (v0 != 0); \
        } \
        *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) | 0x30000000; \
    }

#define DEFINE_func_80155344() \
    extern s32 D_800DE2A4[]; \
    void func_80155344(s32 a0) { \
        s32 *p = D_800DE2A4; \
        s32 v0 = *p; \
        if (v0 != 0) { \
            do { \
                v0 |= 0x1000000; \
                *p = v0; \
                p += 1; \
                v0 = *p; \
            } while (v0 != 0); \
        } \
        *(s32 *)(a0 + 0x44) = *(s32 *)(a0 + 0x44) & 0xCFFFFFFF; \
    }

#define DEFINE_func_8014A6C4() \
    extern s32 func_80029178(s32 a0); \
    s32 func_8014A6C4(s32 a0) { \
        s32 r; \
        if ((func_80029178(0x1F) & 0xFF) == 0) { \
            r = 0; \
        } else if (*(s32 *)(a0 + 0x44) & 0x4) { \
            r = 0; \
        } else { \
            r = *(u8 *)(a0 + 0x1BE) == 0; \
        } \
        return r; \
    }

#define DEFINE_func_8015AB7C() \
    extern u8 D_800D48DC; \
    s32 func_8015AB7C(s32 a0) { \
        u8 v1; \
        if (*(s32*)(a0 + 0xB4) == (s32)&D_800D48DC) { \
            v1 = *(u8*)(a0 + 0xDC); \
            if (v1 < 6) { \
                return 0x10; \
            } \
            if (v1 < 0xB) { \
                return 0x12; \
            } \
            if (v1 < 0x10) { \
                return 0x7; \
            } \
            return 0x9; \
        } \
        return *(u8*)(a0 + 0xBC); \
    }

#define DEFINE_func_801620C4() \
    extern int func_800291DC(int); \
    extern int func_800D0E30(void *a0); \
    int func_801620C4(void) { \
        short local; \
        int lo; \
        local = func_800291DC(8) & 0x7FFF; \
        local = func_800D0E30(&local); \
        lo = *(unsigned char *)&local; \
        return (short)(*((unsigned char *)&local + 1) * 100 + lo); \
    }

#define DEFINE_func_801626B8() \
    extern int func_800291DC(int); \
    extern int func_800D0E30(void *a0); \
    int func_801626B8(void) { \
        short local; \
        int lo; \
        local = func_800291DC(0x12) & 0x7FFF; \
        local = func_800D0E30(&local); \
        lo = *(unsigned char *)&local; \
        return (short)(*((unsigned char *)&local + 1) * 100 + lo); \
    }

#define DEFINE_func_801633A8() \
    extern s32 D_80115100; \
    extern s32 D_80115200; \
    s32 func_801633A8(void) { \
        s32 *p = &D_80115100; \
        s32 *q = &D_80115200; \
        s32 i; \
        for (i = 0; i < 3; i++) { \
            s32 v1 = q[i]; \
            if (v1 != 0) { \
                if ((*(u16*)(p[i] + 0x5C) & 0x400) == 0) { \
                    return v1; \
                } \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8017C230() \
    extern void func_80146C3C(void); \
    void func_8017C230(int a0) { \
        int v0 = *(int *)(a0 + 0x1C); \
        register unsigned char *p __asm__("$5") = *(unsigned char **)(a0 + 0x20); \
        *(int *)(a0 + 0x1C) = v0 + 1; \
        if (v0 >= 0x1F) { \
            func_80146C3C(); \
        } else { \
            unsigned short hv = *(unsigned short *)(p + 0x1A) + 0x1E0; \
            signed char bv = *(unsigned char *)(p + 0x26) - 3; \
            *(unsigned short *)(p + 0x1A) = hv; \
            *(unsigned short *)(p + 0x18) = hv; \
            *(signed char *)(p + 0x26) = bv; \
            *(signed char *)(p + 0x25) = bv; \
            *(signed char *)(p + 0x24) = bv; \
        } \
    }

#define DEFINE_func_80146CC8() \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_80146CC8(s32 a0) { \
        s32 *p = &D_80127090; \
        *(s32*)(a0 + 0x10) += *p; \
        *(s32*)(a0 + 0x14) += D_80127094; \
        *(s32*)(a0 + 0x18) += D_80127098; \
        *p = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
    }

#define DEFINE_func_801657D8() \
    extern s32 D_80078E94; \
    extern s32 D_80078E9C; \
    extern s32 D_80078EA0; \
    extern s32 D_80078EA4; \
    extern s32 D_80078EA8; \
    extern u8 D_80078EBB; \
    extern s32 D_80078ECC; \
    extern s32 D_80078ED0; \
    extern s32 D_80078ED4; \
    extern s32 D_80078ED8; \
    extern s32 D_80078EDC; \
    extern u8 D_80078EE0; \
    void func_801657D8(void) { \
        D_80078ECC = D_80078E94; \
        D_80078ED0 = D_80078E9C; \
        D_80078ED4 = D_80078EA0; \
        D_80078ED8 = D_80078EA4; \
        D_80078EDC = D_80078EA8; \
        D_80078EE0 = D_80078EBB; \
    }

#define DEFINE_func_80165874() \
    extern s32 D_80078ECC; \
    extern s32 D_80078ED0; \
    extern s32 D_80078ED4; \
    extern s32 D_80078ED8; \
    extern s32 D_80078EDC; \
    extern u8 D_80078EE0; \
    extern s32 D_80078E94; \
    extern s32 D_80078E9C; \
    extern s32 D_80078EA0; \
    extern s32 D_80078EA4; \
    extern s32 D_80078EA8; \
    extern u8 D_80078EBB; \
    void func_80165874(void) { \
        D_80078E94 = D_80078ECC; \
        D_80078E9C = D_80078ED0; \
        D_80078EA0 = D_80078ED4; \
        D_80078EA4 = D_80078ED8; \
        D_80078EA8 = D_80078EDC; \
        D_80078EBB = D_80078EE0; \
    }

#define DEFINE_func_8013001C() \
    extern s32 func_8012BCCC(s32 a0); \
    extern s32 func_80131AC8(void *a0); \
    void func_8013001C(void *a0) { \
        s32 v0 = func_8012BCCC((s32)a0); \
        if (v0 <= 0x8FFF) { \
            if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x30)) { \
                return; \
            } \
            ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x31); \
        } else { \
            if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x31)) { \
                return; \
            } \
            ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x30); \
        } \
    }

#define DEFINE_func_80130088() \
    extern s32 func_8012BCCC(s32 a0); \
    extern s32 func_80131AC8(void *a0); \
    void func_80130088(void *a0) { \
        s32 v0 = func_8012BCCC((s32)a0); \
        if (v0 <= 0x8FFF) { \
            if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32)) { \
                return; \
            } \
            ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33); \
        } else { \
            if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x33)) { \
                return; \
            } \
            ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x32); \
        } \
    }

#define DEFINE_func_80128564() \
    extern void func_80178608(void); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern s32 func_80011A3C(void); \
    extern short currentLocationId; \
    extern short D_800B99F2; \
    void func_80128564(void) { \
        register s32 p __asm__("$6") = 0x1F8003FC; \
        __asm__ __volatile__( \
            "addu  $8, %0, $zero\n" \
            "sw    $sp, 0($8)\n" \
            "addiu $8, $8, -4\n" \
            "addu  $sp, $8, $zero\n" \
            "jal   func_80178608\n" \
            "addiu $sp, $sp, 4\n" \
            "lw    $sp, 0($sp)\n" \
            : : "r"(p) : "$8", "memory"); \
        if (currentLocationId == 0x300A) { \
            func_8002D4C8(6, 0); \
        } \
        func_80011A3C(); \
        D_800B99F2 = 1; \
    }

#define DEFINE_func_801691B8() \
    extern s32 func_80169228(void); \
    extern void func_800D22E4(s32 a0); \
    extern void func_80146C3C(void); \
    void func_801691B8(void *a0) { \
        if (*(s32 *)((s32)a0 + 0x1C) < 10) { \
            func_80169228(); \
            func_800D22E4((s32)a0); \
            *(s32 *)((s32)a0 + 0x14) += 0x10000; \
            *(s32 *)((s32)a0 + 0x1C) += 1; \
        } else { \
            ((void (*)(s32))func_80146C3C)((s32)a0); \
        } \
    }

#define DEFINE_func_8016E2E8() \
    extern void func_8016E3CC(s32 a0); \
    extern void func_80146C3C(void); \
    void func_8016E2E8(void *a0) { \
        s32 *s1 = *(s32 **)((s32)a0 + 0x20); \
        func_8016E3CC((s32)a0); \
        if (--*(s32 *)((s32)a0 + 0x1C) != 0) { \
            *(u16 *)((s32)s1 + 0x18) -= 0x100; \
            *(u16 *)((s32)s1 + 0x1A) -= 0x120; \
        } else { \
            ((void (*)(s32))func_80146C3C)((s32)a0); \
        } \
    }

#define DEFINE_func_8016B984() \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_80146C3C(void); \
    void func_8016B984(void *a0) { \
        if (*(s32*)((s32)a0 + 0x10) != 0) { \
            func_80016714(*(void**)((s32)a0 + 0x10), 0x38); \
        } \
        if (*(s32*)((s32)a0 + 0x14) != 0) { \
            func_80016714(*(void**)((s32)a0 + 0x14), 0x38); \
        } \
        if (*(s32*)((s32)a0 + 0x18) != 0) { \
            func_80016714(*(void**)((s32)a0 + 0x18), 0x38); \
        } \
        ((void (*)(void *))func_80146C3C)(a0); \
    }

#define DEFINE_func_8016E358() \
    extern void func_800D22E4(s32 a0); \
    extern void func_8016E460(void *a0, void *a1); \
    extern void func_80146C3C(void); \
    void func_8016E358(void *a0) { \
        s32 v0; \
        v0 = *(s32*)((s32)a0 + 0x1C) - 1; \
        *(s32*)((s32)a0 + 0x1C) = v0; \
        if (v0 != 0) { \
            func_800D22E4((s32)a0); \
            *(s16*)((s32)a0 + 0x16) = *(u16*)((s32)a0 + 0x16) - 3; \
            *(s32*)((s32)a0 + 0x30) = *(s32*)((s32)a0 + 0x30) - 0xE; \
            func_8016E460(a0, (void*)((s32)a0 + 0x38)); \
        } else { \
            ((void (*)(void *))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_8014B6F0() \
    extern s32 D_80078E9C; \
    extern s32 D_80078ED0; \
    void func_8014B6F0(s32 a0, s32 a1) { \
        D_80078E9C += a1; \
        if (*(s16*)((s32)&D_80078E9C + 2) >= 0xA1) { \
            D_80078E9C = 0xA00000; \
        } \
        D_80078ED0 += a1; \
        if (*(s16*)((s32)&D_80078ED0 + 2) >= 0xA1) { \
            D_80078ED0 = 0xA00000; \
        } \
    }

#define DEFINE_func_8012BD3C() \
    extern s32 func_80013478(s32 a0, s32 a1); \
    extern s32 func_8012BDBC(s32 a0, s32 a1); \
    extern s16 D_80126CBA; \
    extern s16 D_80126CB4; \
    s32 func_8012BD3C(s32 a0, s32 a1, s32 a2) { \
        s32 v; \
        s32 hp; \
        hp = a1; \
        if (D_80126CBA != 0) { \
            v = 0x7FFFFFFF; \
        } else { \
            v = func_80013478(a0 + 4, (s32)&D_80126CB4); \
        } \
        if (a2 < v) { \
            return 0; \
        } \
        return func_8012BDBC(a0, (s16)hp); \
    }

#define DEFINE_func_8012CAE4() \
    extern void func_80016714(void *a0, s32 a1); \
    extern u16 D_801274E4[]; \
    void func_8012CAE4(void *a0) { \
        u16 *d; \
        void *p; \
        s32 t; \
        s32 a1; \
        d = D_801274E4; \
        *d |= 1; \
        p = *(void **)((s32)a0 + 0x20); \
        if (p != 0) { \
            t = *(u16 *)p; \
            if (t != 1) { \
                if (t != 2) { \
                    goto done; \
                } \
                a1 = 0x38; \
            } else { \
                a1 = 0x84; \
            } \
            func_80016714(p, a1); \
        done:; \
        } \
        func_80016714(a0, 0x10C); \
    }

#define DEFINE_func_801553C0() \
    extern s32 func_80029178(s32); \
    extern void func_8001D150(s32, s32); \
    void func_801553C0(s32 a0) { \
        s32 *flags; \
        flags = (s32 *)(a0 + 0x44); \
        if ((*flags & 4) != 0 || (func_80029178(0x12F) & 0xFF) != 0) { \
            *flags = *flags & 0xEFFFFFFF; \
        } else { \
            *flags = *flags | 0x10000000; \
        } \
        func_8001D150(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x24), 0x15); \
    }

#define DEFINE_func_8012CE2C() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    s32 func_8012CE2C(s32 a0) { \
        short a[4]; \
        short b[4]; \
        s32 pa, pb; \
        a[0] = *(u16 *)(a0 + 0x6); \
        a[1] = *(u16 *)(a0 + 0xA); \
        a[2] = *(u16 *)(a0 + 0xE); \
        pa = (s32)a; \
        pb = (s32)b; \
        __builtin_memcpy((void *)pb, (void *)pa, 8); \
        b[1] += 8; \
        func_80133784(1, a, pb); \
        return a[1] == b[1]; \
    }

#define DEFINE_func_80147DC0() \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    void func_80147DC0(s32 a0, s32 a1) { \
        s32 pad[4]; \
        s32 buf[8]; \
        s32 q = *(s32 *)(a0 + 0x20); \
        func_80013F3C((s32)buf); \
        func_800126C4((s32)buf, *(s16 *)(q + 0x10)); \
        func_80012558((s32)buf, *(s16 *)(q + 0x12)); \
        func_800123F0((s32)buf, *(s16 *)(q + 0x14)); \
        func_800484EC((s32)buf, a0 + 0x24, a1); \
    }

#define DEFINE_func_8016325C() \
    extern void func_80162F60(s32 arg0, s32 arg1); \
    extern void func_80162F80(s32 arg0, s32 arg1); \
    extern void func_80162FA0(s32 arg0, s32 arg1); \
    extern void func_80146D30(s32 a0); \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3) { \
        func_80162F60(a0, a1); \
        func_80162F80(a0, a2); \
        func_80162FA0(a0, a3); \
        D_80127090 = *(s32 *)(a0 + 0x24); \
        D_80127094 = *(s32 *)(a0 + 0x28); \
        D_80127098 = *(s32 *)(a0 + 0x2C); \
        func_80146D30(a0); \
    }

#define DEFINE_func_8013F1BC() \
    extern void func_800D2624(void); \
    extern short D_800B9A02; \
    extern unsigned short D_80115114; \
    extern unsigned short D_80115112; \
    extern unsigned short D_80115118; \
    void func_8013F1BC(void) { \
        unsigned short *p = &D_80115118; \
        if (*p != 0) { \
            *p -= 0x10; \
            __asm__ __volatile__("" ::: "memory"); \
            if (*p != 0) { \
                return; \
            } \
        } \
        if (D_80115114 == ((unsigned short)D_800B9A02 ^ 1)) { \
            func_800D2624(); \
        } else { \
            D_80115112 += 1; \
        } \
    }

#define DEFINE_func_8014CC28() \
    extern void func_8014D3E0(s32 a0); \
    extern void func_8014D04C(void); \
    extern void func_8014CCB4(void); \
    void func_8014CC28(s32 a0) { \
        if (*(s32 *)(a0 + 0x44) < 0) { \
            if (*(s16 *)(a0 + 0xA) != *(s16 *)(a0 + 0x8A)) { \
                func_8014D3E0(a0); \
                return; \
            } \
            if (*(s16 *)(a0 + 0x6) != *(s16 *)(a0 + 0x88) || \
                *(s16 *)(a0 + 0xE) != *(s16 *)(a0 + 0x8C)) { \
                func_8014D04C(); \
                return; \
            } \
        } \
        func_8014CCB4(); \
    }

#define DEFINE_func_801567BC() \
    extern u8 D_8011DAD8[]; \
    extern s32 D_801151E0[]; \
    extern s32 func_8014C568(void *a0); \
    void func_801567BC(s32 a0) { \
        s32 obj = a0; \
        s32 i = 0; \
        u8 *q = D_8011DAD8; \
        s32 *p = D_801151E0; \
        do { \
            if (*p & 1) { \
                *(s16 *)(*(s32 *)(obj + 0x20) + 0x12) = \
                    ((s32 (*)(void *, void *))func_8014C568)((void *)obj, q); \
            } \
            q += 8; \
            i += 1; \
            p += 1; \
        } while ((u32)i < 3); \
    }

#define DEFINE_func_80142454() \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    extern s32 func_8012C51C(void *a0, s32 a1); \
    void func_80142454(s32 a0) { \
        s32 s0 = a0; \
        u16 *s1 = &D_80126B5E; \
        s32 ret; \
        s16 st[10]; \
        st[3] = 0x13; \
        st[0] = *s1; \
        st[1] = D_80126B62; \
        st[2] = D_80126B66; \
        st[4] = 1; \
        st[5] = 0; \
        st[7] = 0; \
        *(s32 *)&st[8] = 0; \
        ret = ((s32 (*)(void *, s32))func_8012C51C)(st, 0); \
        if (ret != 0) { \
            *(s16 *)(ret + 0x52) = s0; \
            *(s32 *)(ret + 0x64) = (s32)s1 - 6; \
        } \
    }

#define DEFINE_func_801581AC() \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80161418(void *a0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern int func_80155FF8(int arg, int a1); \
    void func_801581AC(s32 a0) { \
        s32 reserved[4]; \
        (void)reserved; \
        *(s32 *)(a0 + 0x44) |= 2; \
        func_80148038(a0, 0x10000); \
        func_80147460(a0); \
        func_80147AD4(a0, 0, 0, 0); \
        func_801473EC((s32 *)a0); \
        { \
            register s32 ret __asm__("$2"); \
            func_80161418((void *)a0); \
            __asm__ __volatile__("" : "=r"(ret)); \
            if (ret != 0) { \
                return; \
            } \
        } \
        if (*(u16 *)(a0 + 0xB8) == 0x8000) { \
            func_801599A4((void *)a0); \
            func_80159B3C((void *)a0); \
        } else { \
            func_80155FF8(a0, *(u8 *)(a0 + 0x1AA)); \
        } \
    }

#define DEFINE_func_8016E1CC() \
    extern void func_8016E3CC(s32 a0); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_8016E1CC(s32 a0) { \
        s32 s1; \
        s32 v; \
        s1 = *(s32 *)(a0 + 0x20); \
        func_8016E3CC(a0); \
        v = *(s32 *)(a0 + 0x1C) - 1; \
        *(s32 *)(a0 + 0x1C) = v; \
        if (v != 0) { \
            func_80146A6C(0x48, (void *)a0, 0, 0, 0, 0x8000, 0); \
            *(s16 *)(s1 + 0x18) = *(u16 *)(s1 + 0x18) + 0x100; \
            *(s16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0x1A) + 0x140; \
            return; \
        } \
        *(s32 *)(a0 + 0x1C) = 0x20; \
        *(s16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1; \
    }

#define DEFINE_func_8013914C() \
    extern s32 func_80139220(s32 a0); \
    s32 func_8013914C(s32 a0, s32 a1) { \
        s32 t; \
        if ((s32)*(u16 *)(a0 + 0x14) >= *(s16 *)(a0 + 0x2C)) { \
            if (func_80139220(a0) != 0) { \
                return 1; \
            } \
        } \
        t = *(u16 *)(a0 + 0x14); \
        *(s16 *)(a1 + 0x0) = *(u16 *)(a0 + 0x38) + (((u32)(t * 3)) >> 1); \
        t = *(u16 *)(a0 + 0x12); \
        *(s16 *)(a1 + 0x2) = *(u16 *)(a0 + 0x3A) + ((t * 3) << 2); \
        *(s16 *)(a0 + 0x14) = *(u16 *)(a0 + 0x14) + 1; \
        return 0; \
    }

#define DEFINE_func_8013ED6C() \
    extern s32 func_80141C50(void); \
    extern s32 func_8013F350(void); /* §30#2 widened (discarding caller) */ \
    extern void func_8013FAF8(s16 a0, s16 a1); \
    extern void func_8013E958(void); \
    extern short D_800B9A02; \
    extern u8 D_801151C8[]; \
    extern s32 D_801151D0; \
    extern u16 D_8011511A; \
    extern u16 D_8011511E; \
    extern u16 D_80115112; \
    void func_8013ED6C(void) { \
        s32 sp10[2]; \
        if ((s16)func_80141C50() == 0) { \
            D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4]; \
            func_8013F350(); \
            func_8013FAF8(7, 8); \
            if (D_8011511A == 7) { \
                if ((D_8011511E & 0x810) == 0) { \
                    return; \
                } \
            } \
            func_8013E958(); \
            D_80115112 = 4; \
        } \
        (void)sp10; \
    }

#define DEFINE_func_801505FC() \
    extern u8 D_801202A0[]; \
    extern s32 func_8014C278(s32 a0, s32 a1, s32 a2); \
    extern s32 func_801506A4(s32 a0, s32 a1); \
    s32 func_801505FC(s32 a0) { \
        u8 *p = D_801202A0; \
        if (p < D_801202A0 + 0x6480) { \
            u8 *end = D_801202A0 + 0x6480; \
            do { \
                if (*(u16 *)(p + 0x0) != 0) { \
                    if (*(u16 *)(p + 0x5C) & 0x100) { \
                        if (func_8014C278(a0, (s32)p, 0x30) != 0) { \
                            func_801506A4(a0, (s32)p); \
                            return 1; \
                        } \
                    } \
                } \
                p += 0x10C; \
            } while (p < end); \
        } \
        return 0; \
    }

#define DEFINE_func_80149DD8() \
    extern u8 D_801202A0[]; \
    extern s32 func_80149F2C(s32 a0, s32 a1); \
    s32 func_80149DD8(s32 a0) { \
        u8 *p; \
        if (*(s32 *)(a0 + 0x178) != 0) { \
            return 0; \
        } \
        if (*(s32 *)(a0 + 0x44) & 0x404) { \
            return 0; \
        } \
        if ((*(u16 *)(a0 + 0xAC) & 0x80) == 0) { \
            return 0; \
        } \
        *(s32 *)(a0 + 0x190) = 0; \
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) { \
            if (func_80149F2C(a0, (s32)p) != 0) { \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8014E98C() \
    extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3); \
    s32 func_8014E98C(void *a0) { \
        s16 buf1[3]; \
        s16 buf2[4]; \
        s32 acc; \
        s32 i; \
        acc = 0; \
        i = 2; \
        if ((*(s32 *)((u8 *)a0 + 0x44) & 0x80000) == 0) { \
            if ((*(s32 *)((u8 *)a0 + 0x1F8) & 0x4000000) == 0) { \
                do { \
                    buf1[0] = *(u16 *)((u8 *)a0 + 0x88); \
                    i -= 1; \
                    buf1[1] = *(u16 *)((u8 *)a0 + 0x8A) - 0x10; \
                    buf1[2] = *(u16 *)((u8 *)a0 + 0x8C); \
                    buf2[0] = *(u16 *)((u8 *)a0 + 0x6); \
                    buf2[1] = *(u16 *)((u8 *)a0 + 0xA) - 0x10; \
                    buf2[2] = *(u16 *)((u8 *)a0 + 0xE); \
                    acc = acc | func_8014EA4C(a0, buf1, buf2, i); \
                } while (i != 0); \
            } \
        } \
        return acc; \
    }

#define DEFINE_func_801575E4() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80147324(s32 a0); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80156648(s32 *a0); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_8014B768(s32 a0, s32 a1); \
    extern void func_80147300(u16 arg0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_800D4F14[]; \
    extern s32 D_8011F730; \
    void func_801575E4(void *a0) { \
        s32 v; \
        func_80154A74((s32)a0, 0x15); \
        v = *(u8 *)((u8 *)a0 + 0x1AB) ^ 1; \
        *(u8 *)((u8 *)a0 + 0x1AB) = v; \
        if (v != 0) { \
            *(u8 *)((u8 *)a0 + 0x1AA) = 0xA; \
        } else { \
            *(u8 *)((u8 *)a0 + 0x1AA) = 0xB; \
        } \
        func_80154274((s32 *)a0, (s32)D_800D4F14); \
        func_80147324(0x455); \
        func_80146E90((s32 *)a0, 0); \
        func_80156648((s32 *)a0); \
        func_80146994(0x5, (s32)a0, 0, 0); \
        func_8014B768((s32)a0, 0x333); \
        func_80147300(0x5F3); \
        D_8011F730 |= 4; \
        func_80146CA0(a0); \
    }

#define DEFINE_func_8016BADC() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_8016BADC(void *a0, s32 a1, s32 a2) { \
        func_80146A6C(0x22, a0, 0, (s16)a1, 0, 0, a2); \
        func_80146A6C(0x22, a0, 0, (s16)a1, 0, 1, a2); \
        func_80146A6C(0x22, a0, 0, (s16)a1, 0, 2, a2); \
        func_80146A6C(0x24, a0, 0, (s16)a1, 0, 0, 0); \
    }

#define DEFINE_func_8012C354() \
    extern void func_8001CFDC(s32 a, s32 b); \
    extern void func_8012CAE4(void *a0); \
    extern void func_8001C214(s32 a0, s32 a1); \
    extern u8 D_80078EAE; \
    s32 func_8012C354(s32 a0, s32 a1) { \
        s32 v; \
        *(s32*)(a0 + 0x78) = a1; \
        if (D_80078EAE == 0) { \
            v = (*(s16*)(a1 + 0x0) * 24) / 16; \
        } else { \
            v = *(u16*)(a1 + 0x0); \
        } \
        *(s16*)(a0 + 0x76) = v; \
        *(s16*)(a0 + 0x5C) = *(u16*)(a1 + 0x2); \
        if (*(s32*)(a1 + 0x4) != 0) { \
            *(s32*)(a0 + 0x20) = ((s32 (*)(s32, s32))func_8001CFDC)(0x26, 0x85); \
            if (*(s32*)(a0 + 0x20) == 0) { \
                func_8012CAE4((void *)a0); \
                return 0; \
            } \
            func_8001C214(*(s32*)(a0 + 0x20), *(s32*)(a1 + 0x4)); \
        } \
        if (*(s32*)(a1 + 0x8) != 0) { \
            *(s32*)(a0 + 0x58) = *(s32*)(a1 + 0x8) | 0x60000000; \
        } \
        return 1; \
    }

#define DEFINE_func_8012C438() \
    extern void func_8001CFDC(s32 a, s32 b); \
    extern void func_8012CAE4(void *a0); \
    extern void func_8001C810(s32 a0, s32 a1); \
    extern u8 D_80078EAE; \
    s32 func_8012C438(s32 a0, s32 a1) { \
        s32 v; \
        *(s32*)(a0 + 0x78) = a1; \
        if (D_80078EAE == 0) { \
            v = (*(s16*)(a1 + 0x0) * 24) / 16; \
        } else { \
            v = *(u16*)(a1 + 0x0); \
        } \
        *(s16*)(a0 + 0x76) = v; \
        *(s16*)(a0 + 0x5C) = *(u16*)(a1 + 0x2); \
        if (*(s32*)(a1 + 0x4) != 0) { \
            *(s32*)(a0 + 0x20) = ((s32 (*)(s32, s32))func_8001CFDC)(0x26, 0x85); \
            if (*(s32*)(a0 + 0x20) == 0) { \
                func_8012CAE4((void *)a0); \
                return 0; \
            } \
            func_8001C810(*(s32*)(a0 + 0x20), *(s32*)(a1 + 0x4)); \
        } \
        if (*(s32*)(a1 + 0x8) != 0) { \
            *(s32*)(a0 + 0x58) = *(s32*)(a1 + 0x8) | 0x60000000; \
        } \
        return 1; \
    }

#define DEFINE_func_8014FA70() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern s32 func_80029178(s32 a0); \
    extern u8 D_801152A8[]; \
    extern s16 D_801152B0; \
    extern s32 D_801152BC; \
    s32 func_8014FA70(s32 a0) { \
        s32 s1; \
        s32 v0; \
        u8 in[8]; \
        u8 out[8]; \
        *(s16 *)(in + 0x0) = *(u16 *)(a0 + 0x88); \
        *(s16 *)(in + 0x2) = *(u16 *)(a0 + 0x8A); \
        *(s16 *)(in + 0x4) = *(u16 *)(a0 + 0x8C); \
        *(s16 *)(out + 0x0) = *(u16 *)(a0 + 0x6); \
        *(s16 *)(out + 0x2) = *(u16 *)(a0 + 0xA); \
        *(s16 *)(out + 0x4) = *(u16 *)(a0 + 0xE); \
        s1 = func_80133784(1, &in[0], (s32)&out[0]); \
        if (s1 != 0) { \
            *(s16 *)(a0 + 0x6) = *(u16 *)(out + 0x0); \
            *(s16 *)(a0 + 0xA) = *(u16 *)(out + 0x2); \
            *(s16 *)(a0 + 0xE) = *(u16 *)(out + 0x4); \
            v0 = *(u8 *)(out + 0x6); \
            if (v0 != 0) { \
                *(s16 *)(a0 + 0x16C) = v0; \
            } \
            *(s16 *)(a0 + 0x16E) = *(u16 *)(out + 0x6) >> 13; \
            if (*(u16 *)(a0 + 0x16C) == 0x1D) { \
                if ((func_80029178(0x21) & 0xFF) == 0) { \
                    s1 &= ~0x2000; \
                    s1 |= 0x4000; \
                    __builtin_memcpy(&D_801152B0, &D_801152A8[0], 8); \
                    D_801152BC = 1; \
                } \
            } \
            return s1; \
        } \
        v0 = *(u8 *)(out + 0x6); \
        if (v0 != 0) { \
            *(s16 *)(a0 + 0x16C) = v0; \
        } \
        return 0; \
    }

#define DEFINE_func_80172170() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80047948(s32 a0); \
    extern s32 func_8004787C(s32 a0); \
    extern s32 D_801151D4; \
    void func_80172170(s32 a0, s32 a1) { \
        s32 base = D_801151D4; \
        s32 s0; \
        s32 s1; \
        s32 v1; \
        s32 s3 = a1; \
        s32 ang; \
        *(s8 *)(a0 + 0xA9) = 0x73; \
        ang = ratan2(*(s32 *)(base + 0x68) - *(s32 *)(base + 0x5C), \
                     *(s32 *)(base + 0x70) - *(s32 *)(base + 0x64)); \
        s0 = (ang + 0x800) & 0xFFF; \
        s0 = (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) - s0) & 0xFF8; \
        if (s0 == 0x400 || s0 == 0xC00) { \
            s1 = 0x80; \
        } else { \
            s32 t = -((s3 & 0xFF) >> 1) * func_80047948(s0); \
            if (t < 0) { \
                t += 0xFFF; \
            } \
            s1 = (t >> 12) + 0x80; \
        } \
        if (s1 < 0) { \
            s1 = 0; \
        } \
        if (!(s1 < 0x100)) { \
            s1 = 0xFF; \
        } \
        if (s0 == 0 || s0 == 0x800) { \
            v1 = 0x80; \
        } else { \
            s32 t = ((s3 & 0xFF) >> 1) * func_8004787C(s0); \
            if (t < 0) { \
                t += 0xFFF; \
            } \
            v1 = (t >> 12) + 0x80; \
        } \
        if (v1 < 0) { \
            v1 = 0; \
        } \
        if (!(v1 < 0x100)) { \
            v1 = 0xFF; \
        } \
        *(s16 *)(a0 + 0xAE) = (v1 & 0xFF) | (s1 << 8); \
    }

#define DEFINE_func_8014BCC0() \
    extern s16 D_80078EB4; \
    void func_8014BCC0(s32 a0, s32 a1) { \
        s32 v1 = (u16)D_80078EB4; \
        if (a1 < v1) { \
            D_80078EB4 = v1 - a1; \
        } else { \
            D_80078EB4 = 1; \
        } \
    }

#define DEFINE_func_8014B160() \
    extern void func_8014B2F8(void); \
    extern void func_8014B4C4(void); \
    void func_8014B160(s32 a0) { \
        func_8014B2F8(); \
        ((void (*)(s32))func_8014B4C4)(a0); \
    }

#define DEFINE_func_80174318() \
    extern void func_80142454(s32 a0); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_80174318(u8 *a0) { \
        func_80142454(-0x80); \
        func_80171A1C(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_8015B8F8() \
    extern void func_801542DC(s32 *a0, s32 a1); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern s32 D_800D4A9C; \
    extern s32 D_800D4B48; \
    void func_8015B8F8(s32 *a0) { \
        s32 v = *(s32 *)((s32)a0 + 0x23C); \
        if (v == (s32)&D_800D4A9C || v == (s32)&D_800D4B48) { \
            ((void (*)(s32 *, s32, s32))func_801542DC)(a0, v, *(u8 *)((s32)a0 + 0x244)); \
        } else { \
            func_80154150((s32)a0, 0xF); \
        } \
    }

#define DEFINE_func_80161B84() \
    extern s32 func_80149884(void); \
    extern void func_801599A4(void *a0); \
    extern void func_801498C0(void); \
    s32 func_80161B84(void *a0) { \
        if ((((s32 *)a0)[0x11] & 0x100) != 0) { \
            if (func_80149884() != 0) { \
                func_801599A4(a0); \
                (*(void (*)(void *))func_801498C0)(a0); \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80168EC4() \
    extern void func_80168F40(); \
    extern void func_800D22E4(s32 a0); \
    extern void func_80146C3C(void); \
    void func_80168EC4(s32 a0) { \
        if (*(s32 *)(a0 + 0x1C) < 5) { \
            func_80168F40(); \
            *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x6); \
            *(u16 *)(a0 + 0x14) = *(u16 *)(a0 + 0xA); \
            *(u16 *)(a0 + 0x18) = *(u16 *)(a0 + 0xE); \
            func_800D22E4(a0); \
            *(s32 *)(a0 + 0x1C) += 1; \
        } else { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_80172BC8() \
    extern s32 func_80012B04(s32 a0, s32 a1, s32 a2); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B32; \
    void func_80172BC8(void *a0) { \
        s32 v0p = *(s32 *)((s32)a0 + 0x20); \
        s32 r = func_80012B04(*(s16 *)(v0p + 0x12), D_80126B32, 4); \
        s32 v1; \
        if (((r << 16) >> 16) == 0) { \
            func_80171A1C((u8 *)a0); \
            func_80174650((s32)a0); \
        } \
        v1 = *(s32 *)((s32)a0 + 0x20); \
        *(s16 *)(v1 + 0x12) = (*(u16 *)(v1 + 0x12) + r) & 0xFFF; \
    }

#define DEFINE_func_80151FB4() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80151FB4(s32 a0) { \
        s32 v1; \
        func_8014BC44(a0, *(s16 *)(a0 + 0xF2)); \
        *(u8 *)(a0 + 0xA8) = 0x20; \
        func_80154A74(a0, 0x11); \
        func_801553C0(a0); \
        func_801470AC((s32 *)a0); \
        func_801472B4((void *)a0); \
        v1 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(a0 + 0x3E) = 0; \
        *(s16 *)(a0 + 0x40) = 0; \
        *(s16 *)(a0 + 0x42) = 0; \
        *(u8 *)(a0 + 0xDD) = 0; \
        *(u16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE; \
        *(s16 *)(v1 + 0x10) = 0; \
        *(u16 *)(a0 + 0x60) = 0x1000; \
        *(u16 *)(a0 + 0x62) = 0x1000; \
        *(u16 *)(a0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)a0, 0); \
        func_80153C18(a0); \
    }

#define DEFINE_func_8014B084() \
    extern u16 D_80078EAC; \
    extern u8 D_80078EBA; \
    extern void func_800D10EC(void); \
    extern void func_8002AC98(void); \
    extern void func_80145C54(void); \
    void func_8014B084(void) { \
        u16 a; \
        u8 b; \
        a = D_80078EAC + 1; \
        b = D_80078EBA + 1; \
        D_80078EAC = a; \
        D_80078EBA = b; \
        if (a >= 0x16E) { \
            D_80078EAC = 1; \
        } \
        D_80078EBA = b % 7; \
        func_800D10EC(); \
        func_8002AC98(); \
        func_80145C54(); \
    }

#define DEFINE_func_80149744() \
    extern u8 D_80078EBF; \
    s32 func_80149744(struct S_80149744 *a0) { \
        if ((a0->w44 & 0x4) == 0 && D_80078EBF >= 0x80) { \
            if (a0->h_AC & 0x80) { \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8014A3E0() \
    extern s16 D_801152B0; \
    extern s16 D_801152B4; \
    s32 func_8014A3E0(struct S_8014A3E0 *a0) { \
        s32 sp[4]; \
        sp[0] = a0->h12 * D_801152B0; \
        sp[2] = a0->h1A * D_801152B4; \
        if (sp[0] >= 0 && sp[2] >= 0) { \
            return 1; \
        } \
        *(s16 *)((char *)a0 + 0x6) = a0->h88; \
        *(s16 *)((char *)a0 + 0xA) = a0->h8A; \
        *(s16 *)((char *)a0 + 0xE) = a0->h8C; \
        return 0; \
    }

#define DEFINE_func_80163328() \
    extern s32 D_80115100; \
    extern u16 D_80126B18[]; \
    extern s32 D_80115200; \
    void func_80163328(void) { \
        u32 i; \
        s32 *table; \
        u16 *src; \
        s32 *flags; \
        i = 0; \
        table = &D_80115100; \
        src = D_80126B18; \
        flags = &D_80115200; \
        do { \
            if (*flags & 1) { \
                u8 *dst = (u8 *)*table; \
                *(struct Vec4s *)(dst + 0x7C) = *(struct Vec4s *)src; \
                *(s16 *)((u8 *)*table + 0x82) = 0; \
            } \
            table += 1; \
            src += 4; \
            i += 1; \
            flags += 1; \
        } while (i < 3); \
    }

#define DEFINE_func_8013A164() \
    extern s16 D_8012752C; \
    void func_8013A164(struct S8013A164 *a0) { \
        s32 flags; \
        if (a0->field_40 == 0 || a0->field_18 == 0 || *a0->field_40 == 2) { \
            flags = a0->field_08 | 0x1000; \
            a0->field_08 = flags; \
            if (flags & 0x10000) { \
                if (D_8012752C != 0) { \
                    if (flags & 0x40000) { \
                        a0->field_04 = 2; \
                    } else { \
                        a0->field_04 = 0x10; \
                    } \
                } else { \
                    a0->field_04 = 2; \
                } \
            } else { \
                a0->field_04 = 2; \
            } \
        } \
    }

#define DEFINE_func_8014BDE8() \
    extern s32 func_8016F1AC(void); \
    extern s32 func_8017267C(s32 *a0); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80013294(void *a0, void *a1); \
    extern void func_80029ED4(s32 a0); \
    void func_8014BDE8(s32 a0) { \
        s32 s0 = a0; \
        struct B8014 sp10; \
        s16 sp18[4]; \
        if (func_8016F1AC() != 0) { \
            return; \
        } \
        if (func_8017267C((s32 *)s0) != 0) { \
            return; \
        } \
        sp10 = *(struct B8014 *)(s0 + 0x98); \
        func_80015978(s0 + 4, (s32 *)sp18); \
        sp18[1] = 0; \
        *(s16 *)((s32)&sp10 + 0x2) = 0; \
        func_80029ED4((func_80013294(&sp10, sp18) << 16) >> 16); \
    }

#define DEFINE_func_8012A4BC() \
    extern s32 D_801151D4; \
    extern struct BigCopy D_80126DB8; \
    extern struct BigCopy D_80114EE8; \
    extern u8 D_80127504; \
    void func_8012A4BC(void) { \
        D_80126DB8 = *(struct BigCopy *)D_801151D4; \
        *(struct BigCopy *)D_801151D4 = D_80114EE8; \
        D_80127504 = 0x30; \
    }

#define DEFINE_func_80150EC4() \
    extern u8 D_800AE6C0; \
    extern s16 D_800AE6C8; \
    extern s16 D_800AE6CA; \
    extern u8 D_80126948[]; \
    extern s16 D_800AE6CC; \
    extern s32 D_800AE6C4; \
    extern s16 D_800AE6CE; \
    extern u8 D_800AE6BE; \
    extern s32 D_800AE6B0; \
    extern u8 D_801201F8[]; \
    void func_80150EC4(s32 a0, s32 a1) { \
        D_800AE6C0 = 1; \
        D_800AE6C8 = *(u16 *)(a0 + 0x6); \
        D_800AE6CA = *(u16 *)(a0 + 0xA); \
        D_800AE6CC = *(u16 *)(a0 + 0xE); \
        D_800AE6CE = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12); \
        D_800AE6B0 = *(s32 *)(((a1 << 2) + D_800AE6C4) + 4); \
        D_800AE6BE = a1 + 1; \
        *(struct copy00 *)D_801201F8 = *(struct copy00 *)D_80126948; \
    }

#define DEFINE_func_8013A0A4() \
    extern void func_80139A8C(s32 a0); \
    extern void func_80139B18(s32 a0); \
    void func_8013A0A4(struct S8013A0A4 *a0) { \
        if (a0->field_1E != 0) { \
            a0->field_1E = a0->field_1E + 5; \
        } else { \
            a0->field_1E = 4; \
        } \
        if (a0->field_1E >= 0xC) { \
            a0->field_16 = (a0->field_16 + 1) % (a0->field_2E + 1); \
            a0->field_1E = 0; \
            if (a0->field_8 & 0x100) { \
                a0->field_4 = 6; \
            } else { \
                a0->field_4 = 2; \
            } \
        } \
        func_80139A8C((s32)a0); \
        func_80139B18((s32)a0); \
    }

#define DEFINE_func_80147060() \
    void func_80147060(u8 * a0) \
    { \
        s32 v = 1; \
        a0[0x4D] = v; \
        return v; \
    }

#define DEFINE_func_8014CB68() \
    extern u8 D_80126D1D; \
    void func_8014CB68(void) \
    { \
        D_80126D1D = 1; \
    }

#define DEFINE_func_80153C30() \
    extern u16 D_8011F748; \
    void func_80153C30(void) \
    { \
        D_8011F748 = 1; \
    }

#define DEFINE_func_80155394() \
    s32 func_80155394(s32 *a0) \
    { \
        return (a0[0x11] |= 0x20000000); \
    }

#define DEFINE_func_80162ACC() \
    s32 func_80162ACC(u8 *a0) \
    { \
        s32 v = a0[1] + 1; \
        a0[1] = v; \
        return v; \
    }

#define DEFINE_func_80162AE0() \
    s32 func_80162AE0(u8 *a0) \
    { \
        s32 v = a0[1] - 1; \
        a0[1] = v; \
        return v; \
    }

#define DEFINE_func_801659B8() \
    extern s32 D_80126B08; \
    void func_801659B8(void) \
    { \
        D_80126B08 = 1; \
    }

#define DEFINE_func_8016F250() \
    extern u8 D_80126D1A; \
    void func_8016F250(void) \
    { \
        D_80126D1A = 1; \
    }

#define DEFINE_func_8016F374() \
    extern u8 D_800B9A17; \
    void func_8016F374(void) \
    { \
        D_800B9A17 = 1; \
    }

#define DEFINE_func_8017197C() \
    s32 func_8017197C(u8 *a0) \
    { \
        s32 v = a0[0x215] + 1; \
        a0[0x216] = 0; \
        a0[0x215] = v; \
        return v; \
    }

#define DEFINE_func_80171990() \
    s32 func_80171990(u8 *a0) \
    { \
        s32 v = a0[0x216] + 1; \
        a0[0x216] = v; \
        return v; \
    }

#define DEFINE_func_80171A44() \
    s32 func_80171A44(u8 *a0) \
    { \
        s32 v = a0[0x215] + 1; \
        a0[0x216] = 0; \
        a0[0x215] = v; \
        return v; \
    }

#define DEFINE_func_80146D90() \
    extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3); \
    void func_80146D90(s32 a0) \
    { \
        func_80146DE8(a0, 0, 0, 0); \
    }

#define DEFINE_func_80165910() \
    extern s8 D_80078EC4; \
    s32 func_80165910(void) \
    { \
        s32 v; \
        s32 ret; \
        v = (u8)D_80078EC4; \
        ret = v; \
        if (v == 0) { \
            register s32 one __asm__("$2"); \
            one = 1; \
            __asm__ __volatile__("" : "=r"(one) : "0"(one)); \
            D_80078EC4 = one; \
        } \
        return ret; \
    }

#define DEFINE_func_80151204() \
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
    int func_80151204(int a0, int a1) \
    { \
        if (a1 != 0 && a1 != 1000) { \
            func_8014ACE8(a0, 1, a1 & 0x7FFF); \
        } \
    }

#define DEFINE_func_80159B3C() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80159B70(void *a0); \
    void func_80159B3C(void * a0) \
    { \
        func_80147078(a0, 0); \
        func_80159B70(a0); \
    }

#define DEFINE_func_8017118C() \
    extern void func_80142454(s32 a0); \
    extern void func_80171928(void *a0); \
    void func_8017118C(u8 * a0) \
    { \
        func_80142454(-0x80); \
        func_80171928(a0); \
    }

#define DEFINE_func_8012A828() \
    extern void func_8012AAAC(void); \
    void func_8012A828(s32 a0, void * a1) \
    { \
        *(s32 *)((u8 *)a0 + 0x90) = a1; \
        *(s32 *)((u8 *)a0 + 0x94) = 0; \
        *(s32 *)((u8 *)a0 + 0x9C) = 0; \
        *(s16 *)((u8 *)a0 + 0x9A) = 0; \
        *(u16 *)((u8 *)a0 + 0x72) = *(u16 *)((u8 *)a0 + 0x72) & 0xF9FF; \
        func_8012AAAC(); \
    }

#define DEFINE_func_8014BCEC() \
    extern u16 D_80078EB6; \
    s32 func_8014BCEC(s32 a0, s32 a1) \
    { \
        u16 v; \
        v = D_80078EB6 + a1; \
        D_80078EB6 = v; \
        if (v >= 0x663) { \
            D_80078EB6 = 0x662; \
        } \
    }

#define DEFINE_func_8014CB9C() \
    extern struct Packed8 D_80126C98; \
    extern short D_80126C9E; \
    void func_8014CB9C(struct Packed8 *a0) \
    { \
        D_80126C98 = *a0; \
        D_80126C9E = 1; \
    }

#define DEFINE_func_8017303C() \
    extern void func_80174684(void *); \
    extern s32 func_80173078(void *a0); \
    extern s32 D_80127508; \
    extern s16 D_80126B30; \
    void func_8017303C(void * a0) \
    { \
        D_80127508 = a0; \
        D_80126B30 = 1; \
        func_80174684((void *)func_80173078); \
    }

#define DEFINE_func_80154150() \
    extern void func_80154190(u8 *a0, s32 a1); \
    void func_80154150(s32 a0, s32 a1) \
    { \
        if (*(s32 *)(a0 + 0xB4) != ((s32 *)*(s32 *)(a0 + 0xB0))[a1]) { \
            func_80154190(a0, a1); \
        } \
    }

#define DEFINE_func_801743F0() \
    extern s32 func_80172658(s32 *a0); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_801743F0(u8 * a0) \
    { \
        if (func_80172658(a0)) { \
            func_80171A1C((u8 *)a0); \
            func_80174650((s32)a0); \
        } \
    }

#define DEFINE_func_80147B18() \
    extern void func_80147D38(s32 a0, s32 a1, s32 a2, s32 a3, void *a4); \
    extern void func_80147B5C(s32 a0, void *a1); \
    void func_80147B18(s32 a0) \
    { \
        s32 buf[4]; \
        s32 b0, b1, b2; \
        func_80147D38(a0, b0, b1, b2, &buf[0]); \
        func_80147B5C(a0, &buf[0]); \
    }

#define DEFINE_func_801508B4() \
    extern s32 func_8014A2E4(s32 a0); \
    extern void func_8014A380(s32 a0, s32 a1); \
    s32 func_801508B4(s32 a0) \
    { \
        s32 r; \
        r = func_8014A2E4(a0); \
        if (r != 0) { \
            func_8014A380(a0, r); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8015173C() \
    extern void func_8014C8F0(s32 arg0); \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_80151780(s32 a0); \
    void func_8015173C(s32 *a0) \
    { \
        func_8014C8F0((s32)a0); \
        *((u8 *)a0 + 0xDE) = *(u16 *)a0; \
        func_80147078(a0, 0x19); \
        func_80151780((s32)a0); \
    }

#define DEFINE_func_8015BD8C() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015BD8C(s32 *a0) \
    { \
        func_801553A8(a0); \
        func_80154A74((s32)a0, 0x11); \
        *(s32 *)((u8 *)a0 + 0x44) &= ~2; \
    }

#define DEFINE_func_8015BF04() \
    extern void func_801553A8(s32 *a0); \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015BF04(s32 *a0) \
    { \
        func_801553A8(a0); \
        func_80154A74((s32)a0, 0x11); \
        *(s32 *)((u8 *)a0 + 0x44) &= ~2; \
    }

#define DEFINE_func_8015BFB0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015C030(s32 *a0, s32 a1); \
    void func_8015BFB0(s32 *a0, s32 a1) \
    { \
        func_80147078(a0, 0x4); \
        func_8015C030(a0, a1); \
    }

#define DEFINE_func_80172D68() \
    extern s32 D_80126B58; \
    extern s32 D_80127508; \
    extern s32 func_80172DAC(void *a0); \
    extern s32 func_8014C168(s32 *a0, s32 a1); \
    extern void func_80174684(void *); \
    void func_80172D68(s32 a0) \
    { \
        D_80127508 = func_8014C168(&D_80126B58, a0); \
        func_80174684(func_80172DAC); \
    }

#define DEFINE_func_8012C284() \
    extern u8 D_80126720[]; \
    u16 *func_8012C284(u16 *a0) \
    { \
        u16 *end; \
        end = (u16 *)D_80126720; \
        if (a0 == 0) { \
            a0 = (u16 *)(D_80126720 - 0x6480); \
        } else { \
            a0 = (u16 *)((u8 *)a0 + 0x10C); \
        } \
        while (a0 != end) { \
            if (*a0 == 0) { \
                return a0; \
            } \
            a0 = (u16 *)((u8 *)a0 + 0x10C); \
        } \
        return 0; \
    }

#define DEFINE_func_8016FE2C() \
    extern s32 func_80172658(s32 *a0); \
    extern s32 func_80171990(u8 *a0); \
    void func_8016FE2C(u8 * a0) \
    { \
        if (func_80172658(a0) != 0) { \
            *(u16 *)((char *)a0 + 0xAC) |= 0x40; \
            *(u16 *)((char *)a0 + 0xAA) |= 0x40; \
            func_80171990((u8 *)a0); \
        } \
    }

#define DEFINE_func_80172D14() \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B30; \
    void func_80172D14(u8 * a0) \
    { \
        if (func_80171AB0(a0, &D_80126B30) == 0) { \
            func_80171A1C((u8 *)a0); \
            func_80174650(a0); \
        } \
    }

#define DEFINE_func_8014B034() \
    extern void func_8014B084(void); \
    extern s16 D_80078E90; \
    void func_8014B034(s32 a0) \
    { \
        register s16 *ptr = &D_80078E90; \
        s16 v; \
        v = ptr[1] + a0; \
        ptr[1] = v; \
        if (v >= 0x5A0) { \
            ptr[1] = v - 0x5A0; \
            func_8014B084(); \
        } \
    }

#define DEFINE_func_80152BF0() \
    extern s32 D_80062C14; \
    extern void func_80019064(void *a0); \
    extern int func_80151204(int arg, int a1); \
    extern void func_80149020(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    void func_80152BF0(s32 a0) \
    { \
        func_80019064(&D_80062C14); \
        func_80151204((int)a0, *(s16 *)((s32)a0 + 0xF2)); \
        func_80149020((s32 *)a0); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80172958() \
    extern s32 func_80171D1C(void *a0, void *a1, s32 a2); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    extern s16 D_80126B36; \
    extern s16 D_80126B30; \
    void func_80172958(u8 * a0) \
    { \
        if (func_80171D1C(a0, &D_80126B30, *(u8 *)&D_80126B36)) { \
            func_80171A1C(a0); \
            func_80174650((s32)a0); \
        } \
    }

#define DEFINE_func_801508F8() \
    extern s32 func_8015094C(s32 a0); \
    short func_801508F8(s32 a0) \
    { \
      if ((*((u8 *) (a0 + 0x1BF))) != 0) \
      { \
        if ((*((u16 *) a0)) != 0x1A) \
        { \
          while (func_8015094C(a0) != 0) \
          { \
            ; \
          } \
        } \
      } \
    }

#define DEFINE_func_80171CC4() \
    extern s32 func_80171D78(s32 a0, s32 a1); \
    extern int func_8017250C(short *a0, short *a1); \
    extern void func_80146D90(s32 a0); \
    s32 func_80171CC4(void * a0, void * a1) \
    { \
        s32 ret; \
        ret = func_80171D78(a0, a1); \
        if (func_8017250C(a0, a1) != 0) { \
            func_80146D90((s32)a0); \
        } \
        return ret; \
    }

#define DEFINE_func_80171D1C() \
    extern s32 func_80171FFC(short *a0, short *a1, s32 a2); \
    extern int func_8017250C(short *a0, short *a1); \
    extern void func_80146D90(s32 a0); \
    s32 func_80171D1C(void * a0, void * a1, s32 a2) \
    { \
        s32 ret; \
        ret = func_80171FFC(a0, a1, a2 & 0xFF); \
        if (func_8017250C(a0, a1) != 0) { \
            func_80146D90((s32)a0); \
        } \
        return ret; \
    }

#define DEFINE_func_801665B4() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80146C3C(); \
    extern void func_800D22E4(s32 a0); \
    void func_801665B4(s32 *a0) \
    { \
        if (func_80128ED8((void *)a0[8], (void *)(a0 + 9))) { \
            func_80146C3C((s32)a0); \
        } else { \
            func_800D22E4((s32)a0); \
            a0[5] -= a0[5] >> 3; \
        } \
    }

#define DEFINE_func_8017044C() \
    extern s32 D_801151D4; \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_80171928(void *a0); \
    void func_8017044C(u8 * a0) \
    { \
        s16 buf[3]; \
        s32 *p; \
        p = (s32 *)D_801151D4; \
        buf[0] = (s16)p[0xF];   /* 0x3C */ \
        buf[1] = (s16)p[0x10];  /* 0x40 */ \
        buf[2] = (s16)p[0x11];  /* 0x44 */ \
        if (func_80171AB0(a0, buf) == 0) { \
            func_80171928((void *)a0); \
        } \
    }

#define DEFINE_func_801533A4() \
    extern s32 func_801472C8(struct S *a0); \
    extern void func_8014CBF8(void *a0); \
    extern void func_801474EC(s32 *a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_80062C04[]; \
    void func_801533A4(s32 a0) \
    { \
        func_80019064(D_80062C04); \
        func_80149020(a0); \
        func_801472C8((struct S *)a0); \
        *((u8 *)a0 + 0xDE) = 0x40; \
        func_8014CBF8(a0); \
        func_801474EC(a0); \
        func_80155440(a0); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80157E38() \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80147324(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_800D4F14[]; \
    void func_80157E38(void * a0) \
    { \
        *((u8 *)a0 + 0x1AA) = 0xD; \
        func_80154274(a0, (s32)D_800D4F14); \
        func_80154A74((s32)a0, 0x15); \
        func_80146994(5, (s32)a0, 0, 0); \
        func_80147324(0x455); \
        *(s16 *)((u8 *)a0 + 0x244) = 0; \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_8015D57C() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_801553A8(s32 *a0); \
    extern void func_80155440(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    extern void func_801746DC(void); \
    void func_8015D57C(s32 arg0) \
    { \
        s16 *p; \
        func_80154150((s32)arg0, 0x19); \
        func_801553A8(arg0); \
        func_80155440(arg0); \
        func_80146CA0(arg0); \
        *(s32 *)((s8 *)arg0 + 0x234) = 0; \
        p = *(s16 **)((s8 *)arg0 + 0x178); \
        if (p != 0) { \
            if (*(u16 *)p == 0x1F8) { \
                *(s16 *)((s8 *)p + 0xFC) = 1; \
                func_801746DC(); \
            } \
        } \
    }

#define DEFINE_func_80170374() \
    extern s32 func_8014C168(s32 *a0, s32 a1); \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_80170374(u8 * a0) \
    { \
        s16 sp[4]; \
        s32 v0; \
        v0 = func_8014C168(a0, (s32)D_8011F738); \
        sp[0] = *(u16 *)(v0 + 0x6); \
        sp[1] = *(u16 *)(v0 + 0xA); \
        sp[2] = *(u16 *)(v0 + 0xE); \
        if (func_80171AB0((s32)a0, sp) == 0) { \
            func_80171928(a0); \
        } \
    }

#define DEFINE_func_8013B204() \
    extern void func_8013B274(s32 a0, s32 a1, void *a2); \
    extern short D_800B9A02; \
    extern s32 D_800A651C; \
    void func_8013B204(s32 a0, s32 a1) \
    { \
        void *a2; \
        s32 idx; \
        a2 = a1; \
        if (*(s16 *)((u8 *)a2 + 0xC) != 0) { \
            return; \
        } \
        if (*(s16 *)a2 != 2) { \
            return; \
        } \
        a2 = (u8 *)a2 + 8; \
        idx = (u16)D_800B9A02; \
        func_8013B274( \
            (&D_800A651C)[idx * 5] + ((u16)(*(u16 *)((u8 *)a0 + 0x1A)) << 2), \
            *(s16 *)((u8 *)a0 + 0x1C), \
            a2); \
    }

#define DEFINE_func_8014C43C() \
    extern u16 func_80156370(u16 a0); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4) \
    { \
        u16 v0; \
        v0 = func_80156370((u16)a2); \
        func_8014C4AC(a1, a2, v0 & 0xFFFF, a3, (s16)a4); \
    }

#define DEFINE_func_801701C8() \
    extern s32 func_80012B04(s32 a0, s32 a1, s32 a2); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    void func_801701C8(u8 * a0) \
    { \
        s16 *p; \
        s32 r; \
        r = func_80012B04(((s16 **)a0)[8][9], *(s16 *)&D_8011F738, 4); \
        if ((s16)r == 0) { \
            func_80171928(a0); \
        } \
        p = ((s16 **)a0)[8]; \
        ((u16 *)p)[9] = (((u16 *)p)[9] + r) & 0xFFF; \
    }

#define DEFINE_func_8015E0D4() \
    int func_8015E0D4(int a0) \
    { \
        s16 sp18[4]; \
        s32 s0; \
        s0 = *(s32 *)(a0 + 0x178); \
        if (s0 != 0) { \
            func_8014C1A0(a0, s0); \
            func_80015978(s0 + 4, (s32 *)sp18); \
            sp18[3] = 0; \
            func_8014C4AC(s0, 0x11, func_80029AAC(), sp18, \
                          *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)); \
            *(s32 *)(a0 + 0x178) = 0; \
        } \
    }

#define DEFINE_func_80147D38() \
    extern void func_80147948(s32 a0, s32 a1, s32 a2); \
    extern void func_801479BC(s32 a0, s32 a1, s32 a2); \
    extern void func_80147A30(s32 a0, s32 a1, s32 a2); \
    extern void func_80147DC0(s32 a0, s32 a1); \
    void func_80147D38(s32 a0, s32 a1, s32 a2, s32 a3, void * a4) \
    { \
        func_80147948(a0, a1, 0x7FFFFFFF); \
        func_801479BC(a0, a2, 0x7FFFFFFF); \
        func_80147A30(a0, a3, 0x7FFFFFFF); \
        func_80147DC0(a0, a4); \
    }

#define DEFINE_func_80129398() \
    extern s16 D_800B9AAC[]; \
    extern s16 D_800B9AAE[]; \
    extern s16 D_800B9AB0[]; \
    extern s16 D_800B9AB2[]; \
    extern s16 D_800B9AB4[]; \
    extern s16 D_800B9AB6[]; \
    extern s16 D_800B9AB8[]; \
    extern s16 D_800B9ABA[]; \
    void func_80129398(void) \
    { \
        s32 i; \
        s32 off; \
        for (i = 0; i < 2; i++) { \
            off = i * 0x54; \
            *(s16 *)((char *)D_800B9AAC + off) = 0x7FFF; \
            *(s16 *)((char *)D_800B9AAE + off) = 0; \
            *(u16 *)((char *)D_800B9AB0 + off) = 0xFFFF; \
            *(s16 *)((char *)D_800B9AB2 + off) = 0; \
            *(s16 *)((char *)D_800B9AB4 + off) = 0x140; \
            *(s16 *)((char *)D_800B9AB6 + off) = 0xEE; \
            *(s16 *)((char *)D_800B9AB8 + off) = 0; \
            *(s16 *)((char *)D_800B9ABA + off) = 0; \
            off += 0x54; \
        } \
    }

#define DEFINE_func_80171D78() \
    extern s32 func_8017248C(s32 a0, s32 a1); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern void func_80171EC8(s32 a0); \
    extern void func_80146D90(s32 a0); \
    s32 func_80171D78(s32 a0, s32 a1) \
    { \
        s32 ret; \
        s32 ang; \
        s32 p; \
        ret = func_8017248C(a0, a1); \
        if (ret != 0) { \
            func_80146D90(a0); \
            return ret; \
        } \
        ang = ratan2(*(s16 *)(a1 + 0) - *(s16 *)(a0 + 6), \
                     *(s16 *)(a1 + 4) - *(s16 *)(a0 + 0xE)); \
        ang = (ang + 0x800) & 0xFFF; \
        p = *(s32 *)(a0 + 0x20); \
        *(s16 *)(p + 0x12) = ang; \
        func_80171EC8(a0); \
        return 0; \
    }

#define DEFINE_func_801776EC() \
    extern u8 D_8011F7AB; \
    void func_801776EC(u8 *a0) \
    { \
        u8 *p; \
        switch (D_8011F7AB) { \
        default: \
            D_8011F7AB = 0; \
        case 0: \
            a0[4] = 0xFF; \
            a0[6] = 0x30; \
            a0[5] = 0x30; \
            break; \
        case 1: \
            a0[5] = 0xFF; \
            a0[6] = 0x30; \
            a0[4] = 0x30; \
            break; \
        case 2: \
            a0[6] = 0xFF; \
            a0[5] = 0x30; \
            a0[4] = 0x30; \
            break; \
        } \
        p = &D_8011F7AB; \
        *p = *p + 1; \
    }

#define DEFINE_func_8012B2CC() \
    extern void func_80049CAC(s32 a0, s32 a1); \
    void func_8012B2CC(s32 a0) \
    { \
        s32 a1; \
        s32 p; \
        s16 v; \
        a1 = *(s32 *)(a0 + 0x20); \
        if (a1 != 0) { \
            func_80049CAC(a1 + 0x10, a1 + 0x34); \
            p = *(s32 *)(a0 + 0x20); \
            v = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50); \
            *(s16 *)(p + 0x8) = v; \
            *(s32 *)(p + 0x48) = v; \
            v = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52); \
            *(s16 *)(p + 0xA) = v; \
            *(s32 *)(p + 0x4C) = v; \
            v = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x54); \
            *(s16 *)(p + 0xC) = v; \
            *(u16 *)(p + 0x2C) = *(u16 *)(p + 0x2C) | 1; \
            *(s32 *)(p + 0x50) = v; \
        } \
    }

#define DEFINE_func_801525F4() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_801525F4(s32 a0) \
    { \
        s32 v1; \
        func_8014BC44(a0, *(s16 *)(a0 + 0xF2)); \
        *(s8 *)(a0 + 0xA8) = 0x20; \
        func_80154A74(a0, 0x11); \
        func_801553C0(a0); \
        func_801470AC((s32 *)a0); \
        func_801472B4((void *)a0); \
        v1 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(a0 + 0x3E) = 0; \
        *(s16 *)(a0 + 0x40) = 0; \
        *(s16 *)(a0 + 0x42) = 0; \
        *(s8 *)(a0 + 0xDD) = 0; \
        *(s16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE; \
        *(s16 *)(v1 + 0x10) = 0; \
        *(s16 *)(a0 + 0x60) = 0x1000; \
        *(s16 *)(a0 + 0x62) = 0x1000; \
        *(s16 *)(a0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)a0, 0); \
        func_80153C18(a0); \
    }

#define DEFINE_func_8014C5FC() \
    extern s32 func_80047D3C(s32 a0); \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8014C5FC(s32 a0, s32 a1, void * a2) \
    { \
        s32 dx; \
        s32 dz; \
        s32 dy; \
        s32 r; \
        dz = (s16)(*(u16 *)((s32)a1 + 0xE) + *(u16 *)((s32)a2 + 0x4) - *(u16 *)((s32)a0 + 0xE)); \
        dx = (s16)(*(u16 *)((s32)a1 + 0x6) + *(u16 *)((s32)a2 + 0x0) - *(u16 *)((s32)a0 + 0x6)); \
        r = func_80047D3C(dz * dz + dx * dx); \
        dy = *(s16 *)((s32)a1 + 0xA) + *(s16 *)((s32)a2 + 0x2) - *(s16 *)((s32)a0 + 0xA); \
        return ratan2(dy, (s16)r) & 0xFFF; \
    }

#define DEFINE_func_8014FC18() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    s32 func_8014FC18(u8 *self) \
    { \
        s16 src[4]; \
        s16 dst[4]; \
        s32 ret; \
        src[0] = *(u16 *)(self + 0x6); \
        src[1] = *(u16 *)(self + 0xA); \
        src[2] = *(u16 *)(self + 0xE); \
        dst[0] = *(u16 *)(self + 0x6); \
        dst[1] = *(u16 *)(self + 0xA) + 0x10; \
        dst[2] = *(u16 *)(self + 0xE); \
        ret = func_80133784(1, src, (s32)dst); \
        if (ret != 0) { \
            *(u16 *)(self + 0x6) = dst[0]; \
            *(u16 *)(self + 0xA) = dst[1]; \
            *(u16 *)(self + 0xE) = dst[2]; \
            if (*(u8 *)&dst[3] != 0) { \
                *(s16 *)(self + 0x16C) = *(u8 *)&dst[3]; \
            } \
            *(s16 *)(self + 0x16E) = (u16)dst[3] >> 13; \
            return ret; \
        } \
        if (*(u8 *)&dst[3] != 0) { \
            *(s16 *)(self + 0x16C) = *(u8 *)&dst[3]; \
        } \
        return 0; \
    }

#define DEFINE_func_80161124() \
    extern void func_801483E8(); \
    extern void func_8014CBF8(void *a0); \
    extern void func_801474EC(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern s32 func_80149184(s32 a0); \
    extern void func_801553A8(s32 *a0); \
    extern s32 func_801725A4(u8 *a0); \
    extern s32 func_80161A60(s32 a0); \
    extern void func_80147324(s32 a0); \
    extern s16 D_801152A0; \
    void func_80161124(void *a0) \
    { \
        u8 *self = (u8 *)a0; \
        *(s16 *)(self + 0x24A) = 0; \
        func_801483E8(); \
        func_8014CBF8(a0); \
        func_801474EC((s32 *)a0); \
        if (*(s32 *)(self + 0x2C) < (s32)0xFFF46000) { \
            *(s32 *)(self + 0x2C) = 0xFFF46000; \
        } \
        if ((*(s32 *)(self + 0x24) | *(s32 *)(self + 0x2C)) != 0) { \
            func_80154150((s32)self, 0xF); \
        } else { \
            func_80154150((s32)self, 0xD); \
        } \
        func_80154A74((s32)self, 0x22); \
        *(s32 *)(self + 0x5C) = 0; \
        *(s32 *)(self + 0x240) = 0; \
        func_80146E90((s32 *)self, 4); \
        D_801152A0 = func_80149184((s32)self); \
        func_801553A8((s32 *)self); \
        func_801725A4((u8 *)self); \
        if (func_80161A60((s32)self) != 0) { \
            func_80147324(0x8E1); \
        } \
    }

#define DEFINE_func_8016EE94() \
    extern void func_801726D0(void *a0); \
    extern s32 D_80126D50; \
    extern s32 D_80126B58; \
    extern s32 D_80126D54; \
    extern u8 D_80126D6C; \
    extern u8 D_80126D6D; \
    extern u8 D_80126D6E; \
    extern s32 D_80126D5C; \
    extern s32 D_80126D60; \
    extern s16 D_80126D64; \
    extern s16 D_80126D66; \
    extern s16 D_80126D68; \
    extern s16 D_80126D6A; \
    extern u8 D_80126D1A; \
    extern s32 D_80127058; \
    extern s32 D_8012705C; \
    extern s32 D_80127060; \
    extern s32 D_80127064; \
    extern s32 D_80127068; \
    extern s32 D_8012706C; \
    extern s32 D_80127070; \
    extern s32 D_80127074; \
    extern u8 D_800B9A17; \
    extern s16 D_80126D20; \
    void func_8016EE94(s32 a0, s32 a1) \
    { \
        a0 = a0 | 0x4000000; \
        D_80126D50 = a0 | a1; \
        D_80126D54 = 0; \
        D_80126D6C = 0; \
        D_80126D6D = 0; \
        D_80126D6E = 0; \
        D_80126D5C = 0; \
        D_80126D60 = 0; \
        D_80126D64 = 0; \
        D_80126D66 = 0; \
        D_80126D68 = 0; \
        D_80126D6A = 0; \
        D_80126D1A = 0; \
        D_80127058 = 0; \
        D_8012705C = 0; \
        D_80127060 = 0; \
        D_80127064 = 0; \
        D_80127068 = 0; \
        D_8012706C = 0; \
        D_80127070 = 0; \
        D_80127074 = 0; \
        func_801726D0(&D_80126B58); \
        D_800B9A17 = 0; \
        D_80126D20 = 0; \
    }

#define DEFINE_func_8014BB24() \
    extern s32 func_80029178(s32 a0); \
    extern u8 D_80078E78[]; \
    extern s16 D_80078EB4; \
    void func_8014BB24(s32 a0, s32 a1, s32 a2) \
    { \
        u8 *base = D_80078E78; \
        u16 cur; \
        if (a2 != 0) { \
            D_80078EB4 = (u16)D_80078EB4 + a1; \
        } else { \
            if ((func_80029178(0x1B) & 0xFF) != 0) { \
                cur = D_80078EB4; \
                if (cur < 0x3E7) { \
                    D_80078EB4 = cur + a1; \
                    if ((u16)(cur + a1) >= 0x3E8) { \
                        D_80078EB4 = 0x3E7; \
                    } \
                } \
            } else { \
                cur = D_80078EB4; \
                if (cur < 0x1F4) { \
                    D_80078EB4 = cur + a1; \
                    if ((u16)(cur + a1) >= 0x1F5) { \
                        D_80078EB4 = 0x1F4; \
                    } \
                } \
            } \
        } \
        if (*(u16 *)(base + 0x3A) < *(u16 *)(base + 0x3C)) { \
            *(u16 *)(base + 0x3C) = *(u16 *)(base + 0x3A); \
        } \
    }

#define DEFINE_func_8015E5B0() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    void func_8015E5B0(u8 *self) \
    { \
        u8 *obj; \
        s16 src[4]; \
        s16 dst[4]; \
        obj = *(u8 **)(self + 0x18C); \
        if (obj == 0) { \
            return; \
        } \
        src[0] = *(u16 *)(self + 0x6); \
        src[1] = *(u16 *)(self + 0xA) - 0x14; \
        src[2] = *(u16 *)(self + 0xE); \
        dst[0] = *(u16 *)(obj + 0x6); \
        dst[1] = *(u16 *)(obj + 0xA); \
        dst[2] = *(u16 *)(obj + 0xE); \
        if (func_80133784(0, src, (s32)dst) != 0) { \
            *(u16 *)(obj + 0x6) = dst[0]; \
            *(u16 *)(obj + 0xA) = dst[1]; \
            *(u16 *)(obj + 0xE) = dst[2]; \
        } \
        func_80015978((s32)(obj + 4), (s32 *)src); \
        src[3] = 0; \
        func_8014C4AC((s32)obj, 0x1C, 0, src, \
                      *(s16 *)(*(u8 **)(self + 0x20) + 0x12)); \
        *(s32 *)(self + 0x18C) = 0; \
    }

#define DEFINE_func_80172E20() \
    extern s32 D_80127508; \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_80172E20(u8 * a0) \
    { \
        struct Src80172E20 *p = (struct Src80172E20 *)D_80127508; \
        u16 sp10[3]; \
        sp10[0] = p->_6; \
        sp10[1] = p->_A; \
        sp10[2] = p->_E; \
        if (func_80171AB0(a0, sp10) == 0) { \
            func_80171A1C((u8 *)a0); \
            func_80174650(a0); \
        } \
    }

#define DEFINE_func_8014706C() \
    void func_8014706C(void *arg0) { \
        M2C_FIELD(arg0, s8 *, 0x4D) = 2; \
    }

#define DEFINE_func_8014708C() \
    void func_8014708C(void *arg0) { \
        M2C_FIELD(arg0, s8 *, 0x221) = 1; \
    }

#define DEFINE_func_801470B4() \
    void func_801470B4(s32 arg0) \
    { \
        M2C_FIELD(arg0, s8 *, 0x222) = 1; \
    }

#define DEFINE_func_8012AD50() \
    s32 func_8012AD50(void * arg0) \
    { \
        M2C_FIELD(arg0, s16 *, 0x34) = 0; \
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1); \
    }

#define DEFINE_func_80151184() \
    s32 func_80151184(s32 arg0, s32 arg1, s32 arg2) \
    { \
      u16 *new_var; \
      int new_var2; \
      *((s16 *) (((s8 *) arg0) + 0x3E)) = arg1; \
      *((s16 *) (((s8 *) arg0) + 0x40)) = arg2; \
      new_var = (u16 *) (((s8 *) arg0) + 0x42); \
      new_var2 = (u16) (*((u16 *) (((s8 *) (*((void **) (((s8 *) arg0) + 0x20)))) + 0x12))); \
      *((u16 *) (((s8 *) arg0) + 0x3C)) = (u16) ((*((u16 *) (((s8 *) arg0) + 0x3C))) | 1); \
      *new_var = new_var2; \
    }

#define DEFINE_func_80139914() \
    extern void func_8013A8B0(s32 *a0); \
    void func_80139914(s32 arg0) \
    { \
        s32 temp_a0; \
        M2C_FIELD(arg0, s16 *, 4) = 0; \
        M2C_FIELD(arg0, s32 *, 0) = 0; \
        if (M2C_FIELD(arg0, u16 *, 0x18) != 0) { \
            temp_a0 = M2C_FIELD(arg0, s32 *, 0x40); \
            if (temp_a0 != 0) { \
                func_8013A8B0(temp_a0); \
            } \
        } \
    }

#define DEFINE_func_80147324() \
    extern void func_80147364(u16, s32); \
    extern void *D_8012707C; \
    void func_80147324(s32 arg0) { \
        s32 temp_a0; \
        temp_a0 = arg0 & 0xFFFF; \
        if (temp_a0 == D_8012707C) { \
            D_8012707C = 0; \
            return; \
        } \
        func_80147364(temp_a0, 0); \
    }

#define DEFINE_func_80165A78() \
    extern void func_80165AC8(void); \
    void func_80165A78(s32 arg0) \
    { \
        void *temp_a0; \
        func_80165AC8(); \
        temp_a0 = M2C_FIELD(arg0, void **, 0x20); \
        M2C_FIELD(arg0, s8 *, 0x197) = 0; \
        M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) & ~8); \
        M2C_FIELD(temp_a0, u16 *, 0x2C) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x2C) & 0xFFDF); \
    }

#define DEFINE_func_801554B8() \
    extern s32 func_801659DC(u8 *a0); \
    s32 func_801554B8(void *arg0) { \
        s32 var_v0; \
        u8 temp_a0; \
        temp_a0 = M2C_FIELD(arg0, u8 *, 0x1A0); \
        var_v0 = 0; \
        if (temp_a0 != M2C_FIELD(arg0, u8 *, 0x196)) { \
            if (func_800D02D0(temp_a0) != 0) { \
                M2C_FIELD(arg0, u8 *, 0x196) = (u8) M2C_FIELD(arg0, u8 *, 0x1A0); \
                func_801659DC(arg0); \
                return 0; \
            } \
            var_v0 = 1; \
            /* Duplicate return node #4. Try simplifying control flow for better match */ \
            return var_v0; \
        } \
        return var_v0; \
    }

#define DEFINE_func_801530E4() \
    extern void func_80019064(void *a0); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_801472C8(struct S *a0); \
    extern void func_801474EC(s32 *a0); \
    extern void func_80149020(s32 *a0); \
    extern void func_8014CBF8(void *a0); \
    extern void func_80155440(s32 *a0); \
    extern u8 D_80062C04[]; \
    void func_801530E4(s32 arg0) \
    { \
        func_80019064(&D_80062C04); \
        func_80149020(arg0); \
        func_801472C8(arg0); \
        M2C_FIELD(arg0, s8 *, 0xDE) = 0x40; \
        func_8014CBF8(arg0); \
        func_801474EC(arg0); \
        func_80155440(arg0); \
        func_80146CA0(arg0); \
    }

#define DEFINE_func_8016B448() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern s32 func_8014C050(s32 a0, s32 a1); \
    extern void func_8016B984(void *a0); \
    extern s32 D_80126B58; \
    s32 func_8016B448(s32 arg0, s32 arg1) \
    { \
        s32 temp_v0; \
        temp_v0 = func_8014C050(&D_80126B58, 0x1E); \
        if (temp_v0 != 0) { \
            func_8016B984(temp_v0); \
        } \
        func_80146A6C(0x1E, arg0, M2C_FIELD(arg0, s16 *, 0x7C), M2C_FIELD(arg0, s16 *, 0x7E), (s32) M2C_FIELD(arg0, s16 *, 0x80), arg1, 0); \
    }

#define DEFINE_func_801485B8() \
    void func_801485B8(s32 arg0, s32 arg1, s32 arg2) \
    { \
        M2C_FIELD(arg1, s16 *, 0) = (s16) (s8) M2C_FIELD(arg0, u8 *, 0); \
        M2C_FIELD(arg1, s16 *, 2) = (s16) (s8) M2C_FIELD(arg0, u8 *, 1); \
        M2C_FIELD(arg1, s16 *, 4) = (s16) (s8) M2C_FIELD(arg0, u8 *, 2); \
        M2C_FIELD(arg2, s16 *, 0) = (s16) (s8) M2C_FIELD(arg0, u8 *, 3); \
        M2C_FIELD(arg2, s16 *, 2) = (s16) (s8) M2C_FIELD(arg0, u8 *, 4); \
        M2C_FIELD(arg2, s16 *, 4) = (s16) (s8) M2C_FIELD(arg0, u8 *, 5); \
    }

#define DEFINE_func_8014E790() \
    s32 func_8014E790(s32 arg0, s16 * arg1, s16 * arg2) \
    { \
        s32 temp_a1; \
        void *temp_s0; \
        temp_s0 = M2C_FIELD(arg0, void **, 0x180); \
        if ((M2C_FIELD(temp_s0, u16 *, 0) == 0) || !(M2C_FIELD(temp_s0, u16 *, 0x5C) & 0x20) || (temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x58), (temp_a1 == 0)) || (func_80135888(M2C_FIELD(temp_s0, s32 *, 0x20), temp_a1, arg1, arg2) == 0)) { \
            M2C_FIELD(arg0, void **, 0x180) = NULL; \
            return 0; \
        } \
        M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(temp_s0, u16 *, 6); \
        M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(temp_s0, u16 *, 0xA); \
        M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(temp_s0, u16 *, 0xE); \
        return 1; \
    }

#define DEFINE_func_8012D3B4() \
    extern s32 AddPrim(s32, void *); \
    extern s32 RotTransPers(s32, s32, s32 *, s32 *); \
    extern void SetLineF2(void *); \
    extern void *func_80010A08(s32); \
    extern void func_8004914C(void *); \
    extern void func_800491AC(void *); \
    extern s32 D_800A651C; \
    extern u8 D_800AF648; \
    extern s16 D_800B9A02; \
    void func_8012D3B4(s32 arg0, s32 arg1, s32 arg2) { \
        s32 sp10; \
        s32 sp14; \
        s32 temp_v0_2; \
        void *temp_v0; \
        temp_v0 = func_80010A08(0x10); \
        (*(s32 *)((s8*)(temp_v0)+(4))) = arg2; \
        SetLineF2(temp_v0); \
        func_8004914C(&D_800AF648); \
        func_800491AC(&D_800AF648); \
        temp_v0_2 = RotTransPers(arg0, temp_v0 + 8, &sp10, &sp14); \
        if ((temp_v0_2 > 0) && (sp14 >= 0) && (RotTransPers(arg1, temp_v0 + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) { \
            AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + (temp_v0_2 * 4), temp_v0); \
        } \
    }

#define DEFINE_func_801303A0() \
    extern void func_8012E364(void); \
    extern void func_80131CA8(int a0, int a1); \
    void func_801303A0(s32 a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x2) { \
            ((void (*)(s32))func_8012E364)(a0); \
        } \
        func_80131CA8(a0, 2); \
    }

#define DEFINE_func_8015773C() \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801553A8(s32 *a0); \
    s32 func_8015773C(u8 * arg0) \
    { \
        *(s32 *)((u8 *)arg0 + 0x44) = *(s32 *)((u8 *)arg0 + 0x44) & ~2; \
        func_80154A74((s32)arg0, 0x11); \
        func_801553C0((s32)arg0); \
        func_801553A8(arg0); \
    }

#define DEFINE_func_8012BE98() \
    extern s32 func_800132BC(s32 a0, s32 a1); \
    void func_8012BE98(s32 arg0, u16 * arg1) \
    { \
        s16 a[3]; \
        s16 b[3]; \
        a[0] = *(u16 *)((u8 *)arg0 + 0x6); \
        a[1] = 0; \
        a[2] = *(u16 *)((u8 *)arg0 + 0xE); \
        b[0] = *(u16 *)((u8 *)arg1 + 0x0); \
        b[1] = 0; \
        b[2] = *(u16 *)((u8 *)arg1 + 0x4); \
        func_800132BC((s32)a, (s32)b); \
    }

#define DEFINE_func_8012A7D4() \
    extern s32 D_801151D4; \
    void func_8012A7D4(void *arg0, void *arg1) { \
        s32 p; \
        p = D_801151D4; \
        *(s16 *)((u8 *)arg0 + 0x0) = *(s32 *)(p + 0x3C); \
        *(s16 *)((u8 *)arg0 + 0x2) = *(s32 *)(p + 0x40); \
        *(s16 *)((u8 *)arg0 + 0x4) = *(s32 *)(p + 0x44); \
        *(s16 *)((u8 *)arg1 + 0x0) = *(s32 *)(p + 0x48); \
        *(s16 *)((u8 *)arg1 + 0x2) = *(s32 *)(p + 0x4C); \
        *(s16 *)((u8 *)arg1 + 0x4) = *(s32 *)(p + 0x50); \
    }

#define DEFINE_func_8012C51C() \
    extern u8 D_80126720[]; \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    s32 func_8012C51C(void *a0, s32 a1) { \
        u8 *base = D_80126720; \
        u8 *p; \
        s32 ret; \
        if (a1 == 0) { \
            p = base - 0x6480; \
        } else { \
            p = (u8 *)(a1 + 0x10C); \
        } \
        if (p != base) { \
            do { \
                if (*(u16 *)p == 0) goto found; \
                p += 0x10C; \
            } while (p != base); \
        } \
        p = 0; \
    found: \
        ret = 0; \
        if (p != 0) { \
            ret = func_8012C890((s32)a0, (s32)p, a1); \
        } \
        return ret; \
    }

#define DEFINE_func_801301E8() \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_80130D48(s32 a0); \
    extern void func_801319E0(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_801301E8(u8 *a0) { \
        if (*(s32 *)(a0 + 0xB4) & 0x2000) { \
            if (*(u8 *)(a0 + 0xC3) != 0) { \
                if (*(u16 *)(a0 + 0x72) & 0x4000) { \
                    func_80130D48((s32)a0); \
                    func_801319E0((s32)a0); \
                } \
            } else if (func_8012BEE8((s32)a0) != 0) { \
                func_80130D48((s32)a0); \
                func_801319E0((s32)a0); \
            } \
        } \
        func_80131CA8((int)a0, 0x26); \
    }

#define DEFINE_func_80130278() \
    extern void func_80131CA8(int a0, int a1); \
    extern void func_80131170(s32 a0, s32 a1, s32 a2); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    void func_80130278(s32 arg0) { \
        s32 flag; \
        flag = 0; \
        *(u8 *)(arg0 + 0xC1) = 0xB; \
        if (*(s32 *)(arg0 + 0xC4) & 1) { \
            func_80131E00((struct S80131E00 *)arg0, 0xE); \
            return; \
        } \
        if (*(s32 *)(arg0 + 0xB4) & 0x800) { \
            func_80131170(arg0, 0, 0); \
            flag = 1; \
        } \
        if (((s32 (*)(int, int))func_80131CA8)(arg0, 0x2C) != 0) { \
            flag = 1; \
        } \
        if (flag == 0) { \
            func_80131E00((struct S80131E00 *)arg0, 6); \
        } \
    }

#define DEFINE_func_8012C588() \
    extern u8 D_801202A0[]; \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    s32 func_8012C588(s32 a0, s32 a1) { \
        s32 p; \
        s32 end; \
        s32 v0; \
        s32 q; \
        s16 sp[10]; \
        if (a1 != 0 && *(u16*)a1 != 0) { \
            sp[0] = *(u16*)(a1 + 0x6); \
            sp[1] = *(u16*)(a1 + 0xA); \
            sp[2] = *(u16*)(a1 + 0xE); \
        } else { \
            sp[2] = 0; \
            sp[1] = 0; \
            sp[0] = 0; \
        } \
        sp[3] = a0; \
        q = (s32)&sp[0]; \
        sp[5] = 0; \
        sp[4] = 0; \
        *(s32*)&sp[8] = 0; \
        sp[7] = 0; \
        sp[6] = 0x7FFF; \
        end = (s32)D_801202A0 + 0x6480; \
        if (a1 == 0) { \
            p = (s32)D_801202A0; \
        } else { \
            p = a1 + 0x10C; \
        } \
        if (p != end) { \
            for (;;) { \
                if (*(u16*)p == 0) { \
                    goto found; \
                } \
                p += 0x10C; \
                if (p == end) { \
                    break; \
                } \
            } \
        } \
        p = 0; \
    found: \
        v0 = 0; \
        if (p != 0) { \
            v0 = func_8012C890(q, p, a1); \
        } \
        return v0; \
    }

#define DEFINE_func_80147B5C() \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_80147B5C(s32 arg0, void *arg1) { \
        if (*(s32 *)(arg0 + 0x44) & 0x400000) { \
            D_80127090 = *(s32 *)(arg0 + 0x24); \
        } else { \
            D_80127090 = *(s32 *)arg1; \
        } \
        if (*(s32 *)(arg0 + 0x44) & 0x800000) { \
            D_80127094 = *(s32 *)(arg0 + 0x28); \
        } else { \
            D_80127094 = *(s32 *)((u8 *)arg1 + 0x4); \
        } \
        if (*(s32 *)(arg0 + 0x44) & 0x1000000) { \
            D_80127098 = *(s32 *)(arg0 + 0x2C); \
        } else { \
            D_80127098 = *(s32 *)((u8 *)arg1 + 0x8); \
        } \
        *(s32 *)(arg0 + 0x10) = D_80127090; \
        *(s32 *)(arg0 + 0x14) = D_80127094; \
        *(s32 *)(arg0 + 0x18) = D_80127098; \
        D_80127090 = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
    }

#define DEFINE_func_8012E8E0() \
    extern void func_80049CAC(s32 a0, s32 a1); \
    void func_8012E8E0(s32 a0, s32 a1) \
    { \
        s32 v1; \
        s32 p; \
        s16 v; \
        u16 e; \
        v1 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(a0 + 0x6) = *(u16 *)(a1 + 0x0); \
        *(s16 *)(a0 + 0xA) = *(u16 *)(a1 + 0x2); \
        e = *(u16 *)(a1 + 0x4); \
        *(s16 *)(a0 + 0xC) = 0; \
        *(s16 *)(a0 + 0x8) = 0; \
        *(s16 *)(a0 + 0x4) = 0; \
        *(s16 *)(a0 + 0xE) = e; \
        if (v1 != 0) { \
            *(s16 *)(v1 + 0x12) = *(u16 *)(a1 + 0x6); \
            a1 = *(s32 *)(a0 + 0x20); \
            if (a1 != 0) { \
                func_80049CAC(a1 + 0x10, a1 + 0x34); \
                p = *(s32 *)(a0 + 0x20); \
                v = *(u16 *)(a0 + 0x6) + *(u16 *)(a0 + 0x50); \
                *(s16 *)(p + 0x8) = v; \
                *(s32 *)(p + 0x48) = v; \
                v = *(u16 *)(a0 + 0xA) + *(u16 *)(a0 + 0x52); \
                *(s16 *)(p + 0xA) = v; \
                *(s32 *)(p + 0x4C) = v; \
                v = *(u16 *)(a0 + 0xE) + *(u16 *)(a0 + 0x54); \
                *(s16 *)(p + 0xC) = v; \
                *(u16 *)(p + 0x2C) = *(u16 *)(p + 0x2C) | 1; \
                *(s32 *)(p + 0x50) = v; \
            } \
        } \
    }

#define DEFINE_func_8012832C() \
    extern s16 currentLocationId; \
    extern s32 func_80029504(void); \
    extern s32 func_800CF854(s32); \
    extern s32 func_80128998(void); \
    extern s32 func_801289F0(void); \
    extern s32 func_801288E8(s32); \
    extern s32 func_80128940(s32); \
    extern s32 func_80029178(s32); \
    extern s32 func_801288B0(void); \
    extern void func_80011C10(void); \
    void func_8012832C(void) { \
        s32 a0 = func_80029504(); \
        s32 v0; \
        switch (currentLocationId) { \
        case 0x300E: \
            if (func_800CF854(a0) == 0) { \
                v0 = func_80128998(); \
            } else { \
                v0 = func_801289F0(); \
            } \
            break; \
        case 0x30A0: \
            if (a0 < 0x640) { \
                v0 = func_801288E8(a0); \
            } else { \
                v0 = func_80128940(a0); \
            } \
            break; \
        case 0x3014: \
            if (a0 == 0x4B0 && (func_80029178(0x138) & 0xFF) == 0) { \
                v0 = func_801288B0(); \
            } else { \
                v0 = 1; \
            } \
            break; \
        default: \
            func_80011C10(); \
            return; \
        } \
        if (v0 != 0) { \
            func_80011C10(); \
        } \
    }

#define DEFINE_func_8012A988() \
    extern s32 func_8012ACE0(void *a0); \
    extern void func_8012AAAC(void); \
    void func_8012A988(u8 *a0) { \
        s32 v0; \
        s16 t; \
        u16 flags; \
        *(u16 *)(a0 + 0x72) = *(u16 *)(a0 + 0x72) & 0x9FFF; \
        if (*(u16 *)(a0 + 0x0) == 0) return; \
        if (*(u8 *)(a0 + 0xC1) == 0x11) return; \
        t = *(s16 *)(a0 + 0x98); \
        if (t == 0) return; \
        t = t - 1; \
        *(s16 *)(a0 + 0x98) = t; \
        if (t > 0) return; \
        if (*(s32 *)(a0 + 0x90) == 0) return; \
        flags = *(u16 *)(a0 + 0x72); \
        if (flags & 0x400) { \
            v0 = *(s32 *)(a0 + 0x94) - 1; \
            *(s32 *)(a0 + 0x94) = v0; \
            if (v0 < 0) { \
                *(s32 *)(a0 + 0x94) = 1; \
                *(u16 *)(a0 + 0x72) = *(u16 *)(a0 + 0x72) & 0xFBFF; \
            } \
        } else if (flags & 0x200) { \
            v0 = *(s32 *)(a0 + 0x94) - 1; \
            *(s32 *)(a0 + 0x94) = v0; \
            if (v0 < 0) { \
                s32 idx = func_8012ACE0(a0); \
                if (*(s16 *)((idx * 8) + *(s32 *)(a0 + 0x90) + 4) != -1) { \
                    *(s32 *)(a0 + 0x94) = 0; \
                    *(s16 *)(a0 + 0x98) = 0; \
                    return; \
                } \
                *(s32 *)(a0 + 0x94) = idx - 1; \
            } \
        } else { \
            *(s32 *)(a0 + 0x94) = *(s32 *)(a0 + 0x94) + 1; \
        } \
        ((void (*)(u8 *))func_8012AAAC)(a0); \
    }

#define DEFINE_func_801399A8() \
    extern s32 D_801269F0; \
    extern s32 D_80126A3C; \
    s32 func_801399A8(void) { \
        s32 iVar2; s32 puVar3; s32 iVar1; \
        for (iVar2 = 1, puVar3 = (s32)&D_80126A3C, iVar1 = 0x4C; iVar2 < 3; puVar3 += 0x4C, iVar2++, iVar1 += 0x4C) { \
            if (*(s32 *)((s32)&D_801269F0 + iVar1) == 0) return puVar3; \
        } \
        return 0; \
    }

#define DEFINE_func_8012B8E4() \
    extern s16 D_80126CB8; \
    extern s16 D_80126CB4; \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012B8E4(s32 arg0, s32 arg1) { \
        register s32 d __asm__("$16"); \
        register s32 s1ang __asm__("$17"); \
        s32 u5; s32 u6; s32 iVar4; s32 q; s32 t; \
        d = arg1; \
        s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12); \
        u5 = (ratan2(*(s16 *)(arg0 + 0xE) - D_80126CB8, D_80126CB4 - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF; \
        __asm__ __volatile__("" : : "r"(u5)); \
        d = (s16)d; \
        u6 = s1ang & 0xFFF; \
        if (u6 == u5) return 0; \
        iVar4 = u5 - u6; \
        if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; } \
        if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; } \
        if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; } \
        else { q = iVar4 / d; if (q == 0) q = -1; } \
        return q; \
    }

#define DEFINE_func_8012CB64() \
    s32 func_8012CB64(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) { \
        register s32 v0 __asm__("$2"); \
        register s32 v1 __asm__("$3"); \
        v0 = 0; \
        v1 = *(s16*)arg0; \
        if (((arg1 <= v1) && (v1 < arg2)) && (arg3 <= *(s16*)(arg0 + 4))) { \
            v0 = *(s16*)(arg0 + 4) < arg4; \
        } \
        return v0; \
    }

#define DEFINE_func_801319E0() \
    extern void func_80131CA8(int a0, int a1); \
    extern void func_8002A04C(s32 a0); \
    extern void func_8012C218(void *a0); \
    void func_801319E0(s32 arg0) { \
        /* arg0 stays in $s0 (callee-saved) across all three calls -- live across each jal, \
         * so clean C allocates it there naturally (no register pin needed). */ \
        if (((s32 (*)(int, int))func_80131CA8)(arg0, 0x11) == 0) { \
            if (*(s32 *)(arg0 + 0x78) != 0) { \
                func_8002A04C(arg0); \
            } \
            func_8012C218((void *)arg0); \
        } \
    }

#define DEFINE_func_80143B6C() \
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2); \
    s32 func_80143B6C(s32 arg0, s32 arg1) { \
        s32 iVar1; \
        iVar1 = func_8012C658(0x1C, arg1, arg0); \
        if (((iVar1 != 0) && (*(s32*)(arg0 + 0x20) != 0)) && (arg1 == 0)) { \
            *(s16*)(iVar1 + 0xFC) = *(u16*)(*(s32*)(arg0 + 0x20) + 0x12); \
        } \
        return iVar1; \
    }

#define DEFINE_func_80149B54() \
    extern u8 func_8014BEF8(void); \
    s32 func_80149B54(s32 * arg0) \
    { \
        s32 var_v0; \
        u32 temp; \
        if ((*(u32*)((u8*)arg0 + 0x44) & 0x400) != 0) { var_v0 = 0; goto end; } \
        if (((s32(*)(s32*))func_8014BEF8)(arg0) == 0) { var_v0 = 0; goto end; } \
        temp = *(u16*)((u8*)arg0 + 0xAC) & 0x10; \
        var_v0 = temp != 0; \
    end: \
        return var_v0; \
    }

#define DEFINE_func_801468C8() \
    extern s32 D_8011F750; \
    extern s32 D_8011F754; \
    u8 *func_801468C8(s32 arg0, u8 arg1) { \
        register u8 *var_a2 __asm__("$6");   /* $a2 — returned base ptr  */ \
        register u8 *var_v1 __asm__("$3");   /* $v1 — scan/store ptr     */ \
        s32 var_t0; \
        s32 var_a3; \
        var_t0 = 0; \
        var_a2 = (u8 *)(s32)&D_8011F750; \
        var_v1 = var_a2; \
        var_a3 = 0; \
        do { \
            if (*var_v1 != 0) { \
                var_a2 += 0x2C; \
                var_v1 += 0x2C; \
                var_t0 += 1; \
                var_a3 += 0x2C; \
            } else { \
                *(s32 *)((s32)&D_8011F754 + var_a3) = arg0; \
                *var_v1 = arg1; \
                return var_a2; \
            } \
        } while (var_t0 < 2); \
        return (u8 *)0; \
    }

#define DEFINE_func_80146994() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    s32 func_80146994(s32 arg0, s32 arg1, s32 arg2, s32 arg3) \
    { \
        func_80146A6C(arg0 & 0xFFFF, (void *)arg1, 0, 0, 0, arg2, arg3); \
    }

#define DEFINE_func_80149544() \
    extern void func_8012F14C(s32); \
    extern void func_8012EF70(s32 a0, s32 a1); \
    void func_80149544(s32 arg0, s32 arg1, s32 arg2) { \
        s32 sp10[2]; \
        ((void(*)(s32,s32,s32))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x34, arg1, (s32)sp10); \
        func_8012EF70((s32)sp10, arg2); \
    }

#define DEFINE_func_8012913C() \
    extern void func_8001D074(s32 a, s32 b); \
    extern u8 *func_801291C0(void); \
    extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3); \
    u8 * func_8012913C(s32 arg0) \
    { \
        s32 iVar1; \
        u8 *puVar2; \
        iVar1 = ((s32(*)(s32,s32))func_8001D074)(0x7E, 0x100); \
        if (iVar1 == 0) { \
            return (u8 *)0; \
        } \
        puVar2 = func_801291C0(); \
        if (puVar2 == (u8 *)0) { \
            return (u8 *)0; \
        } \
        *(s16 *)puVar2 = arg0; \
        *(s32 *)(puVar2 + 0x20) = iVar1; \
        func_8001CC3C(iVar1, 0, 0, 0); \
        return puVar2; \
    }

#define DEFINE_func_80149584() \
    extern void func_8012F14C(s32); \
    extern void func_8012EFB8(s32 a0); \
    void func_80149584(s32 arg0, s32 arg1, s32 arg2) { \
        s8 buf[8]; \
        ((void(*)(s32,s32,s32))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x34, arg1, (s32)buf); \
        ((void(*)(s32,s32))func_8012EFB8)((s32)buf, arg2); \
    }

#define DEFINE_func_8013A380() \
    extern u8 D_8011DA80[]; \
    extern void func_8013A530(); \
    extern void func_8013A448(void *a0); \
    extern void func_8013A4C4(struct S8013A4C4 *a0); \
    void func_8013A380(void) { \
        s16 *p; \
        s32 i; \
        p = (s16 *)D_8011DA80; \
        i = 0; \
        do { \
            if (p != (s16 *)0) { \
                switch (*p) { \
                case 2: \
                    ((void (*)(void *))func_8013A530)(p); \
                    break; \
                case 1: \
                    func_8013A448(p); \
                    break; \
                case 3: \
                    func_8013A4C4((struct S8013A4C4 *)p); \
                    break; \
                } \
            } \
            i += 1; \
            p += 8; \
        } while (i < 2); \
    }

#define DEFINE_func_8012F5F4() \
    extern void func_80131B14(); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern s32 func_80131A34(s32, s32); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F5F4(s32 arg0) { \
        *(u8 *)(arg0 + 0xC1) = 1; \
        if ((*(s32 *)(arg0 + 0xC4) & 2) != 0) { \
            func_80131CA8(arg0, 3); \
            return; \
        } \
        ((void (*)(s32))func_80131B14)(arg0); \
        if (*(s16 *)(arg0 + 0x76) < 1) { \
            func_80131E00((struct S80131E00 *)arg0, 0xC); \
            return; \
        } \
        if (func_80131A34(arg0, 4) != 0) { \
            *(u8 *)(arg0 + 0xC2) = 0; \
        } else { \
            *(s16 *)(arg0 + 0x98) = 0; \
            *(u8 *)(arg0 + 0xC2) = 1; \
            *(s32 *)(arg0 + 0x1C) = 0x10; \
        } \
        func_80131CA8(arg0, 3); \
    }

#define DEFINE_func_8013A8FC() \
    extern u8 D_8011DA80[]; \
    extern void func_8013A9B4(s32 a0, s32 a1); \
    s32 func_8013A8FC(s32 arg0) { \
        s32 p; \
        s32 i; \
        s32 v1; \
        if (*(u16*)(arg0 + 0x18) == 0) { \
            return 1; \
        } \
        if (*(s32*)(arg0 + 0x40) == 0) { \
            i = 0; \
            do { \
                if (*(s16*)(i + (s32)D_8011DA80) == 0) { \
                    p = i + (s32)D_8011DA80; \
                    goto post; \
                } \
                i += 0x10; \
            } while (i < 0x20); \
            i = 0; \
            p = i; \
        post: \
            if (p != 0) { \
                v1 = *(u16*)(arg0 + 0x18); \
                if (v1 < 7) { \
                    if (v1 != 0) { \
                        func_8013A9B4(arg0, p); \
                        return 1; \
                    } \
                } \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_801788B8() \
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2); \
    extern void func_8012E8E0(s32 a0, s32 a1); \
    extern void func_8012B2CC(s32 a0); \
    s32 func_801788B8(s32 arg0, s32 arg1) { \
        s32 iVar1; \
        u16 buf[4]; \
        iVar1 = func_8012C658(0x83, (s32)*(s16 *)((u8 *)arg0 + 0x70), 0); \
        if (iVar1 == 0) { \
            return 0; \
        } \
        *(s32 *)((u8 *)iVar1 + 0x64) = arg0; \
        buf[0] = *(u16 *)((u8 *)arg0 + 0x6); \
        buf[1] = *(u16 *)((u8 *)arg0 + 0xA); \
        buf[2] = *(u16 *)((u8 *)arg0 + 0xE); \
        if (*(s32 *)((u8 *)arg0 + 0x20) != 0) { \
            buf[3] = *(u16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x20)) + 0x12); \
        } else { \
            buf[3] = 0; \
        } \
        func_8012E8E0(iVar1, (s32)buf); \
        func_8012B2CC(iVar1); \
        *(s32 *)((u8 *)iVar1 + 0xDC) = arg1; \
        return iVar1; \
    }

#define DEFINE_func_80171E08() \
    extern s32 func_8017248C(s32 a0, s32 a1); \
    extern void func_80146D90(s32 a0); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80171EC8(s32 a0); \
    s32 func_80171E08(s32 arg0, s32 arg1, s32 arg2) { \
        s32 r; \
        s32 a1v; \
        r = func_8017248C(arg0, arg1); \
        if (r != 0) { \
            func_80146D90(arg0); \
            return r; \
        } \
        a1v = (ratan2((s32)*(s16 *)(arg1 + 0x0) - (s32)*(s16 *)(arg0 + 0x6), \
                      (s32)*(s16 *)(arg1 + 0x4) - (s32)*(s16 *)(arg0 + 0xE)) + 0x800) & 0xFFF; \
        if (arg2 != 0) { \
            a1v = (s16)func_80012DBC((s32)*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), \
                                     a1v, (s32)(s16)arg2, 1); \
        } \
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = a1v; \
        func_80171EC8(arg0); \
        return 0; \
    }

#define DEFINE_func_8014E83C() \
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u8 D_801202A0[]; \
    s32 func_8014E83C(s32 arg0, s16 * arg1, s16 * arg2) \
    { \
        register u8 *p   __asm__("$17");  /* $s1 */ \
        register u8 *q   __asm__("$16");  /* $s0 */ \
        u8 *end; \
        s32 t; \
        p = D_801202A0; \
        if ((u32)p < (u32)(p + 0x6480)) { \
            end = p + 0x6480; \
            q = p + 0xE; \
            do { \
                if (*(u16 *)p != 0 && (*(u16 *)(q + 0x4E) & 0x20) && \
                    (t = *(s32 *)(q + 0x4A), t != 0) && \
                    func_80135888(*(s32 *)(q + 0x12), t, arg1, arg2) != 0) { \
                    *(s32 *)(arg0 + 0x180) = (s32)p; \
                    *(u16 *)(arg0 + 0x6) = *(u16 *)(q - 0x8); \
                    *(u16 *)(arg0 + 0xA) = *(u16 *)(q - 0x4); \
                    *(u16 *)(arg0 + 0xE) = *(u16 *)q; \
                    return 1; \
                } \
                p += 0x10C; \
                q += 0x10C; \
            } while ((u32)p < (u32)end); \
        } \
        return 0; \
    }

#define DEFINE_func_8014DF94() \
    extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2); \
    extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */ \
    void func_8014DF94(s32 arg0) { \
        s16 a[3]; \
        s16 b[3]; \
        register s32 u88 __asm__("$4"); \
        register s32 u8C __asm__("$5"); \
        s32 t; \
        s32 t2; \
        u88 = *(u16 *)(arg0 + 0x88); \
        a[0] = u88; \
        a[1] = *(u16 *)(arg0 + 0x8A) - 0x10; \
        u8C = *(u16 *)(arg0 + 0x8C); \
        a[2] = u8C; \
        t = *(u16 *)(arg0 + 6); \
        b[0] = t; \
        b[1] = *(u16 *)(arg0 + 0xA) - 0x10; \
        t = t - u88; \
        t2 = *(u16 *)(arg0 + 0xE); \
        u88 = u88 - t; \
        b[0] = t; \
        __asm__ __volatile__("" : : : "memory"); \
        b[0] = u88; \
        b[2] = t2; \
        __asm__ __volatile__("" : : : "memory"); \
        t2 = t2 - u8C; \
        u8C = u8C - t2; \
        b[2] = t2; \
        __asm__ __volatile__("" : : : "memory"); \
        b[2] = u8C; \
        if (*(s32 *)(arg0 + 0x170) == 0) { \
            func_8014E284(arg0, a, b); \
        } else { \
            func_8014E048(arg0, a, b); \
        } \
    }

#define DEFINE_func_80154358() \
    extern void func_8015444C(void *a0, s32 *a1, s32 *a2, s32 *a3); \
    s32 func_80154358(void * arg0) \
    { \
        s32 sp10; \
        s32 sp14; \
        s32 sp18; \
        s32 temp_s2; \
        u16 temp_s3; \
        u16 temp_s1; \
        u8 temp_s5; \
        u8 temp_s6; \
        u8 temp_s7; \
        s32 temp_s4; \
        s32 ret; \
        void *v1; \
        temp_s5 = *(u8 *)((u8 *)arg0 + 0xBC); \
        temp_s6 = *(u8 *)((u8 *)arg0 + 0xBD); \
        temp_s7 = *(u8 *)((u8 *)arg0 + 0xDC); \
        sp10 = 0; \
        sp14 = 0; \
        sp18 = 1; \
        temp_s2 = *(s32 *)((u8 *)arg0 + 0xB4); \
        temp_s3 = *(u16 *)((u8 *)arg0 + 0xB8); \
        temp_s1 = *(u16 *)((u8 *)arg0 + 0xBA); \
        temp_s4 = *(s32 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x20); \
        func_8015444C(arg0, &sp10, &sp14, &sp18); \
        v1 = *(void **)((u8 *)arg0 + 0x20); \
        *(s32 *)((u8 *)arg0 + 0xB4) = temp_s2; \
        *(u16 *)((u8 *)arg0 + 0xB8) = temp_s3; \
        *(u16 *)((u8 *)arg0 + 0xBA) = temp_s1; \
        *(u8 *)((u8 *)arg0 + 0xBC) = temp_s5; \
        *(u8 *)((u8 *)arg0 + 0xBD) = temp_s6; \
        *(u8 *)((u8 *)arg0 + 0xDC) = temp_s7; \
        ret = *(s32 *)((u8 *)v1 + 0x20); \
        *(s32 *)((u8 *)v1 + 0x20) = temp_s4; \
        return ret; \
    }

#define DEFINE_func_80171EC8() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80047948(s32 a0); \
    extern s32 func_8004787C(s32 a0); \
    extern s32 D_801151D4; \
    void func_80171EC8(s32 a0) { \
        s32 base = D_801151D4; \
        s32 s0; \
        s32 s1; \
        s32 v1; \
        s32 ang; \
        *(s8 *)(a0 + 0xA9) = 0x73; \
        ang = ratan2(*(s32 *)(base + 0x68) - *(s32 *)(base + 0x5C), \
                     *(s32 *)(base + 0x70) - *(s32 *)(base + 0x64)); \
        s0 = (ang + 0x800) & 0xFFF; \
        s0 = (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) - s0) & 0xFF8; \
        if (s0 == 0x400 || s0 == 0xC00) { \
            s1 = 0x80; \
        } else { \
            s32 t = -(func_80047948(s0) << 7); \
            if (t < 0) { \
                t += 0xFFF; \
            } \
            s1 = (t >> 12) + 0x80; \
        } \
        if (s1 < 0) { \
            s1 = 0; \
        } \
        if (!(s1 < 0x100)) { \
            s1 = 0xFF; \
        } \
        if (s0 == 0 || s0 == 0x800) { \
            v1 = 0x80; \
        } else { \
            s32 t = func_8004787C(s0); \
            if (t < 0) { \
                t += 0x1F; \
            } \
            v1 = (t >> 5) + 0x80; \
        } \
        if (v1 < 0) { \
            v1 = 0; \
        } \
        if (!(v1 < 0x100)) { \
            v1 = 0xFF; \
        } \
        *(s16 *)(a0 + 0xAE) = (v1 & 0xFF) | (s1 << 8); \
    }

#define DEFINE_func_8012BB3C() \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3) { \
        register s32 a __asm__("$17");   /* $s1 */ \
        register s32 div __asm__("$16"); /* $s0 */ \
        register s32 q __asm__("$3");    /* $v1 */ \
        register s32 d __asm__("$2");    /* $v0 */ \
        s32 ang; \
        s32 diff; \
        u32 cur; \
        a = arg2; \
        div = arg3; \
        ang = ratan2(*(s16 *)(arg0 + 0xA) - *(s16 *)(arg1 + 0xA), \
                     *(s16 *)(arg1 + 0x2) - *(s16 *)(arg0 + 0x2)); \
        ang = ang - 0x400; \
        __asm__ __volatile__("" : : "r"(ang)); \
        div = (s16)div; \
        a = a & 0xFFF; \
        cur = ang & 0xFFF; \
        if (a == cur) { \
            d = 0; \
        } else { \
            s32 t; \
            diff = cur - a; \
            if (0x800 < diff) { \
                t = a + 0x1000; \
                diff = cur - t; \
            } \
            if (diff < -0x800) { \
                t = a - 0x1000; \
                diff = cur - t; \
            } \
            if (diff >= 0) { \
                q = diff / div; \
                if (q == 0) { \
                    q = 1; \
                } \
            } else { \
                q = diff / div; \
                if (q == 0) { \
                    q = -1; \
                } \
            } \
            d = q; \
        } \
        return (s16)d; \
    }

#define DEFINE_func_80164F44() \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern void func_80165124(void *a0); \
    extern s32 func_80165140(s32 a0); \
    extern void func_801651B8(void *a0); \
    void func_80164F44(void *arg0) { \
        s32 iVar4; \
        s16 sVar2; \
        s16 sVar1; \
        s16 sVar3; \
        *(s16 *)((u8 *)arg0 + 0x62) = *(u16 *)((u8 *)arg0 + 0x62) + 4; \
        iVar4 = *(u16 *)((u8 *)arg0 + 0x60) + 0x40; \
        *(s16 *)((u8 *)arg0 + 0x60) = iVar4; \
        sVar2 = *(u16 *)((u8 *)arg0 + 0x2E) - iVar4; \
        *(s16 *)((u8 *)arg0 + 0x2E) = sVar2; \
        *(s16 *)((u8 *)arg0 + 0x2C) = sVar2; \
        if (sVar2 < 0x1000) { \
            *(s16 *)((u8 *)arg0 + 0x2E) = 0x1000; \
            *(s16 *)((u8 *)arg0 + 0x2C) = 0x1000; \
            *(s16 *)((u8 *)arg0 + 0x60) = 0x80; \
            func_80146E90((s32 *)arg0, 0xE); \
            func_80146CA0(arg0); \
        } \
        func_80165124(arg0); \
        sVar3 = 2; \
        if (*(s16 *)((u8 *)arg0 + 0x2C) < 0x2800) { \
            sVar1 = *(u16 *)((u8 *)arg0 + 0x66) + 1; \
        } else { \
            sVar3 = 3; \
            sVar1 = *(u16 *)((u8 *)arg0 + 0x66) + 1; \
        } \
        *(s16 *)((u8 *)arg0 + 0x66) = sVar1; \
        if (sVar1 == sVar3) { \
            func_80165140((s32)arg0); \
            *(s16 *)((u8 *)arg0 + 0x66) = 0; \
        } \
        func_801651B8(arg0); \
    }

#define DEFINE_func_80139680() \
    extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80052460(s32 a0, s32 a1, s32 a2); \
    void func_80139680(s32 arg0, u8 * arg1) \
    { \
        s32 buf[10]; \
        s32 var_s1; \
        var_s1 = (s32)*(u16 *)((u8 *)arg0 + 0x12) - (s32)*(u16 *)((u8 *)arg0 + 0x16); \
        if (var_s1 < 0) { \
            var_s1 += 4; \
        } \
        *(s32 *)((u8 *)buf + 0x00) = 0; \
        *(s16 *)((u8 *)buf + 0x0C) = GetTPage(0, 1, 0x1C0, 0x100); \
        *(s16 *)((u8 *)buf + 0x10) = *(u16 *)((u8 *)arg0 + 0x3C); \
        *(s16 *)((u8 *)buf + 0x12) = *(u16 *)((u8 *)arg0 + 0x3E); \
        *(u8 *)((u8 *)buf + 0x16) = 0x80; \
        *(u8 *)((u8 *)buf + 0x15) = 0x80; \
        *(u8 *)((u8 *)buf + 0x14) = 0x80; \
        { \
            u16 idx = *(u16 *)((u8 *)arg0 + 0x14); \
            s32 base = *(s16 *)((u8 *)arg0 + 0x30); \
            s16 val; \
            if (idx < 0x24) { \
                val = idx * 6 + base; \
            } else { \
                val = base + 0xD2; \
            } \
            *(s16 *)((u8 *)buf + 0x04) = val; \
        } \
        *(s16 *)((u8 *)buf + 0x06) = *(u16 *)((u8 *)arg0 + 0x32) + var_s1 * 0xC; \
        if (var_s1 != 0) { \
            *(s16 *)((u8 *)buf + 0x06) = *(s16 *)((u8 *)buf + 0x06) + var_s1 * 2; \
        } \
        *(s16 *)((u8 *)buf + 0x08) = 0xC; \
        *(s16 *)((u8 *)buf + 0x0A) = 0xC; \
        *(u8 *)((u8 *)buf + 0x0E) = 0xF0; \
        *(u8 *)((u8 *)buf + 0x0F) = 0; \
        func_80052460((s32)buf, arg1, (s32)*(u16 *)((u8 *)arg0 + 0x1A)); \
    }

#define DEFINE_func_801298F4() \
    extern unsigned short D_800B99F0; \
    void func_801298F4(void *arg0) { \
        register u8 *a __asm__("$7"); \
        register s32 base4C __asm__("$3"); \
        register u32 b __asm__("$4"); \
        register u16 f38 __asm__("$6"); \
        register u16 f3E __asm__("$5"); \
        register u32 sh __asm__("$2"); \
        u8 *p; \
        a = (u8 *) arg0; \
        base4C = *(s32 *)(a + 0x4C); \
        p = *(u8 **)(a + 0x50); \
        f38 = *(u16 *)(a + 0x38); \
        f3E = *(u16 *)(a + 0x3E); \
        base4C += 8; \
        p += 4; \
        b = *p++; *(s16 *)(a + 0x2) = (u16) b; \
        b = *p++; *(s16 *)(a + 0x4) = (u16) b; \
        b = *p++; *(u8 *)(a + 0x0) = b; \
        b = *p++; *(s32 *)(a + 0x8) = base4C; \
        *(s32 *)(a + 0xC) = (s32) p; \
        *(u8 *)(a + 0x1) = b; \
        sh = ((u32)(u8) *(u8 *)(base4C + 0x6) >> 7) << 0x18; \
        base4C = *(u16 *)(a + 0x3A); \
        b = *(u16 *)(a + 0x3C); \
        *(s16 *)(a + 0x14) = f38; \
        *(s16 *)(a + 0x1A) = f3E; \
        *(s16 *)(a + 0x16) = base4C; \
        *(s16 *)(a + 0x18) = b; \
        *(s32 *)(a + 0x10) = sh | 0x08000000; \
        if (D_800B99F0 == 0) { \
            *(s16 *)(a + 0x1E) = 0; \
            *(s16 *)(a + 0x1C) = 0; \
        } \
        *(u8 *)(a + 0x22) = 0x80; \
        *(u8 *)(a + 0x21) = 0x80; \
        *(u8 *)(a + 0x20) = 0x80; \
        *(s16 *)(a + 0x28) = 0xA0; \
        *(s16 *)(a + 0x2A) = 0x78; \
        *(s32 *)(a + 0x24) = (s32) a; \
        *(s16 *)(a + 0x2E) = 0x1000; \
        *(s16 *)(a + 0x2C) = 0x1000; \
        *(s32 *)(a + 0x30) = 0; \
    }

#define DEFINE_func_80139D04() \
    s32 func_80139D04(s32 a0, s32 a1) { \
        register u8 *p    __asm__("$8");   /* $t0 */ \
        register u32 div  __asm__("$9");   /* $t1 */ \
        register u32 acc  __asm__("$10");  /* $t2 */ \
        register u32 cnt  __asm__("$6");   /* $a2 */ \
        register u32 flag __asm__("$7");   /* $a3 */ \
        register u32 param_2 __asm__("$5"); /* $a1 */ \
        u32 q; \
        register u32 rem __asm__("$4");  /* $a0 */ \
        register u32 hi __asm__("$2");  /* $v0 */ \
        register u32 pm __asm__("$3");  /* $v1 */ \
        register u32 dm __asm__("$2");  /* $v0 */ \
        p = (u8 *)a0; \
        param_2 = (u32)a1; \
        div = 10000; \
        acc = 0; \
        flag = 0; \
        cnt = 5; \
        do { \
            q = (param_2 & 0xffff) / (div & 0xffff); \
            hi = acc << 4; \
            acc = q | hi; \
            __asm__ __volatile__("" : : "r"(acc)); \
            if ((flag & 0xffff) == 0) { \
                if ((acc & 0xffff) != 0) { \
                    flag = cnt; \
                } \
                if ((flag & 0xffff) != 0) goto store; \
            } else { \
            store: \
                *p = (u8)q; \
                p = p + 1; \
            } \
            pm = param_2 & 0xffff; \
            __asm__ __volatile__("" : : "r"(pm)); \
            dm = div & 0xffff; \
            rem = pm % dm; \
            div = dm / 10; \
            cnt = cnt - 1; \
            param_2 = rem; \
            if ((s32)cnt < 1) { \
                if ((flag & 0xffff) == 0) { \
                    *p = 0; \
                    flag = flag + 1; \
                } \
                return flag & 0xffff; \
            } \
        } while (1); \
    }

#define DEFINE_func_8016B114() \
    extern void func_8016B234(); \
    extern void func_800D22E4(s32 a0); \
    extern void func_80146C3C(void); \
    void func_8016B114(void *arg0) \
    { \
        s32 s1; \
        u32 state; \
        s32 cv; \
        s1 = *(s32 *)((u8 *)arg0 + 0x20); \
        if ((u32)*(s32 *)((u8 *)arg0 + 0x2C) < 6U) { \
            func_8016B234(); \
        } \
        state = *(u32 *)((u8 *)arg0 + 0x2C); \
        switch (state) { \
        case 6: \
        case 7: \
            cv = *(u8 *)((u8 *)s1 + 0x26) - 0x10; \
            *(u8 *)((u8 *)s1 + 0x26) = cv; \
            *(u8 *)((u8 *)s1 + 0x25) = cv; \
            *(u8 *)((u8 *)s1 + 0x24) = cv; \
            *(u16 *)((u8 *)arg0 + 0xA) = *(u16 *)((u8 *)arg0 + 0xA) - 2; \
            break; \
        case 1: \
        case 5: \
        { \
            register s32 r26 __asm__("$4"); \
            register s32 r14 __asm__("$2"); \
            register s32 r24 __asm__("$3"); \
            func_800D22E4((s32)arg0); \
            r26 = *(u16 *)((u8 *)arg0 + 0x26); \
            r14 = *(s32 *)((u8 *)arg0 + 0x14); \
            r24 = *(u16 *)((u8 *)arg0 + 0x24); \
            r26 += 1; \
            r14 += 0x18000; \
            r24 -= 0x10; \
            *(s32 *)((u8 *)arg0 + 0x14) = r14; \
            *(u16 *)((u8 *)arg0 + 0x26) = r26; \
            *(u16 *)((u8 *)arg0 + 0x24) = r24; \
            break; \
        } \
        default: \
        { \
            register s32 d26 __asm__("$2"); \
            register s32 dA  __asm__("$3"); \
            register s32 d24 __asm__("$4"); \
            d26 = *(u16 *)((u8 *)arg0 + 0x26); \
            dA  = *(u16 *)((u8 *)arg0 + 0xA); \
            d24 = *(u16 *)((u8 *)arg0 + 0x24); \
            d26 += 1; \
            dA  -= 2; \
            d24 -= 0x10; \
            *(u16 *)((u8 *)arg0 + 0xA) = dA; \
            *(u16 *)((u8 *)arg0 + 0x26) = d26; \
            *(u16 *)((u8 *)arg0 + 0x24) = d24; \
            break; \
        } \
        } \
        cv = *(s32 *)((u8 *)arg0 + 0x1C) - 1; \
        *(s32 *)((u8 *)arg0 + 0x1C) = cv; \
        if (cv == 0) { \
            ((void (*)(s32))func_80146C3C)((s32)arg0); \
        } \
    }

#define DEFINE_func_80169A4C() \
    extern s32  func_80017DC4(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32  func_80017758(void *a0, void *a1); \
    s32 func_80169A4C(s32 a0, s32 a1) { \
        void *arg0 = (void *)a0; \
        void *arg1 = (void *)a1; \
        u8 buf[0x5C];               /* spans $sp+0x10 .. $sp+0x6B */ \
        u8 *p = buf + 0x38;          /* $sp+0x48, passed to first 3 calls */ \
        u8 v1; \
        s8 v0; \
        u16 t2c; \
        register u8 *q __asm__("$4");    /* $sp+0x68, first call a0 */ \
        register s32 m5 __asm__("$3");   /* -5 -> $v1 */ \
        register s32 p5 __asm__("$2");   /* 5  -> $v0 */ \
        q = buf + 0x58; \
        __asm__("" : : "r"(q)); \
        m5 = -5; \
        __asm__("" : : "r"(m5)); \
        p5 = 5; \
        *(s16 *)(buf + 0x18) = p5;   /* 0x28 */ \
        *(s16 *)(buf + 0x10) = p5;   /* 0x20 */ \
        *(s16 *)(buf + 0x1a) = p5;   /* 0x2A */ \
        *(s16 *)(buf + 0x0a) = p5;   /* 0x1A */ \
        *(s16 *)(buf + 0x08) = m5;   /* 0x18 */ \
        *(s16 *)(buf + 0x00) = m5;   /* 0x10 */ \
        *(s16 *)(buf + 0x12) = m5;   /* 0x22 */ \
        *(s16 *)(buf + 0x02) = m5;   /* 0x12 */ \
        *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */ \
        *(s16 *)(buf + 0x14) = 0;    /* 0x24 */ \
        *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */ \
        *(s16 *)(buf + 0x04) = 0;    /* 0x14 */ \
        v1 = *(u8 *)((u8 *)arg0 + 0x30); \
        *(s32 *)(buf + 0x30) = 0x50000000;  /* 0x40 */ \
        v0 = (s8)(v1 >> 2); \
        *(u8 *)(buf + 0x2e) = v1;     /* 0x3E */ \
        *(u8 *)(buf + 0x2a) = v1;     /* 0x3A */ \
        *(u8 *)(buf + 0x26) = v1;     /* 0x36 */ \
        *(u8 *)(buf + 0x22) = v1;     /* 0x32 */ \
        *(s8 *)(buf + 0x2d) = v0;     /* 0x3D */ \
        *(s8 *)(buf + 0x29) = v0;     /* 0x39 */ \
        *(s8 *)(buf + 0x25) = v0;     /* 0x35 */ \
        *(s8 *)(buf + 0x21) = v0;     /* 0x31 */ \
        *(s8 *)(buf + 0x2c) = v0;     /* 0x3C */ \
        *(s8 *)(buf + 0x28) = v0;     /* 0x38 */ \
        *(s8 *)(buf + 0x24) = v0;     /* 0x34 */ \
        *(s8 *)(buf + 0x20) = v0;     /* 0x30 */ \
        t2c = *(u16 *)((u8 *)arg0 + 0x2c); \
        *(u16 *)(q + 0x02) = t2c;  /* 0x6A */ \
        *(u16 *)(q + 0x00) = t2c;  /* 0x68 */ \
        func_80017DC4(q, p); \
        func_80048EAC(arg1, p); \
        *(s32 *)(buf + 0x4c) = (s32)*(s16 *)((u8 *)arg0 + 6);   /* 0x5C */ \
        *(s32 *)(buf + 0x50) = (s32)*(s16 *)((u8 *)arg0 + 0xa); /* 0x60 */ \
        *(s32 *)(buf + 0x54) = (s32)*(s16 *)((u8 *)arg0 + 0xe); /* 0x64 */ \
        func_80017758(buf + 0x00, p); \
        *(s16 *)(buf + 0x00) = -7;   /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;    /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;    /* 0x18 */ \
        *(s16 *)(buf + 0x18) = 7;    /* 0x28 */ \
        *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;    /* 0x12 */ \
        *(s16 *)(buf + 0x0a) = 7;    /* 0x1A */ \
        *(s16 *)(buf + 0x12) = -7;   /* 0x22 */ \
        func_80017758(buf + 0x00, p); \
    }

#define DEFINE_func_8016C74C() \
    extern s32 VectorNormalSS(void *a0, void *a1); \
    void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) { \
        s32 r; s32 lim; s32 sh2; \
        sh2 = (s16)a2; \
        __asm__ __volatile__("" : "=r"(sh2) : "0"(sh2)); \
        __asm__ __volatile__("" : : "r"(a3)); \
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) + (*(s16 *)(a1 + 0x0) << sh2); \
        *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) + (*(s16 *)(a1 + 0x2) << sh2); \
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) + (*(s16 *)(a1 + 0x4) << sh2); \
        *(s16 *)(a1 + 0x0) = *(u16 *)(a0 + 0x12); \
        *(s16 *)(a1 + 0x2) = *(u16 *)(a0 + 0x16); \
        *(s16 *)(a1 + 0x4) = *(u16 *)(a0 + 0x1a); \
        lim = *(volatile s32 *)&a4; \
        __asm__ __volatile__("" ::: "memory"); \
        r = ((s32 (*)(void *))VectorNormalSS)((void *)a1); \
        if (lim < r) { \
            *(s32 *)(a0 + 0x10) = *(s16 *)(a1 + 0x0) << (s16)a3; \
            *(s32 *)(a0 + 0x14) = *(s16 *)(a1 + 0x2) << (s16)a3; \
            *(s32 *)(a0 + 0x18) = *(s16 *)(a1 + 0x4) << (s16)a3; \
        } \
    }

#define DEFINE_func_8012F68C() \
    extern void func_8012CBCC(s32 a0); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_80131C78(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_8012F68C(s32 arg0) { \
        s32 flag; \
        u32 cond; \
        flag = 0; \
        if (!(*(u32 *)(arg0 + 0xC4) & 2) && (*(u32 *)(arg0 + 0xB4) & 1)) { \
            if ((u8)((s32 (*)(s32))func_8012CBCC)(arg0) == 2) { \
                func_80131E00((struct S80131E00 *)arg0, 0x12); \
                return; \
            } \
            if (*(u8 *)(arg0 + 0xC2) != 0) { \
                cond = func_8012BEE8(arg0); \
            } else { \
                cond = *(u16 *)(arg0 + 0x72) & 0x4000; \
            } \
            if (cond != 0) { \
                flag = 1; \
            } \
            if (flag != 0) { \
                func_80131C78(arg0); \
            } \
        } \
        func_80131CA8(arg0, 5); \
    }

#define DEFINE_func_80164D4C() \
    extern s32 func_80164E40(void); \
    extern void func_80146CA0(void *a0); \
    void func_80164D4C(void *arg0) { \
        register s32 a __asm__("$16"); \
        register s32 iVar3 __asm__("$17"); \
        s16 sVar1; \
        a = (s32)arg0; \
        iVar3 = *(s32 *)(a + 0x20); \
        if (((s32 (*)(void))func_80164E40)() != 0) { \
            func_80146CA0((void *)a); \
        } else { \
            sVar1 = *(s16 *)(iVar3 + 0x1a) + 0x100; \
            *(s16 *)(iVar3 + 0x1a) = sVar1; \
            *(s16 *)(iVar3 + 0x18) = sVar1; \
        } \
    }

#define DEFINE_func_8016A890() \
    extern s32 func_8016A8FC(s32 a0); \
    extern void func_80146C3C(void); \
    void func_8016A890(s32 arg0) \
    { \
        s16 *p = *(s16 **)((u8 *)arg0 + 0x34); \
        if (*(s32 *)((u8 *)arg0 + 0x1C) < 4 && *(u16 *)p == 0x14) { \
            ((void (*)(void))func_8016A8FC)(); \
            *(s32 *)((u8 *)arg0 + 0x1C) = *(s32 *)((u8 *)arg0 + 0x1C) + 1; \
        } else { \
            ((void (*)(s32))func_80146C3C)(arg0); \
        } \
    }

#define DEFINE_func_8014AB7C() \
    extern void func_80162CCC(void); \
    extern s32 D_8011F9D0; \
    void func_8014AB7C(s32 arg0) { \
        u8 *p; \
        for (p = (u8 *)&D_8011F9D0; p < (u8 *)&D_8011F9D0 + 0x820; p += 0x68) { \
            if (*(u16 *)p == arg0) { \
                ((void (*)(u8 *))func_80162CCC)(p); \
            } \
        } \
    }

#define DEFINE_func_80165FA4() \
    extern void func_80013F3C(s32 a0); \
    extern void func_80020F34(s32 a0, s32 a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2) \
    { \
        s32 buf[8]; \
        func_80013F3C((s32)buf); \
        func_80020F34((s32)buf, *(s32 *)((u8 *)arg0 + 0x20) + 0x18); \
        ApplyMatrixSV(buf, arg1, arg1); \
        ApplyMatrixSV(buf, arg2, arg2); \
    }

#define DEFINE_func_801615C4() \
    extern void func_8014ED28(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern void func_8014FA04(s32 a0); \
    s32 func_801615C4(void * arg0, s32 arg1) \
    { \
        u32 acc; \
        acc = 0; \
        if (((arg1 & 1) == 0) && (((s32 (*)(void))func_8014ED28)() != 0)) { \
            func_80146D90(arg0); \
        } \
        if (*(s32 *)((u8 *)arg0 + 0x34) > 0) { \
            acc |= ((s32 (*)(s32))func_8014CC28)(arg0); \
        } \
        return acc | ((s32 (*)(s32))func_8014FA04)(arg0); \
    }

#define DEFINE_func_8015DD74() \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    int func_8015DD74(int arg0) \
    { \
        s16 sp18[4]; \
        s32 s0; \
        s0 = *(s32 *)(arg0 + 0x178); \
        if (s0 != 0) { \
            func_8014C1A0(arg0, s0); \
            func_80015978(s0 + 4, (s32 *)sp18); \
            sp18[3] = 0; \
            func_8014C4AC(s0, 9, func_80029AAC(), sp18, \
                          *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)); \
            *(s32 *)(arg0 + 0x178) = 0; \
        } \
    }

#define DEFINE_func_801699D0() \
    extern s32 func_80169A4C(s32 a0, s32 a1); \
    extern void func_800D22E4(s32 a0); \
    extern void func_80146C3C(void); \
    void func_801699D0(void *arg0) { \
        s32 temp_v1; \
        temp_v1 = *(s32 *)((u8 *)arg0 + 0x1C); \
        if (temp_v1 < 0xF) { \
            *(s32 *)((u8 *)arg0 + 0x30) = 0xC0 - temp_v1 * 8; \
            func_80169A4C((s32)arg0, (s32)arg0 + 0x38); \
            func_800D22E4((s32)arg0); \
            *(s32 *)((u8 *)arg0 + 0x14) = *(s32 *)((u8 *)arg0 + 0x14) + 0x10000; \
            *(s32 *)((u8 *)arg0 + 0x1C) = *(s32 *)((u8 *)arg0 + 0x1C) + 1; \
        } else { \
            ((void (*)(s32))func_80146C3C)((s32)arg0); \
        } \
    }

#define DEFINE_func_80148824() \
    extern s32 func_80047D3C(s32 a0); \
    s32 func_80148824(void *arg0) \
    { \
        register u32 t __asm__("$2"); \
        register s32 hi __asm__("$3"); \
        register s32 lo __asm__("$2"); \
        register s32 chi __asm__("$5"); \
        register s32 clo __asm__("$4"); \
        t = *(u16 *)((u8 *)arg0 + 0xAE); \
        hi = (t >> 8) - 0x80; \
        chi = hi; \
        __asm__ __volatile__("" : : "r"(chi)); \
        lo = (t & 0xFF) - 0x80; \
        clo = lo; \
        if (hi == 0) { \
            if (lo < 0) { \
                return (-clo) & 0xFF; \
            } \
            return clo & 0xFF; \
        } else if (lo == 0) { \
            if (hi < 0) { \
                return (-chi) & 0xFF; \
            } \
            return chi & 0xFF; \
        } \
        hi = hi * hi; \
        chi = lo * lo; \
        return func_80047D3C(hi + chi) & 0xFF; \
    }

#define DEFINE_func_80149C08() \
    extern u8 func_8014BEF8(void); \
    extern s32 func_80029178(s32 a0); \
    s32 func_80149C08(s32 arg0) { \
        s32 var_v0; \
        u32 temp; \
        if (*(u8*)(arg0 + 0x223) != 0) { var_v0 = 0; goto end; } \
        if (*(s16*)(arg0 + 0x1C8) != 0) { var_v0 = 0; goto end; } \
        if ((*(u32*)(arg0 + 0x44) & 0x404) != 0) { var_v0 = 0; goto end; } \
        if (((s32(*)(s32))func_8014BEF8)(arg0) == 0) { var_v0 = 0; goto end; } \
        if ((func_80029178(0x89) & 0xFF) == 0) { var_v0 = 0; goto end; } \
        temp = *(u16*)(arg0 + 0xAC) & 0x10; \
        var_v0 = temp != 0; \
    end: \
        return var_v0; \
    }

#define DEFINE_func_80160C28() \
    extern s32 func_80161208(); \
    extern void func_80146CA0(void *a0); \
    void func_80160C28(void *arg0) \
    { \
        s32 p; \
        s32 q; \
        register void *a __asm__("$4"); \
        if (func_80161208() == 0) { \
            *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000; \
            p = *(s32 *)((u8 *)arg0 + 0x20); \
            *(u16 *)((u8 *)p + 0x10) = \
                (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff; \
            q = *(s32 *)((u8 *)arg0 + 0x20); \
            if (*(s16 *)((u8 *)q + 0x10) < 0xc00) { \
                a = arg0; \
                __asm__ __volatile__("" : : "r"(a)); \
                *(u16 *)((u8 *)q + 0x10) = 0xc00; \
                *(u16 *)((u8 *)a + 0xb8) = 1; \
                func_80146CA0(a); \
            } \
        } \
    }

#define DEFINE_func_8016E5F4() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8012EFB8(s32 a0); \
    extern void func_80146C3C(void); \
    extern void func_80015954(s32 a0, s32 a1); \
    void func_8016E5F4(s32 arg0) { \
        s32 sp10; \
        func_80015978(arg0 + 4, &sp10); \
        if ((((s32 (*)(s32, s32))func_8012EFB8)((s32)&sp10, (s32)&sp10) & 0xFFFFEFFF) != 0) { \
            ((void (*)(s32))func_80146C3C)(arg0); \
        } else { \
            func_80015954((s32)&sp10, arg0 + 4); \
            *(s16 *)((u8 *)arg0 + 0x10) = 0x100; \
            *(s16 *)((u8 *)arg0 + 0x12) = 0; \
            *(s16 *)((u8 *)arg0 + 0x14) = 0; \
            *(s16 *)((u8 *)arg0 + 0x16) = 0x80; \
            *(s16 *)((u8 *)arg0 + 2) = *(u16 *)((u8 *)arg0 + 2) + 1; \
        } \
    }

#define DEFINE_func_80175590() \
    extern void func_801757A0(s32 a0); \
    extern short D_800B9A02; \
    void func_80175590(void *arg0) { \
        u8 temp_a0; \
        register s16 temp_v1 __asm__("$3"); \
        s32 temp_v0; \
        temp_a0 = *(u8 *)((u8 *)arg0 + 5); \
        temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0; \
        temp_v1 = -(temp_v0 & 0xFF); \
        *(u8 *)((u8 *)arg0 + 6) = (u8)temp_v0; \
        __asm__ __volatile__("" : : : "memory"); \
        temp_v0 = *(u8 *)((u8 *)arg0 + 6); \
        *(u8 *)((u8 *)arg0 + 5) = (u8)(temp_a0 + 0xFF); \
        *(s16 *)((u8 *)arg0 + 0x10) = temp_v1; \
        *(s16 *)((u8 *)arg0 + 0xC) = temp_v1; \
        *(s16 *)((u8 *)arg0 + 0x16) = (s16)temp_v0; \
        *(s16 *)((u8 *)arg0 + 0x12) = (s16)temp_v0; \
        *(s16 *)((u8 *)arg0 + 0xE) = (s16)temp_v0; \
        *(s16 *)((u8 *)arg0 + 0x14) = (s16)temp_v0; \
        func_801757A0((s32)D_800B9A02); \
        if (*(u8 *)((u8 *)arg0 + 5) == 0) { \
            *(u8 *)((u8 *)arg0 + 8) = 0; \
            *(u8 *)((u8 *)arg0 + 1) = (u8)(*(u8 *)((u8 *)arg0 + 1) + 1); \
        } \
    }

#define DEFINE_func_80145C54() \
    extern s32 func_800291B4(s32 arg); \
    extern void func_800291A0(s32, s32); \
    void func_80145C54(void) { \
        register s32 a1 __asm__("$5"); \
        register s32 v1 __asm__("$3"); \
        s32 s0; \
        a1 = func_800291B4(0x4A) & 0xFF; \
        if (a1 >= 0x20) { \
            v1 = a1 + 1; \
            a1 = v1; \
            if ((v1 & 0xF) == 0) { \
                a1 = (u32)v1 >> 4; \
            } \
            s0 = a1 & 0xFF; \
            func_800291A0(0x4A, s0); \
            func_800291A0(0x50, s0); \
        } \
        a1 = func_800291B4(0x4D) & 0xFF; \
        if (a1 >= 0x20) { \
            v1 = a1 + 1; \
            a1 = v1; \
            if ((v1 & 0xF) == 0) { \
                a1 = (u32)v1 >> 4; \
            } \
            func_800291A0(0x4D, a1 & 0xFF); \
        } \
    }

#define DEFINE_func_80149E94() \
    extern u8 D_801202A0[]; \
    extern s32 func_8016F1AC(void); \
    extern s32 func_80149F2C(s32 a0, s32 a1); \
    s32 func_80149E94(s32 arg0) { \
        u8 *p; \
        if ((func_8016F1AC() == 0) && (*(u8 *)(arg0 + 0x1C5) != 0)) { \
            *(u8 *)(arg0 + 0x1C5) = 0; \
            for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) { \
                if (func_80149F2C(arg0, (s32)p) != 0) { \
                    return 1; \
                } \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80142C9C() \
    extern void func_8012CBF4(s32 a0); \
    void func_80142C9C(s32 * arg0) \
    { \
        u32 uVar1; \
        if (*(s16 *)((u8 *)arg0 + 0x102) < 2) { \
            uVar1 = ((s32 (*)(void))func_8012CBF4)(); \
            if (0x180000 < *(s32 *)((u8 *)arg0 + 0x14)) { \
                *(s32 *)((u8 *)arg0 + 0x14) = 0x180000; \
            } \
            if (((uVar1 & 0x6000) != 0) || (0x100 < *(s16 *)((u8 *)arg0 + 0xA))) { \
                if (*(s16 *)((u8 *)arg0 + 0x102) == 0) { \
                    *(s32 *)((u8 *)arg0 + 0x14) = 0xFFF80000; \
                } \
                *(s16 *)((u8 *)arg0 + 0x102) = *(s16 *)((u8 *)arg0 + 0x102) + 1; \
            } \
        } \
    }

#define DEFINE_func_8014A2E4() \
    extern u8 D_801202A0[]; \
    extern s32 func_8014C278(s32 a0, s32 a1, s32 a2); \
    s32 func_8014A2E4(s32 a0) { \
        register s32 a0v __asm__("$18"); \
        register u32 i __asm__("$17"); \
        register u8 *p __asm__("$16"); \
        a0v = a0; \
        i = 0; \
        p = D_801202A0; \
        do { \
            if (*(u16 *)(p + 0x0) != 0 \
                && (*(u16 *)(p + 0x5C) & 0x8000) \
                && *(s16 *)(p + 0xAA) != 0 \
                && func_8014C278(a0v, (s32)p, 0x30) != 0) { \
                return (s32)p; \
            } \
            i++; \
            p += 0x10C; \
        } while (i < 0x60); \
        return 0; \
    }

#define DEFINE_func_8014C308() \
    s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { \
        register s32 v0 __asm__("$2"); \
        register s32 v1 __asm__("$3"); \
        if (*(u16 *)((u8 *)arg1 + 0x0) == 0) { \
            return 0; \
        } \
        if (*(s32 *)((u8 *)arg1 + 0x58) == 0) { \
            return 0; \
        } \
        if (*(u16 *)((u8 *)arg1 + 0x5E) != arg2) { \
            if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000) { \
                return 0; \
            } \
            if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) { \
                v0 = 1; \
                v1 = 9; \
                if (arg2 == v1) return v0; \
                v1 = 0x11; \
                if (arg2 == v1) return v0; \
                v1 = 0x29; \
                if (arg2 == v1) return v0; \
                v1 = 0xA; \
                if (arg2 == v1) return v0; \
                return *(s32 *)((u8 *)arg0 + 0x178) != arg1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80146B9C() \
    extern u16 D_8011DA28; \
    s32 func_80146B9C(void * arg0) \
    { \
        register u8 *p __asm__("$6"); \
        register u8 *q __asm__("$5"); \
        u8 *end; \
        p = (u8 *)&D_8011DA28; \
        end = p - 0x9F8; \
        if ((u32)p >= (u32)end) { \
            q = p + 0x30; \
            do { \
                if (*(u16 *)p == 0) { \
                    *(s32 *)(q + 0x4) = *(s32 *)((u8 *)arg0 + 0x8); \
                    *(s16 *)p = *(u16 *)((u8 *)arg0 + 0x0); \
                    *(s16 *)(q - 0x2A) = *(u16 *)((u8 *)arg0 + 0x2); \
                    *(s16 *)(q - 0x26) = *(u16 *)((u8 *)arg0 + 0x4); \
                    *(s16 *)(q - 0x22) = *(u16 *)((u8 *)arg0 + 0x6); \
                    *(s32 *)(q - 0x4) = *(s32 *)((u8 *)arg0 + 0xC); \
                    *(s32 *)(q + 0x0) = *(s32 *)((u8 *)arg0 + 0x10); \
                    return (s32)p; \
                } \
                p -= 0x58; \
                q -= 0x58; \
            } while ((u32)p >= (u32)end); \
        } \
        return 0; \
    }

#define DEFINE_func_80168540() \
    extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80166690(); \
    extern void func_80146C3C(void); \
    void func_80168540(s32 a0) { \
        s32 v0; \
        if (((*(u32 *)(*(s32 *)(a0 + 0x34) + 0x44) & 2) == 0) || \
            (v0 = *(s32 *)(a0 + 0x1c) - 1, *(s32 *)(a0 + 0x1c) = v0, v0 == 0)) { \
            *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1; \
            func_80166994(a0, 2, 2, 0); \
        } else { \
            func_80166994(a0, 1, 2, (s32)*(s16 *)(a0 + 0x30)); \
        } \
        if ((short)func_80166690(2, 1) == 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_8014AC10() \
    extern void func_80016714(void *a0, s32 a1); \
    extern s32 D_8011D030; \
    void func_8014AC10(s32 arg0) { \
        u8 *p; \
        u8 *end; \
        u8 *t; \
        s32 one; \
        void *a0; \
        s32 a1; \
        p = (u8 *)&D_8011D030; \
        t = p + 0xA50; \
        if (p < t) { \
            one = 1; \
            end = t; \
            do { \
                if (*(u16 *)p == arg0) { \
                    a0 = *(void **)(p + 0x20); \
                    if (a0 != 0) { \
                        a1 = 0x38; \
                        if (*(u16 *)a0 == one) { \
                            a1 = 0x84; \
                        } \
                        func_80016714(a0, a1); \
                    } \
                    func_80016714(p, 0x58); \
                } \
                p += 0x58; \
            } while (p < end); \
        } \
    }

#define DEFINE_func_80168328() \
    extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80166690(); \
    extern void func_80146C3C(void); \
    void func_80168328(s32 arg0) { \
        s32 a1; \
        s32 a2; \
        s32 a3; \
        s32 v; \
        if (((*(s32 *)(*(s32 *)(arg0 + 0x34) + 0x44) & 2) == 0) || \
            (v = *(s32 *)(arg0 + 0x1c) - 1, *(s32 *)(arg0 + 0x1c) = v, v == 0)) { \
            a1 = 2; \
            a3 = 0; \
            a2 = *(s16 *)(arg0 + 0x2c); \
            *(s16 *)(arg0 + 2) = *(s16 *)(arg0 + 2) + 1; \
            func_80166994(arg0, a1, a2, a3); \
        } else { \
            a2 = *(s16 *)(arg0 + 0x2c); \
            a3 = *(s16 *)(arg0 + 0x30); \
            a1 = 1; \
            func_80166994(arg0, a1, a2, a3); \
        } \
        if ((s16)func_80166690(*(s16 *)(arg0 + 0x2c), *(s16 *)(arg0 + 0x28)) == 0) { \
            ((void (*)(s32))func_80146C3C)(arg0); \
        } \
    }

#define DEFINE_func_801756E4() \
    extern void func_80175DA8(s32 a0); \
    extern void func_80175AB8(s32 a0); \
    extern void func_80176144(s32 a0); \
    extern short D_800B9A02; \
    void func_801756E4(s32 arg0) { \
        register s32 a __asm__("$17") = arg0; \
        register short *p __asm__("$16"); \
        s32 f5; \
        s32 sum; \
        s16 neg; \
        s32 b6; \
        p = &D_800B9A02; \
        f5 = *(u8 *)(a + 5); \
        sum = *(u8 *)(a + 6) + f5; \
        neg = -(s16)(sum & 0xFF); \
        *(u8 *)(a + 6) = sum; \
        __asm__ __volatile__("" : : : "memory"); \
        b6 = *(u8 *)(a + 6); \
        *(u8 *)(a + 5) = (u8)f5 + 0xFF; \
        *(s16 *)(a + 0x10) = neg; \
        *(s16 *)(a + 0xc) = neg; \
        *(u16 *)(a + 0x16) = b6; \
        *(u16 *)(a + 0x12) = b6; \
        *(u16 *)(a + 0xe) = b6; \
        *(u16 *)(a + 0x14) = b6; \
        func_80175DA8(*p); \
        func_80175AB8(*p); \
        func_80176144(*p); \
        if (*(u8 *)(a + 5) == 0) { \
            *(u8 *)(a + 8) = 0; \
            *(u8 *)(a + 1) = *(u8 *)(a + 1) + 1; \
        } \
    }

#define DEFINE_func_8017209C() \
    extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80172170(s32 a0, s32 a1); \
    s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3) { \
        s32 ret; \
        register s32 ang  __asm__("$3");    /* $v1 */ \
        register s32 a3p  __asm__("$19");   /* $s3 = arg3 */ \
        register s32 a2p  __asm__("$20");   /* $s4 = arg2 */ \
        a3p = arg3; \
        a2p = arg2; \
        ret = func_8017248C((s32)arg0, (s32)arg1); \
        if (ret != 0) { \
            func_80146D90((s32)arg0); \
            return ret; \
        } \
        ang = (ratan2((s32)*(s16 *)((u8 *)arg1 + 0) - (s32)*(s16 *)((u8 *)arg0 + 6), \
                             (s32)*(s16 *)((u8 *)arg1 + 4) - (s32)*(s16 *)((u8 *)arg0 + 0xE)) \
               + 0x800) & 0xFFF; \
        if (a3p != 0) { \
            ang = (s16)func_80012DBC((s32)*(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12), \
                                     ang, (s16)a3p, 1); \
        } \
        *(s16 *)(*(s32 *)((u8 *)arg0 + 0x20) + 0x12) = ang; \
        func_80172170((s32)arg0, a2p & 0xFF); \
        return 0; \
    }

#define DEFINE_func_801696D8() \
    extern s32  func_80017DC4(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32  func_80017758(void *a0, void *a1); \
    void func_801696D8(s32 a0, s32 a1) { \
        void *arg0 = (void *)a0; \
        void *arg1 = (void *)a1; \
        u8 buf[0x5C];               /* spans $sp+0x10 .. $sp+0x6B */ \
        u8 *p = buf + 0x38;          /* $sp+0x48, passed to first 3 calls */ \
        u8 v1; \
        u8 v0; \
        u8 a1b; \
        u16 t2c; \
        u8 *q = buf + 0x58;          /* $sp+0x68, first call a0 */ \
        *(s16 *)(buf + 0x00) = 8;    /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;    /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;    /* 0x18 */ \
        *(s16 *)(buf + 0x18) = -8;   /* 0x28 */ \
        *(s16 *)(buf + 0x0a) = 2;    /* 0x1A */ \
        *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;    /* 0x12 */ \
        *(s16 *)(buf + 0x12) = -2;   /* 0x22 */ \
        *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */ \
        *(s16 *)(buf + 0x14) = 0;    /* 0x24 */ \
        *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */ \
        *(s16 *)(buf + 0x04) = 0;    /* 0x14 */ \
        v1 = *(u8 *)((u8 *)arg0 + 0x30); \
        *(s32 *)(buf + 0x30) = 0x50000000;  /* 0x40 */ \
        v0 = (u8)(v1 >> 1); \
        a1b = (u8)(v0 >> 2); \
        *(u8 *)(buf + 0x2a) = v1;     /* 0x3A */ \
        *(u8 *)(buf + 0x26) = v1;     /* 0x36 */ \
        *(u8 *)(buf + 0x2e) = v0;     /* 0x3E */ \
        *(u8 *)(buf + 0x22) = v0;     /* 0x32 */ \
        *(u8 *)(buf + 0x29) = v0;     /* 0x39 */ \
        *(u8 *)(buf + 0x25) = v0;     /* 0x35 */ \
        *(u8 *)(buf + 0x28) = v0;     /* 0x38 */ \
        *(u8 *)(buf + 0x24) = v0;     /* 0x34 */ \
        *(u8 *)(buf + 0x2d) = a1b;    /* 0x3D */ \
        *(u8 *)(buf + 0x21) = a1b;    /* 0x31 */ \
        *(u8 *)(buf + 0x2c) = a1b;    /* 0x3C */ \
        *(u8 *)(buf + 0x20) = a1b;    /* 0x30 */ \
        t2c = *(u16 *)((u8 *)arg0 + 0x2c); \
        *(u16 *)(q + 0x02) = t2c;  /* 0x6A */ \
        *(u16 *)(q + 0x00) = t2c;  /* 0x68 */ \
        func_80017DC4(q, p); \
        func_80048EAC(arg1, p); \
        *(s32 *)(buf + 0x4c) = (s32)*(s16 *)((u8 *)arg0 + 6);   /* 0x5C */ \
        *(s32 *)(buf + 0x50) = (s32)*(s16 *)((u8 *)arg0 + 0xa); /* 0x60 */ \
        *(s32 *)(buf + 0x54) = (s32)*(s16 *)((u8 *)arg0 + 0xe); /* 0x64 */ \
        func_80017758(buf + 0x00, p); \
        *(s16 *)(buf + 0x00) = 2;    /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;    /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;    /* 0x18 */ \
        *(s16 *)(buf + 0x18) = -2;   /* 0x28 */ \
        *(s16 *)(buf + 0x0a) = 8;    /* 0x1A */ \
        *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;    /* 0x12 */ \
        *(s16 *)(buf + 0x12) = -8;   /* 0x22 */ \
        func_80017758(buf + 0x00, p); \
    }

#define DEFINE_func_8016E460() \
    extern s32  func_80017DC4(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32  func_80017758(void *a0, void *a1); \
    void func_8016E460(void *arg0, void *arg1) { \
        u8 buf[0x5C];               /* spans $sp+0x10 .. $sp+0x6B */ \
        u8 *p = buf + 0x38;          /* $sp+0x48, passed to calls */ \
        u8 *q = buf + 0x58;          /* $sp+0x68, first call a0 */ \
        u8 v1; \
        u8 v0; \
        u8 w; \
        u16 t2c; \
        s32 c7  = 7; \
        s32 cm7 = -7; \
        s32 c3  = 3; \
        s32 cm3 = -3; \
        *(s16 *)(buf + 0x00) = c7;    /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;     /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;     /* 0x18 */ \
        *(s16 *)(buf + 0x18) = cm7;   /* 0x28 */ \
        *(s16 *)(buf + 0x0a) = c3;    /* 0x1A */ \
        *(s16 *)(buf + 0x1a) = 0;     /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;     /* 0x12 */ \
        *(s16 *)(buf + 0x12) = cm3;   /* 0x22 */ \
        *(s16 *)(buf + 0x1c) = 0;     /* 0x2C */ \
        *(s16 *)(buf + 0x14) = 0;     /* 0x24 */ \
        *(s16 *)(buf + 0x0c) = 0;     /* 0x1C */ \
        *(s16 *)(buf + 0x04) = 0;     /* 0x14 */ \
        v1 = *(u8 *)((u8 *)arg0 + 0x30); \
        *(s32 *)(buf + 0x30) = 0x50000000;  /* 0x40 */ \
        v0 = v1 >> 2; \
        w  = v0 >> 2; \
        *(u8 *)(buf + 0x2a) = v1;     /* 0x3A */ \
        *(u8 *)(buf + 0x26) = v1;     /* 0x36 */ \
        *(u8 *)(buf + 0x28) = v1;     /* 0x38 */ \
        *(u8 *)(buf + 0x24) = v1;     /* 0x34 */ \
        *(u8 *)(buf + 0x29) = v0;     /* 0x39 */ \
        *(u8 *)(buf + 0x25) = v0;     /* 0x35 */ \
        *(u8 *)(buf + 0x2c) = w;      /* 0x3C */ \
        *(u8 *)(buf + 0x20) = w;      /* 0x30 */ \
        *(u8 *)(buf + 0x2e) = w;      /* 0x3E */ \
        *(u8 *)(buf + 0x22) = w;      /* 0x32 */ \
        *(u8 *)(buf + 0x2d) = w;      /* 0x3D */ \
        *(u8 *)(buf + 0x21) = w;      /* 0x31 */ \
        t2c = *(u16 *)((u8 *)arg0 + 0x2c); \
        *(u16 *)(q + 0x02) = t2c;  /* 0x6A */ \
        *(u16 *)(q + 0x00) = t2c;  /* 0x68 */ \
        func_80017DC4(q, p); \
        func_80048EAC(arg1, p); \
        *(s32 *)(buf + 0x4c) = (s32)*(s16 *)((u8 *)arg0 + 6);   /* 0x5C */ \
        *(s32 *)(buf + 0x50) = (s32)*(s16 *)((u8 *)arg0 + 0xa); /* 0x60 */ \
        *(s32 *)(buf + 0x54) = (s32)*(s16 *)((u8 *)arg0 + 0xe); /* 0x64 */ \
        func_80017758(buf + 0x00, p); \
        *(s16 *)(buf + 0x00) = c3;    /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;     /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;     /* 0x18 */ \
        *(s16 *)(buf + 0x18) = cm3;   /* 0x28 */ \
        *(s16 *)(buf + 0x0a) = c7;    /* 0x1A */ \
        *(s16 *)(buf + 0x1a) = 0;     /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;     /* 0x12 */ \
        *(s16 *)(buf + 0x12) = cm7;   /* 0x22 */ \
        func_80017758(buf + 0x00, p); \
    }

#define DEFINE_func_8015AD08() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8015AD3C(void *a0); \
    void func_8015AD08(void *arg0) \
    { \
        func_80147078((s32 *)arg0, 2); \
        func_8015AD3C(arg0); \
    }

#define DEFINE_func_8015D4B4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_8015D4E8(s16 *a0); \
    void func_8015D4B4(s16 *a0) { \
        func_80147078((s32 *)a0, 0xD); \
        func_8015D4E8(a0); \
    }

#define DEFINE_func_8015E184() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_8015E1B8(s32 a0); \
    void func_8015E184(s32 *arg0) \
    { \
        func_80147078(arg0, 0x10); \
        func_8015E1B8((s32)arg0); \
    }

#define DEFINE_func_8015EDD4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_8015EE08(s32 a0); \
    void func_8015EDD4(s32 *arg0) { \
        func_80147078(arg0, 0x12); \
        func_8015EE08((s32)arg0); \
    }

#define DEFINE_func_8015F7A0() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_8015F7D4(s32 a0); \
    void func_8015F7A0(s32 *arg0) { \
        func_80147078(arg0, 0x15); \
        func_8015F7D4((s32)arg0); \
    }

#define DEFINE_func_80160B00() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern s32 func_80160B34(s32 a0); \
    void func_80160B00(s32 *arg0) { \
        func_80147078(arg0, 0x1D); \
        func_80160B34((s32)arg0); \
    }

#define DEFINE_func_8015ACC4() \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8014ED28(s32 a0); \
    extern void func_8014FA04(s32 a0); \
    extern void func_8015ADB0(s32 a0); \
    void func_8015ACC4(s32 *arg0) { \
        func_80147078(arg0, 2); \
        func_8014ED28((s32)arg0); \
        func_8014FA04((s32)arg0); \
        func_8015ADB0((s32)arg0); \
    }

#define DEFINE_func_8015430C() \
    extern s32 func_801549F8(s32 a0, s32 a1, s32 a2); \
    extern void func_80154418(void *a0); \
    void func_8015430C(u8 *arg0, s32 arg1, s32 arg2) { \
        *(s32 *)(arg0 + 0xB4) = arg1; \
        *(s16 *)(arg0 + 0xBA) = 1; \
        *(s16 *)(arg0 + 0xB8) = 1; \
        *(s8 *)(arg0 + 0xBC) = arg2; \
        *(s8 *)(arg0 + 0xBD) = arg2; \
        *(s8 *)(arg0 + 0xDC) = func_801549F8((s32)arg0, arg1, arg2); \
        func_80154418(arg0); \
    }

#define DEFINE_func_8014DCE0() \
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); \
    s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2) { \
        struct Quad buf; \
        register s32 i __asm__("$17"); \
        register s32 s0 __asm__("$16"); \
        buf = *(struct Quad *)(*(u32 *)(arg0 + 0x58) & 0xFFFFFFF); \
        i = 0; \
        s0 = arg2; \
        do { \
            s32 r; \
            r = func_80135888(*(s32 *)(arg0 + 0x20), (s32)&buf, arg1, s0); \
            i += 1; \
            if (r == 0) { \
                s0 += 8; \
            } else { \
                return 1; \
            } \
        } while (i < 3); \
        return 0; \
    }

#define DEFINE_func_80147514() \
    extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2); \
    extern s32 func_800129CC(s32 a0, s32 a1); \
    void func_80147514(s32 arg0) { \
        s16 buf[8]; \
        *(struct V4s80147514 *)buf = *(struct V4s80147514 *)(arg0 + 0x120); \
        if (((u16)buf[0] | (u16)buf[1] | (u16)buf[2]) == 0) { \
            buf[1] = -0xFFF; \
        } \
        if (*(s16 *)(arg0 + 0x12E) != 0) { \
            buf[0] = (u16)buf[0] + *(u16 *)(arg0 + 0x128); \
            buf[1] = (u16)buf[1] + *(u16 *)(arg0 + 0x12A); \
            buf[2] = (u16)buf[2] + *(u16 *)(arg0 + 0x12C); \
        } \
        *(s16 *)(arg0 + 0x118) = func_80012C6C(*(s16 *)(arg0 + 0x118), buf[0], 8); \
        *(s16 *)(arg0 + 0x11A) = func_80012C6C(*(s16 *)(arg0 + 0x11A), buf[1], 8); \
        *(s16 *)(arg0 + 0x11C) = func_80012C6C(*(s16 *)(arg0 + 0x11C), buf[2], 8); \
        buf[0] = *(u16 *)(arg0 + 0x118); \
        buf[1] = *(u16 *)(arg0 + 0x11A); \
        buf[2] = *(u16 *)(arg0 + 0x11C); \
        func_800129CC((s32)buf, arg0 + 0x100); \
    }

#define DEFINE_func_80148C9C() \
    s32 func_80148C9C(s32 a0, s32 a1) { \
        Obj *p = *(Obj **)((s32)a0 + 0x20); \
        p->field_0x12 = (a1 + 0x400) & 0xFFF; \
        return 1; \
    }

#define DEFINE_func_801593E4() \
    void func_801593E4(A801593E4 *a0) { \
        S801593E4 *v1 = a0->p20; \
        v1->field12 = (v1->field12 + 0x16) & 0xFFF; \
    }

#define DEFINE_func_8016B964() \
    void func_8016B964(SrcB964 *a0, DstB964 *a1) { \
        a1->h8 = a0->h6; \
        a1->hA = a0->hA; \
        a1->hC = 3; \
    }

#define DEFINE_func_8014C118() \
    extern u8 D_801202A0[]; \
    s32 func_8014C118(void * a0, s32 a1, s32 a2) \
    { \
        Entry8014C118 *p; \
        s32 i; \
        i = 0; \
        a2 = (s16)a2; \
        p = (Entry8014C118 *)D_801202A0; \
        do { \
            if (p->unk0 == a1) { \
                if (p->unk70 == a2) { \
                    return (s32)p; \
                } \
            } \
            i++; \
            p++; \
        } while ((u32)i < 0x60); \
        return 0; \
    }

#define DEFINE_func_80153978() \
    extern s32 func_80133784(s32 a0, void *src, s32 dst); \
    extern s32 func_801539F8(s32 a0, void *a1); \
    s32 func_80153978(s32 a0, u16 *src) { \
        Buf80153978 buf; \
        buf.unk0 = src[0]; \
        buf.unk2 = src[1] + 0x1F; \
        buf.unk4 = src[2]; \
        if (func_80133784(0, src, (s32)&buf) == 0x2000 && \
            buf.unk6 == 0 && \
            func_801539F8(a0, &buf) == 0) { \
            return 0; \
        } \
        return 1; \
    }

#define DEFINE_func_8013E4B4() \
    extern void func_8012C750(void *a0); \
    extern u8 *D_801274C8; \
    extern void *D_801274CC; \
    void func_8013E4B4(void) { \
        u8 *s0; \
        Ent *p; \
        s32 i; \
        s0 = D_801274C8; \
        if (s0 != 0) { \
            if (*(u16 *)(s0 + 6) != 0) { \
                do { \
                    func_8012C750(s0); \
                    s0 += 0x14; \
                } while (*(u16 *)(s0 + 6) != 0); \
            } \
        } \
        s0 = (u8 *)D_801274CC; \
        if (s0 != 0) { \
            p = (Ent *)(s0 + 6); \
            for (i = 0; p[i].guard != 0; i++) { \
                p[i].field &= 0x7FFF; \
            } \
        } \
    }

#define DEFINE_func_8014A238() \
    extern s32 func_8014C278(s32 a0, s32 a1, s32 a2); \
    extern s32 func_8014C2B0(void *a0, void *a1, s32 a2); \
    extern u8 D_801202A0[]; \
    s32 func_8014A238(s32 arg0) { \
        u32 i; \
        Entry8014A238 *p; \
        for (i = 0; i < 0x60; i++) { \
            p = &((Entry8014A238 *)D_801202A0)[i]; \
            if ((p->f_0 != 0) && (p->f_AA != 0) && \
                (func_8014C278(arg0, (s32)p, 0x30) != 0) && \
                (func_8014C2B0((void *)arg0, (void *)p, 0x200) != 0)) { \
                return (s32)p; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8017AD0C() \
    extern void MoveImage(void *a0, s32 a1, s32 a2); \
    s32 func_8017AD0C(s32 arg0) \
    { \
        Rect rect; \
        s32 var_v0; \
        s32 var_v1; \
        arg0 = arg0 - 1; \
        rect.x = ((arg0 & 3) * 0x10) + 0x280; \
        var_v0 = arg0; \
        if (arg0 < 0) { \
            var_v0 = arg0 + 3; \
        } \
        rect.y = (var_v0 >> 2) + 0x1F8; \
        rect.w = 0x10; \
        rect.h = 1; \
        MoveImage(&rect, 0x160, 0x1C9); \
        if (arg0 == 0x18) { \
            rect.x = 0x2C0; \
            rect.y = 0x1D0; \
        } else { \
            rect.x = ((arg0 & 7) * 8) + 0x280; \
            var_v1 = arg0; \
            if (arg0 < 0) { \
                var_v1 = arg0 + 7; \
            } \
            rect.y = (var_v1 >> 3) * 0x28 + 0x180; \
        } \
        rect.w = 0x20; \
        rect.h = 0x28; \
        __asm__ __volatile__("" ::: "memory"); \
        MoveImage(&rect, 0x1C8, 0x190); \
    }

#define DEFINE_func_80168664() \
    extern Blk20 D_800AE620; \
    extern s32  RotMatrixX(s32 a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_80168664(void *arg0) { \
        s32 iVar3; \
        void *blk; \
        iVar3 = *(s32 *)((u8 *)arg0 + 0x34); \
        *(s32 *)((u8 *)arg0 + 0x1c) = 0x20; \
        *(s16 *)((u8 *)arg0 + 0x10) = 0x80; \
        *(s16 *)((u8 *)arg0 + 0x12) = 0; \
        *(s32 *)((u8 *)arg0 + 0x30) = 0x1800; \
        *(Blk20 *)((u8 *)arg0 + 0x38) = D_800AE620; \
        blk = (u8 *)arg0 + 0x38; \
        RotMatrixX(0x400, blk); \
        func_80048EAC((void *)(*(s32 *)((u8 *)iVar3 + 0x20) + 0x34), blk); \
        func_801670E4((s32)arg0, -6, -0x44, -0x18); \
        *(s16 *)((u8 *)arg0 + 2) = *(s16 *)((u8 *)arg0 + 2) + 1; \
    }

#define DEFINE_func_80155F80() \
    extern void func_80154A74(s32 a0, s32 a1); \
    s32 func_80155F80(s32 a0) \
    { \
        *(u32 *)(a0 + 0x44) = *(u32 *)(a0 + 0x44) & ~2; \
        func_80154A74(a0, 0x11); \
    }

#define DEFINE_func_8015CC0C() \
    void func_8015CC0C(s32 *param_1) { \
        func_80147078(param_1, 0xB); \
        func_8015CCD0(param_1); \
    }

#define DEFINE_func_8014C168() \
    extern u8 D_801202A0[]; \
    s32 func_8014C168(s32 * param_1, s32 param_2) \
    { \
        u32 i; \
        u16 *p; \
        i = 0; \
        p = (u16 *)D_801202A0; \
        for (; i < 0x60; i++) { \
            if (*p == param_2) { \
                return p; \
            } \
            p = (u16 *)((u8 *)p + 0x10C); \
        } \
        return (u16 *)0; \
    }

#define DEFINE_func_8016E918() \
    extern s32 D_80115218; \
    void func_8016E918(short param_1, short param_2) { \
        char *p; \
        if (param_2 < 10) { \
            p = (char *)&D_80115218 + ((s32)param_1 << 5); \
            p[0] = param_1 + 1; \
            p[3] = param_2; \
            p[1] = 0; \
        } \
    }

#define DEFINE_func_8015CCD0() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern s32 func_801725E0(u8 *a0); \
    extern void func_80147324(s32 arg0); \
    extern void func_80146CA0(void *a0); \
    s32 func_8015CCD0(s32 param_1) \
    { \
        func_80154150(param_1, 0x14); \
        *(s16 *)(param_1 + 0xB8) = 0; \
        func_801725E0((u8 *)param_1); \
        *(s32 *)(param_1 + 0x234) = 0xF; \
        func_80147324(0x6A7); \
        func_80146CA0((void *)param_1); \
    }

#define DEFINE_func_8016C83C() \
    extern s32 VectorNormalSS(void *a0, void *a1); \
    extern void func_800D22E4(s32 a0); \
    extern short func_8016CF04(); \
    void func_8016C83C(s32 a0) { \
        s16 d[20]; \
        s32 a1 = *(s32 *)(a0 + 0x34); \
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1; \
        s32 dist; \
        *(s32 *)(a0 + 0x1C) = v0; \
        if (v0 == 0) { \
            *(s16 *)(a0 + 2) = 4; \
            func_8016CF04(a0, 2); \
            return; \
        } \
        d[0] = *(u16 *)(a1 + 6) - *(u16 *)(a0 + 6); \
        d[1] = *(u16 *)(a1 + 0xA) - *(u16 *)(a0 + 0xA); \
        d[2] = *(u16 *)(a1 + 0xE) - *(u16 *)(a0 + 0xE); \
        dist = VectorNormalSS(d, d); \
        if (dist < 0x790) { \
            *(s16 *)(a0 + 2) = 4; \
            func_8016CF04(a0, 2); \
            return; \
        } \
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) + d[0] * 0x40; \
        *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) + d[1] * 0x40; \
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) + d[2] * 0x40; \
        d[0] = *(u16 *)(a0 + 0x12); \
        d[1] = *(u16 *)(a0 + 0x16); \
        d[2] = *(u16 *)(a0 + 0x1A); \
        dist = VectorNormalSS(d, d); \
        { \
            s32 lim = 0x1000; \
            if (lim < dist) { \
                *(s32 *)(a0 + 0x10) = (s32)d[0] << 10; \
                *(s32 *)(a0 + 0x14) = (s32)d[1] << 10; \
                *(s32 *)(a0 + 0x18) = (s32)d[2] << 10; \
            } \
        } \
        func_800D22E4(a0); \
        func_8016CF04(a0, 1); \
    }

#define DEFINE_func_801539F8() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern void *memcpy(void *dst, const void *src, u32 n); \
    s32 func_801539F8(s32 a0, void * a1) \
    { \
        u8 buf1[8]; \
        u8 buf2[8]; \
        u8 buf3[8]; \
        s32 r1, r2, r3; \
        memcpy(buf1, (void *)(a0 + 0xA0), 8); \
        memcpy(buf2, a1, 8); \
        *(s16 *)(buf1 + 2) -= 4; \
        r1 = func_80133784(0, buf1, buf2); \
        if (r1 != 0x2000) { \
            return 1; \
        } \
        memcpy((void *)buf1, (void *)(s32)buf2, 8); \
        *(s16 *)(buf2 + 2) += 8; \
        r2 = func_80133784(0, buf1, buf2); \
        if (r2 != r1) { \
            return 1; \
        } \
        r3 = func_80133784(2, buf2, buf3); \
        if (r3 != r2) { \
            return 1; \
        } \
        *(s16 *)(a0 + 0x88) = *(s16 *)(buf2 + 0); \
        *(s16 *)(a0 + 0x8A) = *(s16 *)(buf2 + 2); \
        *(s16 *)(a0 + 0x8C) = *(s16 *)(buf2 + 4); \
        memcpy((void *)(a0 + 0x90), (void *)(a0 + 0x88), 8); \
        return 0; \
    }

#define DEFINE_func_80153C44() \
    extern void func_80153C74(s16 a0, s16 a1); \
    extern s16 D_8011DB18; \
    void func_80153C44(int a0, int a1, s16 a2) \
    { \
        ((void (*)(int, int))func_80153C74)(a0, a1); \
        D_8011DB18 = a2; \
    }

#define DEFINE_func_8015CF58() \
    extern void func_8015D01C(); \
    void func_8015CF58(s32 *param_1) \
    { \
        func_80147078(param_1, 0xC); \
        ((void (*)(s32 *))func_8015D01C)(param_1); \
    }

#define DEFINE_func_801711FC() \
    extern void func_80171238(void); \
    void func_801711FC(u8 *param_1) { \
        func_801719A4((int)param_1, 1); \
        func_80171990(param_1); \
        ((void (*)(int))func_80171238)((int)param_1); \
    }

#define DEFINE_func_80161BE0() \
    extern int func_801497A8(void); \
    extern void func_801599A4(void *a0); \
    extern void func_80149864(void); \
    int func_80161BE0(void *param_1) \
    { \
        if (func_801497A8() == 0) { \
            return 0; \
        } \
        func_801599A4(param_1); \
        ((void (*)(void *))func_80149864)(param_1); \
        return 1; \
    }

#define DEFINE_func_801683D8() \
    extern void func_80146C3C(void); \
    void func_801683D8(s32 a0) { \
        func_80166994(a0, 2, *(short *)(a0 + 0x2c), 0); \
        if ((short)func_80166690(*(short *)(a0 + 0x2c), *(short *)(a0 + 0x28)) == 0) { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_801710DC() \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80171928(void *a0); \
    extern void *D_8011F738; \
    extern u16 D_8011F73A; \
    void func_801710DC(u8 * arg0) \
    { \
        ((M2C_UNK (*)(u16, u16))func_8002D4C8)(D_8011F738, D_8011F73A); \
        ((M2C_UNK (*)(s32))func_80171928)(arg0); \
    }

#define DEFINE_func_801612B8() \
    extern void func_8014E934(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    s32 func_801612B8(void * a0, s32 a1) \
    { \
        register s32 p __asm__("$17"); \
        register s32 v0 __asm__("$16"); \
        s32 v1; \
        p = a0; \
        if ((a1 & 1) == 0) { \
            func_8014E934(p); \
        } \
        v0 = ((s32 (*)(s32))func_8014CC28)(p); \
        __asm__ __volatile__("" : : "r"(v0)); \
        v1 = ((s32 (*)(s32))func_8014F3E8)(p); \
        return v0 | v1; \
    }

#define DEFINE_func_8015616C() \
    extern S801563EC *func_801563EC(u16 idx); \
    extern s32 func_80029B4C(s32 a0, s32 a1); \
    extern s32 func_80029BC8(s32 a0, s32 a1); \
    extern s32 func_80029C44(s32 a0, s32 a1); \
    extern s32 func_80029178(s32 arg); \
    extern s32 func_8015640C(s32 a0, s32 a1); \
    extern s32 rand(void); \
    extern u16 D_8012693A; \
    extern u16 D_801152B8; \
    u32 func_8015616C(s32 param_1, u16 param_2) { \
        u16 *p; \
        u16 uVar1, uVar2, uVar3, uVar4, uVar5, uVar7; \
        u32 base; \
        u32 uVar12; \
        s16 sVar11; \
        p = ((u16 * (*)(s32))func_801563EC)(param_2 & 0xFFFF); \
        uVar1 = p[0]; \
        uVar2 = p[1]; \
        uVar3 = p[2]; \
        uVar4 = p[3]; \
        uVar5 = p[4]; \
        uVar7 = p[5]; \
        base = uVar1 & 0xFFF; \
        if (uVar1 & 0x4000) { \
            uVar12 = func_80029B4C(base, (s32)(s16)uVar2) \
                   + func_80029BC8((s32)(s16)uVar3, (s32)(s16)uVar4); \
        } else if (uVar1 & 0x2000) { \
            uVar12 = func_80029C44(base, (s32)(s16)uVar2); \
        } else { \
            uVar12 = base + rand() % (uVar2 + 1); \
        } \
        D_8012693A = uVar5; \
        if ((u8)func_80029178(0x81)) { \
            D_8012693A = D_8012693A << 1; \
        } \
        sVar11 = 0; \
        if (uVar7 != 0) { \
            if ((u8)func_80029178(0x1A)) { \
                sVar11 = 5; \
            } else if ((u8)func_80029178(0x19)) { \
                sVar11 = 4; \
            } else if ((u8)func_80029178(0x18)) { \
                sVar11 = 3; \
            } else if ((u8)func_80029178(0x17)) { \
                sVar11 = 2; \
            } else if ((u8)func_80029178(0x16)) { \
                sVar11 = 1; \
            } \
        } \
        D_801152B8 = uVar7 + sVar11; \
        if (uVar1 & 0x8000) { \
            uVar12 = func_8015640C(param_1, uVar12 & 0xFFFF); \
        } \
        return uVar12 & 0xFFFF; \
    }

#define DEFINE_func_80164530() \
    extern s32 func_8014C59C(void *a0, void *a1); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80047D3C(s32 a0); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern u8 D_801202A0[]; \
    extern u8 D_800AF630[]; \
    void func_80164530(s32 arg0) { \
        register u8 *p __asm__("$17"); \
        register s32 s0 __asm__("$16"); \
        register u8 *unaff_s5 __asm__("$21"); \
        register s32 unaff_s6 __asm__("$22"); \
        register u8 *base __asm__("$23"); \
        s32 iVar9; \
        s16 sVar4; \
        s32 ix, iy, dist; \
        sVar4 = 0x1000; \
        base = D_800AF630; \
        p = D_801202A0; \
        iVar9 = *(s32 *)(arg0 + 0x20); \
        for (; p < D_801202A0 + 0x6480; p += 0x10C) { \
            if ((*(u16 *)(p + 0x5C) & 0x2000) != 0) { \
                s32 r2; \
                s0 = func_8014C59C((void *)arg0, (void *)p); \
                r2 = func_80012A60((s32)(s16)s0, (s32)*(s16 *)(iVar9 + 0x12)); \
                if (((s16)r2 < 0x200) && ((s16)r2 < sVar4)) { \
                    unaff_s6 = s0; \
                    sVar4 = r2; \
                    unaff_s5 = p; \
                } \
            } \
        } \
        if (sVar4 != 0x1000) { \
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = \
                (s16)func_80012DBC((s32)*(s16 *)(iVar9 + 0x12), (s32)(s16)unaff_s6, 10, 1); \
            if (*(s16 *)(base + 0xA3D8) == 0x30A0) { \
                u32 uVar7 = *(u32 *)(unaff_s5 + 0x58) & 0xFFFFFFF; \
                if (uVar7 != 0) { \
                    iy = (s32)((((u32)*(u16 *)(unaff_s5 + 0xE) + \
                                 ((s32)*(s16 *)(uVar7 + 0xC) + (s32)*(s16 *)(uVar7 + 0xE)) / 2) - \
                                (u32)*(u16 *)(arg0 + 0xE)) << 16) >> 16; \
                    ix = (s32)((((u32)*(u16 *)(unaff_s5 + 0x6) + \
                                 ((s32)*(s16 *)(uVar7 + 0x4) + (s32)*(s16 *)(uVar7 + 0x6)) / 2) - \
                                (u32)*(u16 *)(arg0 + 0x6)) << 16) >> 16; \
                    dist = func_80047D3C(iy * iy + ix * ix); \
                    s0 = ratan2(((s32)*(s16 *)(unaff_s5 + 0xA) + \
                                 ((s32)*(s16 *)(uVar7 + 0x8) + (s32)*(s16 *)(uVar7 + 0xA)) / 2) - \
                                (s32)*(s16 *)(arg0 + 0xA), \
                                (s32)(s16)dist) & 0xFFF; \
                    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = (u16)s0; \
                } \
            } \
        } \
    }

#define DEFINE_func_80156FA8() \
    extern s32 func_80013294(void *a0, void *a1); \
    void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3) \
    { \
        s16 d[3]; \
        d[0] = ((s32)param_2[0] - (s32)param_1[0]) / 3; \
        d[1] = ((s32)param_2[1] - (s32)param_1[1]) / 3; \
        d[2] = ((s32)param_2[2] - (s32)param_1[2]) / 3; \
        param_1[3] = 0; \
        if (((s32 (*)(s16 *))func_80013294)(param_1) >= 0x41) { \
            if (d[0] != 0 || d[1] != 0 || d[2] != 0) { \
                param_3[0] = param_2[0] - d[0]; \
                param_3[1] = param_2[1] - d[1]; \
                param_3[2] = param_2[2] - d[2]; \
                param_3[3] = 0; \
            } else { \
                param_3[3] = 1; \
            } \
            if (d[0] != 0 || d[1] != 0 || d[2] != 0) { \
                param_2[0] = param_1[0] + d[0]; \
                param_2[1] = param_1[1] + d[1]; \
                param_2[2] = param_1[2] + d[2]; \
                param_2[3] = 0; \
                return; \
            } \
            param_2[3] = 1; \
            return; \
        } \
        param_3[3] = 1; \
        param_2[3] = 1; \
    }

#define DEFINE_func_8017742C() \
    extern u8 D_8011F837; \
    extern u8 D_8011F7F0; \
    extern u8 D_8011F7AB; \
    u32 *func_8017742C(u32 *param_1, s32 param_2, s32 param_3) { \
        s16 sVar1; \
        u32 uVar2; \
        s32 a3 = (s32)param_1; \
        register s32 t1 __asm__("$9") = param_2; \
        s32 t0 = a3; \
        u8 *base = &D_8011F7F0; \
        *(u32 *)a3 = (a3 - 0x14) & 0xffffff | 0x3000000; \
        *(u8 *)(a3 + 7) = 0x60; \
        if (D_8011F837 < 0x80) { \
            *(u8 *)(a3 + 4) = 0xff; \
            *(u8 *)(a3 + 6) = 0x10; \
            *(u8 *)(a3 + 5) = 0x10; \
        } else if (D_8011F837 == 0x80) { \
            switch (D_8011F7AB) { \
            default: \
                D_8011F7AB = 0; \
            case 0: \
                *(u8 *)(t0 + 4) = 0xff; \
                *(u8 *)(t0 + 6) = 0x30; \
                *(u8 *)(t0 + 5) = 0x30; \
                break; \
            case 1: \
                *(u8 *)(a3 + 5) = 0xff; \
                *(u8 *)(a3 + 6) = 0x30; \
                *(u8 *)(a3 + 4) = 0x30; \
                break; \
            case 2: \
                *(u8 *)(a3 + 6) = 0xff; \
                *(u8 *)(a3 + 5) = 0x30; \
                *(u8 *)(a3 + 4) = 0x30; \
                break; \
            } \
            { \
                u8 *p = &D_8011F7AB; \
                *p = *p + 1; \
            } \
        } else { \
            *(u8 *)(a3 + 5) = 0xff; \
            *(u8 *)(a3 + 6) = 0x10; \
            *(u8 *)(a3 + 4) = 0x10; \
        } \
        a3 += 0x14; \
        *(u16 *)(t0 + 8) = t1; \
        uVar2 = (u32)base[0x47]; \
        *(u16 *)(t0 + 0xc) = 8; \
        sVar1 = (s16)((s32)(uVar2 * 3) >> 3); \
        { \
            s32 d = param_3 + 0x48; \
            *(s16 *)(t0 + 0xa) = d - sVar1; \
        } \
        *(s16 *)(t0 + 0xe) = sVar1; \
        *(u32 *)a3 = (a3 - 0x14) & 0xffffff | 0x3000000; \
        *(u8 *)(a3 + 7) = 0x60; \
        *(u8 *)(a3 + 5) = 0x40; \
        *(u8 *)(a3 + 4) = 0x40; \
        t0 = a3; \
        if (base[0x47] != 0) { \
            *(u8 *)(a3 + 6) = 0xa0; \
        } else { \
            *(u8 *)(a3 + 6) = 0x40; \
        } \
        *(u16 *)(t0 + 0xc) = 8; \
        *(u16 *)(t0 + 0xe) = 0x48; \
        *(u16 *)(t0 + 8) = t1; \
        *(s16 *)(t0 + 0xa) = param_3; \
        return (u32 *)(a3 + 0x14); \
    }

#define DEFINE_func_80153800() \
    extern void (*D_8011DB28)(s32 a0); \
    extern u8 D_80126DB0[]; \
    extern u16 D_80126DB6; \
    extern void func_80015954(s32 a0, s32 a1); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_800139C8(s32 a0, void *a1, void *a2); \
    extern s32 func_80153978(s32 a0, u16 *src); \
    extern void *memcpy(void *dst, const void *src, u32 n); \
    s32 func_80153800(s32 a0) { \
        s32 s1 = a0; \
        s32 s0; \
        s32 s2; \
        u8 bVar1; \
        s16 buf1[4]; \
        s16 buf2[4]; \
        if (D_8011DB28 != 0) { \
            ((void (*)(s32, s32))func_80015978)(s1 + 4, s1 + 0x88); \
            memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8); \
    ret0: \
            return 0; \
        } \
        bVar1 = *(u8 *)(s1 + 0xDE); \
        if (bVar1 >= 0x21) { \
            s32 base = (s32)D_80126DB0; \
            func_80015954(base, s1 + 4); \
            memcpy((void *)(s1 + 0x88), (void *)base, 8); \
            memcpy((void *)(s1 + 0x90), (void *)(s1 + 0x88), 8); \
            *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12) = D_80126DB6; \
            return 0; \
        } \
        { \
            register s32 m __asm__("$3") = bVar1 * 4; \
            s2 = m; \
            buf2[1] = *(u16 *)(s1 + 0xA2) - m; \
        } \
        for (s0 = 0; s0 < 0x80; s0++) { \
            s32 ang = s0 * 0x200000; \
            buf1[0] = 0; \
            buf1[1] = 0; \
            buf1[2] = s2; \
            func_800139C8(ang >> 0x10, buf1, buf1); \
            buf2[0] = *(u16 *)(s1 + 0xA0) + buf1[0]; \
            buf2[2] = *(u16 *)(s1 + 0xA4) + buf1[2]; \
            if (((s32 (*)(s32, void *))func_80153978)(s1, buf2) == 0) { \
                goto ret0; \
            } \
        } \
        *(u8 *)(s1 + 0xDE) = *(u8 *)(s1 + 0xDE) + 1; \
        return 1; \
    }

#define DEFINE_func_80168070() \
    extern void func_80149350(s32 arg0); \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern void func_80017E68(void *a0, void *a1); \
    extern void func_800D23D0(void *a0); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 D_801269A4; \
    extern s32 D_801269A8; \
    extern s32 D_801269AC; \
    void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) { \
        s16 mid[3]; \
        s16 dir[3]; \
        s32 pos[3]; \
        mid[0] = (param_2[0] + param_3[0]) >> 1; \
        mid[1] = (param_2[1] + param_3[1]) >> 1; \
        mid[2] = (param_2[2] + param_3[2]) >> 1; \
        ((void (*)(s32, void *, void *))func_80149350)(param_1, mid, mid); \
        func_800D20C0(mid, dir, 8); \
        func_80017E68(mid, param_4); \
        dir[0] = (u16)param_3[0] - (u16)param_2[0]; \
        dir[1] = (u16)param_3[1] - (u16)param_2[1]; \
        dir[2] = (u16)param_3[2] - (u16)param_2[2]; \
        ApplyMatrixSV((void *)(*(s32 *)(param_1 + 0x20) + 0x34), dir, dir); \
        func_800D23D0(dir); \
        RotMatrixYXZ(dir, param_4); \
        pos[0] = D_801269A4 - mid[0]; \
        pos[1] = D_801269A8 - mid[1]; \
        pos[2] = D_801269AC - mid[2]; \
        ApplyTransposeMatrixLV(param_4, pos, pos); \
        dir[2] = -ratan2(pos[0], pos[1]); \
        RotMatrixYXZ(dir, param_4); \
    }

#define DEFINE_func_8014B7A4() \
    extern s32 func_8016F1C4(void); \
    extern s32 func_80029178(s32 arg); \
    extern void func_8014B944(s32 a0, s32 a1, s32 a2); \
    extern u8 D_800AF630[]; \
    extern u8 D_80078E78[]; \
    extern s16 currentLocationId; \
    extern s32 D_80078EA4; \
    void func_8014B7A4(s16 *param_1) { \
        s32 s0 = (s32)param_1; \
        register u8 *s2 __asm__("$18") = D_800AF630; \
        register s32 s1 __asm__("$17") = (s32)D_80078E78; \
        s32 v0; \
        s32 v1; \
        if (func_8016F1C4() != 0) { \
            return; \
        } \
        if (*(u16 *)s0 == 0x1E) { \
            return; \
        } \
        if (*(u16 *)s0 == 0x1A) { \
            return; \
        } \
        if (*(s32 *)(s0 + 0x44) & 0x10) { \
            return; \
        } \
        if (*(s32 *)(s0 + 0x44) & 0x80) { \
            if ((func_80029178(0x1B) & 0xFF) != 0) { \
                func_8014B944(s0, 0x2D80, 0); \
            } else { \
                func_8014B944(s0, 0x16C0, 0); \
            } \
        } else { \
            v1 = currentLocationId; \
            if (v1 == 0x3024) goto check_end; \
            if (v1 == 0x3042) goto check_end; \
            if (v1 == 0x3067) goto check_end; \
            if (v1 == 0x3075) goto check_end; \
            if ((func_80029178(0x21) & 0xFF) != 0) { \
                D_80078EA4 = D_80078EA4 - 0xF2; \
            } else { \
                D_80078EA4 = D_80078EA4 - 0x16C; \
            } \
        } \
    check_end: \
        if (*(s32 *)(s1 + 0x2C) < 0) { \
            *(s32 *)(s1 + 0x2C) = 0; \
            if (*(s32 *)(s0 + 0x44) & 0x80) { \
                v1 = 0xAAA8; \
                v0 = *(s32 *)(s1 + 0x30) + v1; \
            } else { \
                v0 = *(s32 *)(s1 + 0x30) + 0x1555; \
            } \
            *(s32 *)(s1 + 0x30) = v0; \
            if (*(s16 *)(s1 + 0x32) >= 0x3C) { \
                *(s32 *)(s1 + 0x30) = 0; \
                if (*(s16 *)(s2 + 0xA3D8) != 0x3051) { \
                    *(s32 *)(s0 + 0x44) = *(s32 *)(s0 + 0x44) | 0x100; \
                } \
            } \
        } \
        return; \
    }

#define DEFINE_func_8014A850() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80029AF4(void); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    extern u8 D_801202A0[]; \
    s32 func_8014A850(s32 param_1) { \
        s32 i; \
        s32 cnt; \
        s16 buf[3];   /* 0x18, 0x1A, 0x1C */ \
        s16 out[4];   /* 0x20 .. 0x27 (s2) */ \
        s32 x; \
        s32 uVar2; \
        s16 *po; \
        cnt = 0; \
        po = out;   /* anchors &out ($s2) materialization between cnt=0 and i=0 (scheduler LUID) */ \
        i = 0; \
        do { \
            s32 e = (s32)&D_801202A0 + i; \
            if (*(u16 *)(e + 0) != 0 && *(s32 *)(e + 0x58) != 0 && \
                (*(u16 *)(e + 0x5C) & 0x8000) != 0 && *(u8 *)(e + 0xC1) == 7) { \
                x = *(u16 *)(param_1 + 6) - *(u16 *)(e + 6); \
                buf[0] = x; \
                buf[1] = *(u16 *)(param_1 + 0xA) - (*(u16 *)(e + 0xA) + 0x40); \
                buf[2] = *(u16 *)(param_1 + 0xE) - *(u16 *)(e + 0xE); \
                if ((((s16)x < 0) ? -(s16)x : (s16)x) < 0x40) { \
                    if (((buf[2] < 0) ? -buf[2] : buf[2]) < 0x40) { \
                        if (((buf[1] < 0) ? -buf[1] : buf[1]) < 0x40) { \
                            *(s32 *)(param_1 + 0x18C) = e; \
                            func_80015978(param_1 + 4, (s32 *)po); \
                            out[3] = 0; \
                            uVar2 = func_80029AF4(); \
                            func_8014C4AC(e, 0x1B, uVar2, po, \
                                          (s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12)); \
                            return 1; \
                        } \
                    } \
                } \
            } \
            cnt += 1; \
            i += 0x10C; \
        } while ((u32)cnt < 0x60); \
        return 0; \
    }

#define DEFINE_func_80169584() \
    extern s32 func_80017758(void *a0, void *a1); \
    void func_80169584(s32 param_1) { \
        u8 buf[0x60];   /* spans $sp+0x10 .. (named local_<0x78-off>) */ \
        s32 v1; \
        s32 v0; \
        register s32 s0 __asm__("$16");   /* param_1 + 0x38, held across both calls */ \
        *(s16 *)(buf + 0x00) = 7;     /* 0x10 = local_68 */ \
        *(s16 *)(buf + 0x18) = -7;    /* 0x28 = local_50 */ \
        *(s16 *)(buf + 0x0a) = 2;     /* 0x1A = local_5e */ \
        *(s16 *)(buf + 0x10) = 0;     /* 0x20 = local_58 */ \
        *(s16 *)(buf + 0x08) = 0;     /* 0x18 = local_60 */ \
        *(s16 *)(buf + 0x1a) = 0;     /* 0x2A = local_4e */ \
        *(s16 *)(buf + 0x02) = 0;     /* 0x12 = local_66 */ \
        *(s16 *)(buf + 0x12) = -2;    /* 0x22 = local_56 */ \
        *(s16 *)(buf + 0x1c) = 0;     /* 0x2C = local_4c */ \
        *(s16 *)(buf + 0x14) = 0;     /* 0x24 = local_54 */ \
        *(s16 *)(buf + 0x0c) = 0;     /* 0x1C = local_5c */ \
        *(s16 *)(buf + 0x04) = 0;     /* 0x14 = local_64 */ \
        *(u8 *)(buf + 0x22) = 0;      /* 0x32 = local_46 */ \
        *(u8 *)(buf + 0x20) = 0;      /* 0x30 = local_48 */ \
        *(u8 *)(buf + 0x2e) = 0;      /* 0x3E = local_3a */ \
        *(u8 *)(buf + 0x2c) = 0;      /* 0x3C = local_3c */ \
        *(u8 *)(buf + 0x2d) = 0;      /* 0x3D = local_3b */ \
        *(u8 *)(buf + 0x21) = 0;      /* 0x31 = local_47 */ \
        if (*(s32 *)(param_1 + 0x2c) == 0) { \
            v1 = -0x40 - (*(s32 *)(param_1 + 0x1c) << 4); \
            v0 = ((u32)(v1 & 0xff)) >> 2; \
            *(s8 *)(buf + 0x29) = v1;    /* 0x39 = local_3f */ \
            *(s8 *)(buf + 0x25) = v1;    /* 0x35 = local_43 */ \
            *(s8 *)(buf + 0x2a) = v0;    /* 0x3A = local_3e */ \
            *(s8 *)(buf + 0x26) = v0;    /* 0x36 = local_42 */ \
        } else { \
            v1 = -0x40 - (*(s32 *)(param_1 + 0x1c) << 4); \
            v0 = ((u32)(v1 & 0xff)) >> 2; \
            *(s8 *)(buf + 0x29) = v1;    /* 0x39 */ \
            *(s8 *)(buf + 0x25) = v1;    /* 0x35 */ \
            *(s8 *)(buf + 0x2a) = v1;    /* 0x3A */ \
            *(s8 *)(buf + 0x26) = v1;    /* 0x36 */ \
        } \
        *(s8 *)(buf + 0x28) = v0;        /* 0x38 = local_40 */ \
        *(s8 *)(buf + 0x24) = v0;        /* 0x34 = local_44 */ \
        __asm__ __volatile__("" ::: "memory"); \
        *(s32 *)(buf + 0x30) = 0x50000000;   /* 0x40 = local_38 */ \
        s0 = param_1 + 0x38; \
        *(s32 *)(param_1 + 0x4c) = (s32)*(s16 *)(param_1 + 0x06); \
        *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x0a); \
        *(s32 *)(param_1 + 0x54) = (s32)*(s16 *)(param_1 + 0x0e); \
        func_80017758(buf + 0x00, (void *)s0); \
        *(s16 *)(buf + 0x02) = 7;     /* 0x12 = local_66 */ \
        *(s16 *)(buf + 0x1a) = -7;    /* 0x2A = local_4e */ \
        *(s16 *)(buf + 0x08) = 2;     /* 0x18 = local_60 */ \
        *(s16 *)(buf + 0x12) = 0;     /* 0x22 = local_56 */ \
        *(s16 *)(buf + 0x0a) = 0;     /* 0x1A = local_5e */ \
        *(s16 *)(buf + 0x18) = 0;     /* 0x28 = local_50 */ \
        *(s16 *)(buf + 0x00) = 0;     /* 0x10 = local_68 */ \
        *(s16 *)(buf + 0x10) = -2;    /* 0x20 = local_58 */ \
        func_80017758(buf + 0x00, (void *)s0); \
    }

#define DEFINE_func_80162968() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80047D3C(s32 a0); \
    extern void func_80013F3C(s32 a0); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_800123F0(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    void func_80162968(s32 param_1) \
    { \
        register int p __asm__("$18"); \
        register int iVar4 __asm__("$17"); \
        register int iVar3 __asm__("$16"); \
        register int iVar5 __asm__("$19"); \
        short sVar2; \
        int iVar6; \
        p = param_1; \
        iVar4 = *(int *)(p + 4); \
        iVar5 = *(int *)(p + 8); \
        iVar3 = p + 0xc; \
        *(short *)(iVar5 + 0x10) = \
            (short)ratan2((int)*(short *)(iVar4 + 0x84), (int)*(short *)(iVar4 + 0x82)); \
        sVar2 = (short)func_80047D3C((int)*(short *)(iVar4 + 0x84) * (int)*(short *)(iVar4 + 0x84) + \
                                     (int)*(short *)(iVar4 + 0x82) * (int)*(short *)(iVar4 + 0x82)); \
        *(short *)(iVar5 + 0x14) = \
            (short)ratan2((int)*(short *)(iVar4 + 0x80), -(int)sVar2); \
        func_80013F3C(iVar3); \
        func_800126C4(iVar3, (int)*(short *)(iVar5 + 0x10)); \
        func_800123F0(iVar3, (int)*(short *)(iVar5 + 0x14)); \
        func_80012558(iVar3, (int)*(short *)(*(int *)(iVar4 + 0x20) + 0x12)); \
        func_800126C4(iVar3, 0x400); \
        iVar6 = ((0x300 - (int)(short)(*(int *)(p + 0x24) - (unsigned int)*(unsigned short *)(iVar4 + 0xa))) * 0x2000) / 0x300; \
        sVar2 = (short)iVar6; \
        if ((*(unsigned int *)(iVar4 + 0x44) & 0x400) != 0) { \
            sVar2 = (short)iVar6 / 3; \
        } \
        *(short *)(iVar5 + 0x1c) = sVar2; \
        *(short *)(iVar5 + 0x1a) = sVar2; \
        *(short *)(iVar5 + 0x18) = sVar2; \
        return; \
    }

#define DEFINE_func_80169058() \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern void func_800D23D0(void *a0); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32 rand(void); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    void func_80169058(s32 a0) { \
        s32 s1 = a0; \
        s16 v10[4];   /* sp+0x10 SVECTOR */ \
        s16 v18[4];   /* sp+0x18 SVECTOR */ \
        s16 v20[16];  /* sp+0x20 MATRIX_L48 */ \
        s16 v40[16];  /* sp+0x40 MATRIX_L48 */ \
        register s32 v1 __asm__("$3"); \
        register s32 v0 __asm__("$2"); \
        v10[0] = *(u16 *)(s1 + 0x6); \
        v10[1] = *(u16 *)(s1 + 0xA); \
        v10[2] = *(u16 *)(s1 + 0xE); \
        func_800D20C0(v10, v18, 1); \
        func_800D23D0(v18); \
        RotMatrixYXZ(v18, (void *)(s1 + 0x38)); \
        v10[0] = *(u16 *)(s1 + 0x12); \
        v10[1] = *(u16 *)(s1 + 0x16); \
        v10[2] = *(u16 *)(s1 + 0x1A); \
        RotMatrixYXZ(v10, v40); \
        if ((*(s32 *)(s1 + 0x2C) & 0x2) == 0) { \
            v0 = rand(); \
            v1 = (v0 & 0x7F) << 3; \
            v0 = ((u32)(v0 & 0x7F00)) >> 5; \
            __asm__ __volatile__("" : "=r"(v0) : "0"(v0)); \
            v0 = v0 + 0xC00; \
        } else { \
            v0 = rand(); \
            v1 = ((v0 & 0x7F) << 3) + 0xE40; \
            v0 = (((u32)(v0 & 0x7F00)) >> 5) + 0xE00; \
        } \
        v10[0] = v1; \
        v10[1] = v0; \
        __asm__ __volatile__("" : : "r"(v1), "r"(v0)); \
        v10[2] = 0; \
        RotMatrixYXZ(v10, v20); \
        func_80048EAC(v40, v20); \
        v10[0] = 0; \
        v10[1] = 0; \
        v10[2] = 0xA; \
        ApplyMatrixSV(v20, v10, v10); \
        *(u16 *)(s1 + 0x12) = v10[0]; \
        *(u16 *)(s1 + 0x16) = v10[1]; \
        { \
            s32 c = *(u16 *)(s1 + 0x2); \
            s32 z = (u16)v10[2]; \
            *(s32 *)(s1 + 0x1C) = 0; \
            *(u16 *)(s1 + 0x2) = c + 1; \
            *(u16 *)(s1 + 0x1A) = z; \
        } \
    }

#define DEFINE_func_80146128() \
    extern s32 D_80126B58; \
    extern s32 *D_80126B78; \
    extern u8 D_80078EC1; \
    extern s32 D_80078EC8; \
    extern s32 D_80126B9C; \
    extern s32 D_8011F730; \
    extern u16 D_801152B8; \
    extern u16 D_8012693A; \
    extern u8 D_80126BE0[]; \
    extern u8 D_801150F0[]; \
    extern void *memcpy(void *dst, const void *src, u32 n); \
    extern void func_80146FC4(s32 a0); \
    extern void func_80150A70(s32 a0); \
    extern void func_80147098(s32 *a0); \
    extern void func_8014A638(s32 arg0); \
    extern s32  func_80155458(s32 a0); \
    extern s32  func_80029104(void); \
    extern void func_80029344(void); \
    extern void func_8014ADE0(s32 a0); \
    extern void func_8014B350(s32 a0); \
    extern void func_8014B7A4(s16 *param_1); \
    extern s32 func_80161D58(s32 a0); \
    extern void func_80161A90(s32 a0); \
    extern void func_8014B504(u16 *a0); \
    extern void func_80149BEC(s32 a0); \
    extern void func_8014B5D0(s32 *a0); \
    extern void func_8014C99C(u8 *a0); \
    extern void func_8014B190(s32 s0); \
    extern void func_80148648(s32 a0, s32 a1); \
    extern s32 func_80149228(s32 a0); \
    extern void func_8014A59C(s32 a0); \
    extern void func_8016F14C(void *a0); \
    extern void func_80154418(void *a0); \
    extern void func_80154BE4(s32 a0); \
    extern void func_80165694(s32 arg0); \
    extern void func_801654A8(s32 a0); \
    extern void func_8014A680(s32 a0); \
    extern void func_8014A6A8(s32 a0); \
    extern void func_8014A71C(s32 a0); \
    extern void func_80172588(s32 *a0); \
    extern void func_801473DC(s32 *a0); \
    extern void func_80015978(s32 a0, s32 *a1); \
    s32 func_80146128(void) \
    { \
        register s32 base __asm__("$16"); \
        register s32 *p   __asm__("$17"); \
        p = D_80126B78; \
        base = (s32)&D_80126B58; \
        func_80146FC4(base); \
        memcpy((void *)D_801150F0, (void *)D_80126BE0, 8); \
        func_80150A70(base); \
        ((void (*)(s32))func_80147098)(base); \
        func_8014A638(base); \
        D_8011F730 = 0; \
        D_801152B8 = 0; \
        D_8012693A = 0; \
        if (D_80078EC1 == 0x10 && D_80078EC8 != 0) { \
            *(u16 *)((s32)p + 2) = 6; \
            D_80126B9C |= 0x800; \
        } else { \
            *(u16 *)((s32)p + 2) = 1; \
            *(s32 *)(base + 0x44) &= ~0x800; \
        } \
        if (*(s32 *)(base + 0x1B0) != 0) { \
            *(s32 *)(base + 0x1B0) = *(s32 *)(base + 0x1B0) - 1; \
        } \
        if (func_80155458(base) == 0 && (*(s32 *)(base + 0x44) & 0x4000000) == 0) { \
            if ((func_80029104() & 0xFF) != 0) { \
                func_8014ADE0(base); \
                func_8014B350(base); \
                ((void (*)(s32))func_8014B7A4)(base); \
                ((void (*)(s32))func_80161D58)(base); \
            } \
            func_80029344(); \
            func_80161A90(base); \
            ((void (*)(s32))func_8014B504)(base); \
            func_80149BEC(base); \
            ((void (*)(s32))func_8014B5D0)(base); \
            ((void (*)(s32))func_8014C99C)(base); \
            func_8014B190(base); \
            func_80148648(base, 0); \
            ((void (*)(s32))func_80149228)(base); \
            func_8014A59C(base); \
            ((void (*)(s32))func_8016F14C)(base); \
            ((void (*)(s32))func_80154418)(base); \
            func_80154BE4(base); \
            func_80165694(base); \
            func_801654A8(base); \
            func_8014A680(base); \
            func_8014A6A8(base); \
            func_8014A71C(base); \
            ((void (*)(s32))func_80172588)(base); \
            ((void (*)(s32))func_801473DC)(base); \
            ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98); \
            return 1; \
        } \
        ((void (*)(s32, s32))func_80015978)(base + 4, base + 0x98); \
        return 0; \
    }

#define DEFINE_func_801519C8() \
    extern u8 D_80062BF4[]; \
    extern M2C_UNK D_800D5880; \
    extern s32 D_800D58AC; \
    extern void func_80019064(void *a0); \
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
    extern int func_80151204(int arg, int a1); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80149020(s32 *a0); \
    extern void func_80147324(s32 arg0); \
    extern void func_80146CA0(void *a0); \
    void func_801519C8(s32 arg0) { \
        s16 r; \
        u8 v1; \
        u8 de; \
        s32 v0w; \
        func_80019064(&D_80062BF4); \
        v1 = *(u8 *)(arg0 + 0xDD); \
        if (v1 != 1 && v1 == 0x11) { \
            s16 v0 = *(s16 *)(arg0 + 0xF2); \
            if (v0 != 0) { \
                func_8014ACE8((void *)arg0, 5, (s32)v0 & 0x7FFF); \
            } \
        } else { \
            func_80151204(arg0, *(s16 *)(arg0 + 0xF2)); \
        } \
        v0w = *(s32 *)(arg0 + 0x20); \
        r = (s16)func_80012A60(*(s16 *)(v0w + 0x12), *(s16 *)(arg0 + 0xF4)); \
        if (r >= 0x401) { \
            func_80154274((s32 *)arg0, (s32)&D_800D5880); \
        } else { \
            func_80154274((s32 *)arg0, (s32)&D_800D58AC); \
        } \
        func_80154A74(arg0, 0x16); \
        func_80149020((s32 *)arg0); \
        func_80147324(0x451); \
        de = *(u8 *)(arg0 + 0xDE); \
        if (de == 2 || de == 3 || (de & 0xFF) == 0xB) { \
            func_80146CA0((void *)arg0); \
        } \
        func_80146CA0((void *)arg0); \
    }

#define DEFINE_func_801536DC() \
    extern void (*D_8011DB28)(s32 a0); \
    extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2); \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern s32 func_80013294(void *a0, void *a1); \
    extern void func_80015954(s32 a0, s32 a1); \
    s32 func_801536DC(s32 param_1) { \
        s32 s0 = param_1; \
        s32 s1; \
        s32 s2; \
        s32 sp10[2]; \
        register s32 r __asm__("$2"); \
        s32 q; \
        if (D_8011DB28 != 0) { \
            D_8011DB28(s0 + 0xA0); \
        } \
        *(s16 *)(s0 + 6) = func_80012C6C((s32)*(s16 *)(s0 + 6), (s32)*(s16 *)(s0 + 0xA0), 8); \
        *(s16 *)(s0 + 0xA) = func_80012C6C((s32)*(s16 *)(s0 + 0xA), (s32)*(s16 *)(s0 + 0xA2), 8); \
        { \
        register s32 t __asm__("$2") = func_80012C6C((s32)*(s16 *)(s0 + 0xE), (s32)*(s16 *)(s0 + 0xA4), 8); \
        register s32 chk __asm__("$3") = (s32)D_8011DB28; \
        *(s16 *)(s0 + 0xE) = t; \
        if (chk != 0) { \
            s2 = s0 + 4; \
            func_80015978(s2, sp10); \
            s1 = s0 + 0xA0; \
            q = func_80013294(sp10, (void *)s1); \
            if (q < 0x40 || *(u8 *)(s0 + 0xDE) == 0) { \
                func_80015954(s1, s2); \
                return 0; \
            } \
            *(u8 *)(s0 + 0xDE) = *(u8 *)(s0 + 0xDE) - 1; \
        } \
        } \
        r = 1; \
        if (*(s16 *)(s0 + 6) == *(s16 *)(s0 + 0xA0) && \
            *(s16 *)(s0 + 0xA) == *(s16 *)(s0 + 0xA2)) { \
            r = *(s16 *)(s0 + 0xE) != *(s16 *)(s0 + 0xA4); \
        } \
        return r; \
    }

#define DEFINE_func_80160410() \
    extern void func_80019064(void *a0); \
    extern void func_80149020(s32 *a0); \
    extern void func_80013E94(void *a0, void *a1); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80147324(s32 arg0); \
    extern void func_8001382C(s32 a0, void *a1, void *a2); \
    extern void func_80146DB8(s32 *a0, s32 *a1); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_801553A8(s32 *a0); \
    extern s32 func_80149184(s32 a0); \
    extern void func_80146CA0(void *a0); \
    extern u8 D_80062BD0; \
    extern s16 D_801152A0; \
    void func_80160410(s32 * a0) \
    { \
        register s32 angle __asm__("$17"); \
        s32 m1[3]; \
        s32 out[12]; \
        u32 buf[2]; \
        func_80019064((void *)&D_80062BD0); \
        func_80149020(a0); \
        { \
            s32 t = (s32)(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12)); \
            angle = (s32)(*(u16 *)((s32)a0 + 0x42)) - t; \
        } \
        func_80013E94((void *)((s32)a0 + 0xE8), buf); \
        { \
            s32 a2v = (s32)*(s16 *)((s32)a0 + 0xE0); \
            u32 v6 = buf[0] | 0x80000000; \
            s32 a3v = (s32)*(s16 *)((s32)a0 + 0xE2); \
            s32 a5v = (s32)*(s16 *)((s32)a0 + 0xE4); \
            buf[0] = v6; \
            func_80146A6C(6, a0, a2v, a3v, a5v, v6, 0); \
        } \
        func_80147324(0x43D); \
        angle = (s32)(angle << 16) >> 16; \
        m1[0] = 0; \
        m1[1] = 0; \
        m1[2] = 0xFFFA0000; \
        func_8001382C(angle, m1, out); \
        func_80146DB8(a0, out); \
        m1[0] = 0; \
        m1[1] = 0; \
        m1[2] = 0x8000; \
        func_8001382C(angle, m1, (void *)((s32)a0 + 0x234)); \
        func_80146E90(a0, 8); \
        func_801553A8(a0); \
        D_801152A0 = func_80149184((s32)a0); \
        func_80146CA0(a0); \
    }

#define DEFINE_func_80168D94() \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    extern int rand(void); \
    void func_80168D94(int a0) { \
        int s1 = a0; \
        short v10[4];   /* sp+0x10 SVECTOR */ \
        short v18[16];  /* sp+0x18 MATRIX_L48 */ \
        short v38[16];  /* sp+0x38 MATRIX_L48 */ \
        register int v1 __asm__("$3"); \
        register int v0 __asm__("$2"); \
        v10[0] = *(unsigned short *)(s1 + 0x12); \
        v10[1] = *(unsigned short *)(s1 + 0x16); \
        v10[2] = *(unsigned short *)(s1 + 0x1A); \
        RotMatrixYXZ(v10, v38); \
        if (*(int *)(s1 + 0x2C) == 0) { \
            v0 = rand(); \
            v1 = (v0 & 0x7F) << 3; \
            v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5); \
            __asm__("" : "=r"(v0) : "0"(v0)); \
            v0 += 0xC00; \
        } else { \
            v0 = rand(); \
            v1 = ((v0 & 0x7F) << 3) + 0xE00; \
            v0 = (int)((unsigned int)(v0 & 0x7F00) >> 5) + 0xE00; \
        } \
        v10[0] = v1; \
        v10[1] = v0; \
        __asm__ __volatile__("" ::: "memory"); \
        v10[2] = 0; \
        RotMatrixYXZ(v10, v18); \
        func_80048EAC(v38, v18); \
        v10[0] = 0; \
        v10[1] = 0; \
        v10[2] = 0x24; \
        ApplyMatrixSV(v18, v10, v10); \
        { \
            register s32 a __asm__("$4") = *(unsigned short *)(s1 + 0x6); \
            register s32 b __asm__("$5") = *(unsigned short *)(s1 + 0xA); \
            register s32 c __asm__("$3") = *(unsigned short *)(s1 + 0xE); \
            *(unsigned short *)(s1 + 0x12) = v10[0]; \
            *(unsigned short *)(s1 + 0x16) = v10[1]; \
            { \
                s32 z = (unsigned short)v10[2]; \
                s32 t = *(unsigned short *)(s1 + 0x2); \
                *(unsigned short *)(s1 + 0x10) = a; \
                *(unsigned short *)(s1 + 0x14) = b; \
                *(unsigned short *)(s1 + 0x18) = c; \
                *(int *)(s1 + 0x1C) = 0; \
                *(unsigned short *)(s1 + 0x2) = t + 1; \
                *(unsigned short *)(s1 + 0x1A) = z; \
            } \
        } \
    }

#define DEFINE_func_80178298() \
    u32 *func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4) { \
        u8 bVar1; \
        short sVar2; \
        if (*param_2 < 0x80) { \
            do { \
                sVar2 = *(short *)param_2; \
                switch (sVar2) { \
                case 0x1850: \
                case 0x1858: \
                    *(short *)((u8 *)param_1 + 8) = param_3 + 4; \
                    *(short *)((u8 *)param_1 + 0xA) = param_4 + -7; \
                    break; \
                case 0x3870: \
                    param_3 = param_3 + 8; \
                    param_2 = param_2 + 2; \
                    continue; \
                case 0x3871: \
                    param_3 = param_3 + 4; \
                    param_2 = param_2 + 2; \
                    continue; \
                case 0x3872: \
                    param_3 = param_3 + 2; \
                    param_2 = param_2 + 2; \
                    continue; \
                default: \
                    *(short *)((u8 *)param_1 + 8) = param_3; \
                    *(short *)((u8 *)param_1 + 0xA) = param_4; \
                    if (*(short *)param_2 >= 0x861) { \
                        param_3 = param_3 + 8; \
                    } else { \
                        param_3 = param_3 + 7; \
                    } \
                    break; \
                } \
                *param_1 = (u32)(param_1 + -5) & 0xffffff | 0x4000000; \
                *(u32 *)((u8 *)param_1 + 4) = 0x64808080; \
                ((u8 *)param_1)[0xC] = *param_2; \
                param_2 = param_2 + 1; \
                bVar1 = *param_2; \
                param_2 = param_2 + 1; \
                *(short *)((u8 *)param_1 + 0xE) = 0x4056; \
                ((u8 *)param_1)[0xD] = bVar1; \
                *(short *)((u8 *)param_1 + 0x10) = 8; \
                *(short *)((u8 *)param_1 + 0x12) = 8; \
                param_1 = param_1 + 5; \
            } while (*param_2 < 0x80); \
        } \
        return param_1; \
    }

#define DEFINE_func_8016A08C() \
    extern u8 D_80078EBF; \
    extern void func_80148534(s32 a0, s32 a1); \
    extern void func_8016A290(); \
    extern void func_80147324(s32 arg0); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80147364(u16, s32); \
    extern void func_80146C3C(void); \
    void func_8016A08C(s32 param_1) { \
        register s32 s0 __asm__("$16"); \
        register void *s1 __asm__("$17"); \
        u8 buf20[8]; \
        u8 buf18[8]; \
        s32 iVar4; \
        s16 sVar2; \
        s0 = param_1; \
        if (D_80078EBF != 0) { \
            s1 = buf18; \
            ((void (*)(void *, void *))func_80148534)(buf20, s1); \
            *(s32 *)(s0 + 0x30) = (s32)(u32)D_80078EBF - 0x18; \
            if ((s32)((u32)D_80078EBF - 0x18) >= 0) { \
                func_8016A290(s0, buf20, s1); \
                iVar4 = *(s32 *)(s0 + 0x1C) + 1; \
                *(s32 *)(s0 + 0x1C) = iVar4; \
                if (iVar4 == 4) { \
                    func_80147324(0x44C); \
                } \
                if (D_80078EBF < 0x80) { \
                    sVar2 = 0; \
                    do { \
                        sVar2 = sVar2 + 1; \
                    } while (sVar2 < 2); \
                    ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0x17, s0, (s32)*(s16 *)(s0 + 6), (s32)*(s16 *)(s0 + 0xA), \
                                  (s32)*(s16 *)(s0 + 0xE), 0, 0); \
                } else { \
                    if (*(s16 *)(s0 + 0x2A) == 0) { \
                        *(s16 *)(s0 + 0x2A) = 1; \
                        *(s32 *)(s0 + 0x1C) = 0x100; \
                    } \
                    if ((*(u32 *)(s0 + 0x1C) & 0x1F) == 0) { \
                        func_80147324(0x44D); \
                    } \
                } \
            } \
        } else { \
            ((void (*)(s32, s32))func_80147364)(4, 0x44C); \
            ((void (*)(s32))func_80146C3C)(s0); \
        } \
    }

#define DEFINE_func_8016EDEC() \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8016EE94(); \
    extern s32 D_80126B58; \
    void func_8016EDEC(s32 _arg0, s32 _arg1, s32 _arg2) \
    { \
      unsigned short *new_var; \
      if (1) \
      { \
        ((M2C_UNK (*)(void)) func_8016EE94)(); \
        new_var = &D_80126B58; \
        if (((u32) ((*new_var) - 0x19)) >= 2U) \
        { \
          ((M2C_UNK (*)(u16 *)) func_801599A4)(&D_80126B58); \
          ((M2C_UNK (*)(u16 *)) func_80159B3C)(&D_80126B58); \
        } \
      } \
    }

#define DEFINE_func_8016EE40() \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8016EF78(s32 a0); \
    extern s32 D_80126B58; \
    void func_8016EE40(s32 _arg0, s32 _arg1, s32 _arg2) \
    { \
      s32 *new_var; \
      void (*new_var2)(void *a0); \
      unsigned short new_var3; \
      new_var = &D_80126B58; \
      ((M2C_UNK (*)(void)) func_8016EF78)(); \
      new_var3 = *new_var; \
      if (((u32) (new_var3 - 0x19)) >= 2U) \
      { \
        ((M2C_UNK (*)(u16 *)) func_801599A4)(&D_80126B58); \
        new_var2 = func_80159B3C; \
        ((M2C_UNK (*)(u16 *)) new_var2)(&D_80126B58); \
      } \
    }

#define DEFINE_func_8013EA54() \
    extern s32 func_80141C50(void); \
    extern void func_8013F244(void); \
    extern void func_8013FAF8(s16 a0, s16 a1); \
    extern void func_80137B80(void); \
    extern void func_8013E958(void); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern short D_800B9A02; \
    extern u8 D_801151C8[]; \
    extern s32 D_801151D0; \
    extern u16 D_8011511A; \
    extern u16 D_8011511E; \
    extern unsigned short D_80115112; \
    extern s32 D_80115130; \
    extern s16 D_8011514C; \
    extern s16 currentLocationId; \
    void func_8013EA54(void) { \
        s32 sp10[2]; \
        if ((s16)func_80141C50() == 0) { \
            D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4]; \
            func_8013F244(); \
            func_8013FAF8(0, 5); \
            func_80137B80(); \
            if (D_8011511E & 0x40) { \
                if (D_8011511A == 0 && currentLocationId == 0x308F) { \
                    func_8002D4C8(0x466, 0); \
                } else { \
                    u16 v = D_8011511A; \
                    if (v != 4) { \
                        D_80115130 = 0; \
                    } \
                    if ((u16)(v - 1) <= 1) { \
                        D_8011514C = 0; \
                    } \
                    func_8002D4C8(0x45D, 0); \
                    D_80115112 += 1; \
                } \
            } else if (D_8011511E & 0x810) { \
                func_8013E958(); \
            } \
        } \
        (void)sp10; \
    }

#define DEFINE_func_80152500() \
    extern void func_80149020(s32 *a0); \
    extern void func_801525F4(int); \
    extern void func_80159B3C(void *a0); \
    extern void func_80147A84(s32 arg0); \
    extern void func_801473EC(s32 *a0); \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern s32 func_801535F4(void *arg0); \
    extern void func_8015BF48(s32 *a0); \
    extern void func_8014C010(s32 a0, s32 a1); \
    extern void func_80165718(s32 a0); \
    void func_80152500(int param_1) \
    { \
        int iVar1; \
        ((int (*)(int))func_80149020)(param_1); \
        if (*(int *)(param_1 + 0x1c) == 0) { \
            if (*(unsigned short *)(param_1 + 0xb8) == 0x8000) { \
                func_801525F4(param_1); \
                ((void (*)(int))func_80159B3C)(param_1); \
                goto LAB_801525d8; \
            } \
        } else { \
            *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + -1; \
        } \
        func_80147A84(param_1); \
        ((void (*)(int))func_801473EC)(param_1); \
        func_80148038(param_1, 0x8000); \
        func_80147460(param_1); \
        iVar1 = ((int (*)(int))func_801535F4)(param_1); \
        if (iVar1 == 1) goto LAB_801525a4; \
        if (iVar1 < 2) return; \
        if (iVar1 == 2) goto LAB_801525bc; \
        return; \
    LAB_801525a4: \
        func_801525F4(param_1); \
        ((void (*)(int))func_80159B3C)(param_1); \
        goto LAB_801525d0; \
    LAB_801525bc: \
        func_801525F4(param_1); \
        ((void (*)(int))func_8015BF48)(param_1); \
    LAB_801525d0: \
        func_8014C010(param_1, 1); \
    LAB_801525d8: \
        func_80165718(param_1); \
        return; \
    }

#define DEFINE_func_8013F244() \
    extern u16 D_8011511A; \
    extern u16 D_8011511E; \
    extern void func_80141C0C(s32); \
    void func_8013F244(void) \
    { \
        u16 *p = &D_8011511A; \
        u16 uVar1; \
        s32 iVar2; \
        iVar2 = 0; \
        if (*p < 3) { \
            if ((D_8011511E & 0x2000) != 0) { \
                uVar1 = *p + 1; \
                iVar2 = 1; \
                *p = *p + 1; \
                if (2 < uVar1) { \
                    *p = 0; \
                } \
            } \
            if ((D_8011511E & 0x8000) != 0) { \
                D_8011511A = D_8011511A - 1; \
                if (2 < D_8011511A) { \
                    D_8011511A = 2; \
                } \
                iVar2 = iVar2 + 1; \
            } \
            if ((D_8011511E & 0x5000) != 0) { \
                D_8011511A = 3; \
                iVar2 = iVar2 + 1; \
            } \
        } else { \
            iVar2 = 0; \
            if ((D_8011511E & 0x5000) == 0) \
                goto done; \
            *p = 0; \
            iVar2 = 1; \
        } \
    done: \
        if ((iVar2 << 0x10) != 0) { \
            func_80141C0C(2); \
        } \
        return; \
    }

#define DEFINE_func_80155C64() \
    extern void func_80148038(s32 a0, s32 a1); \
    extern void func_80147460(s32 a0); \
    extern void func_8014ED28(s32 a0); \
    extern void func_80146D90(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8014FA04(s32 a0); \
    extern void func_8014C010(s32 a0, s32 a1); \
    extern void func_8015BF48(s32 *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern int func_80155FF8(int arg, int a1); \
    extern s32 D_800D4DF4; \
    void func_80155C64(s32 a0) { \
        s32 flags; \
        *(s32 *)(a0 + 0x44) |= 2; \
        func_80148038(a0, 0x30000); \
        func_80147460(a0); \
        if (((s32 (*)(s32))func_8014ED28)(a0) != 0) { \
            func_80146D90(a0); \
        } \
        if ((*(s32 *)(a0 + 0x34) > 0) && (((s32 (*)(s32))func_8014CC28)(a0) != 0)) { \
            func_801599A4((void *)a0); \
            func_80159B3C((void *)a0); \
            func_8014C010(a0, 1); \
            return; \
        } \
        flags = ((s32 (*)(s32))func_8014FA04)(a0); \
        if (flags & 0x4000) { \
            func_801599A4((void *)a0); \
            func_8014C010(a0, 1); \
            ((void (*)(void *))func_8015BF48)((void *)a0); \
            return; \
        } \
        if (flags & 0x2000) { \
            func_80154274((s32 *)a0, (s32)&D_800D4DF4); \
            func_80146CA0((void *)a0); \
            func_8014C010(a0, 1); \
            return; \
        } \
        ((void (*)(s32, s32))func_80155FF8)(a0, *(u8 *)(a0 + 0x1AA)); \
    }

#define DEFINE_func_80169408() \
    extern s32 rand(void); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    extern void func_800D20C0(void *a0, void *a1, s32 a2); \
    extern void func_800D23D0(void *a0); \
    extern void func_80169584(s32 param_1); \
    void func_80169408(s32 a0) { \
        register s32 s2 __asm__("$18") = a0; \
        register s32 s1 __asm__("$17"); \
        s16 v10[4];   /* sp+0x10 SVECTOR */ \
        s16 out[4];   /* sp+0x18 SVECTOR */ \
        s16 m[32];    /* sp+0x20 MATRIX_L48 (+ trailing reserve to 0x60 — matches target frame) */ \
        if (*(s32 *)(s2 + 0x2C) == 0) { \
            s32 r = rand(); \
            s1 = s2 + 0x38; \
            v10[0] = (r & 0x7F) << 5; \
            v10[1] = ((u32)(r & 0x7F00)) >> 3; \
            v10[2] = 0; \
            RotMatrixYXZ(v10, m); \
            func_80048EAC((void *)s1, m); \
            v10[0] = 0; \
            v10[1] = 0; \
            v10[2] = 2; \
            ApplyMatrixSV(m, v10, v10); \
            *(u16 *)(s2 + 0x12) = v10[0]; \
            *(u16 *)(s2 + 0x16) = v10[1]; \
            *(u16 *)(s2 + 0x1A) = v10[2]; \
            v10[0] = *(u16 *)(s2 + 0x6); \
            v10[1] = *(u16 *)(s2 + 0xA); \
            v10[2] = *(u16 *)(s2 + 0xE); \
            func_800D20C0(v10, out, 1); \
            func_800D23D0(out); \
            RotMatrixYXZ(out, (void *)s1); \
        } \
        func_80169584(s2); \
        *(u16 *)(s2 + 0x2) = *(u16 *)(s2 + 0x2) + 1; \
    }

#define DEFINE_func_8016432C() \
    extern void func_80164418(); \
    extern s32 func_80146E98(s32 a0); \
    extern void func_801553C0(s32 a0); \
    extern void func_80147364(u16, s32); \
    extern void func_80147324(s32 arg0); \
    extern void func_80162CCC(void); \
    void func_8016432C(s32 a0) { \
        s32 s1 = a0; \
        s32 s0 = *(s32 *)(s1 + 0x4C); \
        func_80164418(); \
        if (func_80146E98(s1) != 0) { \
            u32 v44; \
            *(u16 *)(s0 + 0x18A) = 0; \
            if (*(s32 *)(s0 + 0x184) != 0 && \
                ((v44 = *(u32 *)(s0 + 0x44)) & 0x400) == 0 && \
                (*(u32 *)(s0 + 0x1F8) & 0x80FFFFFF) == 0) { \
                *(u32 *)(s0 + 0x44) = v44 | 0x10; \
                if (*(s16 *)(s0 + 0x188) < 0x80) { \
                    *(u32 *)(s0 + 0x184) = *(u32 *)(s0 + 0x184) | 0x80000000; \
                } \
            } else { \
                *(s32 *)(s0 + 0x184) = 0; \
            } \
            *(u16 *)(s0 + 0x188) = 0; \
            __asm__ __volatile__("" : : "r"(s0)); \
            *(u32 *)(s0 + 0x44) = *(u32 *)(s0 + 0x44) & 0xFFFFFFFB; \
            func_801553C0(s0); \
            func_80147364(4, 0x449); \
            func_80147324(0x44B); \
            ((void (*)(s32))func_80162CCC)(s1); \
        } \
    }

#define DEFINE_func_8017849C() \
    extern void func_801787D4(void); \
    extern void func_8012A908(void); \
    extern void func_8017869C(s32 a0); \
    extern void func_80130D0C(s32 a0); \
    extern void func_8013E370(void); \
    extern u8 D_801202A0[]; \
    extern u16 D_801270C0; \
    extern s32 D_8011DB08; \
    void func_8017849C(void) { \
        register u8 *p __asm__("$17");   /* $s1 base */ \
        register u8 *q __asm__("$16");   /* $s0 = base + 0x54 */ \
        register s32 i __asm__("$18");   /* $s2 counter */ \
        p = (u8 *)D_801202A0; \
        func_801787D4(); \
        i = 0; \
        func_8012A908(); \
        q = p + 0x54; \
        do { \
            if (*(u16 *)p != 0 && \
                (*(s16 *)&D_801270C0 == 1 || (*(u16 *)(q + 0x1E) & 0x1000) != 0)) { \
                register s32 tbl __asm__("$3"); register s32 c6c __asm__("$2"); \
                func_8017869C((s32)p); \
                *(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50); \
                c6c = *(u8 *)(q + 0x6C); \
                *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C); \
                tbl = D_8011DB08; \
                *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48); \
                if (c6c != 0 && *(u8 *)(q + 0x6D) != 0) { \
                    func_80130D0C((s32)p); \
                } else { \
                    (*(void (**)(s32))(tbl + *(u16 *)p * 4))((s32)p); \
                } \
                if (*(s32 *)(q - 0x34) != 0) { \
                    *(s16 *)(*(s32 *)(q - 0x34) + 8) = \
                        *(u16 *)(q - 0x4E) + *(u16 *)(q - 0x4); \
                    *(s16 *)(*(s32 *)(q - 0x34) + 10) = \
                        *(u16 *)(q - 0x4A) + *(u16 *)(q - 0x2); \
                    *(s16 *)(*(s32 *)(q - 0x34) + 0xC) = \
                        *(u16 *)(q - 0x46) + *(u16 *)q; \
                } \
            } \
            i++; \
            q += 0x10C; \
            p += 0x10C; \
        } while (i < 0x60); \
        if (*(s16 *)&D_801270C0 == 1) { \
            func_8013E370(); \
        } \
    }

#define DEFINE_func_80168BDC() \
    extern void func_800D2318(void); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) \
    { \
        short mtx[16]; \
        short vec[4]; \
        int r; \
        register int i __asm__("$17");     /* loop counter, survives the call -> $s1 */ \
        register int tmp __asm__("$2");    /* increment temp -> $v0 (the split-IV) */ \
        func_800D2318(); \
        vec[0] = *(short *)(param_1 + 0x12); \
        vec[1] = *(short *)(param_1 + 0x16); \
        vec[2] = 0; \
        RotMatrixYXZ(vec, mtx); \
        vec[0] = 0; \
        if (*(int *)(param_1 + 0x2c) < 0) { \
            vec[2] = -8; \
            vec[1] = -4; \
        } else { \
            vec[2] = 2; \
            vec[1] = -2; \
        } \
        ApplyMatrixSV(mtx, vec, vec); \
        *(short *)(param_1 + 6) = *(short *)(param_1 + 6) + vec[0]; \
        *(short *)(param_1 + 0xa) = *(short *)(param_1 + 0xa) + vec[1]; \
        *(short *)(param_1 + 0xe) = *(short *)(param_1 + 0xe) + vec[2]; \
        i = 0; \
        if ((short)param_4 > 0) { \
            do { \
                r = func_80146A6C((unsigned short)param_2, (void *)param_1, \
                                  (short)*(short *)(param_1 + 6), \
                                  (short)*(short *)(param_1 + 0xa), \
                                  (short)*(short *)(param_1 + 0xe), \
                                  (short)param_3, 0); \
                if (r != 0) { \
                    *(short *)(r + 0x12) = *(short *)(param_1 + 0x12); \
                    *(short *)(r + 0x16) = *(short *)(param_1 + 0x16); \
                    *(short *)(r + 0x1a) = *(short *)(param_1 + 0x1a); \
                } \
                tmp = i + 1; \
                i = tmp; \
                __asm__ __volatile__("" : "=r"(i) : "0"(i)); \
            } while ((short)tmp < (short)param_4); \
        } \
    }

#define DEFINE_func_80155A44() \
    extern s32 func_80029178(s32 arg); \
    extern u8 func_8014BEF8(void); \
    extern u16 func_80148800(s32 *a0); \
    extern void func_80149CB4(void); \
    int func_80155A44(int param_1) \
    { \
        int x = *(unsigned char *)(param_1 + 0x1AA); \
        switch (x) { \
        case 0: \
        case 1: \
            if ((((unsigned char (*)(int))func_80029178)(0x85) & 0xFF) && \
                ((int (*)(int))func_8014BEF8)(param_1) && \
                *(unsigned char *)(param_1 + 0x1C0) && \
                (((int (*)(int))func_80148800)(param_1) & 0x10)) { \
                ((void (*)(int, int))func_80149CB4)(param_1, 2); \
                return 1; \
            } \
            break; \
        case 2: \
            if ((((unsigned char (*)(int))func_80029178)(0x86) & 0xFF) && \
                (((int (*)(int))func_80148800)(param_1) & 0x10)) { \
                ((void (*)(int, int))func_80149CB4)(param_1, 3); \
                return 1; \
            } \
            break; \
        } \
    }

#define DEFINE_func_80158E24() \
    extern u16 func_801487F4(s32 *a0); \
    extern s32 func_80159434(s32 a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern M2C_UNK D_800D5904; \
    void func_80158E24(s32 *a0) { \
        s32 n; \
        s32 c; \
        c = 0x4C000; \
        n = 1; \
        if (func_801487F4(a0) & 0xF0) { \
            n = 4; \
        } \
        while (n > 0) { \
            func_80159434((s32)a0, c); \
            if (*(s16 *)(a0[0x20 / 4] + 0x10) < 0xC00) { \
                *(s16 *)(a0[0x20 / 4] + 0x10) = 0xC00; \
                func_80154274(a0, (s32)&D_800D5904); \
                func_80154A74((s32)a0, 0x20); \
                func_8002D4C8(0x2A, 0); \
                func_8002D4C8(0x1C, 0); \
                func_80146CA0(a0); \
                n = 0; \
            } \
            n--; \
        } \
    }

#define DEFINE_func_8016AA50() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80146C3C(void); \
    extern s32 D_8011D030; \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    void func_8016AA50(s32 param_1, s32 param_2) { \
        register short *psVar3 __asm__("$4"); \
        register s32 iVar4 __asm__("$5"); \
        register s32 sVar2 __asm__("$3"); \
        register s32 t __asm__("$2"); \
        if (param_2 >= 0) { \
            ((s32 (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)( \
                0x1d, (void *)param_1, \
                *(s16 *)(param_1 + 0x7c), *(s16 *)(param_1 + 0x7e), \
                *(s16 *)(param_1 + 0x80), 0, param_2); \
            return; \
        } \
        iVar4 = 0; \
        psVar3 = (short *)&D_8011D030; \
        do { \
            sVar2 = (u16)*psVar3; \
            if (sVar2 == 0 || sVar2 == 3 || sVar2 == 9) { \
                ((void (*)(void))func_80146C3C)(); \
                ((s32 (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)( \
                    0x1d, (void *)param_1, \
                    (s16)D_80126B5E, (s16)((u16)D_80126B62 - 0x20), \
                    (s16)D_80126B66, 7, 0); \
                return; \
            } \
            t = iVar4 + 1; \
            iVar4 = t; \
            __asm__ __volatile__("" : "=r"(t) : "0"(t)); \
            psVar3 = psVar3 + 0x2c; \
        } while ((s16)t < 0x1e); \
    }

#define DEFINE_func_801439FC() \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_8012C218(void *a0); \
    extern s32 func_80134510(s32 arg); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s16 D_801152AC; \
    extern s16 D_801152AA; \
    extern u8 D_801152A8[]; \
    void func_801439FC(s32 a0) { \
        s32 s1 = *(s32 *)(a0 + 0x64); \
        s32 s0 = *(s32 *)(a0 + 0xCC); \
        s16 sp[3]; \
        s32 v0; \
        if (*(s16 *)(s1 + 0x36) != *(s16 *)(a0 + 0xFC)) { \
            if (a0 == 0) { \
                return; \
            } \
            func_80016714((void *)s0, 0x38); \
            func_8012C218((void *)a0); \
            return; \
        } \
        sp[0] = *(u16 *)(s1 + 6); \
        sp[1] = *(u16 *)(s1 + 0xA) - 0x10; \
        sp[2] = *(u16 *)(s1 + 0xE); \
        if (func_80134510((s32)&sp[0]) == 0) { \
            *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) | 0x80000000; \
            return; \
        } \
        *(s16 *)(s0 + 8) = sp[0]; \
        *(s16 *)(s0 + 0xA) = sp[1]; \
        *(s16 *)(s0 + 0xC) = sp[2]; \
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & 0x7FFFFFFF; \
        *(s16 *)(s0 + 0x10) = ratan2(D_801152AC, D_801152AA) + 0x400; \
        *(s16 *)(s0 + 0x12) = ratan2(*(s16 *)D_801152A8, D_801152AA); \
        v0 = *(s32 *)(s1 + 0x20); \
        *(s16 *)(s0 + 0x14) = -(*(u16 *)(v0 + 0x12)); \
    }

#define DEFINE_func_801415C0() \
    extern s32 func_800291B4(s32 arg); \
    extern void func_800291A0(s32, s32); \
    extern s32 func_800291DC(s32); \
    extern void func_800291C8(s32, s32); \
    void func_801415C0(s32 param_1, s32 param_2) { \
        register s32 a __asm__("$16");  /* $s0: param_2 raw -> sext -> *2+0x14 */ \
        register s32 b __asm__("$17");  /* $s1: param_1 sext / *2+0x14 */ \
        register s32 c __asm__("$18");  /* $s2: param_2 sext + 0x2F   */ \
        register s32 d __asm__("$19");  /* $s3: param_1 sext + 0x2F   */ \
        register s32 e __asm__("$20");  /* $s4: 291B4(d)&0xFF / 291DC(b) */ \
        a = param_2; \
        b = (s16)param_1; \
        d = b + 0x2F; \
        e = func_800291B4(d) & 0xFF; \
        a = (s16)a; \
        c = a + 0x2F; \
        func_800291A0(d, func_800291B4(c) & 0xFF); \
        func_800291A0(c, e); \
        b = b * 2 + 0x14; \
        e = func_800291DC(b); \
        a = a * 2 + 0x14; \
        func_800291C8(b, (s16)func_800291DC(a)); \
        func_800291C8(a, (s16)e); \
    }

#define DEFINE_func_80144558() \
    extern void func_8012C194(void); \
    extern void func_8012CAE4(void *a0); \
    extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80128EA8(s32 a0, s32 a1, s32 a2); \
    extern void func_8012B200(u8 *a0); \
    extern u8 D_800D387C[]; \
    extern u8 D_800D3888[]; \
    void func_80144558(u8 *param_1) { \
        s32 s0; \
        s0 = ((s32 (*)(void))func_8012C194)(); \
        if (s0 == 0) { \
            func_8012CAE4(param_1); \
        } else { \
            *(s32 *)(param_1 + 0xCC) = s0; \
            func_8001CC3C(s0, 0, 0, 0); \
            *(s32 *)(s0 + 0x20) = (s32)D_800D387C; \
            *(u8 *)(s0 + 0x27) = 0x9C; \
            *(u16 *)(s0 + 0x1A) = 0x3000; \
            *(u16 *)(s0 + 0x18) = 0x3000; \
            *(u32 *)(s0 + 4) = *(u32 *)(s0 + 4) | 0x50000000; \
            func_80128EA8(s0, (s32)(param_1 + 0xD0), (s32)D_800D3888); \
            *(u16 *)(s0 + 8) = *(u16 *)(param_1 + 6); \
            *(u16 *)(s0 + 0xA) = *(u16 *)(param_1 + 0xA); \
            *(u16 *)(s0 + 0xC) = *(u16 *)(param_1 + 0xE); \
            *(u16 *)(param_1 + 2) = 1; \
            func_8012B200(param_1); \
        } \
    }

#define DEFINE_func_80145B24() \
    extern s32 func_80029504(void); \
    extern s32 func_800291DC(s32); \
    extern void func_800291C8(s32, s32); \
    extern void func_80162120(void); \
    extern void func_80029124(s32, s32); \
    extern s32 func_80165A50(s32); \
    extern void func_80029514(s32); \
    extern u8 D_800AF630[]; \
    extern u8 D_80078EC0; \
    extern s32 D_80126B58; \
    void func_80145B24(void) \
    { \
        s32 iVar1; \
        s32 uVar2; \
        register u8 *p __asm__("$17"); \
        p = &D_800AF630; \
        iVar1 = func_80029504(); \
        uVar2 = func_800291DC(8); \
        if ((uVar2 & 0x8000) != 0) { \
            func_800291C8(8, 0); \
            func_80162120(); \
        } \
        if (iVar1 >= 0x6A4) { \
            func_80029124(0x1A, 0); \
            func_80029124(0x8E, 0); \
            func_80029124(0x143, 0); \
            if ((D_80078EC0 & 0x7F) != 0) { \
                D_80078EC0 = 1; \
            } \
            func_80165A50((s32)&D_80126B58); \
            func_80029514(0x4B0); \
        } \
        *(s16 *)(p + 0xA3DA) = 0x3000; \
    }

#define DEFINE_func_801446A4() \
    extern void func_8012C194(void); \
    extern void func_8012CAE4(void *a0); \
    extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80128EA8(s32 a0, s32 a1, s32 a2); \
    extern u8 D_800D3888[]; \
    extern u8 D_800D387C[]; \
    void func_801446A4(int param_1) \
    { \
        register int s1 __asm__("$17"); \
        register int iVar1 __asm__("$16"); \
        s1 = param_1; \
        iVar1 = ((int (*)(void))func_8012C194)(); \
        if (iVar1 == 0) { \
            ((void (*)(int))func_8012CAE4)(s1); \
        } else { \
            *(int *)(s1 + 0xcc) = iVar1; \
            ((void (*)(int, int, int, int))func_8001CC3C)(iVar1, 0, 0, 0); \
            *(int *)(iVar1 + 0x20) = (int)&D_800D387C; \
            *(unsigned char *)(iVar1 + 0x27) = 0x9c; \
            *(short *)(iVar1 + 0x1a) = 0x3000; \
            *(short *)(iVar1 + 0x18) = 0x3000; \
            *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000; \
            func_80128EA8(iVar1, s1 + 0xd0, (int)&D_800D3888); \
            *(short *)(iVar1 + 8) = *(unsigned short *)(s1 + 6); \
            *(short *)(iVar1 + 0xa) = *(unsigned short *)(s1 + 0xa); \
            *(short *)(iVar1 + 0xc) = *(unsigned short *)(s1 + 0xe); \
            *(short *)(s1 + 2) = *(short *)(s1 + 2) + 1; \
        } \
    }

#define DEFINE_func_80173E1C() \
    extern void func_801484B0(s32 a0, s32 a1); \
    extern void func_80149350(s32 arg0); \
    extern void func_80015954(s32 a0, s32 a1); \
    extern s32 func_801399F0(s32 a0); \
    extern void func_80139914(s32 a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 D_80127508; \
    extern u8 D_800D5DC0[]; \
    void func_80173E1C(s32 a0) \
    { \
        register s32 s0 __asm__("$16"); \
        register s32 *s1 __asm__("$17"); \
        s32 sp10[2]; \
        s32 sp18[2]; \
        s1 = &D_80127508; \
        s0 = a0; \
        if (*s1 != 0) { \
            func_801484B0((s32)sp10, (s32)sp18); \
            ((void (*)(s32, s32, s32))func_80149350)(s0, (s32)sp10, (s32)sp10); \
            func_80015954((s32)sp10, *s1 + 4); \
        } \
        if (*(s32 *)(s0 + 0x198) != 0) { \
            if (func_801399F0(*(s32 *)(s0 + 0x198)) == 0) { \
                return; \
            } \
            func_80139914(*(s32 *)(s0 + 0x198)); \
            *(s32 *)(s0 + 0x198) = 0; \
            func_80154274((s32 *)s0, (s32)&D_800D5DC0); \
            func_80171A1C((u8 *)s0); \
        } else { \
            s32 iVar1 = *(s32 *)(s0 + 0x200) - 1; \
            *(s32 *)(s0 + 0x200) = iVar1; \
            if (iVar1 != -1) { \
                return; \
            } \
            func_80154274((s32 *)s0, (s32)&D_800D5DC0); \
            func_80171A1C((u8 *)s0); \
        } \
    }

#define DEFINE_func_801716AC() \
    extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern u8 D_800A5E94; \
    extern u8 D_800A5E95; \
    extern u8 D_800A5E96; \
    s32 func_801716AC(s32 a0, void * a1, s32 * a2) \
    { \
        s32 d; \
        s32 p; \
        a0 = a0 * 0x10; \
        p = a0 + (s32)a1; \
        d = (s16)func_80012FC8(*(u8 *)(p + 0xC), (&D_800A5E94)[a0], 10, 1); \
        *a2 += d; \
        *(char *)(p + 0xC) = *(u8 *)(p + 0xC) + d; \
        d = (s16)func_80012FC8(*(u8 *)(p + 0xD), (&D_800A5E95)[a0], 10, 1); \
        *a2 += d; \
        *(char *)(p + 0xD) = *(u8 *)(p + 0xD) + d; \
        d = (s16)func_80012FC8(*(u8 *)(p + 0xE), (&D_800A5E96)[a0], 10, 1); \
        *a2 += d; \
        *(char *)(p + 0xE) = *(u8 *)(p + 0xE) + d; \
    }

#define DEFINE_func_80155D70() \
    extern u16 func_801487F4(s32 *a0); \
    extern void func_801599A4(void *a0); \
    extern void func_8015E880(s32 *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8014CC28(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_8015BDD0(s32 *a0); \
    void func_80155D70(s32 param_1) \
    { \
        s32 iVar2; \
        s32 iVar3; \
        char buf[64]; \
        *(u32 *)(param_1 + 0x44) |= 2; \
        if (*(u16 *)(param_1 + 0xB8) == 0x8000) { \
            if ((((s32 (*)(void))func_801487F4)() & 0x80) != 0) { \
                ((void (*)(s32))func_801599A4)(param_1); \
                ((void (*)(s32))func_8015E880)(param_1); \
            } else { \
                ((void (*)(s32))func_801599A4)(param_1); \
                ((void (*)(s32))func_80159B3C)(param_1); \
            } \
        } else { \
            iVar2 = ((s32 (*)(s32))func_8014CC28)(param_1); \
            iVar3 = ((s32 (*)(s32))func_8014F3E8)(param_1); \
            if (iVar3 == 0 && iVar2 == 0) { \
                ((void (*)(s32))func_801599A4)(param_1); \
                ((void (*)(s32))func_8015BDD0)(param_1); \
            } \
        } \
        (void)buf; \
    }

#define DEFINE_func_80151DB0() \
    extern void func_80019064(void *a0); \
    extern int func_80151204(int arg, int a1); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80149020(s32 *a0); \
    extern void func_80147324(s32 arg0); \
    extern void func_80146CA0(void *a0); \
    extern s32 func_80172630(u8 *a0); \
    extern s32 D_80062C14; \
    extern M2C_UNK D_800D5880; \
    extern s32 D_800D58AC; \
    void func_80151DB0(s32 param_1) \
    { \
        short sVar1; \
        unsigned short uVar2; \
        int iVar3; \
        func_80019064(&D_80062C14); \
        ((void (*)(int, int))func_80151204)(param_1, (int)*(short *)(param_1 + 0xf2)); \
        sVar1 = ((short (*)(int, int))func_80012A60)((int)*(short *)(*(int *)(param_1 + 0x20) + 0x12), \
                              (int)*(short *)(param_1 + 0xf4)); \
        if (sVar1 >= 0x401) { \
            ((void (*)(int, void *))func_80154274)(param_1, &D_800D5880); \
            iVar3 = *(int *)(param_1 + 0x20); \
            uVar2 = 0xc00; \
        } else { \
            ((void (*)(int, void *))func_80154274)(param_1, &D_800D58AC); \
            iVar3 = *(int *)(param_1 + 0x20); \
            uVar2 = 0x400; \
        } \
        *(unsigned short *)(iVar3 + 0x10) = uVar2; \
        *(unsigned short *)(param_1 + 100) = 0xcc; \
        __asm__ __volatile__("" : : "r"(param_1)); \
        ((void (*)(int))func_80149020)(param_1); \
        func_80147324(0x436); \
        ((void (*)(int))func_80146CA0)(param_1); \
        ((void (*)(int))func_80172630)(param_1); \
    }

#define DEFINE_func_8014B944() \
    extern s32 func_80029178(s32 arg); \
    extern u8 D_80078E78[]; \
    extern s32 D_80078EA4; \
    extern u16 D_80078EA6; \
    void func_8014B944(s32 a0, s32 a1, s32 a2) \
    { \
        u8 *base = D_80078E78; \
        if (a2 != 0) { \
            D_80078EA4 += a1; \
            __asm__ __volatile__("" ::: "memory"); \
            if ((s16)D_80078EA6 >= 0xA1) { \
                D_80078EA4 = 0xA00000; \
            } \
        } else { \
            if ((func_80029178(0x1B) & 0xFF) != 0) { \
                D_80078EA4 += a1; \
                __asm__ __volatile__("" ::: "memory"); \
                if ((s16)D_80078EA6 >= 0xA1) { \
                    D_80078EA4 = 0xA00000; \
                } \
            } else { \
                if ((s16)D_80078EA6 < 0x80) { \
                    D_80078EA4 += a1; \
                    __asm__ __volatile__("" ::: "memory"); \
                    if ((s16)D_80078EA6 >= 0x81) { \
                        D_80078EA4 = 0x800000; \
                    } \
                } \
            } \
        } \
        if (a2 != 0) { \
            *(s32 *)(base + 0x60) += a1; \
            if (*(s16 *)(base + 0x62) >= 0xA1) { \
                *(s32 *)(base + 0x60) = 0xA00000; \
            } \
        } else { \
            if ((func_80029178(0x1B) & 0xFF) != 0) { \
                *(s32 *)(base + 0x60) += a1; \
                if (*(s16 *)(base + 0x62) >= 0xA1) { \
                    *(s32 *)(base + 0x60) = 0xA00000; \
                } \
            } else { \
                if (*(s16 *)(base + 0x62) < 0x80) { \
                    *(s32 *)(base + 0x60) += a1; \
                    if (*(s16 *)(base + 0x62) >= 0x81) { \
                        *(s32 *)(base + 0x60) = 0x800000; \
                    } \
                } \
            } \
        } \
    }

#define DEFINE_func_8014A59C() \
    extern u8 D_80078EBF; \
    extern s32 func_80029178(s32 arg); \
    void func_8014A59C(s32 a0) { \
        s32 r; \
        s32 add; \
        if (*(u32 *)(a0 + 0x44) & 1) { \
            if ((*(u16 *)(a0 + 0xAA) & 8) != 0) { \
                r = func_80029178(0x20); \
                add = 3; \
                if ((r & 0xFF) != 0) { \
                    add = 6; \
                } \
                D_80078EBF = D_80078EBF + add; \
                if (0x80 < D_80078EBF) { \
                    __asm__ __volatile__(""); \
                    D_80078EBF = 0x80; \
                } \
            } \
        } else { \
            D_80078EBF = 0; \
        } \
    }

#define DEFINE_func_80157AC8() \
    extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_801473EC(s32 *a0); \
    extern s32 func_80161208(); \
    extern void func_8016706C(s32 a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern int func_80155FF8(int arg, int a1); \
    extern s32 func_801725A4(u8 *a0); \
    extern u8 D_800D51AC[]; \
    void func_80157AC8(s32 param_1) \
    { \
        *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2; \
        ((s32 (*)(s32, s32, s32, s32))func_80147AD4)(param_1, 0, 0, 0x10000); \
        ((void (*)(s32))func_801473EC)(param_1); \
        if (((s32 (*)(s32))func_80161208)(param_1) == 0) { \
            if (*(s32 *)(param_1 + 0x2c) > 0) { \
                func_8016706C(4); \
                func_8016706C(5); \
                ((void (*)(s32, s32))func_80154274)(param_1, (s32)D_800D51AC); \
                ((void (*)(s32))func_80146CA0)(param_1); \
            } else { \
                ((void (*)(s32, s32))func_80155FF8)(param_1, *(u8 *)(param_1 + 0x1aa)); \
                ((void (*)(s32))func_801725A4)(param_1); \
            } \
        } \
    }

#define DEFINE_func_80151AE4() \
    extern void func_80149020(s32 *a0); \
    extern void func_80151C54(s32 a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_801542DC(s32 *a0, s32 a1); \
    extern void func_8014E934(s32 a0); \
    extern s32 func_8014F3E8(s32 a0); \
    extern void func_8014CC28(s32 a0); \
    extern void func_8015BDD0(s32 *a0); \
    extern void func_80165718(s32 a0); \
    extern u8 D_800D46E4[]; \
    extern M2C_UNK D_800D5880; \
    void func_80151AE4(s32 arg0) \
    { \
        func_80149020(arg0); \
        if (*(u16 *)((s32)arg0 + 0xB8) == 0x8000) { \
            func_80151C54(arg0); \
            func_80159B3C(arg0); \
            if (*(s32 *)((s32)arg0 + 0xB4) == (s32)&D_800D5880) { \
                ((void (*)(s32, s32, s32))func_801542DC)(arg0, (s32)D_800D46E4, 0xE); \
            } \
        } else { \
            func_8014E934(arg0); \
            if (((s32 (*)(s32))func_8014F3E8)(arg0) != 0) { \
                return; \
            } \
            if (((s32 (*)(s32))func_8014CC28)(arg0) != 0) { \
                return; \
            } \
            func_80151C54(arg0); \
            func_8015BDD0(arg0); \
        } \
        func_80165718(arg0); \
    }

#define DEFINE_func_80155EA4() \
    extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_801473EC(s32 *a0); \
    extern void func_8014C010(s32 a0, s32 a1); \
    extern int func_80155FF8(int arg, int a1); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern s32 func_80161208(); \
    extern u16 D_800B99DA; \
    void func_80155EA4(void *arg0) { \
        volatile s32 spill[4];  /* forces the 0x28 frame the target reserves */ \
        *(s32 *)((u8 *)arg0 + 0x44) |= 2; \
        func_80147AD4((s32)arg0, 0, 0, 0x8000); \
        func_801473EC((s32 *)arg0); \
        if ((D_800B99DA & 3) == 0) { \
            func_8014C010((s32)arg0, 2); \
        } \
        func_80155FF8((int)arg0, *(u8 *)((u8 *)arg0 + 0x1AA)); \
        if ((*(s32 *)((u8 *)arg0 + 0x2C) >= 0) || (*(u8 *)((u8 *)arg0 + 0x1C0) != 0)) { \
            func_801599A4(arg0); \
            func_80159B3C(arg0); \
        } else { \
            ((void (*)(void *))func_80161208)(arg0); \
        } \
    }

#define DEFINE_func_80177F84() \
    void func_80177F84(s32 param_1, s32 param_2) { \
        u16 uVar4; \
        s16 iVar3; \
        register u8 *pcVar2 __asm__("$6"); \
        u32 uVar1; \
        register s32 c5 __asm__("$10"); \
        register s32 cmask __asm__("$9"); \
        uVar4 = 0x100; \
        iVar3 = 0; \
        c5 = 5; \
        cmask = -257; \
        pcVar2 = (u8 *)(param_1 + 0xc); \
        do { \
            register u32 src __asm__("$2"); \
            register u32 byteval __asm__("$3"); \
            register u32 testval __asm__("$4"); \
            src = (param_2 >> 0x10) & 0xf; \
            __asm__ __volatile__("" : : "r"(src)); \
            byteval = src; \
            __asm__ __volatile__("" : "=r"(byteval) : "0"(byteval)); \
            testval = src; \
            __asm__ __volatile__("" : : "r"(byteval), "r"(testval)); \
            param_2 = param_2 << 4; \
            if ((iVar3 == c5) || (testval != 0)) { \
                uVar4 = 0; \
            } \
            pcVar2 += 0x14; \
            iVar3 += 1; \
            { \
                register s32 r __asm__("$4"); \
                r = *(u16 *)(pcVar2 - 2); \
                pcVar2[0] = (u8)(byteval * 8 + 8); \
                *(u16 *)(pcVar2 - 2) = uVar4 | (r & cmask); \
            } \
        } while (iVar3 < 5); \
    }

#define DEFINE_func_80147C30() \
    extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4); \
    extern s32 D_80127090; \
    extern s32 D_80127094; \
    extern s32 D_80127098; \
    void func_80147C30(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 out[3]; \
        s32 *p0 = &D_80127090; \
        s32 *p1 = &D_80127094; \
        s32 *p2 = &D_80127098; \
        func_80147CC8(a0, a1, a2, a3, (s32)out); \
        D_80127090 = out[0]; \
        D_80127094 = out[1]; \
        D_80127098 = out[2]; \
        *(s32 *)(a0 + 0x10) = *p0; \
        *(s32 *)(a0 + 0x14) = *p1; \
        *(s32 *)(a0 + 0x18) = *p2; \
        D_80127090 = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
    }

#define DEFINE_func_8014FD54() \
    extern void func_80149290(s32 a0); \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    int func_8014FD54(int param_1) \
    { \
        short buf1[3]; \
        short buf2[4]; \
        int ret; \
        register int result __asm__("$2"); \
        buf1[0] = 0; \
        buf1[1] = 0; \
        buf1[2] = 7; \
        ((void (*)(int, void *, void *))func_80149290)(param_1, buf1, buf1); \
        buf2[0] = 0; \
        buf2[1] = 0; \
        buf2[2] = (short)0xffe8; \
        ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2); \
        ret = func_80133784(1, buf1, (int)buf2); \
        if (ret != 0) { \
            result = 0; \
            if ((ret & 0x8000) != 0) { \
                result = *(unsigned char *)((char *)buf2 + 6) == 0x15; \
            } \
        } else { \
            result = 0; \
        } \
        return result; \
    }

#define DEFINE_func_801416D4() \
    extern s16 D_8011514C; \
    extern u8 D_8011514D; \
    extern u8 D_8011515C; \
    extern s32 func_800D11F0(s32 a0); \
    extern s32 func_800D1658(s32 a0); \
    extern void func_80141C0C(s32); \
    s32 func_801416D4(s16 param_1) { \
        s32 cVar2; \
        register s32 iVar1 __asm__("$3"); \
        register s32 two __asm__("$6"); \
        two = 2; \
        iVar1 = 0; \
        cVar2 = *(u8 *)&D_8011514C + D_8011514D * D_8011515C; \
        if (param_1 == 1) goto c1; \
        if (param_1 < 2) { \
            if (param_1 == 0) goto c0; \
            goto ret; \
        } \
        if (param_1 == two) goto c2; \
        goto ret; \
    c0: \
        iVar1 = func_800D11F0(cVar2 & 0xFF); \
        goto ret; \
    c1: \
        iVar1 = func_800D1658(cVar2 & 0xFF); \
        goto ret; \
    c2: \
        func_80141C0C(6); \
        iVar1 = 1; \
    ret: \
        return (iVar1 << 0x10) >> 0x10; \
    }

#define DEFINE_func_8015B6F4() \
    extern s32 func_80149AA8(s32 *a0); \
    extern void func_80156648(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_80147324(s32 arg0); \
    extern void func_80147300(u16 arg0); \
    extern s32 D_800D4A9C; \
    int func_8015B6F4(int param_1) \
    { \
        register int b4 __asm__("$3"); \
        register unsigned int f44 __asm__("$2"); \
        register unsigned int bc __asm__("$4"); \
        if (((int (*)(void))func_80149AA8)() == 0) return 0; \
        ((void (*)(int))func_80156648)(param_1); \
        b4 = *(int *)(param_1 + 0xb4); \
        *(unsigned char *)(param_1 + 0x1aa) = 6; \
        __asm__ __volatile__("" ::: "memory"); \
        f44 = *(unsigned int *)(param_1 + 0x44); \
        bc = *(unsigned char *)(param_1 + 0xbc); \
        *(int *)(param_1 + 0x23c) = b4; \
        *(unsigned int *)(param_1 + 0x44) = f44 | 2; \
        *(unsigned char *)(param_1 + 0x244) = bc; \
        if (*(int *)(param_1 + 0xb4) == (int)&D_800D4A9C) { \
            func_80154150(param_1, 0xb); \
        } else { \
            func_80154150(param_1, 0xc); \
        } \
        func_80154A74(param_1, 0x22); \
        *(unsigned char *)(param_1 + 0xda) = 0; \
        ((void (*)(int, int, int, int))func_80146994)(4, param_1, 5, 0); \
        func_80147324(0x400); \
        ((void (*)(int))func_80147300)(0x5f3); \
        return 1; \
    }

#define DEFINE_func_8013E448() \
    extern s32 (*D_801274D0)(s32); \
    extern s32 D_801274D8; \
    extern s32 D_801274DC; \
    extern s16 D_80126CAC; \
    extern s32 func_800132BC(s32 a0, s32 a1); \
    s32 func_8013E448(s32 param_1) \
    { \
        s32 iVar1; \
        register s32 uVar2 __asm__("$2"); \
        if (D_801274D0 == 0) { \
            iVar1 = func_800132BC((s32)&D_80126CAC, param_1); \
            uVar2 = 0; \
            if (D_801274D8 < iVar1) { \
                uVar2 = (iVar1 < D_801274DC); \
            } \
            return uVar2; \
        } \
        return (*D_801274D0)(param_1); \
    }

#define DEFINE_func_801493D0() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8012F14C(s32); \
    extern void func_80015954(s32 a0, s32 a1); \
    void func_801493D0(s32 param_1, s32 param_2, s32 param_3) \
    { \
      u8 buf1[8]; \
      u8 *new_var; \
      u8 buf2[8]; \
      ((void (*)(s32, u8 *)) func_80015978)(param_2, buf1); \
      new_var = buf2; \
      ((void (*)(s32, u8 *, u8 *)) func_8012F14C)((*((s32 *) (param_1 + 0x20))) + 0x34, buf1, new_var); \
      new_var++; \
      new_var--; \
      ((void (*)(u8 *, s32)) func_80015954)(buf2, param_3); \
    }

#define DEFINE_func_80175414() \
    extern u8 D_8011F7A8; \
    extern u8 D_8011F7A9; \
    extern u8 D_8011F7AD; \
    extern u8 D_8011F7AE; \
    void func_80175414(s32 _arg0) \
    { \
        unsigned char *p = &D_8011F7A8; \
        if (*p == 1) { \
            *p = 0; \
            D_8011F7AD = 10; \
            D_8011F7A9 = 0; \
            D_8011F7AE = 0x37; \
        } \
        return; \
    }

#define DEFINE_func_80171928() \
    extern void func_80171A1C(u8 *a0); \
    void func_80171928(void * a0) \
    { \
        unsigned char idx     = *(unsigned char *)((char *)a0 + 0x214); \
        unsigned int *base    = *(unsigned int **)((char *)a0 + 0x1FC); \
        unsigned int  cur     = *(unsigned int *)((char *)a0 + 0x1F8); \
        *(unsigned int *)((char *)a0 + 0x1F8) = base[idx] | (cur & 0x7F000000); \
        ((void (*)(void *))func_80171A1C)(a0); \
    }

#define DEFINE_func_8014BD60() \
    extern s16 D_80078EB8; \
    void func_8014BD60(s32 param_1, s32 param_2) \
    { \
      int new_var; \
      int v1; \
      v1 = (int) ((unsigned short) D_80078EB8); \
      if (v1 < param_2) \
      { \
        D_80078EB8 = 0; \
      } \
      else \
      { \
        D_80078EB8 = (unsigned short) ((new_var = v1) - param_2); \
      } \
      return; \
    }

#define DEFINE_func_80173EF8() \
    extern s16 D_80126938; \
    extern s16 D_80126B3A; \
    extern void func_80147060(u8 *a0); \
    extern void func_800D128C(s32, s32); \
    extern void func_80029124(s32, s32); \
    extern void func_80029514(s32); \
    extern void func_80174158(s32 a0); \
    extern void func_8002A088(s32); \
    extern void func_8002A2D4(s32); \
    extern void func_8002A544(s32); \
    extern void func_8002A7B4(s32); \
    extern s32 func_80029178(s32 arg); \
    extern s32 func_80174188(s32 a0); \
    extern void func_801741A8(s32 a0); \
    extern s32  func_800D0EC4(void); \
    extern void func_800D0F0C(s32, s32); \
    extern void func_80145EE8(s32); \
    extern void func_80171A1C(u8 *a0); \
    void func_80173EF8(void *param_1) \
    { \
        if ((*(u16 *)((s32)param_1 + 0xB8) & 0x8000) == 0) { \
            return; \
        } \
        D_80126938 = 1; \
        ((void (*)(void))func_80147060)(); \
        switch (D_80126B3A) { \
        case 0: \
            break; \
        case 0x70: \
            func_800D128C((u8)D_80126B3A, 0); \
            break; \
        case 0x78: \
            func_80029124(0x8A, 1); \
            func_80029514(0xC8); \
            ((void (*)(void *))func_80174158)(param_1); \
            func_8002A088(0x64); \
            func_8002A2D4(0x20); \
            func_8002A544(0x20); \
            func_8002A7B4(0x18); \
            break; \
        case 0x79: \
            func_80029124(0x8B, 1); \
            func_80029514(0x258); \
            ((void (*)(void *))func_80174158)(param_1); \
            func_8002A088(0xA0); \
            func_8002A2D4(0x28); \
            func_8002A544(0x40); \
            func_8002A7B4(0x30); \
            break; \
        case 0x7A: \
            func_80029124(0x8C, 1); \
            func_80029514(0x384); \
            ((void (*)(void *))func_80174158)(param_1); \
            func_8002A088(0xF0); \
            func_8002A2D4(0x30); \
            func_8002A544(0x60); \
            func_8002A7B4(0x48); \
            break; \
        case 0x7B: \
            func_80029124(0x8D, 1); \
            func_80029514(0x4B0); \
            ((void (*)(void *))func_80174158)(param_1); \
            func_8002A088(0x140); \
            func_8002A2D4(0x40); \
            func_8002A544(0x80); \
            func_8002A7B4(0x60); \
            break; \
        case 0x7C: \
            if ((u8)func_80029178(0x11D) == 0) { \
                ((void (*)(void *))func_80174188)(param_1); \
            } \
            func_8002A088(0x190); \
            func_8002A2D4(0x50); \
            func_8002A544(0xA0); \
            func_8002A7B4(0x80); \
            ((void (*)(void *))func_801741A8)(param_1); \
            func_80029124(0x8E, 1); \
            break; \
        default: \
            func_800D0F0C(func_800D0EC4(), (s32)D_80126B3A); \
            break; \
        } \
        func_80145EE8(0); \
        ((void (*)(void *))func_80171A1C)(param_1); \
    }

#define DEFINE_func_80141CA4() \
    extern s32 func_80029504(void); \
    extern s32 func_80029178(s32 arg); \
    extern s32 func_800291B4(s32 arg); \
    extern unsigned char D_80112C04[]; \
    extern unsigned char D_80112C50[]; \
    extern unsigned char D_80112C9C[]; \
    extern unsigned char D_80112CE8[]; \
    extern unsigned char D_80112D38[]; \
    extern unsigned char D_80112D78[]; \
    extern unsigned char D_80112DBC[]; \
    extern unsigned char D_80112DF4[]; \
    extern unsigned char D_80112E14[]; \
    extern unsigned char D_80112E40[]; \
    extern unsigned char D_80112E6C[]; \
    extern unsigned char D_80112EBC[]; \
    extern unsigned char D_80112F0C[]; \
    extern unsigned char D_80112F48[]; \
    extern unsigned char D_80112F9C[]; \
    extern unsigned char D_80112FDC[]; \
    extern unsigned char D_8011302C[]; \
    extern unsigned char D_80113074[]; \
    extern unsigned char D_801130B8[]; \
    extern unsigned char D_801130E8[]; \
    extern unsigned char D_80113138[]; \
    extern unsigned char D_8011317C[]; \
    extern unsigned char D_801131A8[]; \
    extern unsigned char D_801131E8[]; \
    extern unsigned char D_80113214[]; \
    extern unsigned char D_80113254[]; \
    extern unsigned char D_80113278[]; \
    extern unsigned char D_801132B8[]; \
    extern unsigned char D_801132E4[]; \
    extern unsigned char D_80113324[]; \
    extern unsigned char D_80113360[]; \
    extern unsigned char D_801133A4[]; \
    extern unsigned char D_801133F4[]; \
    extern unsigned char D_80113440[]; \
    extern unsigned char D_80113474[]; \
    extern unsigned char D_801134B0[]; \
    extern unsigned char D_801134FC[]; \
    extern unsigned char D_80113530[]; \
    extern unsigned char D_80113554[]; \
    extern unsigned char D_801135A8[]; \
    extern unsigned char D_80113600[]; \
    extern unsigned char D_80113650[]; \
    extern unsigned char D_80113694[]; \
    extern unsigned char D_801136DC[]; \
    extern unsigned char D_80113724[]; \
    extern unsigned char D_80113744[]; \
    extern unsigned char D_80113770[]; \
    extern unsigned char D_80113794[]; \
    extern unsigned char D_801137D8[]; \
    extern unsigned char D_8011381C[]; \
    extern unsigned char D_8011383C[]; \
    extern unsigned char D_8011386C[]; \
    extern unsigned char D_801138A4[]; \
    extern unsigned char D_801138D0[]; \
    extern unsigned char D_80113900[]; \
    extern unsigned char D_80113944[]; \
    extern unsigned char D_80113964[]; \
    extern unsigned char D_8011399C[]; \
    extern unsigned char D_801139E8[]; \
    extern unsigned char D_80113A28[]; \
    extern unsigned char D_80113A50[]; \
    extern unsigned char D_80113A84[]; \
    extern unsigned char D_80113AB0[]; \
    extern unsigned char D_80113AE0[]; \
    extern unsigned char D_80113B34[]; \
    extern unsigned char D_80113B68[]; \
    extern unsigned char D_80113BA4[]; \
    extern unsigned char D_80113BC0[]; \
    extern unsigned char D_80113BF0[]; \
    extern unsigned char D_80113C20[]; \
    extern unsigned char D_80113C3C[]; \
    extern unsigned char D_80113C7C[]; \
    unsigned char *func_80141CA4(void) { \
        s32 iVar3; \
        register s32 cVar1 __asm__("$3"); \
        iVar3 = func_80029504(); \
        if (iVar3 < 10) { \
            return D_80112C04; \
        } \
        if (iVar3 < 0x14) { \
            if (func_80029178(0xdf) & 0xff) { \
                return D_80112D38; \
            } \
            if (func_80029178(0xe0) & 0xff) { \
                return D_80112CE8; \
            } \
            cVar1 = func_80029178(0xde) & 0xff; \
            if (cVar1) { \
                return D_80112C9C; \
            } \
            return D_80112C50; \
        } \
        if (iVar3 < 0x1e) { \
            return D_80112D78; \
        } \
        if (iVar3 < 0x28) { \
            return D_80112DBC; \
        } \
        if (iVar3 < 0x32) { \
            return D_80113B34; \
        } \
        if (iVar3 < 0x3c) { \
            cVar1 = func_80029178(0xe5) & 0xff; \
            if (cVar1 == 0) { \
                return D_80112DF4; \
            } \
            return D_80112E14; \
        } \
        if (iVar3 < 0x46) { \
            return D_80112E40; \
        } \
        if (iVar3 < 0x50) { \
            return D_80112E6C; \
        } \
        if (iVar3 < 0x5a) { \
            return D_80112EBC; \
        } \
        if (iVar3 < 100) { \
            return D_80112F0C; \
        } \
        if (iVar3 < 0x78) { \
            return D_80112F48; \
        } \
        if (iVar3 < 0x82) { \
            return D_80112F9C; \
        } \
        if (iVar3 < 0x85) { \
            if (func_80029178(0x9e) & 0xff) { \
                return D_80113074; \
            } \
            cVar1 = func_80029178(0xef) & 0xff; \
            if (cVar1 == 0) { \
                return D_80112FDC; \
            } \
            return D_8011302C; \
        } \
        if (iVar3 < 0x87) { \
            return D_801130B8; \
        } \
        if (iVar3 < 0x8c) { \
            return D_801130E8; \
        } \
        if (iVar3 < 0x96) { \
            return D_80113138; \
        } \
        if (iVar3 < 200) { \
            return D_8011317C; \
        } \
        if (iVar3 < 0xd2) { \
            return D_801131A8; \
        } \
        if (iVar3 < 0xdc) { \
            return D_801131E8; \
        } \
        if (iVar3 < 0xf0) { \
            return D_80113214; \
        } \
        if (iVar3 < 0x104) { \
            return D_80113254; \
        } \
        if (iVar3 < 0x118) { \
            return D_80113278; \
        } \
        if (iVar3 < 0x136) { \
            if (func_80029178(0xf9) & 0xff) { \
                return D_801132E4; \
            } \
            cVar1 = func_80029178(0xfa) & 0xff; \
            if (cVar1) { \
                return D_80113324; \
            } \
            return D_801132B8; \
        } \
        if (iVar3 < 0x140) { \
            return D_80113360; \
        } \
        if (iVar3 < 0x14a) { \
            cVar1 = func_80029178(0xff) & 0xff; \
            if (cVar1) { \
                return D_801133F4; \
            } \
            return D_801133A4; \
        } \
        if (iVar3 < 0x17c) { \
            return D_80113440; \
        } \
        if (iVar3 < 0x186) { \
            return D_80113474; \
        } \
        if (iVar3 < 400) { \
            return D_801134B0; \
        } \
        if (iVar3 < 0x19a) { \
            return D_801134FC; \
        } \
        if (iVar3 < 0x1ae) { \
            return D_80113530; \
        } \
        if (iVar3 < 0x1cc) { \
            return D_80113554; \
        } \
        if (iVar3 < 0x1d1) { \
            return D_801135A8; \
        } \
        if (iVar3 < 0x1e0) { \
            return D_80113600; \
        } \
        if (iVar3 < 600) { \
            cVar1 = func_80029178(0xb3) & 0xff; \
            if (cVar1 == 0) { \
                return D_80113650; \
            } \
            return D_80113694; \
        } \
        if (iVar3 < 0x276) { \
            if (func_80029178(0x10c) & 0xff) { \
                return D_80113744; \
            } \
            cVar1 = func_80029178(0x10d) & 0xff; \
            if (cVar1) { \
                return D_80113770; \
            } \
            return D_801136DC; \
        } \
        if (iVar3 < 0x280) { \
            return D_80113724; \
        } \
        if (iVar3 < 0x28a) { \
            return D_80113794; \
        } \
        if (iVar3 < 0x29e) { \
            return D_801137D8; \
        } \
        if (iVar3 < 0x2a8) { \
            return D_8011381C; \
        } \
        if (iVar3 < 700) { \
            return D_8011383C; \
        } \
        if (iVar3 < 0x2c6) { \
            return D_8011386C; \
        } \
        if (iVar3 < 0x2d0) { \
            return D_801138A4; \
        } \
        if (iVar3 < 0x2da) { \
            return D_801138D0; \
        } \
        if (iVar3 < 0x2e4) { \
            return D_80113900; \
        } \
        if (iVar3 < 0x2f8) { \
            return D_80113944; \
        } \
        if (iVar3 < 900) { \
            return D_80113964; \
        } \
        if (iVar3 < 0x3a2) { \
            return D_8011399C; \
        } \
        if (iVar3 < 0x3ac) { \
            cVar1 = func_800291B4(0x3b) & 0xff; \
            if ((u32)cVar1 < 10) { \
                return D_801139E8; \
            } \
            return D_80113A28; \
        } \
        if (iVar3 < 0x3b6) { \
            return D_80113A50; \
        } \
        if (iVar3 < 0x3ca) { \
            __asm__ __volatile__(""); \
            return D_80113A28; \
        } \
        if (iVar3 < 0x3d4) { \
            return D_80113A84; \
        } \
        if (iVar3 < 0x3f2) { \
            return D_80113AB0; \
        } \
        if (iVar3 < 0x44c) { \
            return D_80113AE0; \
        } \
        if (iVar3 < 0x47e) { \
            return D_80113B68; \
        } \
        if (iVar3 < 0x492) { \
            return D_80113BA4; \
        } \
        if (iVar3 < 0x4b0) { \
            return D_80113BC0; \
        } \
        if (iVar3 < 0x4ba) { \
            cVar1 = func_80029178(0x138) & 0xff; \
            if (cVar1 == 0) { \
                return D_80113BF0; \
            } \
            return D_80113C20; \
        } \
        if (iVar3 < 0x636) { \
            cVar1 = func_80029178(0x143) & 0xff; \
            if (cVar1 == 0) { \
                return D_80113C20; \
            } \
            return D_80113C3C; \
        } \
        return D_80113C7C; \
    }

#define DEFINE_func_80171C64() \
    extern void func_80171EC8(s32 a0); \
    extern void func_80146D90(s32 a0); \
    s32 func_80171C64(s32 param_1, s32 param_2) \
    { \
        register s32 s __asm__("$17") = param_1; \
        register s32 d __asm__("$16") = param_2; \
        u8 v; \
        ((void (*)(void))func_80171EC8)(); \
        v = *(u8 *)(s + 0x20C); \
        *(u8 *)(s + 0x20C) = v + 1; \
        if ((v & 0xFF) == (d & 0xFF)) { \
            func_80146D90(s); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80158548() \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern s32 func_80161208(); \
    void func_80158548(s32 param_1) { \
        *(u32 *)(param_1 + 0x44) = *(u32 *)(param_1 + 0x44) | 2; \
        if (*(u16 *)(param_1 + 0xb8) & 0x8000) { \
            ((void (*)(void))func_801599A4)(); \
            ((void (*)(s32))func_80159B3C)(param_1); \
        } else { \
            ((void (*)(s32))func_80161208)(param_1); \
        } \
    }

#define DEFINE_func_801687CC() \
    extern void func_80168828(void); \
    extern void func_80146C3C(void); \
    void func_801687CC(s32 param_1) \
    { \
        if (*(int *)(param_1 + 0x1c) < 3) { \
            func_80168828(); \
            *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1; \
        } else { \
            ((void (*)(int))func_80146C3C)(param_1); \
        } \
    }

#define DEFINE_func_8013E588() \
    extern s32 func_800D0EC4(void); \
    extern void func_80141874(void); \
    extern u8 D_800B9A15; \
    extern unsigned char D_800B9A13; \
    extern u16 D_80115110; \
    extern unsigned short D_80115112; \
    extern void *D_8011DB24; \
    void func_8013E588(void * _arg0) \
    { \
        if (func_800D0EC4() == 0) { \
            D_800B9A15 = 1; \
            D_800B9A13 = 2; \
            D_80115110 = 1; \
            D_80115112 = 0; \
            D_8011DB24 = func_80141874; \
        } \
    }

#define DEFINE_func_80171AB0() \
    extern s32 func_8014C568(void *a0); \
    extern s32 func_80012B04(s32 a0, s32 a1, s32 a2); \
    s16 func_80171AB0(s32 param_1, void * _arg1) \
    { \
        short sVar1; \
        sVar1 = ((short (*)(void))func_8014C568)(); \
        sVar1 = ((short (*)(int, int, int))func_80012B04)((int)*(short *)(*(int *)(param_1 + 0x20) + 0x12), (int)sVar1, 4); \
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) = \
            *(short *)(*(int *)(param_1 + 0x20) + 0x12) + sVar1 & 0xfff; \
        return (int)sVar1; \
    }

#define DEFINE_func_80172A2C() \
    extern void func_80147060(u8 *a0); \
    extern void func_80149350(s32 arg0); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_80172A8C(void *a0); \
    extern s16 D_80126B30; \
    void func_80172A2C(int param_1) \
    { \
        ((void (*)(int))func_80147060)(param_1); \
        *(short *)(param_1 + 0x136) = 2; \
        *(short *)(param_1 + 0x132) = *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12); \
        ((void (*)(int, void *, void *))func_80149350)(param_1, &D_80126B30, &D_80126B30); \
        ((void (*)(int))func_80171A1C)(param_1); \
        ((void (*)(int))func_80172A8C)(param_1); \
    }

#define DEFINE_func_8016951C() \
    extern void func_80169584(s32 param_1); \
    extern void func_800D22E4(s32 a0); \
    extern void func_80146C3C(void); \
    void func_8016951C(int param_1) \
    { \
        int iVar1; \
        iVar1 = *(int *)(param_1 + 0x1c); \
        *(int *)(param_1 + 0x1c) = iVar1 + 1; \
        if (iVar1 < 10) { \
            ((void (*)(void))func_80169584)(); \
            func_800D22E4(param_1); \
            *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 0x8000; \
        } else { \
            ((void (*)(int))func_80146C3C)(param_1); \
        } \
        return; \
    }

#define DEFINE_func_80156370() \
    extern S801563EC *func_801563EC(u16 idx); \
    extern s32 rand(void); \
    u16 func_80156370(u16 param_1) { \
        u16 *puVar3; \
        u16 uVar1; \
        u16 uVar2; \
        s32 iVar4; \
        s32 iVar5; \
        puVar3 = ((u16 * (*)(s32))func_801563EC)(param_1 & 0xFFFF); \
        uVar1 = puVar3[0] & 0xfff; \
        uVar2 = puVar3[1]; \
        iVar4 = rand(); \
        iVar5 = uVar2 + 1; \
        return (u16)(uVar1 + iVar4 % iVar5); \
    }

#define DEFINE_func_8016DB34() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern void func_80146C3C(void); \
    void func_8016DB34(s32 param_1) \
    { \
        s32 iVar2; \
        iVar2 = *(s32 *)(param_1 + 0x20); \
        if (((s32 (*)(s32, s32))func_80128ED8)(iVar2, param_1 + 0x24) != 0) { \
            ((void (*)(s32))func_80146C3C)(param_1); \
        } else { \
            *(s8 *)(iVar2 + 0x27) = *(u8 *)(param_1 + 0x28) - 0x70; \
            *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) - 0x60000; \
            *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0x14) + *(s32 *)(param_1 + 0x10); \
            *(s32 *)(param_1 + 0x8) = *(s32 *)(param_1 + 0x8) + *(s32 *)(param_1 + 0x14); \
            *(s16 *)(iVar2 + 0x18) = *(s16 *)(iVar2 + 0x18) - 0x500; \
            *(s16 *)(iVar2 + 0x1a) = *(s16 *)(iVar2 + 0x1a) - 0x300; \
        } \
    }

#define DEFINE_func_8013E2C4() \
    extern s16 D_80126CAC; \
    extern short D_80126CAE; \
    extern s16 D_80126CB0; \
    int func_8013E2C4(short *a0) { \
        int in[3]; \
        int out[3]; \
        in[0] = D_80126CAC - a0[0]; \
        in[1] = D_80126CAE - a0[1]; \
        in[2] = D_80126CB0 - a0[2]; \
        __asm__ __volatile__( \
            "lwc2 $9, 0(%0)\n" \
            "lwc2 $10, 4(%0)\n" \
            "lwc2 $11, 8(%0)\n" \
            "nop\n" \
            "nop\n" \
            "sqr 0\n" \
            : : "r"(&in[0]) : "$9", "$10", "$11", "memory"); \
        { \
            register int *pout __asm__("$2") = &out[0]; \
            __asm__ __volatile__( \
                "swc2 $25, 0(%0)\n" \
                "swc2 $26, 4(%0)\n" \
                "swc2 $27, 8(%0)\n" \
                : : "r"(pout) : "memory"); \
        } \
        return (out[0] + out[1] + out[2]) - 0x90001U < 0x18FFF; \
    }

#define DEFINE_func_8016A1CC() \
    extern u8 D_80078EBF; \
    extern void func_80147324(s32 arg0); \
    extern void func_80147364(u16, s32); \
    extern void func_80146C3C(void); \
    void func_8016A1CC(int param_1) \
    { \
        register int iVar1 __asm__("$2"); \
        if (D_80078EBF != 0) { \
            iVar1 = D_80078EBF - 0x18; \
            *(int *)(param_1 + 0x30) = iVar1; \
            if (iVar1 >= 0) { \
                iVar1 = *(int *)(param_1 + 0x1c) + 1; \
                *(int *)(param_1 + 0x1c) = iVar1; \
                if (iVar1 == 4) { \
                    func_80147324(0x44c); \
                } \
                if (D_80078EBF >= 0x80) { \
                    if (*(short *)(param_1 + 0x2a) == 0) { \
                        *(short *)(param_1 + 0x2a) = 1; \
                        *(int *)(param_1 + 0x1c) = 0x100; \
                    } \
                    if ((*(unsigned int *)(param_1 + 0x1c) & 0x1f) == 0) { \
                        func_80147324(0x44d); \
                    } \
                } \
            } \
        } else { \
            ((void (*)(int, int))func_80147364)(4, 0x44c); \
            ((void (*)(int))func_80146C3C)(param_1); \
        } \
    }

#define DEFINE_func_80158AE4() \
    extern s32 D_800AE6AC; \
    extern s32 D_800AE6B0; \
    extern s32 D_80078EC8; \
    extern void func_8016F264(void); \
    extern void func_80165840(void); \
    extern void func_801658DC(void); \
    extern s32 func_80165A20(s32 a0); \
    extern void func_80165A78(s32); \
    extern void func_8014BF48(void); \
    extern void func_8014CBF8(void *a0); \
    extern void func_8014B160(s32 a0); \
    extern void func_80149020(s32 *a0); \
    extern void func_80146CA0(void *a0); \
    void func_80158AE4(void * a0) \
    { \
        D_800AE6B0 = D_800AE6AC | 0x1000000; \
        func_8016F264(); \
        ((void (*)(s32))func_80165840)(a0); \
        ((void (*)(s32))func_801658DC)(a0); \
        func_80165A20(a0); \
        func_80165A78(a0); \
        func_8014BF48(); \
        func_8014CBF8((void *)a0); \
        func_8014B160(a0); \
        func_80149020((s32 *)a0); \
        *(s16 *)(a0 + 0x12E) = 0; \
        *(s16 *)(a0 + 0x74) = 0x1000; \
        *(s16 *)(a0 + 0x72) = 0x1000; \
        *(s16 *)(a0 + 0x70) = 0x1000; \
        *(s16 *)(a0 + 0x6C) = 0x1000; \
        *(s16 *)(a0 + 0x6A) = 0x1000; \
        *(s16 *)(a0 + 0x68) = 0x1000; \
        *(s16 *)(a0 + 0x64) = 0x1000; \
        *(s16 *)(a0 + 0x62) = 0x1000; \
        *(s16 *)(a0 + 0x60) = 0x1000; \
        *(s16 *)(a0 + 0x1BA) = 0x1000; \
        *(s16 *)(a0 + 0x1B8) = 0x1000; \
        *(s16 *)(a0 + 0xF6) = 0x1000; \
        D_80078EC8 = 0; \
        *(s16 *)(a0 + 0x1C8) = 0; \
        func_80146CA0((void *)a0); \
    }

#define DEFINE_func_80151780() \
    extern s16 D_8011DB1A; \
    extern s32 D_80127518; \
    extern s32 D_801151FC; \
    extern s32 func_801725CC(u8 *a0); \
    extern s32 func_80029D3C(void); \
    extern void func_80151878(void); \
    extern void func_80153B58(s32 *a0); \
    void func_80151780(s32 a0) { \
        u8 idx; \
        s32 *tbl; \
        s32 fp; \
        idx = *(u8 *)(a0 + 0xDD); \
        tbl = *(s32 **)(a0 + 0x1F0); \
        if (idx != 0 && idx < 0x21) { \
            fp = tbl[idx - 1]; \
            if (fp != 0) { \
                ((s32 (*)(s32))func_801725CC)(a0); \
                { \
                    register s32 cur __asm__("$4"); \
                    cur = D_8011DB1A; \
                    if (cur != 1000) { \
                        D_8011DB1A = func_80029D3C(); \
                    } \
                } \
                (*(void (**)(s32))((s32)tbl + (s32)(*(u8 *)(a0 + 0xDD)) * 4 - 4))(a0); \
                D_801151FC = D_80127518; \
            } else { \
                ((void (*)(s32))func_80151878)(a0); \
            } \
        } else { \
            (*(void (**)(s32))((s32)tbl + 8))(a0); \
        } \
        if ((*(u16 *)(a0 + 0xF0) & 0x200) != 0) { \
            ((void (*)(s32))func_80153B58)(a0); \
        } \
        return; \
    }

#define DEFINE_func_80155150() \
    extern void func_8001D150(s32, s32); \
    extern void func_8001D130(int, int); \
    extern u8 func_8014BEF8(void); \
    void func_80155150(int param_1) { \
        int iVar1; \
        unsigned int uVar2; \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19); \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18); \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16); \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15); \
        uVar2 = *(unsigned int *)(param_1 + 0x44); \
        if ((uVar2 & 0x400) != 0) { \
            return; \
        } \
        if ((uVar2 & 0x20000) == 0) { \
            if ((uVar2 & 0x20000000) != 0) { \
                func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19); \
            } else { \
                iVar1 = ((int (*)(int))func_8014BEF8)(param_1); \
                if (iVar1 != 0) { \
                    func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19); \
                    func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18); \
                    goto LAB_80155260; \
                } \
                func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x19); \
            } \
            func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x18); \
        } \
    LAB_80155260: \
        if ((*(unsigned int *)(param_1 + 0x44) & 0x10000000) != 0) { \
            func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16); \
            goto LAB_801552CC; \
        } \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x16); \
        func_8001D130(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15); \
        if ((*(unsigned int *)(param_1 + 0x44) & 4) == 0) { \
            return; \
        } \
    LAB_801552CC: \
        func_8001D150(*(int *)(*(int *)(param_1 + 0x20) + 0x24), 0x15); \
        return; \
    }

#define DEFINE_func_80165A50() \
    extern u8 D_80078EC1; \
    extern u8 D_80078EC2; \
    extern u8 D_80078EC3; \
    extern s8 D_80078EC4; \
    s32 func_80165A50(s32 _arg0) \
    { \
        D_80078EC1 = 0; \
        D_80078EC2 = 0; \
        D_80078EC3 = 0; \
        D_80078EC4 = 0; \
    }

#define DEFINE_func_8016F4C4() \
    extern void func_8016F0E4(void); \
    extern void func_80165770(void); \
    s32 func_8016F4C4(s32 param_1) \
    { \
        func_8016F0E4(); \
        ((void (*)(s32))func_80165770)(param_1); \
    }

#define DEFINE_func_80142740() \
    extern s32 func_8012BEE8(s32 a0); \
    extern s32 func_8012AD50(void *a0); \
    void func_80142740(int param_1) \
    { \
        if (((int (*)(void))func_8012BEE8)() != 0) { \
            ((void (*)(int))func_8012AD50)(param_1); \
        } \
    }

#define DEFINE_func_801746A4() \
    extern void func_80172710(void); \
    extern s32 func_80172760(s32 a0); \
    extern void func_8016EDEC(s32 a0, s32 a1, s32 a2); \
    extern void func_80174684(void *); \
    void func_801746A4(void) \
    { \
        ((void (*)(void *, int))func_8016EDEC)(func_80172710, 0x1000000); \
        func_80174684(func_80172760); \
    }

#define DEFINE_func_8016D64C() \
    extern short func_8016CBC0(void); \
    extern void func_80146C3C(void); \
    void func_8016D64C(int param_1) \
    { \
        if (func_8016CBC0() == 0) { \
            ((void (*)(int))func_80146C3C)(param_1); \
        } \
        return; \
    }

#define DEFINE_func_801726D0() \
    extern s32 func_80172760(s32 a0); \
    extern s32 func_80174650(s32); \
    extern void (*D_80127088)(void); \
    extern s32 D_801270BC; \
    extern s16 D_80126B0C; \
    void func_801726D0(void * _arg0) \
    { \
        D_80127088 = func_80172760; \
        D_801270BC = 0; \
        D_80126B0C = 0; \
        ((void (*)(void))func_80174650)(); \
    }

#define DEFINE_func_801741A8() \
    extern void func_8014BDC8(void); \
    extern void func_8014BB0C(void); \
    extern void func_8014B2A8(void); \
    extern s32 D_80078ED8; \
    extern s32 D_80078EA4; \
    void func_801741A8(s32 _arg0) \
    { \
        func_8014BDC8(); \
        func_8014BB0C(); \
        func_8014B2A8(); \
        D_80078ED8 = 0xA00000; \
        D_80078EA4 = 0xA00000; \
    }

#define DEFINE_func_8015086C() \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern void func_8014B2F8(void); \
    extern void func_80147324(s32 arg0); \
    void func_8015086C(int param_1) \
    { \
        ((void (*)(int, int, int, int))func_80146994)(0x48, param_1, 0, 0); \
        ((void (*)(int))func_8014B2F8)(param_1); \
        func_80147324(0xA1B); \
        return; \
    }

#define DEFINE_func_801730B4() \
    extern void func_8014706C(void *arg0); \
    extern void func_801542A4(); \
    extern void func_80171A1C(u8 *a0); \
    extern void func_801730FC(struct S801730FC *a0); \
    extern s32 D_80127508; \
    void func_801730B4(s32 a0) { \
        func_8014706C((void *)a0); \
        ((void (*)(s32, s32))func_801542A4)(a0, D_80127508); \
        ((void (*)(void *))func_80171A1C)((void *)a0); \
        ((void (*)(void *))func_801730FC)((void *)a0); \
    }

#define DEFINE_func_801723C4() \
    extern void func_801599A4(void *a0); \
    extern void func_80147078(s32 *a0, s16 a1); \
    extern void func_8014A1B0(s32 a0, s32 a1); \
    void func_801723C4(s32 param_1, s32 param_2) \
    { \
        ((void (*)(void))func_801599A4)(); \
        ((void (*)(int, int))func_80147078)(param_1, 0xd); \
        *(int *)(param_1 + 0x178) = param_2; \
        func_8014A1B0(param_1, param_2); \
    }

#define DEFINE_func_80157B74() \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern s32 func_80161208(); \
    void func_80157B74(int param_1) \
    { \
        if (*(unsigned short *)(param_1 + 0xB8) == 0x8000) { \
            ((void (*)(void))func_801599A4)(); \
            ((void (*)(int))func_80159B3C)(param_1); \
        } else { \
            ((void (*)(int))func_80161208)(param_1); \
        } \
    }

#define DEFINE_func_80170DE0() \
    extern void *D_8011F738; \
    extern s32 D_8011F73C; \
    extern s32 D_8011F740; \
    extern s32 func_80029178(s32 arg); \
    extern void func_801718AC(void *a0); \
    void func_80170DE0(u8 * _arg0) \
    { \
        s32 arg; \
        if (((u8 (*)(s32))func_80029178)(D_8011F738)) { \
            arg = D_8011F740; \
        } else { \
            arg = D_8011F73C; \
        } \
        ((void (*)(s32))func_801718AC)(arg); \
    }

#define DEFINE_func_80170EAC() \
    extern void *D_8011F738; \
    extern s32 D_8011F73C; \
    extern s32 D_8011F740; \
    extern int func_800D0F8C(int a0); \
    extern void func_801718AC(void *a0); \
    void func_80170EAC(u8 * _arg0) \
    { \
      s32 arg; \
      if (((int (*)(volatile char))func_800D0F8C)(D_8011F738) != 0) \
      { \
        arg = D_8011F73C; \
      } \
      else \
      { \
        arg = D_8011F740; \
      } \
      ((void (*)(s32)) func_801718AC)(arg); \
    }

#define DEFINE_func_80142BB4() \
    extern void func_801439C0(u8 *a0); \
    extern void func_8012AD44(s32 *a0, s16 a1); \
    extern void func_8012C218(void *a0); \
    extern void func_8012C098(void); \
    void func_80142BB4(s32 * param_1, s32 param_2, s32 param_3) \
    { \
      void *new_var; \
      new_var = param_1; \
      if ((*((s16 *) (new_var + 0xfc))) == 1) \
      { \
        if ((param_2 != ((char) 0)) || ((*((s16 *) (new_var + 0x100))) == 0)) \
        { \
          *((u16 *) (new_var + 0x5c)) = (*((u16 *) (new_var + 0x5c))) & 0xfefe; \
          *((u32 *) ((*((s32 *) (new_var + 0x20))) + 4)) = (*((u32 *) ((*((s32 *) (new_var + 0x20))) + 4))) | 0x80000000; \
          func_801439C0(*((u8 **) (new_var + 0xcc))); \
          func_8012AD44((s32 *) new_var, param_3); \
        } \
      } \
      else \
        if ((param_2 != 0) || ((*((s16 *) (new_var + 0x100))) == 0)) \
      { \
     do { func_8012C218(new_var = (void *) new_var); } while (0); \
      } \
      else \
      { \
        ((void (*)(void *)) func_8012C098)((void *) new_var); \
      } \
    }

#define DEFINE_func_80153E00() \
    extern u8 D_80078E78[]; \
    extern s32 D_80127518; \
    extern s16 currentLocationId; \
    extern s16 D_8011DB0C; \
    extern u16 D_8011F748; \
    extern s16 D_8011DB1A; \
    extern void func_80149020(s32 *a0); \
    extern u16 func_80148800(s32 *a0); \
    extern s32 func_8014891C(s32 a0); \
    extern s32 func_80148980(u8 *a0); \
    extern s32 func_801489E8(s32 a0); \
    extern s32 func_80148A48(s32 a0); \
    extern void func_80153C18(void); \
    extern void func_8015410C(void); \
    extern void func_80159B3C(void *a0); \
    extern void func_80165718(s32 a0); \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
    extern void func_8014B310(void); \
    extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80153E00(s32 param_1) { \
        s32 b; \
        register u32 uVar3 __asm__("$17"); \
        register u32 s2 __asm__("$18"); \
        register u8 *s3 __asm__("$19"); \
        register u32 t __asm__("$2"); \
        s32 iVar4; \
        s32 db0c; \
        func_80149020((s32 *)param_1); \
        s3 = D_80078E78; \
        b = *(u8 *)(param_1 + 0xA9); \
        if (b == 0x53) goto LAB_E74; \
        if (b < 0x54) { \
            if (b == 0x41) goto LAB_E64; \
            t = (u16)uVar3; \
            goto LAB_EC8; \
        } \
        if (b == 0x73) goto LAB_E74; \
        t = (u16)uVar3; \
        goto LAB_EC8; \
    LAB_E64: \
        uVar3 = func_80148800((s32 *)param_1) & 0xf000; \
        goto LAB_EC4; \
    LAB_E74: \
        iVar4 = func_8014891C(param_1); \
        s2 = (u32)(iVar4 != 0) << 0xc; \
        uVar3 = s2; \
        iVar4 = func_80148980((u8 *)param_1); \
        if (iVar4 != 0) { \
            uVar3 = s2 | 0x4000; \
        } \
        iVar4 = func_801489E8(param_1); \
        if (iVar4 != 0) { \
            uVar3 = uVar3 | 0x8000; \
        } \
        iVar4 = func_80148A48(param_1); \
        if (iVar4 != 0) { \
            uVar3 = uVar3 | 0x2000; \
        } \
    LAB_EC4: \
        t = (u16)uVar3; \
    LAB_EC8: \
        uVar3 = t >> 0xc; \
        if ((((u16)uVar3 != 0) && (((u16)uVar3 & *(u8 *)(param_1 + 0xdf)) == 0)) && \
            (iVar4 = *(u8 *)(param_1 + 0xde) - 1, *(u8 *)(param_1 + 0xde) = (u8)iVar4, (u8)iVar4 == 0)) { \
            ((void (*)(s32))func_80153C18)(param_1); \
        } \
        *(u8 *)(param_1 + 0xdf) = (u8)uVar3; \
        if (D_80127518 == 0) { \
            if (currentLocationId != 0x3075) { \
                *(u16 *)(param_1 + 0x88) = *(u16 *)(param_1 + 0x244); \
                *(u16 *)(param_1 + 0x8a) = *(u16 *)(param_1 + 0x246); \
                *(u16 *)(param_1 + 0x8c) = *(u16 *)(param_1 + 0x248); \
            } \
            ((void (*)(s32))func_8015410C)(param_1); \
            func_80159B3C((void *)param_1); \
            func_80165718(param_1); \
            return; \
        } \
        db0c = *(u16 *)&D_8011DB0C; \
        if (db0c == 1) goto LAB_FA8; \
        if (db0c < 2) goto LAB_AC; \
        if (db0c == 2) goto LAB_FD4; \
        if (db0c != 3) goto LAB_AC; \
        ((void (*)(s32))func_8014B310)(param_1); \
    LAB_FA8: \
        func_8014BC44(param_1, (s32)D_8011DB1A); \
        func_8014ACE8((void *)param_1, 1, (s32)D_8011DB1A); \
        goto LAB_9C; \
    LAB_FD4: \
        func_8014BC44(param_1, (s32)D_8011DB1A); \
        func_8014ACE8((void *)param_1, 1, (s32)D_8011DB1A); \
        ((void (*)(s32))func_8014B310)(param_1); \
        func_80146994(0x42, param_1, 0, 0); \
        func_80146A6C(0x42, (void *)param_1, 0x20, 0, 0, 1, 0); \
        func_80146A6C(0x42, (void *)param_1, 0, 0, 0x20, 1, 0); \
        func_80146A6C(0x42, (void *)param_1, -0x20, 0, 0, 1, 0); \
        func_80146A6C(0x42, (void *)param_1, 0, 0, -0x20, 1, 0); \
    LAB_9C: \
        D_8011DB0C = 0; \
        D_8011F748 = 0; \
    LAB_AC: \
        if (D_8011F748 != 0) { \
            ((void (*)(s32))func_8015410C)(param_1); \
            func_80159B3C((void *)param_1); \
            func_8014BC44(param_1, *(u16 *)(s3 + 0x3C)); \
            D_8011DB0C = 0; \
            D_8011F748 = 0; \
        } \
    }

#define DEFINE_func_80128DB4() \
    extern void func_80018450(s32 a0, s32 a1); \
    extern void func_800183E0(s32 a0); \
    s32 func_80128DB4(s32 a0, s32 *a1) { \
        s32 base = a1[0]; \
        s16 cnt = *(s16 *)((u8 *)a1 + 6); \
        if (cnt == 0) { \
            return 1; \
        } \
        cnt = cnt - 1; \
        *(s16 *)((u8 *)a1 + 6) = cnt; \
        if (cnt > 0) { \
            return 0; \
        } \
        { \
            s16 idx = *(s16 *)((u8 *)a1 + 4); \
            u32 flags = *(u32 *)(base + idx * 8 + 4); \
            if ((flags & 0xC0) == 0xC0) { \
                *(s16 *)((u8 *)a1 + 6) = 0; \
                return 1; \
            } \
            if ((flags & 0x80) != 0) { \
                *(s16 *)((u8 *)a1 + 4) = 0; \
            } else { \
                *(s16 *)((u8 *)a1 + 4) = idx + 1; \
            } \
            *(s16 *)((u8 *)a1 + 6) = \
                *(u32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8 + 4) & 0x3F; \
            if (a0 != 0) { \
                func_80018450(a0, *(s32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8)); \
            } else { \
                func_800183E0(*(s32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8)); \
            } \
            return 0; \
        } \
    }

#define DEFINE_func_801300F4() \
    extern s32 func_80131A34(s32, s32); \
    extern s32 func_8012BCCC(s32); \
    extern s32 func_80131AC8(void *a0); \
    extern void func_80131CA8(int a0, int a1); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    void func_801300F4(s32 a0) { \
        s32 done = 0; \
        s32 r; \
        *(u8 *)(a0 + 0xC1) = 0xD; \
        if ((*(u32 *)(a0 + 0xB4) & 0x2000) != 0) { \
            *(u16 *)(a0 + 0x5C) = 0; \
            *(s32 *)(a0 + 0x1C) = 0x1E; \
            *(u16 *)(a0 + 0x98) = 0; \
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0; \
            r = func_80131A34(a0, 0x27); \
            if (r != 0) { \
                *(u8 *)(a0 + 0xC3) = 1; \
            } else { \
                *(u8 *)(a0 + 0xC3) = 0; \
            } \
            r = func_8012BCCC(a0); \
            if (r < 0x9000) { \
                r = ((s32 (*)(s32, s32))func_80131AC8)(a0, 0x30); \
                done = 1; \
                if (r != 0) goto skip; \
                ((s32 (*)(s32, s32))func_80131AC8)(a0, 0x31); \
            } else { \
                r = ((s32 (*)(s32, s32))func_80131AC8)(a0, 0x31); \
                done = 1; \
                if (r != 0) goto skip; \
                ((s32 (*)(s32, s32))func_80131AC8)(a0, 0x30); \
            } \
            done = 1; \
        } \
    skip: \
        r = ((s32 (*)(s32, s32))func_80131CA8)(a0, 0x25); \
        if (r != 0) { \
            done = 1; \
        } \
        if (!done) { \
            ((void (*)(s32, s32))func_80131E00)(a0, 6); \
        } \
    }

#define DEFINE_func_80136D08() \
    extern s32 AddPrim(s32, void *); \
    extern s32 RotTransPers(s32, s32, s32 *, s32 *); \
    extern void SetLineG2(void *); \
    extern void *func_80010A08(s32); \
    extern void func_8004914C(void *); \
    extern void func_800491AC(void *); \
    extern s32 D_800A651C; \
    extern u8 D_800AF648; \
    extern s16 D_800B9A02; \
    void func_80136D08(s32 arg0, s32 arg1) { \
        s32 sp10; \
        s32 sp14; \
        s32 temp_v0; \
        s32 temp_v0_2; \
        void *buf; \
        func_8004914C(&D_800AF648); \
        func_800491AC(&D_800AF648); \
        buf = func_80010A08(0x14); \
        SetLineG2(buf); \
        *((u8 *)buf + 0xE) = 0xFF; \
        *((u8 *)buf + 0x4) = 0xFF; \
        *((u8 *)buf + 0xD) = 0x80; \
        *((u8 *)buf + 0x5) = 0x80; \
        *((u8 *)buf + 0xC) = 0x80; \
        *((u8 *)buf + 0x6) = 0x80; \
        temp_v0 = RotTransPers(arg0, (s32)buf + 8, &sp10, &sp14); \
        temp_v0_2 = RotTransPers(arg1, (s32)buf + 0x10, &sp10, &sp14); \
        temp_v0 = ((temp_v0 + temp_v0_2) >> 3) * 4; \
        AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + temp_v0, buf); \
    }

#define DEFINE_func_80130AF0() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80131B14(); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern int  func_80131A34(int a0, int a1); \
    extern void func_80131CA8(int a0, int a1); \
    void func_80130AF0(int param_1) { \
        *(unsigned char *)(param_1 + 0xc1) = 0x13; \
        if ((*(unsigned int *)(param_1 + 0xc4) & 2) != 0) { \
            func_80131CA8(param_1, 3); \
            return; \
        } \
        if ((*(unsigned int *)(param_1 + 0xb4) & 0x20000) != 0) { \
            ((void (*)(int, int, int, int, int, int, int))func_80146A6C)(3, param_1, (int)*(short *)(param_1 + 0x7c), \
                          (int)*(short *)(param_1 + 0x7e), \
                          (int)*(short *)(param_1 + 0x80), 0xc0cfff8, 0xf000b000); \
            if (((*(unsigned int *)(param_1 + 0xb4) & 1) != 0) || \
                ((*(unsigned int *)(param_1 + 0xc4) & 2) == 0)) { \
                ((void (*)(int))func_80131B14)(param_1); \
                if (*(short *)(param_1 + 0x76) < 1) { \
                    ((void (*)(int, int))func_80131E00)(param_1, 0xc); \
                    return; \
                } \
                if (func_80131A34(param_1, 4) != 0) { \
                    *(unsigned char *)(param_1 + 0xc2) = 0; \
                } else { \
                    *(unsigned char *)(param_1 + 0xc2) = 1; \
                    *(short *)(param_1 + 0x98) = 0; \
                    *(int *)(param_1 + 0x1c) = 0x10; \
                } \
            } \
            func_80131CA8(param_1, 3); \
        } \
        func_80131CA8(param_1, 0x37); \
    }

#define DEFINE_func_8012944C() \
    extern s32 D_8005128C; \
    extern s16 D_80114EE0; \
    extern u8 D_800B9A78; \
    extern void func_801298F4(void *arg0); \
    extern void func_801299C8(); \
    void func_8012944C(void) { \
        register s32 base __asm__("$16");   /* $s0 = &D_800B9A78 */ \
        register short *p __asm__("$17");    /* $s1 = base + 0x1E */ \
        register s32 i __asm__("$18");        /* $s2 = counter */ \
        register s32 sh __asm__("$19");       /* $s3 = 0x30000 + i*0x10000 */ \
        s32 *g = (s32 *)&D_8005128C; \
        int v; \
        s32 arg; \
        if (*g == 0x34420200) { \
            *g = 0; \
        } \
        D_80114EE0 = 1; \
        base = (s32)&D_800B9A78; \
        i = 0; \
        sh = 0x30000; \
        p = (short *)(base + 0x1E); \
        do { \
            v = (u16)p[0xb]; \
            if (v == 0x7ffe) goto F0; \
            if (v < 0x7fff) { \
                if (v == 0x7ffd) goto DC; \
                goto L504; \
            } \
            if (v != 0x7fff) goto L504; \
            goto L530; \
        DC: \
            if (i != 0) goto L530; \
            func_801299C8(1, 1, base); \
            goto L530; \
        F0: \
            arg = (i << 0x11) >> 0x10; \
            func_801299C8(1, arg, base); \
            goto L530; \
        L504: \
            func_801298F4((void *)base); \
            arg = sh >> 0x10; \
            *p = p[0x12] + p[0xe]; \
            func_801299C8(1, arg, base); \
        L530: \
            p += 0x2a; \
            sh += 0x10000; \
            i += 1; \
            base += 0x54; \
        } while (i < 2); \
    }

#define DEFINE_func_8012D4B4() \
    extern void func_8012F214(s32 a0, s32 a1, s32 a2); \
    extern s32 AddPrim(s32, void *); \
    extern s32 RotTransPers(s32, s32, s32 *, s32 *); \
    extern void SetLineF2(void *); \
    extern void *func_80010A08(s32); \
    extern void func_8004914C(void *); \
    extern void func_800491AC(void *); \
    extern s32 D_800A651C; \
    extern u8 D_800AF648; \
    extern s16 D_800B9A02; \
    void func_8012D4B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { \
        s32 sp10[2]; \
        s32 sp18[2]; \
        s32 sp20; \
        s32 sp24; \
        s32 temp_v0_2; \
        void *temp_v0; \
        func_8012F214(arg0, arg1, (s32)sp10); \
        func_8012F214(arg0, arg2, (s32)sp18); \
        temp_v0 = func_80010A08(0x10); \
        (*(s32 *)((s8 *)(temp_v0) + (4))) = arg3; \
        SetLineF2(temp_v0); \
        func_8004914C(&D_800AF648); \
        func_800491AC(&D_800AF648); \
        temp_v0_2 = RotTransPers((s32)sp10, temp_v0 + 8, &sp20, &sp24); \
        if ((temp_v0_2 > 0) && (sp24 >= 0) && \
            (RotTransPers((s32)sp18, temp_v0 + 0xC, &sp20, &sp24) > 0) && (sp24 >= 0)) { \
            AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + (temp_v0_2 * 4), temp_v0); \
        } \
    }

#define DEFINE_func_80137030() \
    extern short D_800B9A02; \
    extern u8 D_800A6518[]; \
    extern void GsSortLine(void *a0, void *a1, s32 a2); \
    void func_80137030(s16 a0, s16 a1) { \
        struct { \
            u32 tag; \
            s16 x0; \
            s16 y0; \
            s16 x1; \
            s16 y1; \
            u8 r; \
            u8 g; \
            u8 b; \
        } line; \
        s16 cx; \
        s16 cy; \
        s16 tx; \
        s16 ty; \
        tx = a0 - 3; \
        ty = a1 - 3; \
        cx = a0; \
        cy = a1; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0xFF; \
        line.b = 0; \
        line.x0 = tx; \
        line.y0 = ty; \
        line.x1 = cx; \
        line.y1 = cy; \
        GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0); \
        tx = a0 + 3; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0xFF; \
        line.b = 0; \
        line.x0 = tx; \
        line.y0 = ty; \
        line.x1 = cx; \
        line.y1 = cy; \
        GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0); \
        ty = a1 + 3; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0xFF; \
        line.b = 0; \
        line.x0 = cx; \
        line.y0 = ty; \
        line.x1 = cx; \
        line.y1 = cy; \
        GsSortLine(&line, &D_800A6518[(u16)D_800B9A02 * 20], 0); \
    }

#define DEFINE_func_80132288() \
    extern void func_8005C324(int dst, int src, int n) __asm__("memcpy"); /* Phase-24: 0x8005C324 is named memcpy for overlays (whale needs it); keep the non-builtin C name here (else built-in codegen), emit via asm-label */ \
    extern void func_801325B8(int a0, int a1, int a2, int a3, int a4); \
    void func_80132288(int *param_1, int *param_2, int param_3) { \
        int src; int dst; \
        param_1[0] = (int)param_2; \
        *(short *)((int)param_1 + 4) = 0; \
        *(short *)((int)param_1 + 6) = 0; \
        param_1[2] = param_3; \
        { \
            register char *node __asm__("$6") = (char *)*(int *)param_2[0]; \
            if (*(int *)(node + 4) == 1) src = *(int *)(node + 0xC); \
            else src = (int)(node + ((*(unsigned int *)(node + 0xC) >> 2 << 2) + 0xC)); \
        } \
        { \
            char *p3 = (char *)param_3; \
            if (*(int *)(p3 + 4) == 1) dst = *(int *)(p3 + 0xC); \
            else dst = (int)(p3 + ((*(unsigned int *)(p3 + 0xC) >> 2 << 2) + 0xC)); \
            func_8005C324(dst, src, *(int *)(p3 + 0x10) << 3); \
        } \
        { \
            register int *pn __asm__("$3") = (int *)param_2[0]; \
            if (pn[2] != 0) { \
                { \
                    register char *node __asm__("$6") = (char *)pn[0]; \
                    if (*(int *)(node + 4) == 1) src = *(int *)(node + 0x14); \
                    else src = (int)(node + ((*(unsigned int *)(node + 0x14) >> 2 << 2) + 0xC)); \
                } \
                { \
                    char *p3 = (char *)param_3; \
                    if (*(int *)(p3 + 4) == 1) dst = *(int *)(p3 + 0x14); \
                    else dst = (int)(p3 + ((*(unsigned int *)(p3 + 0x14) >> 2 << 2) + 0xC)); \
                    func_8005C324(dst, src, *(int *)(p3 + 0x18) << 3); \
                } \
            } \
        } \
        if (*(short *)((int)param_2 + 6) < 0) { \
            int *node = (int *)param_2[0]; \
            func_801325B8(param_3, node[0], node[1], node[2], 0x1000); \
        } \
    }

#define DEFINE_func_8012DBD0() \
    extern s32 func_8012DE2C(s32 a0); \
    extern s32 func_8012DDA4(void); \
    extern void func_80013350(s32 a0, void *a1); \
    s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { \
        register s32 param_1 __asm__("$18");  /* $s2 */ \
        register s32 param_2 __asm__("$20");  /* $s4 */ \
        register s32 param_3 __asm__("$21");  /* $s5 */ \
        register s32 param_4 __asm__("$19");  /* $s3 */ \
        register s32 iVar1 __asm__("$16");    /* $s0 */ \
        register s32 iVar5 __asm__("$17");    /* $s1 (running max, then its square) */ \
        s32 iVar4; \
        register s32 t __asm__("$2");          /* $v0: keep the loaded halfword in $v0 so abs copies $v0->$v1 */ \
        u32 uVar3; \
        param_1 = arg0; \
        param_2 = arg1; \
        param_3 = arg2; \
        param_4 = arg3; \
        iVar1 = func_8012DE2C(param_1); \
        if (iVar1 == 0) { \
            return 0; \
        } \
        if (*(u32 *)(param_1 + 0x58) == 0) { \
            iVar5 = 0x80; \
        } else { \
            uVar3 = *(u32 *)(param_1 + 0x58) & 0xfffffff; \
            t = (s32)*(s16 *)(uVar3 + 4); \
            iVar4 = (s32)*(s16 *)(uVar3 + 6); \
            iVar5 = t; \
            if (t < 0) { \
                iVar5 = -iVar5; \
            } \
            if (iVar4 < 0) { \
                iVar4 = -iVar4; \
            } \
            __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4)); \
            if (iVar5 < iVar4) { \
                iVar5 = iVar4; \
            } \
            t = (s32)*(s16 *)(uVar3 + 8); \
            iVar4 = t; \
            if (t < 0) { \
                iVar4 = -iVar4; \
            } \
            __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4)); \
            if (iVar5 < iVar4) { \
                iVar5 = iVar4; \
            } \
            t = (s32)*(s16 *)(uVar3 + 10); \
            iVar4 = t; \
            if (t < 0) { \
                iVar4 = -iVar4; \
            } \
            __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4)); \
            if (iVar5 < iVar4) { \
                iVar5 = iVar4; \
            } \
            t = (s32)*(s16 *)(uVar3 + 0xc); \
            iVar4 = t; \
            if (t < 0) { \
                iVar4 = -iVar4; \
            } \
            __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4)); \
            if (iVar5 < iVar4) { \
                iVar5 = iVar4; \
            } \
            t = (s32)*(s16 *)(uVar3 + 0xe); \
            iVar4 = t; \
            if (t < 0) { \
                iVar4 = -iVar4; \
            } \
            __asm__ __volatile__("" : "=r"(iVar4) : "0"(iVar4)); \
            if (iVar5 < iVar4) { \
                iVar5 = iVar4; \
            } \
        } \
        iVar5 = iVar5 * iVar5; \
    LAB_8012dcf8: \
        do { \
            u16 uVar6 = *(u16 *)(iVar1 + 0x5c); \
            if ((uVar6 & 0x8000) != 0) { \
                if ((uVar6 & 0x4000) == 0) { \
                    if (*(u16 *)(iVar1 + 0x5e) != param_4) { \
                        if ((*(u16 *)(iVar1 + 0xae) & 1) == 0) { \
                            if (((s32(*)(s32, s32))func_80013350)(param_1 + 4, iVar1 + 4) < iVar5) { \
                                *(u16 *)(iVar1 + 0x60) = param_2; \
                                *(u16 *)(iVar1 + 0x62) = param_3; \
                                *(u16 *)(iVar1 + 0x5e) = param_4; \
                                *(u16 *)(iVar1 + 0x5c) = *(u16 *)(iVar1 + 0x5c) | 1; \
                            } \
                        } \
                    } \
                } \
            } \
            iVar1 = func_8012DDA4(); \
        } while (iVar1 != 0); \
        return 0; \
    }

#define DEFINE_func_8013339C() \
    void func_8013339C(short *param_1, short *param_2) \
    { \
        short sVar4; \
        short sVar5; \
        short sVar6; \
        sVar4 = 1; \
        if (*param_2 != 0) { \
            sVar4 = *param_2; \
        } \
        sVar5 = 1; \
        if (param_2[1] != 0) { \
            sVar5 = param_2[1]; \
        } \
        sVar6 = 1; \
        if (param_2[2] != 0) { \
            sVar6 = param_2[2]; \
        } \
        param_1[0] = (short)(((int)param_1[0] << 0xc) / (int)sVar4); \
        param_1[3] = (short)(((int)param_1[3] << 0xc) / (int)sVar4); \
        param_1[6] = (short)(((int)param_1[6] << 0xc) / (int)sVar4); \
        param_1[1] = (short)(((int)param_1[1] << 0xc) / (int)sVar5); \
        param_1[4] = (short)(((int)param_1[4] << 0xc) / (int)sVar5); \
        param_1[7] = (short)(((int)param_1[7] << 0xc) / (int)sVar5); \
        param_1[2] = (short)(((int)param_1[2] << 0xc) / (int)sVar6); \
        param_1[5] = (short)(((int)param_1[5] << 0xc) / (int)sVar6); \
        param_1[8] = (short)(((int)param_1[8] << 0xc) / (int)sVar6); \
    }

#define DEFINE_func_80130514() \
    extern void func_8012CBF4(s32 a0); \
    extern void func_801319E0(int); \
    extern int func_80131D68(int, int); \
    extern int func_8012BEE8(int); \
    extern void func_80131CA8(int, int); \
    void func_80130514(int param_1) \
    { \
        unsigned int uVar1; \
        if ((*(unsigned int *)(param_1 + 0xb4) & 0x40) != 0) { \
            uVar1 = ((int (*)(void))func_8012CBF4)(); \
            if (0xf < *(short *)(param_1 + 10)) { \
                func_801319E0(param_1); \
                return; \
            } \
            if (func_80131D68(param_1, uVar1) == 1) { \
                return; \
            } \
            if (func_8012BEE8(param_1) != 0) { \
                if ((uVar1 & 0x2000) != 0) { \
                    *(unsigned char *)(param_1 + 0xc1) = 0; \
                    *(unsigned short *)(param_1 + 0x5e) = 0; \
                    func_80131CA8(param_1, 0xe); \
                } \
            } \
        } \
        /* Scheduling barrier: blocks gcc-2.7.2 reorg from hoisting the join-block \
           `move $a0,$s0` into the first branch's delay slot (target keeps a nop there). */ \
        __asm__ __volatile__(""); \
        func_80131CA8(param_1, 0x13); \
    }

#define DEFINE_func_8013A2BC() \
    extern s32 D_80127524; \
    extern s32 D_80127528; \
    extern void func_80138C30(void *a0); \
    void func_8013A2BC(s32 a0) { \
        s32 s0 = a0; \
        s32 *v1; \
        s32 *p; \
        s32 v0; \
        v1 = *(s32 **)(s0 + 0x40); \
        if (v1 == 0 || *(u16 *)(s0 + 0x18) == 0 || *(s16 *)v1 == 4) { \
            p = &D_80127524; \
            if (*p == s0) { \
                v0 = D_80127528; \
                D_80127528 = 0; \
                *p = v0; \
                if (v0 != 0) { \
                    *(s16 *)(D_80127524 + 0x1A) = 1; \
                    __asm__ __volatile__("" : : : "memory"); \
                    ((void (*)(s32))func_80138C30)(*p); \
                } \
            } \
            if ((*(s32 *)(s0 + 8) & 0x8000) == 0) { \
                *(s16 *)(s0 + 4) = 0xD; \
            } else { \
                *(s16 *)(s0 + 4) = 0xE; \
            } \
        } \
    }

#define DEFINE_func_80130438() \
    extern void func_80131B14(); \
    extern void func_80143CD4(s32 a0); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    extern void func_800CB0E8(s32 a0); \
    extern s32 func_80131A34(s32 a0, s32 a1); \
    extern void func_80131CA8(int a0, int a1); \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern s32 *D_80126B78; \
    void func_80130438(s32 a0) { \
        s32 flag; \
        flag = 0; \
        *(u8 *)(a0 + 0xC1) = 6; \
        if ((*(u32 *)(a0 + 0xB4) & 0x40) != 0) { \
            flag = 1; \
            func_80131B14(); \
            *(s32 *)(a0 + 0x1C) = 0x78; \
            func_80143CD4(a0); \
            func_8002D4C8(0x47B, 0); \
            func_8002D4C8(0x478, 0); \
            func_800CB0E8(a0); \
            if (func_80131A34(a0, 0x14) == 0) { \
                *(s16 *)(a0 + 0x98) = 0; \
            } \
        } \
        if (((s32 (*)(s32, s32))func_80131CA8)(a0, 0x12) != 0) { \
            flag = 1; \
        } \
        if (flag == 0) { \
            *(s16 *)(a0 + 0x5E) = 2; \
            *(s16 *)(a0 + 0x60) = 1; \
            *(s16 *)(a0 + 0x62) = *(u16 *)((s32)D_80126B78 + 0x12); \
            ((void (*)(s32, s32))func_80131E00)(a0, 1); \
        } \
    }

#define DEFINE_func_8012C2D0() \
    extern u8 D_80120194[]; \
    extern u8 D_801202A0[]; \
    s32 func_8012C2D0(void) \
    { \
        s32 p; \
        s32 it; \
        it = (s32)D_80120194; \
        __asm__ __volatile__("" : "=r"(it) : "0"(it)); \
        p = it + 0x658C; \
        goto test; \
    copy: \
        return it; \
    test: \
        it = (s32)D_801202A0; \
        __asm__ __volatile__("" : "=r"(it) : "0"(it)); \
        if (it == p) goto zero; \
    body: \
        if (*(u16 *)it == 0) goto copy; \
        it += 0x10C; \
        if (it != p) goto body; \
    zero: \
        return 0; \
    }

#define DEFINE_func_8012B0B4() \
    extern int func_80047948(int a0); \
    extern int func_8004787C(int a0); \
    void func_8012B0B4(unsigned int *param_1, int param_2, int param_3) \
    { \
        int iVar1, iVar2; \
        register int prod __asm__("$7");          /* mflo dest = $a3 (both products) */ \
        register unsigned int *p __asm__("$2");    /* store addr copied into $v0 */ \
        register int sh1 __asm__("$2");            /* shares $v0 with p (non-overlapping) */ \
        register int sh2 __asm__("$3");            /* 2nd-product shift -> $v1 */ \
        unsigned int uVar3, result; \
        uVar3 = (param_2 - 0x400U) & 0xfff; \
        iVar1 = func_80047948(uVar3); \
        result &= 0xFFFF0000; \
        prod = iVar1 * param_3; \
        sh1 = prod >> 0xc; \
        result |= sh1 & 0xFFFF; \
        iVar2 = func_8004787C(uVar3); \
        prod = iVar2 * -param_3; \
        result &= 0xFFFF; \
        /* Force the param_1->$v0 copy AND let the scheduler hoist it into the \
           mult->mflo delay slot (a plain `p = param_1` gets coalesced away). */ \
        __asm__ ("addu %0,%1,$zero" : "=r"(p) : "r"(param_1)); \
        sh2 = prod >> 0xc; \
        result |= sh2 << 0x10; \
        *p = result; \
    }

#define DEFINE_func_8012E28C() \
    extern s32 AddPrim(s32, void *); \
    extern void *func_80010A08(s32); \
    extern s32 GetTPage(s32, s32, s32, s32); \
    extern s32 func_8005A600(s32, s32, s32, s32, s32); \
    extern s32 D_800A651C; \
    extern s16 D_800B9A02; \
    void func_8012E28C(s32 arg0, s32 arg1) { \
        void *temp_v0; \
        s32 temp_v1; \
        s32 base; \
        if (arg0 > 0) { \
            base = *(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + (arg0 * 4); \
            temp_v0 = func_80010A08(0xC); \
            temp_v1 = GetTPage(0, arg1, 0, 0); \
            func_8005A600((s32)temp_v0, 0, 0, (u16)temp_v1, 0); \
            AddPrim(base, temp_v0); \
        } \
    }

#define DEFINE_func_8012E688() \
    extern u8 D_800AF648; \
    extern void func_8004914C(void *a0); \
    extern void func_800491AC(void *a0); \
    extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_8012E688(s32 param_1, u16 param_2, u16 param_3) \
    { \
        struct { short v[3]; short pad; short xy[2]; int sp1c; int flag; } f; \
        register void *p __asm__("$4"); \
        register u16 a __asm__("$16") = param_2; \
        register u16 b __asm__("$17") = param_3; \
        if (*(s32 *)(param_1 + 0x20) != 0) { \
            f.v[0] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48); \
            f.v[1] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C); \
            f.v[2] = (short)*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50); \
            p = &D_800AF648; \
            func_8004914C(p); \
            func_800491AC(&D_800AF648); \
            RotTransPers((s32)f.v, (s32)f.xy, &f.sp1c, &f.flag); \
            if (f.flag < 0) { \
                return; \
            } \
            if ((u16)(f.xy[0] + 199) >= 399) { \
                return; \
            } \
            if ((u16)(f.xy[1] + 0xA9) >= 0x153) { \
                return; \
            } \
        } \
        func_8002D4C8(a, b); \
    }

#define DEFINE_func_8012BFA8() \
    extern s16 D_80126CAC; \
    extern short D_80126CAE; \
    extern s16 D_80126CB0; \
    int func_8012BFA8(short *a0) { \
        int in[3]; \
        int out[3]; \
        in[0] = D_80126CAC - a0[3]; \
        in[1] = D_80126CAE - a0[5]; \
        in[2] = D_80126CB0 - a0[7]; \
        __asm__ __volatile__( \
            "lwc2 $9, 0(%0)\n" \
            "lwc2 $10, 4(%0)\n" \
            "lwc2 $11, 8(%0)\n" \
            "nop\n" \
            "nop\n" \
            "sqr 0\n" \
            : : "r"(&in[0]) : "$9", "$10", "$11", "memory"); \
        { \
            register int *pout __asm__("$2") = &out[0]; \
            __asm__ __volatile__( \
                "swc2 $25, 0(%0)\n" \
                "swc2 $26, 4(%0)\n" \
                "swc2 $27, 8(%0)\n" \
                : : "r"(pout) : "memory"); \
        } \
        return 0xfffff < out[0] + out[1] + out[2]; \
    }

#define DEFINE_func_80130974() \
    extern int func_8012BEE8(int); \
    extern void func_80166244(); \
    extern void func_801319E0(int); \
    extern void func_80131CA8(int, int); \
    void func_80130974(int param_1) { \
        short sVar1; \
        if ((*(unsigned int *)(param_1 + 0xb4) & 0x8000) != 0) { \
            sVar1 = *(short *)(*(int *)(param_1 + 0x20) + 0x18); \
            if (sVar1 < 0x1000) { \
                *(short *)(*(int *)(param_1 + 0x20) + 0x18) = sVar1 + 0x400; \
                *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = \
                    *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1c) + 0x400; \
            } \
            if (func_8012BEE8(param_1) != 0) { \
                ((void (*)(int))func_80166244)(param_1); \
                func_801319E0(param_1); \
                return; \
            } \
        } \
        func_80131CA8(param_1, 0x2b); \
    }

#define DEFINE_func_8012F968() \
    extern s32 D_801151D4; \
    extern s32 func_8012B744(void *a0, void *a1); \
    extern s32 func_80131A34(s32 a0, s32 a1); \
    extern s32 func_8012C588(s32 a0, s32 a1); \
    extern void func_80131CA8(s32 a0, s32 a1); \
    void func_8012F968(s32 param_1) { \
        s32 iVar3; \
        s32 iVar2; \
        u32 uVar4; \
        struct { s16 a; s16 b; s16 c; } sp; \
        iVar3 = D_801151D4; \
        *(u8 *)(param_1 + 0xc1) = 0x12; \
        if ((*(u32 *)(param_1 + 0xb4) & 0x10000) != 0) { \
            sp.a = *(s32 *)(iVar3 + 0x5c); \
            sp.b = *(s32 *)(iVar3 + 0x60); \
            sp.c = *(s32 *)(iVar3 + 0x64); \
            iVar2 = *(s32 *)(param_1 + 0x20); \
            *(s16 *)(param_1 + 0x5c) = 0; \
            *(s16 *)(param_1 + 0x54) = 0; \
            *(s16 *)(param_1 + 0x52) = 0; \
            *(s16 *)(param_1 + 0x50) = 0; \
            *(s16 *)(iVar2 + 0x14) = 0; \
            *(s16 *)(iVar2 + 0x10) = 0; \
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = ((s16 (*)(s32, s32))func_8012B744)(param_1 + 4, (s32)&sp); \
            *(s32 *)(param_1 + 0x1c) = 0x2d; \
            if (*(u32 *)(param_1 + 0x58) != 0) { \
                uVar4 = *(u32 *)(param_1 + 0x58) & 0xfffffff | 0x80000000; \
                *(s16 *)(param_1 + 0xac) = \
                    (s16)((s32)*(s16 *)(uVar4 + 8) + (s32)*(s16 *)(uVar4 + 10) >> 1); \
            } else { \
                *(s16 *)(param_1 + 0xac) = 0; \
            } \
            *(s32 *)(param_1 + 0x10) = \
                ((*(s32 *)(iVar3 + 0x5c) - (s32)*(s16 *)(param_1 + 6)) * 0x10000) / 0x1e; \
            *(s32 *)(param_1 + 0x14) = \
                (((*(s32 *)(iVar3 + 0x60) - (s32)*(s16 *)(param_1 + 10)) - \
                  (s32)*(s16 *)(param_1 + 0xac)) * 0x10000) / 0x1e; \
            *(s32 *)(param_1 + 0x18) = \
                ((*(s32 *)(iVar3 + 0x64) - (s32)*(s16 *)(param_1 + 0xe)) * 0x10000) / 0x1e; \
            *(s16 *)(param_1 + 0x98) = 0; \
            if (func_80131A34(param_1, 0x24) == 0) { \
                *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) & 0xfffffffb; \
                if (func_80131A34(param_1, 0x20) != 0) { \
                    *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) | 4; \
                } else { \
                    *(s16 *)(param_1 + 0x98) = 0; \
                } \
            } \
            ((void (*)(s32, s32))func_8012C588)(0x289, param_1); \
        } \
        func_80131CA8(param_1, 0x35); \
    }

#define DEFINE_func_8012D714() \
    extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2); \
    s32 func_8012D714(s32 param_1, u32 param_2) { \
        u16 a[3]; \
        u16 b[3]; \
        u32 base; \
        base = (*(u32 *)(param_1 + 0x58) & 0xFFFFFFF) | 0x80000000; \
        if (param_2 & 1) { \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 8); \
            b[2] = *(u16 *)(base + 0xC); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 0xA); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xC); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xE); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 8); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 0xA); \
            a[2] = *(u16 *)(base + 0xE); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
        } \
        if (param_2 & 2) { \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 4); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xC); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xE); \
            b[0] = *(u16 *)(base + 4); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 6); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xC); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 6); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xE); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
        } \
        if (param_2 & 4) { \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 4); \
            b[1] = *(u16 *)(base + 8); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 4); \
            a[1] = *(u16 *)(base + 0xA); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 4); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 6); \
            a[1] = *(u16 *)(base + 8); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 8); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
            a[0] = *(u16 *)(base + 6); \
            a[1] = *(u16 *)(base + 0xA); \
            a[2] = *(u16 *)(base + 0xC); \
            b[0] = *(u16 *)(base + 6); \
            b[1] = *(u16 *)(base + 0xA); \
            b[2] = *(u16 *)(base + 0xE); \
            if (((s32 (*)(s32, void *, void *))func_8012DEB8)(param_1, a, b) != 0) { \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8012F568() \
    extern void *memcpy(void *, const void *, u32); \
    extern u8 D_80126C38; \
    extern u8 D_80126C40; \
    extern u16 D_80126B94; \
    extern u16 D_80126B96; \
    extern s16 D_80126B98; \
    extern s16 D_80126B9A; \
    void func_8012F568(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6) \
    { \
        memcpy(&D_80126C38, param_5, 8); \
        memcpy(&D_80126C40, param_6, 8); \
        __asm__ __volatile__("" ::: "memory"); \
        D_80126B96 = param_2; \
        D_80126B9A = param_3; \
        D_80126B98 = param_4; \
        D_80126B94 = D_80126B94 | param_1; \
    }

#define DEFINE_func_8015126C() \
    void func_8015126C(u16 *p) \
    { \
        extern s32 D_80127078; \
        extern s32 D_80126AE4; \
        extern s32 D_801151FC; \
        extern s32 D_80127518; \
        extern s32 D_800AE6A8;       /* +0x8 == D_800AE6B0 (s32) */ \
        extern u8  D_80078E78[];     /* +0x49 == D_80078EC1 (u8) */ \
        extern s32 func_801470A0(void *a0); \
        extern s32 func_8014A454(s32 a0); \
        extern void func_80160368(s32 *a0); \
        extern s32 func_801619D0(void *a0); \
        extern s32 func_80151880(s32 a0); \
        extern void func_800CCF68(void *); \
        extern s32 func_80161A00(s32 a0); \
        extern s32 func_801518D8(s32 a0); \
        extern void func_800CCF58(void *); \
        extern s32 func_80161A30(s32 a0); \
        extern s32 func_80161A60(s32 a0); \
        extern void func_801599A4(void *); \
        extern void func_801607B8(s32 *a0); \
        extern void func_80147084(s32 *a0); \
        extern s32  func_80029D3C(void); \
        extern s32 func_8014CB7C(void); \
        extern void func_80153C9C(void); \
        extern void func_8015173C(s32 *a0); \
        extern s32 func_801725CC(u8 *a0); \
        extern void func_8014B310(void); \
        extern void func_8014B4D4(void *a0); \
        extern void func_8014B944(s32 a0, s32 a1, s32 a2); \
        extern void func_80146D80(s32 *a0); \
        extern void func_801477E8(s32 *a0, s32 a1); \
        extern void func_80147324(s32 arg0); \
        extern void func_8014BD24(s32 a0, s32 a1); \
        extern void func_8014ACE8(void *a0, s32 a1, s32 a2); \
        register u8  *r __asm__("$18") = D_80078E78;     /* $s2 */ \
        register s32 *q __asm__("$17") = &D_800AE6A8;   /* $s1 */ \
        register s32 sh16 __asm__("$2");                 /* $v0 */ \
        u16 uVar3; \
        s32 angle; \
        s32 v; \
        D_80126AE4 = D_80127078; \
        D_80127078 = 0; \
        D_801151FC = 0; \
        if (*(u8 *)(p + 0x54) != 0) { \
            if (((p[0x1e] & 1) == 0) || ((p[0x1f] & 0x8000) == 0)) { \
                p[0x1e] &= 0xfffe; \
                p[0x1f] = 0; \
                p[0x20] = 0; \
                p[0x21] = 0; \
            } \
            { \
                u8 bVar2 = *(u8 *)(p + 0x54) - 1; \
                *(u8 *)(p + 0x54) = bVar2; \
                if ((bVar2 & 1) != 0) { \
                    ((void (*)(void *))func_801470A0)(p); \
                } \
            } \
        } \
        uVar3 = p[0x1e]; \
        if ((uVar3 & 1) == 0) { \
            goto L638; \
        } \
        if (((*(u32 *)(p + 0x1e) & 0x80008000) == 0) || ((q[2] & 0x80ffffff) != 0)) { \
            p[0x1e] = uVar3 & 0xfffe; \
            p[0x1f] = 0; \
            p[0x20] = 0; \
            p[0x21] = 0; \
            goto L638; \
        } \
        { \
            u16 uVar1 = p[0x1f]; \
            p[0x1e] = uVar3 & 0xfffe; \
            p[0x1f] = uVar1 & 0x7fff; \
            if (((uVar1 & 0x4000) == 0) && ((*(u32 *)(p + 0x22) & 1) != 0) && \
                (((s32 (*)(void *))func_8014A454)(p) != 0)) { \
                ((void (*)(void *))func_80160368)(p); \
                p[0x1f] = 0; \
                p[0x20] = 0; \
                p[0x21] = 0; \
                p[0x1e] &= 0xfffe; \
                return; \
            } \
        } \
        if ((func_801619D0(p) != 0) && (((s32 (*)(void *))func_80151880)(p) != 0)) { \
            p[0x20] = 0; \
            p[0x79] = 0; \
            func_800CCF68(p); \
        } \
        if ((((s32 (*)(void *))func_80161A00)(p) != 0) && (((s32 (*)(void *))func_801518D8)(p) != 0)) { \
            func_800CCF58(p); \
        } \
        if (((s32 (*)(void *))func_80161A30)(p) != 0) { \
            p[0xe4] = 0; \
        } \
        if (((s32 (*)(void *))func_80161A60)(p) != 0) { \
            p[0xe4] = 0; \
        } \
        if (((u32)(p[0] - 0x19) < 2) || \
            ((*(u32 *)(p + 0xfc) != 0) && ((*(u32 *)(p + 0xfc) & 0x2000000) == 0))) { \
            goto L620; \
        } \
        p[0x78] = p[0x1f]; \
        p[0x79] = p[0x20]; \
        p[0x7a] = p[0x21]; \
        func_801599A4(p); \
        ((void (*)(void *))func_801607B8)(p); \
        ((void (*)(void *))func_80147084)(p); \
        { \
            u16 t = p[0x1f]; \
            register s32 cmp79 __asm__("$4"); \
            *(u8 *)(p + 0x54) = 0; \
            ((s8 *)p)[0xdd] = (s8)t; \
            if (((t & 0xff) != 0x11) && ((cmp79 = *(s16 *)(p + 0x79)) != 1000)) { \
                angle = func_80029D3C(); \
                p[0x79] = angle; \
                if (r[0x49] == 5) { \
                    sh16 = angle << 16; \
                } else { \
                    if (func_8014CB7C() == 0) { \
                        goto LAB_8015152c; \
                    } \
                    sh16 = p[0x79] << 16; \
                } \
                p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1); \
            } \
        } \
    LAB_8015152c: \
        func_80153C9C(); \
        func_8015173C(p); \
        ((void (*)(void *))func_801725CC)(p); \
        if ((p[0x1f] & 0x2000) != 0) { \
            ((void (*)(void *))func_8014B310)(p); \
        } \
        if ((p[0x1f] & 0x1000) != 0) { \
            func_8014B4D4(p); \
        } \
        if ((p[0x1f] & 0x800) != 0) { \
            ((void (*)(void *, s32, s32))func_8014B944)(p, 0x50000, 1); \
        } \
        if ((p[0x1f] & 0x400) != 0) { \
            ((void (*)(void *))func_80146D80)(p); \
            ((void (*)(void *, s32))func_801477E8)(p, 0); \
        } \
        if (((s32 (*)(void *))func_80151880)(p) == 2) { \
            func_80147324(0x676); \
        } \
        if (r[0x49] == 0x14) { \
            ((void (*)(void *, s32))func_8014BD24)(p, 10); \
            func_8014ACE8(p, 4, 10); \
        } \
        D_80127518 = D_80126AE4; \
        v = D_80126AE4; \
        goto L640; \
    L620: \
        p[0x1f] = 0; \
        p[0x20] = 0; \
        p[0x21] = 0; \
        p[0x1e] &= 0xfffe; \
    L638: \
        v = D_80127518; \
    L640: \
        D_801151FC = v; \
    }

#define DEFINE_func_80156B74() \
    void func_80156B74(s32 param_1, u32 param_2, u8 *param_3) { \
        extern S8 D_80126AF0[]; \
        extern S8 D_801270A8; \
        extern void func_801484B0(s32 a0, s32 a1); \
        extern void func_801484E8(s32 a0, s32 a1); \
        extern void func_80148534(s32 a0, s32 a1); \
        extern void func_8014856C(s32 a0, s32 a1); \
        extern void func_800139C8(s32 a0, void *a1, void *a2); \
        extern void func_80156ECC(s32 a0, void *a1, void *a2, void *a3, void *a4); \
        u16 local_28[3]; \
        B8 auStack_20; \
        s32 v1 = *(s32 *)(param_1 + 0x20); \
        D_801270A8.a = 0; \
        D_801270A8.b = -0x1E; \
        D_801270A8.c = 0; \
        if (param_2 == 0) { \
            if (*(s32 *)(v1 + 0x20) != 0) { \
                ((void (*)(void *, void *))func_801484B0)(local_28, &auStack_20); \
                D_80126AF0[0].a = local_28[0]; \
                D_80126AF0[0].b = local_28[1]; \
                D_80126AF0[0].c = local_28[2]; \
                ((void (*)(void *, void *))func_801484E8)(local_28, &auStack_20); \
                D_80126AF0[1].a = local_28[0]; \
                D_80126AF0[1].b = local_28[1]; \
                D_80126AF0[1].c = local_28[2]; \
                goto L_call; \
            } \
            goto L_zero; \
        } \
        if (param_2 != 1) goto L_not1; \
        if (*(s32 *)(v1 + 0x20) != 0) { \
            ((void (*)(void *, void *))func_80148534)(local_28, &auStack_20); \
            D_80126AF0[0].a = local_28[0]; \
            D_80126AF0[0].b = local_28[1]; \
            D_80126AF0[0].c = local_28[2]; \
            ((void (*)(void *, void *))func_8014856C)(local_28, &auStack_20); \
            D_80126AF0[1].a = local_28[1]; \
            D_80126AF0[1].b = local_28[1]; \
            D_80126AF0[1].c = local_28[2]; \
            goto L_call; \
        } \
    L_zero: \
        D_80126AF0[0].a = 0; \
        D_80126AF0[0].b = 0; \
        D_80126AF0[0].c = 0; \
        D_80126AF0[1].a = 0; \
        D_80126AF0[1].b = 0; \
        D_80126AF0[1].c = 0; \
        goto L_call; \
    L_not1: \
        if (param_2 == 2) { \
            D_80126AF0[0].a = 0; \
            D_80126AF0[0].b = -0x1E; \
            D_80126AF0[0].c = -0x52; \
            func_800139C8((s32)(s16)(*(u16 *)(param_1 + 0x24A) - *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12)), \
                          &D_80126AF0[0], &D_80126AF0[0]); \
            D_80126AF0[1].a = 0; \
            D_80126AF0[1].b = -0x1E; \
            D_80126AF0[1].c = -0x52; \
            goto L_call; \
        } \
        { \
            u32 uVar1 = param_2 & 0x80FFFFFF; \
            D_80126AF0[0].a = (s8)*(u8 *)(*param_3 * 3 + uVar1); \
            D_80126AF0[0].b = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 1); \
            D_80126AF0[0].c = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 2); \
            D_80126AF0[1].a = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 3); \
            D_80126AF0[1].b = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 4); \
            D_80126AF0[1].c = (s8)*(u8 *)(*param_3 * 3 + uVar1 + 5); \
        } \
    L_call: \
        if ((param_2 & 0xF000000) == 0) { \
            *param_3 = *param_3 + 1; \
        } \
        func_80156ECC(param_1, &D_801270A8, &D_80126AF0[0], &D_80126AF0[1], &D_80126AF0[2]); \
    }

#define DEFINE_func_80163C2C() \
    void func_80163C2C(s32 param_1) { \
        extern void func_80164530(s32 arg0); \
        extern void func_80013F3C(s32 a0); \
        extern void func_800126C4(s32 a0, s32 a1); \
        extern void func_800123F0(s32 a0, s32 a1); \
        extern void func_80012558(s32 a0, s32 a1); \
        extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4); \
        extern void func_80162FC0(s32 *a0); \
        extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3); \
        extern void func_80146E90(s32 *a0, s32 a1); \
        extern void func_80147364(u16, s32); \
        extern void func_80146CA0(void *a0); \
        extern u16 func_80156370(u16 param_1); \
        extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5); \
        extern s32 func_801632F0(void); \
        extern s32 func_801632E0(void); \
        extern void func_80015978(s32 a0, s32 *a1); \
        extern void func_80015954(s32 a0, s32 a1); \
        extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6); \
        extern void func_80163764(s32 a0); \
        extern void (*D_8011DB10)(s32); \
        u8 dead[0x20]; \
        Buf32 buf; \
        u8 dead2[8]; \
        s32 iVar3; \
        s32 iVar4; \
        s32 obj; \
        u16 tmp; \
        s32 flags; \
        iVar4 = *(s32 *)(param_1 + 0x4c); \
        iVar3 = *(s32 *)(param_1 + 0x20); \
        ((void (*)(void))func_80164530)(); \
        *(u16 *)(iVar3 + 0x14) = (*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + 0x71) & 0xfff; \
        ((void (*)(void *))func_80013F3C)(&buf); \
        ((void (*)(void *, s32))func_800126C4)(&buf, *(s16 *)(param_1 + 0x60)); \
        ((void (*)(void *, s32))func_800123F0)(&buf, *(s16 *)(param_1 + 0x64)); \
        ((void (*)(void *, s32))func_80012558)(&buf, *(s16 *)(param_1 + 0x62)); \
        ((void (*)(void *, s32))func_80012558)(&buf, *(s16 *)(iVar3 + 0x12)); \
        ((void (*)(void *, s32))func_800126C4)(&buf, *(s16 *)(iVar3 + 0x10)); \
        ((void (*)(void *, s32))func_800123F0)(&buf, *(s16 *)(iVar3 + 0x14)); \
        ((void (*)(s32, s32, s32, s32, void *))func_80163194)(param_1, 0, 0, 0x18000, &buf); \
        ((void (*)(s32))func_80162FC0)(param_1); \
        *(Blk16 *)(iVar3 + 0x34) = buf.lo; \
        *(Blk16 *)(iVar3 + 0x44) = buf.hi; \
        if (*(s32 *)(param_1 + 0x2c) >= 0) { \
            ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000); \
            ((void (*)(s32, s32))func_80146E90)(param_1, 0x20); \
            ((void (*)(s32, s32))func_80147364)(4, 0x448); \
            ((void (*)(s32))func_80146CA0)(param_1); \
            ((void (*)(s32))func_80146CA0)(param_1); \
            return; \
        } \
        func_801634D8(param_1, 0xd, (u16)((s32 (*)(s32))func_80156370)(0xd), 1, 0); \
        flags = ((s32 (*)(s32))func_801632F0)(param_1); \
        if ((flags & 1) != 0) { \
            obj = ((s32 (*)(s32))func_801632E0)(param_1); \
            *(s32 *)(iVar4 + 0x184) = obj; \
            *(u32 *)(iVar4 + 0x44) = *(u32 *)(iVar4 + 0x44) | 0x20; \
            tmp = *(u16 *)(obj + 0x36); \
            *(u16 *)(iVar4 + 0x18a) = 0; \
            *(u16 *)(iVar4 + 0x188) = 0; \
            *(u16 *)(iVar4 + 0x194) = tmp; \
            ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000); \
            if (D_8011DB10 == 0) { \
                ((void (*)(s32, s32))func_80015978)(param_1 + 4, param_1 + 0x58); \
            } else { \
                (*D_8011DB10)(param_1 + 0x58); \
                func_80015954(param_1 + 0x58, param_1 + 4); \
            } \
            *(u16 *)(param_1 + 0x66) = 0; \
            ((void (*)(s32, s32))func_80147364)(4, 0x448); \
            ((void (*)(s32, s32, s32, s32, s32, s32, s32))func_80146AB4)(0x30, param_1, 0, 0, 0, 0, *(s32 *)(iVar4 + 0x184)); \
        } else { \
            if ((flags & 6) == 0) goto ret; \
            ((void (*)(s32, s32, s32, s32))func_80146DE8)(param_1, 0, 0, 0xc0000); \
            ((void (*)(s32, s32))func_80146E90)(param_1, 0x20); \
            ((void (*)(s32, s32))func_80147364)(4, 0x448); \
            ((void (*)(s32))func_80146CA0)(param_1); \
        } \
        ((void (*)(s32))func_80146CA0)(param_1); \
    ret: \
        func_80163764(param_1); \
    }

#define DEFINE_func_8012A62C() \
    void func_8012A62C(s32 a0) { \
        extern s32 D_801151D4; \
        extern struct BigCopy D_80126DB8; \
        extern u8 D_80127504; \
        D_80126DB8 = *(struct BigCopy *)D_801151D4; \
        D_80127504 = a0; \
    }

#define DEFINE_func_801661CC() \
    void func_801661CC(s32 param_1) \
    { \
        extern s32 func_80128ED8(void *a0, void *a1); \
        extern void func_80146C3C(void); \
        extern void func_800D22E4(s32 a0); \
        if (((s32 (*)(s32, s32))func_80128ED8)(*(s32 *)(param_1 + 0x20), param_1 + 0x24) != 0) { \
            ((void (*)(s32))func_80146C3C)(param_1); \
        } else { \
            func_800D22E4(param_1); \
            *(s32 *)(param_1 + 0x10) = (*(s32 *)(param_1 + 0x10) >> 1) + (*(s32 *)(param_1 + 0x10) >> 2); \
            *(s32 *)(param_1 + 0x18) = (*(s32 *)(param_1 + 0x18) >> 1) + (*(s32 *)(param_1 + 0x18) >> 2); \
        } \
    }

#define DEFINE_func_8015ADB0() \
    void func_8015ADB0(s32 arg0) { \
        extern s32 D_8011F730; \
        extern void func_80161124(void *a0); \
        extern void func_801477E8(s32 *a0, s32 a1); \
        extern void func_8014C010(s32 a0, s32 a1); \
        extern void func_80146CA0(void *a0); \
        if (*(u8 *)(arg0 + 0xA8) >= 0x19) { \
            *(u8 *)(arg0 + 0xA8) = 0x18; \
        } \
        func_80161124(arg0); \
        ((void (*)(s32, s32))func_801477E8)(arg0, 0xFFEE0000); \
        func_8014C010(arg0, 2); \
        D_8011F730 |= 1; \
        ((void (*)(s32))func_80146CA0)(arg0); \
    }

#define DEFINE_func_80156ECC() \
    void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5) { \
        extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3); \
        extern void func_80147478(s32 a0); \
        extern void func_80149350(s32 arg0); \
        unsigned short uVar1; \
        func_80156FA8(param_3, param_4, param_5); \
        ((s32 (*)(s32))func_80147478)(param_1); \
        ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_2, param_2); \
        uVar1 = *(unsigned short *)(param_3 + 6); \
        if (*(short *)(param_3 + 6) == 0) { \
            ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_3, param_3); \
            *(unsigned short *)(param_3 + 6) = uVar1; \
        } \
        uVar1 = *(unsigned short *)(param_4 + 6); \
        if (*(short *)(param_4 + 6) == 0) { \
            ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_4, param_4); \
            *(unsigned short *)(param_4 + 6) = uVar1; \
        } \
        uVar1 = *(unsigned short *)(param_5 + 6); \
        if (*(short *)(param_5 + 6) == 0) { \
            ((s32 (*)(s32, s32, s32))func_80149350)(param_1, param_5, param_5); \
            *(unsigned short *)(param_5 + 6) = uVar1; \
        } \
    }

#define DEFINE_func_8012CFA8() \
    void func_8012CFA8(s32 arg0) \
    { \
        extern s32 AddPrim(s32, void *); \
        extern s32 RotTransPers(s32, s32 *, s32 *, s32 *); \
        extern void SetPolyF3(void *); \
        extern void *func_80010A08(s32); \
        extern void func_8004914C(void *a0); \
        extern void func_800491AC(void *a0); \
        extern s32 D_800A651C; \
        extern u8 D_800AF648; \
        extern short D_800B9A02; \
        s32 sp10; \
        s32 sp14; \
        s32 sp18; \
        s32 temp_a2; \
        void *temp_v0; \
        temp_v0 = func_80010A08(0x14); \
        (*(s32 *)((s8 *)(temp_v0) + (4))) = 0xFF; \
        SetPolyF3(temp_v0); \
        func_8004914C(&D_800AF648); \
        func_800491AC(&D_800AF648); \
        temp_a2 = (RotTransPers(arg0, &sp10, &sp14, &sp18) >> 2) - 0x20; \
        if (temp_a2 > 0) { \
            *(s32 *)((s8 *)temp_v0 + 8) = sp10; \
            *(s16 *)((s8 *)temp_v0 + 0xC) = *(u16 *)((s8 *)temp_v0 + 8) + 8; \
            *(s16 *)((s8 *)temp_v0 + 0xE) = *(u16 *)((s8 *)temp_v0 + 0xA); \
            *(s16 *)((s8 *)temp_v0 + 0x10) = *(u16 *)((s8 *)temp_v0 + 8); \
            *(s16 *)((s8 *)temp_v0 + 0x12) = *(u16 *)((s8 *)temp_v0 + 0xA) + 8; \
            AddPrim(*(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + (temp_a2 * 4), temp_v0); \
        } \
    }

#define DEFINE_func_80147E44() \
    void func_80147E44(s32 a0, s32 a1, s32 a2, s32 a3) { \
        extern void func_80147928(int a0, int a1); \
        extern void func_8014799C(int a0, int a1); \
        extern void func_80147A10(int a0, int a1); \
        extern void func_80013F3C(s32 a0); \
        extern void RotMatrixX(s32 a0, void *a1); \
        extern void RotMatrixY(s32 a0, void *a1); \
        extern void RotMatrixZ(s32 a0, void *a1); \
        extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
        extern s32 D_80127090; \
        extern s32 D_80127094; \
        extern s32 D_80127098; \
        register s32 r_a0 __asm__("$17");  /* $s1 = param_1 */ \
        register s32 r_a2 __asm__("$16");  /* $s0 = param_3 */ \
        register s32 r_a3 __asm__("$19");  /* $s3 = param_4 */ \
        register s32 v   __asm__("$18");   /* $s2 = *(a0+0x20) */ \
        s32 out[3]; \
        s32 m[8]; \
        s32 *p0 = &D_80127090; \
        s32 *p1 = &D_80127094; \
        s32 *p2 = &D_80127098; \
        r_a0 = a0; \
        r_a2 = a2; \
        r_a3 = a3; \
        v = *(s32 *)(r_a0 + 0x20); \
        func_80147928(r_a0, a1); \
        func_8014799C(r_a0, r_a2); \
        func_80147A10(r_a0, r_a3); \
        func_80013F3C((s32)m); \
        RotMatrixY(*(s16 *)(v + 0x12), (void *)m); \
        RotMatrixX(*(s16 *)(v + 0x10), (void *)m); \
        RotMatrixZ(*(s16 *)(v + 0x14), (void *)m); \
        func_800484EC((s32)m, r_a0 + 0x24, (s32)out); \
        D_80127090 = out[0]; \
        D_80127094 = out[1]; \
        D_80127098 = out[2]; \
        *(s32 *)(r_a0 + 0x10) = *p0; \
        *(s32 *)(r_a0 + 0x14) = *p1; \
        *(s32 *)(r_a0 + 0x18) = *p2; \
        D_80127090 = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
    }

#define DEFINE_func_80166054() \
    void func_80166054(s32 arg0) { \
        extern void func_80149374(s32 a0, s32 a1); \
        extern s32 func_8004787C(s32 a0); \
        extern s32 func_80047948(s32 a0); \
        extern void func_800D1FC8(s32 a0, s32 a1); \
        extern s32 func_800D21C4(s32 a0, void *a1, s32 a2); \
        extern void func_80128EA8(s32 a0, s32 a1, s32 a2); \
        extern void func_801661CC(s32 a0); \
        extern void func_80146C3C(void); \
        extern u8 D_800D387C[]; \
        extern u8 D_800D3888[]; \
        register s32 param_1 __asm__("$18"); /* $s2 */ \
        register s32 s0 __asm__("$16");      /* $s0 */ \
        register s32 s1 __asm__("$17");      /* $s1 */ \
        register s32 r0 __asm__("$19");      /* $s3 */ \
        register s32 r1 __asm__("$20");      /* $s4 */ \
        s32 v1; \
        s32 iVar2; \
        s32 iVar3; \
        register u32 fld __asm__("$2"); /* $v0 */ \
        s32 v0; \
        register s32 r2 __asm__("$5");  /* $a1 */ \
        register s32 a0 __asm__("$4");  /* $a0 */ \
        param_1 = arg0; \
        s0 = *(s32 *)(param_1 + 0x34); \
        func_80149374(s0, param_1 + 4); \
        v1 = *(s32 *)(param_1 + 0x2c); \
        if (v1 != 0) { \
            s1 = 8; \
            if (v1 != 3) { \
                s0 = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) << 16; \
            } else { \
                fld = *(s32 *)(param_1 + 0x30); \
                s0 = fld & 0xfff; \
                s1 = (fld >> 12) & 0xf; \
                s0 = s0 << 16; \
            } \
            s0 = s0 >> 16; \
            iVar2 = func_8004787C(s0); \
            r0 = iVar2 << s1; \
            r1 = -r0; \
            iVar3 = func_80047948(s0); \
            r2 = iVar3 << s1; \
            a0 = -r2; \
            if (*(s32 *)(param_1 + 0x2c) == 2) { \
                r1 = r0; \
                a0 = r2; \
            } \
            *(s32 *)(param_1 + 0x10) = r1; \
            *(s32 *)(param_1 + 0x18) = a0; \
        } \
        *(s32 *)(param_1 + 0x14) = 0xffff0000; \
        func_800D1FC8(param_1, 6); \
        v0 = func_800D21C4(param_1, D_800D387C, 0x9c); \
        if (v0 != 0) { \
            register s32 uVar1 __asm__("$2"); \
            *(s32 *)(param_1 + 0x20) = v0; \
            *(u32 *)(v0 + 4) = *(u32 *)(v0 + 4) | 0x50000040; \
            if (*(s32 *)(param_1 + 0x2c) != 3) { \
                uVar1 = 0x2000; \
            } else { \
                uVar1 = *(u16 *)(param_1 + 0x32); \
            } \
            *(u16 *)(v0 + 0x18) = uVar1; \
            __asm__("" ::: "memory"); \
            *(u16 *)(v0 + 0x1a) = *(u16 *)(v0 + 0x18); \
            func_80128EA8(v0, param_1 + 0x24, (s32)D_800D3888); \
            func_801661CC(param_1); \
            *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1; \
        } else { \
            ((void (*)(s32))func_80146C3C)(param_1); \
        } \
    }

#define DEFINE_func_8017CE24() \
    extern s32 func_800167F0(s32 arg0); \
    s32 func_8017CE24(void) { \
        return (func_800167F0(0) & 0xFFFF) != 0; \
    }

#define DEFINE_func_801705C0() \
    extern void *D_8011F738; \
    extern void func_80171928(void *a0); \
    void func_801705C0(u8 * a0) \
    { \
        ((void (*)(void))D_8011F738)(); \
        ((void (*)(s32))func_80171928)(a0); \
    }

#define DEFINE_func_8017C048() \
    void func_8017C048(void) { \
    }

#define DEFINE_func_8017C120() \
    void func_8017C120(void) { \
    }

#define DEFINE_func_8017C238() \
    void func_8017C238(void) { \
    }

#define DEFINE_func_8017C338() \
    void func_8017C338(void) { \
    }

#define DEFINE_func_8017D5CC() \
    s32 func_8017D5CC(void) { \
            return 0x1; \
        }

#define DEFINE_func_801805A0() \
    void func_801805A0(void) { \
    }

#define DEFINE_func_80180800() \
    void func_80180800(void) { \
    }

#define DEFINE_func_80180A30() \
    void func_80180A30(void) { \
    }

#define DEFINE_func_80180B04() \
    void func_80180B04(void *a0) { \
            *(short *)(*(int *)((char *)a0 + 0xcc) + 0xfc) = 1; \
        }

#define DEFINE_func_80180B14() \
    void func_80180B14(void *a0) { \
            *(short *)(*(int *)((char *)a0 + 0xcc) + 0xfc) = 0x2; \
        }

#define DEFINE_func_8017DA84() \
    s32 func_8017DA84(s32 arg0) { \
            if (arg0 < 5) { \
                return 0x57; \
            } \
            return 0x3D; \
        }

#define DEFINE_func_801807E8() \
    void func_801807E8(void *a0) { \
            *(s16 *)((s32)a0 + 0x10A) = 0x60; \
            *(s16 *)((s32)a0 + 0x106) = 0; \
            *(s16 *)((s32)a0 + 0x108) = 0; \
            *(s16 *)((s32)a0 + 0xFE) = 0; \
        }

#define DEFINE_func_8017D464() \
    s32 func_8017D464(u8 *a0) { \
            *(s32 *)(a0 + 0x28) = 0xA; \
            *(u8 *)(a0 + 0x15) += 1; \
            return 0; \
        }

#define DEFINE_func_8017E0EC() \
    extern u16 D_80115112; \
    void func_8017E0EC(void) { \
        register s32 *p __asm__("$3"); /* pinned to $v1 */ \
        register s32 v __asm__("$2"); /* pinned to $v0 */ \
        p = &D_80115112; \
        v = *(u16 *)p + 1; \
        *(u16 *)p = v; \
    }

#define DEFINE_func_8017D7E0() \
    extern void func_8017D808(s32 arg0, s32 arg1); \
    extern s32 D_801274E8; \
    void func_8017D7E0(s32 arg0) { \
        func_8017D808(arg0, &D_801274E8); \
    }

#define DEFINE_func_8017CDFC() \
    extern s32 func_800167F0(s32 arg0); \
    s32 func_8017CDFC(void) { \
        return (func_800167F0(0) & 0xFFFF) != 0; \
    }

#define DEFINE_func_80181DE0() \
    void func_80181DE0(void) { \
    }

#define DEFINE_func_8018258C() \
    void func_8018258C(void) { \
    }

#define DEFINE_func_80183010() \
    void func_80183010(void) { \
    }

#define DEFINE_func_80183A78() \
    void func_80183A78(s32 *a0) { \
            *(s8 *)((s32)a0 + 0x20C) = 0; \
        }

#define DEFINE_func_80183C94() \
    void func_80183C94(void *a0) { \
            *(s8 *)((s32)a0 + 0x20C) = 0; \
        }

#define DEFINE_func_8018535C() \
    void func_8018535C(void) { \
    }

#define DEFINE_func_801854C4() \
    void func_801854C4(void) { \
    }

#define DEFINE_func_80188DF0() \
    void func_80188DF0(void) { \
    }

#define DEFINE_func_80189950() \
    void func_80189950(void) { \
    }

#define DEFINE_func_80184164() \
    void func_80184164(void *a0) { \
            *(short *)(*(int *)((char *)a0 + 0x20) + 0x12) = 0xC00; \
        }

#define DEFINE_func_8018A650() \
    void func_8018A650(s32 *a0, s32 a1, s32 a2, s32 a3) { \
            *(s8 *)((s32)a0 + 0x4) = a1; \
            *(s8 *)((s32)a0 + 0x5) = a2; \
            *(s8 *)((s32)a0 + 0x6) = a3; \
        }

#define DEFINE_func_8017FC9C() \
    void func_8017FC9C(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 4; \
            *(short *)((char *)a0 + 0x98) = 0; \
            *(int *)((char *)a0 + 0x1c) = 0; \
        }

#define DEFINE_func_80184B00() \
    void func_80184B00(void *a0) { \
            *(s16 *)((s32)a0 + 0x2) += 1; \
        }

#define DEFINE_func_80185364() \
    void func_80185364(void *a0) { \
            *(s16 *)((s32)a0 + 0xA) = -0x1B26; \
            *(s16 *)((s32)a0 + 0x6) = 0; \
            *(s16 *)((s32)a0 + 0xE) = 0x1C59; \
        }

#define DEFINE_func_80180394() \
    void func_80180394(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x7; \
            *(short *)((char *)a0 + 0x98) = 0; \
            *(int *)((char *)a0 + 0x1c) = 0x1e; \
            *(short *)((char *)a0 + 0x5c) = 0; \
        }

#define DEFINE_func_801803B0() \
    extern void func_801803D0(void); \
    void func_801803B0(void) { \
        func_801803D0(); \
    }

#define DEFINE_func_80181914() \
    extern u8 D_8012694C; \
    void func_80181914(void) { \
        D_8012694C++; \
    }

#define DEFINE_func_8018621C() \
    extern void func_8013BD34(void); \
    void func_8018621C(void) { \
        func_8013BD34(); \
    }

#define DEFINE_func_80182338() \
    extern s32 func_800167F0(s32 arg0); \
    s32 func_80182338(void) { \
        return (func_800167F0(4) & 0xFFFF) != 0; \
    }

#define DEFINE_func_801823F0() \
    extern s32 func_800167F0(s32 arg0); \
    s32 func_801823F0(void) { \
        return (func_800167F0(0) & 0xFFFF) != 0; \
    }

#define DEFINE_func_801824A8() \
    extern s32 func_800167F0(s32 arg0); \
    s32 func_801824A8(void) { \
        return (func_800167F0(0) & 0xFFFF) != 0; \
    }

#define DEFINE_func_80184174() \
    extern s32 D_801B5C90; \
    void func_80184174(void *arg0) { \
        *(u16 *)((s32)arg0 + 0xdc) = 0x5a; \
        *(u16 *)((s32)arg0 + 0xde) = 0x3c; \
        *(u16 *)((s32)arg0 + 0xe0) = 1; \
        *(u16 *)((s32)arg0 + 0x2) = *(u16 *)((s32)arg0 + 0x2) + 1; \
    }

#define DEFINE_func_80188F08() \
    extern void func_8018A3FC(s32 *a0); \
    extern u8 D_801E8830[]; \
    void func_80188F08(void) { \
        func_8018A3FC(D_801E8830); \
    }

#define DEFINE_func_80181CE0() \
    extern s32 D_8012695C; \
    extern s16 D_80126968; \
    extern s16 D_80126978; \
    void func_80181CE0(void) { \
        D_8012695C = 0x50; \
        D_80126968 = 0x71; \
        D_80126978 = -0x80; \
    }

#define DEFINE_func_8018623C() \
    extern s32 D_801E8010; \
    extern void func_8002D4C8(s32 arg0, s32 arg1); \
    void func_8018623C(u16 arg0, u16 arg1) { \
        if (D_801E8010 == 0) { \
            func_8002D4C8(arg0 & 0xFFFF, arg1 & 0xFFFF); \
        } \
    }

#define DEFINE_func_80180210() \
    void func_80180210(void) { \
    }

#define DEFINE_func_80183808() \
    void func_80183808(void) { \
    }

#define DEFINE_func_80170B48() \
    void func_80170B48(int a0) \
    { \
        extern void *D_8011F738; \
        extern void func_8014706C(void *a0); \
        extern void func_80154274(s32 *a0, s32 a1); \
        extern s32 func_80171990(u8 *a0); \
        func_8014706C(a0); \
        func_80154274((s32 *)a0, (s32)D_8011F738); \
        func_80171990((u8 *)a0); \
        func_80170B90((u8 *)a0); \
    }

#define DEFINE_func_8015F948() \
    void func_8015F948(s32 *param_1) { \
        extern void func_80146C98(s32 *a0, s16 a1); \
        extern void func_80147078(s32 *a0, s16 a1); \
        extern void func_80154150(s32 a0, s32 a1); \
        extern void func_80154A74(s32 a0, s32 a1); \
        extern s32 func_80161104(void); \
        func_80147078(param_1, 0x15); \
        if (((s32 (*)(s32 *))func_80161104)(param_1) != 0) { \
            func_80154150((s32)param_1, 0x22); \
            func_80154A74((s32)param_1, 0x1A); \
            func_80146C98(param_1, 2); \
        } \
    }

#define DEFINE_func_80155E30() \
    void func_80155E30(void *a0) { \
        extern int func_80155FF8(int arg, int a1); \
        extern void func_801599A4(void *a0); \
        extern void func_80159B3C(void *a0); \
        extern s32 func_80161208(void); \
        volatile s32 spill[4]; \
        *(s32 *)((u8 *)a0 + 0x44) = *(s32 *)((u8 *)a0 + 0x44) | 2; \
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) { \
            func_801599A4(a0); \
            func_80159B3C(a0); \
            return; \
        } \
        if (((s32 (*)(s32 *))func_80161208)(a0) != 0) { \
            return; \
        } \
        func_80155FF8((int)a0, *(u8 *)((u8 *)a0 + 0x1AA)); \
    }

#define DEFINE_func_801576A8() \
    extern int func_80155FF8(int arg, int a1); \
    void func_801576A8(void *arg0) { \
        extern int func_80155FF8(int arg, int a1); \
        extern void func_801599A4(void *a0); \
        extern void func_80159B3C(void *a0); \
        extern s32 func_80161208(void); \
        volatile s32 spill[4];  /* forces the 0x28 frame the target reserves */ \
        *(s32 *)((u8 *)arg0 + 0x44) |= 2; \
        if (*(u16 *)((u8 *)arg0 + 0xB8) == 0x8000) { \
            func_801599A4(arg0); \
            func_80159B3C(arg0); \
        } else if (((s32 (*)(void *))func_80161208)(arg0) == 0) { \
            func_80155FF8((int)arg0, *(u8 *)((u8 *)arg0 + 0x1AA)); \
        } \
    }

#define DEFINE_func_80168F40() \
    void func_80168F40(void *arg0) { \
        extern Blk20 D_800AE620; \
        extern s32 func_80016A5C(); \
        struct A a; \
        struct B b; \
        a.unk00 = *(u16 *)((u8 *)arg0 + 0x10); \
        a.unk02 = *(u16 *)((u8 *)arg0 + 0x14); \
        a.unk04 = *(u16 *)((u8 *)arg0 + 0x18); \
        a.unk08 = *(u16 *)((u8 *)arg0 + 0x6); \
        a.unk0A = *(u16 *)((u8 *)arg0 + 0xA); \
        a.unk0C = *(u16 *)((u8 *)arg0 + 0xE); \
        a.unk10 = 8; \
        a.unk14 = 0xC0; \
        a.unk12 = 0; \
        a.unk11 = 0; \
        a.unk16 = 0x80; \
        a.unk15 = 0x80; \
        *(struct Bv *)&b = *(struct Bv *)&D_800AE620; \
        a.unk18 = 0x50000000; \
        func_80016A5C(&a, &b); \
    }

#define DEFINE_func_80163A94() \
    void func_80163A94(s32 param_1) { \
        extern s32 D_800636C8; \
        extern s32 D_800DE5A0; \
        extern void func_8001C214(s32 a0, s32 a1); \
        extern void func_8014659C(void); \
        extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
        extern void func_80146CA0(void *a0); \
        extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3); \
        extern void func_80146E90(s32 *a0, s32 a1); \
        extern void func_80147324(s32 a0); \
        extern void func_80149374(int, int); \
        s32 iVar7; \
        s32 iVar1; \
        s32 iVar2; \
        s32 iVar3; \
        iVar7 = *(s32 *)(param_1 + 0x4c); \
        *(u32 *)(iVar7 + 0x44) = *(u32 *)(iVar7 + 0x44) | 4; \
        iVar1 = ((s32 (*)(void))func_8014659C)(); \
        *(s32 *)(param_1 + 0x20) = iVar1; \
        if (iVar1 != 0) { \
            func_8001C214(iVar1, (s32)&D_800DE5A0); \
            *(s32 *)(iVar1 + 0x20) = (s32)&D_800636C8; \
            *(s16 *)(iVar1 + 0x1c) = 0x1800; \
            *(s16 *)(iVar1 + 0x1a) = 0x1800; \
            *(s16 *)(iVar1 + 0x18) = 0x1800; \
            *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0x10; \
            func_80149374(iVar7, param_1 + 4); \
            iVar3 = *(s32 *)(param_1 + 0x20); \
            iVar2 = *(s32 *)(iVar7 + 0x20); \
            *(Blk16 *)(iVar3 + 0x34) = *(Blk16 *)(iVar2 + 0x34); \
            *(Blk16 *)(iVar3 + 0x44) = *(Blk16 *)(iVar2 + 0x44); \
            *(s16 *)(iVar1 + 0x10) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x10); \
            *(s16 *)(iVar1 + 0x12) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x12); \
            *(s16 *)(iVar1 + 0x14) = *(s16 *)(*(s32 *)(iVar7 + 0x20) + 0x14); \
            *(s16 *)(param_1 + 0x60) = *(s16 *)(iVar7 + 0x100); \
            *(s16 *)(param_1 + 0x62) = *(s16 *)(iVar7 + 0x102); \
            *(s16 *)(param_1 + 0x64) = *(s16 *)(iVar7 + 0x104); \
            func_80147324(0x448); \
            func_80146E90((s32 *)param_1, 0x10); \
            func_80146A6C(0xd, (void *)param_1, 0, 0, 0, 0, 0); \
            func_80146DE8((s32 *)param_1, 0, 0, 0xffe00000); \
            func_80146CA0((void *)param_1); \
        } \
        return; \
    }

#define DEFINE_func_80156848() \
    extern s32 D_801151E0[]; \
    extern B8 D_80128120[]; \
    extern B8 D_80128138[]; \
    extern S8 D_80126AF0[]; \
    extern u8 D_80126730[]; \
    void func_80156848(s32 param_1, s32 param_2) { \
        extern s32 D_801151E0[]; \
        extern u8 D_80126730[]; \
        extern S8 D_80126AF0[]; \
        extern B8 D_80128120[]; \
        extern B8 D_80128138[]; \
        extern void func_80013E94(void *a0, void *a1); \
        extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8); \
        extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
        extern void func_80156A1C(s32 a0, s32 a1); \
        u32 uVar1; \
        s32 i; \
        u32 uVar3; \
        u32 local_20[2]; \
        uVar3 = 0; \
        i = 0; \
        do { \
            uVar1 = D_801151E0[uVar3]; \
            if (uVar1 & 1) { \
                func_80013E94(&D_80128120[i], local_20); \
                ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(*(u8 *)(param_2 + 8), param_1, (s32)D_80126AF0[i].a, \
                              (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], \
                              *(u8 *)(param_2 + 9)); \
            } else if (uVar1 & 6) { \
                func_80156A1C(param_1, uVar3); \
                func_80013E94(&D_80128138[i], local_20); \
                if ((D_801151E0[uVar3] & 6) == 4) { \
                    local_20[0] = local_20[0] | 0x80000000; \
                } \
                ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(6, param_1, (s32)D_80126AF0[i].a, \
                              (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0); \
                if (D_80126730[uVar3] == 0x24) { \
                    ((void (*)(s32, s32, s32, s32, s32, s32, s32, s32))func_801469C8)(0x53, param_1, (s32)D_80126AF0[i].a, \
                                  (s32)D_80126AF0[i].b, (s32)D_80126AF0[i].c, local_20[0], 0, 0x14); \
                } \
            } \
            uVar3 = uVar3 + 1; \
            i = i + 1; \
        } while (uVar3 < 3); \
    }

#define DEFINE_func_8012FDA8() \
    void func_8012FDA8(int param_1) \
    { \
        extern void func_8012CBF4(s32 a0); \
        extern void func_80131CA8(int a0, int a1); \
        extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
        int iVar1; \
        unsigned int uVar2; \
        if ((*(unsigned int *)(param_1 + 0xb4) & 0x100) != 0) { \
            iVar1 = *(int *)(param_1 + 0x1c) + 1; \
            *(int *)(param_1 + 0x1c) = iVar1; \
            if (0x14 < iVar1) { \
                ((void (*)(int, int))func_80131E00)(param_1, 0xd); \
                return; \
            } \
            uVar2 = ((int (*)(int))func_8012CBF4)(param_1); \
            if ((uVar2 & 0x2000) != 0) { \
                if ((uVar2 & 0xff) == 2) { \
                    ((void (*)(int, int))func_80131E00)(param_1, 0x12); \
                    return; \
                } \
                if ((uVar2 & 0xff) == 0x1a) { \
                    func_801319E0(param_1); \
                    return; \
                } \
                func_80131C78(param_1); \
            } \
        } \
        func_80131CA8(param_1, 0x1d); \
        return; \
    }

#define DEFINE_func_8012BA10() \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012BA10(s32 arg0, s32 arg1) { \
        extern u16 D_80126B5E; \
        extern u16 D_80126B66; \
        register s32 d __asm__("$16");      /* $s0 -- pinned: divisor, live across the jal */ \
        register s32 s1ang __asm__("$17");  /* $s1 -- pinned: ptr+0x12 angle, live across the jal */ \
        s32 u5; s32 u6; s32 iVar4; s32 q; s32 t; \
        d = arg1; \
        s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12); \
        u5 = (ratan2(*(s16 *)(arg0 + 0xE) - (s16)D_80126B66, (s16)D_80126B5E - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF; \
        __asm__ __volatile__("" : : "r"(u5));   /* scheduling barrier: anchor u5 before the (s16)d cast */ \
        d = (s16)d; \
        u6 = s1ang & 0xFFF; \
        if (u6 == u5) return 0; \
        iVar4 = u5 - u6; \
        if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; } \
        if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; } \
        if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; } \
        else { q = iVar4 / d; if (q == 0) q = -1; } \
        return q; \
    }

#define DEFINE_func_80181D2C() \
    extern void (*D_8018EA0C[])(void); \
    void func_80181D2C(u8 *param_1) \
    { \
        D_8018EA0C[param_1[0x4]](); \
    }

#define DEFINE_func_80182D00() \
    extern void (*D_8018ED5C[])(void); \
    void func_80182D00(void *a0) { \
        D_8018ED5C[*(u8 *)((s32)a0 + 0x214)](); \
    }

#define DEFINE_func_801868D4() \
    extern void (*D_8018F31C[])(void); \
    void func_801868D4(void *a0) { \
        D_8018F31C[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_801863E8() \
    extern void (*D_8018F2FC[])(void); \
    void func_801863E8(void *a0) { \
        D_8018F2FC[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8017BF98() \
    void func_8017BF98(void) { \
    }

#define DEFINE_func_8017C07C() \
    void func_8017C07C(void) { \
    }

#define DEFINE_func_8017C14C() \
    void func_8017C14C(void) { \
    }

#define DEFINE_func_8017DD74() \
    void func_8017DD74(void) { \
    }

#define DEFINE_func_8017DF7C() \
    void func_8017DF7C(void) { \
    }

#define DEFINE_func_80180714() \
    void func_80180714(void) { \
    }

#define DEFINE_func_80188470() \
    void func_80188470(void) { \
    }

#define DEFINE_func_801892D4() \
    void func_801892D4(void) { \
    }

#define DEFINE_func_801892DC() \
    void func_801892DC(void) { \
    }

#define DEFINE_func_80189C74() \
    void func_80189C74(void) { \
    }

#define DEFINE_func_80189104() \
    void func_80189104(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x3; \
        }

#define DEFINE_func_801890F8() \
    void func_801890F8(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x2; \
        }

#define DEFINE_func_8018918C() \
    void func_8018918C(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x5; \
            *(int *)((char *)a0 + 0x1c) = 0; \
        }

#define DEFINE_func_80188F18() \
    void func_80188F18(void *a0) { \
            *(s32 *)((s32)a0 + 0x48) = 0x1400; \
            *(s32 *)((s32)a0 + 0x14) = 0; \
        }

#define DEFINE_func_8017F49C() \
    void func_8017F49C(void) { \
    }

#define DEFINE_func_80182ADC() \
    void func_80182ADC(void) { \
    }

#define DEFINE_func_80182AE4() \
    void func_80182AE4(void) { \
    }

#define DEFINE_func_80183AF8() \
    void func_80183AF8(void) { \
    }

#define DEFINE_func_80183C50() \
    void func_80183C50(void) { \
    }

#define DEFINE_func_80187D04() \
    void func_80187D04(void) { \
    }

#define DEFINE_func_80189274() \
    void func_80189274(void) { \
    }

#define DEFINE_func_80182910() \
    void func_80182910(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x3; \
        }

#define DEFINE_func_80182904() \
    void func_80182904(void *a0) { \
            *(short *)((char *)a0 + 0x2) = 0x2; \
        }

#define DEFINE_func_8017F224() \
    void func_8017F224(void) { \
    }

#define DEFINE_func_8018235C() \
    extern void (*D_8018EAD8[])(void); \
    void func_8018235C(void *a0) { \
        D_8018EAD8[*(u8 *)((s32)a0 + 0x15)](); \
    }

#define DEFINE_func_801831A8() \
    extern s32 D_8018ED88; \
    extern void func_8013C9C4(s32); \
    void func_801831A8(void * arg0) { \
        if ((*(s32 *)((char *)arg0 + 0x204) & 0xF) == 0) { \
            func_8013C9C4((s32)&D_8018ED88); \
        } \
    }

#define DEFINE_func_801856B4() \
    void func_801856B4(void *a0) { \
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0x800; \
        }

#define DEFINE_func_80182988() \
    void func_80182988(s32 *a0) { \
            *(s16 *)((s32)a0 + 0x2) = 0x5; \
            *(s32 *)((s32)a0 + 0x1c) = 0; \
        }

#define DEFINE_func_8017D6A8() \
    void func_8017D6A8(void) { \
    }

#define DEFINE_func_8018015C() \
    void func_8018015C(void) { \
    }

#define DEFINE_func_80184B68() \
    void func_80184B68(void) { \
    }

#define DEFINE_func_80184CB0() \
    void func_80184CB0(void *a0) { \
            *(s16 *)((s32)a0 + 0x5C) = 0; \
        }

#define DEFINE_func_801851F0() \
    void func_801851F0(void) { \
    }

#define DEFINE_func_801851F8() \
    void func_801851F8(void) { \
    }

#define DEFINE_func_80185200() \
    void func_80185200(void) { \
    }

#define DEFINE_func_80185208() \
    void func_80185208(void) { \
    }

#define DEFINE_func_80185210() \
    void func_80185210(void) { \
    }

#define DEFINE_func_8018525C() \
    void func_8018525C(void) { \
    }

#define DEFINE_func_8018A988() \
    void func_8018A988(void) { \
    }

#define DEFINE_func_8018C69C() \
    void func_8018C69C(void) { \
    }

#define DEFINE_func_8018CDDC() \
    void func_8018CDDC(void) { \
    }

#define DEFINE_func_8018CDE4() \
    void func_8018CDE4(void) { \
    }

#define DEFINE_func_8018AFE8() \
    s32 func_8018AFE8(void) { \
            return -1; \
        }

#define DEFINE_func_80187E28() \
    void func_80187E28(void *a0) { \
            *(s16 *)((s32)a0 + 0x2) += 1; \
        }

#define DEFINE_func_80182704() \
    void func_80182704(void *a0) { \
            *(s32 *)((s32)a0 + 0x48) = 0x1400; \
            *(s32 *)((s32)a0 + 0x14) = 0; \
        }

#define DEFINE_func_8017F190() \
    extern s32 D_8018FB28; \
    extern s32 func_8012AD50(void *a0); \
    void func_8017F190(void) { \
        D_8018FB28 = 0; \
        ((void (*)(void))func_8012AD50)(); \
    }

#define DEFINE_func_8017E264() \
    void func_8017E264(void *a0) { \
            *(s8 *)((s32)a0 + 0xA0) = 0; \
        }

#define DEFINE_func_8018B868() \
    void func_8018B868(void *a0) { \
            M2C_FIELD(a0, s16 *, 0x2) = 2; \
        }

#define DEFINE_func_8017C090() \
    void func_8017C090(void *a0) { \
            *(s16 *)((s32)a0 + 0x2) += 1; \
        }

#define DEFINE_func_8018248C() \
    s32 func_8018248C(s32 arg0) { \
            return *(u16*)(arg0 + 0x2) == 0x6; \
        }

#define DEFINE_func_8018B564() \
    void func_8018B564(void *a0) { \
            M2C_FIELD(a0, s16 *, 0x2) = 2; \
        }

#define DEFINE_func_8018B6E8() \
    void func_8018B6E8(s32 *a0) { \
            *(s16 *)((s32)a0 + 0x2) = 0x2; \
        }

#define DEFINE_func_8017DEA4() \
    void func_8017DEA4(void) { \
    }

#define DEFINE_func_8017D12C() \
    extern void func_8002931C(void); \
    extern int func_8017D12C(int arg); \
    int func_8017D12C(int arg) { \
        ((void (*)(int))func_8002931C)(0x1A40000); \
    }

#define DEFINE_func_8018B9D0() \
    void func_8018B9D0(void *a0) { \
            M2C_FIELD(a0, s16 *, 0x2) = 2; \
        }

#define DEFINE_func_8017E0FC() \
    void func_8017E0FC(u8 *a0) { \
            *(u8 *)(a0 + 0x214) += 1; \
        }

#define DEFINE_func_8017E074() \
    void func_8017E074(void *a0) { \
            *(u8 *)((s32)a0 + 0x214) += 1; \
        }

#define DEFINE_func_80181998() \
    extern s32 D_801D7598; \
    extern s32 D_801D2200; \
    void func_80181998(void) { \
        *(s32 *)&D_801D2200 = D_801D7598; \
    }

#define DEFINE_func_80183958() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern s32 D_8018F83C; \
    void func_80183958(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018F83C, 0x1000000); \
    }

#define DEFINE_func_801819B0() \
    extern s32 D_801E7018; \
    extern s32 D_801D2200; \
    void func_801819B0(void) { \
        *(s32 *)&D_801D2200 = D_801E7018; \
    }

#define DEFINE_func_8018071C() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018F4F8; \
    void func_8018071C(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018F4F8, 0x1000000); \
    }

#define DEFINE_func_80183930() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018F830; \
    void func_80183930(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018F830, 0x1000000); \
    }

#define DEFINE_func_801892E4() \
    extern s32 func_80128ED8(void *a0, void *a1); \
    extern s32 D_801EAC88; \
    void func_801892E4(void *arg0) { \
        ((void (*)(s32 *, s32))func_80128ED8)(*(s32 *)((s32)arg0 + 0xCC), &D_801EAC88); \
    }

#define DEFINE_func_80184440() \
    extern s32 D_801EAC64; \
    extern s32 D_801EAC68; \
    void func_80184440(void) { \
        __asm__ __volatile__( \
            ".set noreorder\n" \
            "addiu $sp, $sp, -8\n" \
            "sw $fp, 0($sp)\n" \
            "addu $fp, $sp, $zero\n" \
            "li $v0, 1\n" \
            "lui $at, %%hi(D_801EAC64)\n" \
            "sw $v0, %%lo(D_801EAC64)($at)\n" \
            "lui $at, %%hi(D_801EAC68)\n" \
            "sw $zero, %%lo(D_801EAC68)($at)\n" \
            "addu $sp, $fp, $zero\n" \
            "lw $fp, 0($sp)\n" \
            "addiu $sp, $sp, 8\n" \
            : : : "memory"); \
    }

#define DEFINE_func_801819EC() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018DDCC; \
    void func_801819EC(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018DDCC, 0x1000000); \
    }

#define DEFINE_func_80181A3C() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018DDE4; \
    void func_80181A3C(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018DDE4, 0x1000000); \
    }

#define DEFINE_func_801819C4() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018DDC0; \
    void func_801819C4(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018DDC0, 0x1000000); \
    }

#define DEFINE_func_8017F4A4() \
    extern void func_8016EE40(s32 a0, s32 a1, s32 a2); \
    extern M2C_UNK D_8018DA14; \
    void func_8017F4A4(void) { \
        ((void (*)(void *, s32))func_8016EE40)(&D_8018DA14, 0x1000000); \
    }

#define DEFINE_func_801835C4() \
    extern void (*D_8018F804[])(void); \
    void func_801835C4(void *a0) { \
        D_8018F804[*(u8 *)((s32)a0 + 0x15)](); \
    }

#define DEFINE_func_8018BF08() \
    extern void func_8014B2A8(void); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_8018BF08(void) { \
        func_8014B2A8(); \
        ((s32 (*)(s32, s32))func_8002D4C8)(0x464, 0); \
    }

#define DEFINE_func_801848E4() \
    extern void (*D_8018FE80[])(void); \
    void func_801848E4(void *a0) { \
        D_8018FE80[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8018553C() \
    extern void (*D_801903DC[])(void); \
    void func_8018553C(void *a0) { \
        D_801903DC[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_801838E0() \
    extern void (*D_8018E858[])(void); \
    void func_801838E0(void *a0) { \
        D_8018E858[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8018385C() \
    extern void (*D_8018F824[])(void); \
    void func_8018385C(u8 *a0) { \
        D_8018F824[a0[0x15]](); \
    }

#define DEFINE_func_801838A4() \
    extern void (*D_8018E208[])(void); \
    void func_801838A4(void *a0) { \
        D_8018E208[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_80183B00() \
    extern void (*D_8018E8A0[])(void); \
    void func_80183B00(void *a0) { \
        D_8018E8A0[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8018AF00() \
    extern s32 D_801E03E0; \
    extern s32 D_801E7980; \
    extern void func_8018A168(s32 arg0, s32 arg1); \
    void func_8018AF00(void) { \
        D_801E7980 = &D_801E03E0; \
        func_8018A168(0x474, 0x4B0); \
    }

#define DEFINE_func_8016B91C() \
    extern void func_8016B964(SrcB964 *a0, DstB964 *a1); \
    void func_8016B91C(s32 arg0) { \
        ((void (*)(s32, s32))func_8016B964)(arg0, *(s32*)((u8*)arg0 + 0x10)); \
        ((void (*)(s32, s32))func_8016B964)(arg0, *(s32*)((u8*)arg0 + 0x14)); \
        ((void (*)(s32, s32))func_8016B964)(arg0, *(s32*)((u8*)arg0 + 0x18)); \
    }

#define DEFINE_func_8017248C() \
    extern s32 func_801724EC(s32 a0); \
    s32 func_8017248C(s32 arg0, s32 arg1) \
    { \
        if (((s32 (*)(void*, void*))func_801724EC)(arg0, arg1) != 0) { \
            *(u16*)((u8*)arg0 + 6) = *(u16*)((u8*)arg1 + 0); \
            *(u16*)((u8*)arg0 + 0xA) = *(u16*)((u8*)arg1 + 2); \
            *(u16*)((u8*)arg0 + 0xE) = *(u16*)((u8*)arg1 + 4); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_8017C5CC() \
    extern void (*D_80190CCC[])(void); \
    void func_8017C5CC(void *a0) { \
        D_80190CCC[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8018AB3C() \
    extern void (*D_801E0554[])(void); \
    void func_8018AB3C(void *a0) { \
        D_801E0554[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_80186084() \
    extern void (*D_801B8A3C[])(void); \
    void func_80186084(void *a0) { \
        D_801B8A3C[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8017D6B0() \
    extern void (*D_80190D1C[])(void); \
    void func_8017D6B0(s32 *param_1) \
    { \
        D_80190D1C[*(u16 *)((char *)param_1 + 0x2)](); \
    }

#define DEFINE_func_8018233C() \
    extern void (*D_80191EE4[])(void); \
    void func_8018233C(s32 *param_1) { \
        D_80191EE4[*(u16 *)((char *)param_1 + 0x2)](); \
    }

#define DEFINE_func_8018A740() \
    extern void (*D_801E04F0[])(void); \
    void func_8018A740(void *a0) { \
        D_801E04F0[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8018A898() \
    extern void (*D_801E051C[])(void); \
    void func_8018A898(void *a0) { \
        D_801E051C[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8017F058() \
    extern void (*D_8019155C[])(void); \
    void func_8017F058(void *a0) { \
        D_8019155C[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_801800E0() \
    extern void (*D_801918E4[])(void); \
    void func_801800E0(void *a0) { \
        D_801918E4[*(u16 *)((s32)a0 + 0x2)](); \
    }

#define DEFINE_func_8014EE14() \
    extern u16 D_800B99DA; \
    extern u8 D_801202A0[]; \
    extern s32 D_801150D8; \
    extern u8 D_80126720[]; \
    extern s16 D_80126724; \
    extern s16 D_801152AA; \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2) \
    { \
        register s32 param_1 __asm__("$16");   /* $s0 */ \
        register s32 param_2 __asm__("$23");   /* $s7 */ \
        register s16 *param_3 __asm__("$18");  /* $s2 */ \
        register s32 sVar6 __asm__("$20");     /* $s4 */ \
        register s32 sVar7 __asm__("$21");     /* $s5 */ \
        register s32 uVar8 __asm__("$22");     /* $s6 */ \
        u16 *psVar4; \
        s32 *piVar5; \
        s32 iVar2; \
        param_1 = arg0; \
        param_2 = arg1; \
        param_3 = arg2; \
        uVar8 = 0; \
        sVar7 = 8; \
        sVar6 = 8; \
        switch ((D_800B99DA & 0x60) >> 5) { \
        case 0: \
        case 1: \
            sVar7 = 7; \
            break; \
        case 2: \
            sVar6 = 7; \
            break; \
        } \
        __asm__("" : "=r"(param_1) : "0"(param_1)); \
        __asm__("" : "=r"(param_2) : "0"(param_2)); \
        __asm__("" : "=r"(param_3) : "0"(param_3)); \
        if ((*(u32 *)(param_1 + 0x44) & 0x100000) != 0) { \
            psVar4 = (u16 *)D_801202A0; \
            while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) { \
                piVar5 = (s32 *)((u8 *)psVar4 + 0x58); \
                if (*psVar4 != 0 && *piVar5 != 0 && \
                    psVar4 != *(u16 **)(param_1 + 0x178) && \
                    psVar4 != *(u16 **)(param_1 + 0x174) && \
                    (piVar5[1] & 0x1800) != 0) { \
                    D_801150D8 = 0; \
                    iVar2 = ((s32 (*)(s32, s32, s32, s16 *))func_80135A4C)(piVar5[-0xe], ((struct { s32 w; } *)piVar5)->w, param_2, param_3); \
                    if (iVar2 != 0) { \
                        if ((D_801150D8 & 1) != 0) { \
                            if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3) \
                                *(s16 *)(param_1 + 6) = *param_3 - sVar7; \
                            else \
                                *(s16 *)(param_1 + 6) = *param_3 + sVar7; \
                            if (-1 < (s32)D_80126724 - (s32)param_3[2]) \
                                *(s16 *)(param_1 + 0xE) = param_3[2] - sVar6; \
                            else \
                                *(s16 *)(param_1 + 0xE) = param_3[2] + sVar6; \
                            uVar8 = 1; \
                        } else { \
                            *(s16 *)(param_1 + 6) = ((u16 *)param_3)[0]; \
                            *(s16 *)(param_1 + 0xA) = ((u16 *)param_3)[1] + 0x10; \
                            uVar8 = 1; \
                            *(s16 *)(param_1 + 0xE) = ((u16 *)param_3)[2]; \
                        } \
                    } \
                } \
                psVar4 += 0x86; \
            } \
        } else { \
            psVar4 = (u16 *)D_801202A0; \
            while (psVar4 < (u16 *)(D_801202A0 + 0x6480)) { \
                piVar5 = (s32 *)((u8 *)psVar4 + 0x58); \
                if (*psVar4 != 0 && *piVar5 != 0 && \
                    psVar4 != *(u16 **)(param_1 + 0x178) && \
                    psVar4 != *(u16 **)(param_1 + 0x174) && \
                    (piVar5[1] & 0x1800) != 0) { \
                    D_801150D8 = 0; \
                    iVar2 = ((s32 (*)(s32, s32, s32, s16 *))func_80135A4C)(piVar5[-0xe], ((struct { s32 w; } *)piVar5)->w, param_2, param_3); \
                    if (iVar2 != 0) { \
                        if ((D_801150D8 & 1) != 0) { \
                            if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3) \
                                *(s16 *)(param_1 + 6) = *param_3 - sVar7; \
                            else \
                                *(s16 *)(param_1 + 6) = *param_3 + sVar7; \
                            if (-1 < (s32)D_80126724 - (s32)param_3[2]) \
                                *(s16 *)(param_1 + 0xE) = param_3[2] - sVar6; \
                            else \
                                *(s16 *)(param_1 + 0xE) = param_3[2] + sVar6; \
                        } else { \
                            *(s16 *)(param_1 + 6) = ((u16 *)param_3)[0]; \
                            *(s16 *)(param_1 + 0xA) = ((u16 *)param_3)[1] + 0x10; \
                            *(s16 *)(param_1 + 0xE) = ((u16 *)param_3)[2]; \
                            uVar8 = 1; \
                            if (*piVar5 < 0) { \
                                s32 av = D_801152AA; \
                                if (av < 0) av = -av; \
                                if (0x800 < (s16)av) { \
                                    if (-1 < (s32)*(s16 *)D_80126720 - (s32)*param_3) \
                                        *(s16 *)(param_1 + 6) = *param_3 - sVar7; \
                                    else \
                                        *(s16 *)(param_1 + 6) = *param_3 + sVar7; \
                                    if (-1 < (s32)D_80126724 - (s32)param_3[2]) \
                                        *(s16 *)(param_1 + 0xE) = param_3[2] - sVar6; \
                                    else \
                                        *(s16 *)(param_1 + 0xE) = param_3[2] + sVar6; \
                                } \
                            } \
                        } \
                    } \
                } \
                psVar4 += 0x86; \
            } \
        } \
        return uVar8; \
    }

#define DEFINE_func_80150528() \
    extern u8 D_801202A0[]; \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    s32 func_80150528(void *arg0, void *arg1, void *arg2) \
    { \
        u8 *p = D_801202A0; \
        /* Inline limit expression (NOT a cached `end` local): gcc hoists the \
         * loop-invariant `D_801202A0 + 0x6480` into the preheader, landing it in a \
         * callee-saved reg via a temp->saved copy (addu $s5,$v1,$zero) because it \
         * is live across the jal. A cached `end` local instead keeps the limit in \
         * one saved reg (52 ins, wrong regalloc). */ \
        if (p < D_801202A0 + 0x6480) { \
            do { \
                if (*(u16*)p != 0) { \
                    if ((*(u16*)(p + 0x5C) & 0x80) != 0) { \
                        if (*(s32*)(p + 0x58) != 0) { \
                            if (((s32 (*)(s32, s32, s32, s32))func_80135A4C)( \
                                    *(s32*)(p + 0x20), *(s32*)(p + 0x58), \
                                    (s32)arg1, (s32)arg2) != 0) { \
                                *(s32*)((u8*)arg0 + 0x1A4) = (s32)p; \
                                return 1; \
                            } \
                        } \
                    } \
                } \
                p += 0x10C; \
            } while (p < D_801202A0 + 0x6480); \
        } \
        return 0; \
    }

#define DEFINE_func_8014F2E0() \
    extern s32 D_801150D8; \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    extern u8 D_801202A0[]; \
    s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2) \
    { \
        s32 ret = 0; \
        u8 *s; \
        for (s = D_801202A0; s < D_801202A0 + 0x6480; s += 0x10C) { \
            if (*(u16 *)s != 0 && \
                *(s32 *)(s + 0x58) != 0 && \
                (s16 *)s != *(s16 **)(arg0 + 0x178) && \
                (s16 *)s != *(s16 **)(arg0 + 0x174) && \
                (*(s32 *)(s + 0x5C) & 0x1800) != 0) { \
                D_801150D8 = 0; \
                if (((s32 (*)(s32, s32, s32, s32))func_80135A4C)(((struct { s32 field; } *)(s + 0x20))->field, \
                                  ((struct { s32 field; } *)(s + 0x58))->field, \
                                  (s32)arg1, (s32)arg2) != 0) { \
                    ret = 1; \
                } \
            } \
        } \
        return ret; \
    }

#define DEFINE_func_80149374() \
    extern void func_80015978(s32 a0, s32 *a1); \
    extern void func_8012F14C(s32); \
    extern void func_80015954(s32 a0, s32 a1); \
    void func_80149374(s32 arg0, s32 arg1) \
    { \
        u64 sp10; \
        u64 sp18; \
        ((void (*)(s32, void*))func_80015978)(arg1, &sp10); \
        { \
            void *q = &sp18; \
            ((void (*)(s32, void*, void*))func_8012F14C)(*(s32*)(arg0 + 0x20) + 0x34, &sp10, q); \
            __asm__ __volatile__("" : "=r"(q));  /* LOAD-BEARING: kills the (plus sp 0x18) CSE class reg; emits 0 bytes */ \
        } \
        ((void (*)(void*, s32))func_80015954)(&sp18, arg1); \
    }

#define DEFINE_func_80132784() \
    extern void func_80049CAC(s32 a0, s32 a1); \
    extern void func_80020F34(s32 a0, s32 a1); \
    extern void func_80054514(s32 a0, s32 a1); \
    void func_80132784(s32 a0, s32 a1, u32 a2) \
    { \
      s32 s7 = a0; \
      s32 s0p = a1; \
      u32 s2v = a2; \
      s32 s6; \
      s32 s1m; \
      s16 sVar1; \
      u8 buf[0xC0]; \
      if (((*((s32 *) (s7 + 0x20))) != 0) || ((*((s32 *) (s0p + 0x20))) != 0)) \
      { \
        s6 = *((s32 *) (s0p + 0x20)); \
        s1m = *((s32 *) (s6 + 0x20)); \
        if (s1m != 0) \
        { \
          *((s32 *) (buf + 0x48)) = *((s32 *) (s6 + 0x78)); \
          *((s32 *) (buf + 0x00)) = 0; \
          if (((*((u16 *) (s6 + 0x2C))) & 1) != 0) \
          { \
            *((Blk16 *) (buf + 0x04)) = *((Blk16 *) (s6 + 0x34)); \
            *((Blk16 *) (buf + 0x14)) = *((Blk16 *) (s6 + 0x44)); \
          } \
          else \
          { \
            func_80049CAC(s6 + 0x10, (s32) (buf + 0x04)); \
            sVar1 = (*((s16 *) (s0p + 6))) + (*((s16 *) (s0p + 0x50))); \
            *((s16 *) (s6 + 8)) = sVar1; \
            *((s32 *) (buf + 0x18)) = (s32) sVar1; \
            sVar1 = (*((s16 *) (s0p + 0xA))) + (*((s16 *) (s0p + 0x52))); \
            *((s16 *) (s6 + 0xA)) = sVar1; \
            *((s32 *) (buf + 0x1C)) = (s32) sVar1; \
            sVar1 = (*((s16 *) (s0p + 0xE))) + (*((s16 *) (s0p + 0x54))); \
            *((s16 *) (s6 + 0xC)) = sVar1; \
            *((s32 *) (buf + 0x20)) = (s32) sVar1; \
            *((Blk16 *) (s6 + 0x34)) = *((Blk16 *) (buf + 0x04)); \
            *((Blk16 *) (s6 + 0x44)) = *((Blk16 *) (buf + 0x14)); \
            *((u16 *) (s6 + 0x2C)) = (*((u16 *) (s6 + 0x2C))) | 1; \
          } \
          if (((*((u16 *) (s6 + 0x2C))) & 0x10) != 0) \
          { \
            func_80020F34((s32) (buf + 0x04), s6 + 0x18); \
          } \
          func_80054514((s32) (buf + 0x00), (s32) (buf + 0x50)); \
          if (((s1m & 0x1000000) == 0) && (((*((u16 *) (s6 + 0x2C))) & 0x40) == 0)) \
          { \
            s1m = s1m + ((s2v & 0xFFFF) * 0xC); \
            func_80049CAC(s1m + 6, (s32) (buf + 0x70)); \
            *((s32 *) (buf + 0x84)) = (s32) (*((s16 *) (s1m + 0))); \
            *((s32 *) (buf + 0x88)) = (s32) (*((s16 *) (s1m + 2))); \
            *((s32 *) (buf + 0x8C)) = (s32) (*((s16 *) (s1m + 4))); \
          } \
          else \
          { \
            u32 *pu = (u32 *) ((s1m & 0xFEFFFFFF) + ((s2v & 0xFFFF) * 8)); \
            u32 w; \
            *((u16 *) (buf + 0xB0)) = *((u16 *) (((s32) pu) + 6)); \
            w = *pu; \
            *((u16 *) (buf + 0xB2)) = ((u16) (*((u8 *) (((s32) pu) + 1)))) | ((u16) ((w & 0xF) << 8)); \
            *((u16 *) (buf + 0xB4)) = ((u16) (w >> 0x10)) & 0xFF; \
            *((u16 *) (buf + 0xB4)) = (*((u16 *) (buf + 0xB4))) | ((u16) ((w & 0xF0) << 4)); \
            func_80049CAC((s32) (buf + 0xB0), (s32) (buf + 0x70)); \
            *((s32 *) (buf + 0x84)) = (s32) (*((s8 *) (((s32) pu) + 3))); \
            *((s32 *) (buf + 0x88)) = (s32) ((s8) pu[1]); \
            *((s32 *) (buf + 0x8C)) = (s32) (*((s8 *) (((s32) pu) + 5))); \
          } \
          { \
    __asm__ __volatile__( \
                        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n" \
                        "ctc2 $12, $0\n" "ctc2 $13, $1\n" \
                        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n" \
                        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n" \
                        : : "r"((s32 *)(buf + 0x50)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x70)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x90)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x72)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x92)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x74)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x94)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n" \
                        "ctc2 $12, $5\n" "lw $14, 28(%0)\n" \
                        "ctc2 $13, $6\n" "ctc2 $14, $7\n" \
                        : : "r"((s32 *)(buf + 0x50)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n" \
                        "sll $13, $13, 16\n" "or $12, $12, $13\n" \
                        "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n" \
                        : : "r"((s16 *)(buf + 0x84)) : "$12", "$13", "memory"); \
    __asm__ __volatile__( \
                        "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n" \
                        : : "r"((s32 *)(buf + 0xA4)) : "memory"); \
          } \
          s6 = *((s32 *) (s7 + 0x20)); \
          func_80049CAC(s6 + 0x10, (s32) (buf + 0x70)); \
          sVar1 = (*((s16 *) (s7 + 6))) + (*((s16 *) (s7 + 0x50))); \
          *((s16 *) (s6 + 8)) = sVar1; \
          *((s32 *) (buf + 0x84)) = (s32) sVar1; \
          sVar1 = (*((s16 *) (s7 + 0xA))) + (*((s16 *) (s7 + 0x52))); \
          *((s16 *) (s6 + 0xA)) = sVar1; \
          *((s32 *) (buf + 0x88)) = (s32) sVar1; \
          sVar1 = (*((s16 *) (s7 + 0xE))) + (*((s16 *) (s7 + 0x54))); \
          *((s16 *) (s6 + 0xC)) = sVar1; \
          *((s32 *) (buf + 0x8C)) = (s32) sVar1; \
          { \
    __asm__ __volatile__( \
                        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n" \
                        "ctc2 $12, $0\n" "ctc2 $13, $1\n" \
                        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n" \
                        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n" \
                        : : "r"((s32 *)(buf + 0x90)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x70)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x50)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x72)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x52)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
                        "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
                        : : "r"((s16 *)(buf + 0x74)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
                        "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
                        : : "r"((s16 *)(buf + 0x54)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n" \
                        "ctc2 $12, $5\n" "lw $14, 28(%0)\n" \
                        "ctc2 $13, $6\n" "ctc2 $14, $7\n" \
                        : : "r"((s32 *)(buf + 0x90)) : "$12", "$13", "$14", "memory"); \
    __asm__ __volatile__( \
                        "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n" \
                        "sll $13, $13, 16\n" "or $12, $12, $13\n" \
                        "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n" \
                        "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n" \
                        : : "r"((s16 *)(buf + 0x84)) : "$12", "$13", "memory"); \
    __asm__ __volatile__( \
                        "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n" \
                        : : "r"((s32 *)(buf + 0x64)) : "memory"); \
          } \
          *((Blk16 *) (s6 + 0x34)) = *((Blk16 *) (buf + 0x50)); \
          *((Blk16 *) (s6 + 0x44)) = *((Blk16 *) (buf + 0x60)); \
          s0p = 0x30; \
          *((Blk16 *) (s6 + 0x54)) = *((Blk16 *) (buf + 0x50)); \
          *((Blk16 *) (s6 + 0x64)) = *((Blk16 *) (buf + 0x60)); \
          *((s32 *) (s6 + s0p)) = 1; \
          *((u16 *) (s6 + 0x2C)) = (*((u16 *) (s6 + 0x2C))) | 1; \
        } \
      } \
      return; \
    }

#define DEFINE_func_801542A4() \
    extern void func_80154418(void *a0); \
        void func_801542A4(s32 *a0, s32 a1) { \
            *(s32 *)((u8 *)a0 + 0xB4) = a1; \
            *(s16 *)((u8 *)a0 + 0xBA) = 1; \
            *(s16 *)((u8 *)a0 + 0xB8) = 1; \
            *(s8 *)((u8 *)a0 + 0xBC) = 0; \
            *(s8 *)((u8 *)a0 + 0xBD) = 0; \
            *(s8 *)((u8 *)a0 + 0xDC) = 0; \
            ((void (*)(void))func_80154418)(); \
        }

#define DEFINE_func_8015BE94() \
    extern void func_80161124(void *a0); \
        extern void func_80146CA0(void *a0); \
        s32 func_8015BE94(s32 *a0) \
    { \
            ((void (*)(s32 *))func_80161124)(a0); \
            ((s32 (*)(s32))func_80146CA0)((s32)a0); \
        }

#define DEFINE_func_8015F380() \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80148534(s32 a0, s32 a1); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80147324(s32 arg0); \
    extern s32 func_801725B8(u8 *a0); \
    extern void func_80146CA0(void *a0); \
    void func_8015F380(void* arg0) { \
        s64 sp20; \
        s64 sp28; \
        ((void (*)(void*, s32))func_80154150)(arg0, 0x18); \
        *(s8*)((u8*)arg0 + 0x244) = 0; \
        *(s8*)((u8*)arg0 + 0x245) = 0; \
        ((void (*)(void*, s32))func_80146E90)(arg0, 0); \
        ((void (*)(s64*, s64*))func_80148534)(&sp20, &sp28); \
        ((void (*)(s32, void*, s16, s16, s16, s32, s32))func_80146A6C)(0x25, arg0, *(s16*)((u8*)arg0 + 0x6), (s16)(*(u16*)((u8*)arg0 + 0xA) - 0x14), *(s16*)((u8*)arg0 + 0xE), 0, 0); \
        ((void (*)(s32, void*, s16, s16, s16, s32, s32))func_80146A6C)(0x25, arg0, *(s16*)((u8*)arg0 + 0x6), (s16)(*(u16*)((u8*)arg0 + 0xA) - 0x14), *(s16*)((u8*)arg0 + 0xE), 1, 0); \
        func_80147324(0x56D); \
        ((void (*)(void*))func_801725B8)(arg0); \
        func_80146CA0(arg0); \
    }

#define DEFINE_func_80160F00() \
    extern void func_80149020(s32 *a0); \
    extern void func_80154150(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_80129248(s16 a0); \
    extern void func_80146E90(s32 *a0, s32 a1); \
    extern void func_80146CA0(void *a0); \
    extern u16 D_801270C0; \
    extern u8 D_800B9A17; \
    void func_80160F00(void* arg0) { \
        ((void (*)(void*))func_80149020)(arg0); \
        ((void (*)(void*, s32))func_80154150)(arg0, 4); \
        ((void (*)(void*, s32))func_80154A74)(arg0, 0x11); \
        D_801270C0 = 2; \
        ((void (*)(s32))func_80129248)(0); \
        D_800B9A17 = 0; \
        ((void (*)(void*, s32))func_80146E90)(arg0, 0x10); \
        func_80146CA0(arg0); \
    }

#define DEFINE_func_801653B8() \
    extern void func_801653F4(s32 a0); \
        extern void func_80147078(s32 *a0, s16 a1); \
        extern void func_80165580(s32 _arg0); \
        void func_801653B8(s32 *a0) { \
            s32 s = (s32)a0; \
            ((void (*)(s32 *))func_801653F4)((s32 *)s); \
            ((void (*)(s32, s32))func_80147078)(s, 0x17); \
            ((void (*)(void *))func_80165580)((void *)s); \
        }

#define DEFINE_func_80166244() \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    void func_80166244(void* arg0) { \
        ((void (*)(s32, void*, s16, s16, s16, u32, u32))func_80146A6C)(3, arg0, *(s16*)((u8*)arg0 + 6), *(u16*)((u8*)arg0 + 0xA) - 0x10, *(s16*)((u8*)arg0 + 0xE), 0x8F8FFF8, 0xE000B000); \
    }

#define DEFINE_func_8016E778() \
    extern void func_8016E7C8(int param_1, short *p1, unsigned int *p2); \
    void func_8016E778(int param_1) \
    { \
        short local_18[3]; \
        unsigned int local_10; \
        unsigned short uVar1; \
        int iVar2; \
        uVar1 = *(unsigned short *)(param_1 + 0x12); \
        local_18[2] = uVar1; \
        local_18[1] = uVar1; \
        local_18[0] = uVar1; \
        iVar2 = *(short *)(param_1 + 0x16); \
        local_10 = iVar2 | (iVar2 << 16 | iVar2 << 8); \
        func_8016E7C8(param_1, local_18, &local_10); \
    }

#define DEFINE_func_801732C4() \
    extern void func_8016F2A8(void); \
        extern s32 func_80174650(s32); \
        void func_801732C4(s32 *a0) { \
            ((void (*)(s32 *))func_8016F2A8)(a0); \
            func_80174650((s32)a0); \
        }

#define DEFINE_func_8017331C() \
    extern void func_8016F2C8(void); \
        extern s32 func_80174650(s32); \
        void func_8017331C(s32 *a0) { \
            ((void (*)(s32 *))func_8016F2C8)(a0); \
            func_80174650((s32)a0); \
        }

#define DEFINE_func_80173374() \
    extern void func_8016F2EC(void); \
        extern s32 func_80174650(s32); \
        void func_80173374(s32 *a0) { \
            ((void (*)(s32 *))func_8016F2EC)(a0); \
            func_80174650((s32)a0); \
        }

#define DEFINE_func_80174554() \
    extern void func_8014706C(void *arg0); \
        extern s32 func_80174650(s32); \
        void func_80174554(s32 arg0) { \
            ((void (*)(s32 *))func_8014706C)((s32 *)arg0); \
            func_80174650(arg0); \
        }

#define DEFINE_func_801745AC() \
    extern void func_80147060(u8 *a0); \
    extern s32 func_80174650(s32); \
    void func_801745AC(s32 *a0) { \
        ((void (*)(s32 *))func_80147060)(a0); \
        func_80174650((s32)a0); \
    }

#define DEFINE_func_8014F74C() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern s32 func_80029178(s32 arg); \
    extern u8 D_800D3918[]; \
    extern u8 D_801152A8[]; \
    extern s16 D_801152B0; \
    extern s32 D_801152BC; \
    int func_8014F74C(s32 arg0) \
    { \
        PosT  sp10; \
        MoveT sp18; \
        PosT  sp20; \
        u16 x6, xA, xE; \
        s32 ret; \
        sp10.x = *(u16 *)(arg0 + 0x88); \
        sp10.y = *(u16 *)(arg0 + 0x8A); \
        sp10.z = *(u16 *)(arg0 + 0x8C); \
        sp18.x = sp20.x = x6 = *(u16 *)(arg0 + 6); \
        sp18.y = sp20.y = xA = *(u16 *)(arg0 + 0xA); \
        sp18.z = sp20.z = xE = *(u16 *)(arg0 + 0xE); \
        if (*(s16 *)(arg0 + 0x146) != 0) { \
            sp18.x = x6 + *(u16 *)(arg0 + 0x140); \
            sp18.y = xA + *(u16 *)(arg0 + 0x142); \
            sp18.z = xE + *(u16 *)(arg0 + 0x144); \
        } \
        ret = func_80133784(0, &sp10, (s32)&sp18); \
        if (ret != 0) { \
            *(s16 *)(arg0 + 6)   = sp18.x; \
            *(s16 *)(arg0 + 0xA) = sp18.y; \
            *(s16 *)(arg0 + 0xE) = sp18.z; \
            if (*(u8 *)&sp18.w != 0) { \
                *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w; \
            } \
            *(u16 *)(arg0 + 0x16E) = (u32)sp18.w >> 13; \
            if (ret == 0x2000) { \
                __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8); \
            } else if (ret == 0x4000) { \
                __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8); \
            } \
            if (*(u16 *)(arg0 + 0x16C) != 0x1D) { \
                return ret; \
            } \
            if ((func_80029178(0x21) & 0xFF) == 0) { \
                ret &= ~0x2000; \
                ret |= 0x4000; \
                __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8); \
                D_801152BC = 1; \
            } \
            __asm__ __volatile__("" ::: "memory"); \
            return ret; \
        } \
        /* ret == 0 */ \
        __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8); \
        if (*(u8 *)&sp18.w != 0) { \
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w; \
        } \
        if (((sp10.x != sp20.x) || (sp10.y != sp20.y) || (sp10.z != sp20.z)) && \
            (sp10.x == (s16)sp18.x) && (sp10.y == (s16)sp18.y) && (sp10.z == (s16)sp18.z)) { \
            return 0x8000; \
        } \
        return 0; \
    }

#define DEFINE_func_8014E048() \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */ \
    extern s16 D_801152AC; \
    s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3) \
    { \
        s32 dx; \
        s32 dz; \
        s32 w0; \
        s32 w1; \
        s32 t2; \
        s32 p1; \
        register s32 h __asm__("$4");   /* a0 — the b[0]-store copy temp (RC-4b) */ \
        register u16 *p3 __asm__("$7");   /* a3 — force the addu a3,a2 copy to materialize (RC-3) */ \
        u16 *psVar11; \
        s32 sVar7; \
        s16 sVar8; \
        u32 uVar10; \
        short a[3]; \
        short b[3]; \
        __asm__("addu %0,%1,$zero" : "=r"(p3) : "r"(param_3)); \
        w0 = p3[0]; \
        w1 = param_2[0]; \
        dx = w0 - w1; \
        p1 = param_1; \
        __asm__ __volatile__("" : : "r"(p1), "r"(param_2)); \
        w0 = p3[2]; \
        w1 = param_2[2]; \
        dz = w0 - w1; \
        if ((short)(dx | dz) != 0) { \
            h = dx; \
            b[0] = (short)h; \
            b[1] = p3[1] - param_2[1]; \
            t2 = p3[2] - param_2[2]; \
            b[2] = t2; \
            b[0] = -(short)dx; \
            b[2] = -t2; \
            psVar11 = *(u16 **)(p1 + 0x170); \
            if (*psVar11 != 0) { \
                if ((psVar11[0x2e] & 0x1000U) != 0) { \
                    sVar8 = (s16)dz; \
                    if (*(s32 *)(psVar11 + 0x2c) != 0) { \
                        if (((s32 (*)(s32, s32, u16 *))func_80135A4C)(*(s32 *)(psVar11 + 0x10), *(s32 *)(psVar11 + 0x2c), param_2) != 0) { \
                            s32 ndz = psVar11[3] - *(u16 *)(p1 + 6); \
                            s32 ndx = psVar11[7] - *(u16 *)(p1 + 0xe); \
                            sVar7 = (s16)ratan2((s32)sVar8, (s32)(s16)dx); \
                            sVar8 = (s16)ratan2((s32)(s16)ndx, (s32)(s16)ndz); \
                            if ((s16)func_80012A60(sVar7, sVar8) < 0x400) { \
                                a[0] = psVar11[3]; \
                                a[1] = psVar11[5]; \
                                a[2] = psVar11[7]; \
                                b[0] = a[0] + b[0]; \
                                b[1] = a[1] + b[1]; \
                                b[2] = a[2] + b[2]; \
                                uVar10 = ((s32 (*)(s32, void *, void *))func_80133784)(0, a, b); \
                                if ((uVar10 == 0) || (((uVar10 & 0x2000) != 0) && ((*(u16 *)D_801152A8 | *(u16 *)&D_801152AC) == 0))) { \
                                    psVar11[3] = b[0]; \
                                    psVar11[5] = b[1]; \
                                    psVar11[7] = b[2]; \
                                } else { \
                                    *(u16 *)(p1 + 6) = *param_2; \
                                    *(u16 *)(p1 + 10) = param_2[1] + 0x10; \
                                    *(u16 *)(p1 + 0xe) = param_2[2]; \
                                } \
                                return 1; \
                            } \
                        } \
                    } \
                } \
            } \
        } \
        *(s32 *)(p1 + 0x170) = 0; \
        return 0; \
    }

#define DEFINE_func_80157580() \
    extern void func_8014CC28(s32 a0);      /* defined  */ \
    extern s32 func_8014F3E8(s32 a0);      /* declared */ \
    extern void func_8015BDD0(s32 *a0);     /* defined  */ \
    extern void func_801575E4(void *a0);    /* defined  */ \
    void func_80157580(s32 arg0) { \
        s32 temp_s1; \
        /* return-cast: canonical func_8014CC28 is void, but its $v0 is used here */ \
        temp_s1 = ((s32 (*)(s32))func_8014CC28)(arg0); \
        /* return-cast: canonical func_8014F3E8 is void, but its $v0 is tested here */ \
        if ((((s32 (*)(s32))func_8014F3E8)(arg0) == 0) && (temp_s1 == 0)) { \
            func_8015BDD0((s32 *)arg0); \
            return; \
        } \
        func_801575E4((void *)arg0); \
    }

#define DEFINE_func_80129CF8() \
    extern void func_8012A328(void); \
    extern void func_80053308(s32); \
    extern s32 func_80012F74(s32, s32, s32, s32);  /* canonical s32 (engine_core); (s16)-cast the return for the sll/sra */ \
    extern void GsSetRefView2L(void *); \
    extern s8 D_801150D6;            /* canonical (engine_core macro): s8 — access via *(u8*)& for lbu */ \
    extern u8 D_80127504; \
    extern s32 D_80126E60[]; \
    extern s32 D_80126F04[]; \
    extern u8 D_80126948[];          /* canonical (sibling): u8[] — cast (s32*) at use */ \
    extern s32 D_80126FA8[]; \
    extern struct BigCopy D_80126DB8;/* canonical (engine_core macro): struct BigCopy — (s32*)& at use */ \
    extern u8 D_800AF630[];          /* canonical (sibling): u8[] — cast (s32*) at use */ \
    extern s32 D_800AE688[]; \
    extern s32 D_801151D4;           /* canonical (10 siblings): scalar s32 — store (s32)ptr */ \
    void func_80129CF8(void) \
    { \
        RView view; /* unused: reserves the extra 0x20 frame bytes the target has */ \
        s32 *cam; \
        s32 *p1; \
        s32 *p2; \
        s32 a; \
        s32 b; \
        s32 iVar2; \
        func_8012A328(); \
        p2 = (s32 *)D_800AF630; \
        p1 = (s32 *)&D_80126DB8; \
        if (*(u8 *)&D_801150D6 == 1) { \
            cam = D_80126E60; \
        } else if (*(u8 *)&D_801150D6 == 2) { \
            cam = D_80126F04; \
        } else { \
            cam = (s32 *)D_80126948; \
            if (*(u8 *)&D_801150D6 == 3) { \
                cam = D_80126FA8; \
            } \
        } \
        if (cam[0] != 0) { \
            (*(void (*)(s32 *))cam[0])(cam); \
        } \
        func_80053308(cam[2]); \
        if (D_80127504 != 0) { \
            p1[0xf] = (s16)func_80012F74((s16)p1[0xf], (s16)cam[0xf], 2, 1); \
            p1[0x10] = (s16)func_80012F74((s16)p1[0x10], (s16)cam[0x10], 2, 1); \
            p1[0x11] = (s16)func_80012F74((s16)p1[0x11], (s16)cam[0x11], 2, 1); \
            p1[0x12] = (s16)func_80012F74((s16)p1[0x12], (s16)cam[0x12], 2, 1); \
            p1[0x13] = (s16)func_80012F74((s16)p1[0x13], (s16)cam[0x13], 2, 1); \
            p1[0x14] = (s16)func_80012F74((s16)p1[0x14], (s16)cam[0x14], 2, 1); \
            p1[0x15] = (s16)func_80012F74((s16)p1[0x15], (s16)cam[0x15], 2, 1); \
            D_80127504 = D_80127504 - 1; \
        } else { \
            p1[0xf] = cam[0xf]; \
            p1[0x10] = cam[0x10]; \
            p1[0x11] = cam[0x11]; \
            p1[0x12] = cam[0x12]; \
            p1[0x13] = cam[0x13]; \
            p1[0x14] = cam[0x14]; \
            p1[0x15] = cam[0x15]; \
        } \
        a = p1[0xf]; \
        b = cam[0x1f]; \
        cam[0x17] = a + b; \
        a = p1[0x10]; \
        b = cam[0x20]; \
        cam[0x18] = a + b; \
        a = p1[0x11]; \
        b = cam[0x21]; \
        cam[0x19] = a + b; \
        a = p1[0x12]; \
        b = cam[0x22]; \
        cam[0x1a] = a + b; \
        a = p1[0x13]; \
        b = cam[0x23]; \
        cam[0x1b] = a + b; \
        a = p1[0x14]; \
        b = cam[0x24]; \
        cam[0x1c] = a + b; \
        iVar2 = p1[0x15] + cam[0x25]; \
        cam[0x1e] = cam[0x16]; \
        cam[0x1d] = iVar2; \
        GsSetRefView2L(&cam[0x17]); \
        *(RView *)(p2 + 6) = *(RView *)D_800AE688; \
        D_801151D4 = (s32)cam; \
    }

#define DEFINE_func_80138ED0() \
    extern s32 func_8013914C(s32 a0, s32 a1); \
    extern void func_800599B8(u16 *); \
    extern u16 D_80127C0C[]; \
    extern s32 D_80127548[]; \
    s32 func_80138ED0(u8 *param_1, u32 param_2, u8 *param_3) \
    { \
        u16 local[4]; \
        u16 uVar1; \
        s32 result; \
        u16 uVar4; \
        u8 *pbVar7; \
        u8 *pb; \
        u16 *base; \
        u16 *p; \
        s32 iVar2; \
        u32 s0acc; \
        u32 tmp; \
        s32 shift; \
        pb = param_3; \
        uVar1 = *(u8 *)(param_1 + 0x23) & 0xf; \
        result = ((s32 (*)(u8 *, u16 *))func_8013914C)(param_1, local); \
        if (result != 0) { \
            return 1; \
        } \
        uVar4 = local[0] - *(u16 *)(param_1 + 0x38); \
        pbVar7 = pb + (param_2 & 0xffff) * 0xc; \
        base = D_80127C0C + uVar4; \
        iVar2 = 0; \
        if (uVar4 % 3 != 0) { \
            u32 pv = uVar1; \
            p = base; \
            do { \
                shift = 6; \
                do { \
                    tmp = (s0acc & 0xffff) << 4; \
                    s0acc = tmp | pv; \
                    if ((((s32)*pbVar7 >> shift) & 1) == 0) { \
                        s0acc = tmp; \
                    } \
                    shift++; \
                } while (shift < 8); \
                *p = *p | (s0acc << 8); \
                p++; \
                shift = 2; \
                do { \
                    tmp = (s0acc & 0xffff) << 4; \
                    s0acc = tmp | pv; \
                    if ((((s32)*pbVar7 >> shift) & 1) == 0) { \
                        s0acc = tmp; \
                    } \
                    shift++; \
                } while (shift < 6); \
                *p = s0acc; \
                p += 0x35; \
                iVar2++; \
                pbVar7++; \
            } while (iVar2 < 0xc); \
            iVar2 = 0; \
        } else { \
            u32 pv = uVar1; \
            p = base; \
            do { \
                shift = 4; \
                do { \
                    tmp = (s0acc & 0xffff) << 4; \
                    s0acc = tmp | pv; \
                    if ((((s32)*pbVar7 >> shift) & 1) == 0) { \
                        s0acc = tmp; \
                    } \
                    shift++; \
                } while (shift < 8); \
                *p = s0acc; \
                p++; \
                shift = 2; \
                do { \
                    tmp = (s0acc & 0xffff) << 4; \
                    s0acc = tmp | pv; \
                    if ((((s32)*pbVar7 >> shift) & 1) == 0) { \
                        s0acc = tmp; \
                    } \
                    shift++; \
                } while (shift < 4); \
                *p = s0acc & 0xff; \
                p += 0x35; \
                iVar2++; \
                pbVar7++; \
            } while (iVar2 < 0xc); \
            iVar2 = 0; \
        } \
        { \
            u16 *src = base; \
            s32 dcount; \
            s32 df; \
            s32 decoy; \
            s32 c36; \
            u16 tv; \
            register s32 *dp __asm__("$4"); \
            register u16 *ba __asm__("$5"); \
            dp = D_80127548; \
            dcount = *dp; \
            c36 = 0x24; \
            __asm__ ("" : : "r"(c36), "r"(dcount)); \
            df = c36 - dcount; \
            tmp = (df << 1) + df; \
            tmp = tmp << 4; \
            dp = dp + 1; \
            ba = (u16 *)(tmp + (u8 *)dp); \
            __asm__ ("" : "=r"(decoy) : "r"(ba)); \
            __asm__ ("" : : "r"(decoy)); \
            { \
                register u16 *dst __asm__("$4"); \
                dst = ba; \
                do { \
                    tv = *src; src++; \
                    *dst = tv; dst++; \
                    tv = *src; src += 0x35; \
                    *dst = tv; dst++; \
                    iVar2++; \
                } while (iVar2 < 0xc); \
            } \
        } \
        local[2] = 2; \
        local[3] = 0xc; \
        func_800599B8(local); \
        return 0; \
    }

#define DEFINE_func_8012D098() \
    extern void func_8012F214(s32 a0, s32 a1, s32 a2); \
    extern void func_8012D3B4(s32 arg0, s32 arg1, s32 arg2); \
    void func_8012D098(u16 *param_1, u32 param_2) \
    { \
        s32 bufA[2]; \
        s32 bufB[2]; \
        s32 bufC[2]; \
        s32 bufD[2]; \
        s32 bufE[2]; \
        s32 bufF[2]; \
        s32 bufG[2]; \
        s32 bufH[2]; \
        u16 scratch[3]; \
        if (param_1 != 0 && *param_1 != 0) { \
            if (param_2 == 0) { \
                if (*(u32 *)(param_1 + 0x2c) == 0) { \
                    return; \
                } \
                param_2 = (*(u32 *)(param_1 + 0x2c) & 0xfffffff) | 0x80000000; \
            } \
            scratch[0] = *(u16 *)(param_2 + 4); \
            scratch[1] = *(u16 *)(param_2 + 8); \
            scratch[2] = *(u16 *)(param_2 + 0xc); \
            func_8012F214(param_1, scratch, bufA); \
            scratch[0] = *(u16 *)(param_2 + 6); \
            scratch[1] = *(u16 *)(param_2 + 8); \
            scratch[2] = *(u16 *)(param_2 + 0xc); \
            func_8012F214(param_1, scratch, bufB); \
            scratch[0] = *(u16 *)(param_2 + 4); \
            scratch[1] = *(u16 *)(param_2 + 0xa); \
            scratch[2] = *(u16 *)(param_2 + 0xc); \
            func_8012F214(param_1, scratch, bufC); \
            scratch[0] = *(u16 *)(param_2 + 6); \
            scratch[1] = *(u16 *)(param_2 + 0xa); \
            scratch[2] = *(u16 *)(param_2 + 0xc); \
            func_8012F214(param_1, scratch, bufD); \
            scratch[0] = *(u16 *)(param_2 + 4); \
            scratch[1] = *(u16 *)(param_2 + 8); \
            scratch[2] = *(u16 *)(param_2 + 0xe); \
            func_8012F214(param_1, scratch, bufE); \
            scratch[0] = *(u16 *)(param_2 + 6); \
            scratch[1] = *(u16 *)(param_2 + 8); \
            scratch[2] = *(u16 *)(param_2 + 0xe); \
            func_8012F214(param_1, scratch, bufF); \
            scratch[0] = *(u16 *)(param_2 + 4); \
            scratch[1] = *(u16 *)(param_2 + 0xa); \
            scratch[2] = *(u16 *)(param_2 + 0xe); \
            func_8012F214(param_1, scratch, bufG); \
            scratch[0] = *(u16 *)(param_2 + 6); \
            scratch[1] = *(u16 *)(param_2 + 0xa); \
            scratch[2] = *(u16 *)(param_2 + 0xe); \
            func_8012F214(param_1, scratch, bufH); \
            func_8012D3B4(bufA, bufB, 0xffffff); \
            func_8012D3B4(bufB, bufD, 0xffffff); \
            func_8012D3B4(bufD, bufC, 0xffffff); \
            func_8012D3B4(bufC, bufA, 0xffffff); \
            func_8012D3B4(bufE, bufF, 0xffffff); \
            func_8012D3B4(bufF, bufH, 0xffffff); \
            func_8012D3B4(bufH, bufG, 0xffffff); \
            func_8012D3B4(bufG, bufE, 0xffffff); \
            func_8012D3B4(bufA, bufE, 0xffffff); \
            func_8012D3B4(bufB, bufF, 0xffffff); \
            func_8012D3B4(bufC, bufG, 0xffffff); \
            func_8012D3B4(bufD, bufH, 0xffffff); \
        } \
        return; \
    }

#define DEFINE_func_8012EC04() \
    extern void func_80049CAC(s32 a0, s32 a1); \
    void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3) \
    { \
        struct { s16 h[8]; } buf; \
        s32 iVar4; \
        s32 M; \
        s32 c; \
        register u32 v __asm__("$17");   /* $s1 */ \
        iVar4 = *(s32 *)(param_1 + 0x20); \
        v = *(u32 *)(iVar4 + 0x20); \
        if (v == 0) { \
            *(Blk16 *)(param_3)             = *(Blk16 *)(iVar4 + 0x34); \
            *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44); \
        } else if ((v & 0x1000000) != 0) { \
            register s32 p __asm__("$16"); \
            s32 w; \
            p = (s32)(v & 0xfeffffff); \
            p = p + param_2 * 8; \
            buf.h[0] = *(s16 *)(p + 6); \
            w = *(s32 *)p; \
            buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8)); \
            buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4)); \
            func_80049CAC((s32)&buf, (s32)param_3); \
            param_3[5] = *(s8 *)(p + 3); \
            param_3[6] = *(s8 *)(p + 4); \
            param_3[7] = *(s8 *)(p + 5); \
        } else { \
            s32 q; \
            v = v + param_2 * 0xc; \
            q = (s32)v; \
            buf.h[0] = *(s16 *)(q + 6); \
            buf.h[1] = *(s16 *)(q + 8); \
            buf.h[2] = *(s16 *)(q + 0xa); \
            func_80049CAC((s32)&buf, (s32)param_3); \
            param_3[5] = *(s16 *)(q + 0); \
            param_3[6] = *(s16 *)(q + 2); \
            param_3[7] = *(s16 *)(q + 4); \
        } \
        /* --- GTE tail --- */ \
        /* gte_SetRotMatrix(M) */ \
        M = *(s32 *)(param_1 + 0x20) + 0x34; \
        __asm__ __volatile__( \
            "lw $12, 0(%0)\n" "lw $13, 4(%0)\n" \
            "ctc2 $12, $0\n" "ctc2 $13, $1\n" \
            "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n" \
            "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n" \
            : : "r"(M) : "$12", "$13", "$14", "memory"); \
        /* column 0: param_3 in place */ \
        __asm__ __volatile__( \
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
            : : "r"((s32)param_3) : "$12", "$13", "$14", "memory"); \
        __asm__ __volatile__( \
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
            : : "r"((s32)param_3) : "$12", "$13", "$14", "memory"); \
        /* column 1: param_3 + 2 */ \
        c = (s32)param_3 + 2; \
        __asm__ __volatile__( \
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
            : : "r"(c) : "$12", "$13", "$14", "memory"); \
        __asm__ __volatile__( \
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
            : : "r"(c) : "$12", "$13", "$14", "memory"); \
        /* column 2: param_3 + 4 */ \
        c = (s32)param_3 + 4; \
        __asm__ __volatile__( \
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n" \
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n" \
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n" \
            : : "r"(c) : "$12", "$13", "$14", "memory"); \
        __asm__ __volatile__( \
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n" \
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n" \
            : : "r"(c) : "$12", "$13", "$14", "memory"); \
        /* gte_SetTransMatrix(M) — M reloaded */ \
        M = *(s32 *)(param_1 + 0x20) + 0x34; \
        __asm__ __volatile__( \
            "lw $12, 20(%0)\n" "lw $13, 24(%0)\n" \
            "ctc2 $12, $5\n" "lw $14, 28(%0)\n" \
            "ctc2 $13, $6\n" "ctc2 $14, $7\n" \
            : : "r"(M) : "$12", "$13", "$14", "memory"); \
        /* gte_ldlv0(param_3->t) ; gte_rt() ; gte_stlvnl(param_3->t) */ \
        c = (s32)param_3 + 0x14; \
        __asm__ __volatile__( \
            "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n" \
            "sll $13, $13, 16\n" "or $12, $12, $13\n" \
            "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n" \
            "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n" \
            : : "r"(c) : "$12", "$13", "memory"); \
        __asm__ __volatile__( \
            "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n" \
            : : "r"(c) : "memory"); \
    }

#define DEFINE_func_801392FC() \
    extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80052460(s32 a0, s32 a1, s32 a2); \
    void func_801392FC(s32 arg0, s32 arg1, u8 *arg2) \
    { \
        s32 buf[16]; \
        s32 i; \
        s32 acc; \
        s32 rem; \
        u16 cnt; \
        register s32 a1c __asm__("$5"); \
        *(s32 *)((u8 *)buf + 0x00) = 0; \
        *(s16 *)((u8 *)buf + 0x0C) = GetTPage(0, 1, \
            *(s16 *)((u8 *)arg0 + 0x38) & 0xFFC0, \
            *(s16 *)((u8 *)arg0 + 0x3A) & 0xFF00); \
        *(s16 *)((u8 *)buf + 0x10) = *(u16 *)((u8 *)arg0 + 0x3C); \
        *(s16 *)((u8 *)buf + 0x12) = *(u16 *)((u8 *)arg0 + 0x3E); \
        *(u8 *)((u8 *)buf + 0x16) = 0x80; \
        *(u8 *)((u8 *)buf + 0x15) = 0x80; \
        *(u8 *)((u8 *)buf + 0x14) = 0x80; \
        i = 0; \
        cnt = *(volatile u16 *)((u8 *)arg0 + 0x2E); \
        if (*(s16 *)((u8 *)arg0 + 0x2E) > 0) { \
            s32 c12 = 0xC; \
            s32 c12ma = 0xC - arg1; \
            acc = 0; \
            do { \
                rem = (*(u16 *)((u8 *)arg0 + 0x16) + i) % ((s16)cnt + 1); \
                *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30); \
                if (i != 0) { \
                    *(s16 *)((u8 *)buf + 0x06) = (*(u16 *)((u8 *)arg0 + 0x32) + acc - arg1) + i * 2; \
                } else { \
                    *(s16 *)((u8 *)buf + 0x06) = *(u16 *)((u8 *)arg0 + 0x32); \
                } \
                if (i == 0) { \
                    *(s16 *)((u8 *)buf + 0x0A) = c12ma; \
                } else { \
                    *(s16 *)((u8 *)buf + 0x0A) = c12; \
                } \
                *(u8 *)((u8 *)buf + 0x0E) = 0; \
                if (i != 0) { \
                    s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A); \
                    *(u8 *)((u8 *)buf + 0x0F) = t; \
                } else { \
                    s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A) + arg1; \
                    *(u8 *)((u8 *)buf + 0x0F) = t; \
                } \
                *(s16 *)((u8 *)buf + 0x08) = *(u16 *)((u8 *)arg0 + 0x34); \
                func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A)); \
                acc += 0xC; \
                i++; \
                cnt = *(volatile u16 *)((u8 *)arg0 + 0x2E); \
            } while (i < *(s16 *)((u8 *)arg0 + 0x2E)); \
        } \
        if (arg1 != 0) { \
            s16 w; \
            rem = (*(u16 *)((u8 *)arg0 + 0x16) + i) % (*(s16 *)((u8 *)arg0 + 0x2E) + 1); \
            *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30); \
            *(s16 *)((u8 *)buf + 0x06) = (*(u16 *)((u8 *)arg0 + 0x32) + i * 12) - arg1 + i * 2; \
            *(s16 *)((u8 *)buf + 0x0A) = arg1 - 2; \
            *(u8 *)((u8 *)buf + 0x0E) = 0; \
            { \
                s32 t = rem * 12 + *(u8 *)((u8 *)arg0 + 0x3A); \
                *(u8 *)((u8 *)buf + 0x0F) = t; \
            } \
            w = *(s16 *)((u8 *)arg0 + 0x34); \
            if (w >= 0xFD) { \
                *(s16 *)((u8 *)buf + 0x08) = 0x100; \
                func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A)); \
                { \
                    s32 t2; \
                    *(s16 *)((u8 *)buf + 0x04) = *(u16 *)((u8 *)arg0 + 0x30) + *(u16 *)((u8 *)buf + 0x08); \
                    *(s16 *)((u8 *)buf + 0x08) = 0x20; \
                    *(u8 *)((u8 *)buf + 0x0E) = rem << 5; \
                    t2 = (*(s16 *)((u8 *)arg0 + 0x2E) + 1) * 12 + *(u8 *)((u8 *)arg0 + 0x3A); \
                    *(u8 *)((u8 *)buf + 0x0F) = t2; \
                } \
                a1c = (s32)arg2; \
                func_80052460((s32)buf, a1c, *(u16 *)((u8 *)arg0 + 0x1A)); \
            } else { \
                *(s16 *)((u8 *)buf + 0x08) = w; \
                func_80052460((s32)buf, (s32)arg2, *(u16 *)((u8 *)arg0 + 0x1A)); \
            } \
        } \
    }

#define DEFINE_func_8013A530() \
    extern void *memcpy(void *, const void *, u32); \
    extern void func_80015D4C(); \
    extern void func_80015F04(); \
    extern void func_8013AA24(s32 a0, s32 a1); \
    void func_8013A530(int param_1) \
    { \
        int iVar11; \
        u16 uVar2; \
        int sVar2; \
        register u8 bVar1 __asm__("$8"); \
        int deadlocal[2]; \
        iVar11 = *(int *)(param_1 + 4); \
        uVar2 = *(u16 *)(iVar11 + 0x18); \
        sVar2 = uVar2; \
        bVar1 = *(u8 *)(iVar11 + 0x22); \
        if (uVar2 != 0 && uVar2 < 7) { \
            if (uVar2 != 1) { \
                if (sVar2 != 0 && sVar2 < 7) { \
                    register u32 f34 __asm__("$5"); \
                    u32 uVar2b; \
                    u32 uVar6; \
                    short sVar5; \
                    register int fc __asm__("$5"); \
                    register int zr __asm__("$0"); \
                    int iVar7; \
                    f34 = *(u16 *)(iVar11 + 0x34); \
                    uVar6 = f34 + 0x10; \
                    uVar2b = *(u16 *)(iVar11 + 0x36) + 0x10; \
                    if (*(u8 *)(iVar11 + 0x20) != 0) { \
                        uVar6 = f34 + 0x38; \
                    } \
                    sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x28) * (uVar6 & 0xffff)) / 0x9a); \
                    *(s16 *)(param_1 + 8) = sVar5; \
                    if ((bVar1 & 8) == 0) { \
                        *(s16 *)(param_1 + 8) = -sVar5; \
                    } \
                    if ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0) { \
                        *(s16 *)(param_1 + 8) = -*(s16 *)(param_1 + 8); \
                    } \
                    sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x2a) * (uVar2b & 0xffff)) / 0x2a); \
                    *(s16 *)(param_1 + 0xa) = sVar5; \
                    if ((bVar1 & 0x10) != 0) { \
                        *(s16 *)(param_1 + 0xa) = -sVar5; \
                    } \
                    __asm__("" :: "r"(bVar1)); \
                    fc = *(s16 *)(param_1 + 0xc); \
                    iVar7 = fc + zr; \
                    if (fc < *(s16 *)(param_1 + 0xe)) { \
                        int t = iVar7 + 0x400; \
                        *(s16 *)(param_1 + 0xc) = (short)t; \
                        if (((t << 16) >> 16) > (int)*(s16 *)(param_1 + 0xe)) { \
                            *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe); \
                        } \
                    } else if (*(s16 *)(param_1 + 0xe) < fc) { \
                        int t = iVar7 - 0x400; \
                        __asm__("" :: "r"(iVar7), "r"(t)); \
                        *(s16 *)(param_1 + 0xc) = (short)t; \
                        if (((t << 16) >> 16) < (int)*(s16 *)(param_1 + 0xe)) { \
                            *(s16 *)(param_1 + 0xc) = *(s16 *)(param_1 + 0xe); \
                        } \
                    } \
                    __asm__("" :: "r"(fc)); \
                    func_8013AA24(iVar11, param_1); \
                } \
            } else { \
                int iVar7, iVar8; \
                u32 uVar6, uVar4; \
                memcpy((void *)(param_1 + 8), (void *)(iVar11 + 0x28), 4); \
                uVar6 = ((*(s16 *)(iVar11 + 0x34) + 0x10) * (int)*(s16 *)(param_1 + 8)) >> 0xc; \
                uVar4 = ((*(s16 *)(iVar11 + 0x36) + 0x10) * (int)*(s16 *)(param_1 + 0xa)) >> 0xc; \
                iVar7 = *(u16 *)(iVar11 + 0x24) - ((uVar6 & 0xffff) >> 1); \
                iVar8 = *(u16 *)(iVar11 + 0x26) - ((uVar4 & 0xffff) >> 1); \
                func_80015F04((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4, \
                              0xb3, 0x99, 0x4c, *(u16 *)(iVar11 + 0x1a), 4); \
                func_80015F04((int)(s16)(iVar7 + 1), (int)(s16)(iVar8 + 1), \
                              (int)(s16)(uVar6 - 2), (int)(s16)(uVar4 - 2), \
                              0xe6, 0xcc, 0x73, *(u16 *)(iVar11 + 0x1a), 4); \
                func_80015D4C((int)(s16)iVar7, (int)(s16)iVar8, (int)(s16)uVar6, (int)(s16)uVar4, \
                              0xff, 0xe6, 0x99, *(u16 *)(iVar11 + 0x1a), 4); \
            } \
        } \
        return; \
    }

#define DEFINE_func_8013AF20() \
    extern void *func_80010A08(s32); \
    void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4) \
    { \
        u32 *puVar3; \
        u32 *puVar4; \
        u32 *puVar5; \
        s32 iVar8; \
        s32 j; \
        puVar3 = (u32 *)func_80010A08(0x168); \
        puVar4 = (u32 *)func_80010A08(0x1e0); \
        puVar5 = (u32 *)func_80010A08(0x1e0); \
        iVar8 = 0; \
        j = 0; \
        do { \
            *(u8 *)((s32)puVar4 + 3) = 3; \
            *(u8 *)((s32)puVar4 + 7) = 0x40; \
            *(u8 *)((s32)puVar4 + 4) = 0x3d; \
            *(u8 *)((s32)puVar4 + 5) = 0x3d; \
            *(u8 *)((s32)puVar4 + 6) = 0x3d; \
            *(u16 *)((s32)puVar4 + 8) = param_3[j]; \
            *(u16 *)((s32)puVar4 + 0xa) = param_3[j + 1]; \
            iVar8 = iVar8 + 1; \
            *(u16 *)((s32)puVar4 + 0xc) = param_3[j + 2]; \
            *(u16 *)((s32)puVar4 + 0xe) = param_3[j + 3]; \
            j += 2; \
            /* addPrim(param_1, puVar4): setaddr(p, getaddr(ot)), setaddr(ot, p) */ \
            ((P_TAG *)puVar4)->addr = ((P_TAG *)param_1)->addr; \
            ((P_TAG *)param_1)->addr = (u32)puVar4; \
            puVar4 = puVar4 + 4; \
        } while (iVar8 < 0x1e); \
        iVar8 = 0; \
        j = 0; \
        do { \
            iVar8 = iVar8 + 1; \
            *(u8 *)((s32)puVar5 + 3) = 3; \
            *(u8 *)((s32)puVar5 + 7) = 0x40; \
            *(u8 *)((s32)puVar5 + 4) = 0x92; \
            *(u8 *)((s32)puVar5 + 5) = 0x92; \
            *(u8 *)((s32)puVar5 + 6) = 0x92; \
            *(u16 *)((s32)puVar5 + 8) = param_3[j] + (s8)param_4[j]; \
            *(u16 *)((s32)puVar5 + 0xa) = param_3[j + 1] + (s8)param_4[j + 1]; \
            *(u16 *)((s32)puVar5 + 0xc) = param_3[j + 2] + (s8)param_4[j + 2]; \
            *(u16 *)((s32)puVar5 + 0xe) = param_3[j + 3] + (s8)param_4[j + 3]; \
            j += 2; \
            ((P_TAG *)puVar5)->addr = ((P_TAG *)param_1)->addr; \
            ((P_TAG *)param_1)->addr = (u32)puVar5; \
            puVar5 = puVar5 + 4; \
        } while (iVar8 < 0x1e); \
        iVar8 = 0; \
        j = 0; \
        do { \
            *(u8 *)((s32)puVar3 + 3) = 5; \
            *(u8 *)((s32)puVar3 + 7) = 0x28; \
            *(u8 *)((s32)puVar3 + 4) = 0xff; \
            *(u8 *)((s32)puVar3 + 5) = 0xff; \
            *(u8 *)((s32)puVar3 + 6) = 0xff; \
            *(u16 *)((s32)puVar3 + 8) = param_3[j]; \
            *(u16 *)((s32)puVar3 + 0xa) = param_3[j + 1]; \
            *(u16 *)((s32)puVar3 + 0xc) = param_2[0]; \
            *(u16 *)((s32)puVar3 + 0xe) = param_2[1]; \
            *(u16 *)((s32)puVar3 + 0x10) = param_3[j + 2]; \
            *(u16 *)((s32)puVar3 + 0x12) = param_3[j + 3]; \
            iVar8 = iVar8 + 2; \
            *(u16 *)((s32)puVar3 + 0x14) = param_3[j + 4]; \
            *(u16 *)((s32)puVar3 + 0x16) = param_3[j + 5]; \
            j += 4; \
            ((P_TAG *)puVar3)->addr = ((P_TAG *)param_1)->addr; \
            ((P_TAG *)param_1)->addr = (u32)puVar3; \
            puVar3 = puVar3 + 6; \
        } while (iVar8 < 0x1e); \
    }

#define DEFINE_func_801571C4() \
    extern s32 func_80135004(s32 a0, void *a1, s32 a2); \
    extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_8014C918(s32 a0, s32 a1); \
    extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4); \
    extern u8 D_801202A0[]; \
    extern u8 D_801152A8[]; \
    extern u8 D_80126720[]; \
    u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12) \
    { \
      s16 sp18[4]; \
      u16 local_40; \
      u16 local_38; \
      u32 local_30; \
      u32 ret; \
      u32 counter; \
      u32 s4val; \
      s32 off; \
      s32 r; \
      ret = 0; \
      ; \
      local_38 = a10; \
      r = ((s32 (*)(s32, s32, s32))func_80135004)(1, a3, a4); \
      if (r != 0) \
      { \
        *((u8 *) a11) = (*((u16 *) (a4 + 6))) >> 13; \
        *((u8 *) a12) = *((u16 *) (a4 + 6)); \
        ret = 2; \
        __builtin_memcpy((void *) a6, D_801152A8, 8); \
      } \
      counter = 0; \
      s4val = a1; \
      local_30 = a2 & 0x8000; \
      off = 0; \
      do \
      { \
        u8 *e = &D_801202A0[off]; \
        s32 a1v; \
        if (((((((*((u16 *) e)) != 0) && ((a1v = *((s32 *) (e + 0x58))) != 0)) && (((*((u32 *) (e + 0x5c))) & 0x8100) == 0x8000)) && ((*((u16 *) (e + 0x5e))) != 10)) && (((a9 & 0x80) != 0) || ((*((u16 *) (e + 0x5e))) != s4val))) && ((s4val != 0xd) || (((*((u16 *) (e + 0x5c))) & 0x2000) != 0))) \
        { \
          if (func_80135260(*((s32 *) (e + 0x20)), a1v, a3, a4) != 0) \
          { \
            if ((((*((u16 *) (e + 0x5c))) & 0x4000) != 0) || (((*((s16 *) (e + 0xae))) & local_38) != 0)) \
            { \
              *((u8 *) a11) = func_8014C918(a0, *((u8 *) (e + 0x75))); \
              *((u8 *) a12) = 0; \
              __builtin_memcpy((void *) a6, D_801152A8, 8); \
              ret |= 4; \
              *((s32 *) a7) = (s32) e; \
            } \
            else \
            { \
              __builtin_memcpy(sp18, (void *) a4, 8); \
              if (local_30 != 0) \
              { \
                sp18[3] = 1; \
              } \
              else \
              { \
                sp18[3] = 0; \
              } \
              func_8014C4AC((s32) e, a1, a2 & 0x7fff, sp18, *((s16 *) ((*((s32 *) (a0 + 0x20))) + 0x12))); \
              __builtin_memcpy((void *) a5, D_801152A8, 8); \
              *((s32 *) a7) = (s32) e; \
              __builtin_memcpy((void *) a8, D_80126720, 8); \
              ret |= 1; \
              if ((a9 & 0x7f) != 0) \
              { \
                return ret; \
              } \
            } \
          } \
        } \
        counter += 1; \
        off += 0x10c; \
      } \
      while (counter < 0x60); \
    __asm__ volatile("" : "=r"(local_40)); \
      return ret; \
    }

#define DEFINE_func_8014EA4C() \
    extern u8 D_801202A0[]; \
    extern u16 D_800B99DA; \
    extern s32 D_801150D8; \
    extern s16 D_801152AA; \
    extern u8 D_80126720[]; \
    extern s16 D_80126724; \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3) \
    { \
        u8 buf[24]; \
        s32 acc; \
        s16 d5; \
        s16 d4; \
        s32 mode; \
        u8 *p; \
        acc = 0; \
        __builtin_memcpy(buf + 16, a2, 8); \
        d5 = 8; \
        mode = (D_800B99DA & 0x60) >> 5; \
        d4 = 8; \
        switch (mode) { \
        case 0: \
        case 1: \
            d5 = 7; \
            break; \
        case 2: \
            d4 = 7; \
            break; \
        } \
        for (p = D_801202A0; p < D_801202A0 + 0x6480; p += 0x10C) { \
            s32 *q = (s32 *)(p + 0x58); \
            if (*(u16 *)p == 0) continue; \
            if (q[0] == 0) continue; \
            if (p == *(u8 **)((u8 *)a0 + 0x178)) continue; \
            if (p == *(u8 **)((u8 *)a0 + 0x174)) continue; \
            if ((q[1] & 0x1800) == 0) continue; \
            D_801150D8 = 0; \
            if (func_80135A4C(q[-0xe], ((struct { s32 w; } *)q)->w, (s32 *)a1, (s32)a2) != 0) { \
                if ((D_801150D8 & 1) != 0) { \
                    if ((*(u16 *)(p + 0x5C) & 0x10) == 0) { \
                        if ((*(s16 *)&D_80126720) - *(s16 *)((u8 *)a1 + 0x0) >= 0) \
                            *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0) - d5; \
                        else \
                            *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0) + d5; \
                        if (D_80126724 - *(s16 *)((u8 *)a1 + 0x4) >= 0) \
                            *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4) - d4; \
                        else \
                            *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4) + d4; \
                    } \
                    acc |= 2; \
                } else { \
                    *(s16 *)((u8 *)a0 + 0x6) = *(u16 *)((u8 *)a2 + 0x0); \
                    *(s16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a2 + 0x2) + 0x10; \
                    *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a2 + 0x4); \
                    acc |= 1; \
                    if (q[0] < 0) { \
                        s32 t = D_801152AA; \
                        if (t < 0) t = -t; \
                        if (0x800 < (s16)t) { \
                            if ((*(s16 *)&D_80126720) - *(s16 *)((u8 *)a2 + 0x0) >= 0) \
                                *(s16 *)((u8 *)a0 + 0x6) = *(s16 *)((u8 *)a2 + 0x0) - d5; \
                            else \
                                *(s16 *)((u8 *)a0 + 0x6) = *(s16 *)((u8 *)a2 + 0x0) + d5; \
                            if (D_80126724 - *(s16 *)((u8 *)a2 + 0x4) >= 0) \
                                *(s16 *)((u8 *)a0 + 0xE) = *(s16 *)((u8 *)a2 + 0x4) - d4; \
                            else \
                                *(s16 *)((u8 *)a0 + 0xE) = *(s16 *)((u8 *)a2 + 0x4) + d4; \
                        } \
                    } \
                } \
            } \
        } \
        return acc; \
    }

#define DEFINE_func_80176D94() \
    extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3); \
    extern u32 func_801783D0(s32 a0, s32 a1); \
    extern void *func_801777BC(); \
    extern u16 D_8011F82C; \
    extern u16 D_8011F82A; \
    u32 *func_80176D94(void *param_1, u32 param_2, s16 param_3_) \
    { \
        register s32 c3  __asm__("$21") = 3;     /* $s5 */ \
        register s32 cad __asm__("$20") = 0xad;  /* $s4 */ \
        register s32 cff __asm__("$19") = 0xff;  /* $s3 */ \
        s32 iVar6 = (s16)param_3_;               /* -> $s1 */ \
        u32 uVar5 = iVar6 << 16;                 /* -> $s0 */ \
        void *uVar2; \
        void *u4, *u5;                           /* fresh single-set save vars (S2 boost) */ \
        u32 *puVar3; \
        s16 sVar1; \
        u32 uVar4; \
        u32 dl;                                  /* multi-set D-load var (2 sets, no boost) */ \
        s32 t; \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(param_1, uVar5 | (u16)param_2, 0x6b565040); \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 8) & 0xffff), 0x6b565808); \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x10) & 0xffff), 0x6b564060); \
        u4 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x30) & 0xffff), 0x6b563858); \
        sVar1 = (s16)func_801783D0(D_8011F82C, 4); \
        u5 = func_801777BC(u4, sVar1, (s32)((param_2 + 0x18) << 16) >> 16, iVar6, c3, cad, cff); \
        sVar1 = (s16)func_801783D0(D_8011F82A, 4); \
        puVar3 = (u32 *)func_801777BC(u5, sVar1, (s32)((param_2 + 0x38) << 16) >> 16, iVar6, c3, cad, cff); \
        dl = ((struct { u16 h; } *)&D_8011F82C)->h; \
        { u32 v0m = ((u32)(puVar3 - 5) & 0xffffff) | 0x3000000; \
          register u32 c6000 __asm__("$6") = 0x6000dcff; \
          puVar3[1] = c6000; \
          *puVar3 = v0m; } \
        uVar4 = ((iVar6 + 10) << 16) | ((param_2 + 1) & 0xffff); \
        puVar3[2] = uVar4; \
        puVar3[3] = ((s32)(dl * 0x50e6) >> 16) | 0x20000; \
        dl = ((struct { u16 h; } *)&D_8011F82A)->h; \
        puVar3[5] = ((u32)puVar3 & 0xffffff) | 0x3000000; \
        puVar3[10] = ((u32)(puVar3 + 5) & 0xffffff) | 0x3000000; \
        puVar3[6] = 0x600000ff; \
        puVar3[7] = uVar4; \
        puVar3[0xb] = 0x60000000; \
        puVar3[0xc] = ((iVar6 + 9) << 16) | (param_2 & 0xffff); \
        t = (s32)(dl * 0x50e6) >> 16; \
        puVar3[8] = t | 0x20000; \
        puVar3[0xd] = (t + 2) | 0x40000; \
        return puVar3 + 0xf; \
    }

#define DEFINE_func_80148094() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 csqrt(s32 a0); \
    extern void func_80013F3C(s32 a0); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800484EC(s32 a0, s32 a1, s32 a2); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    void func_80148094(int param_1, short *param_2, int *param_3) { \
        s32 s4 = *(int *)(param_1 + 0x20); \
        s32 out[3]; \
        s32 buf[8]; \
        s32 bp; \
        s32 t1; \
        int sVar1; \
        int fac; \
        int r; \
        if (*param_2 != 0 || param_2[2] != 0) { \
            t1 = ratan2(-(int)param_2[2], -(int)*param_2) + 0x400; \
            bp = (s32)buf; \
            func_80013F3C(bp); \
            func_80012558(bp, (s32)*(short *)(s4 + 0x12)); \
            func_800484EC(bp, param_1 + 0x24, (s32)out); \
            sVar1 = (s16)func_80012A60((s16)t1, (s16)(ratan2(out[2], out[0]) + 0x400)); \
            out[0] = *(int *)(param_1 + 0x24); \
            if (out[0] < 0) out[0] = -out[0]; \
            out[2] = *(int *)(param_1 + 0x2c); \
            if (out[2] < 0) out[2] = -out[2]; \
            { \
                int q = csqrt((int)*param_2 * (int)*param_2 + (int)param_2[2] * (int)param_2[2]); \
                if (q < 0) q += 0x3f; \
                fac = ratan2((int)param_2[1], q >> 6); \
            } \
            if (sVar1 < 0x200) { \
                __asm__("" :: "r"(fac)); /* L1: +1 flow-ref on fac (already live-through here); zero bytes */ \
                if (out[0] == out[2]) { \
                    r = *(int *)(param_1 + 0x24) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[0] = r >> 10; \
                    out[1] = 0; \
                    r = *(int *)(param_1 + 0x2c) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[2] = r >> 10; \
                } else if (out[0] > out[2]) { \
                    r = *(int *)(param_1 + 0x24) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[0] = r >> 10; \
                    out[1] = 0; \
                    out[2] = *(int *)(param_1 + 0x2c); \
                } else { \
                    out[0] = *(int *)(param_1 + 0x24); \
                    out[1] = 0; \
                    r = *(int *)(param_1 + 0x2c) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[2] = r >> 10; \
                } \
            } else if (sVar1 >= 0x201) { /* L2: ==0x200 arm must be the LAST (fall-through) block */ \
                if (out[0] == out[2]) { \
                    r = *(int *)(param_1 + 0x24) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[0] = *(int *)(param_1 + 0x24) + (r >> 10); \
                    out[1] = 0; \
                    r = *(int *)(param_1 + 0x2c) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[2] = *(int *)(param_1 + 0x2c) + (r >> 10); \
                } else if (out[0] > out[2]) { \
                    r = *(int *)(param_1 + 0x24) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[0] = *(int *)(param_1 + 0x24) + (r >> 10); \
                    out[1] = 0; \
                    out[2] = *(int *)(param_1 + 0x2c); \
                } else { \
                    out[0] = *(int *)(param_1 + 0x24); \
                    out[1] = 0; \
                    r = *(int *)(param_1 + 0x2c) * -fac; \
                    if (r < 0) r += 0x3ff; \
                    out[2] = *(int *)(param_1 + 0x2c) + (r >> 10); \
                } \
            } else { \
                out[0] = *(int *)(param_1 + 0x24); /* L3: out[0] store before out[1]=0 (delay-fill) */ \
                out[1] = 0; \
                out[2] = *(int *)(param_1 + 0x2c); \
            } \
            param_3[0] = out[0]; \
            param_3[1] = out[1]; \
            param_3[2] = out[2]; \
            return; \
        } \
        param_3[0] = *(int *)(param_1 + 0x24); \
        param_3[1] = *(int *)(param_1 + 0x28); \
        param_3[2] = *(int *)(param_1 + 0x2c); \
    }

#define DEFINE_func_801770E0() \
    extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3); \
    extern u32 func_801783D0(s32 a0, s32 a1); \
    extern void *func_801777BC(); \
    extern u16 D_8011F830; \
    extern u16 D_8011F82E; \
    u32 *func_801770E0(void *param_1, u32 param_2, s16 param_3_) \
    { \
        register s32 c3  __asm__("$21") = 3;     /* $s5 */ \
        register s32 cb8 __asm__("$20") = 0xb8;  /* $s4 */ \
        register s32 cff __asm__("$19") = 0xff;  /* $s3 */ \
        s32 iVar6 = (s16)param_3_;               /* -> $s1 */ \
        u32 uVar5 = iVar6 << 16;                 /* -> $s0 */ \
        void *uVar2; \
        void *u4, *u5;                           /* fresh single-set save vars (S2 boost) */ \
        u32 *puVar3; \
        s16 sVar1; \
        u32 uVar4; \
        u32 dl;                                  /* multi-set D-load var (2 sets, no boost) */ \
        s32 t; \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(param_1, uVar5 | (u16)param_2, 0x6e165010); \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 8) & 0xffff), 0x6e165808); \
        uVar2 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x10) & 0xffff), 0x6e164060); \
        u4 = ((void * (*)(void *, s32, s32))func_80177784)(uVar2, uVar5 | ((param_2 + 0x30) & 0xffff), 0x6e163858); \
        sVar1 = (s16)func_801783D0(D_8011F830, 4); \
        u5 = func_801777BC(u4, sVar1, (s32)((param_2 + 0x18) << 16) >> 16, iVar6, c3, cb8, cff); \
        sVar1 = (s16)func_801783D0(D_8011F82E, 4); \
        puVar3 = (u32 *)func_801777BC(u5, sVar1, (s32)((param_2 + 0x38) << 16) >> 16, iVar6, c3, cb8, cff); \
        dl = ((struct { u16 h; } *)&D_8011F830)->h; \
        { u32 v0m = ((u32)(puVar3 - 5) & 0xffffff) | 0x3000000; \
          register u32 c6055 __asm__("$6") = 0x6055ff00; \
          puVar3[1] = c6055; \
          *puVar3 = v0m; } \
        uVar4 = ((iVar6 - 4) << 16) | ((param_2 + 1) & 0xffff); \
        puVar3[2] = uVar4; \
        puVar3[3] = ((s32)(dl * 0x50e6) >> 16) | 0x20000; \
        dl = ((struct { u16 h; } *)&D_8011F82E)->h; \
        puVar3[5] = ((u32)puVar3 & 0xffffff) | 0x3000000; \
        puVar3[10] = ((u32)(puVar3 + 5) & 0xffffff) | 0x3000000; \
        puVar3[6] = 0x60ff3214; \
        puVar3[7] = uVar4; \
        puVar3[0xb] = 0x60000000; \
        puVar3[0xc] = ((iVar6 - 5) << 16) | (param_2 & 0xffff); \
        t = (s32)(dl * 0x50e6) >> 16; \
        puVar3[8] = t | 0x20000; \
        puVar3[0xd] = (t + 2) | 0x40000; \
        return puVar3 + 0xf; \
    }

#define DEFINE_func_801372B0() \
    extern void ApplyMatrixSV(void *m, Svec_801372B0 *in, Svec_801372B0 *out); \
    extern void aGsSortLine(Gline_801372B0 *p, void *ot, s32 z) __asm__("GsSortLine"); \
    extern void aF80137030(s32 x, s32 y) __asm__("func_80137030"); \
    extern void func_80137178(s32 x, s32 y); \
    extern u8  D_800B9A11; \
    extern u8  D_800AF630[]; \
    extern u16 aD800B9A02 __asm__("D_800B9A02"); \
    extern u8  D_800A6518[]; \
    void func_801372B0(void) { \
        Svec_801372B0 in; \
        Svec_801372B0 out; \
        Gline_801372B0 prim; \
        register u8 *mat __asm__("$23") = D_800AF630;            /* $s7 = base; +0x18 after branch */ \
        register s32 white __asm__("$19");                       /* $s3, assigned lazily in-if */ \
        register s16 ax __asm__("$16");                          /* $s0 = out.vx+0x7B */ \
        register s16 ay __asm__("$17");                          /* $s1 = out.vx+0x75 */ \
        register s16 bx __asm__("$18");                          /* $s2 = out.vy-0x57 */ \
        register s16 by __asm__("$20");                          /* $s4 = out.vy-0x5D */ \
        in.vz = 0; \
        in.vy = 0; \
        in.vx = 0; \
        if (D_800B9A11 != 1) { \
            mat += 0x18;                                         /* addiu $s7, $s7, 0x18 (post-branch) */ \
            white = 0xFF; \
            /* --- corner 0: +X axis, white line from (0x78,-0x5A) --- */ \
            in.vx = 0x10; \
            ApplyMatrixSV(mat, &in, &out); \
            { \
                register s16 vx __asm__("$7") = out.vx;          /* $a3 */ \
                register s16 vy __asm__("$3") = out.vy;          /* $v1 */ \
                prim.attr = 0;                                   /* LEVER B: colors BEFORE x0 here — */ \
                prim.r = white; prim.g = white; prim.b = white;  /* drops the sb LUIDs below the x0  */ \
                prim.x0 = 0x78;                                  /* store -> white's S2 boost fires  */ \
                prim.y0 = -0x5A;                                 /* late -> li $s3,0xFF lands @31    */ \
                { s16 x1v = vx + 0x78; __asm__("" : "=r"(x1v) : "0"(x1v)); prim.x1 = x1v; } \
                { s16 y1v = vy - 0x5A; __asm__("" : "=r"(y1v) : "0"(y1v)); prim.y1 = y1v; } \
                aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0); \
            } \
            /* --- corner 1: +X +6, red cross --- */ \
            in.vx = in.vx + 6; \
            ApplyMatrixSV(mat, &in, &out); \
            prim.attr = 0; \
            prim.r = white; prim.g = 0; prim.b = 0; \
            bx = out.vy;                                         /* $s2 = out.vy (load) */ \
            ay = out.vx;                                         /* $s1 = out.vx (load) */ \
            by = bx - 0x5D;                                      /* $s4 = out.vy - 0x5D */ \
            ax = ay + 0x7B;                                      /* $s0 = out.vx + 0x7B */ \
            bx = bx - 0x57;                                      /* $s2 = out.vy - 0x57 (in place) */ \
            { \
            Gline_801372B0 *op = (Gline_801372B0*)&D_800A6518[(u32)aD800B9A02 * 0x14]; \
            __asm__("" : "=r"(op) : "0"(op)); \
            ay = ay + 0x75;                                      /* $s1 = out.vx + 0x75 (in place) */ \
            prim.x0 = ay; prim.y0 = by; prim.x1 = ax; prim.y1 = bx; \
            aGsSortLine(&prim, op, 0); \
            } \
            __asm__("" : "=r"(ax) : "0"(ax));                    /* LEVER A: 2nd set kills ax's S2   */ \
            __asm__("" : "=r"(by) : "0"(by));                    /* boost (same for by) -> by/ax/bx/ */ \
            prim.attr = 0;                                       /* chain/ay revert to source order  */ \
            prim.r = white; prim.g = 0; prim.b = 0; \
            prim.x0 = ax; prim.y0 = by; prim.x1 = ay; prim.y1 = bx; \
            aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0); \
            /* --- corner 2: +Y axis, white line + sibling 030 --- */ \
            in.vx = 0; \
            in.vy = 0x10; \
            ApplyMatrixSV(mat, &in, &out); \
            { \
                register s16 vx __asm__("$7") = out.vx;          /* $a3 */ \
                register s16 vy __asm__("$2") = out.vy;          /* $v0 */ \
                prim.x0 = 0x78; \
                prim.attr = 0; \
                prim.r = white; prim.g = white; prim.b = white; \
                prim.y0 = -0x5A; \
                { s16 x1v = vx + 0x78; __asm__("" : "=r"(x1v) : "0"(x1v)); prim.x1 = x1v; } \
                { s16 y1v = vy - 0x5A; __asm__("" : "=r"(y1v) : "0"(y1v)); prim.y1 = y1v; } \
                aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0); \
            } \
            in.vy = in.vy + 6; \
            ApplyMatrixSV(mat, &in, &out); \
            aF80137030((s32)(s16)(out.vx + 0x78), (s32)(s16)(out.vy - 0x5A)); \
            /* --- corner 3: +Z axis, white line + sibling 178 --- */ \
            in.vy = 0; \
            in.vz = 0x10; \
            ApplyMatrixSV(mat, &in, &out); \
            { \
                register s16 vx __asm__("$7") = out.vx;          /* $a3 */ \
                register s16 vy __asm__("$2") = out.vy;          /* $v0 */ \
                prim.x0 = 0x78; \
                prim.attr = 0; \
                prim.r = white; prim.g = white; prim.b = white; \
                prim.y0 = -0x5A; \
                { s16 x1v = vx + 0x78; __asm__("" : "=r"(x1v) : "0"(x1v)); prim.x1 = x1v; } \
                { s16 y1v = vy - 0x5A; __asm__("" : "=r"(y1v) : "0"(y1v)); prim.y1 = y1v; } \
                aGsSortLine(&prim, &D_800A6518[(u32)aD800B9A02 * 0x14], 0); \
            } \
            in.vz = in.vz + 6; \
            ApplyMatrixSV(mat, &in, &out); \
            func_80137178((s32)(s16)(out.vx + 0x78), (s32)(s16)(out.vy - 0x5A)); \
        } \
        return; \
    }

#define DEFINE_func_80174650() \
    extern s32 D_801270BC; \
        extern s32 D_801150F8; \
        s32 func_80174650(s32 _arg0) \
    { \
            D_801270BC = D_801270BC | 1; \
            D_801150F8 = 0; \
        }

#define DEFINE_func_8014C8C8() \
    void func_8014C8C8(s32 dst, s32 * src) \
    { \
        *(struct up *)(dst + 0x15c) = *(struct up *)(src + 0); \
        *(s16 *)(dst + 0x162) = 0; \
    }

#define DEFINE_func_8012C098() \
    extern void func_8012C218(void *a0); \
    void func_8012C098(void *param_1) \
    { \
        int iVar1; \
        iVar1 = *(int *)((char *)param_1 + 0x68); \
        if ((iVar1 != 0) && ((*(short *)((char *)param_1 + 0x72) & 0x8000) != 0)) { \
            *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7fff; \
        } \
        func_8012C218(param_1); \
        return; \
    }

#define DEFINE_func_8012F14C() \
    extern void func_8004914C(void *a0); \
    extern void func_800491AC(void *a0); \
    extern void RotTransSV(s32 a0, s32 a1, void *a2); \
    void func_8012F14C(s32 a0, s32 a1, s32 a2) \
    { \
        s32 buf[2]; \
        func_8004914C((void *)a0); \
        func_800491AC((void *)a0); \
        RotTransSV(a1, a2, buf); \
    }

#define DEFINE_func_80157158() \
    void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, \
                       s32 a4, s32 a5, s32 a6, s32 a7, \
                       s32 a8, s32 a9, u16 a10, s32 a11, s32 a12) { \
        func_801571C4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); \
    }

#define DEFINE_func_8012F038() \
    extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2); \
    void func_8012F038(int param_1, short *param_2, short *param_3) { \
        int in[3]; \
        int out[3]; \
        in[0] = (int)param_2[0] - *(int *)(param_1 + 0x14); \
        in[1] = (int)param_2[1] - *(int *)(param_1 + 0x18); \
        in[2] = (int)param_2[2] - *(int *)(param_1 + 0x1c); \
        ApplyTransposeMatrixLV((void *)param_1, in, out); \
        param_3[0] = out[0]; \
        param_3[1] = out[1]; \
        param_3[2] = out[2]; \
    }

#define DEFINE_func_8014964C() \
    extern void func_8012F14C(s32); \
    extern void func_8012EFB8(s32 a0); \
    void func_8014964C(s32 param_1, s32 param_2) { \
        Vec3 in; \
        Vec3 out; \
        s32 mid[2]; \
        register s32 p2 __asm__("$16"); \
        Vec3 *pin; \
        s32 *m1; \
        s32 *m2; \
        s32 mtx; \
        p2 = param_2; \
        in.f0 = *(s16 *)(p2 + 2); \
        in.f2 = *(s16 *)(p2 + 6); \
        in.f4 = *(s16 *)(p2 + 0xA); \
        pin = &in; \
        __asm__ __volatile__("" : "=r"(pin) : "0"(pin)); \
        mtx = *(s32 *)(param_1 + 0x20); \
        __asm__ __volatile__("" : "=r"(mtx) : "0"(mtx)); \
        m1 = mid; \
        __asm__ __volatile__("" : "=r"(m1) : "0"(m1)); \
        ((void (*)(s32, Vec3 *, s32 *))func_8012F14C)(mtx + 0x34, pin, m1); \
        m2 = mid; \
        __asm__ __volatile__("" : "=r"(m2) : "0"(m2)); \
        ((void (*)(s32 *, Vec3 *))func_8012EFB8)(m2, &out); \
        *(s16 *)(p2 + 2) = out.f0; \
        *(s16 *)(p2 + 6) = out.f2; \
        *(s16 *)(p2 + 0xA) = out.f4; \
    }

#define DEFINE_func_8012C0EC() \
    extern s32 D_801274D4; \
    extern s16 D_80126CAC; \
    extern s32 D_801274E0; \
    extern s32 func_80013478(s32 a0, s32 a1); \
    extern void func_8012C218(void *a0); \
    s32 func_8012C0EC(s32 a0) { \
        s32 (*fp)(s32) = (s32 (*)(s32))D_801274D4; \
        s32 cond; \
        s32 *p; \
        if (fp == 0) { \
            cond = (func_80013478(a0 + 4, (s32)&D_80126CAC) < D_801274E0) ^ 1; \
        } else { \
            cond = fp(a0); \
        } \
        if (cond == 0) { \
            return 0; \
        } \
        p = *(s32 **)(a0 + 0x68); \
        if (p != 0) { \
            if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) { \
                *(u16 *)((s32)p + 0xA) = *(u16 *)((s32)p + 0xA) & 0x7FFF; \
            } \
        } \
        func_8012C218((void *)a0); \
        return 1; \
    }

#define DEFINE_func_8012E5CC() \
    extern u8 D_800AF648; \
    extern void func_8004914C(void *a0); \
    extern void func_800491AC(void *a0); \
    extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3); \
    extern void func_8002D4C8(s32 a0, s32 a1); \
    void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3) \
    { \
        struct { short xy[2]; int sp14; int flag; } f; \
        register void *p __asm__("$4"); \
        p = &D_800AF648; \
        func_8004914C(p); \
        func_800491AC(&D_800AF648); \
        RotTransPers(param_1, (s32)f.xy, &f.sp14, &f.flag); \
        if (f.flag >= 0 && (u16)(f.xy[0] + 199) < 399 && (u16)(f.xy[1] + 0xA9) < 0x153) { \
            func_8002D4C8(param_2, param_3); \
        } \
    }

#define DEFINE_func_8012C750() \
    extern u8 D_80120194[]; \
    extern u8 D_801202A0[]; \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    s32 func_8012C750(s32 a0) \
    { \
        s32 p; \
        s32 it; \
        s32 v0; \
        if (*(u16 *)(a0 + 0xA) & 0x800) { \
            s32 base = (s32)D_80120194; \
            p = base + 0x6480; \
            if (p != base) { \
                do { \
                    if (*(u16 *)p == 0) goto found; \
                    p -= 0x10C; \
                } while (p != base); \
            } \
            p = 0; \
            goto found; \
        } else { \
            it = (s32)D_80120194; \
            __asm__ __volatile__("" : "=r"(it) : "0"(it)); \
            p = it + 0x658C; \
            goto test; \
        copy: \
            p = it; \
            goto found; \
        test: \
            it = (s32)D_801202A0; \
            __asm__ __volatile__("" : "=r"(it) : "0"(it)); \
            if (it == p) goto zero; \
        body: \
            if (*(u16 *)it == 0) goto copy; \
            it += 0x10C; \
            if (it != p) goto body; \
        zero: \
            p = 0; \
        } \
    found: \
        if (p == 0) { \
            v0 = 0; \
        } else { \
            *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000; \
            v0 = func_8012C890(a0, p, 0); \
        } \
        return v0; \
    }

#define DEFINE_func_80128ED8() \
    s32 func_80128ED8(s32 param_1, s32 *param_2) { \
        register s32 iVar4 __asm__("$8");   /* base ptr, lives whole fn in $t0 */ \
        register s32 cnt   __asm__("$2");   /* decremented count in $v0 */ \
        register s32 cc    __asm__("$3");   /* preserved count copy in $v1 (forces the bne-delay-slot copy) */ \
        register s32 idx   __asm__("$3");   /* offset-4 index, loaded into $v1 */ \
        register s32 idc   __asm__("$7");   /* $a3: preserved idx copy, forced SEPARATE from the multiply */ \
        u32 uVar3; \
        s32 frame_pad[4];                   /* phantom 0x10 frame the target reserves (induce via clobber anchor) */ \
        __asm__ __volatile__("" : : "r"(&frame_pad) : "memory"); \
        iVar4 = *param_2; \
        cnt = *(s16 *)((s32)param_2 + 6); \
        if (cnt == 0) { \
            return 1; \
        } \
        cc = cnt; \
        __asm__ __volatile__("" : "=r"(cc) : "0"(cc));   /* force the count-preserve copy ($v1=$v0) */ \
        cnt = cc - 1; \
        *(s16 *)((s32)param_2 + 6) = (s16)cnt; \
        if (cnt * 0x10000 < 1) { \
            idx = *(s16 *)((s32)param_2 + 4); \
            __asm__ __volatile__("" : "=r"(idx) : "0"(idx));   /* pin the index into $v1 */ \
            uVar3 = *(u32 *)(idx * 8 + iVar4 + 4); \
            idc = idx; \
            if ((uVar3 & 0xc0) == 0xc0) { \
                *(s16 *)((s32)param_2 + 6) = 0; \
                return 1; \
            } \
            if ((uVar3 & 0x80) != 0) { \
                *(s16 *)((s32)param_2 + 4) = 0; \
            } else { \
                cnt = idc + 1;                       /* reuse the dead $v0 pin so idc+1 lands in $v0, not $a3 */ \
                *(s16 *)((s32)param_2 + 4) = cnt; \
            } \
            *(u16 *)((s32)param_2 + 6) = \
                (u16)(*(u32 *)((s16)param_2[1] * 8 + iVar4 + 4) & 0x3f); \
            *(u16 *)(param_1 + 0x28) = *(u16 *)((s16)param_2[1] * 8 + iVar4); \
            *(u16 *)(param_1 + 0x2a) = *(u16 *)((s16)param_2[1] * 8 + iVar4 + 2); \
        } \
        return 0; \
    }

#define DEFINE_func_80177EA4() \
    uint *func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4) \
    { \
        uint uVar1; \
        register int iVar2 __asm__("$4"); \
        register uint *p1 __asm__("$9"); \
        register uint *puVar3 __asm__("$8"); \
        register int iVar4 __asm__("$10"); \
        register uint uVar5 __asm__("$11"); \
        register uint mask __asm__("$12"); \
        register int nx __asm__("$2"); \
        register int p4s __asm__("$7"); \
        int cont; \
        p1 = param_1; uVar5 = 0x1000000; iVar4 = 0; mask = 0xffffff; \
        p4s = param_4 << 0x10; \
        puVar3 = p1 + 3; \
        do { \
            register uint c74 __asm__("$4"); \
            register uint c3 __asm__("$3"); \
            register uint m __asm__("$2"); \
            c74 = 0x74808080; \
            m = (uint)(p1 + -5) & mask; \
            __asm__ __volatile__("" : "=r"(m) : "0"(m)); \
            c3 = 0x3000000; \
            *p1 = m | c3; \
            puVar3[-2] = c74; \
            if ((short)iVar4 != 0) { \
                register int six __asm__("$2"); \
                six = 6; \
                if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; } \
                else { \
                    register int t __asm__("$2"); \
                    t = param_2 >> 0x10 & 0xf; \
                    iVar2 = t + 1; \
                    param_2 = param_2 << 4; \
                } \
                { \
                    register int iv2c __asm__("$3"); \
                    register int one __asm__("$2"); \
                    iv2c = iVar2; \
                    __asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c)); \
                    one = 1; \
                    if (iv2c != one) uVar5 = 0; \
                } \
                uVar1 = p4s | (param_3 & 0xffff) | uVar5; \
            } else { iVar2 = 0; uVar1 = p4s | (param_3 & 0xffff); } \
            puVar3[-1] = uVar1; \
            __asm__ __volatile__("" : : "r"(iVar2) : "memory"); \
            { \
                register uint c6b __asm__("$3"); \
                register uint r __asm__("$2"); \
                c6b = 0x6b564000; \
                r = (uint)(iVar2 << 3) | c6b; \
                *puVar3 = r; \
            } \
            puVar3 = puVar3 + 5; p1 = p1 + 5; param_3 = param_3 + 8; \
            { \
                register int sx __asm__("$2"); \
                nx = iVar4 + 1; \
                iVar4 = nx; \
                sx = nx << 0x10; \
                cont = (sx >> 0x10) < 7; \
            } \
        } while (cont); \
        return p1; \
    }

#define DEFINE_func_8016A8FC() \
    extern s32 func_80016A5C(); \
    extern Blk20 D_800AE620; \
    s32 func_8016A8FC(s32 a0) \
    { \
        Prim p; \
        int ptr; \
        ptr = *(int *)(a0 + 0x34); \
        p.v0 = (short)*(int *)(a0 + 0x4C); \
        p.v1 = (short)*(int *)(a0 + 0x50); \
        p.v2 = (short)*(int *)(a0 + 0x54); \
        p.w0 = *(unsigned short *)(ptr + 6); \
        p.w1 = *(unsigned short *)(ptr + 0xA); \
        p.w2 = *(unsigned short *)(ptr + 0xE); \
        p.v0 = (short)(((int)*(short *)(a0 + 6) + *(int *)(a0 + 0x4C)) >> 1); \
        p.v1 = (short)(((int)*(short *)(a0 + 0xA) + *(int *)(a0 + 0x50)) >> 1); \
        p.v2 = (short)(((int)*(short *)(a0 + 0xE) + *(int *)(a0 + 0x54)) >> 1); \
        *(short *)(a0 + 6) = (short)*(int *)(a0 + 0x4C); \
        p.w0 = (short)(((int)*(short *)(a0 + 6) + (int)*(short *)(ptr + 6)) >> 1); \
        *(int *)(a0 + 0x4C) = p.w0; \
        *(short *)(a0 + 0xA) = (short)*(int *)(a0 + 0x50); \
        p.w1 = (short)(((int)*(short *)(a0 + 0xA) + (int)*(short *)(ptr + 0xA)) >> 1); \
        *(int *)(a0 + 0x50) = p.w1; \
        *(short *)(a0 + 0xE) = (short)*(int *)(a0 + 0x54); \
        p.w2 = (short)(((int)*(short *)(a0 + 0xE) + (int)*(short *)(ptr + 0xE)) >> 1); \
        *(int *)(a0 + 0x54) = p.w2; \
        p.b11 = 0x10; \
        p.b15 = 0x80; \
        p.b16 = 0x20; \
        p.b14 = 0x20; \
        p.b12 = 0; \
        p.b10 = 0; \
        p.w18 = 0x50000000; \
        ((s32 (*)(void *, void *))func_80016A5C)(&p, &D_800AE620); \
    }

#define DEFINE_func_8014A048() \
    extern u8 func_8014BEF8(void); \
    extern void func_8012F14C(s32); \
    extern s32 func_80135260(s32, s32, s32, s32); \
    extern void func_8014A1B0(s32 a0, s32 a1); \
    extern u8 D_801202A0[]; \
    s32 func_8014A048(s32 param_1) { \
        Loc L; \
        s32 s0; \
        s32 s2; \
        u32 s3; \
        if ((*(u32 *)(param_1 + 0x44) & 0x400) != 0) { \
            return 0; \
        } \
        if ((*(u16 *)(param_1 + 0xAC) & 0x80) == 0) { \
            if ((*(u16 *)(param_1 + 0xAC) & 0x10) == 0) { \
                return 0; \
            } \
            if (((s32 (*)(s32))func_8014BEF8)(param_1) == 0) { \
                goto ret0; \
            } \
        } \
        L.a30 = *(s16 *)(param_1 + 6); \
        L.a2e = *(s16 *)(param_1 + 0xA); \
        L.a2c = *(s16 *)(param_1 + 0xE); \
        L.a1e = -0x10; \
        L.a20 = 0; \
        L.a1c = -0x20; \
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&L.a20, (s32)L.buf); \
        s3 = 0; \
        s2 = 0; \
        while (1) { \
            s0 = (s32)D_801202A0 + s2; \
            __asm__ __volatile__("" : "=r"(s0) : "0"(s0)); \
            if ((*(u16 *)s0 != 0) && \
                (*(s32 *)(s0 + 0x58) != 0) && \
                (*(s16 *)(s0 + 0xAA) == 0) && \
                (*(s32 *)(param_1 + 0x184) != s0) && \
                ((*(u16 *)(s0 + 0x5C) & 0x200) != 0) && \
                (((s32 (*)(s32, s32, s32, s32))func_80135260)(*(s32 *)(s0 + 0x20), *(s32 *)(s0 + 0x58), (s32)&L.a30, (s32)L.buf) != 0)) { \
                break; \
            } \
            s3++; \
            s2 += 0x10C; \
            if (s3 >= 0x60) { \
                return 0; \
            } \
        } \
        *(s32 *)(param_1 + 0x178) = s0; \
        func_8014A1B0(param_1, s0); \
        return 1; \
    ret0: \
        return 0; \
    }

#define DEFINE_func_801678F0() \
    extern s32 rand(void); \
    extern void RotMatrixYXZ(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6); \
    extern void func_80146C3C(void); \
    extern u16 D_800B99DA; \
    void func_801678F0(s32 a0) { \
        s32 p; \
        s32 r; \
        s16 buf[4]; \
        p = *(s32 *)(a0 + 0x34); \
        if ((*(s32 *)(p + 0x44) & 0x10) != 0) { \
            if (*(s16 *)(a0 + 0x12) > *(s16 *)(a0 + 0x10)) { \
                if (*(s32 *)(a0 + 0x1C) > 0) { \
                    *(u16 *)(a0 + 0x10) = rand() & 0x30; \
                    *(s32 *)(a0 + 0x1C) = -0x30; \
                } \
            } else { \
                if (*(s32 *)(a0 + 0x1C) < 0) { \
                    *(u16 *)(a0 + 0x10) = (rand() & 0x30) + 0x40; \
                    *(s32 *)(a0 + 0x1C) = 0x30; \
                } \
            } \
            *(s16 *)(a0 + 0x12) = *(u16 *)(a0 + 0x12) + *(s32 *)(a0 + 0x1C); \
            if (*(s32 *)(a0 + 0x30) != 0) { \
                *(s32 *)(a0 + 0x30) = *(s32 *)(a0 + 0x30) - 0xC0; \
            } \
            buf[0] = 0x400; \
            buf[1] = 0; \
            buf[2] = D_800B99DA << 8; \
            RotMatrixYXZ((void *)buf, (void *)(a0 + 0x38)); \
            ((void (*)(s32, s32))func_80048EAC)(*(s32 *)(p + 0x20) + 0x34, a0 + 0x38); \
            func_801670E4(a0, -6, -0x44, -0x18); \
            r = ((s32 (*)(s32, s32, s32, s32, s32, s32, s32))func_80146A6C)(0xE, a0, *(s16 *)(a0 + 6), *(s16 *)(a0 + 0xA), *(s16 *)(a0 + 0xE), 0, 0); \
            if (r != 0) { \
                *(Blk32 *)(r + 0x38) = *(Blk32 *)(a0 + 0x38); \
            } \
        } else { \
            ((void (*)(s32))func_80146C3C)(a0); \
        } \
    }

#define DEFINE_func_8014DD8C() \
    s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2) { \
        extern u8 D_801202A0[]; \
        extern u8 D_80126720[]; \
        extern s32 ratan2(s32 a0, s32 a1); \
        extern s32 func_80012A60(s32 a0, s32 a1); \
        extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
        s16 temp_s0; \
        s32 temp_s0_2; \
        s16 temp_s1; \
        s16 temp_v0; \
        s16 temp_v1; \
        s32 temp_a1; \
        s8 *var_s2; \
        s8 *var_s3; \
        __asm__ __volatile__("" :: "r"(((void *)arg0))); \
        temp_v0 = M2C_FIELD(arg2, u16 *, 0) - M2C_FIELD(arg1, u16 *, 0); \
        temp_v1 = M2C_FIELD(arg2, u16 *, 4) - M2C_FIELD(arg1, u16 *, 4); \
        if (((temp_v0 | temp_v1) << 0x10) != 0) { \
            var_s3 = (s8 *) D_801202A0; \
            if (var_s3 < var_s3 + 0x6480) { \
                var_s2 = var_s3 + 0xE; \
                __asm__ __volatile__("" :: "r"(var_s2)); \
    loop_3: \
                if (M2C_FIELD(var_s3, u16 *, 0) != 0) { \
                    temp_a1 = M2C_FIELD(var_s2, s32 *, 0x4A); \
                    if ((temp_a1 != 0) && (M2C_FIELD(var_s2, u16 *, 0x4E) & 0x1000) && (func_80135A4C(M2C_FIELD(var_s2, s32 *, 0x12), temp_a1, (s32 *)arg1, (s32)arg2) != 0)) { \
                        temp_s1 = M2C_FIELD(var_s2, u16 *, -8) - M2C_FIELD(((void *)arg0), u16 *, 6); \
                        temp_s0 = M2C_FIELD(var_s2, u16 *, 0) - M2C_FIELD(((void *)arg0), u16 *, 0xE); \
                        temp_s0_2 = (s16) ratan2(temp_v1, temp_v0); \
                        if ((s16) func_80012A60(temp_s0_2, (s16) ratan2(temp_s0, temp_s1)) < 0x400) { \
                            M2C_FIELD(((void *)arg0), s8 **, 0x170) = var_s3; \
                            M2C_FIELD(((void *)arg0), u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 0); \
                            M2C_FIELD(((void *)arg0), s16 *, 0xA) = (s16) (M2C_FIELD(arg2, u16 *, 2) + 0x10); \
                            M2C_FIELD(((void *)arg0), u16 *, 0xE) = (u16) M2C_FIELD(arg2, u16 *, 4); \
                            return 1; \
                        } \
                    } \
                } \
                var_s3 += 0x10C; \
                var_s2 += 0x10C; \
                if ((u32) var_s3 >= (u32) D_80126720) { \
                    goto block_10; \
                } \
                goto loop_3; \
            } \
            return 0; \
        } \
    block_10: \
        return 0; \
    }

#define DEFINE_func_8017C710() \
    int func_8017C710(short *param_1, short *param_2, short *param_3, int param_4) { \
        register int i2o __asm__("$5"); \
        register int i4o __asm__("$9"); \
        short sVar1; int rx, rz, uVar5; \
        i4o = param_2[1]; \
        __asm__ __volatile__("" : : "r"(i4o)); \
        i2o = param_1[1]; uVar5 = 0; \
        if (i2o >= i4o) { \
            rx = param_1[0] - i2o * (param_2[0] - param_1[0]); \
            rz = param_1[2] - i2o * (param_2[2] - param_1[2]); \
        } else { \
            register int den __asm__("$3"); \
            int p2x = param_2[0], p2z = param_2[2]; \
            den = i2o - i4o; \
            rx = p2x + i4o * (p2x - param_1[0]) / den; \
            rz = p2z + i4o * (p2z - param_1[2]) / den; \
        } \
        if (rx >= -0x7fff) { i2o = 0x7fff; if (rx < 0x8000) i2o = rx; } \
        else i2o = -0x7fff; \
        *param_3 = (short)i2o; \
        if (rz >= -0x7fff) { i2o = 0x7fff; if (rz < 0x8000) i2o = rz; } \
        else i2o = -0x7fff; \
        param_3[2] = (short)i2o; param_3[1] = 0; sVar1 = (short)param_4; \
        if ((int)*param_3 < *param_1 - param_4) { uVar5 = 0xffffffff; *param_3 = *param_1 - sVar1; } \
        if (*param_1 + param_4 < (int)*param_3) { uVar5 = 0xffffffff; *param_3 = *param_1 + sVar1; } \
        if ((int)param_3[2] < param_1[2] - param_4) { uVar5 = 0xffffffff; param_3[2] = param_1[2] - sVar1; } \
        if (param_1[2] + param_4 < (int)param_3[2]) { uVar5 = 0xffffffff; param_3[2] = param_1[2] + sVar1; } \
        return uVar5; \
    }

#define DEFINE_func_80130650() \
    extern void func_801319E0(s32 a0); \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_8012CBF4(s32); \
    extern s32 func_80131D68(s32 a0, s32 a1); \
    extern void func_80131C78(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_80130650(s32 a0) { \
        s32 s1; \
        if (*(s32 *)(a0 + 0xB4) & 0x1000) { \
            if (*(s16 *)(a0 + 0xA) >= 0x10) { \
                func_801319E0(a0); \
                return; \
            } \
            if (func_8012BEE8(a0) != 0) { \
                func_801319E0(a0); \
                return; \
            } \
            if (*(s32 *)(a0 + 0xC4) & 0x4) { \
                s32 v1 = *(s32 *)(a0 + 0x20); \
                *(s16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x100; \
            } \
            s1 = ((s32 (*)(s32))func_8012CBF4)(a0); \
            if (func_80131D68(a0, s1) == 1) { \
                return; \
            } \
            if (s1 & 0x2000) { \
                func_80131C78(a0); \
            } \
        } \
        func_80131CA8(a0, 0x23); \
    }

#define DEFINE_func_80149450() \
    extern void func_8012F038(s32); \
    void func_80149450(s32 a0, s16 *a1) { \
        s16 *s0 = a1; \
        s16 sp10[3]; \
        s16 sp18[3]; \
        sp18[0] = *(u16 *)((char *)s0 + 0x2); \
        sp18[1] = *(u16 *)((char *)s0 + 0x6); \
        sp18[2] = *(u16 *)((char *)s0 + 0xA); \
        ((void (*)(s32, s32, s32))func_8012F038)(*(s32 *)(a0 + 0x20) + 0x34, (s32)sp18, (s32)sp10); \
        *(s16 *)((char *)s0 + 0x2) = *(u16 *)((char *)sp10 + 0x0); \
        *(s16 *)((char *)s0 + 0x6) = *(u16 *)((char *)sp10 + 0x2); \
        *(s16 *)((char *)s0 + 0xA) = *(u16 *)((char *)sp10 + 0x4); \
    }

#define DEFINE_func_80174684() \
    extern u8 D_80126D6C; \
    extern void (*D_80127088)(void); \
    extern s32 D_801270BC; \
    void func_80174684(void* a0) \
    { \
        D_80126D6C = 0; \
        (*(void * *)&D_80127088) = a0; \
        D_801270BC = 0; \
    }

#define DEFINE_func_80129C40() \
    extern struct BigCopy D_80126DB8; \
    extern u8 D_80126948[]; \
    extern struct BigCopy D_80114EE8; \
    extern s32 D_80126E60[]; \
    extern s8 D_801150D6; \
    extern s8 D_801152C0; \
    extern u8 D_80127504; \
    extern void func_80016714(void *a0, s32 a1); \
    extern void func_800144D4(void); \
    void func_80129C40(s32 _arg0) \
    { \
        func_80016714(((u8 *)&D_80126DB8), 0xA4); \
        func_80016714(D_80126948, 0xA4); \
        func_80016714(((u8 *)&D_80114EE8), 0xA4); \
        func_80016714(((u8 *)&D_80114EE8) + 0xA4, 0xA4); \
        func_80016714(((u8 *)&D_80114EE8) + 0x148, 0xA4); \
        func_80016714(((u8 *)D_80126E60), 0xA4); \
        func_80016714(((u8 *)D_80126E60) + 0xA4, 0xA4); \
        func_80016714(((u8 *)D_80126E60) + 0x148, 0xA4); \
        D_801150D6 = 0; \
        D_801152C0 = 0; \
        (*(s8 *)&D_80127504) = 0; \
        func_800144D4(); \
    }

#define DEFINE_func_8012A6D0() \
    extern s32 func_80047D3C(s32 a0); \
    extern s32 ratan2(s32 a0, s32 a1); \
    s32 func_8012A6D0(void* a0, void* a1) \
    { \
        s32 s0 = a0; \
        s32 s1 = a1; \
        s32 dy = *(s16 *)(s0 + 0x4) - *(s16 *)(s1 + 0x4); \
        s32 dx = *(s16 *)(s0 + 0x0) - *(s16 *)(s1 + 0x0); \
        s32 d; \
        d = func_80047D3C(dy * dy + dx * dx); \
        return (s16)ratan2(*(s16 *)(s0 + 0x2) - *(s16 *)(s1 + 0x2), (s16)d); \
    }

#define DEFINE_func_80130A18() \
    extern void func_80131CA8(int, int); \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    void func_80130A18(u8 *a0) { \
        s16 b1[4]; \
        s16 b2[4]; \
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE; \
        if (((s32 (*)(int, int))func_80131CA8)((int)a0, 0x34) != 0) { \
            return; \
        } \
        b1[0] = *(u16 *)(a0 + 6); \
        b1[1] = *(u16 *)(a0 + 0xA) - 0x10; \
        b1[2] = *(u16 *)(a0 + 0xE); \
        b2[0] = *(u16 *)(a0 + 6); \
        b2[1] = *(u16 *)(a0 + 0xA) + 8; \
        b2[2] = *(u16 *)(a0 + 0xE); \
        if ((func_80133784(0x11, b1, (s32)b2) & 0x6000) != 0) { \
            *(s8 *)(a0 + 0xC1) = 0x11; \
            *(s16 *)(a0 + 0xAC) = 0x78; \
        } \
    }

#define DEFINE_func_80131D68() \
    extern void func_80131E00(struct S80131E00 *a0, s32 a1); \
    extern void func_80131CA8(int, int); \
    extern void func_8002A04C(s32 a0); \
    extern void func_8012C218(void *a0); \
    int func_80131D68(int a0, int a1) \
    { \
        s32 s0 = a0; \
        s32 c = a1 & 0xFF; \
        if (c == 2 || c == 0x1B) { \
            func_80131E00((struct S80131E00 *)s0, 0x12); \
            return 1; \
        } \
        if (c == 0x1A || c == 0x1C) { \
            if (((s32 (*)(int, int))func_80131CA8)(s0, 0x11) != 0) { \
                return 1; \
            } \
            if (*(s32 *)(s0 + 0x78) != 0) { \
                func_8002A04C(s0); \
            } \
            func_8012C218((void *)s0); \
            return 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80136DFC() \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    extern s32 *D_80126B78; \
    extern u16 D_80126CC4; \
    extern M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); \
    void func_80136DFC(void) { \
        ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xA, (*(s16 *)&D_80126B5E), 0x110, 0x3C, 4, 0); \
        ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xB, (*(s16 *)&D_80126B62), 0x110, 0x44, 4, 0); \
        ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xC, (*(s16 *)&D_80126B66), 0x110, 0x4C, 4, 0); \
        ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xD, *(s16 *)((s32)D_80126B78 + 0x12), 0x110, 0x54, 4, 0); \
        ((void (*)(s32, s32, s32, s32, s32, s32))func_800153CC)(0xE, D_80126CC4, 0x110, 0x5C, 4, 0); \
    }

#define DEFINE_func_80146C3C() \
    extern void func_80016714(void *a0, s32 a1); \
    void func_80146C3C(u8 *a0) { \
        u8 *s0 = a0; \
        u16 *p = *(u16 **)(s0 + 0x20); \
        if (p != 0) { \
            s32 a1; \
            if (*p == 1) { \
                a1 = 0x84; \
            } else { \
                a1 = 0x38; \
            } \
            func_80016714(p, a1); \
        } \
        func_80016714(s0, 0x58); \
    }

#define DEFINE_func_80147F78() \
    extern void func_80147928(int a0, int a1); \
    extern void func_8014799C(int a0, int a1); \
    extern void func_80147A10(int a0, int a1); \
    extern volatile s32 D_80127090; \
    extern volatile s32 D_80127094; \
    extern volatile s32 D_80127098; \
    void func_80147F78(s32 a0, s32 a1, s32 a2, s32 a3) { \
        s32 reserved[16]; \
        s32 t; \
        func_80147928(a0, a1); \
        func_8014799C(a0, a2); \
        func_80147A10(a0, a3); \
        D_80127090 = *(s32 *)(a0 + 0x24); \
        t = D_80127090; \
        D_80127094 = *(s32 *)(a0 + 0x28); \
        D_80127098 = *(s32 *)(a0 + 0x2C); \
        *(s32 *)(a0 + 0x10) = t; \
        *(s32 *)(a0 + 0x14) = D_80127094; \
        *(s32 *)(a0 + 0x18) = D_80127098; \
        D_80127090 = 0; \
        D_80127094 = 0; \
        D_80127098 = 0; \
        (void)reserved; \
    }

#define DEFINE_func_801494CC() \
    extern void func_8012F038(s32); \
    void func_801494CC(s32 a0, u16 *a1, u16 *a2) { \
        u16 dst[3]; \
        u16 src[3]; \
        src[0] = a1[1]; \
        src[1] = a1[3]; \
        src[2] = a1[5]; \
        ((void (*)(s32, u16 *, u16 *))func_8012F038)(*(s32 *)(a0 + 0x20) + 0x34, src, dst); \
        a2[1] = dst[0]; \
        a2[3] = dst[1]; \
        a2[5] = dst[2]; \
    }

#define DEFINE_func_80149F2C() \
    extern s32 func_80144A04(s32 *a0); \
    extern void func_801599A4(void *a0); \
    extern void func_80159B3C(void *a0); \
    extern void func_8016EDEC(s32 a0, s32 a1); \
    s32 func_80149F2C(s32 a0, s32 a1) \
    { \
        void *s1 = a0; \
        s32 *s0; \
        if (*(u16 *)a1 == 0x83 || *(u16 *)a1 == 0x61) { \
            s0 = (s32 *)func_80144A04((s32 *)a1); \
            if (s0 != 0) { \
                func_801599A4(s1); \
                func_80159B3C(s1); \
                func_8016EDEC((s32)s0, 0x1000000); \
                return 1; \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_8014C1C8() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    void func_8014C1C8(s32 a0, s32 a1, void* a2) \
    { \
        s16 buf[4]; \
        s16 out[4]; \
        s32 s0 = a1; \
        buf[0] = *(u16 *)(a0 + 6); \
        buf[1] = *(u16 *)(a0 + 0xA); \
        buf[2] = *(u16 *)(a0 + 0xE); \
        out[0] = *(u16 *)(s0 + 6) + *(u16 *)(a2 + 0); \
        out[1] = *(u16 *)(s0 + 0xA) + *(u16 *)(a2 + 2); \
        out[2] = *(u16 *)(s0 + 0xE) + *(u16 *)(a2 + 4); \
        if (func_80133784(1, buf, (s32)out) != 0) { \
            *(s16 *)(s0 + 6) = out[0]; \
            *(s16 *)(s0 + 0xA) = out[1]; \
            *(s16 *)(s0 + 0xE) = out[2]; \
        } \
    }

#define DEFINE_func_80152C80() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_80152C80(s32* a0) \
    { \
        s32 s0 = a0; \
        func_8014BC44(s0, *(s16 *)(s0 + 0xF2)); \
        *(s8 *)(s0 + 0xA8) = 0x20; \
        func_80154A74(s0, 0x11); \
        func_801553C0(s0); \
        func_801470AC((s32 *)s0); \
        func_801472B4((void *)s0); \
        *(s16 *)(s0 + 0x3E) = 0; \
        *(s16 *)(s0 + 0x40) = 0; \
        *(s16 *)(s0 + 0x42) = 0; \
        *(s8 *)(s0 + 0xDD) = 0; \
        *(s16 *)(s0 + 0x3C) = *(u16 *)(s0 + 0x3C) & 0xFFFE; \
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0; \
        *(s16 *)(s0 + 0x60) = 0x1000; \
        *(s16 *)(s0 + 0x62) = 0x1000; \
        *(s16 *)(s0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)s0, 0); \
        func_80153C18(s0); \
    }

#define DEFINE_func_801719A4() \
    extern void *D_8011F738; \
    void func_801719A4(int a0, int a1) \
    { \
        u32 i; \
        s32 off; \
        s32 pad[1]; \
        for (i = 0; i < a1; i++) { \
            off = i * 4; \
            *(s32*)((s32)&D_8011F738 + off) = \
                *(s32*)(((*(u8*)(a0 + 0x214) + i) << 2) + *(s32*)(a0 + 0x1FC)); \
        } \
        *(u8*)(a0 + 0x214) += i; \
    }

#define DEFINE_func_80173BC0() \
    extern s16 D_80126B3A; \
    extern struct S80126B38 D_80126B38; \
    extern s16 D_8011F9C8; \
    extern s32 func_800D0EC4(void); \
    extern void func_8013E588(void*); \
    extern s32 func_80174650(s32); \
    extern void func_80171A34(s32 *a0, s8 a1); \
    extern void func_80171A1C(u8 *a0); \
    void func_80173BC0(u8* a0) \
    { \
        s32 v = D_80126B3A; \
        if (v != 0 && v < 0x6F && func_800D0EC4() == 0) { \
            if ((*(s16 *)&D_80126B38) & 0x8000) { \
                ((void (*)(void))func_8013E588)(); \
            } else { \
                func_80174650((s32)a0); \
                D_8011F9C8 = 2; \
                func_80171A34(a0, 7); \
                return; \
            } \
        } \
        func_80171A1C((u8 *)a0); \
    }

#define DEFINE_func_80173CB4() \
    extern s16 func_80171AB0(s32 a0, void *a1); \
    extern void func_8014706C(void *a0); \
    extern void func_80154274(s32 *a0, s32 a1); \
    extern void func_801553A8(s32 *a0); \
    extern void func_8016BADC(void *a0, s32 a1, s32 a2); \
    extern void func_80147324(s32 a0); \
    extern s32 func_8013767C(s32 a0); \
    extern void func_80171A1C(u8 *a0); \
    extern s32 D_801151D4; \
    extern struct S80126B38 D_80126B38; \
    extern u8 D_800D5DA8; \
    extern u8 D_800D5DB8; \
    extern s32 D_8012750C; \
    void func_80173CB4(s32 a0) { \
        s32 s0 = a0; \
        s32 v1 = D_801151D4; \
        s16 tmp[4]; \
        s32 a; \
        s32 d; \
        tmp[0] = *(s32 *)(v1 + 0x3C); \
        tmp[1] = *(s32 *)(v1 + 0x40); \
        tmp[2] = *(s32 *)(v1 + 0x44); \
        if (func_80171AB0(a0, tmp) != 0) { \
            return; \
        } \
        func_8014706C((void *)s0); \
        switch ((u8)(*(u8 *)&D_80126B38)) { \
        case 0: \
            func_80154274((s32 *)s0, (s32)&D_800D5DA8); \
            *(s32 *)(s0 + 0x200) = 0x20; \
            a = 0x843; \
            goto ld0; \
        case 1: \
            func_80154274((s32 *)s0, (s32)&D_800D5DA8); \
            goto lb8; \
        case 2: \
            func_80154274((s32 *)s0, (s32)&D_800D5DA8); \
            __asm__ __volatile__(""); \
            goto lb8; \
        case 3: \
            func_80154274((s32 *)s0, (s32)&D_800D5DB8); \
            func_801553A8((s32 *)s0); \
            goto lb8; \
        default: \
            goto ld8; \
        } \
    lb8: \
        func_8016BADC((void *)s0, -0x40, 0x40); \
        *(s32 *)(s0 + 0x200) = 0x80; \
        a = 0x6A6; \
    ld0: \
        func_80147324(a); \
    ld8: \
        d = D_8012750C; \
        if (d != 0) { \
            *(s32 *)(s0 + 0x198) = func_8013767C(d); \
        } else { \
            *(s32 *)(s0 + 0x198) = 0; \
        } \
        func_80171A1C((u8 *)s0); \
    }

#define DEFINE_func_8014ADE0() \
    extern u8 D_80078E78[]; \
    extern s32 func_8016F1C4(void); \
    extern s32 func_8014B154(s32 *a0); \
    extern void func_8014BD24(s32 a0, s32 a1); \
    extern void func_8014BB24(s32 a0, s32 a1, s32 a2); \
    extern void func_8014BC80(s32 a0, s32 a1); \
    extern void func_8014BD60(s32 a0, s32 a1); \
    extern void func_8014B084(void); \
    extern s32 func_80029178(s32 a0); \
    void func_8014ADE0(s32 a0) \
    { \
        /* BLOCK-scope extern: the s32 view of the accumulator. The only file-scope decl of \
         * this symbol in the TU is `extern s16 D_80078E90;` from DEFINE_func_8014B034(), \
         * instantiated at line 1166 — AFTER our slot at 1162 — so gcc-2.7.2 emits only \
         * "warning: type mismatch with previous external decl" (probe-verified, exit 0, no \
         * -Werror in the build) instead of a hard `conflicting types` error. Unlike \
         * `*(s32*)&D_80078E90`, this keeps the symbol_ref INSIDE the mem so each access folds \
         * to `lui %hi / lw %lo`; taking the address instead materializes it and CSE hoists it \
         * into a reg across all 4 uses (§18 &sym trap) — measured, it shifts ~100 insns. */ \
        extern s32 D_80078E90; \
        register u8 *p __asm__("$17") = D_80078E78; \
        s32 temp_s2; \
        s32 var_a1; \
        if (func_8016F1C4() != 0) { \
            return; \
        } \
        if ((*(u16 *)a0 == 0x1A) || (*(u16 *)a0 == 0x1E) || (*(s32 *)(a0 + 0x44) & 0x10)) { \
            return; \
        } \
        temp_s2 = D_80078E90; \
        if (func_8014B154((s32 *)a0) != 0) { \
            D_80078E90 = D_80078E90 + 0xAAA8; \
        } else { \
            D_80078E90 = D_80078E90 + 0x1555; \
        } \
        if ((*(s16 *)(p + 0x1A) - (temp_s2 >> 16)) > 0) { \
            if (p[0x49] == 3) { \
                func_8014BD24(a0, 1); \
            } \
        } \
        if (((s16)(*(s16 *)(p + 0x1A) / 60) - (s16)((s16)(temp_s2 >> 16) / 60)) > 0) { \
            if (func_8014B154((s32 *)a0) == 0) { \
                var_a1 = 4; \
            } else if (func_80029178(0x1B) & 0xFF) { \
                var_a1 = 0xA; \
            } else { \
                var_a1 = 4; \
            } \
            if (*(u16 *)(p + 0x40) != 0) { \
                func_8014BB24(a0, var_a1, 0); \
            } else if (*(u16 *)(p + 0x3C) != 0) { \
                if (*(u16 *)(p + 0x3C) >= 5U) { \
                    func_8014BC80(a0, 4); \
                } else { \
                    *(u16 *)(p + 0x3C) = 1; \
                } \
            } \
            if (func_8014B154((s32 *)a0) != 0) { \
                if (func_80029178(0x1B) & 0xFF) { \
                    func_8014BD24(a0, 8); \
                } else { \
                    func_8014BD60(a0, 1); \
                } \
            } else { \
                func_8014BD60(a0, 4); \
            } \
        } \
        if (*(s16 *)(p + 0x1A) >= 0x5A0) { \
            *(s32 *)(p + 0x18) = 0; \
            func_8014B084(); \
        } \
    }

#define DEFINE_func_801325B8() \
    extern void memcpy(); \
    extern void gteMIMefunc(); \
    void func_801325B8(int dst, int src, int m0, int mm, int arg5) \
    { \
        register int p __asm__("$4"); \
        register int m __asm__("$16"); \
        register int n __asm__("$17"); \
        register int dv __asm__("$18"); \
        int sv; \
        int ofs; \
        int c; \
        m = m0; \
        p = src; \
        if (*(int *)(p + 4) == 1) { \
            sv = *(int *)(p + 0xC); \
        } else { \
            ofs = (int)((*(unsigned int *)(p + 0xC) >> 2) << 2) + 0xC; \
            sv = p + ofs; \
        } \
        p = dst; \
        sv += *(int *)(m + 8) * 8; \
        if (*(int *)(p + 4) == 1) { \
            dv = *(int *)(p + 0xC); \
        } else { \
            ofs = (int)((*(unsigned int *)(p + 0xC) >> 2) << 2) + 0xC; \
            dv = p + ofs; \
        } \
        c = *(int *)(m + 8); \
        dv += c * 8; \
        n = *(int *)(m + 0xC); \
        m += 0x10; \
        memcpy(dv, sv, n * 8); \
        gteMIMefunc(dv, m, n, arg5); \
        if (mm != 0) { \
            m = mm; \
            p = src; \
            if (*(int *)(p + 4) == 1) { \
                sv = *(int *)(p + 0x14); \
            } else { \
                ofs = (int)((*(unsigned int *)(p + 0x14) >> 2) << 2) + 0xC; \
                sv = p + ofs; \
            } \
            p = dst; \
            sv += *(int *)(m + 8) * 8; \
            if (*(int *)(p + 4) == 1) { \
                dv = *(int *)(p + 0x14); \
            } else { \
                ofs = (int)((*(unsigned int *)(p + 0x14) >> 2) << 2) + 0xC; \
                dv = p + ofs; \
            } \
            c = *(int *)(m + 8); \
            dv += c * 8; \
            n = *(int *)(m + 0xC); \
            m += 0x10; \
            memcpy(dv, sv, n * 8); \
            gteMIMefunc(dv, m, n, arg5); \
        } \
    }

#define DEFINE_func_801387B8() \
    void func_801387B8(s32 arg0) { \
        extern s32 func_80138DE0(s32, s32, s32); \
        extern s32 func_80139220(s32 a0); \
        extern void func_80138948(void *a0); \
        extern void func_80139A8C(s32 a0); \
        extern void func_80139B18(s32 a0); \
        extern s32 D_80127530[]; \
        u16 *p; \
        s32 base; \
        s32 cont; \
        u8 cmd; \
        s32 sub; \
        s32 pc; \
        for (;;) { \
            cont = 0; \
            if (*(s32 *)(arg0 + 8) & 0x400) { \
                base = D_80127530[*(u16 *)(arg0 + 0x4A)]; \
                p = (u16 *)(arg0 + 0x44); \
            } else { \
                p = (u16 *)(arg0 + 0x10); \
                base = *(s32 *)(arg0 + 0); \
            } \
            pc = *p; \
            cmd = *(u8 *)(base + pc); \
            sub = *(u8 *)(base + pc + 1); \
            if (cmd >= 0x20) { \
                cont = func_80138DE0(arg0, cmd, sub); \
                if (!(*(s32 *)(arg0 + 8) & 0x80220)) { \
                    cont = 0; \
                } \
            } else { \
                if (cmd != 0) { \
                    switch (cmd) { \
                    case 10: \
                        func_80139220(arg0); \
                        *p += 1; \
                        goto loop_end; \
                    case 1: \
                        cont = 1; \
                        *(u8 *)(arg0 + 0x23) = sub; \
                        *p += 2; \
                        goto loop_end; \
                    case 7: \
                        if (!(*(s32 *)(arg0 + 8) & 0x20000)) { \
                            *(s32 *)(arg0 + 8) &= ~0x20; \
                        } \
                        break; \
                    case 23: \
                        *(s32 *)(arg0 + 8) |= 2; \
                    default: \
                        cont = 1; \
                        *p += 1; \
                        goto loop_end; \
                    } \
                } \
                func_80138948((void *)arg0); \
            } \
        loop_end: \
            if (cont == 0) { \
                func_80139A8C(arg0); \
                func_80139B18(arg0); \
                return; \
            } \
        } \
    }

#define DEFINE_func_8014F4C0() \
    extern s32 func_80133784(s32 a0, void *a1, s32 a2); \
    extern s32 func_80029178(s32 arg); \
    extern int func_8014F74C(); \
    extern u8 D_800D3918[]; \
    extern u8 D_801152A8[]; \
    extern s16 D_801152B0; \
    extern s32 D_801152BC; \
    s32 func_8014F4C0(s32 arg0) \
    { \
        PosT  sp10; \
        MoveT sp18; \
        u16 x6, xA, xE; \
        s32 ret; \
        if (*(s16 *)(arg0 + 0x146) != 0) { \
            return func_8014F74C(); \
        } \
        sp10.x = *(u16 *)(arg0 + 0x88); \
        sp10.y = *(u16 *)(arg0 + 0x8A); \
        sp10.z = *(u16 *)(arg0 + 0x8C); \
        sp18.x = x6 = *(u16 *)(arg0 + 6); \
        sp18.y = xA = *(u16 *)(arg0 + 0xA) + 8; \
        sp18.z = xE = *(u16 *)(arg0 + 0xE); \
        if (*(s16 *)(arg0 + 0x146) != 0) { \
            sp18.x = x6 + *(u16 *)(arg0 + 0x140); \
            sp18.y = xA + *(u16 *)(arg0 + 0x142); \
            sp18.z = xE + *(u16 *)(arg0 + 0x144); \
        } \
        ret = func_80133784(0, &sp10, (s32)&sp18); \
        if (ret != 0) { \
            if (*(u8 *)&sp18.w != 0) { \
                *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w; \
            } \
            *(u16 *)(arg0 + 0x16E) = (u32)sp18.w >> 13; \
            if (ret == 0x2000) { \
                __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_801152A8, 8); \
            } else if (ret == 0x4000) { \
                __builtin_memcpy((void *)(arg0 + 0x120), (void *)&D_801152B0, 8); \
            } \
            /* NOT the sibling's `if (x != 0x1D) return ret;` early-return form — that inverts the \
             * branch polarity here (beq instead of the target's bne) and costs +2 ins. The \
             * short-circuit && is what folds the 0x1D test and the func_80029178 test into the \
             * single fallthrough chain the target uses. */ \
            if (*(u16 *)(arg0 + 0x16C) == 0x1D && (func_80029178(0x21) & 0xFF) == 0) { \
                ret &= ~0x2000; \
                ret |= 0x4000; \
                __builtin_memcpy((void *)&D_801152B0, (void *)D_801152A8, 8); \
                D_801152BC = 1; \
            } \
            return ret; \
        } \
        /* ret == 0 */ \
        __builtin_memcpy((void *)(arg0 + 0x120), (void *)D_800D3918, 8); \
        if (*(u8 *)&sp18.w != 0) { \
            *(u16 *)(arg0 + 0x16C) = *(u8 *)&sp18.w; \
        } \
        return 0; \
    }

#define DEFINE_func_8014E284() \
    extern u8 D_801202A0[]; \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);  /* canonical (engine_core.h:11555) */ \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80012A60(s32 a0, s32 a1); \
    s32 func_8014E284(s32 a0, s16 *arg1, s16 *arg2) { \
        u16 *a1 = (u16 *)arg1; \
        u16 *a2 = (u16 *)arg2; \
        EntSC01077 *p; \
        s16 dx; \
        s16 dz; \
        s16 ax; \
        s16 az; \
        s32 r1; \
        s32 r2; \
        dx = a2[0] - a1[0]; \
        dz = a2[2] - a1[2]; \
        if ((s16)(dx | dz) != 0) { \
            for (p = (EntSC01077 *)D_801202A0; p < (EntSC01077 *)D_801202A0 + 96; p++) { \
                if (p->f00 == 0) continue; \
                if (p->f58 == 0) continue; \
                if ((p->f5C & 0x1000) == 0) continue; \
                /* §17a-1 fn-ptr cast: keep the canonical extern, call with the intended sig. */ \
                if (((s32 (*)(s32, s32, u16 *, u16 *))func_80135A4C)(p->f20, p->f58, a1, a2) == 0) continue; \
                ax = p->f06 - *(u16 *)(a0 + 6); \
                az = p->f0E - *(u16 *)(a0 + 0xE); \
                r1 = (s16)ratan2(dz, dx); \
                r2 = (s16)ratan2(az, ax); \
                if ((s16)func_80012A60(r1, r2) < 0x400) { \
                    *(s32 *)(a0 + 0x170) = (s32)p; \
                    *(u16 *)(a0 + 6) = a2[0]; \
                    *(u16 *)(a0 + 0xA) = a2[1] + 0x10; \
                    *(u16 *)(a0 + 0xE) = a2[2]; \
                    return 1; \
                } \
            } \
        } \
        return 0; \
    }

#define DEFINE_func_80137DD4() \
    extern void *func_80010A08(s32); \
    extern void func_80137FD8(s32 a0, s32 a1, s32 a2, s32 a3); \
    void func_80137DD4(s32 ent, u8 *arg, u8 *work) { \
        register s32 t __asm__("$4"); \
        s32 d, c, c1, sub, y; \
        u32 b; \
        P_TAG_80137DD4 *q, *r; \
        { \
            register u32 h12 __asm__("$2"), h16 __asm__("$3"); \
            h12 = *(u16 *)(ent + 0x12); \
            h16 = *(u16 *)(ent + 0x16); \
            t = h12 - h16; \
        } \
        d = t; \
        if ((s16)t < 0) { \
            register s32 e __asm__("$2"); \
            e = t + 1; \
            d = (u32)*(u16 *)(ent + 0x2e) + e; \
        } \
        b = *(volatile u8 *)(ent + 0x1f); \
        c = (s8)b; \
        sub = d - (u32)*(u8 *)(ent + 0x21); \
        c1 = c + 1; \
        y = (u32)*(u16 *)(ent + 0x32) + (s16)(sub + c1) * 0xe; \
        q = (P_TAG_80137DD4 *)func_80010A08(0x48); \
        *(u8 *)(arg + 3) = 0; \
        func_80137FD8(ent, (s32)arg, (s32)q, (s16)y); \
        q->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr; \
        ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)q; \
        q = (P_TAG_80137DD4 *)((u8 *)q + 0x24); \
        *(u8 *)(arg + 3) = 1; \
        func_80137FD8(ent, (s32)arg, (s32)q, (s16)y); \
        q->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr; \
        ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)q; \
        r = (P_TAG_80137DD4 *)func_80010A08(8); \
        r->len = 1; \
        *(u32 *)((u8 *)r + 4) = 0xe100000a; \
        r->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr; \
        ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)r; \
    }

#define DEFINE_func_80150170() \
    extern s32 func_801502EC(s32 e, void *a1, void *a2); \
    extern s32 func_80150460(s32 e, s32 a1); \
    extern u8 D_801152A8[]; \
    s32 func_80150170(void *e) { \
        u8 a[8]; \
        u8 b[8]; \
        u8 out[8]; \
        s32 r5; \
        s32 r6; \
        *(s16 *)(a + 0) = *(s16 *)(b + 0) = *(u16 *)(((s32)e) + 6); \
        *(s16 *)(a + 2) = *(s16 *)(b + 2) = *(u16 *)(((s32)e) + 0xA) - 0x10; \
        *(s16 *)(a + 4) = *(s16 *)(b + 4) = *(u16 *)(((s32)e) + 0xE); \
        r5 = func_801502EC(((s32)e), a, out); \
        r6 = func_80150460(((s32)e), (s32)b); \
        if (r6 == 0) { \
            *(s16 *)(b + 2) = 0x7fff; \
        } \
        if ((r5 | r6) != 0) { \
            if (*(s16 *)(a + 2) < *(s16 *)(b + 2)) { \
                __asm__ __volatile__("" ::: "memory"); \
                *(s16 *)(((s32)e) + 0x78) = *(u16 *)(a + 0); \
                *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(a + 2); \
                *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(a + 4); \
                __builtin_memcpy((void *)(((s32)e) + 0x80), out, 8); \
            } else { \
                __asm__ __volatile__("" ::: "memory"); \
                *(s16 *)(((s32)e) + 0x78) = *(u16 *)(b + 0); \
                *(s16 *)(((s32)e) + 0x7a) = *(u16 *)(b + 2); \
                *(s16 *)(((s32)e) + 0x7c) = *(u16 *)(b + 4); \
                __builtin_memcpy((void *)(((s32)e) + 0x80), D_801152A8, 8); \
            } \
            *(u16 *)(((s32)e) + 0x7e) &= 0xfffe; \
            return 1; \
        } \
        { \
            register s32 c __asm__("$3"); /* $v1 */ \
            register s32 t __asm__("$4"); /* $a0 */ \
            t = *(u16 *)(a + 0); \
            c = 0x7fff; \
            *(s16 *)(((s32)e) + 0x7a) = c; \
            *(s16 *)(((s32)e) + 0x78) = t; \
            t = *(u16 *)(a + 4); \
            *(s16 *)(((s32)e) + 0x7c) = t; \
            *(u16 *)(((s32)e) + 0x7e) |= 1; \
        } \
        return 0; \
    }

#define DEFINE_func_80141B90() \
    extern void func_8013FAF8(s16, s16); \
    extern short D_800B9A02; \
    extern u8 D_801151C8[]; \
    extern s32 D_801151D0; \
    extern u16 D_80115116; \
    extern u16 D_80115112; \
    extern u8 D_800B9A15; \
    void func_80141B90(void) \
    { \
      volatile char pad; \
      D_801151D0 = ((s32 *) D_801151C8)[*((u16 *) (&D_800B9A02))]; \
      ((void (*)(s32, s32))func_8013FAF8)(2, 3); \
      if (D_80115116 == 0) \
      { \
        *((s8 *) (&D_800B9A15)) = 0; \
        D_80115112 = D_80115112 + 1; \
      } \
    }

#define DEFINE_func_80167714() \
    extern void func_80146C3C(void); \
    extern void func_80147324(s32 arg0); \
    extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); \
    extern s32 rand(void); \
    void func_80167714(s32 param_1) { \
        s32 *psVar7; \
        s32 iVar2; \
        s32 src; \
        u32 uVar4; \
        psVar7 = *(s32 **)(param_1 + 0x34); \
        if (*(u16 *)psVar7 != 1) { \
            goto LAB_80167894; \
        } \
        if (*(s16 *)(param_1 + 0x12) > *(s16 *)(param_1 + 0x10)) { \
            iVar2 = *(s32 *)(param_1 + 0x1c); \
            if (iVar2 < 1) goto LAB_801677b0; \
            *(u16 *)(param_1 + 0x10) = rand() & 0x30; \
            iVar2 = -0x20; \
        } else { \
            iVar2 = *(s32 *)(param_1 + 0x1c); \
            if (-1 < iVar2) goto LAB_801677b0; \
            *(u16 *)(param_1 + 0x10) = (rand() & 0x30) + 0x40; \
            iVar2 = 0x20; \
        } \
        *(s32 *)(param_1 + 0x1c) = iVar2; \
    LAB_801677b0: \
        *(s16 *)(param_1 + 0x12) = *(u16 *)(param_1 + 0x12) + *(s32 *)(param_1 + 0x1c); \
        if ((*(u32 *)(param_1 + 0x2c) & 8) != 0) { \
            *(s32 *)(param_1 + 0x30) = *(s32 *)(param_1 + 0x30) + 0x80; \
        } else { \
            *(s32 *)(param_1 + 0x30) = *(s32 *)(param_1 + 0x30) - 0x40; \
        } \
        uVar4 = *(u32 *)(param_1 + 0x2c); \
        *(u32 *)(param_1 + 0x2c) = uVar4 + 1; \
        if ((uVar4 & 0xf) == 0) { \
            func_80147324(0x44e); \
        } \
        src = *(s32 *)((s32)psVar7 + 0x20); \
        *(Blk16 *)(param_1 + 0x38) = *(Blk16 *)(src + 0x34); \
        *(Blk16 *)(param_1 + 0x48) = *(Blk16 *)(src + 0x44); \
        func_801670E4(param_1, 0, 0, 0); \
        if ((*(u32 *)(*(s32 *)(*(s32 *)(param_1 + 0x34) + 0x4c) + 0x44) & 0x20) == 0) { \
            *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) - 1; \
        } \
        return; \
    LAB_80167894: \
        ((void (*)(s32))func_80146C3C)(param_1); \
    }

#define DEFINE_func_80165CA0() \
    void func_80165CA0(void) { \
        extern s32 D_8011D030; \
        extern s32 D_80126728; \
        register s32 i __asm__("$17"); \
        s32 off; \
        u16 *q; \
        s32 a1, base; \
        short *p; \
        register short v __asm__("$2"); \
        register short w __asm__("$3"); \
        i = 0; q = &D_8011D030; \
        do { \
            if (*q != 0) (*(void (**)(u16 *))((u32)*q * 4 + D_80126728))(q); \
            i = i + 1; q = q + 0x2c; \
        } while (i < 0x1e); \
        i = 0; off = 0; \
        do { \
            base = (s32)&D_8011D030; ENGINE_SHB(base); \
            a1 = off + base; \
            p = *(short **)(a1 + 0x20); \
            if (p != 0) { \
                s32 q2; \
                if ((u16)*p == 1) { \
                    v = *(short *)(a1 + 6); p[4] = v; ENGINE_SHB(v); *(int *)(p + 0x24) = v; \
                    v = *(short *)(a1 + 0xa); p[5] = v; ENGINE_SHB(v); *(int *)(p + 0x26) = v; \
                    w = *(short *)(a1 + 0xe); p[6] = w; v = p[0x16] | 1; ENGINE_SHB(w); p[0x16] = v; *(int *)(p + 0x28) = w; \
                } else if ((q2 = *(int *)(p + 0x1a)) != 0) { \
                    v = *(short *)(a1 + 6); p[4] = v; ENGINE_SHB(v); *(int *)(q2 + 0x14) = v; \
                    v = *(short *)(a1 + 0xa); p[5] = v; q2 = *(int *)(p + 0x1a); ENGINE_SHB(v); *(int *)(q2 + 0x18) = v; \
                    v = *(short *)(a1 + 0xe); p[6] = v; q2 = *(int *)(p + 0x1a); ENGINE_SHB(v); *(int *)(q2 + 0x1c) = v; \
                } else { \
                    p[4] = *(short *)(a1 + 6); p[5] = *(short *)(a1 + 0xa); p[6] = *(short *)(a1 + 0xe); \
                } \
            } \
            i = i + 1; off = off + 0x58; \
        } while (i < 0x1e); \
    }

#define DEFINE_func_8014CD80() \
    extern int func_80135A4C(); \
    extern int func_80135888(); \
    extern int func_8014C918(); \
    int func_8014CD80(int param_1, unsigned short *param_2, unsigned short *param_3) \
    { \
        short *psVar4; \
        register int iVar3 __asm__("$3"); \
        unsigned short uVar1; \
        unsigned short uVar2; \
        psVar4 = *(short **)(param_1 + 0x174); \
        if (*(unsigned short *)psVar4 == 0) goto LAB_ce00; \
        if (((*(unsigned short *)((int)psVar4 + 0x5c) & 0x400) == 0) || \
            (*(int *)((int)psVar4 + 0x58) == 0) || \
            (*(short *)((int)psVar4 + 0xa) < *(short *)(param_1 + 0xa))) { \
            if (*(unsigned short *)psVar4 != 0) { \
                *(char *)((int)psVar4 + 0x74) = 0; \
            } \
    LAB_ce00: \
            *(int *)(param_1 + 0x174) = 0; \
            return 0; \
        } \
        *param_2 = *(unsigned short *)(param_1 + 0x98); \
        param_2[1] = *(unsigned short *)(param_1 + 0x9a) - 3; \
        param_2[2] = *(unsigned short *)(param_1 + 0x9c); \
        if ((*(unsigned short *)((int)psVar4 + 0x5c) & 8) != 0) { \
            param_3[1] = param_2[1] + 0xc; \
            iVar3 = func_80135A4C(*(int *)((int)psVar4 + 0x20), \
                                  *(int *)((int)psVar4 + 0x58), param_2, param_3); \
            if (iVar3 == 0) goto LAB_cec4; \
            uVar1 = param_3[0]; \
            *(unsigned short *)(param_1 + 0x78) = uVar1; \
            *(unsigned short *)(param_1 + 6) = uVar1; \
            uVar1 = param_3[1]; \
            *(unsigned short *)(param_1 + 0x7a) = uVar1; \
            *(unsigned short *)(param_1 + 0xa) = uVar1; \
            uVar1 = param_3[2]; \
            *(unsigned short *)(param_1 + 0x7c) = uVar1; \
            *(unsigned short *)(param_1 + 0xe) = uVar1; \
        } else { \
            iVar3 = func_80135888(*(int *)((int)psVar4 + 0x20), \
                                  *(int *)((int)psVar4 + 0x58), param_2, param_3); \
        } \
        if (iVar3 != 0) goto LAB_ced0; \
    LAB_cec4: \
        *(char *)((int)psVar4 + 0x74) = 0; \
        *(int *)(param_1 + 0x174) = 0; \
        return 0; \
    LAB_ced0: \
        uVar2 = func_8014C918(param_1, *(unsigned char *)((int)psVar4 + 0x75)) & 0xff; \
        *(unsigned short *)(param_1 + 0x16e) = uVar2; \
        return 1; \
    }

#define DEFINE_func_80130C08() \
    extern void func_8012CBCC(s32); \
    extern void func_80131E00(struct S80131E00*, s32); \
    extern s32 func_8012BEE8(s32 a0); \
    extern void func_80131C78(s32 a0); \
    extern void func_80131CA8(int a0, int a1); \
    void func_80130C08(s32 arg0) { \
        s32 flag; \
        u32 cond; \
        flag = 0; \
        if (!(*(u32 *)(arg0 + 0xC4) & 2)) { \
            if (*(u32 *)(arg0 + 0xB4) & 0x20000) { \
                if (*(u32 *)(arg0 + 0xB4) & 1) { \
                    if ((u8)((s32 (*)(s32))func_8012CBCC)(arg0) == 2) { \
                        ((void (*)(void *, s32))func_80131E00)((void *)arg0, 0x12); \
                        return; \
                    } \
                    if (*(u8 *)(arg0 + 0xC2) != 0) { \
                        cond = func_8012BEE8(arg0); \
                    } else { \
                        cond = *(u16 *)(arg0 + 0x72) & 0x4000; \
                    } \
                    if (cond != 0) { \
                        flag = 1; \
                    } \
                    if (flag != 0) { \
                        func_80131C78(arg0); \
                    } \
                } \
                func_80131CA8(arg0, 5); \
            } \
            if (!(*(u32 *)(arg0 + 0xC4) & 2)) { \
                goto mode_38; \
            } \
        } \
        func_80131CA8(arg0, 5); \
        return; \
    mode_38: \
        func_80131CA8(arg0, 0x38); \
    }

#define DEFINE_func_80137178() \
    extern short D_800B9A02; \
    extern u8 D_800A6518[]; \
    extern void GsSortLine(void *a0, void *a1, s32 a2); \
    void func_80137178(s32 a0, s32 a1) \
    { \
        struct { \
            u32 tag; \
            s16 x0; \
            s16 y0; \
            s16 x1; \
            s16 y1; \
            u8 r; \
            u8 g; \
            u8 b; \
        } line; \
        register s16 x0    __asm__("$19");             /* $s3 */ \
        register s16 white __asm__("$17");             /* $s1 */ \
        register u8 *base  __asm__("$18") = D_800A6518; /* $s2 */ \
        s16 x1; \
        s16 y0; \
        s16 y1; \
        x0 = a0 - 3; \
        y0 = a1 - 3; \
        x1 = a0 + 3; \
        __asm__("" : "=r"(x0) : "0"(x0)); \
        y1 = a1 - 3; \
        white = 0xFF; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0; \
        line.b = white; \
        line.x0 = x0; \
        line.y0 = y0; \
        line.x1 = x1; \
        line.y1 = y1; \
        GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0); \
        y0 = a1 + 3; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0; \
        line.b = white; \
        line.x0 = x0; \
        line.y0 = y0; \
        line.x1 = x1; \
        line.y1 = y1; \
        GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0); \
        y1 = a1 + 3; \
        line.tag = 0; \
        line.r = 0; \
        line.g = 0; \
        line.b = white; \
        line.x0 = x0; \
        line.y0 = y0; \
        line.x1 = x1; \
        line.y1 = y1; \
        GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0); \
    }

#define DEFINE_func_8012E138() \
    extern u16 D_80126B5E; \
    extern u16 D_80126B62; \
    extern u16 D_80126B66; \
    extern void func_8012F038(); \
    extern void func_80049CAC(); \
    extern void func_8012F14C(); \
    extern s32 func_80135888(); \
    void func_8012E138(int model) { \
        struct Cam8012E138 cam; \
        int bufB[2]; \
        int bufA[2]; \
        int m; \
        short s; \
        cam.a = D_80126B5E; \
        cam.b = D_80126B62; \
        cam.c = D_80126B66; \
        func_8012F038(*(int *)(model + 0x20) + 0x34, &cam, bufA); \
        m = *(int *)(model + 0x20); \
        if (m != 0) { \
            int mm; \
            func_80049CAC(m + 0x10, m + 0x34); \
            mm = *(int *)(model + 0x20); \
            s = *(u16 *)(model + 6) + *(u16 *)(model + 0x50); \
            *(u16 *)(mm + 8) = s; \
            *(int *)(mm + 0x48) = s; \
            s = *(u16 *)(model + 0xA) + *(u16 *)(model + 0x52); \
            *(u16 *)(mm + 0xA) = s; \
            *(int *)(mm + 0x4C) = s; \
            s = *(u16 *)(model + 0xE) + *(u16 *)(model + 0x54); \
            *(u16 *)(mm + 0xC) = s; \
            *(u16 *)(mm + 0x2C) = *(u16 *)(mm + 0x2C) | 1; \
            *(int *)(mm + 0x50) = s; \
        } \
        func_8012F14C(*(int *)(model + 0x20) + 0x34, bufA, bufB); \
        if (func_80135888(*(int *)(model + 0x20), *(int *)(model + 0x58), bufB, &cam)) { \
            D_80126B5E = cam.a; \
            D_80126B62 = cam.b; \
            D_80126B66 = cam.c; \
        } \
    }

#define DEFINE_func_80175308() \
    extern u8  D_8011F7A8; \
    extern u8  D_8011F7A9; \
    extern u8  D_8011F7AE; \
    extern u16 D_8011F7B4; \
    extern u16 D_8011F7B6; \
    extern s16 D_8011F7B8; \
    extern s16 D_8011F7BA; \
    extern s16 D_8011F7BC; \
    extern s16 D_8011F7BE; \
    extern u8 D_80078E78[]; \
    extern s16 D_800B9A02; \
    extern void func_80016714(void *, s32); \
    extern void func_801757A0(s32); \
    extern void func_800596F4(s32); \
    void func_80175308(void) { \
        u8 *p = (u8 *)&D_8011F7A8; \
        p[0] = 1; \
        D_8011F7A9 = 2; \
        D_8011F7AE = 0x37; \
        D_8011F7B8 = -0x37; \
        (*(s16 *)&D_8011F7B4) = -0x37; \
        D_8011F7BE = 0x37; \
        D_8011F7BA = 0x37; \
        (*(s16 *)&D_8011F7B6) = 0x37; \
        D_8011F7BC = 0x37; \
        *(Blk152 *)(p + 0x48) = (*(Blk152 *)D_80078E78); \
        func_80016714(p + 0xE0, 0x98); \
        { \
            s16 *q = &D_800B9A02; \
            func_801757A0(*q); \
            func_800596F4(0); \
            func_801757A0((s16)(*(u16 *)q ^ 1)); \
        } \
    }

#define DEFINE_func_8014C568() \
    extern s32 ratan2(s32 x, s32 y); \
    s32 func_8014C568(s16 *a0, s16 *a1) { \
        return ratan2(a0[3] - a1[0], a0[7] - a1[2]) & 0xFFF; \
    }

#define DEFINE_func_8012A418() \
    extern s32 D_801151D4; \
    extern struct BigCopy D_80114EE8; \
    void func_8012A418(void) { \
        struct Q16 *src; \
        struct Q16 *dst; \
        struct Q16 *end; \
        src = (struct Q16 *)D_801151D4; \
        dst = &D_80114EE8; \
        end = src + 10; \
        do { \
            *dst = *src; \
            src++; \
            dst++; \
        } while (src != end); \
        *(s32 *)dst = *(s32 *)src; \
    }

#define DEFINE_func_80134310() \
    s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) { \
        return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2; \
    }

#define DEFINE_func_801395D4() \
    extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3); \
    void func_801395D4(void * a0) \
    { \
        Stk801395D4 sp10; \
        u16 mul; \
        u16 base; \
        sp10.f0 = *(u16 *)(a0 + 0x38); \
        mul = *(u16 *)(a0 + 0x12); \
        base = *(u16 *)(a0 + 0x3A); \
        sp10.f4 = 0x38; \
        sp10.f6 = 0xC; \
        sp10.f2 = base + mul * 12; \
        func_80059888(&sp10, 0, 0, 0); \
    }

#define DEFINE_func_80171FFC() \
    extern s32 func_8017248C(s32, s32); \
    extern s32 ratan2(s32, s32); \
    extern void func_80172170(s32, s32); \
    extern void func_80146D90(s32); \
    s32 func_80171FFC(short *a0, short *a1, s32 a2) \
    { \
        s32 r; \
        r = func_8017248C((s32)a0, (s32)a1); \
        if (r != 0) { \
            func_80146D90((s32)a0); \
            return r; \
        } \
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = \
            (ratan2(a1[0] - a0[3], a1[2] - a0[7]) + 0x800) & 0xFFF; \
        func_80172170((s32)a0, a2 & 0xFF); \
        return 0; \
    }

#define DEFINE_func_801522CC() \
    extern void func_8014BC44(s32 a0, s32 a1); \
    extern void func_80154A74(s32 a0, s32 a1); \
    extern void func_801553C0(s32 a0); \
    extern void func_801470AC(s32 *a0); \
    extern void func_801472B4(void *a0); \
    extern void func_801477E8(s32 *a0, s32 a1); \
    extern void func_80153C18(); \
    void func_801522CC(s32 a0) { \
        s32 v1; \
        func_8014BC44(a0, *(s16 *)(a0 + 0xF2)); \
        *(u8 *)(a0 + 0xA8) = 0x20; \
        func_80154A74(a0, 0x11); \
        func_801553C0(a0); \
        func_801470AC((s32 *)a0); \
        func_801472B4((void *)a0); \
        v1 = *(s32 *)(a0 + 0x20); \
        *(s16 *)(a0 + 0x3E) = 0; \
        *(s16 *)(a0 + 0x40) = 0; \
        *(s16 *)(a0 + 0x42) = 0; \
        *(u8 *)(a0 + 0xDD) = 0; \
        *(u16 *)(a0 + 0x3C) = *(u16 *)(a0 + 0x3C) & 0xFFFE; \
        *(s16 *)(v1 + 0x10) = 0; \
        *(u16 *)(a0 + 0x60) = 0x1000; \
        *(u16 *)(a0 + 0x62) = 0x1000; \
        *(u16 *)(a0 + 0x64) = 0x1000; \
        func_801477E8((s32 *)a0, 0); \
        func_80153C18(a0); \
    }

#define DEFINE_func_801497A8() \
    extern u8 D_80078E78[]; \
    extern u8 D_80078EC1; \
    extern s32 func_8014CB7C(void); \
    extern s32 func_8014C088(s32 a0, s32 a1); \
    extern u8 func_80165658(s32 a0, s32 a1); \
    s32 func_801497A8(s32 *a0) { \
        u8 *s1 = D_80078E78; \
        /* Zero-byte RC-7 "second set": reg_n_sets(s1)==2 fails update_equiv_regs' \
           single-set gate -> no REG_EQUIV -> the address constant is NOT \
           rematerialized at its lone use; it is held in a callee-saved reg ($s1) \
           across the calls, as the target does. NOT a register pin (no $N). */ \
        __asm__("" : "=r"(s1) : "0"(s1)); \
        if (*(u16 *)a0 == 0x1A) goto ret0; \
        if (func_8014CB7C() != 0) goto ret0; \
        if (D_80078EC1 == 0xF) { \
            if (func_8014C088((s32)a0, 0xA) != 0) goto ret0; \
        } \
        if (*(s32 *)((u8 *)a0 + 0x44) & 0x404) goto ret0; \
        if (func_80165658((s32)a0, s1[0x49]) & 0x80) goto ret0; \
        if (*(u16 *)((u8 *)a0 + 0xAC) & 0x20) return 1; \
    ret0: \
        return 0; \
    }

#define DEFINE_func_8012C658() \
    extern u8 D_80126720[]; \
    extern s32 func_8012C890(s32 a0, s32 a1, s32 a2); \
    s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2) { \
        struct S8012C658 sp; \
        s32 var_v0; \
        u16 *var_a1; \
        u16 *end; \
        u16 *param; \
        if ((arg2 != 0) && (*(u16 *)(arg2 + 0x0) != 0)) { \
            sp.unk0 = *(u16 *)(arg2 + 0x6); \
            sp.unk2 = *(u16 *)(arg2 + 0xA); \
            sp.unk4 = *(u16 *)(arg2 + 0xE); \
        } else { \
            sp.unk4 = 0; \
            sp.unk2 = 0; \
            sp.unk0 = 0; \
        } \
        sp.unk6 = (s16)arg0; \
        sp.unk8 = (s16)arg1; \
        sp.unkA = 0; \
        sp.unk10 = 0; \
        sp.unkE = 0; \
        sp.unkC = 0x7FFF; \
        param = &sp.unk0; \
        end = (u16 *)D_80126720; \
        if (arg2 == 0) { \
            var_a1 = (u16 *)((u8 *)end - 0x6480); \
        } else { \
            var_a1 = (u16 *)(arg2 + 0x10C); \
        } \
        while (var_a1 != end) { \
            if (*var_a1 == 0) { \
                goto found; \
            } \
            var_a1 = (u16 *)((u8 *)var_a1 + 0x10C); \
        } \
        var_a1 = 0; \
    found: \
        var_v0 = 0; \
        if (var_a1 != 0) { \
            var_v0 = ((s32 (*)(u16 *, u16 *))func_8012C890)(param, var_a1); \
        } \
        return var_v0; \
    }

#define DEFINE_func_8016EFC8() \
    extern u8 D_80126D6C; \
    extern s32 D_80126D54; \
    extern u8 D_80126D6D; \
    extern u8 D_80126D6E; \
    extern s32 D_80126D5C; \
    extern s32 D_80126D60; \
    extern s16 D_80126D64; \
    extern s16 D_80126D66; \
    extern s16 D_80126D68; \
    extern s16 D_80126D6A; \
    extern u8 D_80126D1A; \
    extern s32 D_80127058; \
    extern s32 D_8012705C; \
    extern s32 D_80127060; \
    extern s32 D_80127064; \
    extern s32 D_80127068; \
    extern s32 D_8012706C; \
    extern s32 D_80127070; \
    extern s32 D_80127074; \
    extern u8 D_800B9A17; \
    extern s16 D_80126D20; \
    extern s32 D_80126D50; \
    s32 func_8016EFC8(s32 a0, s32 a1) \
    { \
        s32 v1; \
        s32 m; \
        v1 = *(s32 *)a0; \
        m = 0x4000000; \
        D_80126D6C = 1; \
        D_80126D54 = a0; \
        D_80126D6D = 0; \
        D_80126D6E = 0; \
        D_80126D5C = 0; \
        D_80126D60 = 0; \
        D_80126D64 = 0; \
        D_80126D66 = 0; \
        D_80126D68 = 0; \
        D_80126D6A = 0; \
        D_80126D1A = 0; \
        D_80127058 = 0; \
        D_8012705C = 0; \
        D_80127060 = 0; \
        D_80127064 = 0; \
        D_80127068 = 0; \
        D_8012706C = 0; \
        D_80127070 = 0; \
        D_80127074 = 0; \
        D_800B9A17 = 0; \
        D_80126D20 = 0; \
        D_80126D50 = v1 | m | a1; \
    }

#define DEFINE_func_801775E0() \
    extern u8 D_8011F83B; \
    extern u8 D_8011F837; \
    extern u8 D_8011F7F0; \
    extern void func_801776EC(u8 *a0); \
    void func_801775E0(s32 param_1, s32 param_2) { \
        s32 s0 = param_1; \
        s32 pp = param_2; \
        u8 *base = &D_8011F7F0; \
        s16 sVar1; s32 t; s32 v; \
        s32 c = D_8011F83B; \
        if (c != 0) { \
            if (c < 0) goto store; \
            if (c >= 0xf7) goto store; \
            if (c < 0xf3) goto store; \
            goto docall; \
        } \
        if (D_8011F837 != 0x80) { \
            *(u8 *)(s0 + 4) = 0xff; \
            *(u8 *)(s0 + 6) = 0x10; \
            *(u8 *)(s0 + 5) = 0x10; \
            goto L684; \
        } \
        func_801776EC((u8 *)s0); \
        goto L684; \
    docall: \
        func_801776EC((u8 *)s0); \
        goto L684; \
    store: \
        *(u8 *)(s0 + 5) = 0xff; \
        *(u8 *)(s0 + 6) = 0x10; \
        *(u8 *)(s0 + 4) = 0x10; \
    L684: \
        sVar1 = (s16)((u32)(base[0x47] * 9) >> 4); \
        t = pp + 0x48; \
        *(s16 *)(s0 + 0xe) = sVar1; \
        *(s16 *)(s0 + 0xa) = t - sVar1; \
        if (base[0x47] != 0) { s0 = param_1 + 0x14; v = 0xa0; } else { s0 = param_1 + 0x14; v = 0x40; } \
        *(u8 *)(s0 + 6) = v; \
        *(s16 *)(s0 + 0xa) = pp; \
    }

#define DEFINE_func_80164418() \
    extern s32 ratan2(s32 a0, s32 a1); \
    extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2); \
    extern void func_801630C4(s32, s32, s32, s32); \
    extern void func_80162FC0(s32 *a0); \
    extern void func_80162D88(s32 *a0); \
    void func_80164418(s32 s0) { \
        s16 v[6]; \
        s32 s1 = *(s32 *)(s0 + 0x20); \
        s32 a1 = *(s32 *)(s0 + 0x4C); \
        v[0] = *(u16 *)(a1 + 0x6) - *(u16 *)(s0 + 0x6); \
        v[1] = *(u16 *)(a1 + 0xA) - (*(u16 *)(s0 + 0xA) + 0x1E); \
        v[2] = *(u16 *)(a1 + 0xE) - *(u16 *)(s0 + 0xE); \
        v[5] = ratan2(v[0], v[2]); \
        if (v[2] < 0) { \
            v[2] = -v[2]; \
        } \
        if (v[2] == 0) { \
            v[4] = 0; \
        } else { \
            v[4] = ratan2(-v[1], v[2]); \
        } \
        *(u16 *)(s1 + 0x14) = (*(u16 *)(s1 + 0x14) + 0x71) & 0xFFF; \
        *(s16 *)(s1 + 0x10) = func_80012ABC(*(s16 *)(s1 + 0x10), v[4], 0x2); \
        *(s16 *)(s1 + 0x12) = func_80012ABC(*(s16 *)(s1 + 0x12), v[5], 0x2); \
        ((s32 (*)(s32, s32, s32, s32))func_801630C4)(s0, 0, 0, 0x8000); \
        func_80162FC0((s32 *)s0); \
        func_80162D88((s32 *)s0); \
    }

#define DEFINE_func_801379FC() \
    extern s32 D_80127524; \
    extern s32 D_80127548[]; \
    extern s32 D_801269F0; \
    extern s16 D_801269F4; \
    extern s32 D_801269F8; \
    extern void func_80138BE0(s32 a0); \
    extern void func_80137BD8(s32 a0); \
    extern void func_8013A380(void); \
    void func_801379FC(void) { \
        s32 i; \
        (*(s32 *)D_80127548) = 0x24; \
        if ((D_80127524 != 0) && (*(s32 *)D_80127524 != 0)) { \
            s32 p; \
            s32 idx; \
            func_80138BE0(D_80127524); \
            i = 0; \
            p = (s32)&D_801269F0; \
            idx = 0; \
            do { \
                if ((p != D_80127524) && (*(s32 *)((s32)&D_801269F0 + idx) != 0)) { \
                    func_80138BE0(p); \
                } \
                p = p + 0x4c; \
                i = i + 1; \
                idx = idx + 0x4c; \
            } while (i < 3); \
        } else { \
            s32 p; \
            s32 idx; \
            i = 0; \
            p = (s32)&D_801269F0; \
            idx = 0; \
            do { \
                if (*(s32 *)((s32)&D_801269F0 + idx) != 0) { \
                    func_80138BE0(p); \
                } \
                p = p + 0x4c; \
                i = i + 1; \
                idx = idx + 0x4c; \
            } while (i < 3); \
        } \
        { \
            s32 p; \
            s32 idx; \
            s32 flags; \
            i = 0; \
            p = (s32)&D_801269F0; \
            idx = 0; \
            do { \
                if (*(s16 *)((s32)&D_801269F4 + idx) != 0) { \
                    if (*(s32 *)((s32)&D_801269F0 + idx) != 0) { \
                        flags = *(s32 *)((s32)&D_801269F8 + idx); \
                        if ((flags & 0x1000) != 0) { \
                            if ((flags & 0x2000) == 0) { \
                                func_80137BD8(p); \
                            } \
                        } \
                    } \
                } \
                p = p + 0x4c; \
                i = i + 1; \
                idx = idx + 0x4c; \
            } while (i < 3); \
        } \
        func_8013A380(); \
    }

#define DEFINE_func_8012EA90() \
    void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3) \
    { \
        Buf buf; \
        s32 iVar4; \
        register u32 v __asm__("$17");      /* $s1 */ \
        iVar4 = *(s32 *)(param_1 + 0x20); \
        v = *(u32 *)(iVar4 + 0x20); \
        if (v == 0) { \
            *(Blk16 *)(param_3)        = *(Blk16 *)(iVar4 + 0x34); \
            *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44); \
        } else if ((v & 0x1000000) != 0) { \
            register s32 p __asm__("$16"); \
            s32 w; \
            p = (s32)(v & 0xfeffffff); \
            p = p + param_2 * 8; \
            buf.h[0] = *(s16 *)(p + 6); \
            w = *(s32 *)p; \
            buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8)); \
            buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4)); \
            func_80049CAC((s32)&buf, (s32)param_3); \
            param_3[5] = *(s8 *)(p + 3); \
            param_3[6] = *(s8 *)(p + 4); \
            param_3[7] = *(s8 *)(p + 5); \
        } else { \
            s32 q; \
            v = v + param_2 * 0xc; \
            q = (s32)v; \
            buf.h[0] = *(s16 *)(q + 6); \
            buf.h[1] = *(s16 *)(q + 8); \
            buf.h[2] = *(s16 *)(q + 0xa); \
            func_80049CAC((s32)&buf, (s32)param_3); \
            param_3[5] = *(s16 *)(q + 0); \
            param_3[6] = *(s16 *)(q + 2); \
            param_3[7] = *(s16 *)(q + 4); \
        } \
    }

#define DEFINE_func_8012E778() \
    extern u8 D_800AF648; \
    s32 func_8012E778(int param_1, int param_2) \
    { \
        MATRIX_L48 *r0; \
        int iVarX; \
        int iVarY; \
        int iVar3; \
        int iVar4; \
        int sp[6]; \
        sp[0] = (int)*(short *)(param_1 + 6); \
        sp[1] = (int)*(short *)(param_1 + 10); \
        sp[2] = (int)*(short *)(param_1 + 0xe); \
        r0 = (MATRIX_L48 *)&D_800AF648; \
        gte_SetRotMatrix(r0); \
        gte_SetTransMatrix(r0); \
        gte_ldlv0((VECTOR *)sp); \
        gte_rtps(); \
        gte_stsxy((long *)((int)sp + 0x10)); \
        iVarX = (int)*(short *)((int)sp + 0x10); \
        iVar3 = (short)param_2; \
        if (iVarX >= 0) { \
            if (iVar3 >= iVarX) goto cy; \
            return 0; \
        } \
        if (iVar3 < -iVarX) return 0; \
    cy: \
        iVarY = (int)*(short *)((int)sp + 0x12); \
        iVar4 = param_2 >> 0x10; \
        if (iVarY >= 0) { \
            if (iVar4 >= iVarY) goto c1; \
            return 0; \
        } \
        if (iVar4 < -iVarY) return 0; \
    c1: \
        return 1; \
    }

#define DEFINE_func_8012A464() \
    extern s32 D_801151D4; \
    extern Vec8 D_80114F24; \
    void func_8012A464(void) \
    { \
        D_80114F24 = *(Vec8 *)(*(s32 *)&D_801151D4 + 0x3C); \
    }

#define DEFINE_func_8014FFDC() \
    extern s32 func_80135D20(s32 a0, s32 a1, void *a2); \
    s32 func_8014FFDC(s32 e, void *a1, void *a2) { \
        extern u8 D_801202A0[]; \
        extern u8 D_80126720[]; \
        extern u8 D_801152A8[]; \
        Vec8_c1 save; \
        Vec8_c1 test; \
        s32 found; \
        u8 *p; \
        found = 0; \
        __builtin_memcpy(&save, a1, 8); \
        *(s16 *)((s32)a1 + 2) = 0x7fff; \
        p = D_801202A0; \
        if (p < p + 0x6480) { \
            do { \
                if (*(u16 *)p != 0) { \
                    if ((*(u16 *)(p + 0x5C) & 0x400) != 0) { \
                        if (*(s32 *)(p + 0x58) != 0) { \
                            test = save; \
                            if (func_80135D20(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), &test) != 0) { \
                                found = 1; \
                                if (test.unk2 < *(s16 *)((s32)a1 + 2)) { \
                                    __builtin_memcpy(a1, &test, 8); \
                                    __builtin_memcpy(a2, D_801152A8, 8); \
                                } \
                            } \
                        } \
                    } \
                } \
                p += 0x10C; \
            } while (p < D_80126720); \
        } \
        return found; \
    }

#define DEFINE_func_801502EC() \
    extern s32 func_80135D20(s32 a0, s32 a1, void *a2); \
    s32 func_801502EC(s32 e, void *a1, void *a2) { \
        extern u8 D_801202A0[]; \
        extern u8 D_80126720[]; \
        extern u8 D_801152A8[]; \
        Vec8_c1 save; \
        Vec8_c1 test; \
        s32 found; \
        u8 *p; \
        found = 0; \
        __builtin_memcpy(&save, a1, 8); \
        *(s16 *)((s32)a1 + 2) = 0x7fff; \
        p = D_801202A0; \
        if (p < p + 0x6480) { \
            do { \
                if (*(u16 *)p != 0) { \
                    if ((*(u16 *)(p + 0x5C) & 0x400) != 0) { \
                        if (*(s32 *)(p + 0x58) != 0) { \
                            test = save; \
                            if (func_80135D20(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), &test) != 0) { \
                                found = 1; \
                                if (test.unk2 < *(s16 *)((s32)a1 + 2)) { \
                                    __builtin_memcpy(a1, &test, 8); \
                                    __builtin_memcpy(a2, D_801152A8, 8); \
                                } \
                            } \
                        } \
                    } \
                } \
                p += 0x10C; \
            } while (p < D_80126720); \
        } \
        return found; \
    }

#define DEFINE_func_80136F3C() \
    extern short D_800B9A02; \
    extern u8 D_800A6518[]; \
    extern void GsSortLine(void *a0, void *a1, s32 a2); \
    void func_80136F3C(s32 a0, s32 a1) \
    { \
        struct { \
            u32 tag; \
            s16 x0; \
            s16 y0; \
            s16 x1; \
            s16 y1; \
            u8 r; \
            u8 g; \
            u8 b; \
        } line; \
        register s16 x1    __asm__("$16");               /* $s0 */ \
        register s16 x0    __asm__("$17");               /* $s1 */ \
        register u8 *base  __asm__("$19") = D_800A6518;  /* $s3 */ \
        register s16 white __asm__("$20");               /* $s4 */ \
        s16 y0; \
        s16 y1; \
        y0 = a1 - 3; \
        x1 = a0 + 3; \
        __asm__("" : "=r"(x1) : "0"(x1)); \
        y1 = a1 + 3; \
        white = 0xFF; \
        x0 = a0 - 3; \
        line.tag = 0; \
        line.r = white; \
        line.g = 0; \
        line.b = 0; \
        line.x0 = x0; \
        line.y0 = y0; \
        line.x1 = x1; \
        line.y1 = y1; \
        GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0); \
        line.tag = 0; \
        line.r = white; \
        line.g = 0; \
        line.b = 0; \
        line.x0 = x1; \
        line.y0 = y0; \
        line.x1 = x0; \
        line.y1 = y1; \
        GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0); \
    }

#define DEFINE_func_80180710() \
    extern s16 func_8017DA9C(void); \
    int func_80180710(void) \
    { \
      int new_var; \
      new_var = 0x1; \
      new_var--; \
      return (((unsigned int) ((int (*)(void))func_8017DA9C)()) << 16) == new_var; \
      new_var++; \
    }

#define DEFINE_func_8014A51C() \
    extern s32 func_80029178(s32); \
    int func_8014A51C(int param_1) { \
        if (((unsigned char (*)(int))func_80029178)(0x1e) == 0) return 0; \
        if (*(unsigned int *)(param_1 + 0x44) & 0x400) return 0; \
        if (*(unsigned char *)(param_1 + 0xa8) >= 0x19) return 0; \
        if (*(unsigned char *)(param_1 + 0x223) != 0) return 0; \
        if ((*(unsigned short *)(param_1 + 0xac) & 0x40) == 0) return 0; \
        return 1; \
    }

#define DEFINE_func_801483E8() \
    extern void func_80015978(int a0, int *a1); \
    extern int func_80133784(int a0, void *a1, int a2); \
    void func_801483E8(unsigned char *self) { \
        unsigned short src[4]; \
        short dst[4]; \
        int ret; \
        func_80015978((int)(self + 4), (int *)src); \
        dst[0] = src[0]; \
        dst[1] = src[1] + 8; \
        dst[2] = src[2]; \
        ret = func_80133784(1, src, (int)dst); \
        if (ret == 0x2000 && \
            *(short *)(self + 6) == dst[0] && \
            *(short *)(self + 0xA) == dst[1] && \
            *(short *)(self + 0xE) == dst[2] && \
            *(unsigned char *)&dst[3] == 0) { \
            func_80015978((int)(self + 4), (int *)(self + 0xA0)); \
        } \
    }

#define DEFINE_func_8014680C() \
    extern s32 D_8011F9D0; \
    extern unsigned short D_8011F9D6; \
    extern unsigned short D_8011F9DA; \
    extern unsigned short D_8011F9DE; \
    extern int   D_8011FA1C; \
    extern int   D_8011FA20; \
    extern int   D_8011FA24; \
    unsigned short *func_8014680C(short *param_1) \
    { \
        int iVar1, iVar2; \
        register unsigned short *psVar3 __asm__("$3"); \
        register unsigned short *psVar4 __asm__("$7"); \
        iVar2 = 0; \
        psVar4 = (unsigned short *)&(*(unsigned short *)&D_8011F9D0); \
        psVar3 = psVar4; \
        iVar1 = 0; \
        for (; iVar2 < 8; \
             psVar4 = psVar4 + 0x34, psVar3 = psVar3 + 0x34, iVar2 = iVar2 + 1, iVar1 = iVar1 + 0x68) { \
            if (*psVar3 == 0) { \
                *(int *)((char *)&D_8011FA1C + iVar1) = *(int *)(param_1 + 4); \
                *psVar3 = *param_1; \
                *(short *)((char *)&D_8011F9D6 + iVar1) = param_1[1]; \
                *(short *)((char *)&D_8011F9DA + iVar1) = param_1[2]; \
                *(short *)((char *)&D_8011F9DE + iVar1) = param_1[3]; \
                *(int *)((char *)&D_8011FA20 + iVar1) = *(int *)(param_1 + 6); \
                *(int *)((char *)&D_8011FA24 + iVar1) = *(int *)(param_1 + 8); \
                return psVar4; \
            } \
        } \
        return (unsigned short *)0; \
    }

#define DEFINE_func_8017129C() \
    extern void *D_8011F738; \
    extern struct B16 D_800A5E88; \
    extern struct B16 D_800A5E98; \
    extern struct B16 D_800A5EA8; \
    extern void func_801719A4(int, int); \
    extern s32 func_80171990(u8*); \
    extern void func_80171384(void*); \
    void func_8017129C(int param_1) { \
        S16 *p; \
        func_801719A4(param_1, 1); \
        p = (*(S16 * *)&D_8011F738); \
        p[0] = (*(S16 *)&D_800A5E88); \
        p[1] = (*(S16 *)&D_800A5E98); \
        p[2] = (*(S16 *)&D_800A5EA8); \
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x2C) |= 0x20; \
        *(int *)(*(int *)(param_1 + 0x20) + 0x80) = (int)p; \
        ((void (*)(int))func_80171990)(param_1); \
        ((void (*)(int))func_80171384)(param_1); \
    }

#define DEFINE_func_80177AD4() \
    void func_80177AD4(int param_1, unsigned int param_2) { \
        register unsigned int c __asm__("$2"); \
        register unsigned int b __asm__("$3"); \
        char *base; short i; int f; int t; \
        f = 0x100; i = 0; base = (char *)param_1; \
        do { \
            c = (param_2 << 16) >> 28; \
            b = c; \
            if ((c != 0) || (i == 3) || (i == 1)) f = 0; \
            param_2 = param_2 << 4; i = i + 1; \
            t = *(unsigned short *)(base + 0x1e); \
            *(unsigned short *)(base + 0x1e) = f | (t & ~0x100); \
            base[0x20] = b * 8 + 8; \
            base = base + 0x14; \
        } while (i < 4); \
    }

#define DEFINE_func_80177940() \
    extern s32 func_80029504(void); \
    void func_80177940(u32 *p, u32 a_, u32 b_, u32 c_) \
    { \
      int new_var; \
    register u32 a __asm__("$18"); \
    register u32 b __asm__("$16"); \
    register u32 c __asm__("$17"); \
    register u32 v __asm__("$2"); \
      u32 *q; \
      u32 *r; \
      u32 flag; \
    register u32 n __asm__("$6"); \
      u32 nn; \
      u32 t; \
      u32 cl; \
      u32 cs; \
      u32 col; \
      s16 i; \
      new_var = a_; \
      b = b_; \
      c = c_; \
      a = new_var; \
      v = (u32) func_80029504(); \
      v = v - 10; \
      v = v < 0x4b0; \
      v = -v; \
      v = v & 0xb4; \
      c++; \
      c--; \
      cs = c << 16; \
      p[0] = (((u32) (p - 5)) & 0xffffff) | 0x3000000; \
      p[2] = cs | ((b + 0xf) & 0xffff); \
      p[1] = 0x74808080; \
      p[3] = (((v << 6) | 0x4016) << 16) | 0x3850; \
      p += 5; \
      q = p; \
    __asm__("" : "=r"(v) : "0"(v)); \
      cl = ((v << 6) | 0x4016) << 16; \
      flag = 0x1000000; \
      for (i = 0; i < 4; i++) \
      { \
        nn = (a << 16) >> 28; \
        n = nn; \
        if (((nn != 0) || (i == 3)) || (i == 1)) \
        { \
          flag = 0; \
        } \
        q[0] = (((u32) (q - 5)) & 0xffffff) | 0x3000000; \
        q[2] = (cs | (b & 0xffff)) | flag; \
        col = 0x74808080; \
        new_var = n * 8; \
        q[1] = col; \
        t = (new_var + 8) | 0x4000; \
        q[3] = cl | t; \
        q += 5; \
        b += 8; \
        a <<= 4; \
        col = 0; \
      } \
      p = q; \
      r = p; \
    __asm__("" : "=r"(r) : "0"(r)); \
      *((u16 *) (r - 8)) += 6; \
      *((u16 *) (r - 3)) += 6; \
    }

#define DEFINE_func_8012B4B8() \
    extern Mat32 D_800AE620; \
    extern void RotMatrixX(int r, void *m); \
    extern void RotMatrixY(int r, void *m); \
    extern void RotMatrixZ(int r, void *m); \
    s32 func_8012B4B8(int param_1) \
    { \
        register int self __asm__("$17"); \
        register int obj  __asm__("$16"); \
        register int *src __asm__("$5"); \
        int m[8]; \
        short sVar1; \
        int o2, t0, t1, t2; \
        self = param_1; \
        obj = *(int *)(self + 0x20); \
        if (obj != 0) { \
            src = (int *)&D_800AE620; \
            __asm__("" : "=r"(src) : "0"(src)); \
            t0 = src[0]; t1 = src[1]; t2 = src[2]; m[0] = t0; m[1] = t1; m[2] = t2; \
            t0 = src[3]; t1 = src[4]; t2 = src[5]; m[3] = t0; m[4] = t1; m[5] = t2; \
            t0 = src[6]; t1 = src[7];              m[6] = t0; m[7] = t1; \
            RotMatrixX((int)*(short *)(obj + 0x10), (void *)m); \
            RotMatrixZ((int)*(short *)(obj + 0x14), (void *)m); \
            RotMatrixY((int)*(short *)(obj + 0x12), (void *)m); \
            *(Mat32 *)(obj + 0x34) = *(Mat32 *)m; \
            o2 = *(int *)(self + 0x20); \
            sVar1 = *(unsigned short *)(self + 6) + *(unsigned short *)(self + 0x50); \
            *(short *)(o2 + 8) = sVar1; \
            *(int *)(o2 + 0x48) = (int)sVar1; \
            sVar1 = *(unsigned short *)(self + 0xa) + *(unsigned short *)(self + 0x52); \
            *(short *)(o2 + 0xa) = sVar1; \
            *(int *)(o2 + 0x4c) = (int)sVar1; \
            sVar1 = *(unsigned short *)(self + 0xe) + *(unsigned short *)(self + 0x54); \
            *(short *)(o2 + 0xc) = sVar1; \
            *(unsigned short *)(o2 + 0x2c) = *(unsigned short *)(o2 + 0x2c) | 1; \
            *(int *)(o2 + 0x50) = (int)sVar1; \
        } \
    }

#define DEFINE_func_80169228() \
    extern s32  func_80017DC4(void *a0, void *a1); \
    extern void func_80048EAC(void *a0, void *a1); \
    extern s32  func_80017758(void *a0, void *a1); \
    s32 func_80169228(void) \
    { \
        register s32 a0v __asm__("$4"); \
        s32 arg0 = a0v; \
        u8 buf[0x60];               /* $sp+0x10 .. $sp+0x6F */ \
        register u8 *p __asm__("$16");   /* $sp+0x48 (matrix, a1 to the calls) -> $s0 */ \
        s32 col; \
        s16 base; \
        s16 v; \
        /* first-draw SVECTOR verts — source order == target store order */ \
        *(s16 *)(buf + 0x08) = -5;   /* 0x18 */ \
        *(s16 *)(buf + 0x00) = -5;   /* 0x10 */ \
        *(s16 *)(buf + 0x18) = 5;    /* 0x28 */ \
        *(s16 *)(buf + 0x10) = 5;    /* 0x20 */ \
        *(s16 *)(buf + 0x12) = -5;   /* 0x22 */ \
        *(s16 *)(buf + 0x02) = -5;   /* 0x12 */ \
        *(s16 *)(buf + 0x1a) = 5;    /* 0x2A */ \
        *(s16 *)(buf + 0x0a) = 5;    /* 0x1A */ \
        *(s16 *)(buf + 0x1c) = 0;    /* 0x2C */ \
        *(s16 *)(buf + 0x14) = 0;    /* 0x24 */ \
        *(s16 *)(buf + 0x0c) = 0;    /* 0x1C */ \
        *(s16 *)(buf + 0x04) = 0;    /* 0x14 */ \
        /* colors */ \
        if ((*(u32 *)(arg0 + 0x2c) & 2) == 0) { \
            col = -0x40 - (*(s32 *)(arg0 + 0x1c) << 4); \
            *(u8 *)(buf + 0x21) = *(u8 *)(buf + 0x22) = \
            *(u8 *)(buf + 0x25) = *(u8 *)(buf + 0x26) = \
            *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2a) = \
            *(u8 *)(buf + 0x2d) = *(u8 *)(buf + 0x2e) = col; \
            *(u8 *)(buf + 0x20) = *(u8 *)(buf + 0x24) = \
            *(u8 *)(buf + 0x28) = *(u8 *)(buf + 0x2c) = col; \
        } else { \
            col = -0x40 - (*(s32 *)(arg0 + 0x1c) << 4); \
            *(u8 *)(buf + 0x20) = *(u8 *)(buf + 0x24) = \
            *(u8 *)(buf + 0x2a) = *(u8 *)(buf + 0x2e) = 0x20; \
            *(u8 *)(buf + 0x21) = *(u8 *)(buf + 0x25) = \
            *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2d) = col; \
            *(u8 *)(buf + 0x29) = *(u8 *)(buf + 0x2d) = 0x20; \
        } \
        *(s32 *)(buf + 0x30) = 0x50000000;   /* 0x40 tag */ \
        base = 0x800; \
        if (*(u32 *)(arg0 + 0x2c) & 1) base = 0x4cc; \
        v = base + (*(s32 *)(arg0 + 0x1c) << 7); \
        *(u16 *)(buf + 0x5c) = v;   /* 0x6C */ \
        *(u16 *)(buf + 0x5a) = v;   /* 0x6A */ \
        *(u16 *)(buf + 0x58) = v;   /* 0x68 */ \
        p = buf + 0x38; \
        func_80017DC4(buf + 0x58, p); \
        func_80048EAC((void *)(arg0 + 0x38), p); \
        *(s32 *)(buf + 0x4c) = (s32)*(s16 *)(arg0 + 6);    /* 0x5C */ \
        *(s32 *)(buf + 0x50) = (s32)*(s16 *)(arg0 + 0xa);  /* 0x60 */ \
        *(s32 *)(buf + 0x54) = (s32)*(s16 *)(arg0 + 0xe);  /* 0x64 */ \
        func_80017758(buf + 0x00, p); \
        /* second-draw SVECTOR verts */ \
        *(s16 *)(buf + 0x00) = -7;   /* 0x10 */ \
        *(s16 *)(buf + 0x10) = 0;    /* 0x20 */ \
        *(s16 *)(buf + 0x08) = 0;    /* 0x18 */ \
        *(s16 *)(buf + 0x18) = 7;    /* 0x28 */ \
        *(s16 *)(buf + 0x1a) = 0;    /* 0x2A */ \
        *(s16 *)(buf + 0x02) = 0;    /* 0x12 */ \
        *(s16 *)(buf + 0x0a) = 7;    /* 0x1A */ \
        *(s16 *)(buf + 0x12) = -7;   /* 0x22 */ \
        func_80017758(buf + 0x00, p); \
    }

#define DEFINE_func_80174CB0() \
    extern s16 D_80126940; \
    extern s16 D_80126942; \
    extern s16 D_80126944; \
    extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2); \
    extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2); \
    extern void func_80013F3C(s32 a0); \
    extern void func_800123F0(s32 a0, s32 a1); \
    extern void func_80012558(s32 a0, s32 a1); \
    extern void func_800126C4(s32 a0, s32 a1); \
    extern void func_8012F14C();                        \
    s32 func_80174CB0(s32 param_1, s32 param_2) \
    { \
        s16 *pv = &D_80126940; \
        MATRIX mtx; \
        SVECTOR vec; \
        SVECTOR out; \
        *(s32 *)(param_1 + 8) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 8), (s32)*(s16 *)(param_1 + 0xc), 4); \
        *(s32 *)(param_1 + 0x10) = (s16)((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4); \
        *(s16 *)(param_1 + 0x18) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4); \
        *(s16 *)(param_1 + 0x1a) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1a), (s32)*(s16 *)(param_1 + 0x22), 4); \
        *(s16 *)(param_1 + 0x1c) = ((s16 (*)(s32, s32, s32))func_80012ABC)((s32)*(s16 *)(param_1 + 0x1c), (s32)*(s16 *)(param_1 + 0x24), 4); \
        *(s16 *)(param_1 + 0x28) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2e), 0x10); \
        *(s16 *)(param_1 + 0x2a) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2a), (s32)*(s16 *)(param_1 + 0x30), 0x10); \
        *(s16 *)(param_1 + 0x2c) = ((s16 (*)(s32, s32, s32))func_80012C6C)((s32)*(s16 *)(param_1 + 0x2c), (s32)*(s16 *)(param_1 + 0x32), 0x10); \
        *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)*pv; \
        *(s32 *)(param_1 + 0x4c) = (s32)*(s16 *)(param_1 + 0x2a) + (s32)D_80126942; \
        *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2c) + (s32)D_80126944; \
        func_80013F3C((s32)&mtx); \
        func_800123F0((s32)&mtx, (s32)*(s16 *)(param_1 + 0x1c)); \
        func_80012558((s32)&mtx, ((s32)*(s16 *)(param_1 + 0x1a) + (s32)(s16)param_2) & 0xFFF); \
        func_800126C4((s32)&mtx, (s32)*(s16 *)(param_1 + 0x18)); \
        mtx.t[0] = (s32)*(s16 *)(param_1 + 0x28) + (s32)*pv; \
        mtx.t[1] = (s32)*(s16 *)(param_1 + 0x2a) + (s32)D_80126942; \
        mtx.t[2] = (s32)*(s16 *)(param_1 + 0x2c) + (s32)D_80126944; \
        vec.vx = 0; \
        vec.vy = 0; \
        vec.vz = (s16)*(s32 *)(param_1 + 0x10); \
        ((void (*)(s32, s32, s32))func_8012F14C)((s32)&mtx, (s32)&vec, (s32)&out); \
        *(s32 *)(param_1 + 0x3c) = (s32)out.vx; \
        *(s32 *)(param_1 + 0x40) = (s32)out.vy; \
        *(s32 *)(param_1 + 0x44) = (s32)out.vz; \
    }

#define DEFINE_func_801777BC() \
    void *func_801777BC(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) \
    { \
        u32 cl; \
        u32 flag; \
        u32 nn; \
        register u32 n __asm__("$10"); \
        u32 t; \
        register u32 col __asm__("$4"); \
        u32 mask; \
        s32 cnt; \
        s32 dp; \
        s16 i; \
        flag = 0x1000000; \
        cl = ((((s16)a5 + 0x100) << 6) | 0x16) << 16; \
        dp = a6; \
        i = 0; \
        if ((s16)a4 > 0) { \
            cnt = (s16)a4; \
            do { \
                nn = ((u32)(a1 << 16)) >> 28; \
                n = nn; \
                if (((nn != 0) || (i == cnt - 1)) || (i == ((s32)(dp << 16) >> 16))) { \
                    flag = 0; \
                } \
                mask = 0xffffff; \
                col = 0x74808080; \
                t = ((u32)((u32 *)a0 - 5)) & mask; \
                mask = 0x3000000; \
                t = t | mask; \
                ((u32 *)a0)[0] = t; \
                t = ((a3 << 16) | (a2 & 0xffff)) | flag; \
                ((u32 *)a0)[2] = t; \
                ((u32 *)a0)[1] = col; \
                t = n << 3; \
                t = t + 8; \
                t = t | 0x4000; \
                ((u32 *)a0)[3] = cl | t; \
                a0 = (void *)((u32 *)a0 + 5); \
                a2 += 8; \
                a1 <<= 4; \
                col = 0; \
                i++; \
            } while ((s16)i < cnt); \
        } \
        return a0; \
    }

#define DEFINE_func_8014D4C0() \
    extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3); \
    extern s32 func_8014C918(s32 a0, s32 a1); \
    s32 func_8014D4C0(s32 a0, void *a1, void *a2) { \
        s32 psVar3; \
        ((u16 *)a1)[1] = ((u16 *)a1)[1] - 3; \
        ((u16 *)a2)[1] = ((u16 *)a2)[1] + 8; \
        psVar3 = *(s32 *)(a0 + 0x174); \
        if (*(u16 *)psVar3 != 0) { \
            if ((*(u16 *)(psVar3 + 0x5c) & 0x400) && \
                *(s32 *)(psVar3 + 0x58) != 0 && \
                *(s16 *)(psVar3 + 0xa) >= *(s16 *)(a0 + 0xa)) { \
                goto do_body; \
            } \
            if (*(u16 *)psVar3 != 0) { \
                *(s8 *)(psVar3 + 0x74) = 0; \
            } \
        } \
        *(s32 *)(a0 + 0x174) = 0; \
        return 0; \
    do_body: \
        *(u16 *)a1 = *(u16 *)(a0 + 0x98); \
        ((u16 *)a1)[1] = *(u16 *)(a0 + 0x9a) - 3; \
        ((u16 *)a1)[2] = *(u16 *)(a0 + 0x9c); \
        if (func_80135A4C(*(s32 *)(psVar3 + 0x20), *(s32 *)(psVar3 + 0x58), \
                          (s32 *)a1, (s32)a2) != 0) { \
            *(u16 *)(a0 + 6) = ((u16 *)a2)[0]; \
            *(u16 *)(a0 + 0xa) = ((u16 *)a2)[1]; \
            *(u16 *)(a0 + 0xe) = ((u16 *)a2)[2]; \
            *(u16 *)(a0 + 0x16e) = func_8014C918(a0, *(u8 *)(psVar3 + 0x75)) & 0xff; \
            return 1; \
        } \
        *(s8 *)(psVar3 + 0x74) = 0; \
        *(s32 *)(a0 + 0x174) = 0; \
        return 0; \
    }

#define DEFINE_func_8014F3E8() \
    extern s32 func_8014F468(void); \
    extern int func_8014F6F4(void); \
    s32 func_8014F3E8(s32 param_1) \
    { \
        if ((*(u32 *)(param_1 + 0x44) & 0x40000) == 0) { \
            if ((*(s16 *)(param_1 + 6) == *(s16 *)(param_1 + 0x88)) && \
                (*(s16 *)(param_1 + 10) == *(s16 *)(param_1 + 0x8a)) && \
                (*(s16 *)(param_1 + 0xe) == *(s16 *)(param_1 + 0x8c))) { \
                return ((s32 (*)(void))func_8014F468)(); \
            } else { \
                return func_8014F6F4(); \
            } \
        } \
        return 0; \
    }

#endif
