---
ts: 2026-11-06T09:14:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zwX4ukihIlFHYqRN4JEe
---
Target's tail: `lui v1; lw v1; nop; beqz v1,L; move v0,zero; lui v0; addiu v0; L:`. So res ends in v0 — naturally! Because res's set is a block-local pseudo and v0 is free (void fn, no calls after). So the pin is removable for item 2 — the lever-free body naturally allocates res to v0!

But wait, my lever-free body produced NO tail at all: flow deleted `res = 0` and `res = &D` because res is dead (only the keepalive used it). Right: without the keepalive, res is dead → deleted. So I need to keep res alive without a lever. The target has res live in v0 because... the original code must have used res in a real way: the original function probably returned it! `return res;` — but void fn drops it.

Hmm, but the target keeps the value. So the original source's last statement was a real use of res. What real use produces no extra instruction beyond the moves already there? A `return res;` in a void function: expand_return expands res for side effects only — but `expand_expr(retval, NULL_RTX, VOIDmode, 0)` still *evaluates* res? Evaluating a variable reference has no side effect, so it produces nothing, and res becomes dead → deleted. But the target keeps it. So the original wasn't `return res;` in a void function... 

Unless the original function was NOT void (the extern void in the TU is a port artifact), and the original had `return res;` with a pointer return type. Then the target's `move v0,...` is the return.

So to reproduce without a signature change, we need res to be live. Options: make the final use a real C statement. What if the last statement is `if (res == 0) return;`? That produces `beqz v0,...` extra. No.

What if res is *assigned to something with side effects*? Like `*(s32**)x = res`? extra store.

Hmm. What about making res's value feed the *return of a call argument*? no.

So again expand-void-return.

Hmm wait. What about using the value as the argument to the *last call* `func_801F0E9C()`? No, that's void and before.

OK, hold on. Let me reconsider the whole task framing. This is a "singleton crack shard" — the G26 list is a shard of items each having keepalive,pin, with a line count (23, 56, 139, 29, 26). The expectation from the mod: crack some, wall others. The rules for WALL are strict (≥30 tries, ≥20 min) — presumably to prevent lazy walls.

But maybe the intended crack for these "value in v0" items is a real-C move: the *original source* likely had the function return a value and the port used void because callers don't use it. But the constraint says callers stay as they are — that's about call sites, not the extern decls? "no signature or decl change outside the body (callers stay as they are)". Hmm, changing the file-scope extern `extern void func_800CD5CC(void *a0);` to `extern s32 ...` is a decl change outside the body. Forbidden explicitly.

Unless the extern is *unused* by callers! At line 146, is func_800CD5CC called after that extern with the void declaration? Line 162 calls it via cast `((s32 (*)(void *))func_800CD5CC)(arg0)`. The extern at 146 declares the symbol; calls use casts. If we changed line 146 to s32, would any caller break? Probably not, but it's still a decl change outside the body.

Hmm, wait. Maybe the trick is that the extern at 146 is *inside a function body* (block-scope extern), which is still outside our function's body. Forbidden.

Let me re-read the exact constraint once more: "no signature or decl change outside the body (callers stay as they are)". I read this as: don't change the signature or declarations outside the body. So no.

Therefore: item 2 = WALL expand-void-return, best ? Let me see what PARTIAL/keepalive-only scores for item 2. Keep keepalive only (res ordinary local): res = 0; ...; asm(res). The asm forces res live; local-alloc may put res in v0 (block-local, no calls after) → target! Let me test: keep the keepalive asm but drop the pin. Then res is a plain `s32 *res` used by the asm. That's PARTIAL:keepalive if score 0.

Let me test.
