package BusinessF;

import java.util.List;

public interface iBusiness {
    String getBusiness_id();
    void setBusiness_id(String business_id);
    String getName();
    void setName(String name);
    String getCity();
    void setCity(String city);
    String getState();
    void setState(String state);
    List<String> getCategories();
    void setCategories(List<String> categories);
    Business clone();
    boolean equals(Object o);
    String toString();
}