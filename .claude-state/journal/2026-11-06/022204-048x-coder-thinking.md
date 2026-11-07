---
ts: 2026-11-06T09:22:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q1HQBQndPa38jC3BYoiM
---
The pre-P36 version (c53a9e1a91, phase 35) might have the original C body without the P36-added levers. Let me look at the header as of c53a9e1a91. But that version is the converted macro body — the same C, possibly without the keepalives (P36 added "delever" moves — actually P36 batch headers1 *removed* levers; the commit says "sites removed 302 / needed 340". So P36 was a delever attempt that couldn't remove these, leaving them marked !FAKE. Hmm, actually P36 "delever: batch headers1" — it tried to remove levers and for 158 bodies left residue (needed levers). So the keepalives existed before P36 (from P35 or earlier) or P36 added them as replacements for other levers.

Let me check the P35 version of this header.
