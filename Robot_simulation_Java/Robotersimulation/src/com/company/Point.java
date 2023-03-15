package src.com.company;
import java.lang.Math;

public class Point {
    private int x;
    private int y;

    public Point(){}

    public Point(int newX, int newY)
    {x=newX; y=newY;}

    //Methods
    //getters & setters
    public int getX(){return this.x;}
    public int getY(){return this.y;}
    public void setX(int newX){this.x=newX;}
    public void setY(int newY){this.y=newY;}

    //Print
    public void printPos(){
        System.out.println("The X-Value is "+getX());
        System.out.println("The Y-Value is "+getY());}

    //Move
    public void moveBy(int dx, int dy){
        this.x=x+dx;
        this.y=y+dy; }

    public void moveByVec(Point vector){
        this.x=x+vector.getX();
        this.y=y+vector.getY();
    }
    //distance
    double getDist(Point P){
        return(Math.sqrt((Math.pow((P.getX())-x,2))+(Math.pow((P.getY())-y,2)))); };

    //Outputs Points to the Console
    public void printPoints(Point[] poi) {
        for (int i = 0; i < poi.length; i++) {
            System.out.println("Point "+i);
            poi[i].printPos();
        }
    }
}
