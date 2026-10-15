---
ts: 2026-10-15T04:46:30.633Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7996093418d381a4
model: claude-opus-5-5[1m]
effort: medium
turnId: 709b2f04-d315-4060-ba93-85c3894dd69d
---
So the 5,482 figure covers sites of any cause. Now I want to break down Unkstruct_80126B58 sites by stamped ledger cause and compute live residue cause, plus check fleet-wide how many TNC stamped sites have a map type that's now canonical—stale stamps—since that matters for understanding how much of TNC is just stale stamping. I'll write a scratch script using type_census to get these numbers.

Looking more closely at residue_split, the cause computation keys pools by form, base, and offset, while the site's "type" field actually refers to the map type. So residue_cause pulls from s["type"] for the map type, but site_class needs more context than that—for the anomaly check, I just need to verify canon membership and visibility.

I confirmed that `top_types` ranks covered sites by map type regardless of cause, so "80126B58 5,482" isn't actually a TNC count. I'll now break those sites down by stamped cause against the live predicate and tally fleet-wide TNC stamps whose type is canonical today.
