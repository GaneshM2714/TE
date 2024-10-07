import java.sql.*;
import java.util.Scanner;

public class InvDB {
    // Include server timezone and SSL settings in the URL
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mock";
    private static final String USR = "root";
    private static final String PWD = "";

    public static void main(String[] args) {
        try {
            // Explicitly load the MySQL driver
            Class.forName("com.mysql.cj.jdbc.Driver");
            System.out.println("Driver loaded successfully.");

            // Establish database connection
            try (Connection con = DriverManager.getConnection(DB_URL, USR, PWD);
                 Scanner sc = new Scanner(System.in)) {
                System.out.println("DB connected.");

                // Menu-driven interface
                while (true) {
                    System.out.println("Select an option:");
                    System.out.println("1 - Insert");
                    System.out.println("2 - Update");
                    System.out.println("3 - Delete");
                    System.out.println("4 - Display");
                    System.out.println("5 - Exit");

                    int ch = sc.nextInt();
                    sc.nextLine();

                    switch (ch) {
                        case 1:
                            addInv(con, sc);
                            break;
                        case 2:
                            updInv(con, sc);
                            break;
                        case 3:
                            delInv(con, sc);
                            break;
                        case 4:
                            showInv(con);
                            break;
                        case 5:
                            System.out.println("Exiting.");
                            return;
                        default:
                            System.out.println("Invalid choice.");
                    }
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        } catch (ClassNotFoundException e) {
            System.out.println("Could not load MySQL driver. Ensure the driver jar is in the classpath.");
            e.printStackTrace();
        }
    }

    private static void addInv(Connection con, Scanner sc) {
        System.out.print("No. of records: ");
        int cnt = sc.nextInt();
        sc.nextLine();

        try (Statement stmt = con.createStatement()) {
            for (int i = 0; i < cnt; i++) {
                System.out.print("Cust ID: ");
                int custId = sc.nextInt();
                System.out.print("Prod ID: ");
                int productId = sc.nextInt();
                System.out.print("Qty: ");
                int quantity = sc.nextInt();
                System.out.print("Price: ");
                double price = sc.nextDouble();
                sc.nextLine();
                System.out.print("Date (YYYY-MM-DD): ");
                String date = sc.nextLine();

                String sqlIns = "INSERT INTO Invoice (cust_id, product_id, quantity, price, date) VALUES (" +
                                custId + ", " + productId + ", " + quantity + ", " + price + ", '" + date + "')";

                stmt.executeUpdate(sqlIns);
            }
            System.out.println("Records added.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void updInv(Connection con, Scanner sc) {
        System.out.print("Invoice ID to update: ");
        int invId = sc.nextInt();
        sc.nextLine();

        String sqlUpd = "UPDATE Invoice SET cust_id = ?, product_id = ?, quantity = ?, price = ?, date = ? WHERE invoice_id = ?";

        try (PreparedStatement psUpd = con.prepareStatement(sqlUpd)) {
            System.out.print("New Cust ID: ");
            int cId = sc.nextInt();
            System.out.print("New Prod ID: ");
            int pId = sc.nextInt();
            System.out.print("New Qty: ");
            int qty = sc.nextInt();
            System.out.print("New Price: ");
            double prc = sc.nextDouble();
            sc.nextLine();
            System.out.print("New Date (YYYY-MM-DD): ");
            String dt = sc.nextLine();

            psUpd.setInt(1, cId);
            psUpd.setInt(2, pId);
            psUpd.setInt(3, qty);
            psUpd.setDouble(4, prc);
            psUpd.setString(5, dt);
            psUpd.setInt(6, invId);

            int rows = psUpd.executeUpdate();
            System.out.println(rows > 0 ? "Record updated." : "No matching ID.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void delInv(Connection con, Scanner sc) {
        System.out.print("Invoice ID to delete: ");
        int invId = sc.nextInt();

        String sqlDel = "DELETE FROM Invoice WHERE invoice_id = ?";

        try (PreparedStatement psDel = con.prepareStatement(sqlDel)) {
            psDel.setInt(1, invId);
            int rows = psDel.executeUpdate();
            System.out.println(rows > 0 ? "Record deleted." : "ID not found.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void showInv(Connection con) {
        String sqlSel = "SELECT * FROM Invoice";

        try (Statement st = con.createStatement();
             ResultSet rs = st.executeQuery(sqlSel)) {

            System.out.println("ID\tCust ID\tProd ID\tQty\tPrice\tDate");
            while (rs.next()) {
                System.out.println(rs.getInt("invoice_id") + "\t" +
                        rs.getInt("cust_id") + "\t" +
                        rs.getInt("product_id") + "\t" +
                        rs.getInt("quantity") + "\t" +
                        rs.getDouble("price") + "\t" +
                        rs.getDate("date"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
