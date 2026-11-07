---
ts: 2026-11-06T12:26:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TmxHZKbo9VDk6GZPa3AG
---
own_thread_p(thread=NEXT_INSN(insn), NULL_RTX, allow_fallthrough=1): scans from the insn after the jump up to the "first active insn"... wait, `active_insn = next_active_insn(PREV_INSN(thread))` = the first active insn at/after thread. Loop `for (insn = thread; insn != active_insn; ...)` checks the notes between thread and the first active insn for CODE_LABEL. Hmm, that loop only runs over non-active insns (notes) between NEXT_INSN(jump) and the first active insn. So it returns 0 if there is a CODE_LABEL right after the jump (a label before the first active insn). With allow_fallthrough=1, after that check it returns 1.

So own_fallthrough is 1 unless there's a label immediately after the branch. Hmm — a label right after the branch: e.g., if the then-arm has a label at its start that is used elsewhere... Actually a CODE_LABEL between the jump and the first active insn. Normally there's a NOTE_INSN_BLOCK_BEG maybe, no label. So own_fallthrough=1.

So we need `delay_list == 0` from fill_slots_from_thread(fallthrough...), i.e. the fall-through's first insn is not eligible or not safe. Let me read fill_slots_from_thread to see the conditions.
