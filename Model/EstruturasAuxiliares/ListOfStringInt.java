package EstruturasAuxiliares;

import java.util.*;
import java.util.stream.Collectors;

public class ListOfStringInt {

    public static List<AbstractMap.SimpleEntry<String, Integer>> sortList(
            Comparator<Map.Entry<String, Set<String>>> cmp, Map.Entry<Integer, Map<String, Set<String>>> m) {
        return m.getValue().entrySet().stream().sorted(cmp)
                .map(e -> new AbstractMap.SimpleEntry<>(e.getKey(), e.getValue().size())).collect(Collectors.toList());

    }

}
