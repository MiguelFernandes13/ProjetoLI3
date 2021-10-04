package BusinessF;

import java.io.Serializable;
import java.util.*;

public class Business implements Serializable, iBusiness {
    private String business_id;
    private String name;
    private String city;
    private String state;
    private List<String> categories;

    public Business(String line) {
        String[] c = line.split(";", 5);
        this.business_id = c[0];
        this.name = c[1];
        this.city = c[2];
        this.state = c[3];
        String[] c2 = c[4].split(",", -1);
        this.categories = new ArrayList<>();
        for (int i = 0; i < c2.length; i++) {
            this.categories.add(c2[i]);

        }
    }

    public Business(String business_id, String name, String city, String state, List<String> categories) {
        this.business_id = business_id;
        this.name = name;
        this.city = city;
        this.state = state;
        setCategories(categories);
    }

    public Business(Business b) {
        this.business_id = b.getBusiness_id();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = b.getCategories();
    }

    public String getBusiness_id() {
        return this.business_id;
    }

    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCity() {
        return this.city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getState() {
        return this.state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public List<String> getCategories() {
        return new ArrayList<>(this.categories);
    }

    public void setCategories(List<String> categories) {
        this.categories = new ArrayList<>(categories);
    }

    public Business clone() {
        return new Business(this);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Business)) {
            return false;
        }
        Business business = (Business) o;
        return Objects.equals(business_id, business.business_id) && Objects.equals(name, business.name)
                && Objects.equals(city, business.city) && Objects.equals(state, business.state)
                && Objects.equals(categories, business.categories);
    }

    @Override
    public String toString() {
        return "{" + " business_id='" + getBusiness_id() + "'" + ", name='" + getName() + "'" + ", city='" + getCity()
                + "'" + ", state='" + getState() + "'" + ", categories='" + getCategories() + "'" + "}";
    }

}
