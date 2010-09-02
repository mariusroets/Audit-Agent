/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __INFO_H__
#define __INFO_H__

class Info
{
   public:
      Info() {};
      virtual ~Info() {};
      
   protected:
      virtual void read() =0;

};

#endif	// __INFO_H__
