---
ts: 2026-11-06T09:11:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xWnWNpMeHc3FNPdWQdaI
---
Interesting: p2 (keepalive-only) already has s4! Let me see the full dump. It uses s0=p, s1=a0, s2=found/rv, s3=t, s4=end. Wait the frame is 48 and saves s0-s4, ra at 44. So p2 has all the right registers; only missing `move v0,s2`. So rv coalesced with found into s2 and the asm uses s2 directly.

So the only missing instruction is a move to v0. What produces that in real C without pin? If the asm required rv in a specific reg... no.

Hmm! What about `rv` being the *return value* of the function: void function... 

Wait, actually: what if the last statement is a *call* to `func_800CD6A4(a0, found)`? Not target.

What if `rv` is used as an argument to `func_80015978`? no.

Alternative: make `found` itself be assigned to v0 via a *conditional expression* returning? no.

Let me think about GCC 2.7.2 codegen: `move v0,s2` where s2 holds the value. This is the classic "function returns value" pattern. In a void function, `return;` emits nothing. In a void function with `return found;` GCC 2.7.2 apparently dropped it (score 19, found dead).

What about a *non-void* function whose definition is compatible with the extern void? Impossible in C.

Hmm, what if we declare the function as `s32 func_800CD5CC()` and line 146's extern void... error.

OK here's another thought: is line 146's extern maybe not in this TU's compile? Let me check whether md_MAIN_046.c is the TU (yes, tu = src/md_MAIN_046/md_MAIN_046.c). Line 146 is in it.

Could we make the definition appear in a way that line 146's extern is in a *different* function's body scope? No, it's file scope.

So WALL. But wait — maybe the expected crack here is not the return but something else entirely: maybe the target's `move v0,s2` is NOT needed for a byte-identical match if we restructure the loop so found is used differently... no, target is fixed bytes; we must produce 54 insns exactly.

Unless the match criterion is score 0, which means byte-identical to the baseline object (the current src build). Yes.

Therefore item 1 = WALL (expand-void-return) with best 1, unless signature change allowed. Let me check whether other items in this shard have a similar issue; but first, the budget rule for WALL: ≥20 min and ≥30 scored tries. Ugh. That's a lot of tries. But the rule is binding. Let me consider: maybe I should attempt ≥30 variants quickly. sc.sh scores each file; I can generate variants programmatically? "Scripts, not inline python -c" — I can write a script under my shard dir.

But before investing, let me check whether maybe there's a known crack: grep moves.md for "expand-void-return" entries and read one to see if any cracked.
