---
ts: 2026-11-06T16:38:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IqvBeUtvblNrKGHZVVxb
---
Worse. Let me check what w2_hoist produces (maybe the andi stays before the branch).

Actually, let me think differently. The target's allocation requires a pseudo occupying $2 across the ret live range. What about the *first* call's result or the branch structure? 

Hmm, wait. Let me reconsider the whole function: maybe the target's `move v1,v0` is not the call result but something else entirely. Let me look at the pinned build's lreg dump to see what the pins do and where the move comes from. The pinned build = current src (orig.c). Let me dump orig.c.

Actually, with the pins, ret is a hard register $3, so the RTL is `(set (reg:SI 3) (reg:SI 2 v0))` — a hard→hard move, never tied. That confirms the move is the call result copy.

So the target = "call result copied to $3". To get that in plain C, the copy target must be a pseudo that can't take $2.

Given local-alloc's copy suggestion: the pseudo P with the copy suggestion gets $2 unless $2 is occupied over P's range.

What if P is live across a *call*? Then P can't be in $2 ($2 is call-clobbered). P is used at the branch and the andi, no call between. But if we make P live across a call... e.g., the andi is after a call? No.

What if P is also used in the *switch* blocks later (after more calls)? Then P crosses calls → global-alloc would give it a callee-saved reg. Not $3 (caller-saved). Hmm.

OK, what if we make P a *global* (reg/v across blocks) — global-alloc assigns. In the target ret is $3 which is caller-saved; global-alloc for a pseudo live across calls would pick a callee-saved reg. So no.

So P is block-local. Within the block, $2 must be occupied across P's range by Q. Q must be a block-local pseudo with a range covering P's.

Natural Q candidates: the zero_extend result (r16). Can we get a Q without an extra instruction? 

What if the AND's output m is born BEFORE the branch but the andi insn is scheduled after? We tried hoist → the allocation gave... let me check w2_hoist's diff.

Actually, in w2_hoist the andi is before the branch in the RTL, so ret and m overlap. The allocation order matters. Let me see the diff.
