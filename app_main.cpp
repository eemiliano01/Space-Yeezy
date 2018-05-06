#include "App.h"

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
    
    // Instantiate a new App
    App* myApp = new App("MyApp", 50, 50, 1080, 1080);

	// Start the app
    myApp->run();
}
