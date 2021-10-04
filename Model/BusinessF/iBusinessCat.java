package BusinessF;

import java.util.Map;

public interface iBusinessCat {
    boolean valid(String line);
    Map<String, Business> getAllBizs();
    BusinessCaT clone();

}