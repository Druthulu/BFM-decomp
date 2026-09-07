// ImportAnnotations.java — headless: apply an annotations JSON-Lines file (ExportAnnotations.java's format,
// normally the committed config/ghidra/<program>.jsonl) to the current program. The inverse of the export;
// idempotent (compare-before-write everywhere); run WITHOUT -readOnly so analyzeHeadless commits + saves
// on exit (the ApplySymbols.java precedent). P33 B5.
//
//   analyzeHeadless <proj_dir> bfm -process <PROG> -noanalysis \
//     -scriptPath tools/ghidra_scripts -postScript ImportAnnotations.java <in.jsonl>
//
// Refuses (R43) a file whose `program` row names another language / image base, and any row kind it does
// not know — nothing is applied in that case. Prints one BFMANN summary line with every counter.
// Types are applied in two passes (shells first, then fields) so self- and mutually-referencing structs
// resolve; type strings are Ghidra path names with pointer/array suffixes (`/BFM/Actor *[4]`).
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.util.CodeUnitInsertionException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class ImportAnnotations extends GhidraScript {
    private static final Set<String> KINDS = new HashSet<>(Arrays.asList(
            "program", "block", "archive", "type", "func", "data", "comment", "bookmark", "equate", "label"));
    private int nTypes, nFuncs, nData, nComments, nBookmarks, nEquates, nLabels, unchanged, failed, skippedStorage;
    private DataTypeManager dtm;

    private static String s(JsonObject o, String k) { JsonElement e = o.get(k); return (e == null || e.isJsonNull()) ? null : e.getAsString(); }
    private static boolean bo(JsonObject o, String k) { JsonElement e = o.get(k); return e != null && !e.isJsonNull() && e.getAsBoolean(); }
    private static int in(JsonObject o, String k) { JsonElement e = o.get(k); return (e == null || e.isJsonNull()) ? 0 : e.getAsInt(); }
    private Address addr(String hex) { return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(Long.decode(hex)); }

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args == null || args.length < 1) { println("BFMANN ERROR: usage <in.jsonl>"); return; }
        List<JsonObject> rows = new ArrayList<>();
        for (String ln : Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8)) {
            if (ln.trim().isEmpty()) continue;
            JsonObject o = JsonParser.parseString(ln).getAsJsonObject();
            String k = s(o, "k");
            if (k == null || !KINDS.contains(k)) { println("BFMANN ERROR: unknown row kind " + k + " — nothing applied (R43)"); return; }
            rows.add(o);
        }
        for (JsonObject o : rows) {
            if (!"program".equals(s(o, "k"))) continue;
            String lang = s(o, "lang");
            long base = Long.decode(s(o, "image_base"));
            if (!currentProgram.getLanguageID().getIdAsString().equals(lang) || currentProgram.getImageBase().getOffset() != base) {
                println("BFMANN ERROR: file is for " + lang + " @" + s(o, "image_base") + " but the program is "
                        + currentProgram.getLanguageID().getIdAsString() + " @" + currentProgram.getImageBase() + " — nothing applied (R43)");
                return;
            }
        }
        dtm = currentProgram.getDataTypeManager();
        // pass 1: type shells; pass 2: type bodies (so fields can reference any struct in the file)
        List<JsonObject> types = new ArrayList<>();
        for (JsonObject o : rows) if ("type".equals(s(o, "k"))) types.add(o);
        for (JsonObject o : types) typeShell(o);
        for (JsonObject o : types) typeBody(o);
        for (JsonObject o : rows) {
            String k = s(o, "k");
            try {
                switch (k) {
                    case "func": func(o); break;
                    case "data": data(o); break;
                    case "comment": comment(o); break;
                    case "bookmark": bookmark(o); break;
                    case "equate": equate(o); break;
                    case "label": label(o); break;
                    default: break;   // program/block/archive/type handled above
                }
            } catch (Exception e) {
                failed++;
                println("  fail " + k + " " + (s(o, "addr") != null ? s(o, "addr") : s(o, "name")) + ": " + e);
            }
        }
        println("BFMANN types=" + nTypes + " funcs=" + nFuncs + " data=" + nData + " comments=" + nComments
                + " bookmarks=" + nBookmarks + " equates=" + nEquates + " labels=" + nLabels + " unchanged=" + unchanged
                + " skipped_storage=" + skippedStorage + " failed=" + failed + " rows=" + rows.size());
    }

    // ---- data types ----
    private static CategoryPath catOf(String path) {
        int i = path.lastIndexOf('/');
        return new CategoryPath(i <= 0 ? "/" : path.substring(0, i));
    }
    private static String nameOf(String path) { return path.substring(path.lastIndexOf('/') + 1); }

    /** Resolve a Ghidra path name with optional pointer/array suffixes (`/u8 *[4]`) to a DataType. */
    private DataType resolveType(String spec) {
        String base = spec;
        int cut = -1;
        for (int i = 0; i < spec.length(); i++) {
            char c = spec.charAt(i);
            if (c == '[' || (c == '*' && i > 0 && spec.charAt(i - 1) == ' ')) { cut = i; break; }
        }
        String suffix = "";
        if (cut >= 0) { base = spec.substring(0, cut).trim(); suffix = spec.substring(cut); }
        // "/undefined" is Ghidra's DefaultDataType (DataType.DEFAULT) — the default return/param type of every
        // analysis-created function; it lives in NEITHER data type manager (S87: 13 of main's 13 func rows failed on it).
        DataType dt = (base.equals("/undefined") || base.equals("undefined")) ? DataType.DEFAULT : dtm.getDataType(base);
        if (dt == null) dt = BuiltInDataTypeManager.getDataTypeManager().getDataType(base);
        if (dt == null && !base.startsWith("/")) dt = dtm.getDataType("/" + base);
        if (dt == null) throw new IllegalArgumentException("unresolvable type " + spec);
        int i = 0;
        while (i < suffix.length()) {
            char c = suffix.charAt(i);
            if (c == ' ') { i++; continue; }
            if (c == '*') { dt = new PointerDataType(dt, dtm); i++; continue; }
            if (c == '[') {
                int j = suffix.indexOf(']', i);
                int n = Integer.parseInt(suffix.substring(i + 1, j).trim());
                dt = new ArrayDataType(dt, n, dt.getLength(), dtm);
                i = j + 1; continue;
            }
            throw new IllegalArgumentException("bad type suffix in " + spec);
        }
        return dt;
    }

    private void typeShell(JsonObject o) {
        String kind = s(o, "kind"), path = s(o, "path");
        CategoryPath cat = catOf(path); String name = nameOf(path);
        if (dtm.getDataType(path) != null) return;
        DataType dt;
        switch (kind) {
            case "struct": dt = new StructureDataType(cat, name, in(o, "size"), dtm); break;
            case "union": dt = new UnionDataType(cat, name, dtm); break;
            case "enum": dt = new EnumDataType(cat, name, in(o, "size"), dtm); break;
            case "typedef": dt = new TypedefDataType(cat, name, resolveType(s(o, "base")), dtm); break;
            case "fndef": dt = new FunctionDefinitionDataType(cat, name, dtm); break;
            default: failed++; println("  fail type " + path + ": unsupported kind " + kind); return;
        }
        dtm.resolve(dt, DataTypeConflictHandler.REPLACE_HANDLER);
        nTypes++;
    }

    private void typeBody(JsonObject o) {
        String kind = s(o, "kind"), path = s(o, "path");
        DataType dt = dtm.getDataType(path);
        if (dt == null) return;
        try {
            if ("struct".equals(kind) && dt instanceof Structure) {
                Structure st = (Structure) dt;
                boolean packed = bo(o, "packed");
                if (st.isPackingEnabled() != packed) st.setPackingEnabled(packed);
                if (!packed && st.getLength() != in(o, "size")) { st.deleteAll(); st.growStructure(in(o, "size")); }
                for (JsonElement fe : o.getAsJsonArray("fields")) {
                    JsonObject f = fe.getAsJsonObject();
                    DataType ft = resolveType(s(f, "type"));
                    DataTypeComponent cur = st.getComponentAt(in(f, "off"));
                    if (cur != null && cur.getOffset() == in(f, "off") && Objects.equals(cur.getFieldName(), s(f, "name"))
                            && cur.getDataType().getPathName().equals(ft.getPathName()) && cur.getLength() == in(f, "len")
                            && Objects.equals(cur.getComment(), s(f, "comment"))) { unchanged++; continue; }
                    if (packed) st.add(ft, in(f, "len"), s(f, "name"), s(f, "comment"));
                    else st.replaceAtOffset(in(f, "off"), ft, in(f, "len"), s(f, "name"), s(f, "comment"));
                }
            } else if ("union".equals(kind) && dt instanceof Union) {
                Union u = (Union) dt;
                if (u.getNumComponents() == 0)
                    for (JsonElement fe : o.getAsJsonArray("fields")) {
                        JsonObject f = fe.getAsJsonObject();
                        u.add(resolveType(s(f, "type")), in(f, "len"), s(f, "name"), s(f, "comment"));
                    }
                else unchanged++;
            } else if ("enum".equals(kind) && dt instanceof ghidra.program.model.data.Enum) {
                ghidra.program.model.data.Enum e = (ghidra.program.model.data.Enum) dt;
                for (JsonElement ve : o.getAsJsonArray("values")) {
                    JsonObject v = ve.getAsJsonObject();
                    String n = s(v, "name"); long val = v.get("value").getAsLong();
                    if (e.contains(n) && e.getValue(n) == val) { unchanged++; continue; }
                    if (e.contains(n)) e.remove(n);
                    e.add(n, val);
                }
            } else if ("fndef".equals(kind) && dt instanceof FunctionDefinition) {
                FunctionDefinition fd = (FunctionDefinition) dt;
                fd.setReturnType(resolveType(s(o, "ret")));
                List<ParameterDefinition> ps = new ArrayList<>();
                for (JsonElement pe : o.getAsJsonArray("params")) {
                    JsonObject p = pe.getAsJsonObject();
                    ps.add(new ParameterDefinitionImpl(s(p, "name"), resolveType(s(p, "type")), s(p, "comment")));
                }
                fd.setArguments(ps.toArray(new ParameterDefinition[0]));
                fd.setVarArgs(bo(o, "varargs"));
                String cc = s(o, "cc");
                if (cc != null) try { fd.setCallingConvention(cc); } catch (Exception ex) { /* unknown cc: keep default */ }
            }
        } catch (Exception e) {
            failed++; println("  fail type body " + path + ": " + e);
        }
    }

    // ---- functions ----
    private VariableStorage storageOf(String spec) {
        // "Stack[-0x10]:4" | "a0:4" | "s0:4" ... ; anything else -> null (dynamic storage)
        try {
            if (spec.startsWith("Stack[")) {
                int j = spec.indexOf(']');
                int off = Long.decode(spec.substring(6, j)).intValue();
                int size = Integer.parseInt(spec.substring(spec.lastIndexOf(':') + 1));
                return new VariableStorage(currentProgram, off, size);
            }
            String rn = spec.contains(":") ? spec.substring(0, spec.indexOf(':')) : spec;
            Register r = currentProgram.getRegister(rn);
            if (r != null) return new VariableStorage(currentProgram, r);
        } catch (Exception e) { /* fall through */ }
        return null;
    }

    private void func(JsonObject o) throws Exception {
        Address a = addr(s(o, "addr"));
        FunctionManager fm = currentProgram.getFunctionManager();
        Function f = fm.getFunctionAt(a);
        if (f == null) {
            if (getInstructionAt(a) == null) disassemble(a);
            f = createFunction(a, s(o, "name"));
            if (f == null) { failed++; println("  fail func " + s(o, "addr") + ": cannot create"); return; }
        }
        SourceType src = SourceType.valueOf(s(o, "sigsrc"));
        boolean changed = false;
        String name = s(o, "name");
        if (name != null && !name.equals(f.getName())) { f.setName(name, src == SourceType.DEFAULT ? SourceType.USER_DEFINED : src); changed = true; }
        DataType ret = resolveType(s(o, "ret"));
        if (!f.getReturnType().getPathName().equals(ret.getPathName())) { f.setReturnType(ret, src); changed = true; }
        String cc = s(o, "cc");
        if (cc != null && !cc.equals(f.getCallingConventionName())) { try { f.setCallingConvention(cc); changed = true; } catch (Exception e) { skippedStorage++; } }
        if (f.hasVarArgs() != bo(o, "varargs")) { f.setVarArgs(bo(o, "varargs")); changed = true; }
        if (f.hasNoReturn() != bo(o, "noreturn")) { f.setNoReturn(bo(o, "noreturn")); changed = true; }
        if (f.isInline() != bo(o, "inline")) { f.setInline(bo(o, "inline")); changed = true; }
        // parameters
        JsonArray ps = o.getAsJsonArray("params");
        boolean custom = bo(o, "custom");
        List<Variable> want = new ArrayList<>();
        boolean allStorage = true;
        for (JsonElement pe : ps) {
            JsonObject p = pe.getAsJsonObject();
            DataType pt = resolveType(s(p, "type"));
            VariableStorage vs = custom ? storageOf(s(p, "storage")) : null;
            if (custom && vs == null) allStorage = false;
            want.add(vs != null ? new ParameterImpl(s(p, "name"), pt, vs, currentProgram) : new ParameterImpl(s(p, "name"), pt, currentProgram));
        }
        boolean same = f.getParameterCount() == want.size();
        for (int i = 0; same && i < want.size(); i++) {
            Parameter cur = f.getParameter(i);
            same = Objects.equals(cur.getName(), want.get(i).getName()) && cur.getDataType().getPathName().equals(want.get(i).getDataType().getPathName())
                    && (!custom || cur.getVariableStorage().toString().equals(want.get(i).getVariableStorage().toString()));
        }
        if (!same) {
            Function.FunctionUpdateType ut = (custom && allStorage) ? Function.FunctionUpdateType.CUSTOM_STORAGE : Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS;
            if (custom && !allStorage) skippedStorage++;
            f.replaceParameters(want, ut, true, src == SourceType.DEFAULT ? SourceType.USER_DEFINED : src);
            changed = true;
        }
        // locals: match by storage + first-use; update name/type/comment, else add
        for (JsonElement le : o.getAsJsonArray("locals")) {
            JsonObject l = le.getAsJsonObject();
            String storage = s(l, "storage"); int first = in(l, "first");
            DataType lt = resolveType(s(l, "type"));
            Variable hit = null;
            for (Variable v : f.getLocalVariables())
                if (v.getVariableStorage().toString().equals(storage) && v.getFirstUseOffset() == first) { hit = v; break; }
            SourceType lsrc = SourceType.valueOf(s(l, "src"));
            if (lsrc == SourceType.DEFAULT) lsrc = SourceType.USER_DEFINED;
            if (hit != null) {
                boolean lc = false;
                if (!Objects.equals(hit.getName(), s(l, "name"))) { hit.setName(s(l, "name"), lsrc); lc = true; }
                if (!hit.getDataType().getPathName().equals(lt.getPathName())) { hit.setDataType(lt, lsrc); lc = true; }
                if (!Objects.equals(hit.getComment(), s(l, "comment"))) { hit.setComment(s(l, "comment")); lc = true; }
                if (lc) changed = true;
                continue;
            }
            Variable nv;
            if (storage.startsWith("Stack[")) {
                // stack local: "Stack[-0x10]:4" -> VariableStorage(program, offset, size); the (String,int,DataType,int,Program)
                // ctor does not exist in Ghidra 12.1 (the S86 OSGi-bundle blocker)
                VariableStorage vs = storageOf(storage);
                if (vs == null) { skippedStorage++; continue; }
                nv = new LocalVariableImpl(s(l, "name"), first, lt, vs, currentProgram);
            } else {
                String rn = storage.contains(":") ? storage.substring(0, storage.indexOf(':')) : storage;
                Register r = currentProgram.getRegister(rn);
                if (r == null) { skippedStorage++; continue; }
                nv = new LocalVariableImpl(s(l, "name"), first, lt, r, currentProgram);
            }
            Variable added = f.addLocalVariable(nv, lsrc);
            if (added != null && s(l, "comment") != null) added.setComment(s(l, "comment"));
            changed = true;
        }
        String fc = s(o, "comment");
        if (!Objects.equals(fc, f.getComment())) { f.setComment(fc); changed = true; }
        if (changed) nFuncs++; else unchanged++;
    }

    // ---- data, comments, bookmarks, equates, labels ----
    private void data(JsonObject o) throws Exception {
        Address a = addr(s(o, "addr"));
        DataType dt = resolveType(s(o, "type"));
        Data cur = currentProgram.getListing().getDefinedDataAt(a);
        if (cur != null && cur.getDataType().getPathName().equals(dt.getPathName()) && cur.getLength() == in(o, "len")) { unchanged++; return; }
        try {
            DataUtilities.createData(currentProgram, a, dt, in(o, "len"), DataUtilities.ClearDataMode.CLEAR_ALL_CONFLICT_DATA);
            nData++;
        } catch (CodeUnitInsertionException e) {
            failed++; println("  fail data " + s(o, "addr") + ": " + e.getMessage());
        }
    }

    private void comment(JsonObject o) {
        Address a = addr(s(o, "addr"));
        CommentType t;
        switch (s(o, "type")) {
            case "eol": t = CommentType.EOL; break;
            case "pre": t = CommentType.PRE; break;
            case "post": t = CommentType.POST; break;
            case "plate": t = CommentType.PLATE; break;
            default: t = CommentType.REPEATABLE; break;
        }
        Listing l = currentProgram.getListing();
        if (Objects.equals(l.getComment(t, a), s(o, "text"))) { unchanged++; return; }
        l.setComment(a, t, s(o, "text"));
        nComments++;
    }

    private void bookmark(JsonObject o) {
        Address a = addr(s(o, "addr"));
        BookmarkManager bm = currentProgram.getBookmarkManager();
        Bookmark cur = bm.getBookmark(a, s(o, "type"), s(o, "cat"));
        if (cur != null && Objects.equals(cur.getComment(), s(o, "text"))) { unchanged++; return; }
        bm.setBookmark(a, s(o, "type"), s(o, "cat"), s(o, "text"));
        nBookmarks++;
    }

    private void equate(JsonObject o) throws Exception {
        EquateTable et = currentProgram.getEquateTable();
        String name = s(o, "name"); long value = o.get("value").getAsLong();
        Equate e = et.getEquate(name);
        boolean changed = false;
        if (e == null) { e = et.createEquate(name, value); changed = true; }
        Set<String> have = new HashSet<>();
        for (EquateReference r : e.getReferences()) have.add(r.getAddress().getOffset() + "|" + r.getOpIndex());
        for (JsonElement re : o.getAsJsonArray("refs")) {
            JsonArray r = re.getAsJsonArray();
            Address a = addr(r.get(0).getAsString()); int op = r.get(1).getAsInt();
            if (have.contains(a.getOffset() + "|" + op)) continue;
            e.addReference(a, op); changed = true;
        }
        if (changed) nEquates++; else unchanged++;
    }

    private void label(JsonObject o) throws Exception {
        Address a = addr(s(o, "addr"));
        String name = s(o, "name");
        SourceType src = SourceType.valueOf(s(o, "src"));
        if (src == SourceType.DEFAULT) src = SourceType.USER_DEFINED;
        SymbolTable st = currentProgram.getSymbolTable();
        for (Symbol sym : st.getSymbols(a))
            if (sym.getName().equals(name)) {
                if (bo(o, "primary") && !sym.isPrimary()) { sym.setPrimary(); nLabels++; } else unchanged++;
                return;
            }
        Function f = currentProgram.getFunctionManager().getFunctionAt(a);
        if (bo(o, "func") && f != null) { f.setName(name, src); nLabels++; return; }
        Symbol created = st.createLabel(a, name, src);
        if (bo(o, "primary")) created.setPrimary();
        nLabels++;
    }
}
