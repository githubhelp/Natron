/* ***** BEGIN LICENSE BLOCK *****
 * This file is part of Natron <http://www.natron.fr/>,
 * Copyright (C) 2015 INRIA and Alexandre Gauthier-Foichat
 *
 * Natron is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Natron is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Natron.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>
 * ***** END LICENSE BLOCK ***** */

#ifndef _Gui_NodeGraphPrivate_h_
#define _Gui_NodeGraphPrivate_h_

// ***** BEGIN PYTHON BLOCK *****
// from <https://docs.python.org/3/c-api/intro.html#include-files>:
// "Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard headers are included."
#include <Python.h>
// ***** END PYTHON BLOCK *****

#if !defined(Q_MOC_RUN) && !defined(SBK_RUN)
//#include <boost/shared_ptr.hpp>
//#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
#endif

//#include "NodeGraph.h"

//#include <cstdlib>
//#include <set>
//#include <map>
//#include <vector>
//#include <locale>
//#include <algorithm> // min, max
//

#include "Global/Macros.h"

#include <QtCore/QTimer>
#include <QtCore/QMutex>

//GCC_DIAG_UNUSED_PRIVATE_FIELD_OFF
//// /opt/local/include/QtGui/qmime.h:119:10: warning: private field 'type' is not used [-Wunused-private-field]
//#include <QGraphicsProxyWidget>
//GCC_DIAG_UNUSED_PRIVATE_FIELD_ON
//#include <QGraphicsTextItem>
//#include <QFileSystemModel>
//#include <QScrollBar>
//#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
//#include <QDialogButtonBox>
//#include <QUndoStack>
//#include <QToolButton>
//#include <QThread>
//#include <QDropEvent>
//#include <QApplication>
//#include <QCheckBox>
//#include <QMimeData>
//#include <QLineEdit>
//#include <QDebug>
//#include <QtCore/QRectF>
//#include <QRegExp>
//#include <QtCore/QTimer>
//#include <QAction>
#include <QPainter>
#include <QPointF>
#include <QColor>
#include <QPen>
#include <QStyleOptionGraphicsItem>
//CLANG_DIAG_OFF(deprecated)
//CLANG_DIAG_OFF(uninitialized)
//#include <QMutex>
//CLANG_DIAG_ON(deprecated)
//CLANG_DIAG_ON(uninitialized)
//
//#include <SequenceParsing.h>
//
//#include "Engine/AppManager.h"
//#include "Engine/BackDrop.h"
//#include "Engine/Dot.h"
//#include "Engine/FrameEntry.h"
//#include "Engine/Hash64.h"
//#include "Engine/KnobFile.h"
//#include "Engine/Node.h"
//#include "Engine/NodeGroup.h"
//#include "Engine/NodeSerialization.h"
//#include "Engine/OfxEffectInstance.h"
//#include "Engine/OutputSchedulerThread.h"
//#include "Engine/Plugin.h"
//#include "Engine/Project.h"
//#include "Engine/Settings.h"
//#include "Engine/ViewerInstance.h"
//
//#include "Gui/ActionShortcuts.h"
//#include "Gui/BackDropGui.h"
//#include "Gui/CurveEditor.h"
//#include "Gui/CurveWidget.h"
//#include "Gui/DockablePanel.h"
//#include "Gui/Edge.h"
//#include "Gui/FloatingWidget.h"
//#include "Gui/Gui.h"
//#include "Gui/Gui.h"
//#include "Gui/GuiAppInstance.h"
//#include "Gui/GuiApplicationManager.h"
//#include "Gui/GuiMacros.h"
//#include "Gui/Histogram.h"
//#include "Gui/KnobGui.h"
//#include "Gui/Label.h"
//#include "Gui/Menu.h"
//#include "Gui/NodeBackDropSerialization.h"
//#include "Gui/NodeCreationDialog.h"
#include "Gui/NodeGraphUndoRedo.h" // NodeGuiPtr
//#include "Gui/NodeGui.h"
//#include "Gui/NodeGuiSerialization.h"
//#include "Gui/NodeSettingsPanel.h"
//#include "Gui/SequenceFileDialog.h"
//#include "Gui/TabWidget.h"
//#include "Gui/TimeLineGui.h"
//#include "Gui/ToolButton.h"
//#include "Gui/ViewerGL.h"
//#include "Gui/ViewerTab.h"
//
//#include "Global/QtCompat.h"
class NodeGraph;
class Gui;
class NodeCollection;
struct NodeClipBoard;
class NodeGuiSerialization;
class ViewerTab;

#define NATRON_CACHE_SIZE_TEXT_REFRESH_INTERVAL_MS 1000



#define NATRON_NODE_DUPLICATE_X_OFFSET 50

///These are percentages of the size of the NodeGraph in widget coordinates.
#define NATRON_NAVIGATOR_BASE_HEIGHT 0.2
#define NATRON_NAVIGATOR_BASE_WIDTH 0.2

#define NATRON_SCENE_MAX 1e6
#define NATRON_SCENE_MIN 0

enum EventStateEnum
{
    eEventStateNone,
    eEventStateMovingArea,
    eEventStateZoomingArea,
    eEventStateDraggingArrow,
    eEventStateDraggingNavigator,
    eEventStateDraggingNode,
    eEventStateResizingBackdrop,
    eEventStateSelectionRect,
};

