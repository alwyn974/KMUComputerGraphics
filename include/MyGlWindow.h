
#include "FL/Fl_Gl_Window.H"
#include "FL/Fl.H"
#include "FL/Fl_Value_Slider.H"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/glut.h"
#include "FL/Fl_Double_Window.H"

#include "stdio.h"
#include "math.h"
#include "3DUtils.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

#include "core.h"


#include "object.h"


class MyGlWindow : public Fl_Gl_Window {
	public:
		MyGlWindow(int x, int y, int w, int h);
		
		void putText(char* string, int x, int y, float r, float g, float b);
		std::vector<Vec3f *> history;
        int selected = -1;
		

		Fl_Slider* time;	
		int run;
		void update();
		void drawStuff();
		void doPick();
		void test();
	private:
		void draw();					// standard FlTk
		
		
		int handle(int);				// standard FlTk
		
		float fieldOfView;
		Viewer *m_viewer;


        std::vector<std::unique_ptr<Mover>> movers;
		Mover* mover;

		void setProjection(int clearProjection = 1);
		void getMouseNDC(float& x, float& y);
		void setupLight(float x, float y, float z);
};

