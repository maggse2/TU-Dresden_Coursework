package src.com.company;

import java.awt.Color;

public abstract class Figures {
    /**
     * Super Class for Rectangle and Circle combining their common attributes.
     */
    protected Point pos = new Point(0,0);
    protected String name;
    protected Color col = new Color(0, 0, 0);
    protected int len;    //extent of y
    protected int wid;    //extent of x

    //Getters & Setters
    public Point getPos(){return pos;}
    public String getName(){return name;}
    public Color getCol(){return col;}
    public int getLen(){return len;}
    public int getWid(){return wid;}

    public void setPos(Point newPos){pos=newPos;}
    public void setName(String newName){name=newName;}
    public void setLen(int newLen){len=newLen;}
    public void setWid(int newWid){wid=newWid;}
    public void setCol(Color newCol){
        if (newCol==Color.white) System.out.println("Color white is illegal.");
        else col=newCol;}
    public void setColN(String newCol){                      //Address a color by its name.
        if (newCol.equals("WHITE")) System.out.println("Color white is illegal.");
        else col=Color.getColor(newCol);}

    //Moving around (Copied from the Point class to avoid nesting statements)
    public void moveBy(int dx, int dy){
        pos.setX(pos.getX()+dx);
        pos.setY(pos.getY()+dy);}

    public void moveByVec(Point vector){
        pos.setX(pos.getX()+vector.getX());
        pos.setY(pos.getY()+vector.getY());}


    /**
     * These methods are overridden in the subclasses.
     * @return
     */
    abstract public int minX();
    abstract public int minY();
    abstract public int maxX();
    abstract public int maxY();
}

