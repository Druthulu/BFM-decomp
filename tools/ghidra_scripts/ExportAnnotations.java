// ExportAnnotations.java — headless, READ-ONLY: serialize a program's ANNOTATIONS to byte-stable JSON-Lines
// (P33 B5, the Ghidra-regenerability deliverable carried since Phase 9/10).
//
// WHAT: everything a human (or the MCP) can author in a program that is NOT already text in the repo —
// data types (structs/unions/enums/typedefs/function definitions of the program's LOCAL archive; the
// psyq400 archive types are re-imported by ImportPsyqGdt.java), function signatures (return type,
// calling convention, parameters, locals, flags), defined data, the five comment kinds, bookmarks,
// equates, and non-default labels that the splat symbol files do not already carry — plus the
// container facts (language, image base, memory blocks) so an image-base drift shows as a diff.
//
// HOW IT IS USED: tools/ghidra_rebuild.sh exports the LIVE program and a FRESH rebuild (import +
// analysis + DefineFunctions + ApplySymbols) and stores their DELTA (tools/ghidra_annotations_delta.py)
// as config/ghidra/<program>.jsonl — every row analysis produces on its own subtracts itself out, so
// what is committed is the hand-authored RE work. The proof re-imports that delta and re-exports.
// Byte-stability is the whole contract: fixed key order, sorted rows, 0x%08x addresses, one JSON object
// per line, no whitespace. Deterministic across machines given the same program.
//
//   analyzeHeadless <proj_dir> bfm -process <PROG> -noanalysis -readOnly \
//     -scriptPath tools/ghidra_scripts -postScript ExportAnnotations.java <out.jsonl|out_dir> [symbols.txt ...]
//
// Arg 1: an output FILE, or a DIRECTORY (then <dir>/<program>.jsonl — the all-programs form, run with
//        `-process` and no program name). Args 2..: splat symbol files whose `name = 0xADDR;` rows are
//        skipped from the label export (ApplySymbols.java restores those).
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.*;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExportAnnotations extends GhidraScript {

    // ---- JSON helpers (the DumpFunctionSignatures.java convention: hand-serialized, canonical) ----
    private static String esc(String s) {
        if (s == null) return "null";
        StringBuilder sb = new StringBuilder("\"");
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '"' || c == '\\') sb.append('\\').append(c);
            else if (c == '\n') sb.append("\\n");
            else if (c == '\r') sb.append("\\r");
            else if (c == '\t') sb.append("\\t");
            else if (c < 0x20) sb.append(String.format("\\u%04x", (int) c));
            else sb.append(c);
        }
        return sb.append('"').toString();
    }
    private static String hexAddr(Address a) { return String.format("\"0x%08x\"", a.getOffset()); }
    private static String b(boolean v) { return v ? "true" : "false"; }

    private final Map<Long, Set<String>> symfileNames = new HashMap<>();   // addr -> names the symbol files carry

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args == null || args.length < 1) { println("BFMEXPORT ERROR: usage <out.jsonl|out_dir> [symbols.txt ...]"); return; }
        Path out = Paths.get(args[0]);
        if (Files.isDirectory(out)) out = out.resolve(currentProgram.getName() + ".jsonl");
        Pattern sp = Pattern.compile("^\\s*([A-Za-z_]\\w*)\\s*=\\s*0x([0-9A-Fa-f]+)\\s*;");
        for (int i = 1; i < args.length; i++) {
            Path f = Paths.get(args[i]);
            if (!Files.isRegularFile(f)) { println("BFMEXPORT WARN: symbols file not found: " + f); continue; }
            for (String ln : Files.readAllLines(f)) {
                Matcher m = sp.matcher(ln);
                if (m.find()) symfileNames.computeIfAbsent(Long.parseLong(m.group(2), 16), k -> new HashSet<>()).add(m.group(1));
            }
        }

        List<String> rows = new ArrayList<>();
        int nTypes = program(rows);
        int nFuncs = functions(rows);
        int nData = data(rows);
        int nComments = comments(rows);
        int nBookmarks = bookmarks(rows);
        int nEquates = equates(rows);
        int nLabels = labels(rows);

        StringBuilder sb = new StringBuilder();
        for (String r : rows) sb.append(r).append('\n');
        Files.createDirectories(out.toAbsolutePath().getParent());
        Files.write(out, sb.toString().getBytes(StandardCharsets.UTF_8));
        println("BFMEXPORT program=" + currentProgram.getName() + " types=" + nTypes + " funcs=" + nFuncs
                + " data=" + nData + " comments=" + nComments + " bookmarks=" + nBookmarks + " equates=" + nEquates
                + " labels=" + nLabels + " rows=" + rows.size() + " -> " + out);
    }

    // ---- program, blocks, archives, LOCAL data types (sorted by path) ----
    private int program(List<String> rows) {
        Program p = currentProgram;
        rows.add("{\"k\":\"program\",\"name\":" + esc(p.getName()) + ",\"lang\":" + esc(p.getLanguageID().getIdAsString())
                + ",\"cspec\":" + esc(p.getCompilerSpec().getCompilerSpecID().getIdAsString())
                + ",\"image_base\":" + hexAddr(p.getImageBase()) + ",\"format\":" + esc(p.getExecutableFormat()) + "}");
        List<String> blocks = new ArrayList<>();
        for (MemoryBlock mb : p.getMemory().getBlocks()) {
            String perm = (mb.isRead() ? "r" : "-") + (mb.isWrite() ? "w" : "-") + (mb.isExecute() ? "x" : "-");
            blocks.add("{\"k\":\"block\",\"name\":" + esc(mb.getName()) + ",\"start\":" + hexAddr(mb.getStart())
                    + ",\"end\":" + hexAddr(mb.getEnd()) + ",\"perm\":\"" + perm + "\",\"init\":" + b(mb.isInitialized()) + "}");
        }
        rows.addAll(blocks);   // memory order as Ghidra lists them (address order)
        DataTypeManager dtm = p.getDataTypeManager();
        SourceArchive local = dtm.getLocalSourceArchive();
        TreeSet<String> archives = new TreeSet<>();
        for (SourceArchive sa : dtm.getSourceArchives()) {
            if (sa.getSourceArchiveID().equals(local.getSourceArchiveID())) continue;
            if (sa.getArchiveType() == ArchiveType.BUILT_IN) continue;
            archives.add("{\"k\":\"archive\",\"name\":" + esc(sa.getName()) + "}");
        }
        rows.addAll(archives);
        TreeMap<String, String> types = new TreeMap<>();
        Iterator<DataType> it = dtm.getAllDataTypes();
        while (it.hasNext()) {
            DataType dt = it.next();
            if (dt instanceof Pointer || dt instanceof Array || dt instanceof BuiltInDataType) continue;
            SourceArchive sa = dt.getSourceArchive();
            if (sa != null && !sa.getSourceArchiveID().equals(local.getSourceArchiveID())) continue;   // psyq400 etc.
            String row = typeRow(dt);
            if (row != null) types.put(dt.getPathName(), row);
        }
        rows.addAll(types.values());
        return types.size();
    }

    private String typeRow(DataType dt) {
        String path = esc(dt.getPathName());
        if (dt instanceof Structure) {
            Structure s = (Structure) dt;
            StringBuilder f = new StringBuilder("[");
            boolean first = true;
            for (DataTypeComponent c : s.getDefinedComponents()) {
                if (!first) f.append(','); first = false;
                f.append("{\"off\":").append(c.getOffset()).append(",\"len\":").append(c.getLength())
                 .append(",\"name\":").append(esc(c.getFieldName())).append(",\"type\":").append(esc(c.getDataType().getPathName()))
                 .append(",\"comment\":").append(esc(c.getComment())).append('}');
            }
            return "{\"k\":\"type\",\"kind\":\"struct\",\"path\":" + path + ",\"size\":" + s.getLength()
                    + ",\"packed\":" + b(s.isPackingEnabled()) + ",\"fields\":" + f + "]}";
        }
        if (dt instanceof Union) {
            Union u = (Union) dt;
            StringBuilder f = new StringBuilder("[");
            boolean first = true;
            for (DataTypeComponent c : u.getComponents()) {
                if (!first) f.append(','); first = false;
                f.append("{\"len\":").append(c.getLength()).append(",\"name\":").append(esc(c.getFieldName()))
                 .append(",\"type\":").append(esc(c.getDataType().getPathName())).append(",\"comment\":").append(esc(c.getComment())).append('}');
            }
            return "{\"k\":\"type\",\"kind\":\"union\",\"path\":" + path + ",\"size\":" + u.getLength()
                    + ",\"packed\":" + b(u.isPackingEnabled()) + ",\"fields\":" + f + "]}";
        }
        if (dt instanceof ghidra.program.model.data.Enum) {
            ghidra.program.model.data.Enum e = (ghidra.program.model.data.Enum) dt;
            TreeMap<String, String> vals = new TreeMap<>();
            for (String n : e.getNames()) vals.put(String.format("%020d|%s", e.getValue(n), n),
                    "{\"name\":" + esc(n) + ",\"value\":" + e.getValue(n) + "}");
            return "{\"k\":\"type\",\"kind\":\"enum\",\"path\":" + path + ",\"size\":" + e.getLength()
                    + ",\"values\":[" + String.join(",", vals.values()) + "]}";
        }
        if (dt instanceof TypeDef) {
            return "{\"k\":\"type\",\"kind\":\"typedef\",\"path\":" + path + ",\"base\":" + esc(((TypeDef) dt).getDataType().getPathName()) + "}";
        }
        if (dt instanceof FunctionDefinition) {
            FunctionDefinition fd = (FunctionDefinition) dt;
            StringBuilder ps = new StringBuilder("[");
            boolean first = true;
            for (ParameterDefinition pd : fd.getArguments()) {
                if (!first) ps.append(','); first = false;
                ps.append("{\"name\":").append(esc(pd.getName())).append(",\"type\":").append(esc(pd.getDataType().getPathName()))
                  .append(",\"comment\":").append(esc(pd.getComment())).append('}');
            }
            return "{\"k\":\"type\",\"kind\":\"fndef\",\"path\":" + path + ",\"ret\":" + esc(fd.getReturnType().getPathName())
                    + ",\"cc\":" + esc(fd.getCallingConventionName()) + ",\"varargs\":" + b(fd.hasVarArgs()) + ",\"params\":" + ps + "]}";
        }
        return "{\"k\":\"type\",\"kind\":\"other\",\"path\":" + path + ",\"class\":" + esc(dt.getClass().getSimpleName()) + "}";
    }

    // ---- functions (every non-external function; the delta keeps the user-touched ones) ----
    private int functions(List<String> rows) {
        TreeMap<Long, String> m = new TreeMap<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (f.isExternal()) continue;
            StringBuilder ps = new StringBuilder("[");
            boolean first = true;
            for (Parameter p : f.getParameters()) {
                if (!first) ps.append(','); first = false;
                ps.append("{\"name\":").append(esc(p.getName())).append(",\"type\":").append(esc(p.getDataType().getPathName()))
                  .append(",\"storage\":").append(esc(p.getVariableStorage().toString())).append(",\"src\":").append(esc(p.getSource().name())).append('}');
            }
            ps.append(']');
            TreeMap<String, String> locals = new TreeMap<>();
            for (Variable v : f.getLocalVariables()) {
                String key = String.format("%010d|%s|%s", v.getFirstUseOffset(), v.getVariableStorage().toString(), v.getName());
                locals.put(key, "{\"name\":" + esc(v.getName()) + ",\"type\":" + esc(v.getDataType().getPathName())
                        + ",\"storage\":" + esc(v.getVariableStorage().toString()) + ",\"first\":" + v.getFirstUseOffset()
                        + ",\"src\":" + esc(v.getSource().name()) + ",\"comment\":" + esc(v.getComment()) + "}");
            }
            String row = "{\"k\":\"func\",\"addr\":" + hexAddr(f.getEntryPoint()) + ",\"name\":" + esc(f.getName())
                    + ",\"ret\":" + esc(f.getReturnType().getPathName()) + ",\"cc\":" + esc(f.getCallingConventionName())
                    + ",\"varargs\":" + b(f.hasVarArgs()) + ",\"noreturn\":" + b(f.hasNoReturn()) + ",\"inline\":" + b(f.isInline())
                    + ",\"custom\":" + b(f.hasCustomVariableStorage()) + ",\"sigsrc\":" + esc(f.getSignatureSource().name())
                    + ",\"params\":" + ps + ",\"locals\":[" + String.join(",", locals.values()) + "]"
                    + ",\"comment\":" + esc(f.getComment()) + "}";
            m.put(f.getEntryPoint().getOffset(), row);
        }
        rows.addAll(m.values());
        return m.size();
    }

    // ---- defined data (every typed unit; the delta keeps the user-typed ones) ----
    private int data(List<String> rows) {
        TreeMap<Long, String> m = new TreeMap<>();
        DataIterator it = currentProgram.getListing().getDefinedData(true);
        while (it.hasNext()) {
            Data d = it.next();
            DataType dt = d.getDataType();
            if (dt instanceof DefaultDataType || dt instanceof Undefined) continue;
            m.put(d.getAddress().getOffset(), "{\"k\":\"data\",\"addr\":" + hexAddr(d.getAddress()) + ",\"type\":" + esc(dt.getPathName())
                    + ",\"len\":" + d.getLength() + "}");
        }
        rows.addAll(m.values());
        return m.size();
    }

    // ---- comments, five kinds ----
    private int comments(List<String> rows) {
        TreeMap<String, String> m = new TreeMap<>();
        Listing l = currentProgram.getListing();
        CommentType[] kinds = {CommentType.EOL, CommentType.PRE, CommentType.POST, CommentType.PLATE, CommentType.REPEATABLE};
        String[] names = {"eol", "pre", "post", "plate", "repeat"};
        for (int i = 0; i < kinds.length; i++) {
            AddressIterator ai = l.getCommentAddressIterator(kinds[i], currentProgram.getMemory(), true);
            while (ai.hasNext()) {
                Address a = ai.next();
                String c = l.getComment(kinds[i], a);
                if (c == null) continue;
                m.put(String.format("%016x|%d", a.getOffset(), i), "{\"k\":\"comment\",\"addr\":" + hexAddr(a) + ",\"type\":\"" + names[i] + "\",\"text\":" + esc(c) + "}");
            }
        }
        rows.addAll(m.values());
        return m.size();
    }

    private int bookmarks(List<String> rows) {
        TreeMap<String, String> m = new TreeMap<>();
        Iterator<Bookmark> it = currentProgram.getBookmarkManager().getBookmarksIterator();
        while (it.hasNext()) {
            Bookmark bk = it.next();
            String key = String.format("%016x|%s|%s|%s", bk.getAddress().getOffset(), bk.getTypeString(), bk.getCategory(), bk.getComment());
            m.put(key, "{\"k\":\"bookmark\",\"addr\":" + hexAddr(bk.getAddress()) + ",\"type\":" + esc(bk.getTypeString())
                    + ",\"cat\":" + esc(bk.getCategory()) + ",\"text\":" + esc(bk.getComment()) + "}");
        }
        rows.addAll(m.values());
        return m.size();
    }

    private int equates(List<String> rows) {
        TreeMap<String, String> m = new TreeMap<>();
        Iterator<Equate> it = currentProgram.getEquateTable().getEquates();
        while (it.hasNext()) {
            Equate e = it.next();
            TreeSet<String> refs = new TreeSet<>();
            for (EquateReference r : e.getReferences())
                refs.add("[" + hexAddr(r.getAddress()) + "," + r.getOpIndex() + "]");
            m.put(e.getName(), "{\"k\":\"equate\",\"name\":" + esc(e.getName()) + ",\"value\":" + e.getValue()
                    + ",\"refs\":[" + String.join(",", refs) + "]}");
        }
        rows.addAll(m.values());
        return m.size();
    }

    // ---- labels: every non-DEFAULT, non-external symbol the symbol files do not already carry ----
    private int labels(List<String> rows) {
        TreeMap<String, String> m = new TreeMap<>();
        for (Symbol s : currentProgram.getSymbolTable().getAllSymbols(true)) {
            if (s.isExternal() || s.getSource() == SourceType.DEFAULT) continue;
            if (!currentProgram.getMemory().contains(s.getAddress())) continue;
            Set<String> have = symfileNames.get(s.getAddress().getOffset());
            if (have != null && have.contains(s.getName())) continue;
            boolean isFunc = s.getSymbolType() == SymbolType.FUNCTION;
            m.put(String.format("%016x|%s", s.getAddress().getOffset(), s.getName()),
                  "{\"k\":\"label\",\"addr\":" + hexAddr(s.getAddress()) + ",\"name\":" + esc(s.getName()) + ",\"primary\":" + b(s.isPrimary())
                  + ",\"src\":" + esc(s.getSource().name()) + ",\"func\":" + b(isFunc) + "}");
        }
        rows.addAll(m.values());
        return m.size();
    }
}
