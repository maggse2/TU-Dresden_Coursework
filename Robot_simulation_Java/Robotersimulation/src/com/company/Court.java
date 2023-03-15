package src.com.company;
import java.util.*;
import java.awt.Color;

public class Court {
    final public static int CWID = 1000;           //max X-Value on the court
    final public static int CLEN = 1000;           //max Y-Value on the court
    public Canvas canvas = Canvas.getCanvas();
    public ArrayList<Rectangle> obstacleList;
    public static Robot maggse = new Robot((new Point(0, 0)), 10);
    static Random rand = new Random();

    public Court() {
    }

    /**
     * The main Method is the first thing a third party programmer looks at. Thus we kept it easy to read.
     * @param args
     */
    public static void main(String[] args) {
        Robot maggse = new Robot((new Point(0, 0)), 10);
        Scanner input = new Scanner(System.in);
        Court c = new Court();
        boolean end = false;
        while (!end) {


            System.out.println("Please choose a task for the robot to do\n" +
                    "if you want to ask the robot some questions please enter \"QA\"\n" +
                    "to have the robot find the shortest path through a set of coordinates enter path\n" +
                    "to have the robot run through a set of obstacle enter obst\n" +
                    "enter \"END\" to end the program");
            String tasks = input.nextLine().toUpperCase();

            if (tasks.contains("END")) end = true;

            switch (tasks) {
                case "QA":
                    maggse.voiceRecognition();
                    break;

                case "PATH":{
                    c.pathLauncher();}
                    break;

                case "OBST":{
                    c.avoidObst();}
                    break;

                case "END":
                    System.out.println("buh bye");
                    System.exit(0);


                default:
                    System.out.println("unknown input, please try again.");
                    break;
            }
        }
    }

    /**
     * POI-Input. See further descriptions at submethods below.
     * @return
     */
    public Point[] inputPoints() {
        int k = limitInput(intInput("How many POIs will be selected?"),100);
        System.out.println(k+" Points will be chosen.");
        k++;
        Point[] poi = new Point[k];
        poi[0]=new Point(0, 0);
        for (int i = 1; i < k; i++) {
            poi[i] = new Point(0, 0);
            int x = limitInput((intInput("Insert X-Value for POI #" + i)), CWID);
            poi[i].setX(x);
            int y = limitInput(intInput("Insert Y-Value for POI #" + i), CLEN);
            poi[i].setY(y);
        }
        return poi;
    }    //Redundancy of x and y variables in the for-loop to increase readability.


    /**
     * To increase the modularity and reduce the size of our program we decided to implement
     * reusable input methods. The intinput method is secured by the try-catch method.
     * To further protect the Program from its user, the limitinput method only allows
     * inputs that are positive and below a certain max value. The Methods are made in a way that
     * would allow later changes to the extend of the playing field as long as those
     * changes limit to the first quadrant of coordinates.
     * @param Message
     * @return
     */
    private int intInput(String Message) {       //console input method for any integers
        System.out.print(Message);
        System.out.println(" Please input a positive integer!");
        Scanner scInput = new Scanner(System.in);
        try {
            return scInput.nextInt();
        } catch (Exception e) {
            System.out.println("Exception detected, input value was set to '0'!");
        }
        return 0;
    }

    private int limitInput(int input, int limit) {       //Method to limit the value of positive integers
        if (input > limit) {                               //Also eliminates negative integers.
            System.out.println("Your input was lowered to the maximum value of " + limit);
            return limit;
        }
        if (input < 0) {
            System.out.println("Negative input detected, input value was set to '0'!");
            return 0;
        }
        return input;
    }

    /**
     * Lightweight, versatile RNG method and its extension for a random Color.
     */
    private int rng(int min, int max) {
        int n = rand.nextInt(((max - min) + 1));    //RNG from 0 to max-min-difference, +1 to include the max value
        n = n + min;                          //adding min to have an RNG between min and max
        return n;
    }

    private Color randCol() {        //simple method for random colors using the Color constructor
        Color rc = new Color(rng(0, 250), rng(0, 250), rng(0, 250));
        //Maximum of 250 to avoid white rectangles.
        return rc;                  //the r,g and b value each call the rng Method
    }

    /**
     *  Creating one random rectangle. The rectangles name is given by the caller of this method.
     *  Interference cannot occur as there is currently only one Rectangle generation Method per instance
     *  of 'court'
     * @param index Identifier
     * @return Random Rectangle
     */
    public Rectangle createRec(int index) {
        Point p = new Point(rng(0, 900), rng(0, 900)); //100 offset to keep rectangles on the Court.
        //10x10 as minimum rectangle size.
        int w = rng(10, 100);
        int l = rng(10, 100);
        String n = ("Rectangle " + index);
        Color c = randCol();
        Rectangle r = new Rectangle(p, w, l, n, c);
        return r;
    }

