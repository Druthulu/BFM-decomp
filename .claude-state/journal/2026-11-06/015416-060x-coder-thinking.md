---
ts: 2026-11-06T08:54:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qCnUgCDAPKZw1QyIxKBy
---
c14 scores 0! The restructure:
```c
c = rand();
val = nudge;
if (!(c & 1)) {
    val = -val;
}
```
with `s32 c;` declared.

Let me verify the diff tail and confirm. Also confirm no asm remains.

This is real C: hoist rand() into a temp c, assign val = nudge unconditionally after the call, and negate in the then-branch. combine can't merge across the branch.

But wait: does adding `s32 c;` change the register allocation? Score 0 says no. 

Let me double-check with dt.sh tail 4 and grep asm.

Then write win.c, notes, results row, moves line.

One consideration: is this within "real C moves only"? Yes — temp + statement order. 

Let me verify.
