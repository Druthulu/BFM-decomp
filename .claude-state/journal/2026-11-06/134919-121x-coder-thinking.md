---
ts: 2026-11-06T20:49:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xmfJbTb64uH68Pinj4rF
---
So after cse2, insn 92 (the copy) still exists. The .flow dump is a different kind (flow dump doesn't show RTL). The .combine dump shows it gone. So COMBINE deleted it.

Combine's behavior: `try_combine` with i2 = the copy `87 = 72`, i3 = the first use (e.g., `set (mem) (plus 87 10)`). Combine substitutes 72 for 87 in i3, and since 87 is dead after i3? No, 87 is used many times.

Hmm, unless combine's `try_combine` for a 3-insn combination (i1, i2, i3) replaced 87 in ALL its uses via `subst`? Combine does have a mechanism: if i2 is a copy and i1... Actually there's `combine_instructions` → `try_combine (i3, i2, i1)`: it can combine a copy into i3 if `i2dest` is used only in i3 and `i2dest` is dead after i3 (`dead_or_set_p`). If 87 is used later, the merge shouldn't happen.

Wait, maybe combine did it in multiple steps: the first use is `*(s16*)(ent+0xA) = v[1]` (i3). After merging, 87 is still used. Hmm.

Unless the .combine dump's insn 92 shows as `(note 92 ... NOTE_INSN_DELETED)` — yes! In the combine dump: `(note 92 90 94 "" NOTE_INSN_DELETED)` — so insn 92 was deleted and marked as a deleted note.

So combine deleted the copy and rewrote all uses. That's combine's `try_combine` with the "i0/i1/i2" 3-insn window? Or maybe `combine` has a pass that propagates copies globally (`combine_instructions` calls `try_combine` for each i3 and i2; a copy i2 followed by i3 can be merged if i2dest is dead after i3 — but here it's not dead).

Hmm, wait: maybe the copy 87=72 was merged into i3 and then the *other* uses of 87 were also rewritten because... no.

Let me look more carefully: maybe there were multiple copies? The .cse2 shows insn 92 = `87 = 72`. And the uses (101, 126, 131, ...) use 87. After combine, the uses use 72.

Combine's `try_combine (i3, i2, i1)`: it requires `i2dest` used only in i3? There's a check: "If I2DEST is used in I3 but not dead after, we can still combine if..." Hmm, in gcc 2.7.2 combine, `try_combine` checks `if (reg_n_refs[i2dest] != 1)`? Let me grep.

Actually, there's `if (i1 == 0 && ... && (i2dest used once))`. Let me look at combine.c for "i2dest" and "n_occurrences".

Alternatively, maybe the copy deletion is done by `delete_dead_from_cse`? No, that's after cse1 only (and the copy is used).

Hmm, maybe it's `flow`'s `life_analysis` + `delete_dead_insns`? No such function.

Wait — the .combine dump is produced after combine. The copy was deleted somewhere between cse2 and combine: flow_analysis runs before combine. Does flow delete insns? flow.c `life_analysis`... Let me check if flow.c has dead code deletion: `flow_analysis` calls `life_analysis` which computes; there's `delete_dead_insns`? Let me grep flow.c for "PUT_CODE (insn, NOTE)".

Earlier I grepped for delete_dead_insns and found nothing. Let me grep for "NOTE_INSN_DELETED" in flow.c.

Actually, the .flow dump in gcc 2.7.2 shows register life info, not RTL. The RTL after flow isn't dumped separately; the .combine dump shows the RTL after combine. So the deletion could be in flow or combine.

Let me grep combine.c for the copy-merge logic to see the condition, and flow.c for insn deletion.

Actually, a simpler empirical test: I can test whether making `ent` have MANY uses prevents the merge. It already has many uses (10+ stores) and the copy was still deleted. So the merge is not the single-use kind.

Let me grep combine.c for "copy" and "i2dest".
