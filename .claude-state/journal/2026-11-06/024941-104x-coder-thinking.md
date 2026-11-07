---
ts: 2026-11-06T09:49:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5y3jh4PsANKYKUouQhHk
---
gg1 and gg4 score 0! These use a *plain empty asm* (`__asm__("");` or `__asm__ __volatile__("");`) — no register operand, no "r" constraint. That's still an asm barrier, not real C. The kind "keepalive" is the asm; the brief says lever-free = no asm of the keepalive kind. gg1/gg4 contain an asm statement, so they are NOT lever-free (they're a new barrier). So they don't count as MATCH.

Interesting: the empty asm (no operands) acts as a barrier? `__asm__("")` without volatile: in sched.c, code == ASM_OPERANDS and MEM_VOLATILE_P false → the barrier branch is skipped. Hmm, but gg1 scored 0. Wait, gg1's asm is `__asm__("");` — a non-volatile asm with no operands. The sched.c branch: `if (code != ASM_OPERANDS || MEM_VOLATILE_P(x))` — for a non-volatile ASM_OPERANDS, skipped. So it shouldn't be a barrier... yet it scored 0. Maybe the empty asm still splits scheduling (an insn with unknown latency blocks?). Whatever — it's an asm, so it's a lever of the keepalive/barrier kind. Not a valid crack.

gg4 = `__asm__ __volatile__("");` — volatile empty asm = a barrier, definitely a lever.

So these confirm the mechanism (a barrier is needed) but are not lever-free.

Interesting that gg2 (`__asm__("" : : "r"(s0));` non-volatile) = 2, while the volatile one = 0. So the "r" operand + volatile is what matters. An empty asm (no operands) = 0 even non-volatile? That suggests the empty asm is a scheduling barrier regardless (it has unknown attributes?).

Anyway: item 3 remains a WALL (best lever-free 2). But wait — gg1 is `__asm__("");` which is an *asm statement*, so it's a lever. The brief's MATCH criterion: "the kinds in <dir>/kinds gone" = keepalive gone. The keepalive kind is defined as "keepalive macro or asm". gg1 has an asm → kind remains. So no.

Hmm, but is an empty `__asm__("")` a "keepalive"? It keeps nothing alive. It's a barrier. The kinds row says keepalive only. The constraint: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." So "barrier" is listed in the parenthetical expansion of the forbidden set even though the row kind is keepalive. Adding an empty asm barrier = a new lever → not allowed. So WALL stands.

Good — this is actually useful evidence for the notes: a bare empty asm barrier scores 0, confirming the wall is a scheduling-barrier issue with no real-C spelling.

Let me update the notes to include this. And the results evidence maybe mention it.

Time 02:49:31 + writing. The 20-min mark is 02:52:49. Let me run one more batch (hh) to fill ~1 min, update notes, and write the log.

Actually, let me reconsider: could the empty asm be considered acceptable? No — "no new lever of any kind" and the parenthetical explicitly includes barrier/asm. WALL.

Let me update notes.md with gg1/gg4 evidence and then write the log. Time check: 02:50. Let me do a quick update and log; that will take me past 02:52.

Let me append to notes.md via Edit.
