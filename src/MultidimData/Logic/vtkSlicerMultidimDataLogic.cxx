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

// MultidimData Logic includes
#include "vtkSlicerMultidimDataLogic.h"

// MRMLMultidimData includes
#include "vtkMRMLMultidimDataNode.h"

// MRML includes
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLScene.h"

// VTK includes
#include <vtkNew.h>
#include <vtkObjectFactory.h>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerMultidimDataLogic);

//----------------------------------------------------------------------------
vtkSlicerMultidimDataLogic::vtkSlicerMultidimDataLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerMultidimDataLogic::~vtkSlicerMultidimDataLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic::RegisterNodes()
{
  if (this->GetMRMLScene()==NULL)
  {
    vtkErrorMacro("Scene is invalid");
    return;
  }
  this->GetMRMLScene()->RegisterNodeClass(vtkSmartPointer<vtkMRMLMultidimDataNode>::New());
}

//---------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic::UpdateFromMRMLScene()
{
  if (this->GetMRMLScene()==NULL)
  {
    vtkErrorMacro("Scene is invalid");
    return;
  }
}

//---------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}


//---------------------------------------------------------------------------
void vtkSlicerMultidimDataLogic::SetDataNodesHiddenAtValue( vtkMRMLMultidimDataNode* rootNode, bool hidden, const char* value )
{  
  if ( rootNode==NULL || value==NULL)
  {
    vtkErrorMacro("SetDataNodesHiddenAtValue failed: rootNode or value is invalid");
    return;
  }

  vtkSmartPointer<vtkCollection> dataNodes = vtkSmartPointer<vtkCollection>::New();
  rootNode->GetDataNodesAtValue( dataNodes, value );

  for ( int i = 0; i < dataNodes->GetNumberOfItems(); i++ )
  {
    vtkMRMLNode* currentDataNode = vtkMRMLNode::SafeDownCast( dataNodes->GetItemAsObject( i ) );
    currentDataNode->SetHideFromEditors( hidden );
  }

}


//---------------------------------------------------------------------------
bool vtkSlicerMultidimDataLogic
::GetDataNodesHiddenAtValue( vtkMRMLMultidimDataNode* rootNode, const char* value )
{  
  if ( rootNode==NULL || value==NULL)
  {
    vtkErrorMacro("GetDataNodesHiddenAtValue failed: rootNode or value is invalid");
    return true;
  }

  vtkSmartPointer<vtkCollection> dataNodes = vtkSmartPointer<vtkCollection>::New();
  rootNode->GetDataNodesAtValue( dataNodes, value );

  for ( int i = 0; i < dataNodes->GetNumberOfItems(); i++ )
  {
    vtkMRMLNode* currentDataNode = vtkMRMLNode::SafeDownCast( dataNodes->GetItemAsObject( i ) );
    if ( ! currentDataNode->GetHideFromEditors() )
    {
      return false; // Return false if any node is not hidden for this value
    }
  }

  return true;
}
