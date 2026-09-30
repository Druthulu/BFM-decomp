# Struct twins

`tools/type_census.py --check-structs` reads this file (`TWINS_DOC`). G62: layout twins without evidence stay apart.

- `## Twins`: one `### <lhash>` section per tier-2 duplicate row (plain or `<lhash>:opaque`) kept as separate types, with a
  `names:` line (the row's names, as a set) and a `cause:` line naming at least one address (8 hex digits or `0x…`). A listed
  row does not count in `dup_classes`. An absent lhash, a name-set mismatch or an addressless cause counts in `twins_stale`.
- `## Dead kept`: `- Name — cause` bullets; a listed canon name does not count in `dead`. A name that is not dead or no longer
  defined in the canonical headers counts in `twins_stale`.

## Twins

## Dead kept
