/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SSH_H__
#define __SSH_H__


/** Class that allow certain ssh functions. It implements these
 * functions by calling external commands */
class Ssh
{
   public:
      Ssh();
      Ssh(const QString& username, const QString& serverIp);
      
		/** Sets the username with which to login */
      void setUsername(const QString& username);
		/** Sets the IP Address of the destination server.
		 * Used for copying from local to remote */
      void setDestinationServerIp(const QString& serverIp);
		/** Sets the IP Address of the source server.
		 * Used when copying from remote to local */
      void setSourceServerIp(const QString& serverIp);
		/** The name of the executable used for scp */
      void setScpName(const QString& scpName);
		/** Sets the parameters with which the scp command is called */
      void setScpParameters(const QStringList& parameters);

		/** Call external scp command with srcFile and destFile as 
		 * parameters. 
		 * @return true is successfull, false otherwise */
      bool scp(const QString& srcFile, const QString& destFile);
		/** Gets the output of the previous scp command executed. Should be
		 * empty if the command was successful */
      QStringList getOutput();
   private:
      QString m_destinationServerIp;
      QString m_sourceServerIp;
      QString m_username;
      QString m_scpName;
      QStringList m_scpParameters;
      QString m_errorOutput;
      QString m_standardOutput;

};

#endif	// __SSH_H__

