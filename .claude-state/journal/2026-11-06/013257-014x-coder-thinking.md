---
ts: 2026-11-06T08:32:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZztaW1OYa3BrsMqzYHPK
---
Now cwd is project root. Good.

The explain reads the current src (with keepalive, which is a lever?) and says score 4 with the keepalive NEEDED — interesting: it seems --explain evaluated the *lever-free* variant? No wait: it says score 4, mine 58 ins... and "site keepalive line 2289 NEEDED". Hmm, it might be showing the residual of the body with levers removed? Actually it says score 4 for the current body which dt.sh scored 0. So --explain strips levers first (the "delever" search) and reports the residual + which levers are NEEDED.

So it reports: without the keepalive, mismatch is: target has `addiu a0,sp,24` in the beqz delay slot; mine has nop there and the addiu in the bnez delay slot.

So I need real C that makes the address computed before the inner test (i.e., available as a live value at the first branch).

Options in real C: The address must be computed before `if (D_801270CC == 0)` and stay live across it. In the inner block it is used at the call. If I write the code such that the pointer is used *after* the inner if too (live across), gcc might still sink the single use to the call... Actually a value used at one point gets rematerialized there. To force early materialization, the pointer must be used at a point before the branch (a use that requires the value).

What real C use of `sp18`'s address exists before the inner if? Hmm.

Alternative: maybe the target actually computes the address for a different reason: maybe `func_8012C51C` is called with `sp18` and the original source had the call arguments computed before, e.g., `func_8012C51C(sp18, param_1)` where the first argument's address is loaded early because the second argument `param_1`... no.

Alternatively, maybe target's `addiu a0,sp,24` is not the call arg at all — maybe it's a store base for `sp18[0] = ...`? Stores use 24(sp) immediate offset, so no.

Let me look at the actual target disassembly around there to understand. Where does the target binary live? `build/`. The delever_search compares with the function in build/. Maybe there's a tool to dump the target function. `.run/P40/T10/hdump.sh` is header dumps. tools/cc1_dumps_tu.sh gives TU dumps (my compile). For target objdump, perhaps the item dir has a way. Let me check what the item dirs in T10 worked examples had, e.g., func_80181F4C dir contents.