class Navigator
    : public QGraphicsPixmapItem
{
    QGraphicsLineItem* _navLeftEdge;
    QGraphicsLineItem* _navBottomEdge;
    QGraphicsLineItem* _navRightEdge;
    QGraphicsLineItem* _navTopEdge;

public:

    Navigator(QGraphicsItem* parent = 0)
        : QGraphicsPixmapItem(parent)
          , _navLeftEdge(NULL)
          , _navBottomEdge(NULL)
          , _navRightEdge(NULL)
          , _navTopEdge(NULL)
    {
        QPen p;

        p.setBrush( QColor(200,200,200) );
        p.setWidth(2);

        _navLeftEdge = new QGraphicsLineItem(this);
        _navLeftEdge->setPen(p);

        _navBottomEdge = new QGraphicsLineItem(this);
        _navBottomEdge->setPen(p);

        _navRightEdge = new QGraphicsLineItem(this);
        _navRightEdge->setPen(p);

        _navTopEdge = new QGraphicsLineItem(this);
        _navTopEdge->setPen(p);
    }

    virtual ~Navigator()
    {
    }

    int getLineWidth() const
    {
        return _navLeftEdge->pen().width();
    }

    void refreshPosition(const QPointF & navTopLeftScene,
                         double width,
                         double height)
    {
        setPos(navTopLeftScene);

        _navLeftEdge->setLine(0,
                              height,
                              0,
                              0);

        _navTopEdge->setLine(0,
                             0,
                             width,
                             0);

        _navRightEdge->setLine(width,
                               0,
                               width,
                               height);

        _navBottomEdge->setLine(width,
                                height,
                                0,
                                height);
    }
};

class SelectionRectangle
    : public QGraphicsRectItem
{
public:

    SelectionRectangle(QGraphicsItem* parent = 0)
        : QGraphicsRectItem(parent)
    {
    }

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem */*option*/,
                       QWidget */*widget*/) OVERRIDE FINAL
    {
        QRectF r = rect();
        QColor color(16,84,200,20);

        painter->setBrush(color);
        painter->drawRect(r);
        double w = painter->pen().widthF();
        painter->fillRect(QRect(r.x() + w,r.y() + w,r.width() - w,r.height() - w),color);
    }
};


struct NodeGraphPrivate
{
    NodeGraph* _publicInterface;
    Gui* _gui;
    
    boost::weak_ptr<NodeCollection> group;
    
    QPoint _lastMousePos;
    QPointF _lastNodeDragStartPoint;
    QPoint _lastSelectionStartPoint;
    EventStateEnum _evtState;
    NodeGuiPtr _magnifiedNode;
    double _nodeSelectedScaleBeforeMagnif;
    bool _magnifOn;
    Edge* _arrowSelected;
    mutable QMutex _nodesMutex;
    NodeGuiList _nodes;
    NodeGuiList _nodesTrash;

    ///Enables the "Tab" shortcut to popup the node creation dialog.
    ///This is set to true on enterEvent and set back to false on leaveEvent
    bool _nodeCreationShortcutEnabled;
    QString _lastNodeCreatedName;
    QGraphicsItem* _root; ///< this is the parent of all items in the graph
    QGraphicsItem* _nodeRoot; ///< this is the parent of all nodes
    QGraphicsTextItem* _cacheSizeText;
    QTimer _refreshCacheTextTimer;
    Navigator* _navigator;
    QUndoStack* _undoStack;
    QMenu* _menu;
    QGraphicsItem *_tL,*_tR,*_bR,*_bL;
    bool _refreshOverlays;

    Edge* _highLightedEdge;
    NodeGuiPtr _mergeHintNode;

    ///This is a hint edge we show when _highLightedEdge is not NULL to display a possible connection.
    Edge* _hintInputEdge;
    Edge* _hintOutputEdge;
    
    NodeGuiPtr _backdropResized; //< the backdrop being resized
    
    NodeGuiList _selection;
    
    std::map<NodeGuiPtr,NodeGuiList> _nodesWithinBDAtPenDown;
    
    QGraphicsRectItem* _selectionRect;
    bool _bendPointsVisible;
    bool _knobLinksVisible;
    double _accumDelta;
    bool _detailsVisible;
    QPointF _deltaSinceMousePress; //< mouse delta since last press
    bool _hasMovedOnce;
    
    ViewerTab* lastSelectedViewer;
    bool wasLaskUserSeekDuringPlayback;
    
    NodeGraphPrivate(Gui* gui,
                     NodeGraph* p,
                     const boost::shared_ptr<NodeCollection>& group);
    
    void resetAllClipboards();

    QRectF calcNodesBoundingRect();

    void copyNodesInternal(const NodeGuiList& selection,NodeClipBoard & clipboard);
    void pasteNodesInternal(const NodeClipBoard & clipboard,const QPointF& scenPos,
                            bool useUndoCommand,
                            std::list<std::pair<std::string,boost::shared_ptr<NodeGui> > > *newNodes);

    /**
     * @brief Create a new node given the serialization of another one
     * @param offset[in] The offset applied to the new node position relative to the serialized node's position.
     **/
    boost::shared_ptr<NodeGui> pasteNode(const NodeSerialization & internalSerialization,
                                         const NodeGuiSerialization & guiSerialization,
                                         const QPointF & offset,
                                         const boost::shared_ptr<NodeCollection>& group,
                                         const std::string& parentName,
                                         bool clone);


    /**
     * @brief This is called once all nodes of a clipboard have been pasted to try to restore connections between them
     * WARNING: The 2 lists must be ordered the same: each item in serializations corresponds to the same item in the newNodes
     * list. We're not using 2 lists to avoid a copy from the paste function.
     **/
    void restoreConnections(const std::list<boost::shared_ptr<NodeSerialization> > & serializations,
                            const std::list<std::pair<std::string,boost::shared_ptr<NodeGui> > > & newNodes);

    void editSelectionFromSelectionRectangle(bool addToSelection);

    void resetSelection();

    void setNodesBendPointsVisible(bool visible);

    void rearrangeSelectedNodes();

    void toggleSelectedNodesEnabled();
    
};

#endif // _Gui_NodeGraphPrivate_h_
