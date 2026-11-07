---
ts: 2026-11-06T05:16:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dqVbrxiNYEsc1etxpzok
---
I can use cc1_dumps_tu.sh with a small .c file directly (it handles a .c file). Let me write a minimal test to understand the asm frame artifact. Put it under my shard dir.

Test:
```c
extern u8 D_8011F7A8;
extern u16 D_800B9A02;
s32 f(void) {
    extern u8 D_8011F7A8;
    u8 *p = (u8*)&D_8011F7A8;
    u16 *q = (u16*)&D_800B9A02;
    ...
}
```
Simpler test: 
```c
void g(int *p) { *p = 1; __asm__("" ::: "memory"); *p = 2; }
```
and check the frame. Let me do it.
