---
ts: 2026-11-06T01:56:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GCzjCUV8BI3JK0EophRN
---
I can get JUMP_INSN's value from rtl.def ordering. But let's do it more simply: break on delete_insn and use gdb commands to check `insn->code`. Let me write a gdb script.

Actually, a faster decisive test: break on `redirect_jump` and see if it's called with nlabel=0 for our jump, and on `delete_insn`. Hmm.

Alternatively, I can avoid all this: maybe the answer is that the jump is NOT deleted but *moved*/renumbered, and my dump reading is wrong. Let me diff the .rtl and .jump dumps' insn sequences around the function end directly with a script that lists insn UIDs.

Let me just do a quick gdb run. Write a gdb script:

```
set pagination off
break delete_insn
commands
silent
printf "delete_insn code=%d uid=%d\n", ((struct rtx_def*)insn)->code, ((struct rtx_def*)insn)->fld[0].rtint? ...
```

Hmm, UID access: rtx_def has `fld` array; UID is in `fld[0]`? In gcc 2.7.2, INSN_UID(insn) = XWINT(insn, 0)? Let me check rtl.h for INSN_UID.
