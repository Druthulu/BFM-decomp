---
ts: 2026-11-07T00:54:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gi8svPtUIwCCnAqRHwEg
---
Very useful. Item 1 (func_80177940): the prior best lever-free is 37 or 43. The note says the "u32* return" route would be a signature change, not allowed. So it's likely a WALL. But we need ≥30 tries on lever-free bodies in this shard to record a WALL.

Wait — the constraint says "no signature or decl change outside the body (callers stay as they are)". So return type change is out. Prior S07 note says best 37 with u32* return, 43 with void.

Item 2 (func_8017E98C): best 1 lever-free, 25 tries. Need 30 tries; maybe find a crack. Note: "sched1 hoists the arg copy `a0 = P(param)` above both stores... then reload_cse rewrites the 0x204 store base s0 -> a0". Target keeps s0 as base for 0x204 store. Interesting — the pin $16 keeps s0. Without pin, the copy a0=s0 is hoisted and the second store uses a0.

Also the second item's orig has `do { } while (0);` — an empty do-while, which is in the original but not a lever per se... Actually the pin kind is what must go. `do { } while (0);` is there. In win.c we may keep it? The constraint says MATCH = the kinds in <dir>/kinds gone. kind is pin only. But also "no new lever of any kind". Hmm, and the PARTIAL rule. The do-while is not a pin.

Let me first look at the second item's prior candidates to understand the shape. Check .run/P40/T10/func_8017E98C/orig.c and a couple of candidates, plus scores recorded anywhere? notes only say 25 spellings all score 1.

Let me check the score of the current orig (with pin) to calibrate: it should score 0. Actually the tree's own text scores 0.

Let me check how the item's tu file for the header looks: `src/shared/ov/func_8017E98C__94ae7b9b.h`. And there are 13 includers.

Let me run a quick calibration: score the orig body (with pin) using tryinc.py k=0.

First create dirs: orig.c in each item dir. Copy the function definition from src header (minus the comment header? The header has a comment then the body). For --body, the body file is a bare definition. The worked example win.c starts with `void func_80181F4C(s32 arg0, s32 arg1) {`.

Note item 1 body references func_80029504 (declared extern in header) — the body file needs the extern decl too, presumably. Let me look at a T10 candidate file, e.g. .run/P40/T10/func_80177940/r5.c.
