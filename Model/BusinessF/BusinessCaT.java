package BusinessF;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class BusinessCaT implements Serializable, iBusinessCat {
    private Map<String, Business> allBizs;

    public BusinessCaT(List<String> s) {
        this.allBizs = new HashMap<>();
        for (String l : s) {
            if (this.valid(l)) {
                Business n = new Business(l);
                this.allBizs.put(n.getBusiness_id(), n);
            }
        }
    }
    public BusinessCaT(BusinessCaT bc) {
        this.allBizs = bc.getAllBizs();
    }

    public boolean valid(String line) {
        String[] c = line.split(";", -1);
        if (c.length != 5)
            return false;
        for (int i = 0; i < 4; i++) {
            if (c[i].isEmpty()) {
                return false;
            }
        }
        return true;
    }

    public Map<String, Business> getAllBizs() {
        return this.allBizs.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
    }

    public BusinessCaT clone() {
        return new BusinessCaT(this);
    }
}
