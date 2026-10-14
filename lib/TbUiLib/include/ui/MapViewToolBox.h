/*
 Copyright (C) 2010 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "NotifierConnection.h"
#include "ui/GeneratorTool.h"
#include "ui/ToolBox.h"

#include "vm/vec.h"

#include <array>
#include <memory>

class QStackedLayout;

namespace tb
{
namespace mdl
{
struct SelectionChange;
} // namespace mdl

namespace ui
{
class ClipTool;
class ArrayTool;
class BezierBendTool;
class PolygonCutTool;
class AssembleBrushTool;
class CreateEntityTool;
class DrawShapeTool;
class PrefabTool;
class MapDocument;
class MoveObjectsTool;
class ExtrudeTool;
class RotateTool;
class ScaleTool;
class SculptTool;
class ShearTool;
class SubdivisionTool;
class SymmetryTool;
class VertexTool;
class EdgeTool;
class FaceTool;

class MapViewToolBox : public ToolBox
{
private:
  MapDocument& m_document;

  std::unique_ptr<ClipTool> m_clipTool;
  std::unique_ptr<ArrayTool> m_arrayTool;
  std::unique_ptr<BezierBendTool> m_bezierBendTool;
  std::unique_ptr<PolygonCutTool> m_polygonCutTool;
  std::unique_ptr<AssembleBrushTool> m_assembleBrushTool;
  std::unique_ptr<CreateEntityTool> m_createEntityTool;
  std::unique_ptr<DrawShapeTool> m_drawShapeTool;
  std::unique_ptr<PrefabTool> m_prefabTool;
  std::unique_ptr<MoveObjectsTool> m_moveObjectsTool;
  std::unique_ptr<ExtrudeTool> m_extrudeTool;
  std::unique_ptr<RotateTool> m_rotateTool;
  std::unique_ptr<ScaleTool> m_scaleTool;
  std::unique_ptr<SculptTool> m_sculptTool;
  std::unique_ptr<ShearTool> m_shearTool;
  std::unique_ptr<SubdivisionTool> m_subdivisionTool;
  std::unique_ptr<SymmetryTool> m_symmetryTool;
  bool m_symmetryToolPanelSelected = false;
  std::unique_ptr<VertexTool> m_vertexTool;
  std::unique_ptr<EdgeTool> m_edgeTool;
  std::unique_ptr<FaceTool> m_faceTool;
  std::array<std::unique_ptr<GeneratorTool>, 3> m_generatorTools;

  NotifierConnection m_notifierConnection;

public:
  MapViewToolBox(MapDocument& map, QStackedLayout* bookCtrl);
  ~MapViewToolBox() override;

public: // tools
  ClipTool& clipTool();
  ArrayTool& arrayTool();
  BezierBendTool& bezierBendTool();
  PolygonCutTool& polygonCutTool();
  AssembleBrushTool& assembleBrushTool();
  CreateEntityTool& createEntityTool();
  DrawShapeTool& drawShapeTool();
  PrefabTool& prefabTool();
  MoveObjectsTool& moveObjectsTool();
  ExtrudeTool& extrudeTool();
  RotateTool& rotateTool();
  ScaleTool& scaleTool();
  SculptTool& sculptTool();
  ShearTool& shearTool();
  SubdivisionTool& subdivisionTool();
  SymmetryTool& symmetryTool();
  VertexTool& vertexTool();
  EdgeTool& edgeTool();
  FaceTool& faceTool();

  void toggleGeneratorTool(GeneratorTool::Kind kind);
  bool canToggleGeneratorTool(GeneratorTool::Kind kind) const;
  bool generatorToolActive(GeneratorTool::Kind kind) const;
  bool anyGeneratorToolActive() const;
  bool parameterToolActive() const;

  void toggleAssembleBrushTool();
  bool assembleBrushToolActive() const;
  void performAssembleBrush();

  void toggleClipTool();
  bool clipToolActive() const;
  void toggleClipSide();
  void performClip();
  void removeLastClipPoint();

  void togglePolygonCutTool();
  bool polygonCutToolActive() const;
  void performPolygonCut();
  void togglePolygonSpawnTool();
  bool polygonSpawnToolActive() const;
  void performPolygonSpawn();
  bool undoActiveToolStep();

  void toggleRotateTool();
  bool rotateToolActive() const;
  double rotateToolAngle() const;
  vm::vec3d rotateToolCenter() const;
  void moveRotationCenter(const vm::vec3d& delta);

  void toggleScaleTool();
  bool scaleToolActive() const;

  void toggleSculptTool();
  bool canToggleSculptTool() const;
  bool sculptToolActive() const;

  void toggleArrayTool();
  bool canToggleArrayTool() const;
  bool arrayToolActive() const;
  void applyArrayTool();

  void toggleSubdivisionTool();
  bool canToggleSubdivisionTool() const;
  bool subdivisionToolActive() const;
  void applySubdivisionTool();

  void toggleShearTool();
  bool shearToolActive() const;

  void toggleSymmetryTool();
  bool canToggleSymmetryTool() const;
  bool symmetryToolActive() const;
  bool symmetryToolPanelSelected() const;
  bool symmetryModifierActive() const;
  bool symmetryRelinkInProgress() const;

  bool anyVertexToolActive() const;

  void toggleVertexTool();
  bool vertexToolActive() const;

  void toggleEdgeTool();
  bool edgeToolActive() const;

  void toggleBevelTool();
  bool canToggleBevelTool() const;
  bool bevelToolActive() const;
  void applyBevelTool();

  void toggleFaceTool();
  bool faceToolActive() const;

  void toggleInsetTool();
  bool canToggleInsetTool() const;
  bool insetToolActive() const;
  void applyInsetTool();

  void toggleSpinTool();
  bool canToggleSpinTool() const;
  bool spinToolActive() const;
  void applySpinTool(bool snapVerticesToInteger);

  void toggleBezierBendTool();
  bool canToggleBezierBendTool() const;
  bool bezierBendToolActive() const;
  void applyBezierBendTool();

  bool anyModalToolActive() const;

  void moveVertices(const vm::vec3d& delta);

private: // Tool related methods
  void createTools(QStackedLayout* bookCtrl);

private: // notification
  void registerTool(Tool& tool, QStackedLayout* bookCtrl);
  void connectObservers();
  void toolActivated(Tool& tool);
  void toolDeactivated(Tool& tool);
  void updateEditorContext();
  void documentWasLoaded();
  void selectionDidChange(const mdl::SelectionChange& selectionChange);

  void updateToolPage();
};

} // namespace ui
} // namespace tb
