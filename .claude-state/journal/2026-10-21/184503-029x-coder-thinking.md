---
ts: 2026-10-22T00:45:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_n6Ewuwc4tynvEolbbK4O
---
Item 2: func_8017FE9C. Kinds = launder only (per list.tsv: "launder"). But the function also has PINS ($4, $5) — those are "levers of other kinds the def already had (pins under other causes) may stay, never added". Since the row kind is only `launder`, MATCH requires the launder gone; the pins may stay.

Hmm, but the launder is `__asm__("" : "=r"(vol) : "0"(vol));` on vol. Constraint: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm".

Hmm — this is ambiguous: does "lever-free" require NO asm at all, or only the kinds listed in the row? The constraint section says: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So for this row (kinds=launder), the launder must be gone; the $4/$5 pins may stay. Good — that's consistent with the row-kinds definition.

But wait: the launder is an `__asm__` — and the kinds list only says launder. Also the `register void *r4 __asm__("$4")` pins are `register` vars — the CONSTRAINT says "no `register` vars, no `__asm__`"! Hmm, that constraint conflicts: "no signature or decl change outside the body (callers stay as they are); no `register` vars, no `__asm__`".

Hmm. That reads as a global constraint on what I write. But the def already has register vars and __asm__ pins... The constraint likely means: don't ADD register vars or __asm__ (i.e., don't use levers). But then "levers of other kinds the def already had may stay".

Hmm, tricky. If I keep the pins (which contain `register` and `__asm__`), am I violating "no register vars, no __asm__"? The CONSTRAINTS line explicitly says "no `register` vars, no `__asm__`" as a hard rule. But the row kind is only launder, and the pins are pre-existing...

Look at moves.md precedent: "launder | func_8018E428 | MATCH — launder gone via in-place pv chain; pv pin dropped too; ang $4 pin kept (not a row kind) (G03)" and "launder | func_80184174 | MATCH: launder->pv = *p; pv &= 0xFF000000 split; $3 pin dropped; $4 ang pin kept (not row kind), pin-free 4 (W05)".

So the project's own precedent: pins that were not row kinds may stay, and the result is MATCH. Great — item 2 keeps the $4/$5 pins and drops the launder.

Now the launder: `__asm__("" : "=r"(vol) : "0"(vol));` on vol, followed by use of vol in `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);`.

What does the launder do here? It creates a 2nd set of vol (the asm output is a new pseudo tied to the input). This kills the sched1 birth boost of the vol computation (the magic multiply chain), so the vol computation stays in place rather than being hoisted.

Let me first score the orig and see the target. Let me get the diff: score the orig (should be 0) and then a candidate without the launder.

Candidate A: remove the asm line only.

The moves.md precedent: "launder | func_8018AA98 | MATCH: pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost of the pv load; plain pv = pv & mask (a new temp) does NOT (11 left) (G11)".

So for this function: vol = ((0xA0 - ax) * 0x7F) / 0xA0; then launder; then use vol | flg | x.

A real 2nd set of vol: e.g. `vol = vol | flg;`? Hmm. The structure:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
<asm launder>
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }
```
The launder's purpose (probably): keeps the vol computation from being scheduled/merged. Since the asm creates a new set of vol at that point, the "birth" of vol's computation is separated from its use.

A real 2nd set in C: `vol = vol & 0xFFFFFFFF;`? That's a no-op copy. Or `vol = vol | 0;`. Hmm — "identity-statement launders do NOT count as a crack" (that's about `w = (w>>16<<16)|x` style). Hmm, but a real 2nd set like `vol &= 0xFF000000` is different from an identity launder.

Let me first just remove the asm and see the residual. Let me create orig.c and cand01.c for item 2.

Let me get exact line numbers: function starts at 3018, ends before "extern void (*D_80185E24[])(void);" — the closing brace. From the sed output, the function ends at line 3018+~52 = let me count: the printed range was 3010-3075 and the function ended with "}" followed by two blank lines then "extern void (*D_80185E24[])(void);". Let me compute: lines 3010-3015 are the externs (6 lines: 3010..3015), 3016 blank, 3017 "extern u8 D_800AF648;", 3018 blank?? Hmm the output shows:

3010: extern void func_800491AC(void *a0);
3011: extern s32  RotTransPers(...)
3012: extern void func_8002D4C8(...)
3013: extern void func_8012CBCC(...)
3014: extern void func_8012C218(...)
3015: (blank)
3016: extern u8 D_800AF648;
3017: (blank)
3018: void func_8017FE9C(s32 a0) {

Yes grep said 3018. Then the body runs to "}" — count the lines from the printed output: from "void func_8017FE9C" to the closing "}":
1 void func_8017FE9C(s32 a0) {
2     struct {
3         s16 v[3];
4         s16 pad0;
5         u16 sxy[2];
6         s32 z;
7         s32 flag;
8         s32 padend;
9     } L;
10 (blank)
11     if (((Unkstruct...
12         ((Unkstruct...= ... - 1;
13     } else {
14         ...unk84 = 0xF;
15         L.v[0] = ...
16         L.v[1] = ...
17         L.v[2] = ...
18         { register void *r4 ...
19         { void *r4; r4 = &D_800AF648; func_800491AC(r4); }
20         RotTransPers(...);
21         if (L.flag >= 0 && ...
22                         && (u32)((L.sxy[1]...
23             s32 x = (s16)L.sxy[0];
24             register s32 ax __asm__("$5");
25             s32 vol;
26             ax = x;
27             if (x < 0) {
28                 ax = -x;
29             }
30             vol = ((0xA0 - ax) * 0x7F) / 0xA0;
31             __asm__("" : "=r"(vol) : "0"(vol));
32             x = (x + 0xA0) / 0x14;
33             if (x == 0x10) {
34                 x = 0xF;
35             }
36             x = x << 8;
37             {
38                 s32 flg = 0x3000;
39                 func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
40             }
41         }
42     }
43 (blank)
44     ((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk12 =
45         *(s16 *)(((Unkstruct_800B5CB8 *)a0)->unk20 + 0x12) + 0x300;
46     if (((s32 (*)(s32))func_8012CBCC)(a0) != 0) {
47         func_8012C218(a0);
48     }
49 (blank)
50     if ((((Unkstruct_800B5CB8 *)a0)->unk1C -= 1) == 0) {
51         func_8012C218(a0);
52     }
53 }

53 lines: 3018..3070. The list.tsv says 52 lines for this item — close (maybe counting differently). Good, so "lines" = the function's line count. Item 1 was 26 lines but the function is 27 lines (3584-3610). Close enough.

Let me now write orig.c and cand01.c for item 2, and score both.

Actually to save calls: score orig first (should be 0 — sanity), and cand01 (launder removed).

Let me write both files now.
