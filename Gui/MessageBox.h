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


#ifndef _NATRON_MESSAGE_BOX_H_
#define _NATRON_MESSAGE_BOX_H_

// ***** BEGIN PYTHON BLOCK *****
// from <https://docs.python.org/3/c-api/intro.html#include-files>:
// "Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard headers are included."
#include <Python.h>
// ***** END PYTHON BLOCK *****

#if !defined(Q_MOC_RUN) && !defined(SBK_RUN)
#include <boost/scoped_ptr.hpp>
#endif

#include "Global/Macros.h"
CLANG_DIAG_OFF(deprecated)
CLANG_DIAG_OFF(uninitialized)
#include <QDialog>
CLANG_DIAG_ON(deprecated)
CLANG_DIAG_ON(uninitialized)

#include "Global/GlobalDefines.h"

class QCheckBox;
class QAbstractButton;

namespace Natron {
struct MessageBoxPrivate;
class MessageBox : public QDialog
{
GCC_DIAG_SUGGEST_OVERRIDE_OFF
    Q_OBJECT
GCC_DIAG_SUGGEST_OVERRIDE_ON
    
public:
    
    enum MessageBoxTypeEnum
    {
        eMessageBoxTypeInformation,
        eMessageBoxTypeWarning,
        eMessageBoxTypeError,
        eMessageBoxTypeQuestion
    };
    
    MessageBox(const QString & title,
               const QString & message,
               MessageBoxTypeEnum type,
               const Natron::StandardButtons& buttons,
               Natron::StandardButtonEnum defaultButton,
               QWidget* parent);
    
    virtual ~MessageBox();
    
    Natron::StandardButtonEnum getReply() const;
    
    void setCheckBox(QCheckBox* checkbox);
    
    bool isCheckBoxChecked() const;
    
public Q_SLOTS:
    
    void onButtonClicked(QAbstractButton* button);
    
private:
    
    void updateSize();
    
    void init(const QString & title,
              const QString & message,
              const Natron::StandardButtons& buttons,
              Natron::StandardButtonEnum defaultButton);
    
    virtual bool event(QEvent* e) OVERRIDE FINAL;
    
    boost::scoped_ptr<MessageBoxPrivate> _imp;
};

}

#endif // _NATRON_MESSAGE_BOX_H_
