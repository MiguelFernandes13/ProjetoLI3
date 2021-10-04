import java.io.IOException;

public class GetsReviewsAppMVC {
    public static void main(String[] args) {
        try {
            Controller.run();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
