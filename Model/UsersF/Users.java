package UsersF;

import java.io.Serializable;
import java.util.Objects;

public class Users implements Serializable, iUsers {

    private String user_id;
    private String name;

    public Users(String line) {
        String[] c = line.split(";", 2);
        this.user_id = c[0];
        this.name = c[1];

    }

    public Users(String user_id, String name) {
        this.user_id = user_id;
        this.name = name;
    }

    public Users(Users u) {
        this.user_id = getUser_id();
        this.name = getName();
    }

    public String getUser_id() {
        return this.user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Users)) {
            return false;
        }
        Users users = (Users) o;
        return Objects.equals(user_id, users.user_id) && Objects.equals(name, users.name);
    }

    @Override
    public String toString() {
        return "{" + " user_id='" + getUser_id() + "'" + ", name='" + getName() + "'" + "}";
    }

    public Users clone() {
        return new Users(this);
    }

}
