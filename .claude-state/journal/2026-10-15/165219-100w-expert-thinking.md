---
ts: 2026-10-15T22:52:19.496Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6182af38cb3c98e2
model: claude-opus-5-5[1m]
effort: medium
turnId: 4c23aba1-6a33-47ae-8736-5fe6093d69e7
---
I notice many collisions share the same owner function, like Unkstruct_8015D738 and _2 having identical layouts within one function — likely two parameters of the same struct type that never got unioned since there's no data flow between them. That's suggestive evidence of same-entity status by owner and layout, but still not something E1/E2/E3 would catch directly.

I'm realizing the struct_twins entries are tied to the TNC use sites per map type, so until T4/T5 respell the bodies, the honest cause to write is that these are T3 band defs, dead until rung S, tied to their owning function and map type. Citing the owner function's address as the cause is factually grounded — it reflects where that map type's TNC sites actually live — so the census can honestly treat these as per-type rather than per-layout, with G62 satisfied since no entity link was found, keeping dup-def counts at zero.

Now I'm considering Tier 1: a new def that's an exact layout duplicate of an existing named canonical type. Folding on layout alone here violates G62, since the project's rule is that exact dups of named types must fold structurally, not just by shape — so these can't simply be defined or folded, and none of the four residual classes cleanly fits this case.

I'm weighing whether to add a fifth residual class, like `TYPE-TWIN-CANON`, for canonical dup-without-evidence cases. This extends policy beyond what the done-when criteria foresaw, but it doesn't weaken any existing check — it just names a gap case honestly, which feels like the right minimal move rather than forcing it into an ill-fitting category.

Given the developer is active and wants progress, asking would cost a round trip I can't justify. I'll make the call myself: name it `TYPE-CANON-TWIN` with evidence `layout-twin:<canon name>`, marking it as residual with same layout as the canonical class but no entity evidence, keeping the fold requirement (E1-E3) intact. This respects the no-fold-on-layout rule and the tier-1 dedup gate, and I'll flag the decision in Deviations for review. I also note tier classification: since T3 defs are all placeholder-named, any T3-only class falls under tier 2, not tier 1.

For c3's implementation (c2's work is done, so c3 is a fresh coder continuing from c2's log/patch): the plan is to have restruct.py compute a layout hash on the rendered definition and compare it against existing non-placeholder canonical defs' hashes using census's lhash function. A match triggers the TYPE-CANON-TWIN residual with the layout-twin evidence tag. The coder will need to consult the tier rule in type_census to determine what qualifies as tier 1.

Beyond that, struct_twins.py needs UNBOUND citations for T3 define targets, pulled from census sites via the map type lookup and formatted as U evidence with addresses. Then I need to update selftests, the kit-corpus, and docs, before running the batches following c2's procedure — likely splitting the work so c3 handles the tool fix plus batch 1, while c4 covers batches 2-3, though one coder could plausibly do all three given the per-batch timing.

There's also a scratch script, `.run/P40/t3/dead_kept.py`, putting dead names into docs — rather than leaving it as a one-off, I think it's better to fold that behavior into decide --write so the mode appends its define targets to the Dead kept section directly, keeping things reproducible. I'll ask c3 to make that change.

Now I'm drafting the brief with pointers to c2's log, the patch, the gating tsv, and the relevant line ranges in type_census.py and struct_twins.py.

I'll resolve the batch-1 stop by having struct_twins.py cite census use-site addresses for Tier-2 class twins, while Tier-1 twins (identical to an existing canonical def) become residual under a new `TYPE-CANON-TWIN` class with evidence `layout-twin:<name>`—I'm flagging this new class as a deviation for Claude to judge.
