package src.com.company;

import java.util.ArrayList;
import javax.swing.JPanel;
import java.awt.*;

public class DrawingSurface extends JPanel {
    ArrayList <Rectangle> Obs;

    /**
     * The overwritten paintComponent Method calls the super Method to clear the Canvas (advised on Stackoverflow)
     * We limited this method to only draw our singular robot. If more circles are desired, this method must be
     * reworked.
     * @param g
     */
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        if (Obs!=null) {
            for (int i = 0; i < Obs.size(); i++) {
                Rectangle r = Obs.get(i);
                g.setColor(r.getCol());
                g.drawRect(r.getPos().getX(), r.getPos().getY(), r.getWid(), r.getLen());
                g.fillRect(r.getPos().getX(), r.getPos().getY(), r.getWid(), r.getLen());
            }
        }
        g.setColor(Court.maggse.getCol());
        g.fillOval(Court.maggse.pos.getX(), Court.maggse.pos.getY(), Court.maggse.rad, Court.maggse.rad);
        g.setColor(Color.BLACK);
        g.drawOval(Court.maggse.pos.getX(), Court.maggse.pos.getY(), Court.maggse.rad, Court.maggse.rad);
        }

    /**
     * We could not really adapt ourselves to the 'Zeichne Figuren' method from the task and made the repaint a little
     * differently. We apologize for the inconvenience.
     * @param newObs
     */
    public void repaintObs(ArrayList<Rectangle> newObs){
        Obs=newObs;
        this.repaint();
    }
    public void repaint (){
        super.repaint();
    }


}
