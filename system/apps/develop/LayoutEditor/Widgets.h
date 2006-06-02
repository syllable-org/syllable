#ifndef _WIDGETS_H_
#define _WIDGETS_H_

#include <util/string.h>
#include <util/variant.h>
#include <util/message.h>
#include <gui/layoutview.h>
#include <storage/streamableio.h>
#include <typeinfo>

enum PropertyType
{
	PT_UNKNOWN,
	PT_INT,
	PT_STRING,
	PT_FLOAT,
	PT_BOOL,
	PT_STRING_SELECT,
	PT_STRING_LIST
};

class WidgetProperty : public os::Message
{
public:
	WidgetProperty()
	{
	}
	WidgetProperty( int nID, PropertyType eType, os::String zName, os::Variant cValue )
	{
		SetCode( nID );
		AddInt32( "type", eType );
		AddString( "name", zName );
		AddVariant( "value", cValue );
	}
	PropertyType GetType()
	{
		int32 nType;
		FindInt32( "type", &nType );
		return( (PropertyType)nType );
	}
	os::String GetName()
	{
		os::String zName;
		FindString( "name", &zName );
		return( zName );
	}
	os::Variant GetValue()
	{
		os::Variant cValue;
		FindVariant( "value", &cValue );
		return( cValue );
	}
	void SetValue( os::Variant cValue )
	{
		RemoveName( "value" );
		AddVariant( "value", cValue );
	}
	bool GetSelection( os::String* pcString, int nIndex = 0 )
	{
		return( FindString( "selection", pcString, nIndex ) == 0 );
	}
	void AddSelection( os::String cValue )
	{
		AddString( "selection", cValue );
	}
	void ClearSelections()
	{
		RemoveName( "selection" );
	}
};

class Widget
{
public:
	virtual const std::type_info* GetTypeID() = 0;
	virtual const os::String GetName() = 0;
	virtual const os::String GetCodeName()
	{
		return( GetName() );
	}
	virtual os::LayoutNode* CreateLayoutNode( os::String zName ) = 0;
	virtual os::LayoutNode* GetSubNode( os::LayoutNode* pcNode )
	{
		return( pcNode );
	}
	virtual std::vector<WidgetProperty> GetProperties( os::LayoutNode* pcNode ) {
		std::vector<WidgetProperty> cDummy;
		return( cDummy );
	}
	virtual void SetProperties( os::LayoutNode* pcNode, std::vector<WidgetProperty> cProperties )
	{
	}
	
	virtual void CreateCode( os::StreamableIO* pcFile, os::LayoutNode* pcNode ) = 0;
	virtual	void CreateCodeEnd( os::StreamableIO* pcFile, os::LayoutNode* pcNode )
	{
	}

	void CreateAddCode( os::StreamableIO* pcFile, os::LayoutNode* pcNode )
	{
		char zBuffer[8192];
		sprintf( zBuffer, "m_pc%s->AddChild( m_pc%s, %f );\n", pcNode->GetParent()->GetName().c_str(), pcNode->GetName().c_str(), pcNode->GetWeight() );
		pcFile->Write( zBuffer, strlen( zBuffer ) );
	}
};

os::String ConvertString( os::String zString );


#endif



















