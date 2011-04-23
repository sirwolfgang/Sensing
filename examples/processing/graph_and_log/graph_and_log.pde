/**
 todo: add header notes
  */

import controlP5.*;
import processing.serial.*;
import processing.video.*;


import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;

boolean MAKE_MOVIE = false;

MovieMaker mm;


class eq implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		//return mouseX;
                return intDataArray[0];
	}		
}

class eq2 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		//return mouseY;
                return intDataArray[1];
	}		
}

class eq3 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		/*
                if(mousePressed)
			return 400;
		else
			return 0;
                */
                return intDataArray[2];
	}
}

class eq4 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
	       return intDataArray[3];
	}		
}

class eq5 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
	       return intDataArray[4];
	}		
}

class eq6 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
	       return intDataArray[5];
	}		
}

class eq7 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
	       return intDataArray[6];
	}		
}

class eq8 implements ILine2DEquation{
	public double computePoint(double x,int pos) {
	       return intDataArray[7];
	}		
}


RollingLine2DTrace r,r2,r3,r4,r5,r6,r7,r8;
Graph2D g;

int activeTab=1;	


Serial myPort;
StringBuffer lineBuffer;
int[] intDataArray;

ControlP5 controlP5;

DropdownList ddlCom;



int myColorBackground = color(0,0,0);

int sliderValue = 100;

void setup() {
  
  if (MAKE_MOVIE) {
    mm = new MovieMaker(this, 800,600, "sensing_processing.mov", 30, MovieMaker.ANIMATION, MovieMaker.BEST);
  }
  
  size(800,600);
  frame.setResizable(true);
  frameRate(30);
  
  String portName = Serial.list()[0];
  lineBuffer = new StringBuffer();
  intDataArray = new int[8]; 
  
  myPort = new Serial (this, portName, 9600);
  
  
  
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
	
        r4 = new RollingLine2DTrace(new eq4(),100,0.1f);
	r4.setTraceColour(0, 255, 255);
	
        r5 = new RollingLine2DTrace(new eq5(),100,0.1f);
	r5.setTraceColour(255, 255, 255);

        r6 = new RollingLine2DTrace(new eq6(),100,0.1f);
        r6.setTraceColour(0, 128, 255);
        
        r7 = new RollingLine2DTrace(new eq7(),100,0.1f);
        r7.setTraceColour(0, 255, 128);
        
        
        r8 = new RollingLine2DTrace(new eq8(),100,0.1f);
        r8.setTraceColour(128, 128, 128);


	g = new Graph2D(this, 600, 400, false);
	g.setYAxisMax(100);
	g.addTrace(r);
	g.addTrace(r2);
	g.addTrace(r3);
	g.addTrace(r4);
	g.addTrace(r5);
        g.addTrace(r6);
        g.addTrace(r7);
        g.addTrace(r8);
        
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
  
  if (MAKE_MOVIE){ 
     mm.addFrame();
  }
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

  
  //setup com port dropdown
  for(int i=1;i<20;i++) {
    ddl.addItem("COM "+i,i);
  }
 
  ddl.setColorBackground(color(60));
  ddl.setColorActive(color(255,128));
}


void serialEvent(Serial p)
{
  //println("[serialEvent]");
  if ( myPort.available() > 0) {  // If data is available,
    String inBuffer = myPort.readString();         // read it and store it in val
    if (inBuffer!=null) {
      //println(inBuffer);
      lineBuffer.append(inBuffer);
      //println(lineBuffer);
      /* 
      if (lineBuffer.toString().indexOf('\r') !=-1)
        {
        //println("found CR");
        //splitBuffer();
        }
     */
      if (lineBuffer.toString().indexOf('\n') !=-1)
        {
        //println("found LF");
        splitBuffer();
        }
      
    }
    
  }
}

void splitBuffer(){
  println("[splitBuffer]");
  String[] curReading = split(lineBuffer.toString(), ',');
  for (int i=0; i<curReading.length; i++)
  {
    print("[curReading][");
    print(i);
    print("]");
    println (curReading[i]);
  }
  int sensor = Integer.parseInt(curReading[1]);
  print("[sensor]:");
  println(sensor); 
  
  int sensorReading = Integer.parseInt(curReading[2]);
  print("[sensorReading]:");
  println(sensorReading); 
  
  intDataArray[sensor-10] = sensorReading;
  
  //TODO: Strip out CR in the last item...
  //TODO: graph here
  
  //TODO: write line to csv file here
  
  
  //empty the lineBuffer
  lineBuffer.setLength(0);
  
  
}


