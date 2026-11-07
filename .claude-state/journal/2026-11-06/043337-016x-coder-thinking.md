---
ts: 2026-11-06T11:33:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7bFXVBdAfqr21vIXkIAJ
---
Baseline 0. Now create a lever-free body. Let me construct `nopin.c`: remove the `register s32 zr` pin and `register s32 n __asm__("$2")` pin, remove both asm barriers.

Original body:
```c
void func_80188778(void) {
    extern u16   aD800B9A02 __asm__("D_800B9A02");
    ...
    Panel_S40_8018B238_80188778 *w;
    s32 *ot;
    s32 n;      /* lever 2 */
    s32 cnt;
    register s32 zr __asm__("$0");     /* RC-12 opaque-copy source */  // !FAKE: pin $0
    s16 i;
    volatile u16 *pbh;

    w  = D_80115134;
    ot = (s32 *)func_80137D08(...);
    if (...) {...} else {...}
    ot = func_8013AB54(...);
    if (D_80115126 == 3) {
        if (D_8011511A == 3) {
            ot = func_801889B8(ot, &D_801B9188, 3);
            n = 3 + zr;
        } else { n = 4; }
    } else { n = 3 + zr; }
    i = 0;
    if (n != 0) {
        cnt = n;
        do {
            if (D_80115158[i].h != 0) {
                __asm__("");
                ot = func_801889B8(ot, w, i);
            }
            i++; w++;
        } while (i < cnt);
    }
    func_8005A600(...);
    pbh = (u16 *)&D_800B9A02;
    ...
    ot += 10;
    __asm__ __volatile__("" ::: "memory");
    D_801151D0 = (s32)ot;
}
```

Lever-free:
```c
void func_80188778(void) {
    extern u16   aD800B9A02 __asm__("D_800B9A02");
    ... same decls ...
    s32 n;
    s32 cnt;
    s16 i;
    volatile u16 *pbh;

    w  = D_80115134;
    ot = ...;
    ...
    if (D_80115126 == 3) {
        if (D_8011511A == 3) { ot = ...; n = 3; } else { n = 4; }
    } else { n = 3; }
    i = 0;
    if (n != 0) {
        cnt = n;
        do {
            if (D_80115158[i].h != 0) {
                ot = ...;
            }
            i++; w++;
        } while (i < cnt);
    }
    ...
    ot += 10;
    D_801151D0 = (s32)ot;
}
```

Note the aD800B9A02 extern asm-label alias `__asm__("D_800B9A02")` — that's a symbol-name alias, not a codegen lever (per worked example notes, it's allowed). But it IS an `__asm__` in the source. The brief says "no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm". Hmm — "no ... or asm". Does that mean no `__asm__` at all, including the symbol alias? The worked example kept `aB9A02 __asm__("D_800B9A02")` and called it "symbol name, not a codegen lever". The brief's phrase "no pin (register-asm/`__asm__` reg steer)" — the parenthetical explains pin = register-asm / asm reg steer. And "barrier, keepalive macro or asm" — "or asm" might cover raw asm. But the symbol-name alias is needed for the unsigned access (§37). Hmm. The kinds are barrier,pin. A symbol-name alias is neither. The worked example explicitly kept it. I'll keep it — it's a declaration alias, not a codegen lever. Actually wait, is it? `extern u16 aD800B9A02 __asm__("D_800B9A02")` just renames the symbol; no codegen effect. Fine.

But hold on — the constraint "no new lever of any kind" and "Lever-free = none of the row kinds in <dir>/kinds remain". Kinds are barrier,pin. The alias isn't barrier or pin. Keep.

Let me write nopin.c via a script? I'll write the file with the Write tool. But I need the full exact text. Let me create it by copying orig.c and editing with sed/python. Simpler: use a python script under .run to transform? Actually easiest: Write the file directly since I have the body content. But it's long (~77 lines). I'll use Write.

Actually, a cleaner approach: copy orig.c to nopin.c then apply small edits with sed? The Edit tool requires having Read the file. I have read the src range. But the scratch file nopin.c — I can Write it fresh.

Let me Write nopin.c with the full body.

Wait — the types: `Env_S40_8018B238_80188778`, `Panel_S40_8018B238_80188778`, `Flag_S40_8018B238_80188778`, `W_S40_8018B238_80188778`, `PTag_S40_8018B238_80188778`, `Panel_8017E978_801889B8`. These are defined earlier in the TU. delever_search compiles the body in the TU context, so fine.

Let me write nopin.c.
