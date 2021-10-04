package UsersF;

import java.util.Map;

public interface iUsersCat {
    Map<String, Users> getAllUsers();
    UsersCat clone();
    boolean valid(String line);
}