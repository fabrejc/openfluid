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
  @file FluidHubAPIClient.cpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
  @author Armel THONI <armel.thoni@inrae.fr>
*/


#include <rapidjson/document.h>

#include <openfluid/utils/FluidHubAPIClient.hpp>


namespace openfluid { namespace utils {


template<class T>
void JSONArrayToStringSet(const rapidjson::Value& Obj, std::set<T>& Set)
{
  Set.clear();

  if (Obj.IsArray() && !Obj.Empty())
  {
    for (unsigned int i=0;i<Obj.Capacity();i++)
    {
      if (Obj[i].IsString())
      {
        Set.insert(T(Obj[i].GetString()));
      }
    }
  }
}


// =====================================================================
// =====================================================================


void JSONArrayToStringVector(const rapidjson::Value& Obj, std::vector<std::string>& Vector)
{
  Vector.clear();

  if (Obj.IsArray() && !Obj.Empty())
  {
    for (unsigned int i=0;i<Obj.Capacity();i++)
    {
      if (Obj[i].IsString())
      {
        Vector.push_back(std::string(Obj[i].GetString()));
      }
    }
  }
}


// =====================================================================
// =====================================================================


void JSONObjectToDetailedWares(const rapidjson::Value& Obj,
                               FluidHubAPIClient::WaresDetailsByID_t& WMap, bool IsV0ofAPI=true)
{
  WMap.clear();

  if (Obj.IsObject())
  {
    std::string DASH, DescriptionKey;
    if (IsV0ofAPI)
    {
      DASH = "-";
      DescriptionKey = "shortdesc";
    }
    else
    {
      DASH = "_";
      DescriptionKey = "description";
    }
    

    for (rapidjson::Value::ConstMemberIterator it = Obj.MemberBegin();it != Obj.MemberEnd(); ++it)
    {
      if (it->value.IsObject())
      {
        std::string WareID = it->name.GetString();

        WMap[WareID] = FluidHubAPIClient::WareDetailedDescription();

        rapidjson::Value::ConstMemberIterator itMember = it->value.FindMember(DescriptionKey.c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsString())
        {
          WMap[WareID].ShortDescription = std::string(itMember->value.GetString());
        }

        itMember = it->value.FindMember(("git"+DASH+"url").c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsString())
        {
          WMap[WareID].GitUrl = std::string(itMember->value.GetString());
        }

        itMember = it->value.FindMember(("git"+DASH+"branches").c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsArray())
        {
          JSONArrayToStringVector(itMember->value,WMap[WareID].GitBranches);
        }

        itMember = it->value.FindMember(("issues"+DASH+"counts").c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsObject())
        {
          for (rapidjson::Value::ConstMemberIterator itCounters = itMember->value.MemberBegin();
               itCounters != itMember->value.MemberEnd();
               ++itCounters)
          {
            if (itCounters->value.IsInt())
            {
              WMap[WareID].IssuesCounters[itCounters->name.GetString()] = itCounters->value.GetInt();
            }
          }
        }

        itMember = it->value.FindMember(("users"+DASH+"ro").c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsArray())
        {
          JSONArrayToStringSet(itMember->value,WMap[WareID].ROUsers);
        }

        itMember = it->value.FindMember(("users"+DASH+"rw").c_str());
        if (itMember != it->value.MemberEnd() && itMember->value.IsArray())
        {
          JSONArrayToStringSet(itMember->value,WMap[WareID].RWUsers);
        }
      }
    }
  }
}


// =====================================================================
// =====================================================================


void FluidHubAPIClient::reset()
{
  m_RESTClient.setBaseURL("");
  m_RESTClient.setSSLConfiguration(RESTClient::SSLConfiguration());
  logout();
  m_RESTClient.resetRawHeaders();
  m_RESTClient.addRawHeader("Content-Type", "application/json");
  //m_RESTClient.addRawHeader(QByteArray("Accept"), QByteArray("application/x.openfluid.FLUIDhub+json;version=1.0"));
  m_RESTClient.addRawHeader("Accept", "application/x.openfluid.FLUIDhub+json;version=1.0");
  m_HubAPIVersion.clear();
  m_HubCapabilities.clear();
  m_HubName.clear();
  m_HubStatus.clear();
}


// =====================================================================
// =====================================================================


void FluidHubAPIClient::logout()
{
  m_RESTClient.removeRawHeader("Authorization");
}


// =====================================================================
// =====================================================================


bool FluidHubAPIClient::isCapable(const QString& Capacity) const
{
  return (m_HubCapabilities.find(Capacity) != m_HubCapabilities.end());
}


// =====================================================================
// =====================================================================


QString FluidHubAPIClient::wareTypeToString(openfluid::ware::WareType Type)
{
  if (Type == openfluid::ware::WareType::SIMULATOR)
  {
    return "simulators";
  }
  else if (Type == openfluid::ware::WareType::OBSERVER)
  {
    return "observers";
  }
  else if (Type == openfluid::ware::WareType::BUILDEREXT)
  {
    return "builderexts";
  }

  return "";
}


// =====================================================================
// =====================================================================


bool FluidHubAPIClient::connect(const QString& URL,const RESTClient::SSLConfiguration& SSLConfig)
{
  RESTClient::Reply Reply;
  bool ValidNature = false;

  disconnect();
  m_RESTClient.setBaseURL(URL);
  m_RESTClient.setSSLConfiguration(SSLConfig);

  Reply = m_RESTClient.getResource("/");

  if (Reply.isOK())
  {
    rapidjson::Document JSONDoc;

    if (JSONDoc.Parse<0>(Reply.getContent().toStdString().c_str()).HasParseError())
    {
      return false;
    }

    if (JSONDoc.IsObject())
    {
      // deduce API system from API base call content
      for (rapidjson::Value::ConstMemberIterator it = JSONDoc.MemberBegin();it != JSONDoc.MemberEnd(); ++it)
      {
        QString Key = QString(it->name.GetString());
        if ((Key == "api-version" || Key == "api_version") && it->value.IsString())
        {
          m_HubAPIVersion = it->value.GetString();
          m_IsV0ofAPI = m_HubAPIVersion.startsWith("0."); 
        }
      }

      if (m_IsV0ofAPI)
      {
        m_WareCapabilityName = "wareshub";
      }
      else
      {
        m_WareCapabilityName = "wares";
      }

      for (rapidjson::Value::ConstMemberIterator it = JSONDoc.MemberBegin();it != JSONDoc.MemberEnd(); ++it)
      {
        QString Key = QString(it->name.GetString());

        if (Key == "nature" && it->value.IsString() && (
              (m_IsV0ofAPI && QString(it->value.GetString()) == "OpenFLUID FluidHub") || 
              QString(it->value.GetString()) == "OpenFLUID"))
        {
          ValidNature = true; // URL is really a FluidHub
        }
        else if (Key == "name" && it->value.IsString())
        {
          m_HubName = it->value.GetString();
        }
        else if (Key == "status" && it->value.IsString())
        {
          m_HubStatus = it->value.GetString();
        }
        else if (Key == "capabilities" && it->value.IsArray())
        {
          JSONArrayToStringSet(it->value,m_HubCapabilities);
        }
      }
    }
  }

  if (!ValidNature)
  {
    disconnect();
  }

  return isConnected();
}


// =====================================================================
// =====================================================================


void FluidHubAPIClient::disconnect()
{
  reset();
}


// =====================================================================
// =====================================================================


FluidHubAPIClient::WaresListByType_t FluidHubAPIClient::getAllAvailableWares() const
{
  WaresListByType_t WaresDesc;

  WaresDesc[openfluid::ware::WareType::SIMULATOR] = std::set<openfluid::ware::WareID_t>();
  WaresDesc[openfluid::ware::WareType::OBSERVER] = std::set<openfluid::ware::WareID_t>();
  WaresDesc[openfluid::ware::WareType::BUILDEREXT] = std::set<openfluid::ware::WareID_t>();

  if (isConnected() && isCapable(m_WareCapabilityName))
  {
    RESTClient::Reply Reply = m_RESTClient.getResource("/wares");

    if (Reply.isOK())
    {
      rapidjson::Document JSONDoc;

      if (JSONDoc.Parse<0>(Reply.getContent().toStdString().c_str()).HasParseError())
      {
        return WaresDesc;
      }

      if (JSONDoc.IsObject())
      {
        for (rapidjson::Value::ConstMemberIterator it = JSONDoc.MemberBegin();it != JSONDoc.MemberEnd(); ++it)
        {
          QString Key = QString(it->name.GetString());

          if (Key == "simulators")
          {
            JSONArrayToStringSet(it->value,WaresDesc[openfluid::ware::WareType::SIMULATOR]);
          }
          else if (Key == "observers")
          {
            JSONArrayToStringSet(it->value,WaresDesc[openfluid::ware::WareType::OBSERVER]);
          }
          else if (Key == "builderexts")
          {
            JSONArrayToStringSet(it->value,WaresDesc[openfluid::ware::WareType::BUILDEREXT]);
          }
        }
      }
    }
  }

  return WaresDesc;
}


// =====================================================================
// =====================================================================


std::string fetchFieldFromEndpoint(const RESTClient& Client, const std::string Method, const std::string Url, 
                                   const std::string WantedKey, const std::string RequestData="")
{
  RESTClient::Reply Reply;
  if (Method == "GET")
  {
    Reply = Client.getResource(QString::fromStdString(Url));
  }
  else if (Method == "POST")
  {
    Reply = Client.postResource(QString::fromStdString(Url), QString::fromStdString(RequestData));
  }

  if (Reply.isOK())
  {
    rapidjson::Document JSONDoc;

    if (JSONDoc.Parse<0>(Reply.getContent().toStdString().c_str()).HasParseError())
    {
      return "";
    }

    if (JSONDoc.IsObject())
    {
      for (rapidjson::Value::ConstMemberIterator it = JSONDoc.MemberBegin();it != JSONDoc.MemberEnd(); ++it)
      {
        std::string Key = it->name.GetString();

        if (Key == WantedKey)
        {
          if (it->value.IsString())
          {
            return it->value.GetString();
          }
        }
      }
    }
  }
  return "";
}


// =====================================================================
// =====================================================================


std::string FluidHubAPIClient::getUserUnixname(const std::string Email, const std::string Password)
{
  if (!m_IsV0ofAPI && isConnected())
  {
    if (!m_RESTClient.hasRawHeader("Authorization"))
    {
      std::string AccessBody = "{\"email\":\""+Email+"\",\"password\":\""+Password+"\"}";
      std::string AccessToken = fetchFieldFromEndpoint(m_RESTClient, "POST", "/auth/token", "access", AccessBody);
      if (AccessToken != "")
      {
        QString HeaderData = "Bearer " + QString::fromStdString(AccessToken);
        m_RESTClient.addRawHeader("Authorization", HeaderData.toLocal8Bit()); 
      }
    }
    std::string unixname = fetchFieldFromEndpoint(m_RESTClient, "GET", "/account", "unixname");
    return unixname;
  }
  return "";
}
  

// =====================================================================
// =====================================================================


FluidHubAPIClient::WaresDetailsByID_t FluidHubAPIClient::getAvailableWaresWithDetails(openfluid::ware::WareType Type, 
                                                                                      const QString& Username) const
{
  WaresDetailsByID_t WaresDesc = std::map<openfluid::ware::WareID_t,WareDetailedDescription>();

  QString Path = wareTypeToString(Type);

  if (isConnected() && isCapable(m_WareCapabilityName) && !(Path.isEmpty()))
  {
    Path = "/wares/"+Path;

    if (!Username.isEmpty())
    {
      Path += "?username="+Username;
    }

    RESTClient::Reply Reply = m_RESTClient.getResource(Path);

    if (Reply.isOK())
    {
      rapidjson::Document JSONDoc;

      if (JSONDoc.Parse<0>(Reply.getContent().toStdString().c_str()).HasParseError())
      {
        return WaresDesc;
      }

      if (JSONDoc.IsObject())
      {
        JSONObjectToDetailedWares(JSONDoc, WaresDesc, m_IsV0ofAPI);
      }
    }
  }

  return WaresDesc;
}


// =====================================================================
// =====================================================================


QString FluidHubAPIClient::getNews(const QString& Lang) const
{
  QString Content;

  if (isConnected() && isCapable("news"))
  {
    QString Path = "/news";

    if (!Lang.isEmpty())
    {
      Path += "?lang="+Lang;
    }

    RESTClient::Reply Reply = m_RESTClient.getResource(Path);

    if (Reply.isOK())
    {
      return Reply.getContent();
    }
  }

  return "";
}


} }  // namespaces
