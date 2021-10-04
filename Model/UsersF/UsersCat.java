package UsersF;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class UsersCat implements Serializable, iUsersCat {
    private Map<String, Users> allUsers;

    public UsersCat(List<String> s) {
        this.allUsers = new HashMap<>();
        for (String l : s) {
            if (this.valid(l)) {
                Users n = new Users(l);
                this.allUsers.put(n.getUser_id(), n);
            }
        }
    }

    public UsersCat(UsersCat uc) {
        this.allUsers = uc.getAllUsers();
    }

    public Map<String, Users> getAllUsers() {
        return this.allUsers.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
    }

    public UsersCat clone() {
        return new UsersCat(this);
    }

    public boolean valid(String line) {
        boolean r = true;
        String[] c = line.split(";", 3);
        if (c.length != 3)
            r = false;
        for (int i = 0; i < 2; i++) {
            if (c[i].isEmpty()) {
                r = false;
                break;
            }
        }
        return r;
    }
}