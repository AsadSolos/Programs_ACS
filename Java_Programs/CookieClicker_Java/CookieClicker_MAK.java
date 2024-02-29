//**************************************************************
// CookieClicker_MAK.java
//
// Purpose: Remakes popular idle game in Java using a variety of libraries
//
// Note: This code will NOT RUN on another computer unless if the paths for the images are changed.
// 
// R1: 18-Jan-2024 Muhammad Khurram – Written for Advanced Computer Studies.
//**************************************************************
    
import javax.swing.*;      
import java.awt.*;  
import java.awt.event.*;
import java.util.Timer;
import java.util.TimerTask;

public class CookieClicker_MAK {    
    private double count = 0;
    private double grans = 10;
    private int granAmount = 0;
    private double y = 1;
    private double clickers = 0;
    private double clickPrice = 5;
    private double ovenPrice = 10;
    private int clickTime = 5000;
    private int ovenAmount = 0;
    
    CookieClicker_MAK() {    
        JFrame cookieFrame = new JFrame("Welcome to Cookie Clicker!");            
        JButton cookie = new JButton(new ImageIcon("/Users/asadsolos/Downloads/cookie.png"));
        JButton clickGrade = new JButton(new ImageIcon("/Users/asadsolos/Downloads/clicker(1).png"));
        JButton grandmaGrade = new JButton(new ImageIcon("/Users/asadsolos/Downloads/grandma.png"));
        JButton ovenGrade = new JButton(new ImageIcon("/Users/asadsolos/Downloads/oven.jpg"));    
        JLabel cookieCountLabel = new JLabel("Cookies: " + count);  
        JPanel labelPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JPanel upgradePanel = new JPanel();
        clickGrade.setToolTipText("This will click every " + clickTime + " milliseconds for you, generating a cookie each time. Clicker amount: " + clickers + ". Price is " + clickPrice + ".");
        grandmaGrade.setToolTipText("Each click is multiplied by 1.25x. Grandma amount: " + granAmount + ". Current multiplier is " + y + " and current grandma price is " + grans + ".");
        ovenGrade.setToolTipText("Clicker cooldown is multiplied by 0.75x. Amount of ovens: " + ovenAmount + ". Clicker cooldown: " + clickTime + " ms. Oven price: " + ovenPrice + ".");
        cookie.setToolTipText("Click me for " + y + " cookies!");

        cookie.setPreferredSize(new Dimension(350, 350));

        cookie.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                count = count + y;
                cookieCountLabel.setText("Cookies: " + count);
            }
        });

        labelPanel.add(cookieCountLabel);
        buttonPanel.add(cookie);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.add(labelPanel);
        mainPanel.add(buttonPanel);
        mainPanel.add(upgradePanel);
        upgradePanel.add(clickGrade, BorderLayout.WEST);
        upgradePanel.add(grandmaGrade, BorderLayout.CENTER);
        upgradePanel.add(ovenGrade, BorderLayout.EAST);
        
        grandmaGrade.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                        if (count >= grans)
                        {
                                granAmount++;
                                count -= grans;
                                grans *= 1.5;
                                y *= 1.25;
                                cookieCountLabel.setText("Cookies: " + count);
                                grandmaGrade.setToolTipText("Each manual click is multiplied by 1.25x. Grandma amount: " + granAmount + ". Current multiplier is " + y + " and current grandma price is " + grans + ".");
                                cookie.setToolTipText("Click me for " + y + " cookies!");
                        }   
                }
        });
        
        clickGrade.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                        if (count >= clickPrice)
                        {
                                clickers++;
                                count -= clickPrice;
                                clickPrice *= 1.25;
                                cookieCountLabel.setText("Cookies: " + count);
                                clickGrade.setToolTipText("This will click every " + clickTime + " milliseconds for you, generating a cookie each time. Clicker amount: " + clickers + ". Price is " + clickPrice + ".");
                        }
                }
        });
        ovenGrade.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                        if (count >= ovenPrice)
                        {
                                
                                count -= ovenPrice;
                                ovenPrice *= 1.25;
                                clickTime = (clickTime * 3) / 4;
                                ovenAmount++;
                                cookieCountLabel.setText("Cookies: " + count);
                                ovenGrade.setToolTipText("Clicker cooldown is multiplied by 0.75x. Amount of ovens: " + ovenAmount + ". Clicker cooldown: " + clickTime + ". Oven price: " + ovenPrice + ".");
                                clickGrade.setToolTipText("This will click every " + clickTime + " milliseconds for you, generating a cookie each time. Clicker amount: " + clickers + ". Price is " + clickPrice + ".");
                        }
                }
        });
        
        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
                public void run() {
                        if (clickers >= 1) {
                                count += clickers;
                                cookieCountLabel.setText("Cookies: " + count);
                        }
                }
        };
        timer.scheduleAtFixedRate(task, 0, clickTime);
              
        cookieFrame.add(mainPanel);
        cookieFrame.pack();
        cookieFrame.setLocationRelativeTo(null);
        cookieFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    
        cookieFrame.setVisible(true);
        cookieFrame.setResizable(false);
    }         

    public static void main(String[] args) {    
        new CookieClicker_MAK();    
    }    
}    
