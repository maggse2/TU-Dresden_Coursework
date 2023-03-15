package src.com.company;
import java.awt.*;
import java.util.Scanner;


public class Robot extends Circle {

    //enum keywords for the question commands
    public enum Keyword {
        NAME,
        AGE,
        MANUFACTURER,
        SEX,
        END

    }

    //constructor
    public Robot(Point position, int radius) {
        super(position, radius);
        col = Color.ORANGE;     //Who doesn't like orange?
    }

    /**
     * Voice recognition algorithm according to the task sheet.
     */
    public void voiceRecognition() {
        //ask the robot questions, ends if END is the input

        Scanner scanner = new Scanner(System.in);
        boolean end = false;

        while (!end) {
            String command = new String();

            System.out.println("Please enter a command from the following keywords to ask the robot a question:\n" +
                    "NAME\nAGE\nMANUFACTURER\nSEX\n" +
                    "Once you're done asking questions, enter the command \"END\" :)");
            String input = scanner.nextLine().toUpperCase();
            //convert all the input to uppercase so the keywords are read properly

            if (input.contains("END")) {

                end = true;
            }//if the input is END, the loop stops

            //check if the input is a keyword
            for (Keyword keyword : Robot.Keyword.values()) {
                if (input.contains(keyword.toString())) {
                    command = keyword.toString();
                }
            }

            switch (command) {

                case "NAME":
                    System.out.println("My name is Maggse D'avis");
                    break;

                case "AGE":
                    System.out.println("I'm 3 Months old");
                    break;

                case "MANUFACTURER":
                    System.out.println("Made by 2 & 2");
                    break;

                case "SEX":
                    System.out.println("I'm a Robot bro");
                    break;

                case "END":
                    System.out.println("program ended");
                    break;


                default:
                    System.out.println("Please use the given commands!");
                    break;
            }
        }
    }

    /**
     * Checking if the Robot is touching the boundaries of the field.
     * @return
     */
    public boolean touchingBoundaryX() {
        if ((this.maxX() + 1) > Court.CWID) {
            return true;
        } else {
            return false;
        }
    }

    public boolean touchingBoundaryY() {
        if ((this.maxY() + 1) > Court.CLEN) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Avoiding the rectangles in a similar way we did the overlap check.
     * @param figures List of obstacles we want to avoid.
     * @return Boolean: Too close or not?
     */
    public boolean tooCloseTo_xEdge(Rectangle figures) {
        if (this.minX() < figures.maxX()) {         //ruling out some rectangles we already passed.
            if (figures.minX() - this.maxX() < 5) {   //Dist to Object smaller than 5
                if (this.maxY() > figures.minY() && this.minY() < figures.maxY()) {   //y-Extends overlap
                    return true;
                }
            }
        }
        return false;
    }
    //Same structure as above
    public boolean tooCloseTo_YEdge(Rectangle figures) {
        if (this.minY() < figures.maxY()) {
            if (figures.minY() - this.maxY() < 5) {   //Dist to Object smaller than 5
                if (this.maxX() > figures.minX() && this.minX() < figures.maxX()) {   //x-Extends overlap
                    return true;
                }
            }
        }
        return false;
    }
}