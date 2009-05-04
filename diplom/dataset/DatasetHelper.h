/*
 * DatasetHelper.h
 *
 *  Created on: 27.07.2008
 *      Author: ralph
 */
#ifndef DATASETHELPER_H_
#define DATASETHELPER_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/textfile.h"
#include "wx/file.h"
#include "wx/image.h"
#include "wx/wfstream.h"
#include "wx/datstrm.h"
#include "wx/txtstrm.h"
#include "wx/xml/xml.h"

#include <vector>

#include "datasetInfo.h"


#include "../gui/selectionBox.h"

#include "../gui/mainFrame.h"
#include "../gfx/theScene.h"
#include "splinePoint.h"

#include "AnatomyHelper.h"
#include "../gfx/ShaderHelper.h"

#include "../misc/lic/TensorField.h"

class MainFrame;
class DatasetInfo;
class TheScene;
class AnatomyHelper;
class ShaderHelper;
class SplinePoint;
class SelectionBox;
class Fibers;
class TensorField;
class Surface;

class DatasetHelper {
public:
	DatasetHelper(MainFrame*);
	virtual ~DatasetHelper();

	bool load(int index);
	bool load(wxString filename, bool createBox = true, float threshold = 0.0, bool active = true, bool showFS = true, bool useTex = true);
	void finishLoading(DatasetInfo*);
	bool loadScene(wxString filename);
	bool loadTextFile(wxString*, wxString);
	bool fileNameExists(wxString filename);

	//! Saves the current scene to an xml file
	void save(wxString filename);

	std::vector<std::vector<SelectionBox*> > getSelectionBoxes();
	void updateAllSelectionBoxes();
	Vector mapMouse2World(int, int);
	Vector mapMouse2WorldBack(int, int);

	bool invertFibers() {fibersInverted = !fibersInverted; return fibersInverted;};

	void createIsoSurface();
	void createDistanceMap();
	void createCutDataset();
	/*
	 * Called from MainFrame when a kdTree thread signals it's finished
	 */
	void treeFinished();

	/*
	 * Helper functions
	 */
	void printTime();
	void printwxT(wxString string);
	void printDebug(wxString string, int level);
	/*
	 * Check for GL error
	 */
	bool GLError();
	void printGLError(wxString function = wxT(""));

	void updateView(float x, float y, float z);

	void changeZoom(int z);
	void moveScene(int x, int y);

	void doMatrixManipulation();

	bool getFiberDataset(Fibers *&f);
	bool getSurfaceDataset(Surface *&s);
	float* getVectorDataset();
	TensorField* getTensorField();

	void toggleBoxes() {showBoxes = !showBoxes;};
	bool togglePointMode() {return pointMode = !pointMode;};
	bool getPointMode() {return pointMode;};

	void updateLoadStatus();

	/////////////////////////////////////////////////////////////////////////////////
	// general info about the datasets
	/////////////////////////////////////////////////////////////////////////////////
	int rows;
	int columns;
	int frames;
	
	float xVoxel;
	float yVoxel;
	float zVoxel;
	
	unsigned int countFibers;
	wxString lastError;
	// last path from loading, load file dialog will open with it
	wxString lastPath;
	wxString m_scenePath;
	wxString m_screenshotPath;
	wxString m_screenshotName;
	
	wxString m_scnFileName;
	bool m_scnFileLoaded;

	bool anatomy_loaded;
	bool fibers_loaded;
	bool vectors_loaded;
	bool tensors_loaded;
	bool surface_loaded;
	bool surface_isDirty;

	/////////////////////////////////////////////////////////////////////////////////
	// state variables for rendering
	/////////////////////////////////////////////////////////////////////////////////
	Matrix4fT m_transform;
	bool useVBO;
	GLenum lastGLError;
	int quadrant;
	int textures;
	//! if set the shaders will be reloaded during next render() call
	bool scheduledReloadShaders;
	// the screenshot button has been pressed, next render pass it will be executed
	bool scheduledScreenshot;

	bool showBoxes;
	bool blendAlpha;
	bool pointMode;

	int debugLevel;
	/////////////////////////////////////////////////////////////////////////////////
	// state variables for menu entries
	/////////////////////////////////////////////////////////////////////////////////
	bool showSagittal;
	bool showCoronal;
	bool showAxial;
	
	bool showCrosshair;

	float xSlize;
	float ySlize;
	float zSlize;
	
	Vector m_freeSlizeOffset;
	Vector m_freeSlizeRotation;
	// lighting for fibers
	bool lighting;
	// ignore threshold for textures on meshes
	bool blendTexOnMesh;
	// show the lic texture on spline surface
	bool use_lic;
	// draw vectors as small lines on spline surface
	bool drawVectors;
	// normal direction of the spline surface
	float normalDirection;
	bool fibersInverted;
	bool useFakeTubes;
	bool useTransparency;
	bool filterIsoSurf;
	int colorMap;
	bool showColorMapLegend;
	
	bool morphing;
	/////////////////////////////////////////////////////////////////////////////////
	// pointers to often used objects
	/////////////////////////////////////////////////////////////////////////////////
	SplinePoint* lastSelectedPoint;
	SelectionBox* lastSelectedBox;
	SelectionBox* boxAtCrosshair;
	AnatomyHelper* anatomyHelper;
	ShaderHelper* shaderHelper;
	MainFrame* mainFrame;
	TheScene* scene;

	bool boxLockIsOn;
	bool semaphore;
	int threadsActive;
	/////////////////////////////////////////////////////////////////////////////////
	// variables for mouse interaction
	/////////////////////////////////////////////////////////////////////////////////
	bool m_isDragging;
	bool m_isrDragging;
	bool m_ismDragging;
	float zoom;
	int xMove;
	int yMove;
	
	bool m_texAssigned;
	bool m_selBoxChanged;

	int geforceLevel;

private:

};

#define ID_KDTREE_FINISHED	50

#endif /* DATASETHELPER_H_ */