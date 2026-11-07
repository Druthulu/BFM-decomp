---
ts: 2026-11-06T21:20:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6eYX9MBePIM9ttPhBWXR
---
Item 3 is a header item (src/shared/ov/func_80160C28.h), kinds keepalive (but the orig also has a pin `$4` — the kinds say keepalive only; the pin is "a lever of another kind the def already had"? Hmm, kinds = keepalive. But orig.c has `register void *a __asm__("$4")` — a pin! The kinds file says only keepalive. Interesting: the brief says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer)..." Hmm, "no pin" is mentioned in the definition of lever-free. But the kinds row says keepalive only. The constraint: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So the pin `$4` may stay (it's a lever of another kind not listed in kinds). Hmm, but "Lever-free = none of the row kinds in <dir>/kinds remain: no pin ..." — contradictory. Let me read carefully:

"Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

and

"CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added"

So for this item, kinds = keepalive. The pin $4 is not in the kinds list → it may stay. But "Lever-free = none of the row kinds remain" — the row kinds are {keepalive}, so only the keepalive must go.

Hmm, but the "no pin" phrase is generic. I think the operative rule is the CONSTRAINTS one: MATCH = the kinds in kinds gone. The pin stays (it was already there, and removing it may not be needed).

Wait, but the item dir's orig.c has the pin; if I keep the pin and remove the keepalive, does it score 0? Let's test.

Also this is a header item: MATCH only if score 0 on every includer (tryinc.py k = 0..n-1). The helper: `.run/P40/T10/tryinc.py <k> <header> <fn> <body>` (header item: k-th includer). So for each includer k, score 0.

Let me check how many includers. Let me look at tryinc.py.

First, test the body with the keepalive removed (pin kept). The target:
```
68bc: beqz v0,68d8
68c0: move a0,s0        ; delay slot: a = arg0
68c4: li v0,3072
68c8: sh v0,16(v1)
68cc: li v0,1
68d0: jal func_80146CA0
68d4: sh v0,184(a0)     ; delay slot: *(u16*)(a+0xb8) = 1
```
Note: `move a0,s0` in the delay slot, then a0 is used at 68d4 as the store base and at the call. The keepalive `a = arg0; asm(r(a))` — with the pin $4, a IS a0. Hmm, the pin makes `a` = $4 (a0). Then `a = arg0` (move a0,s0) and the asm use keeps it live.

But without the pin, `a = arg0` would coalesce with s0 (arg0 is in s0) — the move a0,s0 would disappear, and the store `*(u16*)((u8*)a + 0xb8)` would use s0 directly, and the call arg would be `move a0,s0`. Hmm, but the target has the move in the *delay slot* of the beqz — that's the arg setup for the call, which is needed anyway.

Let me think: target's `move a0,s0` at 68c0 (beqz delay slot) is the call argument setup. With the keepalive removed but the pin kept: `a` is $4; `a = arg0` → move a0,s0; then the store uses a (a0); then the call uses a. So we'd still get move a0,s0 — maybe.

The pin `$4` makes `a` hard a0. Then `a = arg0` is a required move. The keepalive's asm use — is it needed? `a` is used at `*(u16*)((u8*)a+0xb8) = 1` and `func_80146CA0(a)` — real uses. So the keepalive may be redundant!

Wait, but the asm keepalive is placed right after `a = arg0` and before the two stores. Its purpose might be to order the move before the stores (a barrier-ish effect). Let me test removing just the keepalive.

Let me write the body:
```c
void func_80160C28(void *arg0)
{
    s32 p;
    s32 q;
    register void *a __asm__("$4");
    if (func_80161208() == 0) {
        *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
        p = *(s32 *)((u8 *)arg0 + 0x20);
        *(u16 *)((u8 *)p + 0x10) =
            (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
        q = *(s32 *)((u8 *)arg0 + 0x20);
        if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
            a = arg0;
            *(u16 *)((u8 *)q + 0x10) = 0xc00;
            *(u16 *)((u8 *)a + 0xb8) = 1;
            func_80146CA0(a);
        }
    }
}
```

Score it on includer 0 first. Let me check tryinc.py usage.
