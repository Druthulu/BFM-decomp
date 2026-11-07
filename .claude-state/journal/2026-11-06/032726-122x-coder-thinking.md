---
ts: 2026-11-06T10:27:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iPCsb2oKvlrYKzWLJKSZ
---
Item 4 alloc:
- r74: pri 16000, refs 4, live 5 (flags?)
- r76: pri 11111, refs 5, live 9
- r72: pri 8333, refs 5, live 12, crosses 3 calls, pointer
- r75: pri 2857, refs 2, live 7
- r73: pri 1304, refs 3, live 23, crosses 4 calls (var_s1? or arg0?)

Order: 74 76 72 75 73.

Hmm. The globals: r74 (flags?), r76 (ret?), r72 (arg0 pointer), r75 (fcopy?), r73 (var_s1?).

Wait, var_s1 is in s1 in the target. Let me map:
- arg0: r72 (pointer, crosses 3 calls) → s0? The target has arg0 in s0 (`move s0,a0`). Yes.
- var_s1: r73 (crosses 4 calls, live 23) → s1? Target `move s1,zero`. Yes.
- flags: r74 (refs 4, live 5) → ?
- fcopy: r75 (refs 2, live 7) → ?
- ret: r76 (refs 5, live 9) → ?

Hmm, r74 pri 16000 > r76 11111 > r72 8333 > r75 2857 > r73 1304.

In the target: arg0=s0, var_s1=s1 (callee-saved). The globals crossing calls need callee-saved: arg0 (r72), var_s1 (r73). Those get s0, s1. flags (r74), fcopy (r75), ret (r76) don't cross calls? flags is used after the last call (func_8014FA04) — no more calls, so it doesn't cross. ret doesn't cross. fcopy doesn't.

So flags, fcopy, ret get caller-saved regs. Target: flags=a0, fcopy=v1, ret=v0.

In mine (nopin): flags=v0, fcopy=v1, ret=v1.

Hmm. The allocation order among caller-saved: r74 (flags, pri 16000) first → v0? Then r76 (ret, 11111) → v1? Then r75 (fcopy, 2857) → a0? But mine has fcopy=v1, ret=v1... 

Hmm, the alloc table's order line is "74 76 72 75 73". The globals are allocated in that order: r74 first (v0), r76 (v1), r72 (s0?), r75 (a0?), r73 (s1?).

Hmm, but r72 and r73 cross calls → callee-saved. r74, r76, r75 → caller-saved (v0, v1, a0).

So mine: flags(r74)=v0, ret(r76)=v1, fcopy(r75)=a0. But the asm showed `move v1,v0` (fcopy=v1?) and ret in v1. Hmm, my mapping might be wrong.

Let me identify by looking at the lreg. Ugh.

Actually, let me take a different approach: the target has flags=a0, fcopy=v1, ret=v0. If I can reorder the priorities so that ret (r76) gets v0 and flags (r74) gets a0...

The target's allocation: ret=v0 (pri?), flags=a0, fcopy=v1.

For ret to get v0, ret must be allocated first among the caller-saved. ret's priority must be highest.

Hmm, the pin makes fcopy a hard reg (v1), which removes it from the competition and also changes flags/ret priorities.

Lever-free, the competition gives flags=v0, ret=v1, fcopy=a0 (or similar).

To make ret=v0: increase ret's priority or decrease flags's.

ret's refs: defined in 3 places (ret=2, ret=1, ret=4, ret=var_s1) and used at return. refs 5, live 9.
flags's refs: def (call), fcopy=flags (use), flags&0x4000 (use), flags&0x2000 (use), keepalive (use) = 5? The table says 4. live 5.

flags pri 16000 (refs 4, live 5), ret pri 11111 (refs 5, live 9).

If flags's refs dropped to 3: floor_log2(3)=1, 1*3/5 = 0.6 → 6000 < ret 11111 → ret gets v0! 

How to reduce flags's refs? flags is used in: `flags = call` (def), `fcopy = flags` (use), `flags & 0x4000` (use), `flags & 0x2000` (use) = 4 (the keepalive is removed in nopin).

If I use `fcopy` for one of the tests instead of flags, flags's refs drop to 3:
```
if (fcopy & 0x4000) ...   // instead of flags
```
But the target uses `flags & 0x4000`? Actually, the target's `andi v0,a0,0x4000` uses a0=flags. And `andi v0,a0,0x2000` uses a0=flags. So the target uses flags for both tests, and fcopy for the &0x8000.

Hmm, but fcopy == flags, so the compiler can use either. If I write `fcopy & 0x4000` in C, the compiler might still use flags (cse). Hmm.

Alternatively, reduce flags's live length. flags's live is 5 (short). ret's live is 9. Hmm.

Let me reconsider: the target has flags=a0. a0 is the 3rd caller-saved (after v0, v1). So in the target, v0 and v1 were taken at flags's allocation. v0 → ret? v1 → fcopy (hard). So flags gets a0.

In mine, flags gets v0 (first). Why? Because ret and fcopy are allocated after flags (lower priority). 

So to match the target, flags must be allocated AFTER ret and fcopy. I.e., flags's priority must be LOWER than ret's and fcopy's.

flags pri 16000. ret 11111. fcopy 2857. So flags is highest → gets v0.

To lower flags's priority below ret's (11111): reduce refs or lengthen live. flags refs 4, live 5 → 16000. If live were 8: 1*4/8 = 5000 < 11111. 

flags's live: from the call result (def) to the last use (flags & 0x2000). If I extend flags's live by moving a use later... The &0x2000 test is in the else-if. Hmm.

Or reduce refs to 3: 1*3/5 = 6000 < 11111.

How to reduce flags's refs from 4 to 3? The uses: `fcopy = flags` (1), `flags & 0x4000` (2), `flags & 0x2000` (3). Plus the def.

If I write the tests using `fcopy` instead of `flags`:
```
fcopy = flags;
if (fcopy & 0x4000) ...
else if (fcopy & 0x2000) ...
```
Then flags's refs = def + fcopy=flags = 2. And fcopy's refs = def + 3 uses = 4. Then flags pri = 1*2/5 = 4000 < ret 11111 → ret gets v0. And fcopy pri = floor_log2(4)*4/live.

But the target uses flags (a0) for the tests, not fcopy (v1). Hmm, but the compiler could cse fcopy and flags into the same register/value. If fcopy and flags are the same value, gcc might use one register for both. In the target, flags=a0 and fcopy=v1 (different). So they're different registers.

Hmm, if I use fcopy for the tests, gcc would use v1 for the tests, not a0. That would differ from the target (which uses a0).

Hmm. But wait — maybe the compiler would cse `fcopy & 0x4000` and `flags & 0x4000` to the same value, using whichever register. Let me just test it.

Let me try:
- m1: tests use fcopy instead of flags.
- m2: `if (flags & 0x4000)` → `if (fcopy & 0x4000)`, `else if (fcopy & 0x2000)`.
- m3: reduce flags's live by computing fcopy = flags later.

Let me test m1.

Also, I should consider the keepalive replacement: the keepalive on flags anchors it. Without it, the `flags & 0x4000` might be reordered.

Let me test m1 first.
