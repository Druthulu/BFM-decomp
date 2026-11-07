---
ts: 2026-11-06T09:55:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FAhYmcaJjI2yPOHsjvm4
---
So kinds are based on asm statements and `register ... __asm__("$N")` pins. A `volatile` local is not counted as a lever by lever_census (kinds B asm, A pin). But "no new lever of any kind" — hmm, the census only has these kinds. Let me look at the census's categories more fully: cls A pin, B asm (barrier/launder/keepalive/instruction/gte/label), C decl-file/decl-body/cast, D register? Let me check around line 540-560 and the class list.

Actually, the constraint says: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". And "Lever-free = none of the row kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

The row kinds are keepalive,pin. So I need to remove those. "no new lever of any kind" means don't add e.g. a barrier asm to compensate. Volatile is likely also considered a lever (it's a codegen lever). Better to avoid volatile.

Let's see what happens with plain C. Since the function is void, flow may delete the rv assignments. Let's just try it. Write win.c:

void func_8017F1F0(s32 a0, s32 a1)
{
    extern s32 D_801EEAEC[];
    s32 x = D_801EEAEC[0];
    s32 y = a1;
    s32 d;
    ...
    d = x - a0;
    if (d < 16) { d = d*2; goto done; } etc.
}

Hmm but the target computes values in v0 and returns. Since the function is void, the compiler will eliminate dead computations of rv. Unless... the target function actually does return (jr ra with v0 set), which suggests the source had a return value or the value was used via asm (which the pin/keepalive provided). Without asm, dead code elimination removes it.

Wait, is `rv` used in a way that makes it live? The keepalive `__asm__("" :: "r"(rv))` marks rv used at the end. The pin forces it into $2. So the target's v0 assignments come from that.

To be lever-free, we need real C that keeps rv live and puts it in v0. Options:
1. Return the value — but that changes the signature (void → s32).
2. Make rv an argument or use a global — that changes codegen.
3. Make the "done" label store to something.

Hmm. Let me check: does the target really return in v0? Let's disassemble. Use dt.sh with --keep... dt.sh doesn't pass --keep. Let me run delever_search --try with --keep directly.

Actually easier: find the baseline object in build/ and objdump. Let me see how build/ is laid out. Let me ask the code retriever? The brief says for code lookups run pa_ext.py ask. But simpler: ls build | head.

Let me check whether `--explain` prints target instructions. Let me just run --try --keep and objdump the candidate object.
