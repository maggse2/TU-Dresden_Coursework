package src.com.company;

import javax.swing.*;
import java.awt.*;

import java.util.ArrayList;

public class Canvas {
    JFrame window;
    public DrawingSurface drawingSurface= new DrawingSurface();
    /**
     * The constructor of Canvas creates the windows for the simulation.
     */
    private Canvas() {
        window = new JFrame("simulation");
        window.setSize(Court.CWID, Court.CLEN); //no getter needed, variables are final
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//so the window closes properly
        window.setTitle("Robot Simulation");
        window.setBackground(Color.white);
        window.setVisible(true);//set window visible
        window.setResizable(false);
        window.getContentPane().setBackground(Color.white);//set background
        window.add(drawingSurface);
    }

    private static Canvas canvasSingleton;
    /**
    *Method checks if there is an existing Canvas and creates a new one if necessary -> Singleton
     */
    public static Canvas getCanvas() {
        if (canvasSingleton == null) {
            canvasSingleton = new Canvas();
        }
        return canvasSingleton;
    }

    public void wait(int ms) {
        try {
            Thread.sleep(ms);
        } catch (Exception END) {}
    }

    public void drawObs(ArrayList<Rectangle> Obs) {
        drawingSurface.repaintObs(Obs);
    }

    public void repaint(){
        drawingSurface.repaint();
    }

}


