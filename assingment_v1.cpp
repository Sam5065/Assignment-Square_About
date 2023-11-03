// assingment_v1.cpp: A program using the TL-Engine
// Samual Hilland
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/

	//sphere starting pos
	const float sphereStartX = -85.0f;
	const float sphereStartY = 10.0f;
	const float sphereStartZ = -85.0f;

	//cube starting pos
	const float cubeStartX = 0.0f;
	const float cubeStartY = 5.0f;
	const float cubeStartZ = 0.0f;

	//platform starting pos
	const float platformStartX = 0.0f;
	const float platformStartY = -5.0f;
	const float platformStartZ = 0.0f;

	//camera postions
	const float cameraLocationX = 0.0f;
	const float cameraLocationY = 200.0f;
	const float cameraLocationZ = -170.0f;
	const float cameraRotation = 45; //rotates camera 45 degress, so that stage can be seen

	//Sphere config
	//speed = 0.005 works best on lab pcs
	//rotation speed= 0.01 works best on lab pcs
	float sphereSpeed = 0.005; //speed at which the sphere moves
	const float sphereRotationSpeed = 0.010; //speed at which the sphere rotates

	float sphereX; //current sphere X
	float sphereY; //current sphere y
	float sphereZ; //current sphere Z

	//stage corrdinates (sphere stops once it reaches these)
	//stage top left coordinates:
	const float stageTopLeftX = -85.0f;
	const float stageTopLeftZ = 85.0f;
	//stage top right corrdinates:
	const float stageTopRightX = 85.0f;
	const float stageTopRightZ = 85.0f;
	//stage bttm right:
	const float stageBttmRightX = 85.0f;
	const float stageBttmRightZ = -85.0f;
	//stage bttm left:
	const float stageBttmLeftX = -85.0f;
	const float stageBttmLeftZ = -85.0f;
	
	bool gamePaused = false; //game pause

	ICamera* myCamera;//Creation of camera
	myCamera = myEngine->CreateCamera(kManual); 
	myCamera->SetPosition(cameraLocationX, cameraLocationY, cameraLocationZ); //camera pos
	myCamera->RotateLocalX(cameraRotation); //rotates camera

	//Game objects:
	IMesh* platformMesh = myEngine->LoadMesh("platform.x"); //game stage
	IModel* platformModel = platformMesh->CreateModel();
	platformModel->SetPosition(platformStartX, platformStartY, platformStartZ); //sets platform location according the assing spec

	IMesh* sphere1Mesh = myEngine->LoadMesh("spheremesh.x"); //sphere 1
	IModel* sphere1 = sphere1Mesh->CreateModel();
	sphere1->SetPosition(sphereStartX, sphereStartY, sphereStartZ); //default sphere location

	IMesh* cubeMesh = myEngine->LoadMesh("cubemesh.x"); //cube
	IModel* cubeModel = cubeMesh->CreateModel();
	cubeModel->SetPosition(cubeStartX, cubeStartY, cubeStartZ); //default cube location

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();
		/**** Update your scene each frame here ****/

		sphereX = sphere1->GetX(); //stores current sphere X location
		sphereY = sphere1->GetY(); //stores current sphere Y location
		sphereZ = sphere1->GetZ();//stores current sphere Z location

		if (gamePaused == false)
		{
			//movement sphere1:
			if (sphereX <= stageTopLeftX && sphereZ < stageTopLeftZ) //bttm left to top left
			{
				sphere1->MoveZ(sphereSpeed); //moves
				sphere1->RotateX(sphereRotationSpeed);//rotates
			}

			else if (sphereX < stageTopRightX && sphereZ >= stageTopRightZ)//top left to top right
			{
				sphere1->MoveX(sphereSpeed);//moves
				sphere1->RotateZ(-sphereRotationSpeed); //rotates
			}

			else if (sphereX >= stageBttmRightX && sphereZ > stageBttmRightZ)//top right to bttm right 
			{
				sphere1->MoveZ(-sphereSpeed);//moves sphere
				sphere1->RotateX(-sphereRotationSpeed);//rotates
			}

			else if (sphereX > stageBttmLeftX && sphereZ <= stageBttmLeftZ)//bttm right to btmm left
			{
				sphere1->MoveX(-sphereSpeed); //moves sphere
				sphere1->RotateZ(sphereRotationSpeed);//rotates sphere
			}
		}


		//Speed decrease code:
		if (myEngine->KeyHit(Key_D))
		{

		}

		if (myEngine->KeyHit(Key_A))
		{

		}

		if (myEngine->KeyHit(Key_P)) //pauses game if pressed
		{
			gamePaused = true;
			//myEngine->Stop();
		}

		if (myEngine->KeyHit(Key_Escape)) //quits game if pressed.
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
