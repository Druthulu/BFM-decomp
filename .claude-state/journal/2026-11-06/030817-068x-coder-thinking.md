---
ts: 2026-11-06T10:08:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pGmhAmiL0tw2K4axVsq1
---
`if (! CONST_CALL_P (insn)) flush_pending_lists (insn);` — CONST_CALL_P means the call is to a `const` function (declared with `__attribute__((const))` or `const` keyword in some form). If the call IS const, memory is NOT flushed → loads can be hoisted above it!

Is `ratan2` declared const? In the header, `extern s32 ratan2(s32 a0, s32 a1);` — not const. But maybe elsewhere in the TU, ratan2 is declared with `__attribute__((const))` or there's a `#pragma`. Hmm.

Actually, CONST_CALL_P checks `find_reg_note (insn, REG_... )` or the SYMBOL_REF's `SYMBOL_REF_FLAG`? Let me check CONST_CALL_P definition. It might be set when the call is to a function known not to touch memory (const attribute).

But hold on — this is about sched1. Even if loads could be hoisted, we'd need them to be hoisted in the right order.

Hmm, this is getting really deep. Let me step back and consider the time budget. I've spent a while on item 2. Let me check the overall time: started 02:54. Let me check now.

Actually, let me reconsider the possibility that the original source computed u6 AFTER the call, and sched1 hoisted the load because ratan2 is a const call. Let me test v2 more carefully — v2 scored 32, but maybe the ordering issue is elsewhere.

Actually, let me reconsider: in v2 (load after call), the score was 32. Let me look at v2's full diff to see how it differs. If the loads ended up in the right place but registers differ, maybe v2 is closer. Let me run dt.sh with a big tail on v2.

Let me do that.
