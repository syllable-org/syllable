/*
    A Mixer plugin for the Syllable Dock

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
                                                                                                                                                       
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <gui/image.h>
#include <gui/window.h>
#include <gui/slider.h>
#include <util/looper.h>
#include <util/resources.h>
#include <storage/file.h>
#include <media/manager.h>
#include <media/server.h>

#include "../../dock/dockplugin.h"

using namespace os;

class MixerWindow;

class DockMixer : public DockPlugin
{
	public:
		DockMixer( os::Path cPath, os::Looper* pcDock );
		~DockMixer();

		os::String GetIdentifier() ;
		Point GetPreferredSize( bool bLargest );
		os::Path GetPath() { return( m_cPath ); }
		
		virtual void AttachedToWindow();
		virtual void DetachedFromWindow();

        virtual void Paint( const Rect &cUpdateRect );

		virtual void MouseMove( const os::Point& cNewPos, int nCode, uint32 nButtons, os::Message* pcData );
		virtual void MouseUp( const os::Point & cPosition, uint32 nButton, os::Message * pcData );
		virtual void MouseDown( const os::Point& cPosition, uint32 nButtons );
        void MixerWindowHidden() { m_bWindowShown = false; }
	private:
		os::Path m_cPath;
		os::BitmapImage* m_pcDockIcon;
		os::BitmapImage* m_pcDragIcon;
		os::Looper* m_pcDock;
		os::MediaManager * m_pcManager;
		MixerWindow* m_pcWindow;
		bool m_bWindowShown;
		bool m_bCanDrag;
		bool m_bDragging;
};

enum { SET_VALUE };

class MixerView : public View
{
	public:
		MixerView( Rect cFrame ) : View( cFrame, "view" )
		{
		}
		void	WindowActivated( bool bIsActive )
		{
			if( !bIsActive )
				GetWindow()->PostMessage( M_QUIT, GetWindow() );
		}
		void Paint( const Rect& cUpdateRect )
		{
			DrawFrame( GetBounds(), FRAME_RECESSED | FRAME_THIN );
		}
};

class MixerWindow : public Window
{
	public:
		MixerWindow( MediaManager* pcManager, DockMixer* pcPlugin, const Rect& cFrame ) : Window( cFrame, "mixer", "mixer", os::WND_NO_TITLE | os::WND_NOT_RESIZABLE | os::WND_NO_BORDER )
		{
			m_pcPlugin = pcPlugin;
			m_pcManager = pcManager;
			m_pcView = new MixerView( GetBounds() );
			m_pcSlider = new Slider( GetBounds().Resize( 3, 3, -3, -3 ), "slider", new os::Message( SET_VALUE ), Slider::TICKS_RIGHT, 10, Slider::KNOB_SQUARE, VERTICAL );
			m_pcSlider->SetMinMax( 0, 100 );
			m_pcSlider->SetTarget( this );
			m_pcView->AddChild( m_pcSlider );
			AddChild( m_pcView );
			m_pcView->MakeFocus();
		}
		~MixerWindow()
		{
		}
		void HandleMessage( Message* pcMessage )
		{
			switch( pcMessage->GetCode() )
			{
				case SET_VALUE:
				{
					int32 nValue = m_pcSlider->GetValue().AsInt32();
					nValue = nValue;
					Message cMsg( MEDIA_SERVER_SET_MASTER_VOLUME );
					cMsg.AddInt32( "volume", nValue );
					m_pcManager->GetInstance()->GetServerLink().SendMessage( &cMsg );
				}
				break;
				default:
					Window::HandleMessage( pcMessage );
			}
		}
		bool OkToQuit()
		{
			Hide();
			m_pcPlugin->MixerWindowHidden();
			return( false );
		}
		void Update()
		{
			int32 nVolume;
			Message cMsg( MEDIA_SERVER_GET_MASTER_VOLUME );
			Message cReply;
			m_pcManager->GetInstance()->GetServerLink().SendMessage( &cMsg, &cReply );
			if( cReply.FindInt32( "volume", &nVolume ) == 0 )
			{
				m_pcSlider->SetValue( nVolume, false );
			}
		}
	private:
		MediaManager* m_pcManager;
		DockMixer* m_pcPlugin;
		MixerView* m_pcView;
		Slider* m_pcSlider;
};

//*************************************************************************************

DockMixer::DockMixer( os::Path cPath, os::Looper* pcDock ) : DockPlugin()
{
	os::File* pcFile;
	os::ResStream *pcStream;

	m_pcDock = pcDock;
	m_bCanDrag = m_bDragging = false;
	m_cPath = cPath;

	/* Load default icons */
	pcFile = new os::File( cPath );
	os::Resources cDockCol( pcFile );
	pcStream = cDockCol.GetResourceStream( "icon24x24.png" );
	
	m_pcDockIcon = new os::BitmapImage( pcStream );
	delete( pcFile );

	pcFile = new os::File( cPath );
	os::Resources cDragCol( pcFile );
	pcStream = cDragCol.GetResourceStream( "icon48x48.png" );
	
	m_pcDragIcon = new os::BitmapImage( pcStream );
	delete( pcFile );

	
	
	
}

