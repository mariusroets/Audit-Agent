/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "ssh.h"

Ssh::Ssh()
{
   m_destinationServerIp = "";
   m_sourceServerIp = "";
}
Ssh::Ssh(const QString& username, const QString& serverIp)
{
   m_username = username;
   m_destinationServerIp = serverIp;
   m_sourceServerIp = "";
}

void Ssh::setUsername(const QString& username)
{
   m_username = username;
}
void Ssh::setDestinationServerIp(const QString& serverIp)
{
   m_destinationServerIp = serverIp;
}
void Ssh::setSourceServerIp(const QString& serverIp)
{
   m_sourceServerIp = serverIp;
}
void Ssh::setScpName(const QString& scpName)
{
   m_scpName = scpName;
}
void Ssh::setScpParameters(const QStringList& parameters)
{
   m_scpParameters = parameters;
}

bool Ssh::scp(const QString& srcFile, const QString& destFile)
{
   //QObject *parent;
   
   QStringList arguments;
   if (m_destinationServerIp.isEmpty() && m_sourceServerIp.isEmpty()) {
      qDebug ("Local copying not supported");
      return false;
   }
   if (!m_destinationServerIp.isEmpty() && !m_sourceServerIp.isEmpty()) {
      qDebug ("Remote to remote copying is not supported");
      return false;
   }
   QString dest = destFile;
   QString src = srcFile;
   if (!m_destinationServerIp.isEmpty()) {
      dest = m_username + "@" + m_destinationServerIp + ":" + destFile;
   }
   if (!m_sourceServerIp.isEmpty()) {
      src = m_username + "@" + m_sourceServerIp + ":" + srcFile;
   }
   arguments << m_scpParameters << src << dest;

   QProcess *process = new QProcess();
   process->start(m_scpName, arguments);
   if (!process->waitForFinished())
      return false;

   m_errorOutput = process->readAllStandardError();
   m_standardOutput = process->readAllStandardOutput();
   
   if (!m_errorOutput.isEmpty()) {
      return false;
   } else if (process->exitStatus() == QProcess::NormalExit) { 
      return true;
   } 
   return false;

}

QStringList Ssh::getOutput()
{
   return QStringList() << m_standardOutput << m_errorOutput;
}
