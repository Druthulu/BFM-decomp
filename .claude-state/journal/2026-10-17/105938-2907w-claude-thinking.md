---
ts: 2026-10-17T16:59:38.562Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: a929cb8c-c58d-4431-838f-471430491695
---
I need to note a T14 add-on for the wiki pages on starting decomp projects and AI-assisted decomp, enforcing structs-as-you-go and the no-levers-unless-walled rule plus the naming tier convention. For this specific project at version 3.43, I should flag the developer's suggestion to allow unk_ guesses, which changes the generation plan and needs confirmation, and the 3.42 scanner will need to handle guessed names with citation requirements.

I'm realizing the unk_ prefix might clash visually with existing unkXX field placeholders and Unkstruct_, since those mean "nothing known" while unk_ would mean a guess — I should flag this and suggest a distinct prefix like guess_ instead, giving the developer a picker with options for adopting unk_ as-is, adopting a distinct prefix, or leaving docs-only for now. I also need to record this change in the plan via an append, and add a card line about the developer's durable preference for best-guess names over placeholders, keeping an eye on the character limit which should still have room.
