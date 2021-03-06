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
  @file ObserverSignatureRegistry.cpp

  @author Aline LIBRES <aline.libres@gmail.com>
*/


#include <openfluid/machine/ObserverSignatureRegistry.hpp>
#include <openfluid/machine/ObserverPluginsManager.hpp>
#include <openfluid/machine/ObserverInstance.hpp>


namespace openfluid { namespace machine {


OPENFLUID_SINGLETON_INITIALIZATION(ObserverSignatureRegistry)


ObserverSignatureRegistry::ObserverSignatureRegistry():
    WareSignatureRegistry<ObserverSignatureInstance>()
{
  update();
}


// =====================================================================
// =====================================================================


ObserverSignatureRegistry::~ObserverSignatureRegistry()
{

}


// =====================================================================
// =====================================================================


const ObserverSignatureInstance* ObserverSignatureRegistry::signature(const std::string& ObserverID) const
{
  for (std::vector<openfluid::machine::ObserverSignatureInstance*>::const_iterator it =
      m_AvailableSignatures.begin(); it != m_AvailableSignatures.end(); ++it)
  {
    if ((*it)->Signature->ID == ObserverID)
    {
      return (*it);
    }
  }
  return nullptr;
}


// =====================================================================
// =====================================================================


void ObserverSignatureRegistry::update()
{
  unloadAll();

  m_AvailableSignatures =
      openfluid::machine::ObserverPluginsManager::instance()->getAvailableWaresSignatures().availablePlugins();

  openfluid::machine::ObserverPluginsManager::instance()->unloadAllWares();
}


// =====================================================================
// =====================================================================


const std::vector<ObserverSignatureInstance*>& ObserverSignatureRegistry::getAvailableSignatures() const
{
  return m_AvailableSignatures;
}


// =====================================================================
// =====================================================================


void ObserverSignatureRegistry::unloadAll()
{
  openfluid::machine::ObserverPluginsManager::instance()->unloadAllWares();
}


} } /* namespaces */

