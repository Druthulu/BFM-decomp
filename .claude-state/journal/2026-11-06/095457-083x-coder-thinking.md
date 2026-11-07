---
ts: 2026-11-06T16:54:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T9K7jfQxqd5kPnaU6ksI
---
Item 4 has two row kinds: keepalive and launder. Plus other-kind levers: pins (a0 $16, t0 $3, t1 $4, t2 $5) and a launder `__asm__("" : "=r"(s) : "0"(s))` (which is a launder too! It's marked "!FAKE: launder"). So the row kinds include launder — both launder asms must go. And the keepalive.

So lever-free means removing:
1. `__asm__("" : "=r"(s) : "0"(s));` (launder, keep base in reg)
2. `__asm__ __volatile__("" : : "r"(t0), "r"(t1));` (keepalive/sched barrier)
3. `__asm__ __volatile__("" : "=r"(q));` (launder out-only, cse remat kill)

The pins (a0 $16, t0 $3, t1 $4, t2 $5) are other-kind (pin) — allowed to stay.

Let me baseline and remove each to see the residuals.

The target:
- `lw s1,32(s0)` — p in $s1
- rand, index, func_8001CC3C
- the m = D_800AE620 copy: lw v1/a0/a1 from a2, sw to sp — this is the hand-expanded copy with t0=$3(v1), t1=$4(a0), t2=$5(a1).
- RotMatrixY: `move a0,sp+32` (a1 = sp+32 in the delay slot), then `addiu a1,sp+16; move a2,a1; li v0,0x4000; sw v0,16(sp); sw zero,24(sp); jal func_800484EC; sw zero,20(sp)`.
- The launder `q` is for cse remat: `q = &m; RotMatrixY(ang&0xFFF, q);` — the launder kills cse's remat of &m so that &m is materialized once? Hmm.

Let me test the baseline and each removal.
