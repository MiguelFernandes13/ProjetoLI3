import java.util.Comparator;
import java.util.Map;
import java.util.Set;

public class StringSetMapComparator implements Comparator<Map.Entry<String, Set<String>>> {
    public int compare(Map.Entry<String, Set<String>> o1, Map.Entry<String, Set<String>> o2) {
        int r2 = o2.getValue().size() - o1.getValue().size();
        if (r2 == 0)
            r2 = o1.getKey().compareTo(o2.getKey());
        return r2;
    }
}
