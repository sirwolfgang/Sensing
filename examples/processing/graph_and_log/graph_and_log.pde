/**
 todo: add header notes
  */

import controlP5.*;
import processing.serial.*;
import processing.video.*;


import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;

MovieMaker mm;

class eq implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		return mouseX;
	}		
}

class eq2 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		return mouseY;
	}		
}

class eq3 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		if(mousePressed)
			return 400;
		else
			return 0;
	}		
}

RollingLine2DTrace r,r2,r3;
Graph2D g;

int activeTab=1;	


Serial myPort;

ControlP5 controlP5;

DropdownList ddlCom;



int myColorBackground = color(0,0,0);

int sliderValue = 100;

void setup() {
  
  //mm = new MovieMaker(this, 800,600, "sensing_processing.mov", 30, MovieMaker.ANIMATION, MovieMaker.BEST);
  
  size(800,600);
  frame.setResizable(true);
  frameRate(30);
  controlP5 = new ControlP5(this);
  
  //ddlCom = controlP5.addDropdownList("comlist", 40,40,100,120);
  //customize(ddlCom);
  
  controlP5.addButton("start",10,680,20,80,20);
  controlP5.addButton("stop",4,680,60,80,20);
  
  // tab global is a tab that lies on top of any other tab and
  // is always visible
  
  controlP5.tab("configuration").setColorForeground(0xffff0000);
  controlP5.tab("configuration").setColorBackground(0xff330000);
  
  controlP5.trigger();
  
  // in case you want to receive a controlEvent when
  // a  tab is clicked, use activeEvent(true)
  controlP5.tab("configuration").activateEvent(true);
  controlP5.tab("configuration").setId(2);
  
  controlP5.tab("default").activateEvent(true);
  // to rename the label of a tab, use setLabe("..."),
  // the name of the tab will remain as given when initialized.
  controlP5.tab("default").setLabel("Graph");
  controlP5.tab("default").setId(1);
  
  	r  = new RollingLine2DTrace(new eq() ,100,0.1f);
	r.setTraceColour(0, 255, 0);
	
	r2 = new RollingLine2DTrace(new eq2(),100,0.1f);
	r2.setTraceColour(255, 0, 0);
	
	r3 = new RollingLine2DTrace(new eq3(),100,0.1f);
	r3.setTraceColour(0, 0, 255);
	 
	g = new Graph2D(this, 600, 400, false);
	g.setYAxisMax(600);
	g.addTrace(r);
	g.addTrace(r2);
	g.addTrace(r3);
	g.position.y = 120;
	g.position.x = 100;
	g.setYAxisTickSpacing(100);
	g.setXAxisMax(5f);
        g.setAxisColour(255,255,255);
        g.setFontColour(255,255,255);
        g.setXAxisLabel("Time");
        g.setYAxisLabel("Sensor Reading");
        
  
}

void draw() {
  background(0);
  //fill(255);
  //rect(0,0,width,100);
  if (activeTab == 1)
  {
    g.draw();
  }
  //mm.addFrame();
}

void keyPressed() {
  if (key == ' ') {
    mm.finish();  // Finish the movie if space bar is pressed!
  }
}
  
void controlEvent(ControlEvent theControlEvent) {
  if(theControlEvent.isController()) {
    println("controller : "+theControlEvent.controller().id());
  } else if (theControlEvent.isTab()) {
    
    
    println("tab : "+theControlEvent.tab().id()+" / "+theControlEvent.tab().name());
    activeTab = theControlEvent.tab().id();
  
  }
}

void customize(DropdownList ddl) {
  ddl.setBackgroundColor(color(190));
  ddl.setItemHeight(20);
  ddl.setBarHeight(15);
  ddl.captionLabel().set("pulldown");
  ddl.captionLabel().style().marginTop = 3;
  ddl.captionLabel().style().marginLeft = 3;
  ddl.valueLabel().style().marginTop = 3;
 
 
  /*
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  */
  
  
  for(int i=1;i<20;i++) {
    ddl.addItem("COM "+i,i);
  }
 
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255,128));
}
