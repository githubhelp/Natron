#ifndef DOPESHEETEDITOR_H
#define DOPESHEETEDITOR_H

// ***** BEGIN PYTHON BLOCK *****
// from <https://docs.python.org/3/c-api/intro.html#include-files>:
// "Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard headers are included."
#include <Python.h>
// ***** END PYTHON BLOCK *****

#if !defined(Q_MOC_RUN) && !defined(SBK_RUN)
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#endif
#include "Global/Macros.h"
CLANG_DIAG_OFF(deprecated)
CLANG_DIAG_OFF(uninitialized)
#include <QtGui/QWidget>
CLANG_DIAG_ON(deprecated)
CLANG_DIAG_ON(uninitialized)

#include "Engine/ScriptObject.h"

class DopeSheetEditorPrivate;
class Gui;
class DopeSheetView;
class NodeGui;
class TimeLine;

/**
 * @class DopeSheetEditor
 *
 * The DopeSheetEditor class provides several widgets to edit keyframe animations
 * and video clips.
 *
 * It contains two main widgets : at left, the hierarchy view provides a tree
 * representation of the animated parameters (knobs) of each opened node.
 * At right, the dope sheet view is an OpenGL widget displaying horizontally the
 * keyframes of these knobs.
 *
 * Visually, the editor looks like a single tool with horizontally layered
 * datas.
 *
 * The user can select, move, delete the keyframes and set their interpolation.
 * He can move and trim clips too.
 *
 * The DopeSheetEditor class acts like a facade. It's the only class visible
 * from the outside. It means that if you want to add a feature which require
 * some interaction with the other tools of Natron, you must add its "entry
 * point" here.
 *
 * For example the 'centerOn' function is called from the CurveWidget and
 * the TimeLineGui classes, and calls the 'centerOn' method of the
 * DopeSheetView class.
 *
 * Internally, this class is a composition of the following classes :
 * - DopeSheet -> it's the main model of the dope sheet editor
 * - HierarchyView -> describes the hierarchy view
 * - DopeSheetView -> describes the dope sheet view
 *
 * These two views query the model to display and modify data.
 */
class DopeSheetEditor : public QWidget, public ScriptObject
{
    Q_OBJECT

public:
    DopeSheetEditor(Gui *gui, boost::shared_ptr<TimeLine> timeline, QWidget *parent = 0);
    ~DopeSheetEditor();

    /**
     * @brief Tells to the dope sheet model to add 'nodeGui' to the dope sheet
     * editor.
     *
     * The model will decide if the node should be accepted or discarded.
     */
    void addNode(boost::shared_ptr<NodeGui> nodeGui);

    /**
     * @brief Tells to the dope sheet model to remove 'node' from the dope
     * sheet editor.
     */
    void removeNode(NodeGui *node);

    /**
     * @brief Center the content of the dope sheet view on the timeline range
     * ['xMin', 'xMax'].
     */
    void centerOn(double xMin, double xMax);
    
    void refreshSelectionBboxAndRedrawView();
    
    int getTimelineCurrentTime() const;
    
    DopeSheetView* getDopesheetView() const;
    
    void setTreeWidgetWidth(int width);

public Q_SLOTS:
    /**
     * @brief If 'enabled' is true, enable the triple synchronization,
     * otherwise disable it.
     *
     * The triple sync feature synchronize the timeline navigation
     * between the dope sheet view, the Curve Editor and the opened
     * viewers.
     */
    void toggleTripleSync(bool enabled);

private:
    boost::scoped_ptr<DopeSheetEditorPrivate> _imp;
};

#endif // DOPESHEETEDITOR_H
