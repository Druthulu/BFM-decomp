---
ts: 2026-11-06T11:57:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YQXSMGfhS6K05d2YeD7r
---
The first launder (_pm2) is a §153 address-rematerialisation launder: cse unifies the address pseudos; the launder empties the equivalence class so global.c rematerialises `addiu aN,sp,N` at every site.

This is the "dead-reset cse-breaker" C0414 technique! A real-C alternative: a dead reset like `_pm2 = 0;` after the use? C0414 cracked 3 launders in G16x with dead resets.

Let me try: replace `__asm__("" : "=r"(_pm2) : "0"(_pm2));` with a real C dead reset, e.g. `_pm2 = 0;` — but that changes the value used at the next site! The pattern is:
```
s32 _pm2 = (s32)&m2;
<launder>
lv...=0;
ReadRotMatrix((void*)_pm2);
```
The launder re-sets _pm2 to the same value, breaking the cse class. A dead reset would be `_pm2 = (s32)&m2;` again? That's the same as a re-assignment — cse would still unify (it's the same expression). Hmm, but the launder is an asm that cse can't see through, so the pseudo is a new value.

C0414 "dead-reset cse-breaker": the trick is `p = 0;` after the use — a store of a constant to the pseudo, which empties the equivalence class and is dead (removed later). E.g.:
```
s32 _pm2 = (s32)&m2;
... use _pm2 ...
_pm2 = 0;
```
The `_pm2 = 0` is dead (never read) → flow deletes it, but cse sees it and breaks the class.

Wait, but the launder is placed BEFORE the use. The C0414 dead reset is placed after the last use. Here, the pattern needs the *address* to be rematerialized at each of the 2 sites (ReadRotMatrix and func_8004974C). 

Hmm, the comment says "&m2 / &m3 are each an argument TWICE inside this one CSE basic block, so cse unifies the pseudos and global.c hands them a callee-saved reg". So without the launder, cse unifies `&m2` (used at ReadRotMatrix and func_8004974C) into one pseudo → one register.

The real-C fix: a dead reset after each use: `_pm2 = 0;` after `ReadRotMatrix(...)`. That empties the class, so the second site rematerialises.

Let me try the C0414 dead-reset approach:
```
s32 _pm2 = (s32)&m2;
lv...;
ReadRotMatrix((void*)_pm2);
_pm2 = 0;
```
Hmm, but `_pm2 = 0` would be a dead store to a register — flow's dead code elimination should remove it. Let me test.

Similarly for _a/_b:
```
s32 _a = (s32)&m2;
s32 _b = (s32)&m3;
func_8004974C((void*)_a, (void*)_b);
_a = 0;
_b = 0;
```

Let me try these. And also try the "0" reset placement variations.

Let me build a candidate: replace the launders with dead resets after the uses.
