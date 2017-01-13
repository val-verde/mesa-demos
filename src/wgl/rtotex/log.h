//////////////////////////////////////////////////////////////////////////////////////////
//	log.h
//	class to output an error log
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

class LOG
{
protected:
	FILE * logfile;
	
	bool Shutdown(void);

public:
	bool Init(const char * filename);

	//Output to log
	void OutputNewline();
	void OutputError(const char * text, ...);
	void OutputSuccess(const char * text, ...);
		
	LOG() {}
	~LOG(){ Shutdown(); }
};

#endif
