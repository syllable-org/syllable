
/*  Syllable Media Preferences
 *  Copyright (C) 2003 Arno Klenke
 *  Based on the preferences code by Daryl Dudey
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of version 2 of the GNU Library
 *  General Public License as published by the Free Software
 *  Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 *  MA 02111-1307, USA
 */

#include <unistd.h>
#include <iostream>
#include <gui/desktop.h>
#include "main.h"

int main( int argc, char *argv[] )
{
	PrefsMediaApp *pcPrefsMediaApp;

	pcPrefsMediaApp = new PrefsMediaApp();
	pcPrefsMediaApp->Run();
}

PrefsMediaApp::PrefsMediaApp():os::Application( "application/x-vnd-MediaPreferences" )
{
	// Get screen width and height to centre the window
	os::Desktop * pcDesktop = new os::Desktop();
	int iWidth = pcDesktop->GetScreenMode().m_nWidth;
	int iHeight = pcDesktop->GetScreenMode().m_nHeight;
	int iLeft = ( iWidth - 500 ) / 2;
	int iTop = ( iHeight - 350 ) / 2;

	// Create media manager 
	m_pcManager = new os::MediaManager();

	if ( !m_pcManager->IsValid() )
	{
		std::cout << "Media server not running" << std::endl;
		PostMessage( os::M_QUIT );
		return;
	}

	// Show main window
	pcWindow = new MainWindow( os::Rect( iLeft, iTop, iLeft + 520, iTop + 350 ) );
	pcWindow->Show();
	pcWindow->MakeFocus();
}

bool PrefsMediaApp::OkToQuit()
{
	delete( m_pcManager );
	return ( true );
}

PrefsMediaApp::~PrefsMediaApp()
{

}




