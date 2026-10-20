---
ts: 2026-10-17T17:27:01.338Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I've got that partial result secured, so now I'm exploring more variations on the s3v/s4v swap—checking whether declaration order matters, and testing what happens if I reduce s4v's weighted references by removing loop weighting from the outer loop, which would still leave s4v ahead of s3v but shift other allocnos too.

Computing the exact weighted reference counts: s4v has 7 unweighted refs versus s3v's 5, so that approach doesn't flip the order. But I realize gcc's reorg can steal an instruction from a jump target when filling a delay slot—if the default case jumps to the shared increment point, the `addiu s4,s4,1` could get absorbed into the delay slot and the jump redirected past it, collapsing s4v's increment into a single occurrence. That would drop s4v's weighted score below s3v's, flipping the priority order I need, so I'm working out whether restructuring the switch's default/break paths to fall through to that shared increment would actually produce this effect.
