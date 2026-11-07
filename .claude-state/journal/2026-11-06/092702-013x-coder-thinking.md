---
ts: 2026-11-06T16:27:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t2u0JvbSXqRFz0vPIBYv
---
Baseline orig scores 0 with levers. Now I need lever-free. Start with orig.c minus levers:
- remove `register s32 v0r __asm__("$2")` → plain s32 v0r
- remove barrier `__asm__ __volatile__("")` 
- remove keepalive `__asm__ __volatile__("" : : "r"(v0r))` and just `v0r = 1;`

Wait, v0r is only used in the keepalive. Without keepalive, `v0r = 1;` is a dead store, and flow may delete it. The keepalive exists to force v0=1. So lever-free must make v0=1 come out naturally — maybe `return 1;`? But the function returns void. Signature change is not allowed outside the body... "no signature or decl change outside the body". Hmm, changing return type would be a decl change. Not allowed.

Alternative: the target likely has v0=1 as a real instruction. Let's check target.s. Let me read the target for item 1.

Actually let me first make the naive lever-free body and score it, then iterate. Let me create nopin.c.

Plan for item 1: 
```c
void func_800D1E9C(void *arg0) {
    s32 sp18[30];
    s16 sp90[4];
    s16 sp98[8];
    s32 *p;
    s32 i;
    s32 v0r;

    p = (s32 *) arg0;
    ...
    ret:
    func_80010A98();
    v0r = 1;
}
```
But v0r dead → flow deletes. Maybe instead just call something that returns 1? Or assign to a global? No, that changes behavior.

Let's check the target to see what v0=1 looks like. Let me read target.s.
