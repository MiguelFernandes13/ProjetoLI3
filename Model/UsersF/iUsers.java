package UsersF;

public interface iUsers {
    String getUser_id();
    void setUser_id(String user_id);
    String getName();
    void setName(String name);
    boolean equals(Object o);
    String toString();
    Users clone();
}