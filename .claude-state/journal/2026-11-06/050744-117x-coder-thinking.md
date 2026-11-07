---
ts: 2026-11-06T12:07:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Dtkm2YfrntCTlBpeYmvz
---
Hmm, the remaining dirs (main__func_80016224 etc.) exist — but I didn't use --keep for those. They may be from other coders or leftover empty dirs. I removed only my --keep one. Note: md_MAIN_041__func_800CB3BC appeared after my last sc.sh run? sc.sh without --keep should remove them... The listing shows the dirs exist but maybe empty (the removal only removes `*__fn/p<pid>` subdirs). Not my concern; leave others alone.

Wait — is the `main__func_80016224` dir mine? I didn't use --keep for it, so score_file removed `*/p<pid>` inside. The parent dir remains (empty). Fine, harmless.

Now let me double-check the results.tsv format matches the header: `dir file func kinds result best tries wall evidence`. Let me print the whole file with tabs visible.
