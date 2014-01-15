/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerMultidimDataModuleWidget_h
#define __qSlicerMultidimDataModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerMultidimDataModuleExport.h"

#include <QtGui>

class qSlicerMultidimDataModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_MULTIDIMDATA_EXPORT qSlicerMultidimDataModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerMultidimDataModuleWidget(QWidget *parent=0);
  virtual ~qSlicerMultidimDataModuleWidget();

  /// Set up the GUI from mrml when entering
  virtual void enter();
  /// Disconnect from scene when exiting
  virtual void exit(); 

public slots:

  void onRootNodeChanged();

  void onParameterNameEdited();
  void onParameterUnitEdited();

  void onDataNodeEdited( int row, int column );
  void onHideDataNodeClicked( int row, int column );

  void onAddDataNodeButtonClicked();
  void onRemoveDataNodeButtonClicked();

  /// Respond to the scene events
  void onNodeAddedEvent(vtkObject* scene, vtkObject* node);
  void onNodeRemovedEvent(vtkObject* scene, vtkObject* node);
  void onMRMLSceneEndImportEvent();
  void onMRMLSceneEndRestoreEvent();
  void onMRMLSceneEndBatchProcessEvent();
  void onMRMLSceneEndCloseEvent();

protected:
  QScopedPointer<qSlicerMultidimDataModuleWidgetPrivate> d_ptr;
  
  virtual void setup();  

  void setEnableWidgets(bool enable);

protected slots:

  void UpdateRootNode();
  void UpdateCandidateNodes();

  void CreateVisItem( QTableWidgetItem*, bool );

private:
  Q_DECLARE_PRIVATE(qSlicerMultidimDataModuleWidget);
  Q_DISABLE_COPY(qSlicerMultidimDataModuleWidget);
};

#endif
