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
 @file WareSrcContainer.hpp
 @brief Header of ...

 @author Aline LIBRES <aline.libres@gmail.com>
 */


#ifndef __OPENFLUID_WARESDEV_WARESRCCONTAINER_HPP__
#define __OPENFLUID_WARESDEV_WARESRCCONTAINER_HPP__


#include <QString>
#include <QObject>
#include <QElapsedTimer>

#include <openfluid/waresdev/WareSrcManager.hpp>
#include <openfluid/waresdev/WareSrcMsgStream.hpp>
#include <openfluid/waresdev/WareSrcProcess.hpp>
#include <openfluid/utils/CMakeProxy.hpp>
#include <openfluid/dllexport.hpp>


namespace openfluid { namespace waresdev {


class OPENFLUID_API WareSrcContainer: public QObject
{
  Q_OBJECT

  public:

    enum class ConfigMode
    {
      CONFIG_DEBUG, CONFIG_RELEASE
    };

    enum class BuildMode
    {
      BUILD_WITHINSTALL, BUILD_NOINSTALL
    };


  private slots:

    void processStandardOutput();

    void processErrorOutput();

    void processFinishedOutput(int ExitCode);


  private:

    QString m_AbsolutePath;

    openfluid::ware::WareType m_Type;

    QString m_ID;

    /**
     * Absolute path of the CMake config file if it exists, otherwise an empty string
     */
    QString m_AbsoluteCMakeConfigPath;

    /**
     * Absolute path of the main .cpp as set in the CMake config file, if this .cpp file exists,
     * otherwise an empty string
     */
    QString m_AbsoluteMainCppPath;

    /**
     * Absolute path of the ui-parameterization .cpp as set in the CMake config file, if this .cpp file exists,
     * otherwise an empty string
     */
    QString m_AbsoluteUiParamCppPath;

    /**
     * Absolute path of the CMake config file if it exists, otherwise an empty string
     */
    QString m_AbsoluteCMakeListsPath;

    /**
     * Absolute path of the wareshub.json file if it exists, otherwise an empty string
     */
    QString m_AbsoluteJsonPath;

    openfluid::waresdev::WareSrcMsgStream* mp_Stream;

    ConfigMode m_ConfigMode;

    BuildMode m_BuildMode;

    unsigned int m_BuildJobs;

    QString m_BuildDirPath;

    WareSrcProcess* mp_Process;

    QElapsedTimer m_ProcessTimer;

    QString m_OFVersion;

    WareSrcMsgParser* mp_CurrentParser;

    QList<WareSrcMsgParser::WareSrcMsg> m_Messages;

    /**
      @throw openfluid::base::FrameworkException
    */
    void findCMake();

    void runCommand(const openfluid::utils::CMakeProxy::CommandInfos& CmdInfos, const QProcessEnvironment& Env,
                    WareSrcProcess::Type CmdType = WareSrcProcess::Type::NONE);


  signals:

    void processLaunched();

    void processFinished();

    void configureProcessLaunched(openfluid::ware::WareType Type, const QString& ID);

    void configureProcessFinished(openfluid::ware::WareType Type, const QString& ID);

    void buildProcessLaunched(openfluid::ware::WareType Type, const QString& ID);

    void buildProcessFinished(openfluid::ware::WareType Type, const QString& ID);


  public:

    WareSrcContainer(const QString& AbsolutePath, openfluid::ware::WareType Type, const QString& WareID);

    ~WareSrcContainer();

    void update();

    static QString searchMainCppFileName(const QString& CMakeFileContent);

    static QString searchUiParamCppFileName(const QString& CMakeFileContent);

    /**
      Return the absolute paths of:
      - the CMake config file if it exists on disk,
      - the main .cpp file as set in the CMakeLists.txt, if this .cpp exists on disk.
      If no .cpp file was found (because it doesn't exists, it wasn't found in CMake file,
      or CMake file doesn't exist):
      - the first .cpp file found in this ware directory (not recursive).
      @return a list of existing absolute paths into this ware directory. It can be empty.
    */
    QStringList getDefaultFilesPaths();

    QString getAbsolutePath() const;

    QString getBuildDirPath() const;

    openfluid::ware::WareType getType() const;

    QString getID() const;

    QString getTypeSubDir() const;

    /**
      Returns the absolute path of the main .cpp as set in the CMake config file, if this .cpp file exists,
      otherwise an empty string
    */
    QString getMainCppPath() const;

    /**
      Returns the absolute path of the ui-parameterization .cpp as set in the CMake config file,
      if this .cpp file exists, otherwise an empty string
    */
    QString getUiParamCppPath() const;

    /**
      Returns the absolute path of the CMake config file, if this file exists,
      otherwise an empty string
    */
    QString getCMakeConfigPath() const;

    /**
      Returns the absolute path of the CMakeLists.txt file, if this file exists,
      otherwise an empty string
    */
    QString getCMakeListsPath() const;

    /**
      Returns the absolute path of the wareshub.json file, if this file exists,
      otherwise an empty string
    */
    QString getJsonPath() const;

    std::map<QString,QString> getConfigureVariables() const;

    QString getConfigureGenerator() const;

    QString getConfigureExtraOptions() const;

    QProcessEnvironment getConfigureEnvironment() const;

    QProcessEnvironment getBuildEnvironment() const;

    QString getBuildTarget() const;

    unsigned int getBuildJobs() const;

    QString getGenerateDocTarget() const;

    void prepareBuildDirectory() const;

    void setMsgStream(openfluid::waresdev::WareSrcMsgStream& Stream);

    void setConfigMode(ConfigMode Mode);

    void setBuildMode(BuildMode Mode);

    void setBuildJobs(unsigned int Jobs);

    void configure();

    void build();

    void generateDoc();

    QList<WareSrcMsgParser::WareSrcMsg> getMessages();

    bool isProcessRunning() const;

};


} } // namespaces


#endif /* __OPENFLUID_WARESDEV_WARESRCCONTAINER_HPP__ */
