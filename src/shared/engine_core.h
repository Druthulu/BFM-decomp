/* src/shared/engine_core.h — Phase 15 shared engine-core bodies (cross-overlay dedup, §14).
 * Each DEFINE_func_XXXX() expands to the WHOLE matched body once; instantiated in place at the
 * func_XXXX site in every overlay that shares it (address order preserved). Registry +
 * byte-honesty: config/dedup.us.yaml + tools/dedup_integrate.py. Tool-generated; do not hand-edit. */
#ifndef SHARED_ENGINE_CORE_H
#define SHARED_ENGINE_CORE_H
#include "common.h"

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
    extern void func_8012D098(int, int); \
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
    extern void func_8015AD08(void); \
    void func_80149704(void) { \
        func_8015AD08(); \
    }

#define DEFINE_func_80149724() \
    extern void func_8015ACC4(void); \
    void func_80149724(void) { \
        func_8015ACC4(); \
    }

#define DEFINE_func_80149788() \
    extern void func_8015F7A0(void); \
    void func_80149788(void) { \
        func_8015F7A0(); \
    }

#define DEFINE_func_80149864() \
    extern void func_801653B8(void); \
    void func_80149864(void) { \
        func_801653B8(); \
    }

#define DEFINE_func_801498C0() \
    extern void func_80160B00(void); \
    void func_801498C0(void) { \
        func_80160B00(); \
    }

#define DEFINE_func_80149C94() \
    extern void func_801577C8(void); \
    void func_80149C94(void) { \
        func_801577C8(); \
    }

#define DEFINE_func_80149CB4() \
    extern void func_80157D20(void); \
    void func_80149CB4(void) { \
        func_80157D20(); \
    }

#define DEFINE_func_8014A218() \
    extern void func_8015D4B4(void); \
    void func_8014A218(void) { \
        func_8015D4B4(); \
    }

#define DEFINE_func_8014A4FC() \
    extern void func_8015EDD4(void); \
    void func_8014A4FC(void) { \
        func_8015EDD4(); \
    }

#define DEFINE_func_8014A830() \
    extern void func_8015E184(void); \
    void func_8014A830(void) { \
        func_8015E184(); \
    }

#define DEFINE_func_8014AB5C() \
    extern void func_8014AB7C(void); \
    void func_8014AB5C(void) { \
        func_8014AB7C(); \
    }

#define DEFINE_func_8014ABF0() \
    extern void func_8014AC10(void); \
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
    extern s32 func_80155F80(void); \
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
    extern s32 func_8015BE94(void); \
    s32 func_8015BE74(void) { \
        return func_8015BE94(); \
    }

#define DEFINE_func_8015BEC4() \
    extern s32 func_8015AE2C(void); \
    s32 func_8015BEC4(void) { \
        return func_8015AE2C(); \
    }

#define DEFINE_func_8015BEE4() \
    extern s32 func_8015B950(void); \
    s32 func_8015BEE4(void) { \
        return func_8015B950(); \
    }

#define DEFINE_func_8015CCB0() \
    extern s32 func_8015CCD0(void); \
    s32 func_8015CCB0(void) { \
        return func_8015CCD0(); \
    }

#define DEFINE_func_8015CFFC() \
    extern void func_8015D01C(void); \
    void func_8015CFFC(void) { \
        func_8015D01C(); \
    }

#define DEFINE_func_8015D524() \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015D524(s32 arg0) { \
        func_80154A74(arg0, 0x11); \
    }

#define DEFINE_func_8015F360() \
    extern void func_8015F380(void); \
    void func_8015F360(void) { \
        func_8015F380(); \
    }

#define DEFINE_func_8015FA24() \
    extern void func_80154A74(s32 a0, s32 a1); \
    void func_8015FA24(s32 arg0) { \
        func_80154A74(arg0, 0x11); \
    }

