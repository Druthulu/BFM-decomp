---
ts: 2026-11-06T08:31:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fXIlwrDZD8VWtNNMU2cs
---
Good, orig body scores 0 as expected. Now the task: produce a body scoring 0 without the keepalive.

Item 1: the keepalive is `void *a0pin = sp18; __asm__ __volatile__("" : : "r"(a0pin));` — it keeps sp18's address in a0 ($4) for the call `func_8012C51C(a0pin, (s32)param_1)`. Without the asm, `a0pin` is just `sp18` and the call becomes `func_8012C51C(sp18, param_1)` which would be the same argument... The keepalive forces a0pin into a register earlier? Actually the asm forces a0pin to be live before the if-block. Hmm, that means the address computation happens before `if (D_801270CC == 0)`. Lever-free: we must make the address of sp18 live in a0 before the branch using real C.

Let me look at the target disassembly to understand what's needed. Maybe a variant like computing `a0pin = sp18;` and passing it. Without asm, gcc may rematerialize the address at the call (addiu a0,sp,...). The keepalive forces materialization before the if.

Let's see the dumps/target. What tool shows the target asm? delever_search with diff tail. dt.sh prints tail of diff (score + diff tail). Let me get more tail lines and see what differs when I remove the asm.

Candidate A: just delete the asm line (keep `void *a0pin = sp18;`). Score it.

Also check: is `a0pin` used elsewhere? Only at call. Let's try.

Item 1 body:
```c
void func_801856D8(int param_1)
{
    u16 sp10[3];
    u16 sp18[10];
    s16 *p;

    if (func_8012BEE8((s32)param_1) != 0) {
        ...
    }
    if (D_801270C8 != 0) {
        void *a0pin = sp18;
        if (D_801270CC == 0) {
            ...
            func_8012C51C(a0pin, (s32)param_1);
        }
    }
}
```
Hmm but `a0pin` unused when the inner if is false → fine.

Wait: a subtlety. The declared locals `u16 sp10[3]; u16 sp18[10];` are 26 bytes; frame is probably 0x30. Fine.

Let me write candidate and score.

Actually, first I should look at what the target does. Let me get the diff for the asm-less candidate directly.

Also the "wall" tags list includes `flow-unused-result`, `expand-void-return`, `lreg-*`, etc. For keepalive items, the usual crack: replace keepalive with a real use/return (as in W04/W06/G24). Let me try.

Let me create the candidate with the asm removed.
