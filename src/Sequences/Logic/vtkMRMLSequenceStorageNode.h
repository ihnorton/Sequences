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

#ifndef __vtkMRMLSequenceStorageNode_h
#define __vtkMRMLSequenceStorageNode_h

#include "vtkSlicerSequencesModuleLogicExport.h"
#include "vtkMRMLStorageNode.h"

/// \brief MRML node for model storage on disk.
///
/// Storage nodes has methods to read/write vtkPolyData to/from disk.
class VTK_SLICER_SEQUENCES_MODULE_LOGIC_EXPORT vtkMRMLSequenceStorageNode : public vtkMRMLStorageNode
{
public:
  static vtkMRMLSequenceStorageNode *New();
  vtkTypeMacro(vtkMRMLSequenceStorageNode,vtkMRMLStorageNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  /// 
  /// Get node XML tag name (like Storage, Sequence)
  virtual const char* GetNodeTagName()  {return "SequenceStorage";};

  /// Return a default file extension for writting
  virtual const char* GetDefaultWriteFileExtension();

  /// Return true if the reference node can be read in
  virtual bool CanReadInReferenceNode(vtkMRMLNode *refNode);

protected:
  vtkMRMLSequenceStorageNode();
  ~vtkMRMLSequenceStorageNode();
  vtkMRMLSequenceStorageNode(const vtkMRMLSequenceStorageNode&);
  void operator=(const vtkMRMLSequenceStorageNode&);

  /// Initialize all the supported read file types
  virtual void InitializeSupportedReadFileTypes();

  /// Initialize all the supported write file types
  virtual void InitializeSupportedWriteFileTypes();

  /// Read data and set it in the referenced node
  virtual int ReadDataInternal(vtkMRMLNode *refNode);

  /// Write data from a  referenced node
  virtual int WriteDataInternal(vtkMRMLNode *refNode);

  bool WriteToMRB(const char* fullName, vtkMRMLScene *scene);

  bool ReadFromMRB(const char* fullName, vtkMRMLScene *scene);

};

#endif