#define DEFINE_func_80160EE0() \
    extern void func_80160F00(void); \
    void func_80160EE0(void) { \
        func_80160F00(); \
    }

#define DEFINE_func_80161104() \
    extern s32 func_80161208(void); \
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
    extern s32 func_8016EFC8(s32); \
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
    extern s32 func_8016F0AC(s32); \
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
    extern s32 func_801749C8(s32); \
    s32 func_801749A8(s32 a0) { \
        return func_801749C8(a0); \
    }

#define DEFINE_func_80174C60() \
    extern s32 func_80174CB0(s32, s32); \
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
    extern void func_8012CC88(s32 a, s32 b, s32 c); \
    void func_8012CC1C(s32 arg0, s32 arg1) { \
        func_8012CC88(arg0, 0, arg1); \
    }

#define DEFINE_func_8012CC40() \
    extern void func_8012CC88(s32 a, s32 b, s32 c); \
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
    extern void func_801732C4(void); \
    void func_8017329C(void) { \
        func_80174684(func_801732C4); \
    }

#define DEFINE_func_801732F4() \
    extern void func_80174684(void *); \
    extern void func_8017331C(void); \
    void func_801732F4(void) { \
        func_80174684(func_8017331C); \
    }

#define DEFINE_func_8017334C() \
    extern void func_80174684(void *); \
    extern void func_80173374(void); \
    void func_8017334C(void) { \
        func_80174684(func_80173374); \
    }

#define DEFINE_func_801733A4() \
    extern void func_80174684(void *); \
    extern void func_8017331C(void); \
    void func_801733A4(void) { \
        func_80174684(func_8017331C); \
    }

#define DEFINE_func_8017452C() \
    extern void func_80174684(void *); \
    extern void func_80174554(void); \
    void func_8017452C(void) { \
        func_80174684(func_80174554); \
    }

#define DEFINE_func_80174584() \
    extern void func_80174684(void *); \
    extern void func_801745AC(void); \
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
    extern void func_8012C890(s32 a0, s32 a1, s32 a2); \
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
    extern void func_8012C658(s32 a0, s32 a1, s32 a2); \
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
    extern void func_80166244(void); \
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
    extern void func_801542A4(void); \
    void func_80154274(s32 *a0, s32 a1) { \
        if (*(s32 *)((s32)a0 + 0xB4) != a1) { \
            func_801542A4(); \
        } \
    }

#define DEFINE_func_801542DC() \
    extern void func_8015430C(void); \
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
    extern void func_8012D664(void *a0); \
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
    extern void func_8012CC88(s32 a0, s32 a1, s32 a2); \
    void func_8012CC64(s32 a0, s32 a1) { \
        func_8012CC88(a0, 0x11, a1); \
    }

#define DEFINE_func_80143C74() \
    extern void func_8012C658(s32 a0, s32 a1, s32 a2); \
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
    extern void func_8014F3E8(s32 a0); \
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
    extern void func_8012CC88(s32 a, s32 b, s32 c); \
    extern u8 D_800D3918[]; \
    void func_8012CBA4(s32 a0) { \
        func_8012CC88(a0, 0, (s32)D_800D3918); \
    }

#define DEFINE_func_8012CBCC() \
    extern void func_8012CC88(s32 a, s32 b, s32 c); \
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
    extern s32 func_80174CB0(s32, s32); \
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
    extern void func_80131B14(void); \
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
    extern s32 func_80161208(void); \
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
    extern void func_8016E778(void); \
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
    extern void func_8012E138(void); \
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
    extern void func_8016E778(void); \
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
    extern void func_80175308(void); \
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
    extern void func_80164E40(void); \
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
    extern void func_8016CF04(s32 a0, s32 a1); \
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
    extern void func_8012C658(s32 a0, s32 a1, s32 a2); \
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
    extern void func_80147514(void); \
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
    extern void RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3); \
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
    extern void func_80131B14(void); \
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

#endif