DockMixer::~DockMixer( )
{
	
	delete( m_pcDockIcon );
	delete( m_pcDragIcon );
	
}

String DockMixer::GetIdentifier()
{
	return( "Mixer" );
}

void DockMixer::Paint( const Rect &cUpdateRect )
{
    FillRect( GetBounds(), get_default_color( COL_NORMAL ) );
	SetBgColor( get_default_color( COL_NORMAL ) );
	SetDrawingMode( DM_BLEND );
	m_pcDockIcon->Draw( Point(0,0), this);
}


void DockMixer::AttachedToWindow()
{
	// Create media manager 
	m_pcManager = os::MediaManager::Get();
	
	// Create window
	m_pcWindow = new MixerWindow( m_pcManager, this, Rect( 0, 0, 50, 100 ) );
	m_pcWindow->Start();
	m_bWindowShown = false;
}


void DockMixer::DetachedFromWindow()
{
	if( m_bWindowShown )
		m_pcWindow->Terminate();
	m_pcManager->Put();
}

Point DockMixer::GetPreferredSize( bool bLargest )
{
	return m_pcDockIcon->GetSize();
}

void DockMixer::MouseMove( const os::Point& cNewPos, int nCode, uint32 nButtons, os::Message* pcData )
{
	if( nCode != MOUSE_ENTERED && nCode != MOUSE_EXITED )
	{
		/* Create dragging operation */
		if( m_bCanDrag )
		{
			m_bDragging = true;
			os::Message* pcMsg = new os::Message();
			BeginDrag( pcMsg, os::Point( m_pcDragIcon->GetBounds().Width() / 2,
											m_pcDragIcon->GetBounds().Height() / 2 ), m_pcDragIcon->LockBitmap() );
			m_bCanDrag = false;
		}
	}
	os::DockPlugin::MouseMove( cNewPos, nCode, nButtons, pcData );
}


void DockMixer::MouseUp( const os::Point & cPosition, uint32 nButtons, os::Message * pcData )
{
	if( m_bDragging && ( cPosition.y > 30 ) )
	{
		/* Remove ourself from the dock */
		os::Message cMsg( os::DOCK_REMOVE );
		cMsg.AddPointer( "plugin", this );
		m_pcDock->PostMessage( &cMsg, m_pcDock );
		return;
	}
	m_bDragging = false;
	m_bCanDrag = false;
	os::DockPlugin::MouseUp( cPosition, nButtons, pcData );
}

void DockMixer::MouseDown( const os::Point& cPosition, uint32 nButtons )
{
	MakeFocus( true );
	if( nButtons == os::MOUSE_BUT_LEFT )
		m_bCanDrag = true;

	/* Display the mixer window */
	if( !m_bWindowShown )
	{
		m_pcWindow->MoveTo( ConvertToScreen( GetBounds() ).left - 25 + GetBounds().Width() / 2, ConvertToScreen( GetBounds() ).bottom );
		m_pcWindow->Lock();
		m_pcWindow->Update();
		m_pcWindow->Show();
		m_pcWindow->MakeFocus();
		m_pcWindow->Unlock();
		m_bWindowShown = true;
	} else
		m_pcWindow->MakeFocus();
	os::DockPlugin::MouseDown( cPosition, nButtons );
}


//*************************************************************************************

extern "C"
{
DockPlugin* init_dock_plugin( os::Path cPluginFile, os::Looper* pcDock )
{
	return( new DockMixer( cPluginFile, pcDock ) );
}
}

