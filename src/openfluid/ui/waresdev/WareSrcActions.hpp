/*

 This file is part of OpenFLUID software
 Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

 OpenFLUID is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenFLUID is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

 Other Usage means a use of OpenFLUID that is inconsistent with the GPL
 license, and requires a written agreement between You and INRA.
 Licensees for Other Usage of OpenFLUID may use this file in accordance
 with the terms contained in the written agreement between You and INRA.
 
 */


/**
 \file WareSrcActions.hpp
 \brief Header of ...

 \author Aline LIBRES <aline.libres@gmail.com>
 */


#ifndef SRC_OPENFLUID_WARESDEV_UI_WARESRCACTIONS_HPP_
#define SRC_OPENFLUID_WARESDEV_UI_WARESRCACTIONS_HPP_

#include <QAction>


namespace openfluid { namespace ui { namespace waresdev {

class WareSrcActions: QObject
{
  Q_OBJECT

  private:

    static WareSrcActions* mp_Instance;

    QMap<QString, QAction*> m_Actions;

    WareSrcActions();

    ~WareSrcActions();

  public:

    static WareSrcActions* getInstance();

    QAction* getAction(const QString& ActionName);

    // TODO to remove after action implementation
    QMap<QString, QAction*>& getActions()
    {
      return m_Actions;
    }

};

} } }  // namespaces

#endif /* SRC_OPENFLUID_WARESDEV_UI_WARESRCACTIONS_HPP_ */