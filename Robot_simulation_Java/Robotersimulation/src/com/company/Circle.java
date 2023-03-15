package src.com.company;
import java.awt.*;


public class Circle extends Figures{
    public int rad;

    public Circle(Point position, int radius){
        rad = radius;
        wid = 2*radius;
        len = 2*radius;
        Point pos = position;
        String name;
        Color col = new Color(0, 0, 0);
    }

    public int getRadius() {
        return rad;
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
    public int maxX() {
        return pos.getX()+rad;
    }

    @Override
    public int maxY() { return pos.getY()+rad; }
}
