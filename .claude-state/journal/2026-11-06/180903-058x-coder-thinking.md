---
ts: 2026-11-07T01:09:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3CA0JRIT4t8OfHvaZ4v0
---
Item 1 done (WALL, best 41). Now item 2.

Item 2: func_8017E98C__func_8017E98C__94ae7b9b, src/shared/ov/func_8017E98C__94ae7b9b.h, kind: pin, 3 includers. Prior: best 1, 25 tries, sched1-argcopy-hoist.

Body (orig):
```c
void func_8017E98C(void *a0)
{
  char *new_var;
  s32 v0;
register void *s0 __asm__("$16");  // pin $16
 do { } while (0);
  s0 = a0;
  ((void (*)(void *))func_8017EE68)(a0);
  new_var = (char *) s0;
  v0 = 0x8;
  *((s32 *) (((char *) s0) + 0x200)) = v0;
  v0 = 0x100000;
  *((s32 *) (new_var + 0x204)) = v0;
  func_80171990((u8 *) s0);
}
```

Target (16 ins). Let me get the target dump. The prior a1.c (pin removed) scores 1. Let me score a1.c and see the diff — that's the key.

Note the `do { } while (0);` in the orig — an empty do-while. Is that a lever? It's not a pin. In the lever-free body we may keep or drop it. The constraint: "Lever-free = none of the row kinds in <dir>/kinds remain" — kind is pin only. But "no new lever of any kind". An empty do-while is a statement (C0535 do-while splits EBBs). Hmm — it was in the orig (pre-existing), and the rule says "levers of other kinds the def already had (pins under other causes) may stay, never added". So keeping the empty do-while is allowed (it was already there). Actually is an empty do-while a "lever"? It's a barrier-ish statement. The orig has it. I'd keep it to preserve the codegen, but must check it's not considered a launder/barrier. The kinds column says "pin" only, so the census didn't classify the do-while as a lever. Keep it.

Let me score a1.c (pin removed) with dt.sh, and get the full diff.

Item 2 start: now (~18:09). Let me note the start time.

First, FRESH check: diff orig.c against src. I wrote orig.c from src just now; the src header hasn't changed. Fine.

Let me score a1.c (the T10 pin-free body) and see the diff.
