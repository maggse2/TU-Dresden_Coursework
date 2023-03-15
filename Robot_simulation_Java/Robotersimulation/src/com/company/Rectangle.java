package src.com.company;

import java.awt.Color;

public class Rectangle extends Figures{

    /**
     * Constructor for rectangles.
     * Currently all input methods as well as the rng only give positive integers, thus there is no need to ensure
     * positive values in this method.
     * @param position
     * @param width
     * @param length
     * @param name1
     * @param color
     */
    public Rectangle(Point position, int width, int length, String name1, Color color) {
        pos=position;
        len=length;
        wid=width;
        name=name1;
        if (color==Color.white) col=Color.BLACK; //replacing white color input with black
            else col=color;
    }

    //prints Attributes of the rectangle, was used for early troubleshooting
    public void printAtr(){
        System.out.println("Position:");
        pos.printPos();
        System.out.println("The X-Extent is "+wid);
        System.out.println("The Y-Extent is "+len);
        System.out.println("Object Name: "+name);
        System.out.println("Object Color: ");
        System.out.println("R: "+col.getRed());
        System.out.println("G: "+col.getGreen());
        System.out.println("B: "+col.getBlue());

    }

    /**
     * Lightweight method to check if Rectangles overlap each other.
     * This works by comparing the overlap for each dimension. If the overlap is true for two dimensions,
     * 'TRUE' is displayed.
     * @param r2
     * @return
     */
    public boolean checkOverlapR(Rectangle r2){
        Point p1=getPos();                      //Position of r1
        Point p2=r2.getPos();                   //Position of r2
        if (p2.getX()>=p1.getX() && p2.getX()<=p1.getX()+getWid()) {    //Check if p2 is INSIDE the x-Extent of r1
            //Check if the y-Extents overlap
            if (p2.getY()>=p1.getY() && p2.getY()<=p1.getY()+getLen()) return true;//p2 in y-Ext. of r1
            if (p1.getY()>=p2.getY() && p1.getY()<=p2.getY()+r2.getLen()) return true;//p1 in y- Ext of r2
        }
        if (p1.getX()>=p2.getX() && p1.getX()<=p2.getX()+r2.getWid()) { //Check if p1 is INSIDE the x-Extent of r2
            //Same y-overlap test as above
            if (p2.getY()>=p1.getY() && p2.getY()<=p1.getY()+getLen()) return true;
            if (p1.getY()>=p2.getY() && p1.getY()<=p2.getY()+r2.getLen()) return true;
        }
        return false;
    }

    @Override
    public int minX() {
        return pos.getX();
    }

    @Override
    public int minY() {
        return pos.getY();
    }

    @Override
    public int maxX() {return pos.getX()+wid;}

    @Override
    public int maxY() {
        return pos.getY()+len;
    }
}