    /**
     * Creates a user-given amount of Rectangles. Further documentation below!
     * @return
     */
    public ArrayList<Rectangle> createObstacleList() {
        int k = intInput("How many Rectangles should be created?");
        ArrayList<Rectangle> rectangles = new ArrayList<Rectangle>();
        for (int c = 0; c < k; c++) {
            /*
            The for-loop allows for the unsuccessful attempts to easily be tracked to break the loop in case
            of too many attempts
             */
            for (int i = 0; i < 50; i++) {
                Rectangle r = createRec(i);
                boolean t1 = false;
                //t1 indicates if ANY of the checks returned true
                //comparing the new rectangle to the existing ones to prevent overlap
                for (int j = 0; j < rectangles.size(); j++) {
                    t1 = r.checkOverlapR(rectangles.get(j));
                    if (t1) break;
                }
                //if there is no overlap, the new rectangle is added, else go to next iteration
                if (!t1) {
                    rectangles.add(r);
                    break;
                }
                //break the loop & add r to list if no overlaps found
                if (i == 49) {
                    System.out.println(c + "Rectangles were created before failure!");
                    return rectangles;
                }
            }    //end the method if creation failed 50 times,
        }
        System.out.println("All " + k + " rectangles created successfully!");
        return rectangles;
    }

    /**
     * POI Sorter.
     * We eventually decided against using the Arraysort class by java as it would require
     * knowledge of the implementation of interfaces which currently exceed our programming skill.
     * @param poi Unsorted POI List
     * @return neatly sorted POI List :)
     */
    public Point[] poiSort(Point[] poi) {
        for (int i = 0; i < poi.length -1; i++) {
    double dist1 = poi[i].getDist(poi[i+1]);
            for (int n = i + 1; n < poi.length; n++ ) {
                if (poi[i].getDist(poi[n]) < dist1) {
                    Point p = poi[n];
                    poi[n] = poi[i+1];
                    poi[i+1] = p;
                }
                }
        }
        return poi;
    }


    /**
     * The method makes the robot avoid an amount ov user-generated Obstacles.
     * The robot has succeeded when it reaches the lower right corner.
     */
    public void avoidObst() {

        boolean rightSideClear = true;
        boolean botSideClear = true;
        obstacleList=createObstacleList();
        maggse.setPos(new Point(0,0));
        canvas.drawObs(obstacleList);

        while (maggse.maxX() < 1001 & maggse.maxY() < 1001) {

            for (Rectangle m : obstacleList) {
                if (maggse.tooCloseTo_xEdge(m) | maggse.touchingBoundaryX()) {
                    rightSideClear = false;
                }//touching right side

                if (maggse.tooCloseTo_YEdge(m) | maggse.touchingBoundaryY()) {
                    botSideClear = false;
                }//touching bottom side
            }

            if (rightSideClear && botSideClear) {maggse.moveBy(1,1);}

            if (!rightSideClear && botSideClear) {maggse.moveBy(0,1);}

            if (!rightSideClear && !botSideClear) {break;}

            if (rightSideClear && !botSideClear) {maggse.moveBy(1,0);
            }
            movementGraph(maggse.getPos(), 16); //16ms stall roughly transmits to 60fps
            rightSideClear = true;
            botSideClear = true;
        }
        if (maggse.maxX()>999 && maggse.maxY()>999) System.out.println("Task finished successfully!");
        else {System.out.println("Maggse: Help! I'm stuck!");
            System.out.println("Task failed!");}
        maggse.setPos(new Point (0,0));
    }

    /**
     * This method makes the Robot find the quickest path to visit all given POI, runtime solely depends on number of
     * POI as one movement always takes 4 seconds (100 steps * 40ms stall)
     */
    public void pathLauncher() {
        maggse.setPos(new Point(0,0));
        obstacleList=null;
        canvas.drawObs(null);
        obstacleList= new ArrayList<Rectangle>();
        Point[] poi = inputPoints();
        poi=poiSort(poi);
        for (int i=0; i < poi.length;i++){
            String name = ("Marker #"+i);
            obstacleList.add(new Rectangle(poi[i],10,10,name,Color.RED));
            System.out.println("Next Point: "+i);
            poi[i].printPos();
            moveTo(poi[i],100,40);
            canvas.drawObs(obstacleList);
        }
    }

    /**
     * The robot will take the same time for any movement, but the animation will be smooth if there is sufficient.
     * Computing power of course :)
     */
    public void moveTo(Point target,int steps, int stall) {
        Point current = maggse.getPos();
        int stepX = (target.getX() - current.getX()) / steps;
        int stepY = (target.getY() - current.getY()) / steps;
        for (int i = 0; i < steps; i++) {
            current.moveBy(stepX,stepY);
            movementGraph(current, stall);
        }

    }

    /**
     * Versatile movement animation method for the POI path below.
     * @param nextP new robot position
     * @param stall waiting time
     */
    public void movementGraph(Point nextP, int stall){
        maggse.setPos(nextP);
        canvas.wait(stall);
        canvas.repaint();
    }
}